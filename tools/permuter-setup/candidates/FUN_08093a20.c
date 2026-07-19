s32 FUN_08093a20(struct Entity* p) {
  struct Entity* z = (struct Entity*)pZero2;
  s32 zx = z->coord.x;
  s32 px = p->coord.x;
  s32 f = (px > zx) ? 1 : 0;
  s32 t = zx - 0x6000 + ((3 * f) << 0xe) - px + 0x800;
  return (t <= 0xfff) ? 2 : f;
}
