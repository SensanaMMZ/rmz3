	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080b9c50
FUN_080b9c50: @ 0x080B9C50
	push {r4, lr}
	adds r4, r0, #0
	bl UpdateMotionGraphic
	ldr r2, [r4, #0x5c]
	ldr r0, [r4, #0x64]
	adds r2, r2, r0
	str r2, [r4, #0x5c]
	ldr r1, [r4, #0x60]
	ldr r0, [r4, #0x68]
	adds r1, r1, r0
	str r1, [r4, #0x60]
	ldr r0, [r4, #0x54]
	adds r0, r0, r2
	str r0, [r4, #0x54]
	ldr r0, [r4, #0x58]
	adds r0, r0, r1
	str r0, [r4, #0x58]
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0xff
	bne _080B9C9A
	ldr r1, _080B9CA0 @ =gVFXFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r4, #0x14]
	adds r0, r4, #0
	bl Ghost27_Die
_080B9C9A:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080B9CA0: .4byte gVFXFnTable
