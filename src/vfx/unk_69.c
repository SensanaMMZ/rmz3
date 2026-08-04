#include "global.h"
#include "script.h"
#include "vfx.h"

void Ghost69_Init(struct VFX* p);
void Ghost69_Update(struct VFX* p);
void Ghost69_Die(struct VFX* p);

// clang-format off
const VFXRoutine gGhost69Routine = {
    [ENTITY_INIT] =      Ghost69_Init,
    [ENTITY_UPDATE] =    Ghost69_Update,
    [ENTITY_DIE] =       Ghost69_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

struct VFX* FUN_080c4e58(struct Coord* c, void* _, struct Entity* e) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_069);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 0;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
    (p->s).unk_28 = e;
  }
  return p;
}

struct VFX* FUN_080c4eac(struct Entity* e, struct Coord* c, u8 n) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_069);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 1;
    (p->s).work[1] = n;
    (p->s).unk_coord.x = c->x;
    (p->s).unk_coord.y = c->y;
    (p->s).unk_28 = e;
  }
  return p;
}

struct VFX* FUN_080c4f04(struct Entity* e, struct Coord* c, u8 n) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_069);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 2;
    (p->s).work[1] = n;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
    (p->s).unk_28 = e;
  }
  return p;
}

struct VFX* FUN_080c4f60(struct Entity* e, struct Coord* c1, struct Coord* c2, u8 n) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_069);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 3;
    (p->s).work[1] = n;
    (p->s).unk_coord.x = c1->x;
    (p->s).unk_coord.y = c1->y;
    (p->props).unk69.c.x = c2->x;
    (p->props).unk69.c.y = c2->y;
    (p->s).unk_28 = e;
  }
  return p;
}

extern const VFXFunc sGhost69Updates[7];

struct VFX* FUN_080c4fc8(struct Coord* c) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_069);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
  }
  return p;
}

struct Unk69PropsV2 { u8 unk_0[12]; u16 unk_c; u16 unk_e; };

struct VFX* FUN_080c5018(struct Coord* c, u8 a1, u16 a2) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_069);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
    (p->s).work[1] = a1;
    ((struct Unk69PropsV2*)(p->props).raw)->unk_c = a2;
  }
  return p;
}

struct VFX* FUN_080c5078(struct Coord* c, u8 a1, u16 a2, u16 a3) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_069);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
    (p->s).work[1] = a1;
    ((struct Unk69PropsV2*)(p->props).raw)->unk_e = a2;
    ((struct Unk69PropsV2*)(p->props).raw)->unk_c = a3;
  }
  return p;
}

void Ghost69_Init(struct VFX* p) {
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
  (p->s).mode[1] = (p->s).work[0];
  (p->s).mode[2] = 0;
  (p->s).mode[3] = 0;
  Ghost69_Update(p);
}


void Ghost69_Update(struct VFX* p) {
  (sGhost69Updates[(p->s).mode[1]])(p);
}


void Ghost69_Die(struct VFX* p) {
  (p->s).flags &= ~DISPLAY;
  SET_VFX_ROUTINE(p, ENTITY_EXIT);
}

// 0x080C5144
void FUN_080c5144(struct VFX* p) {
  register s32 m asm("r5");
  if (((p->s).unk_28)->mode[0] > 1) {
    SET_VFX_ROUTINE(p, ENTITY_DIE);
    return;
  }
  m = (p->s).mode[2];
  switch (m) {
    case 0: {
      register u8 fv asm("r0");
      register u8 fl asm("r1");
      InitNonAffineMotion(&p->s);
      ResetDynamicMotion(&p->s);
      fl = (p->s).flags;
      asm("" : "+r"(fl));
      fv = 0xFE;
      fv &= fl;
      fl = 2;
      fv |= fl;
      (p->s).flags = fv;
      *(s32*)((u8*)p + 0x74) = m;
      *(s32*)((u8*)p + 0x78) = m;
      (p->s).taskCol = 0x19;
      SetMotion(&p->s, 0xB700);
      (p->s).work[3] = m;
      (p->s).work[2] = 0x3C;
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1: {
      struct Entity* q = (p->s).unk_28;
      (p->s).coord.x = (q->coord).x + *(s32*)((u8*)p + 0x74);
      (p->s).coord.y = (q->coord).y + *(s32*)((u8*)p + 0x78);
      {
        register u8 sf asm("r1");
        register s32 k asm("r0");
        sf = q->scriptEntity->flags;
        k = 1;
        k &= sf;
        if (k == 0) {
          goto off;
        }
      }
      {
        u8 md = q->mode[1];
        if (md == 5) {
          goto off;
        }
        if (md == 6 && q->mode[2] <= 1) {
          goto off;
        }
      }
      {
        register s32 sv asm("r0");
        register s32 k2 asm("r1");
        sv = *(u32*)((u8*)q + 0x8c);
        k2 = 1;
        sv &= k2;
        if (sv != 0) {
          (p->s).work[2] = 0x5A;
          goto off;
        }
      }
      if ((p->s).work[2] != 0) {
        s32 t = (p->s).work[2] - 1;
        (p->s).work[2] = t;
        t <<= 24;
        if (t != 0) {
          goto off;
        }
      }
      {
        register u8 fl3 asm("r1");
        register u8 g asm("r0");
        fl3 = (p->s).flags;
        asm("" : "+r"(fl3));
        g = 1;
        g |= fl3;
        (p->s).flags = g;
        goto fs;
      }
    off : {
      register u8 h asm("r1");
      register u8 g2 asm("r0");
      h = (p->s).flags;
      asm("" : "+r"(h));
      g2 = 0xFE;
      g2 &= h;
      (p->s).flags = g2;
    }
    fs:
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}

// 0x080C521C
void FUN_080c521c(struct VFX* p) {
  struct Entity* q = (p->s).unk_28;
  register s32 sc asm("r4");
  if (q->mode[0] > 1) {
    SET_VFX_ROUTINE(p, ENTITY_DIE);
    return;
  }
  switch ((p->s).mode[2]) {
    case 0: {
      InitScalerotMotion1(&p->s);
      {
        u16* h = (u16*)((u8*)p + 0x50);
        register s32 zero asm("r1");
        zero = 0;
        sc = 0x80 * 2;
        *h = sc;
        h++;
        *h = sc;
        *((u8*)h - 0x2e) = zero;
      }
      ResetDynamicMotion(&p->s);
      {
        register u8 fv asm("r0");
        register s32 k asm("r1");
        fv = (p->s).flags;
        k = 2;
        fv |= k;
        k = 1;
        fv |= k;
        (p->s).flags = fv;
      }
      SetMotion(&p->s, MOTION(0xB8, 0x01));
      (p->s).work[2] = 0x10;
      (p->s).d.x = sc;
      {
        struct Entity* r = (p->s).unk_28;
        s32 ox, oy;
        ox = (p->s).unk_coord.x + 0xE0 * 16;
        (p->s).coord.x = r->coord.x + ox;
        oy = (p->s).unk_coord.y + 0xE0 * 8;
        (p->s).coord.y = r->coord.y + oy;
      }
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1: {
      register s32 tx asm("r6");
      s32 ty;
      struct Entity* r = (p->s).unk_28;
      s32 v;
      {
        register s32 t0 asm("r0");
        t0 = r->coord.x;
        tx = t0 + 0xE0 * 16;
        t0 = r->coord.y;
        ty = t0 + 0xE0 * 8;
      }
      {
        register s32 c asm("r1");
        register s32 d asm("r0");
        c = (p->s).coord.x;
        d = tx - c;
        d <<= 5;
        d >>= 8;
        c += d;
        (p->s).coord.x = c;
      }
      {
        register s32 c2 asm("r1");
        register s32 d2 asm("r0");
        c2 = (p->s).coord.y;
        d2 = ty - c2;
        d2 <<= 5;
        d2 >>= 8;
        c2 += d2;
        (p->s).coord.y = c2;
      }
      {
        register s32 dd asm("r1");
        register s32 e asm("r0");
        dd = (p->s).d.x;
        e = 0x20;
        e -= dd;
        e <<= 4;
        e >>= 8;
        dd += e;
        (p->s).d.x = dd;
        v = dd;
      }
      *(u16*)((u8*)p + 0x50) = v;
      asm volatile("" ::: "memory");
      {
        register s32 d3 asm("r0");
        u16* h2;
        d3 = (p->s).d.x;
        h2 = (u16*)((u8*)p + 0x52);
        *h2 = d3;
      }
      if ((p->s).work[2] != 0) {
        s32 t = (p->s).work[2] - 1;
        (p->s).work[2] = t;
        if ((u8)t != 0) {
          goto upd;
        }
      }
      SET_VFX_ROUTINE(p, ENTITY_DIE);
    upd:
      UpdateMotionGraphic(&p->s);
      asm volatile("" ::"r"(sc), "r"(ty), "r"(tx));
      break;
    }
  }
}


void FUN_080c5328(struct VFX* p) {
  u8 md;
  if (((p->s).unk_28)->mode[0] > 1) {
    goto die;
  }
  md = (p->s).mode[2];
  switch (md) {
    case 0:
      InitNonAffineMotion(&p->s);
      ResetDynamicMotion(&p->s);
      {
        u8 f = DISPLAY | (p->s).flags;
        f |= FLIPABLE;
        (p->s).flags = f;
      }
      (p->props).unk69.c.x = md;
      (p->props).unk69.c.y = md;
      SetMotion(&p->s, MOTION(0xB9, 0x03));
      (p->s).work[2] = 0x28;
      (p->s).mode[2]++;
      /* fallthrough */
    case 1:
      (p->s).coord.x = ((p->s).unk_28)->coord.x + (p->props).unk69.c.x;
      (p->s).coord.y = ((p->s).unk_28)->coord.y + (p->props).unk69.c.y;
      UpdateMotionGraphic(&p->s);
      if ((p->s).work[2] != 0) {
        s32 t = (p->s).work[2] - 1;
        (p->s).work[2] = t;
        if ((t << 24) != 0) {
          break;
        }
      }
    die:
      SET_VFX_ROUTINE(p, ENTITY_DIE);
      break;
  }
}

// 0x080C53B8
void FUN_080c53b8(struct VFX* p) {
  if (((p->s).unk_28)->mode[0] > 1) {
    u32 tbl = (u32)gVFXFnTable;
    EntityFunc** rt = (EntityFunc**)((((p->s).id) << 2) + tbl);
    register u32 two asm("r1");
    two = 2;
    *(u32*)((p->s).mode) = two;
    (p->s).onUpdate = (void*)((*rt)[2]);
    return;
  }
  switch ((p->s).mode[2]) {
    case 0: {
      register s32 k asm("r4");
      InitScalerotMotion1(&p->s);
      {
        register u8* q asm("r0");
        register s32 zr asm("r1");
        q = (u8*)p + 0x50;
        zr = 0;
        k = 0x80 << 1;
        *(u16*)q = k;
        q += 2;
        *(u16*)q = k;
        q -= 0x2e;
        *q = zr;
      }
      ResetDynamicMotion(&p->s);
      {
        register u8 g asm("r0");
        register s32 kk asm("r1");
        g = (p->s).flags;
        kk = 2;
        g |= kk;
        kk = 1;
        g |= kk;
        (p->s).flags = g;
      }
      SetMotion(&p->s, 0xB801);
      (p->s).work[2] = 0x10;
      (p->s).d.x = k;
      {
        register s32 base asm("r1");
        register struct Entity* e asm("r2");
        register s32 t asm("r0");
        base = 0xFFFFCA00;
        (p->s).unk_coord.y = base;
        e = (p->s).unk_28;
        t = (e->coord).x + base;
        (p->s).unk_coord.x = t;
        base = *(s32*)((u8*)p + 0x74);
        t += base;
        (p->s).coord.x = t;
        base = *(s32*)((u8*)p + 0x78);
        {
          register s32 k2 asm("r0");
          k2 = 0xe0 << 3;
          base += k2;
        }
        t = (e->coord).y + base;
        (p->s).coord.y = t;
      }
      {
        register s32 a asm("r0");
        register s32 w1 asm("r1");
        w1 = (p->s).work[1];
        a = 0x2a;
        a = w1 * a;
        w1 = 0xff;
        a &= w1;
        (p->s).d.y = a;
      }
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1: {
      register struct Entity* e2 asm("ip");
      register s32 uy asm("r1");
      s32 sy;
      {
        register s32 t2 asm("r0");
        uy = (p->s).unk_coord.y;
        t2 = 0xe0 << 4;
        t2 -= uy;
        t2 <<= 5;
        t2 >>= 8;
        uy += t2;
        (p->s).unk_coord.y = uy;
      }
      {
        register struct Entity* e3 asm("r2");
        register s32 t3 asm("r0");
        e3 = (p->s).unk_28;
        e2 = e3;
        t3 = (e3->coord).x;
        uy += t3;
        (p->s).unk_coord.x = uy;
      }
      {
        register s32 cy asm("r2");
        register s32 n asm("r1");
        register s32 t4 asm("r0");
        cy = *(s32*)((u8*)p + 0x78);
        n = -cy;
        t4 = n << 2;
        t4 += n;
        t4 <<= 2;
        t4 >>= 8;
        cy += t4;
        *(s32*)((u8*)p + 0x78) = cy;
      }
      {
        register s32 dy asm("r1");
        register s32 nd asm("r0");
        dy = (p->s).d.y;
        nd = dy + 0xa;
        (p->s).d.y = nd;
        if (nd > 0xff) {
          nd -= 0xff;
          (p->s).d.y = nd;
        }
      }
      {
        register s32 amp asm("r2");
        register const s16* tb asm("r3");
        register s32 ang asm("r1");
        register s32 sx asm("r6");
        amp = *(s32*)((u8*)p + 0x78);
        sy = amp;
        asm volatile("" : "+r"(sy));
        tb = gSineTable;
        ang = (p->s).d.y;
        {
          register s32 o asm("r0");
          register s32 z4 asm("r4");
          o = (u32)(ang << 0x18) >> 0x17;
          o += (s32)tb;
          asm volatile("mov %0, #0" : "=l"(z4));
          asm volatile("ldrsh %0, [%1, %2]" : "=l"(o) : "l"(o), "l"(z4));
          o = amp * o;
          o >>= 8;
          sx = o;
          ang += 0x40;
          {
            register s32 o2 asm("r1");
            register s32 z5 asm("r3");
            o2 = (u32)(ang << 0x18) >> 0x17;
            o2 += (s32)tb;
            asm volatile("mov %0, #0" : "=l"(z5));
            asm volatile("ldrsh %0, [%1, %2]" : "=l"(o2) : "l"(o2), "l"(z5));
            o2 = amp * o2;
            sy = o2 >> 8;
          }
          o <<= 3;
          o -= sx;
          o <<= 4;
          sx = o >> 8;
        }
        asm("" :: "l"(sy));
        (p->s).coord.x = (p->s).unk_coord.x + sx;
        {
          register s32 k3 asm("r4");
          register s32 t5 asm("r1");
          asm volatile("mov %0, #0xe0\n\tlsl %0, %0, #0x3" : "=l"(k3));
          t5 = sy + k3;
          {
            register struct Entity* e4 asm("r2");
            register s32 yy asm("r0");
            e4 = e2;
            yy = (e4->coord).y;
            yy += t5;
            (p->s).coord.y = yy;
          }
        }
      }
      {
        register s32 dx asm("r1");
        register s32 t6 asm("r0");
        dx = (p->s).d.x;
        t6 = 0x20;
        t6 -= dx;
        t6 <<= 4;
        t6 >>= 8;
        dx += t6;
        (p->s).d.x = dx;
        *(u16*)((u8*)p + 0x50) = dx;
      }
      {
        register s32 dv asm("r0");
        register u8* q2 asm("r1");
        asm volatile("" ::: "memory");
        dv = (p->s).d.x;
        q2 = (u8*)p + 0x52;
        *(u16*)q2 = dv;
      }
      {
        register s32 w2 asm("r0");
        w2 = (p->s).work[2];
        if (w2 != 0) {
          w2 -= 1;
          (p->s).work[2] = w2;
          if ((w2 << 24) != 0) {
            goto upd;
          }
        }
      }
      {
        u32 tbl2 = (u32)gVFXFnTable;
        EntityFunc** rt2 = (EntityFunc**)((((p->s).id) << 2) + tbl2);
        register u32 two2 asm("r1");
        two2 = 2;
        *(u32*)((p->s).mode) = two2;
        (p->s).onUpdate = (void*)((*rt2)[2]);
      }
    upd:
      UpdateMotionGraphic(&p->s);
      asm("" :: "l"(sy));
      break;
    }
  }
}


void nop_080c552c(struct VFX* p) {}

// 0x080C5530
void FUN_080c5530(struct VFX* p) {
  switch ((p->s).mode[2]) {
    case 0: {
      u32 t = RNG_0202f388 * 0x343FD + 0x269EC3;
      u32 r;
      register u16* h asm("r0");
      t <<= 1;
      RNG_0202f388 = t >> 1;
      r = (t >> 0x11) % 0xFF;
      (p->s).work[3] = r;
      *(u8*)((u8*)p + 0x24) = r;
      h = (u16*)((u8*)p + 0x50);
      *h = 0x80;
      asm volatile("add %0, #2" : "+r"(h));
      *h = 0x80;
      (p->s).mode[2]++;
    }
    case 1: {
      s32 dx = (p->s).d.x;
      (p->s).d.x = dx + ((-dx * 12) >> 8);
      (p->s).d.y += 0x40;
      if ((p->s).d.y > 0x700) {
        (p->s).d.y = 0x700;
      }
      (p->s).coord.x += (p->s).d.x;
      (p->s).coord.y += (p->s).d.y;
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}

void FUN_080c55bc(struct VFX* p) {
  switch ((p->s).mode[2]) {
    case 0:
      (p->s).work[2] = 0x50;
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      UpdateMotionGraphic(&p->s);
      (p->s).d.y += 0x20;
      if ((p->s).d.y > 0x700) {
        (p->s).d.y = 0x700;
      }
      (p->s).coord.y += (p->s).d.y;
      (p->s).coord.x += (p->s).d.x;
      if ((p->s).work[2] == 0 || --(p->s).work[2] == 0) {
        SET_VFX_ROUTINE(p, ENTITY_DIE);
      }
      break;
  }
}

// --------------------------------------------

void FUN_080c5144(struct VFX* p);
void FUN_080c521c(struct VFX* p);
void FUN_080c5328(struct VFX* p);
void FUN_080c53b8(struct VFX* p);
void nop_080c552c(struct VFX* p);
void FUN_080c5530(struct VFX* p);
void FUN_080c55bc(struct VFX* p);

// clang-format off
const VFXFunc sGhost69Updates[7] = {
    FUN_080c5144,
    FUN_080c521c,
    FUN_080c5328,
    FUN_080c53b8,
    nop_080c552c,
    FUN_080c5530,
    FUN_080c55bc,
};
// clang-format on
