#include "palette_animation.h"
#include "global.h"
#include "solid.h"
#include "sound.h"
#include "gpu_regs.h"
#include "overworld.h"
#include "system.h"
#include "trig.h"
#include "definition.h"

#define STAGE (gOverworld.work.weilLabo)

static void initWeilLabo(struct Coord* _ UNUSED);
static void FUN_08015010(struct Coord* _ UNUSED);
static void nop_08015244(struct Coord* _ UNUSED);
static void exitWeilLabo(struct Coord* _ UNUSED);

static const StageFunc sStageRoutine[4] = {
    initWeilLabo,
    FUN_08015010,
    nop_08015244,
    exitWeilLabo,
};

static void initWeilLabo(struct Coord* _ UNUSED) {
  STAGE.unk_000 = 0;
  gOverworld.state[2] = 0;
  gOverworld.state[3] = 0;
  gOverworld.state[0] = 0;
  gOverworld.state[1] = 0;
  STAGE.unk_00c = 0;
  STAGE.unk_010.x = PIXEL(7632);
  STAGE.unk_010.y = PIXEL(1360);
  STAGE.unk_018 = 0;
  STAGE.unk_01c = 0;
  STAGE.unk_020 = 0;
  STAGE.unk_024.x = PIXEL(7632);
  STAGE.unk_024.y = PIXEL(1360);
  STAGE.unk_02c.x = PIXEL(7632);
  STAGE.unk_02c.y = PIXEL(1360);
  STAGE.unk_008 = 0;
}

static void FUN_08015010(struct Coord* _ UNUSED) {
  if ((TILESET_ID(0) == STAGE_WEILS_LABO) && (TILESET_IDX(0) == 0) && (gOverworld.state[0] == 0)) {
    if ((STAGE.unk_000 & (1 << 0)) == 0) {
      STAGE.unk_000 |= (1 << 0);
      StartPaletteAnimation(259, 0);
      StartPaletteAnimation(260, 0);
      StartPaletteAnimation(261, 0);
      StartPaletteAnimation(262, 0);
    }
    StepPaletteAnimation(259);
    StepPaletteAnimation(260);
    StepPaletteAnimation(261);
    StepPaletteAnimation(262);
  } else if (STAGE.unk_000 & (1 << 0)) {
    STAGE.unk_000 ^= (1 << 0);
    RemovePaletteAnimation(259);
    RemovePaletteAnimation(260);
    RemovePaletteAnimation(261);
    RemovePaletteAnimation(262);
  }

  if ((TILESET_ID(1) == STAGE_WEILS_LABO) && (TILESET_IDX(1) == 1)) {
    if ((STAGE.unk_000 & (1 << 1)) == 0) {
      STAGE.unk_000 |= (1 << 1);
      StartPaletteAnimation(263, 0);
      StartPaletteAnimation(264, 0);
      StartPaletteAnimation(265, 0);
      StartPaletteAnimation(266, 0);
    }
    StepPaletteAnimation(263);
    StepPaletteAnimation(264);
    StepPaletteAnimation(265);
    StepPaletteAnimation(266);
  } else if (STAGE.unk_000 & (1 << 1)) {
    STAGE.unk_000 ^= (1 << 1);
    RemovePaletteAnimation(263);
    RemovePaletteAnimation(264);
    RemovePaletteAnimation(265);
    RemovePaletteAnimation(266);
  }

  if ((TILESET_ID(1) == STAGE_WEILS_LABO) && (TILESET_IDX(1) == 3) && (gOverworld.state[0] == 0)) {
    if ((STAGE.unk_000 & (1 << 2)) == 0) {
      STAGE.unk_000 |= (1 << 2);
      StartPaletteAnimation(267, 0);
      StartPaletteAnimation(268, 0);
    }
    StepPaletteAnimation(267);
    StepPaletteAnimation(268);
  } else if (STAGE.unk_000 & (1 << 2)) {
    STAGE.unk_000 ^= (1 << 2);
    RemovePaletteAnimation(267);
    RemovePaletteAnimation(268);
  }

  STAGE.unk_008++;
}

static void nop_08015244(struct Coord* _ UNUSED) { return; }

static void exitWeilLabo(struct Coord* _ UNUSED) {
  RemovePaletteAnimation(259);
  RemovePaletteAnimation(260);
  RemovePaletteAnimation(261);
  RemovePaletteAnimation(262);
  RemovePaletteAnimation(263);
  RemovePaletteAnimation(264);
  RemovePaletteAnimation(265);
  RemovePaletteAnimation(266);
  RemovePaletteAnimation(267);
  RemovePaletteAnimation(268);
  RemovePaletteAnimation(269);
  RemovePaletteAnimation(270);
}

// ------------------------------------------------------------------------------------------------------------------------------------

static void LayerUpdate_2(struct StageLayer* l, const struct Stage* _ UNUSED);
static void LayerExit_2(struct StageLayer* l UNUSED, const struct Stage* _ UNUSED);
static void FUN_08015378(struct StageLayer* l, const struct Stage* _ UNUSED);
static void FUN_08015390(struct StageLayer* l, const struct Stage* _ UNUSED);
static void FUN_080153cc(struct StageLayer* l, const struct Stage* _ UNUSED);
void FUN_080153e8(struct StageLayer* l, const struct Stage* stage);
void FUN_08015510(struct StageLayer* l, const struct Stage* stage);
void weilLabo_08015564(struct StageLayer* l, const struct Stage* stage);
void weilLabo_08015710(struct StageLayer* l, const struct Stage* stage);
void FUN_080157b0(struct StageLayer* l, const struct Stage* stage);
void weilLabo_080158a4(struct StageLayer* l, const struct Stage* stage);
void FUN_08015c40(struct StageLayer* l, const struct Stage* stage);
void FUN_08015c5c(struct StageLayer* l, const struct Stage* stage);
void FUN_08015cf0(struct StageLayer* l, const struct Stage* stage);
void weillabo_08015e34(struct StageLayer* l, const struct Stage* stage);
void FUN_08015f7c(struct StageLayer* l, const struct Stage* stage);
void FUN_08016018(struct StageLayer* l, const struct Stage* stage);

// clang-format off
static const StageLayerRoutine sLayerRoutine[11] = {
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
      [LAYER_EXIT]   = LayerExit_2,
    },
    [3] = {
      [LAYER_UPDATE] = FUN_08015378,
      [LAYER_DRAW]   = DrawGeneralStageLayer,
      [LAYER_EXIT]   = NULL,
    },
    [4] = {
      [LAYER_UPDATE] = FUN_08015390,
      [LAYER_DRAW]   = DrawGeneralStageLayer,
      [LAYER_EXIT]   = NULL,
    },
    [5] = {
      [LAYER_UPDATE] = FUN_080153cc,
      [LAYER_DRAW]   = FUN_080153e8,
      [LAYER_EXIT]   = NULL,
    },
    [6] = {
      [LAYER_UPDATE] = FUN_08015510,
      [LAYER_DRAW]   = DrawGeneralStageLayer,
      [LAYER_EXIT]   = NULL,
    },
    [7] = {
      [LAYER_UPDATE] = weilLabo_08015564,
      [LAYER_DRAW]   = weilLabo_08015710,
      [LAYER_EXIT]   = NULL,
    },
    [8] = {
      [LAYER_UPDATE] = FUN_080157b0,
      [LAYER_DRAW]   = weilLabo_080158a4,
      [LAYER_EXIT]   = FUN_08015c40,
    },
    [9] = {
      [LAYER_UPDATE] = FUN_08015c5c,
      [LAYER_DRAW]   = FUN_08015cf0,
      [LAYER_EXIT]   = NULL,
    },
    [10] = {
      [LAYER_UPDATE] = weillabo_08015e34,
      [LAYER_DRAW]   = FUN_08015f7c,
      [LAYER_EXIT]   = FUN_08016018,
    },
};
// clang-format on

// 0x080152bc
static void LayerUpdate_2(struct StageLayer* l, const struct Stage* _ UNUSED) {
#if MODERN == 0
  register u16 tmp asm("r1");
  register s32 sin asm("r1");
  register s32 scy asm("r0");
#else
  u16 sin;
#endif

  if (l->phase == 0) {
    const u16 n = l->bgIdx;
    BGCNT16(n >> 4) &= 0xFFFC;
    BGCNT16(n >> 4) |= 1;
    gBlendRegBuffer.bldclt = 0x3B44;
    gBlendRegBuffer.bldalpha = 0xC04;
    SEA = PIXEL(832);
    StartPaletteAnimation(234, 192);
    l->unk_10 = 0;
    l->phase++;
  }

  l->unk_10++;
#if MODERN == 0
  tmp = SIN(l->unk_10);
  sin = ((s32)tmp << 16) >> 22;
  scy = -27 - sin;
  (l->scroll).y = scy;
#else
  sin = SIN(l->unk_10);
  (l->scroll).y = -27 - (((s16)sin) >> 6);
#endif
  StepPaletteAnimation(234);
}

// 0x0801534c
static void LayerExit_2(struct StageLayer* l UNUSED, const struct Stage* _ UNUSED) {
  RemovePaletteAnimation(234);
  gBlendRegBuffer.bldclt = 0;
  SEA = MAX_Y;
}

// 0x08015378
static void FUN_08015378(struct StageLayer* l, const struct Stage* _ UNUSED) {
  if (l->phase == 0) {
    (l->scrollPower).x = 0;
    (l->scrollPower).y = 0;
    l->phase++;
  }
}

// 0x08015390
static void FUN_08015390(struct StageLayer* l, const struct Stage* _ UNUSED) {
  if (l->phase == 0) {
    (l->scrollPower).x = 0xC0;
    (l->scrollPower).y = 0xC0;
    if ((l->viewportCenterPixel).x < 5760) {
      (l->scroll).x = 840;
    } else {
      (l->scroll).x = 1500;
    }
    (l->scroll).y = 40;
    l->phase++;
  }
}

static void FUN_080153cc(struct StageLayer* l, const struct Stage* _ UNUSED) {
  if (l->phase == 0) {
    l->unk_10 = 0;
    l->phase++;
  }
  l->unk_10++;
}

/* Draws the layer, then builds a 0xA0-entry HDMA table at gIntrManager.reservedDma0
   feeding BG3HOFS/BG3VOFS (0x0400001C): rows 0x00-0x0F copy the current bgofs pair,
   rows 0x10-0x5F apply a two-sine horizontal wave + vertical offset, rows 0x60-0x9F
   copy the pair again. Parked: register-orchestration tie - retail wants cur/n/tbl
   spilled at sp0/sp4/sp8 with buf=r7, d2=sl, tbl=r2 reloaded around __divsi3; every
   pin combination that fixes one home evicts another (the buf pin is silently
   dropped once tbl/d2 are pinned). Logic verified against the asm; all remaining
   diffs are allocation artifacts. */
NON_MATCH void FUN_080153e8(struct StageLayer* l, const struct Stage* stage) {
#if MODERN
  u32 b = l->bgIdx << 16;
  u32 cur;
  u32 n;
  s32 i;
  u32* buf;
  u32* hp;
  u16 vofs;
  DrawGeneralStageLayer(l, stage);
  {
    u32 n1 = (b >> 20) << 2;
    hp = (u32*)((u8*)gVideoRegBuffer.bgofs + n1);
    cur = *(u16*)hp;
    vofs = *(u16*)((u8*)gVideoRegBuffer.bgofs + 2 + n1) + 2;
  }
  buf = Malloc(0xA0 * 4);
  if (buf == NULL) {
    return;
  }
  gIntrManager.reservedDma0[0] = (u32)buf;
  gIntrManager.reservedDma0[1] = 0x0400001C;
  gIntrManager.reservedDma0[2] = 0xA6600001;
  n = b >> 20;
  {
    vu32* src = (vu32*)hp;
    u32* d = buf;
    for (i = 0xF; i >= 0; i--) {
      *d++ = *src;
    }
  }
  {
    const s16* tbl = gSineTable;
    u32 e = vofs + 0x80;
    u32* d2 = buf + 0x10;
    for (i = 0x10; i <= 0x5F; i++) {
      u16 w = l->unk_10;
      s32 acc = tbl[(u8)(w * 3)] * 3;
      acc += tbl[(e + w * 4) & 0x7F] * 2;
      acc >>= 8;
      acc += 4;
      acc += vofs;
      acc <<= 16;
      acc |= (cur + (s16)(tbl[(u8)(w + i * 2)] / 0x13)) & 0xFFFF;
      *d2++ = acc;
      e += 8;
    }
  }
  {
    vu32* src2 = (vu32*)((u8*)gVideoRegBuffer.bgofs + n * 4);
    u32* d3 = (u32*)((u8*)buf + i * 4);
    for (; i <= 0x9F; i++) {
      *d3++ = *src2;
    }
  }
#else
  INCCODE("asm/stage_gfx/weil_labo_153e8.inc");
#endif
}

void FUN_08015510(struct StageLayer* l, const struct Stage* stage) {
  if (l->phase == 0) {
    const u16 n = (l->bgIdx << 16) >> 20;
    BGCNT16(n) = (BGCNT16(n) & 0xFFFC) | 1;
    l->scroll.y = -0x140;
    l->phase++;
  }
  if (gOverworld.state[3] > 0x63) {
    l->scroll.y = 0;
  }
}

INCASM("asm/stage_gfx/weil_labo_p1_p1b.inc");

// 0x08015710
void weilLabo_08015710(struct StageLayer* l, const struct Stage* stage) {
  if (gOverworld.state[0] == 0) {
    DrawGeneralStageLayer(l, stage);
  } else if (gOverworld.terrain.reload_graphic) {
    CpuFastSet(BGMAP(76), gOverworld.bgmap, 0x200);
    LoadGraphic((void*)&(TILESETS(16, 4)[0]).g, (void*)0x4000);
    LoadPalette(&(TILESETS(16, 4)[0]).pal, 0);
    LoadGraphic((void*)&(TILESETS(16, 5)[0]).g, (void*)0x4000);
    LoadPalette(&(TILESETS(16, 5)[0]).pal, 0);
  }
}

s32 RequestType2Transfer(void* src, void* dst, s32 r2);

// 0x080157B0
// Blocker: retail parks the u16 bgIdx copy in r8 (mov r8, r1) because its
// four low callee-saved registers are all busy; agbcc has spare low
// registers and keeps it in r6. Pinning it to r8 costs the u16 truncation
// and six extra instructions. 4 lever rounds.
NON_MATCH void FUN_080157b0(struct StageLayer* l, const struct Stage* stage) {
#if MODERN
  u16 b = l->bgIdx;
  asm("" : "+r"(b));
  switch (l->phase) {
    case 0: {
      u32 n = b >> 4;
      u16 v = l->screenBase | 0x4046;
      BGCNT16(n) = v;
      RESET_BGOFS(n);
      RequestType2Transfer(0, (void*)((v & 0x1F00) << 3), 0x80 << 5);
      {
        u8* ow = (u8*)&gOverworld;
        s32 k = 0x2D025;
        u8* a;
        asm("" : "+r"(ow));
        asm("" : "+r"(k));
        a = (u8*)l + 0x68;
        *a = *(ow + k);
        asm("" : "+r"(a));
        a += 1;
        asm("" : "+r"(a));
        *a = 0;
      }
      l->phase++;
      FALLTHROUGH;
    }
    case 1: {
      u8* ow = (u8*)&gOverworld;
      s32 k = 0x2D024;
      asm("" : "+r"(ow));
      asm("" : "+r"(k));
      if (*(ow + k) == 0) {
        break;
      }
      l->phase++;
      FALLTHROUGH;
    }
    case 2: {
      u32 n = b >> 4;
      u16 v = l->screenBase | 0x4046;
      s32 z = 0;
      BGCNT16(n) = v;
      RESET_BGOFS(n);
      CpuFastSet(&z, (void*)(((v & 0x1F00) << 3) + 0x06000000), 0x01000400);
      LoadBgMap(b, gBgMapOffsets, 0x4a, 0, 0);
      l->phase++;
      break;
    }
  }
#else
  INCCODE("asm/stage_gfx/weil_labo_p1_p1b_post.inc");
#endif
}

void FUN_08015c40(struct StageLayer* l, const struct Stage* stage) {
  gWindowRegBuffer.dispcnt &= ~DISPCNT_WIN1_ON;
  gWindowRegBuffer.winin[2] |= 0xe;
}

// 0x08015c5c -- parked (allocation tie): retail holds bgIdx<<16 in r4, the
// 0x4046 pool constant in callee-saved r5, and pushes r4-r7; agbcc packs the
// same values into r3/r5/r6 with one fewer callee-saved reg. Structure and
// insn sequence otherwise identical (if-goto phase chain, in-place n>>=20).
NON_MATCH void FUN_08015c5c(struct StageLayer* l, const struct Stage* _ UNUSED) {
#if MODERN
  u32 n;
  u16 b;
  s32 ph;
  u32 k;
  u32 zero;
  u16 c;
  n = l->bgIdx << 16;
  b = n >> 16;
  ph = l->phase;
  if (ph == 1) goto show;
  if (ph > 1) goto end;
  if (ph != 0) goto end;
  if (gOverworld.state[0] == 0) {
    goto end;
  }
  l->phase = 1;
show:
  n >>= 20;
  k = 0x4046;
  c = l->screenBase | k;
  BGCNT16(n) = c;
  RESET_BGOFS(n);
  zero = 0;
  CpuFastSet(&zero, (void*)(VRAM + ((c & 0x1F00) << 3)), 0x01000400);
  LoadBgMap(b, gBgMapOffsets, 0x4B, 0, 0);
  l->phase++;
end:;
#else
  INCCODE("asm/stage_gfx/weil_labo_5c5c.inc");
#endif
}

INCASM("asm/stage_gfx/weil_labo_p1_p2_a1.inc");

/* 0x08015cf0 -- parked (scheduling ties): structure and register homes match
   retail (l5=r5, n16=r6, ov=r7-region, b=r8, _CpuFastFill frame) but three
   sites resist: the 0x2C002 pool-offset scratch reg (r1 vs r3), the guarded
   n16>>20 either hoists above the beq or materializes an extra copy, and the
   vu32 spill store schedules early. */
NON_MATCH void FUN_08015cf0(struct StageLayer* l, const struct Stage* stage) {
#if MODERN

  register struct StageLayer* l5 asm("r5");
  register u32 n16 asm("r6");
  register u32 b asm("r8");
  u8* ov;
  l5 = l;
  {
    register u32 raw asm("r0");
    raw = l5->bgIdx;
    n16 = raw << 16;
  }
  b = n16 >> 16;
  ov = (u8*)&gOverworld;
  if (*(ov + 0x2D024) == 0) {
    DrawGeneralStageLayer(l5, stage);
    return;
  }
  if (*(u16*)(ov + 0x2C002) != 0) {
    {
      u32 nn = n16;
      asm("" : "+r"(nn));
      _CpuFastFill(0, (void*)(((BGCNT16(nn >> 20) & 0x1F00) << 3) + VRAM), 0x1000);
    }
    LoadBgMap(b, gBgMapOffsets, 0x4B, 0, 0);
  }
  {
    register u8* ov3 asm("r3");
    register u32 o2 asm("r2");
    ov3 = ov;
    o2 = 0x2D040;
    asm("" : "+r"(o2));
    if (*(s32*)(ov3 + o2) != 0) {
      s32* q;
      {
        u32 o54 = 0x2D054;
        s32* d1;
        asm("" : "+r"(o54));
        d1 = (s32*)(ov3 + o54);
        o2 += 8;
        q = *(s32**)(ov3 + o2);
        *d1 = q[0];
      }
      {
        u32 o58 = 0x2D058;
        s32* d2;
        asm("" : "+r"(o58));
        d2 = (s32*)(ov3 + o58);
        *d2 = q[1];
      }
    }
  }
  {
    u32 n = n16 >> 20;
    u16 v3;
    {
      u32 o54b = 0x2D054;
      asm("" : "+r"(o54b));
      BGnHOFS(n) = (l5->viewportCenterPixel.x - (*(s32*)(ov + o54b) >> 8)) + 0xE0 + (l5->drawPivotOffset.x >> 8);
    }
    {
      u32 o58b = 0x2D058;
      s32 v2;
      asm("" : "+r"(o58b));
      v2 = l5->viewportCenterPixel.y - (((*(s32*)(ov + o58b) + -0x50000) >> 8) + 0x500);
      v2 += (l5->drawPivotOffset.y >> 8) + 0x70;
      BGnVOFS(n) = v2;
      v3 = v2;
    }
    if (*(ov + 0x2D025) != 0 && (s16)v3 > -0xA0) {
      gVideoRegBuffer.dispcnt |= b << 8;
    } else {
      gVideoRegBuffer.dispcnt &= ~(b << 8);
    }
  }
}
#else
  INCCODE("asm/stage_gfx/weil_labo_5cf0.inc");
#endif
}

struct Entity* FUN_080d8f7c(u8 a0);

// 0x08015E34
void weillabo_08015e34(struct StageLayer* l0, const struct Stage* _ UNUSED) {
  register struct StageLayer* l asm("r6");
  register struct Overworld* ow asm("r5");
  register s32 ph asm("r0");
  l = l0;
  ph = l->phase;
  ow = &gOverworld;
  if (ph == 0) {
    register u32 n asm("r0");
    register u16* bg asm("r4");
    register s32 zero asm("r3");
    s32* q;
    n = (u16)l->bgIdx;
    bg = (u16*)&gVideoRegBuffer.bgcnt[0];
    zero = 0;
    q = (s32*)((u8*)l + 0xc);
    do {
      *(s32*)((u8*)q + 0x68) = zero;
      q--;
    } while ((s32)q >= (s32)l);
    {
      register u32 ix asm("r2");
      register u16* bp asm("r2");
      register s32 v asm("r0");
      register s32 k asm("r1");
      ix = n >> 4;
      ix <<= 1;
      bp = (u16*)(ix + (u32)bg);
      k = *bp;
      v = 0xFFFC;
      v &= k;
      k = 2;
      v |= k;
      *bp = v;
    }
    l->unk_10 = 0;
    l->phase++;
  }
  {
    register s32 so asm("r1");
    register u8* sp2 asm("r0");
    so = 0x2D026;
    asm("" : "+r"(so));
    sp2 = (u8*)ow + so;
    if (*sp2 == 0) {
      goto stopall;
    }
  }
  {
    struct Solid** arr = (struct Solid**)l->work.raw;
    register s32 one2 asm("r3");
    s32 i;
    l->unk_10++;
    for (i = 0; i <= 3; i++) {
      if (arr[i] == NULL) {
        arr[i] = (struct Solid*)FUN_080d8f7c((u8)i);
      }
    }
    if (!isSoundPlaying(0x92 * 2)) {
      PlaySound(0x92 * 2);
    }
    {
      register s32 t asm("r0");
      u16 uv = l->unk_10;
      one2 = 1;
      asm volatile("add %0, %1, #0" : "=&l"(t) : "l"(one2));
      t &= uv;
      if (t == 0) {
        goto out;
      }
    }
    {
      register u32* rp asm("r2");
      register u32 rnd asm("r1");
      register u32 acc asm("r0");
      u32 rv;
      rp = &RNG_0202f388;
      asm("" : "+r"(rp));
      rnd = *rp;
      acc = 0x343FD;
      acc *= rnd;
      acc += 0x269EC3;
      rv = acc << 1;
      asm("" : "+r"(rv));
      *rp = rv >> 1;
      if (((rv >> 0x11) & one2) != 0) {
        gBlendRegBuffer.bldalpha = 0xC0A;
        return;
      }
    }
    goto out;
    goto out;
  }
stopall : {
    register s32 zero asm("r4");
    u32 tbl;
    register struct Solid** q asm("r3");
    register s32 i asm("r5");
    zero = 0;
    tbl = (u32)gSolidFnTable;
    q = (struct Solid**)l->work.raw;
    i = 3;
    do {
      struct Solid* e = *q;
      if (e != NULL) {
        u8* a;
        EntityFunc** routine_table;
        (e->s).flags &= ~DISPLAY;
        (e->s).flags &= ~FLIPABLE;
        a = (u8*)e + 0x8c;
        *(u32*)a = zero;
        asm("" : "+r"(a));
        a += 4;
        asm("" : "+r"(a));
        *(u32*)a = zero;
        asm("" : "+r"(a));
        a += 4;
        asm("" : "+r"(a));
        *a = zero;
        (e->s).flags &= ~COLLIDABLE;
        routine_table = (EntityFunc**)((((e->s).id) << 2) + tbl);
        *(u32*)((e->s).mode) = 3;
        (e->s).onUpdate = (void*)(*routine_table)[3];
        *q = (struct Solid*)zero;
      }
      q++;
      i--;
    } while (i >= 0);
    if (isSoundPlaying(0x92 * 2)) {
      StopSound(0x92 * 2);
    }
  }
out:
  gBlendRegBuffer.bldalpha = 0xC04;
}


// 0x08015F7C
void FUN_08015f7c(struct StageLayer* l, const struct Stage* stage) {
  if (gOverworld.state[2] == 0) {
    RequestGraphicTransfer(&(TILESETS(18, 172))->g, (void*)0x4000);
    LoadPalette(&(TILESETS(18, 172))->pal, 0);
  } else {
    RequestGraphicTransfer(&(TILESETS(18, 173)[((u16)l->unk_10 >> 2) & 3]).g, (void*)0x4000);
    LoadPalette(&(TILESETS(18, 173)[((u16)l->unk_10 >> 2) & 3]).pal, 0);
  }
  DrawGeneralStageLayer(l, stage);
}

void FUN_08016018(struct StageLayer* l, const struct Stage* stage) {
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


// 0x08016080
void FUN_08016080(u32 a) {
  STAGE.unk_00c = a;
}

void FUN_08016094(s32 a, s32 b, s32 c) {
  STAGE.unk_018 = a;
  STAGE.unk_01c = b;
  STAGE.unk_020 = c;
}

#undef STAGE

// ------------------------------------------------------------------------------------------------------------------------------------

extern const struct ChunkMap sChunkMap1;
INCBIN_STATIC(sChunkMap1, "data/stage/weil_labo/layer1.bin");  // ./tools/dumper/bin.ts ./baserom.gba 0x08346ab0 0x08346c14 ./data/stage/weil_labo/layer1.bin

extern const struct ChunkMap sChunkMap2;
INCBIN_STATIC(sChunkMap2, "data/stage/weil_labo/layer2.bin");  // ./tools/dumper/bin.ts ./baserom.gba 0x08346c14 0x08346d58 ./data/stage/weil_labo/layer2.bin

extern const struct ChunkMap sChunkMap3;
INCBIN_STATIC(sChunkMap3, "data/stage/weil_labo/layer3.bin");  // ./tools/dumper/bin.ts ./baserom.gba 0x08346d58 0x08346e9c ./data/stage/weil_labo/layer3.bin

extern const tileset_ofs_t sTilesetOffset[];
INCBIN_STATIC(sTilesetOffset, "data/stage/weil_labo/tileset_offset.bin");  // ./tools/dumper/bin.ts ./baserom.gba 0x08346e9c 0x08346fe0 ./data/stage/weil_labo/tileset_offset.bin

extern const u16 sScreenBehavior[];
INCBIN_STATIC(sScreenBehavior, "data/stage/weil_labo/screen_behavior.bin");  // ./tools/dumper/bin.ts ./baserom.gba 0x08346fe0 0x08347268 ./data/stage/weil_labo/screen_behavior.bin

const struct Stage gWeilLaboLandscape = {
  id : STAGE_WEILS_LABO,
  fn : sStageRoutine,
  terrainHdr : &gStageTerrains[STAGE_WEILS_LABO],
  maps : {&sChunkMap1, &sChunkMap2, &sChunkMap3},
  bgIdx : {USE_BG1, USE_BG2, USE_BG3},
  prio : {3, 3, 3},
  screenBase : {BGMAP_BLOCK(2), BGMAP_BLOCK(4), BGMAP_BLOCK(6)},
  scrollPower : {{0x100, 0x100}, {0x100, 0x100}, {0x100, 0x100}},
  scroll : {{0, 0}, {0, 0}, {0, 0}},
  tilesetOffset : sTilesetOffset,
  bgFns : sLayerRoutine,
  behavior : sScreenBehavior,
  conveyor : {0x0, 0x0},
};
