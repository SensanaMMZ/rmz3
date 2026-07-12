#include "anim_loader.h"
#include "collision.h"
#include "gfx.h"
#include "global.h"
#include "quake.h"
#include "solid.h"
#include "stagerun.h"

static const struct Rect sSize;

static void Solid45_Init(struct Solid* p);
static void Solid45_Update(struct Solid* p);
void Solid45_Die(struct Solid* p);

// clang-format off
const SolidRoutine gGiantElevatorPierRoutine = {
    [ENTITY_INIT] =      Solid45_Init,
    [ENTITY_UPDATE] =    Solid45_Update,
    [ENTITY_DIE] =       Solid45_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteSolid,
    [ENTITY_EXIT] =      (SolidFunc)DeleteEntity,
};
// clang-format on

static void Solid45_Init(struct Solid* p) {
  if (gOverworld.state[0] != 0) {
    (p->s).flags &= ~DISPLAY;
    (p->s).flags &= ~FLIPABLE;
    (p->body).status = 0;
    (p->body).prevStatus = 0;
    (p->body).invincibleTime = 0;
    (p->s).flags &= ~COLLIDABLE;
    SET_SOLID_ROUTINE(p, ENTITY_DISAPPEAR);
  } else {
    s32 x;
    (p->s).flags |= DISPLAY;
    (p->s).flags |= FLIPABLE;
    InitNonAffineMotion(&p->s);
    SetMotion(&p->s, MOTION(SM154_GIANT_ELEVATOR_PIER, 0));
    (p->s).flags2 |= ENTITY_HAZARD;
    (p->s).size = &sSize;
    (p->s).hazardAttr = 0x2001;
    (p->s).d.y = PIXEL(0);
    (p->s).d.x = PIXEL(0);
    x = (p->s).coord.x;
    (p->s).coord.x = x - PIXEL(8);
    (p->s).coord.y = FUN_08009f6c(x - PIXEL(80), (p->s).coord.y) + 0x101;
    LOAD_STATIC_GRAPHIC(SM154_GIANT_ELEVATOR_PIER);
    SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
    Solid45_Update(p);
  }
}

static void Solid45_Update(struct Solid* p) {
  UpdateMotionGraphic(&p->s);
  if (gOverworld.state[0] != 0) {
    if ((p->s).mode[1] == 0) {
      AppendQuake(1, &(p->s).coord);
      SetMotion(&p->s, 0x9A00);
      (p->s).work[2] = 0xA;
      (p->s).mode[1]++;
    }
    if ((p->s).d.x <= 0xFF) {
      (p->s).d.x += 8;
    }
    (p->s).coord.x -= (p->s).d.x;
    if ((p->s).work[2] != 0) {
      (p->s).work[2]--;
      if ((u8)(p->s).work[2] == 0) {
        gOverworld.state[0] = 2;
      }
    }
    if (CalcFromCamera(&gStageRun.vm.camera, &(p->s).coord) > 0x4000) {
      SET_SOLID_ROUTINE(p, ENTITY_DIE);
      Solid45_Die(p);
    }
  }
}

void Solid45_Die(struct Solid* p) {
  (p->s).flags &= ~DISPLAY;
  (p->s).flags2 &= ~ENTITY_HAZARD;
  SET_SOLID_ROUTINE(p, ENTITY_EXIT);
}

static const struct Rect sSize = {PIXEL(0), PIXEL(7), PIXEL(128), PIXEL(16)};
