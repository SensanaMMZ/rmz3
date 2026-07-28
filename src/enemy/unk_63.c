#include "collision.h"
#include "enemy.h"
#include "global.h"
#include "vfx.h"
#include "zero.h"

static const EnemyFunc sUpdates1[4];
static const EnemyFunc sUpdates2[4];
static const struct Collision sCollisions[3];
static const u8 sInitModes[6];
static const s16 s16_ARRAY_ARRAY_08369f44[4][2];
static const s8 s8_ARRAY_ARRAY_08369f5a[4][2];

void Enemy63_Update(struct Enemy* p);

#include "entity/macros.h"

void FUN_080949d4(s32 x, s32 y, u8 n) {
  struct Enemy* p = (struct Enemy*)AllocEntityFirst(gEnemyHeaderPtr);

  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(p, 63);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).work[0] = 4;
    (p->s).work[1] = n;
    (p->s).coord.x = x;
    (p->s).coord.y = y;
    (p->s).d.x = s16_ARRAY_ARRAY_08369f44[n][0];
    (p->s).d.y = s16_ARRAY_ARRAY_08369f44[n][1];
    (p->s).unk_coord.x = 0x180;
  }
}

void FUN_08094a54(s32 x, s32 y, u8 n) {
  struct Enemy* p = (struct Enemy*)AllocEntityFirst(gEnemyHeaderPtr);

  if (p != NULL) {
    (p->s).taskCol = 24;
    INIT_ENEMY_ROUTINE(p, 63);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).work[0] = 5;
    (p->s).coord.x = x;
    (p->s).coord.y = y;
    (p->s).d.x = s16_ARRAY_ARRAY_08369f44[n][0] / 2;
    (p->s).d.y = s16_ARRAY_ARRAY_08369f44[n][1] / 2;
  }
}

void nop_08094ad8(struct Enemy* p) {}

void Enemy63_Init(struct Enemy* p) {
  SET_ENEMY_ROUTINE(p, ENTITY_UPDATE);
  (p->s).mode[1] = sInitModes[(p->s).work[0]];
  (p->s).flags |= FLIPABLE;
  (p->s).flags |= DISPLAY;
  InitNonAffineMotion(&p->s);
  INIT_BODY(p, sCollisions, 1, (void*)nop_08094ad8);
  if ((p->s).work[0] <= 3) {
    (p->s).coord.x += s8_ARRAY_ARRAY_08369f5a[(p->s).work[0]][0] << 8;
    (p->s).coord.y += s8_ARRAY_ARRAY_08369f5a[(p->s).work[0]][1] << 8;
    (p->s).work[2] = 0x1e;
  }
  Enemy63_Update(p);
}

void Enemy63_Update(struct Enemy* p) {
  (sUpdates1[(p->s).mode[1]])(p);
  (sUpdates2[(p->s).mode[1]])(p);
}

void Enemy63_Die(struct Enemy* p) {
  SET_ENEMY_ROUTINE(p, ENTITY_EXIT);
}


void nop_08094bcc(struct Enemy* p) {}


void FUN_08094bd0(struct Enemy* p) {
  if ((p->body).status & BODY_STATUS_BINDING) {
    (p->s).mode[1] = 3;
    (p->s).mode[2] = 0;
  }
}

static const motion_t sMotions[4];

void FUN_08094bf0(struct Enemy* p) {
  if (!((p->body).status & BODY_STATUS_BINDING) || ((pZero2->body).status & BODY_STATUS_WHITE)) {
    struct Coord c;
    PlaySound(SE_ICE_BREAK);
    c.x = (p->s).coord.x, c.y = (p->s).coord.y - PIXEL(16);
    FUN_080b7ffc((void*)p, &c, (motion_t*)sMotions, 4);
    (p->s).flags &= ~DISPLAY;
    (p->s).flags &= ~FLIPABLE;
    EXIT_BODY(p);
    SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
  }
}

INCASM("asm/enemy/unk_63_p3_p2.inc");

void FUN_08094e0c(struct Enemy* p) {
  switch ((p->s).mode[2]) {
    case 0: {
      SetMotion(&p->s, MOTION(SM200_SMOKE, 1));
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1: {
      (p->s).coord.x += (p->s).d.x;
      (p->s).coord.y += (p->s).d.y;
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == MOTION_END) (p->s).mode[2]++;
      break;
    }
    case 2: {
      (p->s).flags &= ~DISPLAY;
      (p->s).flags &= ~FLIPABLE;
      EXIT_BODY(p);
      SET_ENEMY_ROUTINE(p, ENTITY_DISAPPEAR);
      break;
    }
  }
}

INCASM("asm/enemy/unk_63_p3_p3.inc");



void Enemy63_Init(struct Enemy* p);
void Enemy63_Update(struct Enemy* p);
void Enemy63_Die(struct Enemy* p);

// clang-format off
const EnemyRoutine gEnemy63Routine = {
    [ENTITY_INIT] =      Enemy63_Init,
    [ENTITY_UPDATE] =    Enemy63_Update,
    [ENTITY_DIE] =       Enemy63_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteEnemy,
    [ENTITY_EXIT] =      (EnemyFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

void nop_08094bcc(struct Enemy* p);
void FUN_08094bd0(struct Enemy* p);
void FUN_08094bf0(struct Enemy* p);

static const EnemyFunc sUpdates1[4] = {
    nop_08094bcc,
    FUN_08094bd0,
    nop_08094bcc,
    FUN_08094bf0,
};

void FUN_08094c80(struct Enemy* p);
void FUN_08094d48(struct Enemy* p);
void FUN_08094e0c(struct Enemy* p);
void FUN_08094ea0(struct Enemy* p);

static const EnemyFunc sUpdates2[4] = {
    FUN_08094c80,
    FUN_08094d48,
    FUN_08094e0c,
    FUN_08094ea0,
};

// --------------------------------------------

static const struct Collision sCollisions[3] = {
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
      damage : 255,
      unk_0a : 0x41,
      remaining : 0,
      layer : 1,
      range : {PIXEL(0), PIXEL(0), PIXEL(10), PIXEL(10)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 255,
      unk_0a : 0x41,
      remaining : 0,
      layer : 1,
      range : {PIXEL(0), PIXEL(0), PIXEL(64), PIXEL(64)},
    },
};

static const s16 s16_ARRAY_ARRAY_08369f44[4][2] = {
    {-0x0180, 0x0000},
    {0x0180, 0x0000},
    {0x0000, -0x0180},
    {0x0000, 0x0180},
};

static const u8 sInitModes[6] = {
    0, 0, 0, 0, 1, 2,
};

static const s8 s8_ARRAY_ARRAY_08369f5a[4][2] = {
    {8, 0},
    {-8, 0},
    {0, 8},
    {0, -8},
};

static const motion_t sMotions[4] = {
    MOTION(SM088_LOCOMO_IF_ICE, 1),
    MOTION(SM088_LOCOMO_IF_ICE, 2),
    MOTION(SM088_LOCOMO_IF_ICE, 3),
    MOTION(SM088_LOCOMO_IF_ICE, 4),
};
