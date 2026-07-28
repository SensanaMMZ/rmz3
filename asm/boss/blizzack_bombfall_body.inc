	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _0805A8A4
	ldr r1, _0805A8EC @ =0x0000B403
	adds r0, r4, #0
	bl SetMotion
	ldr r1, [r4, #0x2c]
	movs r0, #1
	strb r0, [r1, #0xe]
	ldr r0, [r4, #0x2c]
	adds r0, #0xbc
	movs r2, #0
	ldr r1, _0805A8F0 @ =0x00006403
	strh r1, [r0]
	strb r2, [r4, #0xe]
_0805A8A4:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	ldr r0, [r4, #0x58]
	ldr r1, [r4, #0x60]
	adds r0, r0, r1
	str r0, [r4, #0x58]
	adds r1, #0x60
	str r1, [r4, #0x60]
	movs r0, #0xe0
	lsls r0, r0, #3
	cmp r1, r0
	ble _0805A8C8
	str r0, [r4, #0x60]
_0805A8C8:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	bl FUN_08009f6c
	ldr r1, [r4, #0x58]
	cmp r0, r1
	bge _0805A8E6
	movs r0, #0x10
	strb r0, [r4, #0xd]
	movs r0, #1
	strb r0, [r4, #0xe]
	ldr r0, [r4, #0x54]
	bl FUN_08009f6c
	str r0, [r4, #0x58]
_0805A8E6:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_0805A8EC: .4byte 0x0000B403
_0805A8F0: .4byte 0x00006403
