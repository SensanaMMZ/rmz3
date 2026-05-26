void TurnUpBGM(void) {
  u32 i = (u16)gNumMusicPlayers;  // NUM_MUSIC_PLAYERS macro pre-expanded for permuter setup
  const struct MusicPlayer* p = gMPlayTable;
  if (i != 0) {
    do {
      m4aMPlayVolumeControl(p->info, 0xFFFF, 0x100);
      p++;
      i--;
    } while (i != 0);
  }
}
