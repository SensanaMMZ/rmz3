#include "collision.h"
#include "entity.h"
#include "global.h"
#include "solid.h"

// 水没した図書館関連の何か

struct Entity* FUN_080d8f2c(void) {
  struct Entity* p = AllocEntityFirst(gSolidHeaderPtr);
  if (p != NULL) {
    p->taskCol = 30;
    INIT_SOLID_ROUTINE(p, SOLID_UNK_027);
    p->tileNum = 0;
    p->palID = 0;
    p->flags2 |= WHITE_PAINTABLE;
    p->invincibleID = p->uniqueID;
    p->work[0] = 0;
  }
  return p;
}

struct Entity* FUN_080d8f7c(u8 a0) {
  struct Entity* p = AllocEntityFirst(gSolidHeaderPtr);
  if (p != NULL) {
    p->taskCol = 30;
    INIT_SOLID_ROUTINE(p, SOLID_UNK_027);
    p->tileNum = 0;
    p->palID = 0;
    p->flags2 |= WHITE_PAINTABLE;
    p->invincibleID = p->uniqueID;
    p->work[0] = 1;
    p->work[1] = a0;
  }
  return p;
}

void FUN_080d8fd4(struct Entity* p) {
  if (p != NULL) {
    p->work[3] = 1;
  }
}


void FUN_080d8fe4(struct Entity* p) {
  if (p != NULL) {
    p->work[3] = 0;
  }
}

extern const struct Collision Collision_ARRAY_083710f4[5];
void Solid27_Update(struct Solid* p);

// 0x080d8ff4
void Solid27_Init(struct Solid* p) {
  register struct Solid* pp asm("r5");
  register s32 z2 asm("r2");
  register u8 fv asm("r1");
  s32 z6;
  struct Body* body;
  register const struct Collision* col asm("r1");
  pp = p;
  z2 = 0;
  z6 = 0;
  (pp->s).work[3] = z6;
  (pp->s).work[2] = z6;
  {
    u8 t = (pp->s).flags;
    fv = FLIPABLE;
    fv |= t;
    asm("" : "+r"(z2));
    fv |= z2;
    (pp->s).flags = fv;
  }
  if ((pp->s).work[0] == 0) {
    fv |= COLLIDABLE;
    (pp->s).flags = fv;
    body = &pp->body;
    col = &Collision_ARRAY_083710f4[0];
  } else {
    fv |= COLLIDABLE;
    (pp->s).flags = fv;
    body = &pp->body;
    {
      register u8 w1 asm("r0");
      w1 = (pp->s).work[1];
      col = &Collision_ARRAY_083710f4[1 + w1];
    }
  }
  InitBody(body, col, &(pp->s).coord, 0);
  body->parent = (struct CollidableEntity*)pp;
  body->fn = (BodyFunc)z6;
  SET_SOLID_ROUTINE(pp, ENTITY_UPDATE);
  Solid27_Update(pp);
}


INCASM("asm/solid/unk_27_p1_p3.inc");

void Solid27_Die(struct Solid* p) {}

void Solid27_Init(struct Solid* p);
void Solid27_Update(struct Solid* p);
void Solid27_Die(struct Solid* p);

// clang-format off
const SolidRoutine gSolid27Routine = {
    [ENTITY_INIT] =      Solid27_Init,
    [ENTITY_UPDATE] =    Solid27_Update,
    [ENTITY_DIE] =       Solid27_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteSolid,
    [ENTITY_EXIT] =      (SolidFunc)DeleteEntity,
};
// clang-format on

const struct Collision Collision_ARRAY_083710f4[5] = {
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 6,
      hitzone : 0x00,
      remaining : 0,
      layer : 0x00000001,
      range : {0x0000, 0x5000, 0x0800, -0x6200},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 6,
      hitzone : 0x00,
      remaining : 0,
      layer : 0x00000001,
      range : {-0x0600, -0x1000, 0x1000, 0x0800},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 6,
      hitzone : 0x00,
      remaining : 0,
      layer : 0x00000001,
      range : {0x0600, -0x1000, 0x1000, 0x0800},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 6,
      hitzone : 0x00,
      remaining : 0,
      layer : 0x00000001,
      range : {0x0000, -0x0600, 0x0800, 0x1000},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 6,
      hitzone : 0x00,
      remaining : 0,
      layer : 0x00000001,
      range : {0x0000, 0x0600, 0x0800, 0x1000},
    },
};
