// Original asm loads NUM_MUSIC_PLAYERS via ldr+mask (the macro is
// ((u16)gNumMusicPlayers) where gNumMusicPlayers is a linker symbol = 15).
void TurnDownBGM(void) {
  u32 i = (u16)gNumMusicPlayers;  // NUM_MUSIC_PLAYERS macro pre-expanded for permuter setup
  const struct MusicPlayer* p = gMPlayTable;
  if (i != 0) {
    do {
      m4aMPlayVolumeControl(p->info, 0xFFFF, 0x60);
      p++;
      i--;
    } while (i != 0);
  }
}
