#include "collision.h"
#include "global.h"
#include "projectile.h"
#include "vfx.h"

static const ProjectileFunc sUpdates[2];
static const struct Collision sCollisions[3];

void Projectile5_Init(struct Projectile* p);
void Projectile5_Update(struct Projectile* p);
void Projectile5_Die(struct Projectile* p);

// clang-format off
const ProjectileRoutine gProjectile5Routine = {
    [ENTITY_INIT] =      Projectile5_Init,
    [ENTITY_UPDATE] =    Projectile5_Update,
    [ENTITY_DIE] =       Projectile5_Die,
    [ENTITY_DISAPPEAR] = DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};
// clang-format on

struct Projectile* FUN_0809d8a0(struct Coord* c, s32 prevX, s32 prevY, struct Entity* e) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 5);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).coord = *c;
    (p->s).work[0] = 0;
    (p->prevCoord).x = prevX;
    (p->prevCoord).y = prevY;
    (p->s).unk_28 = e;
  }
  return p;
}

struct Projectile* FUN_0809d904(struct Coord* c, s32 prevX, s32 prevY, struct Entity* e) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 5);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).coord = *c;
    (p->s).work[0] = 1;
    (p->prevCoord).x = prevX;
    (p->prevCoord).y = prevY;
    (p->s).unk_28 = e;
  }
  return p;
}

void Projectile5_Init(struct Projectile* p) {
  InitNonAffineMotion(&p->s);
  (p->s).flags |= DISPLAY;
  (p->s).flags |= FLIPABLE;
  INIT_BODY(p, sCollisions, 1, NULL);
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  (p->s).mode[1] = 0;
  (p->s).mode[2] = 0;
  (p->s).mode[3] = 0;
  Projectile5_Update(p);
}


void Projectile5_Update(struct Projectile* p) {
  (sUpdates[(p->s).mode[1]])(p);
}

void Projectile5_Die(struct Projectile* p) {
  (p->s).flags &= ~DISPLAY;
  EXIT_BODY(p);
  SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}

void FUN_0809da14(struct Projectile* p) {
  if ((p->s).unk_28->mode[0] > 1) {
    CreateSmoke(3, &(p->s).coord);
    SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
  } else {
    switch ((p->s).mode[2]) {
      case 0:
        if ((p->s).work[0] == 0) {
          SetMotion(&p->s, 0xa00);
        } else {
          SetMotion(&p->s, 0xa03);
        }
        (p->s).mode[2]++;
        // fallthrough
      case 1:
        UpdateMotionGraphic(&p->s);
        break;
    }
    if ((p->prevCoord).y == 0 || --(p->prevCoord).y == 0) {
      (p->s).work[2] = 0x7f;
      (p->s).mode[1] = 1;
      (p->s).mode[2] = 0;
    }
  }
}

void FUN_0809daa0(struct Projectile* p) {
  if ((p->s).unk_28->mode[0] > 1) {
    CreateSmoke(3, &(p->s).coord);
    SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
  } else if (--(p->s).work[2] == 0) {
    SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
  } else {
    s32 m = (p->s).mode[2];
    switch (m) {
      case 0:
        if ((p->s).work[0] == 0) {
          SetMotion(&p->s, 0xa01);
          SetDDP(&p->body, &sCollisions[1]);
          (p->s).d.y = (p->prevCoord).x;
          (p->s).d.x = m;
        } else {
          SetMotion(&p->s, 0xa04);
          SetDDP(&p->body, &sCollisions[2]);
          (p->s).d.x = -(p->prevCoord).x;
          (p->s).d.y = m;
        }
        RNG_0202f388 = LCG(RNG_0202f388);
        (p->s).work[3] = (RNG_0202f388 >> 16) & 1;
        (p->s).mode[2]++;
        // fallthrough
      case 1:
        UpdateMotionGraphic(&p->s);
        if ((p->s).motion.state == 3) {
          (p->s).flags |= DISPLAY;
          (p->s).mode[2]++;
        }
        break;
      case 2:
        (p->s).coord.x += (p->s).d.x;
        (p->s).coord.y += (p->s).d.y;
        UpdateMotionGraphic(&p->s);
        break;
    }
  }
}

void FUN_0809da14(struct Projectile* p);
void FUN_0809daa0(struct Projectile* p);

static const ProjectileFunc sUpdates[2] = {
    FUN_0809da14,
    FUN_0809daa0,
};

static const struct Collision sCollisions[3] = {
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 0x00,
      hardness : METAL,
      remaining : 0,
      layer : 0xFFFFFFFF,
      range : {0x0000, 0x0000, 0x1000, 0x1000},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      atkType : 0x00,
      element : 0x00,
      nature : BODY_NATURE_B7,
      comboLv : 0x00,
      hitzone : 0x00,
      remaining : 0,
      layer : 0x00000001,
      range : {0x0000, 0x0000, 0x3000, 0x1000},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      atkType : 0x00,
      element : 0x00,
      nature : BODY_NATURE_B7,
      comboLv : 0x00,
      hitzone : 0x00,
      remaining : 0,
      layer : 0x00000001,
      range : {0x0000, 0x0000, 0x1000, 0x3000},
    },
};
