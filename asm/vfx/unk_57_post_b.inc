	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080c1b34
FUN_080c1b34: @ 0x080C1B34
	push {r4, lr}
	adds r4, r0, #0
	bl UpdateMotionGraphic
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	ldr r0, [r4, #0x58]
	ldr r1, [r4, #0x60]
	adds r0, r0, r1
	str r0, [r4, #0x58]
	adds r1, #0x40
	str r1, [r4, #0x60]
	ldrb r1, [r4, #0x12]
	adds r0, r1, #1
	strb r0, [r4, #0x12]
	movs r0, #1
	ands r0, r1
	cmp r0, #0
	beq _080C1B66
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
	b _080C1B6C
_080C1B66:
	ldrb r0, [r4, #0xa]
	movs r1, #1
	orrs r0, r1
_080C1B6C:
	strb r0, [r4, #0xa]
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	bl FUN_080098a4
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _080C1B8E
	ldr r1, _080C1B94 @ =gVFXFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r4, #0x14]
_080C1B8E:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080C1B94: .4byte gVFXFnTable


