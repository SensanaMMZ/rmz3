#include "collision.h"
#include "enemy.h"
#include "global.h"
#include "trig.h"

static const EnemyFunc sDeads[1];

void CreateWormerRockDrone(s32 x, s32 y, u8 angle, u8 w2) {
  struct Enemy* p = (struct Enemy*)AllocEntityLast(gEnemyHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(p, ENEMY_WORMER_ROCK_DRONE);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).work[0] = 0;
    (p->s).work[2] = w2;
    (p->s).coord.x = x;
    (p->s).coord.y = y;
    (p->s).d.x = COS(angle);
    (p->s).d.y = SIN(angle);
  }
}

void nop_08076ee0(struct Enemy* p) {}

void WormerRockDrone_Die(struct Enemy* p);

INCASM("asm/enemy/wormer_rock_drone_p2_pre.inc");

static bool8 FUN_08076ee4(struct Enemy* p) {
  if ((p->body).status & BODY_STATUS_DEAD) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    (p->s).mode[1] = 0;
    WormerRockDrone_Die(p);
    return TRUE;
  }
  return FALSE;
}

INCASM("asm/enemy/wormer_rock_drone_p2_post_pre.inc");

void WormerRockDrone_Die(struct Enemy* p) {
  (sDeads[(p->s).mode[1]])(p);
}

INCASM("asm/enemy/wormer_rock_drone_p2_post_post.inc");

void FUN_08076fe4(struct Enemy* p) {}

INCASM("asm/enemy/wormer_rock_drone_p3.inc");

void WormerRockDrone_Init(struct Enemy* p);
void WormerRockDrone_Update(struct Enemy* p);
void WormerRockDrone_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gWormerRockDroneRoutine = {
    [ENTITY_INIT] =      WormerRockDrone_Init,
    [ENTITY_UPDATE] =    WormerRockDrone_Update,
    [ENTITY_DIE] =       WormerRockDrone_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

void FUN_08076fe4(struct Enemy* p);

static const EnemyFunc sUpdates1[1] = {
    FUN_08076fe4,
};

void FUN_08076fe8(struct Enemy* p);

static const EnemyFunc sUpdates2[1] = {
    FUN_08076fe8,
};

// --------------------------------------------

void FUN_080770ac(struct Enemy* p);

static const EnemyFunc sDeads[1] = {
    FUN_080770ac,
};

// --------------------------------------------

static const struct Collision sCollisions[2] = {
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 2,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(14), PIXEL(14)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : 8,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(14), PIXEL(14)},
    },
};

static const u8 sInitModes[2] = {0, 0};

static const motion_t sMotions[2] = {
    MOTION(SM044_WORMER_ROCK_DRONE, 2),
    MOTION(SM044_WORMER_ROCK_DRONE, 3),
};
