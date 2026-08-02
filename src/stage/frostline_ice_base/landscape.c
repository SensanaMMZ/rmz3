#include "palette_animation.h"
#include "global.h"
#include "overworld.h"
#include "system.h"

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

// 0x08011140
void FUN_08011140(struct StageLayer* l, const struct Stage* stage) {
  if (l->phase == 0) {
    BGCNT16((u16)l->bgIdx >> 4) &= 0xFFFC;
    gBlendRegBuffer.bldclt = 0x3B44;
    gBlendRegBuffer.bldalpha = 0x0C04;
    l->phase++;
  }
  if (l->viewportCenterPixel.x <= 0x151F) {
    SEA = PIXEL(800);
  } else {
    SEA = PIXEL(10240);
  }
}

// 0x080111bc
void FUN_080111bc(struct StageLayer* l UNUSED, const struct Stage* _ UNUSED) {
  gBlendRegBuffer.bldclt = 0;
  SEA = PIXEL(10240);
}

void icebase_080111dc(struct StageLayer* l, const struct Stage* stage UNUSED) {
  if (l->phase == 0) {
    const u16 n = (l->bgIdx << 16) >> 20;
    BGCNT16(n) = (l->prio | l->screenBase) | BGCNT_CHARBASE(1) | BGCNT_MOSAIC | BGCNT_TXT256x512;
    RESET_BGOFS(n);
    CpuFastCopy(BGMAP(63), (void*)(VRAM + SCREEN_BASE_16(n)), 2048);
    CpuFastCopy(BGMAP(64), (void*)(VRAM + 0x800 + SCREEN_BASE_16(n)), 2048);
    l->phase++;
  }
}

void FUN_0801126c(struct StageLayer* l, const struct Stage* stage) {
  u32* q = Malloc(0xA0 * 4);
  if (q != NULL) {
    register s32 i asm("r2");
    u32 sh;
    u32 mfff;
    s32 base;
    u32 hi;
    gIntrManager.reservedDma0[0] = (u32)q;
    gIntrManager.reservedDma0[1] = 0x0400001C;
    gIntrManager.reservedDma0[2] = 0xA6600001;

    hi = (u16)(l->viewportCenterPixel.x / 3);
    {
      s32 c0 = (l->viewportCenterPixel.y - 0xe0) / 3 + 1;
      s32 c;
      i = 0;
      c = (s16)c0;
      if (c <= 0x8b) {
        u32* p = q;
        u32 val;
        base = c;
        val = ((u32)base << 16) | hi;
        do {
          *p++ = val;
          i++;
          if (i > 0x9f) {
            break;
          }
        } while (base + i <= 0x8b);
      }
    }

    hi = (u16)((u32)(l->viewportCenterPixel.x << 0xf) >> 0x10);
    {
      u32 cu = (u16)(((l->viewportCenterPixel.y - 0x160) >> 1) + 3);
      u32 t;
      s32 sum;
      if (i > 0x9f) {
        goto band3;
      }
      t = cu << 16;
      base = (s32)t >> 16;
      sum = base + i;
      asm("" : "=r"(sh) : "0"(t));
      if (sum <= 0x8f) {
        s32 bc = base;
        u32 val = (0x90 << 16) - ((u32)i << 16);
        u32* p = (u32*)((i << 2) + (u32)q);
        mfff = 0xFFFF0000;
        do {
          *p++ = val;
          val += mfff;
          i++;
          if (i > 0x9f) {
            goto band3;
          }
        } while (bc + i <= 0x8f);
        asm volatile("" :: "r"(mfff));
      }
      if (i > 0x9f) {
        goto band3;
      }
      if (((s32)sh >> 16) + i <= 0xe0) {
        u32* p = (u32*)((i << 2) + (u32)q);
        u32 val;
        base = (s32)sh >> 16;
        val = ((u32)base << 16) | hi;
        do {
          *p++ = val;
          i++;
          if (i > 0x9f) {
            goto band3;
          }
        } while (base + i <= 0xe0);
      }
    }

  band3:
    hi = (u16)((u32)((l->viewportCenterPixel.x * 3) << 0xe) >> 0x10);
    {
      u32 cu = (u16)((((l->viewportCenterPixel.y - 0x1e0) * 3) >> 2) + 5);
      u32 t;
      s32 sum;
      if (i > 0x9f) {
        goto done;
      }
      t = cu << 16;
      base = (s32)t >> 16;
      sum = base + i;
      asm("" : "=r"(sh) : "0"(t));
      if (sum <= 0xdf) {
        s32 bc = base;
        u32 val = (0xf0 << 16) - ((u32)i << 16);
        u32* p = (u32*)((i << 2) + (u32)q);
        mfff = 0xFFFF0000;
        do {
          *p++ = val;
          val += mfff;
          i++;
          if (i > 0x9f) {
            goto done;
          }
        } while (bc + i <= 0xdf);
      }
      if (i > 0x9f) {
        goto done;
      }
      {
        u32 val = hi | sh;
        u32* p = (u32*)((i << 2) + (u32)q);
        do {
          *p++ = val;
          i++;
        } while (i <= 0x9f);
      }
    }
  done:
    asm volatile("" :: "r"(hi));
  }
}

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

void FUN_08011414(struct StageLayer* l, const struct Stage* stage) {
  if (l->phase == 0) {
    l->scrollPower.x = 0x40;
    l->scrollPower.y = 0x100;
    l->unk_10 = 0;
    l->phase++;
  }
  if ((l->viewportCenterPixel).x <= 0x1C1F) {
    l->scroll.x = 0x12FC;
  } else {
    l->scroll.x = 0x15CC;
  }
  l->unk_10++;
  if (l->unk_10 == 0x30) {
    l->unk_10 = 0;
  }
}

// 0x08011464
void FUN_08011464(struct StageLayer* l, const struct Stage* stage) {
  RequestGraphicTransfer(&(TILESETS(18, 66)[(u16)(((u16)l->unk_10 >> 3) % 6)]).g, (void*)0x4000);
  LoadPalette(&(TILESETS(18, 66)[(u16)(((u16)l->unk_10 >> 3) % 6)]).pal, 0);
  DrawGeneralStageLayer(l, stage);
}

void icebase_080114d0(struct StageLayer* l, const struct Stage* stage) {
  u32 ph = l->phase;
  if (ph == 0) {
    u32 n = (u16)l->bgIdx >> 4;
    BGCNT16(n) = l->screenBase | 0x45;
    RESET_BGOFS(n);
    gVideoRegBuffer.dispcnt &= 0xDBFF;
    CpuFastSet((void*)(*(s32*)0x085223A4 + 0x085223AC), (void*)(VRAM + SCREEN_BASE_16(n)), 0x200);
    l->phase++;
  }
}

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
