void SeaOtterElf_Init(struct Elf* p) {
  struct Zero* z = *(struct Zero**)&p->buffer[0];
  struct Rect r = gZeroRanges[z->posture];
  InitNonAffineMotion(&p->s);
  ResetDynamicMotion(&p->s);
  (p->s).flags |= (1 << 0);
  (p->s).flags |= (1 << 1);
  SetMotion(&p->s, GetElfMotion(1));
  UpdateMotionGraphic(&p->s);
  (p->s).spr.xflip = 0;
  (p->s).spr.oam.xflip = 0;
  (p->s).flags &= ~(1 << 4);
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
  (p->s).unk_2c = ((void *)0);
  { u32 tbl, id; EntityFunc** routine_table; tbl = (u32)(gElfFnTable); id = (((struct Entity*)p)->id) << 2; routine_table = (EntityFunc**)(tbl + id); *(u32*)(((struct Entity*)p)->mode) = 1; ((struct Entity*)p)->onUpdate = (void*)(*routine_table)[1]; };
  SeaOtterElf_Update(p);
}
