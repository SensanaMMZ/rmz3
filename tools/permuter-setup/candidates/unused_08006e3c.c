static u8 unused_08006e3c(void* p, u32 unk_x, u32 unk_y) {
  u8* arr = ((u8**)p)[3];
  u8 stored = arr[arr[0] * (unk_y / 10) + (unk_x / 15) + 4];
  u32 idx = (unk_y % 10) * 15 + stored * 150 + (unk_x % 15);
  u16 mid = ((u16*)((void**)p)[2])[idx];
  return ((u8*)((void**)p)[0])[mid * 2];
}
