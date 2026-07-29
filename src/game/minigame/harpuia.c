#include "game.h"
#include "global.h"
#include "minigame.h"
#include "sound.h"
#include "text.h"
#include "vfx.h"

INCASM("asm/minigame/harpuia_a.inc");

extern const MinigameFunc HarpuiaMinigameLoops[3];

bool32 harpuiaMinigame(struct GameState* g) {
  struct MinigameState* s = &(g->sceneState).mg;
  return (HarpuiaMinigameLoops[s->unk_04])(g);
}

INCASM("asm/minigame/harpuia_b.inc");

extern const u8 Unicode_SCORE_0810e270[];
extern const u8 Unicode_HI_SCORE_0810e278[];

bool32 harpuia_minigame_080faebc(struct GameState* g) {
  struct MinigameState* s = &(g->sceneState).mg;
  switch (s->unk_06) {
    case 0:
      *(u16*)s->unk_00 = 0x3C;
      s->unk_06++;
      /* fallthrough */
    case 1: {
      s32 t = *(u16*)s->unk_00 - 1;
      *(u16*)s->unk_00 = t;
      if ((t << 16) != 0) {
        break;
      }
      goto adv;
    }
    case 2:
      *(struct VFX**)s->unk_10 = CreateMissionAlert(4);
      fadeoutBGM(0xB7);
      s->unk_06++;
      /* fallthrough */
    case 3:
      if ((*(struct Entity**)s->unk_10)->mode[0] <= 1) {
        break;
      }
    adv:
      s->unk_06++;
      break;
    case 4:
      gGameState.frames = 0x40;
      s->unk_06++;
      /* fallthrough */
    case 5:
      if (gGameState.frames != 0x20) {
        break;
      }
      {
        s32 z = 0;
        *(u16*)s->unk_00 = z;
        s->unk_06 = z;
        return z;
      }
  }
  {
    u8 b1[8];
    u8 b2[12];
    u32 score;
    memcpy(b1, Unicode_SCORE_0810e270, 6);
    PrintUnicodeString(b1, 1, 0);
    score = *(u16*)&s->unk_0e * 3 + *(u16*)s->unk_38 * 5;
    PrintMinigameNumber(score, 0xA, 0);
    if (score > (u32)s->unk_3c) {
      s->unk_3c = score;
    }
    memcpy(b2, Unicode_HI_SCORE_0810e278, 9);
    PrintUnicodeString(b2, 0xF, 0);
    {
      register s32 hs asm("r4");
      hs = s->unk_3c;
      PrintMinigameNumber(hs, 0x1B, 0);
    }
    return 1;
  }
}

bool32 harpuia_minigame_080fab10(struct GameState* g);
bool32 harpuia_minigame_080fabe8(struct GameState* g);
bool32 harpuia_minigame_080faebc(struct GameState* g);

const MinigameFunc HarpuiaMinigameLoops[3] = {
    harpuia_minigame_080fab10,
    harpuia_minigame_080fabe8,
    harpuia_minigame_080faebc,
};

// 0x080FAFC0
bool32 exitHarpuiaMinigame(struct GameState* g) {
  struct MinigameState* s = &(g->sceneState).mg;
  if (s->unk_06 == 0) {
    *((s16*)s->unk_00) = 2;
    s->unk_06++;
    return TRUE;
  }
  if (s->unk_06 == 1) {
    if ((*((s16*)s->unk_00) <= 0 || (--(*((s16*)s->unk_00)) <= 0))) {
      if (s->unk_3c > gSystemSavedataManager.minigameHiscores[MINIGAME_HARPUIA]) {
        gSystemSavedataManager.minigameHiscores[MINIGAME_HARPUIA] = s->unk_3c;
        SaveSystemData();
      }
      return FALSE;
    }
  }
  return TRUE;
}
