#include "collision.h"
#include "global.h"
#include "physics.h"
#include "solid.h"
#include "stagerun.h"
#include "vfx.h"

struct Solid8Object {
  OBJECT_HDR;
  // props (16bytes, offset: 0xB4..)
  s32 y;
  u8 unk_04[12];
};
static_assert(sizeof(struct Solid8Object) == sizeof(struct Solid));

static const struct Rect sSize;
static const u8 sInitMode[4];

static void LavaRiverPlatform_Init(struct Solid8Object* p);
static void LavaRiverPlatform_Update(struct Solid* p);
static void LavaRiverPlatform_Die(struct Solid* p);

// clang-format off
const SolidRoutine gLavaRiverPlatformRoutine = {
    [ENTITY_INIT] =      (SolidFunc)LavaRiverPlatform_Init,
    [ENTITY_UPDATE] =    (SolidFunc)LavaRiverPlatform_Update,
    [ENTITY_DIE] =       (SolidFunc)LavaRiverPlatform_Die,
    [ENTITY_DISAPPEAR] = (SolidFunc)DeleteSolid,
    [ENTITY_EXIT] =      (SolidFunc)DeleteEntity,
};
// clang-format on

void CreateLavaRiverPlatform(u32 x, u32 y) {
  struct Solid* p = (struct Solid*)AllocEntityLast(gSolidHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 30;
    INIT_SOLID_ROUTINE(p, SOLID_LAVA_RIVER_PLATFORM);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).work[0] = 0;
    (p->s).coord.x = x;
    (p->s).coord.y = y;
  }
}

// --------------------------------------------

static void LavaRiverPlatform_Init(struct Solid8Object* p) {
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  (p->s).mode[1] = sInitMode[(p->s).work[0]];
  (p->s).flags |= FLIPABLE;
  (p->s).flags |= DISPLAY;
  InitNonAffineMotion(&p->s);
  (p->s).flags2 |= ENTITY_HAZARD;
  (p->s).size = (struct Rect*)&sSize;
  (p->s).hazardAttr = 0x2001;
  p->y = PIXEL(40);
  LavaRiverPlatform_Update((void*)p);
}

// --------------------------------------------

static void nop_080ccef8(struct Solid* p);
void FUN_080ccefc(struct Solid* p);
void FUN_080cd03c(struct Solid* p);

static void LavaRiverPlatform_Update(struct Solid* p) {
  static const SolidFunc sUpdates1[2] = {
      nop_080ccef8,
      nop_080ccef8,
  };
  static const SolidFunc sUpdates2[2] = {
      FUN_080ccefc,
      FUN_080cd03c,
  };
  (sUpdates1[(p->s).mode[1]])(p);
  (sUpdates2[(p->s).mode[1]])(p);
}

// --------------------------------------------

static void LavaRiverPlatform_Die(struct Solid* p) {
  (p->s).flags2 &= ~ENTITY_HAZARD;
  SET_SOLID_ROUTINE(p, ENTITY_EXIT);
}

// --------------------------------------------

static void nop_080ccef8(struct Solid* p) { return; }

s32 FUN_0800a40c(s32 x, s32 y);

void FUN_080ccefc(struct Solid* p) {
  register s32 m asm("r4");
  m = (p->s).mode[2];
  switch (m) {
    case 0:
      PlaySound(0x77);
      (p->s).d.y = m;
      (p->s).work[2] = m;
      (p->s).unk_coord.x = m;
      SetMotion(&p->s, 0x3B00);
      UpdateMotionGraphic(&p->s);
      (p->s).mode[2]++;
      /* fallthrough */
    case 1: {
      s32 fl;
      (p->s).d.y += 0x40;
      if ((p->s).d.y > 0x700) {
        (p->s).d.y = 0x700;
      }
      {
        s32 ny = (p->s).coord.y + (p->s).d.y;
        s32 po;
        (p->s).coord.y = ny;
        po = PushoutToUp2((p->s).coord.x, ny + ((struct Solid8Object*)p)->y);
        if (po < 0) {
          (p->s).coord.y += po;
        }
      }
      fl = (p->s).coord.y;
      fl += ((struct Solid8Object*)p)->y;
      {
        s32 lim = (p->s).coord.y + 0x1000;
        if (fl < lim) {
          fl = lim;
        }
      }
      {
        s32 po2 = FUN_0800a40c((p->s).coord.x, fl + 0x800);
        if (po2 != 0) {
          (p->s).coord.x += po2;
        }
      }
      (p->s).unk_coord.x += 1;
      {
        s32 w = (p->s).work[2] + 1;
        (p->s).work[2] = w;
        if ((w & 3) == 0) {
          if (CalcFromCamera(&gStageRun.vm.camera, &(p->s).coord) <= 0x7FF) {
            if ((p->s).unk_coord.x <= 0x77) {
              struct Coord c;
              s32 bx = (p->s).coord.x - 0x2800;
              c.x = bx;
              c.x = (RANDOM(RNG_0202f388) % 0x2800) + bx;
              c.y = fl - 0x400;
              CreateParticle(&c, 1, 0);
            }
          }
        }
      }
      ((struct Solid8Object*)p)->y -= 0x60;
      if (((struct Solid8Object*)p)->y < -0x1000) {
        SET_SOLID_ROUTINE(p, ENTITY_DIE);
      }
      break;
    }
  }
}

// 0x080CD03C
void FUN_080cd03c(struct Solid* p) {
  u8 m = (p->s).mode[2];
  switch (m) {
    case 0:
      (p->s).work[2] = m;
      (p->s).d.y = m;
      SetMotion(&p->s, MOTION(0x3B, 0x00));
      (p->s).mode[2]++;
    case 1: {
      s32 hit;
      (p->s).d.y += 0x40;
      if ((p->s).d.y > 0x700) {
        (p->s).d.y = 0x700;
      }
      (p->s).coord.y += (p->s).d.y;
      hit = PushoutToUp2((p->s).coord.x, (p->s).coord.y + *(s32*)((u8*)p + 0xb4));
      if ((p->s).work[2] == 0) {
        (p->s).d.y = 0x80;
        if (hit == 0) {
          (p->s).work[2] = 1;
        }
      } else if (hit < 0) {
        (p->s).coord.y += hit;
        (p->s).mode[1] = 0;
        (p->s).mode[2] = 0;
      }
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}

// --------------------------------------------

static const struct Rect sSize = {PIXEL(0), PIXEL(24), PIXEL(48), PIXEL(48)};

static const u8 sInitMode[4] = {1, 0, 0, 0};
