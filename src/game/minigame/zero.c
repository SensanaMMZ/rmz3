#include "game.h"
#include "global.h"
#include "minigame.h"
#include "sound.h"
#include "text.h"
#include "vfx.h"

INCASM("asm/minigame/zero_a.inc");

extern const GameLoopFunc ZeroMinigameLoops[3];

bool32 zeroMinigame(struct GameState* g) {
  struct MinigameState* s = &(g->sceneState).mg;
  return ((MinigameFunc)ZeroMinigameLoops[s->unk_04])(g);
}

extern const u8 Unicode_SCORE_0810e248[];
extern const u8 Unicode_HI_SCORE_0810e250[];

// 0x080F93E4
bool32 zeroMinigamePhase0(struct GameState* g) {
  struct MinigameState* s = &(g->sceneState).mg;
  u8 b1[8];
  u8 b2[12];
  switch (s->unk_06) {
    case 0:
      *(u16*)s->unk_00 = 0x3c;
      s->unk_06++;
      /* fallthrough */
    case 1: {
      s32 raw = *(u16*)s->unk_00 - 1;
      *(u16*)s->unk_00 = raw;
      if ((u16)raw != 0) {
        break;
      }
      s->unk_06++;
      break;
    }
    case 2:
      *(struct VFX**)s->unk_10 = CreateMissionAlert(0);
      PlaySound(0x1d);
      s->unk_06++;
      /* fallthrough */
    case 3:
      if (((*(struct VFX**)s->unk_10)->s).mode[0] > 1) {
        s->unk_04++;
        s->unk_06 = 0;
      }
      break;
  }
  memcpy(b1, Unicode_SCORE_0810e248, 6);
  PrintUnicodeString(b1, 1, 0);
  {
    u32 score = *(u16*)s->unk_38;
    PrintMinigameNumber(score, 0xa, 0);
    if (score > (u32)s->unk_3c) {
      s->unk_3c = score;
    }
  }
  memcpy(b2, Unicode_HI_SCORE_0810e250, 9);
  PrintUnicodeString(b2, 0xf, 0);
  {
    register u32 hs0 asm("r4");
    u32 hs;
    hs0 = s->unk_3c;
    asm volatile("add %0, %1, #0" : "=&l"(hs) : "l"(hs0));
    PrintMinigameNumber(hs, 0x1b, 0);
  }
  return 1;
}

INCASM("asm/minigame/zero_b.inc");

// 0x080F9750
bool32 zeroMinigamePhase2(struct GameState* g) {
  struct MinigameState* s = &(g->sceneState).mg;
  u8 b1[8];
  u8 b2[12];
  switch (s->unk_06) {
    case 0:
      *(u16*)s->unk_00 = 0x3c;
      s->unk_06++;
      /* fallthrough */
    case 1: {
      s32 raw = *(u16*)s->unk_00 - 1;
      *(u16*)s->unk_00 = raw;
      if ((u16)raw != 0) {
        break;
      }
      goto inc;
    }
    case 2:
      *(struct VFX**)s->unk_10 = CreateMissionAlert(4);
      fadeoutBGM(0xad);
      s->unk_06++;
      /* fallthrough */
    case 3:
      if (((*(struct VFX**)s->unk_10)->s).mode[0] <= 1) {
        break;
      }
    inc:
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
  memcpy(b1, Unicode_SCORE_0810e248, 6);
  PrintUnicodeString(b1, 1, 0);
  {
    u32 score = *(u16*)s->unk_38;
    PrintMinigameNumber(score, 0xa, 0);
    if (score > (u32)s->unk_3c) {
      s->unk_3c = score;
    }
  }
  memcpy(b2, Unicode_HI_SCORE_0810e250, 9);
  PrintUnicodeString(b2, 0xf, 0);
  {
    register u32 hs0 asm("r4");
    u32 hs;
    hs0 = s->unk_3c;
    asm volatile("add %0, %1, #0" : "=&l"(hs) : "l"(hs0));
    PrintMinigameNumber(hs, 0x1b, 0);
  }
  return 1;
}

bool32 zeroMinigamePhase0(struct GameState* g);
void zeroMinigamePhase1(struct GameState* g);
bool32 zeroMinigamePhase2(struct GameState* g);

const GameLoopFunc ZeroMinigameLoops[3] = {
    (GameLoopFunc)zeroMinigamePhase0,
    zeroMinigamePhase1,
    (GameLoopFunc)zeroMinigamePhase2,
};

// clang-format off
const struct Coord Coord_ARRAY_08386af8[6] = {
    {-0x2000, 0x1000}, {+0x2000, 0x1000},
    {-0x2000, 0x4800}, {+0x2000, 0x4800},
    {-0x2000, 0x8000}, {+0x2000, 0x8000},
};
// clang-format on

// clang-format off
const struct Coord Coord_ARRAY_08386b28[6] = {
    {+0x2800, 0x1000}, {-0x2800, 0x1000},
    {+0x1800, 0x4800}, {-0x1800, 0x4800},
    {+0x2800, 0x8000}, {-0x2800, 0x8000},
};
// clang-format on

// 0x080f9848
bool32 exitZeroMinigame(struct GameState* g) {
  struct MinigameState* s = &(g->sceneState).mg;
  if (s->unk_06 == 0) {
    *((s16*)s->unk_00) = 2;
    s->unk_06++;
    return TRUE;
  }
  if (s->unk_06 == 1) {
    if ((*((s16*)s->unk_00) <= 0 || (--(*((s16*)s->unk_00)) <= 0))) {
      if (s->unk_3c > gSystemSavedataManager.minigameHiscores[MINIGAME_ZERO]) {
        gSystemSavedataManager.minigameHiscores[MINIGAME_ZERO] = s->unk_3c;
        SaveSystemData();
      }
      return FALSE;
    }
  }
  return TRUE;
}
