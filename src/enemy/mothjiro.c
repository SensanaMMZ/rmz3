#include "collision.h"
#include "enemy.h"
#include "global.h"

static const struct Collision sCollisions[3];

void Mothjiro_Init(struct Enemy* p);
void Mothjiro_Update(struct Enemy* p);
void Mothjiro_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gMothjiroRoutine = {
    [ENTITY_INIT] =      Mothjiro_Init,
    [ENTITY_UPDATE] =    Mothjiro_Update,
    [ENTITY_DIE] =       Mothjiro_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

struct Enemy* CreateMothjiro(struct Coord* c, u8 r1) {
  struct Enemy* p = (struct Enemy*)AllocEntityFirst(gEnemyHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(p, ENEMY_MOTHJIRO);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).coord = *c;
    (p->s).work[0] = r1;
  }
  return p;
}

INCASM("asm/enemy/mothjiro_p1.inc");

bool8 nop_080881d8(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/mothjiro_p2.inc");

bool8 nop_080884a0(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/mothjiro_p3.inc");

bool8 nop_080885f8(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/mothjiro_p4.inc");

bool8 nop_0808889c(struct Enemy* p) { return TRUE; }

INCASM("asm/enemy/mothjiro_p5.inc");

bool8 nop_08088a1c(struct Enemy* p) { return TRUE; }

void mothjiro_08088a20(struct Enemy* p) {
  if ((p->s).mode[2] == 0) {
    SetDDP(&p->body, &sCollisions[2]);
    (p->s).mode[2]++;
  }
}

bool8 nop_08088a44(struct Enemy* p) { return TRUE; }


void nop_08088a48(struct Enemy* p) {}

bool8 nop_08088a4c(struct Enemy* p) { return TRUE; }


void mothjiro_08088a50(struct Enemy* p) {
  if ((p->s).mode[2] == 0) {
    SetDDP(&p->body, &sCollisions[2]);
    (p->s).mode[2]++;
  }
}

INCASM("asm/enemy/mothjiro_p8_post.inc");

// --------------------------------------------

bool8 nop_080881d8(struct Enemy* p);
bool8 nop_080884a0(struct Enemy* p);
bool8 nop_080885f8(struct Enemy* p);
bool8 nop_0808889c(struct Enemy* p);
bool8 nop_08088a1c(struct Enemy* p);
bool8 nop_08088a44(struct Enemy* p);
bool8 nop_08088a4c(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates1[7] = {
    (EnemyFunc)nop_080881d8,
    (EnemyFunc)nop_080884a0,
    (EnemyFunc)nop_080885f8,
    (EnemyFunc)nop_0808889c,
    (EnemyFunc)nop_08088a1c,
    (EnemyFunc)nop_08088a44,
    (EnemyFunc)nop_08088a4c,
};
// clang-format on

void mothjiro_080881dc(struct Enemy* p);
void mothjiro_080884a4(struct Enemy* p);
void mothjiro_080885fc(struct Enemy* p);
void mothjiro_080888a0(struct Enemy* p);
void mothjiro_08088a20(struct Enemy* p);
void nop_08088a48(struct Enemy* p);
void mothjiro_08088a50(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates2[7] = {
    mothjiro_080881dc,
    mothjiro_080884a4,
    mothjiro_080885fc,
    mothjiro_080888a0,
    mothjiro_08088a20,
    nop_08088a48,
    mothjiro_08088a50,
};
// clang-format on

// --------------------------------------------

static const struct Collision sCollisions[3] = {
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 0,
      hardness : METAL,
      remaining : 0,
      layer : 0xFFFFFFFF,
      range : {PIXEL(0), -PIXEL(5), PIXEL(26), PIXEL(20)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(5), PIXEL(26), PIXEL(20)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(5), PIXEL(26), PIXEL(20)},
    },
};

static const struct Coord sElementCoord = {PIXEL(0), -PIXEL(4)};
