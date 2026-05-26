// Speculative — the asm computes abs(FUN_08009f6c(x ± 0x2000, y) - y)
// but discards it, returning 0xF00 unconditionally. agbcc -O2 normally
// DCEs the abs(). `register asm("r1")` forces r1 allocation and pins
// the computation in place, which is the agbcc trick used elsewhere
// in this codebase (e.g. unused_080e96c8 in math.c).
extern s32 FUN_08009f6c(s32 x, s32 y);
// Best manual seed: pin r4=x+dx, r5=result, r1=d. Orig saves
// {r4, r5, r6, lr}; with these pins, agbcc saves r4, r5, r6 (the last
// for y, naturally) — matches the original prologue/epilogue.
// Remaining diff: agbcc eagerly loads -0x2000 from the literal pool
// then conditionally overwrites with 0x2000 in the !n branch, which
// is 2 bytes shorter than the original's straight if-else. Permuter
// needs to find a rephrasing that defeats this optimization.
static s32 unused_080b4960(s32 x, s32 y, bool8 n) {
  s32 dx;
  register s32 sx asm("r4");
  register s32 r asm("r5");
  register s32 d asm("r1");
  if (n) { dx = 0x2000; } else { dx = -0x2000; }
  sx = x + dx;
  r = FUN_08009f6c(sx, y);
  d = r - y;
  if (d < 0) d = -d;
  asm volatile("" : "+r"(d) : "r"(r), "r"(sx));
  return 0xF00;
}
