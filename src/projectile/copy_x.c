#include "collision.h"
#include "global.h"
#include "projectile.h"

static const ProjectileFunc sUpdates[2];

static const ProjectileFunc sInitializers[2];

void createCopyXSonicBoom(struct Entity* e, u8 w0, u8 w1) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 24);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = w0;
    (p->s).work[1] = w1;
    (p->s).unk_28 = e;
    (p->s).coord = e->coord;
  }
}

void CopyXProjectile_Init(struct Projectile* p) {
  (sInitializers[(p->s).work[0]])(p);
}

void CopyXProjectile_Update(struct Projectile* p) {
  (sUpdates[(p->s).work[0]])(p);
}

void CopyXProjectile_Die(struct Projectile* p) {
  EXIT_BODY(p);
  SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}

INCASM("asm/projectile/copy_x_post_p2.inc");

void CopyXProjectile_Init(struct Projectile* p);
void CopyXProjectile_Update(struct Projectile* p);
void CopyXProjectile_Die(struct Projectile* p);

// clang-format off
const ProjectileRoutine gCopyXProjectileRoutine = {
    [ENTITY_INIT] =      CopyXProjectile_Init,
    [ENTITY_UPDATE] =    CopyXProjectile_Update,
    [ENTITY_DIE] =       CopyXProjectile_Die,
    [ENTITY_DISAPPEAR] = DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

void initCopyXSlidingSonicBoom(struct Projectile* p);
void FUN_080a82dc(struct Projectile* p);

static const ProjectileFunc sInitializers[] = {
    initCopyXSlidingSonicBoom,
    FUN_080a82dc,
};

// --------------------------------------------

void moveSlidingSonicBoom(struct Projectile* p);
void moveNovaStrikeSonicBoom(struct Projectile* p);

static const ProjectileFunc sUpdates[] = {
    moveSlidingSonicBoom,
    moveNovaStrikeSonicBoom,
};

// --------------------------------------------

static const struct Collision sCollisions[4] = {
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      nature : 0x04,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(8), -PIXEL(8), PIXEL(24), PIXEL(16)},
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
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(12), PIXEL(0), PIXEL(24), PIXEL(32)},
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
};
