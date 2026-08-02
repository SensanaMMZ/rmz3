#include "game.h"
#include "global.h"
#include "minigame.h"
#include "sound.h"
#include "text.h"
#include "vfx.h"

extern const u8 Unicode_SCORE_0810e284[];
extern const u8 Unicode_HI_SCORE_0810e28c[];

void MinigameFefnir_DrawScoreHiscore(struct GameState* g) {
  struct MinigameState* s = (struct MinigameState*)(g->sceneState).raw;

  PrintUnicodeString(Unicode_SCORE_0810e284, 1, 0);
  PrintMinigameNumber(s->unk_20, 12, 0);
  PrintUnicodeString(Unicode_HI_SCORE_0810e28c, 15, 0);
  PrintMinigameNumber(s->unk_28, 28, 0);
}

INCASM("asm/minigame/fefnir.inc");

// 0x080FB48C
bool32 fefnir_minigame_080fb48c(struct GameState* g) {
  u8* mg = (u8*)g + 0xDCC;
  s32 t;
  *(u16*)(mg + 0x18) = 0;
  *(u16*)(mg + 0x1a) = 0;
  switch (mg[1]) {
    case 0:
      fadeoutBGM(0xbd);
      *(s32*)(mg + 0x1c) = 0x3c;
      mg[1]++;
      /* fallthrough */
    case 1:
      t = *(s32*)(mg + 0x1c) - 1;
      *(s32*)(mg + 0x1c) = t;
      if (t != 0) {
        break;
      }
      goto adv;
    case 2:
      *(struct VFX**)(mg + 0x14) = CreateMissionAlert(4);
      mg[1]++;
      /* fallthrough */
    case 3:
      if (*(u8*)(*(u8**)(mg + 0x14) + 0xc) <= 1) {
        break;
      }
    adv:
      mg[1]++;
      break;
    case 4:
      gGameState.frames = 0x40;
      mg[1]++;
      /* fallthrough */
    case 5:
      *(s32*)(mg + 0x1c) = *(s32*)(mg + 0x1c) - 1;
      if (gGameState.frames == 0x20) {
        return 0;
      }
      break;
  }
  return 1;
}


void fefnir_minigame_080fb2d8(struct GameState* g);
void fefnir_minigame_080fb354(struct GameState* g);

const GameLoopFunc FefnirMinigameLoops[3] = {
    fefnir_minigame_080fb2d8,
    fefnir_minigame_080fb354,
    (GameLoopFunc)fefnir_minigame_080fb48c,
};

bool32 exitFefnirMinigame(struct GameState* g) {
  struct MinigameState* s = (struct MinigameState*)(g->sceneState).raw;
  gSystemSavedataManager.minigameHiscores[MINIGAME_FEFNIR] = s->unk_28;
  SaveSystemData();
  return FALSE;
}
