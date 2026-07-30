#include "collision.h"
#include "gfx.h"
#include "global.h"
#include "solid.h"
#include "stagerun.h"
#include "story.h"
#include "zero.h"
#include "physics.h"
#include "metatile.h"

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

// One instruction from matching, same tie as door_2d_blue: retail keeps
// the duplicated mode[2]=story stores in both arms (story stays in r2);
// agbcc copies story to r4 and cross-jumps the second arm into the
// non-flag2 tail. Four source shapes tried, all 77 vs 78.
NON_MATCH static void onCollision(struct Body* body, struct Coord* r1 UNUSED, struct Coord* r2 UNUSED) {
#if MODERN
  struct Solid* door = (struct Solid*)body->parent;
  struct Zero* z = (struct Zero*)(body->enemy)->parent;
  u8 flag2;
  u8 story;
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
    story = FLAG(gCurStory.s.gameflags, FLAG_2);
    if (story) {
      return;
    }
    if ((door->s).coord.x > (z->s).coord.x) {
      (door->s).mode[1] = 1;
      (door->s).mode[2] = story;
    } else {
      (door->s).mode[1] = 2;
      (door->s).mode[2] = story;
    }
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
#else
  INCCODE("asm/solid/door_gray_v_collision.inc");
#endif
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

void FUN_080d04cc(struct Solid* p) {
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
      SetMotion(&p->s, 0x7A02);
      {
        s32* tp = (s32*)((u8*)p + 0xbc);
        struct Entity** pb = (struct Entity**)((u8*)p + 0xb4);
        tp[0] = (*pb)->coord.x + 0x3800;
        asm("" : "+r"(pb));
        tp[1] = (*pb)->coord.y;
      }
      gCollisionManager.sweep |= 2;
      (p->s).work[2] = 0x40;
      (p->s).mode[2]++;
      break;
    }
    case 1:
      gCollisionManager.sweep = 0;
      (p->s).mode[2]++;
      // fallthrough
    case 2: {
      struct Entity** pb = (struct Entity**)((u8*)p + 0xb4);
      (*pb)->spr.xflip = 1;
      (*pb)->spr.oam.xflip = 1;
      (*pb)->flags |= X_FLIP;
      UpdateMotionGraphic(&p->s);
      if ((p->s).work[2] == 0x1C) {
        PlaySound(0x9C);
      }
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
        z->coord.x = z->coord.x + 0x100;
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
      PlaySound(0x9D);
      SetMotion(&p->s, 0x7A03);
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

void FUN_080d0664(struct Solid* p) {
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
      SetMotion(&p->s, 0x7A02);
      {
        s32* tp = (s32*)((u8*)p + 0xbc);
        struct Entity** pb = (struct Entity**)((u8*)p + 0xb4);
        tp[0] = (*pb)->coord.x + -0x3800;
        asm("" : "+r"(pb));
        tp[1] = (*pb)->coord.y;
      }
      gCollisionManager.sweep |= 2;
      (p->s).work[2] = 0x40;
      (p->s).mode[2]++;
      break;
    }
    case 1:
      gCollisionManager.sweep = 0;
      (p->s).mode[2]++;
      // fallthrough
    case 2: {
      struct Entity** pb = (struct Entity**)((u8*)p + 0xb4);
      (*pb)->spr.xflip = 0;
      (*pb)->spr.oam.xflip = 0;
      (*pb)->flags &= ~X_FLIP;
      UpdateMotionGraphic(&p->s);
      if ((p->s).work[2] == 0x1C) {
        PlaySound(0x9C);
      }
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
      PlaySound(0x9D);
      SetMotion(&p->s, 0x7A03);
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

void FUN_080d0804(struct Solid* p) {
  switch ((p->s).mode[2]) {
    case 0:
      (p->s).mode[2] = 1;
      // fallthrough
    case 1:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 3) {
        SetMotion(&p->s, MOTION(0x7a, 0x00));
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
