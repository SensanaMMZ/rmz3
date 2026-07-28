#include "collision.h"
#include "global.h"
#include "projectile.h"

// MinigameCopyX?

static const ProjectileFunc PTR_ARRAY_0836d7cc[4];

struct Projectile* FUN_080b18d4(struct Coord* c1, struct Coord* c2, u8 a2) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 45);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 0;
    (p->s).work[1] = a2;
    (p->s).coord.x = c1->x;
    (p->s).coord.y = c1->y;
    (p->s).unk_coord.x = c2->x;
    (p->s).unk_coord.y = c2->y;
  }
  return p;
}

struct Projectile* FUN_080b1934(struct Entity* e, struct Coord* c, u8 a2) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 45);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 1;
    (p->s).work[1] = a2;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
    (p->s).unk_28 = e;
  }
  return p;
}

struct Projectile* FUN_080b1990(struct Entity* e, struct Coord* c, u8 a2) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 45);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 2;
    (p->s).work[1] = a2;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
    (p->s).unk_28 = e;
  }
  return p;
}

struct Projectile* FUN_080b19ec(struct Entity* e, struct Coord* c, u8 a2) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 45);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 3;
    (p->s).work[1] = a2;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
    (p->s).unk_28 = e;
  }
  return p;
}

INCASM("asm/projectile/unk_45_p1_p5.inc");

void FUN_080b1b28(struct Projectile* p) {
  (PTR_ARRAY_0836d7cc[(p->s).mode[1]])(p);
}

void FUN_080b1b40(struct Projectile* p) {
  (p->s).flags &= ~DISPLAY;
  EXIT_BODY(p);
  SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}

INCASM("asm/projectile/unk_45_p2_p1.inc");

// 1 insn from matching: retail keeps the work[1] load in r0 and copies it
// into the a register; agbcc coalesces the copy away (allocation tie).
NON_MATCH void FUN_080b2178(struct Body* body) {
#if MODERN
  u8 win = 0;
  struct CollidableEntity* parent = body->parent;
  struct CollidableEntity* other = (body->enemy)->parent;
  u32 a;
  if (((struct Entity*)parent)->work[1] == 0 && ((struct Entity*)other)->work[1] == 2) {
    win = 1;
  }
  a = ((struct Entity*)parent)->work[1];
  if (a == 1 && ((struct Entity*)other)->work[1] == 0) {
    win = 1;
  }
  if (a == 2 && ((struct Entity*)other)->work[1] == 1) {
    win = 1;
  }
  *(u8*)((u8*)parent + 0xbc) = 1;
  if (win == 1) {
    *(u8*)((u8*)parent + 0xbc) = win;
  }
#else
  INCCODE("asm/projectile/unk_45_2178.inc");
#endif
}

// 1 insn from matching: retail keeps the work[1] load in r0 and copies it
// into the a register; agbcc coalesces the copy away (allocation tie).
NON_MATCH void FUN_080b21c0(struct Body* body) {
#if MODERN
  u8 win = 0;
  struct CollidableEntity* parent = body->parent;
  struct CollidableEntity* other = (body->enemy)->parent;
  u32 a;
  if (((struct Entity*)other)->work[1] == 0 && ((struct Entity*)parent)->work[1] == 2) {
    win = 1;
  }
  a = ((struct Entity*)other)->work[1];
  if (a == 1 && ((struct Entity*)parent)->work[1] == 0) {
    win = 1;
  }
  if (a == 2 && ((struct Entity*)parent)->work[1] == 1) {
    win = 1;
  }
  if (win == 1) {
    *(u8*)((u8*)parent + 0xbc) = win;
  }
#else
  INCCODE("asm/projectile/unk_45_21c0.inc");
#endif
}

void FUN_080b2204(struct Body* body) {
  struct CollidableEntity* parent = body->parent;
  if ((body->enemy->processing)->faction == 0) {
    *(u8*)((u8*)parent + 0xbc) = 1;
  }
}

void FUN_080b1a48(struct Projectile* p);
void FUN_080b1b28(struct Projectile* p);
void FUN_080b1b40(struct Projectile* p);

// clang-format off
const ProjectileRoutine gProjectile45Routine = {
    [ENTITY_INIT] =      FUN_080b1a48,
    [ENTITY_UPDATE] =    FUN_080b1b28,
    [ENTITY_DIE] =       FUN_080b1b40,
    [ENTITY_DISAPPEAR] = DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};
// clang-format on

void FUN_080b1b7c(struct Projectile* p);
void FUN_080b1cbc(struct Projectile* p);
void FUN_080b1f00(struct Projectile* p);
void FUN_080b2044(struct Projectile* p);

// clang-format off
static const ProjectileFunc PTR_ARRAY_0836d7cc[4] = {
    FUN_080b1b7c,
    FUN_080b1cbc,
    FUN_080b1f00,
    FUN_080b2044,
};
// clang-format on

static const struct Collision Collision_ARRAY_0836d7dc[8] = {
    {
      kind : DDP,
      faction : FACTION_ALLY,
      damage : 2,
      element : ELEMENT_FLAME,
      remaining : 0,
      layer : 0x00000004,
      range : {PIXEL(0), PIXEL(0), PIXEL(16), PIXEL(16)},
    },
    {
      kind : DDP,
      faction : FACTION_ALLY,
      damage : 2,
      element : ELEMENT_THUNDER,
      remaining : 0,
      layer : 0x00000002,
      range : {PIXEL(0), PIXEL(0), PIXEL(16), PIXEL(16)},
    },
    {
      kind : DDP,
      faction : FACTION_ALLY,
      damage : 2,
      element : ELEMENT_ICE,
      remaining : 0,
      layer : 0x00000008,
      range : {PIXEL(0), PIXEL(0), PIXEL(16), PIXEL(16)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      layer : 0x000A5294,
      range : {PIXEL(8), PIXEL(8), PIXEL(16), PIXEL(16)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      layer : 0x0046318C,
      range : {PIXEL(8), PIXEL(8), PIXEL(16), PIXEL(16)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      layer : 0x004C6318,
      range : {PIXEL(8), PIXEL(8), PIXEL(16), PIXEL(16)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 2,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(22), PIXEL(28), PIXEL(44)},
    },
    {
      kind : DDP,
      faction : FACTION_NEUTRAL,
      damage : 255,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(16), PIXEL(16)},
    },
};
