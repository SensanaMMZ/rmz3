// Speculative — the asm computes abs(FUN_08009f6c(x ± 0x2000, y) - y)
// but discards it, returning the constant 0xF00 unconditionally.
// The discarded computation is preserved in the original binary (agbcc
// didn't dead-code-eliminate it), suggesting the source uses a
// side-effecting helper or an inline operation the compiler doesn't see
// through.
extern s32 FUN_08009f6c(s32 x, s32 y);
static s32 unused_080b4960(s32 x, s32 y, bool8 n) {
  s32 dx = n ? 0x2000 : -0x2000;
  s32 r = FUN_08009f6c(x + dx, y);
  s32 d = r - y;
  if (d < 0) d = -d;
  (void)d;
  return 0xF00;
}
