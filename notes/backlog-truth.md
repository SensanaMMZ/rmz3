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
