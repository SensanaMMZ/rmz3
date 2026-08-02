#include "global.h"
#include "vfx.h"

void FUN_080c19b4(struct VFX* p);
void FUN_080c1a3c(struct VFX* p);
void FUN_080c1aec(struct VFX* p);
void FUN_080c1b34(struct VFX* p);

void CreateVFX57(struct Coord* c, u8 a1, u8 a2, s16 dx, s16 dy) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_057);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = a1;
    (p->s).work[1] = a2;
    (p->s).d.x = dx;
    (p->s).d.y = dy;
    (p->s).coord = *c;
  }
}

void VFX57_Init(struct VFX* p) {
  if ((p->s).work[0] == 0) {
    FUN_080c19b4(p);
  } else {
    FUN_080c1a3c(p);
  }
}


void VFX57_Update(struct VFX* p) {
  if ((p->s).work[0] == 0) {
    FUN_080c1aec(p);
  } else {
    FUN_080c1b34(p);
  }
}


void VFX57_Die(struct VFX* vfx) {
  SET_VFX_ROUTINE(vfx, ENTITY_EXIT);
}

// 0x080c19b4
void FUN_080c19b4(struct VFX* p) {
  s32 xf;
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
  InitNonAffineMotion(&p->s);
  (p->s).flags |= DISPLAY;
  (p->s).flags |= FLIPABLE;
  SetMotion(&p->s, (p->s).work[1] | MOTION(0x63, 0x00));
  xf = 0;
  if ((p->s).d.x > 0) {
    xf = 1;
  }
  SET_XFLIP(p, xf);
  VFX57_Update(p);
}

// 0x080c1a3c
void FUN_080c1a3c(struct VFX* p) {
  register s32 v asm("r2");
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
  InitNonAffineMotion(&p->s);
  {
    register u8 fv asm("r0");
    register s32 z asm("r5");
    u8 t = (p->s).flags;
    fv = DISPLAY;
    z = 0;
    asm volatile("" ::"r"(z));
    fv |= t;
    fv |= FLIPABLE;
    (p->s).flags = fv;
  }
  SetMotion(&p->s, MOTION(0x62, 0x03) + (p->s).work[1]);
  if ((p->s).work[1] != 1) {
    register s32 t asm("r1");
    t = 0;
    if ((p->s).d.x > 0) {
      t = 1;
    }
    v = t;
    if (v != 0) {
      (p->s).flags |= X_FLIP;
    } else {
      (p->s).flags &= ~X_FLIP;
    }
  } else {
    register s32 t asm("r1");
    t = 0;
    if ((p->s).d.x <= 0) {
      t = 1;
    }
    v = t;
    if (v != 0) {
      (p->s).flags |= X_FLIP;
    } else {
      (p->s).flags &= ~X_FLIP;
    }
  }
  {
    register s32 xf asm("r1");
    u8* oa;
    s32 sh4, ov, m11;
    xf = v;
    (p->s).spr.xflip = xf;
    oa = (u8*)p + 0x4a;
    sh4 = xf << 4;
    ov = *oa;
    m11 = -0x11;
    m11 &= ov;
    m11 |= sh4;
    *oa = m11;
    {
      s32 wz = 0;
      asm("" : "+r"(wz) : "r"(oa));
      (p->s).work[2] = wz;
    }
  }
  PlaySound(0x3f);
  VFX57_Update(p);
}

void FUN_080c1aec(struct VFX* p) {
  UpdateMotionGraphic(&p->s);
  (p->s).coord.x += (p->s).d.x;
  (p->s).coord.y += (p->s).d.y;
  if ((p->s).motion.state == MOTION_NEXT) {
    (p->s).flags &= ~DISPLAY;
    SET_VFX_ROUTINE(p, ENTITY_DIE);
  }
}

void FUN_080c1b34(struct VFX* p) {
  UpdateMotionGraphic(&p->s);
  (p->s).coord.x += (p->s).d.x;
  (p->s).coord.y += (p->s).d.y;
  (p->s).d.y += 0x40;
  if ((p->s).work[2]++ & 1) {
    (p->s).flags &= ~DISPLAY;
  } else {
    (p->s).flags |= DISPLAY;
  }
  if (FUN_080098a4((p->s).coord.x, (p->s).coord.y)) {
    SET_VFX_ROUTINE(p, ENTITY_DIE);
  }
}

void VFX57_Init(struct VFX* vfx);
void VFX57_Update(struct VFX* vfx);
void VFX57_Die(struct VFX* vfx);

// clang-format off
const VFXRoutine gVFX57Routine = {
    [ENTITY_INIT] =      VFX57_Init,
    [ENTITY_UPDATE] =    VFX57_Update,
    [ENTITY_DIE] =       VFX57_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on
