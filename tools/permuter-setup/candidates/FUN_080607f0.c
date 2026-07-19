bool8 FUN_08060838(struct Boss* p);
void FUN_080607f0(struct Boss* p) {
  s32 b;
  *(u8*)((u8*)p + 0x4c) = FUN_08060838(p) & 1;
  b = FUN_08060838(p) & 1;
  *(u8*)((u8*)p + 0x4a) = (b << 4) | (*(u8*)((u8*)p + 0x4a) & ~0x10);
  if (b) {
    (p->s).flags |= 0x10;
  } else {
    (p->s).flags &= ~0x10;
  }
}
