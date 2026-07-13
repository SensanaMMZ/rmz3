#include "gfx.h"
#include "global.h"
#include "renderer.h"
#include "trig.h"
#include "vfx.h"

// Z x (残機数) の表示

static void TaskCB_080be5d0(struct Sprite* s, struct DrawPivot* c);

static void ExlifeIndicator_Init(struct Entity* p);
static void ExlifeIndicator_Update(struct VFX* vfx);
static void ExlifeIndicator_Die(struct Entity* p);

// clang-format off
const VFXRoutine gExlifeIndicatorRoutine = {
    [ENTITY_INIT] =      (VFXFunc)ExlifeIndicator_Init,
    [ENTITY_UPDATE] =    (VFXFunc)ExlifeIndicator_Update,
    [ENTITY_DIE] =       (VFXFunc)ExlifeIndicator_Die,
    [ENTITY_DISAPPEAR] = (VFXFunc)DeleteVFX,
    [ENTITY_EXIT] =      (VFXFunc)DeleteEntity,
};
// clang-format on

struct VFX* CreateExlifeIndicator(u8 extraLife) {
  struct VFX* vfx = (struct VFX*)AllocEntityFirst(gVFXHeaderPtr);
  if (vfx != NULL) {
    (vfx->s).taskCol = 1;
    INIT_VFX_ROUTINE(vfx, VFX_EXLIFE_INDICATOR);
    (vfx->s).tileNum = 0;
    (vfx->s).palID = 0;
    (vfx->s).work[0] = extraLife;
  }
  return vfx;
}

static void ExlifeIndicator_Init(struct Entity* p) {
  SetTaskCallback((struct RenderNode*)&p->spr, TaskCB_080be5d0);
  (p->spr).sprites = (struct MetaspriteHeader*)p;
  p->flags &= ~OAM_PRIO;
  p->flags |= DISPLAY;
  LOAD_STATIC_GRAPHIC(SM060_EXLIFE_INDICATOR);
  (p->coord).x = PIXEL(0);
  (p->coord).y = PIXEL(148);
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
  p->work[2] = 0;
  ExlifeIndicator_Update((void*)p);
}

// Slides the "Zx<lives>" readout in via SIN (t<=0x20) and back out via COS
// (t>0x7E) over a 0xA0-frame timer. Retail keeps the pre-increment value in a
// callee-saved register and expresses the slide-out index as old*2+66 rather
// than COS(t*2); agbcc won't reproduce that allocation from clean C, so
// dual-form it.
NON_MATCH static void ExlifeIndicator_Update(struct VFX* vfx) {
#if MODERN
  u8 t = ++(vfx->s).work[2];
  if (t <= 0x20) {
    (vfx->s).coord.x = SIN(t * 2) * 0xDC;
  } else if (t > 0x7E) {
    (vfx->s).coord.x = 0xDC * 0x200 - 0xDC * COS(t * 2);
  }
  if ((vfx->s).work[2] == 0xA0) {
    SET_VFX_ROUTINE(vfx, ENTITY_DIE);
  }
#else
  INCCODE("asm/wip/ExlifeIndicator_Update.inc");
#endif
}

static void ExlifeIndicator_Die(struct Entity* p) {
  p->flags &= ~DISPLAY;
  SET_VFX_ROUTINE(p, ENTITY_EXIT);
}

static void TaskCB_080be5d0(struct Sprite* s, struct DrawPivot* c) {
  // clang-format off
  static const motion_t sMotions[10] = {
    MOTION(SM060_EXLIFE_INDICATOR, 0), // Zx0
    MOTION(SM060_EXLIFE_INDICATOR, 1), // Zx1
    MOTION(SM060_EXLIFE_INDICATOR, 2), // Zx2
    MOTION(SM060_EXLIFE_INDICATOR, 3), // Zx3
    MOTION(SM060_EXLIFE_INDICATOR, 4), // Zx4
    MOTION(SM060_EXLIFE_INDICATOR, 5), // Zx5
    MOTION(SM060_EXLIFE_INDICATOR, 6), // Zx6
    MOTION(SM060_EXLIFE_INDICATOR, 7), // Zx7
    MOTION(SM060_EXLIFE_INDICATOR, 8), // Zx8
    MOTION(SM060_EXLIFE_INDICATOR, 9), // Zx9
  };
  // clang-format on
  struct VFX* p = (struct VFX*)s->sprites;
  struct Coord coord;
  coord.x = (p->s).coord.x - PIXEL(120);
  coord.x += (c->coord).x;
  coord.y = (p->s).coord.y - PIXEL(80);
  coord.y += (c->coord).y;
  InitNonAffineMotion((struct Entity*)p);
  SetMotion((struct Entity*)p, sMotions[(p->s).work[0]]);
  (p->s).spr.oam.priority = 0;
  UpdateMotionGraphic((struct Entity*)p);
  (p->s).spr.c = &coord;
  (s->fn)(s, c);
  SetTaskCallback((struct RenderNode*)&(p->s).spr, TaskCB_080be5d0);
  (p->s).spr.sprites = (struct MetaspriteHeader*)p;
  (p->s).flags &= ~OAM_PRIO;
}
