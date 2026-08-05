#include "palette_animation.h"
#include "global.h"
#include "overworld.h"
#include "system.h"
#include "story.h"

void FUN_08014b04();

static void initGiantElevator(struct Coord* _ UNUSED);
static void gelevator_08013e88(struct Coord* _ UNUSED);
static void gelevator_08014038(struct Coord* _ UNUSED);
static void nop_080140a4(struct Coord* _ UNUSED);

static const StageFunc sStageRoutine[4] = {
    initGiantElevator,
    gelevator_08013e88,
    gelevator_08014038,
    nop_080140a4,
};

static void initGiantElevator(struct Coord* _ UNUSED) {
  gOverworld.state[0] = 0;
  gOverworld.state[1] = 0;
  gOverworld.work.giantElevator.unk_000[0] = 0;
  gOverworld.work.giantElevator.unk_004 = 0;
  gOverworld.work.giantElevator.unk_006 = 0;
  if (FLAG(gCurStory.s.gameflags, FLAG_49)) {
    FUN_08014b04();
  }
}

static void gelevator_08013e88(struct Coord* _ UNUSED) {
  if ((TILESET_ID(0) == STAGE_GIANT_ELEVATOR) && (TILESET_IDX(0) == 0)) {
    if ((gOverworld.work.giantElevator.unk_000[0] & (1 << 0)) == 0) {
      gOverworld.work.giantElevator.unk_000[0] |= (1 << 0);
      StartPaletteAnimation(216, 0);
    }
    StepPaletteAnimation(216);

  } else if ((gOverworld.work.giantElevator.unk_000[0] & (1 << 0))) {
    gOverworld.work.giantElevator.unk_000[0] ^= (1 << 0);
    RemovePaletteAnimation(216);
  }

  if ((TILESET_ID(1) == STAGE_GIANT_ELEVATOR) && (TILESET_IDX(1) == 1)) {
    if ((gOverworld.work.giantElevator.unk_000[0] & (1 << 1)) == 0) {
      gOverworld.work.giantElevator.unk_000[0] |= (1 << 1);
      StartPaletteAnimation(215, 0);
    }
    StepPaletteAnimation(215);

  } else if ((gOverworld.work.giantElevator.unk_000[0] & (1 << 1))) {
    gOverworld.work.giantElevator.unk_000[0] ^= (1 << 1);
    RemovePaletteAnimation(215);
  }

  if ((TILESET_ID(1) == STAGE_GIANT_ELEVATOR) && (TILESET_IDX(1) == 2)) {
    if ((gOverworld.work.giantElevator.unk_000[0] & (1 << 2)) == 0) {
      gOverworld.work.giantElevator.unk_000[0] |= (1 << 2);
      StartPaletteAnimation(217, 0);
      gOverworld.work.giantElevator.unk_006 = 0;
    }
    StepPaletteAnimation(217);
    if (gOverworld.state[0] >= 11) {
      if (gOverworld.work.giantElevator.unk_004 != 0) {
        gOverworld.work.giantElevator.unk_004 -= 2;
      }
    } else if (gOverworld.state[0] > 1) {
      if (gOverworld.work.giantElevator.unk_004 < 256) {
        gOverworld.work.giantElevator.unk_004 += 2;
      } else if (gOverworld.state[0] == 2) {
        gOverworld.state[0]++;
      }
    }
    gOverworld.work.giantElevator.unk_006 += gOverworld.work.giantElevator.unk_004;
    if (gOverworld.work.giantElevator.unk_006 >= 2560) {
      gOverworld.work.giantElevator.unk_006 = 0;
    }

  } else if ((gOverworld.work.giantElevator.unk_000[0] & (1 << 2))) {
    gOverworld.work.giantElevator.unk_000[0] ^= (1 << 2);
    RemovePaletteAnimation(217);
  }
}

static void gelevator_08014038(struct Coord* _ UNUSED) {
  if ((TILESET_ID(1) == STAGE_GIANT_ELEVATOR) && (TILESET_IDX(1) == 2)) {
    RequestGraphicTransfer(&(TILESETS(18, 153)[gOverworld.work.giantElevator.unk_006 >> 9]).g, (void*)0x4000);
    LoadPalette(&(TILESETS(18, 153)[gOverworld.work.giantElevator.unk_006 >> 9]).pal, 0);
  }
}

static void nop_080140a4(struct Coord* _ UNUSED) {
  // nop
  return;
}

// ------------------------------------------------------------------------------------------------------------------------------------

void FUN_080140a8(struct StageLayer* l, const struct Stage* stage);
void giant_elevator_08014124(struct StageLayer* l, const struct Stage* stage);
void FUN_08014194(struct StageLayer* l, const struct Stage* stage);
void FUN_080141f0(struct StageLayer* l, const struct Stage* stage);
void FUN_08014258(struct StageLayer* l, const struct Stage* stage);
void gelevator_080142b4(struct StageLayer* l, const struct Stage* stage);
void gelevator_08014678(struct StageLayer* l, const struct Stage* stage);
void FUN_0801478c(struct StageLayer* l, const struct Stage* stage);
void giantElevator_08014880(struct StageLayer* l, const struct Stage* stage);
void giantElevator_080148d8(struct StageLayer* l, const struct Stage* stage);
void giantElevator_08014a34(struct StageLayer* l, const struct Stage* stage);
void giantElevator_08014a64(struct StageLayer* l, const struct Stage* stage);
void giantElevator_08014ad4(struct StageLayer* l, const struct Stage* stage);

// clang-format off
static const StageLayerRoutine sLayerRoutine[9] = {
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
      [LAYER_UPDATE] = FUN_080140a8,
      [LAYER_DRAW]   = DrawGeneralStageLayer,
      [LAYER_EXIT]   = NULL,
    },
    [3] = {
      [LAYER_UPDATE] = giant_elevator_08014124,
      [LAYER_DRAW]   = FUN_08014194,
      [LAYER_EXIT]   = NULL,
    },
    [4] = {
      [LAYER_UPDATE] = FUN_080141f0,
      [LAYER_DRAW]   = FUN_08014258,
      [LAYER_EXIT]   = NULL,
    },
    [5] = {
      [LAYER_UPDATE] = gelevator_080142b4,
      [LAYER_DRAW]   = gelevator_08014678,
      [LAYER_EXIT]   = NULL,
    },
    [6] = {
      [LAYER_UPDATE] = FUN_0801478c,
      [LAYER_DRAW]   = giantElevator_08014880,
      [LAYER_EXIT]   = NULL,
    },
    [7] = {
      [LAYER_UPDATE] = giantElevator_080148d8,
      [LAYER_DRAW]   = giantElevator_08014a34,
      [LAYER_EXIT]   = NULL,
    },
    [8] = {
      [LAYER_UPDATE] = giantElevator_08014a64,
      [LAYER_DRAW]   = giantElevator_08014ad4,
      [LAYER_EXIT]   = NULL,
    },
};
// clang-format on

void FUN_080140a8(struct StageLayer* l, const struct Stage* stage) {
  if (l->viewportCenterPixel.x <= 0xB3F && l->viewportCenterPixel.y <= 0x3BF) {
    l->scrollPower.x = 0x40;
    l->scrollPower.y = 0x40;
    l->scroll.x = 0x4EC;
    l->scroll.y = 0xF0;
  } else if (l->viewportCenterPixel.x <= 0xEFF) {
    l->scrollPower.x = 0x80;
    l->scrollPower.y = 0x80;
    l->scroll.x = 0x5A0;
    if (l->viewportCenterPixel.y <= 0x3BF) {
      l->scroll.y = 0x190;
    } else {
      l->scroll.y = 0x320;
    }
  } else {
    l->scrollPower.x = 0x80;
    l->scrollPower.y = 0x80;
    l->scroll.x = 0x8E8;
    l->scroll.y = 0x410;
  }
}

void giant_elevator_08014124(struct StageLayer* l, const struct Stage* stage) {
  u32 ph = l->phase;
  if (ph == 0) {
    u16 b = l->bgIdx;
    u32 n = b >> 4;
    BGCNT16(n) = l->prio | l->screenBase | 0x44;
    RESET_BGOFS(n);
    LoadBgMap(b, gBgMapOffsets, 0x62, 0, 0);
    l->unk_10 = 0;
    l->phase++;
  }
  if (l->viewportCenterPixel.x <= 0x34F) {
    l->unk_10--;
  } else {
    l->unk_10++;
  }
}

void FUN_08014194(struct StageLayer* l, const struct Stage* stage) {
  u16 b = l->bgIdx;
  if (l->viewportCenterPixel.x <= 0x34F) {
    BGnHOFS(b >> 4) = (l->viewportCenterPixel.x - 0xF0) >> 1;
  } else {
    BGnHOFS(b >> 4) = (l->viewportCenterPixel.x - 0x4B0) >> 1;
  }
  BGnVOFS(b >> 4) = l->viewportCenterPixel.y + (l->unk_10 >> 1);
}

void FUN_080141f0(struct StageLayer* l, const struct Stage* stage) {
  u32 ph = l->phase;
  if (ph == 0) {
    u16 b = l->bgIdx;
    u32 n = b >> 4;
    BGCNT16(n) = l->prio | l->screenBase | 0x44;
    LoadBgMap(b, gBgMapOffsets, 0x61, 0, 0);
    l->unk_10 = 0;
    l->phase++;
  }
  if (l->viewportCenterPixel.x <= 0x34F) {
    l->unk_10++;
  } else {
    l->unk_10--;
  }
}

void FUN_08014258(struct StageLayer* l, const struct Stage* stage) {
  u16 b = l->bgIdx;
  if (l->viewportCenterPixel.x <= 0x34F) {
    BGnHOFS(b >> 4) = (l->viewportCenterPixel.x - 0xF0) >> 2;
  } else {
    BGnHOFS(b >> 4) = (l->viewportCenterPixel.x - 0x4B0) >> 2;
  }
  BGnVOFS(b >> 4) = l->viewportCenterPixel.y + (l->unk_10 >> 2);
}

INCASM("asm/stage_gfx/giant_elevator_p1_a.inc");

// Builds the WIN0H HDMA table for the giant elevator shafts: two 0xA0-line
// passes over a Malloc'd buffer keyed off the elevator car positions, hooked
// into gIntrManager.reservedDma0. Logic verified against the asm; parked on
// the loop-staging orchestration basin (bs spilled in-place on b's reg, the
// 0x100 mask living in ip, and the c copy in r7 - a dozen pin/anchor rounds
// each fixed one slot and displaced another).
NON_MATCH void gelevator_08014678(struct StageLayer* l, const struct Stage* stage) {
#if MODERN
  u16 a = (u32)(gOverworld.work.giantElevator.unk_00c << 8) >> 16;
  u16 b = (u32)(gOverworld.work.giantElevator.unk_010 << 8) >> 16;
  u16 c = (u32)(gOverworld.work.giantElevator.unk_01c << 8) >> 16;
  u32 d = (u32)(gOverworld.work.giantElevator.unk_020 << 15) >> 23;
  u32* buf = Malloc(0x280);
  if (buf == NULL) {
    return;
  }
  gIntrManager.reservedDma0[0] = (u32)buf;
  gIntrManager.reservedDma0[1] = 0x04000018;
  gIntrManager.reservedDma0[2] = 0xA6600001;
  {
    s32 i;
    u32 v1 = (d << 16) | c;
    u32 v2 = ((d + 0x100) << 16) | c;
    u32* q = buf;
    for (i = 0; i <= 0x9F; i++) {
      if ((i + d) & 0x100) {
        *q = v1;
      } else {
        *q = v2;
      }
      q++;
    }
  }
  {
    s32 t = (s16)b;
    if (t > 0xFF && l->phase <= 7) {
      return;
    }
    {
      s32 i;
      u32 v3 = (t << 16) | a;
      u32 v4 = ((t + 0x100) << 16) | a;
      u32* q = buf;
      for (i = 0; i <= 0x9F; i++) {
        if (((i + t) & 0x100) == 0) {
          *q = v3;
        } else if (l->phase > 7 && t > 0) {
          *q = v4;
        }
        q++;
      }
    }
  }
#else
  INCCODE("asm/stage_gfx/gelevator_4678.inc");
#endif
}

// 0x0801478C
void FUN_0801478c(struct StageLayer* l, const struct Stage* stage) {
  u16 b = l->bgIdx;
  switch (l->phase) {
    case 0:
      BGCNT16(b >> 4) = l->prio | l->screenBase | 0x44;
      LoadBgMap(b, gBgMapOffsets, 0x5e, 0, 0);
      l->unk_10 = 0;
      l->phase++;
      FALLTHROUGH;
    case 1: {
      const struct TerrainHeader* terrain;
      if (gOverworld.state[0] <= 9) {
        break;
      }
      terrain = stage->terrainHdr;
      BGCNT16(b >> 4) = l->screenBase | 0x4046;
      {
        Metatile* tiles = (Metatile*)(terrain->tiles + PTR_U32(&terrain->tiles));
        Screen* screens = (Screen*)(terrain->screens + PTR_U32(&terrain->tiles));
        ResetLayerGraphic(&l->gfx, &l->viewportCenterPixel, (u16*)(((BGCNT16(l->bgIdx >> 4) & 0x1F00) << 3) + 0x06000000), tiles, screens,
                          stage->maps[l->type]);
      }
      l->prevViewportCenterPixel.y = 0x80000001;
      l->prevViewportCenterPixel.x = 0x80000001;
      l->phase++;
      FALLTHROUGH;
    }
    case 2:
      {
        u8* ow = (u8*)&gOverworld;
        s32 k = 0x2D03C;
        asm("" : "+r"(ow));
        asm("" : "+r"(k));
        l->scroll.x = *(s32*)(ow + k) >> 8;
      }
      break;
  }
}

void giantElevator_08014880(struct StageLayer* p, const struct Stage* _) {
  if (gOverworld.state[0] <= 9) {
    s32 n = (u16)p->bgIdx >> 4;
    BGnHOFS(n) = gOverworld.work.giantElevator.unk_028 >> 8;
    BGnVOFS(n) = gOverworld.work.giantElevator.unk_02c >> 8;
  } else {
    DrawGeneralStageLayer(p, _);
  }
}

// 0x080148D8
// PARKED: agbcc hoists the shared `0` argument out of the three phase arms
// and duplicates the (u8)phase truncation; retail rematerialises both inside
// each arm and cross-jumps `movs r3, #0 / bl LoadBgMap` between arms 1 and 3.
// Every barrier tried either kept the hoist or added an s8 sign-extension.
NON_MATCH void giantElevator_080148d8(struct StageLayer* l, const struct Stage* _ UNUSED) {
#if MODERN
  u16 b = l->bgIdx;
  u8 ph = l->phase;
  if (ph == 0) {
    BGCNT16(b >> 4) = l->prio | l->screenBase | 0x8044;
    RESET_BGOFS(b >> 4);
    LoadBgMap((u8)b, gBgMapOffsets, 0x5a, 0, 0);
    loadBgMap_08004248((u16*)(((BGCNT16(b >> 4) & 0x1F00) << 3) + 0x06000800), gBgMapOffsets, 0x5a, 0, 0);
    l->unk_10 = 0;
    l->unk_12 = 0;
    l->phase++;
  }
  if (gOverworld.state[1] != 0) {
    u16 t = l->unk_12;
    if (t <= 0x7FF) {
      l->unk_12 = t + 8;
    }
  }
  {
    s32 nv = (l->unk_12 >> 8) + l->unk_10;
    u8 ph2;
    l->unk_10 = nv;
    ph2 = l->phase;
    if (ph2 == 1) {
      if ((u32)(nv << 16) <= 0x14FF0000) {
        return;
      }
      LoadBgMap((u8)b, gBgMapOffsets, 0x5b, 0, 0);
    } else if (ph2 == 2) {
      if (l->unk_10 <= 0x15FF) {
        return;
      }
      loadBgMap_08004248((u16*)(((BGCNT16(b >> 4) & 0x1F00) << 3) + 0x06000800), gBgMapOffsets, 0x5d, 0, 0);
    } else if (ph2 == 3) {
      if (l->unk_10 <= 0x16FF) {
        return;
      }
      LoadBgMap((u8)b, gBgMapOffsets, 0x5d, 0, 0);
    } else {
      return;
    }
    l->phase++;
  }
#else
  INCCODE("asm/stage_gfx/giantElevator_080148d8.inc");
#endif
}

// 0x08014a34
void giantElevator_08014a34(struct StageLayer* l, const struct Stage* _ UNUSED) {
  const u16 n = l->bgIdx;
  BGnHOFS(n >> 4) = (l->viewportCenterPixel.x - 0x1428) >> 2;
  BGnVOFS(n >> 4) = l->unk_10;
}

// One pool apart: retail splits &gOverworld and the 0x2D025 state offset into
// two literals where agbcc folds them into one relocated word; every C
// spelling tried (base var, offset var, pointer accumulator) refolds.
void giantElevator_08014a64(struct StageLayer* l, const struct Stage* stage) {
  u16 b = l->bgIdx;
  u32 ph = l->phase;
  if (ph == 0) {
    u32 n = b >> 4;
    BGCNT16(n) = l->prio | l->screenBase | 0x44;
    RESET_BGOFS(n);
    LoadBgMap(b, gBgMapOffsets, 0x5c, 0, 0);
    l->unk_10 = 0;
    l->phase++;
  }
  if (gOverworld.state[1] != 0) {
    l->unk_10++;
  }
}

// 0x08014ad4
void giantElevator_08014ad4(struct StageLayer* l, const struct Stage* _ UNUSED) {
  const u16 n = l->bgIdx;
  BGnHOFS(n >> 4) = (l->viewportCenterPixel.x - 0x1428) >> 7;
  BGnVOFS(n >> 4) = l->unk_10 >> 2;
}

void FUN_08014b04(void) {
  ShiftMetatile(0xb4, 0x72, (const struct MetatileShift*)0x083458BC);
  SET_FLAG(gCurStory.s.gameflags, FLAG_49);
}


// ------------------------------------------------------------------------------------------------------------------------------------

extern const struct ChunkMap sChunkMap1;
INCBIN_STATIC(sChunkMap1, "data/stage/giant_elevator/layer1.bin");  // ./tools/dumper/bin.ts ./baserom.gba 0x0834479c 0x08344a60 ./data/stage/giant_elevator/layer1.bin

extern const struct ChunkMap sChunkMap2;
INCBIN_STATIC(sChunkMap2, "data/stage/giant_elevator/layer2.bin");  // ./tools/dumper/bin.ts ./baserom.gba 0x08344a60 0x08344d24 ./data/stage/giant_elevator/layer2.bin

extern const struct ChunkMap sChunkMap3;
INCBIN_STATIC(sChunkMap3, "data/stage/giant_elevator/layer3.bin");  // ./tools/dumper/bin.ts ./baserom.gba 0x08344d24 0x08344fe8 ./data/stage/giant_elevator/layer3.bin

extern const tileset_ofs_t sTilesetOffset[];
INCBIN_STATIC(sTilesetOffset, "data/stage/giant_elevator/tileset_offset.bin");  // ./tools/dumper/bin.ts ./baserom.gba 0x08344fe8 0x083452ac ./data/stage/giant_elevator/tileset_offset.bin

extern const u16 sScreenBehavior[];
INCBIN_STATIC(sScreenBehavior, "data/stage/giant_elevator/screen_behavior.bin");  // ./tools/dumper/bin.ts ./baserom.gba 0x083452ac 0x08345834 ./data/stage/giant_elevator/screen_behavior.bin

const struct Stage gGiantElevatorLandscape = {
  id : STAGE_GIANT_ELEVATOR,
  fn : sStageRoutine,
  terrainHdr : &gStageTerrains[STAGE_GIANT_ELEVATOR],
  maps : {&sChunkMap1, &sChunkMap2, &sChunkMap3},
  bgIdx : {USE_BG1, USE_BG2, USE_BG3},
  prio : {2, 3, 3},
  screenBase : {BGMAP_BLOCK(2), BGMAP_BLOCK(4), BGMAP_BLOCK(6)},
  scrollPower : {{0x100, 0x100}, {0x100, 0x100}, {0x100, 0x100}},
  scroll : {{0, 0}, {0, 0}, {0, 0}},
  tilesetOffset : sTilesetOffset,
  bgFns : sLayerRoutine,
  behavior : sScreenBehavior,
};

static const struct MetatileShift sMetatileShift1 = {x : 247, y : 130, block : 8, row : 30};
static const struct MetatileShift sMetatileShift2 = {x : 179, y : 114, block : 1, row : 4};
