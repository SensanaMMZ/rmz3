	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080428c4
FUN_080428c4: @ 0x080428C4
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _080428D4
	cmp r0, #1
	beq _080428F0
	b _0804290A
_080428D4:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _08042910 @ =sCollisions
	bl SetDDP
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
	strb r0, [r4, #0xa]
	movs r0, #0x80
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080428F0:
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	lsrs r1, r0, #0x18
	cmp r1, #0
	bne _08042904
	movs r0, #2
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_08042904:
	adds r0, r4, #0
	bl UpdateMotionGraphic
_0804290A:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_08042910: .4byte sCollisions

