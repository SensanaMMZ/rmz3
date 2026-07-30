#include "collision.h"
#include "metatile.h"
#include "physics.h"
#include "stagerun.h"
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

// 0x080cafd0 -- blue 2D door: open, pan the camera to the door target, walk
// the captured entity through, then hand the camera back. Blocker (home
// transposition): p lands r5 vs retail r4 with the case-4 countdown temp and
// door-entity pointer riding r6/r7 (extra saves); the t8-trash and scratch-
// deref levers reduce but do not flip the assignment.
NON_MATCH void FUN_080cafd0(struct Solid* p) {
#if MODERN
  switch ((p->s).mode[2]) {
    case 0: {
      (p->body).status = 0;
      (p->body).prevStatus = 0;
      (p->body).invincibleTime = 0;
      (p->s).flags &= 0xFB;
      (p->s).flags2 &= 0xF7;
      SetMotion(&p->s, 0x1202);
      PlaySound(0x9E);
      {
        s32* tp = (s32*)((u8*)p + 0xbc);
        struct Entity** pb = (struct Entity**)((u8*)p + 0xb4);
        tp[0] = (*pb)->coord.x + 0x3800;
        tp[1] = (*pb)->coord.y;
      }
      (p->s).work[2] = 0x40;
      (p->s).mode[2]++;
      break;
    }
    case 1: {
      u32 g = (u8)((p->s).work[0] & 2);
      if (g == 0) {
        gCollisionManager.sweep = g;
      }
      (p->s).mode[2]++;
    }
      // fallthrough
    case 2: {
      struct Entity** pb = (struct Entity**)((u8*)p + 0xb4);
      (*pb)->spr.xflip = 1;
      *((u8*)(*pb) + 0x4a) |= 0x10;
      (*pb)->flags |= 0x10;
      UpdateMotionGraphic(&p->s);
      {
        s32 t = (p->s).work[2] - 1;
        (p->s).work[2] = t;
        if ((t << 24) != 0) {
          break;
        }
      }
      (p->s).work[2] = 0x38;
      (p->s).mode[2]++;
      break;
    }
    case 3: {
      UpdateMotionGraphic(&p->s);
      (*(struct Entity**)((u8*)p + 0xb4))->coord.x += 0x100;
      if ((p->s).work[2] == 0x1C) {
        u8* cam = (u8*)&gStageRun + 0xE8;
        *(s32**)(cam + 0x48) = (s32*)((u8*)p + 0xbc);
      }
      {
        s32 t = (p->s).work[2] - 1;
        (p->s).work[2] = t;
        if ((t << 24) != 0) {
          break;
        }
      }
      PlaySound(0x9F);
      SetMotion(&p->s, 0x1203);
      (p->s).work[2] = 0x20;
      (p->s).mode[2]++;
      break;
    }
    case 4: {
      struct Entity** pb;
      UpdateMotionGraphic(&p->s);
      {
        s32 t = (p->s).work[2] - 1;
        (p->s).work[2] = t;
        if ((t << 24) != 0) {
          break;
        }
      }
      pb = (struct Entity**)((u8*)p + 0xb4);
      {
        struct Entity* e = *pb;
        if (GetGroundMetatileAttr(e->coord.x, e->coord.y)) {
          struct Entity* e2 = *pb;
          e2->coord.y = FUN_0800a05c(e2->coord.x, e2->coord.y);
        }
      }
      {
        u8* g = (u8*)&gStageRun;
        struct Entity* z3;
        *(u16*)(g + 0x14) &= 0xFFFE;
        {
          u8* cam = g + 0xE8;
          z3 = *pb;
          *(s32**)(cam + 0x48) = (s32*)&z3->coord;
        }
        *((u8*)z3 + 0x119) = 0;
        (p->s).mode[1] = 3;
        (p->s).mode[2] = 0;
      }
      break;
    }
  }
#else
  INCCODE("asm/solid/door_blue_afd0.inc");
#endif
}

void FUN_080cb160(struct Solid* p) {
  switch ((p->s).mode[2]) {
    case 0: {
      {
        u8* w = (u8*)p + 0x8c;
        s32 z = 0;
        *(u32*)w = z;
        asm("" : "+r"(w));
        w += 4;
        *(u32*)w = z;
        asm("" : "+r"(w));
        w += 4;
        asm("" : "+r"(w));
        *w = z;
      }
      (p->s).flags &= 0xFB;
      (p->s).flags2 &= 0xF7;
      SetMotion(&p->s, 0x1202);
      PlaySound(0x9E);
      {
        s32* tp = (s32*)((u8*)p + 0xbc);
        struct Entity** pb = (struct Entity**)((u8*)p + 0xb4);
        tp[0] = (*pb)->coord.x + -0x3800;
        asm("" : "+r"(pb));
        tp[1] = (*pb)->coord.y;
      }
      (p->s).work[2] = 0x40;
      (p->s).mode[2]++;
      break;
    }
    case 1: {
      u8 t = (p->s).work[0] & 2;
      if (t == 0) {
        gCollisionManager.sweep = t;
      }
      (p->s).mode[2]++;
    }
      // fallthrough
    case 2: {
      struct Entity** pb = (struct Entity**)((u8*)p + 0xb4);
      (*pb)->spr.xflip = 0;
      (*pb)->spr.oam.xflip = 0;
      (*pb)->flags &= ~X_FLIP;
      UpdateMotionGraphic(&p->s);
      {
        s32 t = (p->s).work[2] - 1;
        (p->s).work[2] = t;
        if ((t << 24) != 0) {
          break;
        }
      }
      (p->s).work[2] = 0x38;
      (p->s).mode[2]++;
      break;
    }
    case 3: {
      UpdateMotionGraphic(&p->s);
      {
        struct Entity** pb = (struct Entity**)((u8*)p + 0xb4);
        struct Entity* z = *pb;
        z->coord.x = z->coord.x + -0x100;
      }
      if ((p->s).work[2] == 0x1C) {
        u8* cam2 = (u8*)&gStageRun.vm.camera;
        *(s32**)(cam2 + 0x48) = (s32*)((u8*)p + 0xbc);
      }
      {
        s32 t = (p->s).work[2] - 1;
        (p->s).work[2] = t;
        if ((t << 24) != 0) {
          break;
        }
      }
      PlaySound(0x9F);
      SetMotion(&p->s, 0x1203);
      (p->s).work[2] = 0x20;
      (p->s).mode[2]++;
      break;
    }
    case 4: {
      s32 z2;
      UpdateMotionGraphic(&p->s);
      {
        s32 t = (p->s).work[2] - 1;
        (p->s).work[2] = t;
        if ((t << 24) != 0) {
          break;
        }
      }
      {
        u8* pb = (u8*)p + 0xb4;
        {
          struct Entity* z1 = *(struct Entity**)pb;
          if ((u32)(GetGroundMetatileAttr(z1->coord.x, z1->coord.y) << 16) != 0) {
            struct Entity* za = *(struct Entity**)pb;
            s32 ny = FUN_0800a05c(za->coord.x, za->coord.y);
            (*(struct Entity**)pb)->coord.y = ny;
          }
        }
        {
          u8* g = (u8*)&gStageRun;
          struct Entity* z3;
          u32 v = *(u16*)(g + 0x14);
          u32 t = 0xFFFE;
          t &= v;
          asm volatile("movs %0, #0" : "=r"(z2));
          *(u16*)(g + 0x14) = t;
          {
            u8* cam = g + 0xE8;
            z3 = *(struct Entity**)pb;
            *(s32**)(cam + 0x48) = (s32*)&z3->coord;
          }
          *((u8*)z3 + 0x119) = z2;
        }
        (p->s).mode[1] = 3;
        (p->s).mode[2] = z2;
      }
      break;
    }
  }
}

#include "motion.h"
#include "story.h"

void FUN_080cb2f8(struct Solid* p) {
  switch ((p->s).mode[2]) {
    case 0:
      (p->s).mode[2] = 1;
      // fallthrough
    case 1:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 3) {
        SetMotion(&p->s, MOTION(0x12, 0x00));
        (p->s).mode[2]++;
      }
      break;
    case 2:
      UpdateMotionGraphic(&p->s);
      if (((p->s).work[0] & 2) && !FLAG(gCurStory.s.gameflags, FLAG_2)) {
        (p->s).mode[1] = 0;
        (p->s).mode[2] = 0;
      }
      break;
  }
}

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
