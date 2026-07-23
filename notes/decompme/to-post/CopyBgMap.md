# CopyBgMap

**Scratch:** https://www.decomp.me/scratch/UgMGD (score 535/4000)

**Claim link (open while logged in):**
https://www.decomp.me/scratch/UgMGD/claim?token=eyJzbHVnIjoiVWdNR0QifQ.mS36tNFckM46SjPIs1ieMAne3Do

---

## Paste into the About tab

One instruction short (39 vs 40). The target copies **both** arguments into safe registers in the prologue, before any use:

```
mov  ip, r0        @ dst
adds r4, r1, #0    @ src
ldrb r6, [r4, #4]
ldrb r7, [r4, #6]
```

agbcc instead reads through r1 directly and only parks `dst` in `ip` later, after the address arithmetic:

```
ldrb r6, [r1, #4]
ldrb r7, [r1, #6]
adds r4, r1, #0
...
mov  ip, r0
```

Tried: copying both args to locals at the top (no change); an `s64` temp for the offset (adds a copy, but the wrong one — goes to 41); recomputing the row pointer from `dst` inside the loop (49). None reproduce the early prologue copies.

Is there a source shape that makes GCC 2.9 move both incoming argument registers into `ip`/`r4` up front? Compiler: agbcc, `-mthumb-interwork -O2 -fshort-enums`.

**MOOT 2026-07-22**: CopyBgMap was proven to ALREADY MATCH the ROM — the 535
score here came from compiling at MODERN=1, whose SET_ENTITY-style macro swaps
inflated the diff (see notes/backlog-truth.md). Abandon this scratch or note it
as solved; do not spend effort on it.
