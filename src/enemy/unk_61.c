#include "collision.h"
#include "enemy.h"
#include "global.h"

static const EnemyFunc sUpdates1[1];
static const EnemyFunc sUpdates2[1];

void FUN_080935b4(struct Entity* e, u8 a1, u8 a2) {
  struct Enemy* p = (struct Enemy*)AllocEntityFirst(gEnemyHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(p, ENEMY_61);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).work[0] = 0;
    (p->s).coord.x = e->coord.x;
    (p->s).coord.y = FUN_08009f6c(e->coord.x, e->coord.y) - (a2 << 12) - 0x1c00;
    (p->s).work[2] = a1;
    (p->s).unk_28 = e;
  }
}

void nop_0809362c(struct Enemy* p) {}

INCASM("asm/enemy/unk_61_p2_p1.inc");

void Enemy61_Update(struct Enemy* p) {
  if (((struct Entity*)(p->s).unk_28)->mode[0] > 1) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
  } else {
    (sUpdates1[(p->s).mode[1]])(p);
    (sUpdates2[(p->s).mode[1]])(p);
  }
}

INCASM("asm/enemy/unk_61_p2_p2.inc");

void FUN_08093754(struct Enemy* p) {}

INCASM("asm/enemy/unk_61_p3.inc");

void Enemy61_Init(struct Enemy* p);
void Enemy61_Update(struct Enemy* p);
void Enemy61_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gEnemy61Routine = {
    [ENTITY_INIT] =      Enemy61_Init,
    [ENTITY_UPDATE] =    Enemy61_Update,
    [ENTITY_DIE] =       Enemy61_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

void FUN_08093754(struct Enemy* p);

static const EnemyFunc sUpdates1[1] = {
    FUN_08093754,
};

void FUN_08093758(struct Enemy* p);

static const EnemyFunc sUpdates2[1] = {
    FUN_08093758,
};

// --------------------------------------------

static const struct Collision sCollisions[7] = {
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(8), PIXEL(8)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(36), PIXEL(0), PIXEL(18), PIXEL(23)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {PIXEL(36), PIXEL(0), PIXEL(18), PIXEL(23)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 1,
      layer : 0x00000001,
      range : {-PIXEL(36), PIXEL(0), PIXEL(18), PIXEL(23)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {-PIXEL(36), PIXEL(0), PIXEL(18), PIXEL(23)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(36), PIXEL(0), PIXEL(18), PIXEL(23)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 0,
      layer : 0x00000001,
      range : {-PIXEL(36), PIXEL(0), PIXEL(18), PIXEL(23)},
    },
};

static const s8 s8_ARRAY_08369de8[24] = {
    -3, -3, -2, -2, -1, -1, 0, 0, 1, 1, 2, 2, 2, 2, 1, 1, 0, 0, -1, -1, -2, -2, -3, -3,
};

static const u8 sInitModes[4] = {0, 0, 0, 0};
