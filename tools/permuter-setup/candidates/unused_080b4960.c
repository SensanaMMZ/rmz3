// MATCHED — landed in src/vfx/unk_07.c. Kept here for reference.
//
// Key tricks:
//  1. `register s32 r asm("r5")` pin keeps result in r5 across the call,
//     forcing prologue to save {r4, r5, r6, lr}.
//  2. `else { r = -0x2000; dx = r; }` (via the r5-pinned register) defeats
//     agbcc's eager LP-load optimization that would otherwise emit
//     `ldr r1 = -0x2000; cmp; if n: overwrite` (2 bytes shorter, wrong).
//  3. `register s32 ret asm("r0")` + assigning at end keeps r0 live,
//     matching the orig's `pop {r0}; bx r0` epilogue (void return type).
//  4. `asm volatile("" : "+r"(d), "+r"(ret) : "r"(r), "r"(sx))` barrier
//     keeps the abs() and the constant alive — agbcc -O2 would DCE both.
extern s32 FUN_08009f6c(s32 x, s32 y);
static void unused_080b4960(s32 x, s32 y, bool8 n) {
  s32 dx;
  register s32 sx asm("r4");
  register s32 r asm("r5");
  register s32 d asm("r1");
  register s32 ret asm("r0");
  if (n) {
    dx = 0x2000;
  } else {
    r = -0x2000;
    dx = r;
  }
  sx = x + dx;
  r = FUN_08009f6c(sx, y);
  d = r - y;
  if (d < 0) d = -d;
  ret = 0xF00;
  asm volatile("" : "+r"(d), "+r"(ret) : "r"(r), "r"(sx));
}
