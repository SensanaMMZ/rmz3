# door_2d_gray_v / door_2d_blue onCollision (one scratch, two doors)

The two handlers are instruction-identical twins (only label addresses
differ), so one solve matches both. gray_v was ranked as a "2-byte pure
stub" by the size join -- that was the static-name ambiguity dup_scan
warns about; the real body is 78 instructions.

**Scratch (compiles server-side, verified via API):**
https://www.decomp.me/scratch/QGHW3 (475/7900)
Claim: https://www.decomp.me/scratch/QGHW3/claim?token=eyJzbHVnIjoiUUdIVzMifQ.AM2MuxMnQS7HpZwC3eaLU6RyFk0

## Paste into the About tab

One instruction from matching. Retail duplicates the `mode[2] = story`
store in both arms of the flag2-taken branch and keeps `story` in scratch
r2; agbcc instead copies story into callee r4 (`adds r4, r2, #0`) and then
cross-jumps the second arm's stores into the non-flag2 tail (they become
register-identical), losing one instruction (77 vs 78).

Tried: store hoisted after the if/else; store duplicated in both arms;
declaration order both ways; story via repeated FLAG() CSE (worse, 81);
register-pin story to r2 (perturbs the z allocation, r5->r4). The blue
door's draft (NON_MATCH in-tree) is the same tie.

Any source shape that keeps story in a caller-saved reg without disturbing
z in r5? Compiler: agbcc, -mthumb-interwork -O2 -fshort-enums.

Root-cause tag: regalloc-tie (+ cross-jump).
