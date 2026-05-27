#include "collision.h"
#include "enemy.h"
#include "global.h"

struct EnemyLemmingles {
  OBJECT_HDR;
  // props (16bytes, offset: 0xB4..)
  u8 unk_b4[4];
  s32 unk_b8_x;
  u8 unk_bc[8];
};
static_assert(sizeof(struct EnemyLemmingles) == sizeof(struct Enemy));

void Lemmingles_Init(struct Enemy* p);
void Lemmingles_Update(struct Enemy* p);
void Lemmingles_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gLemminglesRoutine = {
    [ENTITY_INIT] =      (EnemyFunc)Lemmingles_Init,
    [ENTITY_UPDATE] =    (EnemyFunc)Lemmingles_Update,
    [ENTITY_DIE] =       (EnemyFunc)Lemmingles_Die,
    [ENTITY_DISAPPEAR] = (EnemyFunc)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

void FUN_0806e590(struct Entity* e, u8 kind1, u8 kind2, u8 kind3) {
  struct EnemyLemmingles* p = (struct EnemyLemmingles*)AllocEntityFirst(gEnemyHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(p, ENEMY_LEMMINGLES);
    (p->s).tileNum = 0, (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).coord.x = e->coord.x;
    (p->s).coord.y = e->coord.y;
    (p->s).unk_28 = (void*)e;
    (p->s).work[0] = kind1;
    (p->s).work[1] = kind3;
    (p->s).work[2] = kind2;
    p->unk_b8_x = e->coord.x;
  }
}

// 0x0806e600
static void onCollision(struct Body* body UNUSED, struct Coord* r1 UNUSED, struct Coord* r2 UNUSED) { return; }

INCASM("asm/enemy/lemmingles_p1.inc");

void nop_0806e96c(struct Enemy* p) {}

INCASM("asm/enemy/lemmingles_p2_p1.inc");

void FUN_0806e970(struct Enemy* p) {
  if (((p->body).status & 0x00020001) == 0x00020001) {
    (p->s).mode[1] = 6;
    (p->s).mode[2] = 0;
  }
}

INCASM("asm/enemy/lemmingles_p2_p2.inc");

// --------------------------------------------

void FUN_0806e990(struct Enemy* p);
void FUN_0806e970(struct Enemy* p);
void nop_0806e96c(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates1[7] = {
    FUN_0806e990,
    FUN_0806e970,
    FUN_0806e970,
    FUN_0806e970,
    FUN_0806e970,
    FUN_0806e970,
    nop_0806e96c,
};
// clang-format on

void FUN_0806e9fc(struct Enemy* p);
void FUN_0806ea64(struct Enemy* p);
void FUN_0806ed08(struct Enemy* p);
void FUN_0806ee0c(struct Enemy* p);
void FUN_0806ee94(struct Enemy* p);
void FUN_0806efa4(struct Enemy* p);
void FUN_0806f07c(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates2[7] = {
    FUN_0806e9fc,
    FUN_0806ea64,
    FUN_0806ed08,
    FUN_0806ee0c,
    FUN_0806ee94,
    FUN_0806efa4,
    FUN_0806f07c,
};
// clang-format on

// --------------------------------------------

void FUN_0806f1dc(struct Enemy* p);
void FUN_0806f274(struct Enemy* p);
void FUN_0806f07c(struct Enemy* p);

static const EnemyFunc sDeads[3] = {
    FUN_0806f1dc,
    FUN_0806f274,
    FUN_0806f07c,
};

// --------------------------------------------

static const struct Collision sCollisions[7] = {
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 0,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(8), PIXEL(8)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 2,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(7), PIXEL(24), PIXEL(15)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(7), PIXEL(24), PIXEL(15)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(7), PIXEL(24), PIXEL(15)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(7), PIXEL(24), PIXEL(15)},
    },
    {
      kind : DDP,
      faction : FACTION_NEUTRAL,
      special : 0,
      damage : 2,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(7), PIXEL(24), PIXEL(15)},
    },
    {
      kind : DDP,
      faction : FACTION_NEUTRAL,
      special : 0,
      damage : 4,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(7), PIXEL(24), PIXEL(15)},
    },
};

static const struct Coord sElementCoord = {PIXEL(0), -PIXEL(8)};
static const u8 sInitModes[4] = {1, 1, 1, 1};

// clang-format off
static const motion_t sMotions[13] = {
    MOTION(SM029_LEMMINGLES, 1),
    MOTION(SM029_LEMMINGLES, 0),
    MOTION(SM029_LEMMINGLES, 3),
    MOTION(SM029_LEMMINGLES, 2),
    // --------------------------------------------
    MOTION(SM029_LEMMINGLES, 1),
    MOTION(SM029_LEMMINGLES, 5),
    MOTION(SM029_LEMMINGLES, 3),
    MOTION(SM029_LEMMINGLES, 11),
    // --------------------------------------------
    MOTION(SM029_LEMMINGLES, 22),
    MOTION(SM029_LEMMINGLES, 23),
    MOTION(SM029_LEMMINGLES, 24),
    // --------------------------------------------
    MOTION(SM029_LEMMINGLES, 19),
    MOTION(SM029_LEMMINGLES, 17),
};


