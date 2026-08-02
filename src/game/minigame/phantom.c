#include "game.h"
#include "global.h"
#include "minigame.h"
#include "text.h"

extern const u8 Unicode_SCORE_0810e2b8[];
extern const u8 Unicode_HI_SCORE_0810e2c0[];

void MinigamePhantom_DrawScoreHiscore(struct GameState* g) {
  struct MinigameState* s = (struct MinigameState*)(g->sceneState).raw;

  PrintUnicodeString(Unicode_SCORE_0810e2b8, 1, 0);
  PrintMinigameNumber(s->unk_34, 12, 0);
  PrintUnicodeString(Unicode_HI_SCORE_0810e2c0, 15, 0);
  PrintMinigameNumber(s->unk_3c, 28, 0);
}

INCASM("asm/minigame/phantom.inc");

#include "vfx.h"
#include "sound.h"

// 0x080FC390
bool32 phantomMinigame_080fc390(struct GameState* g);
bool32 phantomMinigame_080fc390(struct GameState* g) {
  struct MinigameState* s = (struct MinigameState*)(g->sceneState).raw;
  u16 z = 0;
  *(u16*)&s->unk_10[0] = z;
  *(u16*)&s->unk_10[2] = z;
  switch (s->unk_00[1]) {
    case 0:
      fadeoutBGM(0xA8);
      *(s32*)&s->unk_40[0] = 0x3C;
      s->unk_00[1]++;
    case 1:
      *(s32*)&s->unk_40[0] -= 1;
      if (*(s32*)&s->unk_40[0] != 0) {
        goto end1;
      }
      goto inc;
    case 2:
      *(struct VFX**)&s->unk_0c = CreateMissionAlert(4);
      s->unk_00[1]++;
    case 3:
      if (((*(struct VFX**)&s->unk_0c)->s).mode[0] <= 1) {
        return 1;
      }
    inc:
      s->unk_00[1]++;
      break;
    case 4:
      gGameState.frames = 0x40;
      s->unk_00[1]++;
    case 5:
      if (gGameState.frames != 0x20) {
        break;
      }
      return 0;
  }
end1:
  return 1;
}

void phantomMinigame_080fc13c(struct GameState* p);
void phantomMinigame_080fc1b8(struct GameState* p);

const GameLoopFunc PhantomMinigameLoops[3] = {
    phantomMinigame_080fc13c,
    phantomMinigame_080fc1b8,
    (GameLoopFunc)phantomMinigame_080fc390,
};

bool32 exitPhantomMinigame(struct GameState* g) {
  struct MinigameState* s = (struct MinigameState*)(g->sceneState).raw;
  gSystemSavedataManager.minigameHiscores[MINIGAME_PHANTOM] = s->unk_3c;
  SaveSystemData();
  return FALSE;
}
