#include "game.h"
#include "global.h"
#include "widget.h"

/*
  メインメニューの、"メイン", "サブ", "サブタンク", "ヘッド" などの項目名
*/

struct Widget* CreateMenuComp1(struct GameState* m, u8 kind, u8 r2) {
  struct Widget* w = (struct Widget*)AllocEntityFirst(gWidgetHeaderPtr);
  if (w != NULL) {
    (w->s).taskCol = 16;
    INIT_WIDGET_ROUTINE(w, 1);
    (w->s).tileNum = 0;
    (w->s).palID = 0;
    (w->s).unk_28 = (struct Entity*)m;
    (w->s).work[0] = kind;
    (w->s).work[1] = r2;
  }
  return w;
}

extern const motion_t sMenuComp1Motions[14];
extern const u8 u8_ARRAY_08372020[7];
extern const u8 u8_ARRAY_08372027[7];

// Spawn a menu component: display+flippable, unflipped, latch the current
// cursor (work[2]=MENU->unk_0), set the selected/unselected motion for its slot
// (work[0]), and place it from the per-slot x/y tables (mirrored into
// unk_coord), then route to Update. Retail expands `flags |= DISPLAY | FLIPABLE`
// into two bit-ORs where clean C folds to |3 (retail-suboptimal as in
// Weapon16_Init); INCCODE for the byte-match.
NON_MATCH static void MenuComp1_Init(struct Widget* p) {
#if MODERN
  struct GameState* g = (struct GameState*)(p->s).unk_28;

  InitNonAffineMotion(&p->s);
  (p->s).flags |= DISPLAY | FLIPABLE;
  SET_XFLIP(p, 0);
  (p->s).work[2] = MENU->unk_00[0];
  if ((p->s).work[0] == MENU->unk_00[0]) {
    SetMotion(&p->s, sMenuComp1Motions[(p->s).work[0] * 2 + 1]);
  } else {
    SetMotion(&p->s, sMenuComp1Motions[(p->s).work[0] * 2]);
  }
  (p->s).coord.x = u8_ARRAY_08372020[(p->s).work[0]] << 8;
  (p->s).coord.y = u8_ARRAY_08372027[(p->s).work[0]] << 8;
  (p->s).unk_coord = (p->s).coord;
  SET_WIDGET_ROUTINE(p, ENTITY_UPDATE);
  MenuComp1_Update(p);
#else
  INCCODE("asm/wip/MenuComp1_Init.inc");
#endif
}

// Fully decoded. Residual is a 2-instruction tie in the selected-motion arm:
// retail re-loads work[0] and adds 2 to the freshly-loaded table base at
// runtime, where agbcc-from-clean-C reuses work[0] and folds the +2 into the
// pool literal (2 instr shorter). INCCODE for the byte-match.
NON_MATCH static void MenuComp1_Update(struct Widget* p) {
#if MODERN
  struct GameState* g = (struct GameState*)(p->s).unk_28;
  struct MenuState* m = MENU;

  if (((u8*)m)[4] != 0) {
    (p->s).flags &= ~DISPLAY;
    (p->s).flags &= ~FLIPABLE;
    SET_WIDGET_ROUTINE(p, ENTITY_DISAPPEAR);
  } else {
    (p->s).coord = (p->s).unk_coord;
    if ((p->s).work[2] != m->unk_00[0]) {
      if ((p->s).work[0] == m->unk_00[0]) {
        SetMotion(&p->s, sMenuComp1Motions[(p->s).work[0] * 2 + 1]);
      } else {
        SetMotion(&p->s, sMenuComp1Motions[(p->s).work[0] * 2]);
      }
      (p->s).work[2] = MENU->unk_00[0];
    }
    UpdateMotionGraphic(&p->s);
    (p->s).unk_coord = (p->s).coord;
    if (*(u16*)((u8*)&gVideoRegBuffer + 16) > 0x100) {
      (p->s).coord.x += 0x20000;
    }
  }
#else
  INCCODE("asm/wip/MenuComp1_Update.inc");
#endif
}

static void MenuComp1_Die(struct Widget* w) {
  SET_WIDGET_ROUTINE(w, ENTITY_EXIT);
  return;
}

// ------------------------------------------------------------------------------------------------------------------------------------

// clang-format off
const WidgetRoutine gMenuComp1Routine = {
    [ENTITY_INIT] =      (void*)MenuComp1_Init,
    [ENTITY_UPDATE] =    (void*)MenuComp1_Update,
    [ENTITY_DIE] =       (void*)MenuComp1_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteWidget,
    [ENTITY_EXIT] =      (void*)DeleteEntity,
};
// clang-format on

// --------------------------------------------

// clang-format off
const motion_t sMenuComp1Motions[14] = {
  MOTION(SM015_MENUITEM, 0x00),
  MOTION(SM015_MENUITEM, 0x01),
  MOTION(SM015_MENUITEM, 0x02),
  MOTION(SM015_MENUITEM, 0x03),
  MOTION(SM015_MENUITEM, 0x0A),
  MOTION(SM015_MENUITEM, 0x0B),
  MOTION(SM015_MENUITEM, 0x04),
  MOTION(SM015_MENUITEM, 0x05),
  MOTION(SM015_MENUITEM, 0x06),
  MOTION(SM015_MENUITEM, 0x07),
  MOTION(SM015_MENUITEM, 0x08),
  MOTION(SM015_MENUITEM, 0x09),
  MOTION(SM015_MENUITEM, 0x0C),
  MOTION(SM015_MENUITEM, 0x0D),
};
// clang-format on

// --------------------------------------------

const u8 u8_ARRAY_08372020[7] = {
    0x18, 0x18, 0x18, 0xB0, 0xB0, 0xB0, 0x5C,
};

const u8 u8_ARRAY_08372027[7] = {
    0x38, 0x50, 0x68, 0x38, 0x50, 0x68, 0x78,
};
