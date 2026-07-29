#include "entity.h"
#include "global.h"
#include "cyberelf.h"
#include "mod.h"
#include "physics.h"
#include "solid.h"

/*
various:
  00: エルピス
  01: ファントム
*/

static const struct Collision sCollision;

void ModElf_Update(struct Solid* p);

void ModElf_Init(struct Solid* p) {
  register struct Solid* q asm("r6");
  register s32 f asm("r2");
  q = p;
  if ((q->s).work[0] == 0) {
    register u8 b asm("r1");
    register s32 m asm("r0");
    b = gSystemSavedataManager.mods[8];
    m = 2;
    m &= b;
    asm("" : "+r"(m));
    f = (u8)m;
    if (f == 0) {
      goto despawn;
    }
  }
  if (*(volatile u8*)&(q->s).work[0] == 1) {
    register u8 b2 asm("r1");
    register s32 m2 asm("r0");
    b2 = gSystemSavedataManager.mods[4];
    m2 = 2;
    m2 &= b2;
    asm("" : "+r"(m2));
    f = (u8)m2;
    if (f == 0) {
    despawn:
      {
        register u8 f1 asm("r1");
        register s32 fp asm("r0");
        f1 = (q->s).flags;
        fp = 0xFE;
        fp &= f1;
        {
          register s32 c2 asm("r1");
          c2 = 0xFD;
          fp &= c2;
        }
        (q->s).flags = fp;
      }
      (q->body).status = f;
      (q->body).prevStatus = f;
      (q->body).invincibleTime = f;
      (q->s).flags &= ~COLLIDABLE;
      SET_SOLID_ROUTINE(q, ENTITY_DISAPPEAR);
      return;
    }
  }
  SET_SOLID_ROUTINE(q, ENTITY_UPDATE);
  InitNonAffineMotion(&q->s);
  ResetDynamicMotion(&q->s);
  {
    register u8 f0 asm("r1");
    register s32 d0 asm("r0");
    f0 = (q->s).flags;
    d0 = DISPLAY;
    d0 |= f0;
    d0 |= FLIPABLE;
    (q->s).flags = d0;
  }
  SetMotion(&q->s, GetElfMotion(2));
  UpdateMotionGraphic(&q->s);
  {
    s32 z;
    {
      register s32 z5 asm("r5");
      z5 = 0;
      asm("" : "+r"(z5));
      z = z5;
    }
    (q->s).flags &= ~X_FLIP;
    ((q->s).spr).xflip = z;
    {
      u8* a = (u8*)q + 0x4a;
      register u8 b asm("r1");
      s32 msk;
      b = *a;
      msk = -0x11;
      msk &= b;
      *a = msk;
    }
    (q->s).flags |= COLLIDABLE;
    {
      struct Body* body;
      body = &q->body;
      InitBody(body, &sCollision, &(q->s).coord, 8);
      body->parent = (struct CollidableEntity*)q;
      body->fn = (void*)z;
    }
    (q->s).coord.y = FUN_08009f6c((q->s).coord.x, (q->s).coord.y);
    *(s32*)((u8*)q + 0xb4) = (q->s).coord.x;
    *(s32*)((u8*)q + 0xb8) = (q->s).coord.y - 0x3000;
    (q->s).work[2] = z;
  }
  ModElf_Update(q);
}

INCASM("asm/solid/mod_elf.inc");

void ModElf_Die(struct Solid* p) {
  SET_SOLID_ROUTINE(p, ENTITY_EXIT);
}

void ModElf_Init(struct Solid* p);
void ModElf_Update(struct Solid* p);

// clang-format off
const SolidRoutine gModElfRoutine = {
    [ENTITY_INIT] =      ModElf_Init,
    [ENTITY_UPDATE] =    ModElf_Update,
    [ENTITY_DIE] =       ModElf_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteSolid,
    [ENTITY_EXIT] =      (SolidFunc)DeleteEntity,
};
// clang-format on

static const struct Collision sCollision = {
  kind : DDP,
  faction : FACTION_ENEMY,
  special : CHATABLE,
  damage : 255,
  remaining : 0,
  layer : 0x00000001,
  range : {PIXEL(0), PIXEL(0), PIXEL(36), PIXEL(1)},
};
