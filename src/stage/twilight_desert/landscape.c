#include "palette_animation.h"
#include "gfx.h"
#include "global.h"
#include "overworld.h"
#include "story.h"
#include "system.h"

static void initTwilightDesert(struct Coord* _ UNUSED);
static void FUN_0800f8dc(struct Coord* c);
static void nop_0800f9bc(struct Coord* _ UNUSED);
static void exitTwilightDesert(struct Coord* _ UNUSED);

static const StageFunc sStageRoutine[4] = {
    initTwilightDesert,
    FUN_0800f8dc,
    nop_0800f9bc,
    exitTwilightDesert,
};

static void initTwilightDesert(struct Coord* _ UNUSED) {
  gOverworld.work.twilightDesert.unk_004 = 0;
  gOverworld.work.twilightDesert.unk_001 = 0;
  StartPaletteAnimation(131, 0);
  StartPaletteAnimation(132, 0);
}

static void FUN_0800f8dc(struct Coord* c) {
  if (gOverworld.work.twilightDesert.unk_004 != 0) {
    if (!FLAG(gCurStory.s.gameflags, TIME_ELF_ENABLED) && !isSoundPlaying(SE_UNK_102)) {
      PlaySound(SE_UNK_102);
    }
    if ((gOverworld.work.twilightDesert.unk_004 != 0) && !FLAG(gCurStory.s.gameflags, TIME_ELF_ENABLED)) {
      goto _SKIP;
    }
  }
  if (isSoundPlaying(SE_UNK_102)) {
    StopSound(SE_UNK_102);
  }

_SKIP:
  if (c->x < 0x1fe001) {
    if (((c->x - 0x7a000U < 0x7b001) || (c->x - 0xff000U < 0x2f001)) || (c->x - 0x185000U < 0x2e001)) {
      if (!isSoundPlaying(SE_UNK_c6)) {
        PlaySound(SE_UNK_c6);
      }
      SetStageNoiseVolume(SE_UNK_c6);
    } else {
      if (isSoundPlaying(SE_UNK_c6)) {
        StopSound(SE_UNK_c6);
      }
    }
  }
  StepPaletteAnimation(131);
  StepPaletteAnimation(132);
}

static void nop_0800f9bc(struct Coord* _ UNUSED) { return; }

static void exitTwilightDesert(struct Coord* _ UNUSED) {
  RemovePaletteAnimation(131);
  RemovePaletteAnimation(132);
}

static void LayerUpdate_TwilightDesert_2(struct StageLayer* l, const struct Stage* stage) {
  if (l->phase == 0) {
    const u16 n = l->bgIdx;
    BGCNT16(n >> 4) = l->prio | l->screenBase | (BGCNT_MOSAIC | BGCNT_CHARBASE(1));
    *(u32*)gVideoRegBuffer.bgofs[n >> 4] = 0;
    CpuFastCopy(BGMAP(61), (void*)(VRAM + SCREEN_BASE_16(n >> 4)), 2048);
    l->phase++;
  }
}

void FUN_0800fa34(struct StageLayer* l, const struct Stage* stage) {
  u32* q = Malloc(0xA0 * 4);
  if (q != NULL) {
    register s32 i asm("r2");
    u32 sh;
    s32 base;
    register u32 hi asm("ip");
    gIntrManager.reservedDma0[0] = (u32)q;
    gIntrManager.reservedDma0[1] = 0x0400001C;
    gIntrManager.reservedDma0[2] = 0xA6600001;

    hi = (u16)((u32)(l->viewportCenterPixel.x << 0xc) >> 0x10);
    {
      s32 c0 = ((l->viewportCenterPixel.y + 0xa0) >> 4) + 0x10;
      s32 c;
      i = 0;
      c = (s8)c0;
      if (c <= 0x88) {
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
        } while (base + i <= 0x88);
      }
    }

    hi = (u16)((u32)(l->viewportCenterPixel.x << 0xd) >> 0x10);
    {
      u32 cu = (u8)(((l->viewportCenterPixel.y - 0xa0) >> 3) + 0x10);
      u32 t;
      s32 sum;
      if (i > 0x9f) {
        goto band3;
      }
      t = cu << 24;
      base = (s32)t >> 24;
      sum = base + i;
      asm("" : "=r"(sh) : "0"(t));
      if (sum <= 0x88) {
        s32 bc = base;
        u32 val = (0x89 << 16) - ((u32)i << 16);
        u32* p = (u32*)((i << 2) + (u32)q);
        do {
          *p++ = val;
          val += 0xFFFF0000;
          i++;
          if (i > 0x9f) {
            goto band3;
          }
        } while (bc + i <= 0x88);
      }
      if (i > 0x9f) {
        goto band3;
      }
      if (((s32)sh >> 24) + i <= 0x99) {
        u32* p = (u32*)((i << 2) + (u32)q);
        u32 val;
        base = (s32)sh >> 24;
        val = ((u32)base << 16) | hi;
        do {
          *p++ = val;
          i++;
          if (i > 0x9f) {
            goto band3;
          }
        } while (base + i <= 0x99);
      }
    }

  band3:
    hi = (u16)((u32)(l->viewportCenterPixel.x << 0xe) >> 0x10);
    {
      u32 cu = (u8)(((l->viewportCenterPixel.y - 0x140) >> 2) + 0x10);
      u32 t;
      s32 sum;
      if (i > 0x9f) {
        goto done;
      }
      t = cu << 24;
      base = (s32)t >> 24;
      sum = base + i;
      asm("" : "=r"(sh) : "0"(t));
      if (sum <= 0x98) {
        s32 bc = base;
        u32 val = (0x99 << 16) - ((u32)i << 16);
        u32* p = (u32*)((i << 2) + (u32)q);
        do {
          *p++ = val;
          val += 0xFFFF0000;
          i++;
          if (i > 0x9f) {
            goto done;
          }
        } while (bc + i <= 0x98);
      }
      if (i > 0x9f) {
        goto done;
      }
      {
        u32 val = (((s32)sh >> 8) | hi);
        u32* p = (u32*)((i << 2) + (u32)q);
        do {
          *p++ = val;
          i++;
        } while (i <= 0x9f);
      }
    }
  done:;
  }
}

INCASM("asm/stage_gfx/twilight_desert.inc");

// 0x0800FF98
void desert_0800ff98(struct StageLayer* l, const struct Stage* _ UNUSED) {
  u8 ph;
  u32 n;
  u32 c;
  u16* bg;
  ph = l->phase;
  if (ph != 0) {
    return;
  }
  n = (l->bgIdx << 16) >> 20;
  bg = &BGCNT16(n);
  c = l->prio | l->screenBase | 0x44;
  *bg = c;
  *((u32*)&gVideoRegBuffer.bgofs[n]) = ph;
  CpuFastSet(BGMAP(62), (void*)(VRAM + ((c & 0x1F00) << 3)), 0x200);
  gBlendRegBuffer.bldclt = 0x3D42;
  gWindowRegBuffer.dispcnt |= DISPCNT_WIN1_ON;
  gWindowRegBuffer.winin[1] = 0xFF;
  {
    register u8 wv asm("r1");
    register u8 kk asm("r0");
    wv = gWindowRegBuffer.winin[2];
    kk = 0xC;
    kk |= wv;
    kk &= 0xFD;
    gWindowRegBuffer.winin[2] = kk;
  }
  gWindowRegBuffer.winH.half[1] = 0xFF;
  BGnVOFS(n) = 0xFF80;
  gWindowRegBuffer.winV.half[1] = 0x80A0;
  l->phase++;
}

INCASM("asm/stage_gfx/twilight_desert_post.inc");

static void LayerExit_TwilightDesert_4(struct StageLayer* l, const struct Stage* stage) {
  gBlendRegBuffer.bldclt = 0;
  gWindowRegBuffer.dispcnt &= ~(DISPCNT_WIN1_ON);
  gWindowRegBuffer.winin[2] |= 0xE;
}

static void LayerUpdate_TwilightDesert_5(struct StageLayer* l, const struct Stage* stage) {
  if (l->phase == 0) {
    const u16 n = l->bgIdx;
    (l->scrollPower).x = 0xE0;
    (l->scroll).x = 0x3C0;
    BGCNT16(n >> 4) = (BGCNT16(n >> 4) & 0xFFFC) | 3;
    l->phase++;
  }
}

// ------------------------------------------------------------------------------------------------------------------------------------

void FUN_0800fa34(struct StageLayer* l, const struct Stage* stage);
void desert_0800fb88(struct StageLayer* l, const struct Stage* stage);
void desert_0800ff98(struct StageLayer* l, const struct Stage* stage);
void FUN_08010044(struct StageLayer* l, const struct Stage* stage);

// clang-format off
static const StageLayerRoutine sLayerRoutine[6] = {
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
      [LAYER_UPDATE] = LayerUpdate_TwilightDesert_2,
      [LAYER_DRAW]   = FUN_0800fa34,
      [LAYER_EXIT]   = NULL,
    },
    [3] = {
      [LAYER_UPDATE] = desert_0800fb88,
      [LAYER_DRAW]   = DrawGeneralStageLayer,
      [LAYER_EXIT]   = NULL,
    },
    [4] = {
      [LAYER_UPDATE] = desert_0800ff98,
      [LAYER_DRAW]   = FUN_08010044,
      [LAYER_EXIT]   = LayerExit_TwilightDesert_4,
    },
    [5] = {
      [LAYER_UPDATE] = LayerUpdate_TwilightDesert_5,
      [LAYER_DRAW]   = DrawGeneralStageLayer,
      [LAYER_EXIT]   = NULL,
    },
};
// clang-format on

// ------------------------------------------------------------------------------------------------------------------------------------

void FUN_08010188(u8 val) {
  gOverworld.work.twilightDesert.unk_000 = val;
  gOverworld.work.twilightDesert.unk_001 = 1;
}

u16 FUN_080101a8(void) { return (u16)gOverworld.work.twilightDesert.unk_001; }

extern const struct ChunkMap sChunkMap1;
INCBIN_STATIC(sChunkMap1, "data/stage/twilight_desert/layer1.bin");  // ./tools/dumper/bin.ts ./baserom.gba 0x0833ee94 0x0833f018 ./data/stage/twilight_desert/layer1.bin

extern const struct ChunkMap sChunkMap2;
INCBIN_STATIC(sChunkMap2, "data/stage/twilight_desert/layer2.bin");  // ./tools/dumper/bin.ts ./baserom.gba 0x0833f018 0x0833f19c ./data/stage/twilight_desert/layer2.bin

extern const struct ChunkMap sChunkMap3;
INCBIN_STATIC(sChunkMap3, "data/stage/twilight_desert/layer3.bin");  // ./tools/dumper/bin.ts ./baserom.gba 0x0833f19c 0x0833f320 ./data/stage/twilight_desert/layer3.bin

extern const tileset_ofs_t sTilesetOffset[];
INCBIN_STATIC(sTilesetOffset, "data/stage/twilight_desert/tileset_offset.bin");  // ./tools/dumper/bin.ts ./baserom.gba 0x0833f320 0x0833f4a4 ./data/stage/twilight_desert/tileset_offset.bin

extern const u16 sScreenBehavior[];
INCBIN_STATIC(sScreenBehavior, "data/stage/twilight_desert/screen_behavior.bin");  // ./tools/dumper/bin.ts ./baserom.gba 0x0833f4a4 0x0833f7ac ./data/stage/twilight_desert/screen_behavior.bin

const struct Stage gTwilightDesertLandscape = {
  id : STAGE_TWILIGHT_DESERT,
  fn : sStageRoutine,
  terrainHdr : &gStageTerrains[STAGE_TWILIGHT_DESERT],
  maps : {&sChunkMap1, &sChunkMap2, &sChunkMap3},
  bgIdx : {USE_BG2, USE_BG1, USE_BG3},
  prio : {2, 1, 3},
  screenBase : {BGMAP_BLOCK(2), BGMAP_BLOCK(4), BGMAP_BLOCK(6)},
  scrollPower : {{0x100, 0x100}, {0x100, 0x100}, {0x100, 0x100}},
  scroll : {{0, 0}, {0, 0}, {0, 0}},
  tilesetOffset : sTilesetOffset,
  bgFns : sLayerRoutine,
  behavior : sScreenBehavior,
  conveyor : {-PIXEL(1), PIXEL(1)},
};
