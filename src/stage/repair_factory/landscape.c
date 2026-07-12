#include "palette_animation.h"
#include "gfx.h"
#include "global.h"
#include "mission.h"
#include "overworld.h"

#define STAGE (gOverworld.work.repairFactory)

static void initRepairFactory(struct Coord* _ UNUSED);
static void repairFactory_0800d6b4(struct Coord* c);
static void repairFactory_0800d8c0(struct Coord* _ UNUSED);
static void exitRepairFactory(struct Coord* _ UNUSED);

static const StageFunc sStageRoutine[4] = {
    initRepairFactory,
    repairFactory_0800d6b4,
    repairFactory_0800d8c0,
    exitRepairFactory,
};

static void initRepairFactory(struct Coord* _ UNUSED) {
  gOverworld.state[0] = 0;
  STAGE.unk_000 = 0;
  STAGE.unk_001 = 0;
  STAGE.unk_002 = 0;
  StartPaletteAnimation(0x2B, 0);
  StartPaletteAnimation(0x2C, 0);
}

static void repairFactory_0800d6b4(struct Coord* c) {
  if ((TILESET_ID(1) == STAGE_REPAIR_FACTORY) && (TILESET_IDX(1) == 1)) {
    if ((STAGE.unk_000 & (1 << 0)) == 0) {
      STAGE.unk_000 |= (1 << 0);
      StartPaletteAnimation(45, 0);
    }
    StepPaletteAnimation(45);

  } else if (STAGE.unk_000 & (1 << 0)) {
    STAGE.unk_000 ^= (1 << 0);
    RemovePaletteAnimation(45);
  }

  if ((TILESET_ID(1) == STAGE_REPAIR_FACTORY) && (TILESET_IDX(1) == 4)) {
    if ((STAGE.unk_000 & (1 << 1)) == 0) {
      STAGE.unk_000 |= (1 << 1);
      StartPaletteAnimation(46, 0);
      StartPaletteAnimation(47, 0);
      StartPaletteAnimation(48, 0);
    }
    StepPaletteAnimation(46);
    StepPaletteAnimation(47);
    StepPaletteAnimation(48);

  } else if (STAGE.unk_000 & (1 << 1)) {
    STAGE.unk_000 ^= (1 << 1);
    RemovePaletteAnimation(46);
    RemovePaletteAnimation(47);
    RemovePaletteAnimation(48);
  }

  StepPaletteAnimation(43);
  StepPaletteAnimation(44);

  // Toggle Conveyor Direction
  if (gOverworld.state[0] == 0) {
    gOverworld.terrain.conveyor[0] = -0x155;
    gOverworld.terrain.conveyor[1] = 0x155;
    STAGE.unk_001++;
    if (STAGE.unk_001 == 6) {
      STAGE.unk_001 = gOverworld.state[0];
    }
  } else {
    gOverworld.terrain.conveyor[0] = 0x155;
    gOverworld.terrain.conveyor[1] = -0x155;
    STAGE.unk_001--;
    if (STAGE.unk_001 < 0) {
      STAGE.unk_001 = 5;
    }
  }

  STAGE.unk_002++;
  if (STAGE.unk_002 == 45) {
    STAGE.unk_002 = 0;
  }

  if ((c->x - 0x10D001U < 0x5AFFF) || ((c->x < 0x1E000 && (c->y < 0x14000)))) {
    if (!isSoundPlaying(SE_UNK_10b)) {
      PlaySound(SE_UNK_10b);
    }
    SetStageNoiseVolume(SE_UNK_10b);
  } else {
    if (isSoundPlaying(SE_UNK_10b)) {
      StopSound(SE_UNK_10b);
    }
  }
}

static void repairFactory_0800d8c0(struct Coord* _ UNUSED) {
  RequestGraphicTransfer(&(TILESETS(18, 33)[(STAGE.unk_001 << 1) / 3]).g, (void*)0x4000);
  LoadPalette(&(TILESETS(18, 33)[(STAGE.unk_001 << 1) / 3]).pal, 0);

  RequestGraphicTransfer(&(TILESETS(18, 37)[STAGE.unk_002 / 9]).g, (void*)0x4000);
  LoadPalette(&(TILESETS(18, 37)[STAGE.unk_002 / 9]).pal, 0);

  if ((TILESET_ID(1) == STAGE_REPAIR_FACTORY) && (TILESET_IDX(1) == 4)) {
    if ((gMission.unk_00)->missionDones & (1 << STAGE_MISSILE_FACTORY)) {
      RequestGraphicTransfer(&(TILESETS(18, 0)[92]).g, (void*)0x4000);
      LoadPalette(&(TILESETS(18, 0)[92]).pal, 0);
    }
  }
}

static void exitRepairFactory(struct Coord* _ UNUSED) {
  RemovePaletteAnimation(43);
  RemovePaletteAnimation(44);
  RemovePaletteAnimation(45);
  RemovePaletteAnimation(46);
  RemovePaletteAnimation(47);
  RemovePaletteAnimation(48);
  if (isSoundPlaying(SE_UNK_10b)) {
    StopSound(SE_UNK_10b);
  }
}

// ------------------------------------------------------------------------------------------------------------------------------------

static void LayerUpdate_2(struct StageLayer* l, const struct Stage* stage);
static void LayerUpdate_3(struct StageLayer* l, const struct Stage* stage);

// clang-format off
static const StageLayerRoutine sLayerRoutine[4] = {
    [0] = {
      [LAYER_UPDATE] = NULL,
      [LAYER_DRAW]   = NULL,
      [LAYER_EXIT]   = NULL,
    },
    [1] = {
      [LAYER_UPDATE] = NULL,
      [LAYER_DRAW]   = DrawGeneralStageLayer,
      [LAYER_EXIT]   = NULL,
    },
    [2] = {
      [LAYER_UPDATE] = LayerUpdate_2,
      [LAYER_DRAW]   = DrawGeneralStageLayer,
      [LAYER_EXIT]   = NULL,
    },
    [3] = {
      [LAYER_UPDATE] = LayerUpdate_3,
      [LAYER_DRAW]   = DrawGeneralStageLayer,
      [LAYER_EXIT]   = NULL,
    },
};
// clang-format on

static void LayerUpdate_2(struct StageLayer* l, const struct Stage* stage) {
  s32 x;

  if (l->phase == 0) {
    BGCNT16((l->bgIdx << 16) >> 20) = (BGCNT16((l->bgIdx << 16) >> 20) & 0xFFFC) | 2;
    (l->scrollPower).x = 0xC0;
    (l->scrollPower).y = 0xC0;
    l->phase++;
  }

  x = gScreenX[(l->viewportCenterPixel).x >> 4];
  if (x < 6) {
    (l->scrollPower).y = 0x100;
    (l->scroll).x = 120;
  } else if (x < 17) {
    (l->scroll).x = 960;
    (l->scroll).y = 200;
  } else if (x < 20) {
    (l->scroll).x = 1080;
    (l->scroll).y = 140;
  } else {
    (l->scroll).x = 1752;
    (l->scroll).y = 200;
  }
}

static void LayerUpdate_3(struct StageLayer* l, const struct Stage* stage) {
  s32 x = gScreenX[(l->viewportCenterPixel).x >> 4];
  if (x < 6) {
    (l->scrollPower).x = 0x40;
    (l->scrollPower).y = 0x100;
    (l->scroll).x = 360;
  } else if (x < 15) {
    (l->scroll).x = 1560;
    (l->scroll).y = 320;
  } else if (x < 17) {
    (l->scroll).x = 1920;
    (l->scroll).y = 400;
  } else if (x < 20) {
    (l->scroll).x = 2160;
    (l->scroll).y = 280;
  } else if (x < 28) {
    (l->scroll).x = 3000;
    (l->scroll).y = 400;
  } else {
    (l->scroll).x = 3504;
    (l->scroll).y = 400;
  }
}

// ------------------------------------------------------------------------------------------------------------------------------------

bool8 FUN_0800daec(s32 x, s32 y) {
  struct Coord c;
  if ((u32)(x - 0x69000) <= 0x1DFFF && (u32)(y - 0x28000) <= 0x13FFF &&
      gOverworld.terrain.tilemap[gOverworld.terrain.tilemap[0] * (y >> 12) + (x >> 12) + 2] !=
          gOverworld.terrain.tilemap[((y - 0x28000) >> 12) * gOverworld.terrain.tilemap[0] + (x >> 12) + 2]) {
    c.x = x;
    c.y = y;
    if (x <= 0x77FFF) {
      LoadScreenIntoMetatileMap(7, 4, 0x36);
    } else {
      LoadScreenIntoMetatileMap(8, 4, 0x37);
    }
    AppendQuake(8, &c);
    return TRUE;
  }
  return FALSE;
}

#undef STAGE

// ------------------------------------------------------------------------------------------------------------------------------------

#include "stage/repair_factory/layer.h"
//
#include "stage/repair_factory/landscape.h"
