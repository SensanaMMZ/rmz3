// Per the asm, the B channel does shift-before-multiply (not multiply-
// before-shift like R and G). The existing C in src/gfx.c notes that
// the symmetric version "turns the screen yellow".
static void FadeBlack(u32* src, u32* dst, u32 lv, u32* mask) {
  s32 i;
  for (i = 0xff; i >= 0; i--) {
    u32 c = *src;
    u32 r = (((c & mask[0]) * lv) >> 5) & mask[0];
    u32 g = (((c & mask[1]) * lv) >> 5) & mask[1];
    u32 b = (((c & mask[2]) >> 5) * lv) & mask[2];
    *dst = r | g | b;
    src++;
    dst++;
  }
}
