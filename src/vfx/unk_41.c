#include "global.h"
#include "vfx.h"
#include "script.h"

// ヘルバットシルトのレーザーに関係?

extern const VFXFunc PTR_ARRAY_0836eef8[4];

struct VFX* FUN_080bdd74(struct Entity* e, struct Coord* c, u8 mode) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_041);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = mode;
    (p->s).work[1] = 0;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
    (p->s).unk_28 = e;
  }
  return p;
}

struct Unk41Props {
  u16 unk_0;
  u8 pad[2];
  s32 unk_4;
  u8 unk_8;
  u8 unk_9[7];
};

struct VFX* FUN_080bddcc(struct Coord* c, u8 a1, u16 a2, s32 a3) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_041);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = a1;
    (p->s).work[1] = 1;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
    ((struct Unk41Props*)(p->props).raw)->unk_0 = a2;
    ((struct Unk41Props*)(p->props).raw)->unk_4 = a3;
  }
  return p;
}

struct VFX* createHellbatElectricBeam(struct Entity* e, struct Coord* c, u8 a2, u8 a3) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_041);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = a2;
    ((struct Unk41Props*)(p->props).raw)->unk_8 = a3;
    (p->s).work[1] = 2;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
    (p->s).unk_28 = e;
  }
  return p;
}

struct VFX* FUN_080bde9c(struct Entity* e, struct Coord* c, u8 a2, u8 a3) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_041);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = a2;
    ((struct Unk41Props*)(p->props).raw)->unk_8 = a3;
    (p->s).work[1] = 3;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
    (p->s).unk_28 = e;
  }
  return p;
}

void VFX41_Update(struct VFX* vfx);

void VFX41_Init(struct VFX* p) {
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
  VFX41_Update(p);
}

void VFX41_Update(struct VFX* vfx) {
  (PTR_ARRAY_0836eef8[(vfx->s).mode[1]])(vfx);
}

void VFX41_Die(struct VFX* vfx) {
  (vfx->s).flags &= ~DISPLAY;
  SET_VFX_ROUTINE(vfx, ENTITY_EXIT);
}

static const s32* const PTR_ARRAY_0836ef68[3];

void FUN_080be020(struct VFX* p) {
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
        const s32* const* tbl = PTR_ARRAY_0836ef68;
        u16* mp = &((struct Unk41Props*)(p->props).raw)->unk_0;
        u32 base = (u32)tbl[*mp % 3];
        const s32* pair = (const s32*)(((struct Unk41Props*)(p->props).raw)->unk_4 * 8 + base);
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

// 0x080BE154
void FUN_080be154(struct VFX* p) {
  register s32 m asm("r5");
  m = (p->s).mode[2];
  switch (m) {
    case 0: {
      register struct Entity* q asm("r1");
      register s32 dx asm("r0");
      register s32 k asm("r2");
      SetMotion(&p->s, MOTION(0xA8, 0x0D));
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

// 0x080be230
void FUN_080be230(struct VFX* p) {
  if (*((u8*)p + 0x7c) == 0) {
    struct Entity* q = (p->s).unk_28;
    if (q->mode[0] > 1) {
      goto die;
    }
    if ((u8)(q->mode[1] - 0xA) <= 1) {
      goto die;
    }
    switch ((p->s).mode[2]) {
      case 0:
        SetMotion(&p->s, MOTION(0xA9, 0x01));
        SET_YFLIP(p, 1);
        (p->s).mode[2]++;
        /* fallthrough */
      case 1: {
        struct Entity* q2 = (p->s).unk_28;
        (p->s).coord.x = (q2->coord).x - 0x100;
        (p->s).coord.y = (q2->coord).y + 0x2E00;
        UpdateMotionGraphic(&p->s);
        if (((p->s).unk_28)->mode[2] > 9) {
          SET_VFX_ROUTINE(p, ENTITY_DIE);
        }
        break;
      }
    }
  }
  if (*((u8*)p + 0x7c) == 1) {
    switch ((p->s).mode[2]) {
      case 0:
        (p->s).work[2] = 1;
        (p->s).coord.y = FUN_08009f6c((p->s).coord.x, (p->s).coord.y);
        SetMotion(&p->s, MOTION(0xA9, 0x04));
        (p->s).mode[2]++;
        /* fallthrough */
      case 1:
        UpdateMotionGraphic(&p->s);
        if ((u8)--(p->s).work[2] == 0) {
        die:
          SET_VFX_ROUTINE(p, ENTITY_DIE);
        }
        break;
    }
  }
}

static const motion_t motion_t_ARRAY_0836ef74[3];
static const motion_t motion_t_ARRAY_0836ef7a[3];

// 0x080BE330
void FUN_080be330(struct VFX* p) {
  switch ((p->s).mode[2]) {
    case 0: {
      u8 w0 = (p->s).work[0];
      if (w0 == 0) {
        SetMotion(&p->s, MOTION(0xA9, 0x07));
      } else if (w0 == 1) {
        SetMotion(&p->s, MOTION(0xA9, 0x07));
      } else if (w0 == 2) {
        SetMotion(&p->s, MOTION(0xA9, 0x07));
      } else if (w0 == 3) {
        SetMotion(&p->s, MOTION(0xA9, 0x07));
      } else if (w0 == 4) {
        SetMotion(&p->s, MOTION(0xA9, 0x0B));
      } else if (w0 == 5) {
        SetMotion(&p->s, MOTION(0xA9, 0x0B));
      }
      {
        u8 t = *((u8*)p + 0x7c);
        bool8 xf2 = 1;
        xf2 &= t;
        asm volatile("" ::"r"(t));
        if (xf2) {
          (p->s).flags |= X_FLIP;
        } else {
          (p->s).flags &= ~X_FLIP;
        }
        ((p->s).spr).xflip = xf2 & 1;
        ((p->s).spr).oam.xflip = xf2;
      }
      (p->s).work[3] = 3;
      (p->s).work[2] = 0xA;
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1:
      if ((p->s).work[2] != 0) {
        (p->s).work[2]--;
        if ((u8)(p->s).work[2] != 0) {
          goto draw;
        }
      }
      (p->s).work[2] = 0xA;
      if ((p->s).work[3] != 0) {
        (p->s).work[3]--;
        if ((u8)(p->s).work[3] != 0) {
          goto sel;
        }
      }
      SET_VFX_ROUTINE(p, ENTITY_DIE);
      goto draw;
    sel:
      if ((p->s).work[0] <= 3) {
        SetMotion(&p->s, motion_t_ARRAY_0836ef74[(p->s).work[3] - 1]);
      } else {
        SetMotion(&p->s, motion_t_ARRAY_0836ef7a[(p->s).work[3] - 1]);
      }
    draw:
      UpdateMotionGraphic(&p->s);
      break;
  }
}

INCASM("asm/vfx/unk_41_post_b2.inc");

void VFX41_Init(struct VFX* vfx);
void VFX41_Update(struct VFX* vfx);
void VFX41_Die(struct VFX* vfx);

// clang-format off
const VFXRoutine gVFX41Routine = {
    [ENTITY_INIT] =      VFX41_Init,
    [ENTITY_UPDATE] =    VFX41_Update,
    [ENTITY_DIE] =       VFX41_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

void FUN_080be020(struct VFX* vfx);
void FUN_080be154(struct VFX* vfx);
void FUN_080be230(struct VFX* vfx);
void FUN_080be330(struct VFX* vfx);

const VFXFunc PTR_ARRAY_0836eef8[4] = {
    FUN_080be020,
    FUN_080be154,
    FUN_080be230,
    FUN_080be330,
};

static const s32 s32_ARRAY_ARRAY_0836ef08[8 * 3] = {
    0x00000120, -0x00000200, -0x000000B0, -0x00000160, -0x000000B0, -0x00000200, 0x00000120, -0x00000160, -0x000000B0, -0x00000160, -0x000000B0, -0x00000200, 0x00000120, -0x00000160, 0x00000120, -0x00000200, -0x000000B0, -0x00000200, 0x00000120, -0x00000160, 0x00000120, -0x00000200, -0x000000B0, -0x00000160,
};

static const s32* const PTR_ARRAY_0836ef68[3] = {
    &s32_ARRAY_ARRAY_0836ef08[0],
    &s32_ARRAY_ARRAY_0836ef08[8],
    &s32_ARRAY_ARRAY_0836ef08[16],
};

static const motion_t motion_t_ARRAY_0836ef74[3] = {
    MOTION(DM169_HELLBAT_LASER, 9),
    MOTION(DM169_HELLBAT_LASER, 8),
    MOTION(DM169_HELLBAT_LASER, 7),
};

static const motion_t motion_t_ARRAY_0836ef7a[3] = {
    MOTION(DM169_HELLBAT_LASER, 13),
    MOTION(DM169_HELLBAT_LASER, 12),
    MOTION(DM169_HELLBAT_LASER, 11),
};
