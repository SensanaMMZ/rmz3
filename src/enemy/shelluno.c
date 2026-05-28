#include "collision.h"
#include "enemy.h"
#include "global.h"

struct Enemy* CreateShelluno(struct Coord* c, u8 mode) {
  struct Enemy* p = (struct Enemy*)AllocEntityFirst(gEnemyHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(p, ENEMY_SHELLUNO);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).coord = *c;
    (p->s).work[0] = mode;
  }
  return p;
}

INCASM("asm/enemy/shelluno_p1_p2.inc");

bool8 nop_0807939c(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/shelluno_p2.inc");

bool8 FUN_0807a018(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/shelluno_p3.inc");

bool8 FUN_0807a064(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/shelluno_p4_p1.inc");

void FUN_0807a068(struct Enemy* p) {}

INCASM("asm/enemy/shelluno_p4_p2.inc");

bool8 FUN_0807a06c(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/shelluno_p5.inc");

bool8 FUN_0807a0fc(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/shelluno_p6.inc");

bool8 FUN_0807a3e8(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/shelluno_p7.inc");

void Shelluno_Init(struct Enemy* p);
void Shelluno_Update(struct Enemy* p);
void Shelluno_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gShellunoRoutine = {
    [ENTITY_INIT] =      Shelluno_Init,
    [ENTITY_UPDATE] =    Shelluno_Update,
    [ENTITY_DIE] =       Shelluno_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

bool8 nop_0807939c(struct Enemy* p);
void FUN_080795b8(struct Enemy* p);
bool8 FUN_0807a018(struct Enemy* p);
bool8 FUN_0807a064(struct Enemy* p);
bool8 FUN_0807a06c(struct Enemy* p);
bool8 FUN_0807a0fc(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates1[6] = {
    (EnemyFunc)nop_0807939c,
    FUN_080795b8,
    (EnemyFunc)FUN_0807a018,
    (EnemyFunc)FUN_0807a064,
    (EnemyFunc)FUN_0807a06c,
    (EnemyFunc)FUN_0807a0fc,
};
// clang-format on

void shelluno_080793a0(struct Enemy* p);
void FUN_080795f0(struct Enemy* p);
void FUN_0807a01c(struct Enemy* p);
void FUN_0807a068(struct Enemy* p);
void shelluno_0807a070(struct Enemy* p);
void shelluno_0807a100(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates2[6] = {
    shelluno_080793a0,
    FUN_080795f0,
    FUN_0807a01c,
    FUN_0807a068,
    shelluno_0807a070,
    shelluno_0807a100,
};
// clang-format on

// --------------------------------------------

static const struct Collision sCollisions[6] = {
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(7), PIXEL(18), PIXEL(18)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : METAL,
      remaining : 0,
      priorityLayer : 0xFFFFFFFF,
      range : {PIXEL(0), -PIXEL(7), PIXEL(18), PIXEL(18)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(7), PIXEL(18), PIXEL(18)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(7), PIXEL(18), PIXEL(18)},
    },
    {
      kind : DDP,
      faction : FACTION_NEUTRAL,
      damage : 3,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(10), PIXEL(18), PIXEL(25)},
    },
    {
      kind : DRP,
      faction : FACTION_NEUTRAL,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(10), PIXEL(18), PIXEL(25)},
    },
};

static const struct Coord sElementCoord = {PIXEL(0), -PIXEL(9)};
