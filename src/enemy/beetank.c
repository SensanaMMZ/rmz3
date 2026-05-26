#include "collision.h"
#include "enemy.h"
#include "global.h"

void Beetank_Init(struct Enemy* p);
void Beetank_Update(struct Enemy* p);
void Beetank_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gBeetankRoutine = {
    [ENTITY_INIT] =      Beetank_Init,
    [ENTITY_UPDATE] =    Beetank_Update,
    [ENTITY_DIE] =       Beetank_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

struct Enemy* CreateBeetank(struct Coord* c, u8 n) {
  struct Enemy* p = (struct Enemy*)AllocEntityFirst(gEnemyHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(p, ENEMY_BEETANK);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).coord = *c;
    (p->s).work[0] = n;
  }
  return p;
}

INCASM("asm/enemy/beetank_p1.inc");

bool8 nop_0807bc8c(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/beetank_p2.inc");

bool8 nop_0807bd3c(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/beetank_p3.inc");

bool8 nop_0807bde4(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/beetank_p4.inc");

bool8 FUN_0807be14(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/beetank_p5_p1.inc");

void nop_0807be18(struct Enemy* p) {}

INCASM("asm/enemy/beetank_p5_p2.inc");

bool8 FUN_0807be1c(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/beetank_p6_p1.inc");

void nop_0807bea4(struct Enemy* p) {}

INCASM("asm/enemy/beetank_p6_p2.inc");

bool8 nop_0807bc8c(struct Enemy* p);
bool8 nop_0807bd3c(struct Enemy* p);
bool8 nop_0807bde4(struct Enemy* p);
bool8 FUN_0807be14(struct Enemy* p);
bool8 FUN_0807be1c(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates1[5] = {
    (EnemyFunc)nop_0807bc8c,
    (EnemyFunc)nop_0807bd3c,
    (EnemyFunc)nop_0807bde4,
    (EnemyFunc)FUN_0807be14,
    (EnemyFunc)FUN_0807be1c,
};
// clang-format on

void FUN_0807bc90(struct Enemy* p);
void FUN_0807bd40(struct Enemy* p);
void FUN_0807bde8(struct Enemy* p);
void nop_0807be18(struct Enemy* p);
void FUN_0807be20(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates2[5] = {
    FUN_0807bc90,
    FUN_0807bd40,
    FUN_0807bde8,
    nop_0807be18,
    FUN_0807be20,
};
// clang-format on

// --------------------------------------------

static const struct Collision sCollisions[2] = {
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 2,
      atkType : 0x00,
      element : 0x00,
      nature : 0x00,
      comboLv : 0,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(10), PIXEL(24), PIXEL(24)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(10), PIXEL(24), PIXEL(24)},
    },
};

static const struct Coord sElementCoord = {PIXEL(0), -PIXEL(8)};
