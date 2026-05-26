	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start blazinMode0
blazinMode0: @ 0x0803EE30
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _0803EE40
	cmp r0, #1
	beq _0803EE66
	b _0803EE80
_0803EE40:
	ldrb r1, [r4, #0xa]
	movs r0, #1
	orrs r0, r1
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	adds r0, #0xc8
	ldrh r1, [r0]
	adds r1, #0x15
	ldr r2, _0803EE88 @ =0xFFFFA200
	adds r0, r2, #0
	orrs r1, r0
	lsls r1, r1, #0x10
	lsrs r1, r1, #0x10
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0803EE66:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldr r0, [r4, #0x18]
	ldrb r1, [r0, #9]
	movs r2, #1
	adds r0, r2, #0
	ands r0, r1
	cmp r0, #0
	beq _0803EE80
	movs r0, #0
	strb r2, [r4, #0xd]
	strb r0, [r4, #0xe]
_0803EE80:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_0803EE88: .4byte 0xFFFFA200
