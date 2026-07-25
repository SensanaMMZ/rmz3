#include "entity.h"
#include "global.h"
#include "constants/song.h"
#include "sound.h"
#include "motion.h"
#include "definition.h"
#include "story.h"
#include "vfx.h"

struct VFX28 {
  struct Entity s;
  // props (16bytes, offset: 0x74..)
  u16 unk_0;
  u16 unk_2;
  s32 unk_4;
  u8 unk_8[8];
};
static_assert(sizeof(struct VFX28) == sizeof(struct VFX));

static void Ghost28_Init(struct VFX* p);
static void Ghost28_Update(struct VFX* p);
static void Ghost28_Die(struct VFX* p);

// clang-format off
const VFXRoutine gGhost28Routine = {
    [ENTITY_INIT] =      (VFXFunc)Ghost28_Init,
    [ENTITY_UPDATE] =    (VFXFunc)Ghost28_Update,
    [ENTITY_DIE] =       (VFXFunc)Ghost28_Die,
    [ENTITY_DISAPPEAR] = (VFXFunc)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

struct Entity* FUN_080b9e68(struct Coord* c, u8 n) {
  struct Entity* p = AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    p->taskCol = 1;
    INIT_VFX_ROUTINE(p, 28);
    p->tileNum = 0, p->palID = 0;
    p->work[0] = n, p->work[1] = 0;
    (p->coord).x = c->x;
    (p->coord).y = c->y;
  }
  return p;
}

struct Entity* FUN_080b9ebc(struct Coord* c, u8 n, u16 r2, s32 y) {
  struct VFX28* p = (struct VFX28*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, 28);
    (p->s).tileNum = 0, (p->s).palID = 0;
    (p->s).work[0] = n, (p->s).work[1] = 1;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
    p->unk_0 = r2;
    p->unk_4 = y;
  }
  return (void*)p;
}

static void Ghost28_Init(struct VFX* p) {
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
  Ghost28_Update(p);
}

// --------------------------------------------

static void nop_080ba078(void* _ UNUSED);
void FUN_080ba07c(struct VFX* p);
void FUN_080ba16c(struct VFX* p);

static void Ghost28_Update(struct VFX* p) {
  static const VFXFunc sUpdates[] = {
      (VFXFunc)nop_080ba078,
      (VFXFunc)FUN_080ba07c,
      (VFXFunc)FUN_080ba16c,
  };
  if (IS_METTAUR) {
    SET_VFX_ROUTINE(p, ENTITY_DIE);
    Ghost28_Die(p);
    return;
  }
  (sUpdates[(p->s).mode[1]])(p);
}

static void Ghost28_Die(struct VFX* p) {
  (p->s).flags &= ~DISPLAY;
  SET_VFX_ROUTINE(p, ENTITY_EXIT);
}

static void nop_080ba078(void* _ UNUSED) { return; }

void FUN_080ba07c(struct VFX* v) {
  struct Coord c;
  u32 n;

  if (--(v->s).work[2] == 0) {
    CreateSmoke(2, &(v->s).coord);
    RNG_0202f388 = LCG(RNG_0202f388);
    n = (RNG_0202f388 >> 16) & 3;
    c.x = (v->s).coord.x;
    c.y = (v->s).coord.y;
    FUN_080b9ebc(&c, (v->s).work[0], 0x190C, n);
    FUN_080b9ebc(&c, (v->s).work[0], 0x190D, n);
    FUN_080b9ebc(&c, (v->s).work[0], 0x190E, n);
    PlaySound(SE_ZAKO_EXPLODE);
    SET_VFX_ROUTINE(v, ENTITY_DIE);
  } else {
    switch ((v->s).mode[2]) {
      case 0:
        (v->s).work[2] = 0x1e;
        (v->s).d.y = -0x200;
        SetMotion(&v->s, MOTION(0x19, 0x0b));
        (v->s).mode[2]++;
        // fallthrough
      case 1:
        (v->s).d.y += 0x20;
        if ((v->s).d.y > 0x700) {
          (v->s).d.y = 0x700;
        }
        (v->s).coord.y += (v->s).d.y;
        (v->s).coord.x += (v->s).d.x;
        UpdateMotionGraphic(&v->s);
        break;
    }
  }
}

static const s32* const PTR_ARRAY_0836ebac[3];

void FUN_080ba16c(struct VFX* p) {
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
        const s32* const* tbl = PTR_ARRAY_0836ebac;
        u16* mp = &((struct VFX28*)p)->unk_0;
        u32 base = (u32)tbl[*mp % 3];
        const s32* pair = (const s32*)(((struct VFX28*)p)->unk_4 * 8 + base);
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

static const s32 s32_ARRAY_ARRAY_0836eb4c[3][8] = {
    {0x00000120, -0x00000260, -0x000000B0, -0x000001A0, -0x000000B0, -0x00000260, 0x00000120, -0x000001A0},
    {-0x000000B0, -0x000001A0, -0x000000B0, -0x00000260, 0x00000120, -0x000001A0, 0x00000120, -0x00000260},
    {-0x000000B0, -0x00000260, 0x00000120, -0x000001A0, 0x00000120, -0x00000260, -0x000000B0, -0x000001A0},
};

// 0x0836EBAC
static const s32* const PTR_ARRAY_0836ebac[3] = {
    s32_ARRAY_ARRAY_0836eb4c[0],
    s32_ARRAY_ARRAY_0836eb4c[1],
    s32_ARRAY_ARRAY_0836eb4c[2],
};
