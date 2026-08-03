	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_08097924
FUN_08097924: @ 0x08097924
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _08097934
	cmp r0, #1
	beq _080979E8
	b _08097A0C
_08097934:
	adds r1, r4, #0
	adds r1, #0xbe
	strb r0, [r1]
	adds r0, r4, #0
	bl FUN_08096fb0
	movs r1, #0xdc
	lsls r1, r1, #8
	adds r0, r4, #0
	bl SetMotion
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _08097974 @ =0x0836A288
	bl SetDDP
	movs r0, #0x18
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0x10]
	cmp r0, #1
	bne _08097994
	ldr r0, [r4, #0x28]
	ldr r1, [r4, #0x54]
	subs r2, r0, r1
	cmp r2, #0
	blt _08097978
	movs r0, #0x80
	lsls r0, r0, #9
	cmp r2, r0
	bgt _08097982
	b _080979E2
	.align 2, 0
_08097974: .4byte 0x0836A288
_08097978:
	subs r1, r1, r0
	movs r0, #0x80
	lsls r0, r0, #9
	cmp r1, r0
	ble _080979E2
_08097982:
	ldrb r2, [r4, #0xa]
	lsrs r0, r2, #4
	movs r1, #1
	bics r1, r0
	cmp r1, #0
	beq _080979C4
	movs r0, #0x10
	orrs r0, r2
	b _080979C8
_08097994:
	ldr r0, [r4, #0x28]
	ldr r1, [r4, #0x54]
	subs r2, r0, r1
	cmp r2, #0
	blt _080979A8
	movs r0, #0x80
	lsls r0, r0, #7
	cmp r2, r0
	bgt _080979B2
	b _080979E2
_080979A8:
	subs r1, r1, r0
	movs r0, #0x80
	lsls r0, r0, #7
	cmp r1, r0
	ble _080979E2
_080979B2:
	ldrb r2, [r4, #0xa]
	lsrs r0, r2, #4
	movs r1, #1
	bics r1, r0
	cmp r1, #0
	beq _080979C4
	movs r0, #0x10
	orrs r0, r2
	b _080979C8
_080979C4:
	movs r0, #0xef
	ands r0, r2
_080979C8:
	strb r0, [r4, #0xa]
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
_080979E2:
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080979E8:
	ldr r1, [r4, #0x5c]
	ldr r2, [r4, #0x60]
	adds r0, r4, #0
	bl FUN_08096ffc
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	lsrs r1, r0, #0x18
	cmp r1, #0
	bne _08097A06
	movs r0, #4
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_08097A06:
	adds r0, r4, #0
	bl UpdateMotionGraphic
_08097A0C:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
