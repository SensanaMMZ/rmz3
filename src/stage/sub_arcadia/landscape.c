#include "palette_animation.h"
#include "global.h"
#include "overworld.h"

#define STAGE (gOverworld.work.subArcadia)

static void FUN_08014b28(struct Coord* _ UNUSED);
static void subAracadia_08014b48(struct Coord* _ UNUSED);
static void nop_08014e78(struct Coord* _ UNUSED);
static void FUN_08014e7c(struct Coord* _ UNUSED);

static const StageFunc sStageRoutine[4] = {
    FUN_08014b28,
    subAracadia_08014b48,
    nop_08014e78,
    FUN_08014e7c,
};

static void FUN_08014b28(struct Coord* _ UNUSED) {
  STAGE.unk_000 = 0;
  STAGE.unk_001 = 0;
}

static void subAracadia_08014b48(struct Coord* _ UNUSED) {
  if ((W_TERRAIN_V2.tilesets[0] >> 8 == STAGE_SUB_ARCADIA) && ((W_TERRAIN_V2.tilesets[0] & 0xFF) == 0)) {
    if ((STAGE.unk_000 & (1 << 0)) == 0) {
      STAGE.unk_000 |= (1 << 0);
      StartPaletteAnimation(124, 0);
      StartPaletteAnimation(125, 0);
      StartPaletteAnimation(126, 0);
      StartPaletteAnimation(130, 0);
      StartPaletteAnimation(166, 0);
    }
    StepPaletteAnimation(124);
    StepPaletteAnimation(125);
    StepPaletteAnimation(126);
    StepPaletteAnimation(130);
    StepPaletteAnimation(166);

  } else if (STAGE.unk_000 & (1 << 0)) {
    STAGE.unk_000 ^= (1 << 0);
    RemovePaletteAnimation(124);
    RemovePaletteAnimation(125);
    RemovePaletteAnimation(126);
    RemovePaletteAnimation(130);
    RemovePaletteAnimation(166);
  }

  if ((W_TERRAIN_V2.tilesets[1] >> 8 == STAGE_SUB_ARCADIA) && ((W_TERRAIN_V2.tilesets[1] & 0xFF) == 1)) {
    if ((STAGE.unk_000 & (1 << 1)) == 0) {
      STAGE.unk_000 |= (1 << 1);
      StartPaletteAnimation(127, 0);
      StartPaletteAnimation(128, 0);
      StartPaletteAnimation(129, 0);
    }
    StepPaletteAnimation(127);
    StepPaletteAnimation(128);
    StepPaletteAnimation(129);

  } else if (STAGE.unk_000 & (1 << 1)) {
    STAGE.unk_000 ^= (1 << 1);
    RemovePaletteAnimation(127);
    RemovePaletteAnimation(128);
    RemovePaletteAnimation(129);
  }

  if ((W_TERRAIN_V2.tilesets[0] >> 8 == STAGE_SUB_ARCADIA) && ((W_TERRAIN_V2.tilesets[0] & 0xFF) == 2)) {
    if ((STAGE.unk_000 & (1 << 2)) == 0) {
      STAGE.unk_000 |= (1 << 2);
      StartPaletteAnimation(161, 0);
      StartPaletteAnimation(162, 0);
      StartPaletteAnimation(163, 0);
      StartPaletteAnimation(164, 0);
      StartPaletteAnimation(165, 0);
    }
    StepPaletteAnimation(161);
    StepPaletteAnimation(162);
    StepPaletteAnimation(163);
    StepPaletteAnimation(164);
    StepPaletteAnimation(165);

  } else if (STAGE.unk_000 & (1 << 2)) {
    STAGE.unk_000 ^= (1 << 2);
    RemovePaletteAnimation(161);
    RemovePaletteAnimation(162);
    RemovePaletteAnimation(163);
    RemovePaletteAnimation(164);
    RemovePaletteAnimation(165);
  }

  if ((W_TERRAIN_V2.tilesets[1] >> 8 == STAGE_SUB_ARCADIA) && ((W_TERRAIN_V2.tilesets[1] & 0xFF) == 3)) {
    if ((STAGE.unk_000 & (1 << 3)) == 0) {
      STAGE.unk_000 |= (1 << 3);
      StartPaletteAnimation(154, 0);
      StartPaletteAnimation(155, 0);
      StartPaletteAnimation(156, 0);
      StartPaletteAnimation(157, 0);
      StartPaletteAnimation(158, 0);
      StartPaletteAnimation(159, 0);
      StartPaletteAnimation(160, 0);
    }
    StepPaletteAnimation(154);
    StepPaletteAnimation(155);
    StepPaletteAnimation(156);
    StepPaletteAnimation(157);
    StepPaletteAnimation(158);
    StepPaletteAnimation(159);
    StepPaletteAnimation(160);

  } else if (STAGE.unk_000 & (1 << 3)) {
    STAGE.unk_000 ^= (1 << 3);
    RemovePaletteAnimation(154);
    RemovePaletteAnimation(155);
    RemovePaletteAnimation(156);
    RemovePaletteAnimation(157);
    RemovePaletteAnimation(158);
    RemovePaletteAnimation(159);
    RemovePaletteAnimation(160);
  }

  if (STAGE.unk_001 == 0) {
    if (FLAG(gCurStory.s.gameflags, IN_CYBERSPACE)) {
      STAGE.unk_001 = 1;
      LoadScreenIntoMetatileMap(1, 6, 78);
    }
    if (STAGE.unk_001 == 0) {
      return;
    }
  }

  if (!FLAG(gCurStory.s.gameflags, IN_CYBERSPACE)) {
    STAGE.unk_001 = 1;
    LoadScreenIntoMetatileMap(1, 6, 23);
  }
}

static void nop_08014e78(struct Coord* _ UNUSED) { return; }

static void FUN_08014e7c(struct Coord* _ UNUSED) {
  RemovePaletteAnimation(0x7c);
  RemovePaletteAnimation(0x7d);
  RemovePaletteAnimation(0x7e);
  RemovePaletteAnimation(0x7f);
  RemovePaletteAnimation(0x80);
  RemovePaletteAnimation(0x81);
  RemovePaletteAnimation(0x82);
  RemovePaletteAnimation(0x9a);
  RemovePaletteAnimation(0x9b);
  RemovePaletteAnimation(0x9c);
  RemovePaletteAnimation(0x9d);
  RemovePaletteAnimation(0x9e);
  RemovePaletteAnimation(0x9f);
  RemovePaletteAnimation(0xa0);
  RemovePaletteAnimation(0xa1);
  RemovePaletteAnimation(0xa2);
  RemovePaletteAnimation(0xa3);
  RemovePaletteAnimation(0xa4);
  RemovePaletteAnimation(0xa5);
  RemovePaletteAnimation(0xa6);
}

// ------------------------------------------------------------------------------------------------------------------------------------

void FUN_08014efc(struct StageLayer* l, const struct Stage* stage);
void FUN_08014f58(struct StageLayer* l, const struct Stage* stage);

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
      [LAYER_UPDATE] = FUN_08014efc,
      [LAYER_DRAW]   = DrawGeneralStageLayer,
      [LAYER_EXIT]   = NULL,
    },
    [3] = {
      [LAYER_UPDATE] = FUN_08014f58,
      [LAYER_DRAW]   = DrawGeneralStageLayer,
      [LAYER_EXIT]   = NULL,
    },
};
// clang-format on

INCASM("asm/stage_gfx/sub_arcadia_p1.inc");

void FUN_08014f58(struct StageLayer* l, const struct Stage* stage) {
  if (l->phase == 0) {
    l->scrollPower.x = 0x100;
    l->scrollPower.y = 0x80;
    l->scroll.x = 0;
    l->scroll.y = 0x4b0;
    l->phase++;
  }
}

// ------------------------------------------------------------------------------------------------------------------------------------

extern const struct ChunkMap sChunkMap1;
INCBIN_STATIC(sChunkMap1, "data/stage/sub_arcadia/layer1.bin");  // ./tools/dumper/bin.ts ./baserom.gba 0x08345904 0x08345bc8 ./data/stage/sub_arcadia/layer1.bin

extern const struct ChunkMap sChunkMap2;
INCBIN_STATIC(sChunkMap2, "data/stage/sub_arcadia/layer2.bin");  // ./tools/dumper/bin.ts ./baserom.gba 0x08345bc8 0x08345e8c ./data/stage/sub_arcadia/layer2.bin

extern const struct ChunkMap sChunkMap3;
INCBIN_STATIC(sChunkMap3, "data/stage/sub_arcadia/layer3.bin");  // ./tools/dumper/bin.ts ./baserom.gba 0x08345e8c 0x08346150 ./data/stage/sub_arcadia/layer3.bin

extern const tileset_ofs_t sTilesetOffset[];
INCBIN_STATIC(sTilesetOffset, "data/stage/sub_arcadia/tileset_offset.bin");  // ./tools/dumper/bin.ts ./baserom.gba 0x08346150 0x08346414 ./data/stage/sub_arcadia/tileset_offset.bin

extern const u16 sScreenBehavior[];
INCBIN_STATIC(sScreenBehavior, "data/stage/sub_arcadia/screen_behavior.bin");  // ./tools/dumper/bin.ts ./baserom.gba 0x08346414 0x0834699c ./data/stage/sub_arcadia/screen_behavior.bin

const struct Stage gSubArcadiaLandscape = {
  id : STAGE_SUB_ARCADIA,
  fn : sStageRoutine,
  terrainHdr : &gStageTerrains[STAGE_SUB_ARCADIA],
  maps : {&sChunkMap1, &sChunkMap2, &sChunkMap3},
  bgIdx : {USE_BG1, USE_BG2, USE_BG3},
  prio : {2, 2, 3},
  screenBase : {BGMAP_BLOCK(2), BGMAP_BLOCK(4), BGMAP_BLOCK(6)},
  scrollPower : {{0x100, 0x100}, {0x100, 0x100}, {0x100, 0x100}},
  scroll : {{0, 0}, {0, 0}, {0, 0}},
  tilesetOffset : sTilesetOffset,
  bgFns : sLayerRoutine,
  behavior : sScreenBehavior,
  conveyor : {0x0, 0x0},
};

#undef STAGE
