#include "global.h"
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
NON_MATCH static void Ghost30_Init(struct VFX* p) {
#if MODERN
  InitNonAffineMotion(&p->s);
  (p->s).flags |= DISPLAY;
  (p->s).flags |= FLIPABLE;
  ResetDynamicMotion(&p->s);
  SET_XFLIP(p, (p->s).work[0]);
  (p->s).d.x = ((p->s).work[0] == 0) ? 0x80 : -0x80;
  (p->s).d.y = 0;
  (p->s).work[2] = 0xff;
  SET_VFX_ROUTINE(p, ENTITY_UPDATE);
  (p->s).mode[1] = 1;
  (p->s).mode[2] = 0;
  (p->s).mode[3] = 0;
  Ghost30_Update(p);
#else
  INCCODE("asm/wip/Ghost30_Init.inc");
#endif
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

NAKED static void FUN_080ba448(struct VFX* p) {
  asm(".syntax unified\n\
	push {r4, r5, lr}\n\
	adds r4, r0, #0\n\
	ldrb r5, [r4, #0xe]\n\
	cmp r5, #1\n\
	beq _080BA4B6\n\
	cmp r5, #1\n\
	bgt _080BA45C\n\
	cmp r5, #0\n\
	beq _080BA462\n\
	b _080BA52C\n\
_080BA45C:\n\
	cmp r5, #2\n\
	beq _080BA4FE\n\
	b _080BA52C\n\
_080BA462:\n\
	ldrb r0, [r4, #0x11]\n\
	cmp r0, #1\n\
	bne _080BA478\n\
	ldr r1, _080BA474 @ =0x0000A205\n\
	adds r0, r4, #0\n\
	bl SetMotion\n\
	b _080BA480\n\
	.align 2, 0\n\
_080BA474: .4byte 0x0000A205\n\
_080BA478:\n\
	ldr r1, _080BA494 @ =0x0000A21A\n\
	adds r0, r4, #0\n\
	bl SetMotion\n\
_080BA480:\n\
	movs r0, #0x3c\n\
	strb r0, [r4, #0x12]\n\
	ldr r0, [r4, #0x5c]\n\
	cmp r0, #0\n\
	ble _080BA498\n\
	ldr r1, [r4, #0x28]\n\
	ldr r0, [r1, #0x54]\n\
	movs r2, #0xc0\n\
	lsls r2, r2, #4\n\
	b _080BA49E\n\
	.align 2, 0\n\
_080BA494: .4byte 0x0000A21A\n\
_080BA498:\n\
	ldr r1, [r4, #0x28]\n\
	ldr r0, [r1, #0x54]\n\
	ldr r2, _080BA4F0 @ =0xFFFFF400\n\
_080BA49E:\n\
	adds r0, r0, r2\n\
	str r0, [r4, #0x64]\n\
	movs r0, #0x80\n\
	str r0, [r4, #0x60]\n\
	ldr r0, [r1, #0x58]\n\
	movs r1, #0xc0\n\
	lsls r1, r1, #3\n\
	adds r0, r0, r1\n\
	str r0, [r4, #0x68]\n\
	ldrb r0, [r4, #0xe]\n\
	adds r0, #1\n\
	strb r0, [r4, #0xe]\n\
_080BA4B6:\n\
	ldr r0, [r4, #0x64]\n\
	ldr r1, [r4, #0x54]\n\
	subs r0, r0, r1\n\
	lsls r0, r0, #4\n\
	asrs r0, r0, #8\n\
	adds r1, r1, r0\n\
	str r1, [r4, #0x54]\n\
	ldr r0, [r4, #0x68]\n\
	ldr r1, [r4, #0x58]\n\
	subs r0, r0, r1\n\
	lsls r0, r0, #4\n\
	asrs r0, r0, #8\n\
	adds r1, r1, r0\n\
	str r1, [r4, #0x58]\n\
	adds r0, r4, #0\n\
	bl UpdateMotionGraphic\n\
	ldr r0, [r4, #0x28]\n\
	ldrb r1, [r0, #0xa]\n\
	movs r0, #1\n\
	ands r0, r1\n\
	cmp r0, #0\n\
	beq _080BA4F4\n\
	ldrb r1, [r4, #0xa]\n\
	movs r0, #1\n\
	orrs r0, r1\n\
	strb r0, [r4, #0xa]\n\
	b _080BA52C\n\
	.align 2, 0\n\
_080BA4F0: .4byte 0xFFFFF400\n\
_080BA4F4:\n\
	ldrb r1, [r4, #0xa]\n\
	movs r0, #0xfe\n\
	ands r0, r1\n\
	strb r0, [r4, #0xa]\n\
	b _080BA52C\n\
_080BA4FE:\n\
	ldr r0, [r4, #0x28]\n\
	ldr r0, [r0, #0x18]\n\
	ldrb r1, [r0, #9]\n\
	movs r0, #0x80\n\
	ands r0, r1\n\
	cmp r0, #0\n\
	beq _080BA52C\n\
	adds r1, r4, #0\n\
	adds r1, #0x54\n\
	movs r0, #1\n\
	bl CreateSmoke\n\
	movs r0, #0x2a\n\
	bl PlaySound\n\
	ldr r1, _080BA534 @ =gVFXFnTable\n\
	ldrb r0, [r4, #9]\n\
	lsls r0, r0, #2\n\
	adds r0, r0, r1\n\
	str r5, [r4, #0xc]\n\
	ldr r0, [r0]\n\
	ldr r0, [r0, #8]\n\
	str r0, [r4, #0x14]\n\
_080BA52C:\n\
	pop {r4, r5}\n\
	pop {r0}\n\
	bx r0\n\
	.align 2, 0\n\
_080BA534: .4byte gVFXFnTable\n\
 .syntax divided\n");
}
