#include "collision.h"
#include "global.h"
#include "solid.h"

/*
  旧居住区などの蔦の燃える判定(グラフィックは別)
  他にも用途あるかも
*/

static const struct Collision sCollision;

// --------------------------------------------

void Solid3_Init(struct Solid* p);
void Solid3_Update(struct Solid* p);
void Solid3_Die(struct Solid* p);

// clang-format off
const SolidRoutine gSolid3Routine = {
    [ENTITY_INIT] =      Solid3_Init,
    [ENTITY_UPDATE] =    Solid3_Update,
    [ENTITY_DIE] =       Solid3_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteSolid,
    [ENTITY_EXIT] =      (SolidFunc)DeleteEntity,
};
// clang-format on

// 旧居住区などの蔦の燃える判定部分(グラフィックは別)
struct Solid* CreateLeafBurn(u8 r0) {
  struct Solid* p = (struct Solid*)AllocEntityFirst(gSolidHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 30;
    INIT_SOLID_ROUTINE(p, SOLID_UNK_003);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).work[0] = r0;
    (p->s).work[1] = 0;
  }
  return p;
}

INCASM("asm/solid/unk_03_p1a.inc");

void FUN_080cb4c0(struct Entity* p) {
  s32 y, y2;
  p->flags |= DISPLAY;
  InitNonAffineMotion(p);
  SetMotion(p, MOTION(SM032_UNK, 0));
  (p->spr).oam.priority = 0;
  if (p->work[0] == 0) {
    y = (p->coord).y;
  } else {
    y = (p->coord).y - PIXEL(480);
  }
  y >>= 12;
  y2 = y;
  if (y < 0) {
    y += 31;
  }
  p->taskCol = 31 - (y2 - (y >> 5) * 32);
  p->work[2] = (p->work[1] & 3) + 5;
}

INCASM("asm/solid/unk_03_p1b.inc");

void FUN_080cb980(struct Body* body, struct Coord* r1, struct Coord* r2);

void Solid3_Init(struct Solid* p) {
  (p->s).flags |= FLIPABLE;
  if ((p->s).work[1] == 0) {
    INIT_BODY(p, &sCollision, 0, FUN_080cb980);
    (p->s).flags2 &= ~WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
  } else {
    FUN_080cb4c0(&p->s);
  }
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  Solid3_Update(p);
}

INCASM("asm/solid/unk_03_p1c.inc");

void Solid3_Die(struct Solid* p) {}

INCASM("asm/solid/unk_03_p2.inc");

// --------------------------------------------

static const struct Collision sCollision = {
  kind : DRP,
  faction : FACTION_ENEMY,
  damage : 0,
  LAYER(0x442108),
  hitzone : 0xFF,
  remaining : 0,
  range : {PIXEL(0), PIXEL(0), -PIXEL(1), -PIXEL(1)},
};
