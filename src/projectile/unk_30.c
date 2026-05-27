#include "collision.h"
#include "global.h"
#include "projectile.h"

static const ProjectileFunc sUpdates1[1];
static const ProjectileFunc sUpdates2[1];

INCASM("asm/projectile/unk_30_pre_p1.inc");

void nop_080aa638(struct Enemy* p) {}

INCASM("asm/projectile/unk_30_pre_p2_p1.inc");

void Projectile30_Update(struct Projectile* p) {
  (sUpdates1[(p->s).mode[1]])(p);
  (sUpdates2[(p->s).mode[1]])(p);
}

INCASM("asm/projectile/unk_30_pre_p2_p2.inc");

void FUN_080aa710(struct Projectile* p) {}

INCASM("asm/projectile/unk_30_post.inc");

void Projectile30_Init(struct Projectile* p);
void Projectile30_Update(struct Projectile* p);
void Projectile30_Die(struct Projectile* p);

// clang-format off
const ProjectileRoutine gProjectile30Routine = {
    [ENTITY_INIT] =      Projectile30_Init,
    [ENTITY_UPDATE] =    Projectile30_Update,
    [ENTITY_DIE] =       Projectile30_Die,
    [ENTITY_DISAPPEAR] = DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

void FUN_080aa710(struct Projectile* p);

static const ProjectileFunc sUpdates1[1] = {
    FUN_080aa710,
};

void FUN_080aa714(struct Projectile* p);

static const ProjectileFunc sUpdates2[1] = {
    FUN_080aa714,
};

// --------------------------------------------

static const struct Collision sCollisions[1] = {
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(8), PIXEL(8)},
    },
};

static const u8 u8_ARRAY_0836c304[2] = {0, 0};

static const motion_t sMotions[8] = {
    MOTION(SM089_GLACIERLE_HAND, 7), MOTION(SM089_GLACIERLE_HAND, 6), MOTION(SM089_GLACIERLE_HAND, 5), MOTION(SM089_GLACIERLE_HAND, 8), MOTION(SM089_GLACIERLE_HAND, 7), MOTION(SM089_GLACIERLE_HAND, 6), MOTION(SM089_GLACIERLE_HAND, 5), MOTION(SM089_GLACIERLE_HAND, 8),
};
