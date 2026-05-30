#include "collision.h"
#include "global.h"
#include "overworld.h"
#include "physics.h"
#include "solid.h"

static const struct Collision sCollision;

static void Solid34_Init(struct Solid* p);
void Solid34_Update(struct Solid* p);
static void Solid34_Die(struct Solid* p);

// clang-format off
const SolidRoutine gSolid34Routine = {
    [ENTITY_INIT] =      Solid34_Init,
    [ENTITY_UPDATE] =    Solid34_Update,
    [ENTITY_DIE] =       Solid34_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteSolid,
    [ENTITY_EXIT] =      (SolidFunc)DeleteEntity,
};
// clang-format on

static void Solid34_Init(struct Solid* p) {
  (p->s).flags |= DISPLAY;
  (p->s).flags |= FLIPABLE;
  InitNonAffineMotion(&p->s);
  INIT_BODY(p, &sCollision, 0, NULL);
  (p->s).coord.y = FUN_0800a134((p->s).coord.x, (p->s).coord.y);
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  Solid34_Update(p);
}

void Solid34_Update(struct Solid* p) {
  switch ((p->s).mode[3]) {
    case 0:
      (p->s).work[0] = gOverworld.state[0];
      if (gOverworld.state[0] == 0) {
        SetMotion(&p->s, 0x7601);
      } else {
        SetMotion(&p->s, 0x7602);
      }
      (p->s).mode[3]++;
      // fallthrough
    case 1:
      UpdateMotionGraphic(&p->s);
      if ((p->body).status & 8) {
        gOverworld.state[0] ^= 1;
      }
      if ((p->s).work[0] != gOverworld.state[0]) {
        if ((p->s).work[0] == 0) {
          SetMotion(&p->s, 0x7603);
        } else {
          SetMotion(&p->s, 0x7604);
        }
        (p->s).work[2] = 0x1e;
        (p->s).mode[3]++;
      }
      break;
    case 2:
      UpdateMotionGraphic(&p->s);
      if ((u8)(--(p->s).work[2]) == 0) {
        (p->s).mode[3] = 0;
      }
      break;
  }
}

static void Solid34_Die(struct Solid* p) { return; }

static const struct Collision sCollision = {
  kind : DRP,
  faction : FACTION_ENEMY,
  damage : 0,
  atkType : 0xFF,
  element : 0xFF,
  nature : 0xFF,
  comboLv : 0xFF,
  hitzone : 1,
  hardness : METAL,
  remaining : 0,
  layer : 0xFFFFFFFF,
  range : {0x0000, 0x0800, 0x2000, 0x1000},
};
