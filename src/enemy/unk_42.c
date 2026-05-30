#include "collision.h"
#include "enemy.h"
#include "global.h"

// ブリザック・スタグロフ関連？

static void Enemy42_Init(struct Entity* p);
static void Enemy42_Update(struct Entity* p);
static void Enemy42_Die(struct Entity* p);

// clang-format off
const EnemyRoutine gEnemy42Routine = {
    [ENTITY_INIT] =      (EnemyFunc)Enemy42_Init,
    [ENTITY_UPDATE] =    (EnemyFunc)Enemy42_Update,
    [ENTITY_DIE] =       (EnemyFunc)Enemy42_Die,
    [ENTITY_DISAPPEAR] = (EnemyFunc)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

struct Entity* CreateEnemy42(struct Entity* e, u8 type, u8 param_3) {
  struct Entity* p = AllocEntityFirst(gEnemyHeaderPtr);
  if (p != NULL) {
    p->taskCol = 24;
    INIT_ENEMY_ROUTINE(p, ENEMY_42);
    p->tileNum = 0, p->palID = 0;
    p->flags2 |= WHITE_PAINTABLE;
    p->invincibleID = p->uniqueID;
    p->work[0] = type, p->work[1] = param_3;
    p->unk_28 = e;
    p->coord = *(&e->coord);
    return p;
  } else {
    return NULL;
  }
}

// --------------------------------------------

void FUN_08084e7c(struct Enemy* p);
void FUN_08084f18(struct Enemy* p);
void FUN_08084fb4(struct Enemy* p);

static void Enemy42_Init(struct Entity* p) {
  static const EnemyFunc sInitializers[3] = {
      (EnemyFunc)FUN_08084e7c,
      (EnemyFunc)FUN_08084f18,
      (EnemyFunc)FUN_08084fb4,
  };
  (sInitializers[(p->work)[0]])((void*)p);
}

void FUN_08085060(struct Enemy* p);
void FUN_08085124(struct Enemy* p);
void FUN_080852f4(struct Enemy* p);

static void Enemy42_Update(struct Entity* p) {
  static const EnemyFunc sUpdates[3] = {
      (EnemyFunc)FUN_08085060,
      (EnemyFunc)FUN_08085124,
      (EnemyFunc)FUN_080852f4,
  };
  (sUpdates[(p->work)[0]])((void*)p);
}

void FUN_0808534c(struct Enemy* p);
void FUN_0808537c(struct Enemy* p);
static void FUN_08085578(struct Entity* p);

static void Enemy42_Die(struct Entity* p) {
  static const EnemyFunc sDeads[3] = {
      (EnemyFunc)FUN_0808534c,
      (EnemyFunc)FUN_0808537c,
      (EnemyFunc)FUN_08085578,
  };
  (sDeads[(p->work)[0]])((void*)p);
}

INCASM("asm/enemy/unk_42_p1.inc");

void FUN_0808534c(struct Enemy* p) {
  EXIT_BODY(p);
  SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
}

INCASM("asm/enemy/unk_42_p2.inc");

// --------------------------------------------

static void FUN_08085578(struct Entity* p) { SET_ENEMY_ROUTINE(p, ENTITY_EXIT); }

// --------------------------------------------

static const struct Collision sCollisions[6] = {
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      atkType : 0x00,
      element : 0x00,
      nature : 0x00,
      comboLv : 0,
      hitzone : 4,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(4), -PIXEL(30), PIXEL(8), PIXEL(60)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      damage : 4,
      LAYER(0xFFFFFFFF),
      hitzone : 4,
      remaining : 0,
      range : {PIXEL(4), -PIXEL(30), PIXEL(8), PIXEL(60)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      atkType : 0x00,
      element : 0x00,
      nature : 0x00,
      comboLv : 0,
      hitzone : 4,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(8), -PIXEL(29), PIXEL(16), PIXEL(62)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      damage : 4,
      LAYER(0xFFFFFFFF),
      hitzone : 4,
      remaining : 0,
      range : {PIXEL(8), -PIXEL(29), PIXEL(16), PIXEL(62)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      atkType : 0x00,
      element : 0x00,
      nature : 0x00,
      comboLv : 0,
      hitzone : 4,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(11), -PIXEL(28), PIXEL(22), PIXEL(64)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      damage : 4,
      LAYER(0xFFFFFFFF),
      hitzone : 4,
      remaining : 0,
      range : {PIXEL(11), -PIXEL(28), PIXEL(22), PIXEL(64)},
    },
};
