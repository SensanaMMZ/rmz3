# unused_080e14d4 (cyberelf.c) — 52 B, dead compare after the loop

Ask text for the About tab:

---
Backwards search of a circular entity list (GBA, agbcc = GCC 2.9 Thumb, -O2
-fshort-enums). 46/52 bytes match. The target keeps a *provably dead*
`cmp r1, r2 / bne` after the loop:

    0x18  beq  -> 0x24    sentinel exit, threaded straight past the compare
    0x1e  bne  -> 0x14    id mismatch, loop back
    0x20  cmp  r1, r2     <- only reachable when r1 != r2 is already known
    0x22  bne  -> 0x2c

So the in-loop sentinel exit WAS jump-threaded past the post-loop compare,
but the fall-through (id match) path was not, leaving the compare alive.
Every shape I try (break out of do/while, duplicated `return NULL`, compound
while condition, ternary) lets agbcc delete the compare entirely and land at
46 bytes. What source shape leaves it in?
---

**POSTED 2026-07-22**: https://decomp.me/scratch/vjfuX
Claim (owner-only link, then paste the ask above into About):
https://www.decomp.me/scratch/vjfuX/claim?token=eyJzbHVnIjoidmpmdVgifQ.MnNSvfFtDPjc1B3Y9fENrukoNz8
