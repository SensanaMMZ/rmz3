#include "collision.h"
#include "enemy.h"
#include "global.h"

INCASM("asm/enemy/pantheon_bomber_p1.inc");

bool8 nop_08086338(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/pantheon_bomber_p2.inc");

bool8 nop_080863a0(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/pantheon_bomber_p3.inc");

bool8 nop_08086414(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/pantheon_bomber_p4.inc");

bool8 nop_080865d0(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/pantheon_bomber_p5.inc");

bool8 nop_080865f8(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/pantheon_bomber_p6_p1.inc");

void nop_080865fc(struct Enemy* p) {}

INCASM("asm/enemy/pantheon_bomber_p6_p2.inc");

bool8 nop_08086600(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/pantheon_bomber_p7.inc");

void PantheonBomber_Init(struct Enemy* p);
void PantheonBomber_Update(struct Enemy* p);
void PantheonBomber_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gPantheonBomberRoutine = {
    [ENTITY_INIT] =      PantheonBomber_Init,
    [ENTITY_UPDATE] =    PantheonBomber_Update,
    [ENTITY_DIE] =       PantheonBomber_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

bool8 nop_08086338(struct Enemy* p);
bool8 nop_080863a0(struct Enemy* p);
bool8 nop_08086414(struct Enemy* p);
bool8 nop_080865d0(struct Enemy* p);
bool8 nop_080865f8(struct Enemy* p);
bool8 nop_08086600(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates1[6] = {
    (EnemyFunc)nop_08086338,
    (EnemyFunc)nop_080863a0,
    (EnemyFunc)nop_08086414,
    (EnemyFunc)nop_080865d0,
    (EnemyFunc)nop_080865f8,
    (EnemyFunc)nop_08086600,
};
// clang-format on

void pantheon_bomber_0808633c(struct Enemy* p);
void pantheon_bomber_080863a4(struct Enemy* p);
void pantheon_bomber_08086418(struct Enemy* p);
void FUN_080865d4(struct Enemy* p);
void nop_080865fc(struct Enemy* p);
void FUN_08086604(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates2[6] = {
    pantheon_bomber_0808633c,
    pantheon_bomber_080863a4,
    pantheon_bomber_08086418,
    FUN_080865d4,
    nop_080865fc,
    FUN_08086604,
};
// clang-format on

// --------------------------------------------

static const struct Collision sCollisions[5] = {
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 0,
      hardness : METAL,
      remaining : 0,
      layer : 0xFFFFFFFF,
      range : {PIXEL(0), -PIXEL(7), PIXEL(22), PIXEL(19)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(7), PIXEL(22), PIXEL(19)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(7), PIXEL(22), PIXEL(19)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(7), PIXEL(22), PIXEL(19)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(7), PIXEL(22), PIXEL(19)},
    },
};

static const struct Coord sElementCoord = {PIXEL(0), PIXEL(0)};
