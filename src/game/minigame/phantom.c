#include "game.h"
#include "global.h"
#include "minigame.h"
#include "sound.h"
#include "text.h"
#include "vfx.h"

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

extern const GameLoopFunc PhantomMinigameLoops[3];

// 0x080FC084
bool32 phantomMinigame(struct GameState* g) {
  u8* mg = (u8*)g + 0xDCC;
  register bool32 r asm("r8");
  r = ((MinigameFunc)PhantomMinigameLoops[mg[0]])(g);
  if (*(s32*)(mg + 0x34) > 0x1869F) {
    *(s32*)(mg + 0x34) = 0x1869F;
  }
  if (*(s32*)(mg + 0x34) > *(s32*)(mg + 0x3c)) {
    u8* f = (u8*)g + 0xEA3;
    if (*f == 0) {
      *f = 1;
      PlaySound(0x138);
    } else {
      PlaySound(0x137);
    }
    *(s32*)(mg + 0x3c) = *(s32*)(mg + 0x34);
  } else if (*(s32*)(mg + 0x38) != *(s32*)(mg + 0x34)) {
    PlaySound(0x137);
  }
  *(s32*)(mg + 0x38) = *(s32*)(mg + 0x34);
  MinigamePhantom_DrawScoreHiscore(g);
  {
    register s32 i asm("r5");
    u8* n;
    u8* n0;
    i = 0;
    n0 = mg + 0xd5;
    asm volatile("add %0, %1, #0" : "=&l"(n) : "l"(n0));
    if (i < *n) {
      register struct Sprite* sp asm("r4");
      sp = (struct Sprite*)(mg + 0x44);
      do {
        void (*f)(struct Sprite*, struct DrawPivot*) = sp->fn;
        register struct Sprite* a0 asm("r0");
        a0 = sp;
        asm("" : "+r"(mg));
        f(a0, (struct DrawPivot*)(mg + 0xbc));
        sp = (struct Sprite*)((u8*)sp + 0x20);
        i++;
      } while (i < *n);
    }
    asm volatile("" ::"r"(mg));
  }
  return r;
}

// 0x080FC13C
bool32 phantomMinigame_080fc13c(struct GameState* g) {
  u8* mg = (u8*)g + 0xDCC;
  s32 t;
  switch (mg[1]) {
    case 0:
      *(s32*)(mg + 0x40) = 0x3c;
      mg[1]++;
      /* fallthrough */
    case 1:
      t = *(s32*)(mg + 0x40) - 1;
      *(s32*)(mg + 0x40) = t;
      if (t != 0) {
        break;
      }
      mg[1]++;
      break;
    case 2:
      PlaySound(0x1d);
      *(struct VFX**)(mg + 0xc) = CreateMissionAlert(0);
      mg[1]++;
      /* fallthrough */
    case 3:
      if (*(u8*)(*(u8**)(mg + 0xc) + 0xc) > 1) {
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
  return 1;
}

INCASM("asm/minigame/phantom_b.inc");

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

bool32 phantomMinigame_080fc13c(struct GameState* p);
void phantomMinigame_080fc1b8(struct GameState* p);

const GameLoopFunc PhantomMinigameLoops[3] = {
    (GameLoopFunc)phantomMinigame_080fc13c,
    phantomMinigame_080fc1b8,
    (GameLoopFunc)phantomMinigame_080fc390,
};

bool32 exitPhantomMinigame(struct GameState* g) {
  struct MinigameState* s = (struct MinigameState*)(g->sceneState).raw;
  gSystemSavedataManager.minigameHiscores[MINIGAME_PHANTOM] = s->unk_3c;
  SaveSystemData();
  return FALSE;
}
