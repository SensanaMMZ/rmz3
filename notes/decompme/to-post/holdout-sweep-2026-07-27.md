# Holdout sweep scratches (2026-07-27)

Eight more open holdouts posted, all verified compiling server-side via the
API (success=True). Context = notes/decompme/ctx-agbcc-clean.c plus
per-function extras (macros the -P preprocess erased, extern decls for
file-local data). Local gate is now cpp -> agbcc -> as (agbcc alone does NOT
preprocess: // comments and #define silently break, and it hid an implicit
MOTION() call in an earlier check).

| fn | file | scratch (score) | claim |
|---|---|---|---|
| onRod | player/zero/attack/ladder.c | https://www.decomp.me/scratch/DiHnZ (210/3600) | https://www.decomp.me/scratch/DiHnZ/claim?token=eyJzbHVnIjoiRGlIbloifQ.HLyRigbL-K9ZM_IRi-_McfPOe3Y |
| ElfMenuFocusLoop_TabSelect | game/menu/elf.c | https://www.decomp.me/scratch/hG8iv (75/13300) | https://www.decomp.me/scratch/hG8iv/claim?token=eyJzbHVnIjoiaEc4aXYifQ.RnKsZXs0FyQiOkNzIXyhryoyYaY |
| CielMinigameEnemy2_Init | enemy/minigame/ciel2.c | https://www.decomp.me/scratch/9P5L4 (2750/9900) | https://www.decomp.me/scratch/9P5L4/claim?token=eyJzbHVnIjoiOVA1TDQifQ.VpGqqilikJbrLGhdvlpuzXCv9eI |
| Cmd_flag | script_command.c | https://www.decomp.me/scratch/9lETy (2820/6600) | https://www.decomp.me/scratch/9lETy/claim?token=eyJzbHVnIjoiOWxFVHkifQ.BEQ1i6rkBJC9GsZvxBDW8o04mQk |
| PrintAllStrings | bg0/text.c | https://www.decomp.me/scratch/RZnia (1325/6500) | https://www.decomp.me/scratch/RZnia/claim?token=eyJzbHVnIjoiUlpuaWEifQ.LCmLIZG3zqQen3PBByi8M-fgxT4 |
| ResetCharTiles | bg0/text.c | https://www.decomp.me/scratch/WySr0 (1035/3600) | https://www.decomp.me/scratch/WySr0/claim?token=eyJzbHVnIjoiV3lTcjAifQ.gUeuTzeoN2lO8203d-sB3jHW_i0 |
| FUN_08050090 | boss/anubis.c | https://www.decomp.me/scratch/rxbw4 (2645/2700) | https://www.decomp.me/scratch/rxbw4/claim?token=eyJzbHVnIjoicnhidzQifQ.SqnZAZejnPFIK1lgs41A1oSCjv8 |
| childre_08040428 | boss/childre.c | https://www.decomp.me/scratch/ovjs9 (3100/8400) | https://www.decomp.me/scratch/ovjs9/claim?token=eyJzbHVnIjoib3ZqczkifQ.hCi3yZJd9CNqYoFblxXpv6xbivA |

With the blizzack trio (lPXha/GOT18/R35me) this covers every verified-open
holdout from notes/rank-verified.md plus the surviving hand-triaged ties.
Claim each promptly -- anonymous scratches expire.

## About-tab notes (paste per scratch)

- onRod: packed-struct reader, permuter-poisoned; retail CSEs the rod-state
  pointer where agbcc rebuilds r3+0x124. Verdict class from the 2026-07-14
  sweep.
- ElfMenuFocusLoop_TabSelect: 2 instructions short of the target
  (cur < exp); likely one hoisted subexpression.
- CielMinigameEnemy2_Init / Cmd_flag / PrintAllStrings / ResetCharTiles /
  childre_08040428: regalloc/scheduling ties, MODERN logic is faithful, the
  INCCODE body byte-matches.
- FUN_08050090: near-max score -- the MODERN body is an early draft; treat
  as a from-scratch reconstruction target rather than a tie.
