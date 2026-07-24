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
static inline void* GetHdr(const u32* tbl, u8 idx) {
  tbl = (const u32*)((const char*)tbl + tbl[idx]);
  return (void*)&tbl[idx];
}

void LoadBgMap(u8 bg16, const u32* tbl, u8 idx, s8 x8, s8 y8) {
  u16* dst = (void*)(VRAM + SCREEN_BASE_16(bg16 >> 4));
  dst += (y8 * 32) + x8;

  {
    struct BgMapHeader* hdr = GetHdr(tbl, idx);
    u32 w8 = hdr->w;
    u16 h8 = hdr->h;
    u16* src = (u16*)&hdr[1];

    while (h8 > 0) {
      CpuCopy16(src, dst, w8 << 1);
      h8--;
      src += w8, dst += 32;
    }
  }
}

/**
 * @brief BgMapOffsets[n] を(x*8, y*8)にくるようにdst(BGMap)にロード
 * @note 0x08004248
 */
void loadBgMap_08004248(u16* _dst, const u32* tbl, u8 idx, s8 x8, s8 y8) {
  u16* dst = &_dst[(y8 * 32) + x8];
  struct BgMapHeader* hdr = GetHdr(tbl, idx);
  u32 w8 = hdr->w;
  u16 h8 = hdr->h;
  u16* src = (u16*)(hdr + 1);

  while (h8 > 0) {
    CpuCopy16(src, dst, w8 << 1);
    h8--;
    src += w8, dst += 32;
  }
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
void FlushOAM(void) {
  vu16 dispcnt = REG_DISPCNT;
  struct OamData** ep = &gOamManager.p;
  struct OamData* p = *ep;
  struct OamData* buf;

  dispcnt &= ~(DISPCNT_OBJ_ON);
  dispcnt |= gOamManager.dispcnt;
  REG_DISPCNT = dispcnt;

  buf = (struct OamData*)ep - 128;
  while (PTR_U32(p) < PTR_U32(ep)) {
    *((u16*)p) = 0x200;
    p++;
  }
  DmaCopy32(3, buf, OAM, 1024);
  *(struct OamData**)(buf + 128) = buf;
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
