void FUN_080ce538(struct Solid* p) {
  struct LocomoIFPlatformObject* obj = (struct LocomoIFPlatformObject*)p;
  struct Solid* parent = (struct Solid*)(p->s).unk_28;
  u32 phase = obj->unk_00 >> 8;
  (p->s).coord.x = (parent->s).coord.x;
  (p->s).coord.x += (s16)gSineTable[(u8)(phase + 0x40)] * 56;
  (p->s).coord.y = (parent->s).coord.y - 0x1000;
  (p->s).coord.y += (s16)gSineTable[phase] * 56;
}
