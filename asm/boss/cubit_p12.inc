	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start cubitMode10
cubitMode10: @ 0x080542CC
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r5, [r4, #0xe]
	cmp r5, #0
	beq _080542DC
	cmp r5, #1
	beq _0805430E
	b _08054314
_080542DC:
	adds r0, r4, #0
	bl InitNonAffineMotion
	adds r0, r4, #0
	bl ResetDynamicMotion
	adds r0, r4, #0
	adds r0, #0x24
	strb r5, [r0]
	adds r0, #0x2c
	movs r1, #0x80
	lsls r1, r1, #1
	strh r1, [r0]
	adds r0, #2
	strh r1, [r0]
	movs r0, #0xd1
	bl PlaySound
	ldr r1, _08054338 @ =0x0000B01E
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0805430E:
	adds r0, r4, #0
	bl UpdateMotionGraphic
_08054314:
	adds r5, r4, #0
	adds r5, #0xc0
	ldr r0, [r5]
	bl isKilled
	cmp r0, #0
	beq _08054330
	movs r0, #0
	str r0, [r5]
	movs r1, #3
	strb r1, [r4, #0xd]
	strb r0, [r4, #0xe]
	movs r0, #0xff
	strb r0, [r4, #0xf]
_08054330:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_08054338: .4byte 0x0000B01E
