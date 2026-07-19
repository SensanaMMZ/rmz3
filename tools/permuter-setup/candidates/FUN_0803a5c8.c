u8 FUN_0803a5c8(s32 a0, s32 a1, s32 a2) {
  if ((u32)((a0 - a1 + a2) & 0xff) > (u32)(a2 << 1)) {
    s32 s = (((a0 - a1) & 0xff) > 0x7f) ? -1 : 1;
    return (a1 + a2 * s) & 0xff;
  }
  return a0;
}
