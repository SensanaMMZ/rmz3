#include "gfx.h"
#include "global.h"
#include "overworld.h"
#include "system.h"

extern const struct Coord gSnowyPlainMetatileShift1;
extern const struct Coord gSnowyPlainMetatileShift2;

static void initSnowyPlains(struct Coord* _ UNUSED);
static void nop_08012b18(struct Coord* _ UNUSED);
static void nop_08012b1c(struct Coord* _ UNUSED);
static void nop_08012b20(struct Coord* _ UNUSED);

static const StageFunc sStageRoutine[4] = {
    initSnowyPlains,
    nop_08012b18,
    nop_08012b1c,
    nop_08012b20,
};

static void initSnowyPlains(struct Coord* _ UNUSED) {
  struct Coord shift1, shift2;
  shift1 = gSnowyPlainMetatileShift1;
  shift2 = gSnowyPlainMetatileShift2;
  ShiftMetatile(0, 0x51, (struct MetatileShift*)&shift1);
  ShiftMetatile(0xf0, 0x6f, (struct MetatileShift*)&shift2);
}

static void nop_08012b18(struct Coord* _ UNUSED) { return; }

static void nop_08012b1c(struct Coord* _ UNUSED) { return; }

static void nop_08012b20(struct Coord* _ UNUSED) { return; }

// ------------------------------------------------------------------------------------------------------------------------------------

static void LayerUpdate_2(struct StageLayer* l, const struct Stage* _ UNUSED);
static void LayerUpdate_3(struct StageLayer* l, const struct Stage* _ UNUSED);
void snowyPlains_08012b9c(struct StageLayer* l, const struct Stage* stage);
void FUN_08012bfc(struct StageLayer* l, const struct Stage* stage);
void snowyPlains_08012fec(struct StageLayer* l, const struct Stage* stage);
void FUN_0801304c(struct StageLayer* l, const struct Stage* stage);
void snowyplains_0801320c(struct StageLayer* l, const struct Stage* stage);
void snowyplains_0801326c(struct StageLayer* l, const struct Stage* stage);
void snowyplains_080133b4(struct StageLayer* l, const struct Stage* stage);

// clang-format off
static const StageLayerRoutine sLayerRoutine[8] = {
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
    [4] = {
      [LAYER_UPDATE] = snowyPlains_08012b9c,
      [LAYER_DRAW]   = FUN_08012bfc,
      [LAYER_EXIT]   = NULL,
    },
    [5] = {
      [LAYER_UPDATE] = snowyPlains_08012fec,
      [LAYER_DRAW]   = FUN_0801304c,
      [LAYER_EXIT]   = NULL,
    },
    [6] = {
      [LAYER_UPDATE] = snowyplains_0801320c,
      [LAYER_DRAW]   = snowyplains_0801326c,
      [LAYER_EXIT]   = NULL,
    },
    [7] = {
      [LAYER_UPDATE] = snowyplains_080133b4,
      [LAYER_DRAW]   = DrawGeneralStageLayer,
      [LAYER_EXIT]   = NULL,
    },
};
// clang-format on

static void LayerUpdate_2(struct StageLayer* l, const struct Stage* _ UNUSED) {
  if (l->phase == 0) {
    const u16 n = l->bgIdx;
    BGCNT16(n >> 4) = (BGCNT16(n >> 4) & 0xFFFC) | 3;
    l->phase++;
  }
}

static void LayerUpdate_3(struct StageLayer* l, const struct Stage* _ UNUSED) {
  if (l->phase == 0) {
    const u16 n = l->bgIdx;
    BGCNT16(n >> 4) = (BGCNT16(n >> 4) & 0xFFFC) | 3;
    (l->scrollPower).x = 0x60;
    (l->scrollPower).y = 0x60;
    (l->scroll).x = 0x96;
    (l->scroll).y = 0x64;
    l->phase++;
  }
}

void snowyPlains_08012b9c(struct StageLayer* l, const struct Stage* stage) {
  if (l->phase == 0) {
    const u16 n = l->bgIdx;
    BGCNT16(n >> 4) = l->prio | l->screenBase | (BGCNT_MOSAIC | BGCNT_CHARBASE(1));
    *(u32*)gVideoRegBuffer.bgofs[n >> 4] = 0;
    CpuFastCopy(BGMAP(78), (void*)(VRAM + SCREEN_BASE_16(n >> 4)), 2048);
    l->phase++;
  }
}

INCASM("asm/stage_gfx/snowy_plains_a.inc");

void snowyPlains_08012fec(struct StageLayer* l, const struct Stage* stage) {
  if (l->phase == 0) {
    const u16 n = l->bgIdx;
    BGCNT16(n >> 4) = l->prio | l->screenBase | (BGCNT_MOSAIC | BGCNT_CHARBASE(1));
    *(u32*)gVideoRegBuffer.bgofs[n >> 4] = 0;
    CpuFastCopy(BGMAP(77), (void*)(VRAM + SCREEN_BASE_16(n >> 4)), 2048);
    l->phase++;
  }
}

INCASM("asm/stage_gfx/snowy_plains_b.inc");

void snowyplains_0801320c(struct StageLayer* l, const struct Stage* stage) {
  if (l->phase == 0) {
    const u16 n = l->bgIdx;
    BGCNT16(n >> 4) = l->prio | l->screenBase | (BGCNT_MOSAIC | BGCNT_CHARBASE(1));
    *(u32*)gVideoRegBuffer.bgofs[n >> 4] = 0;
    CpuFastCopy(BGMAP(77), (void*)(VRAM + SCREEN_BASE_16(n >> 4)), 2048);
    l->phase++;
  }
}

// 0x0801326C
void snowyplains_0801326c(struct StageLayer* l, const struct Stage* stage UNUSED) {
  register struct StageLayer* lv asm("r8");
  register s32 i asm("r4");
  register u32 hi asm("r5");
  register u32 cu asm("ip");
  u32* q;
  s32 base;
  lv = l;
  i = 0x9f;
  q = Malloc(0xA0 * 4);
  if (q == NULL) {
    return;
  }
  gIntrManager.reservedDma0[0] = (u32)q;
  gIntrManager.reservedDma0[1] = 0x0400001C;
  gIntrManager.reservedDma0[2] = 0xA6600001;
  {
    register struct StageLayer* lp asm("r1");
    register s32 t asm("r0");
    u32 tt;
    lp = lv;
    t = lp->viewportCenterPixel.x;
    hi = (u32)(t << 0xe) >> 0x10;
    t = lp->viewportCenterPixel.y;
    {
      register s32 k asm("r2");
      k = 0xFFFFFCE0;
      asm("" : "+r"(k));
      t += k;
    }
    t >>= 5;
    t -= 0x20;
    tt = (u32)t << 16;
    cu = tt >> 16;
    {
      register s32 b0 asm("r1");
      b0 = (s32)tt >> 16;
      if (b0 + 0x9f > 0x4f) {
      register s32 bc asm("r3");
      register u32 val asm("r2");
      register u32* p asm("r1");
      s32 st;
      bc = b0;
      val = 0xFFB00000;
      p = (u32*)((u32)q + 0x9f * 4);
      st = 0x80 << 9;
      do {
        *p = val;
        val += st;
        p--;
        i--;
        if (i < 0) {
          goto b2;
        }
      } while (bc + i > 0x4f);
      }
    }
  }
  if (i < 0) {
    goto b2;
  }
  {
    register s32 b asm("r2");
    {
      register u32 tv asm("r0");
      asm volatile("mov r1, %1\n\tlsl %0, r1, #0x10" : "=l"(tv) : "r"(cu) : "r1");
      b = (s32)tv >> 16;
    }
    if (b + i > 0x2f) {
      register u32* p asm("r1");
      register s32 bc asm("r3");
      register u32 val asm("r2");
      {
        register u32 o asm("r0");
        o = i << 2;
        p = (u32*)(o + (u32)q);
      }
      bc = b;
      val = (u32)bc << 16;
      val |= hi;
      do {
        *p = val;
        p--;
        i--;
        if (i < 0) {
          goto b2;
        }
      } while (bc + i > 0x2f);
    }
  }
b2:
  {
    register struct StageLayer* lp2 asm("r2");
    register u32 tx asm("r0");
    lp2 = lv;
    tx = lp2->viewportCenterPixel.x;
    tx <<= 0xd;
    hi = tx >> 0x10;
  }
  if (i < 0) {
    goto b3;
  }
  {
    register s32 b asm("r2");
    {
      register u32 tv asm("r0");
      asm volatile("mov r1, %1\n\tlsl %0, r1, #0x10" : "=l"(tv) : "r"(cu) : "r1");
      b = (s32)tv >> 16;
    }
    if (b + i > 0x27) {
      register u32* p asm("r1");
      register s32 bc asm("r3");
      register u32 val asm("r2");
      {
        register u32 o asm("r0");
        o = i << 2;
        p = (u32*)(o + (u32)q);
      }
      bc = b;
      val = (u32)bc << 16;
      val |= hi;
      do {
        *p = val;
        p--;
        i--;
        if (i < 0) {
          goto b3;
        }
      } while (bc + i > 0x27);
    }
  }
b3:
  {
    register struct StageLayer* lp2 asm("r2");
    register u32 tx asm("r0");
    lp2 = lv;
    tx = lp2->viewportCenterPixel.x;
    tx <<= 0xc;
    hi = tx >> 0x10;
  }
  if (i < 0) {
    return;
  }
  {
    register s32 b asm("r2");
    {
      register u32 tv asm("r0");
      asm volatile("mov r1, %1\n\tlsl %0, r1, #0x10" : "=l"(tv) : "r"(cu) : "r1");
      b = (s32)tv >> 16;
    }
    if (b + i > 0x1f) {
      register u32* p asm("r1");
      register s32 bc asm("r3");
      register u32 val asm("r2");
      {
        register u32 o asm("r0");
        o = i << 2;
        p = (u32*)(o + (u32)q);
      }
      bc = b;
      val = (u32)bc << 16;
      val |= hi;
      do {
        *p = val;
        p--;
        i--;
        if (i < 0) {
          return;
        }
      } while (bc + i > 0x1f);
    }
  }
  if (i < 0) {
    return;
  }
  {
    register u32 val asm("r1");
    u32* p;
    s32 st;
    {
      register u32 nv asm("r0");
      register u32 kk asm("r2");
      nv = (u32)i << 16;
      nv = -nv;
      asm("" : "+r"(nv));
      kk = 0x80 << 0xd;
      val = nv + kk;
    }
    p = (u32*)((i << 2) + (u32)q);
    st = 0x80 << 9;
    do {
      *p = val;
      val += st;
      p--;
      i--;
    } while (i >= 0);
  }
}


// 0x080133b4
void snowyplains_080133b4(struct StageLayer* l, const struct Stage* _ UNUSED) {
  if (l->phase == 0) {
    const u16 n = l->bgIdx;
    BGCNT16(n >> 4) = (BGCNT16(n >> 4) & 0xFFFC) | 3;
    l->phase++;
  }
}

extern const struct MetatilePatch MetatilePatch_08343f50;
extern const struct MetatilePatch MetatilePatch_08343f58;
extern const struct MetatilePatch MetatilePatch_08343f60;
extern const struct MetatilePatch MetatilePatch_08343f68;

// 0x080133E8
NON_MATCH void FUN_080133e8(struct Coord* c) {
#if MODERN
  struct MetatilePatch* q;
  register s32 x asm("r5");
  register s32 y asm("r6");
  x = (c->x - 0x800) >> 12;
  y = (c->y + 0x800) >> 12;
  if (x == 0x18B) {
    q = (struct MetatilePatch*)&MetatilePatch_08343f58;
    asm("" : "+r"(q) : "r"(x));
  } else if (x == 0x193) {
    q = (struct MetatilePatch*)&MetatilePatch_08343f58;
    asm("" : "+r"(q) : "r"(y));
  } else if (x == 0x1AB) {
    q = (struct MetatilePatch*)&MetatilePatch_08343f60;
  } else if (x == 0x1B9) {
    q = (struct MetatilePatch*)&MetatilePatch_08343f68;
  } else {
    q = (struct MetatilePatch*)&MetatilePatch_08343f50;
    PatchMetatileMap(x, y, q);
    PatchMetatileMap(x, y + 1, q);
    return;
  }
  PatchMetatileMap(x, y, q);
  PatchMetatileMap(x, y + 1, q);
#else
  INCCODE("asm/stage_gfx/snowy_080133e8.inc");
#endif
}

// ------------------------------------------------------------------------------------------------------------------------------------

extern const struct ChunkMap sChunkMap1;
INCBIN_STATIC(sChunkMap1, "data/stage/snowy_plains/layer1.bin");  // ./tools/dumper/bin.ts ./baserom.gba 0x083428b8 0x08342abc ./data/stage/snowy_plains/layer1.bin

extern const struct ChunkMap sChunkMap2;
INCBIN_STATIC(sChunkMap2, "data/stage/snowy_plains/layer2.bin");  // ./tools/dumper/bin.ts ./baserom.gba 0x08342abc 0x08342ec0 ./data/stage/snowy_plains/layer2.bin

extern const struct ChunkMap sChunkMap3;
INCBIN_STATIC(sChunkMap3, "data/stage/snowy_plains/layer3.bin");  // ./tools/dumper/bin.ts ./baserom.gba 0x08342ec0 0x083432c4 ./data/stage/snowy_plains/layer3.bin

extern const tileset_ofs_t sTilesetOffset[];
INCBIN_STATIC(sTilesetOffset, "data/stage/snowy_plains/tileset_offset.bin");  // ./tools/dumper/bin.ts ./baserom.gba 0x083432c4 0x083436c8 ./data/stage/snowy_plains/tileset_offset.bin

extern const u16 sScreenBehavior[];
INCBIN_STATIC(sScreenBehavior, "data/stage/snowy_plains/screen_behavior.bin");  // ./tools/dumper/bin.ts ./baserom.gba 0x083436c8 0x08343ed0 ./data/stage/snowy_plains/screen_behavior.bin

const struct Stage gSnowyPlainsLandscape = {
  id : STAGE_SNOWY_PLAINS,
  fn : sStageRoutine,
  terrainHdr : &gStageTerrains[STAGE_SNOWY_PLAINS],
  maps : {&sChunkMap1, &sChunkMap2, &sChunkMap3},
  bgIdx : {USE_BG2, USE_BG1, USE_BG3},
  prio : {2, 1, 3},
  screenBase : {BGMAP_BLOCK(2), BGMAP_BLOCK(4), BGMAP_BLOCK(6)},
  scrollPower : {{0x100, 0x100}, {0x100, 0x100}, {0x100, 0x100}},
  scroll : {{0, 0}, {0, 0}, {0, 0}},
  tilesetOffset : sTilesetOffset,
  bgFns : sLayerRoutine,
  behavior : sScreenBehavior,
  conveyor : {0x0, 0x0},
};

const struct MetatilePatch MetatilePatch_08343f50 = {w : 2, h : 1};
const metatile_id_t MetatilePatchData_08343f50[2] = {0x0, 0x0};

const struct MetatilePatch MetatilePatch_08343f58 = {w : 2, h : 1};
const metatile_id_t MetatilePatchData_08343f58[2] = {0x0, 0x217};

const struct MetatilePatch MetatilePatch_08343f60 = {w : 2, h : 1};
const metatile_id_t MetatilePatchData_08343f60[2] = {0x1D2, 0x1D3};

const struct MetatilePatch MetatilePatch_08343f68 = {w : 2, h : 1};
const metatile_id_t MetatilePatchData_08343f68[2] = {0x217, 0x0};
