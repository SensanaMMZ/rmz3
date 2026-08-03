#include "global.h"
#include "vfx.h"
#include "script.h"

// トレテスタ・ケルベリアン関連
// - トレテスタ・ケルベリアンが死んだ際のパーティクル
// - コンテナが壊れる時のパーティクル

struct VFX46 {
  struct Entity s;
  // props (16bytes, offset: 0x74..)
  motion_t unk_74;  // 0xAD01 とか
  u32 unk_78;
  u8 unk_7c;
  u32 pad_80;
};
static_assert(sizeof(struct VFX46) == sizeof(struct VFX));

void VFX46_Init(struct VFX* vfx);
void VFX46_Update(struct VFX* vfx);
void VFX46_Die(struct VFX* vfx);

// clang-format off
const VFXRoutine gVFX46Routine = {
    [ENTITY_INIT] =      VFX46_Init,
    [ENTITY_UPDATE] =    VFX46_Update,
    [ENTITY_DIE] =       VFX46_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

// 0x080bec34
struct Entity* FUN_080bec34(struct Entity* e, struct Coord* c, u8 kind) {
  struct Entity* p = AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    p->taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_046);
    p->tileNum = 0;
    p->palID = 0;
    p->work[0] = kind;
    p->work[1] = 0;
    p->coord.x = c->x;
    p->coord.y = c->y;
    p->unk_28 = (void*)e;
  }
  return p;
}

// 0x080bec8c
struct Entity* FUN_080bec8c(struct Coord* c, u8 kind, motion_t m, u32 n) {
  struct VFX46* p = (struct VFX46*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_046);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = kind;
    (p->s).work[1] = 1;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
    p->unk_74 = m;
    p->unk_78 = n;
  }
  return (void*)p;
}

// 0x080becf8
struct Entity* FUN_080becf8(struct Coord* c, u8 kind, motion_t m, u32 n) {
  struct VFX46* p = (struct VFX46*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_046);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = kind;
    (p->s).work[1] = 2;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
    p->unk_74 = m;
    p->unk_78 = n;
  }
  return (void*)p;
}

// 0x080bed5c
struct Entity* FUN_080bed5c(struct Entity* e, struct Coord* c, u8 kind, u8 param_4) {
  struct VFX46* p = (struct VFX46*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_046);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = kind;
    p->unk_7c = param_4;
    (p->s).work[1] = 2;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
    (p->s).unk_28 = (void*)e;
  }
  return (void*)p;
}

static const VFXFunc sUpdates[4];

struct Entity* FUN_080bedc0(struct Entity* e, struct Coord* c, u8 kind, u8 param_4) {
  struct VFX46* p = (struct VFX46*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_046);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = kind;
    p->unk_7c = param_4;
    (p->s).work[1] = 3;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
    (p->s).unk_28 = (void*)e;
  }
  return (void*)p;
}

void VFX46_Init(struct VFX* p) {
  InitNonAffineMotion(&p->s);
  (p->s).flags |= DISPLAY;
  (p->s).flags |= FLIPABLE;
  ResetDynamicMotion(&p->s);
  if ((p->s).work[0] == 0) {
    SET_XFLIP(p, FALSE);
    (p->s).d.x = PIXEL(1) / 2;
  } else {
    SET_XFLIP(p, TRUE);
    (p->s).d.x = -PIXEL(1) / 2;
  }
  (p->s).d.y = 0;

  if ((p->s).work[1] == 0) {
    (p->s).work[2] = 0xFF;
    SET_VFX_ROUTINE(p, ENTITY_UPDATE);
    (p->s).mode[1] = 1, (p->s).mode[2] = 0, (p->s).mode[3] = 0;
  } else if ((p->s).work[1] == 1) {
    (p->s).work[2] = 0xFF;
    SET_VFX_ROUTINE(p, ENTITY_UPDATE);
    (p->s).mode[1] = 0, (p->s).mode[2] = 0, (p->s).mode[3] = 0;
  } else if ((p->s).work[1] == 2) {
    (p->s).work[2] = 0xFF;
    SET_VFX_ROUTINE(p, ENTITY_UPDATE);
    (p->s).mode[1] = 2, (p->s).mode[2] = 0, (p->s).mode[3] = 0;
  } else if ((p->s).work[1] == 3) {
    (p->s).work[2] = 0xFF;
    SET_VFX_ROUTINE(p, ENTITY_UPDATE);
    (p->s).mode[1] = 3, (p->s).mode[2] = 0, (p->s).mode[3] = 0;
  }
  VFX46_Update(p);
}

void VFX46_Update(struct VFX* vfx) {
  (sUpdates[(vfx->s).mode[1]])(vfx);
}

void VFX46_Die(struct VFX* vfx) {
  (vfx->s).flags &= ~DISPLAY;
  SET_VFX_ROUTINE(vfx, ENTITY_EXIT);
}

INCASM("asm/vfx/unk_46_post.inc");

// 0x080BF0A0
void FUN_080bf0a0(struct VFX* p) {
  register s32 m asm("r5");
  m = (p->s).mode[2];
  switch (m) {
    case 0: {
      register struct Entity* q asm("r1");
      register s32 dx asm("r0");
      register s32 k asm("r2");
      SetMotion(&p->s, MOTION(0xAB, 0x27));
      (p->s).work[2] = 0x1E;
      if ((p->s).d.x > 0) {
        q = (p->s).unk_28;
        dx = (q->coord).x;
        k = 0xC00;
      } else {
        q = (p->s).unk_28;
        dx = (q->coord).x;
        k = -0xC00;
      }
      dx += k;
      (p->s).unk_coord.x = dx;
      (p->s).d.y = 0x80;
      (p->s).unk_coord.y = (q->coord).y + 0x600;
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1: {
      {
        register s32 t asm("r0");
        register s32 cx asm("r1");
        t = (p->s).unk_coord.x;
        cx = (p->s).coord.x;
        t -= cx;
        t <<= 4;
        t >>= 8;
        cx += t;
        (p->s).coord.x = cx;
      }
      {
        register s32 t2 asm("r0");
        register s32 cy asm("r1");
        t2 = (p->s).unk_coord.y;
        cy = (p->s).coord.y;
        t2 -= cy;
        t2 <<= 4;
        t2 >>= 8;
        cy += t2;
        (p->s).coord.y = cy;
      }
      UpdateMotionGraphic(&p->s);
      if (((p->s).unk_28)->flags & 1) {
        (p->s).flags |= 1;
      } else {
        (p->s).flags &= 0xFE;
      }
      break;
    }
    case 2:
      if (((p->s).unk_28)->scriptEntity->flags & 0x80) {
        CreateSmoke(1, &(p->s).coord);
        PlaySound(0x2A);
        {
          u32 tbl = (u32)gVFXFnTable;
          u32 id = ((p->s).id) << 2;
          EntityFunc** rt = (EntityFunc**)(tbl + id);
          *(u32*)((p->s).mode) = m;
          (p->s).onUpdate = (void*)((*rt)[2]);
        }
      }
      break;
  }
}

static const s32* const PTR_ARRAY_0836f0cc[5];

void FUN_080bf17c(struct VFX* p) {
  s32 t = (p->s).work[2] - 1;
  (p->s).work[2] = t;
  if ((t << 24) != 0) {
    u32 at = FUN_080098a4((p->s).coord.x, (p->s).coord.y);
    if (at == 0) {
      goto sw;
    }
    if (at & 0x8000) {
      goto sw;
    }
    if ((p->s).d.y <= 0) {
      goto sw;
    }
  }
  CreateSmoke(2, &(p->s).coord);
  {
    u32 tbl = (u32)gVFXFnTable;
    u32 id = ((p->s).id) << 2;
    EntityFunc** rt = (EntityFunc**)(tbl + id);
    *(u32*)((p->s).mode) = 2;
    (p->s).onUpdate = (void*)((*rt)[2]);
  }
  return;
sw:
  {
    s32 m2 = (p->s).mode[2];
    switch (m2) {
      case 0: {
        const s32* const* tb = PTR_ARRAY_0836f0cc;
        u16* mp = &((struct VFX46*)p)->unk_74;
        u32 sel = *mp % 5;
        const s32* arr = tb[(u16)sel];
        const s32* ent = (const s32*)((((struct VFX46*)p)->unk_78 << 3) + (u32)arr);
        s32 ny, cx;
        ny = ent[1] - (RANDOM(RNG_0202f388) % 0xC0);
        (p->s).d.y = ny;
        cx = ent[0] - 0x80;
        cx += RANDOM(RNG_0202f388) & 0xFF;
        (p->s).d.y = ((ny * 3) << 6) >> 8;
        (p->s).d.x = ((cx * 3) << 6) >> 8;
        SetMotion(&p->s, *mp);
        (p->s).work[2] = 0x5A;
        (p->s).work[3] = m2;
        (p->s).unk_coord.x = (RANDOM(RNG_0202f388) & 7) + 0x1E;
        (p->s).mode[2]++;
      }
        // fallthrough
      case 1: {
        s32 t3 = (p->s).work[3] + 1;
        (p->s).work[3] = t3;
        {
          u32 w3 = (p->s).work[3];
          if ((s32)w3 > (p->s).unk_coord.x) {
            if (w3 & 1) {
              (p->s).flags |= DISPLAY;
            } else {
              (p->s).flags &= ~DISPLAY;
            }
          }
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

// 0x080BF2F0
void FUN_080bf2f0(struct VFX* p) {
  switch ((p->s).mode[2]) {
    case 0: {
      u32 f = 1 & *(u8*)((u8*)p + 0x7c);
      if (f != 0) {
        (p->s).flags |= 0x10;
      } else {
        (p->s).flags &= 0xEF;
      }
      {
        register u32 xf asm("r1");
        register u8* oa asm("ip");
        u32 sh4;
        s32 ov;
        s32 m11;
        asm volatile("add %0, %1, #0" : "=&l"(xf) : "l"(f));
        ((p->s).spr).xflip = xf;
        oa = (u8*)p + 0x4a;
        sh4 = xf << 4;
        ov = *oa;
        m11 = -0x11;
        m11 &= ov;
        m11 |= sh4;
        *oa = m11;
      }
      (p->s).work[3] = 3;
      (p->s).work[2] = 0xA;
      (p->s).mode[2]++;
    }
    case 1:
      if ((p->s).work[2] != 0) {
        if ((u8)--(p->s).work[2] != 0) {
          goto draw;
        }
      }
      (p->s).work[2] = 0xA;
      if ((p->s).work[3] != 0) {
        if ((u8)--(p->s).work[3] != 0) {
          goto draw;
        }
      }
      SET_VFX_ROUTINE(p, 2);
    draw:
      UpdateMotionGraphic(&p->s);
      break;
  }
}

void FUN_080bef44(struct VFX* vfx);
void FUN_080bf0a0(struct VFX* vfx);
void FUN_080bf17c(struct VFX* vfx);
void FUN_080bf2f0(struct VFX* vfx);

static const VFXFunc sUpdates[4] = {
    FUN_080bef44,
    FUN_080bf0a0,
    FUN_080bf17c,
    FUN_080bf2f0,
};

// clang-format off
static const s32 s32_ARRAY_ARRAY_0836f02c[5][8] = {
    {0x00000120, -0x00000400, -0x000000B0, -0x00000360, -0x000000B0, -0x00000400, 0x00000120, -0x00000260},
    {-0x000000B0, -0x00000260, -0x000000B0, -0x00000400, 0x00000120, -0x00000260, 0x00000120, -0x00000400},
    {-0x000000B0, -0x00000400, 0x00000120, -0x00000360, 0x00000120, -0x00000400, -0x000000B0, -0x00000360},
    {0x00000160, -0x00000260, -0x000000C0, -0x00000400, 0x00000160, -0x00000400, -0x000000C0, -0x00000260},
    {-0x000000E0, -0x00000400, 0x00000180, -0x00000360, -0x000000E0, -0x00000360, 0x00000180, -0x00000400},
};
// clang-format on

static const s32* const PTR_ARRAY_0836f0cc[5] = {
    s32_ARRAY_ARRAY_0836f02c[0], s32_ARRAY_ARRAY_0836f02c[1], s32_ARRAY_ARRAY_0836f02c[2], s32_ARRAY_ARRAY_0836f02c[3], s32_ARRAY_ARRAY_0836f02c[4],
};
