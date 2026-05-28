#include "collision.h"
#include "enemy.h"
#include "global.h"

struct Enemy* CreatePetatria(struct Coord* c, u8 mode) {
  struct Enemy* p = (struct Enemy*)AllocEntityFirst(gEnemyHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(p, ENEMY_PETATRIA);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).coord = *c;
    (p->s).work[0] = mode;
  }
  return p;
}

INCASM("asm/enemy/petatria_p1_pre_p1_p2.inc");

bool8 FUN_080902a8(struct Enemy* p) {
  if ((p->body).status & BODY_STATUS_B3) {
    (p->s).mode[1] = 4;
    (p->s).mode[2] = 0;
  }
  return TRUE;
}

INCASM("asm/enemy/petatria_p1_pre_p2.inc");

bool8 FUN_080906ec(struct Enemy* p) {
  if ((p->body).status & BODY_STATUS_B3) {
    (p->s).mode[1] = 5;
    (p->s).mode[2] = 0;
  }
  return TRUE;
}

INCASM("asm/enemy/petatria_p1_pre_p3.inc");

void FUN_08091154(struct Enemy* p) {
  if ((p->s).mode[2] == 0) {
    (p->s).mode[2] = 1;
  }
}

INCASM("asm/enemy/petatria_p1_post.inc");

bool8 FUN_08091168(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/petatria_p2_p1.inc");

void FUN_0809116c(struct Enemy* p) {}

INCASM("asm/enemy/petatria_p2_p2.inc");

bool8 FUN_08091170(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/petatria_p3_pre.inc");

void FUN_08091174(struct Enemy* p) {
  if ((p->s).mode[2] == 0) {
    (p->s).mode[2] = 1;
  }
}

INCASM("asm/enemy/petatria_p3_post.inc");

bool8 FUN_08091188(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/petatria_p4_p1.inc");

void nop_0809127c(struct Enemy* p) {}

INCASM("asm/enemy/petatria_p4_p2.inc");

void Petatria_Init(struct Enemy* p);
void Petatria_Update(struct Enemy* p);
void Petatria_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gPetatriaRoutine = {
    [ENTITY_INIT] =      Petatria_Init,
    [ENTITY_UPDATE] =    Petatria_Update,
    [ENTITY_DIE] =       Petatria_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

bool8 FUN_080902a8(struct Enemy* p);
bool8 FUN_080906ec(struct Enemy* p);
void FUN_08090b20(struct Enemy* p);
void FUN_08090c60(struct Enemy* p);
void FUN_08090da4(struct Enemy* p);
void FUN_08090edc(struct Enemy* p);
void FUN_08091068(struct Enemy* p);
void FUN_08091150(struct Enemy* p);
bool8 FUN_08091168(struct Enemy* p);
bool8 FUN_08091170(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates1[10] = {
    (EnemyFunc)FUN_080902a8,
    (EnemyFunc)FUN_080906ec,
    FUN_08090b20,
    FUN_08090c60,
    FUN_08090da4,
    FUN_08090edc,
    FUN_08091068,
    FUN_08091150,
    (EnemyFunc)FUN_08091168,
    (EnemyFunc)FUN_08091170,
};
// clang-format on

void FUN_080902c8(struct Enemy* p);
void FUN_0809070c(struct Enemy* p);
void FUN_08090b24(struct Enemy* p);
void FUN_08090c64(struct Enemy* p);
void FUN_08090da8(struct Enemy* p);
void FUN_08090ee0(struct Enemy* p);
void FUN_0809106c(struct Enemy* p);
void FUN_08091154(struct Enemy* p);
void FUN_0809116c(struct Enemy* p);
void FUN_08091174(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates2[10] = {
    FUN_080902c8,
    FUN_0809070c,
    FUN_08090b24,
    FUN_08090c64,
    FUN_08090da8,
    FUN_08090ee0,
    FUN_0809106c,
    FUN_08091154,
    FUN_0809116c,
    FUN_08091174,
};
// clang-format on

// --------------------------------------------

static const struct Collision sCollisions[12] = {
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 2,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(16), PIXEL(26), PIXEL(26)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : METAL,
      remaining : 0,
      layer : 0xFFFFFFFF,
      range : {PIXEL(0), -PIXEL(16), PIXEL(26), PIXEL(26)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 2,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(17), -PIXEL(25), PIXEL(26), PIXEL(26)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : METAL,
      remaining : 0,
      layer : 0xFFFFFFFF,
      range : {PIXEL(17), -PIXEL(25), PIXEL(26), PIXEL(26)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 2,
      remaining : 2,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(16), PIXEL(26), PIXEL(26)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 1,
      range : {PIXEL(0), -PIXEL(29), PIXEL(10), PIXEL(10)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : METAL,
      remaining : 0,
      layer : 0xFFFFFFFF,
      range : {PIXEL(0), -PIXEL(10), PIXEL(26), PIXEL(14)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 2,
      remaining : 2,
      layer : 0x00000001,
      range : {PIXEL(17), -PIXEL(25), PIXEL(26), PIXEL(26)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 1,
      range : {PIXEL(3), -PIXEL(25), PIXEL(10), PIXEL(10)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : METAL,
      remaining : 0,
      layer : 0xFFFFFFFF,
      range : {PIXEL(22), -PIXEL(25), PIXEL(14), PIXEL(26)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 0,
      hardness : METAL,
      remaining : 0,
      layer : 0xFFFFFFFF,
      range : {PIXEL(0), -PIXEL(16), PIXEL(26), PIXEL(26)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : METAL,
      remaining : 0,
      layer : 0xFFFFFFFF,
      range : {PIXEL(0), -PIXEL(16), PIXEL(26), PIXEL(26)},
    },
};

static const s32 s32_ARRAY_08369728[16] = {1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0};

// clang-format off
static const motion_t sMotions1[6] = {
    MOTION(SM126_PETATRIA, 0),
    MOTION(SM126_PETATRIA, 1),
    MOTION(SM126_PETATRIA, 2),
    MOTION(SM126_PETATRIA, 3),
    MOTION(SM126_PETATRIA, 4),
    MOTION(SM126_PETATRIA, 5),
};
// clang-format on

static const s32 s32_ARRAY_08369774[6] = {
    PIXEL(1), PIXEL(2), PIXEL(5), PIXEL(5), PIXEL(2), PIXEL(1),
};
static const s32 s32_ARRAY_0836978c[6] = {
    PIXEL(1), PIXEL(1), PIXEL(2), PIXEL(5), PIXEL(5), PIXEL(2),
};

// clang-format off
static const motion_t sMotions2[6] = {
    MOTION(SM126_PETATRIA, 6),
    MOTION(SM126_PETATRIA, 7),
    MOTION(SM126_PETATRIA, 8),
    MOTION(SM126_PETATRIA, 9),
    MOTION(SM126_PETATRIA, 10),
    MOTION(SM126_PETATRIA, 11),
};
// clang-format on

static const s32 s32_ARRAY_083697b0[6] = {
    -PIXEL(1), -PIXEL(2), -PIXEL(5), -PIXEL(5), -PIXEL(2), -PIXEL(1),
};
static const s32 s32_ARRAY_083697c8[6] = {
    -PIXEL(1), -PIXEL(1), -PIXEL(2), -PIXEL(5), -PIXEL(5), -PIXEL(2),
};
