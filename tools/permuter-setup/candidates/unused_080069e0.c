static void unused_080069e0(u32* dst, u32* src, u16 idx) {
  s32 y = 0;
  u32 a = src[idx * 2];
  u32 b = src[idx * 2 + 1];
  do {
    u32* p = (u32*)((u8*)dst + y * 128);
    s32 x = 15;
    do {
      *p = a;
      *(u32*)((u8*)p + 0x40) = b;
      p++;
    } while (--x >= 0);
  } while (++y <= 15);
}
