#include "collision.h"
#include "global.h"
#include "projectile.h"
#include "vfx.h"

static const ProjectileFunc sUpdates1[5];
static const ProjectileFunc sUpdates2[5];

void FUN_080a0888(s32 x, s32 y, u8 a2, u8 a3) {
  struct Projectile* p = (struct Projectile*)AllocEntityLast(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 14);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 4;
    (p->s).coord.x = x;
    (p->s).coord.y = y;
    (p->s).work[2] = a2;
    (p->s).work[3] = a3;
  }
}

void FUN_080a08e0(struct Entity* e, s32 x, s32 y, u8 a3) {
  struct Projectile* p = (struct Projectile*)AllocEntityLast(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 14);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 0;
    (p->s).coord.x = x;
    (p->s).coord.y = y;
    (p->s).work[2] = a3;
    (p->s).unk_28 = e;
  }
}

INCASM("asm/projectile/unk_14_p1_p1_p3.inc");

void Projectile14_Update(struct Projectile* p) {
  (sUpdates1[(p->s).mode[1]])(p);
  (sUpdates2[(p->s).mode[1]])(p);
}

void Projectile14_Die(struct Projectile* p) {
  EXIT_BODY(p);
  CreateSmoke(1, &(p->s).coord);
  PlaySound(0x2a);
  SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}

void nop_080a0b6c(struct Projectile* p) {}

INCASM("asm/projectile/unk_14_p2.inc");

void Projectile14_Init(struct Projectile* p);
void Projectile14_Update(struct Projectile* p);
void Projectile14_Die(struct Projectile* p);

// clang-format off
const ProjectileRoutine gProjectile14Routine = {
    [ENTITY_INIT] =      Projectile14_Init,
    [ENTITY_UPDATE] =    Projectile14_Update,
    [ENTITY_DIE] =       Projectile14_Die,
    [ENTITY_DISAPPEAR] = DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

void nop_080a0b6c(struct Projectile* p);

// clang-format off
static const ProjectileFunc sUpdates1[5] = {
    nop_080a0b6c,
    nop_080a0b6c,
    nop_080a0b6c,
    nop_080a0b6c,
    nop_080a0b6c,
};
// clang-format on

// --------------------------------------------

void FUN_080a0b70(struct Projectile* p);
void FUN_080a0dc0(struct Projectile* p);
void FUN_080a0fa8(struct Projectile* p);
void FUN_080a1280(struct Projectile* p);
void FUN_080a133c(struct Projectile* p);

// clang-format off
static const ProjectileFunc sUpdates2[5] = {
    FUN_080a0b70,
    FUN_080a0dc0,
    FUN_080a0fa8,
    FUN_080a1280,
    FUN_080a133c,
};
// clang-format on

// --------------------------------------------

static const struct Collision sCollisions[10] = {
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      atkType : 0x00,
      element : 0x00,
      nature : 0x04,
      comboLv : 0,
      hitzone : 0,
      remaining : 2,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(40), PIXEL(40)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      atkType : 0x00,
      element : 0x00,
      nature : 0x04,
      comboLv : 0,
      hitzone : 0,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(50), PIXEL(26)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      atkType : 0x00,
      element : 0x00,
      nature : 0x04,
      comboLv : 0,
      hitzone : 0,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(26), PIXEL(50)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 5,
      atkType : 0x00,
      element : 0x00,
      nature : 0x04,
      comboLv : 0,
      hitzone : 0,
      remaining : 0,
      layer : 0x00000001,
      range : {-PIXEL(4), PIXEL(2), PIXEL(40), PIXEL(16)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 5,
      atkType : 0x00,
      element : 0x00,
      nature : 0x04,
      comboLv : 0,
      hitzone : 0,
      remaining : 0,
      layer : 0x00000001,
      range : {-PIXEL(20), PIXEL(19), PIXEL(8), PIXEL(51)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(8), PIXEL(60)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 1,
      layer : 0x00000001,
      range : {-PIXEL(57), -PIXEL(24), PIXEL(36), PIXEL(14)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 0,
      layer : 0x00000001,
      range : {-PIXEL(35), -PIXEL(11), PIXEL(37), PIXEL(13)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 1,
      layer : 0x00000001,
      range : {-PIXEL(57), -PIXEL(39), PIXEL(36), PIXEL(14)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 0,
      layer : 0x00000001,
      range : {-PIXEL(35), -PIXEL(53), PIXEL(37), PIXEL(13)},
    },
};

static const u8 u8_ARRAY_0836b20c[5] = {0, 1, 2, 3, 4};
static const u8 u8_ARRAY_0836b211[2] = {6, 8};
