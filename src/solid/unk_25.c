#include "collision.h"
#include "entity.h"
#include "global.h"
#include "overworld.h"
#include "solid.h"

static void Solid25_Init(struct Solid* p);
void Solid25_Update(struct Solid* p);
void Solid25_Die(struct Solid* p);

// clang-format off
const SolidRoutine gSolid25Routine = {
    [ENTITY_INIT] =      Solid25_Init,
    [ENTITY_UPDATE] =    Solid25_Update,
    [ENTITY_DIE] =       Solid25_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteSolid,
    [ENTITY_EXIT] =      (SolidFunc)DeleteEntity,
};
// clang-format on

static void Solid25_Init(struct Solid* p) {
  static const struct Rect size = {0, 0x1800, 0x2000, 0x3000};

  (p->s).flags |= DISPLAY;
  InitNonAffineMotion(&p->s);
  (p->s).flags |= FLIPABLE;
  (p->s).flags2 |= ENTITY_HAZARD;
  (p->s).size = (struct Rect*)&size;
  (p->s).hazardAttr = 0x2001;
  (p->s).coord.x += PIXEL(8);
  (p->s).unk_coord.y = (p->s).coord.y - PIXEL(8);
  if ((p->s).work[1] == 0) {
    SetMotion(&p->s, MOTION(0x7c, 0x01));
  } else {
    SetMotion(&p->s, MOTION(0x7d, 0x00));
  }
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  Solid25_Update(p);
}

void Solid25_Update(struct Solid* p) {
  u16 val;
  u32 tmp = (p->s).work[0] * 64;
  if (((gOverworld.terrain.id & 0x7F) == STAGE_AREA_X2) || ((gOverworld.terrain.id & 0x7F) == STAGE_WEILS_LABO)) {
    tmp += gOverworld.work.areaX2.unk_008;
  }

  val = tmp;
  val &= 0xFF;
  if (val < 0x80) {
    s32 y = (val * 0xC0) - PIXEL(48);
    (p->s).coord.y = (p->s).unk_coord.y + y;
  } else {
    s32 y = ((val - 0x80) * 0xC0) - PIXEL(48);
    (p->s).coord.y = (p->s).unk_coord.y - y;
  }
  UpdateMotionGraphic(&p->s);
}

void Solid25_Die(struct Solid* p) {}
