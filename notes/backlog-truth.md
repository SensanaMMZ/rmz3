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
