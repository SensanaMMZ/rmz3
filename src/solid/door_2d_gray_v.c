#include "collision.h"
#include "gfx.h"
#include "global.h"
#include "solid.h"

// 2D Door(Gray, Vertical)

static const struct Collision sCollisions[2];

// ------------------------------------------------------------------------------------------------------------------------------------

static void Door2DGray_Init(struct Solid* p);
static void Door2DGray_Update(struct Solid* p);
static void Door2DGray_Die(struct Solid* p);

// clang-format off
const SolidRoutine gDoor2DGrayVRoutine = {
    [ENTITY_INIT] =      Door2DGray_Init,
    [ENTITY_UPDATE] =    Door2DGray_Update,
    [ENTITY_DIE] =       Door2DGray_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteSolid,
    [ENTITY_EXIT] =      (SolidFunc)DeleteEntity,
};
// clang-format on

static void Door2DGray_Init(struct Solid* p) {
  InitNonAffineMotion(&p->s);
  (p->s).coord.x += PIXEL(8);
  (p->s).coord.y += PIXEL(8);
  LOAD_STATIC_GRAPHIC(SM122_DOOR_2D_GRAY_V);
  (p->s).spr.oam.priority = 1;
  (p->s).flags |= DISPLAY;
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  (p->s).mode[1] = 0;
  (p->s).mode[2] = 0;
  Door2DGray_Update(p);
}

static void FUN_080d0478(struct Solid* p);
void FUN_080d04cc(struct Solid* p);
void FUN_080d0664(struct Solid* p);
void FUN_080d0804(struct Solid* p);

static void Door2DGray_Update(struct Solid* p) {
  static const SolidFunc sUpdates[4] = {
      FUN_080d0478,
      FUN_080d04cc,
      FUN_080d0664,
      FUN_080d0804,
  };
  (sUpdates[(p->s).mode[1]])(p);
}

static void Door2DGray_Die(struct Solid* p) {
  EXIT_BODY(p);
  (p->s).flags &= ~DISPLAY;
  SET_SOLID_ROUTINE(p, ENTITY_EXIT);
}

NAKED static void onCollision(struct Body* body, struct Coord* r1 UNUSED, struct Coord* r2 UNUSED) {
  INCCODE("asm/solid/door_gray_v_collision.inc");
}

static void FUN_080d0478(struct Solid* p) {
  switch ((p->s).mode[2]) {
    case 0: {
      SetMotion(&p->s, MOTION(SM122_DOOR_2D_GRAY_V, 0));
      INIT_BODY(p, &sCollisions[0], 0, onCollision);
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1: {
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}

INCASM("asm/solid/unk_20.inc");

// --------------------------------------------

static const struct Collision sCollisions[2] = {
    [0] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 255,
      atkType : 0x00,
      nature : BODY_NATURE_B7,
      comboLv : 0x00,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), -PIXEL(32), PIXEL(34), PIXEL(66)},
    },
    [1] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      damage : 255,
      LAYER(0xFFFFFFFF),
      hitzone : 0x00,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(0), PIXEL(0)},
    },
};
