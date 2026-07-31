# Decompilation Progress Report

Updated: 2026-07-30

## Scope

This report tracks the effort to decompile every remaining unclaimed
assembly function in the game region (the 689-function queue captured in
`build/undeclared_game_queue.txt`). Each function is worked smallest-first
and is only counted as done when one of the following holds:

- **Matched** — the C replaces the assembly entirely and the build gate
  (`make compare` → `rmz3.gba: OK`, full-ROM SHA-1) proves the ROM is
  byte-identical.
- **Parked (dual-form)** — the function's logic is fully decompiled and
  builds under `MODERN`, but one or more compiler-layout details (register
  homes, pool placement, scheduling slots) could not be reproduced after a
  bounded number of attempts. The retail build keeps the original assembly
  via `NON_MATCH`/`INCCODE`, so the ROM stays byte-exact. Every parked
  function carries a comment naming the exact blocker.

## Headline numbers

| Category | Functions | Share |
|---|---|---|
| Matched (byte-exact C) | 422 | 61.2% |
| Parked (dual-form C, blocker documented) | 94 | 13.6% |
| Deferred (data-as-code blobs, need disassembly pass) | 6 | 0.9% |
| **Dispositioned total** | **522** | **75.8%** |
| Remaining (live) | 167 | 24.2% |

By code size: the queue totals 221,936 bytes of function bodies, of which
120,412 bytes (54.3%) are dispositioned. The remaining 167 functions are
disproportionately large (99,552 bytes): 19 are under 300 bytes, 83 are
300–600, 41 are 600–1000, and 24 exceed 1000 bytes.

## Per-area breakdown

| Area | Matched | Parked | Live | Deferred |
|---|---|---|---|---|
| boss | 99 | 19 | 53 | – |
| enemy | 148 | 27 | 62 | 3 |
| solid | 45 | 18 | 26 | – |
| projectile | 46 | 11 | 15 | 2 |
| vfx | 39 | 4 | 7 | – |
| cyberelf | 18 | 2 | – | – |
| stage gfx/landscape | 16 | 10 | 3 | 1 |
| player | 4 | 2 | – | – |
| weapon | 4 | 1 | 1 | – |
| minigame | 3 | – | – | – |

## Parked-function basins

Most of the 94 dual-forms fall into a small number of recurring layout
basins rather than logic gaps. The main classes, each documented in the
affected files:

- **Home transposition** — two values with symmetric lifetimes come out
  with swapped register homes (e.g. r9↔r10 staged constants); everything
  else byte-exact.
- **Pool/scratch coin flips** — literal-pool entry order or a scratch
  register pick differs with no source-level lever found.
- **Formation-home** — a pointer/base formed in one register and copied to
  its long-term home; source shapes either skip the copy or misorder loads.
- **Chained-RNG family** — multi-draw random sequences where intermediate
  register roles resist all tested shapes.
- **Snapshot-register convention** — mid-function spill/reload slots tied
  to allocation order.

A single new insight into one of these classes typically unparks several
functions at once (this has already happened once with the scanline-table
builder family).

## Verification discipline

Every match is gated by a full ROM rebuild and SHA-1 comparison against
the reference image; a function is only recorded as matched when the gate
prints `rmz3.gba: OK`. Instruction-stream diffs of the object file against
the original assembly are used during development, but never as the final
proof. Parked functions keep the original bytes flowing into the ROM, so
the shipping image is byte-identical at every commit on the branch.

## Deferred items (6)

`FUN_080a449c`, `snowyplains_0801326c` (scanline table), `FUN_08086b6c`,
`FUN_080a5290`, `FUN_0807db9c`, `FUN_080748a8` — these regions decode as
instructions but behave as data tables (or have false function
boundaries). They need a dedicated disassembly/data-recovery pass rather
than function-by-function matching.

## Recent session (2026-07-30)

Nine functions dispositioned, eight byte-matched, one parked:

| Function | File | Result |
|---|---|---|
| FUN_080bc200 | src/vfx/unk_36.c | matched |
| copyx_0805763c | src/boss/copy_x.c | matched |
| FUN_0805c87c | src/boss/hanumachine.c | matched |
| FUN_0806ee94 | src/enemy/lemmingles.c | matched |
| FUN_080a9810 | src/projectile/unk_27.c | matched |
| FUN_080cabe8 | src/solid/icebon_ice.c | parked (home transposition) |
| childreStartRising | src/boss/childre.c | matched |
| glacierle_080594dc | src/boss/glacierle.c | matched |

Session highlights: the `SET_XFLIP`/`SET_YFLIP` porter macros were shown
to reproduce entire retail flip-dispatch arms (including the folded
variable-argument form), and several new source-shape techniques for
register-home control were added to `MATCHING_IDIOMS.md` territory
(value-copy via stored-field re-read, compound-assign multiply destination
control, keep-alive placement for allocation priority).

## Next up (smallest-first)

FUN_08082484 (276 B), FUN_080a9358 (276), FUN_0807e060 (280),
FUN_080921c8 (280), FUN_080a8a38 (280), FUN_080a96f8 (280),
deathtanzMode16 (280), glacierle_080593c4 (280), ActorLastX_Update (288),
FUN_08054fcc (288).

At the recent pace (7–10 dispositions per working session) the live queue
projects to roughly 17–24 further sessions, with per-function effort
rising as the median size grows.
