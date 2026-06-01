#include "collision.h"
#include "gfx.h"
#include "global.h"
#include "projectile.h"

// コピーXのチャージショットに関係?

static void Projectile28_Init(struct Entity* p);
static void Projectile28_Update(struct Entity* p);
static void Projectile28_Die(Object* p);

// clang-format off
const ProjectileRoutine gProjectile28Routine = {
    [ENTITY_INIT] =      (ProjectileFunc)Projectile28_Init,
    [ENTITY_UPDATE] =    (ProjectileFunc)Projectile28_Update,
    [ENTITY_DIE] =       (ProjectileFunc)Projectile28_Die,
    [ENTITY_DISAPPEAR] = (ProjectileFunc)DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

void FUN_080a9aa0(struct Entity* e, u8 kind1, u8 kind2) {
  struct Entity* p = AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    p->taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 28);
    p->tileNum = 0, p->palID = 0;
    p->work[0] = kind1, p->work[1] = kind2;
    p->unk_28 = (void*)e;
    p->coord = e->coord;
  }
}

// --------------------------------------------

void FUN_080a9b90(struct Projectile* p);
void FUN_080a9d88(struct Projectile* p);
void FUN_080a9e74(struct Projectile* p);
void FUN_080aa08c(struct Projectile* p);

static void Projectile28_Init(struct Entity* p) {
  static const ProjectileFunc PTR_ARRAY_0836c20c[4] = {
      (ProjectileFunc)FUN_080a9b90,
      (ProjectileFunc)FUN_080a9d88,
      (ProjectileFunc)FUN_080a9e74,
      (ProjectileFunc)FUN_080aa08c,
  };  // 0x0836c20c
  (PTR_ARRAY_0836c20c[p->work[0]])((void*)p);
}

void FUN_080a9c88(struct Projectile* p);
void FUN_080a9dcc(struct Projectile* p);
void FUN_080a9ef8(struct Projectile* p);
void FUN_080aa120(struct Projectile* p);

static void Projectile28_Update(struct Entity* p) {
  static const ProjectileFunc PTR_ARRAY_0836c21c[4] = {
      (ProjectileFunc)FUN_080a9c88,
      (ProjectileFunc)FUN_080a9dcc,
      (ProjectileFunc)FUN_080a9ef8,
      (ProjectileFunc)FUN_080aa120,
  };
  (PTR_ARRAY_0836c21c[p->work[0]])((void*)p);
}

static void Projectile28_Die(Object* p) {
  if ((p->s).work[0] > 1) {
    gWindowRegBuffer.dispcnt &= ~DISPCNT_WIN1_ON;
    gWindowRegBuffer.winin[2] |= 0xFE;
    PALETTE16(0) = RGB_BLACK;
  }
  EXIT_BODY(p);
  SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}

// --------------------------------------------

INCASM("asm/projectile/unk_28_p1.inc");

void FUN_080a9d88(struct Projectile* p) {
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  InitNonAffineMotion(&p->s);
  (p->s).flags |= FLIPABLE;
  SetMotion(&p->s, MOTION(0x5f, 1));
  (p->s).mode[2] = 1;
  Projectile28_Update(&p->s);
}

INCASM("asm/projectile/unk_28_p2.inc");

// --------------------------------------------

// 0x0836c22c
static const struct Collision sCollisions[4] = {
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(8), PIXEL(8)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      damage : 4,
      LAYER(0xFFFFFFFF),
      hitzone : 0,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(0), PIXEL(0)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      nature : 0x04,
      hitzone : 1,
      hardness : METAL,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(127), PIXEL(64), -PIXEL(1)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      damage : 4,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : METAL,
      remaining : 0,
      priorityLayer : 0xFFFFFFFF,
      range : {PIXEL(0), -PIXEL(127), PIXEL(64), -PIXEL(1)},
    },
};
