#include "global.h"
#include "vfx.h"

static const VFXFunc sUpdates[9];

struct VFX* FUN_080c1b98(struct Coord* c, u8 mode) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_058);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = mode;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
  }
  return p;
}

struct VFX* FUN_080c1bec(struct Coord* c, u8 mode, struct Entity* e) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_058);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = mode;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
    (p->s).unk_28 = e;
  }
  return p;
}

struct VFX* FUN_080c1c44(struct Coord* c) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_058);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 4;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
  }
  return p;
}

struct Unk58Props { u8 unk_0[12]; u16 unk_c; u16 unk_e; };

struct VFX* FUN_080c1c94(struct Coord* c, u8 a1, u16 a2) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_058);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 6;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
    (p->s).work[1] = a1;
    ((struct Unk58Props*)(p->props).raw)->unk_c = a2;
  }
  return p;
}

struct VFX* FUN_080c1cf4(struct Coord* c, u8 a1, u16 a2, u16 a3) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_058);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = 7;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
    (p->s).work[1] = a1;
    ((struct Unk58Props*)(p->props).raw)->unk_e = a2;
    ((struct Unk58Props*)(p->props).raw)->unk_c = a3;
  }
  return p;
}

INCASM("asm/vfx/unk_58_pre_pre_p4_post.inc");

void VFX58_Update(struct VFX* vfx) {
  (sUpdates[(vfx->s).mode[1]])(vfx);
}


void VFX58_Die(struct VFX* vfx) {
  (vfx->s).flags &= ~DISPLAY;
  SET_VFX_ROUTINE(vfx, ENTITY_EXIT);
}

void FUN_080c2124(struct VFX* vfx) {
  (vfx->s).work[2]--;
  if ((vfx->s).work[2] == 0) {
    (vfx->s).work[2] = 8, (vfx->s).mode[1] = 1, (vfx->s).mode[2] = 0;
    return;
  }

  switch ((vfx->s).mode[2]) {
    case 0: {
      SetMotion(&vfx->s, MOTION(SM010_OMEGA_RING, 8));
      (vfx->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1: {
      UpdateMotionGraphic(&vfx->s);
      break;
    }
  }
}

void FUN_080c216c(struct Entity* p) {
  if (--p->work[2] == 0) {
    SET_VFX_ROUTINE(p, ENTITY_DIE);
  } else {
    switch (p->mode[2]) {
      case 0:
        SetMotion(p, 0xA09);
        p->mode[2]++;
        FALLTHROUGH;
      case 1:
        UpdateMotionGraphic(p);
        break;
    }
  }
}

INCASM("asm/vfx/unk_58_post_p1.inc");

// 0x080c2294: follow the parent entity, flickering every other frame;
// hidden while the parent is invincible/painted white
void FUN_080c2294(struct VFX* p) {
  if ((p->s).unk_28->mode[0] > 1 || --(p->s).work[2] == 0) {
    SET_VFX_ROUTINE(p, ENTITY_DIE);
  } else {
    struct Entity* parent;
    switch ((p->s).mode[2]) {
      case 0:
        SetMotion(&p->s, 0xB01);
        (p->s).work[3] = 0;
        (p->s).mode[2]++;
        FALLTHROUGH;
      case 1: {
        u8 t;
        struct CollidableEntity* ce;
        parent = (p->s).unk_28;
        (p->s).coord.x = (parent->coord).x + (p->props.tmp.c).x;
        (p->s).coord.y = (parent->coord).y + (p->props.tmp.c).y;
        t = (p->s).work[3]++ & 1;
        ce = (struct CollidableEntity*)parent;
        if (t) {
          (p->s).flags |= DISPLAY;
        } else {
          (p->s).flags &= ~DISPLAY;
        }
        if ((ce->body).invincibleTime != 0 ||
            (gWhitePaintFlags[(ce->s).invincibleID >> 5] & (1 << ((ce->s).invincibleID & 0x1F))) ||
            ((ce->body).status & BODY_STATUS_WHITE)) {
          (p->s).flags &= ~DISPLAY;
        }
        UpdateMotionGraphic(&p->s);
        break;
      }
    }
  }
}

void FUN_080c2364(struct VFX* p) {
  if (--(p->s).work[2] == 0) {
    SET_VFX_ROUTINE(p, ENTITY_DIE);
  }
}

INCASM("asm/vfx/unk_58_post_p2_a.inc");

#include "motion.h"

void FUN_080c248c(struct VFX* p) {
  switch ((p->s).mode[2]) {
    case 0:
      SetMotion(&p->s, *(motion_t*)&(p->props).raw[12]);
      (p->s).work[2] = 0x28;
      (p->s).mode[2]++;
      // fallthrough
    case 1:
      UpdateMotionGraphic(&p->s);
      if ((p->s).work[2] & 1) {
        (p->s).flags |= DISPLAY;
      } else {
        (p->s).flags &= ~DISPLAY;
      }
      if ((p->s).work[2] != 0 && --(p->s).work[2] == 0) {
        SET_VFX_ROUTINE(p, ENTITY_DIE);
      }
      break;
  }
}

extern const s32* const PTR_s32_ARRAY_0836f2f0[3];

// 0x080c2500
void FUN_080c2500(struct VFX* p) {
  switch ((p->s).mode[2]) {
    case 0: {
      const s32* const* tbl = PTR_s32_ARRAY_0836f2f0;
      u16* mp = &p->props.unk25.unk_80;
      u16 idx = *mp % 3;
      const s32* base = tbl[idx];
      {
        const s32* e = base + (p->s).work[1] * 2;
        RNG_0202f388 = LCG(RNG_0202f388);
        (p->s).d.y = e[1] - ((RNG_0202f388 >> 16) & 0x1F);
      }
      {
        s32 x = base[(p->s).work[1] * 2] - 0x20;
        RNG_0202f388 = LCG(RNG_0202f388);
        (p->s).d.x = x + ((RNG_0202f388 >> 16) & 0x3F);
      }
      SetMotion(&p->s, *mp);
      (p->s).work[2] = 0x50;
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
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

// 0x080c25f4
void FUN_080c25f4(struct VFX* p) {
  switch ((p->s).mode[2]) {
    case 0: {
      const s32* const* tbl = PTR_s32_ARRAY_0836f2f0;
      u16* mp = &p->props.unk25.unk_80;
      u16 idx = *mp % 3;
      const s32* base = tbl[idx];
      {
        const s32* e = base + (p->s).work[1] * 2;
        RNG_0202f388 = LCG(RNG_0202f388);
        (p->s).d.y = e[1] - ((RNG_0202f388 >> 16) & 0x1F);
      }
      {
        s32 x = base[(p->s).work[1] * 2] - 0x20;
        RNG_0202f388 = LCG(RNG_0202f388);
        (p->s).d.x = x + ((RNG_0202f388 >> 16) & 0x3F);
      }
      SetMotion(&p->s, *mp);
      (p->s).work[2] = 0x50;
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
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

void VFX58_Init(struct VFX* vfx);
void VFX58_Update(struct VFX* vfx);
void VFX58_Die(struct VFX* vfx);

// clang-format off
const VFXRoutine gVFX58Routine = {
    [ENTITY_INIT] =      VFX58_Init,
    [ENTITY_UPDATE] =    VFX58_Update,
    [ENTITY_DIE] =       VFX58_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

void FUN_080c2124(struct VFX* vfx);
void FUN_080c216c(struct Entity* p);
void FUN_080c21c0(struct VFX* vfx);
void FUN_080c2294(struct VFX* vfx);
void FUN_080c2364(struct VFX* vfx);
void FUN_080c2390(struct VFX* vfx);
void FUN_080c248c(struct VFX* vfx);
void FUN_080c2500(struct VFX* vfx);
void FUN_080c25f4(struct VFX* vfx);

// clang-format off
static const VFXFunc sUpdates[9] = {
    FUN_080c2124,
    (VFXFunc)FUN_080c216c,
    FUN_080c21c0,
    FUN_080c2294,
    FUN_080c2364,
    FUN_080c2390,
    FUN_080c248c,
    FUN_080c2500,
    FUN_080c25f4,
};
// clang-format on

static const s32 s32_ARRAY_0836f290[8 * 3] = {
    0x000002C0, -0x00000300, -0x00000220, -0x00000260, -0x00000220, -0x00000300, 0x000002C0, -0x00000260, -0x00000100, -0x000001F0, -0x00000200, -0x00000280, 0x00000160, -0x000001F0, 0x00000260, -0x00000280, -0x000000B0, -0x00000340, 0x00000120, -0x000002A0, 0x00000120, -0x00000340, -0x000000B0, -0x000002A0,
};

const s32* const PTR_s32_ARRAY_0836f2f0[3] = {
    &s32_ARRAY_0836f290[0],
    &s32_ARRAY_0836f290[8],
    &s32_ARRAY_0836f290[16],
};
