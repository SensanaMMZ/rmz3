#include "collision.h"
#include "entity.h"
#include "global.h"
#include "solid.h"
#include "overworld.h"
#include "zero.h"
#include "vfx.h"

static const struct Rect sSize;

static void Solid36_Init(struct Solid* p);
static void Solid36_Update(struct Solid* p);
static void Solid36_Die(struct Solid* p);

// clang-format off
const SolidRoutine gSolid36Routine = {
    [ENTITY_INIT] =      Solid36_Init,
    [ENTITY_UPDATE] =    Solid36_Update,
    [ENTITY_DIE] =       Solid36_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteSolid,
    [ENTITY_EXIT] =      (SolidFunc)DeleteEntity,
};
// clang-format on

static void Solid36_Init(struct Solid* p) {
  (p->s).flags |= DISPLAY;
  InitNonAffineMotion(&p->s);
  (p->s).flags |= FLIPABLE;
  (p->s).unk_coord.y = (p->s).coord.y - PIXEL(8);
  SetMotion(&p->s, MOTION(0x97, 0x01));
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  Solid36_Update(p);
}

// Vertically-oscillating platform: phase = work[0]*96 + stage frame counter,
// wrapped to [0,0x180); a triangle wave drives coord.y around unk_coord.y with
// amplitude ~PIXEL(80). Above pZero2 - PIXEL(12) the platform is solid (hazard),
// otherwise Zero passes through. Matches except an r0/r1 register-allocation tie
// in the phase computation (agbcc colors work[0]->r1, retail ->r0).
NON_MATCH static void Solid36_Update(struct Solid* p) {
#if MODERN
  u32 tmp = ((p->s).work[0] * 3 << 5) + gOverworld.work.missileFactory.unk_004;
  u16 val = (u32)(u16)tmp % 0x180;
  if (val < 0xc0) {
    s32 y = ((u32)val * 5 << 13) / 0xc0 - PIXEL(80);
    (p->s).coord.y = (p->s).unk_coord.y + y;
  } else {
    s32 y = ((u32)(val - 0xc0) * 5 << 13) / 0xc0 - PIXEL(80);
    (p->s).coord.y = (p->s).unk_coord.y - y;
  }
  if ((p->s).coord.y > (pZero2->s).coord.y - PIXEL(12)) {
    (p->s).flags2 |= ENTITY_HAZARD;
    (p->s).size = (struct Rect*)&sSize;
    (p->s).hazardAttr = 0xA001;
  } else {
    (p->s).flags2 &= ~ENTITY_HAZARD;
  }
  UpdateMotionGraphic(&p->s);
#else
  INCCODE("asm/wip/Solid36_Update.inc");
#endif
}

static void Solid36_Die(struct Solid* p) { return; }

static const struct Rect sSize = {0, 0x800, 0x3000, 0x1000};
