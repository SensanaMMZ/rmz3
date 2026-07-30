#include "collision.h"
#include "global.h"
#include "entity/macros.h"
#include "gpu_regs.h"
#include "projectile.h"
#include "sound.h"
#include "zero.h"

static const ProjectileFunc sUpdates[9];

static const ProjectileFunc sInitializers[9];
static const ProjectileFunc PTR_ARRAY_0836c408[9];

struct Projectile* FUN_080aaa80(struct Entity* e, u8 a, u8 b) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);

  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 32);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = a;
    (p->s).work[1] = b;
    (p->s).unk_28 = e;
    (p->s).coord = e->coord;
    return p;
  }
  return NULL;
}

void blizzack_080aaae0(struct Entity* e, u8 n) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);

  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 32);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 1;
    (p->s).work[1] = n;
    (p->s).unk_28 = e;
    (p->s).coord = e->coord;
  }
}

#include "enemy.h"

void FUN_080aab38(struct Enemy* e, struct Entity* parent) {
  struct Projectile* p = (struct Projectile*)AllocEntityLast(gProjectileHeaderPtr);

  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 32);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 2;
    (p->s).work[1] = 0;
    (p->s).unk_28 = parent;
    SET_XFLIP(p, (e->s).d.x > 0);
    (p->s).coord = (e->s).coord;
    (p->s).coord.y = *(s32*)&e->props[4];
  }
}

void FUN_080aabd4(struct Entity* e) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 32);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 3;
    (p->s).work[1] = 0;
    (p->s).unk_28 = e;
    (p->s).coord = e->coord;
  }
}

void FUN_080aac28(struct Entity* e) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 32);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 4;
    (p->s).work[1] = 0;
    (p->s).unk_28 = e;
    (p->s).coord = e->coord;
  }
}

void FUN_080aac7c(struct Coord* c, bool8 xflip, struct Entity* e) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);

  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 32);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 5;
    (p->s).work[1] = 0;
    (p->s).coord = *c;
    SET_XFLIP(p, xflip);
    (p->s).unk_28 = e;
  }
}

void FUN_080aad0c(struct Coord* c, bool8 xflip, struct Entity* e) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);

  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 32);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 6;
    (p->s).work[1] = 0;
    (p->s).coord = *c;
    SET_XFLIP(p, xflip);
    (p->s).unk_28 = e;
    (p->s).unk_2c = e->unk_28;
  }
}

void FUN_080aada0(struct Entity* e, u8 n) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);

  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 32);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 7;
    (p->s).work[1] = n;
    (p->s).coord = e->coord;
    SET_XFLIP(p, (e->flags >> 4) & 1);
    (p->s).unk_28 = e;
  }
}

struct Projectile* FUN_080aae34(struct Entity* e) {
  struct Projectile* p = (struct Projectile*)AllocEntityFirst(gProjectileHeaderPtr);

  if (p != NULL) {
    (p->s).taskCol = 8;
    INIT_PROJECTILE_ROUTINE(p, 32);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 8;
    (p->s).work[1] = 0;
    (p->s).unk_28 = e;
    return p;
  }
  return NULL;
}

void Projectile32_Init(struct Projectile* p) {
  (sInitializers[(p->s).work[0]])(p);
}


void Projectile32_Update(struct Projectile* p) {
  (sUpdates[(p->s).work[0]])(p);
}


void Projectile32_Die(struct Projectile* p) {
  (PTR_ARRAY_0836c408[(p->s).work[0]])(p);
}


void nop_080aaecc(struct Projectile* p) {}


void nop_080aaed0(struct Projectile* p) {}


void nop_080aaed4(struct Projectile* p) {}

INCASM("asm/projectile/unk_32_p4_p1.inc");

void FUN_080ab178(struct Projectile* p) {
  SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}

INCASM("asm/projectile/unk_32_p4_p2_s1.inc");

void FUN_080ac1e4(struct RenderNode* t);

void FUN_080ab550(struct Projectile* p) {
  struct Entity* q = (p->s).unk_28;
  gVideoRegBuffer.dispcnt |= 0x2400;
  SetTaskCallback((struct RenderNode*)&(p->s).spr, (void*)FUN_080ac1e4);
  ((p->s).spr).sprites = (void*)p;
  {
    register u8 f0 asm("r0");
    register s32 f2m asm("r2");
    register s32 z3 asm("r3");
    f0 = (p->s).flags;
    f2m = 0xF7;
    f2m &= f0;
    {
      register s32 d1 asm("r0");
      d1 = DISPLAY;
      asm("" : "+r"(d1));
      z3 = 0;
      asm("" : "+r"(z3));
      f2m |= d1;
    }
    f2m |= FLIPABLE;
    f2m |= z3;
    (p->s).flags = f2m;
    {
      u8 on = (q->flags >> 4) & 1;
      if (on) {
        f2m |= X_FLIP;
      } else {
        f2m &= 0xEF;
      }
      (p->s).flags = f2m;
      ((p->s).spr).xflip = on;
      {
        u8* a = (u8*)p + 0x4a;
        register s32 sh asm("r1");
        register u8 b2 asm("r2");
        s32 msk2;
        sh = on << 4;
        b2 = *a;
        msk2 = -0x11;
        msk2 &= b2;
        msk2 |= sh;
        *a = msk2;
      }
    }
  }
  gBlendRegBuffer.bldclt = 0x3F44;
  gBlendRegBuffer.bldalpha = 0x1008;
  gWindowRegBuffer.dispcnt |= 0x4000;
  gWindowRegBuffer.winin[1] = 0xFF;
  gWindowRegBuffer.winin[2] &= 0xFB;
  {
    s32 v;
    if ((p->s).flags & X_FLIP) {
      (p->s).coord.x += 0x1E00;
      v = -2;
    } else {
      (p->s).coord.x += -0x1E00;
      v = 2;
    }
    (p->s).d.x = v;
  }
  (p->s).coord.y += -0x2600;
  (p->s).work[2] = 0xB4;
  (p->s).work[3] = 0;
  *(u16*)((u8*)p + 0xc0) = PlaySound(0x44);
  FUN_080aada0(&p->s, 0);
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  Projectile32_Update(p);
}

INCASM("asm/projectile/unk_32_p4_p2_s1_b.inc");

void FUN_080ab724(struct Projectile* p) {
  gVideoRegBuffer.dispcnt &= ~(DISPCNT_WIN0_ON | DISPCNT_BG2_ON);
  gWindowRegBuffer.dispcnt &= ~DISPCNT_WIN1_ON;
  gWindowRegBuffer.winin[2] |= 0xFE;
  StopSound(*(s16*)((u8*)p + 0xC0));
  (p->s).flags &= ~DISPLAY;
  SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}

void FUN_080ac1e4();

void FUN_080ab784(struct Projectile* p) {
  struct Entity* par = (p->s).unk_28;
  gVideoRegBuffer.dispcnt |= 0x2400;
  SetTaskCallback((struct RenderNode*)((u8*)p + 0x34), FUN_080ac1e4);
  *(void**)((u8*)p + 0x3c) = p;
  {
    register u32 f asm("r2");
    register s32 z3 asm("r3");
    {
      register s32 fl0 asm("r0");
      fl0 = (p->s).flags;
      f = 0xF7;
      asm("" : "+r"(f));
      f &= fl0;
    }
    {
      register u32 c1 asm("r0");
      c1 = 1;
      asm("" : "+r"(c1));
      z3 = 0;
      asm("" : "+r"(z3));
      f |= c1;
    }
    f |= 2;
    f |= z3;
    (p->s).flags = f;
    {
      register u32 xf asm("r1");
      {
        register u32 pf asm("r0");
        pf = par->flags;
        xf = pf >> 4;
      }
      {
        register u32 c1x asm("r0");
        c1x = 1;
        asm("" : "+r"(c1x));
        xf &= c1x;
      }
      if (xf != 0) {
        f |= 0x10;
      } else {
        f &= 0xEF;
      }
      (p->s).flags = f;
      ((p->s).spr).xflip = xf;
      {
        register u8* oa3 asm("r3");
        s32 ov2;
        s32 m11b;
        oa3 = (u8*)&((p->s).spr).oam + 6;
        xf <<= 4;
        ov2 = *oa3;
        m11b = -0x11;
        asm("" : "+r"(m11b));
        *oa3 = (m11b & ov2) | xf;
      }
    }
  }
  gBlendRegBuffer.bldclt = 0x3F44;
  gBlendRegBuffer.bldalpha = 0x1008;
  gWindowRegBuffer.dispcnt |= 0x4000;
  gWindowRegBuffer.winin[1] = 0xFF;
  gWindowRegBuffer.winin[2] &= 0xFB;
  if ((p->s).flags & 0x10) {
    (p->s).coord.x += 0x1E00;
    (p->s).d.x = -3;
  } else {
    (p->s).coord.x += -0x1E00;
    (p->s).d.x = 3;
  }
  (p->s).coord.y += -0x1E00;
  {
    s32 z1 = 0;
    (p->s).work[2] = 0xB4;
    (p->s).work[3] = z1;
  }
  {
    u16* sh = (u16*)((u8*)p + 0xc0);
    {
      register u32 hv asm("r0");
      hv = 0xFFFF;
      asm("" : "+r"(hv));
      *sh = hv;
    }
    *sh = PlaySound(0x44);
  }
  {
    u32 rr = RANDOM(RNG_0202f388) % 3;
    *((u8*)p + 0xc2) = rr;
  }
  FUN_080aada0(&p->s, 1);
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  Projectile32_Update(p);
}

INCASM("asm/projectile/unk_32_p4_p2_s2b.inc");

void FUN_080ab990(struct Projectile* p) {
  gVideoRegBuffer.dispcnt &= ~(DISPCNT_WIN0_ON | DISPCNT_BG2_ON);
  gWindowRegBuffer.dispcnt &= ~DISPCNT_WIN1_ON;
  gWindowRegBuffer.winin[2] |= 0xFE;
  StopSound(*(s16*)((u8*)p + 0xC0));
  (p->s).flags &= ~DISPLAY;
  SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}

static const struct Collision sCollisions[14];

void FUN_080ab9f0(struct Projectile* p) {
  InitNonAffineMotion(&p->s);
  (p->s).flags |= DISPLAY;
  (p->s).flags |= FLIPABLE;
  SetMotion(&p->s, MOTION(0x62, 0x02));
  UpdateMotionGraphic(&p->s);
  INIT_BODY(p, &sCollisions[8], 0x40, NULL);
  (p->s).d.x = 0xA0;
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  Projectile32_Update(p);
}

INCASM("asm/projectile/unk_32_p4_p2_s3.inc");

void FUN_080abb2c(struct Projectile* p) {
  SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}

void FUN_080abb44(struct Projectile* p) {
  SET_PROJECTILE_ROUTINE(p, ENTITY_UPDATE);
  InitNonAffineMotion(&p->s);
  (p->s).flags |= DISPLAY;
  (p->s).flags |= FLIPABLE;
  SetMotion(&p->s, MOTION(0x62, 0x07));
  INIT_BODY(p, &sCollisions[10], 0x40, NULL);
  (p->s).d.x = 0x80;
  (p->s).d.y = 0;
  (p->s).work[2] = 0;
  (p->s).work[3] = 0;
  Projectile32_Update(p);
}

INCASM("asm/projectile/unk_32_p4_p3_p1.inc");

void FUN_080abdc8(struct Projectile* p) {
  *(u32*)((u8*)p + 0x8c) = 0;
  *(u32*)((u8*)p + 0x90) = 0;
  *(u8*)((u8*)p + 0x94) = 0;
  (p->s).flags &= ~COLLIDABLE;
  SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}

INCASM("asm/projectile/unk_32_p4_p3_p2.inc");

void FUN_080abe54(struct Projectile* p) {
  struct Entity* q = (p->s).unk_28;
  UpdateMotionGraphic(&p->s);
  {
    s32 x = (pZero2->s).coord.x;
    (p->s).coord.x = x;
    if ((p->s).flags & 0x10) {
      if (x < q->coord.x) {
        (p->s).coord.x = q->coord.x;
      }
    } else {
      if (x > q->coord.x) {
        (p->s).coord.x = q->coord.x;
      }
    }
  }
  if (q->mode[0] > 1) {
    SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
  }
}

void FUN_080abea8(struct Projectile* p) {
  SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}

// 0x080abec0 -- parked (dead-zero basin, blizzackJump family): retail
// materializes an unused r4=0 before the flags orrs and a separate scratch
// 1 for DISPLAY; agbcc unifies the SET_ROUTINE constant 1 with the orr
// mask and deletes the dead zero in every variable arrangement tried.
NON_MATCH void FUN_080abec0(struct Projectile* p) {
#if MODERN
  s32 one = 0;
  s32 t;
  InitNonAffineMotion(&p->s);
  (p->s).flags |= DISPLAY;
  (p->s).flags |= FLIPABLE;
  SetMotion(&p->s, MOTION(0x62, 0x00));
  UpdateMotionGraphic(&p->s);
  t = ((pZero2->s).flags >> 4) & 1;
  if (t != 0) {
    (p->s).flags |= X_FLIP;
  } else {
    (p->s).flags &= ~X_FLIP;
  }
  one = 1;
  {
    s16 w = one & t;
    s32 z = 0;
    (p->s).spr.xflip = w;
    ((p->s).spr).oam.xflip = w;
    (p->s).work[1] = z;
  }
  SET_PROJECTILE_ROUTINE(p, one);
  Projectile32_Update(p);
#else
  INCCODE("asm/projectile/unk_32_bec0.inc");
#endif
}

void FUN_080abf54(struct Projectile* p) {
  UpdateMotionGraphic(&p->s);
  {
    register u8 f asm("r0");
    u8 odd;
    {
      register u8 t asm("r1") = (p->s).work[2];
      (p->s).work[2] = t + 1;
      odd = t & 1;
    }
    if (odd) {
      register u8 f0 asm("r1");
      f0 = (p->s).flags;
      f = ~DISPLAY & f0;
    } else {
      f = (p->s).flags;
      f = DISPLAY | f;
    }
    (p->s).flags = f;
  }
  (p->s).coord.x = (pZero2->s).coord.x;
  (p->s).coord.y = (pZero2->s).coord.y - PIXEL(8);
  if ((p->s).work[1] != 0) {
    PlaySound(0x3F);
    SET_PROJECTILE_ROUTINE(p, ENTITY_DIE);
  }
}

INCASM("asm/projectile/unk_32_p4_p4.inc");

// 0x080ac1a4
void FUN_080ac1a4(struct Body* body, struct Coord* r1 UNUSED, struct Coord* r2 UNUSED) {
  struct Projectile* self = (struct Projectile*)body->parent;
  struct Zero* z = (struct Zero*)(body->enemy)->parent;
  s32 kind = (z->s).kind;
  if (kind != ENTITY_PLAYER) {
    return;
  }
  {
    s32 v = ((self->s).work[1] == 0) ? 0x180 : 0x280;
    if ((self->s).flags & X_FLIP) {
      *(s32*)&z->horizontalSlide = v;
    } else {
      *(s32*)&z->horizontalSlide = -v;
    }
  }
}

INCASM("asm/projectile/unk_32_p4_p4_b.inc");

void Projectile32_Init(struct Projectile* p);
void Projectile32_Update(struct Projectile* p);
void Projectile32_Die(struct Projectile* p);

// clang-format off
const ProjectileRoutine gProjectile32Routine = {
    [ENTITY_INIT] =      Projectile32_Init,
    [ENTITY_UPDATE] =    Projectile32_Update,
    [ENTITY_DIE] =       Projectile32_Die,
    [ENTITY_DISAPPEAR] = DeleteProjectile,
    [ENTITY_EXIT] =      (ProjectileFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

void nop_080aaecc(struct Projectile* p);
void FUN_080aaed8(struct Projectile* p);
void FUN_080ab190(struct Projectile* p);
void FUN_080ab550(struct Projectile* p);
void FUN_080ab784(struct Projectile* p);
void FUN_080ab9f0(struct Projectile* p);
void FUN_080abb44(struct Projectile* p);
void FUN_080abdf8(struct Projectile* p);
void FUN_080abec0(struct Projectile* p);

// clang-format off
static const ProjectileFunc sInitializers[9] = {
    nop_080aaecc,
    FUN_080aaed8,
    FUN_080ab190,
    FUN_080ab550,
    FUN_080ab784,
    FUN_080ab9f0,
    FUN_080abb44,
    FUN_080abdf8,
    FUN_080abec0,
};
// clang-format on

// --------------------------------------------

void nop_080aaed0(struct Projectile* p);
void FUN_080ab004(struct Projectile* p);
void FUN_080ab21c(struct Projectile* p);
void FUN_080ab668(struct Projectile* p);
void FUN_080ab8cc(struct Projectile* p);
void FUN_080aba60(struct Projectile* p);
void FUN_080abbb8(struct Projectile* p);
void FUN_080abe54(struct Projectile* p);
void FUN_080abf54(struct Projectile* p);

// clang-format off
static const ProjectileFunc sUpdates[9] = {
    nop_080aaed0,
    FUN_080ab004,
    FUN_080ab21c,
    FUN_080ab668,
    FUN_080ab8cc,
    FUN_080aba60,
    FUN_080abbb8,
    FUN_080abe54,
    FUN_080abf54,
};
// clang-format on

// --------------------------------------------

void nop_080aaed4(struct Projectile* p);
void FUN_080ab178(struct Projectile* p);
void FUN_080ab3ac(struct Projectile* p);
void FUN_080ab724(struct Projectile* p);
void FUN_080ab990(struct Projectile* p);
void FUN_080abb2c(struct Projectile* p);
void FUN_080abdc8(struct Projectile* p);
void FUN_080abea8(struct Projectile* p);
void FUN_080abfbc(struct Projectile* p);

// clang-format off
static const ProjectileFunc PTR_ARRAY_0836c408[9] = {
    nop_080aaed4,
    FUN_080ab178,
    FUN_080ab3ac,
    FUN_080ab724,
    FUN_080ab990,
    FUN_080abb2c,
    FUN_080abdc8,
    FUN_080abea8,
    FUN_080abfbc,
};
// clang-format on

// --------------------------------------------

static const struct Collision sCollisions[14] = {
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 2,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(16), PIXEL(16)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      damage : 2,
      LAYER(0xFFFFFFFF),
      hitzone : 0,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(0), PIXEL(0)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 255,
      unk_0a : 0x41,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(12), PIXEL(32), PIXEL(24)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      damage : 255,
      LAYER(0xFFFFFFFF),
      hitzone : 0,
      unk_0a : 0x41,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(0), PIXEL(0)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 2,
      hitzone : 4,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(8), PIXEL(16), PIXEL(16)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      damage : 2,
      LAYER(0xFFFFFFFF),
      hitzone : 4,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(8), PIXEL(16), PIXEL(16)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 255,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(8), PIXEL(80)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      damage : 255,
      LAYER(0xFFFFFFFF),
      hitzone : 0,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(0), PIXEL(0)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 2,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(16), PIXEL(8)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      damage : 2,
      LAYER(0xFFFFFFFF),
      hitzone : 0,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(0), PIXEL(0)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 255,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(12), PIXEL(12)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      damage : 255,
      LAYER(0xFFFFFFFF),
      hitzone : 0,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(0), PIXEL(0)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 255,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), -PIXEL(1), -PIXEL(1)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      damage : 255,
      LAYER(0xFFFFFFFF),
      hitzone : 0,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(0), PIXEL(0)},
    },
};

static const s32 s32_ARRAY_0836c57c[30] = {
    0x00001800, 0x00001800, -0x00000001, -0x00001800, 0x00000000, 0x00000000, 0x00001800, 0x00000000, 0x00000000, 0x00001800, 0x00001800, 0x00000000, -0x00000001, -0x00001800, 0x00000000, 0x00001800, -0x00001800, 0x00000000, 0x00001800, -0x00001800, 0x00000000, 0x00000000, -0x00000001, 0x00001800, 0x00000000, -0x00000001, -0x00001800, 0x00000000, -0x00000001, -0x00001800,
};
