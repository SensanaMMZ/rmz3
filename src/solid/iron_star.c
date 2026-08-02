#include "collision.h"
#include "entity.h"
#include "global.h"
#include "overworld.h"
#include "solid.h"

/*
  ファントムのミニゲームに出てくるトゲ付き鉄球
*/

void initIronStar(struct Solid* p);
void ironStarAI(struct Solid* p);
void killIronStar(struct Solid* p);

// clang-format off
const SolidRoutine gIronStarRoutine = {
    [ENTITY_INIT] =      initIronStar,
    [ENTITY_UPDATE] =    ironStarAI,
    [ENTITY_DIE] =       killIronStar,
    [ENTITY_DISAPPEAR] = (void*)DeleteSolid,
    [ENTITY_EXIT] =      (SolidFunc)DeleteEntity,
};
// clang-format on

void CreateIronStar(struct Entity* e, s32 x, s32 y) {
  struct Solid* p = (struct Solid*)AllocEntityFirst(gSolidHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 30;
    INIT_SOLID_ROUTINE(p, SOLID_UNK_004);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).work[0] = 2;
    (p->s).coord.x = x;
    (p->s).coord.y = y;
    (p->s).unk_28 = e;
  }
}

static void onCollision(struct Body* body UNUSED, struct Coord* r1 UNUSED, struct Coord* r2 UNUSED) {
  // NOP
  return;
}

INCASM("asm/solid/iron_star_p1_a.inc");

extern const SolidFunc PTR_ARRAY_0836fe00[2];
extern const SolidFunc PTR_ARRAY_0836fe08[2];

// 0x080CBC14
void ironStarAI(struct Solid* p) {
  if ((p->s).work[0] == 2) {
    struct Entity* q = (p->s).unk_28;
    if ((*(struct Entity**)((u8*)q + 8))->coord.x - (p->s).coord.x > 0xC000) {
      register u8* w asm("r0");
      u8 fl;
      u32 z;
      fl = (p->s).flags & 0xFE;
      z = 0;
      fl &= 0xFD;
      (p->s).flags = fl;
      w = (u8*)p + 0x8c;
      *(u32*)w = z;
      asm volatile("add %0, #4" : "+r"(w));
      *(u32*)w = z;
      asm volatile("add %0, #4" : "+r"(w));
      *w = z;
      (p->s).flags &= 0xFB;
      SET_SOLID_ROUTINE(p, 3);
      return;
    }
    (p->s).coord.x += *(s32*)((u8*)q + 0x14);
  }
  (PTR_ARRAY_0836fe00[(p->s).mode[1]])(p);
  (PTR_ARRAY_0836fe08[(p->s).mode[1]])(p);
}

void killIronStar(struct Solid* p) {
  (p->s).flags2 &= ~ENTITY_HAZARD;
  SET_SOLID_ROUTINE(p, ENTITY_EXIT);
}

void nop_080cbcc0(struct Solid* p) {}

INCASM("asm/solid/iron_star_p2.inc");

extern const struct Collision Collision_ARRAY_0836fe10[3];

void FUN_080cbd6c(struct Solid* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SetDDP(&p->body, &Collision_ARRAY_0836fe10[2]);
      SetMotion(&p->s, MOTION(0x2D, 0x00));
      (p->s).mode[2]++;
      /* fallthrough */
    case 1:
      if ((p->s).work[0] != 2) {
        struct Overworld* ow = &gOverworld;
        (p->s).coord.y = ow->sea;
      }
      UpdateMotionGraphic(&p->s);
      break;
  }
}

// --------------------------------------------

void nop_080cbcc0(struct Solid* p);

const SolidFunc PTR_ARRAY_0836fe00[2] = {
    nop_080cbcc0,
    nop_080cbcc0,
};

// --------------------------------------------

void FUN_080cbcc4(struct Solid* p);
void FUN_080cbd6c(struct Solid* p);

const SolidFunc PTR_ARRAY_0836fe08[2] = {
    FUN_080cbcc4,
    FUN_080cbd6c,
};

// --------------------------------------------

const struct Collision Collision_ARRAY_0836fe10[3] = {
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      atkType : 0x00,
      element : 0x00,
      nature : BODY_NATURE_B2,
      comboLv : 0x00,
      hitzone : 0x00,
      remaining : 1,
      layer : 0x00000001,
      range : {0x0000, 0x0600, 0x1A00, 0x1000},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 255,
      hitzone : 0x00,
      remaining : 0,
      layer : 0x00000001,
      range : {0x0000, -0x0A00, 0x2000, 0x0800},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      atkType : 0x00,
      element : 0x00,
      nature : BODY_NATURE_B2,
      comboLv : 0x00,
      hitzone : 0x00,
      remaining : 0,
      layer : 0x00000001,
      range : {0x0000, 0x0000, 0x1800, 0x1800},
    },
};

const struct Coord Coord_0836fe58 = {-0x04000000, 0x10002000};
