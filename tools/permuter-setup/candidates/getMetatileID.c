static s16 getMetatileID(s32 x, s32 y) {
  const s32 mx = (x >> 12);  // METACOORD inlined — macro lost during preproc strip
  const s32 my = (y >> 12);
  u16* m = gOverworld.terrain.tilemap;
  if (((u32)mx > 0x770) || (my < 0) || (my > 0x4F5)) {
    return -1;
  }
  return ((s16*)m)[my * m[0] + mx + 2];
}
