
void SeaOtterElf_Update(struct Elf* p);

void SeaOtterElf_Init(struct Elf* p) {
  struct Zero* z = *(struct Zero**)&p->buffer[0];
  struct Rect r = gZeroRanges[z->posture];
  InitNonAffineMotion(&p->s);
  ResetDynamicMotion(&p->s);
  (p->s).flags |= DISPLAY;
  (p->s).flags |= FLIPABLE;
  SetMotion(&p->s, GetElfMotion(1));
  UpdateMotionGraphic(&p->s);
  (p->s).spr.xflip = FALSE;
  (p->s).spr.oam.xflip = FALSE;
  (p->s).flags &= ~X_FLIP;
  (p->s).coord.x = (z->s).coord.x + r.x;
  (p->s).coord.y = (z->s).coord.y + r.y;
  *(s32*)&p->buffer[4] = (p->s).coord.x;
  *(s32*)&p->buffer[8] = (p->s).coord.y;
  {
    u8 zz = 0;
    p->buffer[12] = zz;
    *(u16*)&p->buffer[14] = 0x200;
    p->buffer[13] = 0x20;
  }
  (p->s).unk_2c = NULL;
  SET_ELF_ROUTINE(p, ENTITY_UPDATE);
  SeaOtterElf_Update(p);
}
