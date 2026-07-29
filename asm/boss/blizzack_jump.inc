	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _0805A26A
	ldr r1, _0805A2B4 @ =0x0000B403
	adds r0, r4, #0
	bl SetMotion
	ldr r1, [r4, #0x2c]
	movs r0, #1
	strb r0, [r1, #0xe]
	ldr r0, [r4, #0x2c]
	adds r0, #0xbc
	movs r2, #0
	ldr r1, _0805A2B8 @ =0x00006403
	strh r1, [r0]
	strb r2, [r4, #0xe]
	ldr r0, _0805A2BC @ =pZero2
	ldr r0, [r0]
	ldr r0, [r0, #0x54]
	ldr r1, [r4, #0x54]
	subs r0, r0, r1
	movs r1, #0x34
	bl __divsi3
	str r0, [r4, #0x5c]
	ldr r0, _0805A2C0 @ =0xFFFFF640
	str r0, [r4, #0x60]
_0805A26A:
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
	ble _0805A28E
	str r0, [r4, #0x60]
_0805A28E:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	bl FUN_08009f6c
	ldr r1, [r4, #0x58]
	cmp r0, r1
	bge _0805A2AC
	ldr r0, [r4, #0x54]
	bl FUN_08009f6c
	str r0, [r4, #0x58]
	movs r0, #6
	strb r0, [r4, #0xd]
	movs r0, #1
	strb r0, [r4, #0xe]
_0805A2AC:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_0805A2B4: .4byte 0x0000B403
_0805A2B8: .4byte 0x00006403
_0805A2BC: .4byte pZero2
_0805A2C0: .4byte 0xFFFFF640

