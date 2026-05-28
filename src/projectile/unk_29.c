#include "collision.h"
#include "global.h"
#include "projectile.h"

void copyx_080aa24c(struct Entity* e, u8 a1, u8 a2) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 29);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).unk_28 = e;
    (p->s).work[0] = a1;
    (p->s).work[1] = a2;
  }
}

INCASM("asm/projectile/unk_29_p2.inc");

void Projectile29_Die(struct Projectile* p) {
  (p->s).flags &= ~DISPLAY;
  SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}

void Projectile29_Init(struct Projectile* p);
void Projectile29_Update(struct Projectile* p);

// clang-format off
const ProjectileRoutine gProjectile29Routine = {
    [ENTITY_INIT] =      Projectile29_Init,
    [ENTITY_UPDATE] =    Projectile29_Update,
    [ENTITY_DIE] =       Projectile29_Die,
    [ENTITY_DISAPPEAR] = DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

static const struct Collision sCollisions[2] = {
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 5,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(16), PIXEL(16)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      damage : 5,
      LAYER(0xFFFFFFFF),
      hitzone : 0,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(16), PIXEL(16)},
    },
};
