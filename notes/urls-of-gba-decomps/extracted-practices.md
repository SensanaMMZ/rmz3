# Practices extracted from other GBA decomps

Survey date: 2026-07-23. Every repo in `list-of-decomps.md` was researched
(clones + raw files; all claims below carry their source). This document is
**additive**: `notes/matching-workflow.md` remains the procedure of record.
This is the knowledge base of levers, idioms, and tools the rest of the scene
uses, mapped onto our open problems.

The single biggest structural finding: **this community fixes systematic
codegen deltas inside agbcc behind `-f` flags, not per-function in C.**
pret's `-fprologue-bugfix`, jiangzhengwenjz's `-f2003-patch`, Dream-Atelier's
`-ftst`, StanHash's `-mtpcs-frame` restoration — all are small, published
compiler patches that made whole classes of mismatches disappear. Our agbcc
already accepts `-fhex-asm`, which is a pret-family custom flag, so these
forks' patches should graft cleanly.

## 1. Compiler-flag levers, mapped to our pain points

| our pain point | lever | source |
|---|---|---|
| spurious `push {lr}` / prologue-shape diffs | `-fprologue-bugfix` — newer agbcc caches `current_function_has_far_jump` and the stale value forces lr saves; the flag restores old behavior. Documented: "needed to produce matching code for certain GBA games". Likely already in our binary (pret family). Does NOT work with old_agbcc (SAT-R's makefile comment). | [pret/agbcc gcc/toplev.c](https://github.com/pret/agbcc/blob/master/gcc/toplev.c) ~L735, gcc/thumb.c ~L719 |
| redundant compares the compiler jump-threads away; shift-then-compare folds; wrong-signedness conditions | `-f2003-patch` — models a vendor compiler patch dated 03-OCT-2003. One hunk in `combine.c simplify_comparison` (~L10181): changes when `(x >> N) cmp C` folds to `x cmp (C << N)` (stricter overflow check, unsigned-condition conversion for logical shifts). **rmz3 shipped 2004-04, after this patch date** — same era as MZM (2004-02) and katam, which both need it. | [jiangzhengwenjz/agbcc](https://github.com/jiangzhengwenjz/agbcc) branch `new_newlib_pret`, gcc/flags.h "thumb_patch03-OCT-03" |
| mmbn4 `tst r0,r0` tails instead of `ands`+`cmp` | `-ftst` — exists as a real flag in the Klonoa: Empire of Dreams fork; their m4a_1.c is compiled `old_agbcc -ftst`. Their README also states the pool-load regalloc fact we observed: "old_agbcc assigns the first literal pool load to **r2**, while agbcc assigns it to **r3**". | [Dream-Atelier/kl-eod-decomp](https://github.com/Dream-Atelier/kl-eod-decomp) README, [Dream-Atelier/agbcc](https://github.com/Dream-Atelier/agbcc) |
| mmbn4 `push {r7, lr}` frame form under `-O -mno-thumb-interwork` | `-mtpcs-frame` — FE6 hit exactly one file with a frame-pointer prologue and solved it by restoring GCC 2.9's `-mtpcs-frame` option in a fork, applied per-file (`%/main.o: CFLAGS += -mtpcs-frame`). | [FireEmblemUniverse/fireemblem6j Makefile](https://github.com/FireEmblemUniverse/fireemblem6j/blob/main/Makefile) L308+, [StanHash/agbcc branch tpcs_frame](https://github.com/StanHash/agbcc/commits/tpcs_frame) |
| dead compares (unused_080e14d4 class) | `-foptimize-comparisons` — off-by-default comparison-sequence flag present in the pret-family flag table, wired into fold-const.c. Worth an A/B on the dead-compare holdouts. | pret/agbcc toplev.c f_options |
| cross-statement optimization we can't block | **`-g` is a codegen input on this compiler.** pokeruby/pokeemerald only match WITH `-g` (line notes act as optimization barriers; several "one line required to match with -g" comments), pokefirered matches WITHOUT it. Corollary: under `-g`, joining/splitting statements across lines is a legitimate matching lever. We build without `-g`; if the target kept redundancy we can't reproduce, try the function with `-g`. | pokeruby src/battle_message.c:463 et al.; pokeemerald Makefile L119 |
| struct-copy / builtin expansion diffs | `-ffreestanding` per-file (pokeemerald: `record_mixing.o`; pokefirered: two files) stops special treatment of memcpy-class builtins in one TU. | [pret/pokeemerald Makefile](https://github.com/pret/pokeemerald/blob/master/Makefile) L283–295 |

Order of experiments for a stubborn function: flags first (cheap, whole-class),
then pure-C nudges (§3), then GNU-extension escapes (§4), then permuter.

## 2. old_agbcc is a finite, known delta — the mmbn4 roadmap

`old_agbcc` is the same source tree built with `-DOLD_COMPILER`
([pret/agbcc gcc/Makefile](https://github.com/pret/agbcc/blob/master/gcc/Makefile)).
The complete list of gated differences (12 sites, 5 files):

1. **gcc/thumb.c ~L715** — far-jump tracking: new agbcc's sticky
   `current_function_has_far_jump` cache forces `push {lr}` prologues
   (`-fprologue-bugfix` reverts); old has no cache.
2. **gcc/thumb.c ~L1543** — `s_register_operand`: new adds a mode check and
   SUBREG unwrapping; old accepts more operand shapes → different reload and
   **register allocation** (the documented r2-vs-r3 first-pool-load split
   lives in this territory).
3. **gcc/function.c ~L6136** — new calls `use_return_register()` at epilogue
   expansion; old doesn't → r0 liveness at function tails differs (relevant
   to result-in-flags-looking tails).
4. **gcc/loop.c ~L7207** — increment→decrement loop conversion: old converts
   more aggressively (no `CONST_INT` guard) → count-up vs count-down shapes.
5. **gcc/unroll.c** (4 sites) — pseudo-register renumbering bounds differ
   during unrolling → regalloc tie-breaks differ.

For mmbn4: sweep {agbcc, old_agbcc} × {-O0, -O1/-O, -O2} × {-ftst,
-fprologue-bugfix, -mtpcs-frame} with its own `-mno-thumb-interwork`, across
several functions at once. Reference corpora for old_agbcc ground truth:
[Normmatt/bof](https://github.com/Normmatt/bof) (whole game = old_agbcc -O0;
`agb_sram.c` is a matching old_agbcc -O1 sample) and FE6 (whole game =
old_agbcc, ~24 files at -O0). Era pattern across the scene: 2002 games lean
old_agbcc/low -O; 2004 games lean new agbcc -O2 — matching our tree's shape.

## 3. The pure-C nudge catalog (pokeemerald existence proof)

pokeemerald is fully matched with **zero** asm fakematches and zero register
pins — every regalloc/emission-order fight was eventually won with plain C.
The documented nudges (each shipped in matched code, with comments):

- self-assignment: `x[0] = x[0]; // Needed to match` (battle_ai_script_commands.c:543)
- param→fresh local copy: `u8 n = n_; // Needed to match` (dodrio_berry_picking.c:4692)
- constants as locals: `int zero = 0, one = 1; // needed for matching` (battle_tv.c:1061) — the `movs #0` placement lever we already exploit
- explicit narrow casts to force `lsl/lsr` pairs: `if ((u8)x == 1)` (battle_anim_flying.c:665)
- hand-written shift pairs when combine won't make them: `y = y << 18 >> 18;` (pokefirered easy_chat_3.c:1665)
- kept arithmetic identities: `+ 1 + i - 1` (battle_anim_water.c:910)
- unused-but-updated locals: `s16 unusedVar = 1; ... unusedVar *= -1;` (battle_anim_water.c:1564)
- temp pointer for an increment: `u8 *v = &s->field; (*v)++;` (battle_util.c:1214)
- `do {} while (0);` statement barriers (pokeruby battle/anim/normal.c:1293)
- duplicated/dummy case labels to keep compare chains (pokeruby battle_ai_script_commands.c:403; pmd-red dungeon_vram.c:634 "any value >= 150 works")
- trivially-true conditions to keep dead compares: `if ((unk & 0x10000) == 0) // if (1); required to match` (fe6j ai_utility.c:499)
- return-type widening: "compiler needs to think func returns int (not u8) to match" (fe6j chapter.c:26) — the exact FUN_080e964c lesson we learned independently
- `*&var` forced reload: `(*&gMPlayJumpTable[1])(...)` (pokeruby m4a.c:1494; csm3 attribute_O2_1.c:700)
- loop-shape substitutions: "should be one while loop, but that doesn't match" (do/while + split condition), "won't match with while loop" (for)
- `volatile` parameters (pokepinballrs display.c:336 — "There is no reason, *ever*, to do this" — but it matched)
- dead ops to reproduce deleted code: `x += 0;` / `+ ZERO` dummy reads (pokepinballrs, pokefirered help_system_util.c:412)

Feed this list to the permuter as seed transforms and try them by hand on
near-misses before reaching for §4.

## 4. Sanctioned GNU-extension escapes (when pure C fails)

All accepted by agbcc, all used in shipped matching builds elsewhere, all
kept behind `#ifndef NONMATCHING`-style guards with a comment:

- `register int x asm("rN") = ...;` — hard register pinning (pmd-red ships 8, pokeruby 27, fe8u, sa2)
- `asm("" ::: "rN");` — clobber nudge to push allocation off a register (fe8u banim-ekrdragon-myrrh.c:126)
- `asm("" :: "r"(var));` — mark a value used, pinning induction/condition form (sa2 sprite.c:1035)
- `asm("" : "=r"(var));` — **value laundering: makes the compiler "forget" a known constant/range so a compare it would fold survives** (sa2 item_tasks.c:246). Direct counter-tool for our dead-compare class.
- `asm("" ::: "memory")` — emission-order barrier for loads/stores (tmc MEMORY_BARRIER; katam object.h)
- `({ expr; })` statement-expression fences — force evaluation/addition order: `EfxTmCpyExt(({gTmA_Banim + offset;}) + TM_OFFSET(5,5), ...)` (fe6j banim_ekrterrainfx.c:267); `r2 + ({ duration + 0x14; })` (fe8u)
- `{a++;a--;}` — pmd-red's `ASM_MATCH_TRICK` macro, documented in-tree: "changes how registers are allocated" (global.h L91)

## 5. The single-relocation pool anchor (FlushOAM class) — best evidence found

No repo documents our exact `global+0x400` case, but two point at the source
shape:

- **pokeruby pokenav.c:1619** — retail code contains a single relocation with
  a huge offset because the original source indexed **out of bounds off one
  base symbol**: `arr = ((u8*)&gSaveBlock1); ... arr[0x30F7]`. One symbol,
  one reloc, everything else is arithmetic.
- **fe8u AccessArray macro** (banim-ekrbattleintro.c:185) — matching form is
  `(*(typeof(&*(array)))((void *)(array) + (offset)))`: one base address,
  byte-offset arithmetic, no second literal.

Implication for FlushOAM: the original probably **never names offset 0 at
all** — it takes ONE address (plausibly `&gOamManager.p`-equivalent as a raw
`(u8*)&g + 0x400` or a pointer-to-tail struct view) and derives buffer, p,
and dispcnt from it arithmetically. Next attempts should write the anchor
into the source literally (`u8 *base = (u8 *)&gOamManager + 0x400;` then
negative offsets), possibly with a `({ })` fence to stop re-materialization.
This matches our earlier inference ("nothing names offset 0 directly") and
gives it a documented precedent.

## 6. Tools worth importing

| tool | what it does | why us |
|---|---|---|
| [StanHash/samefunc](https://github.com/StanHash/samefunc) | finds identical/similar ARM functions across ELFs | run over our ELF: any of the 362 stubs identical to an already-matched function is a free match; MMZ engine code repeats heavily |
| [SBird1337/cexplore](https://github.com/SBird1337/cexplore) / [octorock/cexplore](https://github.com/octorock/cexplore) | self-hosted Compiler Explorer running agbcc, preloaded project headers + diff layout | instant-feedback matching loop, no decomp.me round-trip; tmc's primary tool on the road to 100% |
| [WhenGryphonsFly/decomp-permuter-agbcc](https://github.com/WhenGryphonsFly/decomp-permuter-agbcc) | permuter fork scoped to ARMv4T/agbcc | also documents: out-of-range branches make agbcc emit `bl`, creating **false function boundaries** — audit stubs that might be tails of the previous function |
| tmc `genctx.sh` | preprocess all headers into one ctx.c | one-command decomp.me/cexplore context (we build ours ad hoc) |
| pret `.github/calcrom` / tmc `progress.py` / sa2 `scripts/progress.py` | progress % from linker map + NONMATCH greps, posted to Discord/shields.io | cheap public progress tracking; tmc tracks "matching" and "nonmatching" as two curves |
| fomt `finddata.py` / `findiwrams.py` / fe8u `resolve_pointers.py` | rewrite anonymous `.4byte 0x08xxxxxx` literals in asm into real symbols from the ELF symtab | INCCODE hygiene — complements our resolve_pool_refs.py on the asm side |
| pokepinballrs root `objdiff.json` + `permuter_settings.toml` | checked-in configs (objdiff `target_dir` of expected objects; permuter `compiler_command` = agbcc \| arm-none-eabi-as) | make our objdiff/permuter setup reproducible for anyone cloning |
| pokepinballrs `DEBUG.md` | source-level mGBA debugging: `-g` DWARF kept in ELF, GDB server, `hbreak` | template if we ever want live debugging of the matched ROM |
| pret `ramscrgen` | linker fragments controlling COMMON/BSS symbol order | only if we ever hit .bss ordering mismatches |

Build-system detail seen in tmc, mzm, katam, csm3, fomt: after every cc1
invocation they append `.align 2, 0 @ Don't pad with nop` (fomt does it per
section) so end-of-TU padding is zeros, not nops. If we ever see padding
diffs at TU boundaries, this is the fix.

## 7. Workflow conventions worth adopting

1. **Drafts live in-tree, compiling.** tmc/sa2 pattern:
   `NONMATCH("asm/x.inc", ret Func(args)) { ...WIP C draft... if (0) }` — the
   asm is what's emitted, the draft stays type-checked and permuter-ready,
   and `NON_MATCHING=1` flips every draft live. 204 uses in sa2; tmc rode
   this to 100%. For us: our 357 Ghidra drafts currently live outside the
   tree in build/; this pattern would put each next to its stub.
2. **Annotate every stubborn function with scratch URL + root cause.** sa2
   embeds 224 decomp.me links with match % ("100% (fake match): …/63L6J");
   fomt writes the *construct* that fails ("the nonmatching part is inlined
   FixedVec::resize, which may come up again") so one diagnosis solves the
   whole sibling family. We should tag each near-miss: `regalloc-tie`,
   `pool-anchor`, `jump-thread`, `combine-shift`, etc.
3. **Keep both bodies.** katam splits `#ifdef NONMATCHING` (ideal C, kept for
   readers) from `#ifndef NONMATCHING` (fakematch actually built) inside the
   same function — intent is never lost.
4. **Name override TUs for their flags.** csm3 literally names files
   `attribute_O1_1.c`, `attribute_O2_1.c` — functions binned by detected
   optimization level, makefile overrides keyed on the filename. Cleaner
   than remembering which file is special.
5. **Sister-ROM cross-validation.** pmd-red proves source forms by checking
   the sibling game's binary ("NOT optimized by blue's compiler which proves
   that's how it was written"); fe8u cites FE6 addresses the same way. Our
   equivalent: rmz2/rmz4 ROMs share this engine — when two source shapes
   both match rmz3, the sibling ROM can break the tie. laqieer's
   FE_GBA_Function_Library (cross-game function DB from decomp ELFs) is the
   scaled-up model.
6. **Per-file flag sweeps are normal, not exotic.** Every mature repo has
   per-file overrides, and they are almost always SDK libraries at -O/-O1 or
   old_agbcc (flash/sram/m4a/siirtc/libc) — exactly our mmbn4/agb_sram/m4a
   shape. pokeemerald even uses a separate ARM-mode cc1 (`agbcc_arm
   -quiet`) for one interrupt-handling file; if we ever meet an ARM-mode
   holdout, that is the precedent.

## 8. Negative findings (so nobody re-searches)

- **No repo documents the single-reloc pool-anchor problem as such.** §5 is
  the closest evidence; there is no compiler flag for it in any fork.
- **pret has no per-function match verifier and no fake-match detector** —
  whole-ROM sha1 only. Our fnbytes.py/objdiff flow is ahead of theirs.
- **No pret wiki matching docs exist** — the lore lives in source comments
  (extracted above) and Discord. Searching wikis again is wasted effort.
- **sma2 is a dead template skeleton** (one commit, 2019; asmdiff.sh still
  points at an FE8 ROM). Only datapoint: author judged SMA2 to be agbcc -O1.
- **goldensun has no C at all** (Camelot code resists agbcc; they know it) —
  useful only for its per-overlay `cmp` verification pattern.
- **mzm's residue at 99.89% is register swaps and branch layout** — the same
  two failure classes as our near-misses, unsolved even with a bespoke
  compiler fork. Some ties genuinely end there.

## 9. Experiment queue distilled from this survey

1. Check our agbcc binary for `-fprologue-bugfix` / `-foptimize-comparisons`
   support (it accepts `-fhex-asm`, so it is pret-family); if absent, the
   patches are small and public.
2. mmbn4 sweep (§2): flags × compilers matrix over several functions at
   once, including `-ftst` (build the Klonoa fork) and `-mtpcs-frame`
   (StanHash branch).
3. Re-attempt FlushOAM with the §5 single-base arithmetic shapes.
4. Re-attempt unused_080e14d4 with `asm("" : "=r"(var))` value laundering
   and the `if (1)`-style kept-compare trick, and A/B `-f2003-patch` /
   `-foptimize-comparisons` / `-g` on it.
5. Run samefunc over our ELF for free stub matches.
6. Audit small "stubs" adjacent to large functions for the false-boundary
   `bl` artifact before attempting them as standalone functions.
7. Port a calcrom-style progress script over our linker map (matching vs
   nonmatching curves).
