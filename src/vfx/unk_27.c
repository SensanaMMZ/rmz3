#include "entity.h"
#include "global.h"
#include "story.h"
#include "vfx.h"

static void Ghost27_Init(struct VFX* p);
static void Ghost27_Update(struct VFX* p);
static void Ghost27_Die(struct VFX* p);

// clang-format off
const VFXRoutine gGhost27Routine = {
    [ENTITY_INIT] =      Ghost27_Init,
    [ENTITY_UPDATE] =    Ghost27_Update,
    [ENTITY_DIE] =       Ghost27_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

void CreateGhost27(struct Coord* c, u8 r1, u8 r2) {
  struct VFX* g = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (g != NULL) {
    (g->s).taskCol = 1;
    INIT_VFX_ROUTINE(g, VFX_UNK_027);
    (g->s).tileNum = 0;
    (g->s).palID = 0;
    (g->s).coord = *c;
    SET_XFLIP(g, r1);
    (g->s).work[0] = r2;
  }
}

// --------------------------------------------

void FUN_080b9b9c(struct VFX* p);
void FUN_080b9c08(struct VFX* p);

static void Ghost27_Init(struct VFX* p) {
  static const VFXFunc sInitializers[] = {
      FUN_080b9b9c,
      FUN_080b9c08,
  };
  (sInitializers[(p->s).work[0]])(p);
}

// --------------------------------------------

void FUN_080b9c50(struct VFX* p);
void FUN_080b9ca4(struct VFX* p);

static void Ghost27_Update(struct VFX* p) {
  static const VFXFunc sUpdates[] = {
      FUN_080b9c50,
      FUN_080b9ca4,
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

void FUN_080b9cf8(struct VFX* p);
void FUN_080b9db0(struct VFX* p);

static void Ghost27_Die(struct VFX* p) {
  static const VFXFunc sDeinitializers[] = {
      FUN_080b9cf8,
      FUN_080b9db0,
  };
  if (IS_METTAUR) {
    (p->s).flags &= ~DISPLAY;
    (p->s).flags &= ~FLIPABLE;
    SET_VFX_ROUTINE(p, ENTITY_DISAPPEAR);
    return;
  }
  (sDeinitializers[(p->s).work[0]])(p);
}

void FUN_080b9b9c(struct VFX* p) {
  InitNonAffineMotion(&p->s);
  (p->s).flags |= DISPLAY;
  (p->s).flags |= FLIPABLE;
  SetMotion(&p->s, 0x1701);
  if ((p->s).flags & (1 << 4)) {
    (p->s).d.x = 0x40;
    (p->s).unk_coord.x = -2;
  } else {
    (p->s).d.x = -0x40;
    (p->s).unk_coord.x = 2;
  }
  (p->s).d.y = 0x40;
  (p->s).unk_coord.y = -2;
  (p->s).work[2] = 0x20;
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
  Ghost27_Update(p);
}

void FUN_080b9c08(struct VFX* p) {
  InitNonAffineMotion(&p->s);
  (p->s).flags |= DISPLAY;
  (p->s).flags |= FLIPABLE;
  SetMotion(&p->s, 0x1708);
  (p->s).d.y = 0;
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
  Ghost27_Update(p);
}

void FUN_080b9c50(struct VFX* p) {
  UpdateMotionGraphic(&p->s);
  (p->s).d.x += (p->s).unk_coord.x;
  (p->s).d.y += (p->s).unk_coord.y;
  (p->s).coord.x += (p->s).d.x;
  (p->s).coord.y += (p->s).d.y;
  (p->s).work[2]--;
  if ((p->s).work[2] == 0xff) {
    SET_VFX_ROUTINE(p, ENTITY_DIE);
    Ghost27_Die(p);
  }
}

void FUN_080b9ca4(struct VFX* p) {
  UpdateMotionGraphic(&p->s);
  (p->s).d.y += 0x40;
  if ((p->s).d.y > 0x700) {
    (p->s).d.y = 0x700;
  }
  (p->s).coord.y += (p->s).d.y;
  if (FUN_080098a4((p->s).coord.x, (p->s).coord.y + 0xa00)) {
    SET_VFX_ROUTINE(p, ENTITY_DIE);
    Ghost27_Die(p);
  }
}

INCASM("asm/vfx/unk_27_p2_p2.inc");
