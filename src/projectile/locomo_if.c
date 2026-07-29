#include "collision.h"
#include "global.h"
#include "zero.h"
#include "projectile.h"
#include "vfx.h"

// LocomoIF

static const ProjectileFunc sUpdates1[];
static const ProjectileFunc sUpdates2[];
static const struct Collision sCollisions[4];
static const u8 u8_ARRAY_0836bec4[2];

void Projectile23_Update(struct Projectile* p);

void FUN_080a7c60(s32 x, s32 y, u8 a2) {
  struct Projectile* p = (struct Projectile*)AllocEntityLast(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 23);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 0;
    (p->s).coord.x = x;
    (p->s).coord.y = y;
    (p->s).work[2] = a2;
  }
}

void FUN_080a7cb0(s32 x, s32 y, u8 a2) {
  struct Projectile* p = (struct Projectile*)AllocEntityLast(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 23);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 1;
    (p->s).coord.x = x;
    (p->s).coord.y = y;
    (p->s).work[2] = a2;
  }
}

void FUN_080a7d00(struct Enemy* p) {}

void Projectile23_Init(struct Projectile* p) {
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  (p->s).mode[1] = u8_ARRAY_0836bec4[(p->s).work[0]];
  (p->s).flags |= FLIPABLE;
  (p->s).flags |= DISPLAY;
  InitNonAffineMotion(&p->s);
  INIT_BODY(p, sCollisions, 1, (void*)FUN_080a7d00);
  Projectile23_Update(p);
}

void Projectile23_Update(struct Projectile* p) {
  (sUpdates1[(p->s).mode[1]])(p);
  (sUpdates2[(p->s).mode[1]])(p);
}

void Projectile23_Die(struct Projectile* p) {
  EXIT_BODY(p);
  CreateSmoke(3, &(p->s).coord);
  SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}

void FUN_080a7de8(struct Projectile* p) {}


void FUN_080a7dec(struct Projectile* p) {
  if ((p->body).status & BODY_STATUS_BINDING) {
    (p->s).mode[1] = 2;
    (p->s).mode[2] = 0;
  }
}

static const motion_t sMotions[4];
void FUN_080b7ffc(struct Entity* e, struct Coord* c, motion_t* motions, u8 len);

void FUN_080a7e0c(struct Projectile* p) {
  struct Coord c;
  u32* st = &(p->body).status;
  if (*st & BODY_STATUS_BINDING) {
    if (!((pZero2->body).status & BODY_STATUS_WHITE)) {
      return;
    }
  }
  c.x = (p->s).coord.x;
  c.y = (p->s).coord.y - PIXEL(16);
  FUN_080b7ffc(&p->s, &c, (motion_t*)sMotions, 4);
  PlaySound(0x3F);
  {
    u8 f = (p->s).flags & ~DISPLAY;
    s32 z = 0;
    f &= ~FLIPABLE;
    (p->s).flags = f;
    *st = z;
    (p->body).prevStatus = z;
    (p->body).invincibleTime = z;
    (p->s).flags &= ~COLLIDABLE;
  }
  SET_PROJECTILE_ROUTINE(p, ENTITY_DISAPPEAR);
}

INCASM("asm/projectile/locomo_if_post_p2.inc");

void FUN_080a7f70(struct Projectile* p) {
  s32 md = (p->s).mode[2];
  switch (md) {
    case 0:
      SetDDP(&p->body, &sCollisions[1]);
      (p->s).d.x = (p->s).work[2] * 0x240 - 0x120;
      (p->s).d.y = 0xE0;
      (p->s).work[2] = 0x40;
      SetMotion(&p->s, MOTION(0x56, 0x00));
      (p->s).mode[2]++;
      /* fallthrough */
    case 1: {
      s32 t;
      (p->s).coord.x += (p->s).d.x;
      {
        s32 cy = (p->s).coord.y;
        s32 v = (p->s).d.y;
        (p->s).coord.y = cy + v;
        (p->s).d.y = v - 2;
      }
      UpdateMotionGraphic(&p->s);
      t = (p->s).work[2] - 1;
      (p->s).work[2] = t;
      if ((t << 24) == 0) {
        (p->s).mode[2]++;
      }
      break;
    }
    case 2:
      (p->s).coord.x += (p->s).d.x;
      {
        s32 cy = (p->s).coord.y;
        s32 v = (p->s).d.y;
        (p->s).coord.y = cy + v;
        (p->s).d.y = v - 2;
      }
      EXIT_BODY(p);
      SetMotion(&p->s, MOTION(0x56, 0x01));
      (p->s).mode[2]++;
      /* fallthrough */
    case 3: {
      u8 st;
      UpdateMotionGraphic(&p->s);
      st = (p->s).motion.state;
      if (st == 3) {
        (p->s).flags &= ~DISPLAY;
        (p->s).flags &= ~FLIPABLE;
        EXIT_BODY(p);
        {
          u32 tb = (u32)gProjectileFnTable;
          const ProjectileRoutine** ta = (const ProjectileRoutine**)(tb + (p->s).id * 4);
          *(u32*)&(p->s).mode[0] = st;
          (p->s).onUpdate = (void*)(**ta)[ENTITY_DISAPPEAR];
        }
      }
      break;
    }
  }
}

// 0x080a8080 -- parked (allocation cascade): retail holds &pZero2 in r2
// and reloads the 0x143 offset pool per RMW (its byte temp overwrites the
// offset reg); agbcc caches the offset and parks &pZero2 in r5, pushing p
// to r6. One insn shorter, several regs shuffled; pins cascade.
NON_MATCH void FUN_080a8080(struct Projectile* p) {
#if MODERN
  u8 m = (p->s).mode[2];
  switch (m) {
    case 0:
      PlaySound(0x40);
      (p->s).work[2] = m;
      SetDDP(&p->body, &sCollisions[2]);
      SetMotion(&p->s, MOTION(0x58, 0x00));
      (p->s).mode[2]++;
      /* fallthrough */
    case 1: {
      s32 one;
      s32 t;
      one = 1;
      *((u8*)pZero2 + 0x143) = (*((u8*)pZero2 + 0x143) & ~0xF) | one;
      *((u8*)pZero2 + 0x143) = *((u8*)pZero2 + 0x143) & 0xF;
      t = (p->s).work[2] + 1;
      (p->s).work[2] = t;
      if (t & 1) {
        (p->s).flags |= one;
      } else {
        (p->s).flags &= 0xFE;
      }
      (p->s).coord.x = (pZero2->s).coord.x;
      (p->s).coord.y = (pZero2->s).coord.y;
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
#else
  INCCODE("asm/projectile/locomo_8080.inc");
#endif
}

void Projectile23_Init(struct Projectile* p);
void Projectile23_Update(struct Projectile* p);
void Projectile23_Die(struct Projectile* p);

// clang-format off
const ProjectileRoutine gProjectile23Routine = {
    [ENTITY_INIT] =      Projectile23_Init,
    [ENTITY_UPDATE] =    Projectile23_Update,
    [ENTITY_DIE] =       Projectile23_Die,
    [ENTITY_DISAPPEAR] = DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

void FUN_080a7dec(struct Projectile* p);
void FUN_080a7de8(struct Projectile* p);
void FUN_080a7e0c(struct Projectile* p);

static const ProjectileFunc sUpdates1[] = {
    FUN_080a7dec,
    FUN_080a7de8,
    FUN_080a7e0c,
};

void FUN_080a7e9c(struct Projectile* p);
void FUN_080a7f70(struct Projectile* p);
void FUN_080a8080(struct Projectile* p);

static const ProjectileFunc sUpdates2[] = {
    FUN_080a7e9c,
    FUN_080a7f70,
    FUN_080a8080,
};

// --------------------------------------------

static const struct Collision sCollisions[4] = {
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 255,
      unk_0a : 0x41,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(2), PIXEL(16), PIXEL(16)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(6), PIXEL(17), PIXEL(21)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 255,
      unk_0a : 0x41,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(64), PIXEL(64)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(2), PIXEL(16), PIXEL(16)},
    },
};

static const u8 u8_ARRAY_0836bec4[2] = {0, 1};

static const motion_t sMotions[4] = {
    MOTION(SM088_LOCOMO_IF_ICE, 1),
    MOTION(SM088_LOCOMO_IF_ICE, 2),
    MOTION(SM088_LOCOMO_IF_ICE, 3),
    MOTION(SM088_LOCOMO_IF_ICE, 4),
};
