u8 FUN_080e964c(u32 a, s32 b, s32 c) {
  s32 sign;
  if (((a - b + c) & 0xff) <= c * 2) {
    return a;
  }
  if (((a - b) & 0xff) > 0x7f) {
    sign = -1;
  } else {
    sign = 1;
  }
  return (b + c * sign) & 0xff;
}
