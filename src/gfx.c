#include "gfx.h"

#include "gba/gba.h"
#include "global.h"
#include "motion.h"

// GraphicTransfer.type
enum TransferType {
  TT_GRAPHIC,    // struct Graphic
  TT_BG_MAP,     // BG map
  TT_VRAM_FILL,  // VRAM fill
};

IWRAM_DATA ALIGNED(16) struct PaletteManager gPaletteManager = {};
IWRAM_DATA ALIGNED(16) struct OamManager gOamManager = {};

/**
 * @brief VRAM全体を 0x11111111 で埋める (Reset VRAM by filling 0x11111111)
 */
void ClearVRAM(void) {
  gGraphicTransferManager.len = 0;
  gGraphicTransferManager.bg0.buffer = NULL;
  DmaFill32(3, 0x11111111, VRAM, VRAM_SIZE);
}

/**
 * @brief 0x02001f00 のタスクどおりに転送を行う
 */
void doGraphicTransferTasks(void) {
  s32 i;
  struct GraphicTransferManager* gtman = &gGraphicTransferManager;
  s32 len = gtman->len;

  if ((gtman->bg0).buffer != NULL) {
    // buffer を dst に転送した後で, backdrop で buffer をクリア
    DmaCopy32(3, (gtman->bg0).buffer, (void*)(VRAM + (gtman->bg0).dst), (gtman->bg0).bytesize);
    DmaFill32(3, (gtman->bg0).backdrop, (gtman->bg0).buffer, (gtman->bg0).bytesize);
  }

  while (len != 0) {
    struct GraphicTransfer* t = &gGraphicTransferManager.tasks[--len];
    u32 type = t->type;
    if (type != TT_GRAPHIC) {
      if (type == TT_BG_MAP) {
        // 1: BG map
        if (t->bytesize < 32) {
          CpuCopy16(t->src, VRAM + t->dst, t->bytesize);
        } else {
          CpuFastCopy(t->src, VRAM + t->dst, t->bytesize);
        }
      } else {
        // 2, 3: VRAM fill
        CpuFastFill(t->src, VRAM + t->dst, t->bytesize);
      }
    } else {
      LoadGraphic((void*)t->src, t->dst);  // 0: struct Graphic
    }
  }

  gGraphicTransferManager.len = 0;
}

// このグラフィックを構成するタイル1枚あたりのバイト数(e.g. 4bpp: TILESIZE(g) = 32, 8bpp: 64)
#define TILESIZE(g) ((u32)g->tilesize << 3)

// 0x080037c0
void LoadGraphic(const struct GraphicV2* g, void* dst) {
  if (g->size != 0) {
    dst += g->tileId * TILESIZE(g);

    // VRAM layout
    if (g->map2d) {
      void* src = SELF_REL_PTR(&g->src);
      s32 size = g->size;

      if (g->lz77) {
        while (size > 0) {
          // block
          //   u32 bytesize : 30;   // bit0..30
          //   u32 compressed : 1;  // bit31
          //   u8 data[.bytesize];
          if ((*(u32*)src) & (1 << 31)) {
            u32 buf[8];
            CpuFastCopy(VRAM + dst + g->rowsize, buf, 32);
            LZ77UnCompVram(src + 4, VRAM + dst);
            CpuFastCopy(buf, VRAM + dst + g->rowsize, 32);
          } else {
            CpuFastCopy(src + 4, VRAM + dst, g->rowsize);
          }
          // Next row
          dst += TILESIZE(g) << 5;  // BGマップは 1行32タイルなので (<< 5) で次の行に移動
          size -= (*(u32*)src) & 0x7FFFFFFF;
          src += (*(u32*)src) & 0x7FFFFFFF;
        }

      } else if (g->rlu) {
        while (size > 0) {
          // block
          //   u32 bytesize : 30;   // bit0..30
          //   u32 compressed : 1;  // bit31
          //   u8 data[.bytesize];
          if ((*(u32*)src) & (1 << 31)) {
            RLUnCompVram(src + 4, VRAM + dst);
          } else {
            CpuFastCopy(src + 4, VRAM + dst, g->rowsize);
          }
          // Next row
          dst += TILESIZE(g) << 5;  // BGマップは 1行32タイルなので (<< 5) で次の行に移動
          size -= (*(u32*)src) & 0x7FFFFFFF;
          src += (*(u32*)src) & 0x7FFFFFFF;
        }

      } else {
        while (size > 0) {
          CpuFastCopy((void*)src, VRAM + dst, g->rowsize);
          // Next row
          dst += TILESIZE(g) << 5;  // BGマップは 1行32タイルなので (<< 5) で次の行に移動
          src += g->rowsize;
          size -= g->rowsize;
        }
      }

    } else {
      if (g->lz77) {
        LZ77UnCompVram(SELF_REL_PTR(&g->src), VRAM + dst);
      } else if (g->rlu) {
        RLUnCompVram(SELF_REL_PTR(&g->src), VRAM + dst);
      } else {
        CpuFastCopy(SELF_REL_PTR(&g->src), VRAM + dst, g->size);
      }
    }
  }
}

/**
 * @brief Graphic構造体を gGraphicTransferManager(0x02001f00) に追加する
 * @note 0x08003934
 */
s32 RequestGraphicTransfer(const struct Graphic* g, void* dst) {
  u32 i;

  // Check same request
  for (i = 0; i < gGraphicTransferManager.len; i++) {
    if (((struct Graphic*)gGraphicTransferManager.tasks[i].src == g) && (gGraphicTransferManager.tasks[i].dst == dst)) {
      return 0;  // Already requested
    }
  }
  if ((u32)gGraphicTransferManager.len < 16) {
    gGraphicTransferManager.tasks[i].dst = dst;
    gGraphicTransferManager.tasks[i].type = TT_GRAPHIC;
    gGraphicTransferManager.tasks[i].src = (void*)g;
    gGraphicTransferManager.len++;
    return 0;
  }
  return -1;
}

/**
 * @brief BGマップを gGraphicTransferManager(0x02001f00) に追加する
 * @return 0(success), -1(fail)
 * @note 0x080039ac
 */
s32 RequestBgMapTransfer(u16* src, void* dst, s32 bytesize) {
  const s32 len = gGraphicTransferManager.len;
  if (len < 16) {
    gGraphicTransferManager.tasks[len].type = TT_BG_MAP;
    gGraphicTransferManager.tasks[len].bytesize = bytesize;
    gGraphicTransferManager.tasks[len].dst = dst;
    gGraphicTransferManager.tasks[len].src = src;
    gGraphicTransferManager.len++;
    return 0;
  }
  return -1;
}

/**
 * @note バイル研究所くらいでしか使ってない
 * @return 0(success), -1(fail)
 * @note 0x08003a08
 */
s32 RequestType2Transfer(void* src, void* dst, s32 r2) {
  const s32 len = gGraphicTransferManager.len;
  if (len < 16) {
    gGraphicTransferManager.tasks[len].type = TT_VRAM_FILL;
    gGraphicTransferManager.tasks[len].bytesize = r2;
    gGraphicTransferManager.tasks[len].dst = dst;
    gGraphicTransferManager.tasks[len].src = src;
    gGraphicTransferManager.len++;
    return 0;
  }
  return -1;
}

// 0x08003a64
void EnableBG0(u32* buffer, u32 dst, u32 bytesize, u16 backdrop) {
  gGraphicTransferManager.bg0.buffer = (void*)buffer;
  gGraphicTransferManager.bg0.dst = dst;
  gGraphicTransferManager.bg0.bytesize = bytesize;
  gGraphicTransferManager.bg0.backdrop = ((((u32)backdrop) << 16) | backdrop);
  DmaFill32(3, gGraphicTransferManager.bg0.backdrop, buffer, bytesize);
}

// Disable BG0 (HUD layer)
void DisableBG0(void) {
  gGraphicTransferManager.bg0.buffer = NULL;
  return;
}

// ------------------------------------------------------------------------------------------------------------------------------------

void InitPaletteManager(void) {
  DmaFill32(3, 0, &gPaletteManager, PLTT_SIZE);
  DmaCopy32(3, &gPaletteManager, PLTT, PLTT_SIZE);
  gPaletteManager.filter[0] = gPaletteManager.filter[1] = gPaletteManager.filter[2] = 0x20;
  gPaletteManager.unk_406 = 0;
  gPaletteManager.post_process = NULL;
}

static void FadeBlack(u32* src, u32* dst, u32 lv, u32* mask);
static void FadeWhite(u32* src, u32* dst, u32* fades, u32* mask);
static void FadeColor(u32* src, u32* dst, u32* fades, u32* mask);

// 0x08003b24
void FlushPalette(void) {
  u32 mask[3];
  u32 fadeval[6];  // [R1, G1, B1, R2, G2, B2]
  struct PaletteManager* pman = &gPaletteManager;

  // mask for ((RGB555 << 16) | RGB555)
  mask[0] = (0x1F << 16) | 0x1F;                  // Red
  mask[1] = ((0x1F << 5) << 16) | (0x1F << 5);    // Green
  mask[2] = ((0x1F << 10) << 16) | (0x1F << 10);  // Blue

  if (pman->filter[0] == pman->filter[1]) {  // R と G のFadeレベルが同じなら、単一フェードとして扱う
    if (pman->filter[0] == 0x20) {
      DmaCopy32(3, pman->buf, PLTT, PLTT_SIZE);
    } else if (pman->filter[0] < 0x20) {
      FadeBlack((u32*)pman->buf, (u32*)PLTT, pman->filter[0], mask);
    } else {
      fadeval[0] = 0x40 - pman->filter[0];
      fadeval[1] = (pman->filter[0] - 0x21) | ((pman->filter[0] - 0x21) << 16);
      FadeWhite((u32*)pman->buf, (u32*)PLTT, fadeval, mask);
    }
  } else {
    if (pman->filter[0] < 0x21) {
      fadeval[0] = pman->filter[0];
      fadeval[3] = 0;
    } else {
      fadeval[0] = 0x40 - pman->filter[0];
      fadeval[3] = (pman->filter[0] - 0x21) | ((pman->filter[0] - 0x21) << 16);
    }

    if (pman->filter[1] < 0x21) {
      fadeval[1] = pman->filter[1];
      fadeval[4] = 0;
    } else {
      fadeval[1] = 0x40 - pman->filter[1];
      fadeval[4] = (pman->filter[1] - 0x21) | ((pman->filter[1] - 0x21) << 16);
    }

    if (pman->filter[2] < 0x21) {
      fadeval[2] = pman->filter[2];
      fadeval[5] = 0;
    } else {
      fadeval[2] = 0x40 - pman->filter[2];
      fadeval[5] = (pman->filter[2] - 0x21) | ((pman->filter[2] - 0x21) << 16);
    }
    FadeColor((u32*)gPaletteManager.buf, (u32*)PLTT, fadeval, mask);
  }

  {
    struct PaletteManager* pman = &gPaletteManager;
    if (pman->unk_406 != 0) {
      DmaFill16(3, 0xFFFF, PLTT + pman->unk_404, pman->unk_406);
      pman->unk_406 = 0;
    }
    if (pman->post_process != NULL) {
      pman->post_process();
    }
  }
}

/**
 * @fn void LoadPalette(struct Palette* p, u32 r1)
 * @brief Palette構造体の示すパレットを gPaletteManager.buf に転送する
 * @note 0x08003c98
 */
void LoadPalette(const struct Palette* p, u32 ofs) {
  if (p->size != 0) {
    ofs += (p->dst << 5);
    if (p->lz77) {
      LZ77UnCompWram(SELF_REL_PTR(&p->src), (u8*)&gPaletteManager.buf + ofs);
    } else {
      DmaCopy32(3, SELF_REL_PTR(&p->src), (u8*)&gPaletteManager.buf + ofs, p->size);
    }
  }
}

/**
 * @note 0x08003cf0
 */
WIP static void FadeBlack(u32* src, u32* dst, u32 lv, u32* mask) {
#ifdef ALWAYS_FALSE
  // 画面が黄色くなるので、コードがおかしい
  s32 i;
  for (i = 0; i < 256; i++) {
    u32 c = *src;
    u32 r = (((c & mask[0]) * lv) >> 5) & mask[0];
    u32 g = (((c & mask[1]) * lv) >> 5) & mask[1];
    u32 b = (((c & mask[2]) * lv) >> 5) & mask[2];
    *dst = r | g | b;
    src++;
    dst++;
  }
#else
  INCCODE("asm/wip/FadeBlack.inc");
#endif
}

NAKED static void FadeWhite(u32* src, u32* dst, u32* fades, u32* mask) {
  INCCODE("asm/gfx/gfx_fadewhite.inc");
}

// 0x08003d84
NAKED static void FadeColor(u32* src, u32* dst, u32* fades, u32* mask) {
  INCCODE("asm/gfx/gfx_fadecolor.inc");
}
