#include "collision.h"
#include "entity.h"
#include "global.h"
#include "pickup.h"
#include "solid.h"
#include "stagerun.h"
#include "vfx.h"

static const struct Collision sCollisions[2];

static void Solid37_Init(struct Solid* p);
static void Solid37_Update(struct Solid* p);
static void Solid37_Die(struct Solid* p);

// clang-format off
const SolidRoutine gSolid37Routine = {
    [ENTITY_INIT] =      Solid37_Init,
    [ENTITY_UPDATE] =    Solid37_Update,
    [ENTITY_DIE] =       Solid37_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteSolid,
    [ENTITY_EXIT] =      (SolidFunc)DeleteEntity,
};
// clang-format on

void CreateSolid37(struct Solid* p) {
  struct Solid* s = (struct Solid*)AllocEntityFirst(gSolidHeaderPtr);
  if (s != NULL) {
    (s->s).taskCol = 30;
    INIT_SOLID_ROUTINE(s, SOLID_UNK_037);
    (s->s).tileNum = 0;
    (s->s).palID = 0;
    (s->s).flags2 |= WHITE_PAINTABLE;
    (s->s).invincibleID = (s->s).uniqueID;
    (s->s).unk_28 = &p->s;
    (s->s).coord = (p->s).coord;
    (s->s).work[0] = 1;
    (s->s).work[1] = 0;
  }
}

void FUN_080dc81c(struct Solid* p);
void FUN_080dc900(struct Solid* p);

static void Solid37_Init(struct Solid* p) {
  if ((p->s).work[0] == 0) {
    FUN_080dc81c(p);
  } else {
    FUN_080dc900(p);
  }
}

void FUN_080dc898(struct Solid* p);
void FUN_080dca60(struct Solid* p);

static void Solid37_Update(struct Solid* p) {
  if ((p->s).work[0] == 0) {
    FUN_080dc898(p);
  } else {
    FUN_080dca60(p);
  }
}

void FUN_080dc8e8(struct Solid* p);
void FUN_080dcb80(struct Solid* p);

static void Solid37_Die(struct Solid* p) {
  if ((p->s).work[0] == 0) {
    FUN_080dc8e8(p);
  } else {
    FUN_080dcb80(p);
  }
}

INCASM("asm/solid/unk_37_pre_a.inc");

void FUN_080dc898(struct Solid* p) {
  if ((u8)(--(p->s).work[3]) == 0xff) {
    CreateSolid37(p);
    RNG_0202f388 = LCG(RNG_0202f388);
    (p->s).work[3] = ((RNG_0202f388 >> 16) & 0x1f) + 8;
  }
  if ((p->s).work[2] > 0x1e) {
    (p->s).work[2] = 0;
  }
}

void FUN_080dc8e8(struct Solid* p) {
  SET_SOLID_ROUTINE(p, ENTITY_EXIT);
}

INCASM("asm/solid/unk_37_post_p1.inc");

void FUN_080dca60(struct Solid* p) {
  u32* ps = (u32*)((u8*)p + 0x8c);
  s32 st = *ps & 0x200;
  if (st != 0) {
    SET_SOLID_ROUTINE(p, ENTITY_DIE);
    Solid37_Die(p);
    return;
  }
  UpdateMotionGraphic(&p->s);
  (p->s).coord.x += (p->s).d.x;
  {
    s32 cy0 = (p->s).coord.y;
    s32 ndy = (p->s).d.y;
    s32 ny = cy0 + ndy;
    (p->s).coord.y = ny;
    ndy += 0x40;
    (p->s).d.y = ndy;
    switch ((p->s).mode[1]) {
      case 0:
        if (ndy > -0x40) {
          SetMotion(&p->s, MOTION(0xE6, 0x01));
          UpdateMotionGraphic(&p->s);
          (p->s).mode[1]++;
        }
        break;
      case 1:
        if ((p->s).motion.state == 3) {
          SetMotion(&p->s, MOTION(0xE6, 0x02));
          UpdateMotionGraphic(&p->s);
          if ((p->s).work[1] != 0) {
            ((p->s).spr).oam.priority = 1;
            CreatePickupItem(4, &(p->s).coord, 0);
          }
          (p->s).mode[1]++;
        }
        break;
      case 2:
        if (ny > *(s32*)((u8*)p + 0xb8)) {
          PlaySound(0xF);
          if ((p->s).work[1] == 0) {
            struct Entity* q = (p->s).unk_28;
            q->work[2] = st;
          }
          {
            register u8 f1 asm("r1");
            register s32 f2 asm("r0");
            f1 = (p->s).flags;
            f2 = 0xFE;
            f2 &= f1;
            {
              register s32 c2 asm("r1");
              c2 = 0xFD;
              f2 &= c2;
            }
            (p->s).flags = f2;
          }
          *ps = st;
          *(u32*)((u8*)p + 0x90) = st;
          *((u8*)p + 0x94) = st;
          (p->s).flags &= ~COLLIDABLE;
          SET_SOLID_ROUTINE(p, ENTITY_DISAPPEAR);
        }
        break;
    }
  }
}

void FUN_080dcb80(struct Solid* p) {
  struct Camera* cam;
  if ((p->s).mode[1] == 0) {
    struct Entity* q;
    SetMotion(&p->s, MOTION(SM230_FLYING_FISH, 0));
    (p->s).d.x = PIXEL(7) / 4;
    (p->s).d.y = -PIXEL(4);
    (p->s).work[2] = 0;
    q = (p->s).unk_28;
    q->work[2]++;
    EXIT_BODY(p);
    (p->s).mode[1]++;
  }
  UpdateMotionGraphic(&p->s);
  (p->s).coord.x += (p->s).d.x;
  (p->s).coord.y += (p->s).d.y;
  (p->s).d.y += PIXEL(1) / 4;
  (p->s).work[2]++;
  if ((p->s).work[2] & 1) {
    (p->s).flags &= ~DISPLAY;
  } else {
    (p->s).flags |= DISPLAY;
  }
  cam = &gStageRun.vm.camera;
  if ((p->s).coord.x > ((cam->viewport).x + PIXEL(136) - 1)) {
    SET_SOLID_ROUTINE(p, ENTITY_EXIT);
  }
}

static const struct Collision sCollisions[2] = {
    {
      kind : DRP,
      faction : FACTION_NEUTRAL,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 0x02,
      remaining : 0,
      range : {0x0000, 0x0000, 0x0E00, 0x0E00},
    },
    {
      kind : DRP,
      faction : FACTION_NEUTRAL,
      special : CS_BOSS,
      LAYER(0xFFFFFFFF),
      hitzone : 0x02,
      remaining : 0,
      range : {0x0000, 0x0000, 0x0E00, 0x0E00},
    },
};
