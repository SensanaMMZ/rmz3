#include "collision.h"
#include "entity.h"
#include "global.h"
#include "solid.h"
#include "zero.h"
#include "overworld.h"
#include "physics.h"

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


// 0x080D9070
void Solid27_Update(struct Solid* p) {
  register s32 z asm("r6");
  z = (p->s).work[0];
  if (z == 0) {
    register s32 w3 asm("r1");
    register s32 w3a asm("r0");
    register s32 w2 asm("r2");
    w3a = (p->s).work[3];
    asm volatile("add %0, %1, #0" : "=&l"(w3) : "l"(w3a));
    w2 = (p->s).work[2];
    if (w3 != w2) {
      (p->s).work[2] = w3a;
      if (w3 != 0) {
        struct Body* body;
        (p->s).flags |= COLLIDABLE;
        body = &p->body;
        InitBody(body, (const struct Collision*)0x083710F4, &(p->s).coord, 0);
        body->parent = (struct CollidableEntity*)p;
        body->fn = (BodyFunc)z;
      } else {
        u8* a = (u8*)p + 0x8c;
        *(u32*)a = w3;
        asm("" : "+r"(a));
        a += 4;
        asm("" : "+r"(a));
        *(u32*)a = w3;
        asm("" : "+r"(a));
        a += 4;
        asm("" : "+r"(a));
        *a = w3;
        (p->s).flags &= ~COLLIDABLE;
      }
    }
    (p->s).coord.x = (pZero2->s).coord.x;
    {
      register u8* ow asm("r0");
      register u32 off asm("r1");
      ow = (u8*)&gOverworld;
      off = 0x2C00C;
      asm volatile("" : "+r"(off));
      asm volatile("add %0, %0, %1" : "+l"(ow) : "l"(off));
      (p->s).coord.y = *(s32*)ow;
    }
    return;
  }
  {
    struct Zero* zp = pZero2;
    register s32 cx asm("r2");
    cx = (zp->s).coord.x;
    (p->s).coord.x = cx;
    (p->s).coord.y = (zp->s).coord.y;
    {
      u8 w1 = (p->s).work[1];
      if (w1 == 0) {
        s32 cy;
        (p->s).coord.x = FUN_0800a31c(cx, (p->s).coord.y);
        {
          register u8* ow2 asm("r0");
          register s32 off2 asm("r2");
          register u16 hv asm("r1");
          register s32 mk asm("r0");
          ow2 = (u8*)&gOverworld;
          off2 = 0xE8 * 2;
          asm volatile("add %0, %0, %1" : "+l"(ow2) : "l"(off2));
          hv = *(u16*)ow2;
          mk = 0x7F;
          mk &= hv;
          if (mk != 0xD) {
            return;
          }
        }
        cy = (p->s).coord.y;
        {
          s32 hi = 0x4B800;
          if (cy > hi) {
            (p->s).coord.y = hi;
            return;
          }
        }
        {
          s32 lo = 0x427FF;
          if (cy > lo) {
            return;
          }
          (p->s).coord.y = lo + 1;
          return;
        }
      }
      if (w1 == 1) {
        (p->s).coord.x = FUN_0800a22c(cx, (p->s).coord.y);
        return;
      }
      if (w1 == 2) {
        (p->s).coord.y = FUN_0800a134(cx, (p->s).coord.y);
        return;
      }
      (p->s).coord.y = FUN_08009f6c(cx, (p->s).coord.y);
    }
  }
}

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
