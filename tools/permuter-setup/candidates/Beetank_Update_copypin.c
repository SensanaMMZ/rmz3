#include "collision.h"
#include "enemy.h"
#include "global.h"

void Beetank_Init(struct Enemy* p);
void Beetank_Update(struct Enemy* p);
void Beetank_Die(struct Enemy* p);

void FUN_0807be50(struct Enemy* p);
static const EnemyFunc sUpdates1[5];
static const EnemyFunc sUpdates2[5];

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

INCASM("asm/enemy/beetank_Init.inc");

// Does not match: agbcc cannot reproduce the target's register allocation in
// the ground-snap min() block (the constant is cached in r8 forcing a push/pop,
// and the two FUN_08009f6c results are double-homed). ~48h of permuter search
// floored at 18 instruction diffs / score 235, so this stays as the matching
// asm body; the MODERN branch documents the equivalent C.
void Beetank_Update(struct Enemy* p) {
  if (*(u32*)((u8*)p + 0x8c) & 0x200) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    Beetank_Die(p);
  } else {
    register struct Enemy* pp asm("r5") = p;

    (sUpdates1[(pp->s).mode[1]])(pp);
    FUN_0807be50(pp);

    {
      register s32 push asm("r0") = PushoutToLeft1((pp->s).coord.x + 0x400, (pp->s).coord.y - 0x400);
      register s32 pushc asm("r6") = push;
      if (push != 0) (pp->s).coord.x += pushc;
    }
    {
      register s32 push asm("r0") = PushoutToRight1((pp->s).coord.x - 0x400, (pp->s).coord.y - 0x400);
      register s32 pushc asm("r6") = push;
      if (push != 0) (pp->s).coord.x += pushc;
    }

    {
      register s32 k asm("r8") = -0x600;
      register s32 a asm("r4") = FUN_08009f6c((pp->s).coord.x - 0x1000, (pp->s).coord.y + k);
      register s32 b asm("r0") = FUN_08009f6c((pp->s).coord.x + 0x1000, (pp->s).coord.y + k);
      register s32 ca asm("r6") = a;
      register s32 cb asm("r7") = b;
      (pp->s).coord.y = (ca < cb) ? a : b;
    }

    if (IsFrozen(&pp->s)) {
      *(u8*)((u8*)pp + 0xba) = (pp->s).mode[1];
    } else {
      (sUpdates2[(pp->s).mode[1]])(pp);
    }
  }
}

INCASM("asm/enemy/beetank_Die.inc");

bool8 nop_0807bc8c(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/beetank_p2.inc");

bool8 nop_0807bd3c(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/beetank_p3.inc");

bool8 nop_0807bde4(struct Enemy* p) { return TRUE; }

void FUN_0807bde8(struct Enemy* p) {
  struct Entity** slot;
  if ((p->s).mode[2] == 0) (p->s).mode[2] = 1;
  slot = (struct Entity**)((u8*)p + 0xbc);
  if (isKilled(*slot)) {
    *slot = NULL;
    (p->s).mode[1] = 0;
    (p->s).mode[2] = 0;
  }
}

bool8 FUN_0807be14(struct Enemy* p) { return TRUE; }


void nop_0807be18(struct Enemy* p) {}

bool8 FUN_0807be1c(struct Enemy* p) { return TRUE; }

void FUN_0807be20(struct Enemy* p) {
  struct Entity** slot;
  u8 m = (p->s).mode[2];
  if (m == 0) {
    (p->s).d.y = m;
    (p->s).mode[2]++;
  }
  slot = (struct Entity**)((u8*)p + 0xbc);
  if (isKilled(*slot)) {
    *slot = NULL;
    (p->s).mode[1] = 0;
    (p->s).mode[2] = 0;
  }
}

INCASM("asm/enemy/beetank_p6_p1_p2.inc");

void nop_0807bea4(struct Enemy* p) {}

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
