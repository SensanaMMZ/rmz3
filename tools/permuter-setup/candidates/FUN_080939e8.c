bool8 FUN_080939e8(struct Entity* p, s32 dir) {
  s32 x = p->coord.x - 0xe00;
  if (dir > 0) {
    x += 0x1c00;
  }
  if ((u16)FUN_080098a4(x, p->coord.y + 0xa00)) {
    return 1;
  }
  return 0;
}
