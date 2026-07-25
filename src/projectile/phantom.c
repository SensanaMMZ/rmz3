#include "collision.h"
#include "global.h"
#include "entity/macros.h"
#include "projectile.h"

static void PhantomProjectile_Init(struct Projectile* p);
static void PhantomProjectile_Update(struct Projectile* p);
void PhantomProjectile_Die(struct Projectile* p);

// clang-format off
const ProjectileRoutine gPhantomProjectileRoutine = {
    [ENTITY_INIT] =      PhantomProjectile_Init,
    [ENTITY_UPDATE] =    PhantomProjectile_Update,
    [ENTITY_DIE] =       PhantomProjectile_Die,
    [ENTITY_DISAPPEAR] = DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};
// clang-format on

static const struct Collision sCollisions[8] = {
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      atkType : 0x00,
      comboLv : 0,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(5), -PIXEL(5), PIXEL(10), PIXEL(10)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      damage : 3,
      LAYER(0xFFFFFFFF),
      hitzone : 0,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(16), PIXEL(8)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 5,
      atkType : 0x00,
      comboLv : 0,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(24), PIXEL(8)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      damage : 5,
      LAYER(0xFFFFFFFF),
      hitzone : 0,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(16), PIXEL(8)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 5,
      atkType : 0x00,
      comboLv : 0,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(20), PIXEL(20)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      damage : 5,
      LAYER(0xFFFFFFFF),
      hitzone : 0,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(16), PIXEL(8)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      atkType : 0x00,
      comboLv : 0,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(16), PIXEL(16)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      damage : 4,
      LAYER(0xFFFFFFFF),
      hitzone : 0,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(16), PIXEL(8)},
    },
};

// --------------------------------------------

static void FUN_080af114(struct Projectile* p);
static void FUN_080af1b4(struct Projectile* p);
static void FUN_080af214(struct Projectile* p);
static void FUN_080af250(struct Projectile* p);
void FUN_080af70c(struct Projectile* p);
static void FUN_080af2b0(struct Projectile* p);

static void PhantomProjectile_Init(struct Projectile* p) {
  // clang-format off
  static const ProjectileFunc sInitializers[6] = {
    FUN_080af114,
    FUN_080af1b4,
    FUN_080af214,
    FUN_080af250,
    FUN_080af70c,
    FUN_080af2b0,
  };
  // clang-format on
  (sInitializers[(p->s).work[0]])(p);
}

static void FUN_080af114(struct Projectile* p) {
  if (((p->s).unk_28)->mode[0] > 1) {
    (p->s).flags &= ~DISPLAY;
    (p->s).flags &= ~FLIPABLE;
    EXIT_BODY(p);
    SET_PROJECTILE_ROUTINE(p, ENTITY_DISAPPEAR);
  } else if (*((u16*)&((p->s).unk_28)->mode[2]) == 0x101) {
    SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
    (p->s).mode[1] = 0;
    InitNonAffineMotion(&p->s);
    (p->s).taskCol = 0x19;
    (p->s).flags |= DISPLAY;
    (p->s).flags |= FLIPABLE;
    SetMotion(&p->s, MOTION(0x86, 3));
    PhantomProjectile_Update(p);
  }
}

static void FUN_080af1b4(struct Projectile* p) {
  INIT_BODY(p, &sCollisions[0], 0, NULL);
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  (p->s).mode[1] = 0;
  InitRotatableMotion(&p->s);
  (p->s).flags |= DISPLAY;
  (p->s).flags |= FLIPABLE;
  PhantomProjectile_Update(p);
}

static void FUN_080af214(struct Projectile* p) {
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  (p->s).mode[1] = 0;
  InitRotatableMotion(&p->s);
  (p->s).flags |= DISPLAY;
  (p->s).flags |= FLIPABLE;
  PhantomProjectile_Update(p);
}

static void FUN_080af250(struct Projectile* p) {
  INIT_BODY(p, &sCollisions[4], 0, NULL);
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  (p->s).mode[1] = 0;
  InitNonAffineMotion(&p->s);
  (p->s).flags |= DISPLAY;
  (p->s).flags |= FLIPABLE;
  PhantomProjectile_Update(p);
}

static void FUN_080af2b0(struct Projectile* p) {
  INIT_BODY(p, &sCollisions[6], 0, NULL);
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  (p->s).flags &= ~DISPLAY;
  (p->s).flags |= FLIPABLE;
  PhantomProjectile_Update(p);
}

// --------------------------------------------

static void FUN_080af32c(struct Projectile* p);
void FUN_080af61c(struct Projectile* p);
void FUN_080af8b0(struct Projectile* p);
void FUN_080af9b0(struct Projectile* p);
void FUN_080af748(struct Projectile* p);
void FUN_080afb1c(struct Projectile* p);

static void PhantomProjectile_Update(struct Projectile* p) {
  // clang-format off
  static const ProjectileFunc sUpdates[6] = {
    FUN_080af32c,
    FUN_080af61c,
    FUN_080af8b0,
    FUN_080af9b0,
    FUN_080af748,
    FUN_080afb1c,
  };
  // clang-format on
  (sUpdates[(p->s).work[0]])(p);
  UpdateMotionGraphic(&p->s);
}

void FUN_080af368(struct Projectile* p);
void FUN_080af3ec(struct Projectile* p);
void FUN_080af46c(struct Projectile* p);

static void FUN_080af32c(struct Projectile* p) {
  static const ProjectileFunc PTR_ARRAY_0836d418[3] = {
      FUN_080af368,
      FUN_080af3ec,
      FUN_080af46c,
  };

  if (((p->s).unk_28)->mode[0] >= 2) {
    SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
    return;
  }
  (PTR_ARRAY_0836d418[(p->s).mode[1]])(p);
}

static const ProjectileFunc PTR_ARRAY_0836d430[2];
static const ProjectileFunc PTR_ARRAY_0836d438[2];
static const ProjectileFunc PTR_ARRAY_0836d440[3];
static const ProjectileFunc PTR_ARRAY_0836d44c[2];

INCASM("asm/projectile/phantom_p1_p1_p1.inc");

bool8 FUN_080afdf0(struct Entity* e, struct Coord* a, struct Coord* b, struct Coord* c);

void FUN_080af5cc(struct Projectile* p) {
  if (FUN_080afdf0((p->s).unk_28, &(p->s).coord, &(p->s).d, &(p->s).unk_coord)) {
    (p->s).mode[2] = 2;
  }
}

bool8 FUN_080afe38(struct Entity* e, struct Coord* a, struct Coord* b, struct Coord* c);

void FUN_080af5f4(struct Projectile* p) {
  if (FUN_080afe38((p->s).unk_28, &(p->s).coord, &(p->s).d, &(p->s).unk_coord)) {
    (p->s).mode[2] = 1;
  }
}

void FUN_080af61c(struct Projectile* p) {
  (PTR_ARRAY_0836d430[(p->s).mode[1]])(p);
}

void FUN_080af65c(struct Projectile* p);

void FUN_080af634(struct Projectile* p) {
  SetMotion(&p->s, MOTION(0x86, 5));
  (p->s).angle = (p->s).work[2] + 0x20;
  (p->s).mode[1] = 1;
  FUN_080af65c(p);
}

INCASM("asm/projectile/phantom_p1_p2_p2_p1.inc");

void FUN_080af70c(struct Projectile* p) {
  *(u32*)((u8*)p + 0x8c) = 0;
  *(u32*)((u8*)p + 0x90) = 0;
  *(u8*)((u8*)p + 0x94) = 0;
  (p->s).flags &= ~COLLIDABLE;
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  (p->s).mode[1] = 0;
  PhantomProjectile_Update(p);
}

void FUN_080af748(struct Projectile* p) {
  (PTR_ARRAY_0836d438[(p->s).mode[1]])(p);
}

INCASM("asm/projectile/phantom_p1_p3.inc");

void FUN_080af8b0(struct Projectile* p) {
  (PTR_ARRAY_0836d440[(p->s).mode[1]])(p);
}

void FUN_080af8e8(struct Projectile* p);


void FUN_080af8c8(struct Projectile* p) {
  SetMotion(&p->s, MOTION(0x86, 5));
  (p->s).mode[1] = 1;
  FUN_080af8e8(p);
}

INCASM("asm/projectile/phantom_p1_p4_p2.inc");

void nop_080af9ac(struct Projectile* p) {}


void FUN_080af9b0(struct Projectile* p) {
  (PTR_ARRAY_0836d44c[(p->s).mode[1]])(p);
}

void FUN_080af9f4(struct Projectile* p);

void FUN_080af9c8(struct Projectile* p) {
  SetMotion(&p->s, MOTION(0x86, 2));
  (p->s).angle = (p->s).work[2] + 0x20;
  (p->s).mode[1] = 1;
  (p->s).work[3] = 0;
  FUN_080af9f4(p);
}

INCASM("asm/projectile/phantom_p2_p2_p2.inc");

void FUN_080afb1c(struct Projectile* p) {
  if (((p->s).unk_28)->mode[0] > 1) {
    (p->s).flags &= ~DISPLAY;
    (p->s).flags &= ~FLIPABLE;
    EXIT_BODY(p);
    SET_PROJECTILE_ROUTINE(p, ENTITY_DISAPPEAR);
  }
}

INCASM("asm/projectile/phantom_p2_p2_p2_b.inc");

#include "entity/macros.h"

struct Projectile* FUN_080afbb0(struct Entity* e, u8 n) {
  struct Projectile* p = (struct Projectile*)AllocEntityLast(gProjectileHeaderPtr);

  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 40);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = n;
    (p->s).unk_28 = e;
  }
  return p;
}

#include "trig.h"

struct Projectile* FUN_080afbfc(struct Coord* c, s32 speed, u8 angle, u8 n) {
  struct Projectile* p = (struct Projectile*)AllocEntityLast(gProjectileHeaderPtr);

  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 40);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 1;
    (p->s).coord = *c;
    (p->s).d.x = Cos(angle, speed);
    (p->s).d.y = Sin(angle, speed);
    (p->s).work[2] = angle;
    (p->s).work[1] = n;
  }
  return p;
}

struct Projectile* FUN_080afc9c(struct Entity* e, u8 n) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);

  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 40);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 2;
    (p->s).work[2] = n;
    (p->s).unk_28 = e;
  }
  return p;
}

INCASM("asm/projectile/phantom_p2_p2_p2_d.inc");

struct Projectile* FUN_080afda4(struct Entity* e) {
  struct Projectile* p = (struct Projectile*)AllocEntityLast(gProjectileHeaderPtr);

  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 40);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 5;
    (p->s).unk_28 = e;
  }
  return p;
}

INCASM("asm/projectile/phantom_p2_p2_p2_e.inc");

void FUN_080af518(struct Projectile* p);
void FUN_080af5cc(struct Projectile* p);
void FUN_080af5f4(struct Projectile* p);

static const ProjectileFunc PTR_ARRAY_0836d424[3] = {
    FUN_080af518,
    FUN_080af5cc,
    FUN_080af5f4,
};

void FUN_080af634(struct Projectile* p);
void FUN_080af65c(struct Projectile* p);

static const ProjectileFunc PTR_ARRAY_0836d430[2] = {
    FUN_080af634,
    FUN_080af65c,
};

void FUN_080af760(struct Projectile* p);
void FUN_080af7b0(struct Projectile* p);

static const ProjectileFunc PTR_ARRAY_0836d438[2] = {
    FUN_080af760,
    FUN_080af7b0,
};

void FUN_080af8c8(struct Projectile* p);
void FUN_080af8e8(struct Projectile* p);
void nop_080af9ac(struct Projectile* p);

static const ProjectileFunc PTR_ARRAY_0836d440[3] = {
    FUN_080af8c8,
    FUN_080af8e8,
    nop_080af9ac,
};

void FUN_080af9c8(struct Projectile* p);
void FUN_080af9f4(struct Projectile* p);

static const ProjectileFunc PTR_ARRAY_0836d44c[2] = {
    FUN_080af9c8,
    FUN_080af9f4,
};
