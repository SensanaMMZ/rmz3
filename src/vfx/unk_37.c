#include "global.h"
#include "stagerun.h"
#include "vfx.h"
#include "palette_animation.h"

// ベビーエルフ関連

void VFX37_Init(struct VFX* vfx);
void VFX37_Update(struct VFX* vfx);
void VFX37_Die(struct VFX* vfx);

// clang-format off
const VFXRoutine gVFX37Routine = {
    [ENTITY_INIT] =      VFX37_Init,
    [ENTITY_UPDATE] =    VFX37_Update,
    [ENTITY_DIE] =       VFX37_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

void FUN_080bc540(s32 x1, s32 y1, s32 x2, s32 y2) {
  struct Entity* p = AllocEntityLast(gVFXHeaderPtr);
  if (p != NULL) {
    p->taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_037);
    p->tileNum = 0;
    p->palID = 0;
    p->work[0] = 0;
    p->coord.x = x1;
    p->coord.y = y1;
    p->d.x = x2;
    p->d.y = y2;
  }
}

void FUN_080bc594(s32 x1, s32 y1, s32 x2, s32 y2, u8 n) {
  struct Entity* p = AllocEntityLast(gVFXHeaderPtr);
  if (p != NULL) {
    p->taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_037);
    p->tileNum = 0;
    p->palID = 0;
    p->work[0] = 1;
    p->coord.x = x1;
    p->coord.y = y1;
    p->d.x = x2;
    p->d.y = y2;
    p->work[2] = n;
  }
}

void FUN_080bc5fc(struct Entity* e, u8 n) {
  s32 i;
  for (i = 0; i < 6; i++) {
    struct Entity* p = AllocEntityLast(gVFXHeaderPtr);
    if (p != NULL) {
      p->taskCol = 1;
      INIT_VFX_ROUTINE(p, VFX_UNK_037);
      p->tileNum = 0;
      p->palID = 0;
      p->work[0] = 2;
      p->unk_28 = e;
      p->work[2] = i;
      p->work[3] = n + i;
    }
  }
}

void FUN_080bc660(s32 x, s32 y) {
  struct Entity* p = AllocEntityLast(gVFXHeaderPtr);
  if (p != NULL) {
    p->taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_037);
    p->tileNum = 0;
    p->palID = 0;
    p->work[0] = 3;
    p->coord.x = x;
    p->coord.y = y;
  }
}

extern const VFXFunc PTR_ARRAY_0836edd4[7];

#include "trig.h"

void FUN_080bc6ac(struct Entity* e, s32 x, s32 y, s32 speed, u8 angle) {
  struct VFX* p = (struct VFX*)AllocEntityLast(gVFXHeaderPtr);

  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, 37);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 4;
    (p->s).coord.x = x;
    (p->s).coord.y = y;
    (p->s).d.x = Cos(angle, speed);
    (p->s).d.y = -Sin(angle, speed);
    (p->s).unk_28 = e;
    *((u8*)e + 0xCF) += 1;
  }
}

void FUN_080bc758(s32 x, s32 y) {
  struct Entity* p = AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    p->taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_037);
    p->tileNum = 0;
    p->palID = 0;
    p->work[0] = 5;
    p->coord.x = x;
    p->coord.y = y;
  }
}

void FUN_080bc7a4(s32 x, s32 y, s32 speed, u8 angle, u8 n) {
  struct VFX* p = (struct VFX*)AllocEntityLast(gVFXHeaderPtr);

  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, 37);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 6;
    (p->s).coord.x = x;
    (p->s).coord.y = y;
    (p->s).d.x = Cos(angle, speed);
    (p->s).d.y = -Sin(angle, speed);
    (p->s).work[2] = n;
  }
}

extern const u8 u8_ARRAY_0836edf0[7];

void VFX37_Init(struct VFX* vfx) {
  SET_VFX_ROUTINE(vfx, ENTITY_UPDATE);
  (vfx->s).mode[1] = u8_ARRAY_0836edf0[(vfx->s).work[0]];
  (vfx->s).flags |= FLIPABLE;
  (vfx->s).flags |= DISPLAY;
  InitNonAffineMotion(&vfx->s);
  VFX37_Update(vfx);
}

void VFX37_Update(struct VFX* vfx) {
  (PTR_ARRAY_0836edd4[(vfx->s).mode[1]])(vfx);
}


void VFX37_Die(struct VFX* vfx) {
  SET_VFX_ROUTINE(vfx, ENTITY_EXIT);
}

// 0x080BC8C0
void FUN_080bc8c0(struct VFX* p) {
  switch ((p->s).mode[2]) {
    case 0:
      (p->s).taskCol = 0x19;
      SetMotion(&p->s, MOTION(0x30, 0x01));
      (p->s).work[2] = 0x20;
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 1: {
      s32 w;
      u8 wu;
      register s32 z asm("r2");
      UpdateMotionGraphic(&p->s);
      (p->s).coord.x += (p->s).d.x;
      (p->s).d.y += 3;
      (p->s).coord.y += (p->s).d.y;
      w = (p->s).work[2] - 1;
      z = 0;
      asm("" : "+r"(z));
      (p->s).work[2] = w;
      wu = w;
      if (wu <= 7) {
        if ((w & 2) == 0) {
          (p->s).flags |= DISPLAY;
        } else {
          (p->s).flags &= ~DISPLAY;
        }
      } else if (wu <= 0xF) {
        if ((w & 1) == 0) {
          (p->s).flags |= DISPLAY;
        } else {
          (p->s).flags &= ~DISPLAY;
        }
      }
      if ((p->s).work[2] == 0) {
        register u8 f asm("r0");
        register u8 t asm("r1");
        register u8 k2 asm("r1");
        t = (p->s).flags;
        f = 0xFE;
        f &= t;
        asm volatile("" ::"r"(t));
        k2 = 0xFD;
        f &= k2;
        (p->s).flags = f;
        SET_VFX_ROUTINE(p, 3);
      }
      break;
    }
  }
}

INCASM("asm/vfx/unk_37_post.inc");

extern const s16 s16_ARRAY_0836edfe[6];

// Baby elf orbit: converge toward screen center, flicker, despawn with the
// parent. Logic verified; parked on an allocation-cascade tie: retail pools
// the SetMotion const into r0 with an arg copy, keeps the camera ptr in ip,
// and routes both /2 roundings through r0 with a copy-back - agbcc folds all
// three in-place (pin/anchor either gets ignored or adds a u16 re-truncation).
NON_MATCH void FUN_080bca5c(struct VFX* vfx) {
#if MODERN
  struct Entity* e = (vfx->s).unk_28;
  switch ((vfx->s).mode[2]) {
    case 0:
      SetMotion(&vfx->s, MOTION(0x33, 0x02) + (vfx->s).work[2]);
      (vfx->s).mode[2]++;
      /* fallthrough */
    case 1: {
      struct Camera* cam = &gStageRun.vm.camera;
      s32 cx = ((cam->viewport.x - 1) + cam->viewport.x) / 2;
      s32 cy = ((cam->viewport.y - 1) + cam->viewport.y) / 2;
      s32 k = s16_ARRAY_0836edfe[(vfx->s).work[2]];
      s32 dx = ((e->coord.x - cx) * k) / 256;
      s32 dy = ((e->coord.y - cy) * k) / 256;
      (vfx->s).coord.x = cx + dx;
      (vfx->s).coord.y = cy + dy;
      (vfx->s).work[3]++;
      if (CalcFromCamera(cam, &e->coord) != 0 || ((vfx->s).work[3] & 1)) {
        (vfx->s).flags &= ~DISPLAY;
      } else {
        (vfx->s).flags = ((vfx->s).flags & ~DISPLAY) | DISPLAY;
      }
      if (*((u8*)e + 0xc8) != 0 || e->mode[0] > 1 || e->mode[0] == 4) {
        (vfx->s).flags &= ~DISPLAY;
        (vfx->s).flags &= ~FLIPABLE;
        SET_VFX_ROUTINE(vfx, ENTITY_DISAPPEAR);
      }
      UpdateMotionGraphic(&vfx->s);
      break;
    }
  }
#else
  INCCODE("asm/vfx/unk_37_ca5c.inc");
#endif
}

u8 GetEntityPalID(struct Entity* p);

// 0x080BCB6C
void FUN_080bcb6c(struct VFX* vfx) {
  switch ((vfx->s).mode[2]) {
    case 0:
      (vfx->s).taskCol = 0x11;
      (vfx->s).work[2] = 6;
      SetMotion(&vfx->s, MOTION(0x33, 0x00));
      (vfx->s).mode[2]++;
      FALLTHROUGH;
    case 1:
      if ((u8)--(vfx->s).work[2] == 0) {
        (vfx->s).mode[2]++;
      }
      {
        register u8 fv asm("r0");
        if ((1 & (vfx->s).work[2]) != 0) {
          fv = (vfx->s).flags;
          fv |= DISPLAY;
        } else {
          u8 t = (vfx->s).flags;
          fv = 0xFE;
          fv &= t;
          asm volatile("" ::"r"(t));
        }
        (vfx->s).flags = fv;
      }
      goto draw;
    case 2: {
      u32 v;
      u32 sv;
      u32 k;
      (vfx->s).flags |= DISPLAY;
      v = GetEntityPalID(&vfx->s);
      sv = ((u32)(u8)v) << 5;
      k = 0x200;
      {
        u32 kc;
        asm volatile("add %0, %1, #0" : "=&l"(kc) : "l"(k));
        ((void (*)(u16, u32))StartPaletteAnimation)(0x18, sv | kc);
      }
      (vfx->s).mode[2]++;
      FALLTHROUGH;
    }
    case 3:
      if ((u8)StepPaletteAnimation(0x18) == 3) {
        (vfx->s).mode[2]++;
      }
    draw:
      UpdateMotionGraphic(&vfx->s);
      break;
    case 4:
      RemovePaletteAnimation(0x18);
      (vfx->s).work[2] = 6;
      (vfx->s).mode[2]++;
      FALLTHROUGH;
    case 5:
      if ((u8)--(vfx->s).work[2] == 0) {
        (vfx->s).flags &= ~DISPLAY;
        (vfx->s).flags &= ~FLIPABLE;
        SET_VFX_ROUTINE(vfx, ENTITY_DISAPPEAR);
      }
      {
        register u8 fv asm("r0");
        if ((1 & (vfx->s).work[2]) != 0) {
          fv = (vfx->s).flags;
          fv |= DISPLAY;
        } else {
          u8 t = (vfx->s).flags;
          fv = 0xFE;
          fv &= t;
          asm volatile("" ::"r"(t));
        }
        (vfx->s).flags = fv;
      }
      UpdateMotionGraphic(&vfx->s);
      break;
  }
}

INCASM("asm/vfx/unk_37_post_c2.inc");

void FUN_080bcc94(struct VFX* vfx) {
  struct Entity* e = (vfx->s).unk_28;
  s32 md = (vfx->s).mode[2];
  switch (md) {
    case 0:
      (vfx->s).taskCol = 0x1A;
      (vfx->s).work[2] = 0x12;
      SetMotion(&vfx->s, MOTION(0x33, 0x0B));
      (vfx->s).mode[2]++;
      // fallthrough
    case 1: {
      s32 t = (vfx->s).work[2] - 1;
      (vfx->s).work[2] = t;
      if ((t << 24) == 0) {
        (vfx->s).mode[2]++;
      }
      (vfx->s).coord.x += (vfx->s).d.x;
      (vfx->s).coord.y += (vfx->s).d.y;
      if ((vfx->s).work[3] != 0) {
        StepPaletteAnimation(0x19);
      }
      UpdateMotionGraphic(&vfx->s);
      break;
    }
    case 2:
      (vfx->s).work[2] = 0x10;
      (vfx->s).mode[2]++;
      // fallthrough
    case 3: {
      register s32 w asm("r0");
      u32 u;
      s32 f;
      w = (vfx->s).work[2];
      asm("" : "+r"(w));
      u = w;
      if (u > 8) {
        if (u & 1) {
          register u8 f1 asm("r1");
          register s32 fr asm("r0");
          f1 = (vfx->s).flags;
          fr = DISPLAY;
          fr |= f1;
          asm("" : "+r"(fr));
          f = fr;
        } else {
          goto off;
        }
      } else {
        if (((*(volatile u8*)&(vfx->s).work[2] % 3) << 24) == 0) {
          register u8 f1 asm("r1");
          register s32 fr asm("r0");
          f1 = (vfx->s).flags;
          fr = DISPLAY;
          fr |= f1;
          f = fr;
        } else {
        off: {
            register u8 f1 asm("r1");
            register s32 fr asm("r0");
            f1 = (vfx->s).flags;
            fr = 0xFE;
            fr &= f1;
            f = fr;
          }
        }
      }
      (vfx->s).flags = f;
      {
        register s32 t2 asm("r0");
        t2 = u - 1;
        (vfx->s).work[2] = t2;
        if ((t2 << 24) == 0) {
          register u8 f1 asm("r1");
          register s32 f2 asm("r0");
          *((u8*)e + 0xCF) -= 1;
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
      }
      (vfx->s).coord.x += (vfx->s).d.x;
      (vfx->s).coord.y += (vfx->s).d.y;
      UpdateMotionGraphic(&vfx->s);
      break;
    }
  }
}

// 0x080BCD9C
void FUN_080bcd9c(struct VFX* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SetMotion(&p->s, MOTION(0x33, 0x0C));
      *(u8*)((u8*)p + 0x25) = 0x19;
      StartPaletteAnimation(0x1A, (((u32)(u8)GetEntityPalID(&p->s)) << 24 >> 19) | 0x200);
      (p->s).work[2] = 0xC;
      (p->s).mode[2]++;
    case 1:
      StepPaletteAnimation(0x1A);
      UpdateMotionGraphic(&p->s);
      if ((1 & (p->s).work[2]) != 0) {
        (p->s).flags |= 1;
      } else {
        (p->s).flags &= 0xFE;
      }
      if ((u8)--(p->s).work[2] == 0) {
        u8 fl;
        RemovePaletteAnimation(0x1A);
        fl = (p->s).flags & 0xFE;
        fl &= 0xFD;
        (p->s).flags = fl;
        SET_VFX_ROUTINE(p, 3);
      }
      break;
  }
}

extern const motion_t motion_t_ARRAY_0836ee0a[3];

// 0x080BCE48
void FUN_080bce48(struct VFX* vfx) {
  switch ((vfx->s).mode[2]) {
    case 0:
      (vfx->s).taskCol = 0x19;
      (vfx->s).palID = (vfx->s).work[2];
      SetMotion(&vfx->s, motion_t_ARRAY_0836ee0a[RANDOM(RNG_0202f388) % 3]);
      (vfx->s).work[2] = 0x12;
      (vfx->s).mode[2]++;
      FALLTHROUGH;
    case 1:
      if ((u8)--(vfx->s).work[2] == 0) {
        (vfx->s).mode[2]++;
      }
      (vfx->s).coord.x += (vfx->s).d.x;
      (vfx->s).coord.y += (vfx->s).d.y;
      UpdateMotionGraphic(&vfx->s);
      break;
    case 2:
      (vfx->s).work[2] = 0x10;
      (vfx->s).mode[2]++;
      FALLTHROUGH;
    case 3: {
      u8 w0 = (vfx->s).work[2];
      u32 w;
      u32 k1 = 1;
      s32 v;
      register u32 res asm("r0");
      asm volatile("add %0, %1, #0" : "=&l"(w) : "l"(w0));
      if (w > 8) {
        asm("" : "+r"(k1));
        res = w & k1;
        asm volatile("" ::"r"(w));
        if (res != 0) {
          (vfx->s).flags |= DISPLAY;
        } else {
          (vfx->s).flags &= ~DISPLAY;
        }
      } else if ((u8)(*(volatile u8*)&(vfx->s).work[2] % 3) == 0) {
        (vfx->s).flags |= DISPLAY;
      } else {
        (vfx->s).flags &= ~DISPLAY;
      }
      v = w - 1;
      (vfx->s).work[2] = v;
      if ((u8)v == 0) {
        (vfx->s).flags &= ~DISPLAY;
        (vfx->s).flags &= ~FLIPABLE;
        SET_VFX_ROUTINE(vfx, ENTITY_DISAPPEAR);
      }
      (vfx->s).coord.x += (vfx->s).d.x;
      (vfx->s).coord.y += (vfx->s).d.y;
      UpdateMotionGraphic(&vfx->s);
      break;
    }
  }
}

// --------------------------------------------

void FUN_080bc8c0(struct VFX* vfx);
void FUN_080bc974(struct VFX* vfx);
void FUN_080bca5c(struct VFX* vfx);
void FUN_080bcb6c(struct VFX* vfx);
void FUN_080bcc94(struct VFX* vfx);
void FUN_080bcd9c(struct VFX* vfx);
void FUN_080bce48(struct VFX* vfx);

// clang-format off
const VFXFunc PTR_ARRAY_0836edd4[7] = {
    FUN_080bc8c0,
    FUN_080bc974,
    FUN_080bca5c,
    FUN_080bcb6c,
    FUN_080bcc94,
    FUN_080bcd9c,
    FUN_080bce48,
};
// clang-format on

static const u8 u8_ARRAY_0836edf0[7] = {0, 1, 2, 3, 4, 5, 6};

const motion_t motion_t_ARRAY_0836edf8[3] = {
    MOTION(SM050_CREA_PREA, 0),
    MOTION(SM050_CREA_PREA, 1),
    MOTION(SM050_CREA_PREA, 2),
};

const s16 s16_ARRAY_0836edfe[6] = {
    0x00C0, 0x0080, 0x0010, -0x0080, -0x00C0, -0x0100,
};

const motion_t motion_t_ARRAY_0836ee0a[3] = {
    MOTION(SM050_CREA_PREA, 0),
    MOTION(SM050_CREA_PREA, 1),
    MOTION(SM050_CREA_PREA, 2),
};
