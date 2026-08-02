	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_08071888
FUN_08071888: @ 0x08071888
	push {r4, r5, r6, lr}
	adds r5, r0, #0
	ldr r6, [r5, #0x2c]
	cmp r6, #0
	beq _080718A8
	ldrb r0, [r6, #0xc]
	cmp r0, #1
	bls _080718A8
	movs r6, #0
	str r6, [r5, #0x2c]
	movs r0, #5
	strb r0, [r5, #0xd]
	strb r6, [r5, #0xe]
	adds r0, r5, #0
	bl FUN_08071b88
_080718A8:
	ldrb r0, [r5, #0xe]
	cmp r0, #0
	beq _080718B4
	cmp r0, #1
	beq _0807192C
	b _0807195C
_080718B4:
	ldr r0, [r6, #0x54]
	ldr r1, [r5, #0x54]
	subs r0, r0, r1
	str r0, [r5, #0x5c]
	movs r1, #0x28
	bl __divsi3
	adds r4, r0, #0
	str r4, [r5, #0x5c]
	movs r0, #0x20
	rsbs r0, r0, #0
	str r0, [r5, #0x68]
	ldr r0, [r6, #0x58]
	ldr r1, _080718FC @ =0xFFFFDE00
	adds r0, r0, r1
	ldr r1, [r5, #0x58]
	subs r0, r0, r1
	str r0, [r5, #0x60]
	movs r1, #0x28
	bl __divsi3
	movs r1, #0xa0
	lsls r1, r1, #2
	adds r0, r0, r1
	str r0, [r5, #0x60]
	movs r1, #0
	cmp r4, #0
	ble _080718EE
	movs r1, #1
_080718EE:
	adds r2, r1, #0
	cmp r2, #0
	beq _08071900
	ldrb r1, [r5, #0xa]
	movs r0, #0x10
	orrs r0, r1
	b _08071906
	.align 2, 0
_080718FC: .4byte 0xFFFFDE00
_08071900:
	ldrb r1, [r5, #0xa]
	movs r0, #0xef
	ands r0, r1
_08071906:
	strb r0, [r5, #0xa]
	adds r1, r2, #0
	adds r0, r5, #0
	adds r0, #0x4c
	strb r1, [r0]
	adds r3, r5, #0
	adds r3, #0x4a
	lsls r1, r1, #4
	ldrb r2, [r3]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r1
	strb r0, [r3]
	movs r0, #0x28
	strb r0, [r5, #0x12]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_0807192C:
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x5c]
	adds r0, r0, r1
	str r0, [r5, #0x54]
	ldr r1, [r5, #0x60]
	ldr r0, [r5, #0x68]
	adds r1, r1, r0
	str r1, [r5, #0x60]
	ldr r0, [r5, #0x58]
	adds r0, r0, r1
	str r0, [r5, #0x58]
	ldrb r0, [r5, #0x12]
	subs r0, #1
	strb r0, [r5, #0x12]
	lsls r0, r0, #0x18
	lsrs r1, r0, #0x18
	cmp r1, #0
	bne _08071956
	movs r0, #4
	strb r0, [r5, #0xd]
	strb r1, [r5, #0xe]
_08071956:
	adds r0, r5, #0
	bl UpdateMotionGraphic
_0807195C:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
