#include "game.h"
#include "global.h"
#include "widget.h"
#include "cyberelf.h"
#include "menu.h"
#include "zero.h"

static void Widget9_Init(struct Widget* w);
static void Widget9_Update(struct Widget* w);
static void Widget9_Die(struct Widget* w);

// clang-format off
const WidgetRoutine gWidget9Routine = {
    [ENTITY_INIT] =      (void*)Widget9_Init,
    [ENTITY_UPDATE] =    (void*)Widget9_Update,
    [ENTITY_DIE] =       (void*)Widget9_Die,
    [ENTITY_DISAPPEAR] = (void*)DeleteWidget,
    [ENTITY_EXIT] =      (void*)DeleteEntity,
};
// clang-format on

struct Widget* CreateMenuComp9(struct GameState* g, bool8 r1, u8 r2) {
  struct Widget* w = (struct Widget*)AllocEntityFirst(gWidgetHeaderPtr);
  if (w != NULL) {
    (w->s).taskCol = 16;
    INIT_WIDGET_ROUTINE(w, 9);
    (w->s).tileNum = 0;
    (w->s).palID = 0;
    (w->s).unk_28 = (struct Entity*)g;
    (w->s).work[0] = r1;
    (w->s).work[1] = r2;
  }
  return w;
}

// --------------------------------------------

static void FUN_080e7a84(struct Widget* w);
static void FUN_080e7a9c(struct Widget* w);

static void Widget9_Init(struct Widget* w) {
  static const WidgetFunc sInitializers[2] = {
      FUN_080e7a84,
      FUN_080e7a9c,
  };
  SET_WIDGET_ROUTINE(w, ENTITY_UPDATE);
  InitNonAffineMotion(&w->s);
  (w->s).flags |= DISPLAY;
  (w->s).flags |= FLIPABLE;
  (w->s).spr.xflip = FALSE;
  (w->s).spr.oam.xflip = FALSE;
  (w->s).flags &= ~X_FLIP;
  (sInitializers[(w->s).work[0]])(w);
  Widget9_Update(w);
}

// --------------------------------------------

static void FUN_080e7ab0(struct Widget* w);
static void FUN_080e7b9c(struct Widget* w);

static void Widget9_Update(struct Widget* w) {
  static const WidgetFunc sUpdates[2] = {
      FUN_080e7ab0,
      FUN_080e7b9c,
  };

  struct GameState* g = (struct GameState*)(w->s).unk_28;
  if ((((&((g->sceneState).menu).elf)->unk_f & 0xFC) != 0) || g->mode[3] == 0) {
    (w->s).flags &= ~DISPLAY;
    (w->s).flags &= ~FLIPABLE;
    SET_WIDGET_ROUTINE(w, ENTITY_DISAPPEAR);
    return;
  }

  if (g->mode[3] < 2) {
    (w->s).flags &= ~DISPLAY;
  } else {
    (w->s).flags |= DISPLAY;
    (sUpdates[(w->s).work[0]])(w);
  }
  UpdateMotionGraphic(&w->s);
}

// --------------------------------------------

static void Widget9_Die(struct Widget* w) {
  SET_WIDGET_ROUTINE(w, ENTITY_EXIT);
  return;
}

// --------------------------------------------

static void FUN_080e7a84(struct Widget* w) {
  (w->s).coord.x = PIXEL(357);
  (w->s).coord.y = (w->s).work[1] * PIXEL(16) + PIXEL(16);
}

static void FUN_080e7a9c(struct Widget* w) {
  (w->s).coord.x = PIXEL(340);
  (w->s).coord.y = (w->s).work[1] * PIXEL(16) + PIXEL(16);
}

// --------------------------------------------

// Pick the elf-menu icon's motion by the equipped elf's breed/growup state.
// The row's elf id comes from ELF_MENU->displayed[work[1]]; 0xFF hides the
// widget. Already-used elves show 0x5302; the two equipped satellites show
// 0x5301 / 0x530F; otherwise the motion follows breed-minus-growup (and, when
// equal, the breed stage and the satellite-availability bit).
// Retail caches breedInfo<<26 and recomputes >>29 for each breed-stage check
// (two shifts) where agbcc-from-clean-C CSEs the full field extraction into one
// value and re-tests it — a CSE-granularity split (plus a 0x5300 materialization
// difference) that no source form flips. Decode is exact; INCCODE the byte-match.
NON_MATCH static void FUN_080e7ab0(struct Widget* w) {
#if MODERN
  struct GameState* g = (struct GameState*)(w->s).unk_28;
  struct Zero* z = *(struct Zero**)((u8*)g + 0x64AC);
  cyberelf_t e = ELF_MENU->displayed[(w->s).work[1]];

  if (e != 0xFF) {
    u8* avail = *gUnlockedElfPtr;
    motion_t id;
    if (avail[e] & 2) {
      id = 0x5302;
    } else if (SATELITE_1 == e) {
      id = 0x5301;
    } else if (SATELITE_2 == e) {
      id = 0x530F;
    } else {
      u8 breedInfo = gElfBreedInfo[e].unk_0;
      switch ((s32)(((u32)breedInfo << 29) >> 29) - (s32)((*(u32*)(avail + e) << 27) >> 30)) {
        case 0: {
          u32 stage = (u32)breedInfo << 26;
          if ((stage >> 29) == 1) {
            id = 0x5303;
          } else if ((stage >> 29) == 2) {
            id = (avail[e] & 4) ? 0x5300 : 0x5306;
          } else {
            id = 0x5300;
          }
          break;
        }
        case 1:
          id = 0x5304;
          break;
        case 2:
          id = 0x5305;
          break;
        default:
          return;
      }
    }
    SetMotion(&w->s, id);
  } else {
    (w->s).flags &= ~DISPLAY;
  }
#else
  INCCODE("asm/wip/FUN_080e7ab0.inc");
#endif
}

// Sibling of FUN_080e7ab0 for the second icon column: picks the motion from the
// elf's breed-info flags (bit 6 = fully bred, bit 7 = variant) and, when neither
// fully bred, whether it is an available satellite at breed-stage 1. Retail tests
// the flag bits via sign-shifts (`x<<25; bge`), caches the breed-info base, and
// re-reads unk_0 in the fallback arm; agbcc-from-clean-C masks the bits and reuses
// the cached byte, ~10 instr shorter. Retail-suboptimal like the sibling; INCCODE
// for the byte-match.
NON_MATCH static void FUN_080e7b9c(struct Widget* w) {
#if MODERN
  struct GameState* g = (struct GameState*)(w->s).unk_28;
  cyberelf_t e = ELF_MENU->displayed[(w->s).work[1]];

  if (e != 0xFF) {
    u8 breedInfo = gElfBreedInfo[e].unk_0;
    motion_t id;
    if (breedInfo & 0x40) {
      id = (breedInfo & 0x80) ? 0x5311 : 0x5308;
    } else if ((ELF_AVABILITY(e) & 4) && (((u32)breedInfo << 26) >> 29) == 1) {
      id = (breedInfo & 0x80) ? 0x5311 : 0x5308;
    } else {
      id = (breedInfo & 0x80) ? 0x5310 : 0x5307;
    }
    SetMotion(&w->s, id);
  } else {
    (w->s).flags &= ~DISPLAY;
  }
#else
  INCCODE("asm/wip/FUN_080e7b9c.inc");
#endif
}
