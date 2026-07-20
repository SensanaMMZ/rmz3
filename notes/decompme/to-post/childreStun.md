# childreStun

**Scratch:** https://www.decomp.me/scratch/asMGq

**Claim link (open while logged in):**
https://www.decomp.me/scratch/asMGq/claim?token=eyJzbHVnIjoiYXNNR3EifQ.2pu4x4NEVwp9fs8DmaoJ-XmJVsc

---

## Paste into the About tab

Reconstructed with m2c plus field mapping: this reaches **exact size parity (96 vs 96 instructions)**, but the branch layout differs. The target emits `cmp; ble <else>; str r1, [coord.x]` — storing straight out of the limit register — while agbcc gives me `bgt` with the arms laid out the other way.

Variants tried, all staying at 96/96 with the same polarity flip:

- a separate `lim` temp;
- inlining `x + 0x6000` at both uses;
- reloading the base separately in each arm;
- swapping the compare operands.

Is there a source shape that makes GCC 2.9 lay out `if (a > b) { store } else { ... }` with the else as the fallthrough here? Same project and compiler as my Beetank_Update scratch (agbcc allocation and layout ties).
