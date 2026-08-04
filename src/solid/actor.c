#include "anim_loader.h"
#include "collision.h"
#include "entity.h"
#include "global.h"
#include "gpu_regs.h"
#include "overworld.h"
#include "solid.h"
#include "vfx.h"
#include "vfx/after_image.h"
#include "zero.h"

/*
  Actor:
  Solid.id が 21 の Entity は 基本的にフィールドスクリプト(Script)によって生成される、スクリプトの登場人物のようなもの
  どの種類のActorかは Solid.s.work[0] に格納される (constants/entity/solid.h の ACTOR_XXXX を参照)
*/

static void Actor_Init(struct Solid* p);
void Actor_Update(struct Solid* p);
void Actor_Die(struct Solid* p);

// clang-format off
const SolidRoutine gScriptActorRoutine = {
    [ENTITY_INIT] =      Actor_Init,
    [ENTITY_UPDATE] =    Actor_Update,
    [ENTITY_DIE] =       Actor_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteSolid,
    [ENTITY_EXIT] =      (SolidFunc)DeleteEntity,
};
// clang-format on

struct Solid* CreateScriptActor(struct Solid* e, u8 kind) {
  struct Solid* p = (struct Solid*)AllocEntityFirst(gSolidHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 30;
    INIT_SOLID_ROUTINE(p, SOLID_SCRIPT_ACTOR);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).work[0] = kind;
    (p->s).coord.x = (e->s).coord.x;
    (p->s).coord.y = (e->s).coord.y;
    (p->s).unk_28 = &e->s;
  }
  return p;
}

u16 FUN_080d08d0(struct Boss* babyelf, motion_t m) { return FUN_080d0934(&babyelf->s, m, ((babyelf->s).flags2 >> 2) & 1); }

// --------------------------------------------

static const SolidFunc sActorUpdate[ACTOR_COUNT];
static const SolidFunc sActorDeinitalizer[ACTOR_COUNT];

// --------------------------------------------

static void initStaticActor(struct Solid* p);
static void initDynamicActor(struct Solid* p);
static void loadNeutralZeroColor(struct Solid* p);
static void initActor8(struct Solid* p);
void initActor21(struct Solid* p);
void initActor23(struct Solid* p);
void initActor28(struct Solid* p);
void initActor32(struct Solid* p);

static void Actor_Init(struct Solid* p) {
  // clang-format off
  static SolidFunc const sInitializers[] = {
      [0] =  initStaticActor,
      [ACTOR_ZERO_WALK] =  loadNeutralZeroColor,
      [ACTOR_CIEL_WALK] =  initDynamicActor,
      [3] =  initStaticActor,
      [4] =  initDynamicActor,
      [5] =  initStaticActor,
      [6] =  initDynamicActor,
      [7] =  initStaticActor,
      [8] =  initActor8,
      [9] =  initStaticActor,
      [10] = initStaticActor,
      [11] = initDynamicActor,
      [12] = initDynamicActor,
      [13] = initStaticActor,
      [14] = initDynamicActor,
      [15] = initStaticActor,
      [16] = initStaticActor,
      [17] = initStaticActor,
      [18] = initDynamicActor,
      [19] = initDynamicActor,
      [20] = initDynamicActor,
      [21] = initActor21,
      [22] = initStaticActor,
      [23] = initActor23,
      [24] = initStaticActor,
      [25] = initStaticActor,
      [26] = initStaticActor,
      [27] = initDynamicActor,
      [28] = initActor28,
      [29] = initStaticActor,
      [30] = initStaticActor,
      [31] = initStaticActor,
      [32] = initActor32,
      [33] = initDynamicActor,
      [34] = initStaticActor,
      [35] = initDynamicActor,
      [36] = initStaticActor,
      [37] = initStaticActor,
      [38] = initStaticActor,
      [39] = initDynamicActor,
      [40] = initDynamicActor,
      [41] = initStaticActor,
      [42] = initDynamicActor,
      [43] = initDynamicActor,
      [44] = initStaticActor,
      [45] = initDynamicActor,
      [46] = initStaticActor,
      [47] = initDynamicActor,
      [48] = initDynamicActor,
      [49] = initDynamicActor,
      [50] = initDynamicActor,
      [51] = initDynamicActor,
      [52] = initStaticActor,
      [53] = initStaticActor,
      [54] = initStaticActor,
      [55] = initStaticActor,
      [56] = initDynamicActor,
      [57] = initStaticActor,
      [58] = initStaticActor,
      [59] = initStaticActor,
      [60] = initDynamicActor,
      [61] = initDynamicActor,
      [62] = initDynamicActor,
      [63] = initStaticActor,
      [64] = initStaticActor,
      [65] = initStaticActor,
  };
  // clang-format on
  (sInitializers[(p->s).work[0]])(p);
  return;
}

// --------------------------------------------

static void ActorDummy_Update(struct Solid* p);
static void Actor1_Update(struct Solid* p);
static void Actor2_Update(struct Solid* p);
static void Actor3_Update(struct Solid* p);
static void Actor4_Update(struct Solid* p);
static void Actor5_Update(struct Solid* p);
static void Actor6_Update(struct Solid* p);
static void Actor7_Update(struct Solid* p);
void Actor8_Update(struct Solid* p);
void ActorCrashedPantheon_Update(struct Solid* p);
void Actor10_Update(struct Solid* p);
void ActorLeviathan11_Update(struct Solid* p);
void ActorFefnir12_Update(struct Solid* p);
void Actor13_Update(struct Solid* p);
void ActorSaveSelectCiel_Update(struct Solid* p);
void Actor15_Update(struct Solid* p);
void ActorOperator_Update(struct Solid* p);
void Actor17_Update(struct Solid* p);
void Actor18_Update(struct Solid* p);
void Actor19_Update(struct Solid* p);
void Actor20_Update(struct Solid* p);
void Actor21_Update(struct Solid* p);
void Actor22_Update(struct Solid* p);
void Actor23_Update(struct Solid* p);
void Actor24_Update(struct Solid* p);
void Actor25_Update(struct Solid* p);
void Actor26_Update(struct Solid* p);
void Actor27_Update(struct Solid* p);
void Actor28_Update(struct Solid* p);
void Actor29_Update(struct Solid* p);
void Actor30_Update(struct Solid* p);
void Actor31_Update(struct Solid* p);
void Actor32_Update(struct Solid* p);
void Actor33_Update(struct Solid* p);
void Actor34_Update(struct Solid* p);
void Actor35_Update(struct Solid* p);
void Actor36_Update(struct Solid* p);
void Actor37_Update(struct Solid* p);
void Actor38_Update(struct Solid* p);
void Actor39_Update(struct Solid* p);
void ActorOmegaZero40_Update(struct Solid* p);
void Actor41_Update(struct Solid* p);
void ActorLastHarpuia_Update(struct Solid* p);
void ActorLastFefnir_Update(struct Solid* p);
void ActorLastFefnirFireball_Update(struct Solid* p);
void ActorLastLeviathan_Update(struct Solid* p);
void ActorLastX_Update(struct Solid* p);
void Actor47_Update(struct Solid* p);
void Actor48_Update(struct Solid* p);
void FUN_080d5c5c(struct Solid* p);
void FUN_080d5d20(struct Solid* p);
void FUN_080d5e08(struct Solid* p);
void omega1_080d5fc8(struct Solid* p);
void FUN_080d6504(struct Solid* p);
void FUN_080d6814(struct Solid* p);
void FUN_080d6afc(struct Solid* p);
void FUN_080d6c80(struct Solid* p);
void FUN_080d6fa0(struct Solid* p);
void FUN_080d724c(struct Solid* p);
void FUN_080d740c(struct Solid* p);
void FUN_080d751c(struct Solid* p);
void FUN_080d7638(struct Solid* p);
void Actor62_Update(struct Solid* p);
void Actor63_Update(struct Solid* p);
void Actor64_Update(struct Solid* p);
void Actor65_Update(struct Solid* p);

void Actor_Update(struct Solid* p) {
  // clang-format off
  static SolidFunc const sUpdates[] = {
      [0] =  ActorDummy_Update,
      [ACTOR_ZERO_WALK] =  Actor1_Update,
      [ACTOR_CIEL_WALK] =  Actor2_Update,
      [3] =  Actor3_Update,
      [4] =  Actor4_Update,
      [5] =  Actor5_Update,
      [6] =  Actor6_Update,
      [7] =  Actor7_Update,
      [8] =  Actor8_Update,
      [9] =  ActorCrashedPantheon_Update,
      [10] = Actor10_Update,
      [11] = ActorLeviathan11_Update,
      [12] = ActorFefnir12_Update,
      [13] = Actor13_Update,
      [14] = ActorSaveSelectCiel_Update,
      [15] = Actor15_Update,
      [16] = ActorOperator_Update,
      [17] = Actor17_Update,
      [18] = Actor18_Update,
      [19] = Actor19_Update,
      [20] = Actor20_Update,
      [21] = Actor21_Update,
      [22] = Actor22_Update,
      [23] = Actor23_Update,
      [24] = Actor24_Update,
      [25] = Actor25_Update,
      [26] = Actor26_Update,
      [27] = Actor27_Update,
      [28] = Actor28_Update,
      [29] = Actor29_Update,
      [30] = Actor30_Update,
      [31] = Actor31_Update,
      [32] = Actor32_Update,
      [33] = Actor33_Update,
      [34] = Actor34_Update,
      [35] = Actor35_Update,
      [36] = Actor36_Update,
      [37] = Actor37_Update,
      [38] = Actor38_Update,
      [39] = Actor39_Update,
      [40] = ActorOmegaZero40_Update,
      [41] = Actor41_Update,
      [42] = ActorLastHarpuia_Update,
      [43] = ActorLastFefnir_Update,
      [44] = ActorLastFefnirFireball_Update,
      [45] = ActorLastLeviathan_Update,
      [46] = ActorLastX_Update,
      [47] = Actor47_Update,
      [48] = Actor48_Update,
      [49] = FUN_080d5c5c,
      [50] = FUN_080d5d20,
      [51] = FUN_080d5e08,
      [52] = omega1_080d5fc8,
      [53] = FUN_080d6504,
      [54] = FUN_080d6814,
      [55] = FUN_080d6afc,
      [56] = FUN_080d6c80,
      [57] = FUN_080d6fa0,
      [58] = FUN_080d724c,
      [59] = FUN_080d740c,
      [60] = FUN_080d751c,
      [61] = FUN_080d7638,
      [62] = Actor62_Update,
      [63] = Actor63_Update,
      [64] = Actor64_Update,
      [65] = Actor65_Update,
  };
  // clang-format on
  (sUpdates[(p->s).work[0]])(p);
  return;
}

// --------------------------------------------

static void deleteActor(struct Solid* p);

void Actor_Die(struct Solid* p) {
  // clang-format off
  static const SolidFunc sDeinitalizer[] = {
      [0] =  deleteActor,
      [ACTOR_ZERO_WALK] =  deleteActor,
      [ACTOR_CIEL_WALK] =  deleteActor,
      [3] =  deleteActor,
      [4] =  deleteActor,
      [5] =  deleteActor,
      [6] =  deleteActor,
      [7] =  deleteActor,
      [8] =  deleteActor,
      [9] =  deleteActor,
      [10] = deleteActor,
      [11] = deleteActor,
      [12] = deleteActor,
      [13] = deleteActor,
      [14] = deleteActor,
      [15] = deleteActor,
      [16] = deleteActor,
      [17] = deleteActor,
      [18] = deleteActor,
      [19] = deleteActor,
      [20] = deleteActor,
      [21] = deleteActor,
      [22] = deleteActor,
      [23] = deleteActor,
      [24] = deleteActor,
      [25] = deleteActor,
      [26] = deleteActor,
      [27] = deleteActor,
      [28] = deleteActor,
      [29] = deleteActor,
      [30] = deleteActor,
      [31] = deleteActor,
      [32] = deleteActor,
      [33] = deleteActor,
      [34] = deleteActor,
      [35] = deleteActor,
      [36] = deleteActor,
      [37] = deleteActor,
      [38] = deleteActor,
      [39] = deleteActor,
      [40] = deleteActor,
      [41] = deleteActor,
      [42] = deleteActor,
      [43] = deleteActor,
      [44] = deleteActor,
      [45] = deleteActor,
      [46] = deleteActor,
      [47] = deleteActor,
      [48] = deleteActor,
      [49] = deleteActor,
      [50] = deleteActor,
      [51] = deleteActor,
      [52] = deleteActor,
      [53] = deleteActor,
      [54] = deleteActor,
      [55] = deleteActor,
      [56] = deleteActor,
      [57] = deleteActor,
      [58] = deleteActor,
      [59] = deleteActor,
      [60] = deleteActor,
      [61] = deleteActor,
      [62] = deleteActor,
      [63] = deleteActor,
      [64] = deleteActor,
      [65] = deleteActor,
  };
  // clang-format on
  (sDeinitalizer[(p->s).work[0]])(p);
}

// --------------------------------------------

// ピシュンと音を立ててキャラクターを転送させる処理？(帰還)
u16 FUN_080d0934(struct Entity* p, motion_t m, u8 r2) {
  switch (p->mode[3]) {
    case 0: {
      p->work[2] = 30;
      p->mode[3]++;
    }
    case 1: {
      UpdateMotionGraphic(p);
      if (p->work[2] & 1) {
        PaintEntityWhite(p);
      } else {
        UpdateEntityPaletteID(p);
      }
      p->work[2]--;
      if (p->work[2] == 0) {
        p->work[2] = 8;
        p->mode[3]++;
      }
      break;
    }
    case 2: {
      InitScalerotMotion1(p);
      if (r2 != 0) {
        ResetDynamicMotion(p);
      }
      SetMotion(p, m);
      p->mode[3]++;
    }
    case 3: {
      UpdateMotionGraphic(p);
      PaintEntityWhite(p);
      (p->spr).mag.x = p->work[2] * -4 + 0x120;
      (p->spr).mag.y = p->work[2] * 4 + 0xe0;
      if (--p->work[2] != 0) {
        return 0;
      }
      p->work[2] = 4;
      p->mode[3]++;
      break;
    }
    case 4: {
      UpdateMotionGraphic(p);
      PaintEntityWhite(p);
      (p->spr).mag.x = p->work[2] * 0x40 + 0x20;
      (p->spr).mag.y = p->work[2] * -0x20 + 0x160;
      if (--p->work[2] != 0) {
        return 0;
      }
      (p->d).y = -0xc00;
      PlaySound(SE_TENSOU_BACK);
      p->mode[3]++;
      break;
    }
    case 5: {
      UpdateMotionGraphic(p);
      PaintEntityWhite(p);
      (p->spr).mag.x = 0x20;
      (p->d).y -= 0x40;
      (p->coord).y += (p->d).y * 2;
      if (0x3000 < CalcFromCamera(&gStageRun.vm.camera, &p->coord)) {
        p->flags &= ~DISPLAY;
        p->mode[3] = 0;
        return 1;
      }
      break;
    }
  }

  return 0;
}

// ピシュンと音を立ててキャラクターを転送させる処理？(召喚)
NON_MATCH u16 FUN_080d0aa0(struct Entity* p, motion_t m, u8 r2) {
#if MODERN
  switch (p->mode[3]) {
    case 0: {
      InitScalerotMotion1(p);
      if (r2 != 0) {
        ResetDynamicMotion(p);
      }
      SetMotion(p, m);
      (p->spr).mag.x = 0x20;
      (p->spr).mag.y = 0x200;
      PaintEntityWhite(p);
      (p->unk_coord).y = FUN_08009f6c((p->coord).x, (p->coord).y);
      (p->coord).y = gStageRun.vm.camera.viewport.y - PIXEL(96);
      p->mode[3]++;
    }
    case 1: {
      UpdateMotionGraphic(p);
      (p->coord).y += 0x1c00;
      if ((p->coord).y <= (p->unk_coord).y) {
        return 0;
      }
      (p->coord).y = (p->unk_coord).y;
      PlaySound(SE_TENSOU_BACK);
      p->work[2] = 1;
      p->mode[3]++;
      break;
    }
    case 2: {
      UpdateMotionGraphic(p);
      (p->spr).mag.x = p->work[2] * 0x40 + 0x20;
      (p->spr).mag.y = p->work[2] * -0x20 + 0x160;
      if (++p->work[2] < 5) {
        return 0;
      }
      p->work[2] = 1;
      p->mode[3]++;
      break;
    }
    case 3: {
      UpdateMotionGraphic(p);
      (p->spr).mag.x = p->work[2] * -4 + 0x120;
      (p->spr).mag.y = p->work[2] * 4 + 0xe0;
      if (++p->work[2] < 9) {
        return 0;
      }
      p->mode[3]++;
      break;
    }
    case 4: {
      InitNonAffineMotion(p);
      if (r2 != 0) {
        ResetDynamicMotion(p);
      }
      SetMotion(p, m);
      p->work[2] = 30;
      p->mode[3]++;
    }
    case 5: {
      UpdateMotionGraphic(p);
      if (p->work[2] & 1) {
        UpdateEntityPaletteID(p);
      } else {
        PaintEntityWhite(p);
      }
      if (--p->work[2] == 0) {
        p->mode[3] = 0;
        return 1;
      }
    }
  }
  return 0;
#else
  INCCODE("asm/wip/FUN_080d0aa0.inc");
#endif
}

// --------------------------------------------

static void initStaticActor(struct Solid* p) {
  (p->s).flags |= DISPLAY;
  (p->s).flags |= FLIPABLE;
  InitNonAffineMotion(&p->s);
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  Actor_Update(p);
}

static void initDynamicActor(struct Solid* p) {
  (p->s).flags |= DISPLAY;
  (p->s).flags |= FLIPABLE;
  InitNonAffineMotion(&p->s);
  ResetDynamicMotion(&p->s);
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  Actor_Update(p);
}

// --------------------------------------------

static void ActorDummy_Update(struct Solid* p) {
  SET_SOLID_ROUTINE(p, ENTITY_DIE);
  Actor_Die(p);
}

// --------------------------------------------

static void deleteActor(struct Solid* p) {
  (p->s).flags &= ~DISPLAY;
  EXIT_BODY(p);
  (p->s).flags2 &= ~ENTITY_HAZARD;
  SET_SOLID_ROUTINE(p, ENTITY_EXIT);
}

// --------------------------------------------

static void loadNeutralZeroColor(struct Solid* p) {
  if (FLAG(gCurStory.s.gameflags, FLAG_HARD)) {
    LoadZeroPalette(&p->s, BODY_CHIP_PROTO);
  } else if (FLAG(gCurStory.s.gameflags, FLAG_ULTIMATE)) {
    LoadZeroPalette(&p->s, BODY_CHIP_ULTIMA);
  } else {
    LoadZeroPalette(&p->s, BODY_CHIP_NONE);
  }
  initDynamicActor(p);
}

// --------------------------------------------

static void Actor1_Update(struct Solid* p) {
  switch ((p->s).mode[1]) {
    case 0:
      (p->s).taskCol = 0x10;
      (p->s).coord.y = FUN_08009f6c((p->s).coord.x + PIXEL(240), (p->s).coord.y);
      (p->s).unk_2c = NULL;
      (p->s).taskCol = 0x10;
      SetMotion(&p->s, MOTION(DM196_ZERO_WALK, 0));
      (p->s).mode[1]++;
      // fallthrough
    case 1:
      UpdateMotionGraphic(&p->s);
      (p->s).coord.x += 0x50;
      if ((p->s).scriptEntity->flags & 1) {
        if ((p->s).motion.state == 4) {
          SetMotion(&p->s, MOTION(DM051_ZERO_UNK, 3));
          (p->s).work[2] = 0x10;
          (p->s).mode[1]++;
        }
      }
      break;
    case 2:
      UpdateMotionGraphic(&p->s);
      (p->s).work[2]--;
      if ((u8)(p->s).work[2] == 0) {
        SET_XFLIP(&p->s, 0);
        (p->s).mode[1]++;
      }
      break;
    case 3:
      UpdateMotionGraphic(&p->s);
      if ((p->s).scriptEntity->flags & 2) {
        SetMotion(&p->s, MOTION(DM051_ZERO_UNK, 1));
        (p->s).mode[1]++;
      }
      break;
    case 4:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 3) {
        (p->s).work[2] = 8;
        (p->s).mode[1]++;
      }
      break;
    case 5:
      UpdateMotionGraphic(&p->s);
      (p->s).work[2]--;
      if ((u8)(p->s).work[2] == 0) {
        bool8 isRight = 1;
        SET_XFLIP(&p->s, isRight);
        SetMotion(&p->s, MOTION(DM003_ZERO_DASH, 0));
        CreateParticle(&(p->s).coord, 0, ((p->s).flags >> 4) & isRight);
        PlaySound(SE_DASH_1);
        (p->s).work[2] = 0x20;
        (p->s).mode[1]++;
      }
      break;
    case 6:
      UpdateMotionGraphic(&p->s);
      if ((p->s).work[2] != 0) {
        (p->s).work[2]--;
        if ((p->s).unk_2c == NULL) {
          (p->s).unk_2c = CreateAfterImages(&p->s);
        }
      } else if ((p->s).unk_2c != NULL) {
        (p->s).unk_2c->work[1] = 1;
      }
      (p->s).coord.x += 0x380;
      break;
  }
}

// --------------------------------------------

static void Actor2_Update(struct Solid* p) {
  switch ((p->s).mode[1]) {
    case 0: {
      (p->s).coord.y = FUN_08009f6c((p->s).coord.x + 0xF000, (p->s).coord.y);
      SetMotion(&p->s, MOTION(DM194_CIEL, 15));
      (p->s).mode[1]++;
      FALLTHROUGH
    }
    case 1: {
      UpdateMotionGraphic(&p->s);
      (p->s).coord.x += 0x50;
      if (((p->s).scriptEntity->flags & (1 << 0)) && ((p->s).motion.state == MOTION_NEXT)) {
        SetMotion(&p->s, MOTION(DM194_CIEL, 17));
        (p->s).mode[1]++;
      }
      break;
    }

    case 2: {
      UpdateMotionGraphic(&p->s);
      if (((p->s).scriptEntity->flags & (1 << 1)) == 0) {
        return;
      }
      SetMotion(&p->s, MOTION(DM194_CIEL, 19));
      (p->s).mode[1]++;
      break;
    }

    case 3: {
      UpdateMotionGraphic(&p->s);
      if (((p->s).scriptEntity->flags & (1 << 2)) == 0) {
        return;
      }
      SetMotion(&p->s, MOTION(DM194_CIEL, 17));
      (p->s).mode[1]++;
      break;
    }

    case 4: {
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}

// --------------------------------------------

static void Actor3_Update(struct Solid* p) {
  switch ((p->s).mode[1]) {
    case 0: {
      (p->s).coord.y = FUN_08009f6c((p->s).coord.x + PIXEL(240), (p->s).coord.y);
      if ((p->s).work[1] == 0) {
        LOAD_STATIC_GRAPHIC(SM130_PROLOGUE_RESISTANCE);
      }
      SetMotion(&p->s, MOTION(SM130_PROLOGUE_RESISTANCE, 2));
      (p->s).mode[1]++;
      FALLTHROUGH
    }
    case 1: {
      UpdateMotionGraphic(&p->s);
      (p->s).coord.x += 0x50;
      if ((p->s).motion.state != MOTION_NEXT) {
        return;
      }
      if (((p->s).scriptEntity->flags & 1) == 0) {
        return;
      }
      SetMotion(&p->s, MOTION(SM130_PROLOGUE_RESISTANCE, 0));
      (p->s).mode[1]++;
      break;
    }
    case 2: {
      UpdateMotionGraphic(&p->s);
      if (((p->s).scriptEntity->flags & 2) == 0) {
        return;
      }
      LOAD_STATIC_GRAPHIC(SM130_PROLOGUE_RESISTANCE);
      (p->s).mode[1]++;
      break;
    }
    case 3: {
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}

static void Actor4_Update(struct Solid* p) {
  switch ((p->s).mode[1]) {
    case 0:
      (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y);
      SetMotion(&p->s, MOTION(DM194_CIEL, 16));
      (p->s).mode[1]++;
      // fallthrough
    case 1:
      UpdateMotionGraphic(&p->s);
      if ((p->s).scriptEntity->flags & 1) {
        SetMotion(&p->s, MOTION(DM194_CIEL, 20));
        (p->s).mode[1]++;
      }
      break;
    case 2:
      UpdateMotionGraphic(&p->s);
      if ((p->s).scriptEntity->flags & 2) {
        SetMotion(&p->s, MOTION(DM194_CIEL, 17));
        (p->s).work[2] = 8;
        (p->s).mode[1]++;
      }
      break;
    case 3:
      SET_XFLIP(&p->s, 0);
      UpdateMotionGraphic(&p->s);
      (p->s).work[2]--;
      if ((u8)(p->s).work[2] == 0) {
        SetMotion(&p->s, MOTION(DM194_CIEL, 18));
        (p->s).mode[1]++;
      }
      break;
    case 4:
      UpdateMotionGraphic(&p->s);
      break;
  }
}

static void Actor5_Update(struct Solid* p) {
  switch ((p->s).mode[1]) {
    case 0:
      (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y);
      if ((p->s).work[1] == 0) {
        LOAD_STATIC_GRAPHIC(SM140_RESISTANCE_MOB);
      }
      SetMotion(&p->s, MOTION(SM140_RESISTANCE_MOB, 5));
      (p->s).mode[1]++;
      // fallthrough
    case 1:
      UpdateMotionGraphic(&p->s);
      if ((p->s).scriptEntity->flags & 1) {
        SetMotion(&p->s, MOTION(SM140_RESISTANCE_MOB, 6));
        (p->s).work[2] = 0x2D;
        (p->s).mode[1]++;
      }
      if ((p->s).scriptEntity->flags & 2) {
        SetMotion(&p->s, MOTION(SM140_RESISTANCE_MOB, 7));
        (p->s).work[2] = 0xE;
        (p->s).mode[1] = 3;
      }
      break;
    case 2:
      if ((p->s).work[2]++ > 0x2C) {
        PlaySound(SE_UNK_59);
        (p->s).work[2] = 0;
      }
      UpdateMotionGraphic(&p->s);
      break;
    case 3:
      UpdateMotionGraphic(&p->s);
      (p->s).coord.x += 0x1C0;
      (p->s).work[2]--;
      if ((u8)(p->s).work[2] == 0) {
        SetMotion(&p->s, MOTION(SM140_RESISTANCE_MOB, 5));
        (p->s).work[2] = 8;
        (p->s).mode[1]++;
      }
      break;
    case 4:
      UpdateMotionGraphic(&p->s);
      (p->s).work[2]--;
      if ((u8)(p->s).work[2] == 0) {
        SET_XFLIP(&p->s, 0);
        (p->s).work[2] = 8;
        (p->s).mode[1]++;
      }
      break;
    case 5:
      UpdateMotionGraphic(&p->s);
      (p->s).work[2]--;
      if ((u8)(p->s).work[2] == 0) {
        SetMotion(&p->s, MOTION(SM140_RESISTANCE_MOB, 6));
        (p->s).mode[1]++;
      }
      break;
    case 6:
      UpdateMotionGraphic(&p->s);
      break;
  }
}

static void Actor6_Update(struct Solid* p) {
  switch ((p->s).mode[1]) {
    case 0:
      if (FUN_080d0aa0(&p->s, MOTION(DM190_HARPUIA, 0), 1) != 0) {
        (p->s).mode[1] += 2;
      }
      break;
    case 2:
      UpdateMotionGraphic(&p->s);
      if ((p->s).scriptEntity->flags & 1) {
        SetMotion(&p->s, MOTION(DM190_HARPUIA, 28));
        (p->s).mode[1]++;
      }
      break;
    case 3:
      UpdateMotionGraphic(&p->s);
      if ((p->s).scriptEntity->flags & 2) {
        SetMotion(&p->s, MOTION(DM190_HARPUIA, 29));
        (p->s).mode[1]++;
      }
      break;
    case 4:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 3) {
        SetMotion(&p->s, MOTION(DM190_HARPUIA, 0));
        (p->s).mode[1]++;
      }
      break;
    case 5:
      UpdateMotionGraphic(&p->s);
      if ((p->s).scriptEntity->flags & 4) {
        (p->s).work[2] = 0x1E;
        (p->s).mode[1]++;
      }
      break;
    case 6:
      if (FUN_080d0934(&p->s, MOTION(DM190_HARPUIA, 0), 1) != 0) {
        (p->s).mode[1]++;
      }
      break;
    case 7:
      break;
  }
}

static void Actor7_Update(struct Solid* p) {
  switch ((p->s).mode[1]) {
    case 0: {
      (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y);
      wStaticGraphicTilenums[19] = 0x388;
      wStaticMotionPalIDs[19] = 9;
      LOAD_STATIC_GRAPHIC(SM019_PANTHEON_HUNTER);
      SetMotion(&p->s, MOTION(SM019_PANTHEON_HUNTER, 9));
      (p->s).mode[1]++;
      FALLTHROUGH;
    }
    case 1: {
      UpdateMotionGraphic(&p->s);
      (p->s).coord.x += PIXEL(1);
      break;
    }
  }
}

// --------------------------------------------

NAKED static void initActor8(struct Solid* p) {
  asm(".syntax unified\n\
	push {r4, r5, r6, r7, lr}\n\
	mov r7, sb\n\
	mov r6, r8\n\
	push {r6, r7}\n\
	adds r6, r0, #0\n\
	ldr r5, [r6, #0x54]\n\
	asrs r0, r5, #0xc\n\
	movs r1, #0xf\n\
	bl __modsi3\n\
	lsls r0, r0, #0x10\n\
	lsrs r0, r0, #0x10\n\
	mov sb, r0\n\
	ldr r4, [r6, #0x58]\n\
	asrs r0, r4, #0xc\n\
	movs r1, #0xa\n\
	bl __modsi3\n\
	lsls r0, r0, #0x10\n\
	lsrs r0, r0, #0x10\n\
	mov r8, r0\n\
	adds r0, r5, #0\n\
	adds r1, r4, #0\n\
	bl GetMetatileAttr\n\
	lsls r0, r0, #0x10\n\
	lsrs r2, r0, #0x10\n\
	cmp r2, #0\n\
	bne _080D1558\n\
	ldrb r1, [r6, #0xa]\n\
	movs r0, #0xfe\n\
	ands r0, r1\n\
	movs r1, #0xfd\n\
	ands r0, r1\n\
	strb r0, [r6, #0xa]\n\
	adds r0, r6, #0\n\
	adds r0, #0x8c\n\
	str r2, [r0]\n\
	adds r0, #4\n\
	str r2, [r0]\n\
	adds r0, #4\n\
	strb r2, [r0]\n\
	ldrb r1, [r6, #0xa]\n\
	movs r0, #0xfb\n\
	ands r0, r1\n\
	strb r0, [r6, #0xa]\n\
	ldr r1, _080D1554 @ =gSolidFnTable\n\
	ldrb r0, [r6, #9]\n\
	lsls r0, r0, #2\n\
	adds r0, r0, r1\n\
	movs r1, #3\n\
	str r1, [r6, #0xc]\n\
	ldr r0, [r0]\n\
	ldr r0, [r0, #0xc]\n\
	str r0, [r6, #0x14]\n\
	b _080D172E\n\
	.align 2, 0\n\
_080D1554: .4byte gSolidFnTable\n\
_080D1558:\n\
	ldrb r1, [r6, #0xa]\n\
	movs r0, #0xfe\n\
	ands r0, r1\n\
	movs r1, #2\n\
	orrs r0, r1\n\
	strb r0, [r6, #0xa]\n\
	ldr r0, [r6, #0x54]\n\
	str r0, [r6, #0x64]\n\
	ldr r0, [r6, #0x58]\n\
	str r0, [r6, #0x68]\n\
	movs r4, #0xba\n\
	ldr r0, _080D1630 @ =wStaticGraphicTilenums\n\
	lsls r1, r4, #1\n\
	adds r0, r0, r1\n\
	movs r2, #0xbf\n\
	lsls r2, r2, #2\n\
	strh r2, [r0]\n\
	ldr r0, _080D1634 @ =wStaticMotionPalIDs\n\
	adds r7, r0, r1\n\
	movs r0, #6\n\
	strh r0, [r7]\n\
	mov r1, r8\n\
	lsls r0, r1, #0x10\n\
	asrs r5, r0, #0x10\n\
	cmp r5, #1\n\
	bne _080D15C2\n\
	lsls r4, r4, #4\n\
	movs r0, #0xba\n\
	lsls r0, r0, #2\n\
	adds r4, r4, r0\n\
	ldr r1, _080D1638 @ =gStaticMotionGraphics\n\
	adds r0, r4, r1\n\
	ldrh r1, [r0, #6]\n\
	lsrs r1, r1, #6\n\
	subs r1, r2, r1\n\
	lsls r1, r1, #5\n\
	movs r2, #0x80\n\
	lsls r2, r2, #9\n\
	adds r1, r1, r2\n\
	bl LoadGraphic\n\
	ldr r0, _080D163C @ =gStaticMotionGraphics+12\n\
	adds r4, r4, r0\n\
	ldrh r1, [r7]\n\
	ldrb r0, [r4, #7]\n\
	subs r1, r1, r0\n\
	lsls r1, r1, #5\n\
	movs r2, #0x80\n\
	lsls r2, r2, #2\n\
	adds r1, r1, r2\n\
	adds r0, r4, #0\n\
	bl LoadPalette\n\
_080D15C2:\n\
	cmp r5, #0\n\
	bne _080D1680\n\
	ldrb r0, [r6, #0xa]\n\
	movs r1, #4\n\
	orrs r0, r1\n\
	strb r0, [r6, #0xa]\n\
	adds r4, r6, #0\n\
	adds r4, #0x74\n\
	ldr r1, _080D1640 @ =Collision_08370ab8\n\
	adds r2, r6, #0\n\
	adds r2, #0x54\n\
	adds r0, r4, #0\n\
	movs r3, #0\n\
	bl InitBody\n\
	str r6, [r4, #0x2c]\n\
	str r5, [r4, #0x24]\n\
	adds r0, r6, #0\n\
	bl InitNonAffineMotion\n\
	movs r0, #0\n\
	strb r0, [r6, #0x11]\n\
	mov r1, sb\n\
	lsls r0, r1, #0x10\n\
	asrs r4, r0, #0x10\n\
	adds r0, r4, #0\n\
	subs r0, #0xf\n\
	lsls r0, r0, #6\n\
	str r0, [r6, #0x60]\n\
	lsls r0, r4, #4\n\
	adds r0, r0, r4\n\
	movs r1, #7\n\
	bl __modsi3\n\
	movs r1, #3\n\
	subs r1, r1, r0\n\
	lsls r1, r1, #7\n\
	str r1, [r6, #0x5c]\n\
	ldr r2, _080D1644 @ =RNG_0202f388\n\
	ldr r1, [r2]\n\
	ldr r0, _080D1648 @ =0x000343FD\n\
	muls r0, r1, r0\n\
	ldr r1, _080D164C @ =0x00269EC3\n\
	adds r0, r0, r1\n\
	lsls r0, r0, #1\n\
	lsrs r1, r0, #1\n\
	str r1, [r2]\n\
	lsrs r0, r0, #0x11\n\
	movs r1, #0x7f\n\
	ands r0, r1\n\
	strb r0, [r6, #0x12]\n\
	cmp r4, #0xd\n\
	ble _080D1654\n\
	ldr r1, _080D1650 @ =0x0000BA02\n\
	b _080D165A\n\
	.align 2, 0\n\
_080D1630: .4byte wStaticGraphicTilenums\n\
_080D1634: .4byte wStaticMotionPalIDs\n\
_080D1638: .4byte gStaticMotionGraphics\n\
_080D163C: .4byte gStaticMotionGraphics+12\n\
_080D1640: .4byte Collision_08370ab8\n\
_080D1644: .4byte RNG_0202f388\n\
_080D1648: .4byte 0x000343FD\n\
_080D164C: .4byte 0x00269EC3\n\
_080D1650: .4byte 0x0000BA02\n\
_080D1654:\n\
	cmp r4, #0xb\n\
	ble _080D1668\n\
	ldr r1, _080D1664 @ =0x0000BA01\n\
_080D165A:\n\
	adds r0, r6, #0\n\
	bl SetMotion\n\
	b _080D1672\n\
	.align 2, 0\n\
_080D1664: .4byte 0x0000BA01\n\
_080D1668:\n\
	movs r1, #0xba\n\
	lsls r1, r1, #8\n\
	adds r0, r6, #0\n\
	bl SetMotion\n\
_080D1672:\n\
	ldr r0, [r6, #0x58]\n\
	ldr r2, _080D167C @ =0xFFFFF100\n\
	adds r0, r0, r2\n\
	b _080D1708\n\
	.align 2, 0\n\
_080D167C: .4byte 0xFFFFF100\n\
_080D1680:\n\
	adds r0, r6, #0\n\
	bl InitRotatableMotion\n\
	movs r0, #1\n\
	strb r0, [r6, #0x11]\n\
	ldr r0, _080D16C0 @ =0xFFFFFF00\n\
	str r0, [r6, #0x60]\n\
	movs r0, #3\n\
	mov r1, r8\n\
	ands r0, r1\n\
	subs r0, #1\n\
	strb r0, [r6, #0x12]\n\
	cmp r5, #2\n\
	bgt _080D16C8\n\
	ldr r1, _080D16C4 @ =0x0000BA06\n\
	adds r0, r6, #0\n\
	bl SetMotion\n\
	movs r0, #2\n\
	strb r0, [r6, #0x11]\n\
	lsls r0, r5, #4\n\
	adds r0, r0, r5\n\
	movs r1, #3\n\
	bl __modsi3\n\
	movs r1, #4\n\
	rsbs r1, r1, #0\n\
	subs r1, r1, r0\n\
	lsls r1, r1, #8\n\
	str r1, [r6, #0x5c]\n\
	b _080D16F8\n\
	.align 2, 0\n\
_080D16C0: .4byte 0xFFFFFF00\n\
_080D16C4: .4byte 0x0000BA06\n\
_080D16C8:\n\
	lsls r0, r5, #4\n\
	adds r0, r0, r5\n\
	movs r1, #3\n\
	bl __modsi3\n\
	movs r1, #3\n\
	rsbs r1, r1, #0\n\
	subs r1, r1, r0\n\
	lsls r1, r1, #8\n\
	str r1, [r6, #0x5c]\n\
	cmp r5, #7\n\
	ble _080D16F0\n\
	ldr r1, _080D16EC @ =0x0000BA08\n\
	adds r0, r6, #0\n\
	bl SetMotion\n\
	b _080D16F8\n\
	.align 2, 0\n\
_080D16EC: .4byte 0x0000BA08\n\
_080D16F0:\n\
	ldr r1, _080D173C @ =0x0000BA07\n\
	adds r0, r6, #0\n\
	bl SetMotion\n\
_080D16F8:\n\
	ldr r0, [r6, #0x54]\n\
	movs r2, #0x80\n\
	lsls r2, r2, #4\n\
	adds r0, r0, r2\n\
	str r0, [r6, #0x54]\n\
	ldr r0, [r6, #0x58]\n\
	ldr r1, _080D1740 @ =0xFFFFF800\n\
	adds r0, r0, r1\n\
_080D1708:\n\
	str r0, [r6, #0x58]\n\
	movs r0, #0xa\n\
	mov r2, r8\n\
	subs r0, r0, r2\n\
	adds r1, r6, #0\n\
	adds r1, #0x25\n\
	strb r0, [r1]\n\
	ldr r1, _080D1744 @ =gSolidFnTable\n\
	ldrb r0, [r6, #9]\n\
	lsls r0, r0, #2\n\
	adds r0, r0, r1\n\
	movs r1, #1\n\
	str r1, [r6, #0xc]\n\
	ldr r0, [r0]\n\
	ldr r0, [r0, #4]\n\
	str r0, [r6, #0x14]\n\
	adds r0, r6, #0\n\
	bl Actor_Update\n\
_080D172E:\n\
	pop {r3, r4}\n\
	mov r8, r3\n\
	mov sb, r4\n\
	pop {r4, r5, r6, r7}\n\
	pop {r0}\n\
	bx r0\n\
	.align 2, 0\n\
_080D173C: .4byte 0x0000BA07\n\
_080D1740: .4byte 0xFFFFF800\n\
_080D1744: .4byte gSolidFnTable\n\
 .syntax divided\n");
}

INCASM("asm/solid/actor_p1_p1_a.inc");

extern const struct Collision Collision_08370ad0;
extern const struct SlashedEnemy sProloguePantheons[4];

// 0x080d1cf4
void ActorCrashedPantheon_Update(struct Solid* p) {
  struct Coord c;
  u8 m1 = (p->s).mode[1];
  switch (m1) {
    case 0:
      wStaticGraphicTilenums[SM019_PANTHEON_HUNTER] = 0x284;
      wStaticMotionPalIDs[SM019_PANTHEON_HUNTER] = 5;
      if ((p->s).work[1] == 0) {
        LOAD_STATIC_GRAPHIC(SM019_PANTHEON_HUNTER);
      }
      (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y);
      SetMotion(&p->s, MOTION(SM019_PANTHEON_HUNTER, 1));
      (p->s).flags |= 4;
      {
        struct Body* b = &p->body;
        InitBody(b, &Collision_08370ad0, &(p->s).coord, 0);
        b->parent = (struct CollidableEntity*)p;
        b->fn = (BodyFunc)(u32)m1;
      }
      (p->s).mode[1]++;
      FALLTHROUGH;
    case 1:
      UpdateMotionGraphic(&p->s);
      if ((p->body).status & 0x200) {
        SetMotion(&p->s, MOTION(SM019_PANTHEON_HUNTER, 3));
        (p->s).mode[1]++;
      }
      break;
    case 2:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 3) {
        register s32 s10 asm("r5");
        u32* rng;
        register const struct SlashedEnemy* d asm("r4");
        u32 v1, s1, v2, v3, s3, v4;
        c.x = (p->s).coord.x;
        c.y = (p->s).coord.y + -0x1800;
        d = ({ const struct SlashedEnemy* d_ = sProloguePantheons; asm("" : "+r"(d_)); d_; });
        CreateSlashedEnemy(&c, d, 0, ({
                             u32 f_ = (p->s).flags;
                             u32 xf = ({ s10 = 0x10; s10; });
                             asm("" : "+r"(xf));
                             xf &= f_;
                             asm("" : "+r"(xf));
                             xf;
                           }));
        CreateSlashedEnemy(&c, &d[1], 0, ({
                             u32 f_ = (p->s).flags;
                             u32 xf = s10;
                             asm("" : "+r"(xf));
                             xf &= f_;
                             asm("" : "+r"(xf));
                             xf;
                           }));
        d += 2;
        CreateSlashedEnemy(&c, d, 0, ({
                             u32 f_ = (p->s).flags;
                             u32 xf = s10;
                             asm("" : "+r"(xf));
                             xf &= f_;
                             asm("" : "+r"(xf));
                             xf;
                           }));
        c.y = (p->s).coord.y + -0x1000;
        CreateSmoke(1, &c);
        rng = ({ u32* r_ = &RNG_0202f388; asm("" : "+r"(r_)); r_; });
        v1 = (*rng * 0x343FD + 0x269EC3) << 1;
        s1 = v1 >> 1;
        {
          u32 r = (v1 >> 0x11) & 0x1f;
          r = s10 - r;
          c.x = (p->s).coord.x + (r << 8);
        }
        v2 = (s1 * 0x343FD + 0x269EC3) << 1;
        *rng = v2 >> 1;
        c.y = (p->s).coord.y - (((v2 >> 0x11) & 0x1f) << 8);
        CreateSmoke(2, &c);
        v3 = (*rng * 0x343FD + 0x269EC3) << 1;
        s3 = v3 >> 1;
        c.x = (p->s).coord.x + ((s10 - ((v3 >> 0x11) & 0x1f)) << 8);
        v4 = (s3 * 0x343FD + 0x269EC3) << 1;
        *rng = v4 >> 1;
        c.y = (p->s).coord.y - (((v4 >> 0x11) & 0x1f) << 8);
        CreateSmoke(2, &c);
        PlaySound(0x2a);
        (p->s).flags &= ~DISPLAY;
        {
          s32 z = 0;
          (p->body).status = z;
          (p->body).prevStatus = z;
          (p->body).invincibleTime = z;
        }
        (p->s).flags &= ~4;
        (p->s).mode[1]++;
      }
      break;
  }
}

INCASM("asm/solid/actor_p1_p1_a_post.inc");

// 0x080d2804
void Actor13_Update(struct Solid* p) {
  struct Entity* q = (p->s).unk_28;
  switch ((p->s).mode[1]) {
    case 0:
      InitScalerotMotion1(&p->s);
      (p->s).spr.mag.x = 0x180;
      (p->s).spr.mag.y = 0x180;
      SetMotion(&p->s, MOTION(0x21, 0x00));
      SET_XFLIP(&p->s, TRUE);
      (p->s).coord.x = (q->coord).x + 0x1E00;
      (p->s).coord.y = (q->coord).y - 0x1E00;
      (p->s).mode[1]++;
      FALLTHROUGH;
    case 1: {
      s32 x;
      UpdateMotionGraphic(&p->s);
      x = (p->s).coord.x + 0x400;
      (p->s).coord.x = x;
      {
        struct Camera* cam = &gStageRun.vm.camera;
        if (x > cam->viewport.x + 0xB7FF) {
          SET_SOLID_ROUTINE(&p->s, ENTITY_DIE);
        }
      }
      break;
    }
  }
}

// 0x080d28b4
void ActorSaveSelectCiel_Update(struct Solid* p) {
  switch ((p->s).mode[1]) {
    case 0:
      (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y);
      SetMotion(&p->s, 0xC200);
      (p->s).mode[1]++;
      FALLTHROUGH;
    case 1:
      UpdateMotionGraphic(&p->s);
      break;
  }
}


// 0x080d28ec
void Actor15_Update(struct Solid* p) {
  switch ((p->s).mode[1]) {
    case 0:
      (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y) - 0x1C00;
      SetMotion(&p->s, 0xCA00);
      (p->s).taskCol = 0x1F;
      (p->s).mode[1]++;
      FALLTHROUGH;
    case 1:
      UpdateMotionGraphic(&p->s);
      break;
  }
}


// 0x080d2934
void ActorOperator_Update(struct Solid* p) {
  switch ((p->s).mode[1]) {
    case 0:
      (p->s).coord.x += ((p->s).work[1] != 0) ? 0xC00 : -0xC00;
      (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y) - 0x1B00;
      SetMotion(&p->s, 0xC900 | (p->s).work[1]);
      (p->s).taskCol = 0x1F;
      SET_XFLIP(p, (p->s).work[1] == 0);
      (p->s).mode[1]++;
      FALLTHROUGH;
    case 1:
      UpdateMotionGraphic(&p->s);
      break;
  }
}

static const struct Collision sCollisions_08370B58[11];

// 0x080D29D0
void Actor17_Update(struct Solid* p) {
  s32 md;
  md = (p->s).mode[1];
  switch (md) {
    case 0: {
      register struct Body* b asm("r4");
      if (((p->s).work[1] & 0x10) != 0) {
        PlaySound(0x2B);
        wStaticGraphicTilenums[SM236_SPARK] = 0xe0 << 2;
        wStaticMotionPalIDs[SM236_SPARK] = 8;
      }
      {
        const struct Graphic* g;
        const struct Palette* pal;
        register u32 ofs asm("r4");
        register void* pb asm("r3");
        ofs = (sizeof(struct ColorGraphic) * SM236_SPARK);
        g = gStaticGraphic(ofs);
        LoadGraphic((void*)g, (void*)((wStaticGraphicTilenums[SM236_SPARK] - g->ofs) * 32 + 0x10000));
        pb = STATIC_PALETTES;
        asm volatile("add %0, %0, %1" : "+l"(ofs) : "l"(pb));
        pal = (const struct Palette*)ofs;
        {
          register s32 t asm("r1");
          register s32 k asm("r0");
          t = (wStaticMotionPalIDs[SM236_SPARK] - pal->dst) * 32;
          asm volatile("mov %0, #0x80\n\tlsl %0, %0, #0x2" : "=l"(k));
          t += k;
          LoadPalette(pal, t);
        }
      }
      InitNonAffineMotion(&p->s);
      SetMotion(&p->s, 0xEC01);
      {
        u8* q = (u8*)p + 0x45;
        register s32 msk asm("r1");
        register s32 v asm("r0");
        register s32 four asm("r2");
        {
          register s32 t asm("r2");
          t = *q;
          msk = 0xD;
          msk = -msk;
          v = msk;
          v &= t;
        }
        four = 4;
        v |= four;
        *q = v;
        q += 4;
        v = *q;
        msk &= v;
        msk |= four;
        *q = msk;
        four |= (p->s).flags;
        (p->s).flags = four;
      }
      b = &p->body;
      {
        register s32 ix asm("r0");
        register s32 off asm("r1");
        off = (p->s).work[1];
        ix = 0xf;
        ix &= off;
        off = ix << 1;
        off += ix;
        off <<= 3;
        InitBody(b, (const struct Collision*)(off + (u32)&sCollisions_08370B58[2]), &(p->s).coord, 9);
      }
      *(struct Solid**)((u8*)b + 0x2c) = p;
      *(s32*)((u8*)b + 0x24) = md;
      (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y) + 0xFFFFB000;
      gBlendRegBuffer.bldclt = 0xfd << 6;
      (p->s).work[2] = 8;
      (p->s).mode[1]++;
      FALLTHROUGH;
    }
    case 1: {
      register struct WramBlendRegister* bb asm("r2");
      UpdateMotionGraphic(&p->s);
      if ((p->s).work[2] > 6) {
        register struct WramBlendRegister* b1 asm("r1");
        b1 = &gBlendRegBuffer;
        b1->bldalpha = 0x1010;
        bb = b1;
      } else {
        register s32 v asm("r0");
        register s32 k asm("r1");
        bb = &gBlendRegBuffer;
        k = (p->s).work[2];
        v = k << 1;
        v += k;
        k = 0x1f;
        v &= k;
        asm volatile("mov r3, #0x80\n\tlsl r3, r3, #0x5\n\tadd %0, r3, #0" : "=l"(k) :: "r3");
        v |= k;
        bb->bldalpha = v;
      }
      {
        register u32 t asm("r3");
        register s32 t0 asm("r0");
        t0 = (p->s).work[2] - 1;
        (p->s).work[2] = t0;
        t = (u32)(t0 << 24) >> 24;
        if (t == 0) {
          (p->s).flags &= 0xFE;
          bb->bldclt = t;
          (p->s).mode[1]++;
        }
      }
      break;
    }
    case 2:
      break;
  }
}


INCASM("asm/solid/actor_b_a.inc");

// 0x080D2D50
void Actor19_Update(struct Solid* p) {
  switch ((p->s).mode[1]) {
    case 0: {
      s32 x;
      wDynamicGraphicTilenums[0xc5] = 0x380;
      wDynamicMotionPalIDs[0xc5] = 8;
      SetMotion(&p->s, MOTION(0xc5, 0x01));
      x = (p->s).coord.x;
      (p->s).unk_coord.x = x;
      (p->s).coord.x = x + 0x1000;
      (p->s).unk_coord.y = (p->s).coord.y;
      {
        struct Camera* cam = &gStageRun.vm.camera;
        (p->s).coord.y = cam->viewport.y - 0x5000;
      }
      (p->s).mode[1]++;
      FALLTHROUGH;
    }
    case 1: {
      s32 x;
      s32 y;
      UpdateMotionGraphic(&p->s);
      x = (p->s).coord.x;
      (p->s).coord.x = (((x << 7) - x) + (p->s).unk_coord.x) >> 7;
      y = (p->s).coord.y;
      (p->s).coord.y = (((y << 7) - y) + (p->s).unk_coord.y) >> 7;
      if (((p->s).scriptEntity->flags & 1) != 0) {
        (p->s).mode[1]++;
      }
      break;
    }
    case 2:
      if (((u16)FUN_080d0934(&p->s, MOTION(0xc5, 0x01), 1) << 16) != 0) {
        (p->s).mode[1]++;
      }
      break;
  }
}

void Actor20_Update(struct Solid* p) {
  switch ((p->s).mode[1]) {
    case 0:
      wDynamicGraphicTilenums[0xb3] = 0x340;
      wDynamicMotionPalIDs[0xb3] = 7;
      (p->s).mode[1]++;
      /* fallthrough */
    case 1:
      if (FUN_080d0aa0(&p->s, MOTION(0xB3, 0x19), 1) != 0) {
        (p->s).mode[1]++;
      }
      break;
    case 2:
      UpdateMotionGraphic(&p->s);
      if ((p->s).scriptEntity->flags & 1) {
        (p->s).mode[1]++;
      }
      break;
    case 3:
      if (FUN_080d0934(&p->s, MOTION(0xB3, 0x19), 1) != 0) {
        (p->s).mode[1]++;
      }
      break;
    case 4:
      break;
  }
}

// Identical instructions except the routine constant lands in r3 (retail)
// vs r2 (agbcc) -- register-number tie.
NON_MATCH void initActor21(struct Solid* p) {
#if MODERN
  gWindowRegBuffer.dispcnt |= DISPCNT_WIN1_ON;
  gWindowRegBuffer.winin[2] |= 0xFE;
  gWindowRegBuffer.winin[1] = 0;
  (p->s).work[2] = 0;
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  Actor_Update(p);
#else
  INCCODE("asm/solid/actor_initActor21.inc");
#endif
}

// 0x080D2EDC
void Actor21_Update(struct Solid* p) {
  switch ((p->s).mode[1]) {
    case 0: {
      register s32 z asm("r1");
      z = 0;
      (p->s).coord.x = z;
      (p->s).coord.y = 0x93 << 8;
      (p->s).work[3] = z;
      (p->s).mode[1]++;
      FALLTHROUGH;
    }
    case 1: {
      register s32 i asm("r1");
      {
        register const s16* tb asm("r2");
        register s32 o asm("r0");
        tb = gSineTable;
        i = (p->s).work[3];
        o = (u32)(i << 0x19) >> 0x17;
        o += (s32)tb;
        {
          register s32 v asm("r2");
          register s32 k asm("r3");
          k = 0;
          v = *(const s16*)(o + k);
          o = v << 1;
          o += v;
          o <<= 4;
          (p->s).coord.x = o;
        }
      }
      i += 1;
      (p->s).work[3] = i;
      if ((u32)(i << 24) >> 24 <= 0x1f) {
        break;
      }
      (p->s).mode[1]++;
      (p->s).work[3] = 0x10;
      break;
    }
    case 2: {
      register s32 t asm("r0");
      t = (p->s).work[3] - 1;
      (p->s).work[3] = t;
      if ((t << 24) == 0) {
        break;
      }
      (p->s).work[3] = 4;
      goto adv;
    }
    case 3: {
      register s32 t2 asm("r0");
      (p->s).coord.x = (p->s).coord.x + (0x80 << 2);
      t2 = (p->s).work[3] - 1;
      (p->s).work[3] = t2;
      if ((t2 << 24) == 0) {
        break;
      }
      (p->s).work[3] = 8;
      goto adv;
    }
    case 4: {
      register s32 j asm("r1");
      j = (p->s).work[3] - 1;
      (p->s).work[3] = j;
      {
        register const s16* tb2 asm("r2");
        register s32 o2 asm("r0");
        tb2 = gSineTable;
        o2 = (u32)(j << 0x1b) >> 0x17;
        o2 += (s32)tb2;
        {
          register s32 v2 asm("r2");
          register s32 k2 asm("r3");
          k2 = 0;
          v2 = *(const s16*)(o2 + k2);
          o2 = v2 << 1;
          o2 += v2;
          o2 <<= 4;
          v2 = 0x80 << 4;
          o2 += v2;
          (p->s).coord.x = o2;
        }
      }
      if ((j << 24) != 0) {
        break;
      }
      (p->s).mode[1]++;
      PlaySound(0x97 << 1);
      break;
    }
    case 5: {
      register s32 y asm("r0");
      {
        register s32 x asm("r1");
        x = (p->s).coord.x;
        y = x << 1;
        y += x;
        y >>= 2;
        (p->s).coord.x = y;
      }
      {
        register s32 y2 asm("r1");
        register s32 lim asm("r1");
        y2 = (p->s).coord.y;
        y = y2 << 1;
        y += y2;
        y >>= 2;
        (p->s).coord.y = y;
        lim = 0x80 << 3;
        if (y > lim) {
          break;
        }
      }
      gWindowRegBuffer.dispcnt &= 0xBFFF;
    adv:
      (p->s).mode[1]++;
      break;
    }
    case 6:
      break;
  }
  {
    register s32 w asm("r0");
    register struct WramWindowRegister* wb asm("r5");
    register s32 b asm("r3");
    register s32 ff asm("r4");
    w = (p->s).work[2] + 1;
    (p->s).work[2] = w;
    wb = &gWindowRegBuffer;
    {
      register s32 cx asm("r2");
      register s32 t3 asm("r1");
      cx = (p->s).coord.x >> 8;
      b = 1;
      b &= w;
      w = b << 3;
      cx += w;
      t3 = cx + 0xbc;
      ff = 0xff;
      t3 &= ff;
      w = 0xbc;
      w -= cx;
      w <<= 8;
      t3 |= w;
      (wb->winH).half[1] = t3;
    }
    {
      register s32 cy asm("r0");
      cy = (p->s).coord.y >> 8;
      b <<= 2;
      cy += b;
      cy &= ff;
      (wb->winV).half[1] = cy;
    }
    {
      register u16* pm asm("r1");
      register s32 k3 asm("r3");
      register s32 k4 asm("r0");
      pm = (u16*)&gPaletteManager;
      k3 = 0x7FFF;
      asm volatile("add %0, %1, #0" : "=l"(k4) : "l"(k3));
      *pm = k4;
    }
  }
}


// 0x080D303C
void Actor22_Update(struct Solid* p) {
  switch ((p->s).mode[1]) {
    case 0: {
      u32 n;
      (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y);
      n = SM130_PROLOGUE_RESISTANCE;
      wStaticGraphicTilenums[n] = 0x24D;
      wStaticMotionPalIDs[n] = 8;
      if ((p->s).work[1] == 0) {
        LOAD_STATIC_GRAPHIC(n);
      }
      SetMotion(&p->s, MOTION(SM130_PROLOGUE_RESISTANCE, 0));
      (p->s).mode[1]++;
      FALLTHROUGH;
    }
    case 1: {
      u8 t;
      u8 r;
      UpdateMotionGraphic(&p->s);
      t = ((p->s).scriptEntity)->flags;
      r = 1;
      r &= t;
      asm volatile("" ::"r"(t));
      if (r == 0) {
        break;
      }
      SET_XFLIP(p, 0);
      (p->s).work[2] = 8;
      goto inc;
    }
    case 2:
      UpdateMotionGraphic(&p->s);
      if ((u8)--(p->s).work[2] != 0) {
        break;
      }
      SetMotion(&p->s, MOTION(0x82, 0x02));
      goto inc;
    case 3: {
      s32 x;
      UpdateMotionGraphic(&p->s);
      x = (p->s).coord.x - 0x80;
      (p->s).coord.x = x;
      {
        struct Camera* cam = &gStageRun.vm.camera;
        if (x >= cam->viewport.x - 0x8800) {
          break;
        }
      }
      {
        register u8 t asm("r0");
        u8 fv;
        t = (p->s).flags;
        fv = 0xFE;
        fv &= t;
        asm volatile("" ::"r"(t));
        (p->s).flags = fv;
      }
    inc:
      (p->s).mode[1]++;
      break;
    }
    case 4:
      break;
  }
}

extern const struct Rect Rect_08370c60;

void initActor23(struct Solid* p) {
  (p->s).flags2 |= 8;
  (p->s).size = &Rect_08370c60;
  (p->s).hazardAttr = 0x2001;
  (p->s).d.x = 0;
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  Actor_Update(p);
}

// 0x080D31B0
void Actor23_Update(struct Solid* p) {
  if ((p->s).scriptEntity->flags & 1) {
    if (CalcFromCamera(&gStageRun.vm.camera, &(p->s).coord) <= 0xFFF) {
      (p->s).d.x += 4;
      if ((p->s).d.x > 0x700) {
        (p->s).d.x = 0x700;
      }
      (p->s).coord.x += (p->s).d.x;
      (p->s).coord.y -= (p->s).d.x;
    }
  }
}

void Actor24_Update(struct Solid* p) {
  if ((p->s).mode[1] == 0) {
    struct Coord* c = (struct Coord*)(p->s).unk_28;
    LOAD_STATIC_GRAPHIC(SM211_MENU_CURSOR_BORDER);
    SetMotion(&p->s, MOTION(SM211_MENU_CURSOR_BORDER, 0x01));
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
    (p->s).mode[1]++;
  }
  UpdateMotionGraphic(&p->s);
}

INCASM("asm/solid/actor_p1_p2_a2.inc");

struct VFX* FUN_080c5628(u8 r0, u8 r1, s32 x, s32 y);

// 0x080D3594 -- Dark Elf fly-by: borrow the SM081 graphic slot, ride a sine
// path across the screen, then restore the slot and stop.
// Blocker (store-operand order): the two restore stores emit the value load
// before the +0xA2 address form, where retail emits the address first; the
// instruction stream is otherwise byte-identical (only those two halfword
// pairs differ). Pointer temps and barriers fix the order but let CSE reuse
// case 0's address and drop three instructions; volatile reads do not move it.
NON_MATCH void Actor26_Update(struct Solid* p) {
#if MODERN
  s32 m = (p->s).mode[1];
  if (m == 1) {
    goto phase1;
  }
  if (m > 1) {
    return;
  }
  if (m != 0) {
    return;
  }
  {
    {
      u8 z;
      (p->s).unk_coord.x = wStaticGraphicTilenums[0x51];
      (p->s).unk_coord.y = wStaticMotionPalIDs[0x51];
      (p->s).d.x = (p->s).coord.x;
      (p->s).d.y = (p->s).coord.y;
      z = 0;
      wStaticGraphicTilenums[0x51] = 0x305;
      wStaticMotionPalIDs[0x51] = 8;
      LOAD_STATIC_GRAPHIC(SM081_DARK_ELF);
      SetMotion(&p->s, MOTION(SM081_DARK_ELF, 0));
      (p->s).work[2] = z;
      (p->s).mode[1]++;
    }
  phase1: {
      u32 w;
      s32 x;
      UpdateMotionGraphic(&p->s);
      if ((0xF & (p->s).work[2]) == 0) {
        FUN_080c5628(3, 0, (p->s).coord.x, (p->s).coord.y);
      }
      w = (p->s).work[2] + 1;
      (p->s).work[2] = w;
      x = (p->s).d.x + 0x200;
      (p->s).d.x = x;
      x += gSineTable[((w << 25) + 0x40000000) >> 24] << 1;
      (p->s).coord.x = x;
      (p->s).coord.y = (p->s).d.y + (gSineTable[(w << 26) >> 24] << 2);
      {
        struct Camera* cam = &gStageRun.vm.camera;
        if (x >= cam->viewport.x + 0x97FF) {
        (p->s).flags &= ~DISPLAY;
        wStaticGraphicTilenums[0x51] = (p->s).unk_coord.x;
        wStaticMotionPalIDs[0x51] = (p->s).unk_coord.y;
        (p->s).mode[1]++;
        }
      }
    }
  }
#else
  INCCODE("asm/solid/actor_26_update.inc");
#endif
}

// 0x080D36B8
void Actor27_Update(struct Solid* p) {
  switch ((p->s).mode[1]) {
    case 0: {
      register u16* g asm("r2");
      register u16* pl asm("r1");
      register s32 ix asm("r3");
      (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y);
      g = wDynamicGraphicTilenums;
      ix = 0xA4 * 2;
      asm volatile("add %0, %0, %1" : "+l"(g) : "l"(ix));
      (p->s).unk_coord.x = *g;
      pl = wDynamicMotionPalIDs;
      asm volatile("add %0, %0, %1" : "+l"(pl) : "l"(ix));
      (p->s).unk_coord.y = *pl;
      {
        register s32 t305 asm("r0");
        t305 = 0x305;
        *g = t305;
      }
      *pl = 9;
      SetMotion(&p->s, MOTION(0xA4, 0x00));
      (p->s).mode[1]++;
      FALLTHROUGH;
    }
    case 1:
      if (((p->s).scriptEntity->flags & 1) == 0) {
        goto upd;
      }
      goto setm;
    case 2:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 3) {
        goto tramp;
      }
      break;
    tramp:
      asm volatile("");
      goto inc;
    case 3:
      SetMotion(&p->s, MOTION(0xA4, 0x00));
      SET_XFLIP(&p->s, 0);
      (p->s).mode[1]++;
      FALLTHROUGH;
    case 4:
      if (((p->s).scriptEntity->flags & 1) != 0) {
        goto upd;
      }
    setm:
      SetMotion(&p->s, MOTION(0xA4, 0x08));
      (p->s).mode[1]++;
    upd:
      UpdateMotionGraphic(&p->s);
      break;
    case 5:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state != 3) {
        break;
      }
      goto inc;
    case 6:
      SetMotion(&p->s, MOTION(0xA4, 0x00));
      SET_XFLIP(&p->s, 1);
      (p->s).work[2] = 0x10;
      (p->s).mode[1]++;
      FALLTHROUGH;
    case 7:
      UpdateMotionGraphic(&p->s);
      (p->s).work[2]--;
      if ((p->s).work[2] != 0) {
        break;
      }
      SetMotion(&p->s, MOTION(0xA4, 0x05));
      (p->s).d.y = -0x500;
      (p->s).d.x = (p->s).coord.y;
      goto inc;
    case 8: {
      s32 vy;
      (p->s).coord.x += 0xB8 * 2;
      (p->s).coord.y += (p->s).d.y;
      vy = (p->s).d.y + 0x40;
      (p->s).d.y = vy;
      if (vy > 0) {
        if (MOTION_VALUE(p) != MOTION(0xA4, 0x06)) {
          SetMotion(&p->s, MOTION(0xA4, 0x06));
        }
      }
      UpdateMotionGraphic(&p->s);
      {
      register s32 kk asm("r1");
      kk = 0xD0 * 64;
      if ((p->s).d.x + kk < (p->s).coord.y) {
        register u16* g2 asm("r0");
        register s32 ix2 asm("r2");
        g2 = wDynamicGraphicTilenums;
        ix2 = 0xA4 * 2;
        asm volatile("add %0, %0, %1" : "+l"(g2) : "l"(ix2));
        *g2 = (p->s).unk_coord.x;
        g2 = wDynamicMotionPalIDs;
        asm volatile("add %0, %0, %1" : "+l"(g2) : "l"(ix2));
        *g2 = (p->s).unk_coord.y;
        (p->s).flags &= ~DISPLAY;
        goto inc;
      }
      }
      break;
    }
    case 9:
      break;
  }
  return;
inc:
  (p->s).mode[1]++;
}


// 0x080d38a4
void initActor28(struct Solid* p) {
  gWindowRegBuffer.dispcnt |= 0x4000;
  gWindowRegBuffer.winin[1] = 0;
  gWindowRegBuffer.winin[2] |= 0xFE;
  (p->s).work[2] = 0;
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  Actor_Update(p);
}

void Actor28_Update(struct Solid* p) {
  switch ((p->s).mode[1]) {
    case 0:
      (p->s).coord.x = 0;
      (p->s).coord.y = 0x9300;
      PlaySound(0x12E);
      (p->s).work[3] = 0;
      (p->s).mode[1]++;
      /* fallthrough */
    case 1: {
      const s16* tbl = gSineTable;
      u8 w = (p->s).work[3];
      s32 t;
      (p->s).coord.x = tbl[(u8)(w * 4)] * 48;
      t = w + 1;
      (p->s).work[3] = t;
      if ((u8)t > 0xF) {
        (p->s).mode[1]++;
        (p->s).work[3] = 0x20;
      }
      break;
    }
    case 2: {
      s32 t = (p->s).work[3] - 1;
      (p->s).work[3] = t;
      if ((t << 24) != 0) {
        break;
      }
      (p->s).work[3] = 0x20;
      (p->s).mode[1]++;
    }
      /* fallthrough */
    case 3: {
      const s16* tbl = gSineTable;
      u8 w = (p->s).work[3];
      s32 t;
      (p->s).coord.x = tbl[(u8)(w * 2)] * 48;
      t = w - 1;
      (p->s).work[3] = t;
      if ((t << 24) == 0) {
        gWindowRegBuffer.dispcnt &= 0xBFFF;
        (p->s).mode[1]++;
      }
      break;
    }
    case 4:
      break;
  }
  {
    struct WramWindowRegister* wr;
    s32 t12 = (p->s).work[2] + 1;
    s32 odd;
    s32 x;
    s32 y;
    (p->s).work[2] = t12;
    wr = &gWindowRegBuffer;
    x = (p->s).coord.x >> 8;
    odd = t12 & 1;
    x += odd << 3;
    wr->winH.half[1] = ((x + 0xBC) & 0xFF) | ((0xBC - x) << 8);
    y = (p->s).coord.y >> 8;
    y += odd << 2;
    wr->winV.half[1] = y & 0xFF;
    PALETTE16(0) = 0x7FFF;
  }
}

// 0x080D39FC
void Actor29_Update(struct Solid* p) {
  struct Coord c;
  s32 z = (p->s).mode[1];
  switch (z) {
    case 0: {
      register s32 zero asm("r5");
      (p->s).coord.y = FUN_08009f6c((p->s).coord.x + -0xF000, (p->s).coord.y) + 1;
      {
        register u16* gt asm("r0");
        register s32 v asm("r1");
        const struct Graphic* g;
        const struct Palette* pal;
        u32 ofs;
        gt = wStaticGraphicTilenums;
        zero = 0;
        v = 0x3CE;
        gt[SM001_UNK] = v;
        wStaticMotionPalIDs[SM001_UNK] = 9;
        ofs = (sizeof(struct ColorGraphic) * SM001_UNK);
        g = gStaticGraphic(ofs);
        LoadGraphic((void*)g, (void*)((v - g->ofs) * 32 + 0x10000));
        pal = gStaticPalette(ofs);
        LoadPalette(pal, (wStaticMotionPalIDs[SM001_UNK] - pal->dst) * 32 + PLTT_SIZE / 2);
      }
      SetMotion(&p->s, MOTION(0x01, 0x00));
      AppendQuake(8, &(p->s).coord);
      (p->s).work[2] = zero;
      (p->s).d.y = z;
      (p->s).mode[1]++;
      FALLTHROUGH;
    }
    case 1: {
      struct Coord* cp;
      s32 t;
      UpdateMotionGraphic(&p->s);
      (p->s).d.y += 0x10;
      (p->s).coord.y += (p->s).d.y;
      cp = &(p->s).coord;
      AppendQuake(2, cp);
      t = (p->s).work[2] + 1;
      (p->s).work[2] = t;
      if ((t & 3) != 0) {
        register u32 rnd asm("r1");
        register u32 acc asm("r0");
        u32 rv;
        c.x = (p->s).coord.x + -0x4000;
        rnd = RNG_0202f388;
        acc = 0x343FD;
        acc *= rnd;
        acc += 0x269EC3;
        rv = acc << 1;
        asm("" : "+r"(rv));
        RNG_0202f388 = rv >> 1;
        c.y = (p->s).coord.y + ((rv << 3) >> 0x14);
        CreateSmoke(3, &c);
      }
      if (CalcFromCamera(&gStageRun.vm.camera, cp) > 0x800) {
        (p->s).flags &= ~DISPLAY;
        (p->s).mode[1]++;
      }
      break;
    }
    case 2:
      AppendQuake(2, &(p->s).coord);
      break;
  }
}


NAKED void Actor30_Update(struct Solid* p) {
  asm(".syntax unified\
\n	push {r4, r5, r6, r7, lr}\
\n	mov r7, sl\
\n	mov r6, sb\
\n	mov r5, r8\
\n	push {r5, r6, r7}\
\n	sub sp, #8\
\n	adds r7, r0, #0\
\n	ldrb r0, [r7, #0xd]\
\n	cmp r0, #1\
\n	beq _080D3C16\
\n	cmp r0, #1\
\n	bgt _080D3B56\
\n	cmp r0, #0\
\n	beq _080D3B64\
\n	b _080D3D10\
\n_080D3B56:\
\n	cmp r0, #2\
\n	bne _080D3B5C\
\n	b _080D3C8C\
\n_080D3B5C:\
\n	cmp r0, #3\
\n	bne _080D3B62\
\n	b _080D3D08\
\n_080D3B62:\
\n	b _080D3D10\
\n_080D3B64:\
\n	ldr r0, [r7, #0x54]\
\n	ldr r1, _080D3CD4 @ =0xFFFF6000\
\n	adds r0, r0, r1\
\n	ldr r1, [r7, #0x58]\
\n	bl FUN_08009f6c\
\n	ldr r2, _080D3CD8 @ =0x00000101\
\n	adds r0, r0, r2\
\n	str r0, [r7, #0x58]\
\n	ldr r1, _080D3CDC @ =wStaticGraphicTilenums\
\n	ldr r0, _080D3CE0 @ =0x000003CE\
\n	strh r0, [r1, #2]\
\n	ldr r6, _080D3CE4 @ =wStaticMotionPalIDs\
\n	movs r0, #9\
\n	strh r0, [r6, #2]\
\n	movs r4, #0xb9\
\n	lsls r0, r4, #1\
\n	mov r8, r0\
\n	adds r2, r1, #0\
\n	add r2, r8\
\n	mov sl, r2\
\n	ldr r0, _080D3CE8 @ =0x000003AF\
\n	strh r0, [r2]\
\n	add r8, r6\
\n	movs r0, #0xa\
\n	mov r2, r8\
\n	strh r0, [r2]\
\n	ldr r5, _080D3CEC @ =gStaticMotionGraphics\
\n	adds r0, r5, #0\
\n	adds r0, #0x14\
\n	ldrh r1, [r1, #2]\
\n	ldrh r2, [r0, #6]\
\n	lsrs r2, r2, #6\
\n	subs r1, r1, r2\
\n	lsls r1, r1, #5\
\n	movs r2, #0x80\
\n	lsls r2, r2, #9\
\n	adds r1, r1, r2\
\n	bl LoadGraphic\
\n	ldr r0, _080D3CF0 @ =gStaticMotionGraphics+12\
\n	mov sb, r0\
\n	adds r0, #0x14\
\n	ldrh r1, [r6, #2]\
\n	ldrb r2, [r0, #7]\
\n	subs r1, r1, r2\
\n	lsls r1, r1, #5\
\n	movs r6, #0x80\
\n	lsls r6, r6, #2\
\n	adds r1, r1, r6\
\n	bl LoadPalette\
\n	lsls r4, r4, #4\
\n	movs r1, #0xb9\
\n	lsls r1, r1, #2\
\n	adds r4, r4, r1\
\n	adds r5, r4, r5\
\n	mov r2, sl\
\n	ldrh r1, [r2]\
\n	ldrh r0, [r5, #6]\
\n	lsrs r0, r0, #6\
\n	subs r1, r1, r0\
\n	lsls r1, r1, #5\
\n	movs r0, #0x80\
\n	lsls r0, r0, #9\
\n	adds r1, r1, r0\
\n	adds r0, r5, #0\
\n	bl LoadGraphic\
\n	add r4, sb\
\n	mov r2, r8\
\n	ldrh r1, [r2]\
\n	ldrb r0, [r4, #7]\
\n	subs r1, r1, r0\
\n	lsls r1, r1, #5\
\n	adds r1, r1, r6\
\n	adds r0, r4, #0\
\n	bl LoadPalette\
\n	movs r1, #0x80\
\n	lsls r1, r1, #1\
\n	adds r0, r7, #0\
\n	bl SetMotion\
\n	movs r0, #0\
\n	strb r0, [r7, #0x12]\
\n	ldrb r0, [r7, #0xd]\
\n	adds r0, #1\
\n	strb r0, [r7, #0xd]\
\n_080D3C16:\
\n	adds r0, r7, #0\
\n	bl UpdateMotionGraphic\
\n	ldr r0, [r7, #0x18]\
\n	ldrb r1, [r0, #9]\
\n	movs r0, #1\
\n	ands r0, r1\
\n	cmp r0, #0\
\n	beq _080D3D10\
\n	adds r1, r7, #0\
\n	adds r1, #0x54\
\n	movs r0, #0x10\
\n	bl AppendQuake\
\n	ldr r5, _080D3CF4 @ =RNG_0202f388\
\n	mov r6, sp\
\n	movs r4, #3\
\n_080D3C38:\
\n	ldr r0, [r7, #0x54]\
\n	ldr r1, _080D3CF8 @ =0xFFFFC000\
\n	adds r0, r0, r1\
\n	str r0, [sp]\
\n	ldr r1, [r5]\
\n	ldr r0, _080D3CFC @ =0x000343FD\
\n	muls r1, r0, r1\
\n	ldr r2, _080D3D00 @ =0x00269EC3\
\n	adds r1, r1, r2\
\n	lsls r1, r1, #1\
\n	lsrs r0, r1, #1\
\n	str r0, [r5]\
\n	lsls r1, r1, #3\
\n	lsrs r1, r1, #0x14\
\n	ldr r0, [r7, #0x58]\
\n	adds r0, r0, r1\
\n	str r0, [r6, #4]\
\n	movs r0, #3\
\n	mov r1, sp\
\n	bl CreateSmoke\
\n	subs r4, #1\
\n	cmp r4, #0\
\n	bge _080D3C38\
\n	ldr r0, _080D3D04 @ =pZero2\
\n	ldr r0, [r0]\
\n	ldr r0, [r0, #0x58]\
\n	str r0, [r7, #0x64]\
\n	adds r0, r7, #0\
\n	bl InitRotatableMotion\
\n	movs r1, #0x80\
\n	lsls r1, r1, #1\
\n	adds r0, r7, #0\
\n	bl SetMotion\
\n	movs r0, #0\
\n	str r0, [r7, #0x60]\
\n	str r0, [r7, #0x68]\
\n	ldrb r0, [r7, #0xd]\
\n	adds r0, #1\
\n	strb r0, [r7, #0xd]\
\n_080D3C8C:\
\n	adds r0, r7, #0\
\n	bl UpdateMotionGraphic\
\n	ldr r1, [r7, #0x60]\
\n	adds r1, #1\
\n	str r1, [r7, #0x60]\
\n	ldr r0, [r7, #0x68]\
\n	adds r0, r0, r1\
\n	str r0, [r7, #0x68]\
\n	asrs r0, r0, #0xb\
\n	adds r1, r7, #0\
\n	adds r1, #0x24\
\n	strb r0, [r1]\
\n	ldr r1, [r7, #0x60]\
\n	asrs r2, r1, #2\
\n	ldr r0, [r7, #0x58]\
\n	subs r0, r0, r2\
\n	str r0, [r7, #0x58]\
\n	asrs r1, r1, #1\
\n	ldr r0, [r7, #0x64]\
\n	subs r0, r0, r1\
\n	str r0, [r7, #0x64]\
\n	ldr r1, _080D3D04 @ =pZero2\
\n	ldr r1, [r1]\
\n	str r0, [r1, #0x58]\
\n	ldr r0, [r7, #0x18]\
\n	ldrb r1, [r0, #9]\
\n	movs r0, #2\
\n	ands r0, r1\
\n	cmp r0, #0\
\n	beq _080D3D10\
\n	ldrb r0, [r7, #0xd]\
\n	adds r0, #1\
\n	strb r0, [r7, #0xd]\
\n	b _080D3D10\
\n	.align 2, 0\
\n_080D3CD4: .4byte 0xFFFF6000\
\n_080D3CD8: .4byte 0x00000101\
\n_080D3CDC: .4byte wStaticGraphicTilenums\
\n_080D3CE0: .4byte 0x000003CE\
\n_080D3CE4: .4byte wStaticMotionPalIDs\
\n_080D3CE8: .4byte 0x000003AF\
\n_080D3CEC: .4byte gStaticMotionGraphics\
\n_080D3CF0: .4byte gStaticMotionGraphics+12\
\n_080D3CF4: .4byte RNG_0202f388\
\n_080D3CF8: .4byte 0xFFFFC000\
\n_080D3CFC: .4byte 0x000343FD\
\n_080D3D00: .4byte 0x00269EC3\
\n_080D3D04: .4byte pZero2\
\n_080D3D08:\
\n	ldr r0, _080D3D4C @ =pZero2\
\n	ldr r1, [r0]\
\n	ldr r0, [r7, #0x64]\
\n	str r0, [r1, #0x58]\
\n_080D3D10:\
\n	ldrb r0, [r7, #0xd]\
\n	cmp r0, #2\
\n	bhi _080D3D3A\
\n	ldrb r0, [r7, #0x12]\
\n	adds r0, #1\
\n	strb r0, [r7, #0x12]\
\n	movs r1, #1\
\n	ands r0, r1\
\n	cmp r0, #0\
\n	bne _080D3D30\
\n	movs r0, #4\
\n	movs r1, #0\
\n	movs r2, #0\
\n	movs r3, #0\
\n	bl FUN_080c5628\
\n_080D3D30:\
\n	adds r1, r7, #0\
\n	adds r1, #0x54\
\n	movs r0, #2\
\n	bl AppendQuake\
\n_080D3D3A:\
\n	add sp, #8\
\n	pop {r3, r4, r5}\
\n	mov r8, r3\
\n	mov sb, r4\
\n	mov sl, r5\
\n	pop {r4, r5, r6, r7}\
\n	pop {r0}\
\n	bx r0\
\n	.align 2, 0\
\n_080D3D4C: .4byte pZero2\
\n .syntax divided\
");
}

struct Entity* CreateVFX39(struct Coord* c, u8 r1, u8 r2);

void Actor31_Update(struct Solid* p) {
  s32 md = (p->s).mode[1];
  if (md == 1) {
    goto c1;
  }
  if (md > 1) {
    return;
  }
  if (md != 0) {
    return;
  }
  {
      struct Entity* v;
      (p->s).flags &= ~DISPLAY;
      v = CreateVFX39(&(p->s).coord, 1, 0);
      (p->s).unk_28 = v;
      *((u8*)v + 0x7c) = md;
      *((u8*)(p->s).unk_28 + 0x74) = 0x1F;
      *((u8*)(p->s).unk_28 + 0x75) = 0x1F;
      *((u8*)(p->s).unk_28 + 0x76) = 0x1F;
      (p->s).work[2] = md;
      (p->s).mode[1]++;
  }
c1:
  {
    struct Entity* q;
    s16 sv;
    (p->s).work[2]++;
    q = (p->s).unk_28;
    sv = gSineTable[((p->s).work[2] & 0xFE) >> 1];
    *(s32*)((u8*)q + 0x78) = sv * 3 << 7;
    asm volatile("" ::: "memory");
    *(s32*)((u8*)(p->s).unk_28 + 0x78) += ((p->s).work[2] & 1) << 12;
    asm volatile("" ::: "memory");
    if ((p->s).work[2] == 0x81) {
      register u8* q3 asm("r0");
      q3 = (u8*)(p->s).unk_28;
      q3[0x77] = 1;
      (p->s).mode[1]++;
    }
  }
}

// 0x080d3de4
void initActor32(struct Solid* p) {
  gWindowRegBuffer.dispcnt |= 0x4000;
  gWindowRegBuffer.winin[1] = 4;
  gWindowRegBuffer.winin[2] |= 0xFE;
  (p->s).work[2] = 0;
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  Actor_Update(p);
}

void Actor32_Update(struct Solid* p) {
  register struct WramWindowRegister* wr asm("r5");
  u8 md = (p->s).mode[1];
  wr = &gWindowRegBuffer;
  switch (md) {
    case 0:
      (p->s).coord.x = 0x400;
      (p->s).coord.y = 0x9200;
      (p->s).work[3] = 0;
      (p->s).mode[1]++;
      /* fallthrough */
    case 1: {
      s32 t;
      (p->s).coord.y += -0x800;
      t = (p->s).work[3] + 1;
      (p->s).work[3] = t;
      {
        u8 t8 = t;
        asm("" : "+r"(wr));
        wr = &gWindowRegBuffer;
        if (t8 <= 0x3F) {
          break;
        }
      }
      (p->s).work[3] = 0;
      (p->s).mode[1]++;
    }
      /* fallthrough */
    case 2: {
      const s16* tbl = gSineTable;
      s32 t;
      (p->s).coord.x = tbl[(p->s).work[3]] * 0xB8;
      t = (p->s).work[3] + 1;
      (p->s).work[3] = t;
      {
        u8 t8 = t;
        asm("" : "+r"(wr));
        wr = &gWindowRegBuffer;
        if (t8 <= 0x3F) {
          break;
        }
      }
      (p->s).work[3] = 0x10;
      (p->s).mode[1]++;
    }
      /* fallthrough */
    case 3: {
      s32 t = (p->s).work[3] - 1;
      (p->s).work[3] = t;
      {
        s32 t24 = t << 24;
        asm("" : "+r"(wr));
        wr = &gWindowRegBuffer;
        if (t24 != 0) {
          break;
        }
      }
      wr->dispcnt &= 0xBFFF;
      (p->s).mode[1]++;
    }
      /* fallthrough */
    case 4:
      break;
  }
  {
    struct WramWindowRegister* w4;
    s32 t12 = (p->s).work[2] + 1;
    s32 x;
    register s32 right asm("r1");
    s32 left;
    register u32 lo asm("r0");
    s32 y;
    s32 k;
    u32 bot;
    register s32 y2 asm("r1");
    (p->s).work[2] = t12;
    x = (p->s).coord.x >> 8;
    x += (t12 & 1) << 3;
    right = x + 0xC0;
    w4 = wr;
    left = (0xC0 - x) << 8;
    right <<= 16;
    right >>= 16;
    if (right > 0xF0) {
      goto clampF;
    }
    lo = right & 0xFF;
    goto wjoin;
  clampF:
    lo = 0xF0;
  wjoin:
    lo |= left;
    w4->winH.half[1] = lo;
    y2 = (p->s).coord.y >> 8;
    k = ((p->s).work[2] & 1) << 3;
    y2 -= k;
    bot = k;
    bot += 0x93;
    bot &= 0xFF;
    y = (s16)y2;
    if (y >= 0) {
      bot |= y << 8;
    }
    wr->winV.half[1] = bot;
    PALETTE16(0) = 0x7FFF;
  }
}

INCASM("asm/solid/actor_p1_p2_b_b.inc");

// Weil-throne idle actor: one-time graphic/palette load with the tilenum and
// palid slots written first, then breathe/flicker. Logic verified; parked on
// the loader staging tie (retail keeps idx=0xB8 live in r4 and reuses its <<1
// across both slot addresses - pins either fold the constant, bump p off r6,
// or spill).
NON_MATCH void Actor34_Update(struct Solid* p) {
#if MODERN
  switch ((p->s).mode[1]) {
    case 0: {
      const struct Graphic* g;
      u32 ofs;
      (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y) - 0x1800;
      wStaticGraphicTilenums[0xB8] = 0x385;
      wStaticMotionPalIDs[0xB8] = 5;
      ofs = sizeof(struct ColorGraphic) * 0xB8;
      g = gStaticGraphic(ofs);
      LoadGraphic((void*)g, (void*)((wStaticGraphicTilenums[0xB8] - g->ofs) * 32 + 0x10000));
      pal = gStaticPalette(ofs);
      LoadPalette(pal, (wStaticMotionPalIDs[0xB8] - pal->dst) * 32 + PLTT_SIZE / 2);
      SetMotion(&p->s, MOTION(0xB8, 0x02));
      (p->s).mode[1]++;
    }
      /* fallthrough */
    case 1:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 3) {
        SetMotion(&p->s, MOTION(0xB8, 0x02));
      }
      if ((RANDOM(RNG_0202f388) & 0x1F) == 0) {
        SetMotion(&p->s, MOTION(0xB8, 0x03));
      }
      if ((p->s).work[1] != 0) {
        if (RANDOM(RNG_0202f388) & 1) {
          (p->s).flags |= DISPLAY;
        } else {
          (p->s).flags &= ~DISPLAY;
        }
      }
      break;
  }
#else
  INCCODE("asm/solid/actor_34upd.inc");
#endif
}

INCASM("asm/solid/actor_p1_p2_b_b_c.inc");

void Actor36_Update(struct Solid* p) {
  switch ((p->s).mode[1]) {
    case 0: {
      s32 n;
      (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y);
      n = 0xc2;
      wStaticGraphicTilenums[n] = 0x220;
      wStaticMotionPalIDs[n] = 5;
      LOAD_STATIC_GRAPHIC(n);
      SetMotion(&p->s, MOTION(0xC2, 0x00));
      (p->s).mode[1]++;
      FALLTHROUGH;
    }
    case 1: {
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}

INCASM("asm/solid/actor_p1_p2_b_c.inc");

// 0x080D45F8
void Actor38_Update(struct Solid* p) {
  register const s16* tb asm("r5");
  switch ((p->s).mode[1]) {
    case 0: {
      register s32 z6 asm("r6");
      register u16* gt asm("r0");
      register u16* pt asm("r5");
      register u32 ofs asm("r4");
      const struct Graphic* g;
      (p->s).d.x = (p->s).coord.x;
      (p->s).d.y = (p->s).coord.y;
      (p->s).unk_coord.y = (p->s).coord.y + -0x5000;
      gt = wStaticGraphicTilenums;
      asm("" : "+r"(gt));
      gt += SM081_DARK_ELF;
      z6 = 0;
      {
        register s32 v asm("r1");
        register s32 sev asm("r0");
        v = 0xE0 * 4;
        *gt = v;
        pt = wStaticMotionPalIDs;
        asm("" : "+r"(pt));
        pt += SM081_DARK_ELF;
        sev = 7;
        *pt = sev;
        ofs = (sizeof(struct ColorGraphic) * SM081_DARK_ELF);
        g = gStaticGraphic(ofs);
        v -= g->ofs;
        v *= 32;
        asm volatile("mov r3, #0x80\n\tlsl r3, r3, #9\n\tadd %0, %0, r3" : "+l"(v) :: "r3");
        LoadGraphic((void*)g, (void*)v);
      }
      {
        register const struct Palette* pal2 asm("r4");
        register u32 pb asm("r0");
        register s32 sv asm("r1");
        register s32 dv asm("r0");
        pb = (u32)STATIC_PALETTES;
        asm("" : "+r"(pb));
        pal2 = (const struct Palette*)(ofs + pb);
        sv = *pt;
        dv = pal2->dst;
        asm volatile("sub %0, %0, %1" : "+l"(sv) : "l"(dv));
        sv *= 32;
        asm volatile("mov r2, #0x80\n\tlsl r2, r2, #2\n\tadd %0, %0, r2" : "+l"(sv) :: "r2");
        LoadPalette(pal2, sv);
      }
      {
        register u8* pp asm("r1");
        register s32 one asm("r0");
        pp = (u8*)p + 0x22;
        one = 1;
        *pp = one;
      }
      SetMotion(&p->s, 0xA2 * 128);
      (p->s).work[2] = z6;
      (p->s).work[3] = z6;
      (p->s).mode[1]++;
      FALLTHROUGH;
    }
    case 1: {
      register s32 t2 asm("r2");
      register s32 cx asm("r4");
      register s32 cy asm("r3");
      UpdateMotionGraphic(&p->s);
      {
        register s32 t asm("r0");
        t = (p->s).work[2];
        t2 = t + 1;
        (p->s).work[2] = t2;
        tb = gSineTable;
        t += 0x41;
        {
          register s32 sv asm("r0");
          register s32 dxv asm("r1");
          const s16* bp = (const s16*)(((((u32)t) << 24) >> 23) + (u32)tb);
          asm volatile("mov r3, #0\n\tldrsh %0, [%1, r3]" : "=l"(sv) : "l"(bp) : "r3");
          sv <<= 1;
          dxv = (p->s).d.x;
          cx = dxv + sv;
          (p->s).coord.x = cx;
        }
      }
      {
        register s32 sy asm("r0");
        const s16* bp2 = (const s16*)(((((u32)t2) << 25) >> 23) + (u32)tb);
        asm volatile("mov r1, #0\n\tldrsh %0, [%1, r1]" : "=l"(sy) : "l"(bp2) : "r1");
        sy <<= 2;
        {
          register s32 uy0 asm("r1");
          uy0 = (p->s).unk_coord.y;
          cy = uy0 + sy;
        }
        (p->s).coord.y = cy;
      }
      {
        register s32 k asm("r0");
        k = 0xF;
        t2 &= k;
        if (t2 == 0) {
          ((void (*)(s32, s32, s32, s32))FUN_080c5628)(3, 0, cx, cy);
        }
      }
      if (((p->s).scriptEntity->flags & 1) == 0) {
        goto slide;
      }
      {
        register s32 w asm("r1");
        register s32 dx asm("r2");
        register s32 sv2 asm("r1");
        w = (p->s).work[3] + 1;
        (p->s).work[3] = w;
        dx = (p->s).d.x;
        asm volatile("mov r3, #0x80\n\tlsl r3, r3, #1\n\tadd %0, %0, r3" : "+l"(dx) :: "r3");
        w = (((u32)w) << 24) >> 26;
        {
          register s32 q asm("r0");
          const s16* bp3;
          q = 0x40 - w;
          bp3 = (const s16*)(((((u32)q) << 24) >> 23) + (u32)tb);
          asm volatile("mov r3, #0\n\tldrsh %0, [%1, r3]" : "=l"(sv2) : "l"(bp3) : "r3");
        }
        dx -= sv2;
        (p->s).d.x = dx;
        {
          register s32 uy asm("r0");
          uy = (p->s).unk_coord.y + -0x100;
          uy += sv2;
          (p->s).unk_coord.y = uy;
        }
      }
      if (CalcFromCamera(&gStageRun.vm.camera, &(p->s).coord) > 0x80 * 64) {
        (p->s).flags &= ~DISPLAY;
        (p->s).mode[1]++;
      }
      break;
    slide : {
      register s32 u asm("r0");
      register s32 uu asm("r1");
      u = (p->s).unk_coord.y;
      uu = u << 7;
      uu -= u;
      uu += (p->s).d.y;
      uu >>= 7;
      (p->s).unk_coord.y = uu;
      break;
    }
    }
    case 2:
      break;
  }
}

INCASM("asm/solid/actor_p1_p2_b_c2.inc");

// 0x080D5444
void ActorLastFefnir_Update(struct Solid* p) {
  switch ((p->s).mode[1]) {
    case 0: {
      register s32 ix asm("r2");
      {
        register u16* g asm("r0");
        register s32 v asm("r1");
        g = wDynamicGraphicTilenums;
        ix = 0xA1 * 2;
        asm volatile("add %0, %0, %1" : "+l"(g) : "l"(ix));
        v = 0xD0 * 4;
        *g = v;
      }
      {
        register u16* g2 asm("r0");
        register s32 v2 asm("r1");
        g2 = wDynamicMotionPalIDs;
        asm volatile("add %0, %0, %1" : "+l"(g2) : "l"(ix));
        v2 = 8;
        *g2 = v2;
      }
      (p->s).mode[1]++;
      FALLTHROUGH;
    }
    case 1: {
      register u16* gt asm("r1");
      register u16* pt asm("r5");
      register u32 ofs asm("r4");
      register s32 kk asm("r2");
      const struct Graphic* g;
      if (((u16)FUN_080d0aa0(&p->s, MOTION(0xA1, 0x00), 1) << 16) == 0) {
        break;
      }
      SetMotion(&p->s, MOTION(0xA1, 0x09));
      gt = wStaticGraphicTilenums;
      asm("" : "+r"(gt));
      gt += SM033_FEFNIR_FIREBALL;
      {
        register s32 v3 asm("r0");
        v3 = 0x327;
        *gt = v3;
      }
      pt = wStaticMotionPalIDs;
      asm("" : "+r"(pt));
      pt += SM033_FEFNIR_FIREBALL;
      *pt = 7;
      ofs = (sizeof(struct ColorGraphic) * SM033_FEFNIR_FIREBALL);
      g = gStaticGraphic(ofs);
      {
        register s32 sv0 asm("r1");
        sv0 = (*gt - g->ofs) * 32;
        kk = 0x80 * 512;
        sv0 += kk;
        LoadGraphic((void*)g, (void*)sv0);
      }
      {
        register const struct Palette* pal2 asm("r4");
        register u32 pb asm("r0");
        pb = (u32)STATIC_PALETTES;
        asm("" : "+r"(pb));
        pal2 = (const struct Palette*)(ofs + pb);
        {
          register s32 sv asm("r1");
          register s32 dv asm("r0");
          sv = *pt;
          dv = pal2->dst;
          asm volatile("sub %0, %0, %1" : "+l"(sv) : "l"(dv));
          sv *= 32;
          asm volatile("mov r2, #0x80\n\tlsl r2, r2, #2\n\tadd %0, %0, r2" : "+l"(sv) :: "r2");
          LoadPalette(pal2, sv);
        }
      }
      goto inc;
    }
    case 2:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state != 4) {
        break;
      }
      goto inc;
    case 3:
    case 5:
    case 7: {
      struct Solid* q;
      UpdateMotionGraphic(&p->s);
      SetMotion(&p->s, MOTION(0xA1, 0x0B));
      q = CreateScriptActor(p, 0x2C);
      (q->s).work[1] = ((p->s).mode[1] - 3) / 2;
      PlaySound(0xF5);
      AppendQuake(2, &(p->s).coord);
      goto inc;
    }
    case 4:
    case 6:
    case 8:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state != 3) {
        break;
      }
    inc:
      (p->s).mode[1]++;
      break;
    case 9:
      SetMotion(&p->s, MOTION(0xA1, 0x00));
      (p->s).mode[1]++;
      FALLTHROUGH;
    case 10:
      UpdateMotionGraphic(&p->s);
      break;
  }
}

static const struct Collision sCollisions_08370C68[16];

void ActorLastFefnirFireball_Update(struct Solid* p) {
  struct Entity* q = (p->s).unk_28;
  s32 md = (p->s).mode[1];
  s32 z;
  switch (md) {
    case 0:
      InitScalerotMotion1(&p->s);
      ((p->s).spr).mag.x = 0x180;
      ((p->s).spr).mag.y = 0x180;
      SetMotion(&p->s, MOTION(0x21, 0x00));
      SET_XFLIP(p, 1);
      (p->s).coord.x = q->coord.x + 0x1E00;
      (p->s).coord.y = q->coord.y - 0x1E00;
      (p->s).work[2] = md;
      (p->s).mode[1]++;
      /* fallthrough */
    case 1: {
      s32 t;
      UpdateMotionGraphic(&p->s);
      (p->s).coord.x += 0x400;
      t = (p->s).work[2] + 1;
      z = 0;
      (p->s).work[2] = t;
      if ((u8)t == 0x10) {
        struct Body* body;
        (p->s).flags |= COLLIDABLE;
        body = &p->body;
        InitBody(body, &sCollisions_08370C68[8 + (p->s).work[1]], &(p->s).coord, 1);
        body->parent = (struct CollidableEntity*)p;
        body->fn = (void*)z;
      }
      if ((p->body).status & 4) {
        u8 f = (p->s).flags & ~DISPLAY;
        f &= ~FLIPABLE;
        (p->s).flags = f;
        (p->body).status = z;
        (p->body).prevStatus = z;
        (p->body).invincibleTime = z;
        (p->s).flags &= ~COLLIDABLE;
        SET_SOLID_ROUTINE(p, ENTITY_DISAPPEAR);
      }
      break;
    }
  }
}

INCASM("asm/solid/actor_p1_p2_b_d.inc");

// 0x080D59D4
void ActorLastX_Update(struct Solid* p) {
  u8 m = (p->s).mode[1];
  switch (m) {
    case 0: {
      s16 j;
      s32 k;
      u32 n = SM253_UNK;
      wStaticGraphicTilenums[n] = 0x2B7;
      wStaticMotionPalIDs[n] = 0xA;
      LOAD_STATIC_GRAPHIC(n);
      (p->s).taskCol = 0x12;
      SetMotion(&p->s, MOTION(SM253_UNK, 0));
      (p->s).d.y = m;
      (p->s).unk_coord.y = 0x10;
      j = 0;
      k = 0x10;
      asm("" : "+r"(k));
      do {
        (p->s).d.y += k;
        (p->s).coord.y -= (p->s).d.y;
        j++;
      } while (j <= 0x5F);
      (p->s).mode[1]++;
      FALLTHROUGH;
    }
    case 1: {
      s32 y;
      s32 dy;
      UpdateMotionGraphic(&p->s);
      y = (p->s).coord.y + (p->s).d.y;
      (p->s).coord.y = y;
      dy = (p->s).d.y - (p->s).unk_coord.y;
      (p->s).d.y = dy;
      if (dy != 0) {
        break;
      }
      (p->s).unk_coord.x = (p->s).coord.x;
      (p->s).unk_coord.y = y;
      (p->s).work[3] = dy;
      (p->s).mode[1]++;
      break;
    }
    case 2: {
      u32 w3;
      u32 nw;
      UpdateMotionGraphic(&p->s);
      w3 = (p->s).work[3];
      nw = w3 + 1;
      (p->s).work[3] = nw;
      (p->s).coord.x = (p->s).unk_coord.x + (gSineTable[(u8)(w3 + 0x81)] << 1);
      (p->s).coord.y = (p->s).unk_coord.y + (gSineTable[(nw << 25) >> 24] << 2);
      break;
    }
  }
}

// 0x080D5AF4
void Actor47_Update(struct Solid* p) {
  switch ((p->s).mode[1]) {
    case 0: {
      register s32 ix asm("r2");
      {
        register u16* g asm("r0");
        register s32 v asm("r1");
        g = wDynamicGraphicTilenums;
        asm volatile("" : "+r"(g));
        ix = 0xC5 * 2;
        asm volatile("add %0, %0, %1" : "+l"(g) : "l"(ix));
        v = 0xB6 * 2;
        *g = v;
      }
      {
        register u16* g2 asm("r0");
        register s32 v2 asm("r1");
        g2 = wDynamicMotionPalIDs;
        asm volatile("add %0, %0, %1" : "+l"(g2) : "l"(ix));
        v2 = 6;
        *g2 = v2;
      }
      SetMotion(&p->s, MOTION(0xC5, 0x01));
      (p->s).mode[1]++;
      FALLTHROUGH;
    }
    case 1: {
      register u8* st asm("r5");
      register s32 one asm("r6");
      UpdateMotionGraphic(&p->s);
      {
        register u8 ms asm("r0");
        ms = (p->s).motion.state;
        st = (u8*)p + 0x70;
        asm volatile("" : "+r"(st));
        if (ms != 3) {
          goto after;
        }
      }
      {
        register s32 mv asm("r0");
        register u8 sv asm("r1");
        register s32 k asm("r1");
        mv = (p->s).motionID;
        mv <<= 8;
        sv = *st;
        mv |= sv;
        k = 0xC502;
        asm volatile("" : "+r"(k));
        if (mv == k) {
          ((void (*)(struct Entity*, s32))SetMotion)(&p->s, k + 1);
        } else {
          SetMotion(&p->s, 0xC501);
        }
      }
    after:
      {
        register u8 sf asm("r1");
        register s32 t asm("r0");
        sf = (p->s).scriptEntity->flags;
        one = 1;
        asm volatile("add %0, %1, #0" : "=&l"(t) : "l"(one));
        t &= sf;
        if (t == 0) {
          goto last;
        }
      }
      {
        register s32 mv2 asm("r0");
        register u8 sv2 asm("r1");
        register s32 k2 asm("r1");
        mv2 = (p->s).motionID;
        mv2 <<= 8;
        sv2 = *st;
        mv2 |= sv2;
        k2 = 0xC501;
        asm volatile("" : "+r"(k2));
        if (mv2 == k2) {
          ((void (*)(struct Entity*, s32))SetMotion)(&p->s, k2 + 1);
        }
        {
          register u8 sf2 asm("r1");
          register s32 t2 asm("r0");
          sf2 = (p->s).scriptEntity->flags;
          asm volatile("add %0, %1, #0" : "=&l"(t2) : "l"(one));
          t2 &= sf2;
          if (t2 != 0) {
            goto tail;
          }
        }
      }
    last : {
        register s32 mv3 asm("r0");
        register u8 sv3 asm("r1");
        register s32 k3 asm("r1");
        mv3 = (p->s).motionID;
        mv3 <<= 8;
        sv3 = *st;
        mv3 |= sv3;
        k3 = 0xC503;
        asm volatile("" : "+r"(k3));
        if (mv3 == k3) {
          ((void (*)(struct Entity*, s32))SetMotion)(&p->s, k3 + 1);
        }
      }
    tail : {
        register u8 sf3 asm("r1");
        register s32 t3 asm("r0");
        sf3 = (p->s).scriptEntity->flags;
        t3 = 2;
        t3 &= sf3;
        if (t3 == 0) {
          break;
        }
      }
      {
        register s32 mv4 asm("r1");
        register u8 id4 asm("r0");
        register s32 k4 asm("r0");
        id4 = (p->s).motionID;
        mv4 = id4 << 8;
        id4 = *st;
        mv4 |= id4;
        k4 = 0xC501;
        asm volatile("" : "+r"(k4));
        if (mv4 != k4) {
          k4 += 2;
          if (mv4 != k4) {
            break;
          }
        }
        (p->s).mode[1]++;
      }
      break;
    }
    case 2:
      if (((u16)FUN_080d0934(&p->s, MOTION_VALUE(p), 1) << 16) != 0) {
        (p->s).mode[1]++;
      }
      break;
  }
}


void Actor48_Update(struct Solid* p) {
  switch ((p->s).mode[1]) {
    case 0:
      wDynamicGraphicTilenums[0xb3] = 0x200;
      wDynamicMotionPalIDs[0xb3] = 4;
      SetMotion(&p->s, 0xb31d);
      (p->s).mode[1]++;
      // fallthrough
    case 1:
      UpdateMotionGraphic(&p->s);
      break;
  }
}

// 0x080D5C5C
void FUN_080d5c5c(struct Solid* p) {
  switch ((p->s).mode[1]) {
    case 0:
      wDynamicGraphicTilenums[0xbe] = 0x280;
      wDynamicMotionPalIDs[0xbe] = 5;
      SetMotion(&p->s, MOTION(0xbe, 0x00));
      (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y);
      (p->s).mode[1]++;
      FALLTHROUGH;
    case 1:
      UpdateMotionGraphic(&p->s);
      if (((p->s).scriptEntity->flags & 1) != 0) {
        SetMotion(&p->s, MOTION(0xbe, 0x20));
        (p->s).mode[1]++;
      }
      break;
    case 2:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 3) {
        (p->s).mode[1]++;
      }
      break;
    case 3:
      SetMotion(&p->s, MOTION(0xbe, 0x00));
      (p->s).coord.x += 0x800;
      (p->s).mode[1]++;
      FALLTHROUGH;
    case 4:
      UpdateMotionGraphic(&p->s);
      break;
  }
}

// 0x080D5D20
void FUN_080d5d20(struct Solid* p) {
  switch ((p->s).mode[1]) {
    case 0: {
      register s32 ix asm("r2");
      {
        register u16* g asm("r0");
        register s32 v asm("r1");
        g = wDynamicGraphicTilenums;
        asm volatile("" : "+r"(g));
        ix = 0xC5 * 2;
        asm volatile("add %0, %0, %1" : "+l"(g) : "l"(ix));
        v = 0x300;
        *g = v;
      }
      {
        register u16* g2 asm("r0");
        register s32 v2 asm("r1");
        g2 = wDynamicMotionPalIDs;
        asm volatile("add %0, %0, %1" : "+l"(g2) : "l"(ix));
        v2 = 6;
        *g2 = v2;
      }
      (p->s).mode[1]++;
      FALLTHROUGH;
    }
    case 1:
      if (FUN_080d0aa0(&p->s, MOTION(0xC5, 0x01), 1) != 0) {
        (p->s).mode[1]++;
      }
      break;
    case 2: {
      register u8* st asm("r5");
      register s32 one asm("r6");
      UpdateMotionGraphic(&p->s);
      {
        register u8 ms asm("r0");
        ms = (p->s).motion.state;
        st = (u8*)p + 0x70;
        asm volatile("" : "+r"(st));
        if (ms != 3) {
          goto after;
        }
      }
      {
        register s32 mv asm("r0");
        register u8 sv asm("r1");
        register s32 k asm("r1");
        mv = (p->s).motionID;
        mv <<= 8;
        sv = *st;
        mv |= sv;
        k = 0xC502;
        asm volatile("" : "+r"(k));
        if (mv == k) {
          ((void (*)(struct Entity*, s32))SetMotion)(&p->s, k + 1);
        } else {
          SetMotion(&p->s, 0xC501);
        }
      }
    after:
      {
        register u8 sf asm("r1");
        register s32 t asm("r0");
        sf = (p->s).scriptEntity->flags;
        one = 1;
        asm volatile("add %0, %1, #0" : "=&l"(t) : "l"(one));
        t &= sf;
        if (t == 0) {
          goto last;
        }
      }
      {
        register s32 mv2 asm("r0");
        register u8 sv2 asm("r1");
        register s32 k2 asm("r1");
        mv2 = (p->s).motionID;
        mv2 <<= 8;
        sv2 = *st;
        mv2 |= sv2;
        k2 = 0xC501;
        asm volatile("" : "+r"(k2));
        if (mv2 == k2) {
          ((void (*)(struct Entity*, s32))SetMotion)(&p->s, k2 + 1);
        }
        {
          register u8 sf2 asm("r1");
          register s32 t2 asm("r0");
          sf2 = (p->s).scriptEntity->flags;
          asm volatile("add %0, %1, #0" : "=&l"(t2) : "l"(one));
          t2 &= sf2;
          if (t2 != 0) {
            break;
          }
        }
      }
    last : {
        register s32 mv3 asm("r0");
        register u8 sv3 asm("r1");
        register s32 k3 asm("r1");
        mv3 = (p->s).motionID;
        mv3 <<= 8;
        sv3 = *st;
        mv3 |= sv3;
        k3 = 0xC503;
        asm volatile("" : "+r"(k3));
        if (mv3 == k3) {
          ((void (*)(struct Entity*, s32))SetMotion)(&p->s, k3 + 1);
        }
      }
      break;
    }
  }
}

INCASM("asm/solid/actor_p2.inc");

struct VFX* FUN_080c5628(u8 r0, u8 r1, s32 x, s32 y);

// 0x080d6afc -- Dark Elf cutscene actor: loads SM081, bobs on a sine track,
// swells (mag ramp) and fades. Blocker (const-cluster placement): the dead-
// kept r6 zero must materialize between the tilenum address form and the
// 0x2BE pool load, and the sine/limit temps ride a 3-reg permutation on it;
// every anchor shape tried either hoists the zero or re-forms the address.
NON_MATCH void FUN_080d6afc(struct Solid* p) {
#if MODERN
  switch ((p->s).mode[1]) {
    case 0:
      (p->s).d.x = (p->s).coord.x;
      (p->s).d.y = (p->s).coord.y;
      wStaticGraphicTilenums[0x51] = 0x2BE;
      wStaticMotionPalIDs[0x51] = 6;
      LOAD_STATIC_GRAPHIC(SM081_DARK_ELF);
      InitScalerotMotion1(&p->s);
      SetMotion(&p->s, 0x5100);
      (p->s).work[2] = 0;
      (p->s).work[3] = 1;
      (p->s).mode[1]++;
      // fallthrough
    case 1:
      UpdateMotionGraphic(&p->s);
      {
        s32 t = (p->s).work[3] + 1;
        (p->s).work[3] = t;
        if ((t & 0xF) == 0) {
          FUN_080c5628(3, 0, (p->s).coord.x, (p->s).coord.y);
        }
      }
      {
        struct ScriptEntity* se = (p->s).scriptEntity;
        if (((u8*)se)[9] & 1) {
          (p->s).d.x += 0x60;
        }
        if (((u8*)se)[9] & 2) {
          (p->s).work[3] = 0;
          goto inc;
        }
      }
      break;
    case 2: {
      s32 t;
      UpdateMotionGraphic(&p->s);
      (p->s).d.x += 0x80;
      t = (p->s).work[3];
      (p->s).work[3] = t + 1;
      {
        u32 mt = (u16)(0x200 - ((s16)gSineTable[(u8)(t + 0x41)] >> 8));
        u32 m = mt;
        if (mt > 0x120) {
          m = 0x120;
        }
        ((p->s).spr).mag.x = m;
      }
      ((p->s).spr).mag.y = ((s32)gSineTable[(u8)((p->s).work[3] + 0x40)] + 0x100) >> 1;
      if ((p->s).work[3] > 0x50) {
        (p->s).flags &= 0xFE;
      inc:
        (p->s).mode[1]++;
      }
      break;
    }
  }
  {
    s32 t = (p->s).work[2];
    s32 t1 = t + 1;
    (p->s).work[2] = t1;
    (p->s).coord.x = (p->s).d.x + ((s32)gSineTable[(u8)(t + 0x41)] << 1);
    (p->s).coord.y = (p->s).d.y + ((s32)gSineTable[(u8)((p->s).work[2] * 2)] << 2);
  }
#else
  INCCODE("asm/solid/actor_6afc.inc");
#endif
}

INCASM("asm/solid/actor_p2_post6afc.inc");

void FUN_080d740c(struct Solid* p) {
  switch ((p->s).mode[1]) {
    case 0:
      LOAD_STATIC_GRAPHIC(0x8C);
      SetMotion(&p->s, MOTION(0x8C, 0x07));
      (p->s).unk_coord.x = (p->s).coord.x;
      {
        struct Camera* cam = &gStageRun.vm.camera;
        (p->s).coord.x = cam->viewport.x + 0x87FF;
      }
      (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y);
      (p->s).mode[1]++;
      /* fallthrough */
    case 1:
      UpdateMotionGraphic(&p->s);
      (p->s).coord.x += -0x100;
      if ((p->s).coord.x < (p->s).unk_coord.x) {
        (p->s).coord.x = (p->s).unk_coord.x;
        SetMotion(&p->s, MOTION(0x8C, 0x05));
        (p->s).mode[1]++;
      }
      break;
    case 2:
      UpdateMotionGraphic(&p->s);
      if (((p->s).scriptEntity->flags & 1) == 0) {
        break;
      }
      (p->s).mode[1]++;
      /* fallthrough */
    case 3:
      if (FUN_080d0934(&p->s, MOTION(0x8C, 0x05), 0) != 0) {
        (p->s).mode[1]++;
      }
      break;
    case 4:
      break;
  }
}

// 0x080D751C
void FUN_080d751c(struct Solid* p) {
  switch ((p->s).mode[1]) {
    case 0: {
      register s32 ix asm("r2");
      {
        register u16* g asm("r0");
        register s32 v asm("r1");
        g = wDynamicGraphicTilenums;
        asm volatile("" : "+r"(g));
        ix = 0xC5 * 2;
        asm volatile("add %0, %0, %1" : "+l"(g) : "l"(ix));
        v = 0xB0 * 4;
        *g = v;
      }
      {
        register u16* g2 asm("r0");
        register s32 v2 asm("r1");
        g2 = wDynamicMotionPalIDs;
        asm volatile("add %0, %0, %1" : "+l"(g2) : "l"(ix));
        v2 = 9;
        *g2 = v2;
      }
      SetMotion(&p->s, MOTION(0xC5, 0x01));
      (p->s).mode[1]++;
      FALLTHROUGH;
    }
    case 1: {
      register u8* st asm("r5");
      register s32 one asm("r6");
      UpdateMotionGraphic(&p->s);
      {
        register u8 ms asm("r0");
        ms = (p->s).motion.state;
        st = (u8*)p + 0x70;
        asm volatile("" : "+r"(st));
        if (ms != 3) {
          goto after;
        }
      }
      {
        register s32 mv asm("r0");
        register u8 sv asm("r1");
        register s32 k asm("r1");
        mv = (p->s).motionID;
        mv <<= 8;
        sv = *st;
        mv |= sv;
        k = 0xC502;
        asm volatile("" : "+r"(k));
        if (mv == k) {
          ((void (*)(struct Entity*, s32))SetMotion)(&p->s, k + 1);
        } else {
          SetMotion(&p->s, 0xC501);
        }
      }
    after:
      {
        register u8 sf asm("r1");
        register s32 t asm("r0");
        sf = (p->s).scriptEntity->flags;
        one = 1;
        asm volatile("add %0, %1, #0" : "=&l"(t) : "l"(one));
        t &= sf;
        if (t == 0) {
          goto last;
        }
      }
      {
        register s32 mv2 asm("r0");
        register u8 sv2 asm("r1");
        register s32 k2 asm("r1");
        mv2 = (p->s).motionID;
        mv2 <<= 8;
        sv2 = *st;
        mv2 |= sv2;
        k2 = 0xC501;
        asm volatile("" : "+r"(k2));
        if (mv2 == k2) {
          ((void (*)(struct Entity*, s32))SetMotion)(&p->s, k2 + 1);
        }
        {
          register u8 sf2 asm("r1");
          register s32 t2 asm("r0");
          sf2 = (p->s).scriptEntity->flags;
          asm volatile("add %0, %1, #0" : "=&l"(t2) : "l"(one));
          t2 &= sf2;
          if (t2 != 0) {
            goto tail;
          }
        }
      }
    last : {
        register s32 mv3 asm("r0");
        register u8 sv3 asm("r1");
        register s32 k3 asm("r1");
        mv3 = (p->s).motionID;
        mv3 <<= 8;
        sv3 = *st;
        mv3 |= sv3;
        k3 = 0xC503;
        asm volatile("" : "+r"(k3));
        if (mv3 == k3) {
          ((void (*)(struct Entity*, s32))SetMotion)(&p->s, k3 + 1);
        }
      }
    tail : {
        register u8 sf3 asm("r1");
        register s32 t3 asm("r0");
        sf3 = (p->s).scriptEntity->flags;
        t3 = 2;
        t3 &= sf3;
        if (t3 == 0) {
          break;
        }
      }
      {
        register s32 mv4 asm("r1");
        register u8 id4 asm("r0");
        register s32 k4 asm("r0");
        id4 = (p->s).motionID;
        mv4 = id4 << 8;
        id4 = *st;
        mv4 |= id4;
        k4 = 0xC501;
        asm volatile("" : "+r"(k4));
        if (mv4 != k4) {
          k4 += 2;
          if (mv4 != k4) {
            break;
          }
        }
        (p->s).mode[1]++;
      }
      break;
    }
    case 2:
      if (((u16)FUN_080d0934(&p->s, MOTION_VALUE(p), 1) << 16) != 0) {
        (p->s).mode[1]++;
      }
      break;
  }
}


// 0x080d7638
void FUN_080d7638(struct Solid* p) {
  switch ((p->s).mode[1]) {
    case 0:
      wDynamicGraphicTilenums[DM190_HARPUIA] = 0x240;
      wDynamicMotionPalIDs[DM190_HARPUIA] = 6;
      SetMotion(&p->s, MOTION(DM190_HARPUIA, 0));
      (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y);
      (p->s).mode[1]++;
      FALLTHROUGH;
    case 1:
      UpdateMotionGraphic(&p->s);
      if ((p->s).scriptEntity->flags & 1) {
        (p->s).mode[1]++;
      }
      break;
    case 2:
      if (FUN_080d0934(&p->s, MOTION(DM190_HARPUIA, 0), 1) != 0) {
        (p->s).mode[1]++;
      }
      break;
  }
}

INCASM("asm/solid/actor_p2b.inc");

// 0x080D787C
void Actor63_Update(struct Solid* p) {
  switch ((p->s).mode[1]) {
    case 0:
      LOAD_STATIC_GRAPHIC(SM194_CERVEAU);
      SetMotion(&p->s, MOTION(0xc2, 0x03));
      (p->s).coord.y = FUN_08009f6c((p->s).coord.x + 0xA000, (p->s).coord.y);
      (p->s).work[2] = 0x5A;
      (p->s).mode[1]++;
      FALLTHROUGH;
    case 1:
      UpdateMotionGraphic(&p->s);
      (p->s).coord.x += 0x80;
      if ((u8)--(p->s).work[2] == 0) {
        SetMotion(&p->s, MOTION(0xc2, 0x00));
        (p->s).mode[1]++;
      }
      break;
    case 2:
      UpdateMotionGraphic(&p->s);
      break;
  }
}

INCASM("asm/solid/actor_p2b_post.inc");

// ------------------------------------------------------------------------------------------------------------------------------------

const struct Collision Collision_08370ab8 = {
  kind : DDP,
  faction : FACTION_ALLY,
  damage : 1,
  remaining : 0,
  layer : 0x00000001,
  range : {PIXEL(0), PIXEL(8), PIXEL(32), PIXEL(16)},
};

const struct Collision Collision_08370ad0 = {
  kind : DRP,
  faction : FACTION_ENEMY,
  LAYER(0xFFFFFFFF),
  hitzone : 1,
  remaining : 1,
  range : {PIXEL(0), -PIXEL(16), PIXEL(16), PIXEL(32)},
};

// 0x08370ae8
static const struct SlashedEnemy sProloguePantheons[4] = {
    {
      m : MOTION(SM019_PANTHEON_HUNTER, 6),
      unk_02 : {0xFF, 0x11},
      c : {PIXEL(0), PIXEL(0)},
      d : {PIXEL(1) / 2, -PIXEL(5)},
      unk_coord_0c : {0x00FF, 0x01FF},
      unk_10 : {0x0000, 0x0040},
      unk_14 : {512, 512},
    },
    {
      m : MOTION(SM019_PANTHEON_HUNTER, 7),
      unk_02 : {0xFE, 0x11},
      c : {PIXEL(0), PIXEL(0)},
      d : {PIXEL(1) / 2, -PIXEL(2)},
      unk_coord_0c : {0x007F, 0x007F},
      unk_10 : {0x0000, 0x0040},
      unk_14 : {512, 512},
    },
    {
      m : MOTION(SM019_PANTHEON_HUNTER, 8),
      unk_02 : {0xFE, 0x11},
      c : {PIXEL(0), PIXEL(0)},
      d : {PIXEL(1), -PIXEL(3)},
      unk_coord_0c : {0x01FF, 0x01FF},
      unk_10 : {0x0000, 0x0040},
      unk_14 : {512, 512},
    },
    {
      m : MOTION(SM019_PANTHEON_HUNTER, 5),
      unk_02 : {0xFF, 0x04},
      c : {PIXEL(0), PIXEL(0)},
      d : {PIXEL(0), PIXEL(0)},
      unk_coord_0c : {PIXEL(0), PIXEL(0)},
      unk_10 : {0x0000, 0x0040},
      unk_14 : {2048, 512},
    },
};

// 0x08370B58
static const struct Collision sCollisions_08370B58[11] = {
    [0] = {
      kind : DDP,
      faction : FACTION_ALLY,
      damage : 1,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(32), PIXEL(32)},
    },
    [1] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(16), PIXEL(16), PIXEL(32)},
    },
    [2] = {
      kind : DDP,
      faction : FACTION_ALLY,
      damage : 1,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(32), PIXEL(120)},
    },
    [3] = {
      kind : DDP,
      faction : FACTION_ALLY,
      damage : 1,
      comboLv : 1,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(32), PIXEL(120)},
    },
    [4] = {
      kind : DDP,
      faction : FACTION_ALLY,
      damage : 1,
      comboLv : 2,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(32), PIXEL(120)},
    },
    [5] = {
      kind : DDP,
      faction : FACTION_ALLY,
      damage : 1,
      comboLv : 3,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(32), PIXEL(120)},
    },
    [6] = {
      kind : DDP,
      faction : FACTION_ALLY,
      damage : 1,
      comboLv : 4,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(32), PIXEL(120)},
    },
    [7] = {
      kind : DDP,
      faction : FACTION_ALLY,
      damage : 1,
      comboLv : 5,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(32), PIXEL(120)},
    },
    [8] = {
      kind : DDP,
      faction : FACTION_ALLY,
      damage : 1,
      comboLv : 6,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(32), PIXEL(120)},
    },
    [9] = {
      kind : DDP,
      faction : FACTION_ALLY,
      damage : 1,
      comboLv : 7,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(32), PIXEL(120)},
    },
    [10] = {
      kind : DDP,
      faction : FACTION_ALLY,
      damage : 1,
      comboLv : 8,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(32), PIXEL(120)},
    },
};

// 0x08370c60
const struct Rect Rect_08370c60 = {PIXEL(8), PIXEL(8), PIXEL(16), PIXEL(16)};

// 0x08370C68
static const struct Collision sCollisions_08370C68[16] = {
    [0] = {
      kind : DRP,
      faction : FACTION_ALLY,
      special : HALFABLE,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(16), PIXEL(16), PIXEL(32)},
    },
    [1] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 1,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), -PIXEL(128), PIXEL(120)},
    },
    [2] = {
      kind : DRP,
      faction : FACTION_ALLY,
      special : HALFABLE,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(16), PIXEL(16), PIXEL(32)},
    },
    [3] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      special : HALFABLE,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(14), PIXEL(16), PIXEL(28)},
    },
    [4] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 1,
      remaining : 0,
      layer : 0x00000001,
      range : {-PIXEL(24), -PIXEL(16), PIXEL(16), PIXEL(16)},
    },
    [5] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 1,
      comboLv : 1,
      remaining : 0,
      layer : 0x00000001,
      range : {-PIXEL(24), -PIXEL(16), PIXEL(16), PIXEL(16)},
    },
    [6] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 1,
      comboLv : 2,
      remaining : 0,
      layer : 0x00000001,
      range : {-PIXEL(24), -PIXEL(16), PIXEL(16), PIXEL(16)},
    },
    [7] = {
      kind : DRP,
      faction : FACTION_ALLY,
      special : HALFABLE,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(16), PIXEL(16), PIXEL(32)},
    },
    [8] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 1,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(16), PIXEL(16)},
    },
    [9] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 1,
      comboLv : 1,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(16), PIXEL(16)},
    },
    [10] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 1,
      comboLv : 2,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(16), PIXEL(16)},
    },
    [11] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 1,
      remaining : 0,
      layer : 0x00000001,
      range : {-PIXEL(24), -PIXEL(16), PIXEL(16), PIXEL(16)},
    },
    [12] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 1,
      comboLv : 1,
      remaining : 0,
      layer : 0x00000001,
      range : {-PIXEL(24), -PIXEL(16), PIXEL(16), PIXEL(16)},
    },
    [13] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 1,
      comboLv : 2,
      remaining : 0,
      layer : 0x00000001,
      range : {-PIXEL(24), -PIXEL(16), PIXEL(16), PIXEL(16)},
    },
    [14] = {
      kind : DRP,
      faction : FACTION_ALLY,
      special : HALFABLE,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(16), PIXEL(16), PIXEL(32)},
    },
    [15] = {
      kind : DRP,
      faction : FACTION_NEUTRAL,
      LAYER(0xFFFFFFFF),
      hitzone : 1,
      remaining : 0,
      range : {PIXEL(0), -PIXEL(16), PIXEL(16), PIXEL(32)},
    },
};

const s32 s32_ARRAY_08370de8[8] = {56, 32, 48, 64, 56, 48, 72, 48};

const struct Coord Coord_08370e08 = {PIXEL(0), -PIXEL(24)};

const struct Rect Rect_08370e10 = {0x0, 0x0, 0x1000, 0x2800};
