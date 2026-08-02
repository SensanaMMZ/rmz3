#include "collision.h"
#include "global.h"
#include "solid.h"

static void Solid47_Init(struct Solid* p);
static void Solid47_Update(struct Solid* p);
static void Solid47_Die(struct Solid* p);

// clang-format off
const SolidRoutine gAnatreCubeRoutine = {
    [ENTITY_INIT] =      Solid47_Init,
    [ENTITY_UPDATE] =    Solid47_Update,
    [ENTITY_DIE] =       Solid47_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteSolid,
    [ENTITY_EXIT] =      (SolidFunc)DeleteEntity,
};
// clang-format on

struct Solid* FUN_080deb10(struct Coord* c) {
  struct Solid* p = (struct Solid*)AllocEntityFirst(gSolidHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 30;
    INIT_SOLID_ROUTINE(p, SOLID_ANATRE_CUBE);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).work[0] = 0;
    (p->s).unk_coord.y = (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
  }
  return p;
}

struct Solid* FUN_080deb6c(u8 r0, struct Coord* c) {
  struct Solid* p = (struct Solid*)AllocEntityFirst(gSolidHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 30;
    INIT_SOLID_ROUTINE(p, SOLID_ANATRE_CUBE);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).work[0] = 1;
    (p->s).work[1] = r0;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
  }
  return p;
}

// --------------------------------------------

static void FUN_080dec04(struct Solid* p);
void FUN_080def4c(struct Solid* p);

static void Solid47_Init(struct Solid* p) {
  static const SolidFunc sInitializers[2] = {
      FUN_080dec04,
      FUN_080def4c,
  };
  (sInitializers[(p->s).work[0]])(p);
}

// --------------------------------------------

void FUN_080dec48(struct Solid* p);
void FUN_080defa8(struct Solid* p);

static void Solid47_Update(struct Solid* p) {
  static const SolidFunc sUpdates[2] = {
      FUN_080dec48,
      FUN_080defa8,
  };
  (sUpdates[(p->s).work[0]])(p);
}

// --------------------------------------------

static void Solid47_Die(struct Solid* p) {
  // nop
  return;
}

// --------------------------------------------

static void FUN_080dec04(struct Solid* p) {
  struct Coord* d;
  (p->s).flags |= FLIPABLE;
  (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y) - (PIXEL(32) - 1);
  d = &(p->s).d;
  d->x = d->y = 0;
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
}

INCASM("asm/solid/anatre_cube.inc");

// 0x080def4c
void FUN_080def4c(struct Solid* p) {
  {
    register u8 fv asm("r1");
    u8 t = (p->s).flags;
    fv = FLIPABLE;
    fv |= t;
    (p->s).flags = fv;
  }
  if ((p->s).work[1] != 4) {
    (p->s).unk_coord.x = 0x7002;
    (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y);
  } else {
    (p->s).unk_coord.x = 0x7006;
    (p->s).coord.x = FUN_0800a22c((p->s).coord.x, (p->s).coord.y);
  }
  (p->s).d.y = 0;
  (p->s).d.x = 0;
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
}

INCASM("asm/solid/anatre_cube_b.inc");

static const struct Collision sCollisions[2] = {
    {
      kind : DRP,
      faction : FACTION_NEUTRAL,
      special : 0,
      damage : 0,
      LAYER(RECOIL_PUSHABLE),
      hitzone : 0xFF,
      remaining : 0,
      range : {PIXEL(0), PIXEL(16), PIXEL(32), PIXEL(32)},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 255,
      hitzone : 0x00,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(0), PIXEL(16), PIXEL(4)},
    },
};

static const struct Rect sSize = {PIXEL(0), PIXEL(16), PIXEL(32), PIXEL(32)};
