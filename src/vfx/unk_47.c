#include "global.h"
#include "vfx.h"

// アヌビステップ関連
// - アヌビステップの棺
// - パンテオンゾンビの爆散パーティクル

static void VFX47_Init(struct Entity* p);
static void VFX47_Update(struct Entity* p);
static void VFX47_Die(struct Entity* p);

// clang-format off
const VFXRoutine gVFX47Routine = {
    [ENTITY_INIT] =      (VFXFunc)VFX47_Init,
    [ENTITY_UPDATE] =    (VFXFunc)VFX47_Update,
    [ENTITY_DIE] =       (VFXFunc)VFX47_Die,
    [ENTITY_DISAPPEAR] = (VFXFunc)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

void FUN_080bf390(struct Entity* e) {
  void* q = e->unk_2c;
  struct Entity* p = AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    p->taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_047);
    p->tileNum = 0;
    p->palID = 0;
    p->work[0] = 1;
    p->unk_28 = (void*)e;
    p->unk_2c = q;
  }
}

void FUN_080bf3d8(struct Entity* e) {
  s32 i;
  void* q = NULL;
  for (i = 0; i < 2; i++) {
    struct Entity* p = AllocEntityFirst(gVFXHeaderPtr);
    if (p != NULL) {
      p->taskCol = 1;
      INIT_VFX_ROUTINE(p, VFX_UNK_047);
      p->tileNum = 0;
      p->palID = 0;
      p->work[0] = 0;
      p->work[2] = i;
      p->unk_28 = (void*)e;
      p->unk_2c = q;
      q = (void*)p;
    }
  }
}

void FUN_080bf438(s32 x, s32 y, u8 param_3) {
  struct Entity* p = AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    p->taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_047);
    p->tileNum = 0;
    p->palID = 0;
    p->work[0] = 2;
    p->work[2] = param_3;
    (p->coord).x = x;
    (p->coord).y = y;
  }
}

void FUN_080bf48c(s32 x, s32 y, u8 n) {
  s32 i;
  for (i = 0; i < 3; i++) {
    struct Entity* p = AllocEntityFirst(gVFXHeaderPtr);
    if (p != NULL) {
      p->taskCol = 1;
      INIT_VFX_ROUTINE(p, VFX_UNK_047);
      p->tileNum = 0;
      p->palID = 0;
      p->work[0] = 3;
      p->work[2] = i;
      p->work[3] = n;
      (p->coord).x = x - PIXEL(8);
      RNG_0202f388 = LCG(RNG_0202f388);
      (p->coord).x += (RNG_0202f388 >> 16) & 0xFFF;
      (p->coord).y = y;
    }
  }
}

void FUN_080bf52c(s32 x, s32 y, u8 n) {
  s32 i;
  for (i = 0; i < 6; i++) {
    struct Entity* p = AllocEntityFirst(gVFXHeaderPtr);
    if (p != NULL) {
      p->taskCol = 1;
      INIT_VFX_ROUTINE(p, VFX_UNK_047);
      p->tileNum = 0;
      p->palID = 0;
      p->work[0] = 4;
      p->work[2] = i;
      (p->coord).x = x - PIXEL(8);
      RNG_0202f388 = LCG(RNG_0202f388);
      (p->coord).x += (RNG_0202f388 >> 16) & 0xFFF;
      (p->coord).y = y;
    }
  }
}

// --------------------------------------------

static const u8 sInitModes[];

static void VFX47_Init(struct Entity* p) {
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
  p->mode[1] = sInitModes[p->work[0]];
  p->flags |= FLIPABLE;
  p->flags |= DISPLAY;
  InitNonAffineMotion(p);
  VFX47_Update((void*)p);
}

void FUN_080bf634(struct VFX* vfx);
void FUN_080bf6d8(struct VFX* vfx);
void FUN_080bf890(struct VFX* vfx);
void FUN_080bfa10(struct VFX* vfx);
void FUN_080bfa7c(struct VFX* vfx);
void FUN_080bfb54(struct VFX* vfx);

static void VFX47_Update(struct Entity* p) {
  // clang-format off
  static const VFXFunc sUpdates[6] = {
      (VFXFunc)FUN_080bf634,
      (VFXFunc)FUN_080bf6d8,
      (VFXFunc)FUN_080bf890,
      (VFXFunc)FUN_080bfa10,
      (VFXFunc)FUN_080bfa7c,
      (VFXFunc)FUN_080bfb54,
  }; // 0x0836f0f4
  // clang-format on
  (sUpdates[p->mode[1]])((void*)p);
}

static void VFX47_Die(struct Entity* p) { SET_VFX_ROUTINE(p, ENTITY_EXIT); }

#include "palette_animation.h"

u8 GetEntityPalID(struct Entity* p);

// 0x080bf634
void FUN_080bf634(struct VFX* p) {
  struct Entity* q = (p->s).unk_28;
  switch ((p->s).mode[2]) {
    case 0:
      if ((p->s).work[2] != 0) {
        (p->s).taskCol = 0x1a;
        SetMotion(&p->s, MOTION(0x4B, 0x01));
      } else {
        u32 g0;
        u32 g;
        (p->s).taskCol = 0x16;
        SetMotion(&p->s, MOTION(0x4B, 0x00));
        g0 = GetEntityPalID(&p->s);
        g = (u8)g0 << 5;
        StartPaletteAnimation(0x46, g | 0x200);
      }
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 1: {
      s32 one;
      s32 x = (q->coord).x - 0x300;
      u32 f;
      (p->s).coord.x = x + (((p->s).work[2] * 3) << 9);
      (p->s).coord.y = (q->coord).y;
      f = *(u32*)((u8*)q + 0xc0);
      one = 1;
      if ((f & one) != 0) {
        s32 z = 0;
        (p->s).mode[1] = one;
        (p->s).mode[2] = z;
      }
      StepPaletteAnimation(0x46);
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}

// 0x080bf6d8
void FUN_080bf6d8(struct VFX* p) {
  register struct Entity* e2 asm("r3");
  e2 = (struct Entity*)(p->s).unk_2c;
  switch ((p->s).mode[2]) {
    case 0: {
      PlaySound(0x80);
      RemovePaletteAnimation(0x46);
      {
        u32 g0 = GetEntityPalID(&p->s);
        u32 g = (u8)g0 << 5;
        StartPaletteAnimation(0x47, g | 0x200);
      }
      {
        s32 v = (p->s).coord.x + -0xA00;
        v += (p->s).work[2] * 0x1400;
        (p->s).coord.x = v;
      }
      (p->s).work[3] = 6;
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1: {
      s32 t = (p->s).work[3] - 1;
      (p->s).work[3] = t;
      if ((t << 24) == 0) {
        (p->s).mode[2]++;
      }
      if ((p->s).work[2] != 0) {
        {
          register s32 w3 asm("r0");
          register s32 m3 asm("r1");
          w3 = (p->s).work[3];
          m3 = 3;
          w3 &= m3;
          if (w3 == 0) {
            FUN_080bf390(&p->s);
          }
        }
      }
      goto pal;
    }
    case 2:
      (p->s).d.x = ((p->s).work[2] << 7) - 0x40;
      (p->s).work[3] = 0x30;
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 3:
      if ((p->s).work[2] == 0) {
        goto addx;
      }
      {
        register s32 w3 asm("r0");
        register s32 m3 asm("r1");
        w3 = (p->s).work[3];
        m3 = 3;
        w3 &= m3;
        if (w3 != 0) {
          goto addx;
        }
      }
      goto call;
    case 4:
      (p->s).work[3] = 0x50;
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 5:
      if ((p->s).work[2] != 0) {
        {
          register s32 w3 asm("r0");
          register s32 m3 asm("r1");
          w3 = (p->s).work[3];
          m3 = 3;
          w3 &= m3;
          if (w3 == 0) {
            FUN_080bf390(&p->s);
          }
        }
      }
      (p->s).coord.y -= 0xC0;
      goto dec;
    case 6:
      {
        register s32 base asm("r1");
        register s32 w asm("r2");
        register s32 k asm("r0");
        base = 0x75;
        w = (p->s).work[2];
        k = 0xEA;
        k = k * w;
        base -= k;
        (p->s).d.x = base;
      }
      (p->s).work[3] = 0x30;
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 7:
      if ((p->s).work[2] != 0) {
        {
          register s32 w3 asm("r0");
          register s32 m3 asm("r1");
          w3 = (p->s).work[3];
          m3 = 3;
          w3 &= m3;
          if (w3 == 0) {
            if ((p->s).coord.x - e2->coord.x > 0x2000) {
            call:
              FUN_080bf390(&p->s);
            }
          }
        }
      }
    addx:
      (p->s).coord.x += (p->s).d.x;
    dec: {
      s32 t = (p->s).work[3] - 1;
      (p->s).work[3] = t;
      if ((t << 24) == 0) {
        (p->s).mode[2]++;
      }
    }
    pal:
      StepPaletteAnimation(0x47);
      UpdateMotionGraphic(&p->s);
      break;
    case 8:
      (p->s).work[3] = 0x50;
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 9: {
      s32 t;
      StepPaletteAnimation(0x47);
      UpdateMotionGraphic(&p->s);
      (p->s).coord.y -= 0xC0;
      t = (p->s).work[3] - 1;
      (p->s).work[3] = t;
      if ((t << 24) == 0) {
        RemovePaletteAnimation(0x47);
        (p->s).flags &= ~1;
        (p->s).flags &= ~2;
        SET_VFX_ROUTINE(p, ENTITY_DISAPPEAR);
      }
      break;
    }
  }
}


void FUN_080bf890(struct VFX* p) {
  struct Entity* e1 = (struct Entity*)(p->s).unk_28;
  struct Entity* e2 = (struct Entity*)(p->s).unk_2c;
  s32 m = (p->s).mode[2];
  switch (m) {
    case 0: {
      (p->s).unk_coord.x = m;
      {
        s32 k = -0x1800;
        (p->s).unk_coord.y = k;
        (p->s).unk_coord.y = (s32)(RANDOM(RNG_0202f388) % 0x3000) + k;
      }
      if (RANDOM(RNG_0202f388) & 1) {
        *((u8*)p + 0x25) = 0x17;
      } else {
        *((u8*)p + 0x25) = 0x19;
      }
      {
        u32 w3 = RANDOM(RNG_0202f388) & 1;
        (p->s).work[3] = w3;
        {
          s32 k2 = -0x200;
          s32 d = k2 - (s32)(RANDOM(RNG_0202f388) & 0x1FF);
          (p->s).d.x = d;
          if (w3 != 0) {
            (p->s).d.x = -d;
          }
        }
      }
      (p->s).work[2] = 0;
      SetMotion(&p->s, 0x4B04);
      (p->s).mode[2]++;
    }
      // fallthrough
    case 1: {
      {
        s32 t = (p->s).work[2] + 1;
        (p->s).work[2] = t;
        if (t & 1) {
          (p->s).flags |= 1;
        } else {
          (p->s).flags &= 0xFE;
        }
      }
      UpdateMotionGraphic(&p->s);
      if ((p->s).work[3] == 0) {
        s32 ux = (p->s).unk_coord.x + (p->s).d.x;
        s32 nx;
        (p->s).unk_coord.x = ux;
        nx = (e1->coord).x + ux;
        (p->s).coord.x = nx;
        (p->s).coord.y = (e1->coord).y + (p->s).unk_coord.y;
        {
          s32 bx = (e2->coord).x;
          if (nx < bx) {
            (p->s).coord.x = bx;
            {
              u32 fl = (p->s).flags & 0xFE;
              fl &= 0xFD;
              (p->s).flags = fl;
            }
            {
              u32 tbl = (u32)gVFXFnTable;
              u32 id = ((p->s).id) << 2;
              EntityFunc** rt = (EntityFunc**)(tbl + id);
              *(u32*)((p->s).mode) = 3;
              (p->s).onUpdate = (void*)((*rt)[3]);
            }
          }
        }
      } else {
        s32 ux = (p->s).unk_coord.x + (p->s).d.x;
        s32 nx;
        (p->s).unk_coord.x = ux;
        nx = (e2->coord).x + ux;
        (p->s).coord.x = nx;
        (p->s).coord.y = (e2->coord).y + (p->s).unk_coord.y;
        {
          s32 bx = (e1->coord).x;
          if (nx > bx) {
            (p->s).coord.x = bx;
            {
              u32 fl = (p->s).flags & 0xFE;
              fl &= 0xFD;
              (p->s).flags = fl;
            }
            {
              u32 tbl = (u32)gVFXFnTable;
              u32 id = ((p->s).id) << 2;
              EntityFunc** rt = (EntityFunc**)(tbl + id);
              *(u32*)((p->s).mode) = 3;
              (p->s).onUpdate = (void*)((*rt)[3]);
            }
          }
        }
      }
      break;
    }
  }
}

#include "motion.h"

void FUN_080bfa10(struct VFX* p) {
  switch ((p->s).mode[2]) {
    case 0:
      if ((p->s).work[2] != 0) {
        SetMotion(&p->s, MOTION(0x4a, 0x01));
      } else {
        SetMotion(&p->s, MOTION(0x4a, 0x00));
      }
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      UpdateMotionGraphic(&p->s);
      if ((p->s).motion.state == 3) {
        (p->s).flags &= ~DISPLAY;
        (p->s).flags &= ~FLIPABLE;
        SET_VFX_ROUTINE(p, ENTITY_DISAPPEAR);
      }
      break;
  }
}

static const motion_t sMotions[3];

// 0x080BFA7C
void FUN_080bfa7c(struct VFX* p) {
  register s32 m asm("r5");
  m = (p->s).mode[2];
  switch (m) {
    case 0:
      *((u8*)p + 0x49) |= 0xC;
      SetMotion(&p->s, sMotions[(p->s).work[2]]);
      if ((p->s).work[3] != 0) {
        (p->s).d.y = m;
      } else {
        s32 k = -0x480;
        (p->s).d.y = k - (s32)(RANDOM(RNG_0202f388) & 0xFF);
      }
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 1: {
      s32 dy;
      s32 ny;
      UpdateMotionGraphic(&p->s);
      (p->s).d.y += 0x40;
      if ((p->s).d.y > 0x700) {
        (p->s).d.y = 0x700;
      }
      asm("" ::: "memory");
      {
        register s32 cy asm("r0");
        register s32 dv asm("r2");
        register s32 nv asm("r1");
        cy = (p->s).coord.y;
        dv = (p->s).d.y;
        nv = cy + dv;
        (p->s).coord.y = nv;
        dy = dv;
        ny = nv;
      }
      if ((p->s).work[3] != 0) {
        if (!((bool16 (*)(s32, s32))FUN_080098a4)((p->s).coord.x, ny)) {
          break;
        }
        FUN_080bf438((p->s).coord.x, (p->s).coord.y, 1);
      } else if (dy <= 0) {
        break;
      }
      {
        register u8 g asm("r0");
        register u8 h asm("r1");
        h = (p->s).flags;
        asm("" : "+r"(h));
        g = 0xFE;
        g &= h;
        h = 0xFD;
        g &= h;
        (p->s).flags = g;
      }
      SET_VFX_ROUTINE(p, ENTITY_DISAPPEAR);
      break;
    }
  }
}

#ifdef NON_MATCHING
// close but for a SetMotion-arg scratch-register tie: agbcc loads work[2]
// into r0 (dead const home) where retail uses r2; two bytes differ.
NON_MATCH void FUN_080bfb54(struct VFX* p) {
  register s32 m asm("r6");
  m = (p->s).mode[2];
  switch (m) {
    case 0:
      InitRotatableMotion(&p->s);
      SetMotion(&p->s, MOTION(0x4c, 0x05) + (p->s).work[2]);
      {
        register s32 b1 asm("r1");
        register u32* rp asm("ip");
        register u32 A3 asm("r3");
        register u32 C3 asm("r2");
        register u32 seed asm("r4");
        register u32 mff asm("r5");
        register u32 r0v asm("r0");
        b1 = ((p->s).work[2] << 7) + -0x200;
        {
          register u32* rt asm("r2");
          rt = &RNG_0202f388;
          rp = rt;
          asm("" : "+r"(rp));
          r0v = *rt;
          asm("" : "+r"(r0v));
        }
        A3 = 0x343FD;
        asm("" : "+r"(A3));
        r0v *= A3;
        C3 = 0x269EC3;
        asm("" : "+r"(C3));
        r0v += C3;
        r0v <<= 1;
        seed = r0v >> 1;
        asm("" : "+r"(seed));
        {
          u32 rr = r0v >> 0x11;
          mff = 0xFF;
          asm("" : "+r"(mff));
          rr &= mff;
          (p->s).d.x = b1 + rr;
        }
        b1 = -0x380;
        asm("" : "+r"(b1));
        r0v = seed;
        r0v *= A3;
        r0v += C3;
        r0v <<= 1;
        seed = r0v >> 1;
        asm("" : "+r"(seed));
        {
          u32 rr2 = r0v >> 0x11;
          rr2 &= mff;
          (p->s).d.y = b1 - rr2;
        }
        (p->s).work[3] = m;
        r0v = seed;
        r0v *= A3;
        r0v += C3;
        r0v <<= 1;
        {
          u32 s3 = r0v >> 1;
          register u32* rt2 asm("r2");
          rt2 = rp;
          *rt2 = s3;
        }
        {
          u32 sp3 = ((r0v >> 0x11) % 3) + 1;
          *(s32*)((u8*)p + 0x64) = sp3;
          {
            u32 q = (p->s).work[2] / 3;
            {
              register u32 one1 asm("r1");
              one1 = 1;
              asm("" : "+r"(one1));
              q ^= one1;
            }
            {
              u32 sh24 = q << 24;
              asm("" : "+r"(sh24));
              q = sh24 >> 23;
            }
            q *= sp3;
            sp3 -= q;
            *(s32*)((u8*)p + 0x64) = sp3;
          }
        }
      }
      (p->s).mode[2]++;
      /* fallthrough */
    case 1: {
      s32 w = (p->s).work[2] + 1;
      (p->s).work[2] = w;
      if (w & 1) {
        (p->s).flags |= 1;
      } else {
        (p->s).flags &= 0xFE;
      }
      (p->s).coord.x += (p->s).d.x;
      (p->s).d.y += 0x40;
      if ((p->s).d.y > 0x700) {
        (p->s).d.y = 0x700;
      }
      {
        s32 ny = (p->s).coord.y + (p->s).d.y;
        (p->s).coord.y = ny;
        if (FUN_080098a4((p->s).coord.x, ny) != 0) {
          FUN_080bf438((p->s).coord.x, (p->s).coord.y, 1);
          {
            u32 f = (p->s).flags & 0xFE;
            asm("" : "+r"(f));
            (p->s).flags = f & 0xFD;
          }
          SET_VFX_ROUTINE(p, ENTITY_DISAPPEAR);
        }
      }
      {
        register s32 xv asm("r0");
        register s32 nw asm("r1");
        xv = *(s32*)((u8*)p + 0x64);
        nw = (p->s).work[3];
        nw += xv;
        (p->s).work[3] = nw;
        (p->s).angle = nw;
      }
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}
#else
NAKED void FUN_080bfb54(struct VFX* p) {
  INCCODE("asm/vfx/unk_47_fb54.inc");
}
#endif

// --------------------------------------------

static const u8 sInitModes[5] = {
    0, 2, 3, 4, 5,
};

// 0x0836f112
static const motion_t sMotions[3] = {
    MOTION(SM076_PANTHEON_ZOMBIE, 5),
    MOTION(SM076_PANTHEON_ZOMBIE, 10),
    MOTION(SM076_PANTHEON_ZOMBIE, 9),
};
