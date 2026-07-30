#include "collision.h"
#include "global.h"
#include "overworld.h"
#include "overworld_terrain.h"
#include "sound.h"
#include "stagerun.h"
#include "zero.h"
#include "solid.h"

enum ElevatorSkin {
  ELEVATOR_DEFAULT,
  ELEVATOR_WOOD,
  ELEVATOR_MMX,
};

struct ElevatorObject {
  OBJECT_HDR;
  // props
  struct Coord c;
  u8 unk_bc;
  u8 skin;  // 1: Wood, 2: MMX
  SoundIDS16 se;
  u8 unk_c0;
  u8 unk_c1;
  u16 unk_c2;
};
static_assert(sizeof(struct ElevatorObject) == sizeof(struct Solid));

#define level work[1]

static const struct Collision sCollisions[2];
static const struct Rect Rect_08370728;

static void BaseElevator_Init(struct Solid* p);
void BaseElevator_Update(struct Solid* p);
static void BaseElevator_Die(struct ElevatorObject* p);
static void BaseElevator_Disappear(struct ElevatorObject* p);

// clang-format off
const SolidRoutine gBaseElevatorRoutine = {
    [ENTITY_INIT] =      (SolidFunc)BaseElevator_Init,
    [ENTITY_UPDATE] =    (SolidFunc)BaseElevator_Update,
    [ENTITY_DIE] =       (SolidFunc)BaseElevator_Die,
    [ENTITY_DISAPPEAR] = (SolidFunc)BaseElevator_Disappear,
    [ENTITY_EXIT] =      (SolidFunc)DeleteEntity,
};
// clang-format on

// ------------------------------------------------------------------------------------------------------------------------------------

struct Solid* CreateResistanceBaseElevator(u8 lv) {
  struct ElevatorObject* p = (struct ElevatorObject*)AllocEntityFirst(gSolidHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 30;
    INIT_SOLID_ROUTINE(p, SOLID_BASE_ELEVATOR);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).work[0] = 0;
    (p->s).level = lv;
    p->skin = gSystemSavedataManager.elevator;
  }
  return (void*)p;
}

// 0x080cfc40
static void CreateResistanceBaseElevator2(struct Entity* e, u8 r1, u8 lv) {
  struct Entity* p = AllocEntityFirst(gSolidHeaderPtr);
  if (p != NULL) {
    p->taskCol = 30;
    INIT_SOLID_ROUTINE(p, SOLID_BASE_ELEVATOR);
    p->tileNum = 0;
    p->palID = 0;
    p->flags2 |= WHITE_PAINTABLE;
    p->invincibleID = p->uniqueID;
    p->unk_28 = e;
    p->work[0] = r1;
    p->level = lv;
  }
}

// --------------------------------------------

static void rBase_080cfd4c(struct ElevatorObject* p);
void FUN_080cff48(struct Solid* p);
void FUN_080d0008(struct Solid* p);
void FUN_080d0024(struct Solid* p);

static void BaseElevator_Init(struct Solid* p) {
  if ((p->s).work[0] != 0) {
    FUN_080cff48(p);
    return;
  }
  rBase_080cfd4c((void*)p);
}

void BaseElevator_Update(struct Solid* p) {
  if ((p->s).work[0] != 0) {
    FUN_080d0024(p);
  } else {
    FUN_080d0008(p);
  }
}

static void BaseElevator_Die(struct ElevatorObject* p) {
  if ((p->s).work[0] == 0) {
    if (p->se != MUS_NONE) {
      StopSound(p->se);
      p->se = MUS_NONE;
    }
  }
  SET_SOLID_ROUTINE(p, ENTITY_EXIT);
}

static void BaseElevator_Disappear(struct ElevatorObject* p) {
  if ((p->s).work[0] == 0) {
    if (p->se != MUS_NONE) {
      StopSound(p->se);
      p->se = MUS_NONE;
    }
  }
  DeleteSolid((void*)p);
}

// 0x080cfd4c
static void rBase_080cfd4c(struct ElevatorObject* p) {
  if (p->skin == ELEVATOR_DEFAULT) {
    LOAD_STATIC_GRAPHIC(SM115_ELEVATOR);
  }
  if (p->skin == ELEVATOR_WOOD) {
    LOAD_STATIC_GRAPHIC(SM137_ELEVATOR_WOOD);
  }
  if (p->skin == ELEVATOR_MMX) {
    LOAD_STATIC_GRAPHIC(SM138_ELEVATOR_MMX);
  }

  InitNonAffineMotion(&p->s);
  (p->s).flags |= DISPLAY;
  (p->s).flags |= FLIPABLE;
  SET_XFLIP(p, FALSE);
  (p->s).flags2 |= ENTITY_HAZARD;
  (p->s).size = &Rect_08370728;
  (p->s).hazardAttr = 0x2001;
  INIT_BODY(p, sCollisions, 0, NULL);
  p->c.x = 0x65000;
  p->c.y = 0x26000;
  (p->s).coord.x = p->c.x;
  (p->s).coord.y = p->c.y + (p->s).level * PIXEL(160);

  p->se = MUS_NONE;
  CreateResistanceBaseElevator2((void*)p, 1, 0);
  gOverworld.range.left = PIXEL(0);
  gOverworld.range.top = PIXEL(0);
  gOverworld.range.right = MAX_X;
  gOverworld.range.bottom = MAX_Y;
  p->unk_c0 = 0;
  p->unk_c1 = 5;
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  BaseElevator_Update((void*)p);
}

void FUN_080d0224(struct Solid* p);
void rBaseElevatorScript(struct Solid* p);

INCASM("asm/solid/base_elevator_p1.inc");

void FUN_080d0008(struct Solid* p) {
  if ((p->s).mode[1] != 0) {
    FUN_080d0224(p);
  } else {
    rBaseElevatorScript(p);
  }
}

INCASM("asm/solid/base_elevator_p2a.inc");

extern const motion_t sBaseElevatorMotions[6];
void rBaseElevatorScript(struct Solid* p);

void rBaseElevatorScript(struct Solid* p) {
  if ((p->s).mode[2] == 0) {
    if (*((u8*)p + 0xbd) == 0) {
      if ((p->s).work[1] <= 5) {
        SetMotion(&p->s, sBaseElevatorMotions[(p->s).work[1]]);
      } else {
        SetMotion(&p->s, sBaseElevatorMotions[0]);
      }
    } else if (*((u8*)p + 0xbd) == 1) {
      SetMotion(&p->s, 0x8901);
    } else {
      SetMotion(&p->s, 0x8A01);
    }
    UpdateMotionGraphic(&p->s);
    {
      s32 z2 = 0;
      register u8* ob asm("r1");
      register u32 o3 asm("r3");
      (p->s).d.y = z2;
      ob = (u8*)&gOverworld;
      asm("" : "+r"(ob));
      o3 = 0x2C014;
      asm("" : "+r"(o3));
      *(s32*)(ob + o3) = z2;
      o3 += 4;
      *(s32*)(ob + o3) = z2;
      {
        u32 o2 = 0x2C01C;
        asm("" : "+r"(o2));
        *(s32*)(ob + o2) = 0x3C0000;
      }
      o3 += 8;
      *(s32*)(ob + o3) = 0x280000;
    }
    (p->s).mode[2]++;
  }
  if (((p->body).status & 4) != 0) {
    u32 mz = *(u32*)(pZero2->s).mode & 0x00FFFF00;
    if (mz == 0) {
      register u8* ca asm("r1");
      register u32 w1raw asm("r0");
      register u32 w1 asm("r3");
      u32 lim;
      ca = (u8*)p + 0xc0;
      w1raw = (p->s).work[1];
      asm("" : "+r"(w1raw));
      w1 = w1raw;
      asm("" : "+r"(w1));
      lim = *ca;
      if (w1 > lim && (gStageRun.input & 0x40)) {
        (p->s).d.y = -0x200;
        (p->s).mode[1] = 1;
        (p->s).mode[2] = mz;
        goto upd;
      }
      {
        register u8* cb asm("r1");
        register u32 t8 asm("r0");
        cb = (u8*)p + 0xc1;
        t8 = (u8)w1;
        if (t8 < *cb) {
          if (gStageRun.input & 0x80) {
            register s32 zz asm("r1");
            (p->s).d.y = 0x200;
            zz = 0;
            asm("" : "+r"(zz));
            (p->s).mode[1] = 1;
            (p->s).mode[2] = zz;
          upd:
            BaseElevator_Update(p);
            return;
          }
        }
      }
    }
  }
  {
    s16* sp0 = (s16*)((u8*)p + 0xbe);
    if (*sp0 != -1) {
      u32 fv;
      StopSound(*sp0);
      fv = 0xFFFF;
      asm("" : "+r"(fv));
      *sp0 = fv;
    }
  }
}

INCASM("asm/solid/base_elevator_p2b.inc");

// ------------------------------------------------------------------------------------------------------------------------------------

static const struct Collision sCollisions[2] = {
    [0] = {
      kind : DDP,
      faction : FACTION_ENEMY,
      damage : 0xFF,
      remaining : 0,
      layer : 0x00000001,
      range : {PIXEL(0), PIXEL(8), PIXEL(16), PIXEL(18)},
    },
    [1] = {
      kind : DRP,
      faction : FACTION_ENEMY,
      damage : 0xFF,
      LAYER(0xFFFFFFFF),
      hitzone : 0x00,
      remaining : 0,
      range : {PIXEL(0), PIXEL(0), PIXEL(0), PIXEL(0)},
    },
};

// --------------------------------------------

// clang-format off
const motion_t sBaseElevatorMotions[6] = {
    MOTION(SM115_ELEVATOR, 6),
    MOTION(SM115_ELEVATOR, 5),
    MOTION(SM115_ELEVATOR, 4),
    MOTION(SM115_ELEVATOR, 3),
    MOTION(SM115_ELEVATOR, 2),
    MOTION(SM115_ELEVATOR, 1),
};
// clang-format on

// --------------------------------------------

static const struct Rect Rect_08370728 = {PIXEL(0), PIXEL(8), PIXEL(64), PIXEL(16)};
const struct Rect Rect_08370730 = {PIXEL(0), -PIXEL(72), PIXEL(64), PIXEL(16)};

#undef level
