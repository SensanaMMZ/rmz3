#include "boss.h"
#include "collision.h"
#include "global.h"
#include "motion.h"

void FUN_080c4be0(s32 x, s32 y);

static const motion_t sMotions[];

extern const struct Collision sCollisions[];

void FUN_0805ecc8(struct Entity* p) {
  s32 i;
  for (i = 0; i < 4; i++) {
    s32 x, y;

    RNG_0202f388 = LCG(RNG_0202f388);
    x = (p->coord).x + PIXEL(((RNG_0202f388 >> 16) % 24) - 12);

    RNG_0202f388 = LCG(RNG_0202f388);
    y = (p->coord).y - PIXEL(-(RNG_0202f388 >> 16) & 0x1F);
    FUN_080c4be0(x, y);
  }
}

void FUN_080608c8(struct Boss* p);

static const BossFunc sDeads[1];

bool8 FUN_08060924(struct Boss* p);
bool8 FUN_080608e0(struct Boss* p);
s8 FUN_08060974(struct Boss* p);
void FUN_0805f464(struct Boss* p);
void FUN_080607a0(struct Boss* p, s32 idx);

static const BossFunc PTR_ARRAY_08365418[7];
static const BossFunc PTR_ARRAY_08365434[2];
static const BossFunc PTR_ARRAY_0836544c[2];
static const BossFunc PTR_ARRAY_08365454[2];
static const BossFunc PTR_ARRAY_0836545c[2];
static const BossFunc PTR_ARRAY_08365464[6];
static const BossFunc PTR_ARRAY_0836547c[6];
static const BossFunc PTR_ARRAY_08365494[5];
static const BossFunc PTR_ARRAY_083654a8[4];
static const BossFunc PTR_ARRAY_083654b8[3];
static const BossFunc PTR_ARRAY_083654c4[5];
static const BossFunc PTR_ARRAY_083654d8[5];
static const BossFunc PTR_ARRAY_083654ec[6];
static const BossFunc PTR_ARRAY_08365504[7];
static const BossFunc PTR_ARRAY_08365520[3];
static const BossFunc PTR_ARRAY_0836552c[6];
static const BossFunc PTR_ARRAY_08365544[5];
static const BossFunc PTR_ARRAY_08365558[4];

INCASM("asm/boss/phantom_p1_pre_p1.inc");

void callPhantomBossModeTable(struct Boss* p) {
  (PTR_ARRAY_08365418[(p->s).mode[1]])(p);
}

INCASM("asm/boss/phantom_p1_pre_p2.inc");

void phantom_0805efa4(struct Boss* p) {
  (PTR_ARRAY_08365434[(p->s).mode[2]])(p);
}

INCASM("asm/boss/phantom_p1_pre_p3.inc");

void FUN_0805f180(struct Boss* p) {
  (PTR_ARRAY_0836544c[(p->s).mode[3]])(p);
}

INCASM("asm/boss/phantom_p1_pre_p4.inc");

void FUN_0805f26c(struct Boss* p) {
  (PTR_ARRAY_08365454[(p->s).mode[3]])(p);
}

INCASM("asm/boss/phantom_p1_pre_p5.inc");

void FUN_0805f338(struct Boss* p) {
  (PTR_ARRAY_0836545c[(p->s).mode[3]])(p);
}

INCASM("asm/boss/phantom_p1_pre_p6.inc");

void FUN_0805f3d0(struct Boss* p) {
  (PTR_ARRAY_08365464[(p->s).mode[2]])(p);
}

INCASM("asm/boss/phantom_p1_pre_p7_p1_p1.inc");

void FUN_0805f444(struct Boss* p) {
  if (FUN_080608e0(p)) {
    *(u16*)((u8*)p + 0xe) = 2;
    FUN_0805f464(p);
  }
}

INCASM("asm/boss/phantom_p1_pre_p7_p1_p2.inc");

void FUN_0805f488(struct Boss* p) {
  if ((s8)FUN_08060974(p) < 0) {
    (p->s).mode[1] = 0;
    *(u16*)((u8*)p + 0xe) = 0;
  }
}

INCASM("asm/boss/phantom_p1_pre_p7_p2.inc");

void FUN_0805f54c(struct Boss* p) {
  (PTR_ARRAY_0836547c[(p->s).mode[2]])(p);
}

INCASM("asm/boss/phantom_p1_pre_p8.inc");

void FUN_0805f564(struct Boss* p) {
  (PTR_ARRAY_08365494[(p->s).mode[3]])(p);
}

INCASM("asm/boss/phantom_p1_pre_p9.inc");

void FUN_0805f6b0(struct Boss* p) {
  (PTR_ARRAY_083654a8[(p->s).mode[3]])(p);
}

INCASM("asm/boss/phantom_p1_pre_p10.inc");

void FUN_0805f76c(struct Boss* p) {
  (PTR_ARRAY_083654b8[(p->s).mode[3]])(p);
}

INCASM("asm/boss/phantom_p1_pre_p11.inc");

void FUN_0805f784(struct Boss* p) {
  (p->s).mode[3] = 1;
  FUN_080608c8(p);
}

INCASM("asm/boss/phantom_p1_post_p1.inc");

void FUN_0805f820(struct Boss* p) {
  (PTR_ARRAY_083654c4[(p->s).mode[3]])(p);
}

INCASM("asm/boss/phantom_p1_post_p2.inc");

void nop_0805f930(struct Boss* p) {}

INCASM("asm/boss/phantom_p2_pre_pre_p1.inc");

void FUN_0805f934(struct Boss* p) {
  (PTR_ARRAY_083654d8[(p->s).mode[3]])(p);
}

INCASM("asm/boss/phantom_p2_pre_pre_p2_p1.inc");

void FUN_0805f9dc(struct Boss* p) {
  if (FUN_08060924(p)) {
    (p->s).mode[3] = 4;
  }
}

INCASM("asm/boss/phantom_p2_pre_pre_p2_p2.inc");

void FUN_0805fa10(struct Boss* p) {
  (PTR_ARRAY_083654ec[(p->s).mode[2]])(p);
}

INCASM("asm/boss/phantom_p2_pre_pre_p3_p1.inc");

void FUN_0805fa28(struct Boss* p) {
  SetDDP(&p->body, &sCollisions[0]);
  *(u16*)((u8*)p + 0xe) = 1;
}

INCASM("asm/boss/phantom_p2_pre_pre_p3_p2.inc");

void FUN_0805fa44(struct Boss* p) {
  (PTR_ARRAY_08365504[(p->s).mode[3]])(p);
}

INCASM("asm/boss/phantom_p2_pre_pre_p4_p1.inc");

void FUN_0805fac4(struct Boss* p) {
  if (FUN_080608e0(p)) {
    (p->s).mode[3] = 2;
  }
}

INCASM("asm/boss/phantom_p2_pre_pre_p4_p2_p1.inc");

void FUN_0805fafc(struct Boss* p) {
  if (FUN_08060974(p)) {
    PlaySound(0xfd);
    (p->s).mode[3] = 4;
    FUN_080607a0(p, 0xe);
  }
}

INCASM("asm/boss/phantom_p2_pre_pre_p4_p2_p2.inc");

void FUN_0805fd5c(struct Boss* p) {
  (PTR_ARRAY_08365520[(p->s).mode[3]])(p);
}

INCASM("asm/boss/phantom_p2_pre_pre_p5.inc");

void FUN_0805ff64(struct Boss* p) {
  (PTR_ARRAY_0836552c[(p->s).mode[3]])(p);
}

INCASM("asm/boss/phantom_p2_pre_pre_p6_p1.inc");

void FUN_080600c8(struct Boss* p) {
  if (FUN_08060924(p)) {
    (p->s).mode[3] = 5;
  }
}

INCASM("asm/boss/phantom_p2_pre_pre_p6_p2_p1.inc");

void FUN_080600e0(struct Boss* p) {
  if ((s8)FUN_08060974(p) < 0) {
    (p->s).mode[1] = 0;
    *(u16*)((u8*)p + 0xe) = 0;
  }
}

INCASM("asm/boss/phantom_p2_pre_pre_p6_p2_p2.inc");

void FUN_080600fc(struct Boss* p) {
  (PTR_ARRAY_08365544[(p->s).mode[3]])(p);
}

INCASM("asm/boss/phantom_p2_pre_pre_p7_p1.inc");

void FUN_080601f0(struct Boss* p) {
  if ((p->s).motion.state == 3) {
    (p->s).mode[1] = 0;
    *(u16*)((u8*)p + 0xe) = 0;
  }
}

INCASM("asm/boss/phantom_p2_pre_pre_p7_p2.inc");

void FUN_080603b8(struct Boss* p) {
  (PTR_ARRAY_08365558[(p->s).mode[2]])(p);
}

INCASM("asm/boss/phantom_p2_pre_pre_p8.inc");

void FUN_080603d0(struct Boss* p) {
  switch ((p->s).mode[3]) {
    case 0:
      SetMotion(&p->s, MOTION(0xbc, 0x16));
      (p->s).mode[3]++;
      break;
    case 1:
      if ((p->s).motion.state == 3) {
        (p->s).mode[3] = 0;
        (p->s).mode[2]++;
      }
      break;
  }
}

INCASM("asm/boss/phantom_p2_pre_post_pre.inc");

void Phantom_Die(struct Boss* p) {
  (sDeads[(p->s).mode[1]])(p);
}

INCASM("asm/boss/phantom_p2_pre_post_post_p1.inc");

void FUN_080607a0(struct Boss* p, s32 idx) {
  *((u8*)p + 0xb4) = idx;
  SetMotion(&p->s, sMotions[idx]);
}

INCASM("asm/boss/phantom_p2_pre_post_post_p2.inc");

void phantom_080607e4(struct Entity* p) {
  UpdateMotionGraphic(p);
}

INCASM("asm/boss/phantom_p2_post_p1.inc");

s8 FUN_08060974(struct Boss* p) {
  SetDDP(&p->body, &sCollisions[0]);
  if ((p->s).motion.state == 2) return -1;
  if ((p->s).motion.state == 3) return 1;
  return 0;
}

INCASM("asm/boss/phantom_p2_post_p2.inc");

void Phantom_Init(struct Boss* p);
void Phantom_Update(struct Boss* p);
void Phantom_Die(struct Boss* p);

// clang-format off
const BossRoutine gPhantomBossRoutine = {
    [ENTITY_INIT] =      (BossFunc)Phantom_Init,
    [ENTITY_UPDATE] =    (BossFunc)Phantom_Update,
    [ENTITY_DIE] =       (BossFunc)Phantom_Die,
    [ENTITY_DISAPPEAR] = (BossFunc)DeleteBoss,
    [ENTITY_EXIT] =      (BossFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

// clang-format off
// 0x08365214
static const motion_t sMotions[21] = {
    MOTION(DM188_PHANTOM, 0x00),
    MOTION(DM188_PHANTOM, 0x0B),
    MOTION(DM188_PHANTOM, 0x0D),
    MOTION(DM188_PHANTOM, 0x03),
    MOTION(DM188_PHANTOM, 0x0A),
    MOTION(DM188_PHANTOM, 0x11),
    MOTION(DM188_PHANTOM, 0x12),
    MOTION(DM188_PHANTOM, 0x0C),
    MOTION(DM188_PHANTOM, 0x06),
    MOTION(DM188_PHANTOM, 0x04),
    MOTION(DM188_PHANTOM, 0x05),
    MOTION(DM188_PHANTOM, 0x07),
    MOTION(DM188_PHANTOM, 0x08),
    MOTION(DM188_PHANTOM, 0x09),
    MOTION(DM188_PHANTOM, 0x01),
    MOTION(DM188_PHANTOM, 0x02),
    MOTION(DM188_PHANTOM, 0x10),
    MOTION(DM188_PHANTOM, 0x0E),
    MOTION(DM188_PHANTOM, 0x0F),
    MOTION(DM188_PHANTOM, 0x13),
    MOTION(DM188_PHANTOM, 0x14),
};
// clang-format on

// 0x08365240
static const s32 s32_ARRAY_08365240[32] = {
    0x00000000, 0x00000040, 0x000000C0, 0x00000180, 0x00000280, 0x000003C0, 0x00000540, 0x00000700, 0x00000900, 0x00000B40, 0x00000DC0, 0x00001080, 0x00001380, 0x000016C0, 0x00001A40, 0x00001E00, 0x00002200, 0x00002640, 0x00002AC0, 0x00002F80, 0x00003480, 0x000039C0, 0x00003F40, 0x00004500, 0x00004B00, 0x00005140, 0x000057C0, 0x00005E80, 0x00006580, 0x00006CC0, 0x00007440, 0x00007C00,
};

// 0x083652c0
static const struct Collision sCollisions[14] = {
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      atkType : 0x00,
      hitzone : 5,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(14), PIXEL(16), PIXEL(28)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      LAYER(0xFFFFFFFF),
      hitzone : 5,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(14), PIXEL(16), PIXEL(28)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 4,
      atkType : 0x00,
      hitzone : 5,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(16), PIXEL(16), PIXEL(32)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 4,
      LAYER(0xFFFFFFFF),
      hitzone : 5,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(16), PIXEL(16), PIXEL(32)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 4,
      atkType : 0x00,
      hitzone : 5,
      remaining : 1,
      layer : 0x00000001,
      range : {-PIXEL(16), -PIXEL(9), PIXEL(48), PIXEL(18)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 4,
      LAYER(0xFFFFFFFF),
      hitzone : 5,
      remaining : 0,
      range : {-PIXEL(5), -PIXEL(12), PIXEL(26), PIXEL(24)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 0,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(16), PIXEL(16), PIXEL(32)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 0,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(16), PIXEL(16), PIXEL(32)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 5,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(16), PIXEL(16), PIXEL(32)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 5,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(16), PIXEL(16), PIXEL(32)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      atkType : 0x00,
      nature : BODY_NATURE_B2,
      hitzone : 5,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(19), PIXEL(16), PIXEL(38)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      LAYER(0xFFFFFFFF),
      hitzone : 5,
      remaining : 0,
      layer : 0xFFFFFFFF,
      range : {PIXEL(0), -PIXEL(19), PIXEL(16), PIXEL(38)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      atkType : 0x00,
      hitzone : 5,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(19), PIXEL(16), PIXEL(38)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 3,
      LAYER(0xFFFFFFFF),
      hitzone : 5,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(19), PIXEL(16), PIXEL(38)},
    },
};

// --------------------------------------------

void phantom_08060668(struct Boss* p);

static const BossFunc sDeads[1] = {
    phantom_08060668,
};  // 0x08365410

// --------------------------------------------

void callPhantomBossModeTable(struct Boss* p);

static const BossFunc PTR_ARRAY_08365414[1] = {
    callPhantomBossModeTable,
};

void phantom_0805efa4(struct Boss* p);
void phantom_0805f0a0(struct Boss* p);
void FUN_0805f3d0(struct Boss* p);
void FUN_0805f54c(struct Boss* p);
void FUN_0805fa10(struct Boss* p);
void phantom_08060244(struct Boss* p);
void FUN_080603b8(struct Boss* p);

// clang-format off
static const BossFunc PTR_ARRAY_08365418[7] = {
    phantom_0805efa4,
    phantom_0805f0a0,
    FUN_0805f3d0,
    FUN_0805f54c,
    FUN_0805fa10,
    phantom_08060244,
    FUN_080603b8,
};
// clang-format on

void FUN_0805efbc(struct Boss* p);
void FUN_0805f004(struct Boss* p);

static const BossFunc PTR_ARRAY_08365434[2] = {
    FUN_0805efbc,
    FUN_0805f004,
};

void FUN_0805f0f4(struct Boss* p);
void FUN_0805f180(struct Boss* p);
void FUN_0805f26c(struct Boss* p);
void FUN_0805f338(struct Boss* p);

static const BossFunc PTR_ARRAY_0836543c[4] = {
    FUN_0805f0f4,
    FUN_0805f180,
    FUN_0805f26c,
    FUN_0805f338,
};

void phantom_0805f198(struct Boss* p);
void FUN_0805f214(struct Boss* p);

static const BossFunc PTR_ARRAY_0836544c[2] = {
    phantom_0805f198,
    FUN_0805f214,
};

void FUN_0805f284(struct Boss* p);
void FUN_0805f2e0(struct Boss* p);

static const BossFunc PTR_ARRAY_08365454[2] = {
    FUN_0805f284,
    FUN_0805f2e0,
};

void FUN_0805f350(struct Boss* p);
void FUN_0805f394(struct Boss* p);

static const BossFunc PTR_ARRAY_0836545c[2] = {
    FUN_0805f350,
    FUN_0805f394,
};

void FUN_0805f3e8(struct Boss* p);
void FUN_0805f444(struct Boss* p);
void FUN_0805f464(struct Boss* p);
void FUN_0805f488(struct Boss* p);
void FUN_0805f4a4(struct Boss* p);
void FUN_0805f52c(struct Boss* p);

// clang-format off
static const BossFunc PTR_ARRAY_08365464[6] = {
    FUN_0805f3e8,
    FUN_0805f444,
    FUN_0805f464,
    FUN_0805f488,
    FUN_0805f4a4,
    FUN_0805f52c,
};
// clang-format on

void FUN_0805f564(struct Boss* p);
void FUN_0805f6b0(struct Boss* p);
void FUN_0805f738(struct Boss* p);
void FUN_0805f76c(struct Boss* p);
void FUN_0805f820(struct Boss* p);
void FUN_0805f934(struct Boss* p);

// clang-format off
static const BossFunc PTR_ARRAY_0836547c[6] = {
    FUN_0805f564,
    FUN_0805f6b0,
    FUN_0805f738,
    FUN_0805f76c,
    FUN_0805f820,
    FUN_0805f934,
};
// clang-format on

void FUN_0805f57c(struct Boss* p);
void FUN_0805f5a8(struct Boss* p);
void FUN_0805f630(struct Boss* p);
void FUN_0805f660(struct Boss* p);
void FUN_0805f690(struct Boss* p);

// clang-format off
static const BossFunc PTR_ARRAY_08365494[5] = {
    FUN_0805f57c,
    FUN_0805f5a8,
    FUN_0805f630,
    FUN_0805f660,
    FUN_0805f690,
};
// clang-format on

void FUN_0805f6c8(struct Boss* p);
void FUN_0805f6e0(struct Boss* p);
void FUN_0805f6fc(struct Boss* p);
void FUN_0805f71c(struct Boss* p);

static const BossFunc PTR_ARRAY_083654a8[4] = {
    FUN_0805f6c8,
    FUN_0805f6e0,
    FUN_0805f6fc,
    FUN_0805f71c,
};

void FUN_0805f784(struct Boss* p);
void FUN_0805f794(struct Boss* p);
void FUN_0805f7d0(struct Boss* p);

static const BossFunc PTR_ARRAY_083654b8[3] = {
    FUN_0805f784,
    FUN_0805f794,
    FUN_0805f7d0,
};

void FUN_0805f838(struct Boss* p);
void FUN_0805f85c(struct Boss* p);
void FUN_0805f870(struct Boss* p);
void FUN_0805f8c4(struct Boss* p);
void nop_0805f930(struct Boss* p);

// clang-format off
static const BossFunc PTR_ARRAY_083654c4[5] = {
    FUN_0805f838,
    FUN_0805f85c,
    FUN_0805f870,
    FUN_0805f8c4,
    nop_0805f930,
};
// clang-format on

void FUN_0805f94c(struct Boss* p);
void FUN_0805f97c(struct Boss* p);
void FUN_0805f9a0(struct Boss* p);
void FUN_0805f9dc(struct Boss* p);
void FUN_0805f9f4(struct Boss* p);

// clang-format off
static const BossFunc PTR_ARRAY_083654d8[5] = {
    FUN_0805f94c,
    FUN_0805f97c,
    FUN_0805f9a0,
    FUN_0805f9dc,
    FUN_0805f9f4,
};
// clang-format on

void FUN_0805fa28(struct Boss* p);
void FUN_0805fa44(struct Boss* p);
void FUN_0805fc7c(struct Boss* p);
void FUN_0805fd5c(struct Boss* p);
void FUN_0805ff64(struct Boss* p);
void FUN_080600fc(struct Boss* p);

// clang-format off
static const BossFunc PTR_ARRAY_083654ec[6] = {
    FUN_0805fa28,
    FUN_0805fa44,
    FUN_0805fc7c,
    FUN_0805fd5c,
    FUN_0805ff64,
    FUN_080600fc,
};
// clang-format on

void FUN_0805fa5c(struct Boss* p);
void FUN_0805fac4(struct Boss* p);
void FUN_0805fadc(struct Boss* p);
void FUN_0805fafc(struct Boss* p);
void FUN_0805fb24(struct Boss* p);
void FUN_0805fb8c(struct Boss* p);
void FUN_0805fc1c(struct Boss* p);

// clang-format off
static const BossFunc PTR_ARRAY_08365504[7] = {
    FUN_0805fa5c,
    FUN_0805fac4,
    FUN_0805fadc,
    FUN_0805fafc,
    FUN_0805fb24,
    FUN_0805fb8c,
    FUN_0805fc1c,
};
// clang-format on

void FUN_0805fd74(struct Boss* p);
void FUN_0805fdac(struct Boss* p);
void FUN_0805feac(struct Boss* p);

static const BossFunc PTR_ARRAY_08365520[3] = {
    FUN_0805fd74,
    FUN_0805fdac,
    FUN_0805feac,
};

void FUN_0805ff7c(struct Boss* p);
void FUN_0805ffb4(struct Boss* p);
void FUN_0805ffec(struct Boss* p);
void FUN_08060040(struct Boss* p);
void FUN_080600c8(struct Boss* p);
void FUN_080600e0(struct Boss* p);

// clang-format off
static const BossFunc PTR_ARRAY_0836552c[6] = {
    FUN_0805ff7c,
    FUN_0805ffb4,
    FUN_0805ffec,
    FUN_08060040,
    FUN_080600c8,
    FUN_080600e0,
};
// clang-format on

void FUN_08060114(struct Boss* p);
void FUN_0806016c(struct Boss* p);
void FUN_0806019c(struct Boss* p);
void FUN_080601f0(struct Boss* p);
void FUN_08060208(struct Boss* p);

// clang-format off
static const BossFunc PTR_ARRAY_08365544[5] = {
    FUN_08060114,
    FUN_0806016c,
    FUN_0806019c,
    FUN_080601f0,
    FUN_08060208,
};
// clang-format on

void FUN_080603d0(struct Boss* p);
void FUN_08060410(struct Boss* p);
void FUN_080604e0(struct Boss* p);
void FUN_08060560(struct Boss* p);

static const BossFunc PTR_ARRAY_08365558[4] = {
    FUN_080603d0,
    FUN_08060410,
    FUN_080604e0,
    FUN_08060560,
};

void FUN_080afdf0(struct Boss* p);
void FUN_080afe38(struct Boss* p);

static const BossFunc PTR_ARRAY_08365568[2] = {
    FUN_080afdf0,
    FUN_080afe38,
};
