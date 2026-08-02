#include "palette_animation.h"
#include "global.h"
#include "solid.h"
#include "sound.h"
#include "overworld.h"

#define STAGE (gOverworld.work.sunkenLib)

static void initSunkenLib(struct Coord* _ UNUSED);
static void updateSunkenLib(struct Coord* _ UNUSED);
static void FUN_080136a0(struct Coord* _ UNUSED);
static void exitSunkenLibrary(struct Coord* _ UNUSED);

static const StageFunc sGfxRoutine[4] = {
    initSunkenLib,
    updateSunkenLib,
    FUN_080136a0,
    exitSunkenLibrary,
};

static void initSunkenLib(struct Coord* _ UNUSED) {
  gOverworld.state[0] = 0;
  STAGE.unk_000 = 0;
  STAGE.unk_001 = 0;
  STAGE.unk_002 = 0;
  STAGE.theta = 0;
  STAGE.rng = 0;
  SEA = PIXEL(568);
  StartPaletteAnimation(150, 0);
}

static void updateSunkenLib(struct Coord* _ UNUSED) {
  if ((TILESET_ID(0) == STAGE_SUNKEN_LIBRARY) && (TILESET_IDX(0) == 4)) {
    if (!(STAGE.unk_000 & (1 << 0))) {
      STAGE.unk_000 |= (1 << 0);
      StartPaletteAnimation(148, 0);
      StartPaletteAnimation(149, 0);
    }
    StepPaletteAnimation(148);
    StepPaletteAnimation(149);
  } else if (STAGE.unk_000 & (1 << 0)) {
    STAGE.unk_000 ^= (1 << 0);
    RemovePaletteAnimation(148);
    RemovePaletteAnimation(149);
  }

  if ((TILESET_ID(1) == STAGE_SUNKEN_LIBRARY) && (TILESET_IDX(1) == 5)) {
    if (!(STAGE.unk_000 & (1 << 1))) {
      STAGE.unk_000 |= (1 << 1);
      StartPaletteAnimation(153, 0);
    }
    StepPaletteAnimation(153);
  } else if (STAGE.unk_000 & (1 << 1)) {
    STAGE.unk_000 ^= (1 << 1);
    RemovePaletteAnimation(153);
  }

  StepPaletteAnimation(150);

  if (STAGE.unk_001 == 0) {
    if (STAGE.unk_002 == 0) {
      STAGE.unk_002 = (((STAGE.rng = LCG(STAGE.rng)) >> 16) & 1) + 1;
      STAGE.unk_001 = 8;
    } else {
      STAGE.unk_002 = 0;
      STAGE.unk_001 = ((((STAGE.rng = LCG(STAGE.rng)) >> 16) % 58) & 0xF8) + 7;
    }
  }

  STAGE.unk_001--;
  STAGE.theta++;
  SEA = (SIN(STAGE.theta >> 1) * 24) + PIXEL(568);
  gBlendRegBuffer.bldalpha = BLDALPHA_BLEND(4, 12);
}

static void FUN_080136a0(struct Coord* _ UNUSED) {
  if ((TILESET_ID(0) == STAGE_SUNKEN_LIBRARY) && (TILESET_IDX(0) == 4)) {
    if (STAGE.unk_002 != 0) {
      RequestGraphicTransfer(&(TILESETS(18, 0)[72 + (STAGE.unk_002 << 1) + (STAGE.unk_001 >> 2)]).g, (void*)0x4000);
      LoadPalette(&(TILESETS(18, 0)[72 + (STAGE.unk_002 << 1) + (STAGE.unk_001 >> 2)]).pal, 0);
    } else {
      RequestGraphicTransfer(&(TILESETS(18, 0)[72 + ((STAGE.unk_001 >> 2) & 1)]).g, (void*)0x4000);
      LoadPalette(&(TILESETS(18, 0)[72 + ((STAGE.unk_001 >> 2) & 1)]).pal, 0);
    }
  }
}

static void exitSunkenLibrary(struct Coord* _ UNUSED) {
  SEA = PIXEL(10240);
  RemovePaletteAnimation(148);
  RemovePaletteAnimation(149);
  RemovePaletteAnimation(150);
  RemovePaletteAnimation(151);
  RemovePaletteAnimation(152);
  RemovePaletteAnimation(153);
}

// ------------------------------------------------------------------------------------------------------------------------------------

static void LayerUpdate_2(struct StageLayer* l, const struct Stage* _ UNUSED);
static void FUN_08013898(struct StageLayer* l, const struct Stage* _ UNUSED);
static void FUN_08013908(struct StageLayer* l UNUSED, const struct Stage* _ UNUSED);
void sunkenlib_08013930(struct StageLayer* l, const struct Stage* stage);
void FUN_08013a98(struct StageLayer* l, const struct Stage* stage);
void FUN_08013b10(struct StageLayer* l, const struct Stage* stage);
void sunkenlib_08013b6c(struct StageLayer* l, const struct Stage* stage);
void FUN_08013bdc(struct StageLayer* l, const struct Stage* stage);
void sunkenLib_08013c0c(struct StageLayer* l, const struct Stage* stage);
void FUN_08013d38(struct StageLayer* l, const struct Stage* stage);
void FUN_08013dd4(struct StageLayer* l, const struct Stage* stage);

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
      [LAYER_UPDATE] = LayerUpdate_2,
      [LAYER_DRAW]   = FUN_08013898,
      [LAYER_EXIT]   = FUN_08013908,
    },
    [3] = {
      [LAYER_UPDATE] = sunkenlib_08013930,
      [LAYER_DRAW]   = FUN_08013a98,
      [LAYER_EXIT]   = FUN_08013b10,
    },
    [4] = {
      [LAYER_UPDATE] = sunkenlib_08013b6c,
      [LAYER_DRAW]   = FUN_08013bdc,
      [LAYER_EXIT]   = NULL,
    },
    [5] = {
      [LAYER_UPDATE] = sunkenLib_08013c0c,
      [LAYER_DRAW]   = FUN_08013d38,
      [LAYER_EXIT]   = FUN_08013dd4,
    },
};
// clang-format on

// 0x080137c0
static void LayerUpdate_2(struct StageLayer* l, const struct Stage* _ UNUSED) {
  if (l->phase == 0) {
    const u16 n = l->bgIdx;
    BGCNT16(n >> 4) = l->prio | l->screenBase | 0x8044;
    *(u32*)gVideoRegBuffer.bgofs[n >> 4] = 0;
    CpuFastCopy(BGMAP(67), (void*)(VRAM + SCREEN_BASE_16(n >> 4)), 2048);
    CpuFastCopy(BGMAP(68), (void*)(VRAM + 0x800 + SCREEN_BASE_16(n >> 4)), 2048);
    gBlendRegBuffer.bldclt = 0x3B44;
    gBlendRegBuffer.bldalpha = 0xC04;
    gWindowRegBuffer.dispcnt |= 0x4000;
    gWindowRegBuffer.winin[1] = 0xF3;
    gWindowRegBuffer.winin[2] |= 0xE;
    *((u16*)&gWindowRegBuffer.winH + 1) = 0xFF;
    l->unk_10 = 0;
    l->phase++;
  }
}

static void FUN_08013898(struct StageLayer* l, const struct Stage* _ UNUSED) {
  u16 n = l->bgIdx;
  s32 deltaPixel = ((l->viewportCenterPixel).y - (SEA >> 8)) + 5;
  if (deltaPixel > 255) {
    deltaPixel = 255;
  }
  if (deltaPixel < -255) {
    deltaPixel = -255;
  }
  if (deltaPixel < 0) {
    gWindowRegBuffer.winV.half[1] = (-deltaPixel) & 0xFF;
  } else {
    gWindowRegBuffer.winV.half[1] = 0;
  }

  BGOFS(n >> 4)->x = (l->viewportCenterPixel).x;
  gVideoRegBuffer.bgofs[n >> 4][1] = deltaPixel;
}

static void FUN_08013908(struct StageLayer* l UNUSED, const struct Stage* _ UNUSED) {
  gBlendRegBuffer.bldclt = 0;
  gWindowRegBuffer.dispcnt &= 0xBFFF;
  gWindowRegBuffer.winin[2] |= 0xE;
}

struct Entity* FUN_080d8f2c(void);
void FUN_080d8fd4(struct Entity* p);
void FUN_080d8fe4(struct Entity* p);

void sunkenlib_08013930(struct StageLayer* l, const struct Stage* stage) {
  struct Overworld* ow;
  s32 sea;
  u32 ph = l->phase;
  if (ph == 0) {
    u32 n = (u16)l->bgIdx >> 4;
    u16* bg = &BGCNT16(n);
    u32 sz;
    u32 v;
    {
      u32 sb = l->screenBase;
      register u32 k asm("r4");
      register u32 kc asm("r2");
      k = 0x8045;
      asm("" : "+r"(k));
      kc = k;
      asm("" : "+r"(kc));
      v = sb | kc;
    }
    *bg = v;
    *((u32*)&gVideoRegBuffer.bgofs[n]) = ph;
    CpuFastSet((void*)(*(s32*)0x085223B4 + 0x085223BC), (void*)(((v & 0x1F00) << 3) + VRAM), sz = 0x200);
    CpuFastSet((void*)(*(s32*)0x085223B8 + 0x085223C0), (void*)(VRAM + 0x800 + (((u32)*bg & 0x1F00) << 3)), sz);
    *(struct Entity**)((u8*)l + 0x68) = (void*)ph;
    l->unk_10 = ph;
    l->phase++;
  }
  gWindowRegBuffer.winin[1] &= 0xF7;
  if (*(struct Entity**)((u8*)l + 0x68) == NULL) {
    *(struct Entity**)((u8*)l + 0x68) = FUN_080d8f2c();
  }
  ow = &gOverworld;
  {
    register u32 so asm("r4");
    so = 0x2C00C;
    sea = ow->sea;
    asm volatile("" :: "r"(so));
  }
  if (sea <= 0x227FF) {
    s32 t = l->unk_10 + 1;
    u32 one;
    l->unk_10 = t;
    if ((u16)t > 0x13) {
      l->unk_10 = 4;
    }
    FUN_080d8fd4(*(struct Entity**)((u8*)l + 0x68));
    {
      s32 sid = 0x124;
      if (!isSoundPlaying(sid)) {
        PlaySound(sid);
      }
    }
    {
      u32 w = l->unk_10;
      register u32 res asm("r0");
      one = 1;
      asm("" : "+r"(one));
      res = one;
      asm volatile("" : "+r"(res));
      res &= w;
      if (res == 0) {
        goto tail;
      }
    }
    {
      u32* rp = (u32*)((u8*)ow + 0x2D02C);
      u32 r = *rp * 0x343FD + 0x269EC3;
      u32 sl = r << 1;
      *rp = sl >> 1;
      if ((sl >> 0x11) & one) {
        gBlendRegBuffer.bldalpha = 0xC0A;
        return;
      }
    }
  tail:;
  } else {
    s32 sid;
    l->unk_10 = 3;
    FUN_080d8fe4(*(struct Entity**)((u8*)l + 0x68));
    sid = 0x124;
    if (isSoundPlaying(sid)) {
      StopSound(sid);
    }
  }
  gBlendRegBuffer.bldalpha = 0xC04;
}

#undef STAGE

// One pool apart: retail keeps &gStageTilesetOffsets[18] twice — once as the
// relocated symbol for the deref, once as the raw address for the
// SELF_REL_PTR addend — where agbcc folds the two link constants together.
NON_MATCH void FUN_08013a98(struct StageLayer* l, const struct Stage* stage) {
#if MODERN
  u16 b = l->bgIdx;
  s32 vy = l->viewportCenterPixel.y - (SEA >> 8) + 5;
  BGnHOFS(b >> 4) = l->viewportCenterPixel.x;
  BGnVOFS(b >> 4) = vy;
  RequestGraphicTransfer(&(TILESETS(18, 0)[(u16)l->unk_10 >> 2]).g, (void*)0x4000);
  LoadPalette(&(TILESETS(18, 0)[(u16)l->unk_10 >> 2]).pal, 0);
#else
  INCCODE("asm/stage_gfx/sunkenlib_13a98.inc");
#endif
}

// 0x08013B10
void FUN_08013b10(struct StageLayer* l, const struct Stage* stage) {
  struct Solid* p = *(struct Solid**)&(l->work);
  if (p != NULL) {
    register u8* q asm("r0");
    u8 fl;
    u32 z;
    fl = (p->s).flags & 0xFE;
    z = 0;
    fl &= 0xFD;
    (p->s).flags = fl;
    q = (u8*)p + 0x8c;
    *(u32*)q = z;
    asm volatile("add %0, #4" : "+r"(q));
    *(u32*)q = z;
    asm volatile("add %0, #4" : "+r"(q));
    *q = z;
    (p->s).flags &= 0xFB;
    SET_SOLID_ROUTINE(p, 3);
  }
  if (isSoundPlaying(0x124)) {
    StopSound(0x124);
  }
}

void sunkenlib_08013b6c(struct StageLayer* l0, const struct Stage* stage) {
  register struct StageLayer* l asm("r5") = l0;
  register s32 ph asm("r6");
  register u16* vb asm("r4");
  ph = l->phase;
  if (ph == 0) {
    register u32 n asm("r0");
    register u16* pc asm("r3");
    u32 c;
    register u32 sh2 asm("r3");
    n = (l->bgIdx << 16) >> 20;
    sh2 = n << 1;
    vb = (u16*)&gVideoRegBuffer.bgcnt[0];
    pc = (u16*)(sh2 + (u32)vb);
    c = l->prio | l->screenBase | 0x44;
    *pc = c;
    *(u32*)((n << 2) + (u32)(vb += 4)) = ph;
    CpuFastSet((void*)(*(s32*)0x085223BC + 0x085223C4), (void*)(VRAM + ((c & 0x1F00) << 3)), 0x200);
    l->phase++;
  }
  gWindowRegBuffer.winin[1] |= 8;
}

// 0x08013bdc
void FUN_08013bdc(struct StageLayer* l, const struct Stage* _ UNUSED) {
  const u16 n = l->bgIdx;
  BGnHOFS(n >> 4) = (l->viewportCenterPixel.x * 3) >> 2;
  BGnVOFS(n >> 4) = (l->viewportCenterPixel.y * 3) >> 2;
}

INCASM("asm/stage_gfx/sunken_library_b.inc");

void FUN_08013dd4(struct StageLayer* l, const struct Stage* stage) {
  s32 i;
  for (i = 0; i < 4; i++) {
    struct Entity* e = (*(struct Entity* (*)[4]) & (l->work))[i];
    if (e != NULL) {
      u8 fl = e->flags & ~DISPLAY;
      e->flags = fl & ~FLIPABLE;
      (((struct Solid*)e)->body).status = 0;
      (((struct Solid*)e)->body).prevStatus = 0;
      (((struct Solid*)e)->body).invincibleTime = 0;
      e->flags &= ~COLLIDABLE;
      SET_SOLID_ROUTINE(e, ENTITY_DISAPPEAR);
    }
  }
  if (isSoundPlaying(0x124)) {
    StopSound(0x124);
  }
}

// ------------------------------------------------------------------------------------------------------------------------------------

extern const struct ChunkMap sChunkMap1;
INCBIN_STATIC(sChunkMap1, "data/stage/sunken_library/layer1.bin");  // ./tools/dumper/bin.ts ./baserom.gba 0x08343fc8 0x083440ec ./data/stage/sunken_library/layer1.bin

extern const struct ChunkMap sChunkMap2;
INCBIN_STATIC(sChunkMap2, "data/stage/sunken_library/layer2.bin");  // ./tools/dumper/bin.ts ./baserom.gba 0x083440ec 0x08344210 ./data/stage/sunken_library/layer2.bin

extern const struct ChunkMap sChunkMap3;
INCBIN_STATIC(sChunkMap3, "data/stage/sunken_library/layer3.bin");  // ./tools/dumper/bin.ts ./baserom.gba 0x08344210 0x08344334 ./data/stage/sunken_library/layer3.bin

extern const tileset_ofs_t sTilesetOffset[];
INCBIN_STATIC(sTilesetOffset, "data/stage/sunken_library/tileset_offset.bin");  // ./tools/dumper/bin.ts ./baserom.gba 0x08344334 0x08344458 ./data/stage/sunken_library/tileset_offset.bin

extern const u16 sScreenBehavior[];
INCBIN_STATIC(sScreenBehavior, "data/stage/sunken_library/screen_behavior.bin");  // ./tools/dumper/bin.ts ./baserom.gba 0x08344458 0x083446a0 ./data/stage/sunken_library/screen_behavior.bin

const struct Stage gSunkenLibraryLandscape = {
  id : STAGE_SUNKEN_LIBRARY,
  fn : sGfxRoutine,
  terrainHdr : &gStageTerrains[STAGE_SUNKEN_LIBRARY],
  maps : {&sChunkMap1, &sChunkMap2, &sChunkMap3},
  bgIdx : {USE_BG1, USE_BG2, USE_BG3},
  prio : {2, 0, 3},
  screenBase : {BGMAP_BLOCK(2), BGMAP_BLOCK(4), BGMAP_BLOCK(6)},
  scrollPower : {{0x100, 0x100}, {0x100, 0x100}, {0x100, 0x100}},
  scroll : {{0, 0}, {0, 0}, {0, 0}},
  tilesetOffset : sTilesetOffset,
  bgFns : sLayerRoutine,
  behavior : sScreenBehavior,
  conveyor : {0x0, 0x0},
};
