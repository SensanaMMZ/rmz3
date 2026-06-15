#include "collision.h"
#include "gfx.h"
#include "global.h"
#include "overworld.h"
#include "solid.h"

// 2Dドア(青色)

static const struct Collision sCollisions[2];

static void Door2DBlue_Init(struct Solid* p);
static void Door2DBlue_Update(struct Solid* p);
static void Door2DBlue_Die(struct Solid* p);

// clang-format off
const SolidRoutine gDoor2DBlueRoutine = {
    [ENTITY_INIT] =      Door2DBlue_Init,
    [ENTITY_UPDATE] =    Door2DBlue_Update,
    [ENTITY_DIE] =       Door2DBlue_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteSolid,
    [ENTITY_EXIT] =      (SolidFunc)DeleteEntity,
};
// clang-format on

NON_MATCH static void Door2DBlue_Init(struct Solid* p) {
#if MODERN
  bool8 xflip;

  InitNonAffineMotion(&p->s);
  if ((p->s).work[1] == 0) {
    struct Solid* otherside = (struct Solid*)AllocEntityFirst(gSolidHeaderPtr);
    if (otherside == NULL) {
      return;
    }
    (p->s).coord.x += PIXEL(8);
    (p->s).coord.y += PIXEL(9);
    (otherside->s).taskCol = 30;
    INIT_SOLID_ROUTINE(otherside, SOLID_DOOR_2D_BLUE);
    (otherside->s).tileNum = 0;
    (otherside->s).palID = 0;
    (otherside->s).flags2 |= WHITE_PAINTABLE;
    (otherside->s).invincibleID = (otherside->s).uniqueID;
    (otherside->s).work[1] = 1;
    (otherside->s).unk_28 = &p->s;
    (otherside->s).coord.x = (p->s).coord.x - PIXEL(1);
    (otherside->s).coord.y = (p->s).coord.y;
    if ((W_TERRAIN_V2.id & 0x7F) == STAGE_OCEAN) {
      wStaticMotionPalIDs[SM018_DOOR_2D_BLUE] = 10;
    }
    LOAD_STATIC_GRAPHIC(SM018_DOOR_2D_BLUE);
  } else {
    SetMotion(&p->s, MOTION(SM018_DOOR_2D_BLUE, 0));
    xflip = TRUE;
    (p->s).flags |= X_FLIP;
    (p->s).spr.xflip = xflip;
    (p->s).spr.oam.xflip |= TRUE;
  }

  (p->s).spr.oam.priority = 1;
  (p->s).flags |= DISPLAY;
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  (p->s).mode[1] = 0;
  (p->s).mode[2] = 0;
  Door2DBlue_Update(p);
#else
  INCCODE("asm/wip/Door2DBlue_Init.inc");
#endif
}

// --------------------------------------------

static void FUN_080caf7c(struct Solid* p);
void FUN_080cafd0(struct Solid* p);
void FUN_080cb160(struct Solid* p);
void FUN_080cb2f8(struct Solid* p);

static void Door2DBlue_Update(struct Solid* p) {
  static const SolidFunc sUpdates[4] = {
      FUN_080caf7c,
      FUN_080cafd0,
      FUN_080cb160,
      FUN_080cb2f8,
  };

  if ((p->s).work[1] != 0) {
    struct Entity* friend = (p->s).unk_28;
    if (friend->mode[0] >= 2) {
      SET_SOLID_ROUTINE(p, ENTITY_DIE);
      Door2DBlue_Die(p);
    } else {
      (p->s).spr.sprites = (friend->spr).sprites;
      (p->s).spr.spriteIdx = (friend->spr).spriteIdx;
    }
    return;
  }
  (sUpdates[(p->s).mode[1]])(p);
}

static void Door2DBlue_Die(struct Solid* p) {
  EXIT_BODY(p);
  (p->s).flags &= ~DISPLAY;
  SET_SOLID_ROUTINE(p, ENTITY_EXIT);
}

#if MODERN
static void onCollision(struct Body* body, struct Coord* r1 UNUSED, struct Coord* r2 UNUSED) {
  u8 flag2;
  struct Solid* door = (struct Solid*)body->parent;
  struct Zero* z = (struct Zero*)(body->enemy)->parent;
  if ((z->s).kind != ENTITY_PLAYER) {
    return;
  }
  if ((door->s).coord.y < (z->s).coord.y) {
    return;
  }
  if ((door->s).coord.y - (z->s).coord.y > PIXEL(8)) {
    return;
  }
  flag2 = (door->s).work[0] & 2;
  if (flag2) {
    u8 story = FLAG(gCurStory.s.gameflags, FLAG_2);
    if (story) {
      return;
    }
    if ((door->s).coord.x > (z->s).coord.x) {
      (door->s).mode[1] = 1;
    } else {
      (door->s).mode[1] = 2;
    }
    (door->s).mode[2] = story;
  } else {
    if ((door->s).coord.x > (z->s).coord.x) {
      if ((door->s).work[0] & 1) {
        return;
      }
      (door->s).mode[1] = 1;
    } else {
      if (!((door->s).work[0] & 1)) {
        return;
      }
      (door->s).mode[1] = 2;
    }
    (door->s).mode[2] = flag2;
  }
  z->isAreaChange = TRUE;
  gStageRun.vm.unk_004 |= 1;
  *(struct Zero**)door->props.raw = z;
}
#else
NAKED static void onCollision(struct Body* body, struct Coord* r1 UNUSED, struct Coord* r2 UNUSED) {
  INCCODE("asm/wip/door_2d_blue_oncollision.inc");
}
#endif

static void FUN_080caf7c(struct Solid* p) {
  switch ((p->s).mode[2]) {
    case 0: {
      SetMotion(&p->s, MOTION(SM018_DOOR_2D_BLUE, 0));
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

INCASM("asm/solid/unk_02.inc");

// --------------------------------------------

static const struct Collision sCollisions[2] = {
    {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 255,
      atkType : 0x00,
      nature : BODY_NATURE_B7,
      comboLv : 0x00,
      remaining : 0,
      layer : 0x00000001,
      range : {0x0000, -0x2000, 0x2200, 0x4200},
    },
    {
      kind : DRP,
      faction : FACTION_ENEMY,
      damage : 255,
      LAYER(0xFFFFFFFF),
      hitzone : 0x00,
      remaining : 0,
      range : {0x0000, 0x0000, 0x0000, 0x0000},
    },
};
