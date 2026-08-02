#include "game.h"
#include "global.h"
#include "minigame.h"
#include "text.h"

extern const u8 Unicode_SCORE_0810e298[];
extern const u8 Unicode_HI_SCORE_0810e2a0[];
extern const u8 Unicode_REST_0810e2ac[];

// 0x080fb550
void MinigameLeviathan_DrawScoreHiscore(struct GameState* g) {
  struct MinigameState* s = (struct MinigameState*)(g->sceneState).raw;

  PrintUnicodeString(Unicode_SCORE_0810e298, 1, 0);
  PrintMinigameNumber(s->unk_24, 12, 0);
  PrintUnicodeString(Unicode_HI_SCORE_0810e2a0, 15, 0);
  PrintMinigameNumber(s->unk_2c, 28, 0);
}

// 0x080fb594
void leviathan_minigame_080fb594(struct GameState* g) {
  struct MinigameState* s = (struct MinigameState*)(g->sceneState).raw;

  PrintUnicodeString(Unicode_REST_0810e2ac, 10, 19);
  PrintMinigameNumber(s->unk_20 / 60 % 60, 18, 19);
  PrintMinigameNumber(s->unk_20 / 3600, 15, 19);
}

INCASM("asm/minigame/leviathan.inc");

extern const GameLoopFunc LeviathanMinigameLoops[3];

// 0x080FBB0C
bool32 leviathanMinigame(struct GameState* g) {
  u8* mg = (u8*)g + 0xDCC;
  bool32 r = ((MinigameFunc)LeviathanMinigameLoops[mg[0]])(g);
  leviathan_minigame_080fb594(g);
  if (*(s32*)(mg + 0x24) < 0) {
    *(s32*)(mg + 0x24) = 0;
  } else if (*(s32*)(mg + 0x24) > 0x1869F) {
    *(s32*)(mg + 0x24) = 0x1869F;
  }
  if (*(s32*)(mg + 0x24) > *(s32*)(mg + 0x2c)) {
    u8* f = mg + 0x30;
    if (*f == 0) {
      *f = 1;
      PlaySound(0x138);
    } else {
      PlaySound(0x137);
    }
    *(s32*)(mg + 0x2c) = *(s32*)(mg + 0x24);
  } else if (*(s32*)(mg + 0x28) != *(s32*)(mg + 0x24)) {
    PlaySound(0x137);
  }
  *(s32*)(mg + 0x28) = *(s32*)(mg + 0x24);
  MinigameLeviathan_DrawScoreHiscore(g);
  return r;
}

INCASM("asm/minigame/leviathan_b.inc");

void leviathan_minigame_080fbba0(struct GameState* g);
void leviathan_minigame_080fbc30(struct GameState* g);
void leviathan_minigame_080fbcdc(struct GameState* g);

const GameLoopFunc LeviathanMinigameLoops[3] = {
    leviathan_minigame_080fbba0,
    leviathan_minigame_080fbc30,
    leviathan_minigame_080fbcdc,
};

const u8 u8_ARRAY_08386bb0[16] = {
    2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 5, 5,
};

const u8 u8_ARRAY_08386bc0[16] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 3, 3, 3, 5,
};

bool32 exitLeviathanMinigame(struct GameState* g) {
  struct MinigameState* s = (struct MinigameState*)(g->sceneState).raw;
  gSystemSavedataManager.minigameHiscores[MINIGAME_LEVIATHAN] = s->unk_2c;
  SaveSystemData();
  return FALSE;
}
