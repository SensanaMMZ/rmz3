// PlaySound near-miss seed. Macros pre-expanded (SE_ZAKO_STUN=41, MUS_DUMMY=0)
// because the candidate is appended AFTER cpp and parsed by pycparser — no
// header macros available. Off by 1 coalescing copy: agbcc emits
//   lsrs r2, r0, #16 ; adds r4, r2, #0
// (extend (u16)id into scratch, copy to callee-saved home) instead of the
// target's direct  lsrs r4, r0, #16. Needs a phrasing that lands the masked
// id straight in the home register.
s16 PlaySound(SoundID id) {
  if (gSongTable[id].ms == gSongTable[41].ms) {
    if ((SoundID2 == 0) || (SoundID2 == 41)) {
      SoundID2 = id;
    }
    return id;
  }
  if (id == 0) {
    return 0;
  }
  m4aSongNumStart(id);
  return id;
}
