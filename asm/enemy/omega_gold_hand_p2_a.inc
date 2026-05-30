	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_08083288
FUN_08083288: @ 0x08083288
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r5, [r4, #0xe]
	cmp r5, #0
	beq _08083298
	cmp r5, #1
	beq _08083304
	b _08083320
_08083298:
	ldrb r1, [r4, #0xb]
	movs r0, #0x10
	orrs r0, r1
	strb r0, [r4, #0xb]
	ldr r0, [r4, #0x28]
	ldrb r0, [r0, #0x1c]
	strb r0, [r4, #0x1d]
	movs r1, #0x90
	lsls r1, r1, #4
	adds r0, r4, #0
	bl SetMotion
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	adds r0, #0x4c
	strb r5, [r0]
	adds r2, r4, #0
	adds r2, #0x4a
	ldrb r1, [r2]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r2]
	ldrb r1, [r4, #0xa]
	movs r0, #0xdf
	ands r0, r1
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	adds r0, #0x4d
	strb r5, [r0]
	ldrb r1, [r2]
	movs r0, #0x21
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r2]
	adds r0, r4, #0
	adds r0, #0xb8
	ldr r2, [r4, #0x28]
	ldr r0, [r0]
	ldr r1, [r2, #0x58]
	adds r0, r0, r1
	str r0, [r4, #0x58]
	adds r0, r4, #0
	adds r0, #0xb4
	ldr r0, [r0]
	ldr r1, [r2, #0x54]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08083304:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldr r0, [r4, #0x28]
	ldr r0, [r0, #0x18]
	ldrb r1, [r0, #9]
	movs r2, #1
	adds r0, r2, #0
	ands r0, r1
	cmp r0, #0
	beq _08083320
	movs r0, #0
	strb r2, [r4, #0xd]
	strb r0, [r4, #0xe]
_08083320:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0

