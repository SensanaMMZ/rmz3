#ifndef GUARD_RMZ3_STAGE_GIANT_ELEVATOR_PROPS_H
#define GUARD_RMZ3_STAGE_GIANT_ELEVATOR_PROPS_H

#include "common.h"
#include "gba/types.h"

// 0x0202f228
struct GiantElevatorState {
  u8 unk_000[4];
  u16 unk_004;
  u16 unk_006;
  u8 unk_008[32];
  s32 unk_028;
  s32 unk_02c;
  u8 unk_030[216];
};
static_assert(sizeof(struct GiantElevatorState) == 264);

#endif  // GUARD_RMZ3_STAGE_GIANT_ELEVATOR_PROPS_H
