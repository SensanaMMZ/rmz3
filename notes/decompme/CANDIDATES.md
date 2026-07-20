# decomp.me candidate holdouts (ranked by closeness)

Post these with `tools/scratch_up.py`. Closest first — the register-allocation
ties where an outside solver is most likely to find the missing lever.

| function | file | gap | class | posted |
|---|---|---|---|---|
| readKeyInput | src/input.c | — | s64 live-range split | SOLVED (PR #46) |
| CountRodButton | src/player/zero/input/util.c | 1 instr | z register-home tie | https://decomp.me/scratch/JxrgW |
| CopyBgMap | src/game/menu.c | 1 instr | prologue arg-copy placement | https://decomp.me/scratch/UgMGD |
| childreStun | src/boss/childre.c | ~ | branch-layout polarity | https://decomp.me/scratch/asMGq |
| Beetank_Update | src/enemy/beetank.c | min-block | r8 reload base (proven CSE-remat) | https://decomp.me/scratch/gwvlA |
| onRod | src/player/zero/attack/ladder.c | 4 | CSE: target reuses r0 vs rebuild r3+0x124 | — |
| blizzackMode0/1 | src/boss/blizzack.c | 7-8 | const 0x6400 built r3 then copied r1 | — |
| ElfMenuFocusLoop_TabSelect | src/game/menu/elf.c | 8 (cur<exp) | missing 2 instrs | — |
| CielMinigameEnemy2_Init | src/enemy/minigame/ciel2.c | 10 | reg-alloc | — |

## Do NOT bother posting

- FUN_0802e338 family (walk/ladder/wall IsAttackOK twins): proven unblockable —
  the branch condition *is* the assigned value, so agbcc always folds+merges.
- Beetank r8: mechanism proven (CSE rematerializes the constant); the scratch is
  up mainly to document the question, not because clean C can reach it.
- gOverworld/packed-struct readers (IsInHazard, onRod caveat): permuter-poisoned;
  a scratch is fine but the sandbox strips packing.
