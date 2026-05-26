#include "entity.h"
#include "global.h"
#include "motion.h"
#include "vfx.h"

struct VFX7 {
  struct Entity s;
  // props (16bytes, offset: 0x74..)
  struct Coord16 mag;
  u32 unk;
  u8* unk_7c;
  u8 work[4];
};
static_assert(sizeof(struct VFX7) == sizeof(struct VFX));

static void Ghost7_Init(struct Entity* p);
static void Ghost7_Update(struct VFX* p);
static void Ghost7_Die(struct VFX* p);

// clang-format off
const VFXRoutine gGhost7Routine = {
    [ENTITY_INIT] =      (VFXFunc)Ghost7_Init,
    [ENTITY_UPDATE] =    (VFXFunc)Ghost7_Update,
    [ENTITY_DIE] =       (VFXFunc)Ghost7_Die,
    [ENTITY_DISAPPEAR] = (VFXFunc)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

// ------------------------------------------------------------------------------------------------------------------------------------

void CreateGhost7(s32 x, s32 y, u8 param_3) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_007);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = param_3;
    (p->s).work[1] = param_3;
    (p->s).coord.x = x;
    (p->s).coord.y = y;
  }
}

// --------------------------------------------

static void FUN_080b4504(struct VFX7* p);
static void FUN_080b455c(struct VFX7* p);
static void FUN_080b45c0(struct VFX7* p);
static void FUN_080b4624(struct VFX7* p);
static void FUN_080b4688(struct VFX7* p);
static void FUN_080b46e0(struct VFX7* p);
static void FUN_080b4744(struct Entity* p);

static void Ghost7_Init(struct Entity* p) {
  // clang-format off
  static VFXFunc const sInitializers[] = {
      (VFXFunc)FUN_080b4504,
      (VFXFunc)FUN_080b455c,
      (VFXFunc)FUN_080b45c0,
      (VFXFunc)FUN_080b4624,
      (VFXFunc)FUN_080b45c0,
      (VFXFunc)FUN_080b4624,
      (VFXFunc)FUN_080b4688,
      (VFXFunc)FUN_080b46e0,
      (VFXFunc)FUN_080b4744,
      (VFXFunc)FUN_080b4744,
      (VFXFunc)FUN_080b4744,
  };
  // clang-format on
  (sInitializers[p->work[0]])((void*)p);
}

// --------------------------------------------

static void FUN_080b4788(struct VFX7* p);
static void FUN_080b4800(struct VFX7* p);
static void FUN_080b487c(struct VFX* p);

static void Ghost7_Update(struct VFX* p) {
  // clang-format off
  static VFXFunc const sUpdates[] = {
      (VFXFunc)FUN_080b4788,
      (VFXFunc)FUN_080b4788,
      (VFXFunc)FUN_080b4788,
      (VFXFunc)FUN_080b4788,
      (VFXFunc)FUN_080b4788,
      (VFXFunc)FUN_080b4788,
      (VFXFunc)FUN_080b4800,
      (VFXFunc)FUN_080b4800,
      FUN_080b487c,
      FUN_080b487c,
      FUN_080b487c,
  };
  // clang-format on
  (sUpdates[(p->s).work[0]])(p);
}

// --------------------------------------------

static void deleteGhost7(struct VFX* p);
static void FUN_080b491c(struct VFX* p);

static void Ghost7_Die(struct VFX* p) {
  // clang-format off
  static VFXFunc const sDeinitializers[] = {
      (VFXFunc)deleteGhost7,
      (VFXFunc)deleteGhost7,
      (VFXFunc)deleteGhost7,
      (VFXFunc)deleteGhost7,
      (VFXFunc)FUN_080b491c,
      (VFXFunc)FUN_080b491c,
      (VFXFunc)deleteGhost7,
      (VFXFunc)deleteGhost7,
      (VFXFunc)deleteGhost7,
      (VFXFunc)deleteGhost7,
      (VFXFunc)deleteGhost7,
  };
  // clang-format on
  (sDeinitializers[(p->s).work[0]])((void*)p);
}

// --------------------------------------------

static void FUN_080b4504(struct VFX7* p) {
  InitScalerotMotion1(&p->s);
  (p->s).flags |= DISPLAY;
  SetMotion(&p->s, MOTION(SM000_BATTLE_EFFECT, 14));
  UpdateMotionGraphic(&p->s);
  (p->s).spr.mag.x = 0x80;
  (p->s).spr.mag.y = 0x100;
  (p->mag).x = 0x100;
  (p->mag).y = 0x80;
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
  Ghost7_Update((void*)p);
}

static void FUN_080b455c(struct VFX7* p) {
  InitScalerotMotion1(&p->s);
  (p->s).flags |= DISPLAY;
  SetMotion(&p->s, MOTION(SM000_BATTLE_EFFECT, 14));
  UpdateMotionGraphic(&p->s);
  (p->s).spr.mag.x = 0x100;
  (p->s).spr.mag.y = 0x800;
  (p->mag).x = 0x100;
  (p->mag).y = 0x80;
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
  Ghost7_Update((void*)p);
}

static void FUN_080b45c0(struct VFX7* p) {
  InitScalerotMotion1(&p->s);
  (p->s).flags |= DISPLAY;
  SetMotion(&p->s, MOTION(SM000_BATTLE_EFFECT, 14));
  UpdateMotionGraphic(&p->s);
  (p->s).spr.mag.x = 0x80;
  (p->s).spr.mag.y = 0x100;
  (p->s).angle = 0x20;
  (p->mag).x = 0x100;
  (p->mag).y = 0x80;
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
  Ghost7_Update((void*)p);
}

static void FUN_080b4624(struct VFX7* p) {
  InitScalerotMotion1(&p->s);
  (p->s).flags |= DISPLAY;
  SetMotion(&p->s, MOTION(SM000_BATTLE_EFFECT, 14));
  UpdateMotionGraphic(&p->s);
  (p->s).spr.mag.x = 0x100;
  (p->s).spr.mag.y = 0x80;
  (p->s).angle = 0x20;
  (p->mag).x = 0x100;
  (p->mag).y = 0x80;
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
  Ghost7_Update((void*)p);
}

static void FUN_080b4688(struct VFX7* p) {
  InitScalerotMotion1(&p->s);
  (p->s).flags |= DISPLAY;
  SetMotion(&p->s, MOTION(SM000_BATTLE_EFFECT, 14));
  UpdateMotionGraphic(&p->s);
  (p->s).spr.mag.x = 0x80;
  (p->s).spr.mag.y = 0x80;
  (p->s).work[2] = 0;
  (p->mag).x = 0x80;
  (p->mag).y = 0x80;
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
  Ghost7_Update((void*)p);
}

static void FUN_080b46e0(struct VFX7* p) {
  InitScalerotMotion1(&p->s);
  (p->s).flags |= DISPLAY;
  SetMotion(&p->s, MOTION(SM000_BATTLE_EFFECT, 14));
  UpdateMotionGraphic(&p->s);
  (p->s).spr.mag.x = 0x80;
  (p->s).spr.mag.y = 0x80;
  (p->s).angle = 0x20;
  (p->s).work[2] = 0;
  (p->mag).x = 0x80;
  (p->mag).y = 0x80;
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
  Ghost7_Update((void*)p);
}

static void FUN_080b4744(struct Entity* p) {
  InitScalerotMotion1(p);
  p->flags |= DISPLAY;
  SetMotion(p, MOTION(SM000_BATTLE_EFFECT, 14));
  UpdateMotionGraphic(p);
  p->work[2] = 6;
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
  Ghost7_Update((void*)p);
}

static void FUN_080b4788(struct VFX7* p) {
  if (((p->s).work[0] & 1) != 0) {
    (p->s).spr.mag.x = (p->mag).x;
    (p->s).spr.mag.y = (p->mag).y;
  } else {
    (p->s).spr.mag.x = (p->mag).y;
    (p->s).spr.mag.y = (p->mag).x;
  }
  (p->mag).x -= 0x2A;
  (p->mag).y += 0x40;
  if ((p->mag).y > 0x200) {
    SET_VFX_ROUTINE(((struct VFX*)p), ENTITY_DIE);
  }
}

static void FUN_080b4800(struct VFX7* p) {
  if (((p->s).work[2]++ & 1) != 0) {
    (p->s).spr.mag.x = (p->mag).y;
    (p->s).spr.mag.y = (p->mag).x;
  } else {
    (p->s).spr.mag.x = (p->mag).x;
    (p->s).spr.mag.y = (p->mag).y;
  }
  (p->mag).x -= 0x14;
  (p->mag).y += 0x40;
  if ((p->mag).y > 0x200) {
    SET_VFX_ROUTINE(((struct VFX*)p), ENTITY_DIE);
  }
}

static void FUN_080b487c(struct VFX* p) {
  static const u8 angles[4] = {0x00, 0x40, 0x00, 0x00};
  static const u16 mag[3][3] = {
      {0x0060, 0x0060, 0x0030},
      {0x0080, 0x0080, 0x0040},
      {0x00A0, 0x00A0, 0x0050},
  };

  (p->s).work[2]--;
  (p->s).spr.mag.x = mag[(p->s).work[0] - 8][(p->s).work[2] >> 1];
  (p->s).spr.mag.y = mag[(p->s).work[0] - 8][(p->s).work[2] >> 1];
  (p->s).angle = angles[(p->s).work[2] >> 1];
  if ((p->s).work[2] == 0) {
    SET_VFX_ROUTINE(((struct VFX*)p), ENTITY_DIE);
  }
}

static void deleteGhost7(struct VFX* p) {
  (p->s).flags &= ~DISPLAY;
  SET_VFX_ROUTINE(p, ENTITY_EXIT);
}

static void FUN_080b491c(struct VFX* p) {
  if ((p->s).work[0] == 4) {
    CreateGhost7((p->s).coord.x, (p->s).coord.y, 3);
  } else {
    CreateGhost7((p->s).coord.x, (p->s).coord.y, 2);
  }
  (p->s).flags &= ~DISPLAY;
  SET_VFX_ROUTINE(p, ENTITY_EXIT);
}

static void unused_080b4960(s32 x, s32 y, bool8 n) {
  s32 dx;
  register s32 sx asm("r4");
  register s32 r asm("r5");
  register s32 d asm("r1");
  register s32 ret asm("r0");
  if (n) {
    dx = 0x2000;
  } else {
    r = -0x2000;
    dx = r;
  }
  sx = x + dx;
  r = FUN_08009f6c(sx, y);
  d = r - y;
  if (d < 0) {
    d = -d;
  }
  ret = 0xF00;
  asm volatile("" : "+r"(d), "+r"(ret) : "r"(r), "r"(sx));
}
