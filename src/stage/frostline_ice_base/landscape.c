#include "palette_animation.h"
#include "global.h"
#include "overworld.h"

static void initIceBase(struct Coord* _ UNUSED);
static void FUN_08010eb8(struct Coord* _ UNUSED);
static void FUN_08011100(struct Coord* _ UNUSED);
static void FUN_08011104(struct Coord* _ UNUSED);

static const StageFunc sStageRoutine[4] = {
    initIceBase,
    FUN_08010eb8,
    FUN_08011100,
    FUN_08011104,
};

static void initIceBase(struct Coord* _ UNUSED) {
  gOverworld.work.iceBase.unk_000 = 0;
  return;
}

static void FUN_08010eb8(struct Coord* _ UNUSED) {
  if ((W_TERRAIN_V2.tilesets[0] >> 8 == STAGE_ICE_BASE) && ((W_TERRAIN_V2.tilesets[0] & 0xFF) == 0)) {
    if ((gOverworld.work.iceBase.unk_000 & (1 << 0)) == 0) {
      gOverworld.work.iceBase.unk_000 |= (1 << 0);
      StartPaletteAnimation(133, 0);
    }
    StepPaletteAnimation(133);

  } else if ((gOverworld.work.iceBase.unk_000 & (1 << 0))) {
    gOverworld.work.iceBase.unk_000 ^= (1 << 0);
    RemovePaletteAnimation(133);
  }

  if ((W_TERRAIN_V2.tilesets[0] >> 8 == STAGE_ICE_BASE) && ((W_TERRAIN_V2.tilesets[0] & 0xFF) == 4)) {
    if ((gOverworld.work.iceBase.unk_000 & (1 << 1)) == 0) {
      gOverworld.work.iceBase.unk_000 |= (1 << 1);
      StartPaletteAnimation(139, 0);
      StartPaletteAnimation(140, 0);
      StartPaletteAnimation(141, 0);
    }
    StepPaletteAnimation(139);
    StepPaletteAnimation(140);
    StepPaletteAnimation(141);

  } else if ((gOverworld.work.iceBase.unk_000 & (1 << 1))) {
    gOverworld.work.iceBase.unk_000 ^= (1 << 1);
    RemovePaletteAnimation(139);
    RemovePaletteAnimation(140);
    RemovePaletteAnimation(141);
  }

  if ((W_TERRAIN_V2.tilesets[1] >> 8 == STAGE_ICE_BASE) && ((W_TERRAIN_V2.tilesets[1] & 0xFF) == 2)) {
    if ((gOverworld.work.iceBase.unk_000 & (1 << 2)) == 0) {
      gOverworld.work.iceBase.unk_000 |= (1 << 2);
      StartPaletteAnimation(136, 0);
    }
    StepPaletteAnimation(136);

  } else if ((gOverworld.work.iceBase.unk_000 & (1 << 2))) {
    gOverworld.work.iceBase.unk_000 ^= (1 << 2);
    RemovePaletteAnimation(136);
  }

  if ((W_TERRAIN_V2.tilesets[1] >> 8 == STAGE_ICE_BASE) && ((W_TERRAIN_V2.tilesets[1] & 0xFF) == 1)) {
    if ((gOverworld.work.iceBase.unk_000 & (1 << 3)) == 0) {
      gOverworld.work.iceBase.unk_000 |= (1 << 3);
      StartPaletteAnimation(134, 0);
      StartPaletteAnimation(135, 0);
    }
    StepPaletteAnimation(134);
    StepPaletteAnimation(135);

  } else if ((gOverworld.work.iceBase.unk_000 & (1 << 3))) {
    gOverworld.work.iceBase.unk_000 ^= (1 << 3);
    RemovePaletteAnimation(134);
    RemovePaletteAnimation(135);
  }

  if ((W_TERRAIN_V2.tilesets[1] >> 8 == STAGE_ICE_BASE) && ((W_TERRAIN_V2.tilesets[1] & 0xFF) == 3)) {
    if ((gOverworld.work.iceBase.unk_000 & (1 << 4)) == 0) {
      gOverworld.work.iceBase.unk_000 |= (1 << 4);
      StartPaletteAnimation(137, 0);
      StartPaletteAnimation(138, 0);
    }
    StepPaletteAnimation(137);
    StepPaletteAnimation(138);

  } else if ((gOverworld.work.iceBase.unk_000 & (1 << 4))) {
    gOverworld.work.iceBase.unk_000 ^= (1 << 4);
    RemovePaletteAnimation(137);
    RemovePaletteAnimation(138);
  }
}

static void FUN_08011100(struct Coord* _ UNUSED) {
  // Nop
  return;
}

static void FUN_08011104(struct Coord* _ UNUSED) {
  RemovePaletteAnimation(133);
  RemovePaletteAnimation(134);
  RemovePaletteAnimation(135);
  RemovePaletteAnimation(136);
  RemovePaletteAnimation(137);
  RemovePaletteAnimation(138);
  RemovePaletteAnimation(139);
  RemovePaletteAnimation(140);
  RemovePaletteAnimation(141);
}

// ------------------------------------------------------------------------------------------------------------------------------------

void FUN_08011140(struct StageLayer* l, const struct Stage* stage);
void FUN_080111bc(struct StageLayer* l, const struct Stage* stage);
void icebase_080111dc(struct StageLayer* l, const struct Stage* stage);
void FUN_0801126c(struct StageLayer* l, const struct Stage* stage);
void FUN_080113dc(struct StageLayer* l, const struct Stage* stage);
void FUN_08011414(struct StageLayer* l, const struct Stage* stage);
void FUN_08011464(struct StageLayer* l, const struct Stage* stage);
void icebase_080114d0(struct StageLayer* l, const struct Stage* stage);

// clang-format off
static const StageLayerRoutine sLayerRoutine[7] = {
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
      [LAYER_UPDATE] = FUN_08011140,
      [LAYER_DRAW]   = DrawGeneralStageLayer,
      [LAYER_EXIT]   = FUN_080111bc,
    },
    [3] = {
      [LAYER_UPDATE] = icebase_080111dc,
      [LAYER_DRAW]   = FUN_0801126c,
      [LAYER_EXIT]   = NULL,
    },
    [4] = {
      [LAYER_UPDATE] = FUN_080113dc,
      [LAYER_DRAW]   = DrawGeneralStageLayer,
      [LAYER_EXIT]   = NULL,
    },
    [5] = {
      [LAYER_UPDATE] = FUN_08011414,
      [LAYER_DRAW]   = FUN_08011464,
      [LAYER_EXIT]   = NULL,
    },
    [6] = {
      [LAYER_UPDATE] = icebase_080114d0,
      [LAYER_DRAW]   = NULL,
      [LAYER_EXIT]   = NULL,
    },
};
// clang-format on

INCASM("asm/stage_gfx/frostline_ice_base_p1.inc");

void FUN_080113dc(struct StageLayer* l, const struct Stage* stage) {
  if (l->phase == 0) {
    l->scrollPower.x = 0x80;
    l->scrollPower.y = 0x100;
    l->phase++;
  }
  if ((l->viewportCenterPixel).x <= 0x1c1f) {
    l->scroll.x = 0xca8;
  } else {
    l->scroll.x = 0xe88;
  }
}

INCASM("asm/stage_gfx/frostline_ice_base_p2.inc");

// ------------------------------------------------------------------------------------------------------------------------------------

extern const struct ChunkMap sChunkMap1;
INCBIN_STATIC(sChunkMap1, "data/stage/frostline_ice_base/layer1.bin");  // ./tools/dumper/bin.ts ./baserom.gba 0x083402f4 0x083404f8 ./data/stage/frostline_ice_base/layer1.bin

extern const struct ChunkMap sChunkMap2;
INCBIN_STATIC(sChunkMap2, "data/stage/frostline_ice_base/layer2.bin");  // ./tools/dumper/bin.ts ./baserom.gba 0x083404f8 0x083406fc ./data/stage/frostline_ice_base/layer2.bin

extern const struct ChunkMap sChunkMap3;
INCBIN_STATIC(sChunkMap3, "data/stage/frostline_ice_base/layer3.bin");  // ./tools/dumper/bin.ts ./baserom.gba 0x083406fc 0x08340900 ./data/stage/frostline_ice_base/layer3.bin

extern const tileset_ofs_t sTilesetOffset[];
INCBIN_STATIC(sTilesetOffset, "data/stage/frostline_ice_base/tileset_offset.bin");  // ./tools/dumper/bin.ts ./baserom.gba 0x08340900 0x08340b04 ./data/stage/frostline_ice_base/tileset_offset.bin

extern const u16 sScreenBehavior[];
INCBIN_STATIC(sScreenBehavior, "data/stage/frostline_ice_base/screen_behavior.bin");  // ./tools/dumper/bin.ts ./baserom.gba 0x08340b04 0x08340f0c ./data/stage/frostline_ice_base/screen_behavior.bin

const struct Stage gFrostlineIceBaseLandscape = {
  id : STAGE_ICE_BASE,
  fn : sStageRoutine,
  terrainHdr : &gStageTerrains[STAGE_ICE_BASE],
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
