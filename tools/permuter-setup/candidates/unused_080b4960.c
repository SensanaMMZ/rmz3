// Speculative — the asm computes abs(FUN_08009f6c(x ± 0x2000, y) - y)
// but discards it, returning 0xF00 unconditionally. agbcc -O2 normally
// DCEs the abs(). `register asm("r1")` forces r1 allocation and pins
// the computation in place, which is the agbcc trick used elsewhere
// in this codebase (e.g. unused_080e96c8 in math.c).
extern s32 FUN_08009f6c(s32 x, s32 y);
static s32 unused_080b4960(s32 x, s32 y, bool8 n) {
  s32 dx = n ? 0x2000 : -0x2000;
  s32 r = FUN_08009f6c(x + dx, y);
  register s32 d asm("r1") = r - y;
  if (d < 0) d = -d;
  asm volatile("" : "+r"(d));  // barrier to keep abs() alive (matches orig)
  return 0xF00;
}
