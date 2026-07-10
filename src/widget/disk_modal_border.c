#include "game.h"
#include "global.h"
#include "widget.h"

/*
セルヴォの研究所でシークレットディスクの中身を表すモーダルの四隅の枠
work[0]:
  0: 左上
  1:
  2:
  3:
*/

static void DiskModalBorder_Init(struct Widget* w);
static void DiskModalBorder_Update(struct Widget* w);
static void DiskModalBorder_Die(struct Widget* w);

// clang-format off
const WidgetRoutine gDiskModalBorderRoutine = {
    [ENTITY_INIT] =      (void*)DiskModalBorder_Init,
    [ENTITY_UPDATE] =    (void*)DiskModalBorder_Update,
    [ENTITY_DIE] =       (void*)DiskModalBorder_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteWidget,
    [ENTITY_EXIT] =      (void*)DeleteEntity,
};
// clang-format on

struct Widget* createSecretDiskModalBorder(struct GameState* g, u8 n) {
  struct Widget* w = (struct Widget*)AllocEntityFirst(gWidgetHeaderPtr);
  if (w != NULL) {
    (w->s).taskCol = 16;
    INIT_WIDGET_ROUTINE(w, 12);
    (w->s).tileNum = 0;
    (w->s).palID = 0;
    (w->s).unk_28 = (struct Entity*)g;
    (w->s).work[0] = n;
    (w->s).work[1] = 0;
  }
  return w;
}

// Init a disk-modal corner border: route to Update, flippable, motion 0xE04,
// then set X/Y flip from work[0] bits 0/1 (which corner). Retail keeps the `1`
// it wrote for the ENTITY_UPDATE mode live in a callee-saved reg and reuses it
// as the flip `& 1` mask across both flips; agbcc-from-clean-C re-materializes
// the mask and copies, ~6 instr longer — a constant-reuse allocation tie clean
// C can't force. INCCODE for the byte-match.
NON_MATCH static void DiskModalBorder_Init(struct Widget* w) {
#if MODERN
  SET_WIDGET_ROUTINE(w, ENTITY_UPDATE);
  InitNonAffineMotion(&w->s);
  (w->s).flags |= FLIPABLE;
  SetMotion(&w->s, 0xE04);

  (w->s).spr.xflip = (w->s).work[0] & 1;
  (w->s).spr.oam.xflip = (w->s).work[0] & 1;
  if ((w->s).work[0] & 1) {
    (w->s).flags |= X_FLIP;
  } else {
    (w->s).flags &= ~X_FLIP;
  }

  (w->s).spr.yflip = ((w->s).work[0] >> 1) & 1;
  (w->s).spr.oam.yflip = ((w->s).work[0] >> 1) & 1;
  if (((w->s).work[0] >> 1) & 1) {
    (w->s).flags |= Y_FLIP;
  } else {
    (w->s).flags &= ~Y_FLIP;
  }

  DiskModalBorder_Update(w);
#else
  INCCODE("asm/wip/DiskModalBorder_Init.inc");
#endif
}

static void DiskModalBorder_Update(struct Widget* w) {
  struct GameState* g = (struct GameState*)(w->s).unk_28;
  struct MenuState* m = MENU;

  if (m->unk_0d != 0) {
    (w->s).flags &= ~DISPLAY;
    (w->s).flags &= ~FLIPABLE;
    SET_WIDGET_ROUTINE(w, ENTITY_DISAPPEAR);
  } else if (m->unk_0e != 0) {
    (w->s).flags |= DISPLAY;
    UpdateMotionGraphic(&w->s);
    switch ((w->s).work[0]) {
      case 0:
        (w->s).coord.x = (0x40 - m->unk_0e) << 8;
        (w->s).coord.y = (0x50 - m->unk_0f) << 8;
        break;
      case 1:
        (w->s).coord.x = (m->unk_0e + 0x40) << 8;
        (w->s).coord.y = (0x50 - m->unk_0f) << 8;
        break;
      case 2:
        (w->s).coord.x = (0x40 - m->unk_0e) << 8;
        (w->s).coord.y = (m->unk_0f + 0x50) << 8;
        break;
      case 3:
        (w->s).coord.x = (m->unk_0e + 0x40) << 8;
        (w->s).coord.y = (m->unk_0f + 0x50) << 8;
        break;
    }
  } else {
    (w->s).flags &= ~DISPLAY;
  }
}

static void DiskModalBorder_Die(struct Widget* w) { SET_WIDGET_ROUTINE(w, ENTITY_EXIT); }
