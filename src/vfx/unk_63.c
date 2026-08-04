#include "global.h"
#include "story.h"
#include "vfx.h"

static const VFXFunc sUpdates[1];
void VFX63_Update(struct VFX* vfx);
void VFX63_Die(struct VFX* p);
extern u32 RNG_0202f388;

struct Unk63Props {
  u16 unk_0;
  u8 pad[2];
  s32 unk_4;
  u8 unk_8[8];
};

struct VFX* CreateVFX63(struct Coord* c, u8 a1, u16 a2, s32 a3) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_063);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = a1;
    (p->s).work[1] = 0;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
    ((struct Unk63Props*)(p->props).raw)->unk_0 = a2;
    ((struct Unk63Props*)(p->props).raw)->unk_4 = a3;
  }
  return p;
}

void VFX63_Init(struct VFX* p) {
  InitNonAffineMotion(&p->s);
  (p->s).flags |= DISPLAY;
  (p->s).flags |= FLIPABLE;
  if ((p->s).work[0] == 0) {
    SET_XFLIP(p, FALSE);
  } else {
    SET_XFLIP(p, TRUE);
  }
  if ((p->s).work[0] == 0) {
    (p->s).d.x = -0xc0;
  } else {
    (p->s).d.x = 0xc0;
  }
  (p->s).d.y = 0;
  if ((p->s).work[1] == 0) {
    RNG_0202f388 = LCG(RNG_0202f388);
    (p->s).work[2] = ((RNG_0202f388 >> 16) & 7) + 0x7f;
    SET_VFX_ROUTINE(p, ENTITY_UPDATE);
    (p->s).mode[1] = 0;
    (p->s).mode[2] = 0;
    (p->s).mode[3] = 0;
  }
  VFX63_Update(p);
}

void VFX63_Update(struct VFX* vfx) {
  if (IS_METTAUR) {
    SET_VFX_ROUTINE(vfx, ENTITY_DIE);
    VFX63_Die(vfx);
  } else {
    (sUpdates[(vfx->s).mode[1]])(vfx);
  }
}


void VFX63_Die(struct VFX* vfx) {
  (vfx->s).flags &= ~DISPLAY;
  SET_VFX_ROUTINE(vfx, ENTITY_EXIT);
}

// 0x080C3864
void FUN_080c3864(struct VFX* p) {
  register s32 md asm("r9");
  register struct Coord* cp asm("r1");
  register s32 sk asm("r0");
  {
    s32 t = (p->s).work[2] - 1;
    (p->s).work[2] = t;
    if ((u8)t == 0) {
      cp = &(p->s).coord;
      sk = 2;
      goto smoke;
    }
  }
  {
    register u32 at asm("r1");
    at = (u16)FUN_080098a4((p->s).coord.x, (p->s).coord.y);
    if (at == 0) {
      goto normal;
    }
    {
      register s32 k asm("r0");
      k = 0x80 * 256;
      k &= at;
      if (k != 0) {
        goto normal;
      }
    }
    if ((p->s).d.y <= 0) {
      goto normal;
    }
  }
  cp = &(p->s).coord;
  sk = 3;
smoke:
  ((struct Entity * (*)(s32, struct Coord*)) CreateSmoke)(sk, cp);
  SET_VFX_ROUTINE(p, ENTITY_DIE);
  return;
normal:
  md = (p->s).mode[2];
  switch (md) {
    case 0: {
      register const s32** tb asm("r4");
      register u16* mp asm("r8");
      register u32 mul asm("r6");
      register u32 add asm("r5");
      register u32 s1 asm("r4");
      register u32* rp2 asm("r3");
      register const s32* q asm("r2");
      tb = (const s32**)0x0836F538;
      asm("" : "+r"(tb));
      {
        register u16* mtmp asm("r1");
        register u32 i asm("r0");
        asm volatile("mov %0, #0x74\n\tadd %0, %0, %1" : "=&l"(mtmp) : "l"(p));
        mp = mtmp;
        i = (u16)*mtmp % 3;
        i <<= 16;
        i >>= 14;
        i += (u32)tb;
        {
          register const s32* qb asm("r0");
          register s32 off asm("r2");
          qb = *(const s32**)i;
          off = *(s32*)((u8*)p + 0x78);
          off <<= 3;
          q = (const s32*)(off + (u32)qb);
        }
      }
      {
        register u32 r0v asm("r0");
        register u32 r1v asm("r1");
        register u32* rp asm("r3");
        rp = &RNG_0202f388;
        asm("" : "+r"(rp));
        rp2 = rp;
        r0v = *rp;
        mul = 0x343FD;
        asm volatile("add %0, %1, #0" : "=&l"(r1v) : "l"(r0v));
        r1v *= mul;
        add = 0x269EC3;
        r1v += add;
        r1v <<= 1;
        asm("" : "+r"(r1v));
        s1 = r1v >> 1;
        *rp = s1;
        r1v >>= 0x11;
        r0v = 0x1F;
        r1v &= r0v;
        (p->s).d.y = q[1] + r1v;
      }
      {
        register u32 r1w asm("r1");
        register u32 r0w asm("r0");
        asm volatile("add %0, %1, #0" : "=&l"(r1w) : "l"(s1));
        r1w *= mul;
        r1w += add;
        r1w <<= 1;
        asm("" : "+r"(r1w));
        *rp2 = r1w >> 1;
        r1w >>= 0x11;
        r0w = 0x3F;
        r1w &= r0w;
        (p->s).d.x = q[0] - r1w;
      }
      ((void (*)(struct Entity*, u32))SetMotion)(&p->s, *mp);
      {
        register s32 mv asm("r1");
        mv = md;
        (p->s).work[3] = mv;
      }
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1: {
      register s32 w asm("r0");
      register s32 one asm("r1");
      w = (p->s).work[3] + 1;
      (p->s).work[3] = w;
      one = 0xFF;
      w &= one;
      one = 1;
      w &= one;
      if (w != 0) {
        register u8 f asm("r0");
        f = (p->s).flags;
        f |= one;
        (p->s).flags = f;
      } else {
        register u8 h asm("r1");
        register u8 g asm("r0");
        h = (p->s).flags;
        asm("" : "+r"(h));
        g = 0xFE;
        g &= h;
        (p->s).flags = g;
      }
      (p->s).d.y += 0x20;
      if ((p->s).d.y > 0xE0 * 8) {
        (p->s).d.y = 0xE0 * 8;
      }
      (p->s).coord.y += (p->s).d.y;
      (p->s).coord.x += (p->s).d.x;
      UpdateMotionGraphic(&p->s);
      break;
    }
  }
}


void VFX63_Init(struct VFX* vfx);
void VFX63_Update(struct VFX* vfx);
void VFX63_Die(struct VFX* vfx);

// clang-format off
const VFXRoutine gVFX63Routine = {
    [ENTITY_INIT] =      VFX63_Init,
    [ENTITY_UPDATE] =    VFX63_Update,
    [ENTITY_DIE] =       VFX63_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

void FUN_080c3864(struct VFX* vfx);

static const VFXFunc sUpdates[1] = {
    FUN_080c3864,
};

static const s32 s32_ARRAY_0836f4d8[8 * 3] = {
    0x00000120, -0x00000260, -0x000000B0, -0x000001A0, -0x000000B0, -0x00000260, 0x00000120, -0x000001A0, -0x000000B0, -0x000001A0, -0x000000B0, -0x00000260, 0x00000120, -0x000001A0, 0x00000120, -0x00000260, -0x000000B0, -0x00000260, 0x00000120, -0x000001A0, 0x00000120, -0x00000260, -0x000000B0, -0x000001A0,
};

static const s32* const PTR_s32_ARRAY_0836f538[3] = {
    &s32_ARRAY_0836f4d8[0],
    &s32_ARRAY_0836f4d8[8],
    &s32_ARRAY_0836f4d8[16],
};
