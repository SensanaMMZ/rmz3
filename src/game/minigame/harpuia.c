#include "anim_loader.h"
#include "game.h"
#include "global.h"
#include "minigame.h"
#include "overworld_terrain.h"
#include "sound.h"
#include "text.h"
#include "zero.h"
#include "vfx.h"

struct Zero* CreatePlayerHarpuia(void* p, struct Coord* c, u8 n);
struct VFX* FUN_080c82b8(struct Entity* e, struct Coord* c, u8 a2, u32 a3, u8 a4);

void initHarpuiaMinigame(struct GameState* g) {
  u8* mg = (u8*)g + 0xDCC;
  struct Coord* rc = (struct Coord*)((u8*)g + 0xDC4);
  struct Coord c;
  struct Zero* e;
  s32 i;
  rc->x = 0x16800;
  rc->y = 0xF000;
  ResetLandscape(0xA, rc);
  wStaticGraphicTilenums[0x47] = 0;
  wStaticMotionPalIDs[0x47] = 7;
  LOAD_STATIC_GRAPHIC(0x47);
  {
    u32 n = 0xF3;
    wStaticGraphicTilenums[n] = 0xC8;
    wStaticMotionPalIDs[n] = 8;
    LOAD_STATIC_GRAPHIC(n);
  }
  {
    u32 n = 0xA1;
    wStaticGraphicTilenums[n] = 0x1E0;
    wStaticMotionPalIDs[n] = 9;
    LOAD_STATIC_GRAPHIC(n);
  }
  LOAD_STATIC_GRAPHIC(0xAA);
  wStaticGraphicTilenums[0] = 0xF0;
  wStaticMotionPalIDs[0] = 0xE;
  LOAD_STATIC_GRAPHIC(0);
  c.x = 0x12C00;
  c.y = 0xF000;
  e = CreatePlayerHarpuia(mg, &c, 0);
  *(struct Zero**)(mg + 0x14) = e;
  *(struct Zero* volatile*)&pZero2 = e;
  i = 0;
  do {
    s32 n = i + 1;
    struct VFX* v;
    c.x = 0x1D800 - n * 0x1000;
    c.y = 0x12800;
    v = FUN_080c82b8((struct Entity*)mg, &c, 3, (u32)(mg + 0xc), (u8)i);
    *(struct GameState**)((u8*)v + 0x2c) = g;
    i = n;
  } while (i <= 2);
  {
    s32 z = 0;
    u8 z2;
    mg[0xc] = 3;
    z2 = 0;
    *(u16*)(mg + 0) = z;
    *(u16*)((u8*)g + 6) = 0x78;
    *(u16*)((u8*)g + 8) = z;
    *(u16*)((u8*)g + 0xa) = z;
    *(u16*)(mg + 4) = z;
    *(u16*)(mg + 6) = z;
    *(s32*)(mg + 0x18) = z;
    *(s32*)(mg + 0x1c) = z;
    *(s32*)(mg + 0x30) = z;
    *(s32*)(mg + 0x2c) = z;
    *(u16*)(mg + 0xe) = z;
    *(u16*)(mg + 0x38) = z;
    *(s32*)(mg + 0x34) = 0x200;
    mg[0xd] = z2;
    *(s32*)(mg + 0x20) = z;
    *(s32*)(mg + 0x24) = z;
    *(u16*)(mg + 0x28) = z;
    *(u16*)(mg + 0x2a) = z;
    *(s32*)(mg + 0x3c) = gSystemSavedataManager.minigameHiscores[3];
    *(u16*)(mg + 0x3a) = z;
    playBGM(0xB7);
    *(u16*)((u8*)g + 4) = z;
  }
}

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
