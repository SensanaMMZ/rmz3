#include "collision.h"
#include "global.h"
#include "story.h"
#include "motion.h"
#include "projectile.h"
#include "gfx.h"
#include "anim_loader.h"
#include "constants/motion/static.h"
#include "entity/macros.h"

struct Projectile* FUN_080a2790(struct Coord* c, u8 a1) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 17);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = a1;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
    (p->s).work[1] = 1;
  }
  return p;
}

struct Projectile* FUN_080a27e4(struct Coord* c, u8 a1) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 17);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = a1;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
    (p->s).work[1] = 2;
  }
  return p;
}

struct Projectile* FUN_080a2838(struct Entity* e, struct Coord* c1, struct Coord* c2, u8 a3) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 17);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = a3;
    (p->s).coord.x = c1->x;
    (p->s).coord.y = c1->y;
    (p->s).unk_coord.x = c2->x;
    (p->s).unk_coord.y = c2->y;
    (p->s).work[1] = 0;
    (p->s).unk_28 = e;
  }
  return p;
}

static const struct Collision sCollisions[4];
void Projectile17_Update(struct Projectile* p);

void Projectile17_Init(struct Projectile* p) {
  s32 w1;
  InitNonAffineMotion(&p->s);
  {
    register s32 r0v asm("r0");
    register s32 r1v asm("r1");
    register s32 r2v asm("r2");
    register s32 r3v asm("r3");
    r1v = (p->s).flags;
    r0v = DISPLAY;
    r3v = 0;
    asm("" : "+r"(r0v), "+r"(r3v));
    r2v = r0v;
    r2v |= r1v;
    r0v = FLIPABLE;
    asm("" : "+r"(r0v));
    r2v |= r0v;
    r2v |= r3v;
    (p->s).flags = r2v;
    r1v = (p->s).work[0];
    if (r1v == 0) {
      r2v &= 0xEF;
      (p->s).flags = r2v;
      r0v = (s32)((u8*)p + 0x4c);
      *(u8*)r0v = r1v;
      r2v = (s32)((u8*)p + 0x4a);
      r1v = *(u8*)r2v;
      r0v = ~X_FLIP;
      asm("" : "+r"(r0v));
      *(u8*)r2v = r0v & r1v;
      asm volatile("");
    } else {
      r1v = 1;
      asm("" : "+r"(r1v));
      r0v = X_FLIP;
      r2v |= r0v;
      (p->s).flags = r2v;
      r0v = (s32)((u8*)p + 0x4c);
      *(u8*)r0v = r1v;
      r3v = (s32)((u8*)p + 0x4a);
      r2v = X_FLIP;
      r1v = *(u8*)r3v;
      r0v = ~X_FLIP;
      asm("" : "+r"(r0v));
      *(u8*)r3v = (r0v & r1v) | r2v;
    }
  }
  (p->s).work[2] = 0xFF;
  w1 = (p->s).work[1];
  if (w1 == 0) {
    LOAD_STATIC_GRAPHIC(SM066_PUFFY_BUBBLE);
    INIT_BODY(p, &sCollisions[0], 4, (void*)(u32)w1);
    SET_PROJECTILE_ROUTINE(&p->s, 1);
    (p->s).mode[1] = w1;
    (p->s).mode[2] = w1;
    (p->s).mode[3] = w1;
  } else if (w1 == 1) {
    register s32 z2 asm("r5");
    struct Body* body;
    {
      register s32 fl2 asm("r1");
      register s32 c4 asm("r0");
      fl2 = (p->s).flags;
      c4 = COLLIDABLE;
      z2 = 0;
      c4 |= fl2;
      (p->s).flags = c4;
    }
    body = &p->body;
    InitBody(body, &sCollisions[2], &(p->s).coord, 4);
    body->parent = (struct CollidableEntity*)p;
    body->fn = (void*)z2;
    SET_PROJECTILE_ROUTINE(&p->s, 1);
    (p->s).mode[1] = w1;
    (p->s).mode[2] = z2;
    (p->s).mode[3] = z2;
  } else if (w1 == 2) {
    register s32 z3 asm("r5");
    struct Body* body;
    {
      register s32 fl2 asm("r1");
      register s32 c4 asm("r0");
      fl2 = (p->s).flags;
      c4 = COLLIDABLE;
      z3 = 0;
      c4 |= fl2;
      (p->s).flags = c4;
    }
    body = &p->body;
    InitBody(body, &sCollisions[3], &(p->s).coord, 4);
    body->parent = (struct CollidableEntity*)p;
    body->fn = (void*)z3;
    {
      register s32* t asm("r2");
      t = (s32*)0x080FF080;
      (p->s).coord.x += t[(p->s).work[0] * 2];
      {
        register s32 i asm("r1");
        i = (p->s).work[0] * 8;
        t = (s32*)((u8*)t + 4);
        i += (s32)t;
        (p->s).coord.y += *(s32*)i;
      }
    }
    SET_PROJECTILE_ROUTINE(&p->s, 1);
    (p->s).mode[1] = w1;
    (p->s).mode[2] = z3;
    (p->s).mode[3] = z3;
  }
  Projectile17_Update(p);
}

static const ProjectileFunc PTR_ARRAY_0836b3b4[3];

void Projectile17_Update(struct Projectile* p) {
  if (IS_METTAUR) {
    (p->s).flags &= ~DISPLAY;
    (p->s).flags &= ~FLIPABLE;
    EXIT_BODY(p);
    SET_PROJECTILE_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }

  (PTR_ARRAY_0836b3b4[(p->s).mode[1]])(p);
}

void Projectile17_Die(struct Projectile* p) {
  (p->s).flags &= ~DISPLAY;
  EXIT_BODY(p);
  SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}

INCASM("asm/projectile/unk_17_pre_p4_p2.inc");

void FUN_080a2d9c(struct Projectile* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SetMotion(&p->s, MOTION(0x42, 4));
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 3) {
        SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
      }
      break;
  }
}

void FUN_080a2dec(struct Projectile* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SetMotion(&p->s, 0x4202);
      (p->s).work[2] = 0x14;
      (p->s).d.y = 0x40;
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      (p->s).coord.y -= (p->s).d.y;
      UpdateMotionGraphic(&p->s);
      if ((p->s).work[2] == 0 || --(p->s).work[2] == 0) {
        (p->s).mode[2]++;
      }
      break;
    case 2:
      SetMotion(&p->s, 0x4203);
      (p->s).work[2] = 0x14;
      (p->s).d.y = 0x20;
      (p->s).mode[2]++;
      // fallthrough
    case 3:
      (p->s).coord.y -= (p->s).d.y;
      UpdateMotionGraphic(&p->s);
      if ((p->s).work[2] == 0 || --(p->s).work[2] == 0) {
        SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
      }
      break;
  }
}

void Projectile17_Init(struct Projectile* p);
void Projectile17_Update(struct Projectile* p);
void Projectile17_Die(struct Projectile* p);

// clang-format off
const ProjectileRoutine gProjectile17Routine = {
    [ENTITY_INIT] =      Projectile17_Init,
    [ENTITY_UPDATE] =    Projectile17_Update,
    [ENTITY_DIE] =       Projectile17_Die,
    [ENTITY_DISAPPEAR] = DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};
// clang-format on

void FUN_080a2adc(struct Projectile* p);
void FUN_080a2d9c(struct Projectile* p);
void FUN_080a2dec(struct Projectile* p);

static const ProjectileFunc PTR_ARRAY_0836b3b4[3] = {
    FUN_080a2adc,
    FUN_080a2d9c,
    FUN_080a2dec,
};

static const struct Collision sCollisions[] = {
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(20), PIXEL(20)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(20), PIXEL(20)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(32), PIXEL(32)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(10), PIXEL(10)},
    },
};
