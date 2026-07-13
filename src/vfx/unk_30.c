#include "global.h"
#include "script.h"
#include "vfx.h"

static void Ghost30_Init(struct VFX* p);
static void Ghost30_Update(struct VFX* p);
static void Ghost30_Die(struct VFX* p);

// clang-format off
const VFXRoutine gGhost30Routine = {
    [ENTITY_INIT] =      Ghost30_Init,
    [ENTITY_UPDATE] =    Ghost30_Update,
    [ENTITY_DIE] =       Ghost30_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

struct VFX* CreateGhost30(struct Entity* e, struct Coord* c, u8 n, u32 m) {
  struct VFX* p = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (p != NULL) {
    (p->s).taskCol = 1;
    INIT_VFX_ROUTINE(p, 30);
    (p->s).tileNum = 0;
    (p->s).palID = 0;
    (p->s).work[0] = n;
    (p->s).work[1] = m;
    (p->s).coord.x = c->x;
    (p->s).coord.y = c->y;
    (p->s).unk_28 = e;
  }
  return p;
}

// Cyberelf ghost/afterimage. Flip the sprite by spawn direction (work[0]) via
// SET_XFLIP, set horizontal speed d.x = +/-0x80 to match, arm the lifetime
// timer (work[2]=0xff), and route to Update. Retail RELOADS work[0] for the d.x
// direction, keeping the SET_XFLIP branch and the d.x branch separate; agbcc
// from clean C proves work[0] unchanged across SET_XFLIP's writes and MERGES
// the two work[0]==0 tests (11 instr shorter) — a no-alias CSE clean C can't
// suppress. INCCODE for the byte-match; MODERN keeps the readable decode.
static void Ghost30_Init(struct VFX* p) {
  InitNonAffineMotion(&p->s);
  (p->s).flags |= DISPLAY;
  (p->s).flags |= FLIPABLE;
  ResetDynamicMotion(&p->s);
  if ((p->s).work[0] == 0) {
    SET_XFLIP(p, FALSE);
  } else {
    SET_XFLIP(p, TRUE);
  }
  if ((p->s).work[0] == 0) {
    (p->s).d.x = PIXEL(1) / 2;
  } else {
    (p->s).d.x = -PIXEL(1) / 2;
  }
  (p->s).d.y = 0;
  (p->s).work[2] = 0xFF;
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
  (p->s).mode[1] = 1, (p->s).mode[2] = 0, (p->s).mode[3] = 0;
  Ghost30_Update(p);
}

// --------------------------------------------

static void nop_080ba444(struct VFX* p);
static void FUN_080ba448(struct VFX* p);

static void Ghost30_Update(struct VFX* p) {
  static const VFXFunc sUpdates[2] = {
      nop_080ba444,
      FUN_080ba448,
  };
  (sUpdates[(p->s).mode[1]])(p);
}

static void Ghost30_Die(struct VFX* p) {
  (p->s).flags &= ~DISPLAY;
  SET_VFX_ROUTINE(p, ENTITY_EXIT);
}

static void nop_080ba444(struct VFX* p) { return; }

static void FUN_080ba448(struct VFX* p) {
  switch ((p->s).mode[2]) {
    case 0: {
      if ((p->s).work[1] == 1) {
        SetMotion(&p->s, MOTION(DM162_BLAZIN, 5));
      } else {
        SetMotion(&p->s, MOTION(DM162_BLAZIN, 26));
      }
      (p->s).work[2] = 60;
      if ((p->s).d.x > 0) {
        (p->s).unk_coord.x = (((p->s).unk_28)->coord).x + PIXEL(12);
      } else {
        (p->s).unk_coord.x = (((p->s).unk_28)->coord).x - PIXEL(12);
      }
      (p->s).d.y = 0x80;
      (p->s).unk_coord.y = (((p->s).unk_28)->coord).y + PIXEL(6);
      (p->s).mode[2]++;
      FALLTHROUGH;
    }
    case 1: {
      (p->s).coord.x += (((p->s).unk_coord.x - (p->s).coord.x) << 4) >> 8;
      (p->s).coord.y += (((p->s).unk_coord.y - (p->s).coord.y) << 4) >> 8;
      UpdateMotionGraphic(&p->s);
      if (((p->s).unk_28)->flags & DISPLAY) {
        (p->s).flags |= DISPLAY;
      } else {
        (p->s).flags &= ~DISPLAY;
      }
      break;
    }
    case 2: {
      if ((((p->s).unk_28)->scriptEntity)->flags & (1 << 7)) {
        CreateSmoke(1, &(p->s).coord);
        PlaySound(SE_ZAKO_EXPLODE);
        SET_VFX_ROUTINE(p, ENTITY_DIE);
      }
      break;
    }
  }
}
