#include "collision.h"
#include "entity.h"
#include "game.h"
#include "global.h"
#include "solid.h"
#include "story.h"
#include "text.h"
#include "text_window.h"
#include "zero.h"
#include "physics.h"

static void MainNPC_Init(struct Solid* p);
static void MainNPC_Update(struct Solid* p);
static void MainNPC_Die(struct Solid* p);

// clang-format off
/*
  xx nn nn nn
  work[0]:
    0: ??
    1: Ciel
    2: Cerveau
    3: Hazard Colbor (until Player go to cerveru room for the first time)
    4: Search console at Sunken Library
    5: ?? (『メンテナンス・ルーム』という文字列を表示している ゼロ2の名残？)
*/
const SolidRoutine gMainNPCRoutine = {
    [ENTITY_INIT] =      MainNPC_Init,
    [ENTITY_UPDATE] =    MainNPC_Update,
    [ENTITY_DIE] =       MainNPC_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteSolid,
    [ENTITY_EXIT] =      (SolidFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

static void initMainNPC(struct Solid* p);

static void MainNPC_Init(struct Solid* p) {
  // clang-format off
  static SolidFunc const sInitializers[] = {
    initMainNPC,
    initMainNPC,
    initMainNPC,
    initMainNPC,
    initMainNPC,
    initMainNPC,
  };
  // clang-format on
  (sInitializers[(p->s).work[0]])(p);
}

// --------------------------------------------

static void FUN_080daee8(struct Solid* p);
static void UpdateCiel(struct Solid* p);
void UpdateCerveau(struct Solid* p);
void UpdateBlockingColbor(struct Solid* p);
static void UpdateSearchConsole(Object* p);
static void FUN_080db930(Object* p);

static void MainNPC_Update(struct Solid* p) {
  // clang-format off
  static SolidFunc const sUpdates[] = {
    (SolidFunc)FUN_080daee8,
    (SolidFunc)UpdateCiel,
    (SolidFunc)UpdateCerveau,
    (SolidFunc)UpdateBlockingColbor,
    (SolidFunc)UpdateSearchConsole,
    (SolidFunc)FUN_080db930,
  };
  // clang-format on
  (sUpdates[(p->s).work[0]])(p);
}

// --------------------------------------------

static void deleteMainNPC(struct Solid* p);

void MainNPC_Die(struct Solid* p) {
  // clang-format off
    static SolidFunc const sDeinitializers[] = {
    deleteMainNPC,
    deleteMainNPC,
    deleteMainNPC,
    deleteMainNPC,
    deleteMainNPC,
    deleteMainNPC,
  };
  // clang-format on
  (sDeinitializers[(p->s).work[0]])(p);
}

// --------------------------------------------

static void initMainNPC(struct Solid* p) {
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  MainNPC_Update(p);
}

static void FUN_080daee8(struct Solid* p) {
  SET_SOLID_ROUTINE(p, ENTITY_DIE);
  MainNPC_Die(p);
}

static void deleteMainNPC(struct Solid* p) {
  (p->s).flags &= ~DISPLAY;
  EXIT_BODY(p);
  (p->s).flags2 &= ~ENTITY_HAZARD;
  SET_SOLID_ROUTINE(p, ENTITY_EXIT);
}

NAKED static void UpdateCiel(struct Solid* p) { INCCODE("asm/wip/UpdateCiel.inc"); }

INCASM("asm/solid/main_npc.inc");

extern const struct Collision Collision_ARRAY_083713e0[2];

void UpdateBlockingColbor(struct Solid* p) {
  switch ((p->s).mode[1]) {
    case 0: {
      u32 g6 = (u8)(gCurStory.s.gameflags[1] & 2);
      if (g6 != 0) {
        {
          u32 fl = (p->s).flags & 0xFE;
          fl &= 0xFD;
          (p->s).flags = fl;
        }
        {
          u8* w = (u8*)p + 0x8c;
          s32 z = 0;
          *(u32*)w = z;
          asm("" : "+r"(w));
          w += 4;
          *(u32*)w = z;
          asm("" : "+r"(w));
          w += 4;
          asm("" : "+r"(w));
          *w = z;
        }
        (p->s).flags &= 0xFB;
        {
          u32 tbl = (u32)gSolidFnTable;
          u32 id = ((p->s).id) << 2;
          EntityFunc** rt = (EntityFunc**)(tbl + id);
          *(u32*)((p->s).mode) = 3;
          (p->s).onUpdate = (void*)((*rt)[3]);
        }
        break;
      }
      {
        u32 fl = (p->s).flags;
        register u32 t asm("r0");
        u32 two;
        t = 1;
        asm volatile("" : "+r"(t));
        t |= fl;
        two = 2;
        asm("" : "+r"(two));
        t |= two;
        (p->s).flags = t;
      }
      InitNonAffineMotion(&p->s);
      (p->s).flags &= 0xEF;
      ((p->s).spr).xflip = g6;
      {
        u8* oa = (u8*)p + 0x4a;
        s32 ov = *oa;
        s32 m11 = -0x11;
        m11 &= ov;
        *oa = m11;
      }
      SetMotion(&p->s, 0x8200);
      (p->s).flags |= 4;
      {
        struct Body* body = &p->body;
        InitBody(body, Collision_ARRAY_083713e0, &(p->s).coord, 0x40);
        body->parent = (struct CollidableEntity*)p;
        body->fn = (void*)g6;
      }
      (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y);
      (p->s).mode[1]++;
    }
      // fallthrough
    case 1: {
      UpdateMotionGraphic(&p->s);
      if (!((p->body).status & 0x20000000)) {
        break;
      }
      if (gInChat == 0) {
        break;
      }
      {
        u8* cm = (u8*)&gCollisionManager;
        asm("" : "+r"(cm));
        if (*(void**)(cm + 0x628) != (void*)&p->body) {
          break;
        }
      }
      {
        u32 xf = 0;
        if ((pZero2->s).coord.x - (p->s).coord.x > 0) {
          xf = 1;
        }
        if (xf != 0) {
          (p->s).flags |= 0x10;
        } else {
          (p->s).flags &= 0xEF;
        }
        {
          register u32 xfc asm("r1");
          xfc = xf;
          asm volatile("" : "+r"(xfc));
          ((p->s).spr).xflip = xfc;
          {
            u8* oa = (u8*)p + 0x4a;
            u32 sh4 = xfc << 4;
            s32 ov, m11;
            ov = *oa;
            m11 = -0x11;
            m11 &= ov;
            m11 |= sh4;
            *oa = m11;
          }
        }
      }
      PrintNormalMessage(0x1306);
      (p->s).mode[1]++;
      break;
    }
    case 2: {
      u32 tw;
      UpdateMotionGraphic(&p->s);
      {
        struct TextWindowText* tx = &gTextWindow.text;
        tw = tx->mode;
      }
      if (tw != 0) {
        break;
      }
      gInChat = tw;
      (p->s).mode[1] = 1;
      break;
    }
  }
}

const struct Collision Collision_ARRAY_08371380[2] = {
    {
      kind : DDP,
      faction : FACTION_NEUTRAL,
      special : CHATABLE,
      damage : 255,
      hitzone : 0x00,
      remaining : 0,
      layer : 0x00000001,
      range : {-PIXEL(32), PIXEL(0), PIXEL(16), PIXEL(1)},
    },
    {
      kind : DRP,
      faction : FACTION_NEUTRAL,
      special : CHATABLE,
      damage : 255,
      LAYER(0xFFFFFFFF),
      hitzone : 0x00,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(0), PIXEL(0)},
    },
};

const struct Collision Collision_ARRAY_083713b0[2] = {
    {
      kind : DDP,
      faction : FACTION_NEUTRAL,
      special : CHATABLE,
      damage : 255,
      hitzone : 0x00,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(32), PIXEL(0), PIXEL(16), PIXEL(1)},
    },
    {
      kind : DRP,
      faction : FACTION_NEUTRAL,
      special : CHATABLE,
      damage : 255,
      LAYER(0xFFFFFFFF),
      hitzone : 0x00,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(0), PIXEL(0)},
    },
};

const struct Collision Collision_ARRAY_083713e0[2] = {
    {
      kind : DDP,
      faction : FACTION_NEUTRAL,
      special : CHATABLE,
      damage : 255,
      hitzone : 0x00,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(80), PIXEL(1)},
    },
    {
      kind : DRP,
      faction : FACTION_NEUTRAL,
      special : CHATABLE,
      damage : 255,
      LAYER(0xFFFFFFFF),
      hitzone : 0x00,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(0), PIXEL(0)},
    },
};

// --------------------------------------------

static const struct Collision Collision_ARRAY_08371410[2] = {
    {
      kind : DDP,
      faction : FACTION_NEUTRAL,
      special : CHATABLE,
      damage : 255,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(24), PIXEL(1)},
    },
    {
      kind : DRP,
      faction : FACTION_NEUTRAL,
      special : CHATABLE,
      damage : 255,
      LAYER(0xFFFFFFFF),
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(0), PIXEL(0)},
    },
};

static void UpdateSearchConsole(Object* p) {
  switch ((p->s).mode[1]) {
    case 0: {
      (p->s).flags |= FLIPABLE;
      INIT_BODY(p, Collision_ARRAY_08371410, 64, NULL);
      (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y);
      (p->s).mode[1]++;
      FALLTHROUGH;
    }
    case 1: {
      if (((p->body).status & BODY_STATUS_CHAT) && gInChat && (gCollisionManager.talkTo == &p->body)) {
        PlaySound(SE_ARCADIA_RINGTONE);
        SetGameMode(&gGameState, GAMEMODE(MAINGAME, OVERWORLD, 7, 0));
        (p->s).mode[1]++;
      }
      break;
    }
    case 2: {
      if (gGameState.mode[2] != 0) {
        return;
      }
      gInChat = FALSE;
      (p->s).mode[1] = 1;
      break;
    }
    default: {
      break;
    }
  }
}

static void FUN_080db930(Object* p) {
  switch ((p->s).mode[1]) {
    case 0: {
      if (FLAG(gCurStory.s.gameflags, SUNKEN_ANALYZE) || !FLAG(gCurStory.s.gameflags, FLAG_12)) {
        (p->s).flags &= ~DISPLAY;
        (p->s).flags &= ~FLIPABLE;
        EXIT_BODY(p);
        SET_SOLID_ROUTINE(p, ENTITY_DISAPPEAR);
        break;
      }
      (p->s).flags |= FLIPABLE;
      INIT_BODY(p, Collision_ARRAY_08371410, 64, NULL);
      (p->s).coord.x += PIXEL(8);
      (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y);
      (p->s).mode[1]++;
      FALLTHROUGH;
    }
    case 1: {
      if (((p->body).status & BODY_STATUS_CHAT) && gInChat && (gCollisionManager.talkTo == &p->body)) {
        PrintNormalMessage(0x1333);
        (p->s).mode[1]++;
      }
      break;
    }
    case 2: {
      if ((&gTextWindow.text)->mode != 0) {
        return;
      }
      gInChat = FALSE;
      (p->s).mode[1] = 1;
      break;
    }
    default: {
      break;
    }
  }
}
