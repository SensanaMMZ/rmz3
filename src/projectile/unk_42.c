#include "collision.h"
#include "global.h"
#include "projectile.h"

void Projectile42_Init(struct Projectile* p);
void Projectile42_Update(struct Projectile* p);
void Projectile42_Die(struct Projectile* p);

// clang-format off
const ProjectileRoutine gProjectile42Routine = {
    [ENTITY_INIT] =      Projectile42_Init,
    [ENTITY_UPDATE] =    Projectile42_Update,
    [ENTITY_DIE] =       Projectile42_Die,
    [ENTITY_DISAPPEAR] = DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};
// clang-format on

void FUN_080b1234(s32 x, s32 y, s32 dx, s32 dy, u8 n) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 42);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = n;
    (p->s).coord.x = x;
    (p->s).coord.y = y;
    (p->s).d.x = dx;
    (p->s).d.y = dy;
  }
}

void FUN_080b1298(struct Projectile* _) { return; }

// --------------------------------------------

void FUN_080b13d8(struct Projectile* p);
void FUN_080b13dc(struct Projectile* p);

// clang-format off
// two adjacent 1-entry dispatch tables: Projectile42_Update loads each
// base from its own literal pool slot
const ProjectileFunc PTR_ARRAY_0836d710[1] = {
    FUN_080b13d8,
};
const ProjectileFunc PTR_ARRAY_0836d714[1] = {
    FUN_080b13dc,
};
// clang-format on

static const struct Collision sCollision = {
  kind : DDP,
  faction : FACTION_ENEMY,
  damage : 4,
  remaining : 0,
  layer : 0x00000001,
  range : {PIXEL(0), PIXEL(0), PIXEL(12), PIXEL(12)},
};

static const u8 u8_ARRAY_0836d730[4] = {0, 0, 0, 0};

void Projectile42_Init(struct Projectile* p) {
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  (p->s).mode[1] = u8_ARRAY_0836d730[(p->s).work[0]];
  (p->s).flags |= FLIPABLE;
  (p->s).flags |= DISPLAY;
  InitNonAffineMotion(&p->s);
  INIT_BODY(p, &sCollision, 1, (void*)FUN_080b1298);
  Projectile42_Update(p);
}
