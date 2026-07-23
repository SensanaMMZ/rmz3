// Loop shape and register roles (r4 = write pointer, r5 = bound) match.
// The open problem: the target's literal pool holds ONE relocation,
// gOamManager+0x400 (the address of .p), and derives everything from it --
// [r5,#0] = p, [r5,#4] = dispcnt, buffer = r5 - 0x400. This version emits
// TWO relocations (gOamManager and gOamManager+0x400). Six spellings of the
// address all produce the two-relocation form, so it is not controlled by
// how the address is written. Suspicion: the original never names offset 0
// (gOamManager.buf) at all.
void FlushOAM(void) {
  vu16 dispcnt = REG_DISPCNT;
  struct OamData* p = gOamManager.p;
  struct OamData* end = (struct OamData*)&gOamManager.p;

  dispcnt &= ~(DISPCNT_OBJ_ON);
  dispcnt |= gOamManager.dispcnt;
  REG_DISPCNT = dispcnt;

  while (PTR_U32(p) < PTR_U32(end)) {
    *((u16*)p) = 0x200;
    p++;
  }
  DmaCopy32(3, end - 128, OAM, 1024);
  gOamManager.p = end - 128;
}
