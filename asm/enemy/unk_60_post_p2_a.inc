	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080929e8
FUN_080929e8: @ 0x080929E8
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r5, [r4, #0xe]
	cmp r5, #0
	beq _080929F8
	cmp r5, #1
	beq _08092A34
	b _08092A54
_080929F8:
	movs r1, #0xb6
	lsls r1, r1, #8
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
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _08092A5C @ =0x08369AD4
	bl SetDDP
	str r5, [r4, #0x60]
	str r5, [r4, #0x5c]
	strb r5, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08092A34:
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
	adds r0, r4, #0
	bl UpdateMotionGraphic
_08092A54:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_08092A5C: .4byte 0x08369AD4
