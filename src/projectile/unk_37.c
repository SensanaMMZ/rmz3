#include "collision.h"
#include "global.h"
#include "story.h"
#include "projectile.h"

struct Projectile* FUN_080ada80(struct Entity* e, u8 a1) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 37);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = a1;
    (p->s).work[1] = 1;
    (p->s).unk_28 = e;
  }
  return p;
}

struct Projectile* FUN_080adad0(struct Coord* c, u8 a1) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 37);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = a1;
    (p->s).work[1] = 0;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
  }
  return p;
}

static const struct Collision sCollisions[3];
void Projectile37_Update(struct Projectile* p);

// 0x080ADB24
void Projectile37_Init(struct Projectile* p) {
  u8 w1 = (p->s).work[1];
  asm("" : "+r"(w1));
  if (w1 == 0) {
      InitNonAffineMotion(&p->s);
      (p->s).flags = DISPLAY | (p->s).flags;
      (p->s).flags |= FLIPABLE;
      INIT_BODY(p, &sCollisions[1], 4, NULL);
      SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
      (p->s).mode[1] = w1;
      (p->s).mode[2] = w1;
      (p->s).mode[3] = w1;
      asm volatile("" ::"r"(w1));
  } else if (w1 == 1) {
      u32 z;
      register u8 fv asm("r0");
      register u8 fl asm("r1");
      InitNonAffineMotion(&p->s);
      fl = (p->s).flags;
      fv = DISPLAY;
      z = 0;
      asm("" : "+r"(z));
      fv |= fl;
      fl = FLIPABLE;
      fv |= fl;
      fl = COLLIDABLE;
      fv |= fl;
      (p->s).flags = fv;
      {
        struct Body* body = &p->body;
        InitBody(body, &sCollisions[0], &(p->s).coord, 1);
        body->parent = (struct CollidableEntity*)p;
        body->fn = (void*)z;
      }
      SET_PROJECTILE_ROUTINE(p, w1);
      (p->s).mode[1] = w1;
      (p->s).mode[2] = z;
      (p->s).mode[3] = z;
  }
  (p->s).work[2] = 0xFF;
  Projectile37_Update(p);
}

static const ProjectileFunc sUpdates[2];
void Projectile37_Die(struct Projectile* p);

void Projectile37_Update(struct Projectile* p) {
  if (IS_METTAUR) {
    (p->s).flags &= ~DISPLAY;
    EXIT_BODY(p);
    SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
    Projectile37_Die(p);
    return;
  }
  (sUpdates[(p->s).mode[1]])(p);
}

void Projectile37_Die(struct Projectile* p) {
  (p->s).flags &= ~DISPLAY;
  EXIT_BODY(p);
  SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}

INCASM("asm/projectile/unk_37_p3_p2.inc");

// 0x080AE140
void FUN_080ae140(struct Projectile* p) {
  struct Entity* q = (p->s).unk_28;
  if (q->mode[0] > 2) {
    *(u32*)((u8*)p + 0x8c) = 0;
    *(u32*)((u8*)p + 0x90) = 0;
    *(u8*)((u8*)p + 0x94) = 0;
    (p->s).flags &= ~COLLIDABLE;
    SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
    return;
  }
  switch ((p->s).mode[2]) {
    case 0:
      SetMotion(&p->s, MOTION(0x6E, 0x06));
      (p->s).work[2] = 0;
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 1:
      (p->s).coord = ((p->s).unk_28)->coord;
      UpdateMotionGraphic(&p->s);
      if (((p->s).unk_28)->mode[0] > 1) {
        (p->s).mode[2]++;
      }
      break;
    case 2: {
      s32 w;
      u32 kf;
      u32 one;
      (p->s).coord = q->coord;
      w = (p->s).work[2] + 1;
      (p->s).work[2] = w;
      kf = 0xFF;
      w &= kf;
      one = 1;
      w &= one;
      if (w != 0) {
        (p->s).flags |= one;
      } else {
        (p->s).flags &= 0xFE;
      }
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}

void Projectile37_Init(struct Projectile* p);
void Projectile37_Update(struct Projectile* p);
void Projectile37_Die(struct Projectile* p);

// clang-format off
const ProjectileRoutine gProjectile37Routine = {
    [ENTITY_INIT] =      Projectile37_Init,
    [ENTITY_UPDATE] =    Projectile37_Update,
    [ENTITY_DIE] =       Projectile37_Die,
    [ENTITY_DISAPPEAR] = DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

void FUN_080adc84(struct Projectile* p);
void FUN_080ae140(struct Projectile* p);

static const ProjectileFunc sUpdates[2] = {
    FUN_080adc84,
    FUN_080ae140,
};

// --------------------------------------------

static const struct Collision sCollisions[3] = {
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 0,
      hardness : METAL,
      remaining : 0,
      priorityLayer : 0xFFFFFFFF,
      range : {PIXEL(0), -PIXEL(7), PIXEL(22), PIXEL(19)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      nature : 0x80,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(10), PIXEL(10)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(10), PIXEL(10)},
    },
};
