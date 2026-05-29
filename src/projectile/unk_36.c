#include "collision.h"
#include "global.h"
#include "projectile.h"

// Hanumachine

static const ProjectileFunc sUpdates[4];

static const ProjectileFunc sInitializers[4];

void hanu_080ad598(struct Entity* e, u8 a1, u8 a2) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 36);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = a1;
    (p->s).work[1] = a2;
    (p->s).unk_28 = e;
    (p->s).coord = e->coord;
  }
}

void FUN_080ad5f0(struct Entity* e, u8 a1, u8 a2) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 36);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = a1;
    (p->s).work[1] = a2;
    (p->s).unk_28 = e;
    (p->s).coord = e->coord;
  }
}

void Projectile36_Init(struct Projectile* p) {
  (sInitializers[(p->s).work[0]])(p);
}


void Projectile36_Update(struct Projectile* p) {
  (sUpdates[(p->s).work[0]])(p);
}

void Projectile36_Die(struct Projectile* p) {
  (p->s).flags &= ~DISPLAY;
  SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}

INCASM("asm/projectile/unk_36_pre_post_p2.inc");

void FUN_080ada50(struct Projectile* p) {
  UpdateMotionGraphic(&p->s);
  if ((p->s).motion.state == 3) {
    SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
  }
}


void Projectile36_Init(struct Projectile* p);
void Projectile36_Update(struct Projectile* p);
void Projectile36_Die(struct Projectile* p);

// clang-format off
const ProjectileRoutine gProjectile36Routine = {
    [ENTITY_INIT] =      Projectile36_Init,
    [ENTITY_UPDATE] =    Projectile36_Update,
    [ENTITY_DIE] =       Projectile36_Die,
    [ENTITY_DISAPPEAR] = DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

void FUN_080ad698(struct Projectile* p);
void FUN_080ad7d0(struct Projectile* p);
void FUN_080ad8b8(struct Projectile* p);
void FUN_080ad994(struct Projectile* p);

static const ProjectileFunc sInitializers[4] = {
    FUN_080ad698,
    FUN_080ad7d0,
    FUN_080ad8b8,
    FUN_080ad994,
};

// --------------------------------------------

void FUN_080ad778(struct Projectile* p);
void FUN_080ad840(struct Projectile* p);
void FUN_080ad958(struct Projectile* p);
void FUN_080ada50(struct Projectile* p);

static const ProjectileFunc sUpdates[4] = {
    FUN_080ad778,
    FUN_080ad840,
    FUN_080ad958,
    FUN_080ada50,
};

// --------------------------------------------

static const struct Collision sCollisions[2] = {
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(8), PIXEL(8)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      damage : 3,
      LAYER(0xFFFFFFFF),
      hitzone : 0,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(0), PIXEL(0)},
    },
};
