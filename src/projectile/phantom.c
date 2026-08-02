#include "stagerun.h"
#include "collision.h"
#include "global.h"
#include "physics.h"
#include "entity/macros.h"
#include "projectile.h"
#include "vfx.h"

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

// 0x080af368
void FUN_080af368(struct Projectile* p) {
  struct Entity* q = (p->s).unk_28;
  s32 x = (q->coord).x;
  s32 y = (q->coord).y;
  s32 t = (q->flags >> 4) & 1;
  s32 d;
  SET_XFLIP(p, t);
  d = -1;
  if (t == 0) {
    d = 1;
  }
  (p->s).coord.x = x + d * PIXEL(16);
  (p->s).coord.y = y - PIXEL(28);
  if ((p->s).motion.state == 3) {
    (p->s).mode[1] = 1;
    SetMotion(&p->s, MOTION(0x86, 0x01));
  }
}

void FUN_080af46c(struct Projectile* p);

void FUN_080af3ec(struct Projectile* p) {
  struct Entity* q = (p->s).unk_28;
  if (q->mode[3] > 2) {
    (p->s).mode[1] = 2;
    (p->s).mode[2] = 0;
    FUN_080af46c(p);
  } else {
    s32 x = q->coord.x;
    s32 y = q->coord.y;
    s32 t = (q->flags >> 4) & 1;
    s16 v = t;
    s32 d;
    if (v) {
      (p->s).flags |= X_FLIP;
    } else {
      (p->s).flags &= ~X_FLIP;
    }
    {
      s16 w = v;
      (p->s).spr.xflip = w;
      (p->s).spr.oam.xflip = w;
    }
    d = -1;
    if (t == 0) {
      d = 1;
    }
    (p->s).coord.x = x + d * 0xE00;
    (p->s).coord.y = y - 0x1700;
  }
}

static const ProjectileFunc PTR_ARRAY_0836d424[3];

// 0x080af46c
void FUN_080af46c(struct Projectile* p) {
  struct Entity* q = (p->s).unk_28;
  if (q->mode[0] > 1) {
    SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
    return;
  }
  (PTR_ARRAY_0836d424[(p->s).mode[2]])(p);
  if ((struct Projectile*)q->unk_2c == p && q->mode[2] <= 4) {
    if (q->mode[2] == 4) {
      q->coord = (p->s).coord;
    }
    return;
  }
  if (CalcFromCamera(&gStageRun.vm.camera, &(p->s).coord) > 0x2000) {
    register u8 f asm("r0");
    register u8 t asm("r1");
    register u8 k2 asm("r1");
    register s32 z asm("r2");
    u8* qq;
    t = (p->s).flags;
    f = 0xFE;
    f &= t;
    asm volatile("" ::"r"(t));
    z = 0;
    k2 = 0xFD;
    f &= k2;
    (p->s).flags = f;
    qq = (u8*)p + 0x8c;
    asm("" : "+r"(qq));
    *(s32*)qq = z;
    asm("" : "+r"(qq));
    qq += 4;
    asm("" : "+r"(qq));
    *(s32*)qq = z;
    asm("" : "+r"(qq));
    qq += 4;
    asm("" : "+r"(qq));
    *qq = z;
    {
      register u8 f3 asm("r0");
      register u8 t3 asm("r1");
      t3 = (p->s).flags;
      f3 = 0xFB;
      f3 &= t3;
      (p->s).flags = f3;
      asm volatile("" ::"r"(t3));
    }
    SET_PROJECTILE_ROUTINE(p, 3);
  }
}

INCASM("asm/projectile/phantom_p1_p1_p1b.inc");

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

// 0x080AF65C
void FUN_080af65c(struct Projectile* p) {
  s32 x = (p->s).coord.x + (p->s).d.x;
  s32 y;
  (p->s).coord.x = x;
  y = (p->s).coord.y + (p->s).d.y;
  (p->s).coord.y = y;
  if ((p->s).work[1] != 0) {
    const s16* st = gSineTable;
    s32 ox = st[(u8)((p->s).work[2] + 0x40)] << 3;
    s32 oy = st[(p->s).work[2]] << 3;
    if (((u16)FUN_080098a4(x + ox, y + oy) << 16) != 0) {
      PlaySound(0x100);
      (p->s).work[0] = 4;
      (p->s).mode[1] = 0;
    }
  }
  if (CalcFromCamera(&gStageRun.vm.camera, &(p->s).coord) > 0x6000) {
    register u8 f asm("r0");
    register u8 t asm("r1");
    register u8 k2 asm("r1");
    register s32 z asm("r2");
    u8* qq;
    t = (p->s).flags;
    f = 0xFE;
    f &= t;
    asm volatile("" ::"r"(t));
    z = 0;
    k2 = 0xFD;
    f &= k2;
    (p->s).flags = f;
    qq = (u8*)p + 0x8c;
    asm("" : "+r"(qq));
    *(s32*)qq = z;
    asm("" : "+r"(qq));
    qq += 4;
    asm("" : "+r"(qq));
    *(s32*)qq = z;
    asm("" : "+r"(qq));
    qq += 4;
    asm("" : "+r"(qq));
    *qq = z;
    {
      register u8 f3 asm("r0");
      register u8 t3 asm("r1");
      t3 = (p->s).flags;
      f3 = 0xFB;
      f3 &= t3;
      (p->s).flags = f3;
      asm volatile("" ::"r"(t3));
    }
    SET_PROJECTILE_ROUTINE(p, 3);
  }
}

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

void FUN_080af7b0(struct Projectile* p);

void FUN_080af760(struct Projectile* p) {
  EXIT_BODY(p);
  SetMotion(&p->s, MOTION(0x86, 0x05));
  (p->s).angle = (p->s).work[2] + 0x20;
  (p->s).d.y -= 0x600;
  (p->s).work[3] = 0x1C;
  (p->s).mode[1] = 1;
  FUN_080af7b0(p);
}

// 0x080af7b0 -- parked two insns from a match: retail materializes the
// flicker mask 1 after the work[3] truncation and burns r6 for a sine
// ldrsh zero index; agbcc hoists the movs and packs the zero temps
// (pins on t/one/r oscillate between the two shapes). Bounce damping
// d.y = -(d.y*230)/256 and the vanish tail fully decoded and verified.
NON_MATCH void FUN_080af7b0(struct Projectile* p) {
#if MODERN
  u8 t = (p->s).work[3] - 1;
  (p->s).work[3] = t;
  if ((t >> 1) & 1) {
    (p->s).flags &= ~DISPLAY;
  } else {
    (p->s).flags |= DISPLAY;
  }
  if ((p->s).work[3] == 0) {
    u8 f = ~DISPLAY & (p->s).flags;
    f = f & ~FLIPABLE;
    (p->s).flags = f;
    (p->body).status = 0;
    (p->body).prevStatus = 0;
    (p->body).invincibleTime = 0;
    (p->s).flags &= ~COLLIDABLE;
    SET_PROJECTILE_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }
  (p->s).d.y += 0x40;
  if ((p->s).d.y > 0x700) {
    (p->s).d.y = 0x700;
  }
  (p->s).coord.x += (p->s).d.x;
  (p->s).coord.y += (p->s).d.y;
  {
    s32 r;
    r = PushoutToUp1((p->s).coord.x + gSineTable[(u8)((p->s).work[2] + 0x40)] * 8,
                     (p->s).coord.y + gSineTable[(p->s).work[2]] * 8);
    if (r < 0) {
      PlaySound(0x100);
      (p->s).coord.y += r;
      (p->s).d.y = -((p->s).d.y * 230) / 256;
    }
  }
  {
    u8 a = (p->s).work[2];
    if ((p->s).d.x > 0) {
      a += 8;
    } else {
      a -= 8;
    }
    (p->s).work[2] = a;
    (p->s).angle = a + 0x20;
  }
#else
  INCCODE("asm/projectile/phantom_f7b0.inc");
#endif
}

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

struct Projectile* FUN_080afbfc(struct Coord* c, s32 speed, u8 angle, u8 n);

void FUN_080af9f4(struct Projectile* p) {
  s32 i;
  (p->s).coord.x += (p->s).d.x;
  (p->s).coord.y += (p->s).d.y;
  if ((((u32)(p->s).work[3] % 10) << 24) == 0) {
    struct Coord c;
    register struct Coord* cp asm("r6");
    const s16* tbl;
    {
      register s32 i5 asm("r5");
      i5 = 0;
      asm volatile("" : "+r"(i5));
      i = i5;
    }
    tbl = gSineTable;
    cp = &c;
    asm("" : "+r"(cp));
    do {
      u32 a3 = (u32)(((p->s).work[3] << 4) + (i << 6)) << 24;
      u8 a2;
      c = (p->s).coord;
      a2 = a3 >> 24;
      {
        register s32 v0 asm("r0");
        u32 off = (a3 + 0x40000000) >> 23;
        off += (u32)tbl;
        v0 = *(const s16*)off * 8;
        v0 += c.x;
        c.x = v0;
      }
      {
        register s32 v1 asm("r0");
        v1 = tbl[a2] * 8;
        v1 += cp->y;
        cp->y = v1;
      }
      FUN_080afbfc(&c, 0x3C0, a2, 0);
      i++;
    } while (i <= 3);
  }
  {
    s32 t = (p->s).work[3] + 1;
    i = 0;
    (p->s).work[3] = t;
  }
  if (((u16)FUN_080098a4((p->s).coord.x, (p->s).coord.y + 0x800) << 16) != 0) {
    PlaySound(0x100);
    {
      register u8 e1 asm("r1");
      register s32 fp asm("r0");
      e1 = (p->s).flags;
      fp = 0xFE;
      fp &= e1;
      {
        register s32 c2 asm("r1");
        c2 = 0xFD;
        fp &= c2;
      }
      (p->s).flags = fp;
      (p->body).status = i;
      (p->body).prevStatus = i;
      (p->body).invincibleTime = i;
      (p->s).flags &= ~COLLIDABLE;
      SET_PROJECTILE_ROUTINE(p, ENTITY_DISAPPEAR);
    }
  }
  {
    struct Camera* cam = &gStageRun.vm.camera;
    if (CalcFromCamera(cam, &(p->s).coord) > 0x6000) {
      register u8 e1 asm("r1");
      register s32 fp asm("r0");
      e1 = (p->s).flags;
      fp = 0xFE;
      fp &= e1;
      {
        register s32 c2 asm("r1");
        c2 = 0xFD;
        fp &= c2;
      }
      (p->s).flags = fp;
      (p->body).status = i;
      (p->body).prevStatus = i;
      (p->body).invincibleTime = i;
      (p->s).flags &= ~COLLIDABLE;
      SET_PROJECTILE_ROUTINE(p, ENTITY_DISAPPEAR);
    }
  }
}


void FUN_080afb1c(struct Projectile* p) {
  if (((p->s).unk_28)->mode[0] > 1) {
    (p->s).flags &= ~DISPLAY;
    (p->s).flags &= ~FLIPABLE;
    EXIT_BODY(p);
    SET_PROJECTILE_ROUTINE(p, ENTITY_DISAPPEAR);
  }
}

void PhantomProjectile_Die(struct Projectile* p) {
  SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
  CreateSmoke(1, &(p->s).coord);
  EXIT_BODY(p);
  (p->s).flags &= ~DISPLAY;
}

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

// Same 33 instructions; retail pools the -PIXEL(38)/-PIXEL(76) constants
// where agbcc rebuilds them inline (pressure/pooling tie).
NON_MATCH bool8 FUN_080afdf0(struct Entity* e, struct Coord* a, struct Coord* b, struct Coord* c) {
#if MODERN
  s32 t;
  s32 dx = b->x;
  a->x += dx;
  a->y += b->y;
  {
    s32 limit = *(s32*)((u8*)e + 0xdc) - PIXEL(76);
    t = (a->x - PIXEL(38)) - *(s32*)((u8*)e + 0xd4);
    if ((u32)t > (u32)limit) {
      if (t * dx > 0) {
        return TRUE;
      }
    }
  }
  return FALSE;
#else
  INCCODE("asm/projectile/phantom_afdf0.inc");
#endif
}

INCASM("asm/projectile/phantom_p2_p2_p2_e.inc");

// 3 insns over: same pointer-copy allocation tie as its sibling FUN_080afdf0.
NON_MATCH bool8 FUN_080afe38(struct Entity* e, struct Coord* a, struct Coord* b, struct Coord* c) {
#if MODERN
  s32 cx = c->x;
  s32 by;
  b->x += cx;
  by = b->y;
  if (by > -0x80) {
    by -= 8;
    b->y = by;
  }
  a->x += b->x;
  a->y += by;
  if ((u32)(b->x + 0x3FF) <= 0x7FE) {
    return FALSE;
  }
  c->x = -cx;
  return TRUE;
#else
  INCCODE("asm/projectile/phantom_afe38.inc");
#endif
}

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
