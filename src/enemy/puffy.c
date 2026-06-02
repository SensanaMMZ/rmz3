#include "collision.h"
#include "enemy.h"
#include "global.h"
#include "overworld_terrain.h"

struct Enemy* CreatePuffy(struct Coord* c, u8 mode) {
  struct Enemy* p = (struct Enemy*)AllocEntityFirst(gEnemyHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(p, ENEMY_PUFFY);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).coord = *c;
    (p->s).work[0] = mode;
  }
  return p;
}

INCASM("asm/enemy/puffy_p1_p2_a.inc");

extern const EnemyFunc PTR_ARRAY_08367aec[4];
extern const EnemyFunc PTR_ARRAY_08367afc[4];
void FUN_0807cb50(struct Enemy* p);
void Puffy_Die(struct Enemy* p);

void Puffy_Update(struct Enemy* p) {
  if ((p->body).status & BODY_STATUS_DEAD) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    Puffy_Die(p);
  } else {
    (PTR_ARRAY_08367aec[(p->s).mode[1]])(p);
    FUN_0807cb50(p);
    if (IsFrozen(&p->s)) {
      u8 m = (p->s).mode[1];
      *(u8*)((u8*)p + 0xba) = m;
    } else {
      (PTR_ARRAY_08367afc[(p->s).mode[1]])(p);
    }
  }
}

INCASM("asm/enemy/puffy_p1_p2_c.inc");

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


void nop_0807cacc(struct Enemy* p) {}

bool8 nop_0807cad0(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/puffy_p5_p1.inc");

void FUN_0807cba4(struct Body* body) {
  struct Enemy* parent = (struct Enemy*)body->parent;
  if ((*(u32*)((u8*)parent + 0x8c) & 0x200) && (gCollisionManager.sweep & 2)) {
    *(u8*)((u8*)parent + 0xc0) = 0;
  }
}

int dragInSea(struct Entity* p) {
  s32 sea = gOverworld.sea;
  if (sea > p->coord.y) {
    p->coord.y = sea;
  }
}

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
