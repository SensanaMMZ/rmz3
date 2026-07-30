#include "collision.h"
#include "global.h"
#include "projectile.h"
#include "stagerun.h"
#include "trig.h"
#include "vfx.h"

static const ProjectileFunc sUpdates1[7];
static const ProjectileFunc sUpdates2[7];
static const struct Collision sCollisions[5];
static const u8 u8_0836b0c8[6];

void Projectile13_Update(struct Projectile* p);

void FUN_0809f8ac(struct Entity* e) {
  s32 i;
  for (i = 0; i <= 3; i++) {
    struct Projectile* p = (struct Projectile*)AllocEntityLast(gProjectileHeaderPtr);
    if (p != NULL) {
      (p->s).taskCol = 8;
      INIT_PROJECTILE_ROUTINE(p, 13);
      (p->s).tileNum = 0;
      (p->s).palID = 0;
      (p->s).work[0] = 5;
      (p->s).work[2] = i;
      (p->s).unk_28 = e;
    }
  }
}

void FUN_0809f8fc(s32 x, s32 y, u8 angle) {
  struct Projectile* p = (struct Projectile*)AllocEntityLast(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 13);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 0;
    (p->s).coord.x = x;
    (p->s).coord.y = y;
    (p->s).d.x = COS(angle) * 2;
    (p->s).d.y = -(SIN(angle) * 2);
  }
}

void FUN_0809f970(s32 x, s32 y, u8 n) {
  struct Projectile* p = (struct Projectile*)AllocEntityLast(gProjectileHeaderPtr);

  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 13);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 1;
    (p->s).work[2] = n;
    (p->s).unk_coord.x = x;
    (p->s).unk_coord.y = y;
    (p->s).coord.x = x - 0x400 + (RANDOM(RNG_0202f388) & 0x7FF);
    (p->s).coord.y = y;
  }
}

#include "entity/macros.h"

void babyelf_0809f9f0(struct Entity* parent, s32 x, s32 y, u8 n) {
  struct Projectile* p = (struct Projectile*)AllocEntityLast(gProjectileHeaderPtr);

  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 13);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 2;
    (p->s).coord.x = x;
    (p->s).coord.y = y;
    (p->s).work[2] = n;
    (p->s).unk_28 = parent;
  }
}


void FUN_0809fa44(struct Entity* parent, s32 x, s32 y, u8 n) {
  struct Projectile* p = (struct Projectile*)AllocEntityLast(gProjectileHeaderPtr);

  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 13);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 3;
    (p->s).work[2] = n;
    (p->s).unk_coord.x = x;
    (p->s).unk_coord.y = y;
    (p->s).coord.x = x;
    (p->s).coord.y = y;
    (p->s).unk_28 = parent;
  }
}

void FUN_0809fa9c(struct Entity* parent, s32 x, s32 y, u8 n) {
  struct Projectile* p = (struct Projectile*)AllocEntityLast(gProjectileHeaderPtr);

  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 13);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 4;
    (p->s).work[2] = n;
    (p->s).coord.x = x;
    (p->s).coord.y = y;
    (p->s).unk_28 = parent;
  }
}

void nop_0809faf0(struct Projectile* p) {}

void Projectile13_Init(struct Projectile* p) {
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  (p->s).mode[1] = u8_0836b0c8[(p->s).work[0]];
  (p->s).flags |= FLIPABLE;
  (p->s).flags |= DISPLAY;
  InitNonAffineMotion(&p->s);
  INIT_BODY(p, sCollisions, 1, (void*)nop_0809faf0);
  Projectile13_Update(p);
}

void Projectile13_Update(struct Projectile* p) {
  (sUpdates1[(p->s).mode[1]])(p);
  (sUpdates2[(p->s).mode[1]])(p);
}

void Projectile13_Die(struct Projectile* p) {
  EXIT_BODY(p);
  CreateSmoke(3, &(p->s).coord);
  SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}


void nop_0809fbd8(struct Projectile* p) {}

void FUN_0809fbdc(struct Projectile* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SetDDP(&p->body, sCollisions);
      (p->s).work[2] = 0x28;
      SetMotion(&p->s, MOTION(0x33, 0x08));
      (p->s).mode[2]++;
      /* fallthrough */
    case 1: {
      s32 t = (p->s).work[2] - 1;
      (p->s).work[2] = t;
      if ((t << 24) == 0) {
        (p->s).mode[2]++;
      }
      (p->s).coord.x += (p->s).d.x;
      (p->s).coord.y += (p->s).d.y;
      UpdateMotionGraphic(&p->s);
      break;
    }
    case 2:
      EXIT_BODY(p);
      (p->s).work[2] = 0xA;
      (p->s).mode[2]++;
      /* fallthrough */
    case 3: {
      u32 u;
      register s32 f asm("r0");
      register s32 tzp asm("r2");
      {
        register s32 w asm("r0");
        w = (p->s).work[2];
        asm("" : "+r"(w));
        u = w;
      }
      if (u > 4) {
        if (u & 1) {
          u8 fl2 = (p->s).flags;
          f = DISPLAY;
          asm("" : "+r"(f));
          f |= fl2;
        } else {
          goto off;
        }
        goto store;
      }
      if (u & 2) {
        u8 fl2 = (p->s).flags;
        f = DISPLAY;
        f |= fl2;
      } else {
      off: {
          u8 fl3 = (p->s).flags;
          f = 0xFE;
          f &= fl3;
        }
      }
    store:
      (p->s).flags = f;
      {
        register s32 t2p asm("r0");
        t2p = u - 1;
        (p->s).work[2] = t2p;
        tzp = (u8)t2p;
      }
      if (tzp == 0) {
        register u8 e1 asm("r1");
        e1 = *(volatile u8*)&(p->s).flags;
        f = 0xFE;
        f &= e1;
        {
          register s32 c2 asm("r1");
          c2 = 0xFD;
          f &= c2;
        }
        (p->s).flags = f;
        (p->body).status = tzp;
        (p->body).prevStatus = tzp;
        (p->body).invincibleTime = tzp;
        (p->s).flags &= ~COLLIDABLE;
        SET_PROJECTILE_ROUTINE(p, ENTITY_DISAPPEAR);
      }
      (p->s).coord.x += (p->s).d.x;
      (p->s).coord.y += (p->s).d.y;
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}

INCASM("asm/projectile/unk_13_p3a.inc");

s32 PushoutToUp1(s32 x, s32 y);
void FUN_080bc6ac(struct Entity* e, s32 x, s32 y, s32 speed, u8 angle);
void FUN_080bc758(s32 x, s32 y);

void FUN_080a025c(struct Projectile* p) {
  struct Entity* par = (p->s).unk_28;
  switch ((p->s).mode[2]) {
    case 0:
      (p->s).taskCol = 0x18;
      SetDDP(&p->body, &sCollisions[3]);
      SetMotion(&p->s, 0x3401);
      (p->s).mode[2]++;
      /* fallthrough */
    case 1:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 3) {
        (p->s).mode[2]++;
      }
      break;
    case 2:
      (p->s).work[3] = 1;
      SetMotion(&p->s, 0x3402);
      (p->s).mode[2]++;
      /* fallthrough */
    case 3: {
      u8 w2 = (p->s).work[2];
      if (w2 <= 1) {
        u8 w3 = (p->s).work[3];
        if (w3 != 0) {
          s32 t = w3 - 1;
          (p->s).work[3] = t;
          if ((t << 24) == 0) {
            FUN_0809fa44(par, (p->s).unk_coord.x, (p->s).unk_coord.y, (u8)(w2 + 1));
          }
        }
      }
      (p->s).coord.y += 0x280;
      {
        s32 po = PushoutToUp1((p->s).coord.x, (p->s).coord.y);
        if (po < 0) {
          (p->s).coord.y += po;
          {
            u32 f = (p->s).flags & 0xFE;
            s32 z2 = 0;
            asm("" : "+r"(f));
            f &= 0xFD;
            (p->s).flags = f;
            (p->body).status = z2;
            (p->body).prevStatus = z2;
            (p->body).invincibleTime = z2;
          }
          (p->s).flags &= 0xFB;
          SET_PROJECTILE_ROUTINE(p, ENTITY_DISAPPEAR);
          if ((p->s).work[2] == 0) {
            u32 ang = 0x20000000;
            s32 i = 2;
            do {
              FUN_080bc6ac(par, (p->s).coord.x, (p->s).coord.y, 0x100, ang >> 0x18);
              ang += 0x20000000;
              i--;
            } while (i >= 0);
            FUN_080bc758((p->s).coord.x, (p->s).coord.y);
          }
          FUN_0809fa9c(par, (p->s).coord.x, (p->s).coord.y, 0);
          FUN_0809fa9c(par, (p->s).coord.x, (p->s).coord.y, 1);
        }
      }
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}

void FUN_080a03ac(struct Projectile* p) {
  s32 m = (p->s).mode[2];
  switch (m) {
    case 0:
      (p->s).taskCol = 0x18;
      SetDDP(&p->body, &sCollisions[3]);
      SetMotion(&p->s, 0x3403);
      (p->s).d.x = ((p->s).work[2] * 7 << 8) - 0x380;
      (p->s).d.y = m;
      (p->s).mode[2]++;
      /* fallthrough */
    case 1:
      (p->s).coord.x += (p->s).d.x;
      {
        struct Camera* cam = &gStageRun.vm.camera;
        if (CalcFromCamera(cam, &(p->s).coord) > 0x2000) {
          register u8 e1 asm("r1");
          register s32 fp asm("r0");
          register s32 z2 asm("r2");
          e1 = (p->s).flags;
          fp = 0xFE;
          fp &= e1;
          z2 = 0;
          {
            register s32 c2 asm("r1");
            c2 = 0xFD;
            fp &= c2;
          }
          (p->s).flags = fp;
          (p->body).status = z2;
          (p->body).prevStatus = z2;
          (p->body).invincibleTime = z2;
          (p->s).flags &= ~COLLIDABLE;
          SET_PROJECTILE_ROUTINE(p, ENTITY_DISAPPEAR);
        }
      }
      UpdateMotionGraphic(&p->s);
      break;
  }
  if (((p->s).unk_28)->mode[0] > 1) {
    register s32 f asm("r0");
    s32 t = (p->s).d.y + 1;
    (p->s).d.y = t;
    if (t > 0xf) {
      if ((t & 2) != 0) {
        goto fset;
      }
      goto fclear;
    }
    if ((t & 1) == 0) {
      goto fclear;
    }
  fset:
    {
      u8 fl2 = (p->s).flags;
      f = 1;
      f |= fl2;
      goto fst;
    }
  fclear:
    {
      u8 fl3 = (p->s).flags;
      f = 0xFE;
      f &= fl3;
    }
  fst:
    (p->s).flags = f;
    if ((p->s).d.y > 0x1e) {
      register u8 e1 asm("r1");
      register s32 fp asm("r0");
      register s32 z2 asm("r2");
      e1 = *(volatile u8*)&(p->s).flags;
      fp = 0xFE;
      fp &= e1;
      z2 = 0;
      {
        register s32 c2 asm("r1");
        c2 = 0xFD;
        fp &= c2;
      }
      (p->s).flags = fp;
      (p->body).status = z2;
      (p->body).prevStatus = z2;
      (p->body).invincibleTime = z2;
      (p->s).flags &= ~COLLIDABLE;
      SET_PROJECTILE_ROUTINE(p, ENTITY_DISAPPEAR);
    }
  }
}

INCASM("asm/projectile/unk_13_p3_b.inc");


void Projectile13_Init(struct Projectile* p);
void Projectile13_Update(struct Projectile* p);
void Projectile13_Die(struct Projectile* p);

// clang-format off
const ProjectileRoutine gProjectile13Routine = {
    [ENTITY_INIT] =      Projectile13_Init,
    [ENTITY_UPDATE] =    Projectile13_Update,
    [ENTITY_DIE] =       Projectile13_Die,
    [ENTITY_DISAPPEAR] = DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

void nop_0809fbd8(struct Projectile* p);

// clang-format off
static const ProjectileFunc sUpdates1[7] = {
    nop_0809fbd8,
    nop_0809fbd8,
    nop_0809fbd8,
    nop_0809fbd8,
    nop_0809fbd8,
    nop_0809fbd8,
    nop_0809fbd8,
};
// clang-format on

// --------------------------------------------

void FUN_0809fbdc(struct Projectile* p);
void FUN_0809fcfc(struct Projectile* p);
void FUN_0809ff74(struct Projectile* p);
void FUN_080a025c(struct Projectile* p);
void FUN_080a03ac(struct Projectile* p);
void FUN_080a04d4(struct Projectile* p);
void FUN_080a06c0(struct Projectile* p);

// clang-format off
static const ProjectileFunc sUpdates2[7] = {
    FUN_0809fbdc,
    FUN_0809fcfc,
    FUN_0809ff74,
    FUN_080a025c,
    FUN_080a03ac,
    FUN_080a04d4,
    FUN_080a06c0,
};
// clang-format on

// --------------------------------------------

static const struct Collision sCollisions[5] = {
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(10), PIXEL(10)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 255,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(8), PIXEL(8)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(16), PIXEL(16)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(14), PIXEL(14)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(10), PIXEL(10)},
    },
};

static const u8 u8_0836b0c8[6] = {0, 1, 2, 3, 4, 5};

static const motion_t sMotions[4] = {
    MOTION(0x30, 0x00),
    MOTION(0x20, 0x00),
    MOTION(0xE0, 0x00),
    MOTION(0xD0, 0x00),
};

static const s16 s16_ARRAY_0836b0d6[4] = {
    0x30,
    0x90,
    0xC0,
    0x60,
};
