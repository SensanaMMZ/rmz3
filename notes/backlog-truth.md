# What is actually left to decompile

Written after finding that the objdiff ranking was pointing at solved work.

## The ranking was measuring a configuration the ROM never used

`tools/objdiff_rank.sh` compiles each file with `-DMODERN=1` and diffs every
symbol against the expected object. But `MODERN` swaps shared macros. The one
that matters is `SET_ENTITY_ROUTINE` (`include/entity/macros.h`):

```c
#if MODERN
  *(u32*)(entity->mode) = modeID;
  entity->onUpdate = (void*)((*functable[entity->id])[modeID]);
#else
  u32 tbl, id;  EntityFunc** routine_table;
  tbl = (u32)(functable);
  id = (entity->id) << 2;
  routine_table = (EntityFunc**)(tbl + id);   /* address computed FIRST */
  *(u32*)(entity->mode) = modeID;
  entity->onUpdate = (void*)(*routine_table)[modeID];
#endif
```

The `#else` form computes the table address before the mode store, so agbcc
emits the table load, then `movs r1,#2 / str r1,[r4,#12]`, then the deref. The
`MODERN` form stores the mode first and puts the constant in r0. Four
instructions different — enough to drop a byte-perfect function to ~92%.

So every function that calls `SET_BOSS_ROUTINE` / `SET_ENEMY_ROUTINE` / etc.
showed up in the ranking as a near-miss **while already matching the shipped
ROM byte-for-byte**. Verified at `MODERN=0` (the real build config):

| ranked | function | real status |
|---|---|---|
| 97.12% | CopyX_Update | already matches |
| 95.34% | Blazin_Update | already matches |
| 92.57% | tryKillChildre / tryKillDeathtanz / tryKillGlacierle | already matches |
| 91.60% | CreateBlazin | already matches |
| 89.89% | loadMugshot | already matches |

The whole top of the ranking was noise. `tools/verify_rank.sh` re-checks the
ranking at `MODERN=0` and labels each entry.

**Read the ranking's match% only for functions actually declared
`NON_MATCH`/`NAKED`.** For those it is a genuine "how close is the
reconstructed C body" measure. For anything else it is an artifact.

The mirror-image trap: for a *declared* holdout, `MODERN=0` emits the
`INCCODE`'d assembly verbatim, so "matches expected" is trivially true and
proves nothing. Neither configuration alone gives a straight answer, which is
why `verify_rank.sh` reports which population each function is in.

## The real backlog: 491 declared holdouts

`git grep -E '^(NON_MATCH|NAKED)\b' -- 'src/**/*.c'`, split by whether the
function has a `#if MODERN` C body:

- **129 have a reconstructed C body** — objdiff/permuter territory. The
  ranking's match% is meaningful here.
- **362 are pure `INCCODE` stubs** — no C at all. These need source
  reconstruction before any matching work can start, and they are the bulk of
  the remaining project.

Lists: `build/holdouts-withc.txt`, `build/holdouts-pure.txt`.

Files with the most reconstruction work:

| file | stubs |
|---|---|
| src/mmbn4.c | 18 |
| src/boss/omega_zero.c | 15 |
| src/overworld_layer.c | 14 |
| src/player.c | 14 |
| src/game/menu/main.c | 12 |
| src/intro.c | 9 |

This reframes the roadmap. The dominant cost is **reconstruction (362)**, not
register-tie cracking (at most 129, and many of those are the known-intractable
ties). Reconstruction is exactly what the Ghidra harness is for -- see
`tools/ghidra/symbolize_rom.md`. With named globals it resolves the pool
literals m2c reports as `M2C_ERROR`:

```
InitMotionLocation -> wStaticGraphicTilenums, wDynamicMotionPalIDs,
                      gDynamicMotionGraphicOffsets
FlushOAM           -> gOamManager, and the DMA3 register writes
IsInHazard         -> the 0x0200_23xx hazard array, stride 0xc
```

## Worked example: FlushOAM (still open)

First reconstruction driven by the Ghidra harness. Ghidra named the pool
literals (`gOamManager`, the DMA3 registers) that m2c reported as `M2C_ERROR`,
which made the shape readable immediately.

Two real corrections to the MODERN body came out of it, both now in:

- The write pointer lives in a **local variable**, not `gOamManager.p` re-read
  each iteration. The target keeps it in `r4` across the loop and stores it back
  only at the end; our version reloaded it every pass.
- The loop bound is a second local (`end`), and the buffer base is derived from
  it as `end - 128`, which is what produces the `0xfffffc00` pool constant.

That fixed the loop shape and the register roles (`r4` = pointer, `r5` = bound).

**What is still wrong:** the target's literal pool holds exactly *one*
`gOamManager` relocation — `gOamManager + 0x400`, i.e. the address of the tail
— and reaches everything from it: `[r5,#0]` is `p`, `[r5,#4]` is `dispcnt`, and
the buffer is `r5 - 0x400`. Ours emits **two** relocations, anchoring on
`gOamManager` itself (offset 0) and computing the tail at runtime.

Six spellings of that address were tried — `&gOamManager.p`,
`&gOamManager.buf[128]`, `gOamManager.buf + 128`, each crossed with naming vs
deriving the DMA source — and all six give the same two-relocation result. So
the anchoring is not controlled by how the address is *written*.

The remaining question is what makes agbcc route every reference to a global
through a single non-zero offset into it. Deriving `buf` via a pool-loaded
`-0x400` is *more* expensive than anchoring at offset 0, so the compiler only
does it when nothing names offset 0 directly — which suggests the original
source never mentions `gOamManager.buf` at all. That is a permuter-shaped
search, not a guess-the-spelling one.

Verified: the `MODERN=0` object is byte-identical to expected, so the ROM is
unaffected by this edit.

## Two findings from working the small end of the stub list

Ranked the 362 pure stubs by size (exact, from the symbol map): 22 are 64 bytes
or less, 138 are 256 or less. Small functions should be the cheapest matches, so
that is where to start.

### src/mmbn4.c -- CORRECTED: I was wrong, it is not out of scope

**Retracted.** An earlier version of this note said mmbn4.c "is not our
compiler's output" and told people to treat its 18 stubs as out of scope. That
conclusion was wrong, and the way it was reached is worth recording.

The evidence looked strong: the SIO helpers use `push {r7, lr}` / `pop {r7, pc}`
with r7 as the scratch base, and that form appears only 3 times in the whole
ROM, all in mmbn4. So it plainly is not built like the rest of the game.

The error was jumping from *"different from the rest of the game"* to *"outside
our toolchain"* without testing it. Three things falsify it:

1. **The Makefile already compiles mmbn4.c differently** and always has:
   ```make
   $(BUILD_DIR)/src/mmbn4.o: CFLAGS := -O -mno-thumb-interwork
   ```
   Every probe used the default `-mthumb-interwork -O2`. The codegen looked
   foreign because it was compiled with the wrong flags -- by me, not by Capcom.
   `-mno-thumb-interwork` is exactly what produces `pop {r7, pc}` instead of
   `pop {r1}; bx r1`.
2. **agbcc reproduces the prologue.** `-O -mno-thumb-interwork
   -fno-omit-frame-pointer` emits `push {r7, lr}` ... `pop {r7, pc}`. `-O2`
   turns frame pointers off, which is the only reason it never appeared
   elsewhere.
3. **`tools/agbcc/bin/old_agbcc.exe` exists** and the Makefile already uses it
   for `src/libs/m4a.o`. The Klonoa GBA project reports that old_agbcc
   allocates literal-pool loads to a different register than agbcc and that
   `-ftst` makes it emit `tst` instead of `ands`+`cmp` -- and the target here
   ends with exactly `movs r0, r0` / `tst r0, r0`.

What is still genuinely unexplained: the target puts the *global's address* in
r7 (`ldr r7, =gUnk02000d50`) rather than using r7 as a frame pointer, and ends
with a redundant `movs r0, r0` / `tst r0, r0` that looks like a
result-in-flags convention. Neither agbcc nor old_agbcc reproduced that in the
flag combinations tried so far.

So the honest status is **unknown and worth investigating**, not ruled out. The
next steps are to probe old_agbcc's `-ftst` against a function whose target
actually contains `ands`+`cmp`, and to sweep flag combinations against several
mmbn4 functions at once rather than one.

**General lesson: always compile a holdout with the flags its own object uses.**
`tools/verify_rank.sh`, `tools/objdiff_rank.sh` and every ad-hoc probe in this
session hardcode `-mthumb-interwork -O2`, so their verdicts are invalid for
`src/mmbn4.c` and `src/libs/agb_sram.o` (`-O -mthumb-interwork`) and for
`src/libs/m4a.o` (old_agbcc). Read the per-file overrides near the bottom of the
Makefile before trusting any diff.

### original note (kept for the record, conclusion retracted above)

#### how the wrong conclusion looked at the time

The tiny SIO helpers there use `push {r7, lr}` / `pop {r7, pc}` with **r7** as
the scratch base, plus oddities like `movs r0, r0` and `tst r0, r0` for a bool
return. That is frame-pointer codegen, not agbcc `-O2`.

Checked across the whole ROM: `push {r7, lr}` appears **3 times, all in mmbn4**.
agbcc never emits that form anywhere else in the game.

mmbn4.c is the MMBN4 link-cable and e-Reader code -- a separately-built library
rather than game code. Attacking those 18 stubs with our standard agbcc
invocation cannot work, and mmbn4.c is the single largest cluster in
`notes/holdouts-pure.md` (18 of 362). It should be treated as out of scope
until someone works out what built it.

### unused_080e14d4 (cyberelf.c) -- 46 of 52 bytes, blocked on a dead compare

A circular-list search, reconstructed from the Ghidra draft. `gElfHeaderPtr`,
the `&h->next` sentinel and the backwards `prev` walk all read straight off the
draft, and the neighbouring `close_menu_080e1540` confirms the idiom.

Everything up to the loop matches byte for byte. The gap is six bytes at the
tail. Reading the target's offsets:

```
0x18  beq  -> 0x24        sentinel exit, threaded straight to `return NULL`
0x1e  bne  -> 0x14        id mismatch, loop back
0x20  cmp  r1, r2         <-- reached only on the found path, where r1 != r2
0x22  bne  -> 0x2c            is already established. Provably dead.
```

So the ROM keeps a comparison it does not need, on a path where agbcc had
already proved the answer. Four loop shapes were tried -- `do/while` with a
compound condition, `for(;;)` with two breaks, assign-then-return, ternary --
and agbcc threads the compare away in every one, landing at 46 bytes. Writing
the sentinel expression inline instead of via a variable is worse (56 bytes,
spills to r4).

This is the "no C knob" class: the target contains a redundancy that agbcc will
not reproduce from any arrangement tried. Left as asm. It is an `unused_`
function, so the payoff is low -- recorded so nobody repeats the four attempts.

`tools/fnbytes.py` came out of this: byte comparison is the final arbiter, and
disassembly framing lies. This function is stored as raw data in the expected
object (it came from an INCCODE'd `.inc`), so `objdump -d` renders it as
`.word`s and a disassembly diff is meaningless.

### FUN_080ee328 (game/main.c) -- hand-written asm, never C

The existing comment on it guessed this, and the assembly confirms it:

```
lsrs r1, r1, #1          <-- work
push {r4, r5, r6, r7}    <-- prologue, second
```

A compiler always emits the prologue first, so this was written by hand and
there is no C source to recover.

`tools/detect_handwritten_asm.py` looks for that signature across the whole
backlog. It reports its own coverage on every run, because a detector that
silently parses nothing would otherwise report a clean bill of health -- the
current run scans **2,409 function segments, 2,353 of them with a prologue**.

The result is a useful negative: only **4** functions are hand-written
(`FUN_080ee328` plus three `push {r7, lr}` cases in mmbn4.c). The
reconstruction backlog is essentially all compiler output, so it is reachable
in principle. Full list: `notes/handwritten-asm.md`.

## The player attack-dispatch 5-cluster (2026-07-24 session findings)

`_zeroTryAttack`, `FUN_0802e338`, `air1`, `zero_wall_080303d4`,
`zero_ladder_08030ee0` — five declared NON_MATCH twins (116 B each,
identical modulo their IsAttackOK/attack callees). Structural facts
recovered from the byte diff (the MODERN drafts were wrong about all
three):

1. The early-return path is `z->forceWeapon |= 0xFF; return;` — an OR
   of the already-0xFF value (`movs #0xFF; orrs; strb`), not a plain
   return.
2. The attackMode stores are duplicated in BOTH arms of the if/else
   (no shared tail): the if-arm's `attackMode[1] = 0` materializes a
   fresh zero; the else-arm stores the IsAttackOK bool register
   (provably 0 there) — i.e. the original wrote `attackMode[1] = ok;`
   in the else arm, which also prevents the arms from cross-jumping.
3. THE REMAINING BLOCKER: our build CSEs `&z->usingWeapon` (z+0x128)
   from the call argument into callee-saved r5 (push {r4,r5,lr});
   the target recomputes it (`movs #0x94; lsls #1`) in the else arm
   (push {r4,lr}). With the address kept, our arms' stores become
   register-identical and cross-jump collapses them (96 B vs 116).
   `-fno-cse-follow-jumps -fno-cse-skip-blocks` together shift the
   result (98 B) proving the mechanism, but this file builds with
   stock flags, so the original source shape must break the CSE some
   other way. Tried and failed: do{}while(0) separator after the call,
   `= ok` alone, plain duplication. Next: decomp.me with root-cause
   tag `cse-keep / cross-jump`, or a source shape where the call
   argument expression is not visible to the else-arm store.

Solving any one of the five solves all five (verify per-file callee
names with build/scratch/twin_diff.py).

## FUN_080e58bc (bird.c) + twins FUN_080e2510/FUN_080e2b78 — 24-byte regalloc tie

Structure is fully correct at MODERN=0 (108/108 bytes, tail exact once
compiled with the real macro form; per-branch `u8* buf = e->buffer;`
reproduces the base+offset-1 load). The ONLY surviving diff is a
pseudo-register swap: ours allocates the p-copy to r2 and z to r3, the
target the reverse (fl follows: r1 vs r0). Tried and failed: e/z
declaration order swap (worse), fl-first declaration (no change),
Body-pointer block for the stores (much worse), explicit p-copy local
(macro conflicts). Root cause tag: regalloc-tie / pseudo-priority.
decomp.me candidate; solving it retires 3 functions (108 B each).
Test harness: build/scratch/e58bc/v3.c (best variant).

## FUN_08099ce4 / FUN_08099d88 (cattatank) — SOLVED (the blocker was arithmetic)

2026-07-25: both matched, ROM sha1 exact, NO data split needed. The
"non-integral sCollisions+0xB0" conclusion was wrong twice over: struct
Collision in this file is 24 bytes (not 28), and the current-build map
places cattatank .rodata at 0x0836a45c with sCollisions at +0x64
(routine 0x14 + sUpdates1 0x28 + sUpdates2 0x28), so the pool word
0x0836a550 is sCollisions + 0x90 = &sCollisions[6] exactly. Lesson
re-proven: NEVER hand-derive collision indexes — read the map
(build/rmz3/rmz3.map) and subtract. (original notes below)

The gravity-fall bodies match byte-for-byte in probe (switch with
fallthrough, PushoutToUp1 pair at +/-PIXEL(10), the isKilled tail) EXCEPT
the SetDDP pool word: the ROM points at sCollisions+0xB0, which is not an
integral index of our merged sCollisions[18] (28-byte entries). The
original file evidently declared its collision data as differently-split
arrays. Harness: build/scratch/batch4/t2.c (byte-identical mod that one
word, index [8] = +0xE0). To finish: reconstruct the file's true data
split (what symbol starts at 0x0836A550) and re-land both lifts.

## FUN_080b9cf8 / FUN_080b9db0 — slash-death VFX pair (SOLVED)

Both matched, ROM sha1 exact. Winning shape (t5): per call a scoped block
computing `u8 f = flags & X_FLIP; u32 hi = f ? 0x10 : 0;` (agbcc emits
the ternary branchless: rsbs/asrs #31/ands #0x10, and keeps f's (u8)
truncation because f has 2+ uses), then a branchy if:
`if (f) { arg = 1; arg |= hi; } else { arg = hi; }` — the TRUE arm MUST
be the compound two-statement form; `arg = hi | 1` and `arg = 1 | hi`
both materialize the 1 into a separate pseudo (movs r0,#1; mov r3,r0).
The false arm keeps its truncation because GCC 2.9 combine is per-BB and
the hi producer sits in the entry block. The second block assigns the
smoke-coord pointer BETWEEN hi and the if (interleave lever, same as
b963c). The identical CreateSmoke(2,...) if/else arms are real — agbcc
does not crossjump call-containing arms. Data = sSlashedEnemies[2]/[3],
de-static'd in gyro_cannon.c (symbol visibility only; ROM unchanged).

(original notes below)

184 B each; draft in build/ghidra-drafts/FUN_080b9cf8.c is UNRELIABLE
(Ghidra deduped the CreateSmoke arms and hid a VRAM pool word
0x06004008 that twin_diff shows). Real shape from disassembly: per
CreateSlashedEnemy call the flip arg is computed as
`-(u8)(flags & X_FLIP) >> 31 & 0x10` (branchless high nibble) plus a
BRANCHY low bit (`f ? r3 = 1|r1 : r3 = (u8)r1`), likely from
`u8 xf = (p->flags & X_FLIP) != 0;` then `(xf << 4) | xf` or a ternary
mix; coord recomputed per call, saved in r5 for the smokes; the
CreateSmoke if/else arms LOOK identical in the draft but 40 bytes are
missing vs our probe. Probe harness: build/scratch/b9cf8/t.c (144/184).
Next: transcribe the full 184-byte disasm and diff arm by arm.

## FUN_080b963c / FUN_080c2294 — follow-parent flicker pair (in progress)

208 B each. Draft fully decoded (parent-mode<2 gate with --work[2]
countdown, SetMotion(0xB01) phase, follow parent + props s32 offsets at
+0x74/+0x78, post-increment parity flicker on work[3], whitepaint-bitset
OR body-WHITE hide, else ENTITY_DIE). Best harness:
build/scratch/b963c/t2.c at 192/208 with diffs from byte 10 — the head
diverges early (suspect the compound && evaluation order, the
unk_28->mode[0] access form, or a kept-pointer for unk_28). The
whitepaint test idiom confirmed from entity.c:172:
`gWhitePaintFlags[id >> 5] & (1 << (id & 0x1F))`.

## SeaOtterElf_Init / BirdElf_Init — 216 B pair (in progress, m4 = best)

2026-07-24 update: best harness build/scratch/elf2/m4.c — 216/216 with
only 22 diff bytes, all in the buffer[12..15] block. SOLVED pieces:
plain `flags |= DISPLAY; flags |= FLIPABLE;` DOES keep two ORs in a
full-context compile (agbcc dead-store-elims the intermediate RMW; the
earlier fold-to-3 came from the compound v=1 form, NOT the plain form —
Elf0_Init ground truth); the r8 zero park is a pure compiler artifact
(no source var needed); `oam.xflip = FALSE` alone emits the
movs #0x11 / rsbs / ands trio (-0x11 == ~0x10 synthesis).
REMAINING 22 bytes: target does
`adds r2,#0x78 / movs r1,#0 / movs r0,#0x80 / lsls / strh r0,[r2]` then
buffer[12] strb r1 — i.e. buffer[14] addressed from the DEAD oam
pointer (r2=p+0x4a) and a FRESH zero in r1. Ours always picks r1+6
(from the buffer[8] pointer) and reuses the r8 zero for buffer[12].
Hypothesis: in the original, the zero temp allocates INTO r1 before the
strh, killing the r1=p+0xbc equivalence, which forces cse to the
r2+0x78 base. Tried and failed: hp var from p (m1/m2), plain (m3),
zz-before-strh (m4, closest), ob = oam-byte pointer + hp = ob+0x78
(t13 — cse still canonicalizes to r1+6). Next ideas: give the zero a
use that pins r1 (e.g. pass it through a u16 expression), or an
`s16 zero = 0` typed temp; or try `p->buffer[12] = 0; ... reordered`
permutations under the permuter.

(old notes below)

Structure decoded and size-exact at 216: player from buffer[0],
`struct Rect r = gZeroRanges[z->posture]` (packed x/y word read), init +
reset motion, DISPLAY|FLIPABLE via TWO unfused ORs (single ldrb/strb —
needs an intermediate, but the naive block-scoped `u8 fl` regressed the
head: the target parks a zero in r8 BETWEEN the two orrs), GetElfMotion(1)
SetMotion, xflip clears (elf0 forms), coord = z->coord + r, buffer[4/8] =
coord copy, u16 buffer[14]=0x200 addressed via the OLD spr pointer + 0x78,
buffer[12]=0 (zero parked in r1 before the strh), buffer[13]=0x20,
unk_2c=NULL, ROUTINE(UPDATE), tail call. Harnesses:
build/scratch/elf2/t.c (216/216, 135 diffs) and t2.c (220/216, 69).
Next: transcribe the flag-OR + zero-parking region exactly
(`0120 0022 9046 0843 0221 0843 b872`) — the r8 zero is probably
`(p->s).unk_2c = NULL` hoisted between the ORs by scheduling; try
declaring `struct Entity* none = NULL;` early or moving unk_2c=NULL
before the flag ORs.

## SeaOtterElf/BirdElf_Init addendum (8 variants)

The or-region bytes are IDENTICAL to target, only the r8-zero park
position rotates (pure emission order), and any named fl temp costs +4
(a spill — register pressure with r8 zero + struct-copy head). t8
(unk_2c=NULL hoisted before the ORs) restores 216B but emits the store
early. Harnesses t1..t8 in build/scratch/elf2/. Next ideas: eliminate
the fl temp but block the constant fold some other way (the |= two
statements with BLOCK_CROSS_JUMP between costs ldrb/strb pairs — no);
or accept the two-OR fuse is downstream of something else and try
transcribing the zero park via `struct Entity* n = NULL;` used for
BOTH xflip stores and unk_2c.

## doOmega1BallLaser2 / doGoldOmega1Laser2 — 284 B pair (close, in progress)

The old carve sketch (omega_white.c:196) is structurally right and the
old blocker is now understood: the "redundant (u8) truncation" is the
`(u8)(p->s).work[3]++ & 1` post-increment cast lever. Two corrections
found this round: the sine angle and bounce flag are the PROJECTILE's
own work[] at 0xB4 (`p->work[0]`, `p->work[1]`), NOT (p->s).work; and
the angle reads go through a KEPT pointer (`u8* ang` in r2, both
gSineTable reads via *ang, gSineTable held in r3, ldrsh index zero in
r6 — hence push {r4,r5,r6,lr}). Harnesses: build/scratch/laser2/t1.c
(head-exact, 268/284, no ang), t3.c (280/284 but head broken by the
case-0 brace scope). Next: declare ang in the else-scope (not inside
braced case 0), or at top; if head still breaks, transcribe register
roles from the disasm at 0x9D688. Solving retires both twins +
doOmega1Hoopshot (113/115, same file, same levers likely).

## b963c pair addendum (t4 state)

t4 = build/scratch/b963c/t4.c at 204/208 (was 192). Confirmed by disasm:
the gate is the ||-die form (die inline, bhi into it, countdown bne over
it); the flicker is a PLAIN post-increment (`work[3]++ & 1`, arms
|= DISPLAY on true / &= ~DISPLAY on false — no truncation temp); the
hide condition is a TRIPLE || starting with the parent body's
invincibleTime != 0 (Ghidra's draft hid it), then the whitepaint bitset,
then status & WHITE. Remaining: e allocated r3 (ours) vs r2 (target,
with a mid-block r2→r3 copy), and 4 missing bytes near the
invincibleTime address formation. Next: try `struct CollidableEntity*
e` typed directly (drops the casts, may change the addressing form),
or hoist `struct Body* b = &e->body;`.

## b963c pair SOLVED (t7)

FUN_080b963c + FUN_080c2294 both in-tree as C, ROM sha1 exact.
Final lever (NEW, added to workflow table): an unexplained register-copy
insn WEDGED INSIDE a condition evaluation (between the `ands` and its
`cmp`) means the source evaluates the condition into a NAMED temp, then
assigns ANOTHER variable, then tests the temp: `u8 t = work[3]++ & 1;
ce = (struct CollidableEntity*)parent; if (t) ...`. The intervening
assignment emits between the mask and the test, and the adds/copy
clobbers flags which forces the `cmp` to exist at all. Also confirmed:
Ghidra hid the invincibleTime leg of the triple-|| entirely.

## FUN_080c2500 / FUN_080c25f4 — 244B RNG-scatter pair (SOLVED)

Both matched, ROM sha1 exact, second try. Body: mode[2] switch; case 0
picks a scatter row via `u16 idx = *mp % 3` (mp = kept u16* to
props.unk25.unk_80, used again for SetMotion — the pool-anchor kept-
pointer form), base = PTR_s32_ARRAY_0836f2f0[idx] (lives in r8), then
d.y/d.x from table minus/plus LCG rands. THE lever: the first table
access must be hoisted into `const s32* e = base + work[1]*2;` AS ITS
OWN STATEMENT BEFORE the first `RNG = LCG(RNG)` — that single position
change snapped base into r8 and fixed every downstream register role
(37 diffs -> 0). The second access stays as a fresh expression (the RNG
global store aliases work[1], forcing the reload seen in the target).
Tail: `if (work[2] == 0 || --work[2] == 0) DIE` || form.

## Freeze-dispatcher trio FUN_080772f8/FUN_08093b50/FUN_08095124 (SOLVED)

All three matched (one C body each, per-file sUpdates1/sUpdates2), ROM
sha1 exact. bool8 return; gate order mode[1]!=7 then props-word==0;
case 0 = IsFrozen -> call both update tables, mode[3]++, UMG, TRUE;
case 1 = IsFrozen ? (status&0x20001)==0x20001 ? mode[3]=0 : TRUE
: mode[3]=0. Lever: the status test MUST be the == spelling with the
clear in the then-arm — crossjump then shares case 0's `movs r0,#1`
tail (bne backwards), 2 bytes shorter; the != / early-return-TRUE
spelling emits a second movs#1 and never merges. The two mode[3]=0
stores pick up per-arm known-zero registers (r5 = props word, r0 =
IsFrozen result) automatically.

## FUN_0809c664 / FUN_0809e7c0 — 504B bounce pair (SOLVED, first try)

Biggest pair of the run, matched on the first probe (502/504 with only
the sCollisions reloc word). Enemy/Projectile twins (unk_72.c /
blazin.c, sCollisions[1] in both — blazin index verified from its naked
pool: sCollisions base 0x0836ad60). Shape: triple die-gate
(parent-mode>1 / status&0x200 double-smoke with a stack struct Coord /
--work[2]) with agbcc auto-crossjumping the shared smoke+DIE tail;
case 0 = SetMotion(0xA304) + parent-xflip copy via constant-folded
SET_XFLIP(p,0)/SET_XFLIP(p,1) per arm; case 1 = && DDP-arm timer,
gravity clamp 0x700, PushoutToUp1 bounce (d.y=-0x300), wall pushouts
(Left at +0x800 when d.x>0, Right at -0x800 otherwise) with
SET_XFLIP(p, !((flags >> 4) & 1)) toggle and coord.x += push. All
levers were table lookups from this session's catalog — zero new ones.

## FUN_080ac700 — gold omega scatter debris (SOLVED)

280B, matched. c2500-family variant: status&0x200 head that CLEARS the
body (status/prevStatus/invincibleTime = 0, flags &= ~4, smoke, DIE);
scatter case uses PTR_ARRAY_0836c6f4[work[1] % 4] — the index MUST be
spelled % 4, not & 3: the umod strength-reduction route puts the value
in the and's dest register (ldrb r0 / movs r1,#3 / ands r0,r1), while a
literal & 3 materializes the mask first and accumulates into it. New
lever for the table: power-of-two % vs & are NOT interchangeable
spellings under agbcc. SetDDP fires at work[2]==0x32 (not a --timer),
tail is the ||-die form after UpdateMotionGraphic.

## CheckZeroHazard — hazard cluster opener (in progress, t3 = 192/188)

Harness build/scratch/hz/t3.c. SOLVED pieces: loop body field access
split is CONFIRMED — start.x/start.y each read through their OWN
pooled anchor (gOverworld+0x1DC / +0x1E0, i.e. address-constant
&HAZARD(0)->start.x + i*24 spelling), while w/h/objectLen go through
the gOverworld base register (W_TERRAIN_V2.objects[i].w spelling) —
mixing the two spellings stopped agbcc from hoisting a unified
objects-base (that hoist made t2 32 bytes SHORT). len IS hoisted to a
u8 local (r8). struct Hazard checks out: objects[] at gOverworld+0x1D4,
{id,attr,w,h,start,unk_10} stride 24.
REMAINING: whole-function register roles are shuffled vs target
(target pins z straight into ip with `mov ip, r0` as the FIRST insn,
x->sl, y->sb, count-ptr->r5, gOverworld->r6; ours puts z in r2, x in
ip). Same class as the e58bc tie. Ideas: declaration order of x/y/z
locals; taking &z->hazardCount as an explicit early local; permuter.
Siblings IsInHazard (0x080283EC, 0xA0) and IsAgainstHazard (0x0802848C,
0xD0) in src/player.c share the anchors — solve CheckZeroHazard first,
the levers transfer.

## mmbn4 sweep — RESOLVED: the module is hand-written assembly

The planned old_agbcc/-ftst flag sweep is unnecessary. Proof that no
compiler produced src/mmbn4.c's functions: they return results in the
CPSR FLAGS. SioLink_GetTransmitFlags ends `tst r0, r0 / pop {pc}` and
its caller (asm/mmbn4.inc:1681) does `bl SioLink_GetTransmitFlags /
beq ...` with NO comparison after the call — the branch consumes the Z
flag set inside the callee. SioLink_GetLocalPlayerId likewise ends
`movs r0, r0 / tst r0, r0` (value in r0 AND flags valid, serving both
caller styles — see asm/mmbn4.inc:836 vs :1030). C has no
flag-returning calling convention; this is a hand-asm SIO/e-Reader
link library (crt0-class). DISPOSITION: the 18 mmbn4 functions stay
NAKED permanently and come OFF the reconstruction backlog. This also
closes the old "mmbn4 is not our compiler's output" question from
notes/matching-workflow.md: the original observation was right, but
the reason is "not any compiler's output", not a flag difference.
The r7-as-global-base and push {r7,lr} frames are asm-programmer
idioms, consistent with this conclusion.

## Permuter campaign state (2026-07-25, end of cont 17)

Round 1+2 results: SeaOtterElf_Init plateaued at score 465 (best
mutation = the semantics-safe m1 store order: strh 0x200 before
buffer[12]=zz); CheckZeroHazard crept 1800 -> 1515 but its top
snapshots include SEMANTICS-BROKEN mutations — behavior-check anything
before lifting. Two 6-hour --stop-on-zero -j6 longruns launched; best
candidates accumulate in tools/permuter-setup/<fn>/output-<score>-N/.
Setup-recipe corrections for future targets are in the project memory
(preprocess candidates, replace NAKED stubs, trim multi-fn incs,
ASFLAGS -I repo, permuter_base_fix.py).

## FUN_080c3678 — VFX62 gravity-fall debris (SOLVED, free twin)

Match 107. Byte-identical C twin of the already-matched FUN_080b6b8c
(src/vfx/unk_17.c): coord += d, d.y += PIXEL(1)/4, UMG, then
FUN_080098a4 collision -> CreateSmoke(3) + DIE. Lifted verbatim into
src/vfx/unk_62.c, ROM sha1 exact first try. Only the two pool words
differ (per-file VFX motion consts) and they are data, not code shape.
Needed metatile.h (FUN_080098a4) added to unk_62.c includes.

## FUN_080b7e3c / FUN_080bd288 — 308B scatter pair (12 bytes, regalloc tie)

Best harness build/scratch/b7e3c/t4.c — instruction stream is IDENTICAL to
the target; only a 3-way register rotation remains (ours e->r4, RNG->r2,
LCG temp->r3; target e->r2, RNG->r3, temp->r4). Solved along the way:
  - tbl pool load must come from its own `const s32* const* tbl = ...`
    statement (173 -> 17 diffs);
  - the props u16 is a KEPT pointer (used for %3 and SetMotion) but the
    s32 at +0x78 is read DIRECTLY off p — mixing those two spellings is
    what stops agbcc hoisting a unified objects base;
  - flicker is `if (++(p->s).work[3] & 1)` used INLINE — a named u8 temp
    emits lsl/lsr #24, the inline pre-increment emits the target's
    `movs r1,#0xff; ands` (probe TU: build/scratch/b7e3c/probe.c, f6).
CORPUS CROSS-REFERENCE (tools/decomp_crawl.py, 50589 fns / 15 projects):
zero functions anywhere in the corpus emit our target's
`ldr base,[base] / ldr off,[p,#n] / lsl off / add off,off,base` window;
and every spelling of base+offset we tried (+=, single expr, named base,
&b[i], commutative swap) canonicalizes to base-as-accumulator. Conclusion:
the rotation is not reachable by source shape under -O2 -fshort-enums,
same class as e58bc/elf/hazard. decomp.me candidate (cite the corpus
evidence in the About text).

## MobNPC init cluster FUN_080da21c/320/5e8/6f0 (SOLVED, 4 x 120B)

Four byte-identical NPC initializers, one C body each, ROM sha1 exact.
Shape: flags |= COLLIDABLE; InitBody(b, sCollisions, &coord, 1);
b->parent = p; b->fn = NULL; three separate `sMotions[work[0]]` stores
to motion/m_c0/m_c2 (each re-loads work[0] — write them as three
statements, not one temp); unk_05 = 1; unk_04 = 0; unk_08 = 0;
mode[1] = 0; tail call MobNPC_Update.
TWO levers, both about WHERE the body pointer is created:
 1. `struct Body* b` must be a kept pointer used for the InitBody arg AND
    both field stores — otherwise the two stores recompute p+0xA0 and the
    function grows 4 bytes (124 vs 120);
 2. b must be ASSIGNED AFTER the flags |= line, not initialised at its
    declaration — an initialiser hoists `adds r4,#0x74` above the flags
    RMW and shifts 16 bytes of the head.
struct MobObject refined: unk_00[8] split into unk_00[4]/unk_04/unk_05/
unk_06[2], and unk_0c[4] into m_c0/m_c2 (two more motion_t).
asm/solid/mob_npc_pre_p1.inc split into _1.._5 to interleave the four C
bodies in ROM order.

## _zeroTryAttack five-pack (116B x5) — in progress, 96/116

Cluster: _zeroTryAttack(0802D020), FUN_0802e338, air1, zero_wall_080303d4,
zero_ladder_08030ee0 — identical modulo the second bl (zeroAttack /
FUN_0802e3b0 / zeroAirAtk / zeroWallAtk / zeroLadderAtk). Existing MODERN
body in src/player/zero/attack/ground/idle.c is WRONG in two ways, both
now proven from asm/wip/TryAttackGroundIdle.inc:
 1. the `forceWeapon == 0xFF` early-out is NOT a bare return — it does
    `z->forceWeapon |= 0xFF;` first (target: `movs r0,#0xff; orrs r0,r1;
    strb r0,[r2]`, reusing the already-loaded value);
 2. the `attackMode[0]=3; attackMode[1]=0;` pair is DUPLICATED into both
    arms, not shared after the if/else — and cross-jumping does not merge
    them because the ok-arm materialises a fresh 0 while the else-arm
    reuses the (known-zero) IsAttackOK result register.
Harness build/scratch/tryatk/t2.c reaches 96/116. REMAINING: (a) our
duplicated arms get cross-jumped back together (need whatever keeps the
two zero pseudos distinct), and (b) the target does NOT keep
`&z->usingWeapon` across the IsAttackOK call — it recomputes
z+0x128 for the later store, while ours CSEs it into r5 and pays a
push {r5}. Next: try spellings that stop the address CSE (store through
a separately-derived lvalue) and re-check whether that alone unblocks
the arm duplication.

### five-pack addendum (negative results, do not re-run)

Tried and ALL produce byte-identical 96B output (agbcc canonicalises them):
 v1 block-local `weapon_t* uw = &z->usingWeapon; *uw = w;`
 v2 hoisted `weapon_t* aw` used as the call argument
 v3 `z->usingWeapon = z->forceWeapon;` (no temp at the store)
 v4 `attackMode[1] = ok;` in the else arm (reading the target literally —
    it stores the known-zero ok register there)
So the 20-byte gap is NOT reachable by differentiating the two arms at
source level: agbcc cross-jumps them back together every time, and it
also insists on keeping &z->usingWeapon in a callee-saved register
(push {r4,r5,lr}) where the target recomputes z+0x128 and pushes only
{r4,lr}. Those two facts are linked — the kept pointer is what makes the
two arms identical enough to merge.
NEXT IDEA (untried): the target's two `=0x12B` pool entries are separate,
which hints the two arms were compiled from two textually separate
statement groups rather than one shared tail — consider that the original
may not be an if/else at all but two sequential `if` blocks each ending in
its own `zeroAttack` tail-merge candidate. Worth a corpus grep for
functions with a duplicated store pair around a shared call tail.

## Shotloid_Die / PantheonFist_Die (SOLVED, 108B x2, first try)

Standard _Die dispatcher plus a two-condition gate:
`if (work[1] == 0 && IS_METTAUR) { hide; EXIT_BODY; DISAPPEAR; }
 else (sDeads[mode[1]])(p);`
The only non-obvious part is the hide, which is the intermediate-u8
lever already in the table: `u8 fl = flags & ~DISPLAY;
flags = fl & ~FLIPABLE;` — one ldrb, two ands, one strb. Writing it as
two `flags &= ~X` statements would emit two load/store pairs.
EXIT_BODY supplies the body zeroing AND the trailing
`flags &= ~COLLIDABLE`, which is why that AND appears after the three
body stores rather than with the other two.

## FUN_080c6c60 / FUN_080c7250 (SOLVED, 112B x2)

Drift + parity flicker + collision death, one C body each, ROM sha1 exact.
coord += d; d.y += 0x40 (agbcc reuses the just-loaded d.y register, so
write it as the third statement); UpdateMotionGraphic; then the counter
flicker in the NO-TRUNCATION spelling (`work[2]++;` on its own line, then
`if (work[2] & 1)`) — see the trichotomy table in matching-workflow.md;
then `if (FUN_080098a4(coord.x, coord.y))` -> CreateSmoke(3) + DIE.
asm/vfx/unk_72.inc split into _a/_b around the lifted body.

## MobNPC inits, second wave (SOLVED): da01c/da114/da41c/da500

Four more from the same family, ROM sha1 exact. TWO body shapes:
 A (da114, da41c — 120B, &sCollisions[1]): identical to the da21c
   template except unk_05 = 0 instead of 1.
 B (da01c, da500 — 124B, &sCollisions[0]): the three motion stores come
   FIRST, before `flags |= COLLIDABLE`; m_c0 gets sMotions[work[0]] + 1;
   then unk_05 = 1, unk_04 = 0x30, unk_08 = 0x100, mode[1] = 1.
   agbcc computes 0x100 as 0x30 + 0xD0 off the just-stored unk_04 value
   and reuses the `1` for mode[1] — both fall out of writing the
   constants literally, no contortion needed.
The B shape's chained `adds r1,#2` addressing (0xBE -> 0xC0 -> 0xC2) is
what tells you the three motion stores are consecutive statements with
nothing between them; in shape A they are recomputed from p each time
because the flags/InitBody block sits in front.
All eight MobNPC initializers in this family are now C.

## FUN_080d7e5c (gray-h door collision, 92B) — 8 bytes, pure r2/r5 swap

Harness build/scratch/dgh/t4.c: 92/92, instruction stream IDENTICAL to
the target, only two registers transposed (target keeps `kind` in r2 and
the constant 1 in r5; we get the mirror). Reconstructed from scratch off
asm/solid/door_gray_h_collision.inc with field names borrowed from the
blue door's MODERN body (isAreaChange, gStageRun.vm.unk_004,
door->props.raw).
KEY TYPE FINDING: `kind` is `s8` in ENTITY_HDR, and the target reads it
with `movs r2,#8; ldrsb r2,[r4,r2]` — the register-offset form Thumb
requires for a SIGNED byte load. Declaring the local `u8` (or reading
inline) produces `ldrb` and a 4-byte-larger function; the local must be
`s32 kind = (z->s).kind;` to get ldrsb AND keep the value live for the
later `mode[2] = kind` store (that store is how the known-zero is
reused). `s8 kind` is WRONG too — it re-truncates and costs 4 bytes.
Tried and failed to flip the r2/r5 pair: `mode[2] = 0` literal (96B,
worse), explicit `!= 0` / `== 0` on the work[0] mask (identical).
Same regalloc-tie class as the rest; park.

### CORRECTION (2026-07-25): the FUN_080b7e3c permuter result was invalid

The run reported earlier as "permuter found nothing" never permuted that
function. Its settings.toml had been copied from the CheckZeroHazard dir,
so func_name still said "CheckZeroHazard"; the permuter printed
"Function CheckZeroHazard not found in base.c" and then ran against
nothing. Any conclusion drawn from that run is void. Re-run with the
corrected settings. The corpus evidence (zero hits for the target's
instruction window across 95k functions) is UNAFFECTED — that came from
the index, not the permuter.
Lesson: copying a permuter dir silently mis-targets it; audit loop added
to tools/permuter-setup/setup_fn.sh.

### FUN_080d7e5c permuter verdict (VALID run, 2026-07-25)

tools/permuter-setup/FUN_080d7e5c, settings verified to target the right
symbol (base score 40 = the r2/r5 pair). 1013 iterations, -j6: NO
improvement below base, no output-* snapshot produced. So the two-register
transposition is not reachable by the permuter's source mutations either.
Conclusion for the class stands: instruction-identical-modulo-registers
targets need either a different reconstruction of the surrounding code
(not this function alone) or acceptance as asm.

### FUN_080b7e3c permuter verdict (VALID re-run, 2026-07-25)

Corrected settings, 1354 iterations, -j4. Base score 180 -> best 160
(output-160-1). The mutation that scored better splits the SECOND LCG
into two statements:
    RNG = RNG * 0x343FD + 0x269EC3;
    RNG = (RNG << 1) >> 1;
instead of the one-expression LCG() macro. Applied to the real harness
(build/scratch/b7e3c/t5.c) this changes NOTHING measurable here: still
306B, still 12 masked byte diffs, still 27 differing instruction lines.
The permuter's score weights differences my masking differ ignores, so
its "improvement" is not a step toward the match.
NET: the 3-way register rotation survives a valid permuter run too. Same
disposition as FUN_080d7e5c. Do not re-run either without a new idea
about the SURROUNDING code — the tie is not inside these functions.

## unused_080e9d94 (hex formatter, 108B) — reconstructed to 90B, in progress

Right-aligned hex-string formatter into a 16-byte stack buffer, then
PrintUnicodeString. FOUR params, not the three the current NAKED
declaration in src/bg0/text.c claims — fix the decl when landing it:
    void unused_080e9d94(u32 v, u16 x, u16 y, u16 len)
Harness: build/scratch/hexs/t3.c (90/108, 62 diffs; t.c was 88/73).
CONFIRMED from the asm:
  * `v` is UNSIGNED — the target shifts with `lsrs r4,r4,#4`; an s32
    parameter gives `asrs` and is wrong;
  * the digit char needs its own u8 temp (`u8 ch = d + 0x30;`) so the
    `> 0x39` test emits the `ands r5` (0xFF) truncation, and the second
    store must recompute `d + 0x37` (writing `buf[i] = ch + 7` folds to
    `adds r0,#7` and loses 4 bytes);
  * x goes to ip and y to r7/r6 — both are u16 params zero-extended.
STILL WRONG (18 bytes): the target keeps the loop counter SHIFTED across
iterations — it holds `i << 16` in r0, does `asrs r2,r0,#0x10` to use it,
and closes with `subs r0,r2,#1; lsls r0,r0,#0x10; bge`. It also derives
the loop start as `(len<<16) + 0xFFFF0000` from the SAME `len<<16` it
used for `buf[len] = 0`. Ours sign-extends len once (`asr r3,r3,#0x10`)
and then works with the unshifted counter. ALL loop-form spellings tried (2026-07-25), best is still t3 at 90/108:
  `while (--i >= 0)`                          -> 98B / 76 diffs
  `for (i = (s16)len - 1; ...)`               -> 96B / 67 diffs
  `buf[(s16)len]=0; for (i=(s16)(len-1);...)` -> 96B / 67 diffs (t6)
ROOT CAUSE of the residual: the target materialises len TWICE — first
zero-extended (`lsrs r0,r3,#16`, the plain u16 param value) and then
sign-extended from that (`lsls r2,r0,#16; asrs r0,r0,#16`), keeping
`len<<16` live to build `(len-1)<<16` by adding 0xFFFF0000. agbcc folds
our u16->s16 conversion into ONE `asrs r0,r3,#16` because we only ever
use len in a signed context, and no spelling of the cast prevents the
fold. That is the same materialisation/allocation class as
FUN_080d7e5c and FUN_080b7e3c — the pressure that forces the target to
keep both forms comes from outside the expression. The loop BODY is
correct in t3/t6; only the head differs. Park.

## FUN_080111bc (ice base LAYER_EXIT, 32B) — SOLVED first try

`gBlendRegBuffer.bldclt = 0; SEA = PIXEL(10240);` — that is the whole
function. The pool constant 0x0002C00C is `gOverworld.sea` (the SEA
macro); the value is built by agbcc as `movs r1,#0xa0; lsls r1,#0xe`
from the plain constant, so write PIXEL(10240) as the rest of the
codebase does (src/stage/sunken_library/landscape.c:89) and let the
compiler pick the encoding.

METHOD NOTE that found it: scanning asm/**/*.inc for thumb_func_start
symbols still absent from src, cross-referenced with rom_symbols.txt
sizes and filtered to 0x18..0x50 bytes EXCLUDING mmbn4, yields 82
candidates. Sorting by size and preferring files where a sibling is
already matched is a much better target picker than the dup-scan
cluster list, which is now exhausted. Reusable snippet is in this
session's transcript; consider promoting it to tools/.

## DeathtanzRock_Update (SOLVED) + a fnbytes.py measurement trap

Standard update dispatcher:
  `if (!FUN_0807a5c0(p)) { (sUpdates1[mode[1]])(p); (sUpdates2[mode[1]])(p); }`
ROM sha1 exact.

TRAP worth knowing: rom_symbols.txt gives this function size 0x2A, but
the real function runs to 0x3C — the symbol table SPLIT it, with the
tail carrying its own `non_word_aligned_thumb_func_start FUN_0807a6ce`
label. Comparing our 60-byte output against the 42-byte "symbol" made a
correct match look wrong (ours "bigger", plus a bogus diff at byte 6).
Whenever our output is LARGER than the claimed symbol size, check the
.inc for a non_word_aligned_thumb_func_start immediately after it and
re-measure against the real extent before touching the C.
Second reminder from the same probe: standalone harnesses that only
DECLARE the dispatch tables produce a wrong pool addend (0x10 vs the
ROM's 0xC) because the arrays are never laid out — that difference is a
probe artifact, not a mismatch. The ROM build is the arbiter.

## Stage-layer bgofs draw family (FUN_08013bdc et al) — in progress

FUN_08013bdc (sunken library, 48B) is the simplest of a family that also
includes giantElevator_08014a34/_08014ad4 and snowyplains_080133b4.
Body is understood completely:
  n = l->bgIdx;
  gVideoRegBuffer.bgofs[n >> 4][0] = (l->viewportCenterPixel.x * 3) >> 2;
  gVideoRegBuffer.bgofs[n >> 4][1] = (l->viewportCenterPixel.y * 3) >> 2;
(giantElevator uses `(x - 0x1428) >> 2` instead of the *3>>2 parallax.)

STRUCT OFFSETS PINNED (useful for the whole family): bgIdx is the u32 at
0x5C, which anchors the six Coords before it —
drawPivotOffset 0x2C, viewportCenterPixel 0x34, prevViewportCenterPixel
0x3C, scrollPower 0x44, scroll 0x4C, scrollCopy 0x54.

SOLVED — the answer was an existing macro. include/gpu_regs.h already
defines BGnHOFS(n)/BGnVOFS(n) as
  *(u16*)((u8*)gVideoRegBuffer.bgofs + ((n) << 2)      )
  *(u16*)((u8*)gVideoRegBuffer.bgofs + ((n) << 2) + 2  )
which is EXACTLY the byte arithmetic the target shows, and pools
&bgofs (= gVideoRegBuffer+0xC) instead of the struct base. Using them:
  BGnHOFS(n >> 4) = (l->viewportCenterPixel.x * 3) >> 2;
  BGnVOFS(n >> 4) = (l->viewportCenterPixel.y * 3) >> 2;
matches 48/48 (last word is the +0xC relocation addend).
LESSON: before inventing pointer-anchor spellings, GREP THE HEADERS for
an existing accessor macro — the codebase usually already has the exact
idiom, and hand-rolled equivalents miss the pool form. Cost here: two
failed spellings (52B with the plain member expression, 40B with a
hand-rolled anchor) before checking gpu_regs.h.

(superseded) the target pools `gVideoRegBuffer+12` (i.e. &bgofs)
and then derives BOTH stores from it — index*4 in one register, and the
second address by `adds r4,#2; adds r2,r2,r4`. Writing the plain member
expression pools gVideoRegBuffer+0 and adds 0xC (52B, too big);
anchoring `u16 (*ofs)[2] = gVideoRegBuffer.bgofs;` gets the +12 pool but
then GCC collapses both stores onto one base register (40B, too small).
Need the form that keeps the +12 anchor AND two separate address
computations. This is the FlushOAM pool-anchor lever again — see
notes/matching-workflow.md step 4.

## giantElevator_08014a34 / _08014ad4 (SOLVED, 48B each, first try)

Direct payoff of workflow step 4c (grep for the accessor macro). Same
BGnHOFS/BGnVOFS idiom as FUN_08013bdc, different arithmetic:
  a34: BGnHOFS = (viewportCenterPixel.x - 0x1428) >> 2;  BGnVOFS = unk_10;
  ad4: BGnHOFS = (viewportCenterPixel.x - 0x1428) >> 7;  BGnVOFS = unk_10 >> 2;
(0xFFFFEBD8 in the pool is -0x1428.) Both matched on the first probe
because the family idiom was already pinned. Remaining sibling of this
family: snowyplains_080133b4 (52B, has a phase==0 guard and a bgcnt
read-modify-write on top of the same bgofs writes).

## snowyplains_080133b4 (SOLVED, 52B, first try) — family complete

  if (l->phase == 0) {
    const u16 n = l->bgIdx;
    BGCNT16(n >> 4) = (BGCNT16(n >> 4) & 0xFFFC) | 3;
    l->phase++;
  }
STRUCT FACT this pinned: `struct BgCnt` is 2 bytes, so gVideoRegBuffer is
dispcnt(0..1), bgcnt[4] at 4..11 (the ALIGNED(4) is on the ARRAY, not the
element), bgofs at 12 — which is why BGnHOFS/BGnVOFS pool +12 and
BGCNT16 indexes 4 + 2n. The stage-layer draw family is now complete:
FUN_08013bdc, giantElevator_08014a34/_08014ad4, snowyplains_080133b4.
Four functions, one idiom, three of them first-probe once the idiom and
the offsets were known.

## FUN_0800f840 (SOLVED, 52B, first try) — 5th of the layer family

Byte-for-byte the same body as snowyplains_080133b4, with ONE source
difference visible in the asm: `const u16 n = l->bgIdx;` is declared
BEFORE the `if (l->phase == 0)` guard, so the load and its `lsls #16`
hoist above the compare (the `lsrs #0x14` stays inside). Declaring n
inside the if would sink both. That hoist/sink split is a cheap, reliable
tell for where a local is declared relative to a guard.

## FUN_080ddec0 (ciel minigame obj update, 52B) — 8 bytes, accumulator order

Body is certain:
  e = (p->s).unk_28;            // loaded BEFORE the call, kept in r4
  UpdateMotionGraphic(&p->s);
  if (*(u16*)((u8*)e + 0xDF0 + (p->s).work[1] * 2) == 0xFF)
      flags |= DISPLAY; else flags &= ~DISPLAY;
Tail (the two arms computing into one register with a shared strb) is
byte-identical already.
REMAINING: the address computation accumulates into the BASE register in
the target (`movs r1,#0xdf; lsls r1,#4; adds r4,r4,r1; adds r4,r4,r0;
ldrh r0,[r4]`) but into the INDEX register for us (`adds r0,r0,r4; ...;
adds r0,r0,r1; ldrh r0,[r0]`). Tried: inline cast expression, an inner
`((u16*)((u8*)e+0xDF0))[i]` cast, a `u16* t` assigned before the call
(52B but the base then hoists above the call, 40 diffs), and `u16* t`
assigned after the call (50B, 13 diffs — worse). agbcc reassociates all
of them the same way.
NOTE the caller (asm/minigame/ciel.inc) is still asm, so unk_28's real
type is unknown and 0xDF0 stays a raw offset for now; naming it may
change the codegen and is worth retrying once the minigame file lands.
TOOLING NOTE: when hand-diffing objdump output, filter BOTH files
identically — dropping lines containing `<` removes bl/branch lines from
one side only and makes instruction counts meaningless.

## ActorSaveSelectCiel_Update (SOLVED, 56B, first try)

Textbook switch-with-FALLTHROUGH mode dispatcher:
  case 0: coord.y = FUN_08009f6c(coord.x, coord.y);
          SetMotion(&p->s, 0xC200); mode[1]++;  FALLTHROUGH;
  case 1: UpdateMotionGraphic(&p->s); break;
(0xC200 is the pooled `movs r1,#0xc2; lsls r1,#8` pair.) Nothing novel —
logged only to record that the actor_p1_p1.inc file has many more
functions of exactly this shape (Actor8/10/13/15_Update,
ActorCrashedPantheon_Update, ActorLeviathan11_Update,
ActorFefnir12_Update ...), all still asm. That single 3203-line inc is
probably the densest remaining vein of easy dispatchers in the repo.

## Actor15_Update (SOLVED, 72B) — actor vein, 2nd of the family

Same dispatcher as ActorSaveSelectCiel_Update with different constants:
  coord.y = FUN_08009f6c(coord.x, coord.y) - 0x1C00;   (pool 0xFFFFE400)
  SetMotion(&p->s, 0xCA00);  taskCol = 0x1F;  mode[1]++;  FALLTHROUGH;
  case 1: UpdateMotionGraphic.
FIELD NOTE: offset 0x25 is `taskCol`, NOT spr.spriteIdx — guessing
spriteIdx compiled to within ONE byte of correct, which is exactly the
kind of near-miss that could be mistaken for a regalloc tie. When a
single byte differs inside a store, re-check the FIELD before blaming
allocation: grep the offset in include/entity/entity.h.
Remaining in this vein (all still asm, same file):
ActorOperator_Update, Actor17_Update, Actor8/10/13_Update,
ActorCrashedPantheon_Update, ActorLeviathan11_Update,
ActorFefnir12_Update.

## ActorOperator_Update (SOLVED, 156B, first try) — actor vein, 3rd

Same dispatcher skeleton, richer case 0:
  coord.x += (work[1] != 0) ? 0xC00 : -0xC00;   // ternary, ONE add
  coord.y  = FUN_08009f6c(coord.x, coord.y) - 0x1B00;
  SetMotion(&p->s, 0xC900 | work[1]);
  taskCol = 0x1F;
  SET_XFLIP(p, work[1] == 0);
  mode[1]++;  FALLTHROUGH;  case 1: UpdateMotionGraphic.
Recognising SET_XFLIP from its asm signature is what made this
first-probe: the macro expands to the flags AND/OR pair, then a strb to
+0x4C (spr.xflip) and a masked read-modify-write at +0x4A with the
constant -0x11 (spr.oam.xflip). Any time you see `movs r0,#0x11; rsbs
r0,r0,#0; ands; orrs` around offsets 0x4A/0x4C, it is SET_XFLIP/SET_YFLIP
— do not hand-roll the three writes.

## Actor13_Update (176B) — decoded, 4 bytes over on one pool anchor

Body fully recovered (build/scratch/act/t5.c, 180/176):
  e = (p->s).unk_28;   // kept in r5 across the whole switch
  case 0: InitScalerotMotion1; spr.mag.x = spr.mag.y = 0x180;
          SetMotion(0x2100); SET_XFLIP(p, TRUE);
          coord.x = e->coord.x + 0x1E00; coord.y = e->coord.y - 0x1E00;
          mode[1]++; FALLTHROUGH;
  case 1: UpdateMotionGraphic; coord.x += 0x400;
          if (coord.x > <viewport.x> + 0xB7FF) SET_SOLID_ROUTINE(DIE);
OFFSET PINNED: gStageRun.vm is at +232 (0xE8) and camera.viewport.x at
+0x38 inside it, i.e. StageRun+288 — verified by compiling
`char a[(int)&((struct StageRun*)0)->vm.camera.viewport.x];` and reading
the .comm size (a cheap, reliable offsetof trick worth reusing).
REMAINING (4 bytes): the target pools `gStageRun+232` (= &gStageRun.vm)
and reads with an immediate `[r0,#0x38]`; every spelling we tried folds
to a single address and materialises 288 in a register instead:
  gStageRun.vm.camera.viewport.x        (180B)
  (&gStageRun.vm)->camera.viewport.x    (180B, identical)
  struct VM* vm = &gStageRun.vm; ...    (180B, and it perturbs the head)
Same class as the FlushOAM/BGnHOFS pool-anchor problem — the fix is
probably an existing accessor macro that does not yet exist in
include/stagerun.h. Worth revisiting when another function needs the
same read; several actor updates do.

## FUN_08016080 (SOLVED, 20B, first try) — smallest match of the session

  void FUN_08016080(u32 a) { STAGE.unk_00c = a; }
where landscape.c already had `#define STAGE (gOverworld.work.weilLabo)`.
The pool constant 0x0002D034 decodes as gOverworld.work (which starts at
0x2D028) + 12, i.e. WeilLaboState.unk_00c. Two greps (the STAGE macro,
the props header) and it was done — step 4c working exactly as intended.
The whole asm/stage_gfx/weil_labo_p1_p2_b.inc file is now gone.

RE-SCAN NOTE: this candidate did NOT appear in the earlier 0x18..0x50
sweep because that run excluded sizes under 0x18. Re-running the scan
after each batch surfaces newly-smallest candidates as incs get split
and removed; the current list has 178 functions at <= 0x60 bytes.

## blazin_080403a0 (SOLVED, 36B, first try) — crossjumping used FOR us

A 4-way pointer selector out of the Boss props union:
  n==0 -> raw[0x20], n==1 -> raw[0x24], n==2 -> raw[0x28], else raw[0x2C]
written as four plain `return *(struct Entity**)&(p->props).raw[N];`
branches. The target has ONE shared `ldr r0,[r0]; pop; bx` at the join,
which looks like the source computed an address per branch and
dereferenced once — but it is just agbcc cross-jumping the four
identical loads. This is the same cross-jumping that BLOCKS the
_zeroTryAttack five-pack; here it works in our favour, so do not
contort the source to reproduce a shared tail — write the natural
per-branch returns and let it merge.
Offsets: Boss props union starts at 0xB4, so the pool offsets
0xD4/0xD8/0xDC/0xE0 are raw[0x20/0x24/0x28/0x2C].

## FUN_080e2310 (SOLVED, 60B, first try) — 5-arg call with a stack Coord

  struct Coord c;
  struct Zero* z = *(struct Zero**)&p->buffer[0];
  c.x = (z->s).coord.x;  c.y = (z->s).coord.y;
  if (FUN_080e1578((struct Coord*)&p->buffer[8], &(p->s).unk_coord, &c,
                   &p->buffer[6], 0xA0))
    (p->s).mode[1]++;
The 5th argument goes on the stack (`str r2,[sp]` before the bl) and the
local Coord lives at sp+4 — `sub sp,#0xc` covers both. Getting the
callee's real signature from src/cyberelf.c:89 (it is NAKED there but
the prototype is written out) is what made this first-probe; do not
guess arity from the asm when a prototype already exists somewhere.

ALSO: FUN_080a449c (36B, tretista) is NOT a function — the preceding
function branches into it (`bne _080A44AE`). It is a split tail like
DeathtanzRock_Update's. Skip it in candidate lists.

## FUN_080ac1a4 (SOLVED, 64B) — conveyor-push collision handler

  self = (struct Projectile*)body->parent;
  z    = (struct Zero*)(body->enemy)->parent;
  s32 kind = (z->s).kind;                  // ldrsb via the s32-local rule
  if (kind != ENTITY_PLAYER) return;
  v = ((self->s).work[1] == 0) ? 0x180 : 0x280;
  if ((self->s).flags & X_FLIP) *(s32*)&z->horizontalSlide =  v;
  else                          *(s32*)&z->horizontalSlide = -v;

TERNARY POLARITY is load-bearing: the target materialises the DEFAULT
value first and branches over the other arm, so read which constant is
loaded BEFORE the cmp and make that the ternary's false-branch value.
`(work[1] != 0) ? 0x280 : 0x180` and `(work[1] == 0) ? 0x180 : 0x280`
are semantically identical but compile to opposite branch polarities
(5 diff bytes).
FIELD NOTE: z->horizontalSlide is declared u8 at 0x190 in
include/entity/player.h with a comment about 3 bytes of padding, but the
ROM stores a WORD there — src/player/zero/zero.c:95 already works around
this with `*((u32*)&z->horizontalSlide) = 0;`. Kept that convention
rather than retyping a field used by an already-matched file; the field
is probably really s32 and worth fixing upstream.

## FUN_080823ec (glacierle arm distance, 64B) — 6 bytes, mul-copy shape

Semantics certain (build/scratch/gla/t2.c, 58/64):
  a = body->parent;  if (!a) return 0;
  b = (a->s).unk_2c; if (!b) return 0;
  dx = b->coord.x - a->s.coord.x;  dy = b->coord.y - a->s.coord.y;
  return (u16)Sqrt((dx>>8)*(dx>>8) + (dy>>8)*(dy>>8)) << 8;
(the tail `lsls #16; lsrs #8` is exactly `(u16)result << 8`.)
REMAINING: the target squares each term as `adds r2,rX,#0; muls r2,rX,r2;
adds rX,r2,#0` — a copy, a 2-operand multiply, and a copy back (3 insns
per square) — while we emit a single `muls rX,rX`. Six bytes = the four
extra copies. That pattern means the two multiply operands are DISTINCT
pseudos in the original, so the source probably squares via two separate
variables or a macro rather than `x * x` on one variable. Tried: shifting
inside the expression, shifting as separate statements (both 58B).
Tried POW2 (include/definition.h:9) — it is literally `#define POW2(n)
(n * n)`, i.e. textually identical to what we already had, and compiles
2 bytes SMALLER (56B). So the codebase's own square macro is NOT the
answer here; the extra copies are an allocation artefact, same class as
the other residuals. Useful corollary: POW2(x) and x*x are
interchangeable, so never spend a probe distinguishing them.

## FUN_080c17e8 (SOLVED, 68B) — VFX56 frame-throttle

  if (p->work[2] == 0) { UpdateMotionGraphic(p); p->work[2] = 3; }
  else                 { p->work[2]--; }
  if ((p->motion).state == 3) { SET_VFX_ROUTINE(p, ENTITY_DIE); VFX56_Die(p); }
The single `strb ...,[r4,#0x12]` at the join is agbcc cross-jumping the
two arms' stores — write them naturally (confirms the blazin_080403a0
rule: a SHARED tail in the target means let the compiler merge).
OFFSET PINNED: struct Motion is 8 bytes and sits at 0x6C in Entity, so
0x6C=cmds, 0x70=step, 0x71=cmdIdx, 0x72=duration, 0x73=state. Any lone
byte access at +0x73 is `motion.state` — worth remembering, several VFX
updaters test it.
NOTE: the file's forward declaration said `struct VFX*` while the
function really takes `struct Entity*` (the rest of unk_56.c already
uses struct Entity*); retyping the decl was needed to build.

## FUN_08062b70 (SOLVED, 68B, first try) — spearook flag gate

  case 0: *(u32*)&(p->props).raw[8] |= 0x20;  mode[2]++;  FALLTHROUGH;
  case 1: u32 f = *(u32*)&(p->props).raw[8] & 0x20;
          if (f == 0) { mode[1] = f; mode[2] = f; }
          coord.y = FUN_08009f6c(coord.x, coord.y);
The two `strb` of the SAME masked value f (not a literal 0) is the
known-zero-register reuse pattern: assign the masked result to a named
variable and store THAT in both places, rather than writing 0.

## FUN_080ce760 (SOLVED, 68B) — locomoif platform scroller

  e = (p->s).unk_28;                       // kept in r5 across the switch
  case 0: mode[2] = 1;  FALLTHROUGH;       // literal 1, NOT mode[2]++
  case 1: *(u16*)&(p->props).raw[0] += (p->s).d.x;
          FUN_080ce538(p); UpdateMotionGraphic(&p->s); break;
  // OUTSIDE the switch:
  if (e->mode[0] > 1) { mode[1] = 3; mode[2] = 0; }
Note `struct Solid` has `props.raw[16]` (NOT `buffer[]` like Enemy/Elf) —
the per-kind field name differs by entity type: Enemy/Elf use buffer[],
Solid/Boss/VFX use props. Check the struct before writing the accessor.

## copyx_08056bd0 + FUN_08064e38 (SOLVED, 68B each, first try)

copyx_08056bd0: if (mode[2]) { SetMotion(0xB303); mode[2]=0; work[2]=0x40; }
  UpdateMotionGraphic; then `u8 st = motion.state; if (st == 3) {
  mode[1] = st; mode[2]=1; mode[3]=2; work[2]=4; }` — mode[1] takes the
  COMPARED VARIABLE, not a literal 3.
FUN_08064e38: `u8 m = mode[2]; if (m == 0) { SetMotion(0x1300);
  work[2]=0x1E; d.y = m; d.x = m; mode[2]++; }` — the two zero stores
  take m (known 0 there), and d.y is written BEFORE d.x.
  Tail: work[2]--; if (work[2] == 0xFF) { mode[1] = mode[3]; mode[2]=0; }

Both are instances of one rule that keeps paying: when a store's value
equals something already in a register (the switch selector, the compared
value, a just-masked flag), the ORIGINAL wrote the variable, not the
literal. Writing the literal costs a `movs` every time. Reuse candidates
to check first: the mode/selector byte, the comparison operand, and any
value produced by the preceding test.

## initActor28 / initActor32 (SOLVED, 68B each) + initActor21 (14B off)

Window-register setup family in src/solid/actor.c:
  gWindowRegBuffer.dispcnt |= 0x4000;      // 0x80<<7
  gWindowRegBuffer.winin[1] = <0 or 4>;
  gWindowRegBuffer.winin[2] |= 0xFE;
  (p->s).work[2] = 0;
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  Actor_Update(p);
initActor28 (winin[1]=0) and initActor32 (winin[1]=4) match exactly.
STRUCT: gWindowRegBuffer is dispcnt(0), _(2), winH(4), winV(8),
winin[4](0xC..0xF) — so [r2,#0xd] is winin[1] and [r2,#0xe] is winin[2].

initActor21 is the SAME body with the two winin statements swapped
(winin[2] |= 0xFE first, then winin[1] = 0). Our output has the identical
instruction sequence but agbcc places the `movs r3,#1` that feeds
SET_SOLID_ROUTINE differently: the target hoists it between the two
winin stores, we emit it just before the `str`. 14 bytes of downstream
encoding shift from one scheduling choice. Parked — pure scheduling,
same class as the other residuals.

## phunterRaiseArm (SOLVED, 68B, first try) — twin of FUN_08064e38

Identical template to FUN_08064e38, three constants changed: motion
0x1301 (vs 0x1300), only d.x is zeroed (not d.y), and the timeout sets
mode[1] = 8 (a literal here, where 08064e38 copied mode[3]). The `u8 m =
mode[2]` known-zero reuse carries over unchanged.
Pantheon-hunter now has two of its mode handlers in C; the file's
remaining asm follows the same skeleton, so the template should keep
paying there.

## phunter_080651c0 (SOLVED, 88B, first try) — decel glide

  if (mode[2] == 0) { SetMotion(0x1300); unk_coord.x = d.x / 32;
                      work[2] = 0x1F; mode[2]++; }
  UpdateMotionGraphic; coord.x += d.x; d.x -= unk_coord.x;
  work[2]--; if (work[2] == 0xFF) { mode[1] = 0; mode[2] = 0; }
unk_coord is used here as a per-frame decel step — a nice confirmation
that Entity.unk_coord (0x64) is a general scratch Coord, as its header
comment suggests. The `/ 32` is the signed-division idiom (see workflow).

## phunter_080652e8 (SOLVED, 136B) — hunter dive

  if (mode[2] == 0) { if (props[9]) d.x = 0x80; else d.x = -0x80;
                      d.y = -0x300; mode[2]++; }
  SetMotion(0x1309);            // EVERY frame, outside the guard
  UpdateMotionGraphic; coord += d; d.y += 0x40; clamp 0x700;
  if (FUN_080098a4(coord.x, coord.y)) {
    coord.y = FUN_08009f6c(coord.x, coord.y);
    *(s32*)&p->props[4] = coord.y;      // same register reused
    mode[1] = 5; mode[2] = 0;
  }
struct Enemy uses `props[16]` (not buffer[]) — third time this per-type
naming has cost a compile; the list is Enemy/Boss/Solid/VFX = props,
Elf/Weapon = buffer.

## phunterShotBuster (SOLVED, 168B) — buster volley

switch (work[2]) with cases 0/5/10 sharing a body and case 0x30 ending
the mode; work[2]++ after the switch. Fires CreateLemon(&c, 0x240, dir)
from a stack Coord whose y is set before the X_FLIP branch and whose x
is set inside each arm. See the workflow note on hoisting the call
result — the `if (q != NULL) PlaySound(0x2C);` must be ONE test after
the if/else, not duplicated in both arms.

## phunter_08065218 (208B) — decoded, 4 bytes on a SET_XFLIP detail

Semantics complete (build/scratch/ph/t9.c, 204/208):
  u8 m = mode[2];
  if (m == 0) { SetMotion(0x1300); d.y = m; d.x = m; mode[2]++; }
  UpdateMotionGraphic;
  SET_XFLIP(p, coord.x < pZero2->s.coord.x);
  if (gProjectileHeaderPtr->remaining > 6) {          // s16 at hdr+0xA
    u8 left = (pZero2->s.coord.x <= coord.x);
    if (left != ((flags >> 4) & 1)) {
      if ((u32)(pZero2->s.coord.x - coord.x + 0x6E00) <= 0xDC00 &&
          (u32)(pZero2->s.coord.y - coord.y + 0x5000) <= 0xA000) {
        mode[3] = mode[1]; mode[1] = 7; mode[2] = 0;
      }
    }
  }
REMAINING: inside SET_XFLIP the target keeps the macro's `__xflip__ & 1`
(`movs r6,#1; adds r1,r6,#0; ands r1,r2`) and REUSES that r6 for the
later `(flags >> 4) & 1`. We pass a comparison result, so agbcc proves
it is 0/1 and elides the AND, which also stops the constant being
shared — 4 bytes plus downstream branch shifts. Needs a value that is
NOT provably boolean; CHECKED: ActorOperator_Update's ROM asm has `adds r1, r2, #0` with NO
and-mask — identical to our output — confirming that a comparison
argument makes agbcc drop the mask. So phunter_08065218's argument is
NOT a comparison; it must be a value agbcc cannot range-analyse to 0/1
(a field read, a helper return, or a masked flag). Look for a source of
the flip direction other than `coord.x < pZero2->coord.x` when the
minigame/hunter files are further decompiled.

## FUN_08073ea8 (SOLVED, 72B, first try) — snakecord horizontal step

  u32 FUN_08073ea8(struct Entity* p, s32 dx) {
    if (dx == 0) return 0;
    p->coord.x += dx;
    if (dx < 0) { push = PushoutToRight2(coord.x, coord.y);
                  if (push > 0) { coord.x += push; return 2; } }
    else        { push = PushoutToLeft2 (coord.x, coord.y);
                  if (push < 0) { coord.x += push; return 1; } }
    return 0;
  }
Direction mapping is the counter-intuitive part and comes straight from
the branch: dx < 0 (moving LEFT) probes PushoutToRight2 and returns 2;
dx >= 0 probes PushoutToLeft2 and returns 1. The push sign tests differ
per arm (> 0 vs < 0) — do not "tidy" them into != 0.

## FUN_08073ef0 (SOLVED, 76B, first try) — vertical twin of FUN_08073ea8

Identical shape on the Y axis: dy < 0 probes PushoutToDown2 and returns
2; dy >= 0 probes PushoutToUp2 and returns 1. Derived from the matched
horizontal version by pure substitution.
DECL NOTE: PushoutToLeft2/Right2 live in include/definition.h while
PushoutToUp2/Down2 live in include/physics.h — the four siblings are
split across two headers, which is easy to trip over (cost one build
here). Both headers are needed when a function uses all four.

## shellcrawler (2026-07-25)

- **FUN_08095d80** (0x48) MATCHED. Two `FUN_08009f6c` probes at `x ± PIXEL(10)`,
  each `<= 0x43F` from `coord.y`, OR-ing a bool8. Key: the call result must be a
  *named local* (`t = FUN_...(); if (t - y <= ...)`), which forces the
  `adds r2, r0, #0` copy at both sites. Inlining the call into the comparison
  drops the copy and loses 4 bytes.
- **FUN_08095dc8** (0x60) MATCHED first probe. `PushoutToUp1` right / `FUN_08009f6c`
  left, `if (a < b) {...} else {...}` with *duplicated* bodies
  (`if (v < 0 && v > -0x400) { coord.y += v; r = TRUE; }`). Cross-jumping merges
  only the `str`/`movs #1` tail — writing it as a min() would not.
- **FUN_08095e28** (0x9C) MATCHED in 3 probes. Two lessons:
  1. The pushout-result temp and the probe-y temp are the **same variable** in the
     original. Separate variables let agbcc keep the first in a caller-saved reg
     (r2); one variable spans the `PushoutToLeft1` call and must be callee-saved,
     which is what puts `p` in r5 and the temp in r4 as in the ROM.
  2. `dir * PIXEL(20) - PIXEL(10)` is literal source, not a compiled ternary —
     agbcc emits `lsl #2; add; lsl #10` for the `* 0x1400`.
  3. Final `if (attr) return 0; return 2;` compiles with the arms swapped versus
     the ROM; `if (attr == 0) return 2; return 0;` puts them in ROM order.
- **FUN_080964c0** (0xB0) MATCHED after 18 probes. Three separate levers stacked:
  case 0 needs the `-0x40` as its own short-lived constant (so agbcc reuses the
  live `0x60` via `subs r0,#0xa0`) plus a *separate* variable for the flip value;
  case 1 needs the `||` short-circuit (see matching-workflow.md, "Branch polarity");
  case 2 needs `if (--work[2] == 0)`.
  Side effect: the call site proves **FUN_08095e28 returns u8**, not u32 — the
  caller truncates with `lsls #24`. Changing the declaration did not disturb
  FUN_08095e28's own codegen (ROM sha1 still exact).
- **FUN_08096570** (0x9C) MATCHED in 2 probes; retires `shellcrawler_post_pre.inc`
  entirely. Lever: `mode[1] = work[0] ? 6 : 0` is NOT a ternary — the ROM reuses
  the register already holding `work[0]` for the zero case. Source is a local:
  `m = work[0]; if (m != 0) { m = 6; } mode[1] = m;`. A ternary or if/else
  materialises a fresh `movs rN, #0` (+2 bytes, +2 more from pool realignment).
  Note this is the *same* known-value-reuse family as FUN_080964c0's
  `movs r0,#0x60 / subs r0,#0xa0`: when the ROM omits a constant you expect,
  look for a register that already provably holds it.
- **FUN_08096950** (0x80) MATCHED first probe — the documented levers transferred
  directly: store-then-select-then-store for `d.x` (as FUN_080964c0 case 0),
  `if (--work[3] == 0)`, and `*(s32*)&p->props[0]` compiling to
  `adds r0,r4,#0 / adds r0,#0xb4 / ldr r0,[r0]` (offset > 124 defeats ldr imm5).
  Required splitting shellcrawler_post_post.inc into _a/_b (see matching-workflow.md).
- **FUN_0809678c** (0x88) MATCHED first probe — byte-for-byte sibling of
  FUN_08096950 with MOTION(0xdb,1) and the FUN_08096570 `m = work[0]` idiom for
  mode[1]. Note the `--work[3]` test compiles as `lsls #24; cmp #0` here but
  `lsls #24; lsrs #24; cmp r1,#0` in FUN_08096950 — the extra `lsrs` appears only
  because that function reuses the zero for `mode[2] = 0`. Same source, different
  bytes: do not treat that pair as a discrepancy.
- **FUN_080966fc** (0x90) MATCHED first probe. Two known-value reuses in one
  function: `SetDDP(&p->body, ...)` reuses the `&p->motion.state` address register
  via `adds r0,#1` (0x73 + 1 = 0x74 = &body), and `SET_ENEMY_ROUTINE(c,
  ENTITY_DISAPPEAR)` stores r5 — the local holding `motion.state`, provably 3
  after the `!= 3` guard — instead of materialising the constant 3. The guard
  value must therefore be a *local*, not an inline `(p->s).motion.state != 3`.
  `0x0836A08C` resolved to this file's own `sCollisions` via nm + the .map
  (.rodata at 0x0836a078 = gShellcrawlerRoutine, 5 ptrs, then sCollisions).
- **FUN_0809664c** (0xB0) MATCHED in 1 probe. Standard spawn idiom already in the
  tree (cf. CreateBlazin): `taskCol = 24; INIT_ENEMY_ROUTINE(...); tileNum = 0,
  palID = 0; flags2 |= WHITE_PAINTABLE; invincibleID = uniqueID;`. The comma
  operator in `tileNum = 0, palID = 0` is load-bearing — it is why the two zeroes
  land in different registers (one reuses the known-zero mode[2]).
- **FUN_08096814** (0x13C) MATCHED in 9 probes. Four independent levers:
  1. Case 0's select temp and case 2's abs temp must be **separate** variables.
     Reusing one name creates a single long-lived pseudo, bumps pressure, and
     shifts the whole register assignment (r2/r3 instead of ROM's r1/r2).
  2. `p->props[9]++; if (p->props[9] == 3)` — GCC forwards the stored value and
     truncates it (`strb; lsls #24; lsrs #24`) rather than reloading. Writing it
     with an explicit `u8 n` temp reverses the store/truncate order; writing it as
     `++p->props[9] == 3` makes GCC hoist `movs r3,#255` and use `ands` instead.
     Only the store-then-test form gives the ROM bytes.
  3. `coord.x - PIXEL(12) + dir * PIXEL(24)` gets reassociated — GCC sinks the
     constant onto the multiply. An explicit `x = coord.x - PIXEL(12);` temp
     pins the order, and the final add must be `dir * PIXEL(24) + x` (multiply
     first) or the result lands in the wrong register.
  4. `dir` must be **s32**. As u32, GCC rewrites `dir * 0x80 - 0x80` into
     `+ 0x80` because only the low byte survives the u8 truncation.
- **FUN_080969d0** (0xC0) MATCHED first probe. Every lever came from FUN_08096814:
  explicit `x = coord.x - PIXEL(16)` temp, multiply-first in the final add,
  `dir` as s32. Confirms those are general to this file's projectile spawns.
- **FUN_08096a90** (0xF4) MATCHED first probe (only the `&sCollisions[14]` pool
  word differs in isolation — relocation, resolves in-tree). Lever: the story
  flag must go through a **u8 local**:
  `u8 f = gCurStory.s.gameflags[4] & 0x40; if (f) {...}`. The inline
  `if (gCurStory.s.gameflags[4] & 0x40)` form omits the `lsls #24 / lsrs #24`,
  and — more importantly — the local is what leaves a register provably holding
  zero on the fall-through path, which the second EXIT_BODY then reuses instead
  of emitting its own `movs r2,#0`. Two teardown blocks, only one materialises 0.
- **FUN_08096b84** (0xA4) MATCHED first probe. Death handler: `flags &= ~DISPLAY`
  then EXIT_BODY (whose zero reuses the switch's `mode[2]` register), drop calls
  through a `struct Coord* pc = &(p->s).coord` local, `gMission.enemyCount`
  capped at 0x270E, then SET_ENEMY_ROUTINE(p, ENTITY_EXIT).
- **FUN_08096c28** (0x15C) MATCHED in 5 probes. Structure fell out first try; the
  whole cost was one declaration: **`dir` must be `u16`**, matching the
  `bool16 isDirRight` parameter of FUN_080b2b40. As `s32` the code is
  instruction-for-instruction identical but every callee-saved register rotates
  by one (p in r6 instead of r5), so all 59 diffs were register numbers. When a
  probe is the right size and the right shape but differs from byte 4 onward,
  suspect an argument type before suspecting the control flow.
  Also confirms the documented signed-power-of-two idiom: `d.x * 240 / 256`
  compiles to `lsls #4; subs; lsls #4` then `cmp; bge; adds #0xff; asrs #8`.
- **FUN_08096d84** (0x128) MATCHED first probe. Same death-effect family; the
  `||` lever applies to `if (--work[2] == 0 || FUN_080098a4(x, y) != 0)`.
- **FUN_08096eac** (0x104) MATCHED in 4 probes; retires shellcrawler_post_post_c.inc.
  Homing-shot maths. Levers: (a) the y delta needs a pinning temp
  (`dy = coord.y - 0x1800; d.y = dy - z->coord.y;`) or GCC reassociates
  `(a - K) - b` into `a - (b + K)` and materialises +0x1800 instead of loading
  -0x1800 from the pool; (b) the sum-of-squares accumulator and `dist` are the
  **same variable**, written with `+=`, which is what puts it in callee-saved r6
  across the Sqrt call; (c) arms ordered `if (dist != 0) {...} else {...}`.
  **Process note:** I sized this function 0x100 from eyeballing the listing; it
  is 0x104. The probe reported "260B/256B, 4 bytes over" and I spent a cycle
  hunting phantom extra bytes. Get the size from the *next* thumb_func_start,
  not by counting.
- **FUN_08096348** (0xF0) MATCHED first probe; retires shellcrawler_pre_p1_p1_b.inc.
  **Contains a genuine original-game bug that must be reproduced verbatim.** The
  detach block nulls the child pointer and then dereferences it:

      c = NULL;
      (p->s).unk_2c = (struct Entity*)c;
      (c->s).flags &= ~DISPLAY;   /* address 0x0A  */
      EXIT_BODY(c);               /* 0x8C/0x90/0x94 */
      SET_ENEMY_ROUTINE(c, ENTITY_DISAPPEAR);

  agbcc constant-folds `NULL + offset` into absolute addresses, so the ROM really
  contains `movs r0,#0x8c / str r2,[r0]`. Those land in GBA BIOS space, where
  writes are ignored — the whole teardown is a silent no-op at runtime.
  The checked-in `asm/enemy/shellcrawler_pre_p1_p1_b.inc` listing was NOT wrong;
  I doubted it first and verified against baseimg.gba, which is the right order.
  Also note `if (m == 3 || m == 4 || m == 8)` compiles to the range test
  `subs r0,r1,#3; lsls/lsrs #24; cmp r0,#1; bls` followed by `cmp r1,#8; beq`.
- **Shellcrawler_Init** (0x1A0) MATCHED in 7 probes. The whole cost was one
  wrong arm order. Written as
  `if (A == 0 || (f = B) != 0) { hp = 0xc } else { hp = 0x10 }` agbcc hoists a
  single zero into a *fourth* callee-saved register (r7), shared between
  `mode[1] = 0` and the `body->fn = NULL` of INIT_BODY, so the prologue becomes
  `push {r4,r5,r6,r7,lr}` and every register shifts. Written the other way round,
  `if (A && (f = B) == 0) { hp = 0x10 } else { hp = 0xc }`, the NULL pseudo
  coalesces with `f` instead — which is what the ROM does (`str r5,[r4,#0x24]`,
  r5 = f, provably 0 on that path) — and the prologue drops back to three.
  **Diagnostic worth reusing:** a differing `push` mask is a register-count
  signal, not a code-shape signal. Find which pseudo owns the extra register
  (`objdump | grep r7`) and ask what two values agbcc coalesced.
  Also: `BodyFunc` is `void (*)(struct Body*, struct Coord*, struct Coord*)`, so
  FUN_08096348 had to take three params. The two extra unused args do not change
  its codegen (ROM sha1 unchanged).
- **Shellcrawler_Update** (0x284) MATCHED in 4 probes. **src/enemy/shellcrawler.c
  is now fully decompiled — zero INCASM.** Three levers:
  1. The element-effect slot is NOT a cached local. The ROM re-loads
     `*(struct VFX**)((u8*)p + 0xb8)` at every test; a `struct VFX** slot` local
     caches the *value* and also loses the `adds r5,r0,#0` address copy.
     Use the raw expression at each use site and let agbcc CSE the address.
  2. `mode[1] = 0` in the death-cause chain must be written
     `(p->s).mode[1] = (p->body).status & 0x20000;` — the ROM reuses the AND
     result (provably 0 on that path) rather than materialising `movs r0,#0`.
  3. Control flow needs `goto`. Two sites jump out of nested ifs into a shared
     tail; no structured rewrite reproduces it. `goto` is precedented in this
     tree (anubis.c, cubit.c, text_window.c, hanumachine.c).

## "one function left" vein (2026-07-25)

Target picker: for each src/*.c, count thumb_func_start across the .inc files it
INCASMs; sort ascending. 14 files sit at exactly one remaining function, so each
match completes a whole file. This is the highest-value vein currently open.

- **FUN_08014efc** (0x5C) MATCHED in 2 probes; sub_arcadia/landscape.c now 100% C.
- **FUN_0800e308** (0x68) MATCHED in 3 probes; old_residential/landscape.c now 100% C.
  Note the patch tables are *adjacent 8-byte records*, so the ROM indexes off one
  symbol with stride 8 even when that symbol is declared `struct MetatilePatch`
  (4 bytes). Reproduce with an explicit cast:
  `(struct MetatilePatch2x1*)&MetatilePatch_0833dfe2 + ((x - 0xf8) >> 1)`.

**Recurring lever across this whole vein: arm order.** Three of the last four
matches differed only in which side of a comparison was the fallthrough. agbcc
puts the *then* block in the fallthrough position, so read the ROM's branch and
write the condition whose false-arm it jumps to. Cheap to test, so check it
before hypothesising anything structural.
- **BurstShot_Init** (0xC8) MATCHED first probe; burst_shot.c now 100% C.
  `unk_28` (Zero*) and `unk_2c` load at the very top and live across every call,
  which is what forces sl/sb. FUN_0803b73c needed the 3-arg BodyFunc signature.
- **OmegaGoldProjectile_Init** (0xC0) **PARKED** after 6 probes, 37 diffs, correct
  size. Residual is a pure two-pseudo register tie: ROM has p=r6 and the
  zero-carrier=r5; we get p=r5, carrier=r6. Everything else is byte-identical.
  Two reachable states, neither complete:
    * no zero variable -> registers correct, but the shared tail materialises a
      fresh `movs r0,#0` for mode[2]/mode[3] (+4 bytes, 20 diffs from 0x74);
    * `u8 v = (p->s).work[0]` threaded through body->fn/taskCol/mode[1..3] ->
      exact size and the tail uses the carrier, but p and v swap registers.
  Ruled out: v as u8/u16/u32/s32 (identical), split declaration, an `e = &p->s`
  local to cut p's refcount, chained `mode[3] = mode[2] = 0`, and assigning v
  inside each branch. This is the regalloc-tie class documented earlier — the
  one that survives hand levers. Revisit with the permuter, not by hand.
- **FUN_08076fe8** (0xC4) MATCHED first probe; wormer_rock_drone.c now 100% C.
- **FUN_080b36e0** (0xBC) MATCHED first probe; zero_death_effect.c now 100% C.
  `(v->s).work[2] = 2` in case 2 reuses the switch's mode[1] register (== 2 on
  that path) — write the literal, agbcc finds the reuse itself.
- **FUN_080ba07c** (0xF0) MATCHED first probe; vfx/unk_28.c now 100% C.
  Three-draw LCG: `RNG_0202f388 = LCG(RNG_0202f388)` assigned repeatedly with no
  call between — agbcc dead-store-eliminates all but the last write and keeps the
  intermediates in a register, exactly as the ROM does. Read the draw with
  `(RNG_0202f388 >> 16) & mask`, NOT `>> 17` as childre.c uses: the ROM's
  `lsrs rX, rX, #0x11` operates on the pre-`>>1` value, so it is `>> 16` of the
  stored seed.
- **FUN_080c0b68** (0xF8) MATCHED in 2 probes; vfx/unk_51.c now 100% C.
  Lever: `if (++(v->s).work[2] & 1)` emits a redundant `movs r1,#255 / ands`
  (u8 truncation of the pre-increment value). The ROM has none, so the source
  keeps the incremented value in an int:
  `n = work[2] + 1; work[2] = n; if (n & 1)`.
- **FUN_080c3574** (0x104) **PARKED** after 5 probes at 4 bytes / 109 diffs.
  Structure is right and `s32 v` (not u8) removed the truncation block around
  `v = 2 - v`. Residual is another register permutation: ROM keeps &RNG_0202f388
  in r6 (reusing the register that held &spr.xflip); we run out and shuttle it
  through ip (`mov ip,r3` / `mov r0,ip`, +4 bytes). Tried: flip as u8/s32,
  declaration order, SET_XFLIP(p, TRUE) vs SET_XFLIP(p, v). Unexplained tell:
  the ROM emits a **dead `movs r6,#0`** at the top, so the original had one more
  pseudo than my version — find what that zero is and the allocation likely falls
  into place. Same permuter-not-hand class as OmegaGoldProjectile_Init.
- **Solid53_Die** (0x114) **PARKED** after 3 probes, 4 bytes over. Structure right.
  We emit `sub sp,#4` / `add sp,#4`: one value spills. ROM hoists exactly four
  loop invariants (&RNG_0202f388, 0x1FFF, -0x1000, 0x269EC3) and deliberately
  **re-loads 0x343FD from the pool three times per iteration**; agbcc in our build
  hoists that too and runs out of registers. Tried: separate x/y locals, fully
  inlined call arguments, block-scoped x/y — all identical. Loop-invariant-motion
  pressure heuristic, not a source shape. Permuter territory.
  Also note `FUN_0800d5a8` is called here **with a `struct Coord*` argument**
  though ocean/landscape.c defines it `(void)` — an unused parameter, so the
  definition still matches; the real signature takes a Coord*.

Three consecutive parks (OmegaGoldProjectile_Init, FUN_080c3574, Solid53_Die) all
fail on the same axis: agbcc register allocation under pressure. That is the
documented permuter class. Switching selection strategy to smallest-function-first
rather than one-function-file-first.
- **FUN_0807465c / FUN_080746c0** (0x62 / 0x6C) MATCHED; retires
  asm/enemy/snakecord_p1_p2.inc. FUN_080746c0 is another `||` short-circuit
  (`*slot == NULL || isKilled(*slot)`).
  **Method error worth remembering:** my byte-compare masks "relocation" pool
  words by offset. I masked 0x50 in FUN_0807465c on the assumption it was
  gEnemyFnTable, the probe reported MATCH, and the in-tree build then failed on
  exactly those 2 bytes — the word is **gVFXFnTable** (0x0836D900), i.e. the
  child in `unk_2c` is a struct VFX*, not a struct Enemy*, so the macro is
  SET_VFX_ROUTINE. A masked byte is an *unverified* byte: only mask pool words
  after resolving them with nm, and never treat a probe MATCH with masked words
  as final. The in-tree sha1 caught it, as it is supposed to.
  Also: my size estimates from `.byte` blob line counts were over by 6 and 8
  bytes; real sizes come from the next symbol's address.
- **FUN_0808bd1c** (0x74) MATCHED first probe (omega_gold_sword); retires
  omega_gold_sword_p3_p1_b.inc.
- **FUN_080bac14 / FUN_080baca4 / FUN_080bacec** (0x48 each) MATCHED first probe,
  three siblings in one pass. Identical bodies differing only in the init call
  (InitScalerotMotion1 vs InitNonAffineMotion) and mode[1] (3/5/6).

**Sizing rule (third time this bit me).** `rom_symbols.txt` sizes are unreliable:
FUN_0808bd1c is listed 0x46 but is really 0x74 — the listed size stops at an
internal label. Derive the true size from the *next symbol's address*, and sanity
check that the disassembly's branch targets all fall inside. A related tell:
FUN_080a449c "starts" with `ldr` and ends with a `pop` that restores r8/r9 with
no matching `push` — it is the tail of a split function, not a function. Skip
those rather than trying to match them.
- **FUN_080bad34** (0x48) MATCHED first probe — fourth sibling of the unk_32
  init family (InitNonAffineMotion, mode[1] = 7); retires unk_32_pre_pre_b.inc.
- **FUN_08093a20** (0x44) **PARKED** after 5 probes at 2 bytes / 8 diffs.
  Progress made and worth keeping if revisited:
    * `push {lr}` only (no r4) requires `zx -= 0x6000;` as its own statement —
      writing `(zx - 0x6000) + dir * 0xC000` lets agbcc reassociate, which needs
      a fifth live value and forces r4 into the prologue;
    * `struct Zero* z = pZero2;` as an explicit local reproduces the ROM's order
      (load the global pointer, load x, then deref) and took it 18 diffs -> 8.
  Residual is the usual register permutation (ROM dir=r3/x=r2/zx=r0; ours
  dir=r2/x=r3/zx=r1). Permuter class.
- **FUN_080afb1c** (0x4C) MATCHED first probe — standard teardown gated on
  `((p->s).unk_28)->mode[0] > 1`.
- **FUN_080a14dc / FUN_080a1538 / FUN_080a1594** (0x5C each) MATCHED first probe,
  all three in one pass. Exact copies of the file's existing `createBat` /
  `createEchoWave` idiom differing only in `(p->s).work[0]` = 2/3/4.

**Sibling-batching is the cheapest remaining move.** Scan: group asm functions by
(inc file stem, true size); any group of >=2 is a candidate family. Verify they
really are siblings by disassembling two — the phantom_p2_p2_p2 group of four at
0x4C was a *coincidence* of size, not a family, so check before writing. When
they are real siblings, write all of them in one probe and lift in one build;
the unk_32 inits (4) and these hellbat spawners (3) each cost one probe total.
- **FUN_080aabd4 / FUN_080aac28** (0x54 each) and **FUN_080c3f1c / FUN_080c40ec**
  (0x58 each) MATCHED — two families, four functions, two probes total.
  The unk_32 spawners took a second probe for one reason: they return **void**,
  not `struct Projectile*`. Tell: the epilogue is `pop {r4} / pop {r0} / bx r0`,
  i.e. r0 is clobbered by the pop that reloads the return address, and there is
  no `adds r0, rN, #0` before it. A pointer-returning sibling (the hellbat trio)
  ends `adds r0,r3,#0 / pop {r4,r5} / pop {r1} / bx r1` instead. **Read the
  epilogue to decide the return type before writing the body.**
  unk_64: `SET_VFX_ROUTINE(v, ENTITY_DISAPPEAR)` reuses the register holding
  `motion.state` (== 3 after the guard), so the guard needs a `u8 state` local —
  same lever as FUN_080966fc.
- **FUN_080ce710** (0x50) MATCHED first probe; retires locomoif_platform_part3_a.inc.
- **FUN_080a2ea0** (0x48) **PARKED** at 6 bytes. Body is exact; only the three
  loop-preheader setup instructions are ordered differently:
  ROM `movs r5,#0 / ldr r6,=gProjectileFnTable / movs r4,#4`, ours
  `movs r4,#4 / movs r5,#0 / ldr r6,=...`. i.e. agbcc placed the LICM-hoisted
  invariants *before* the for-init; we get the for-init first. Tried: for-loop,
  do/while with `--i >= 0`, and swapping the declaration order — all identical.
  Preheader scheduling, not source shape.

**Two more "same size != same family" false positives** this round
(unk_55 FUN_080c123c/FUN_080c13c8, unk_1_p1_b pair). Always disassemble two
before writing. The check costs one objdump and has now saved three wasted probes.
- **FUN_08095074** (0x58) MATCHED first probe; retires pantheon_fist_pre_p1_p2_p2.inc.
  Same shape as snakecord's FUN_08073ea8: `if (dx == 0) return 0;` then a
  `dx < 0` / else pair of FUN_080098a4 probes returning 1 / 2.
- **FUN_0807b800** (0x60) MATCHED first probe; retires wormer_snow_ball_p3_p2_p2.inc.
  gMission.enemyCount cap, TryDropZakoDisk, EXIT_BODY, CreateIceballParticle4,
  SET_ENEMY_ROUTINE(p, ENTITY_EXIT).

Resolving `bl` targets via rom_symbols.txt address lookup is reliable and fast —
both of this pair's unknown calls (0x08024F3C -> TryDropZakoDisk,
0x080BEA80 -> CreateIceballParticle4) came straight from it. Do that before
guessing at a helper's identity from context.
- **FUN_0807be50** (0x54) MATCHED first probe; retires beetank_p6_p1_p2.inc.
  Byte-for-byte the claveker.c `FUN_0808f1e0` idiom (element-effect slot at
  props[8], attr = `*(u8*)((u8*)p + 0x97) & 0xf0`, 0x10 -> mode[1]=2,
  0x30 -> mode[1]=4).
  **The tree's forward declaration was wrong**: beetank.c declared
  `void FUN_0807be50(struct Enemy* p);` but the ROM ends `movs r0,#1 / pop ...`,
  i.e. it returns a value. Matched as `bool8` returning TRUE (same as its
  claveker twin) and corrected the declaration. The ROM is the authority on
  signatures, not the existing stub declaration — cf. the porter-comments rule.
- **Mellnet_Die** (0x6C) MATCHED first probe; retires mellnet_pre_p2_b.inc.
  `if ((p->s).work[0] == 0 && IS_METTAUR) { ...teardown... } else
  { (sDeads[(p->s).mode[1]])(p); }` — the dispatch goes through `_call_via_r1`
  (0x080FE6E8), which is just how agbcc calls a table entry, not a real helper.
- **createPantheonZombie** (0x64) **PARKED** at 8 bytes. Body exact and the same
  size; the only difference is *where* an independent `movs r3,#0` is scheduled
  (ROM emits it between `adds r0,#1` and `strb r0,[r1,#0]`, we emit it three
  slots later). Pure instruction scheduling. Note it returns **void** despite the
  name — epilogue is `pop {r4,r5,r6,r7} / pop {r0} / bx r0` with no move into r0.

**tools/lift_fn.py added.** Lifts everything in the scratch from a marker line
onward (declarations included) into the src file in place of an INCASM, and
deletes the inc. Written because extracting just the function with a regex
dropped forward declarations five times this session, costing a build each.
- **FUN_080babac** (0x68) MATCHED first probe; retires unk_32_pre_pre_a.inc.
  Fifth member of the unk_32 init family, with an LCG draw for the angle:
  `RNG_0202f388 = LCG(RNG_0202f388); (v->s).angle = RNG_0202f388 >> 16;`
  (`lsrs #0x11` on the pre-`>>1` value == `>> 16` of the stored seed, as before).
- **FUN_080913c0** (0x6C) MATCHED first probe; retires unk_59_pre_pre_p1b.inc.
  Spawn helper, id 59; last field is
  `(e->s).work[3] = (*(s32*)&p->props[0] > 0);` written directly as a comparison.
- **mothjiro_08088a74** (0x6C) MATCHED first probe; retires mothjiro_p8_post_p1.inc.
  Third variant of the element-effect-slot idiom (claveker / beetank / mothjiro):
  same guard, same `attr = *(u8*)((u8*)p + 0x97) & 0xf0` decode, but the arms call
  `SetDDP(&p->body, &sCollisions[2])` instead of setting mode. **Both arms use the
  same collision pointer** — that redundancy is in the original, not a misread;
  agbcc keeps them separate because the two pool copies sit far apart.
  **Second wrong `void` declaration corrected** (after beetank's FUN_0807be50):
  mothjiro.c declared it void, the ROM ends `movs r0,#1 / pop`, so it is bool8.
  Whenever a stub declaration says void, check the epilogue before trusting it.
- **FUN_08061ef0** (0x48, spearook) and **crossbyne_0807cdc4** (0x48) MATCHED,
  both element-effect-slot variants. spearook clears a flag
  (`*(u32*)&(p->props).raw[8] &= ~4;`) then sets mode[1]=15; crossbyne guards on
  `(p->s).work[0] <= 1 && (p->s).mode[1] == 2` and zeroes both modes.
  **struct Boss's buffer is `props.raw[48]` (a union), not `props[]`.** Enemy and
  Projectile use a plain `props[16]`/`work[]` array; Boss and VFX use a named
  union with a `raw` member. Check the struct before writing `&p->props[0]`.

**Scan that found these:** decode every `bl` in each remaining asm function
(Thumb BL is two halfwords, F000-F7FF then F800-FFFF, offset sign-extended from
22 bits) and look for a known callee address — 0x08025250 = ApplyElementEffect
turned up 19 remaining callers of an idiom already matched three times. Doing
this per-callee is a much better target picker than sorting by size.

**lift_fn.py --keep-inc places the C BEFORE the kept INCASM.** When splitting an
inc and keeping the first half, the order must be INCASM(first); C; INCASM(rest).
Caught by the sha1; fixed by reordering. Worth adding a flag for this case.
- **FUN_0808c4e8** (0x50) and **FUN_08075e8c** (0x54) MATCHED first probe — a
  fourth element-effect shape, this one with a frozen check first:
  `frozen = (p->body).status & 0x20000; if (frozen) { mode[1]=N; mode[2]=0; }
   else { *slot = ApplyElementEffect(...); if (*slot) { mode[1]=0; mode[2]=0; } }`
  Both `mode[2] = 0` stores reuse an already-zero register (`*slot` in the frozen
  arm, `frozen` in the else arm) — write the literal, agbcc finds it.
  In FUN_0808c4e8 the `(p->body).status & 1` also reuses the `1` from the
  `work[0] == 1` compare; that falls out for free when work[0] is compared to 1
  and not otherwise (FUN_08075e8c compares to 0 and materialises a fresh 1).

Running tally of the ApplyElementEffect vein: 19 found, 4 matched
(FUN_08061ef0, crossbyne_0807cdc4, FUN_0808c4e8, FUN_08075e8c), 15 left.
- **FUN_08077388** (0x54) MATCHED first probe; retires volcaire_p1_a.inc.
  Third instance of the frozen-check element shape (work[0] != 0, mode[1] = 7).
- **blazin_0803fed8** (0x50) MATCHED. Two things it taught:
  1. The third argument is **gBlazinCoords**, not an sElementCoord. I had masked
     that pool word as a relocation and the probe said MATCH regardless — the same
     trap as snakecord's gVFXFnTable. Resolved it with nm before lifting this
     time. **Masked pool words must be resolved, not assumed**, and the callee's
     first argument here is 9, not the usual 0.
  2. **Third wrong `void` declaration corrected** (after beetank and mothjiro):
     ROM ends `movs r0,#1 / pop`, so it is bool8.
  Also note the else-arm writes `*slot = NULL` — a spawn that is immediately
  discarded when the element attribute is not 0x10.

ApplyElementEffect vein: 19 found, 6 matched, 13 left.
- **FUN_0808d4a0** (0x58) MATCHED first probe. Fourth instance of the frozen-check
  element shape. Its guard is a two-value exclusion written naturally as
  `if ((p->s).work[0] != 8 && (p->s).work[0] != 9)`, which agbcc compiles to the
  range test `subs r0,#8 / lsls #24 / lsrs #24 / cmp r0,#1 / bls` — same
  transformation as the `m == 3 || m == 4` case in FUN_08096348. Recognising a
  `subs K / cmp #N / bls` block as an N+1-value range test on the ORIGINAL value
  is now a reliable read.
  Pool word verified with nm before lifting (0x08369314 sits inside deathlock's
  rodata 0x08369134+0x1f6) rather than assumed.

ApplyElementEffect vein: 19 found, 7 matched, 12 left.
- **FUN_0804d0a4** (0x54, bee_server) **PARKED** at 4 bytes. Body and control flow
  exact. Residual: the final `*(u16*)&(p->props).raw[4] = 0xFC00;` materialises
  the constant in r2 and copies (`movs r2,#0xfc / lsls r2,#8 / adds r0,r2,#0 /
  strh r0,[r1]`); the ROM builds it straight in r0 (`movs r0,#0xfc / lsls r0,#8 /
  strh r0,[r1]`). Tried u16/s16/negative-constant/pointer-local forms; s16 with
  -0x400 makes it worse (pool load of 0xFFFFFC00). Register choice for a constant,
  same class as the other parks.
  Its third argument is the shared global **Coord_0836331c** (defined in
  bee_server.c itself), and ApplyElementEffect's first argument is 18.
- **FUN_08068f08** (0x60, piller_cannon) **PARKED** at 12 bytes short (84 vs 96)
  after 3 probes. Two anomalies in the ROM that no straightforward source
  reproduces:
  1. **Dead code**: `ldrb r1,[r4,#0xa] / movs r0,#0x10 / ands r0,r1` computes
     `flags & X_FLIP` and both registers are overwritten before use. Tried an
     expression statement and duplicated if/else arms; neither emits it.
  2. **Redundant address recompute**: the first read and the store of
     `*(struct VFX**)&p->props[8]` go through a cached r5, but the *second* read
     recomputes `adds r0,r4,#0 / adds r0,#0xbc / ldr r0,[r0]`. Writing the raw
     expression there just gets CSE'd back to r5.
  Together those are the missing 12 bytes. It does return **bool8** (TRUE) —
  fourth stub declared `void` that the epilogue contradicts. Suspect the original
  used a macro that expands to something with the flip value; revisit with the
  corpus grep (tools/decomp_crawl.py) for a matching idiom rather than guessing.
- **hellbat_0804cbe4** (0x54) MATCHED first probe. ApplyElementEffect with first
  argument **17**, and the interesting part is a **duplicated `*slot = NULL`**:
  the ROM stores NULL once right after the non-null check and again in the else
  arm of the attribute test. Written literally as
  `*slot = NULL; if (attr == 0x30) { PlaySound(0x8a); } else { *slot = NULL; }`
  it matches exactly — do not "clean up" the redundant store, and do not assume
  agbcc would have hoisted it.
  **Fourth wrong `void` declaration corrected** (beetank, mothjiro, blazin, now
  hellbat). Every one of these element-effect helpers returns bool8 TRUE and was
  stubbed `void`; treat that as the default expectation for the family.
  Pool word verified with nm first: sElementCoord at 0x08363208 is immediately
  followed by sExplosionCoords, matching hellbat.c's own declaration order.

ApplyElementEffect vein: 19 found, 8 matched, 2 parked, 9 left.
- **batring_08068130** and **cattatank_08099e20** (0x94 each) MATCHED. Fifth
  element-effect shape: after the spawn, `if (mode[1] != GUARD)` sets
  props[12] and mode[1]/mode[2] from the attribute; the `== GUARD` arm sets only
  props[12]. Constants: batring (8, 5, 7), cattatank (6, 7, 9).
  Arm order matters again — the ROM's fallthrough is the `!= GUARD` path, so it
  must be written `if (mode[1] != GUARD) {...} else if (e != NULL) {...}`.
  Writing `== GUARD` first costs 4 bytes and 70 diffs.
  `p->props[12] = 1` reuses r7, the `1` from the `status & 1` mask.
  **Fifth wrong `void` declaration corrected** (cattatank).
  **shotcounter_08066da0 differs** despite matching size — its constants appear in
  a different order (movs #5 / movs #2 / movs #7) and it diffs from byte 6, so it
  is NOT a third clone; treat separately.
- **shotcounter_08066da0** (0x94) MATCHED after correcting the offsets. It IS the
  same shape as batring/cattatank after all, with the same constants as batring
  (8, 5, 7) — what differed was where the fields live:
  slot at **props[12]** (0xC0) and the flag byte at **props[11]** (0xBF), versus
  slot at props[8] (0xBC) and flag at props[12] (0xC0) in the other two.
  My earlier note calling it "not a third clone" was wrong: the byte-6 diff was
  the `adds r6,#0xc0` vs `#0xbc` offset, not a structural difference. Read the
  offsets out of the disassembly per instance instead of inheriting them from the
  sibling. (Its declaration was already bool8 — the only one of the family that
  was right.)

ApplyElementEffect vein: 19 found, 11 matched, 2 parked, 6 left.
- **cubit_080544c0** (0x70) MATCHED in 3 probes. Two real mistakes on the way,
  both worth avoiding next time:
  1. **Scope**: I put the trailing `if (*slot != NULL) *slot = NULL;` outside the
     outer `if`. The ROM's early exit (`*slot != NULL`) branches straight to the
     `movs r0,#1` return, *skipping* that block — so it lives INSIDE the outer if.
     Read where the early-exit branch actually lands before placing trailing code.
  2. **Halfword order**: I read the motion constant off the disassembler's
     `b019 / 0000` rendering as 0x19B0. The word is **0xB019** — the first
     halfword printed IS the low half. So the test is MOTION(0xb0, 0x19).
     Verify pool constants with `struct.unpack('<I', rom[off:off+4])`, never by
     eye from two halfword mnemonics.
  Also confirms the composite-motion idiom from hellbat.c:
  `(((p->s).motionID << 8) | (p->s).motion.step) == MOTION(a, b)`, with
  motion.step at entity offset 0x70. Sixth wrong `void` declaration corrected.

ApplyElementEffect vein: 19 found, 12 matched, 2 parked, 5 left.
- **FUN_08085c4c** (0x78, capsule_cannon) and **FUN_08068f08** (0x60,
  piller_cannon) MATCHED. **The dead-code puzzle is solved.**
  The `ldrb flags / movs #0x10 / ands` whose result is immediately overwritten
  comes from an if/else with **identical arms**:

      if ((p->s).flags & X_FLIP) {
        *slot = ApplyElementEffect(0, &p->s, coord);
      } else {
        *slot = ApplyElementEffect(0, &p->s, coord);
      }

  agbcc merges the two arms into one call but leaves the condition computed.
  This also explains the paired identical pool words seen in mothjiro and
  capsule_cannon (both SetDDP arms using the same &sCollisions[N]) — same
  duplicated-arm construct, arms merged, pools not deduped.
  FUN_08068f08 had been PARKED at 12 bytes; this insight closed it. Its second
  slot read genuinely recomputes the address, so use the raw expression there.
  **Fourth masked-pool-word burn**: piller_cannon has no sElementCoord at all —
  the third argument is the shared global **Coord_083661ec**. My placeholder
  `static const struct Coord sElementCoord;` became a tentative .bss definition
  and the LINKER caught it ("`.bss' referenced ... defined in discarded section").
  Resolve every pool word with nm BEFORE writing the C, not after.

ApplyElementEffect vein: 19 found, 14 matched, 1 parked, 4 left.
- **FUN_080742ec** (0x74, snakecord) **PARKED** at 6 bytes after 4 probes.
  Correct size and every instruction present. Two levers found and kept:
  * the coord must be selected by **duplicated calls** in both arms, not by a
    `const struct Coord* c` temp — the temp costs a callee-saved register
    (push {r4,r5,r6,lr} instead of {r4,r5,lr}) and 12 bytes;
  * testing the slot with the **raw expression** while assigning `slot` inside
    the block keeps the address in a temp, which is what lets agbcc derive the
    status address as `subs r0,#0x28` from the props address instead of
    recomputing `adds r0,#0x8c`. That alone took 11 diffs -> 6.
  Residual: the `adds r5,r0,#0` copy sits before the `cmp` in the ROM and after
  the `bne` in ours. Assigning `slot` before the test moves it but then the
  address goes straight to r5 with no temp (back to 11 diffs). Independent-copy
  scheduling, same class as createPantheonZombie.
- **FUN_08061c74 / FUN_08061ccc** (0x58 each, spearook) **PARKED** at 14/15 bytes
  after 3 probes. Correct size and identical instruction multiset; the ROM hoists
  the `flags2` load and its 0x10 mask to the top of the tail block, we emit them
  adjacent to the OR/store. Moving `flags2 |= WHITE_PAINTABLE` earlier in the
  source does not move them; an explicit `u8 f2 = (e->s).flags2; ... = f2 | ...`
  helps slightly (16->14) but does not close it. RMW scheduling.
  Settled facts: they spawn a **Boss** (gBossHeaderPtr / INIT_BOSS_ROUTINE, id 24
  — and `strb r0,[r3,#9]` reuses the 24 from taskCol), FUN_08061c74 returns the
  Boss while FUN_08061ccc returns void, and both write invincibleID **twice**
  (own uniqueID, then the parent's).
- **FUN_080afbb0 / FUN_080afc9c / FUN_080afda4** (phantom projectile spawners)
  MATCHED first probe, three at once. All id 40, taskCol 8; they differ only in
  the allocator (AllocEntityLast vs AllocEntityFirst), work[0] (n / 2 / 5), and
  whether work[2] is set. Required a four-way inc split (they sit at positions
  2, 4 and 6 of an eight-function inc).

**Best target picker so far:** decode every `bl` in each remaining asm function
and rank callees by how many small functions call them. Then take the ones whose
ONLY call is to a known simple helper. `AllocEntityFirst`/`AllocEntityLast` gives
42 such "pure spawn helper" candidates — the INIT_*_ROUTINE idiom, usually one
probe each. Two caveats learned this round:
  * always resolve the header/table pool words: spearook's spawners use
    **gBossHeaderPtr / gBossFnTable**, not the Enemy ones, despite living in a
    file full of enemies;
  * spawners with a `flags2 |= ...` RMW plus a double invincibleID write hit
    the scheduler (see the spearook park); the plain ones do not.
- **FUN_0807b0d0** (0x54, wormer_snow_ball) MATCHED first probe. Plain spawner:
  AllocEntityLast, id 29, coord from the two s32 args, returns void.
  Useful contrast with the spearook park: this one HAS the `flags2 |=
  WHITE_PAINTABLE` RMW and it compiles contiguously. So the RMW is not what makes
  spearook schedule oddly — it is the **second invincibleID write** (own uniqueID
  then the parent's) that spreads the RMW apart.
- **FUN_08093994** (0x54, shotloid) **PARKED** at 33 diffs / correct size.
  Structure certain (AllocEntityFirst, id 62, work[0]=1, unk_28=parent, void).
  Residual is a register-class choice: the ROM keeps the new entity in **r4**
  and the parent in r5 (`push {r4,r5,lr}`), while we put the entity in r3 and the
  parent in r4 (`push {r4,lr}`). Both are valid — nothing is live across a call
  after the alloc — so agbcc simply chose a callee-saved register where we chose
  a scratch one. Note its two-argument sibling FUN_0807b0d0 matches exactly,
  so this only bites the single-argument spawners.
- **babyelf_0809f9f0 / FUN_0809fa9c** (0x54, unk_13 projectile) and
  **FUN_0807b184** (0x58, wormer_snow_ball) MATCHED first probe, three at once.
  **Correction to the previous note**: the single-vs-multi-argument theory for
  FUN_08093994's register-class mismatch is wrong. FUN_0807b184 takes two args and
  keeps the entity in **r3** (`push {r4,r5,lr}`) while FUN_0807b0d0 also takes two
  and keeps it in **r4** (`push {r4,r5,r6,lr}`). The actual difference is
  `work[0] = 0` vs `work[0] = 1`: a zero lets agbcc reuse the already-live zero
  register, which changes pressure and pushes the entity into a callee-saved reg.
  So: **a `= 0` field store is not free — it changes allocation.** Write the
  literal the ROM implies and let that fall out; do not generalise from arity.
  Field-write ORDER also differs between the two unk_13 twins (coord before
  work[2] in one, after in the other) and must be copied per instance.
- **deathtanz_080a09a0** (0x54) MATCHED first probe — identical in shape to
  babyelf_0809f9f0 (4 args, AllocEntityLast, work[0]=2, coord, work[2]=n,
  unk_28=parent), only the projectile id differs (14 vs 13).
- **FUN_08093994 still PARKED.** Field-write order is NOT the factor either
  (tried unk_28 early / mid / late, and invincibleID from the parent: 42/53/33
  diffs, never the right prologue). The ROM keeps the new entity in a
  callee-saved r4 where a scratch r3 would do, and I have not found the source
  property that forces that. Recording what it is NOT, so the next attempt does
  not repeat: not arity, not `work[0]` value, not field order.

The 4-argument spawners (parent, x, y, u8) are the reliable subset: five matched
first-probe (phantom x3, babyelf, FUN_0809fa9c, deathtanz). Prefer those.
- **FUN_0809fa44** (0x58) and **FUN_08093930** (0x64) MATCHED first probe.
  FUN_0809fa44 writes BOTH unk_coord (0x64/0x68) and coord (0x54/0x58) from the
  same x,y args. FUN_08093930 returns the Enemy and stores its u8 arg to
  props[9] (0xBD) — note it is a **3-argument** spawner (x, y, n) with no parent.
  Both use the same INIT_*_ROUTINE skeleton; only the tail fields differ.

Spawn-helper vein tally: 42 found, 9 matched, 3 parked (FUN_08093994,
FUN_08061c74, FUN_08061ccc), ~30 left. All three parks are register-allocation
or scheduling, none are shape errors.
- **FUN_0808f2e4** (seimeran) and **FUN_08080c64** (pantheon_aqua_mod_obj)
  MATCHED first probe. Both plain spawners (ids 57 and 38).

**A new failure mode, and the worst one yet: orphan bytes at the end of an .inc.**
asm/enemy/seimeran_p1.inc ended with

    _0808F344:
      .byte 0x70, 0x47, 0x00, 0x00

after FUN_0808f2e4's literal pool — a stray `bx lr` plus padding with **no
thumb_func_start**. Lifting the last function from that inc silently deleted
those 4 bytes, shifting every later object and producing a 5.5-million-byte ROM
diff starting at 0x5D6.
Two things let it through:
  * my byte-probe compares `min(len(ours), len(target))`, so "96B diffs=0"
    against a 100-byte target reported a MATCH while being 4 bytes short. **A
    size mismatch must be treated as a failure, not a footnote.**
  * rom_symbols gives FUN_0808f2e4 size 0x64, which includes the orphan bytes.
Fix: split the orphan tail into its own inc and INCASM it after the C.
**Before lifting the LAST function of an inc, diff the inc against what the
function actually needs — anything after the final pool must be preserved.**

- **FUN_08075b74** (purple_nerple, enemy 22, `unk_28` + `props[5]`),
  **FUN_0807b124** (wormer_snow_ball, enemy 29, coord+d from 4 args),
  **blizzack_080aaae0** (projectile 32, work[0]=1/work[1]=n) -- all matched first probe.
- **FUN_080aa7a8** (projectile 31) needed one iteration and gives a **new lever**:
  an early-return guard is NOT the same shape as a positive if-block.

      if (p == NULL) { return NULL; }        -> beq to the return, body falls through
      body; return p;                           (92B, pool after the body's `b`)

      if (p != NULL) { body; return p; }     -> bne to the body, return-NULL falls
      return NULL;                              through (96B, matches ROM)

  Same instructions, both orders; only the layout differs, and the mid-function
  pool + its `.align 2, 0` padding makes the ROM form 4 bytes LONGER. So for a
  spawn helper that RETURNS the entity, write the positive if-block with a
  trailing `return NULL;` -- never the guard clause.

- **FUN_08071508** (carry_arm, enemy 17, `props[0]` holds a 32-bit `struct Entity*`),
  **FUN_08099f54** (minigame leviathan, enemy 68, writes coord.x/y, unk_coord.y, d.x),
  **FUN_080a60c8** (cubit projectile 22, `coord = *c` from a Coord*, work[1]/work[2]),
  **FUN_080aaa80** (projectile 32) -- all matched first probe.
  FUN_08071508 / FUN_080a60c8 return the entity on BOTH paths (`adds r0,r3,#0`
  sits *after* the join label), so they are `if (p != NULL) { ... } return p;`
  -- distinct from FUN_080aa7a8's `return p;` inside the block + `return NULL;`.

- **createGlacierleSucker** (0x080822E4) PARKED. Right length (100B), right
  instruction multiset, right STORE order -- but the ROM keeps `flags2` (r2) and
  the constant 0x10 (r1) live across three unrelated stores and does the
  `orrs`/`strb` late:

      ldrb r2,[r3,#0xb] / movs r1,#0x10 / <inv, work0, unk_2c stores> / orrs r1,r2 / strb r1,[r3,#0xb]

  Store order alone is settled: it follows source order exactly, and the ROM's
  is inv1, work0, unk_2c, flags2, inv2, props8. Tried flags2-first, flags2-in-
  place, a read-early/write-late temp (`fl = flags2; ... flags2 = fl | 0x10;`),
  and props8-before-inv2: 16/16/14/26 diffs, never 0. Register allocation only.
  This function has the double `invincibleID` write (own uniqueID, then the
  parent's) that I already flagged as a divergence trigger elsewhere -- that
  correlation now holds on a third function.

**The cyberelf CreateXxxElf family.** CreateBirdElf (12), CreateNurseEElf (4),
CreateSeaotterElf (9), elf_080e4bf4 (10) are all the same shape as the already-
decompiled CreateNurseBElf: `(struct Zero* z, u8 breed, u8 availability,
u8 satelite_slot)`, a local `struct CyberElfXxx` with `struct Zero* player` at
0xB4, and `work[3] = satelite_slot == 0 ? SATELITE_1 : SATELITE_2`. The SATELITE
macros in zero.h expand `z` by name, so the parameter MUST be called `z`.
elf_080e4bf4 differs in one instruction: it writes `unk_coord.x = satelite_slot`
(`str r5,[r3,#0x64]`) where the others write `work[2]` (`strb r5,[r3,#0x12]`).

- **FUN_0808f27c** (seimeran, enemy 57): writes `unk_coord.x` and `coord.x` from
  the same argument, then `coord.y`, `work[2]`, `unk_28`. seimeran.c is now 100% C.
- **summonPurpleNerple**: `coord.y = (&gStageRun.vm.camera)->viewport.y - PIXEL(112)`.
  Writing it as `gStageRun.vm.camera.viewport.y` costs 8 bytes -- agbcc pools
  `gStageRun` and materialises 292 with `mov #0x92 / lsl #1`. Taking the address
  of the *camera* pools `gStageRun+232` and reaches the member with `[r0,#0x3c]`.
  Same idiom already in volcano_bomb.c:67 and omega_zero_rock.c:33.
- **createFlameRain1 / createFlameRain2** (cubit projectile 22): the third
  parameter is **s32, not u8** -- the ROM prologue has a plain `adds r5,r2,#0`
  with no `lsl #24 / lsr #24`, even though the value is later stored with `strb`.
  A zero-extending prologue in the ROM proves a u8 parameter; its ABSENCE proves
  a wider one. Both functions shuttle the entity through `ip`, which agbcc
  reproduces on its own here -- `ip` is not automatically a hard residual.

- **FUN_08099fb8** (minigame leviathan, enemy 68): `coord.x = n * 0x13000 + 0xD000`
  -- agbcc builds n*19 with `lsl #2 / add / lsl #2 / sub` then `lsl #12`.
- **FUN_08075bd0** (purple_nerple): the first LOOPING spawner matched --
  `for (i = 0; i <= 1; i++)` around the whole alloc+init. Two consequences worth
  remembering: gEnemyFnTable gets hoisted into a callee-saved register so
  INIT_ENEMY_ROUTINE collapses to a bare `ldr r0,[r7,#0x58]`, and the coord copy
  is two separate `x =` / `y =` statements, NOT `coord = e->coord` (which would
  emit the paired thumb_load_double_from_address). agbcc also saves/restores r8
  here without ever using it.
- **deathtanz_080a0934 / deathtanz_080a09f4** (projectile 14, 5 args, so the 5th
  arrives at `[sp,#0x18]`). 0934 writes a byte at 0xBC, which is inside
  `prevCoord` in the generic struct Projectile, so it needs a local struct.

- **FUN_08075c40** (purple_nerple, enemy 22) PARKED, 2 instructions short of a
  match. Everything through the coord stores is byte-identical. The ROM's tail:

      lsr r0,#0x11 / movs r1,#1 / ands r0,r1 / strb r0,[r3,#0x11]  <- work[1]
      ... coord/d stores ...
      adds r0,r3,#0 / adds r0,#0xb9 / strb r1,[r0]                 <- props[5] = r1

  It REUSES the `& 1` mask constant still live in r1; agbcc from my source picks
  r1 for the pointer temp and re-materialises `movs r0,#1`, costing 2 bytes.
  Tried a shared `u32 one` local (+4B), props[5] moved earlier (21 diffs, and it
  confirms store order = source order), and a `bool8 flip` temp (identical to the
  plain form). Register assignment only.

**The SET_XFLIP spawners** (FUN_080aac7c, FUN_080aad0c, FUN_080aada0,
FUN_080aab38 -- all projectile 32). The tell is a long inline sequence that looks
like open-coded bit twiddling but is exactly the SET_XFLIP macro:

    cmp / ldrb [x,#0xa] / orrs #0x10   (or  movs #0xef / ands)   -> flags
    strb [x,#0xa] / ... strb [x,#0x4c]                            -> spr.xflip
    movs #0x4a / mov ip / lsls #4 / movs #0x11 / rsbs / ands / orrs -> spr.oam.xflip

`__xflip__ & 1` materialises as `movs r1,#1 / ands r1,r2` when the value came
from a u8 PARAMETER, but folds to a plain `adds r1,r2,#0` when agbcc can prove
it is already 0/1 (`(e->flags >> 4) & 1`, or `e->d.x > 0`). That difference is
diagnostic, not a mismatch.
- FUN_080aad0c additionally sets `unk_2c = e->unk_28`.
- FUN_080aab38 takes a `struct Enemy*`, does `coord = e->coord` then overwrites
  `coord.y` from `*(s32*)&e->props[4]`.
- FUN_08071470 (carry_arm, enemy 17, 5 args) links the new entity into a list:
  `if (e->unk_2c != NULL) { unk_2c = NULL; props[4] = 1; }
   else { unk_2c = e; props[4] = 0; e->unk_2c = p; }`

- **FUN_080949d4 / FUN_08094a54** (enemy 63) also **corrected a data type**. The
  table at 0x08369F44 was declared `static const struct Coord16 [4]`; it is
  actually `static const s16 [4][2]`. Nothing else in the tree referenced it, so
  the struct form was only ever a guess. The two forms differ by 4 bytes:

      arr[n].x / arr[n].y   -> one base `tbl + n*4`, reused with ldrsh offsets 0 and 2
      arr[n][0] / arr[n][1] -> `lsls n,#2` CSEd, but base recomputed: `adds r1,#2`
                               then `adds r2,r2,r1`   <-- what the ROM does

  So `adds <base>, #2` followed by re-adding the scaled index means a 2D array,
  NOT a struct member. FUN_08094a54 additionally halves both with the signed
  power-of-two divide.
- **FUN_0809f970** (projectile 13): `coord.x = x - 0x400 + (RANDOM(RNG_0202f388) & 0x7FF)`.
  Operand order is load-bearing and all three groupings are 128B, so only the
  byte compare distinguishes them:
      x + (rnd & 0x7FF) - 0x400     -> add x first, then the constant  (5 diffs)
      x + ((rnd & 0x7FF) - 0x400)   -> needs an extra callee-saved reg (50 diffs)
      (rnd & 0x7FF) - 0x400 + x     -> right shape, x still added last (3 diffs)
      x - 0x400 + (rnd & 0x7FF)     -> MATCH
  `(v << 4) >> 0x15` after the LCG is `(RANDOM(rng) & 0x7FF)` -- a mask built
  from a shift pair, not an `ands`.

**The gSineTable velocity idiom** (FUN_080afbfc, FUN_080bc6ac, FUN_080bc7a4 --
all matched first probe). ~10 instructions per axis that look like open-coded
table math are just the `Cos`/`Sin` static inlines from trig.h:

    adds r0,angle,#0 / adds r0,#0x40 / lsls #0x18 / lsrs #0x17  -> COS index
    lsls r0,angle,#1                                            -> SIN index
    adds r0,r0,gSineTable / ldrsh / muls speed / cmp #0 / bge / adds #0xff / asrs #8

i.e. `d.x = Cos(angle, speed)`, `d.y = Sin(angle, speed)`. A trailing
`rsbs r0,r0,#0` is `-Sin(...)`. The `(u8)` cast inside the SIN/COS macros is
what produces the `lsls #0x18 / lsrs #0x17` pair (cast then scale by 2), so seeing
a 24/23 shift pair rather than 24/24 means an s16 table index, not a plain u8.
FUN_080bc6ac also bumps a counter on its parent: `*((u8*)e + 0xCF) += 1`.

## A SPLIT `flags2 |= WHITE_PAINTABLE` means the source does it TWICE

This retracts the "register allocation" verdict I recorded for
createGlacierleSucker, FUN_08061c74 and FUN_08061ccc. All three now MATCH.

The signature is a read-modify-write torn apart by unrelated stores:

    ldrb r2,[r3,#0xb]      <- load hoisted to the top
    movs r1,#0x10
    ... invincibleID / work[0] / unk_28 / unk_2c stores ...
    orrs r1,r2             <- OR and store sunk to the bottom
    strb r1,[r3,#0xb]

That is not the scheduler. It is agbcc CSEing **two** identical
`(p->s).flags2 |= WHITE_PAINTABLE;` statements -- one in the usual header
position after palID, one again after the later stores -- into a single
load-early/store-late pair. Writing it once can never reproduce it: I tried
flags2-first, flags2-in-place, an explicit read-early/write-late temp, and
reordering the stores, and got 16/16/14/26 diffs. Writing it twice gives 0.

I had also noted a correlation with "the second invincibleID write" on three
functions. That was reading the wrong feature: the real marker is that these
functions set invincibleID twice AND flags2 twice, and only the flags2
duplication has any effect on codegen.

- **createGlacierleJoint** (0x08082218, 204B) matched once the in-place coord
  fixup was written as `+=`:
      coord.x = prev->coord.x;  ...  coord.x += prev->coord.x - prev->unk_2c->coord.x;
  Writing `coord.x = prev->coord.x + (prev->coord.x - ...)` lets agbcc fold the
  repeated load and comes out 10 bytes short; the `+=` keeps the already-stored
  value live in a register and re-loads prev->coord.x for the subtraction.

## A countdown loop in the ROM does NOT mean a countdown in the source

FUN_080a2ea0 was parked as "preheader ordering". The ROM is a countdown:

    movs r5,#0 / ldr r6,=gProjectileFnTable / movs r4,#4    <- counter init LAST
    loop: <body, does not use the counter>
    subs r4,#1 / cmp r4,#0 / bge loop

`for (i = 4; i >= 0; i--)` gives the identical 72 bytes but emits the counter
init FIRST (6 diffs, offsets 0x2-0x7), because a for-init precedes the preheader
that hoisted invariants land in. `for (i = 0; i < 5; i++)` MATCHES -- agbcc
reverses the loop itself when the counter is unused in the body, and the
replacement counter is created in the preheader, i.e. after the hoists.
`for (i = 0; i <= 4; i++)` also matches; `do {} while (--i >= 0)` does not.
So: counter init AFTER the hoisted invariants = a reversed ascending loop.
FUN_080a2f34 does use `i` in its body, is not reversed, and stays ascending --
its `x - 0x1C00 + i * 0x3800` is strength-reduced into the preheader add plus a
per-iteration `+= 0x3800`, which is why the ROM looks like a pointer walk.

- **FUN_080aae34** (projectile 32): `taskCol = 8` and `work[0] = 8` share one
  `movs r2,#8` -- another known-value reuse, same trick as spearook's
  `taskCol = 24` / boss id 24.

**Still parked after retesting:**
- **createPantheonZombie**: 8 diffs, same length. Everything matches except that
  the ROM slots `movs r3,#0` between the parent counter's `adds r0,#1` and its
  `strb`. Tried the `tileNum = 0, palID = 0` comma form -- no change.
- **FUN_08093994**: the ROM keeps the entity in r4 and the argument in r5 (push
  {r4,r5,lr}); mine puts the entity in r3, argument in r4 (push {r4,lr}). The
  epilogue is `pop {r1} / bx r1`, i.e. r0 is LIVE at exit, so it returns
  something -- but adding `return p` emits an extra `adds r0,r4,#0` and comes out
  4 bytes LONG. So it returns a value that is already in r0 by other means.

- **createStretchedGrabArm / createStretchedArms** (pantheon_aqua_mod_obj, enemy
  38). One spawn plus a 6-iteration loop; createStretchedArms wraps the whole
  thing in a second loop over n. Both needed the reassociation temp:

      coord.x = e->coord.x - 0x1700 + n * 0x2E00;   -> agbcc folds -0x1700 into
                                                       the multiply chain, 4B short
      base = e->coord.x - 0x1700;
      coord.x = base + n * 0x2E00;                  -> MATCH

  The ROM's `ldr =0xFFFFE900 / adds` against the loaded coord BEFORE the
  `lsls/adds/lsls/subs/lsls` multiply chain is the tell: if the ROM adds the
  constant to the base first, the source pinned it in a temp. The multiply here
  is n*23 built as `((n*3) << 3) - n`, then `<< 9`.
  Inner-loop `work[2] = i + 1` shows up as `adds r3,r5,#1` hoisted ABOVE the NULL
  check, because the same value is reused as the next loop counter.

- **CreateDeathtanzRock** (enemy 27): same one-spawn-then-loop shape as the
  stretched arms; `coord.y = y + s16_ARRAY_0836773c[i]`.
- **CreateBlizzardArrow** (weapon 10): both arms of the if duplicate the ENTIRE
  init -- INIT_WEAPON_ROUTINE, `flags2 &= ~ENTITY_FLAGS2_B6`, `taskCol = 16` --
  and differ only in `gWeaponTileNum[0]/[1]` and `gWeaponPalIDs[0]/[1]`. Same
  shape as throw_blade.c:98. Condition is `(z->unk_b4).mainCopy == WEAPON_BUSTER`
  (mainCopy is at 0xE4, confirmed with an offsetof probe, and the ROM's
  `cmp r0,#0` pins the constant to 0 = WEAPON_BUSTER, not SABER).

## NEW VEIN: entity mode handlers (SetMotion + UpdateMotionGraphic only)

The spawn-helper vein is exhausted. A `bl`-target rescan finds **63** remaining
asm functions whose ONLY calls are SetMotion and UpdateMotionGraphic. They share
one skeleton:

    if ((p->s).mode[2] != 0) {          <- ldrb [r4,#0xe] / cmp #0 / beq
      SetMotion(&p->s, MOTION(a, b));   <- ldr r1,=0x0000AABB
      (p->s).mode[2] = 0;
      ...per-mode setup...
    }
    UpdateMotionGraphic(&p->s);
    ...per-mode update...
    if ((p->s).motion.state == 3) {     <- adds r0,#0x73 / ldrb / cmp #3
      (p->s).mode[1] = <next>;
      (p->s).mode[2] = 1;
    }

Offsets: mode[] at 0xC so mode[1]=0xD, mode[2]=0xE; work[] at 0x10;
motion.state at 0x73. `motion.state == 3` means the animation finished.
Matched copyxNovaStrike2 and copyx_080568bc from this skeleton on the first probe.

Caveat found while scanning: the scanner must SKIP functions whose body is a raw
`.byte` blob (INCCODE'd rather than disassembled). 117 functions looked like
call-free leaves purely because their `bl`s are invisible inside the blob.

**blizzackMode18 / blizzackMode20 PARKED** (45/46 diffs, right length). Both
write a u16 motion into the child at `unk_2c + 0xBC`; agbcc loads the constant
into r3 and copies it (`ldr r3,pool / add r1,r3,#0`) where the ROM stores from r1
directly, and it materialises the `mode[2] = 0` zero several instructions early.
Tried `(u16)` cast, `motion_t*` via Enemy props[8], separate motionID/motionSubID
stores, and SetMotion on the child: 45/45/53/27 diffs.

## Two levers from the mode-handler vein

**1. `work[n]--` then RE-READ, not a `u8` temp.** The countdown-and-test idiom
appears constantly in this vein, and the store/truncate order distinguishes them:

    u8 n = work[2] - 1;        ->  ldrb / sub / lsl#24 / lsr#24 / strb / cmp
    work[2] = n; if (n == X)       (truncate BEFORE the store)

    work[2]--;                 ->  ldrb / sub / strb / lsl#24 / lsr#24 / cmp
    if (work[2] == X)              (store the untruncated value, truncate for
                                    the compare only)  <-- what the ROM does

So `strb` sitting between the `subs` and the `lsls/lsrs` pair means a plain
`--` followed by an independent re-read of the field. This fixed both
FUN_080dd894 and FUN_0808772c.

**2. Pinning applies to a bare CONSTANT operand too.** For
`d.x = 0x400 - (work[2] & 1) * 0x800` agbcc evaluates the masked term first;
the ROM materialises 0x400 first. Swapping the multiply operands, using PIXEL(),
and writing the shift by hand all still gave 13 diffs. Only

    s32 speed = 0x400;
    d.x = speed - (work[2] & 1) * 0x800;

matches. I had this lever recorded for subexpressions; it applies to plain
constants as well.

- **FUN_080dd894** (solid/cat) also shows `mode[1]++` reusing the `ldrb r3` from
  the enclosing `mode[1] != 0` test (`adds r0,r3,#1`) -- write `++`, not `= 1`,
  even though the value is provably 1 on that path.

- **FUN_0806bfdc / FUN_0806c04c** (flopper, one per axis). A wobble driven by
  `SIN(angle) * 45` -- agbcc builds *45 as `v*3` then `(v*3 << 4) - v*3`.
  These came down to ONE byte: `asrs r0,r0,#8` vs the ROM's `lsrs r0,r0,#8`.
  **An arithmetic vs logical shift right is a signedness assertion about the
  field.** The angle accumulator had to be the `u32 unk_08` from the file's own
  `struct FlopperObject`, not the `s32` I inferred from a props[] cast; the
  struct was already in the file and I should have used it first.
  The field also holds the phase modulo 0x10000: `unk_08 = (unk_08 + 0x200) & 0xFFFF`.

- **FUN_08074d18** (snakecord), **FUN_080cb2f8** (door_2d_blue),
  **FUN_080d0804** (door_2d_gray_v) -- all matched first probe from the
  mode-handler skeleton. The two doors are identical apart from the motion id
  (0x12 vs 0x7a). Their guard is
  `if ((work[0] & 2) && !FLAG(gCurStory.s.gameflags, FLAG_2))`; agbcc reuses the
  switch value (mode[2] == 2, still live in r4) as the mask constant on its own,
  so writing the literal `& 2` is correct -- no temp needed.

- **FUN_080bfa10** (vfx 47) and **FUN_080c094c** (vfx 50), both first probe.
  Two reusable details from these:
  * The tail `ldr gVFXFnTable / ldrb [r4,#9] / lsls #2 / adds / str rN,[r4,#0xc]
    / ldr / ldr [r0,#K] / str [r4,#0x14]` is just SET_VFX_ROUTINE(p, K/4). In
    FUN_080bfa10 the modeID register is the SAME one holding motion.state (both
    are 3), so agbcc reuses it -- write the macro normally, the reuse is free.
  * `flags &= ~DISPLAY; flags &= ~FLIPABLE;` stays as TWO `ands` (0xfe then
    0xfd). agbcc does not fold them to a single `& 0xfc`, so two separate `ands`
    in the ROM means two separate statements in the source.
  * FUN_080c094c's guard is `if (work[3] == 0 || --work[3] == 0)` -- note the
    truncation is a bare `lsls #24` with no `lsrs`, i.e. a test-for-zero only.

## Reading `||` vs `&&` off the countdown guard's BRANCH TARGET

Two functions in this vein have a byte-identical instruction sequence for the
countdown guard, and differ ONLY in where the first `beq` lands:

    ldrb work[n] / cmp #0 / beq X / subs #1 / strb / lsls #24 / cmp #0 / bne END
    <body>
    END:

  * X == the BODY   ->  `if (work[n] == 0 || --work[n] == 0)`   (FUN_080c094c)
  * X == END        ->  `if (work[n] != 0 && --work[n] == 0)`   (FUN_080c248c)

I wrote the `||` form for both; FUN_080c248c came out with exactly ONE differing
byte -- the `beq` displacement (0xD004 vs 0xD00D). Everything else, including the
length, was identical. **Resolve the branch target before choosing the connective;
a one-byte diff in a `beq` is a control-flow error, not a scheduling artefact.**

- **FUN_080bba18** (vfx 33) matched first probe; `if (unk_28->mode[0] > 1)` guards
  a disappear, else the usual mode switch, tracking `pZero2` with a -0x1000 y offset.

- **FUN_080a3418** (projectile 18), **FUN_080c3e98** / **FUN_080c3f74** (vfx 64) --
  all three first probe. Two more macro sightings for the vocabulary:
  * `adds r0,#0x8c / str r2 / adds r0,#4 / str r2 / adds r0,#4 / strb r2` plus a
    following `flags &= ~4` is the **EXIT_BODY** macro (body.status,
    body.prevStatus, body.invincibleTime, then flags &= ~COLLIDABLE). The
    walking `adds r0,#4` between stores is the macro's three consecutive fields,
    not hand-written pointer arithmetic.
  * The vfx_64 pair run their mode switch and THEN, outside it, an unconditional
    `if (unk_28->mode[0] > 1)` teardown -- so the same disappear block appears
    twice in the function. That is real duplication in the source, not a
    tail-merge failure.
FUN_080a449c: FALSE BOUNDARY - shared tail of FUN_080a3c58 (uses caller r7, no prologue); match only via the parent
FUN_08094534: .byte blob in shotloid_post_p2_p2.inc - needs Ghidra decode pass
REVISIT: vfx56 FUN_080c15d4 + goldOmega1Laser parks used spr.xflip for the 0x4A RMW; correct target is oam byte6 (unused:4/xflip:1 bits) — remap and retry
FUN_0807db9c: .byte blob (inline jumptable) in mellnet_post_post_post.inc - Ghidra pass
- FUN_0807dd24 (mellnet dive): PARKED at 2 ties (cmdIdx r3-vs-r7, one d.y lsls schedule). Three NEW levers proven here, retry the parked set with them:
  1. oam attr1 flip RMW = BITFIELD INSERT `spr.oam.xflip = v` (s16 v temp) - emits the -0x11 mask + value copy natively. Applies to vfx56 + goldOmega1Laser + future flip dances.
  2. flip-select motion tables with +4/+8 base offsets = 2D array `motion_t tbl[N][2]`, direct ternary index `[k][(flags & 0x10) ? 1 : 0]` - keeps scc branchless and pools the symbol with adds #4/#8.
  3. one function-scope temp for repeated per-case loads (cmdIdx) unifies its register across cases.
  NEVER pin asm("r7") in thumb - generates mov r0,sp garbage (frame reg alias).
- FUN_0807db9c (mellnet, 188B): .byte blob (inline jumptable) - Ghidra pass with FUN_08094534.
- dd24 queued for a background permuter run (residual = pure allocation/schedule tie, ideal target).
- Levers from FUN_0805fc1c + FUN_08076df8: (a) label-filtered mdiff hides branch-POLARITY inversions - write the if with the target's taken-branch (goto snap idiom); (b) double-mask flags RMW that refuses to fold = ONE u8 var reused for the body-zero AND the mask accumulator (`(p->body).status = z = 0;` chain keeps the movs after the addr; redefining z kills the zero-value CSE exploit and claims its register); (c) coord stack copies are per-member here, struct-copy pairs elsewhere - check the load/store interleave first.
- EXIT-SHAPE SOLVED (carry_arm FUN_08071b88 exact): the double-mask + body-zero release idiom is
    u8 f = ~DISPLAY & (p->s).flags;
    s32 z = 0;              <- declared BETWEEN the two mask statements (slots the movs)
    f = f & ~FLIPABLE;
    (p->s).flags = f;
    (p->body).status = z; prevStatus = z; invincibleTime = z;
  RETRY the energy-facility door twins with this exact shape - their ip-parking may have been downstream of the f/z structure, not a real basin.
- MILESTONE 100/689 dispositioned (76 matches / 20 dual-forms / 2 triage / 2 blobs). New levers today: exit-shape (u8 f + interleaved z), phase/result-register equivalence, offset-struct row views for giv shapes, pointer-typed index for adds operand order. 58-68B bands drained.

## ret-variable lever (2026-07-28, hirondelle/autruche)
Final `if (x) return A; y; return B;` gets branch-INVERTED by agbcc (A's load
sinks to the end pool, join reorders, pools compact = ROM shorter). Fix: wrap
in a block with `TextID ret; if (x) { ret = A; } else { y; ret = B; } return
ret;` — keeps then-arm inline with its mid-function pool. This unparked
autruche_080da768 (the "r3 constant" park diagnosis was wrong — it was layout
inversion all along). Candidate retry for any park whose diff shows a
bne-vs-beq flip near the epilogue with a migrated pool word.

## register-pin constant lever (2026-07-28, guardian f50)
`cmp rX, rY`-with-constant ties (retail keeps a materialized constant in a
reg and compares reg-reg; agbcc folds to cmp #imm): house-precedented fix is
`register s32 one asm("r3"); ... one = 1; f &= one; if (f != one)` —
childre.c/math.c already pin regs, so this is in-style. Init placement
follows source order, so assign `one` exactly where retail materializes it.
Candidate for the regmove/0x64xx blizzack-family parks.

## register-pin cracks the reg-swap basin too (flopper pair)
The r4/r5 and r2/r3 register-number swaps (shelluno, locomo-intro parks) are
fixable the same way as the constant-reg ties: pin the minority variable
(`register const s16* tbl asm("r4")`, `register s32 t asm("r2")`) and let
the allocator place the rest. Flopper float pair matched with tbl+t pinned.
RETRY: shelluno_a3ec, locomo intro r0/r1, leviathan_aa10 trunc reg.

## byte-blobs are hand-decodable (tile cannon 8908)
FUN_08078908 was a raw .byte blob in the inc; hand-decoding the thumb
opcodes (160 bytes) gave a normal SET_XFLIP+motion/DDP handler that
matched first try. The two remaining blobs (mellnet FUN_0807db9c,
shotloid FUN_08094534) should get the same treatment before reaching for
Ghidra — mdiff shows no target side for blobs, so the ROM gate is the
only verification.

## FUN_080a449c (tretista, 24B) — triage 2026-07-29
Not a normal function: no prologue, reads p from r7 (caller's reg), pops the
CALLER's frame (r8/sb restore) — a shared die-tail reached by `bl` from inside
FUN_080a3c58 (lines 462/470 of tretista_post_p2_p1.inc). Cannot exist as
standalone C; must be absorbed (or NAKED-paired) when FUN_080a3c58 is done.
