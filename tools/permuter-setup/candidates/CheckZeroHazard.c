
void CheckZeroHazard(struct Zero* z) {
  s32 x = (z->s).coord.x;
  s32 y = (z->s).coord.y - PIXEL(15);
  u8 i;
  u8 len;
  u8* cnt = &z->hazardCount;
  *cnt = 0;
  i = 0;
  len = W_TERRAIN_V2.objectLen;
  while (i < len) {
    u32 dx = x - *(s32*)((u8*)&HAZARD(0)->start.x + i * 24);
    u32 w = (u32)W_TERRAIN_V2.objects[i].w + PIXEL(31);
    if (dx + w < w * 2) {
      u32 dy = y - *(s32*)((u8*)&HAZARD(0)->start.y + i * 24);
      u32 h = (u32)W_TERRAIN_V2.objects[i].h + PIXEL(31);
      if (dy + h < h * 2) {
        z->hazard[*cnt] = i;
        (*cnt)++;
      }
    }
    i++;
  }
}
