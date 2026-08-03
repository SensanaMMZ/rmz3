#include "collision.h"
#include "global.h"
#include "metatile.h"
#include "projectile.h"

// Hanumachine

static const ProjectileFunc sUpdates[4];

static const ProjectileFunc sInitializers[4];

void hanu_080ad598(struct Entity* e, u8 a1, u8 a2) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 36);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = a1;
    (p->s).work[1] = a2;
    (p->s).unk_28 = e;
    (p->s).coord = e->coord;
  }
}

void FUN_080ad5f0(struct Entity* e, u8 a1, u8 a2) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 36);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = a1;
    (p->s).work[1] = a2;
    (p->s).unk_28 = e;
    (p->s).coord = e->coord;
  }
}

void Projectile36_Init(struct Projectile* p) {
  (sInitializers[(p->s).work[0]])(p);
}


void Projectile36_Update(struct Projectile* p) {
  (sUpdates[(p->s).work[0]])(p);
}

void Projectile36_Die(struct Projectile* p) {
  (p->s).flags &= ~DISPLAY;
  SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}

extern const s16 gSineTable[256];

// 0x080AD698
void FUN_080ad698(struct Projectile* p) {
  register s32 z asm("r5");
  register const s16* tb asm("r4");
  s32 dx;
  s32 dy;
  InitNonAffineMotion(&p->s);
  {
    register u8 fv asm("r0");
    register u8 fl asm("r1");
    fl = (p->s).flags;
    fv = 1;
    z = 0;
    fv |= fl;
    fl = 2;
    fv |= fl;
    (p->s).flags = fv;
  }
  SetMotion(&p->s, 0x6A00);
  (p->s).flags |= COLLIDABLE;
  {
    struct Body* body = &p->body;
    InitBody(body, (const struct Collision*)0x0836C8E0, &(p->s).coord, 1);
    body->parent = (struct CollidableEntity*)p;
    body->fn = (BodyFunc)z;
  }
  tb = gSineTable;
  {
    register s32 a2 asm("r3");
    u8 a = (p->s).work[1];
    s32 s1;
    a2 = a;
    a2 += 0xC0;
    s1 = tb[a];
    dx = ((s1 * 8 - s1) << 7) / 256;
    (p->s).d.x = dx;
    {
      register s32 ix asm("r0");
      s32 s2;
      asm volatile("lsl %0, %1, #0x18
	lsr %0, %0, #0x17" : "=l"(ix) : "l"(a2));
      {
        register const s16* e asm("r0");
        asm volatile("add %0, %1, %2" : "=l"(e) : "l"(ix), "l"(tb));
        s2 = *e;
      }
      dy = ((s2 * 8 - s2) << 7) / 256;
      (p->s).d.y = dy;
    }
  }
  {
    register s32 nx asm("r2");
    nx = (p->s).coord.x + (dx << 3);
    (p->s).coord.x = nx;
    (p->s).coord.y += (dy << 3);
    *(s32*)((u8*)p + 0xb4) = nx;
    *(s32*)((u8*)p + 0xb8) = (p->s).coord.y;
  }
  FUN_080ad5f0(&p->s, 1, 3);
  FUN_080ad5f0(&p->s, 1, 6);
  FUN_080ad5f0(&p->s, 1, 9);
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  Projectile36_Update(p);
}

void FUN_080ad778(struct Projectile* p) {
  UpdateMotionGraphic(&p->s);
  (p->s).coord.x += (p->s).d.x;
  (p->s).coord.y += (p->s).d.y;
  if (FUN_080098a4((p->s).coord.x, (p->s).coord.y)) {
    SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
    (p->body).status = 0;
    (p->body).prevStatus = 0;
    (p->body).invincibleTime = 0;
    (p->s).flags &= ~COLLIDABLE;
  }
}

void FUN_080ad7d0(struct Projectile* p) {
  struct Projectile* q = (struct Projectile*)(p->s).unk_28;
  InitNonAffineMotion(&p->s);
  (p->s).flags |= FLIPABLE;
  SetMotion(&p->s, MOTION(0x6a, 0x01));
  (p->s).taskCol = 9;
  (p->s).d.x = (q->s).d.x;
  (p->s).d.y = (q->s).d.y;
  (p->s).coord.x = *(s32*)((u8*)q + 0xb4);
  (p->s).coord.y = *(s32*)((u8*)q + 0xb8);
  *(s32*)((u8*)p + 0xb4) = (p->s).coord.x;
  *(s32*)((u8*)p + 0xb8) = (p->s).coord.y;
  (p->s).work[3] = (p->s).work[1];
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  Projectile36_Update(p);
}

void FUN_080ad840(struct Projectile* p) {
  UpdateMotionGraphic(&p->s);
  if ((p->s).work[3] != 0) {
    if (--(p->s).work[3] == 0) {
      (p->s).flags |= DISPLAY;
    }
  } else {
    u32 w = (p->s).work[2] + 1;
    (p->s).work[2] = w;
    (p->s).coord.x += (p->s).d.x;
    (p->s).coord.y += (p->s).d.y;
    if ((w & 3) > 1) {
      (p->s).flags |= DISPLAY;
    } else {
      (p->s).flags &= ~DISPLAY;
    }
  }
  if (FUN_080098a4((p->s).coord.x, (p->s).coord.y)) {
    SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
  }
}

INCASM("asm/projectile/unk_36_pre_post_p2_p1b.inc");

// 0x080AD8B8
NON_MATCH void FUN_080ad8b8(struct Projectile* p) {
#if MODERN
  register u8 z6 asm("r6");
  register u8 z4 asm("r4");
  register u8 z3 asm("r3");
  u8 f;
  InitRotatableMotion(&p->s);
  (p->s).flags |= DISPLAY;
  z4 = 0;
  z6 = 0;
  (p->s).flags |= FLIPABLE;
  SetMotion(&p->s, MOTION(0x6A, 0x05));
  UpdateMotionGraphic(&p->s);
  *(u8*)((u8*)p + 0x24) = z4;
  f = (p->s).work[1];
  if (f != 0) {
    (p->s).flags |= 0x10;
  } else {
    (p->s).flags &= 0xEF;
  }
  {
    u32 xf = 1 & f;
    register u8* oa asm("r4");
    z3 = 0;
    ((p->s).spr).xflip = xf;
    oa = (u8*)p + 0x4a;
    {
      u32 sh4 = xf << 4;
      s32 ov = *oa;
      s32 m11 = -0x11;
      m11 &= ov;
      m11 |= sh4;
      *oa = m11;
    }
    (p->s).work[2] = z3;
    (p->s).work[3] = z3;
  }
  {
    s32 nf;
    if ((p->s).flags & 0x10) {
      nf = -4;
      asm("" : "+r"(nf));
    } else {
      nf = 4;
      asm("" : "+r"(nf) : "r"(z6));
    }
    (p->s).work[3] = nf;
  }
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  Projectile36_Update(p);
#else
  INCCODE("asm/projectile/unk36_080ad8b8.inc");
#endif
}

void FUN_080ad958(struct Projectile* p) {
  UpdateMotionGraphic(&p->s);
  (p->s).work[2] += (p->s).work[3];
  (p->s).angle = (p->s).work[2];
  if ((p->s).motion.state == 3) {
    SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
  }
}

// 0x080AD994
void FUN_080ad994(struct Projectile* p) {
  struct Entity* q = (p->s).unk_28;
  register s32 z asm("r6");
  InitNonAffineMotion(&p->s);
  {
    register u8 fv asm("r0");
    register u8 fl asm("r1");
    fl = (p->s).flags;
    fv = DISPLAY;
    z = 0;
    asm("" : "+r"(z));
    fv |= fl;
    fl = FLIPABLE;
    fv |= fl;
    (p->s).flags = fv;
  }
  SetMotion(&p->s, MOTION(0x6A, 0x06));
  SET_XFLIP(p, (q->flags >> 4) & 1);
  if ((p->s).flags & X_FLIP) {
    (p->s).coord.x += 0xA00;
  } else {
    (p->s).coord.x += -0xA00;
  }
  (p->s).coord.y += 0x1000;
  if (((u16)FUN_080098a4((p->s).coord.x, (p->s).coord.y) << 16) != 0) {
    (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y);
  }
  asm volatile("" ::"r"(z));
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  Projectile36_Update(p);
}

void FUN_080ada50(struct Projectile* p) {
  UpdateMotionGraphic(&p->s);
  if ((p->s).motion.state == 3) {
    SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
  }
}


void Projectile36_Init(struct Projectile* p);
void Projectile36_Update(struct Projectile* p);
void Projectile36_Die(struct Projectile* p);

// clang-format off
const ProjectileRoutine gProjectile36Routine = {
    [ENTITY_INIT] =      Projectile36_Init,
    [ENTITY_UPDATE] =    Projectile36_Update,
    [ENTITY_DIE] =       Projectile36_Die,
    [ENTITY_DISAPPEAR] = DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

void FUN_080ad698(struct Projectile* p);
void FUN_080ad7d0(struct Projectile* p);
void FUN_080ad8b8(struct Projectile* p);
void FUN_080ad994(struct Projectile* p);

static const ProjectileFunc sInitializers[4] = {
    FUN_080ad698,
    FUN_080ad7d0,
    FUN_080ad8b8,
    FUN_080ad994,
};

// --------------------------------------------

void FUN_080ad778(struct Projectile* p);
void FUN_080ad840(struct Projectile* p);
void FUN_080ad958(struct Projectile* p);
void FUN_080ada50(struct Projectile* p);

static const ProjectileFunc sUpdates[4] = {
    FUN_080ad778,
    FUN_080ad840,
    FUN_080ad958,
    FUN_080ada50,
};

// --------------------------------------------

static const struct Collision sCollisions[2] = {
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(8), PIXEL(8)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      damage : 3,
      LAYER(0xFFFFFFFF),
      hitzone : 0,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(0), PIXEL(0)},
    },
};
