# blizzack trio (blizzackMode0 / blizzackMode1 / blizzackNextMode)

All three are the same regmove tie: agbcc schedules the `mode[2] = 0` zero
early, forcing the 0x64xx constant into a spare register plus a copy that the
target avoids (const built in r3, copied to r1). Logic is faithful; the
INCCODE bodies match byte-for-byte.

**Scratches (all compile server-side, verified via the API):**

| fn | scratch | claim |
|---|---|---|
| blizzackMode0 | https://www.decomp.me/scratch/lPXha (520/3400) | https://www.decomp.me/scratch/lPXha/claim?token=eyJzbHVnIjoibFBYaGEifQ.H0dDWvMmLZo0cFCEtGlkFzNeork |
| blizzackMode1 | https://www.decomp.me/scratch/GOT18 (615/4200) | https://www.decomp.me/scratch/GOT18/claim?token=eyJzbHVnIjoiR09UMTgifQ.-jxmUNssO2_eM2bj-UwByugqWCw |
| blizzackNextMode | https://www.decomp.me/scratch/R35me (615/3500) | https://www.decomp.me/scratch/R35me/claim?token=eyJzbHVnIjoiUjM1bWUifQ.nPX0vLSu1Tf9VFt4nROjjJ6fM1o |

DEAD (first posting, context leaked .incbin so the server assembler failed;
do NOT claim): VGRlc, yt9Gj, GhyhM. Lesson recorded: local kit check must run
the ASSEMBLER too, agbcc alone passes .incbin through silently.

## Paste into each About tab

One regmove from matching (per function). agbcc zeroes `mode[2]` before
materializing the 0x64xx constant, so the constant needs a spare register
and an extra copy; the ROM builds the constant late in r3 and stores it
directly. Any source shape that delays the `mode[2] = 0` store past the
constant store without changing the logic? Compiler: agbcc
(-mthumb-interwork -O2 -fshort-enums).

## Reusable context

`notes/decompme/ctx-agbcc-clean.c` is the full genctx.sh output made
agbcc+assembler clean (unnamed-varargs prototype fixed, 4 leaked const
struct definitions and 25 leaked __asm__/.incbin rodata lines stripped,
MOTION macro re-added post-preprocess). It compiles + assembles under the
exact decomp.me agbcc preset; reuse it for every future rmz3 scratch.
