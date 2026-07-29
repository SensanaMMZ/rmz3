#include "collision.h"
#include "enemy.h"
#include "global.h"
#include "text.h"
#include "minigame.h"

static const EnemyFunc sDeads[4];

#include "entity/macros.h"

void FUN_08099f54(s32 x, s32 y, s32 a, s32 b) {
  struct Enemy* p = (struct Enemy*)AllocEntityFirst(gEnemyHeaderPtr);

  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(p, 68);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).work[0] = 6;
    (p->s).coord.x = x;
    (p->s).coord.y = y;
    (p->s).unk_coord.y = a;
    (p->s).d.x = b;
  }
}

void FUN_08099fb8(struct Entity* e, s32 y, u8 n, u8 w) {
  struct Enemy* p = (struct Enemy*)AllocEntityFirst(gEnemyHeaderPtr);

  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(p, 68);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).work[0] = w;
    (p->s).coord.x = n * 0x13000 + 0xD000;
    (p->s).coord.y = y;
    (p->s).work[2] = n;
    (p->s).unk_28 = e;
  }
}

// 0x0809a02c
struct Enemy* FUN_0809a02c(void* parent, u8 n) {
  struct Enemy* e = (struct Enemy*)AllocEntityFirst(gEnemyHeaderPtr);
  if (e != NULL) {
    s32 x;
    s32 y;
    (e->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(e, 68);
    (e->s).tileNum = 0;
    (e->s).palID = 0;
    (e->s).flags2 |= WHITE_PAINTABLE;
    (e->s).invincibleID = (e->s).uniqueID;
    (e->s).work[0] = 4;
    x = 0x16800;
    (e->s).coord.x = x;
    y = 0x41000;
    (e->s).coord.y = y;
    (e->s).coord.y = FUN_08009f6c(x, y);
    y = (e->s).coord.x;
    y -= 0x9800;
    y += n * 0x13000;
    (e->s).coord.x = y;
    (e->s).work[2] = n;
    (e->s).unk_28 = parent;
  }
  return e;
}

void nop_0809a0b4(struct Enemy* p) {}

static const struct Collision sCollisions[6];
static const u8 u8_ARRAY_0836a764[6];
static const u8 u8_ARRAY_0836a76a[8];
static const motion_t sMotions[12];
static const EnemyFunc sUpdates1[7];
static const EnemyFunc sUpdates2[7];

void LeviathanMinigameEnemy_Die(struct Enemy* p);
void LeviathanMinigameEnemy_Update(struct Enemy* p);

bool8 FUN_0809a0b8(struct Enemy* p) {
  if ((p->body).status & 0x200) {
    *(u8*)((u8*)(p->s).unk_28 + 0x31) = 10;
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    (p->s).mode[1] = u8_ARRAY_0836a764[(p->s).work[0]];
    LeviathanMinigameEnemy_Die(p);
    return TRUE;
  }
  return FALSE;
}

void LeviathanMinigameEnemy_Init(struct Enemy* p) {
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  (p->s).mode[1] = u8_ARRAY_0836a76a[(p->s).work[0]];
  (p->s).flags |= FLIPABLE;
  (p->s).flags |= DISPLAY;
  InitNonAffineMotion(&p->s);
  if ((p->s).work[0] != 6) {
    SetMotion(&p->s, sMotions[(p->s).work[0]]);
  }
  UpdateMotionGraphic(&p->s);
  INIT_BODY(p, sCollisions, 1, (void*)nop_0809a0b4);
  LeviathanMinigameEnemy_Update(p);
}

void LeviathanMinigameEnemy_Update(struct Enemy* p) {
  if (!FUN_0809a0b8(p)) {
    sUpdates1[(p->s).mode[1]](p);
    sUpdates2[(p->s).mode[1]](p);
  }
}

void LeviathanMinigameEnemy_Die(struct Enemy* p) {
  (sDeads[(p->s).mode[1]])(p);
}

void nop_0809a1ec(struct Enemy* p) {}

INCASM("asm/enemy/minigame_leviathan_p3.inc");

extern const u8 StrMISS[];
extern const u8 StrSEC[];

// One register from a match: retail truncates the row argument in place
// (lsls/lsrs on the variable's register plus a copy to r2) where agbcc
// shifts directly into the argument register in every spelling tried.
NON_MATCH void FUN_0809aa10(struct Sprite* spr, struct DrawPivot* pivot) {
#if MODERN
  struct Entity* e = (struct Entity*)spr->sprites;
  s32 x = (e->coord.x - pivot->lefttop.x) >> 8;
  s32 y = (e->coord.y - pivot->lefttop.y) >> 8;
  x -= 0x10;
  x /= 8;
  if (x < 0) {
    x = 0;
  } else if (x + 4 > 0x1E) {
    x = 0x1A;
  }
  y += 0x10;
  y /= 8;
  if (y <= 0) {
    y = 1;
  } else if (y > 0x11) {
    y = 0x11;
  }
  PrintUnicodeString((const char_t*)StrMISS, x, y);
  PrintUnicodeString((const char_t*)StrSEC, x + 2, ++y);
  PrintMinigameNumber(e->d.x, (u16)x, (u16)y);
#else
  INCCODE("asm/enemy/leviathan_aa10.inc");
#endif
}

INCASM("asm/enemy/minigame_leviathan_p3b.inc");

void LeviathanMinigameEnemy_Init(struct Enemy* p);
void LeviathanMinigameEnemy_Update(struct Enemy* p);
void LeviathanMinigameEnemy_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gLeviathanMinigameEnemyRoutine = {
    [ENTITY_INIT] =      LeviathanMinigameEnemy_Init,
    [ENTITY_UPDATE] =    LeviathanMinigameEnemy_Update,
    [ENTITY_DIE] =       LeviathanMinigameEnemy_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

void nop_0809a1ec(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates1[7] = {
    nop_0809a1ec,
    nop_0809a1ec,
    nop_0809a1ec,
    nop_0809a1ec,
    nop_0809a1ec,
    nop_0809a1ec,
    nop_0809a1ec,
};
// clang-format on

void FUN_0809a1f0(struct Enemy* p);
void FUN_0809a31c(struct Enemy* p);
void FUN_0809a4bc(struct Enemy* p);
void FUN_0809a5e0(struct Enemy* p);
void FUN_0809a700(struct Enemy* p);
void FUN_0809a90c(struct Enemy* p);
void FUN_0809ab28(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates2[7] = {
    FUN_0809a1f0,
    FUN_0809a31c,
    FUN_0809a4bc,
    FUN_0809a5e0,
    FUN_0809a700,
    FUN_0809a90c,
    FUN_0809ab28,
};
// clang-format on

// --------------------------------------------

void FUN_0809ac28(struct Enemy* p);
void FUN_0809acdc(struct Enemy* p);
void FUN_0809ad8c(struct Enemy* p);
void FUN_0809ae68(struct Enemy* p);

static const EnemyFunc sDeads[4] = {
    FUN_0809ac28,
    FUN_0809acdc,
    FUN_0809ad8c,
    FUN_0809ae68,
};

// --------------------------------------------

static const struct Collision sCollisions[6] = {
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
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {PIXEL(6), PIXEL(1), PIXEL(20), PIXEL(8)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {PIXEL(1), -PIXEL(8), PIXEL(12), PIXEL(12)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {PIXEL(4), PIXEL(1), PIXEL(33), PIXEL(10)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(11), PIXEL(11)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {PIXEL(2), -PIXEL(2), PIXEL(18), PIXEL(16)},
    },
};

static const u8 u8_ARRAY_0836a764[6] = {
    0, 1, 2, 2, 3, 3,
};

static const u8 u8_ARRAY_0836a76a[8] = {
    0, 1, 2, 3, 4, 5, 6, 0,
};

// clang-format off
static const motion_t sMotions[12] = {
    MOTION(SM024_SHARKSEAL_X, 0),
    MOTION(SM053_SHELLUNO, 1),
    MOTION(SM240_SEA_BREAM, 0),
    MOTION(SM239_ANGEL_FISH, 0),
    MOTION(SM241_CRAB, 1),
    MOTION(SM242_FISH_SCHOOL, 0),
    MOTION(SM024_SHARKSEAL_X, 4),
    MOTION(SM024_SHARKSEAL_X, 5),
    MOTION(SM024_SHARKSEAL_X, 5),
    MOTION(SM053_SHELLUNO, 6),
    MOTION(SM053_SHELLUNO, 7),
    MOTION(SM053_SHELLUNO, 8),
};


