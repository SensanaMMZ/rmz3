#include "collision.h"
#include "enemy.h"
#include "global.h"
#include "motion.h"
#include "sound.h"

static const struct Collision sCollisions[3];

void EyeCannon_Init(struct Enemy* p);
void EyeCannon_Update(struct Enemy* p);
void EyeCannon_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gEyeCannonRoutine = {
    [ENTITY_INIT] =      EyeCannon_Init,
    [ENTITY_UPDATE] =    EyeCannon_Update,
    [ENTITY_DIE] =       EyeCannon_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

static void onCollision(struct Body* body UNUSED, struct Coord* r1 UNUSED, struct Coord* r2 UNUSED) {
  // NOP
  return;
}

static bool8 FUN_08084708(struct Enemy* p) {
  if ((p->body).status & BODY_STATUS_DEAD) {
    SET_ENEMY_ROUTINE(p, ENTITY_DIE);
    (p->s).mode[1] = 0;
    EyeCannon_Die(p);
    return TRUE;
  }
  return FALSE;
}

static const EnemyFunc sDeads[1];
static const EnemyFunc sUpdates1[6];
static const EnemyFunc sUpdates2[6];

void FUN_080847b8(struct Enemy* p);
bool8 FUN_08084744(struct Enemy* p);

INCASM("asm/enemy/eye_cannon_pre_pre_p1.inc");

void EyeCannon_Update(struct Enemy* p) {
  if (!FUN_08084708(p)) {
    FUN_080847b8(p);
    if (!FUN_08084744(p)) {
      (sUpdates1[(p->s).mode[1]])(p);
      (sUpdates2[(p->s).mode[1]])(p);
    }
  }
}

void EyeCannon_Die(struct Enemy* p) {
  (sDeads[(p->s).mode[1]])(p);
}

void FUN_08084930(struct Enemy* p) {}

INCASM("asm/enemy/eye_cannon_post_pre_p1.inc");

void FUN_08084934(struct Enemy* p) {
  struct Entity** slot = (struct Entity**)((u8*)p + 0xb4);
  if (*slot == NULL || isKilled(*slot)) {
    *slot = NULL;
    SetDDP(&p->body, &sCollisions[1]);
    if (!IsFrozen(&p->s)) {
      (p->s).mode[1] = 1;
      (p->s).mode[2] = 0;
    }
  }
}

void FUN_08084974(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SetMotion(&p->s, MOTION(0x66, 0));
      SetDDP(&p->body, &sCollisions[2]);
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      UpdateMotionGraphic(&p->s);
      break;
  }
}

INCASM("asm/enemy/eye_cannon_post_post_pre.inc");

void FUN_08084cbc(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0:
      PlaySound(0x8f << 1);
      SetMotion(&p->s, MOTION(0x66, 3));
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 3) {
        (p->s).mode[1] = (p->s).motion.state;
        (p->s).mode[2] = 0;
      }
      break;
  }
}

INCASM("asm/enemy/eye_cannon_post_post_post.inc");

void FUN_08084934(struct Enemy* p);
void FUN_08084930(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates1[6] = {
    FUN_08084934,
    FUN_08084930,
    FUN_08084930,
    FUN_08084930,
    FUN_08084930,
    FUN_08084930,
};
// clang-format on

void FUN_08084974(struct Enemy* p);
void FUN_080849b0(struct Enemy* p);
void FUN_08084a80(struct Enemy* p);
void FUN_08084b2c(struct Enemy* p);
void FUN_08084c30(struct Enemy* p);
void FUN_08084cbc(struct Enemy* p);

// clang-format off
static const EnemyFunc sUpdates2[6] = {
    FUN_08084974,
    FUN_080849b0,
    FUN_08084a80,
    FUN_08084b2c,
    FUN_08084c30,
    FUN_08084cbc,
};
// clang-format on

void _killEyeCannon(struct Enemy* p);

static const EnemyFunc sDeads[1] = {
    _killEyeCannon,
};

// --------------------------------------------

static const struct Collision sCollisions[3] = {
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 0,
      hardness : 8,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(8), PIXEL(8)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 3,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(18), PIXEL(20), PIXEL(20)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      hardness : 8,
      remaining : 0,
      range : {PIXEL(0), PIXEL(18), PIXEL(20), PIXEL(20)},
    },
};

static const u32 u32_ARRAY_08368358[4] = {
    45,
    46,
    47,
    48,
};

static const struct Coord sElementCoord = {PIXEL(0), PIXEL(18)};

static const u8 u8_ARRAY_08368370[4] = {
    249,
    135,
    224,
    160,
};

static const motion_t sMotions[3] = {
    MOTION(102, 5),
    MOTION(102, 6),
    MOTION(102, 7),
};
