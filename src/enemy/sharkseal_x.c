#include "collision.h"
#include "enemy.h"
#include "global.h"

static const struct Collision sCollisions[5];

struct Enemy* CreateSharksealX(struct Coord* c, u8 mode) {
  struct Enemy* p = (struct Enemy*)AllocEntityFirst(gEnemyHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(p, ENEMY_SHARKSEAL_X);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).coord = *c;
    (p->s).work[0] = mode;
  }
  return p;
}

INCASM("asm/enemy/sharkseal_x_p1_p2.inc");

bool8 FUN_080707d0(struct Enemy* p) { return TRUE; }


void nop_080707d4(struct Enemy* p) {}

bool8 FUN_080707d8(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/sharkseal_x_p3.inc");

bool8 FUN_080708dc(struct Enemy* p) { return TRUE; }

void forceWaterLanding(struct Entity* p);

void sharksealxMode2(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SetMotion(&p->s, 0x1800);
      SetDDP(&p->body, &sCollisions[0]);
      (p->s).d.y = 0;
      (p->s).d.x = 0;
      SET_XFLIP(p, *(u8*)((u8*)p + 0xbc));
      (p->s).work[2] = 0x18;
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      UpdateMotionGraphic(&p->s);
      (p->s).d.y += 0x20;
      if ((p->s).d.y > 0x100) {
        (p->s).d.y = 0x100;
      }
      (p->s).coord.y += (p->s).d.y;
      forceWaterLanding(&p->s);
      if ((p->s).work[2] == 0 || --(p->s).work[2] == 0) {
        (p->s).mode[1] = 3;
        (p->s).mode[2] = 0;
      }
      break;
  }
}

bool8 FUN_08070990(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/sharkseal_x_p5.inc");

bool8 FUN_08070c68(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/sharkseal_x_p6.inc");

bool8 FUN_08070f3c(struct Enemy* p) { return TRUE; }

void sharksealxMode5(struct Enemy* p) {
  struct Entity** slot;
  if ((p->s).mode[2] == 0) {
    SetDDP(&p->body, &sCollisions[4]);
    (p->s).mode[2]++;
  }
  slot = (struct Entity**)((u8*)p + 0xc0);
  if (isKilled(*slot)) {
    SetDDP(&p->body, &sCollisions[0]);
    *slot = NULL;
    (p->s).mode[1] = 1;
    (p->s).mode[2] = 0;
  }
}

bool8 FUN_08070f8c(struct Enemy* p) { return TRUE; }


void nop_08070f90(struct Enemy* p) {}

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
