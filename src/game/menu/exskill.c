#include "palette_animation.h"
#include "game.h"
#include "gfx.h"
#include "global.h"
#include "menu.h"
#include "widget/exskill_icons.h"

static void ExMenuLoop_Init(struct GameState* g);
static void ExMenuLoop_Update(struct GameState* g);
static void ExMenuLoop_SlideOut(struct GameState* g);
static void ExMenuLoop_Exit(struct GameState* g);

// 01 02 xx xx (BYTE[0x02031978] = 1)
static const MenuLoopFunc ExSkillMenuLoops[4] = {
    ExMenuLoop_Init,
    ExMenuLoop_Update,
    ExMenuLoop_SlideOut,
    ExMenuLoop_Exit,
};

// ------------------------------------------------------------------------------------------------------------------------------------

void EachMenuLoop_ExSkill(struct GameState* g) {
  (ExSkillMenuLoops[g->mode[2]])(g);
  return;
}

#include "widget.h"
struct Entity* CreateMenuComp2(struct GameState* g, u8 kind, u8 r2);
struct Widget* CreateExSkillIcon(struct GameState* g, u8 kind);

static void ExMenuLoop_Init(struct GameState* g) {
  u8 i;
  struct Zero* z = g->z2;
  struct ExSkillMenuState* exskill = &((g->sceneState).menu).exskill;
  exskill->selected = 0;
  exskill->inactive = FALSE;
  LoadGraphic(BG_GRAPHIC(BG_EXSKILL_MENU), (void*)CHAR_BASE(1));
  LoadPalette(BG_PALETTE(BG_EXSKILL_MENU), 0);
  CpuFastCopy(BGMAP(BG_EXSKILL_MENU), g->menuBgMap2, 960 * 2);
  RequestBgMapTransfer(g->menuBgMap1, (void*)SCREEN_BASE_16(1), 0x1000);
  StartPaletteAnimation(62, 0);
  StartPaletteAnimation(63, 0);
  exskill->w = (struct Widget*)CreateMenuComp2(g, TRUE, 0);
  ((struct SquareCursorWidget*)exskill->w)->px = 284;
  ((struct SquareCursorWidget*)exskill->w)->py = 40;
  LOAD_STATIC_GRAPHIC(SM069_EXSKILL_ICON);
  for (i = 0; i < 12; i++) {
    u16 exskill = ((&z->unk_b4)->status).unlockedExSkill;
    if ((exskill & (1 << i)) >> i) CreateExSkillIcon(g, i);
  }
  g->mode[2] = 2;
}

NAKED static void ExMenuLoop_Update(struct GameState* g) {
  asm(".syntax unified\n\
	push {r4, r5, r6, r7, lr}\n\
	mov r7, r8\n\
	push {r7}\n\
	adds r6, r0, #0\n\
	ldr r1, _080F7C14 @ =0x000064AC\n\
	adds r0, r6, r1\n\
	ldr r0, [r0]\n\
	mov r8, r0\n\
	adds r0, r6, #0\n\
	bl TrySlideMenu\n\
	lsls r0, r0, #0x18\n\
	cmp r0, #0\n\
	beq _080F7B46\n\
	b _080F7CD2\n\
_080F7B46:\n\
	movs r0, #0x3e\n\
	bl StepPaletteAnimation\n\
	movs r0, #0x3f\n\
	bl StepPaletteAnimation\n\
	movs r0, #0xdf\n\
	lsls r0, r0, #4\n\
	adds r4, r6, r0\n\
	ldrb r7, [r4, #4]\n\
	ldr r5, _080F7C18 @ =gJoypad\n\
	ldrh r1, [r5, #6]\n\
	movs r0, #0x40\n\
	ands r0, r1\n\
	cmp r0, #0\n\
	beq _080F7B72\n\
	adds r0, r7, #0\n\
	adds r0, #8\n\
	movs r1, #0xc\n\
	bl __modsi3\n\
	strb r0, [r4, #4]\n\
_080F7B72:\n\
	ldrh r5, [r5, #6]\n\
	movs r0, #0x80\n\
	ands r0, r5\n\
	cmp r0, #0\n\
	beq _080F7B88\n\
	ldrb r0, [r4, #4]\n\
	adds r0, #4\n\
	movs r1, #0xc\n\
	bl __modsi3\n\
	strb r0, [r4, #4]\n\
_080F7B88:\n\
	movs r0, #0x20\n\
	ands r0, r5\n\
	cmp r0, #0\n\
	beq _080F7BA4\n\
	ldrb r1, [r4, #4]\n\
	lsrs r0, r1, #2\n\
	lsls r3, r0, #2\n\
	adds r2, r1, #3\n\
	adds r0, r2, #0\n\
	asrs r0, r0, #2\n\
	lsls r0, r0, #2\n\
	subs r0, r2, r0\n\
	adds r0, r3, r0\n\
	strb r0, [r4, #4]\n\
_080F7BA4:\n\
	ldr r0, _080F7C18 @ =gJoypad\n\
	ldrh r1, [r0, #6]\n\
	movs r0, #0x10\n\
	ands r0, r1\n\
	cmp r0, #0\n\
	beq _080F7BCA\n\
	movs r1, #0xdf\n\
	lsls r1, r1, #4\n\
	adds r4, r6, r1\n\
	ldrb r1, [r4, #4]\n\
	lsrs r0, r1, #2\n\
	lsls r3, r0, #2\n\
	adds r2, r1, #1\n\
	adds r0, r2, #0\n\
	asrs r0, r0, #2\n\
	lsls r0, r0, #2\n\
	subs r0, r2, r0\n\
	adds r0, r3, r0\n\
	strb r0, [r4, #4]\n\
_080F7BCA:\n\
	movs r0, #0xdf\n\
	lsls r0, r0, #4\n\
	adds r5, r6, r0\n\
	ldrb r1, [r5, #4]\n\
	cmp r7, r1\n\
	beq _080F7BDC\n\
	movs r0, #1\n\
	bl PlaySound\n\
_080F7BDC:\n\
	ldr r0, _080F7C18 @ =gJoypad\n\
	ldrh r1, [r0, #4]\n\
	movs r2, #1\n\
	adds r0, r2, #0\n\
	ands r0, r1\n\
	mov r4, r8\n\
	adds r4, #0xb4\n\
	cmp r0, #0\n\
	beq _080F7C2E\n\
	ldrh r0, [r4, #0x14]\n\
	ldrb r3, [r5, #4]\n\
	lsls r2, r3\n\
	ands r0, r2\n\
	asrs r0, r3\n\
	cmp r0, #0\n\
	beq _080F7C28\n\
	ldrh r1, [r4, #0x12]\n\
	adds r0, r1, #0\n\
	ands r0, r2\n\
	asrs r0, r3\n\
	cmp r0, #0\n\
	beq _080F7C1C\n\
	eors r1, r2\n\
	strh r1, [r4, #0x12]\n\
	movs r0, #3\n\
	bl PlaySound\n\
	b _080F7C2E\n\
	.align 2, 0\n\
_080F7C14: .4byte 0x000064AC\n\
_080F7C18: .4byte gJoypad\n\
_080F7C1C:\n\
	orrs r1, r2\n\
	strh r1, [r4, #0x12]\n\
	movs r0, #2\n\
	bl PlaySound\n\
	b _080F7C2E\n\
_080F7C28:\n\
	movs r0, #4\n\
	bl PlaySound\n\
_080F7C2E:\n\
	movs r0, #0xdf\n\
	lsls r0, r0, #4\n\
	adds r6, r6, r0\n\
	ldr r2, [r6]\n\
	ldrb r1, [r6, #4]\n\
	movs r0, #3\n\
	ands r1, r0\n\
	lsls r0, r1, #1\n\
	adds r0, r0, r1\n\
	lsls r0, r0, #3\n\
	movs r1, #0x8e\n\
	lsls r1, r1, #1\n\
	adds r0, r0, r1\n\
	adds r2, #0x74\n\
	strh r0, [r2]\n\
	ldr r2, [r6]\n\
	ldrb r1, [r6, #4]\n\
	lsrs r1, r1, #2\n\
	lsls r0, r1, #1\n\
	adds r0, r0, r1\n\
	lsls r0, r0, #3\n\
	adds r0, #0x28\n\
	adds r2, #0x76\n\
	strh r0, [r2]\n\
	ldrh r1, [r4, #0x14]\n\
	ldrb r2, [r6, #4]\n\
	movs r0, #1\n\
	lsls r0, r2\n\
	ands r1, r0\n\
	asrs r1, r2\n\
	cmp r1, #0\n\
	beq _080F7CAC\n\
	ldr r5, _080F7CA0 @ =StringOfsTable\n\
	movs r1, #0xe1\n\
	lsls r1, r1, #1\n\
	adds r0, r2, r1\n\
	lsls r0, r0, #1\n\
	adds r0, r0, r5\n\
	ldrh r0, [r0]\n\
	ldr r4, _080F7CA4 @ =gStringData\n\
	adds r0, r0, r4\n\
	movs r1, #2\n\
	movs r2, #0xe\n\
	bl PrintString\n\
	ldrb r0, [r6, #4]\n\
	ldr r1, _080F7CA8 @ =0x000001CF\n\
	adds r0, r0, r1\n\
	lsls r0, r0, #1\n\
	adds r0, r0, r5\n\
	ldrh r0, [r0]\n\
	adds r0, r0, r4\n\
	movs r1, #0x11\n\
	movs r2, #1\n\
	bl PrintString\n\
	b _080F7CD2\n\
	.align 2, 0\n\
_080F7CA0: .4byte StringOfsTable\n\
_080F7CA4: .4byte gStringData\n\
_080F7CA8: .4byte 0x000001CF\n\
_080F7CAC:\n\
	ldr r4, _080F7CDC @ =StringOfsTable\n\
	movs r1, #0xe7\n\
	lsls r1, r1, #2\n\
	adds r0, r4, r1\n\
	ldrh r0, [r0]\n\
	ldr r5, _080F7CE0 @ =gStringData\n\
	adds r0, r0, r5\n\
	movs r1, #2\n\
	movs r2, #0xe\n\
	bl PrintString\n\
	ldr r0, _080F7CE4 @ =0x000003B6\n\
	adds r4, r4, r0\n\
	ldrh r0, [r4]\n\
	adds r0, r0, r5\n\
	movs r1, #0x11\n\
	movs r2, #1\n\
	bl PrintString\n\
_080F7CD2:\n\
	pop {r3}\n\
	mov r8, r3\n\
	pop {r4, r5, r6, r7}\n\
	pop {r0}\n\
	bx r0\n\
	.align 2, 0\n\
_080F7CDC: .4byte StringOfsTable\n\
_080F7CE0: .4byte gStringData\n\
_080F7CE4: .4byte 0x000003B6\n\
 .syntax divided\n");
}

static void ExMenuLoop_SlideOut(struct GameState* g) {
  if (MENU->unk_4d == 2) {
    (*(u16*)((u8*)&gVideoRegBuffer + 16)) += 0x10;
  } else {
    (*(u16*)((u8*)&gVideoRegBuffer + 16)) -= 0x10;
  }
  (*(u16*)((u8*)&gVideoRegBuffer + 16)) &= 0x1FF;
  if (((*(u16*)((u8*)&gVideoRegBuffer + 16)) & 0xFF) == 0) {
    MENU->unk_4c = MENU->unk_4d;
    g->mode[2] = 1;
    ExMenuLoop_Exit(g);
  }
}

static void ExMenuLoop_Exit(struct GameState* g) {
  struct ExSkillMenuState* m = &((g->sceneState).menu).exskill;
  m->inactive = TRUE;
  RemovePaletteAnimation(0x3E);
  RemovePaletteAnimation(0x3F);
  ((struct ExSkillIcons*)(m->w))->unk_004[0] = 1;
}
