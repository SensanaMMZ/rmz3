#include "global.h"
#include "story.h"
#include "vfx.h"

static const VFXFunc sUpdates[3];
void VFX59_Die(struct VFX* p);

struct VFX* FUN_080c26e8(struct Coord* c, u8 mode) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_059);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = mode;
    (p->s).work[1] = 0;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
  }
  return p;
}

struct Unk59Props {
  u16 unk_0;
  u8 pad[2];
  s32 unk_4;
  u8 unk_8[8];
};

struct VFX* FUN_080c273c(struct Coord* c, u8 a1, u16 a2, s32 a3) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_059);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = a1;
    (p->s).work[1] = 1;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
    ((struct Unk59Props*)(p->props).raw)->unk_0 = a2;
    ((struct Unk59Props*)(p->props).raw)->unk_4 = a3;
  }
  return p;
}

void VFX59_Update(struct VFX* vfx);

void VFX59_Init(struct VFX* p) {
  InitNonAffineMotion(&p->s);
  (p->s).flags |= DISPLAY;
  (p->s).flags |= FLIPABLE;
  if ((p->s).work[0] == 0) {
    SET_XFLIP(p, FALSE);
  } else {
    SET_XFLIP(p, TRUE);
  }
  if ((p->s).work[0] == 0) {
    (p->s).d.x = -PIXEL(3) / 4;
  } else {
    (p->s).d.x = PIXEL(3) / 4;
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
  VFX59_Update(p);
}

void VFX59_Update(struct VFX* vfx) {
  if (IS_METTAUR) {
    SET_VFX_ROUTINE(vfx, ENTITY_DIE);
    VFX59_Die(vfx);
  } else {
    (sUpdates[(vfx->s).mode[1]])(vfx);
  }
}


void VFX59_Die(struct VFX* vfx) {
  (vfx->s).flags &= ~DISPLAY;
  SET_VFX_ROUTINE(vfx, ENTITY_EXIT);
}


void nop_080c28fc(struct VFX* vfx) {}

void FUN_080c2900(struct VFX* p) {
  s32 t = (p->s).work[2] - 1;
  (p->s).work[2] = t;
  if ((t << 24) == 0) {
    struct Coord c;
    u32 r;
    CreateSmoke(2, &(p->s).coord);
    PlaySound(0x2A);
    r = RANDOM(RNG_0202f388) & 3;
    c.x = (p->s).coord.x;
    c.y = (p->s).coord.y;
    FUN_080c273c(&c, (p->s).work[0], 0x6908, r);
    FUN_080c273c(&c, (p->s).work[0], 0x6909, r);
    FUN_080c273c(&c, (p->s).work[0], 0x690A, r);
    {
      u32 tbl = (u32)gVFXFnTable;
      u32 id = ((p->s).id) << 2;
      EntityFunc** rt = (EntityFunc**)(tbl + id);
      *(u32*)((p->s).mode) = 2;
      (p->s).onUpdate = (void*)((*rt)[2]);
    }
  } else {
    u32 at = FUN_080098a4((p->s).coord.x, (p->s).coord.y);
    if (at != 0 && !(at & 0x8000)) {
      struct Coord c2;
      u32 r;
      CreateSmoke(2, &(p->s).coord);
      PlaySound(0x2A);
      r = RANDOM(RNG_0202f388) & 3;
      c2.x = (p->s).coord.x;
      c2.y = (p->s).coord.y;
      FUN_080c273c(&c2, (p->s).work[0], 0x6908, r);
      FUN_080c273c(&c2, (p->s).work[0], 0x6909, r);
      FUN_080c273c(&c2, (p->s).work[0], 0x690A, r);
      {
        u32 tbl = (u32)gVFXFnTable;
        u32 id = ((p->s).id) << 2;
        EntityFunc** rt = (EntityFunc**)(tbl + id);
        *(u32*)((p->s).mode) = 2;
        (p->s).onUpdate = (void*)((*rt)[2]);
      }
    } else {
      switch ((p->s).mode[2]) {
        case 0:
          (p->s).work[2] = 0x3C;
          (p->s).d.y = -0x100;
          SetMotion(&p->s, 0x6907);
          (p->s).mode[2]++;
          // fallthrough
        case 1:
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

extern const s32* const PTR_s32_ARRAY_0836f37c[3];

void FUN_080c2a78(struct VFX* p) {
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
        const s32* const* tbl = PTR_s32_ARRAY_0836f37c;
        u16* mp = &((struct Unk59Props*)(p->props).raw)->unk_0;
        u32 base = (u32)tbl[*mp % 3];
        const s32* pair = (const s32*)(((struct Unk59Props*)(p->props).raw)->unk_4 * 8 + base);
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

void VFX59_Init(struct VFX* vfx);
void VFX59_Update(struct VFX* vfx);
void VFX59_Die(struct VFX* vfx);

// clang-format off
const VFXRoutine gVFX59Routine = {
    [ENTITY_INIT] =      VFX59_Init,
    [ENTITY_UPDATE] =    VFX59_Update,
    [ENTITY_DIE] =       VFX59_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

// --------------------------------------------

void nop_080c28fc(struct VFX* vfx);
void FUN_080c2900(struct VFX* vfx);
void FUN_080c2a78(struct VFX* vfx);

static const VFXFunc sUpdates[3] = {
    nop_080c28fc,
    FUN_080c2900,
    FUN_080c2a78,
};

static const s32 s32_ARRAY_0836f31c[8 * 3] = {
    0x00000120, -0x00000260, -0x000000B0, -0x000001A0, -0x000000B0, -0x00000260, 0x00000120, -0x000001A0, -0x000000B0, -0x000001A0, -0x000000B0, -0x00000260, 0x00000120, -0x000001A0, 0x00000120, -0x00000260, -0x000000B0, -0x00000260, 0x00000120, -0x000001A0, 0x00000120, -0x00000260, -0x000000B0, -0x000001A0,
};

const s32* const PTR_s32_ARRAY_0836f37c[3] = {
    &s32_ARRAY_0836f31c[0],
    &s32_ARRAY_0836f31c[8],
    &s32_ARRAY_0836f31c[16],
};
