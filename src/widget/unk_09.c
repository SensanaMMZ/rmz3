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

NAKED static void FUN_080e7b9c(struct Widget* w) {
  asm(".syntax unified\n\
	push {r4, r5, r6, lr}\n\
	adds r3, r0, #0\n\
	ldr r0, [r3, #0x28]\n\
	ldr r1, _080E7BCC @ =0x00000DFC\n\
	adds r0, r0, r1\n\
	ldrb r1, [r3, #0x11]\n\
	adds r0, r0, r1\n\
	ldrb r4, [r0]\n\
	cmp r4, #0xff\n\
	beq _080E7C38\n\
	ldr r1, _080E7BD0 @ =gElfBreedInfo\n\
	lsls r2, r4, #2\n\
	adds r0, r2, r1\n\
	ldrb r5, [r0]\n\
	lsls r0, r5, #0x19\n\
	adds r6, r1, #0\n\
	cmp r0, #0\n\
	bge _080E7BE0\n\
	lsrs r0, r5, #7\n\
	cmp r0, #0\n\
	beq _080E7BD8\n\
	ldr r1, _080E7BD4 @ =0x00005311\n\
	b _080E7C2A\n\
	.align 2, 0\n\
_080E7BCC: .4byte 0x00000DFC\n\
_080E7BD0: .4byte gElfBreedInfo\n\
_080E7BD4: .4byte 0x00005311\n\
_080E7BD8:\n\
	ldr r1, _080E7BDC @ =0x00005308\n\
	b _080E7C2A\n\
	.align 2, 0\n\
_080E7BDC: .4byte 0x00005308\n\
_080E7BE0:\n\
	ldr r0, _080E7C04 @ =gUnlockedElfPtr\n\
	ldr r0, [r0]\n\
	adds r0, r0, r4\n\
	ldrb r1, [r0]\n\
	movs r0, #4\n\
	ands r0, r1\n\
	cmp r0, #0\n\
	beq _080E7C14\n\
	lsls r0, r5, #0x1a\n\
	lsrs r0, r0, #0x1d\n\
	cmp r0, #1\n\
	bne _080E7C14\n\
	lsls r0, r5, #0x18\n\
	cmp r0, #0\n\
	bge _080E7C0C\n\
	ldr r1, _080E7C08 @ =0x00005311\n\
	b _080E7C2A\n\
	.align 2, 0\n\
_080E7C04: .4byte gUnlockedElfPtr\n\
_080E7C08: .4byte 0x00005311\n\
_080E7C0C:\n\
	ldr r1, _080E7C10 @ =0x00005308\n\
	b _080E7C2A\n\
	.align 2, 0\n\
_080E7C10: .4byte 0x00005308\n\
_080E7C14:\n\
	adds r0, r2, r6\n\
	ldrb r0, [r0]\n\
	lsrs r0, r0, #7\n\
	cmp r0, #0\n\
	beq _080E7C28\n\
	ldr r1, _080E7C24 @ =0x00005310\n\
	b _080E7C2A\n\
	.align 2, 0\n\
_080E7C24: .4byte 0x00005310\n\
_080E7C28:\n\
	ldr r1, _080E7C34 @ =0x00005307\n\
_080E7C2A:\n\
	adds r0, r3, #0\n\
	bl SetMotion\n\
	b _080E7C40\n\
	.align 2, 0\n\
_080E7C34: .4byte 0x00005307\n\
_080E7C38:\n\
	ldrb r1, [r3, #0xa]\n\
	movs r0, #0xfe\n\
	ands r0, r1\n\
	strb r0, [r3, #0xa]\n\
_080E7C40:\n\
	pop {r4, r5, r6}\n\
	pop {r0}\n\
	bx r0\n\
 .syntax divided\n");
}
