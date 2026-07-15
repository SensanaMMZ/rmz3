#include "collision.h"
#include "global.h"
#include "solid.h"
#include "vfx.h"

struct IcebonIceObject {
  OBJECT_HDR;
  // props (16bytes, offset: 0xB4..)
  s32 y;
  u8 unk_04[12];
};
static_assert(sizeof(struct IcebonIceObject) == sizeof(struct Solid));

static const u8 sInitModes[2];
static const struct Collision sCollisions[5];
static const motion_t sMotions[4];

static void IcebonIce_Init(struct IcebonIceObject* p);
static void IcebonIce_Update(struct Solid* p);
static void IcebonIce_Die(Object* p);

// clang-format off
const SolidRoutine gIcebonIceRoutine = {
    [ENTITY_INIT] =      (SolidFunc)IcebonIce_Init,
    [ENTITY_UPDATE] =    (SolidFunc)IcebonIce_Update,
    [ENTITY_DIE] =       (SolidFunc)IcebonIce_Die,
    [ENTITY_DISAPPEAR] = (SolidFunc)DeleteSolid,
    [ENTITY_EXIT] =      (SolidFunc)DeleteEntity,
};
// clang-format on

void icebon_080ca550(struct Entity* e, u8 n) {
  struct Entity* p = AllocEntityLast(gSolidHeaderPtr);
  if (p != NULL) {
    p->taskCol = 30;
    INIT_SOLID_ROUTINE(p, SOLID_ICEBON_ICE);
    p->tileNum = 0;
    p->palID = 0;
    p->flags2 |= WHITE_PAINTABLE;
    p->invincibleID = p->uniqueID;
    p->coord.x = (e->coord).x;
    p->coord.y = (e->coord).y - PIXEL(21);
    p->work[0] = n;
    p->unk_28 = e;
  }
}

// --------------------------------------------

static void onCollision(struct Body* body UNUSED, struct Coord* r1 UNUSED, struct Coord* r2 UNUSED) {
  // nop
  return;
}

static void IcebonIce_Init(struct IcebonIceObject* p) {
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  (p->s).mode[1] = sInitModes[(p->s).work[0]];
  (p->s).flags |= FLIPABLE;
  (p->s).flags |= DISPLAY;
  InitNonAffineMotion(&p->s);
  INIT_BODY(p, &sCollisions[0], 8, onCollision);
  p->y = (p->s).coord.y;
  IcebonIce_Update((void*)p);
}

// --------------------------------------------

void FUN_080ca700(struct Solid* p);
static void nop_080ca6fc(struct Solid* p);
void FUN_080ca76c(struct Solid* p);

void FUN_080ca7d8(struct IcebonIceObject* p);
void FUN_080ca880(struct Solid* p);
void FUN_080ca988(struct Solid* p);
void FUN_080caafc(struct Solid* p);
void FUN_080cab58(struct Solid* p);
void FUN_080cabe8(struct Solid* p);

static void IcebonIce_Update(struct Solid* p) {
  // clang-format off
  static const SolidFunc sUpdates1[6] = {
      FUN_080ca700,
      nop_080ca6fc,
      nop_080ca6fc,
      FUN_080ca76c,
      nop_080ca6fc,
      nop_080ca6fc,
  };
  // clang-format on

  // clang-format off
  static const SolidFunc sUpdates2[6] = {
      (SolidFunc)FUN_080ca7d8,
      FUN_080ca880,
      FUN_080ca988,
      FUN_080caafc,
      FUN_080cab58,
      FUN_080cabe8,
  };
  // clang-format on

  if ((p->body).status & BODY_STATUS_DEAD) {
    (p->s).flags2 &= ~ENTITY_HAZARD;
    SET_SOLID_ROUTINE(p, ENTITY_DIE);
    IcebonIce_Die((void*)p);
    return;
  }

  (sUpdates1[(p->s).mode[1]])(p);
  (sUpdates2[(p->s).mode[1]])(p);
}

// --------------------------------------------

static void IcebonIce_Die(Object* p) {
  struct Coord c;

  PlaySound(SE_ICE_BREAK);
  EXIT_BODY(p);
  (p->s).flags &= ~DISPLAY;

  c.x = (p->s).coord.x;
  c.y = (p->s).coord.y + PIXEL(16);
  FUN_080b81a0((struct Entity*)p, &c, (motion_t*)sMotions, 4);
  SET_SOLID_ROUTINE(p, ENTITY_EXIT);
}

// --------------------------------------------

static void nop_080ca6fc(struct Solid* p) {
  // nop
  return;
}

// --------------------------------------------

extern const struct Rect Rect_0836fd58;

// 0x080ca700
void FUN_080ca700(struct Solid* p) {
  struct Entity* icebon = (p->s).unk_28;
  if (icebon->mode[0] >= ENTITY_DISAPPEAR) {
    (p->s).flags &= ~DISPLAY;
    (p->s).flags &= ~FLIPABLE;
    EXIT_BODY(p);
    SET_SOLID_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }
  if (icebon->mode[0] >= ENTITY_DIE) {
    SET_SOLID_ROUTINE(p, ENTITY_DIE);
    (p->s).mode[1] = 0;
  }
}

// 0x080ca700 と全く同じ
void FUN_080ca76c(struct Solid* p) {
  struct Entity* icebon = (p->s).unk_28;
  if (icebon->mode[0] >= ENTITY_DISAPPEAR) {
    (p->s).flags &= ~DISPLAY;
    (p->s).flags &= ~FLIPABLE;
    EXIT_BODY(p);
    SET_SOLID_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }
  if (icebon->mode[0] >= ENTITY_DIE) {
    SET_SOLID_ROUTINE(p, ENTITY_DIE);
    (p->s).mode[1] = 0;
  }
}

// 0x080ca7d8
void FUN_080ca7d8(struct IcebonIceObject* p) {
  if ((p->body).hp >= 5) {
    SetMotion(&p->s, MOTION(SM017_ICEBON_ICE, 0));
  } else {
    SetMotion(&p->s, MOTION(SM017_ICEBON_ICE, 2));
  }
  UpdateMotionGraphic(&p->s);

  switch ((p->s).mode[2]) {
    case 0: {
      p->y = (p->s).coord.y;
      (p->s).unk_coord.y = (p->s).coord.y;
      (p->s).flags2 |= ENTITY_HAZARD;
      (p->s).size = (struct Rect*)&Rect_0836fd58;
      (p->s).hazardAttr = 0x801;
      SetDDP(&p->body, &sCollisions[1]);
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1: {
      s32 y;
      p->y -= PIXEL(1) / 2;
      y = p->y - (p->s).coord.y;
      if (y < 0) y += 7;
      (p->s).coord.y += y >> 3;
      if ((p->s).coord.y - (p->s).unk_coord.y <= -PIXEL(15)) (p->s).mode[1] = 1, (p->s).mode[2] = 0;
      break;
    }
  }
}

INCASM("asm/solid/icebon_ice_p2.inc");

static const struct Collision sCollisions[5] = {
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 0,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {0x0000, 0x0000, 0x0800, 0x0800},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 255,
      comboLv : 0,
      remaining : 1,
      layer : 0x00000001,
      range : {0x0000, -0x0700, 0x1C00, 0x0800},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 4,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {0x0000, 0x0400, 0x1C00, 0x1800},
    },
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 4,
      comboLv : 0,
      remaining : 1,
      layer : 0x00000001,
      range : {0x0000, 0x0200, 0x1400, 0x1400},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      LAYER(0xFFFFFFFF),
      hitzone : 4,
      hardness : HARDNESS_B3,
      remaining : 0,
      range : {0x0000, 0x0200, 0x1400, 0x1400},
    },
};

const struct Rect Rect_0836fd58 = {PIXEL(0), -PIXEL(3), PIXEL(24), PIXEL(16)};

static const u8 sInitModes[2] = {0, 3};

static const motion_t sMotions[4] = {
    MOTION(SM017_ICEBON_ICE, 6),
    MOTION(SM017_ICEBON_ICE, 7),
    MOTION(SM017_ICEBON_ICE, 8),
    MOTION(SM017_ICEBON_ICE, 6),
};
