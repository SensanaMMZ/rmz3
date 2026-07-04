#include "gpu_regs.h"

#include "gba/gba.h"
#include "gfx.h"
#include "global.h"
#include "motion.h"

void ResetVideoRegister(void) {
  gVideoRegBuffer.dispcnt &= BG_MODE_0;
  gVideoRegBuffer.dispcnt &= 0xB0FF;
  DmaFill32(3, 0, gVideoRegBuffer.bgcnt, 56);
  *(u16*)(&gVideoRegBuffer.bgcnt[0]) = 0xc008;
  *(u16*)(&gVideoRegBuffer.bgcnt[1]) = 0x4205;
  *(u16*)(&gVideoRegBuffer.bgcnt[2]) = 0x4406;
  *(u16*)(&gVideoRegBuffer.bgcnt[3]) = 0x4807;
  FlushVideoRegister();
}

void FlushVideoRegister(void) {
  vu16 dispcnt = REG_DISPCNT;
  dispcnt &= 0xF0E8;
  gVideoRegBuffer.dispcnt &= 0x0F17;
  dispcnt |= gVideoRegBuffer.dispcnt;
  REG_DISPCNT = dispcnt;
  DmaCopy32(3, gVideoRegBuffer.bgcnt, REG_ADDR_BG0CNT, 56);
}

/**
 * @brief VRAM内のBgMapにBgMapOffsets[idx]のBgMapデータをロードする
 * @param bg16 n = (bg16 / 16) = 0,1,2,3 となり BGnCNT を表す
 * @param tbl gBgMapOffsets (0x085222a0)
 * @param idx gBgMapOffsets のidx
 * @param x BgMapのX座標(タイル単位)
 * @param y BgMapのY座標(タイル単位)
 * @note 0x080041c4
 */
NON_MATCH void LoadBgMap(u8 bg16, const u32* tbl, u8 idx, s8 x, s8 y) {
#if MODERN
  u16* base = (void*)(VRAM + SCREEN_BASE_16(bg16 >> 4));
  u16* dst = &base[(y * 32) + x];

  struct BgMapHeader* hdr = (struct BgMapHeader*)SELF_REL_PTR(&tbl[idx]);
  u32 w = hdr->w * 2;
  u16 row = hdr->h;
  u16* src = (u16*)&hdr[1];

  while (row != 0) {
    CpuCopy16(src, dst, w);
    row--;
    src += (w / 2);
    dst += 32;
  }
#else
  INCCODE("asm/wip/LoadBgMap.inc");
#endif
}

/**
 * @brief BgMapOffsets[n] を(x*8, y*8)にくるようにdst(BGMap)にロード
 * @note 0x08004248
 */
NON_MATCH void loadBgMap_08004248(u16* dst, const u32* tbl, s32 idx, u8 x, s32 y) {
#if MODERN
  u16* d = &dst[((s8)y * 32) + (s8)x];
  struct BgMapHeader* hdr = (struct BgMapHeader*)SELF_REL_PTR(&tbl[(u8)idx]);
  u32 w = hdr->w * 2;
  u16 row = hdr->h;
  u16* src = (u16*)&hdr[1];

  while (row != 0) {
    CpuCopy16(src, d, w);
    row--;
    src += (w / 2);
    d += 32;
  }
#else
  INCCODE("asm/wip/loadBgMap_08004248.inc");
#endif
}

/**
 * @note 0x080042b0
 */
void ResetOAM(void) {
  gOamManager.dispcnt = 0x1040;
  gOamManager.p = gOamManager.buf;
  DmaFill32(3, 0x200, gOamManager.buf, 1024);
  FlushOAM();
}

// 0x080042F8
NON_MATCH void FlushOAM(void) {
#if MODERN
  vu16 dispcnt = REG_DISPCNT;
  dispcnt &= ~(DISPCNT_OBJ_ON);
  dispcnt |= gOamManager.dispcnt;
  REG_DISPCNT = dispcnt;

  while (PTR_U32(gOamManager.p) < PTR_U32(&gOamManager.p)) {
    *((u16*)gOamManager.p) = 0x200;
    gOamManager.p = &gOamManager.p[1];
  }
  DmaCopy32(3, gOamManager.buf, OAM, 1024);
  gOamManager.p = gOamManager.buf;
#else
  INCCODE("asm/wip/FlushOAM.inc");
#endif
}

// 0x08004370
void ClearBLDCLT_1(void) {
  gBlendRegBuffer.bldclt = 0;
  return;
}

void FlushBlendRegister(void) {
  REG_BLDALPHA = gBlendRegBuffer.bldalpha;
  REG_BLDY = gBlendRegBuffer.bldy;
  REG_BLDCNT = gBlendRegBuffer.bldclt;
}

/**
 * @note 0x0800439C
 */
void ResetWindow(void) {
  gWindowRegBuffer.dispcnt = 0;
  gWindowRegBuffer.winin[2] = 0xFF;
}

/**
 * @note 0x080043AC
 */
void FlushWinRegister(void) {
  vu16 dispcnt = REG_DISPCNT;
  dispcnt &= ~(DISPCNT_WIN0_ON | DISPCNT_WIN1_ON | DISPCNT_OBJWIN_ON);
  dispcnt |= gWindowRegBuffer.dispcnt;
  REG_DISPCNT = dispcnt;

  (*(vu32*)REG_ADDR_WIN0H) = gWindowRegBuffer.winH.word;
  (*(vu32*)REG_ADDR_WIN0V) = gWindowRegBuffer.winV.word;
  (*(vu32*)REG_ADDR_WININ) = *((u32*)&gWindowRegBuffer.winin);
}

void ClearMOSAIC(void) {
  wMOSAIC = 0;
  return;
}

void FlushMOSAIC(void) {
  REG_MOSAIC = wMOSAIC;
  return;
}
