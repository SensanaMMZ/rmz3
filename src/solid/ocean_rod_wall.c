#include "collision.h"
#include "quake.h"
#include "sound.h"
#include "stagerun.h"
#include "vfx.h"
#include "global.h"
#include "overworld_terrain.h"
#include "solid.h"

// Wall that can be destroyed by Charge Recoil Rod in Ocean highway ruins.

static const struct Collision sCollision;

static void Solid53_Init(struct Solid* p);
static void Solid53_Update(struct Solid* p);
void Solid53_Die(struct Solid* p);

// clang-format off
const SolidRoutine gOceanRodWallRoutine = {
    [ENTITY_INIT] =      Solid53_Init,
    [ENTITY_UPDATE] =    Solid53_Update,
    [ENTITY_DIE] =       Solid53_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteSolid,
    [ENTITY_EXIT] =      (SolidFunc)DeleteEntity,
};
// clang-format on

static void Solid53_Init(struct Solid* p) {
  struct Coord* velocity;

  if (GetMetatileAttr((p->s).coord.x, (p->s).coord.y) == 0) {
    (p->s).flags &= ~DISPLAY;
    (p->s).flags &= ~FLIPABLE;
    EXIT_BODY(p);
    SET_SOLID_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }

  INIT_BODY(p, &sCollision, 0, NULL);
  velocity = &(p->s).d;
  velocity->x = velocity->y = PIXEL(0);
  (p->s).coord.x += PIXEL(8);
  (p->s).coord.y += PIXEL(8);
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  Solid53_Update(p);
}

static void Solid53_Update(struct Solid* p) {
  if ((p->body).status & BODY_STATUS_WHITE) {
    if ((p->body).status & BODY_STATUS_RECOILED) {
      EXIT_BODY(p);
      (p->s).flags |= DISPLAY;
      (p->s).flags |= FLIPABLE;
      InitNonAffineMotion(&p->s);
      SetMotion(&p->s, MOTION(SM182_UNK, 1));
      SET_SOLID_ROUTINE(p, ENTITY_DIE);
      Solid53_Die(p);
    }
  }
}

void FUN_0800d5a8(struct Coord* c);
void CreateBubble(s32 x, s32 y, u8 kind);

// Sink + bubble-burst death. Logic verified; parked on the RNG-unroll naming
// basin: the 3-chained RANDOMs keep the seed/constants in sl/r9/r8 with a
// staged copy before the first muls - every pin/anchor combination either
// loses the copy, spills the loop counter, or renames the invariant homes.
NON_MATCH void Solid53_Die(struct Solid* p) {
#if MODERN
  switch ((p->s).mode[1]) {
    case 0: {
      s32 i;
      FUN_0800d5a8(&(p->s).coord);
      AppendQuake(4, &(p->s).coord);
      PlaySound(0xE2);
      for (i = 0xF; i >= 0; i--) {
        s32 x = ((RANDOM(RNG_0202f388) & 0x1FFF) - 0x1000) + (p->s).coord.x;
        s32 y = ((RANDOM(RNG_0202f388) & 0x1FFF) - 0x1000) + (p->s).coord.y;
        u8 k = RANDOM(RNG_0202f388) & 3;
        CreateBubble(x, y, k);
      }
      (p->s).mode[1]++;
    }
      /* fallthrough */
    case 1: {
      s32 v;
      UpdateMotionGraphic(&p->s);
      v = (p->s).d.y;
      if (v <= 0x6FF) {
        (p->s).d.y = v + 0x20;
      }
      (p->s).coord.y += (p->s).d.y;
      (p->s).unk_coord.y = (p->s).coord.y;
      if (CalcFromCamera(&gStageRun.vm.camera, &(p->s).coord) > 0x3000) {
        (p->s).flags &= ~DISPLAY;
        SET_SOLID_ROUTINE(p, ENTITY_EXIT);
      }
      break;
    }
  }
#else
  INCCODE("asm/solid/unk_53_die.inc");
#endif
}

static const struct Collision sCollision = {
  kind : DRP,
  faction : FACTION_ENEMY,
  LAYER(RECOIL_PUSHABLE),
  hitzone : 0xFF,
  remaining : 0,
  range : {PIXEL(0), PIXEL(0), PIXEL(32), PIXEL(32)},
};
