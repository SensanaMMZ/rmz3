#include "collision.h"
#include "entity.h"
#include "global.h"
#include "solid.h"
#include "metatile.h"
#include "motion.h"
#include "zero.h"

// SubArcadia's platform

static const struct Collision sCollisions[];
static const struct Rect sSize;
static const u8 sInitMode[];

static void Solid17_Init(Object* p);
static void Solid17_Update(struct Entity* p);
static void Solid17_Die(struct Entity* p);

// clang-format off
const SolidRoutine gSubArcadiaPlatformRoutine = {
    [ENTITY_INIT] =      (SolidFunc)Solid17_Init,
    [ENTITY_UPDATE] =    (SolidFunc)Solid17_Update,
    [ENTITY_DIE] =       (SolidFunc)Solid17_Die,
    [ENTITY_DISAPPEAR] = (SolidFunc)DeleteSolid,
    [ENTITY_EXIT] =      (SolidFunc)DeleteEntity,
};
// clang-format on

// ------------------------------------------------------------------------------------------------------------------------------------

// 0x080cf098
static void onCollision(struct Body* body, struct Coord* c1 UNUSED, struct Coord* c2 UNUSED) {
  Object* attacker = body->enemy->parent;
  Object* self = body->parent;
  if (body->hitboxFlags & 4) {
    if ((attacker->s).kind == 0) {
      if ((pZero2->s).coord.y <= (self->s).coord.y) {
        (self->s).work[2] = 1;
        if ((self->s).mode[1] == 0) {
          (self->s).mode[1] = 1;
          (self->s).mode[2] = 0;
        }
      }
    }
  }
  if (body->hitboxFlags & 0x20) {
    if (*(u16*)&(attacker->s).kind == 0x1106) {
      if ((self->s).mode[1] == 1) {
        (self->s).mode[1] = 2;
        (self->s).mode[2] = 0;
      }
    }
  }
}

// --------------------------------------------

static void Solid17_Init(Object* p) {
  struct Body* body;

  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  (p->s).mode[1] = sInitMode[(p->s).work[0]];
  (p->s).flags |= FLIPABLE;
  (p->s).flags |= DISPLAY;
  InitNonAffineMotion(&p->s);

  (p->s).flags |= COLLIDABLE;
  body = &p->body;
  InitBody(body, sCollisions, &(p->s).coord, 1);
  body->parent = (Object*)p;
  body->fn = NULL;  // ???
  (p->s).flags2 &= ~WHITE_PAINTABLE;
  (p->s).invincibleID = (p->s).uniqueID;
  body->fn = onCollision;  // ???
  (p->s).flags2 |= ENTITY_HAZARD;
  (p->s).size = &sSize;
  (p->s).hazardAttr = 0x2001;
  (p->s).coord.x -= PIXEL(8);
  (p->s).coord.y -= PIXEL(8);
  (p->s).unk_coord.x = (p->s).coord.x;
  (p->s).unk_coord.y = (p->s).coord.y;
  (p->s).work[3] = 0;
  Solid17_Update((void*)p);
}

static void nop_080cf208(void* _ UNUSED);
void FUN_080cf20c(struct Solid* p);
void FUN_080cf250(struct Solid* p);
void FUN_080cf378(struct Solid* p);

static void Solid17_Update(struct Entity* p) {
  static const SolidFunc sUpdates1[] = {
      (SolidFunc)nop_080cf208,
      (SolidFunc)nop_080cf208,
      (SolidFunc)nop_080cf208,
  };
  static const SolidFunc sUpdates2[] = {
      (SolidFunc)FUN_080cf20c,
      (SolidFunc)FUN_080cf250,
      (SolidFunc)FUN_080cf378,
  };
  (sUpdates1[(p->mode)[1]])((void*)p);
  (sUpdates2[(p->mode)[1]])((void*)p);
  p->work[3] = p->work[2];
  p->work[2] = 0;
}

static void Solid17_Die(struct Entity* p) {
  p->flags2 &= ~ENTITY_HAZARD;
  SET_SOLID_ROUTINE(p, ENTITY_EXIT);
}

// --------------------------------------------

static void nop_080cf208(void* _ UNUSED) {}

extern const motion_t sSolid17Motions[3][4];

void FUN_080cf20c(struct Solid* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SetDDP(&p->body, &sCollisions[1]);
      SetMotion(&p->s, sSolid17Motions[0][(p->s).work[0]]);
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      UpdateMotionGraphic(&p->s);
      break;
  }
}

extern const struct Rect Rect_ARRAY_08370628[6];

void FUN_080cf250(struct Solid* p) {
  switch ((p->s).mode[2]) {
    case 0: {
      const s16* t;
      {
        const motion_t* tb0 = sSolid17Motions[1];
        SetMotion(&p->s, tb0[(p->s).work[0]]);
      }
      t = (const s16*)Rect_ARRAY_08370628;
      (p->s).d.x = t[(p->s).work[0] * 2];
      {
        u32 offd = (u32)((p->s).work[0] << 2);
        asm("" : "+r"(offd));
        t = (const s16*)((const u8*)t + 2);
        offd += (u32)t;
        (p->s).d.y = *(const s16*)offd;
      }
      (p->s).mode[2]++;
    }
      /* fallthrough */
    case 1: {
      u32 msk;
      msk = 0xFFFF;
      asm("" : "+r"(msk));
      if (*(u16*)&(p->s).work[2] == 1) {
        const motion_t* tb0 = sSolid17Motions[1];
        u16 mo = tb0[(p->s).work[0]];
        u16 m2 = *(s8*)((u8*)p + 0x71);
        u16 m3 = *(s8*)((u8*)p + 0x72);
        GotoMotion(&p->s, mo, m2, m3);
      }
      msk &= *(u16*)&(p->s).work[2];
      if (msk == 0x100) {
        const motion_t* tb1 = sSolid17Motions[2];
        u16 mo;
        u16 m2;
        u16 m3;
        asm("" : "+r"(tb1));
        mo = tb1[(p->s).work[0]];
        m2 = *(s8*)((u8*)p + 0x71);
        m3 = *(s8*)((u8*)p + 0x72);
        GotoMotion(&p->s, mo, m2, m3);
      }
      (p->s).coord.x += (p->s).d.x;
      (p->s).coord.y += (p->s).d.y;
      UpdateMotionGraphic(&p->s);
      {
        const u8* t2 = (const u8*)&Rect_ARRAY_08370628[2];
        s32 y;
        {
          register u32 off asm("r2");
          register s32 x0 asm("r0");
          const u8* tb;
          off = (p->s).work[0] << 3;
          x0 = (p->s).coord.x + *(const s16*)(off + t2);
          tb = t2 + 2;
          off += (u32)tb;
          y = (p->s).coord.y + *(const s16*)off;
          if ((FUN_080098a4(x0, y) << 16) != 0) {
            goto setm;
          }
        }
        {
          register u32 off2 asm("r2");
          register s32 x0 asm("r0");
          const u8* t4;
          const u8* tb;
          off2 = (p->s).work[0] << 3;
          t4 = t2 + 4;
          x0 = (p->s).coord.x + *(const s16*)(off2 + t4);
          tb = t2 + 6;
          off2 += (u32)tb;
          y = (p->s).coord.y + *(const s16*)off2;
          if ((FUN_080098a4(x0, y) << 16) != 0) {
          setm:
            (p->s).mode[1] = 2;
            (p->s).mode[2] = 0;
          }
        }
      }
      break;
    }
  }
}

INCASM("asm/solid/unk_17_p2.inc");

// --------------------------------------------

// 0x083705BC
static const struct Collision sCollisions[3] = {
    [0] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 0,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(8), PIXEL(8)},
    },
    [1] = {
      kind : DDP,
      faction : FACTION_NEUTRAL,
      damage : 255,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(12), PIXEL(30), PIXEL(32)},
    },
    [2] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 0,
      hardness : HARDNESS_B3,
      remaining : 0,
      priorityLayer : 0xFFFFFFFF,
      range : {PIXEL(0), PIXEL(14), PIXEL(30), PIXEL(28)},
    },
};

// --------------------------------------------

// clang-format off
const motion_t sSolid17Motions[3][4] = {
    {
        MOTION(SM108_SUBARCADIA_PLATFORM, 6),
        MOTION(SM108_SUBARCADIA_PLATFORM, 4),
        MOTION(SM108_SUBARCADIA_PLATFORM, 2),
        MOTION(SM108_SUBARCADIA_PLATFORM, 8),
    },
    {
        MOTION(SM108_SUBARCADIA_PLATFORM, 7),
        MOTION(SM108_SUBARCADIA_PLATFORM, 5),
        MOTION(SM108_SUBARCADIA_PLATFORM, 3),
        MOTION(SM108_SUBARCADIA_PLATFORM, 9),
    },
    {
        MOTION(SM108_SUBARCADIA_PLATFORM, 12),
        MOTION(SM108_SUBARCADIA_PLATFORM, 11),
        MOTION(SM108_SUBARCADIA_PLATFORM, 10),
        MOTION(SM108_SUBARCADIA_PLATFORM, 13),
    },
};
// clang-format on

// --------------------------------------------

// 0x0837061c
static const struct Rect sSize = {PIXEL(0), PIXEL(14), PIXEL(30), PIXEL(28)};

// 0x08370624
static const u8 sInitMode[4] = {0, 0, 0, 0};

// clang-format off
const struct Rect Rect_ARRAY_08370628[6] = {
    { PIXEL(0), PIXEL(1), -PIXEL(1), PIXEL(0) },
    { PIXEL(0), -PIXEL(1), PIXEL(1), PIXEL(0) },
    { -PIXEL(15), PIXEL(28), PIXEL(15), PIXEL(28) },
    { -PIXEL(15), PIXEL(0), -PIXEL(15), PIXEL(28) },
    { -PIXEL(15), PIXEL(0), PIXEL(15), PIXEL(0) },
    { PIXEL(15), PIXEL(0), PIXEL(15), PIXEL(28) },
}; // 0x08370628
// clang-format on
