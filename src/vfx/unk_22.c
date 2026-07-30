#include "entity.h"
#include "global.h"
#include "story.h"
#include "vfx.h"

static const VFXFunc sUpdates[];
void Ghost22_Die(struct VFX* p);

struct VFX* FUN_080b7b38(struct Coord* c, u8 mode) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_022);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = mode;
    (p->s).work[1] = 0;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
  }
  return p;
}

struct Unk22Props {
  u16 unk_0;
  u8 pad[2];
  s32 unk_4;
  u8 unk_8[8];
};

struct VFX* FUN_080b7b8c(struct Coord* c, u8 a1, u16 a2, s32 a3) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_022);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = a1;
    (p->s).work[1] = 1;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
    ((struct Unk22Props*)(p->props).raw)->unk_0 = a2;
    ((struct Unk22Props*)(p->props).raw)->unk_4 = a3;
  }
  return p;
}

void Ghost22_Update(struct VFX* p);

void Ghost22_Init(struct VFX* p) {
  InitNonAffineMotion(&p->s);
  (p->s).flags |= DISPLAY;
  (p->s).flags |= FLIPABLE;
  if ((p->s).work[0] == 0) {
    SET_XFLIP(p, FALSE);
  } else {
    SET_XFLIP(p, TRUE);
  }
  if ((p->s).work[0] == 0) {
    (p->s).d.x = -PIXEL(1) / 2;
  } else {
    (p->s).d.x = PIXEL(1) / 2;
  }
  (p->s).d.y = 0;

  if ((p->s).work[1] == 0) {
    (p->s).work[2] = 0xFF;
    SET_VFX_ROUTINE(p, ENTITY_UPDATE);
    (p->s).mode[1] = 1, (p->s).mode[2] = 0, (p->s).mode[3] = 0;
  } else {
    RNG_0202f388 = LCG(RNG_0202f388);
    (p->s).work[2] = 127 + ((RNG_0202f388 >> 16) & 7);
    SET_VFX_ROUTINE(p, ENTITY_UPDATE);
    (p->s).mode[1] = 2, (p->s).mode[2] = 0, (p->s).mode[3] = 0;
  }
  Ghost22_Update(p);
}

void Ghost22_Update(struct VFX* p) {
  if (IS_METTAUR) {
    SET_VFX_ROUTINE(p, ENTITY_DIE);
    Ghost22_Die(p);
  } else {
    (sUpdates[(p->s).mode[1]])(p);
  }
}


void Ghost22_Die(struct VFX* p) {
  (p->s).flags &= ~DISPLAY;
  SET_VFX_ROUTINE(p, ENTITY_EXIT);
}


void nop_080b7d48(struct VFX* p) {}

INCASM("asm/vfx/unk_22_p2.inc");

extern const s32* const PTR_ARRAY_0836ea50[3];

void FUN_080b7e3c(struct VFX* p) {
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
        const s32* const* t4 = PTR_ARRAY_0836ea50;
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
          register u32 three asm("r1");
          u32 md;
          three = 3;
          asm("" : "+r"(three));
          md = mv0 % three;
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


static const VFXFunc sUpdates[3];

void Ghost22_Init(struct VFX* p);
void Ghost22_Update(struct VFX* p);
void Ghost22_Die(struct VFX* p);

// clang-format off
const VFXRoutine gGhost22Routine = {
    [ENTITY_INIT] =      Ghost22_Init,
    [ENTITY_UPDATE] =    Ghost22_Update,
    [ENTITY_DIE] =       Ghost22_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

void nop_080b7d48(struct VFX* p);
void FUN_080b7d4c(struct VFX* p);
void FUN_080b7e3c(struct VFX* p);

static const VFXFunc sUpdates[3] = {
    nop_080b7d48,
    FUN_080b7d4c,
    FUN_080b7e3c,
};

const s32 s32_ARRAY_0836e9f0[24] = {
    0x00000120,  -0x00000200, -0x000000B0, -0x00000160, -0x000000B0, -0x00000200, 0x00000120,  -0x00000160,  // 0
    -0x000000B0, -0x00000160, -0x000000B0, -0x00000200, 0x00000120,  -0x00000160, 0x00000120,  -0x00000200,  // 1
    -0x000000B0, -0x00000200, 0x00000120,  -0x00000160, 0x00000120,  -0x00000200, -0x000000B0, -0x00000160,  // 2
};

const s32* const PTR_ARRAY_0836ea50[3] = {
    &s32_ARRAY_0836e9f0[0],
    &s32_ARRAY_0836e9f0[8],
    &s32_ARRAY_0836e9f0[16],
};
