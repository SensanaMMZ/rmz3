#include "global.h"
#include "trig.h"
#include "motion.h"
#include "entity/macros.h"
#include "vfx.h"

static const VFXFunc sUpdates[9];


void oz_080c39a0(struct Entity* e) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_064);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).unk_28 = e;
    (p->s).work[0] = 0;
  }
}

static const u8 sInitModes[7];
void Ghost64_Update(struct VFX* p);

void FUN_080c39e8(struct Entity* e) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_064);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).unk_28 = e;
    (p->s).work[0] = 1;
    {
      s32 ex = (e->coord).x;
      s32 x = (p->s).coord.x = ex + PIXEL(12);
      if ((e->flags & X_FLIP) != 0) {
        x = ex - PIXEL(12);
      }
      (p->s).coord.x = x;
    }
    (p->s).coord.y = (e->coord).y - PIXEL(32);
  }
}

void oz_Rekkoha_080c3a5c(struct Entity* e) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_064);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).unk_28 = e;
    (p->s).work[0] = 3;
    {
      s32 ex = (e->coord).x;
      s32 x = (p->s).coord.x = ex + PIXEL(12);
      if ((e->flags & X_FLIP) != 0) {
        x = ex - PIXEL(12);
      }
      (p->s).coord.x = x;
    }
    (p->s).coord.y = (e->coord).y - PIXEL(32);
  }
}

void ozMessenkou2(struct Entity* e) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_064);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 2;
    {
      s32 ex = (e->coord).x;
      s32 x = (p->s).coord.x = ex - PIXEL(5);
      if ((e->flags & X_FLIP) != 0) {
        x = ex + PIXEL(5);
      }
      (p->s).coord.x = x;
    }
    (p->s).coord.y = (e->coord).y + PIXEL(1);
  }
}

void oz_080c3b44(struct Entity* e) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_064);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 4;
    (p->s).coord.x = (e->coord).x;
    (p->s).coord.y = (e->coord).y - PIXEL(22);
  }
}

void oz_080c3b9c(struct Entity* e) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_064);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 5;
    (p->s).coord.x = (e->coord).x;
    (p->s).coord.y = (e->coord).y - PIXEL(22);
  }
}

void FUN_080c3bf4(s32 x, s32 y) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_064);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 6;
    (p->s).coord.x = x, (p->s).coord.y = y;
  }
}

void Ghost64_Init(struct VFX* p) {
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
  (p->s).mode[1] = sInitModes[(p->s).work[0]];
  (p->s).flags |= FLIPABLE;
  (p->s).flags |= DISPLAY;
  InitNonAffineMotion(&p->s);
  Ghost64_Update(p);
}

void Ghost64_Update(struct VFX* p) {
  (sUpdates[(p->s).mode[1]])(p);
}


void Ghost64_Die(struct VFX* p) {
  SET_VFX_ROUTINE(p, ENTITY_EXIT);
}

INCASM("asm/vfx/unk_64_p3_a.inc");

void FUN_080c3d84(struct VFX* vfx) {
  struct Sprite* spr = &((vfx->s).spr);
  struct Entity* e = (vfx->s).unk_28;
  register struct Sprite* espr asm("r9");
  espr = (struct Sprite*)((u8*)e + 0x34);
  switch ((vfx->s).mode[2]) {
    case 0:
      (vfx->s).work[2] = 0x3C;
      (vfx->s).d.x = gSineTable[60] / 32 + 0x138;
      (vfx->s).mode[2]++;
      /* fallthrough */
    case 1: {
      s32 v = (vfx->s).d.x;
      s32 d4 = (0x100 - v) / 16;
      s32 nx;
      s32 t;
      nx = v + d4;
      (vfx->s).d.x = nx;
      (vfx->s).work[3]++;
      (vfx->s).work[3] %= 3;
      {
        register s32 tt asm("r1");
        register s32 kx asm("r0");
        {
          register s32 wv asm("r1");
          wv = (vfx->s).work[3] * 16;
          kx = 0x110 - wv;
        }
        tt = nx;
        asm("" : "+r"(tt));
        tt *= kx;
        ((vfx->s).spr).mag.x = tt / 256;
      }
      {
        s32 ty = ((0x100 - (vfx->s).work[3] * 16) * (vfx->s).d.x) / 256;
        register u8* ay asm("r2");
        ay = (u8*)vfx + 0x52;
        *(u16*)ay = ty;
      }
      {
        struct Sprite* es2 = espr;
        spr->sprites = es2->sprites;
        spr->spriteIdx = es2->spriteIdx;
      }
      spr->xflip = (e->flags >> 4) & 1;
      spr->oam.xflip = (e->flags >> 4) & 1;
      t = (vfx->s).work[2] - 1;
      (vfx->s).work[2] = t;
      if (((t << 24) == 0) || (vfx->s).d.x <= 0x10F) {
        register u8 f1 asm("r1");
        register s32 f2 asm("r0");
        f1 = (vfx->s).flags;
        f2 = 0xFE;
        f2 &= f1;
        {
          register s32 c2 asm("r1");
          c2 = 0xFD;
          f2 &= c2;
        }
        (vfx->s).flags = f2;
        SET_VFX_ROUTINE(vfx, ENTITY_DISAPPEAR);
      }
      break;
    }
  }
}

#include "motion.h"

void FUN_080c3e98(struct VFX* p) {
  struct Entity* e = (p->s).unk_28;

  switch ((p->s).mode[2]) {
    case 0:
      SetMotion(&p->s, MOTION(0x80, 0x00));
      (p->s).work[2] = 0xe;
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      UpdateMotionGraphic(&p->s);
      if (--(p->s).work[2] == 0) {
        (p->s).flags &= ~DISPLAY;
        (p->s).flags &= ~FLIPABLE;
        SET_VFX_ROUTINE(p, ENTITY_DISAPPEAR);
      }
      break;
  }

  if (e->mode[0] > 1) {
    (p->s).flags &= ~DISPLAY;
    (p->s).flags &= ~FLIPABLE;
    SET_VFX_ROUTINE(p, ENTITY_DISAPPEAR);
  }
}

void FUN_080c3f1c(struct VFX* v) {
  u8 state;

  switch ((v->s).mode[2]) {
    case 0:
      SetMotion(&v->s, MOTION(0x80, 4));
      (v->s).mode[2]++;
      // fallthrough
    case 1:
      UpdateMotionGraphic(&v->s);
      state = (v->s).motion.state;
      if (state == 3) {
        (v->s).flags &= ~DISPLAY;
        (v->s).flags &= ~FLIPABLE;
        SET_VFX_ROUTINE(v, ENTITY_DISAPPEAR);
      }
      break;
  }
}

void FUN_080c3f74(struct VFX* p) {
  struct Entity* e = (p->s).unk_28;

  switch ((p->s).mode[2]) {
    case 0:
      SetMotion(&p->s, MOTION(0x80, 0x0a));
      (p->s).work[2] = 0xe;
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      UpdateMotionGraphic(&p->s);
      if (--(p->s).work[2] == 0) {
        (p->s).flags &= ~DISPLAY;
        (p->s).flags &= ~FLIPABLE;
        SET_VFX_ROUTINE(p, ENTITY_DISAPPEAR);
      }
      break;
  }

  if (e->mode[0] > 1) {
    (p->s).flags &= ~DISPLAY;
    (p->s).flags &= ~FLIPABLE;
    SET_VFX_ROUTINE(p, ENTITY_DISAPPEAR);
  }
}

u8 GetEntityPalID(struct Entity* p);

void FUN_080c3ffc(struct VFX* vfx) {
  switch ((vfx->s).mode[2]) {
    case 0:
      SetMotion(&vfx->s, 8);
      (vfx->s).mode[2]++;
      /* fallthrough */
    case 1:
      if ((vfx->s).motion.cmdIdx > 3) {
        ForceEntityPalette(&vfx->s, GetEntityPalID(&vfx->s) + 1);
      }
      UpdateMotionGraphic(&vfx->s);
      if ((vfx->s).motion.state == 4) {
        register u8 f1 asm("r1");
        register s32 f2 asm("r0");
        f1 = (vfx->s).flags;
        f2 = 0xFE;
        f2 &= f1;
        {
          register s32 c2 asm("r1");
          c2 = 0xFD;
          f2 &= c2;
        }
        (vfx->s).flags = f2;
        SET_VFX_ROUTINE(vfx, ENTITY_DISAPPEAR);
      }
      break;
  }
}

void FUN_080c4074(struct VFX* vfx) {
  switch ((vfx->s).mode[2]) {
    case 0:
      SetMotion(&vfx->s, 0x12);
      (vfx->s).mode[2]++;
      /* fallthrough */
    case 1:
      if ((vfx->s).motion.cmdIdx > 3) {
        ForceEntityPalette(&vfx->s, GetEntityPalID(&vfx->s) + 1);
      }
      UpdateMotionGraphic(&vfx->s);
      if ((vfx->s).motion.state == 4) {
        register u8 f1 asm("r1");
        register s32 f2 asm("r0");
        f1 = (vfx->s).flags;
        f2 = 0xFE;
        f2 &= f1;
        {
          register s32 c2 asm("r1");
          c2 = 0xFD;
          f2 &= c2;
        }
        (vfx->s).flags = f2;
        SET_VFX_ROUTINE(vfx, ENTITY_DISAPPEAR);
      }
      break;
  }
}

void FUN_080c40ec(struct VFX* v) {
  u8 state;

  switch ((v->s).mode[2]) {
    case 0:
      SetMotion(&v->s, MOTION(0x80, 6));
      (v->s).mode[2]++;
      // fallthrough
    case 1:
      UpdateMotionGraphic(&v->s);
      state = (v->s).motion.state;
      if (state == 3) {
        (v->s).flags &= ~DISPLAY;
        (v->s).flags &= ~FLIPABLE;
        SET_VFX_ROUTINE(v, ENTITY_DISAPPEAR);
      }
      break;
  }
}

INCASM("asm/vfx/unk_64_p3_c.inc");

void Ghost64_Init(struct VFX* p);

// clang-format off
const VFXRoutine gGhost64Routine = {
    [ENTITY_INIT] =      Ghost64_Init,
    [ENTITY_UPDATE] =    Ghost64_Update,
    [ENTITY_DIE] =       Ghost64_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

void FUN_080c3cbc(struct VFX* p);
void FUN_080c3d84(struct VFX* p);
void FUN_080c3e98(struct VFX* p);
void FUN_080c3f1c(struct VFX* p);
void FUN_080c3f74(struct VFX* p);
void FUN_080c3ffc(struct VFX* p);
void FUN_080c4074(struct VFX* p);
void FUN_080c40ec(struct VFX* p);
void FUN_080c4144(struct VFX* p);

// clang-format off
static const VFXFunc sUpdates[9] = {
    FUN_080c3cbc,
    FUN_080c3d84,
    FUN_080c3e98,
    FUN_080c3f1c,
    FUN_080c3f74,
    FUN_080c3ffc,
    FUN_080c4074,
    FUN_080c40ec,
    FUN_080c4144,
};
// clang-format on

static const u8 sInitModes[7] = {8, 2, 3, 4, 5, 6, 7};
