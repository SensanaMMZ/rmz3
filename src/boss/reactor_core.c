#include "palette_animation.h"
#include "boss.h"
#include "collision.h"
#include "global.h"
#include "motion.h"
#include "stagerun.h"

static const BossFunc sDeads[1];

// エネルギー再生施設の炉心(スイッチ押し込み部屋)

INCASM("asm/boss/reactor_core_p1_pre.inc");

static const BossFunc sUpdates1[2];
static const BossFunc sUpdates2[2];
struct Entity* FUN_0807cbf4(s32 x, s32 y, u8 n);
void ReactorCore_Die(struct Boss* p);

void ReactorCore_Update(struct Boss* p) {
  StepPaletteAnimation(0xCB);
  StepPaletteAnimation(0xCC);
  {
  register u8* sr asm("r2");
  sr = (u8*)&gStageRun;
  if (!(sr[0x12] & 1)) {
    u32 w0 = (p->s).work[0];
    if (w0 == 1) {
      s32* timer = (s32*)((u8*)p + 0xbc);
      if (*timer == 0) {
        register struct Camera* cam asm("r8");
        register u32 A asm("sl");
        register u32 s2 asm("r9");
        register s32 x5 asm("r5");
        u32 C4;
        u32 raw1;
        u32 raw2;
        u32 raw3;
        u32 seed3;
        s32 y;
        u32 r2a;
        u32 sd;
        *timer = 0x5A;
        sr += 0xE8;
        cam = (struct Camera*)sr;
        x5 = ((struct Camera*)sr)->viewport.x + -0x6000;
        sd = RNG_0202f388;
        {
          register u32 a3s asm("r3");
          a3s = 0x343FD;
          A = a3s;
        }
        {
          register u32 t1 asm("r1");
          t1 = A;
          t1 *= sd;
          raw1 = t1;
        }
        C4 = 0x269EC3;
        asm("" : "+r"(C4));
        raw1 += C4;
        raw1 <<= 1;
        s2 = raw1 >> 1;
        RNG_0202f388 = s2;
        x5 += (raw1 >> 0x11) % 0xC000;
        {
          s32 vy = cam->viewport.y;
          register u32 ck asm("r2");
          ck = (u32)-0x3000;
          asm("" : "+r"(ck));
          y = vy + ck;
        }
        {
          register u32 t3 asm("r3");
          register u32 t0 asm("r0");
          t3 = A;
          asm("" : "+r"(t3));
          t0 = s2;
          t0 *= t3;
          raw2 = t0;
        }
        raw2 += C4;
        raw2 <<= 1;
        seed3 = raw2 >> 1;
        y += (raw2 << 1) >> 0x12;
        {
          register u32 t0b asm("r0");
          t0b = A;
          asm("" : "+r"(t0b));
          t0b *= seed3;
          asm("" : "+r"(t0b));
          raw3 = t0b;
        }
        {
          register u32 t2 asm("r2");
          t2 = raw3;
          asm("" : "+r"(t2));
          t2 += C4;
          t2 <<= 1;
          RNG_0202f388 = t2 >> 1;
          r2a = (t2 >> 0x11) & w0;
        }
        FUN_0807cbf4(x5, y, r2a);
      }
      (*timer)--;
    }
  }
  }
  {
    s32 sum = 0;
    s32 i = 0;
    u8* pr = (u8*)p + 0xb4;
    do {
      sum += pr[i];
      i++;
    } while (i <= 5);
    if (sum == 0) {
      SET_BOSS_ROUTINE(p, ENTITY_DIE);
      (p->s).mode[1] = sum;
      ReactorCore_Die(p);
    } else {
      (sUpdates1[(p->s).mode[1]])(p);
      (sUpdates2[(p->s).mode[1]])(p);
    }
  }
}


void ReactorCore_Die(struct Boss* p) {
  StepPaletteAnimation(0xcb);
  StepPaletteAnimation(0xcc);
  (sDeads[(p->s).mode[1]])(p);
}

void ReactorCore_Disappear(struct Boss* p) {
  RemovePaletteAnimation(0xcb);
  RemovePaletteAnimation(0xcc);
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

void FUN_08061adc(struct Boss* p) {
  switch ((p->s).mode[2]) {
    case 0:
      StopSound(0xe0);
      (p->s).flags2 &= ~0x08;
      EXIT_BODY(p);
      if ((gStageRun.missionStatus & 1) && !(gStageRun.vm.active & 1)) {
        gStageRun.missionStatus = (gStageRun.missionStatus & 0xfffe) | 0x10;
      }
      (p->s).work[2] = 2;
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      if (--(p->s).work[2] == 0) {
        gStageRun.vm.active |= 2;
        (p->s).mode[2]++;
      }
      break;
  }
}

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
