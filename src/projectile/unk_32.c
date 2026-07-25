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

INCASM("asm/projectile/unk_32_p1_pre_pre.inc");

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

INCASM("asm/projectile/unk_32_p1_pre_pre_b.inc");

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

void FUN_080ab724(struct Projectile* p) {
  gVideoRegBuffer.dispcnt &= ~(DISPCNT_WIN0_ON | DISPCNT_BG2_ON);
  gWindowRegBuffer.dispcnt &= ~DISPCNT_WIN1_ON;
  gWindowRegBuffer.winin[2] |= 0xFE;
  StopSound(*(s16*)((u8*)p + 0xC0));
  (p->s).flags &= ~DISPLAY;
  SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}

INCASM("asm/projectile/unk_32_p4_p2_s2.inc");

void FUN_080ab990(struct Projectile* p) {
  gVideoRegBuffer.dispcnt &= ~(DISPCNT_WIN0_ON | DISPCNT_BG2_ON);
  gWindowRegBuffer.dispcnt &= ~DISPCNT_WIN1_ON;
  gWindowRegBuffer.winin[2] |= 0xFE;
  StopSound(*(s16*)((u8*)p + 0xC0));
  (p->s).flags &= ~DISPLAY;
  SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
}

INCASM("asm/projectile/unk_32_p4_p2_s3.inc");

void FUN_080abb2c(struct Projectile* p) {
  SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
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

void FUN_080abea8(struct Projectile* p) {
  SET_PROJECTILE_ROUTINE(p, ENTITY_EXIT);
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
