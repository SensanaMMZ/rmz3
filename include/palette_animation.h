#ifndef GUARD_RMZ3_PALETTE_ANIMATION_H
#define GUARD_RMZ3_PALETTE_ANIMATION_H

#include "gba/gba.h"
#include "motion.h"

#define MAX_PLTT_ANIM 16
#define BLINK_NUM 280

// 0x02002000
struct PaletteAnimation {
  struct MotionPltt *pal;
  struct MotionCmd **cmds;
  struct Motion m;
  bool16 paused;
  u16 palIdx;
};  // 20 bytes;

struct PaletteAnimationManager {
  u16 ids[MAX_PLTT_ANIM];  // wBlinks(02002000)のうち、点滅処理を行うもののBlinkID(=085be764のidx)
  struct PaletteAnimation blinks[MAX_PLTT_ANIM];
};

// --------------------------------------------

extern struct PaletteAnimationManager gPaletteAnimationManager;

// --------------------------------------------

void RemovePaletteAnimation(u16 n);
void StartPaletteAnimation(u16 blinkID, u16 ofs);
u32 StepPaletteAnimation(u16 blinkID);
void RemoveAllPaletteAnimations(void);
void TransferAnimatedPalettesToPaletteBuffer(void);
void PauseAllPaletteAnimations(void);
void ResumeAllPaletteAnimations(void);

#endif  // GUARD_RMZ3_PALETTE_ANIMATION_H
