#include "entity.h"
#include "global.h"
#include "mod.h"
#include "solid.h"

// 改造カードで出現する猫

static void Cat_Init(struct Solid* p);
static void Cat_Update(struct Solid* p);
static void Cat_Die(struct Solid* p);

// clang-format off
const SolidRoutine gCatRoutine = {
    [ENTITY_INIT] =      Cat_Init,
    [ENTITY_UPDATE] =    Cat_Update,
    [ENTITY_DIE] =       Cat_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteSolid,
    [ENTITY_EXIT] =      (SolidFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

void FUN_080dd4fc(struct Solid* p);
void FUN_080dd5e0(struct Solid* p);

static void Cat_Init(struct Solid* p) {
  u8 enabled;
  if ((p->s).work[0] == 0) {
    enabled = MOD_ENABLED(gSystemSavedataManager.mods, MOD_ORANGE_CAT);
  } else {
    enabled = MOD_ENABLED(gSystemSavedataManager.mods, MOD_TABBY_CAT);
  }
  if (!enabled) {
    (p->s).flags &= ~DISPLAY;
    (p->s).flags &= ~FLIPABLE;
    EXIT_BODY(p);
    SET_SOLID_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }

  if ((p->s).work[0] == 0) {
    FUN_080dd4fc(p);
  } else {
    FUN_080dd5e0(p);
  }
}

// --------------------------------------------

void FUN_080dd69c(struct Solid* p);
void FUN_080dd894(struct Solid* p);

static void Cat_Update(struct Solid* p) {
  if ((p->s).work[0] == 0) {
    FUN_080dd69c(p);
  } else {
    FUN_080dd894(p);
  }
}

// --------------------------------------------

static void Cat_Die(struct Solid* p) { SET_SOLID_ROUTINE(p, ENTITY_EXIT); }

// --------------------------------------------

void Cat_Update(struct Solid* p);

// 0x080DD4FC
void FUN_080dd4fc(struct Solid* p) {
  register s32 one asm("r6");
  register s32 r asm("r5");
  {
    u32 tbl = (u32)gSolidFnTable;
    EntityFunc** rt = (EntityFunc**)(tbl + (((p->s).id) << 2));
    one = 1;
    *(u32*)((p->s).mode) = one;
    (p->s).onUpdate = (void*)((*rt)[1]);
  }
  InitNonAffineMotion(&p->s);
  {
    register u8 fv asm("r0");
    register u8 fl asm("r1");
    fl = (p->s).flags;
    asm("" : "+r"(fl));
    fv = 1;
    fv |= fl;
    fl = 2;
    fv |= fl;
    (p->s).flags = fv;
  }
  {
    register u32 t asm("r0");
    t = RNG_0202f388 * 0x343FD + 0x269EC3;
    t <<= 1;
    RNG_0202f388 = t >> 1;
    r = t >> 0x11;
  }
  r &= one;
  if (r != 0) {
    register s32 z asm("r2");
    SetMotion(&p->s, MOTION(0xD8, 0x02));
    z = 0;
    (p->s).flags &= ~X_FLIP;
    ((p->s).spr).xflip = z;
    {
      register u8* oa asm("r2");
      s32 ov;
      s32 m11;
      oa = (u8*)p + 0x4a;
      ov = *oa;
      m11 = -0x11;
      m11 &= ov;
      *oa = m11;
    }
    (p->s).mode[1] = 2;
    (p->s).work[3] = one;
  } else {
    SetMotion(&p->s, MOTION(0xD8, 0x03));
    (p->s).flags &= ~X_FLIP;
    ((p->s).spr).xflip = r;
    {
      register u8* oa2 asm("r2");
      s32 ov2;
      s32 m112;
      oa2 = (u8*)p + 0x4a;
      ov2 = *oa2;
      m112 = -0x11;
      m112 &= ov2;
      *oa2 = m112;
    }
    (p->s).mode[1] = r;
    (p->s).work[3] = r;
  }
  (p->s).taskCol = 0x1D;
  (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y) + 0x100;
  {
    register s32* b asm("r1");
    b = (s32*)((u8*)p + 0xb4);
    *b = (p->s).coord.x;
    asm("" : "+r"(b));
    b += 1;
    asm("" : "+r"(b));
    *b = (p->s).coord.y;
  }
  Cat_Update(p);
}

// 0x080DD5E0
void FUN_080dd5e0(struct Solid* p) {
  register s32 one asm("r4");
  register s32 z asm("r6");
  u32 r;
  InitNonAffineMotion(&p->s);
  {
    register u8 fv asm("r0");
    register u8 k asm("r1");
    fv = (p->s).flags;
    one = 1;
    z = 0;
    asm("" : "+r"(z));
    fv |= one;
    k = FLIPABLE;
    fv |= k;
    (p->s).flags = fv;
  }
  SetMotion(&p->s, MOTION(0xD9, 0x00));
  r = RANDOM(RNG_0202f388) & one;
  SET_XFLIP(p, r);
  (p->s).taskCol = 0x1D;
  (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y) + 0x100;
  *(s32*)((u8*)p + 0xb4) = (p->s).coord.x;
  *(s32*)((u8*)p + 0xb8) = (p->s).coord.y;
  asm volatile("" ::"r"(z));
  SET_SOLID_ROUTINE(p, ENTITY_UPDATE);
  Cat_Update(p);
}

void FUN_080dd69c(struct Solid* p) {
  u32 t;
  u8 st;

  UpdateMotionGraphic(&p->s);
  switch ((p->s).mode[1]) {
    case 0:
      st = (p->s).motion.state;
      if (st != 3) {
        return;
      }
      if ((p->s).work[3] == 0 && (RANDOM(RNG_0202f388) & 1)) {
        SetMotion(&p->s, MOTION(0xD8, 0x01));
        (p->s).work[3]++;
        (p->s).mode[1] = st;
      } else {
        SetMotion(&p->s, MOTION(0xD8, 0x00));
        (p->s).work[3] = 0;
        (p->s).mode[1]++;
      }
      UpdateMotionGraphic(&p->s);
      t = RNG_0202f388 * 0x343FD + 0x269EC3;
      asm("" : "+l"(t));
      t <<= 1;
      RNG_0202f388 = t >> 1;
      (p->s).work[2] = ((t >> 17) & 0x3F) + 0x28;
      break;
    case 1:
      (p->s).coord.x += 0xC0;
      (p->s).work[2]--;
      if ((p->s).work[2] != 0xFF && (p->s).coord.x <= *(s32*)((u8*)p + 0xb4) + 0x4000 &&
          FUN_080098a4((p->s).coord.x + 0xC00, (p->s).coord.y - 0x800) == 0) {
        return;
      }
      SetMotion(&p->s, MOTION(0xD8, 0x02));
      UpdateMotionGraphic(&p->s);
      (p->s).mode[1]++;
      break;
    case 2:
      if ((p->s).motion.state != 3) {
        return;
      }
      if ((p->s).work[3] == 0 && (RANDOM(RNG_0202f388) & 1)) {
        SetMotion(&p->s, MOTION(0xD8, 0x00));
        (p->s).mode[1] = 1;
        (p->s).work[3]++;
      } else {
        SetMotion(&p->s, MOTION(0xD8, 0x01));
        (p->s).work[3] = 0;
        (p->s).mode[1]++;
      }
      UpdateMotionGraphic(&p->s);
      (p->s).work[2] = (RANDOM(RNG_0202f388) & 0x3F) + 0x28;
      break;
    case 3:
      (p->s).coord.x -= 0xC0;
      (p->s).work[2]--;
      if ((p->s).work[2] != 0xFF && (p->s).coord.x >= *(s32*)((u8*)p + 0xb4) - 0x4000 &&
          FUN_080098a4((p->s).coord.x - 0xC00, (p->s).coord.y - 0x800) == 0) {
        return;
      }
      SetMotion(&p->s, MOTION(0xD8, 0x03));
      UpdateMotionGraphic(&p->s);
      (p->s).mode[1] = 0;
      break;
  }
}

#include "motion.h"

void FUN_080dd894(struct Solid* p) {
  UpdateMotionGraphic(&p->s);
  if ((p->s).mode[1] != 0) {
    (p->s).work[2]--;
    if ((p->s).work[2] == 0xFF) {
      SetMotion(&p->s, MOTION(0xd9, 0x00));
      (p->s).mode[1] = 0;
    }
  } else if ((p->s).motion.state == 3) {
    (p->s).work[2] = (RANDOM(RNG_0202f388) & 0x7F) + 0x40;
    (p->s).mode[1]++;
  }
}
