#include "entity.h"
#include "global.h"
#include "story.h"
#include "vfx.h"

void Ghost20_Init(struct VFX* p);
void Ghost20_Update(struct VFX* p);
void Ghost20_Die(struct VFX* p);

// clang-format off
const VFXRoutine gGhost20Routine = {
    [ENTITY_INIT] =      Ghost20_Init,
    [ENTITY_UPDATE] =    Ghost20_Update,
    [ENTITY_DIE] =       Ghost20_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

struct VFX* CreateGhost20(struct Coord* c, u8 n) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_020);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = n;
    (p->s).work[1] = 0;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
  }
  return p;
}

extern const VFXFunc sGhost20Updates[3];

struct Unk20Props {
  u16 unk_0;
  u8 pad[2];
  s32 unk_4;
  u8 unk_8[8];
};

struct VFX* FUN_080b721c(struct Coord* c, u8 a1, u16 a2, s32 a3) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, VFX_UNK_020);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = a1;
    (p->s).work[1] = 1;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
    ((struct Unk20Props*)(p->props).raw)->unk_0 = a2;
    ((struct Unk20Props*)(p->props).raw)->unk_4 = a3;
  }
  return p;
}

void Ghost20_Init(struct VFX* p) {
  InitNonAffineMotion(&p->s);
  (p->s).flags |= DISPLAY;
  (p->s).flags |= FLIPABLE;
  if ((p->s).work[0] == 0) {
    SET_XFLIP(p, FALSE);
    (p->s).d.x = -PIXEL(3) / 4;
  } else {
    SET_XFLIP(p, TRUE);
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
  Ghost20_Update(p);
}

void Ghost20_Update(struct VFX* p) {
  if (IS_METTAUR) {
    SET_VFX_ROUTINE(p, ENTITY_DIE);
    Ghost20_Die(p);
  } else {
    (sGhost20Updates[(p->s).mode[1]])(p);
  }
}


void Ghost20_Die(struct VFX* p) {
  (p->s).flags &= ~DISPLAY;
  SET_VFX_ROUTINE(p, ENTITY_EXIT);
}


void FUN_080b73d0(struct VFX* p) {}

void FUN_080b73d4(struct VFX* p) {
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
    FUN_080b721c(&c, (p->s).work[0], 0x409, r);
    FUN_080b721c(&c, (p->s).work[0], 0x40A, r);
    FUN_080b721c(&c, (p->s).work[0], 0x40B, r);
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
      FUN_080b721c(&c2, (p->s).work[0], 0x409, r);
      FUN_080b721c(&c2, (p->s).work[0], 0x40A, r);
      FUN_080b721c(&c2, (p->s).work[0], 0x40B, r);
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
          SetMotion(&p->s, 0x407);
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

extern const s32* const PTR_s32_ARRAY_0836e938[3];

void FUN_080b754c(struct VFX* p) {
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
        const s32* const* tbl = PTR_s32_ARRAY_0836e938;
        u16* mp = &((struct Unk20Props*)(p->props).raw)->unk_0;
        u32 base = (u32)tbl[*mp % 3];
        const s32* pair =
            (const s32*)(((struct Unk20Props*)(p->props).raw)->unk_4 * 8 + base);
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

// --------------------------------------------

void FUN_080b73d0(struct VFX* p);
void FUN_080b73d4(struct VFX* p);
void FUN_080b754c(struct VFX* p);

const VFXFunc sGhost20Updates[3] = {
    FUN_080b73d0,
    FUN_080b73d4,
    FUN_080b754c,
};

const s32 s32_ARRAY_0836e8d8[8 * 3] = {
    0x00000120, -0x00000200, -0x000000B0, -0x00000160, -0x000000B0, -0x00000200, 0x00000120, -0x00000160, -0x000000B0, -0x00000160, -0x000000B0, -0x00000200, 0x00000120, -0x00000160, 0x00000120, -0x00000200, -0x000000B0, -0x00000200, 0x00000120, -0x00000160, 0x00000120, -0x00000200, -0x000000B0, -0x00000160,
};

const s32* const PTR_s32_ARRAY_0836e938[3] = {
    &s32_ARRAY_0836e8d8[0],
    &s32_ARRAY_0836e8d8[8],
    &s32_ARRAY_0836e8d8[16],
};
