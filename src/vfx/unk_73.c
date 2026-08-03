#include "global.h"
#include "metatile.h"
#include "story.h"
#include "vfx.h"

static const VFXFunc sInitializers[2];
static const VFXFunc sUpdates[2];

void Ghost73_Init(struct VFX* p);
void Ghost73_Update(struct VFX* p);
void Ghost73_Die(struct VFX* p);

// clang-format off
const VFXRoutine gGhost73Routine = {
    [ENTITY_INIT] =      Ghost73_Init,
    [ENTITY_UPDATE] =    Ghost73_Update,
    [ENTITY_DIE] =       Ghost73_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

struct VFX* FUN_080c6e24(struct Entity* e) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_073);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 0;
    (p->s).unk_28 = e;
  }
  return p;
}

void FUN_080c6e70(struct Entity* e, struct Coord* c) {
  s32 i;
  for (i = 0; i < 3; i++) {
    struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
    if (p != NULL) {
      (p->s).taskCol = 1;
      INIT_VFX_ROUTINE(p, VFX_UNK_073);
      (p->s).tileNum = 0;
      (p->s).palID = 0;
      (p->s).work[0] = 1;
      (p->s).work[1] = i;
      (p->s).unk_28 = e;
      (p->s).coord.x = c->x;
      (p->s).coord.y = c->y;
    }
  }
}


void Ghost73_Init(struct VFX* p) {
  (sInitializers[(p->s).work[0]])(p);
}


void Ghost73_Update(struct VFX* p) {
  if (IS_METTAUR) {
    (p->s).flags &= ~DISPLAY;
    (p->s).flags &= ~FLIPABLE;
    SET_VFX_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }
  (sUpdates[(p->s).work[0]])(p);
}


void Ghost73_Die(struct VFX* p) {
  (p->s).flags &= ~DISPLAY;
  SET_VFX_ROUTINE(p, ENTITY_EXIT);
}

// 0x080C6F60
void FUN_080c6f60(struct VFX* p) {
  register struct Entity* e asm("r8");
  register struct Coord* ec asm("sb");
  register s32 xf asm("r4");
  register s32 yf asm("r6");
  register s32 yv asm("r3");
  s32 z7;
  {
    struct Entity* e0 = (p->s).unk_28;
    e = e0;
    ec = (struct Coord*)((u8*)e + 0x54);
    {
      register s32 t asm("r0");
      register s32 one asm("r1");
      t = e0->flags;
    t <<= 24;
    xf = (u32)t >> 28;
    one = 1;
    xf &= one;
      yf = (u32)t >> 29;
      yf &= one;
    }
  }
  {
    register u8 fl asm("r1");
    register s32 v asm("r0");
    fl = (p->s).flags;
    v = 1;
    z7 = 0;
    v |= fl;
    (p->s).flags = v;
  }
  InitNonAffineMotion(&p->s);
  SetMotion(&p->s, 0xDC06);
  if (xf != 0) {
    (p->s).flags |= 0x10;
  } else {
    (p->s).flags &= 0xEF;
  }
  {
    register u8* oa asm("r2");
    u32 x1;
    s32 sh4, ov, m11;
    asm volatile("add %0, %1, #0" : "=&l"(x1) : "l"(xf));
    ((p->s).spr).xflip = x1;
    oa = (u8*)p + 0x4a;
    sh4 = x1 << 4;
    ov = *oa;
    m11 = -0x11;
    m11 &= ov;
    *oa = m11 | sh4;
    asm volatile("add %0, %1, #0" : "=&l"(yv) : "l"(yf));
    asm volatile("add %0, %1, #0" : "=&l"(xf) : "l"(oa));
  }
  if (yv != 0) {
    (p->s).flags |= 0x20;
  } else {
    register u8 h asm("r1");
    register u8 g asm("r0");
    h = (p->s).flags;
    asm("" : "+r"(h));
    g = 0xDF;
    g &= h;
    (p->s).flags = g;
  }
  {
    register s32 one asm("r6");
    register s32 v2 asm("r1");
    s32 sh5, ov2, m21;
    one = 1;
    v2 = one;
    v2 &= yv;
    ((p->s).spr).yflip = v2;
    sh5 = v2 << 5;
    ov2 = *(u8*)xf;
    m21 = -0x21;
    m21 &= ov2;
    *(u8*)xf = m21 | sh5;
    {
      register struct Coord* c2 asm("r2");
      c2 = ec;
      (p->s).coord.x = c2->x;
      (p->s).coord.y = c2->y;
    }
    {
      register struct Entity* e1 asm("r1");
      e1 = e;
      (p->s).d.x = e1->d.x;
    }
    {
      register s32 f asm("r1");
      f = 0;
      {
        register struct Entity* e2 asm("r2");
        e2 = e;
        if ((u8)(e2->mode[3] - 1) <= 1) {
          f = 1;
        }
      }
      (p->s).work[3] = f;
      {
        register s32 dy asm("r0");
        dy = 0;
        if (f != 0) {
          register struct Entity* e3 asm("r1");
          e3 = e;
          dy = e3->d.y;
        }
        (p->s).d.y = dy;
      }
    }
    (p->s).work[2] = 0x16;
    {
      u32 tbl = (u32)gVFXFnTable;
      EntityFunc** rt = (EntityFunc**)(tbl + (((p->s).id) << 2));
      *(u32*)((p->s).mode) = one;
      (p->s).onUpdate = (void*)((*rt)[1]);
    }
  }
  asm volatile("" : "+l"(z7));
  Ghost73_Update(p);
}

// 0x080C705C
void FUN_080c705c(struct VFX* p) {
  s32 cx;
  s32 dx;
  s32 cy;
  s32 dy;
  cx = (p->s).coord.x;
  dx = (p->s).d.x;
  (p->s).coord.x = cx + dx;
  (p->s).d.x = dx * 0xF5 / 0x100;
  cy = (p->s).coord.y;
  dy = (p->s).d.y;
  (p->s).coord.y = cy + dy;
  if ((p->s).work[3] != 0) {
    s32 nd = dy + 0x20;
    (p->s).d.y = nd;
    if (nd > 0x700) {
      (p->s).d.y = 0x700;
    }
  }
  UpdateMotionGraphic(&p->s);
  (p->s).work[2]--;
  if ((p->s).work[3] != 0) {
    s32 x = (p->s).coord.x;
    register s32 y asm("r2");
    register s32 yy asm("r3");
    y = (p->s).coord.y;
    yy = y - 0x200;
    if ((p->s).flags & 0x20) {
      yy = y + 0x200;
    }
    if (((bool16 (*)(s32, s32))FUN_080098a4)(x, yy)) {
      (p->s).work[2] = 0;
    }
  } else {
    s32 g = FUN_08009f6c((p->s).coord.x, (p->s).coord.y);
    if ((p->s).coord.y > g) {
      (p->s).coord.y = g;
    }
  }
  if ((p->s).work[2] == 0) {
    struct Entity* q = (p->s).unk_28;
    struct Coord* pc = &(p->s).coord;
    FUN_080c6e70(q, pc);
    CreateSmoke(1, pc);
    SET_VFX_ROUTINE(p, ENTITY_DIE);
  }
}

extern const motion_t motion_t_ARRAY_0836f884[3];

void FUN_080c7120(struct VFX* p) {
  struct Entity* e = (p->s).unk_28;
  u32 xf = e->flags >> 4;
  s32 w1;
  {
    u32 one = 1;
    xf &= one;
    w1 = (p->s).work[1];
    one |= (p->s).flags;
    (p->s).flags = one;
  }
  InitNonAffineMotion(&p->s);
  {
    register u32 t2 asm("r2");
    s32 v;
    if (w1 == 1) {
      register u32 ta asm("r1");
      ta = xf;
      asm("" : "+r"(ta));
      ta ^= w1;
      asm("" : "+r"(ta));
      t2 = ta;
    } else {
      register u32 tb asm("r1");
      tb = xf;
      asm("" : "+r"(tb));
      t2 = tb;
    }
    if (t2 != 0) {
      register u8 lf asm("r1");
      register s32 vv asm("r0");
      lf = (p->s).flags;
      vv = 0x10;
      vv |= lf;
      v = vv;
    } else {
      register u8 lf2 asm("r1");
      register s32 vv2 asm("r0");
      lf2 = (p->s).flags;
      vv2 = 0xEF;
      vv2 &= lf2;
      v = vv2;
    }
    (p->s).flags = v;
    {
      register u32 one2 asm("r4");
      register s32 one8 asm("r8");
      u8* a3;
      u32 y2;
      s32 v2;
      one2 = 1;
      {
        u32 x1 = one2;
        x1 &= t2;
        ((p->s).spr).xflip = x1;
        a3 = (u8*)p + 0x4a;
        {
          s32 sh = x1 << 4;
          u8 b = *a3;
          s32 msk = -0x11;
          msk &= b;
          msk |= sh;
          *a3 = msk;
        }
      }
      y2 = e->flags >> 5;
      y2 &= one2;
      if (y2 != 0) {
        register s32 vf2 asm("r0");
        register u32 c20 asm("r1");
        vf2 = (p->s).flags;
        c20 = 0x20;
        vf2 |= c20;
        v2 = vf2;
      } else {
        register u8 lf4 asm("r1");
        register s32 vv4 asm("r0");
        lf4 = (p->s).flags;
        vv4 = 0xDF;
        vv4 &= lf4;
        v2 = vv4;
      }
      (p->s).flags = v2;
      one8 = 1;
      {
        register u32 y1 asm("r1");
        y1 = one8;
        y1 &= y2;
        *((u8*)p + 0x4d) = y1;
        {
          s32 sh2 = y1 << 5;
          u8 b2 = *a3;
          s32 msk2 = -0x21;
          msk2 &= b2;
          msk2 |= sh2;
          *a3 = msk2;
        }
      }
      SetMotion(&p->s, motion_t_ARRAY_0836f884[w1]);
      if (xf != 0) {
        w1 = 2 - w1;
      }
      {
        register s32 dx0 asm("r1");
        register u32* rp asm("r6");
        register u32 m9 asm("r4");
        register u32 A3 asm("r5");
        dx0 = (w1 - 1) << 8;
        rp = &RNG_0202f388;
        {
          u32 sd = *rp;
          u32 r0v;
          u32 seed2;
          u32 r2v;
          register u32 C3 asm("r3");
          asm("" : "+r"(sd));
          A3 = 0x343FD;
          asm("" : "+r"(A3));
          r0v = sd * A3;
          C3 = 0x269EC3;
          asm("" : "+r"(C3));
          r0v += C3;
          r0v <<= 1;
          seed2 = r0v >> 1;
          {
            u32 sh1 = r0v >> 0x11;
            m9 = 0x1FF;
            asm("" : "+r"(m9));
            (p->s).d.x = dx0 + (sh1 & m9) + -0x100;
          }
          r2v = seed2 * A3;
          r2v += C3;
          r2v <<= 1;
          *rp = r2v >> 1;
          (p->s).d.y = -0x200 - ((r2v >> 0x11) & m9);
        }
      }
      (p->s).work[2] = 0;
      {
        u32 tbl, id;
        EntityFunc** routine_table;
        tbl = (u32)gVFXFnTable;
        id = ((p->s).id) << 2;
        routine_table = (EntityFunc**)(tbl + id);
        *(u32*)((p->s).mode) = one8;
        (p->s).onUpdate = (void*)(*routine_table)[1];
      }
      Ghost73_Update(p);
    }
  }
}


// 0x080c7250
void FUN_080c7250(struct VFX* p) {
  (p->s).coord.x += (p->s).d.x;
  (p->s).coord.y += (p->s).d.y;
  (p->s).d.y += 0x40;
  UpdateMotionGraphic(&p->s);
  (p->s).work[2]++;
  if ((p->s).work[2] & 1) {
    (p->s).flags |= DISPLAY;
  } else {
    (p->s).flags &= ~DISPLAY;
  }
  if (FUN_080098a4((p->s).coord.x, (p->s).coord.y)) {
    CreateSmoke(3, &(p->s).coord);
    SET_VFX_ROUTINE(p, ENTITY_DIE);
  }
}

// --------------------------------------------

void FUN_080c6f60(struct VFX* p);
void FUN_080c7120(struct VFX* p);

static const VFXFunc sInitializers[2] = {
    FUN_080c6f60,
    FUN_080c7120,
};

// --------------------------------------------

void FUN_080c705c(struct VFX* p);
void FUN_080c7250(struct VFX* p);

static const VFXFunc sUpdates[2] = {
    FUN_080c705c,
    FUN_080c7250,
};

// --------------------------------------------

const motion_t motion_t_ARRAY_0836f884[3] = {
    MOTION(SM220_CANNON_HOPPER, 8),
    MOTION(SM220_CANNON_HOPPER, 8),
    MOTION(SM220_CANNON_HOPPER, 9),
};
