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
