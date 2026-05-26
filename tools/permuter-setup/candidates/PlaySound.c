// Seed from src/sound.c's MODERN branch. Manual diff shows the only issue
// is agbcc emitting `lsrs r2, r0, #16; adds r4, r2, #0` (2 instructions)
// instead of `lsrs r4, r0, #16` (1 instruction) — 2 bytes too long.
// Probably needs a phrasing that makes the masked id land directly in
// a callee-saved register.
s16 PlaySound(SoundID id) {
  if (gSongTable[id].ms == gSongTable[SE_ZAKO_STUN].ms) {
    if ((SoundID2 == MUS_DUMMY) || (SoundID2 == SE_ZAKO_STUN)) {
      SoundID2 = id;
    }
    return id;
  }
  if (id == MUS_DUMMY) {
    return MUS_DUMMY;
  }
  m4aSongNumStart(id);
  return id;
}
