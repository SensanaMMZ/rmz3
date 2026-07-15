#ifndef GUARD_RMZ3_GPU_REGS_H
#define GUARD_RMZ3_GPU_REGS_H

#include "constants/constants.h"
#include "gba/gba.h"

#define USE_BG1 0x12
#define USE_BG2 0x24
#define USE_BG3 0x38

#define BGCNT16(n) *((u16*)&gVideoRegBuffer.bgcnt[n])
#define BGOFS(n) ((struct BgOfs*)gVideoRegBuffer.bgofs[(n)])
#define RESET_BGOFS(n) *((u32*)&gVideoRegBuffer.bgofs[(n)]) = 0
#define BGnHOFS(n) (*((u16*)(((u8*)gVideoRegBuffer.bgofs) + ((n) << 2))))
#define BGnVOFS(n) (*((u16*)(((u8*)gVideoRegBuffer.bgofs) + ((n) << 2) + 2)))
#define CHAR_BASE(n) ((*((u16*)&gVideoRegBuffer.bgcnt[n]) & 0xc) << 0xc)
#define SCREEN_BASE(n) (gVideoRegBuffer.bgcnt[n].screenBaseBlock * 0x800)
#define SCREEN_BASE_16(n) ((BGCNT16(n) & 0x1F00) << 3)

struct BgOfs {
  u16 x;
  u16 y;
};

// Video register buffer on EWRAM (gVideoRegBuffer)
struct WramVideoRegister {
  /*
    ただし、 bit13..15 は無視される (0x2002190 が担う)
    WramWindowRegister.dispcnt と OR したものが 実際のDISPCNT
  */
  u16 dispcnt;
  struct BgCnt ALIGNED(4) bgcnt[4];
  u16 bgofs[4][2];
};

// Video register buffer on EWRAM (gBlendRegBuffer)
struct WramBlendRegister {
  u16 bldclt;
  u16 bldalpha;
  u16 bldy;
  u16 _;
};  // 8 bytes

union WindowRegister {
  u32 word;
  u16 half[2];  // win0, win1
};

// Window register buffer on EWRAM (gWindowRegBuffer)
struct WramWindowRegister {
  /*
    DISPCNTの bit13..15 (Window有効化周り)
    WramVideoRegister.dispcnt と OR したものが 実際のDISPCNT
  */
  u16 dispcnt;
  u16 _;
  union WindowRegister winH;
  union WindowRegister winV;
  u8 winin[4];  // 0x04000048, 0x04000049, 0x0400004A, 0x0400004B
};  // 16 bytes

// --------------------------------------------

extern struct WramVideoRegister gVideoRegBuffer;
extern struct WramBlendRegister gBlendRegBuffer;
extern struct WramWindowRegister gWindowRegBuffer;
extern u16 wMOSAIC;  // wMOSAIC

// --------------------------------------------

void ResetVideoRegister(void);
void FlushVideoRegister(void);
void LoadBgMap(u8 bg16, const u32* tbl, u8 idx, s8 x, s8 y);
void loadBgMap_08004248(u16* dst, const u32* tbl, u8 idx, s8 x8, s8 y8);
void ResetOAM(void);
void FlushOAM(void);
void ClearBLDCLT_1(void);
void FlushBlendRegister(void);
void ResetWindow(void);
void FlushWinRegister(void);
void ClearMOSAIC(void);
void FlushMOSAIC(void);

#endif  // GUARD_RMZ3_GPU_REGS_H
