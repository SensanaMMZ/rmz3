#include "global.h"
#include "metatile.h"
#include "story.h"
#include "vfx.h"

static void Ghost72_Init(struct VFX* p);
void Ghost72_Update(struct VFX* p);
void Ghost72_Die(struct VFX* p);

// clang-format off
const VFXRoutine gGhost72Routine = {
    [ENTITY_INIT] =      Ghost72_Init,
    [ENTITY_UPDATE] =    Ghost72_Update,
    [ENTITY_DIE] =       Ghost72_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

struct VFX* FUN_080c6880(struct Entity* e) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_072);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 0;
    (p->s).unk_28 = e;
  }
  return p;
}

void FUN_080c68cc(struct Entity* e, struct Coord* c) {
  s32 i;
  for (i = 0; i < 3; i++) {
    struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
    if (p != NULL) {
      (p->s).taskCol = 1;
      INIT_VFX_ROUTINE(p, VFX_UNK_072);
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

void FUN_080c6934(struct Entity* e, u8 n) {
  s32 i;
  for (i = 0; i < 2; i++) {
    struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
    if (p != NULL) {
      (p->s).taskCol = 1;
      INIT_VFX_ROUTINE(p, VFX_UNK_072);
      (p->s).tileNum = 0;
      (p->s).palID = 0;
      (p->s).work[0] = 2;
      (p->s).work[1] = i;
      (p->s).work[2] = n;
      (p->s).unk_28 = e;
    }
  }
}

// --------------------------------------------

void FUN_080c6a1c(struct VFX* p);
void FUN_080c6b78(struct VFX* p);
void FUN_080c6cd0(struct VFX* p);

static void Ghost72_Init(struct VFX* p) {
  static const VFXFunc sInitializers[3] = {
      FUN_080c6a1c,
      FUN_080c6b78,
      FUN_080c6cd0,
  };
  (sInitializers[(p->s).work[0]])(p);
}

// --------------------------------------------

void FUN_080c6ad8(struct VFX* p);
void FUN_080c6c60(struct VFX* p);
void FUN_080c6dc4(struct VFX* p);

void Ghost72_Update(struct VFX* p) {
  static const VFXFunc sUpdates[3] = {
      FUN_080c6ad8,
      FUN_080c6c60,
      FUN_080c6dc4,
  };
  if (IS_METTAUR) {
    (p->s).flags &= ~DISPLAY;
    (p->s).flags &= ~FLIPABLE;
    SET_VFX_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }
  (sUpdates[(p->s).work[0]])(p);
}

// --------------------------------------------

void Ghost72_Die(struct VFX* p) {
  (p->s).flags &= ~DISPLAY;
  SET_VFX_ROUTINE(p, ENTITY_EXIT);
}

// 0x080C6A1C
void FUN_080c6a1c(struct VFX* p0) {
  register struct VFX* p asm("r5");
  register struct Entity* q asm("r6");
  register struct Coord* qc asm("r8");
  register u32 xf asm("r4");
  s32 one;
  u32 k54;
  p = p0;
  q = (p->s).unk_28;
  k54 = 0x54;
  asm("" : "+r"(k54));
  qc = (struct Coord*)(k54 + (u32)q);
  {
    u8 fv;
    register u8 fl asm("r1");
    xf = q->flags;
    xf >>= 4;
    fv = 1;
    xf &= fv;
    fl = (p->s).flags;
    one = 0;
    asm("" : "+r"(one));
    asm volatile("" ::"r"(one));
    fv |= fl;
    (p->s).flags = fv;
  }
  InitNonAffineMotion(&p->s);
  SetMotion(&p->s, MOTION(0xDB, 0x0A));
  if (xf != 0) {
    (p->s).flags |= X_FLIP;
  } else {
    (p->s).flags &= 0xEF;
  }
  one = 1;
  {
    s32 v = one & xf;
    ((p->s).spr).xflip = v;
    {
      u8* oa = (u8*)p + 0x4a;
      s32 sh4 = v << 4;
      s32 ov = *oa;
      s32 m11 = -0x11;
      m11 &= ov;
      m11 |= sh4;
      *oa = m11;
    }
  }
  {
    struct Coord* qcl = qc;
    (p->s).coord.x = qcl->x;
    (p->s).coord.y = qcl->y;
  }
  (p->s).d.x = (q->d.x * 5 << 5) / 0x100;
  (p->s).d.y = q->d.y;
  (p->s).work[3] = (q->mode[3] == 1);
  (p->s).work[2] = 0x16;
  {
    u32 tbl = (u32)gVFXFnTable;
    u32 id = ((p->s).id) << 2;
    EntityFunc** rt = (EntityFunc**)(tbl + id);
    *(u32*)((p->s).mode) = one;
    (p->s).onUpdate = (void*)(*rt)[ENTITY_UPDATE];
  }
  Ghost72_Update(p);
}

// 0x080c6ad8
void FUN_080c6ad8(struct VFX* p) {
  (p->s).coord.x += (p->s).d.x;
  (p->s).d.x = ((p->s).d.x * 0xE6) / 0x100;
  if ((p->s).work[3] != 0) {
    s32 v = (p->s).d.y + 0x20;
    (p->s).d.y = v;
    if (v > 0x700) {
      (p->s).d.y = 0x700;
    }
  }
  UpdateMotionGraphic(&p->s);
  (p->s).work[2]--;
  if ((p->s).work[3] != 0) {
    if ((u16)FUN_080098a4((p->s).coord.x, (p->s).coord.y) != 0) {
      (p->s).work[2] = 0;
    }
  } else {
    s32 y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y);
    if ((p->s).coord.y > y) {
      (p->s).coord.y = y;
    }
  }
  if ((p->s).work[2] == 0) {
    struct Entity* e = (p->s).unk_28;
    struct Coord* c = &(p->s).coord;
    FUN_080c68cc(e, c);
    CreateSmoke(1, c);
    SET_VFX_ROUTINE(p, ENTITY_DIE);
  }
}

void Ghost72_Update(struct VFX* p);

// 0x080C6B78
void FUN_080c6b78(struct VFX* p) {
  register s32 xf asm("r4");
  register s32 w1 asm("r5");
  register s32 z6 asm("r6");
  register s32 one asm("r8");
  {
    register s32 t asm("r0");
    t = ((p->s).unk_28)->flags;
    xf = t >> 4;
    t = 1;
    xf &= t;
    w1 = (p->s).work[1];
    {
      register u8 fl asm("r1");
      fl = (p->s).flags;
      z6 = 0;
      asm volatile("" : "+r"(z6));
      asm volatile("" : "+r"(z6));
      t |= fl;
      (p->s).flags = t;
    }
  }
  InitNonAffineMotion(&p->s);
  {
    register s32 v asm("r2");
    asm volatile("add %0, %1, #0" : "=&l"(v) : "l"(xf));
    if (xf != 0) {
      register u8 g asm("r0");
      register s32 k asm("r1");
      g = (p->s).flags;
      k = 0x10;
      g |= k;
      (p->s).flags = g;
    } else {
      register u8 fl2 asm("r1");
      register u8 g2 asm("r0");
      fl2 = (p->s).flags;
      asm("" : "+r"(fl2));
      g2 = 0xEF;
      g2 &= fl2;
      (p->s).flags = g2;
    }
    {
      register s32 xv asm("r1");
      register u8* oa asm("r3");
      s32 sh4, ov, m11;
      one = 1;
      xv = one;
      xv &= v;
      *((u8*)p + 0x4c) = xv;
      oa = (u8*)p + 0x4a;
      sh4 = xv << 4;
      ov = *oa;
      m11 = -0x11;
      m11 &= ov;
      *oa = m11 | sh4;
    }
  }
  {
    register const u16* tb asm("r1");
    register u32 ix asm("r0");
    tb = (const u16*)0x0836F854;
    ix = w1 << 1;
    {
      register const u16* e asm("r0");
      asm volatile("add %0, %1, %2" : "=l"(e) : "l"(ix), "l"(tb));
      SetMotion(&p->s, *e);
    }
  }
  if (xf != 0) {
    register s32 two asm("r0");
    two = 2;
    w1 = two - w1;
  }
  {
    register s32 dx asm("r1");
    register u32* rng asm("r6");
    register u32 ka asm("r5");
    register u32 kc asm("r3");
    register u32 msk asm("r4");
    register u32 nx asm("r2");
    dx = (w1 - 1) << 8;
    rng = &RNG_0202f388;
    {
      register u32 t2 asm("r0");
      t2 = *rng;
      ka = 0x343FD;
      t2 *= ka;
      kc = 0x269EC3;
      t2 += kc;
      t2 <<= 1;
      nx = t2 >> 1;
      t2 >>= 0x11;
      msk = 0x1FF;
      t2 &= msk;
      dx += t2;
      {
        register s32 k1 asm("r0");
        k1 = -0x100;
        dx += k1;
      }
      (p->s).d.x = dx;
    }
    {
      register u32 t3 asm("r0");
      asm volatile("add %0, %1, #0" : "=&l"(t3) : "l"(nx));
      t3 *= ka;
      t3 += kc;
      t3 <<= 1;
      *rng = t3 >> 1;
      t3 >>= 0x11;
      t3 &= msk;
      {
        register s32 k2 asm("r1");
        k2 = -0x200;
        k2 -= t3;
        (p->s).d.y = k2;
      }
    }
  }
  asm volatile("" ::"r"(z6));
  {
    u32 tbl = (u32)gVFXFnTable;
    EntityFunc** rt = (EntityFunc**)(tbl + (((p->s).id) << 2));
    *(u32*)((p->s).mode) = one;
    (p->s).onUpdate = (void*)((*rt)[1]);
  }
  Ghost72_Update(p);
}

// 0x080c6c60
void FUN_080c6c60(struct VFX* p) {
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

INCASM("asm/vfx/unk_72_b.inc");

void FUN_080c6dc4(struct VFX* p) {
  (p->s).coord.x += (p->s).d.x;
  (p->s).coord.y += (p->s).d.y;
  (p->s).d.y += 0x40;
  UpdateMotionGraphic(&p->s);
  if (FUN_080098a4((p->s).coord.x, (p->s).coord.y)) {
    CreateSmoke(1, &(p->s).coord);
    if ((p->s).work[1] == 1) {
      PlaySound(0x2A);
    }
    SET_VFX_ROUTINE(p, ENTITY_DIE);
  }
}

// --------------------------------------------

const motion_t motion_t_ARRAY_0836f854[3] = {
    MOTION(SM219_SHELLCRAWLER, 0x0B),
    MOTION(SM219_SHELLCRAWLER, 0x0B),
    MOTION(SM219_SHELLCRAWLER, 0x0C),
};

const motion_t motion_t_ARRAY_0836f85a[2] = {
    MOTION(SM219_SHELLCRAWLER, 0x06),
    MOTION(SM219_SHELLCRAWLER, 0x07),
};
