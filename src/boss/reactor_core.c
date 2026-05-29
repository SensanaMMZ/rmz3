#include "blink.h"
#include "boss.h"
#include "collision.h"
#include "global.h"
#include "motion.h"
#include "stagerun.h"

static const BossFunc sDeads[1];

// エネルギー再生施設の炉心(スイッチ押し込み部屋)

INCASM("asm/boss/reactor_core_p1_pre.inc");

void ReactorCore_Die(struct Boss* p) {
  UpdateBlinkMotionState(0xcb);
  UpdateBlinkMotionState(0xcc);
  (sDeads[(p->s).mode[1]])(p);
}

void ReactorCore_Disappear(struct Boss* p) {
  ClearBlink(0xcb);
  ClearBlink(0xcc);
  DeleteBoss(p);
}

void nop_08061a74(struct Boss* p) {}

void FUN_08061a78(struct Boss* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SetMotion(&p->s, MOTION(0x8b, 0));
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      UpdateMotionGraphic(&p->s);
      break;
  }
}

void FUN_08061aa4(struct Boss* p) {
  switch ((p->s).mode[2]) {
    case 0:
      if ((p->s).scriptEntity->flags & 1) {
        (p->s).mode[2] = 1;
      }
      break;
    case 1:
      if (!(gStageRun.vm.active & 1)) {
        (p->s).mode[1] = 0;
        (p->s).mode[2] = 0;
      }
      break;
  }
}

INCASM("asm/boss/reactor_core_p2_post_p2.inc");

void ReactorCore_Init(struct Boss* p);
void ReactorCore_Update(struct Boss* p);
void ReactorCore_Die(struct Boss* p);
void ReactorCore_Disappear(struct Boss* p);

// clang-format off
const BossRoutine gReactorCoreRoutine = {
    [ENTITY_INIT] =      ReactorCore_Init,
    [ENTITY_UPDATE] =    ReactorCore_Update,
    [ENTITY_DIE] =       ReactorCore_Die,
    [ENTITY_DISAPPEAR] = ReactorCore_Disappear,
    [ENTITY_EXIT] =      (BossFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

void nop_08061a74(struct Boss* p);

static const BossFunc sUpdates1[2] = {
    nop_08061a74,
    nop_08061a74,
};

void FUN_08061a78(struct Boss* p);
void FUN_08061aa4(struct Boss* p);

static const BossFunc sUpdates2[2] = {
    FUN_08061a78,
    FUN_08061aa4,
};

// --------------------------------------------

void FUN_08061adc(struct Boss* p);

static const BossFunc sDeads[1] = {
    FUN_08061adc,
};

// --------------------------------------------

// 0x083656b0
static const struct Collision sCollisions[1] = {
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(48), PIXEL(32)},
    },
};

static const struct Rect sSize = {PIXEL(0), PIXEL(0), PIXEL(48), PIXEL(26)};
static const u8 sInitModes[4] = {0, 0, 0, 0};
