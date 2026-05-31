# agbcc matching idioms & the intractable-function playbook

A catalog of the **source-level idioms** that make agbcc (legacy GCC 2.x, Thumb-1,
`-O2 -fshort-enums`) emit byte-identical code, plus the tooling and strategy for
the functions that resist a straight decompilation.

Companion docs: `DECOMP.md` (toolchain/status), `DECOMP_WORKFLOW.md` (the
hunt→split→edit→verify loop). This file is specifically about **why a function
won't match and what to write instead.**

Build gate: `make compare` hashes `rmz3.gba` against
`ff7a801776dc76e6d8c7ef73a6660ae732934a3f`. Force-rebuild the `.o` before trusting
any match (`rm build/rmz3/<path>.o && make ...`) — stale objects lie.

---

## 0. The two oracles + the permuter (use these, don't eyeball)

| Tool | What it is | Use |
| ---- | ---------- | --- |
| `tools/diff.sh <Func>` | objdiff (Rust disassembler) vs `expected/` snapshot | **primary** % match + side-by-side |
| `tools/diff2.sh <Func>` | devkitARM `objdump --disassemble=<Func>` vs `expected/`, reloc-folded | **independent second opinion** — two disassemblers agreeing is a strong signal; disagreement = tooling bug |
| `tools/refresh-expected.sh <file>` | snapshot the matching `.o` into `expected/` | run after every committed match |
| decomp-permuter | randomized source mutation | the hammer for register-allocation/scheduling mismatches — see §3 |

`tools/asm-differ/` exists but its whole-binary mode **does not work on this GBA
map** (no "load address"/LMA line; the maintainer already flagged it unreliable).
Use `diff2.sh` as the second oracle instead.

A residual whose **only** diff is a tail `.word <abs>` vs `.word .rodata` is a real
match — those are table relocations resolved at link time.

---

## 1. The idiom catalog (by symptom)

Each entry: the asm symptom → the source that reproduces it.

### Register allocation

- **Build-then-copy of a slot pointer (CSE).** asm builds a struct-slot address in
  a scratch reg, derefs, then copies the address to a callee-saved reg
  (`adds r0,r4; adds r0,#0xbc; ldr r1,[r0]; adds r5,r0,#0`). A named
  `slot = (T**)((u8*)p + 0xbc)` builds directly in r5 (wrong). **Fix:** inline the
  full `*(T**)((u8*)p + 0xbc)` expression at *every* use — no named variable — so
  CSE keeps the address in a scratch and copies to the saved reg. (CapsuleCannon,
  Claveker.)

- **Load a global field once, keep it in its home reg (CSE).** `gCurStory.s.gameflags[4]`
  read through a named `u8 gf = ...` local makes agbcc load to r0 then *copy* to r1
  (`ldrb r0,[..]; adds r1,r0,#0`). Inlining `gCurStory.s.gameflags[4]` directly at
  both uses lets agbcc CSE it to a **single load that stays in r1**, matching.
  (GeneratorCannon_Update.)

- **Materialize a value straight into its home register.** Target computes a `(u8)`
  cast result directly into a callee-saved reg (`lsrs r5, r0, #24`); agbcc computes
  in a scratch then copies (`lsrs r0; adds r5,r0,#0`, +2B and often a `.short` pad).
  No direct C knob — wrap a *later* statement that uses the value in `do { ... } while(0)`
  to perturb the allocator into emitting it directly. **Permuter-found; don't
  hand-guess.** (Gallisni_Update; the path-B `prevStatus = sf` write. Same nudge
  finished GeneratorCannon_Update.)

- **`bool8` vs `s32` at the test site.** `if (helper(p))` where the helper returns
  `bool8` makes agbcc zero-extend (`lsls#24`) before the branch. Declare the helper
  `bool8` if the asm has that `lsls#24`; declare/define it `s32` if the asm tests a
  bare `cmp r0,#0`. (GeneratorCannon FUN_0808c3ec = bool8; Lamplort FUN_0806ce5c = s32.)

- **bool8 guard merge — tail-merge, don't store a variable.** Two if/else branches
  each producing a bool8 guard tested by a shared `if (guard) return;`: a
  `bool8 guard` local forces `lsls#24; lsrs#24; cmp` (extra lsrs). **Fix:** drop the
  variable, write a separate inline `if (helper(p)) return;` in *each* branch — agbcc
  tail-merges the identical returns into one `lsls#24; cmp`. (TileCannon.)

- **Shared-store temp: use `s32`, not `u8`.** Two branches funnel a value into one
  shared store of a u8 field. A `u8 v` truncates at the assignment (`lsls#24; lsrs#24`,
  +4B → ROM overflow); `s32 v` keeps the raw value and lets the final `strb` truncate.
  (Anubis timer.)

### Control flow / scheduling

- **Duplicated despawn blocks beat goto/merge+temp (tail-merge).** When two despawn
  paths converge to one shared tail in the asm (clear FLIPABLE, store flags, EXIT_BODY,
  SET_ROUTINE), that tail is agbcc *tail-merging two fully-duplicated
  `if(...){ ...; return; }` blocks* — NOT a hand-written `goto merge` with a carried
  `fl` temp. The carry temp forces the half-cleared flags into the wrong register
  (an r0/r1 swap neither hand-tuning nor the permuter could flip). Write the two
  blocks out in full; agbcc merges the common suffix AND keeps flags in r0.
  (GeneratorCannon_Update — `fac7cf7a`.)

- **Prevent range-folding of consecutive int compares.** Testing `mode[1]` against
  `{2,3,5,4}` as four `cmp;beq`: writing `if(m==2||m==3||...)`, a switch, or `&&` lets
  agbcc fold the consecutive pair `2,3` into a range check `(m-2)<=1`. **Fix:** one
  statement each — `if (m==2) goto skip; if (m==3) goto skip; ...` — in the asm's cmp
  order.

- **Signed vs unsigned compare + branch direction.** `x & 3` on signed `s32` →
  signed compare (`ble`/`bgt`). For unsigned (`bls`/`bhi`) make it `(x & 3U) > 1`.
  agbcc keeps the *first-written* if-branch as fall-through; put an out-of-line block
  in the `else`. (HanumachineObj blink.)

- **Load/declaration order sets register & load order.** Declaration order of plain
  locals sets which register each lands in and the load order. To evaluate a field
  load *before* another compare operand, hoist it to a local right before the `if`
  (`s32 sea = gOverworld.sea; if (sea > ...)`). For "compute address early, defer the
  load," use a *pointer* local (`s32* ppx = (s32*)((u8*)p+0xb4); ... cx - *ppx`).
  (Shelluno, PantheonAqua sea-sink.)

### Value materialization

- **Redundant `& 0xff` before `& 1`.** asm masks `(work+1)&0xff` then `&1` (two
  `movs;ands`). `x & 0xff & 1` folds to `x & 1`; a `u8` cast gives `lsls#24;lsrs#24`.
  **Fix:** split the mask into its own statement — `blink = work+1; work = blink;
  blink &= 0xff; if (blink & 1)`. (CarrybeeG.)

- **`gOverworld.sea` is a field, not a raw cast.** When asm shows
  `ldr =gOverworld; ldr =0x2C00C; adds; ldr [r0]`, write `gOverworld.sea` (macro
  `SEA`), NOT `*(s32*)((u8*)&gOverworld+0x2C00C)` — the raw cast makes agbcc
  reassociate the constant onto the other comparison operand.

- **Struct-copy a Coord** (`(p->s).coord = par->coord`) to get
  load-both-then-store-both instead of sequential load/store.

### Family pattern

- **Boss/element-slot Update.** Many bosses share: an alive check
  `if ((!dead && *(s16*)(p+0xa4)) || (gStageRun.missionStatus & 8)) goto alive;`
  (missionStatus = gStageRun+8, bit3 = FAIL); an element child slot at p+0xb4/+0xc4
  cleared on kill / spawned via `ApplyElementEffect(idx, &p->s, &sElementCoord)` with
  a shared store through a temp; then a guard helper and a two-table dispatch (first
  table often NULL-checked). Inline the slot expression to avoid an extra
  callee-saved push. (Cubit, Hanumachine, LocomoIF, Anubis.)

### Mechanical

- **`--p->s.work[N] == 0`** needs `u32 w = p->s.work[N] - 1; p->s.work[N] = w; if (w == 0)`
  to avoid a redundant lsl extension.

- **Split `.inc` header.** Splitting a `_p1.inc` into `_a`/`_b`: the tail half loses
  the file header, so `adds r0,r0,r1` errors "not supported in Thumb16". Prepend
  `.include "asm/macros.inc"` / `.syntax unified` / `.text` to the `_b` half. (Or use
  `tools/split_inc_multi.py`, which handles this.)

---

## 2. The intractable categories — what's actually hard

"Intractable" is a spectrum. The inverse problem is: *find the source whose agbcc
output equals these bytes.* It's hard when the bytes encode a compiler decision no
surface C reliably reproduces.

1. **Register allocation / scheduling.** *Mostly solved now* via the permuter (§3) +
   the idioms above. Gallisni and GeneratorCannon — asm even upstream — are now
   byte-perfect C. Three sub-cases, hardest last:
   - materialize-into-home-register → `do/while(0)` nudge (solved).
   - tail-merge vs carry-variable → duplicated blocks (solved).
   - **compiler-is-too-good** → the target is *less efficient* than agbcc's natural
     output (redundant copies, a constant spilled to r8 under pressure you can't
     manufacture). You can't ask a compiler to be deliberately worse. **Beetank_Update
     is the standing example — left as asm, asm upstream too.**
2. **RNG / fixed-point bit-extraction** (Wormer, Projectile31, BeeServer). Inlined LCG
   (`*0x343FD + 0x269EC3`) + masks, duplicated per call. Fiddly but tractable with
   careful parenthesization/typing.
3. **Jump-table switches** (`mov pc` — Actor20/31, IceBlock, Ripple). agbcc decides
   case-by-case between a branch chain and a jump table via an internal density
   heuristic. Reshape the case labels to hit it — brittle.
4. **Long / context-heavy** (Seimeran, Shellcrawler, MettaurSwim, PantheonGuardian,
   Enemy59, …). Not impossible, just *long* — cumulative micro-decisions. Grind with
   the oracles. (Their smaller *helper* functions are often already C upstream — §4.)

**Bottom line:** categories 1–4 are mostly tractable with the permuter + idioms; the
only permanent holdouts are the "compiler produced *worse* code than your C will"
cases (beetank). Leaving a handful as `NAKED`/INCASM asm is a respectable answer —
upstream does the same.

---

## 3. The permuter recipe (the hammer for §1)

The decomp-permuter is wired and **proven** (it landed Gallisni and GeneratorCannon).
The key enabling patch: `objdump.py`/`scorer.py` isolate the target symbol with
`--disassemble=<func>` (nested-repo commit `004daa5`), so it runs `--no-prune`
(faithful full-translation-unit codegen) yet scores only the function. Without that,
the pruned base.c diverges from the real build and finds don't transfer.

Reusable recipe (works first try on the regalloc class):

1. Write your best near-miss **C** into the `.c` (the function must be C, not still
   asm). Keep sibling functions via a split inc (`tools/split_inc_multi.py` or
   `head -N`); place the new C exactly where the asm function was so the ROM layout
   is identical.
2. **Before editing**, `cp` the matching build's real `.o` aside as the byte-exact
   target.
3. `python tools/decomp-permuter/import.py --keep --no-prune <c> gtarget.s`, where
   `gtarget.s` is a trivial `glabel <Func>` / `bx r0` stub.
4. Overwrite the scratch `target.o` with the real `.o`, then `objcopy -x target.o`
   to strip local symbols (else every branch label mismatches and inflates the score
   ~+7 per branch).
5. `python tools/decomp-permuter/permuter.py nonmatchings/<Func>/`.
6. A candidate whose only isolated diff is tail `.word .rodata` relocs is a real
   match — **verify the full ROM SHA** (`rm rmz3.gba && make ... | grep OK`), not just
   the isolated score, before claiming it.

Tips: if it stalls, **ratchet** — copy the best `output-*/source.c` over `base.c` and
re-run from there. Watch what mutation it found (often an `inline_fn` wrapper or a
`do{}while(0)`) and fold the *idea* into clean source. For the compiler-too-good case,
the only untried lever is a `[weight_overrides]` block cranking temp/copy-insertion
passes with an hours-long run — low confidence.

---

## 4. Porting from upstream `mmzret/rmz3`

Both forks decompile the same byte-identical ROM, so `FUN_<addr>` and named functions
share names — directly comparable. This fork is **well ahead overall** (≈625 functions
are C here but asm upstream), but **68 functions are C upstream and still asm here** —
free ports (mind **signature drift**: upstream uses `Player*`/`Object*` where this fork
uses its own structs; adapt types and re-verify the SHA). Fetch bodies from
`raw.githubusercontent.com/mmzret/rmz3/main/<path>`.

Notably, several are *helpers inside the "intractable" files* (the `*_Update` stays
asm, but its helpers are portable): `unk_59` (Enemy59) ×4, `seimeran` ×4,
`mettaur` ×3, `phantom` ×3, `hellbat` ×3.

Portable candidates by file (68 total):

```
vfx/unk_64 ×7   vfx/unk_33 ×5   enemy/unk_59 ×4   enemy/seimeran ×4
cyberelf/unk_0 ×4   vfx/pantheon_aqua ×3   projectile/unk_20 ×3   enemy/mettaur ×3
boss/phantom ×3   boss/hellbat ×3   weapon/saber_smash_elec ×2   solid/unk_27 ×2
projectile/unk_16 ×2   enemy/pantheon_aqua_mod_obj ×2   boss/copy_x ×2
+ singletons: weapon/{reflect_laser,minigame_rod}, vfx/{unk_65,unk_59,unk_51,unk_41,
unk_38,unk_20,icebon_icedust}, solid/{unk_44,unk_37,unk_25,seagulls},
projectile/unk_06, player/minigame/leviathan, boss/{phantom,hellbat} extras, …
```

Regenerate the exact list anytime by name-diffing C-definitions (`<type> name(...) {`)
against `thumb_func_start` names across the two trees.

---

*Maintained alongside the agent memory notes (`reference_agbcc_match_idioms`,
`reference_decomp_tooling`, `project_open_todos`). Add an idiom here every time a new
agbcc quirk is cracked.*
