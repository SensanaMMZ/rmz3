#include "boss.h"
#include "collision.h"
#include "element.h"
#include "global.h"
#include "palette_animation.h"
#include "overworld.h"

static const struct Collision sCollisions[8];

void BeeServer_Init(struct Boss* p);
void BeeServer_Update(struct Boss* p);
void BeeServer_Die(struct Boss* p);

// clang-format off
const BossRoutine gBeeServerRoutine = {
    [ENTITY_INIT] =      BeeServer_Init,
    [ENTITY_UPDATE] =    BeeServer_Update,
    [ENTITY_DIE] =       BeeServer_Die,
    [ENTITY_DISAPPEAR] = DeleteBoss,
    [ENTITY_EXIT] =      (BossFunc)DeleteEntity,
};
// clang-format on

static void onCollision(struct Body* body UNUSED, struct Coord* r1 UNUSED, struct Coord* r2 UNUSED) { return; }

static bool8 tryKillBeeServer(struct Boss* p) {
  if ((((p->body).status & BODY_STATUS_DEAD) || ((p->body).hp == 0)) && !(gStageRun.missionStatus & MISSION_FAIL)) {
    SET_BOSS_ROUTINE(p, ENTITY_DIE);
    (p->s).mode[1] = 0;
    BeeServer_Die(p);
    return TRUE;
  }
  return FALSE;
}

static const BossFunc sDeads[1];

INCASM("asm/boss/bee_server_p1_pre.inc");

static const BossFunc sUpdates1[4];
static const BossFunc sUpdates2[4];

// 0x0804cfd4
void BeeServer_Update(struct Boss* p) {
  struct Entity** slot = (struct Entity**)((u8*)p + 0xb4);
  if (*slot != NULL && isKilled(*slot)) {
    *slot = NULL;
  }
  {
    register s16* h0 asm("r0");
    register s32 v asm("r1");
    register s16* h asm("r3");
    s32 lim;
    h0 = (s16*)&p->props.raw[4];
    v = *h0 + 0x100;
    lim = 0x200;
    h = h0;
    asm("" : "+r"(h));
    if ((u32)v > (u32)lim) {
      s32 t;
      *(u16*)h = -*(u16*)h;
      t = *h;
      *h = ((t * 15) << 4) / 0x100;
    } else {
      *h = 0;
    }
    {
      s32 bx = *(s32*)&p->props.raw[8];
      (p->s).coord.x = bx;
      asm volatile("" ::: "memory");
      (p->s).coord.x = bx + *h;
    }
  }
  {
    s16* w = (s16*)&p->props.raw[6];
    u16 wv = *(u16*)w;
    if (*w != 0) {
      *(u16*)w = wv - 1;
    }
  }
  if (!tryKillBeeServer(p)) {
    (sUpdates1[(p->s).mode[1]])(p);
    (sUpdates2[(p->s).mode[1]])(p);
    StepPaletteAnimation(0x45);
  }
}

void BeeServer_Die(struct Boss* p) {
  (sDeads[(p->s).mode[1]])(p);
}

void nop_0804d0a0(struct Boss* p) {}

extern const struct Coord Coord_0836331c;

void FUN_0804d0a4(struct Boss* p) {
  if (((p->body).status & BODY_STATUS_WHITE) && (p->body).elemented == 2) {
    *(struct VFX**)&p->props.raw[0] = ApplyElementEffect(0x12, &p->s, &Coord_0836331c);
  }
  if (((p->body).status & 0x00020008) == 0x00020008) {
    u16* q = (u16*)&p->props.raw[4];
    register s32 v asm("r0");
    v = 0xFC00;
    *q = v;
  }
}

void FUN_0807d6c0(s32 x, s32 y, u8 a2);

void FUN_0804d0f8(struct Boss* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SetDDP(&p->body, &sCollisions[1]);
      (p->s).work[2] = 0xFF;
      SetMotion(&p->s, MOTION(0x46, 0x00));
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 1: {
      s16* t = (s16*)&p->props.raw[6];
      u8 v;
      if (*t == 0 && ((p->body).status & 0x00020008) == 0x00020008) {
        u32 r;
        *t = 0x78;
        r = RANDOM(RNG_0202f388) & 3;
        FUN_0807d6c0((p->s).coord.x,
                     (p->s).coord.y + ({
                       s32 o_ = ((r >> 1) << 14) - 0x2000;
                       asm("" : "+r"(o_));
                       o_;
                     }),
                     r & 1);
      }
      v = --(p->s).work[2];
      if (v == 0) {
        (p->s).mode[1] = 2;
        (p->s).mode[2] = v;
      }
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}

u8 GetEntityPalID(struct Entity* p);

// 0x0804d1ac
void FUN_0804d1ac(struct Boss* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SetMotion(&p->s, MOTION(0x46, 0x00));
      {
        u32 g0 = GetEntityPalID(&p->s);
        u32 g = (u8)g0 << 5;
        StartPaletteAnimation(0x45, g | 0x200);
      }
      (p->s).mode[2]++;
      /* fallthrough */
    case 1:
      UpdateMotionGraphic(&p->s);
      if ((p->s).scriptEntity->flags & 1) {
        (p->s).mode[2]++;
      }
      break;
    case 2:
      SetMotion(&p->s, MOTION(0x46, 0x00));
      (p->s).mode[2]++;
      /* fallthrough */
    case 3: {
      u32 v;
      UpdateMotionGraphic(&p->s);
      v = gStageRun.vm.active & 1;
      if (v == 0) {
        (p->s).mode[1] = v;
        (p->s).mode[2] = v;
      }
      break;
    }
  }
}

INCASM("asm/boss/bee_server_p2b.inc");

extern const u8 u8_ARRAY_0836332e[5];
void FUN_080a2f34(s32 x, s32 y);

// 0x0804d418
void FUN_0804d418(struct Boss* p) {
  switch ((p->s).mode[2]) {
    case 0:
      PlaySound(0x10F);
      FUN_080a2f34((p->s).coord.x, (p->s).coord.y);
      SetMotion(&p->s, MOTION(0x46, 0x03));
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 1:
      SetDDP(&p->body, &sCollisions[u8_ARRAY_0836332e[(s8)(p->s).motion.cmdIdx]]);
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 3) {
        (p->s).mode[1] = 0;
        (p->s).mode[2] = 0;
      }
      break;
  }
}

INCASM("asm/boss/bee_server_p2b_b.inc");

// --------------------------------------------

void FUN_0804d0a4(struct Boss* p);
void nop_0804d0a0(struct Boss* p);

static const BossFunc sUpdates1[4] = {
    FUN_0804d0a4,
    nop_0804d0a0,
    FUN_0804d0a4,
    FUN_0804d0a4,
};

// --------------------------------------------

void FUN_0804d0f8(struct Boss* p);
void FUN_0804d1ac(struct Boss* p);
void FUN_0804d240(struct Boss* p);
void FUN_0804d418(struct Boss* p);

static const BossFunc sUpdates2[4] = {
    FUN_0804d0f8,
    FUN_0804d1ac,
    FUN_0804d240,
    FUN_0804d418,
};

// --------------------------------------------

void FUN_0804d494(struct Boss* p);

static const BossFunc sDeads[1] = {
    FUN_0804d494,
};

// --------------------------------------------

// 0x08363258
static const struct Collision sCollisions[8] = {
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 0x00,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(8), PIXEL(8)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      atkType : 0x00,
      nature : BODY_NATURE_B2,
      comboLv : 0x00,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(55), PIXEL(84)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 5,
      hardness : METAL,
      remaining : 0,
      priorityLayer : 0xFFFFFFFF,
      range : {PIXEL(0), PIXEL(0), PIXEL(55), PIXEL(84)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      atkType : 0x00,
      nature : BODY_NATURE_B2,
      comboLv : 0x00,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(55), PIXEL(88)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      atkType : 0x00,
      element : 0x00,
      nature : BODY_NATURE_B2,
      comboLv : 0x00,
      hitzone : 0x00,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(55), PIXEL(94)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      atkType : 0x00,
      element : 0x00,
      comboLv : 0x00,
      remaining : 2,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(22), PIXEL(55), PIXEL(40)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      atkType : 0x00,
      element : 0x00,
      comboLv : 0x00,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(35), PIXEL(55), PIXEL(36)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 5,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {PIXEL(0), PIXEL(7), PIXEL(55), PIXEL(19)},
    },
};

static const u8 sInitModes[4] = {1, 0, 0, 0};

const struct Coord Coord_0836331c = {0, 0};

const u8 u8_ARRAY_08363324[5] = {2, 3, 4, 5, 5};
const u8 u8_ARRAY_08363329[5] = {4, 3, 3, 2, 2};
const u8 u8_ARRAY_0836332e[5] = {5, 5, 4, 3, 2};
