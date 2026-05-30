#include "collision.h"
#include "enemy.h"
#include "global.h"
#include "sound.h"
#include "vfx.h"

static void Enemy14_Init(struct Enemy* p);
void Enemy14_Update(struct Enemy* p);
void Enemy14_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gTopGabyoallRoutine = {
    [ENTITY_INIT] =      (EnemyFunc)Enemy14_Init,
    [ENTITY_UPDATE] =    (EnemyFunc)Enemy14_Update,
    [ENTITY_DIE] =       (EnemyFunc)Enemy14_Die,
    [ENTITY_DISAPPEAR] = (EnemyFunc)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

struct Entity* CreateTopGabyoall(struct Coord* c, u8 r1, u8 r2) {
  struct Entity* p = AllocEntityFirst(gEnemyHeaderPtr);
  if (p != NULL) {
    p->taskCol = 24;
    INIT_ENEMY_ROUTINE(p, ENEMY_TOP_GABYOALL);
    p->tileNum = 0;
    p->palID = 0;
    p->flags2 |= WHITE_PAINTABLE;
    p->invincibleID = p->uniqueID;
    p->work[0] = r1;
    p->work[1] = r2;
    p->coord = *c;
    return p;
  } else {
    return NULL;
  }
}

// --------------------------------------------

void FUN_0806f5d0(struct Enemy* p);
void FUN_0806f6cc(struct Enemy* p);
void FUN_0806f7dc(struct Enemy* p);
void FUN_0806f89c(struct Enemy* p);

static void Enemy14_Init(struct Enemy* p) {
  static const EnemyFunc sInitializers[4] = {
      (EnemyFunc)FUN_0806f5d0,
      (EnemyFunc)FUN_0806f6cc,
      (EnemyFunc)FUN_0806f7dc,
      (EnemyFunc)FUN_0806f89c,
  };
  (sInitializers[(p->s).work[0]])((void*)p);
}

// --------------------------------------------

void FUN_0806f964(struct Enemy* p);
void FUN_0806fb08(struct Enemy* p);
void FUN_0806fc78(struct Enemy* p);
void FUN_0806fe38(struct Enemy* p);

static const EnemyFunc PTR_ARRAY_08366960[4] = {
    (EnemyFunc)FUN_0806f964,
    (EnemyFunc)FUN_0806fb08,
    (EnemyFunc)FUN_0806fc78,
    (EnemyFunc)FUN_0806fe38,
};

// --------------------------------------------

INCASM("asm/enemy/top_gabyoall_p1.inc");

void Enemy14_Die(struct Enemy* p) {
  CreateSmoke(1, &(p->s).coord);
  PlaySound(0x2a);
  (p->s).flags &= ~DISPLAY;
  SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
}

INCASM("asm/enemy/top_gabyoall_p2.inc");

// 0x08070000
void FUN_08070000(struct Body* body, struct Coord* r1 UNUSED, struct Coord* r2 UNUSED) {
  if (body->hitboxFlags & (BODY_STATUS_WHITE | BODY_STATUS_B3)) {
    struct Entity* self = (struct Entity*)body->parent;
    if (self->mode[1] != 2) {
      self->mode[1] = 2;
      self->mode[2] = 0;
    } else {
      self->work[2] = 64;
    }
  }
}

// --------------------------------------------

static const struct Collision sCollisions[] = {
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 2,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(8), PIXEL(24), PIXEL(12)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : NO_DAMAGE,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(8), PIXEL(24), PIXEL(12)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 2,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(8), PIXEL(12), PIXEL(24)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : NO_DAMAGE,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(8), PIXEL(12), PIXEL(24)},
    },
};

static const struct Coord sElementCoords[4] = {
    {0x00000000, -0x00000800},
    {0x00000000, -0x00000800},
    {0x00000000, -0x00000800},
    {0x00000000, 0x00000800},
};
