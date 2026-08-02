#include "boss.h"
#include "collision.h"
#include "element.h"
#include "global.h"
#include "stagerun.h"
#include "motion.h"

void nop_0805474c(struct Boss* p) {}

static const BossFunc sDeads[1];
static const struct Coord sElementCoord;

void LocomoIF_Die(struct Boss* p);

bool8 tryKillLocomoIF(struct Boss* p) {
  if ((((p->body).status & BODY_STATUS_DEAD) || ((p->body).hp == 0)) && !(gStageRun.missionStatus & MISSION_FAIL)) {
    SET_BOSS_ROUTINE(p, ENTITY_DIE);
    (p->s).mode[1] = 0;
    LocomoIF_Die(p);
    return TRUE;
  }
  return FALSE;
}

INCASM("asm/boss/locomo_if_p1_pre_a.inc");

static const BossFunc sUpdates1[7];
static const BossFunc sUpdates2[7];
bool8 tryKillLocomoIF(struct Boss* p);

void LocomoIF_Update(struct Boss* p) {
  struct Entity** slot = (struct Entity**)((u8*)p + 0xb4);
  struct Entity* e;
  if (*slot != NULL) {
    if (!isKilled(*slot)) {
      goto next;
    }
    e = NULL;
  } else {
    if (!((p->body).status & 1)) {
      goto next;
    }
    if ((*(u8*)((u8*)p + 0x97) & 0xf0) != 0x20) {
      goto next;
    }
    e = (struct Entity*)ApplyElementEffect(0x17, &p->s, &sElementCoord);
  }
  *slot = e;
next:
  if (tryKillLocomoIF(p)) {
    return;
  }
  (sUpdates1[(p->s).mode[1]])(p);
  (sUpdates2[(p->s).mode[1]])(p);
}

void LocomoIF_Die(struct Boss* p) {
  (sDeads[(p->s).mode[1]])(p);
}

void nop_08054ad8(struct Boss* p) {}

void FUN_08054adc(struct Boss* p) {
  switch ((p->s).mode[2]) {
    case 0:
      (p->s).work[2] = 0x1e;
      SetMotion(&p->s, MOTION(0x54, 0));
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      (p->s).work[2]--;
      if ((p->s).work[2] == 0) {
        (p->s).mode[1] = 2;
        (p->s).mode[2] = 0;
      }
      UpdateMotionGraphic(&p->s);
      break;
  }
}

// A pure r0/r1 swap from a match: retail allocates the 0xBD store's value
// register below its address register; agbcc picks the opposite pair in
// every spelling tried (plain, shared var, chained init, s16).
NON_MATCH void FUN_08054b20(struct Boss* p) {
#if MODERN
  switch ((p->s).mode[2]) {
    case 0:
      InitRotatableMotion(&p->s);
      SetMotion(&p->s, MOTION(0x54, 0x00));
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      if ((p->s).scriptEntity->flags & 1) {
        (p->s).mode[2]++;
      }
      UpdateMotionGraphic(&p->s);
      break;
    case 2:
      (p->s).mode[2] = 3;
      // fallthrough
    case 3:
      *((u8*)p + 0xbd) = 1;
      if (!(gStageRun.vm.active & 1)) {
        (p->s).mode[1] = 0;
        (p->s).mode[2] = 0;
      }
      UpdateMotionGraphic(&p->s);
      break;
  }
#else
  INCCODE("asm/boss/locomo_54b20.inc");
#endif
}

void FUN_08054b98(struct Boss* p) {
  switch ((p->s).mode[2]) {
    case 0:
      *(s32*)((u8*)p + 0xb8) = 0;
      (p->s).d.x = 0;
      (p->s).work[2] = Sqrt(0xAAA);
      (p->s).mode[2]++;
      /* fallthrough */
    case 1: {
      s32 t;
      *(s32*)((u8*)p + 0xb8) += (p->s).d.x;
      (p->s).d.x += 0x18;
      t = (p->s).work[2] - 1;
      (p->s).work[2] = t;
      if ((t << 24) == 0) {
        (p->s).mode[2]++;
      }
      UpdateMotionGraphic(&p->s);
      break;
    }
    case 2:
      (p->s).d.x = Sqrt(0xAAA) * 24;
      (p->s).mode[2]++;
      /* fallthrough */
    case 3:
      *(s32*)((u8*)p + 0xb8) += (p->s).d.x;
      if (*(u32*)((u8*)p + 0xb8) > 0x307FF) {
        (p->s).mode[2]++;
      }
      UpdateMotionGraphic(&p->s);
      break;
    case 4:
      (p->s).work[2] = Sqrt(0xAAA);
      (p->s).mode[2]++;
      /* fallthrough */
    case 5: {
      u8 t;
      (p->s).d.x -= 0x18;
      *(s32*)((u8*)p + 0xb8) += (p->s).d.x;
      t = --(p->s).work[2];
      if (t == 0) {
        (p->s).mode[1] = 4;
        (p->s).mode[2] = t;
      }
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
  if (*((u8*)p + 0xbc) != 0) {
    (p->s).angle = -(*(u32*)((u8*)p + 0xb8) >> 8);
  } else {
    (p->s).angle = *(u32*)((u8*)p + 0xb8) >> 8;
  }
}

INCASM("asm/boss/locomo_if_p2_post.inc");

void FUN_08054e94(struct Boss* p) {
  switch ((p->s).mode[2]) {
    case 0:
      (p->s).work[2] = Sqrt(0xAA);
      (p->s).d.x = -(Sqrt(0xAA) * 24);
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      *(s32*)((u8*)p + 0xb8) += (p->s).d.x;
      (p->s).d.x += 0x18;
      if ((u8)--(p->s).work[2] == 0) {
        *(s32*)((u8*)p + 0xb8) = 0x8000;
        (p->s).mode[1] = 3;
        (p->s).mode[2] = 0;
      }
      break;
  }
  if (*((u8*)p + 0xbc) != 0) {
    (p->s).angle = -(*(u32*)((u8*)p + 0xb8) >> 8);
  } else {
    (p->s).angle = *(u32*)((u8*)p + 0xb8) >> 8;
  }
}

static const struct Collision sCollisions[];

void locomoIF_08054f18(struct Boss* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SetMotion(&p->s, MOTION(0x54, 0x03));
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 1:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 3) {
        (p->s).mode[2]++;
      }
      if ((s8)(p->s).motion.cmdIdx == 2) {
        SetDDP(&p->body, &sCollisions[2]);
      }
      break;
    case 2:
      (p->s).work[2] = 0x1e;
      if (*((u8*)p + 0xbc) != 0) {
        SetMotion(&p->s, MOTION(0x54, 0x06));
      } else {
        SetMotion(&p->s, MOTION(0x54, 0x07));
      }
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 3: {
      u8 t = --(p->s).work[2];
      if (t == 0) {
        (p->s).mode[1] = 6;
        (p->s).mode[2] = t;
      }
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}

void FUN_080a7c60(s32 x, s32 y, u8 a2);
void FUN_080a7cb0(s32 x, s32 y, u8 a2);

// 0x08054FCC
void FUN_08054fcc(struct Boss* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SetMotion(&p->s, MOTION(0x54, 0x04));
      (p->s).work[2] = 0x5A;
      if (*((u8*)p + 0xbc) != 0) {
        PlaySound(0x129);
      } else {
        PlaySound(0x128);
      }
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 1:
      if ((u8)((p->s).work[2] % 12) == 0) {
        if (*((u8*)p + 0xbc) != 0) {
          FUN_080a7c60((p->s).coord.x - 0xC00, (p->s).coord.y - 0xC00, 0);
          FUN_080a7c60((p->s).coord.x + 0xC00, (p->s).coord.y - 0xC00, 1);
        } else {
          FUN_080a7cb0((p->s).coord.x - 0xC00, (p->s).coord.y + 0xC00, 0);
          FUN_080a7cb0((p->s).coord.x + 0xC00, (p->s).coord.y + 0xC00, 1);
        }
      }
      if ((u8)--(p->s).work[2] == 0) {
        (p->s).mode[2]++;
      }
      UpdateMotionGraphic(&p->s);
      break;
    case 2:
      SetMotion(&p->s, MOTION(0x54, 0x05));
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 3:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 3) {
        (p->s).mode[1] = 0;
        (p->s).mode[2] = 0;
      }
      if ((s8)(p->s).motion.cmdIdx == 1) {
        SetDDP(&p->body, sCollisions);
      }
      break;
  }
}

INCASM("asm/boss/locomo_if_p2_post_b2.inc");

void LocomoIF_Init(struct Boss* p);
void LocomoIF_Update(struct Boss* p);
void LocomoIF_Die(struct Boss* p);

// clang-format off
const BossRoutine gLocomoIFRoutine = {
    [ENTITY_INIT] =      (BossFunc)LocomoIF_Init,
    [ENTITY_UPDATE] =    (BossFunc)LocomoIF_Update,
    [ENTITY_DIE] =       (BossFunc)LocomoIF_Die,
    [ENTITY_DISAPPEAR] = (BossFunc)DeleteBoss,
    [ENTITY_EXIT] =      (BossFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

void nop_08054ad8(struct Boss* p);

// clang-format off
static const BossFunc sUpdates1[7] = {
    nop_08054ad8,
    nop_08054ad8,
    nop_08054ad8,
    nop_08054ad8,
    nop_08054ad8,
    nop_08054ad8,
    nop_08054ad8,
};
// clang-format on

void FUN_08054adc(struct Boss* p);
void FUN_08054b20(struct Boss* p);
void FUN_08054b98(struct Boss* p);
void FUN_08054cac(struct Boss* p);
void FUN_08054e94(struct Boss* p);
void locomoIF_08054f18(struct Boss* p);
void FUN_08054fcc(struct Boss* p);

// clang-format off
static const BossFunc sUpdates2[7] = {
    FUN_08054adc,
    FUN_08054b20,
    FUN_08054b98,
    FUN_08054cac,
    FUN_08054e94,
    locomoIF_08054f18,
    FUN_08054fcc,
};
// clang-format on

// --------------------------------------------

void locomoIF_080550ec(struct Boss* p);

static const BossFunc sDeads[1] = {
    locomoIF_080550ec,
};

// --------------------------------------------

// 0x08363af8
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
      damage : 3,
      atkType : 0x00,
      element : 0x00,
      nature : 0x00,
      comboLv : 0,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(9), PIXEL(60), PIXEL(8)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 5,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(12), PIXEL(12)},
    },
};

static const u8 sInitModes[2] = {1, 0};
static const struct Coord sElementCoord = {0, 0};

static const motion_t sMotions[3] = {
    MOTION(0x54, 0x9),
    MOTION(0x54, 0xA),
    MOTION(0x54, 0xA),
};
