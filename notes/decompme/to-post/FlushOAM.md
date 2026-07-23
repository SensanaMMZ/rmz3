# FlushOAM (gpu_regs.c) — 120 B, single-relocation pool anchoring

Ask text for the About tab:

---
OAM flush routine (GBA, agbcc = GCC 2.9 Thumb, -O2 -fshort-enums). Loop shape
and register roles match. The blocker is the literal pool: the target holds
ONE relocated word, gOamManager+0x400 (the address of the .p member), and
reaches everything from it — [r5,#0] is p, [r5,#4] is dispcnt, and the
128-entry buffer base is r5 - 0x400 (pool constant 0xfffffc00).

My version emits TWO relocations: gOamManager (offset 0) and the tail.
I tried &gOamManager.p, &gOamManager.buf[128], gOamManager.buf + 128, each
crossed with naming vs deriving the DMA source — always two relocations.

What makes GCC 2.9 route every access through a single non-zero offset into
a global? Deriving the buffer via a pool-loaded -0x400 is more expensive than
anchoring at 0, so I suspect the original source never names gOamManager.buf
at all (a different struct layout? a pointer global to the tail?).
---

**POSTED 2026-07-22**: https://decomp.me/scratch/nkRzd
Claim (owner-only link, then paste the ask above into About):
https://www.decomp.me/scratch/nkRzd/claim?token=eyJzbHVnIjoibmtSemQifQ.kwCnyBb0LAffOhIyKoypAW5C_ho
