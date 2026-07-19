// ladder_08026bb0 near-miss seed (macros expanded: METATILE_SOFT_PLATFORM|0xF
// = 0x800F, |0xE = 0x800E). Off by: (1) the dead u16 mask on the 2nd
// GetMetatileAttr result that agbcc keeps in the target but DCEs here, and
// (2) the 0x800E compare landing in r0 vs the target's callee-saved r6.
u8 ladder_08026bb0(struct Zero* z, const struct Rect* range, bool8 _) {
  u8 val;
  metatile_attr_t attr = GetMetatileAttr((z->s).coord.x, (z->s).coord.y + range->y);
  if (attr == 0x800F) {
    val = 1;
  } else if (attr == 0x800E) {
    val = 2;
  } else {
    struct Coord* pc = &(z->unk_b4).prevCoord;
    attr = GetMetatileAttr(pc->x, pc->y + range->y);
    val = 3;
  }
  return val;
}
