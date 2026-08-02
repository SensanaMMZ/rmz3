#include "palette_animation.h"
#include "boss.h"
#include "collision.h"
#include "global.h"
#include "overworld_terrain.h"
#include "script.h"
#include "stagerun.h"

void OmegaGold_Init(struct Boss* p);
void OmegaGold_Update(struct Boss* p);
void OmegaGold_Die(struct Boss* p);
void OmegaGold_Disappear(struct Boss* p);

static void floatGoldOmega1(struct Boss* p);
static const struct Collision sCollisions[8];

// clang-format off
const BossRoutine gOmegaGoldRoutine = {
    [ENTITY_INIT] =      (void*)OmegaGold_Init,
    [ENTITY_UPDATE] =    (void*)OmegaGold_Update,
    [ENTITY_DIE] =       (void*)OmegaGold_Die,
    [ENTITY_DISAPPEAR] = (void*)OmegaGold_Disappear,
    [ENTITY_EXIT] =      (void*)DeleteEntity,
};
// clang-format on

// --------------------------------------------

struct Entity* CreateOmegaGold(struct Coord* c, u8 n) {
  struct Entity* p = AllocEntityFirst(gBossHeaderPtr);
  if (p != NULL) {
    p->taskCol = 24;
    INIT_BOSS_ROUTINE(p, BOSS_OMEGA_GOLD);
    p->tileNum = 0, p->palID = 0;
    p->flags2 |= WHITE_PAINTABLE;
    p->invincibleID = p->uniqueID;
    p->coord = *c;
    p->work[0] = n;
  }
  return p;
}

// --------------------------------------------

static const BossFunc sDeads[2];

INCASM("asm/boss/omega_gold_p1_pre_a.inc");

static const BossFunc sUpdates1[8];
static const BossFunc sUpdates2[8];

void OmegaGold_Update(struct Boss* p) {
  u8 m;
  if (!((p->body).status & BODY_STATUS_DEAD)) {
    if (*(s16*)((u8*)p + 0xa4) != 0) {
      goto alive;
    }
  }
  if (gStageRun.missionStatus & 8) {
    goto alive;
  }
  SET_BOSS_ROUTINE(p, ENTITY_DIE);
  OmegaGold_Die(p);
  return;

alive:
  m = (p->s).mode[1];
  if (m > 1 && m != 6) {
    StepPaletteAnimation(0x66);
  }
  (sUpdates1[(p->s).mode[1]])(p);
  (sUpdates2[(p->s).mode[1]])(p);
}

void OmegaGold_Die(struct Boss* p) {
  (sDeads[(p->s).mode[1]])(p);
}

void OmegaGold_Disappear(struct Boss* p) {
  RemovePaletteAnimation(0xb);
  RemovePaletteAnimation(0x66);
  RemovePaletteAnimation(0x67);
  RemovePaletteAnimation(0x10f);
  DeleteBoss(p);
}

INCASM("asm/boss/omega_gold_p1_post_p2.inc");

bool8 FUN_0805b41c(struct Boss* p) { return TRUE; }

void goldOmega1_0805b420(struct Boss* p) {
  switch ((p->s).mode[2]) {
    case 0:
      (p->s).mode[2] = 1;
      // fallthrough
    case 1:
      if ((p->s).scriptEntity->flags & 1) {
        gOverworld.state[1] = 1;
        (p->s).mode[1] = 1;
        (p->s).mode[2] = 0;
      }
      break;
  }
}

bool8 FUN_0805b45c(struct Boss* p) { return TRUE; }

void makeGoldOmega1Mode2(struct Boss* p) {
  switch ((p->s).mode[2]) {
    case 0:
      (p->s).mode[2] = 1;
      (p->s).work[2] = 0x3c;
      // fallthrough
    case 1:
      if ((p->s).work[2] == 0 || --(p->s).work[2] == 0) {
        (p->s).mode[2]++;
      }
      break;
    case 2:
      (p->s).mode[1] = (p->s).mode[2];
      (p->s).mode[2] = 0;
      break;
  }
}

bool8 FUN_0805b4a4(struct Boss* p) { return TRUE; }

void FUN_0805b4a8(struct Boss* p) {
  switch ((p->s).mode[2]) {
    case 0:
      (p->s).mode[2] = 1;
      // fallthrough
    case 1:
      if (!(gStageRun.vm.active & 1)) {
        (p->s).mode[1] = 3;
        (p->s).mode[2] = 0;
      }
      break;
  }
}

extern const u8 unk_080fefb8[24];
u16 FUN_0805b8ac(struct Boss* _, u32 old);

// 0x0805B4D8
bool8 changeGoldOmega1Mode(struct Boss* p0) {
  register struct Boss* p asm("r5");
  s32 raw;
  u8 w3;
  u8 t;
  s8* a0;
  s8* b0;
  s8* a;
  s8* b;
  s32 av;
  s32 bv;
  u16 nm;
  u32 i;
  const u8* tbl;
  p = p0;
  if ((p->s).mode[2] == 0) {
    return 1;
  }
  w3 = (p->s).work[3];
  if (w3 == 0) {
    return 1;
  }
  raw = w3 - 1;
  (p->s).work[3] = raw;
  t = raw;
  if (t != 0) {
    return 1;
  }
  a0 = (s8*)((u8*)p + 0xb5);
  b0 = (s8*)((u8*)p + 0xb6);
  av = *a0;
  bv = *b0;
  a = a0;
  asm("" : "+r"(a));
  b = b0;
  asm("" : "+r"(b));
  if (av == bv) {
    i = RANDOM(RNG_0202f388);
    tbl = &unk_080fefb8[6];
    asm("" : "+r"(tbl));
    i %= tbl[0];
    i++;
    asm("" : "+r"(i));
    i += (u32)tbl;
    nm = *(const u8*)i;
    if (nm == *a) {
      nm = FUN_0805b8ac(p, nm);
    }
    goto tail;
  }
  i = RANDOM(RNG_0202f388);
  tbl = &unk_080fefb8[6];
  asm("" : "+r"(tbl));
  i %= tbl[0];
  i++;
  asm("" : "+r"(i));
  i += (u32)tbl;
  nm = *(const u8*)i;
tail:
  (p->s).mode[1] = nm;
  (p->s).mode[2] = t;
  *(u8*)b = *(u8*)a;
  *(u8*)a = nm;
  return 1;
}

void goldOmega1Neutral(struct Boss* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SetDDP(&p->body, &sCollisions[1]);
      (p->s).d.y = 0;
      (p->s).d.x = 0;
      (p->s).work[3] = 0x1e;
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      floatGoldOmega1(p);
      break;
  }
}

bool8 nop_0805b5dc(struct Boss* p) { return TRUE; }

extern const u8 unk_080fefb8[24];

// 1 insn from parity (151 vs 152) with switch-block layout differences;
// logic verified case-by-case against the asm. Layout tie.
// Semantics corrected by the oam.xflip bitfield insert (the old draft wrote
// spriteIdx); laser table pools exactly via the hoisted index. Three ties
// left: retail splits the d.y address (base+0x5C, str +4), reuses the masked
// zero for the else-arm mode[3] store, and materializes 0x4D0 before the
// table load.
NON_MATCH void goldOmega1Laser(struct Boss* p) {
#if MODERN
  switch ((p->s).mode[2]) {
    case 0: {
      (p->s).spr.xflip = 0;
      (p->s).spr.oam.xflip = 0;
      (p->s).flags &= ~X_FLIP;
      (p->s).d.y = 0;
      (p->s).d.x = 0;
      (p->s).work[2] = 3;
      if (RANDOM(RNG_0202f388) & 1) {
        (p->s).mode[3] = 1;
      } else {
        (p->s).mode[3] = 0;
      }
      (p->s).mode[2]++;
      /* fallthrough */
    }
    case 1: {
      (p->s).work[3] = 0x30;
      if ((p->s).mode[3] == 0) {
        s32 i = (p->s).work[2] - 1;
        createGoldOmega1Laser(0x4D0, unk_080fefb8[i], 0x30, &p->s);
      } else {
        s32 i = (p->s).work[2] - 1;
        createGoldOmega1Laser(0x4D0, (unk_080fefb8 + 3)[i], 0x30, &p->s);
      }
      StepPaletteAnimation(0xb);
      (p->s).mode[2]++;
      break;
    }
    case 2: {
      floatGoldOmega1(p);
      if ((p->s).work[3] != 0) {
        (p->s).work[3]--;
        if ((p->s).work[3] == 0) {
          (p->s).mode[2]++;
        }
      }
      floatGoldOmega1(p);
      StepPaletteAnimation(0xb);
      break;
    }
    case 3: {
      floatGoldOmega1(p);
      (p->s).work[2]--;
      if ((p->s).work[2] == 0) {
        *(s32*)((u8*)p + 0xbc) = 0;
        (p->s).work[2] = 0x3C;
        (p->s).mode[2]++;
      } else {
        (p->s).mode[2] = 1;
      }
      StepPaletteAnimation(0xb);
      break;
    }
    case 4: {
      floatGoldOmega1(p);
      StepPaletteAnimation(0xb);
      if ((p->s).work[2] != 0) {
        (p->s).work[2]--;
        if ((p->s).work[2] == 0) {
          (p->s).mode[1] = 3;
          (p->s).mode[2] = 0;
        }
      }
      break;
    }
  }
#else
  INCCODE("asm/boss/omega_gold_laser.inc");
#endif
}

bool8 nop_0805b740(struct Boss* p) { return TRUE; }

static void floatGoldOmega1(struct Boss* p);

void FUN_0805b744(struct Boss* p) {
  switch ((p->s).mode[2]) {
    case 0:
      (p->s).spr.xflip = 0;
      (p->s).spr.oam.xflip = 0;
      (p->s).flags &= ~X_FLIP;
      (p->s).d.y = 0;
      (p->s).d.x = 0;
      (p->s).work[2] = 0xff;
      (p->s).work[3] = -1;
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      if ((p->s).work[2] != 0) {
        (p->s).work[2]--;
      } else if ((p->s).work[3] != 0 && --(p->s).work[3] == 0) {
        (p->s).work[2] = 0x3c;
        (p->s).mode[2]++;
      }
      StepPaletteAnimation(0xb);
      floatGoldOmega1(p);
      break;
    case 2:
      if ((p->s).work[2] == 0 || --(p->s).work[2] == 0) {
        (p->s).mode[1] = 3;
        (p->s).mode[2] = 0;
      }
      StepPaletteAnimation(0xb);
      floatGoldOmega1(p);
      break;
  }
}

bool8 nop_0805b7ec(struct Boss* p) { return TRUE; }

void FUN_0805b7f0(struct Boss* p) {
  switch ((p->s).mode[2]) {
    case 0:
      (p->s).spr.xflip = 0;
      (p->s).spr.oam.xflip = 0;
      (p->s).flags &= ~X_FLIP;
      (p->s).d.y = 0;
      (p->s).d.x = 0;
      (p->s).work[2] = 0xFF;
      (p->s).work[3] = -1;
      RemovePaletteAnimation(0x66);
      StartPaletteAnimation(0x67, 0x300);
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      if ((*(struct Entity**)((u8*)p + 0xc8))->mode[2] > 0x1d) {
        StartPaletteAnimation(0x66, 0x300);
        (p->s).mode[1] = 3;
        (p->s).mode[2] = 0;
      } else {
        StepPaletteAnimation(0x67);
        floatGoldOmega1(p);
      }
      break;
  }
}

bool8 FUN_0805b41c(struct Boss* p);
bool8 FUN_0805b45c(struct Boss* p);
bool8 FUN_0805b4a4(struct Boss* p);
bool8 changeGoldOmega1Mode(struct Boss* p);
bool8 nop_0805b5dc(struct Boss* p);
bool8 nop_0805b740(struct Boss* p);
bool8 nop_0805b7ec(struct Boss* p);
static bool32 nop_0805b874(void* _ UNUSED);

// clang-format off
static const BossFunc sUpdates1[8] = {
    (void*)FUN_0805b41c,
    (void*)FUN_0805b45c,
    (void*)FUN_0805b4a4,
    (void*)changeGoldOmega1Mode,
    (void*)nop_0805b5dc,
    (void*)nop_0805b740,
    (void*)nop_0805b7ec,
    (void*)nop_0805b874,
};
// clang-format on

// --------------------------------------------

void goldOmega1_0805b420(struct Boss* p);
void makeGoldOmega1Mode2(struct Boss* p);
void FUN_0805b4a8(struct Boss* p);
void goldOmega1Neutral(struct Boss* p);
void goldOmega1Laser(struct Boss* p);
void FUN_0805b744(struct Boss* p);
void FUN_0805b7f0(struct Boss* p);
static void FUN_0805b878(struct Entity* p);

// clang-format off
static const BossFunc sUpdates2[8] = {
    (void*)goldOmega1_0805b420,
    (void*)makeGoldOmega1Mode2,
    (void*)FUN_0805b4a8,
    (void*)goldOmega1Neutral,
    (void*)goldOmega1Laser,
    (void*)FUN_0805b744,
    (void*)FUN_0805b7f0,
    (void*)FUN_0805b878,
};
// clang-format on

// --------------------------------------------

void FUN_0805b270(struct Boss* p);
void FUN_0805b358(struct Boss* p);

static const BossFunc sDeads[2] = {
    FUN_0805b270,
    FUN_0805b358,
};

// --------------------------------------------

static bool32 nop_0805b874(void* _) { return TRUE; }

static void FUN_0805b878(struct Entity* p) {
  switch (p->mode[2]) {
    case 0: {
      (p->d).x = 0, (p->d).y = 0;
      p->mode[2]++;
      /* fallthrough */
    }
    case 1: {
      (p->d).y += (PIXEL(1) / 4);
      if ((p->d).y > (PIXEL(1) / 4)) {
        (p->d).y = (PIXEL(1) / 4);
      }
      UpdateMotionGraphic(p);
      break;
    }
  }
}

extern const u16 u16_ARRAY_080fefd0[3];

u16 FUN_0805b8ac(struct Boss* _, u32 old) {
  s32 i;
  for (i = 0; i < (s32)ARRAY_COUNT(u16_ARRAY_080fefd0); i++) {
    if (u16_ARRAY_080fefd0[i] == old) {
      return u16_ARRAY_080fefd0[(i + 1) % ((s32)ARRAY_COUNT(u16_ARRAY_080fefd0))];
    }
  }
}

// 0x0805b8e0
static void onCollision(struct Body* body, struct Coord* c1, struct Coord* c2) {
  {
    struct Boss* self = (struct Boss*)body->parent;
    struct Entity* fx = (struct Entity*)(self->s).unk_2c;
    if (fx != NULL) {
      if (fx->mode[0] >= ENTITY_DIE) {
        (self->s).unk_2c = NULL;
      } else {
        fx->flags &= ~DISPLAY;
      }
    }
  }
  {
    struct Boss* self = (struct Boss*)body->parent;
    struct Entity* fx = (self->props).omegaWhite.unk_bc;
    if (fx != NULL) {
      if (fx->mode[0] >= ENTITY_DIE) {
        (self->props).omegaWhite.unk_bc = NULL;
      } else {
        fx->flags &= ~DISPLAY;
      }
    }
  }
}

// 0x0805B924
// オメガが縦にふわふわする処理
static void floatGoldOmega1(struct Boss* p) {
  u16 val = ((p->props.omegaWhite).unk_c0 + 1) & 0xFF;
  (p->props.omegaWhite).unk_c0 = val;
  (p->s).coord.y = (p->s).unk_coord.y + (gSineTable[val] << 3);
}

// --------------------------------------------

// 0x08364c74
static const struct Collision sCollisions[8] = {
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 0,
      hardness : METAL,
      remaining : 0,
      priorityLayer : 0xFFFFFFFF,
      range : {PIXEL(0), PIXEL(3), PIXEL(24), PIXEL(24)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 2,
      remaining : 2,
      layer : 0x00000001,
      range : {PIXEL(20), -PIXEL(64), PIXEL(54), -PIXEL(128)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 5,
      remaining : 1,
      range : {PIXEL(2), -PIXEL(102), PIXEL(16), PIXEL(16)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 5,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(80), PIXEL(16), PIXEL(28)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 2,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(3), PIXEL(40), PIXEL(80)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 5,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(80), PIXEL(24), PIXEL(24)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      damage : 2,
      remaining : 1,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(3), PIXEL(40), PIXEL(80)},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 5,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(80), PIXEL(24), PIXEL(24)},
    },
};
