#include "collision.h"
#include "enemy.h"
#include "global.h"

INCASM("asm/enemy/puffy_p1.inc");

bool8 nop_0807c968(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/puffy_p2.inc");

bool8 nop_0807ca98(struct Enemy* p) { return TRUE; }

void FUN_0807ca9c(struct Enemy* p) {
  struct Entity** slot;
  if ((p->s).mode[2] == 0) (p->s).mode[2] = 1;
  slot = (struct Entity**)((u8*)p + 0xbc);
  if (isKilled(*slot)) {
    *slot = NULL;
    (p->s).mode[1] = 0;
    (p->s).mode[2] = 0;
  }
}

bool8 nop_0807cac8(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/puffy_p4_p1.inc");

void nop_0807cacc(struct Enemy* p) {}

INCASM("asm/enemy/puffy_p4_p2.inc");

bool8 nop_0807cad0(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/puffy_p5.inc");

void Puffy_Init(struct Enemy* p);
void Puffy_Update(struct Enemy* p);
void Puffy_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gPuffyRoutine = {
    [ENTITY_INIT] =      Puffy_Init,
    [ENTITY_UPDATE] =    Puffy_Update,
    [ENTITY_DIE] =       Puffy_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

bool8 nop_0807c968(struct Enemy* p);
bool8 nop_0807ca98(struct Enemy* p);
bool8 nop_0807cac8(struct Enemy* p);
bool8 nop_0807cad0(struct Enemy* p);

static const EnemyFunc PTR_ARRAY_08367aec[4] = {
    (EnemyFunc)nop_0807c968,
    (EnemyFunc)nop_0807ca98,
    (EnemyFunc)nop_0807cac8,
    (EnemyFunc)nop_0807cad0,
};

void FUN_0807c96c(struct Enemy* p);
void FUN_0807ca9c(struct Enemy* p);
void nop_0807cacc(struct Enemy* p);
void FUN_0807cad4(struct Enemy* p);

static const EnemyFunc PTR_ARRAY_08367afc[4] = {
    FUN_0807c96c,
    FUN_0807ca9c,
    nop_0807cacc,
    FUN_0807cad4,
};

// --------------------------------------------

static const struct Collision sCollisions[2] = {
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      atkType : 0x00,
      comboLv : 0,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(6), PIXEL(28), PIXEL(28)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(6), PIXEL(28), PIXEL(28)},
    },
};

static const struct Coord sElementCoord = {PIXEL(0), PIXEL(0)};
