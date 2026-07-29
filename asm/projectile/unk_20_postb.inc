	.include "asm/macros.inc"

	.syntax unified

	.text


	thumb_func_start FUN_080a5b28
FUN_080a5b28: @ 0x080A5B28
	push {r4, r5, lr}
	adds r4, r0, #0
	ldr r5, [r4, #0x28]
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _080A5B3A
	cmp r0, #1
	beq _080A5B62
	b _080A5BA8
_080A5B3A:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _080A5BB0 @ =0x0836BAD0
	bl SetDDP
	movs r0, #0x80
	lsls r0, r0, #3
	bl Sqrt
	lsls r0, r0, #0x10
	lsrs r0, r0, #0xb
	str r0, [r4, #0x5c]
	adds r1, r4, #0
	adds r1, #0xb4
	movs r0, #0x80
	lsls r0, r0, #7
	str r0, [r1]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080A5B62:
	adds r3, r4, #0
	adds r3, #0xb4
	ldr r0, [r3]
	ldr r1, [r4, #0x5c]
	adds r0, r0, r1
	str r0, [r3]
	movs r1, #0xc0
	lsls r1, r1, #0xa
	cmp r0, r1
	ble _080A5B7C
	ldr r0, [r4, #0x5c]
	subs r0, #0x20
	str r0, [r4, #0x5c]
_080A5B7C:
	ldr r0, [r4, #0x5c]
	cmp r0, #0
	bgt _080A5B9C
	adds r2, r5, #0
	adds r2, #0xc0
	ldr r0, [r2]
	movs r1, #0x81
	rsbs r1, r1, #0
	ands r0, r1
	str r0, [r2]
	movs r0, #0x80
	lsls r0, r0, #7
	str r0, [r3]
	movs r0, #1
	strb r0, [r4, #0xd]
	strb r0, [r4, #0xe]
_080A5B9C:
	adds r0, r4, #0
	bl FUN_080a4fa4
	adds r0, r4, #0
	bl UpdateMotionGraphic
_080A5BA8:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080A5BB0: .4byte 0x0836BAD0
