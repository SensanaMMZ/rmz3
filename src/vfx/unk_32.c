#include "global.h"
#include "entity/macros.h"
#include "motion.h"
#include "story.h"
#include "vfx.h"

static void Ghost32_Init(struct VFX* p);
void Ghost32_Update(struct VFX* p);
void Ghost32_Die(struct VFX* p);

// clang-format off
const VFXRoutine gGhost32Routine = {
    [ENTITY_INIT] =      Ghost32_Init,
    [ENTITY_UPDATE] =    Ghost32_Update,
    [ENTITY_DIE] =       Ghost32_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

struct VFX* FUN_080ba7c8(struct Coord* c, u8 n) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, 32);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = n;
    (p->s).work[1] = 0;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
  }
  return p;
}

struct VFX* FUN_080ba81c(struct Coord* c, bool8 isRight, s16 r2, s32 r3) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, 32);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = isRight;
    (p->s).work[1] = 1;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
    (p->props).unk32.unk_0 = r2;
    (p->props).unk32.unk_4 = r3;
  }
  return p;
}

struct VFX* FUN_080ba888(struct Coord* c, struct Coord* d, u8 n) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, 32);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = n;
    (p->s).work[1] = 2;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
    (p->s).d.x = d->x;
    (p->s).d.y = d->y;
  }
  return p;
}

struct VFX* FUN_080ba8e8(struct Coord* c, u8 n) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, 32);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = n;
    (p->s).work[1] = 3;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
  }
  return p;
}

struct VFX* FUN_080ba940(struct Coord* c, u8 n, u8 r2) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, 32);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = n;
    (p->s).work[1] = 4;
    (p->props).unk32.unk_c = r2;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
  }
  return p;
}

struct VFX* FUN_080ba9a0(struct Coord* c) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, 32);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 0;
    (p->s).work[1] = 5;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
  }
  return p;
}

struct VFX* FUN_080ba9f4(struct Coord* c, u8 n) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, 32);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = n;
    (p->s).work[1] = 6;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
  }
  return p;
}

struct VFX* FUN_080baa4c(struct Coord* c, u8 n) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, 32);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = n;
    (p->s).work[1] = 7;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
  }
  return p;
}

// --------------------------------------------

void FUN_080baad8(struct VFX* p);
void FUN_080bab54(struct VFX* p);
void FUN_080babac(struct VFX* p);
void FUN_080bac14(struct VFX* p);
void FUN_080bac5c(struct VFX* p);
void FUN_080baca4(struct VFX* p);
void FUN_080bacec(struct VFX* p);
void FUN_080bad34(struct VFX* p);

static void Ghost32_Init(struct VFX* p) {
  // clang-format off
  static const VFXFunc sInitializers[8] = {
      FUN_080baad8,
      FUN_080bab54,
      FUN_080babac,
      FUN_080bac14,
      FUN_080bac5c,
      FUN_080baca4,
      FUN_080bacec,
      FUN_080bad34,
  };
  // clang-format on
  (p->s).work[2] = 0xFF;
  (p->s).flags |= DISPLAY;
  (p->s).flags |= FLIPABLE;
  (sInitializers[(p->s).work[1]])(p);
  Ghost32_Update(p);
}

static const VFXFunc sUpdates[8];
void Ghost32_Die(struct VFX* p);

void FUN_080baad8(struct VFX* p) {
  InitNonAffineMotion(&p->s);
  if ((p->s).work[0] == 0) {
    SET_XFLIP(p, FALSE);
    (p->s).d.x = PIXEL(3) / 8;
  } else {
    SET_XFLIP(p, TRUE);
    (p->s).d.x = -PIXEL(3) / 8;
  }
  (p->s).d.y = 0;
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
  (p->s).mode[1] = 0, (p->s).mode[2] = 0, (p->s).mode[3] = 0;
}

void FUN_080bab54(struct VFX* p) {
  InitNonAffineMotion(&p->s);
  (p->s).d.x = 0, (p->s).d.y = 0;
  RNG_0202f388 = LCG(RNG_0202f388);
  (p->s).work[2] = ((RNG_0202f388 >> 16) & 7) + 0x7F;
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
  (p->s).mode[1] = 1, (p->s).mode[2] = 0, (p->s).mode[3] = 0;
}

void FUN_080babac(struct VFX* v) {
  InitScalerotMotion1(&v->s);
  (v->props).unk32.unk_8 = 0x100;
  (v->s).spr.mag.x = 0x100;
  (v->s).spr.mag.y = (v->props).unk32.unk_8;
  RNG_0202f388 = LCG(RNG_0202f388);
  (v->s).angle = RNG_0202f388 >> 16;
  SET_VFX_ROUTINE(v, ENTITY_UPDATE);
  (v->s).mode[1] = 2;
  (v->s).mode[2] = 0;
  (v->s).mode[3] = 0;
}

void FUN_080bac14(struct VFX* v) {
  InitScalerotMotion1(&v->s);
  (v->props).unk32.unk_8 = 0x100;
  (v->s).spr.mag.x = 0x100;
  (v->s).spr.mag.y = (v->props).unk32.unk_8;
  (v->s).angle = 0;
  SET_VFX_ROUTINE(v, ENTITY_UPDATE);
  (v->s).mode[1] = 3;
  (v->s).mode[2] = 0;
  (v->s).mode[3] = 0;
}

// 0x080bac5c
NON_MATCH void FUN_080bac5c(struct VFX* p) {
#if MODERN
  InitScalerotMotion1(&p->s);
  ((struct Unk32Props*)(p->props).raw)->unk_8 = 0x100;
  (p->s).spr.mag.x = 0x100;
  (p->s).spr.mag.y = ((struct Unk32Props*)(p->props).raw)->unk_8;
  (p->s).angle = 0;
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
  (p->s).mode[1] = 4, (p->s).mode[2] = 0, (p->s).mode[3] = 0;  // なんかここのレジスタ割り当てが合わない (NON_MATCH の原因)
#else
  INCCODE("asm/wip/FUN_080bac5c.inc");
#endif
}

void FUN_080baca4(struct VFX* v) {
  InitScalerotMotion1(&v->s);
  (v->props).unk32.unk_8 = 0x100;
  (v->s).spr.mag.x = 0x100;
  (v->s).spr.mag.y = (v->props).unk32.unk_8;
  (v->s).angle = 0;
  SET_VFX_ROUTINE(v, ENTITY_UPDATE);
  (v->s).mode[1] = 5;
  (v->s).mode[2] = 0;
  (v->s).mode[3] = 0;
}

void FUN_080bacec(struct VFX* v) {
  InitNonAffineMotion(&v->s);
  (v->props).unk32.unk_8 = 0x100;
  (v->s).spr.mag.x = 0x100;
  (v->s).spr.mag.y = (v->props).unk32.unk_8;
  (v->s).angle = 0;
  SET_VFX_ROUTINE(v, ENTITY_UPDATE);
  (v->s).mode[1] = 6;
  (v->s).mode[2] = 0;
  (v->s).mode[3] = 0;
}

void FUN_080bad34(struct VFX* v) {
  InitNonAffineMotion(&v->s);
  (v->props).unk32.unk_8 = 0x100;
  (v->s).spr.mag.x = 0x100;
  (v->s).spr.mag.y = (v->props).unk32.unk_8;
  (v->s).angle = 0;
  SET_VFX_ROUTINE(v, ENTITY_UPDATE);
  (v->s).mode[1] = 7;
  (v->s).mode[2] = 0;
  (v->s).mode[3] = 0;
}

void Ghost32_Update(struct VFX* p) {
  if (IS_METTAUR) {
    SET_VFX_ROUTINE(p, ENTITY_DIE);
    Ghost32_Die(p);
  } else {
    (sUpdates[(p->s).mode[1]])(p);
  }
}


void Ghost32_Die(struct VFX* p) {
  (p->s).flags &= ~DISPLAY;
  SET_VFX_ROUTINE(p, ENTITY_EXIT);
}

// Chained-RNG basin (Solid44 family): the spark block wants its c3.y init
// stored direct-to-sp with the &c3 pointer materialized only at the RMW, the
// multiplier constant in r6 with an a-copy, and the unstored middle seed
// parked in r8 - each ordering lever rotates the const/seed homes instead.
// Both explosion paths and the glide physics stream-match.
NON_MATCH void FUN_080bade8(struct VFX* p) {
#if MODERN
  struct Coord c;
  struct Coord c2;
  struct Coord c3;
  s32 t = (p->s).work[2] - 1;
  (p->s).work[2] = t;
  if ((t << 24) == 0) {
    u32 a, v, k;
    CreateSmoke(2, &(p->s).coord);
    a = RNG_0202f388;
    v = (a * 0x343FD + 0x269EC3) << 1;
    RNG_0202f388 = v >> 1;
    k = (v >> 0x11) & 3;
    c.x = (p->s).coord.x;
    c.y = (p->s).coord.y;
    FUN_080ba81c(&c, (p->s).work[0], 0x2710, k);
    FUN_080ba81c(&c, (p->s).work[0], 0x2711, k);
    FUN_080ba81c(&c, (p->s).work[0], 0x2712, k);
    FUN_080ba81c(&c, (p->s).work[0], 0x2713, k);
    FUN_080ba81c(&c, (p->s).work[0], 0x2714, k);
    FUN_080ba81c(&c, (p->s).work[0], 0x2715, k);
    PlaySound(0x31);
    SET_VFX_ROUTINE(p, ENTITY_DIE);
    return;
  }
  {
    u32 gr = FUN_080098a4((p->s).coord.x, (p->s).coord.y);
    if (gr != 0 && !(gr & 0x8000)) {
      u32 a, v, k;
      CreateSmoke(2, &(p->s).coord);
      PlaySound(0x31);
      a = RNG_0202f388;
      v = (a * 0x343FD + 0x269EC3) << 1;
      RNG_0202f388 = v >> 1;
      k = (v >> 0x11) & 3;
      c2.x = (p->s).coord.x;
      c2.y = (p->s).coord.y;
      FUN_080ba81c(&c2, (p->s).work[0], 0x2710, k);
      FUN_080ba81c(&c2, (p->s).work[0], 0x2711, k);
      FUN_080ba81c(&c2, (p->s).work[0], 0x2712, k);
      FUN_080ba81c(&c2, (p->s).work[0], 0x2713, k);
      FUN_080ba81c(&c2, (p->s).work[0], 0x2714, k);
      FUN_080ba81c(&c2, (p->s).work[0], 0x2715, k);
      SET_VFX_ROUTINE(p, ENTITY_DIE);
      return;
    }
  }
  switch ((p->s).mode[2]) {
    case 0:
      (p->s).work[2] = 0x3C;
      (p->s).d.y = 0;
      (p->s).work[3] = 0;
      SetMotion(&p->s, 0x270A);
      (p->s).mode[2]++;
      FALLTHROUGH;
    case 1: {
      s32 g = (p->s).d.y + 8;
      (p->s).d.y = g;
      if (g > 0x700) {
        (p->s).d.y = 0x700;
      }
      if (((p->s).work[2] % 0x14 << 24) == 0) {
        u32 a1, v1, s1, r1v, v2;
        struct Coord* p3;
        c3.x = (p->s).coord.x;
        *(volatile s32*)&c3.y = (p->s).coord.y;
        a1 = RNG_0202f388;
        v1 = (a1 * 0x343FD + 0x269EC3) << 1;
        s1 = v1 >> 1;
        r1v = (v1 >> 0x11) & 0x7FF;
        p3 = &c3;
        p3->y = *(volatile s32*)&p3->y - r1v;
        {
          s32 cx = *(volatile s32*)&c3.x + -0x400;
          v2 = (s1 * 0x343FD + 0x269EC3) << 1;
          RNG_0202f388 = v2 >> 1;
          c3.x = cx + ((v2 >> 0x11) & 0x7FF);
        }
        FUN_080ba9f4(p3, 0);
        FUN_080ba9f4(p3, 1);
      }
      (p->s).coord.y += (p->s).d.y;
      (p->s).coord.x += (p->s).d.x;
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
#else
  INCCODE("asm/vfx/unk_32_ade8.inc");
#endif
}

static const s32* const PTR_ARRAY_0836ed24[6];

void FUN_080bb048(struct VFX* p) {
  {
    s32 t = (p->s).work[2] - 1;
    (p->s).work[2] = t;
    if ((t << 24) == 0) {
      goto smoke;
    }
  }
  {
    u16 a = FUN_080098a4((p->s).coord.x, (p->s).coord.y);
    if (a != 0) {
      if (!(a & 0x8000)) {
        if ((p->s).d.y > 0) {
        smoke:
          CreateSmoke(2, &(p->s).coord);
          SET_VFX_ROUTINE(p, ENTITY_DIE);
          return;
        }
      }
    }
  }
  {
    register u32 m9 asm("r9");
    m9 = (p->s).mode[2];
    switch (m9) {
      case 0: {
        const s32* const* t4 = PTR_ARRAY_0836ed24;
        register u16* mo8 asm("r8");
        register const s32* row asm("r0");
        register const s32* ent asm("r2");
        u32 mv0;
        {
          register u8* a1 asm("r1");
          u32 av = 0x74;
          asm("" : "+r"(av));
          av += (u32)p;
          a1 = (u8*)av;
          asm("" : "+r"(a1));
          mo8 = (u16*)a1;
          mv0 = *(u16*)a1;
        }
        {
          register u32 six asm("r1");
          u32 md;
          six = 6;
          asm("" : "+r"(six));
          md = mv0 % six;
          row = t4[(u16)md];
        }
        {
          register u32 offb asm("r2");
          offb = *(s32*)((u8*)p + 0x78) << 3;
          offb += (u32)row;
          ent = (const s32*)offb;
        }
        {
          register u32* rp asm("r3");
          register u32 A3 asm("r6");
          register u32 C3 asm("r5");
          register u32 seed2 asm("r4");
          u32 sd;
          u32 r0v;
          u32 r2v;
          rp = &RNG_0202f388;
          sd = *rp;
          asm("" : "+r"(sd));
          A3 = 0x343FD;
          asm("" : "+r"(A3));
          r0v = sd * A3;
          C3 = 0x269EC3;
          asm("" : "+r"(C3));
          r0v += C3;
          r0v <<= 1;
          seed2 = r0v >> 1;
          *rp = seed2;
          (p->s).d.y = ent[1] + ((r0v >> 0x11) & 0x1F);
          r2v = seed2 * A3;
          r2v += C3;
          r2v <<= 1;
          *rp = r2v >> 1;
          (p->s).d.x = ent[0] - ((r2v >> 0x11) & 0x3F);
        }
        SetMotion(&p->s, *mo8);
        asm("" : "+r"(m9));
        {
          register s32 w1 asm("r1");
          w1 = m9;
          (p->s).work[3] = w1;
        }
        (p->s).mode[2]++;
      }
        /* fallthrough */
      case 1: {
        register u32 one asm("r1");
        s32 t3 = (p->s).work[3] + 1;
        u32 tf;
        s32 v2;
        (p->s).work[3] = t3;
        tf = t3 & 0xFF;
        one = 1;
        if (tf & one) {
          register s32 vf asm("r0");
          vf = (p->s).flags;
          vf |= one;
          v2 = vf;
        } else {
          register u8 lf3 asm("r1");
          register s32 vv3 asm("r0");
          lf3 = (p->s).flags;
          vv3 = 0xFE;
          vv3 &= lf3;
          v2 = vv3;
        }
        (p->s).flags = v2;
        (p->s).d.y += 0x10;
        if ((p->s).d.y > 0x700) {
          (p->s).d.y = 0x700;
        }
        (p->s).coord.y += (p->s).d.y;
        (p->s).coord.x += (p->s).d.x;
        UpdateMotionGraphic(&p->s);
        break;
      }
    }
  }
}


INCASM("asm/vfx/unk_32_post_b.inc");

// 0x080BB5D4
void FUN_080bb5d4(struct VFX* p) {
  if ((u8)--(p->s).work[2] == 0) {
    SET_VFX_ROUTINE(p, ENTITY_DIE);
    return;
  }
  switch ((p->s).mode[2]) {
    case 0: {
      (p->s).work[2] = RANDOM(RNG_0202f388) % 6 + 0x12;
      SetMotion(&p->s, MOTION(0x27, 0x0C));
      (p->s).work[3] = 0;
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1: {
      s32 dy;
      s32 w3 = (p->s).work[3] + 1;
      (p->s).work[3] = w3;
      {
        u32 kf;
        u32 one;
        kf = 0xFF;
        w3 &= kf;
        one = 1;
        w3 &= one;
        if (w3 != 0) {
          (p->s).flags |= one;
        } else {
          u8 t = (p->s).flags;
          u8 fv = 0xFE;
          fv &= t;
          asm volatile("" ::"r"(t));
          (p->s).flags = fv;
        }
      }
      dy = (p->s).d.y;
      dy += ((-0x100 - dy) << 4) >> 8;
      (p->s).d.y = dy;
      (p->s).coord.y += dy;
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}

// 0x080BB68C
void FUN_080bb68c(struct VFX* p) {
  if ((u8)--(p->s).work[2] == 0) {
    SET_VFX_ROUTINE(p, ENTITY_DIE);
    return;
  }
  switch ((p->s).mode[2]) {
    case 0: {
      u32 z;
      (p->s).work[2] = RANDOM(RNG_0202f388) % 6 + 0x1E;
      if ((p->s).work[0] == 0) {
        SetMotion(&p->s, MOTION(0x27, 0x0E));
      } else {
        SetMotion(&p->s, MOTION(0x27, 0x0F));
      }
      {
        u32 t = RNG_0202f388 * 0x343FD + 0x269EC3;
        t <<= 1;
        RNG_0202f388 = t >> 1;
        (p->s).unk_coord.x = (s32)((t << 6) >> 23) - 0x100;
      }
      z = 0;
      (p->s).d.y = z;
      (p->s).d.x = z;
      (p->s).work[3] = z;
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1: {
      s32 dy;
      s32 dx;
      s32 w3 = (p->s).work[3] + 1;
      (p->s).work[3] = w3;
      {
        u32 kf;
        u32 one;
        kf = 0xFF;
        w3 &= kf;
        one = 1;
        w3 &= one;
        if (w3 != 0) {
          (p->s).flags |= one;
        } else {
          u8 t = (p->s).flags;
          u8 fv = 0xFE;
          fv &= t;
          asm volatile("" ::"r"(t));
          (p->s).flags = fv;
        }
      }
      {
        s32 g = (p->props).unk32.unk_8;
        s32 d = 0x180 - g;
        g += (d * 5 << 3) >> 8;
        (p->props).unk32.unk_8 = g;
        ((p->s).spr).mag.x = g;
        ((p->s).spr).mag.y = (p->props).unk32.unk_8;
      }
      dy = (p->s).d.y;
      dy += ((-0x100 - dy) << 4) >> 8;
      (p->s).d.y = dy;
      {
        s32 ux = (p->s).unk_coord.x;
        dx = (p->s).d.x;
        dx += ((ux - dx) << 4) >> 8;
      }
      (p->s).d.x = dx;
      (p->s).coord.y += dy;
      (p->s).coord.x += dx;
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}

void FUN_080bb7c4(struct VFX* p) {
  if (--(p->s).work[2] == 0) {
    SET_VFX_ROUTINE(p, ENTITY_DIE);
    return;
  }

  switch ((p->s).mode[2]) {
    case 0:
      SetMotion(&p->s, MOTION(SM039_PANTHEON_AQUA, 12));
      (p->s).work[3] = 0;
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      (p->s).work[3]++;
      (p->s).coord.y += (p->s).d.y;
      (p->s).coord.x += (p->s).d.x;
      UpdateMotionGraphic(&p->s);
      break;
  }
}

void FUN_080bade8(struct VFX* p);
void FUN_080bb048(struct VFX* p);
void FUN_080bb17c(struct VFX* p);
void FUN_080bb2d8(struct VFX* p);
void FUN_080bb3d4(struct VFX* p);
void FUN_080bb5d4(struct VFX* p);
void FUN_080bb68c(struct VFX* p);
void FUN_080bb7c4(struct VFX* p);

// clang-format off
static const VFXFunc sUpdates[8] = {
    FUN_080bade8,
    FUN_080bb048,
    FUN_080bb17c,
    FUN_080bb2d8,
    FUN_080bb3d4,
    FUN_080bb5d4,
    FUN_080bb68c,
    FUN_080bb7c4,
};
// clang-format on

const s32 s32_ARRAY_ARRAY_0836ec64[6][8] = {
    {0x00000120, -0x00000200, -0x000000B0, -0x00000160, -0x000000B0, -0x00000200, 0x00000120, -0x00000160}, {-0x000000B0, -0x00000160, -0x000000B0, -0x00000200, 0x00000120, -0x00000160, 0x00000120, -0x00000200}, {-0x000000B0, -0x00000200, 0x00000120, -0x00000160, 0x00000120, -0x00000200, -0x000000B0, -0x00000160}, {-0x00000060, -0x00000160, 0x00000060, -0x00000200, 0x000000A0, -0x00000160, -0x000000A0, -0x00000200}, {-0x000000A0, -0x00000160, 0x00000060, -0x00000200, -0x00000060, -0x00000160, 0x000000A0, -0x00000200}, {0x000000A0, -0x00000200, -0x000000A0, -0x00000160, 0x00000060, -0x00000200, -0x00000060, -0x00000160},
};

static const s32* const PTR_ARRAY_0836ed24[6] = {
    s32_ARRAY_ARRAY_0836ec64[0], s32_ARRAY_ARRAY_0836ec64[1], s32_ARRAY_ARRAY_0836ec64[2], s32_ARRAY_ARRAY_0836ec64[3], s32_ARRAY_ARRAY_0836ec64[4], s32_ARRAY_ARRAY_0836ec64[5],
};
