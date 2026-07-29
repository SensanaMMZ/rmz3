#include "stagerun.h"
#include "entity.h"
#include "global.h"
#include "mod.h"
#include "solid.h"
#include "syssav.h"

static void Seagulls_Init(struct Solid* p);
static void Seagulls_Update(struct Solid* p);
static void Seagulls_Die(struct Solid* p);

// clang-format off
const SolidRoutine gSeagullsRoutine = {
    [ENTITY_INIT] =      Seagulls_Init,
    [ENTITY_UPDATE] =    Seagulls_Update,
    [ENTITY_DIE] =       Seagulls_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteSolid,
    [ENTITY_EXIT] =      (SolidFunc)DeleteEntity,
};
// clang-format on

struct Solid* CreateSeagulls(struct Solid* friend, u8 t, u8 param_3) {
  struct Solid* p = (struct Solid*)AllocEntityFirst(gSolidHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 30;
    INIT_SOLID_ROUTINE(p, SOLID_SEAGULLS);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).flags2 |= WHITE_PAINTABLE;
    (p->s).invincibleID = (p->s).uniqueID;
    (p->s).unk_28 = &friend->s;
    (p->s).coord = (friend->s).coord;
    (p->s).work[0] = t;
    (p->s).work[1] = param_3;
  }
  return p;
}

void FUN_080dcd20(struct Solid* p);
void FUN_080dcdac(struct Solid* p);
void FUN_080dced4(struct Solid* p);

static void Seagulls_Init(struct Solid* p) {
  switch ((p->s).work[0]) {
    case 0: {
      FUN_080dcd20(p);
      break;
    }
    case 1: {
      FUN_080dcdac(p);
      break;
    }
    case 2: {
      FUN_080dced4(p);
      break;
    }
  }
}

void FUN_080dd02c(struct Solid* p);
void FUN_080dd11c(struct Solid* p);
void FUN_080dd364(struct Solid* p);

static void Seagulls_Update(struct Solid* p) {
  switch ((p->s).work[0]) {
    case 0: {
      FUN_080dd02c(p);
      break;
    }
    case 1: {
      FUN_080dd11c(p);
      break;
    }
    case 2: {
      FUN_080dd364(p);
      break;
    }
  }
}

void FUN_080dd400(struct Solid* p);
void FUN_080dd418(struct Solid* p);
void FUN_080dd430(struct Solid* p);

static void Seagulls_Die(struct Solid* p) {
  switch ((p->s).work[0]) {
    case 0: {
      FUN_080dd400(p);
      break;
    }
    case 1: {
      FUN_080dd418(p);
      break;
    }
    case 2: {
      FUN_080dd430(p);
      break;
    }
  }
}

struct Seagulls {
  OBJECT_HDR;
  // props (16bytes, offset: 0xB4..)
  s32 unk_b4_x;   // 0xB4
  u8 unk_b8[12];  // 0xB8
};

void FUN_080dcd20(struct Solid* p) {
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  if (!MOD_ENABLED(gSystemSavedataManager.mods, MOD_SEAGULLS)) {
    (p->s).flags &= ~DISPLAY;
    (p->s).flags &= ~FLIPABLE;
    EXIT_BODY(p);
    SET_SOLID_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }
  (p->s).unk_2c = (void*)CreateSeagulls(p, 1, 0);
  ((struct Seagulls*)p)->unk_b4_x = (p->s).coord.x;
  (p->s).work[2] = 0, (p->s).work[3] = 0;
  Seagulls_Update(p);
}

void FUN_080dcdac(struct Solid* p) {
  s32* pb4;
  u8* a;
  u8 fl;
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  InitNonAffineMotion(&p->s);
  {
    register u8 f0 asm("r1");
    register s32 d0 asm("r0");
    f0 = (p->s).flags;
    d0 = DISPLAY;
    d0 |= f0;
    {
      register s32 c2 asm("r1");
      c2 = FLIPABLE;
      d0 |= c2;
    }
    (p->s).flags = d0;
  }
  SetMotion(&p->s, 0xDA00);
  {
    u8* pr = (u8*)p + 0x49;
    *pr |= 0xC;
  }
  (p->s).taskCol = 0x1D;
  pb4 = &((struct Seagulls*)p)->unk_b4_x;
  *pb4 = (p->s).coord.x;
  (p->s).flags |= X_FLIP;
  ((p->s).spr).xflip = 1;
  a = (u8*)p + 0x4a;
  {
    u32 ten = 0x10;
    u8 b2 = *a;
    s32 msk = -0x11;
    msk &= b2;
    msk |= ten;
    *a = msk;
    ten &= (p->s).flags;
    fl = (u8)ten;
  }
  if (fl != 0) {
    struct Camera* cam = &gStageRun.vm.camera;
    s32* pb8;
    s32 r;
    (p->s).coord.x = cam->viewport.x - 0x8800;
    pb8 = (s32*)(a + 0x6e);
    r = ((RANDOM(RNG_0202f388) & 0x3F) << 8) + 0x2000;
    *pb8 = *pb4 + r;
    (p->s).d.x = 0;
  } else {
    struct Camera* cam = &gStageRun.vm.camera;
    s32* pb8;
    s32 r;
    (p->s).coord.x = cam->viewport.x + 0x87FF;
    pb8 = (s32*)((u8*)p + 0xb8);
    r = ((RANDOM(RNG_0202f388) & 0x3F) << 8) + 0x2000;
    *pb8 = *pb4 - r;
    (p->s).d.x = fl;
  }
  (p->s).work[2] = 0;
  Seagulls_Update(p);
}

INCASM("asm/solid/seagulls_p1.inc");

void FUN_080dd400(struct Solid* p) {
  SET_SOLID_ROUTINE(p, ENTITY_EXIT);
}


void FUN_080dd418(struct Solid* p) {
  SET_SOLID_ROUTINE(p, ENTITY_EXIT);
}


void FUN_080dd430(struct Solid* p) {
  SET_SOLID_ROUTINE(p, ENTITY_EXIT);
}

