#include "global.h"
#include "story.h"
#include "vfx.h"

static const VFXFunc sUpdates[3];
void VFX61_Update(struct VFX* vfx);
void VFX61_Die(struct VFX* p);

struct VFX* FUN_080c2e7c(struct Coord* c, u8 mode) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_061);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = mode;
    (p->s).work[1] = 0;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
  }
  return p;
}

struct Unk61Props {
  u16 unk_0;
  u8 pad[2];
  s32 unk_4;
  u8 unk_8[8];
};

struct VFX* FUN_080c2ed0(struct Coord* c, u8 a1, u16 a2, s32 a3) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_061);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = a1;
    (p->s).work[1] = 1;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
    ((struct Unk61Props*)(p->props).raw)->unk_0 = a2;
    ((struct Unk61Props*)(p->props).raw)->unk_4 = a3;
  }
  return p;
}


struct VFX* FUN_080c2f3c(struct Coord* c, u8 mode) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_061);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = mode;
    (p->s).work[1] = 2;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
  }
  return p;
}

void VFX61_Init(struct VFX* vfx) {
  s32 f;
  s32 z5;
  InitNonAffineMotion(&vfx->s);
  {
    register u8 f0 asm("r1");
    register s32 d asm("r0");
    register s32 z asm("r3");
    register s32 ft asm("r2");
    f0 = (vfx->s).flags;
    d = DISPLAY;
    z = 0;
    asm("" : "+r"(z));
    ft = d | f0;
    ft |= FLIPABLE;
    ft |= z;
    (vfx->s).flags = ft;
    f = ft;
  }
  {
    u8 xf = (vfx->s).work[0];
    if (xf == 0) {
      f &= 0xEF;
      (vfx->s).flags = f;
      asm volatile("" : "+r"(f));
      ((vfx->s).spr).xflip = xf;
      ((vfx->s).spr).oam.xflip = xf;
    } else {
      register s32 one1 asm("r1");
      one1 = 1;
      asm("" : "+r"(one1));
      f |= X_FLIP;
      (vfx->s).flags = f;
      asm volatile("" : "+r"(f));
      ((vfx->s).spr).xflip = one1;
      {
        u8* a = (u8*)&((vfx->s).spr).oam + 6;
        register s32 m asm("r2");
        s32 msk;
        u8 b;
        m = 0x10;
        asm("" : "+r"(m));
        b = *a;
        msk = -0x11;
        msk &= b;
        msk |= m;
        *a = msk;
      }
    }
  }
  if ((vfx->s).work[0] == 0) {
    (vfx->s).d.x = -0xC0;
  } else {
    (vfx->s).d.x = 0xC0;
  }
  z5 = 0;
  (vfx->s).d.y = z5;
  {
    register s32 k asm("r3");
    k = (vfx->s).work[1];
    if (k == 0) {
      (vfx->s).work[2] = 0xFF;
      SET_VFX_ROUTINE(vfx, ENTITY_UPDATE);
      (vfx->s).mode[1] = 1;
    } else if (k == 1) {
      (vfx->s).work[2] = (RANDOM(RNG_0202f388) & 7) + 0x7F;
      {
        u32 tb = (u32)gVFXFnTable;
        const VFXRoutine** ta = (const VFXRoutine**)(tb + (vfx->s).id * 4);
        *(u32*)&(vfx->s).mode[0] = k;
        (vfx->s).onUpdate = (void*)(**ta)[ENTITY_UPDATE];
      }
      (vfx->s).mode[1] = 2;
    } else {
      (vfx->s).work[2] = 0xFF;
      SET_VFX_ROUTINE(vfx, ENTITY_UPDATE);
      (vfx->s).mode[1] = z5;
    }
  }
  (vfx->s).mode[2] = z5;
  (vfx->s).mode[3] = z5;
  VFX61_Update(vfx);
}

void VFX61_Update(struct VFX* vfx) {
  if (IS_METTAUR) {
    SET_VFX_ROUTINE(vfx, ENTITY_DIE);
    VFX61_Die(vfx);
  } else {
    (sUpdates[(vfx->s).mode[1]])(vfx);
  }
}


void VFX61_Die(struct VFX* vfx) {
  (vfx->s).flags &= ~DISPLAY;
  SET_VFX_ROUTINE(vfx, ENTITY_EXIT);
}

INCASM("asm/vfx/unk_61_post.inc");

static const s32* const PTR_s32_ARRAY_0836f490[3];

void FUN_080c338c(struct VFX* p) {
  u16 attr;
  (p->s).work[2]--;
  if ((p->s).work[2] == 0 ||
      ((attr = FUN_080098a4((p->s).coord.x, (p->s).coord.y)) != 0 &&
       !(attr & 0x8000) && (p->s).d.y > 0)) {
    CreateSmoke(2, &(p->s).coord);
    SET_VFX_ROUTINE(p, ENTITY_DIE);
  } else {
    switch ((p->s).mode[2]) {
      case 0: {
        const s32* const* tbl = PTR_s32_ARRAY_0836f490;
        u16* mp = &((struct Unk61Props*)(p->props).raw)->unk_0;
        u32 base = (u32)tbl[*mp % 3];
        const s32* pair = (const s32*)(((struct Unk61Props*)(p->props).raw)->unk_4 * 8 + base);
        (p->s).d.y = pair[1] + (RANDOM(RNG_0202f388) & 0x1F);
        (p->s).d.x = pair[0] - (RANDOM(RNG_0202f388) & 0x3F);
        SetMotion(&p->s, *mp);
        (p->s).work[3] = 0;
        (p->s).mode[2]++;
        FALLTHROUGH;
      }
      case 1: {
        if ((u8)++(p->s).work[3] & 1) {
          (p->s).flags |= DISPLAY;
        } else {
          (p->s).flags &= ~DISPLAY;
        }
        (p->s).d.y += 0x20;
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

void VFX61_Init(struct VFX* vfx);
void VFX61_Update(struct VFX* vfx);
void VFX61_Die(struct VFX* vfx);

// clang-format off
const VFXRoutine gVFX61Routine = {
    [ENTITY_INIT] =      VFX61_Init,
    [ENTITY_UPDATE] =    VFX61_Update,
    [ENTITY_DIE] =       VFX61_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

void FUN_080c3108(struct VFX* vfx);
void FUN_080c3214(struct VFX* vfx);
void FUN_080c338c(struct VFX* vfx);

static const VFXFunc sUpdates[3] = {
    FUN_080c3108,
    FUN_080c3214,
    FUN_080c338c,
};

static const s32 s32_ARRAY_0836f430[8 * 3] = {
    0x00000120, -0x00000260, -0x000000B0, -0x000001A0, -0x000000B0, -0x00000260, 0x00000120, -0x000001A0, -0x000000B0, -0x000001A0, -0x000000B0, -0x00000260, 0x00000120, -0x000001A0, 0x00000120, -0x00000260, -0x000000B0, -0x00000260, 0x00000120, -0x000001A0, 0x00000120, -0x00000260, -0x000000B0, -0x000001A0,
};

static const s32* const PTR_s32_ARRAY_0836f490[3] = {
    &s32_ARRAY_0836f430[0],
    &s32_ARRAY_0836f430[8],
    &s32_ARRAY_0836f430[16],
};
