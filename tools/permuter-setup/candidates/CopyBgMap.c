void CopyBgMap(u16* dst, struct BgMapHeader* src, u8 x, u8 y) {
  u8 w = src->w;
  u8 h = src->h;
  const u16* data = (const u16*)(src + 1);
  u16* base = dst + y * 32 + x;
  u8 row, col;
  for (row = 0; row < h; row++) {
    u16* p = base + row * 32;
    for (col = 0; col < w; col++) {
      p[col] = *data++;
    }
  }
}
