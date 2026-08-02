#include "collision.h"
#include "global.h"
#include "projectile.h"

static const ProjectileFunc PTR_ARRAY_0836d8b0[3];
static const ProjectileFunc PTR_ARRAY_0836d8bc[3];
static const ProjectileFunc PTR_ARRAY_0836d8c8[3];

struct Projectile* FUN_080b221c(struct Entity* e, u8 a1, u8 a2) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 46);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).unk_28 = e;
    (p->s).work[0] = a1;
    (p->s).work[1] = a2;
  }
  return p;
}

struct Projectile* FUN_080b2270(struct Entity* e, struct Entity* e2, u8 a2, u8 a3) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 46);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).unk_28 = e;
    (p->s).unk_2c = e2;
    (p->s).work[0] = a2;
    (p->s).work[1] = a3;
  }
  return p;
}

void FUN_080b22c8(struct Projectile* p) {
  (PTR_ARRAY_0836d8b0[(p->s).work[0]])(p);
}


void FUN_080b22e0(struct Projectile* p) {
  (PTR_ARRAY_0836d8bc[(p->s).work[0]])(p);
}


void FUN_080b22f8(struct Projectile* p) {
  (PTR_ARRAY_0836d8c8[(p->s).work[0]])(p);
}

void FUN_080b2310(struct Projectile* p) {
  InitNonAffineMotion(&p->s);
  (p->s).flags |= DISPLAY;
  (p->s).flags |= FLIPABLE;
  SetMotion(&p->s, MOTION(SM234_UNK, 0));
  UpdateMotionGraphic(&p->s);
  SET_XFLIP(p, FALSE);
  ((p->s).coord).x = PIXEL(((p->s).work[1] * 32) + 24);
  ((p->s).coord).y = PIXEL(0);
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  FUN_080b22e0(p);
}

// 0x080b2384
void FUN_080b2384(struct Projectile* p) {
  register struct Entity* q asm("r6");
  q = (p->s).unk_28;
  InitNonAffineMotion(&p->s);
  (p->s).flags |= DISPLAY;
  (p->s).flags |= FLIPABLE;
  SetMotion(&p->s, MOTION(0xE9, 0x02));
  UpdateMotionGraphic(&p->s);
  ForceEntityPalette(&p->s, (p->s).work[1] + 5);
  SET_XFLIP(p, FALSE);
  ((p->s).coord).x = PIXEL(((p->s).work[1] * 32) + 8);
  ((p->s).coord).y = PIXEL(0x78);
  {
    register u8* a asm("r0");
    register u8 w asm("r1");
    a = (u8*)q + 0xDE9;
    w = (p->s).work[1];
    asm("" : "+r"(a));
    a += w;
    (p->s).work[2] = *a;
  }
  (p->s).unk_2c = (struct Entity*)FUN_080b2270(q, &p->s, 2, (p->s).work[1]);
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  FUN_080b22e0(p);
}

// 0x080b2428
void FUN_080b2428(struct Projectile* p) {
  struct Entity* q = (p->s).unk_28;
  InitNonAffineMotion(&p->s);
  (p->s).flags |= DISPLAY;
  (p->s).flags |= FLIPABLE;
  SetMotion(&p->s, MOTION(0xE9, 0x05));
  UpdateMotionGraphic(&p->s);
  ForceEntityPalette(&p->s, (p->s).work[1] + 5);
  (p->s).taskCol = 9;
  SET_XFLIP(p, FALSE);
  ((p->s).coord).x = PIXEL(((p->s).work[1] * 32) + 8);
  ((p->s).coord).y = PIXEL(0x78);
  {
    u8* a = (u8*)q + 0xDE9;
    asm("" : "+r"(a));
    a += (p->s).work[1];
    (p->s).work[2] = *a;
  }
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  FUN_080b22e0(p);
}

struct Enemy* FUN_0809bdd4(struct Entity* e, u8 a1, u8 a2);

// 0x080B24C8
void FUN_080b24c8(struct Projectile* p) {
  struct Entity* q = (p->s).unk_28;
  switch ((p->s).mode[1]) {
    case 0: {
      u8 w1 = (p->s).work[1];
      register u8* t asm("r0");
      register u8* t2 asm("r2");
      u8 v;
      t = (u8*)q + 0xDE4;
      t2 = t + w1;
      v = *t2;
      if (v != 0xFF) {
        struct Entity* r;
        u8 v2;
        asm volatile("add %0, %1, #0" : "=&l"(v2) : "l"(v));
        r = (struct Entity*)FUN_0809bdd4(q, w1, v2);
        (p->s).unk_2c = r;
        if (r != NULL) {
          *((u8*)q + 0xE12) = 1;
          (p->s).mode[1]++;
        }
      }
      break;
    }
    case 1:
      if (((p->s).unk_2c)->mode[1] > 1) {
        SetMotion(&p->s, MOTION(0xEA, 0x01));
        PlaySound(0x139);
        (p->s).mode[1]++;
      }
      /* fallthrough */
    case 2:
      if (((p->s).unk_2c)->coord.y > 0x1000) {
        SetMotion(&p->s, MOTION(0xEA, 0x02));
        (p->s).mode[1]++;
      }
      break;
    case 3:
      if ((p->s).motion.state == 3) {
        u8* t = (u8*)q + 0xDE4;
        t[(p->s).work[1]] = 0xFF;
        (p->s).mode[1] = 0;
      }
      break;
  }
  UpdateMotionGraphic(&p->s);
}

INCASM("asm/projectile/unk_46_p4_p1_b.inc");

void FUN_080b274c(struct Projectile* p) {
  SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}


void FUN_080b2764(struct Projectile* p) {
  SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}


void FUN_080b277c(struct Projectile* p) {
  SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}


void FUN_080b22c8(struct Projectile* p);
void FUN_080b22e0(struct Projectile* p);
void FUN_080b22f8(struct Projectile* p);

// clang-format off
const ProjectileRoutine gProjectile46Routine = {
    [ENTITY_INIT] =      FUN_080b22c8,
    [ENTITY_UPDATE] =    FUN_080b22e0,
    [ENTITY_DIE] =       FUN_080b22f8,
    [ENTITY_DISAPPEAR] = DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};
// clang-format on

void FUN_080b2310(struct Projectile* p);
void FUN_080b2384(struct Projectile* p);
void FUN_080b2428(struct Projectile* p);

// clang-format off
static const ProjectileFunc PTR_ARRAY_0836d8b0[3] = {
    FUN_080b2310,
    FUN_080b2384,
    FUN_080b2428,
};
// clang-format on

void FUN_080b24c8(struct Projectile* p);
void FUN_080b258c(struct Projectile* p);
void FUN_080b2654(struct Projectile* p);

// clang-format off
static const ProjectileFunc PTR_ARRAY_0836d8bc[3] = {
    FUN_080b24c8,
    FUN_080b258c,
    FUN_080b2654,
};
// clang-format on

void FUN_080b274c(struct Projectile* p);
void FUN_080b2764(struct Projectile* p);
void FUN_080b277c(struct Projectile* p);

// clang-format off
static const ProjectileFunc PTR_ARRAY_0836d8c8[3] = {
    FUN_080b274c,
    FUN_080b2764,
    FUN_080b277c,
};
// clang-format on
