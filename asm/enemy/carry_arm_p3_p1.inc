	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080716ac
FUN_080716ac: @ 0x080716AC
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _080716BC
	cmp r0, #1
	beq _0807173C
	b _0807176C
_080716BC:
	adds r1, r4, #0
	adds r1, #0x25
	movs r0, #0x17
	strb r0, [r1]
	movs r2, #0xc0
	lsls r2, r2, #6
	ldrb r1, [r4, #0x11]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #0xd
	subs r2, r2, r0
	str r2, [r4, #0x5c]
	cmp r2, #0
	bge _080716DA
	adds r2, #0xf
_080716DA:
	asrs r2, r2, #4
	str r2, [r4, #0x5c]
	movs r1, #0x20
	rsbs r1, r1, #0
	str r1, [r4, #0x68]
	movs r0, #0x80
	lsls r0, r0, #1
	lsls r1, r1, #3
	subs r0, r0, r1
	str r0, [r4, #0x60]
	movs r1, #0
	cmp r2, #0
	ble _080716F6
	movs r1, #1
_080716F6:
	adds r2, r1, #0
	cmp r2, #0
	beq _08071704
	ldrb r0, [r4, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _0807170A
_08071704:
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
_0807170A:
	strb r0, [r4, #0xa]
	adds r1, r2, #0
	adds r0, r4, #0
	adds r0, #0x4c
	strb r1, [r0]
	adds r3, r4, #0
	adds r3, #0x4a
	lsls r1, r1, #4
	ldrb r2, [r3]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r1
	strb r0, [r3]
	movs r0, #0x10
	strb r0, [r4, #0x12]
	ldr r1, _08071774 @ =0x00002201
	adds r0, r4, #0
	movs r2, #6
	movs r3, #3
	bl GotoMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0807173C:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	ldr r1, [r4, #0x60]
	ldr r0, [r4, #0x68]
	adds r1, r1, r0
	str r1, [r4, #0x60]
	ldr r0, [r4, #0x58]
	adds r0, r0, r1
	str r0, [r4, #0x58]
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	lsrs r1, r0, #0x18
	cmp r1, #0
	bne _08071766
	movs r0, #1
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_08071766:
	adds r0, r4, #0
	bl UpdateMotionGraphic
_0807176C:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_08071774: .4byte 0x00002201
