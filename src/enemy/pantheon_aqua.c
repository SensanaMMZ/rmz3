#include "collision.h"
#include "enemy.h"
#include "global.h"

static const struct Collision sCollisions[];

struct Enemy* CreatePantheonAqua(struct Coord* c, u8 mode) {
  struct Enemy* p = (struct Enemy*)AllocEntityFirst(gEnemyHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(p, ENEMY_P_AQUA);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).coord = *c;
    (p->s).work[0] = mode;
  }
  return p;
}

INCASM("asm/enemy/pantheon_aqua_p1_p2.inc");

bool8 nop_080726a8(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/pantheon_aqua_p2.inc");

bool8 FUN_08072800(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/pantheon_aqua_p3.inc");

bool8 FUN_080729e8(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/pantheon_aqua_p4.inc");

bool8 FUN_08072e40(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/pantheon_aqua_p5.inc");

bool8 FUN_08072fac(struct Enemy* p) { return TRUE; }

void FUN_08072fb0(struct Enemy* p) {
  if ((p->s).mode[2] == 0) {
    SetDDP(&p->body, &sCollisions[1]);
    (p->s).mode[2]++;
  }
  if (isKilled(*(struct Entity**)((u8*)p + 0xbc))) {
    SetDDP(&p->body, &sCollisions[0]);
    *(struct Entity**)((u8*)p + 0xbc) = NULL;
    (p->s).mode[1] = 0;
    (p->s).mode[2] = 0;
  }
}

bool8 FUN_08072ff8(struct Enemy* p) { return TRUE; }


void FUN_08072ffc(struct Enemy* p) {}

bool8 FUN_08073000(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/pantheon_aqua_p8.inc");

bool8 FUN_080730cc(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/pantheon_aqua_p9.inc");

bool8 FUN_08073368(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/pantheon_aqua_p10.inc");

void PantheonAqua_Init(struct Enemy* p);
void PantheonAqua_Update(struct Enemy* p);
void PantheonAqua_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gPantheonAquaRoutine = {
    [ENTITY_INIT] =      PantheonAqua_Init,
    [ENTITY_UPDATE] =    PantheonAqua_Update,
    [ENTITY_DIE] =       PantheonAqua_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

bool8 nop_080726a8(struct Enemy* p);
bool8 FUN_08072800(struct Enemy* p);
bool8 FUN_080729e8(struct Enemy* p);
bool8 FUN_08072e40(struct Enemy* p);
bool8 FUN_08072fac(struct Enemy* p);
bool8 FUN_08072ff8(struct Enemy* p);
bool8 FUN_08073000(struct Enemy* p);
bool8 FUN_080730cc(struct Enemy* p);

// clang-format off
const EnemyFunc PTR_ARRAY_08366bd0[8] = {
    (EnemyFunc)nop_080726a8,
    (EnemyFunc)FUN_08072800,
    (EnemyFunc)FUN_080729e8,
    (EnemyFunc)FUN_08072e40,
    (EnemyFunc)FUN_08072fac,
    (EnemyFunc)FUN_08072ff8,
    (EnemyFunc)FUN_08073000,
    (EnemyFunc)FUN_080730cc,
};
// clang-format on

void FUN_080726ac(struct Enemy* p);
void FUN_08072804(struct Enemy* p);
void FUN_080729ec(struct Enemy* p);
void FUN_08072e44(struct Enemy* p);
void FUN_08072fb0(struct Enemy* p);
void FUN_08072ffc(struct Enemy* p);
void FUN_08073004(struct Enemy* p);
void FUN_080730d0(struct Enemy* p);

// clang-format off
const EnemyFunc PTR_ARRAY_08366bf0[8] = {
    FUN_080726ac,
    FUN_08072804,
    FUN_080729ec,
    FUN_08072e44,
    FUN_08072fb0,
    FUN_08072ffc,
    FUN_08073004,
    FUN_080730d0,
};
// clang-format on

// --------------------------------------------

static const struct Collision sCollisions[] = {
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(21), PIXEL(28), PIXEL(36)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(22), PIXEL(30), PIXEL(38)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 3,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(21), PIXEL(28), PIXEL(36)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 2,
      range : {PIXEL(0), -PIXEL(22), PIXEL(30), PIXEL(38)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 1,
      layer : 0x00000001,
      range : {-PIXEL(21), -PIXEL(29), PIXEL(19), PIXEL(9)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      range : {-PIXEL(21), -PIXEL(29), PIXEL(19), PIXEL(9)},
    },
    {
      kind : DDP,
      faction : FACTION_NEUTRAL,
      special : 0,
      damage : 3,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(21), PIXEL(28), PIXEL(36)},
    },
    {
      kind : DRP,
      faction : FACTION_NEUTRAL,
      special : 0,
      damage : 0,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(22), PIXEL(30), PIXEL(38)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(22), PIXEL(30), PIXEL(38)},
    },
};

static const struct Coord sElementCoord = {PIXEL(0), -PIXEL(23)};
