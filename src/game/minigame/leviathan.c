#include "game.h"
#include "global.h"
#include "minigame.h"
#include "sound.h"
#include "vfx.h"
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

bool32 leviathan_minigame_080fb5dc(struct GameState* g);

// 0x080FBBA0
bool32 leviathan_minigame_080fbba0(struct GameState* g) {
  u8* mg = (u8*)g + 0xDCC;
  switch (mg[1]) {
    case 0:
      *((u8*)g + 0xDFF) = 0x3c;
      mg[1]++;
      /* fallthrough */
    case 1: {
      u8* t = mg + 0x33;
      s32 v = *t - 1;
      *t = v;
      if ((v << 24) != 0) {
        break;
      }
      mg[1]++;
      break;
    }
    case 2:
      PlaySound(0x1d);
      *(struct VFX**)(mg + 8) = CreateMissionAlert(0);
      mg[1]++;
      /* fallthrough */
    case 3:
      if (*(u8*)(*(u8**)(mg + 8) + 0xc) > 1) {
        u8 t0 = mg[0] + 1;
        u8 z = 0;
        mg[0] = t0;
        mg[1] = z;
        mg[2] = z;
        mg[3] = z;
      }
      break;
  }
  *(u16*)(mg + 0x10) = 0;
  *(u16*)(mg + 0x12) = 0;
  leviathan_minigame_080fb5dc(g);
  return 1;
}

INCASM("asm/minigame/leviathan_b.inc");

bool32 leviathan_minigame_080fbba0(struct GameState* g);
void leviathan_minigame_080fbc30(struct GameState* g);
void leviathan_minigame_080fbcdc(struct GameState* g);

const GameLoopFunc LeviathanMinigameLoops[3] = {
    (GameLoopFunc)leviathan_minigame_080fbba0,
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
