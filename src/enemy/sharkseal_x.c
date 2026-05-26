#include "collision.h"
#include "enemy.h"
#include "global.h"

INCASM("asm/enemy/sharkseal_x_p1.inc");

bool8 FUN_080707d0(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/sharkseal_x_p2.inc");

bool8 FUN_080707d8(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/sharkseal_x_p3.inc");

bool8 FUN_080708dc(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/sharkseal_x_p4.inc");

bool8 FUN_08070990(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/sharkseal_x_p5.inc");

bool8 FUN_08070c68(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/sharkseal_x_p6.inc");

bool8 FUN_08070f3c(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/sharkseal_x_p7.inc");

bool8 FUN_08070f8c(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/sharkseal_x_p8.inc");

bool8 FUN_08070f94(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/sharkseal_x_p9.inc");

bool8 nop_080711d4(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/sharkseal_x_p10.inc");

void SharksealX_Init(struct Enemy* p);
void SharksealX_Update(struct Enemy* p);
void SharksealX_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gSharksealXRoutine = {
    [ENTITY_INIT] =      SharksealX_Init,
    [ENTITY_UPDATE] =    SharksealX_Update,
    [ENTITY_DIE] =       SharksealX_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

bool8 FUN_080707d0(struct Enemy* p);
bool8 FUN_080707d8(struct Enemy* p);
bool8 FUN_080708dc(struct Enemy* p);
bool8 FUN_08070990(struct Enemy* p);
bool8 FUN_08070c68(struct Enemy* p);
bool8 FUN_08070f3c(struct Enemy* p);
bool8 FUN_08070f8c(struct Enemy* p);
bool8 FUN_08070f94(struct Enemy* p);

// clang-format off
static const EnemyFunc PTR_ARRAY_08366a04[8] = {
    (EnemyFunc)FUN_080707d0,
    (EnemyFunc)FUN_080707d8,
    (EnemyFunc)FUN_080708dc,
    (EnemyFunc)FUN_08070990,
    (EnemyFunc)FUN_08070c68,
    (EnemyFunc)FUN_08070f3c,
    (EnemyFunc)FUN_08070f8c,
    (EnemyFunc)FUN_08070f94,
};
// clang-format on

void nop_080707d4(struct Enemy* p);
void sharksealxMode1(struct Enemy* p);
void sharksealxMode2(struct Enemy* p);
void sharksealxMode3(struct Enemy* p);
void sharksealxMode4(struct Enemy* p);
void sharksealxMode5(struct Enemy* p);
void nop_08070f90(struct Enemy* p);
void sharksealxMode7(struct Enemy* p);

// clang-format off
const EnemyFunc PTR_ARRAY_08366a24[8] = {
    nop_080707d4,
    sharksealxMode1,
    sharksealxMode2,
    sharksealxMode3,
    sharksealxMode4,
    sharksealxMode5,
    nop_08070f90,
    sharksealxMode7,
};
// clang-format on

static const struct Collision sCollisions[] = {
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 2,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(5), PIXEL(0), PIXEL(30), PIXEL(9)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      range : {PIXEL(5), PIXEL(0), PIXEL(32), PIXEL(11)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 2,
      remaining : 1,
      layer : 0x00000001,
      range : {-PIXEL(4), PIXEL(1), PIXEL(18), PIXEL(12)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      range : {-PIXEL(5), PIXEL(1), PIXEL(18), PIXEL(12)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      range : {PIXEL(5), PIXEL(0), PIXEL(32), PIXEL(11)},
    },
};

static const struct Coord sElementCoord = {PIXEL(0), PIXEL(0)};
