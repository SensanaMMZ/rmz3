	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _0805A482
	ldr r1, _0805A4A4 @ =0x0000B408
	adds r0, r4, #0
	bl SetMotion
	ldr r1, [r4, #0x2c]
	movs r0, #1
	strb r0, [r1, #0xe]
	ldr r0, [r4, #0x2c]
	adds r0, #0xbc
	movs r2, #0
	ldr r1, _0805A4A8 @ =0x00006408
	strh r1, [r0]
	strb r2, [r4, #0xe]
	movs r0, #8
	strb r0, [r4, #0x12]
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _0805A4AC @ =sCollisions
	bl SetDDP
_0805A482:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0xff
	bne _0805A49E
	movs r0, #3
	strb r0, [r4, #0xd]
	movs r0, #1
	strb r0, [r4, #0xe]
_0805A49E:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_0805A4A4: .4byte 0x0000B408
_0805A4A8: .4byte 0x00006408
_0805A4AC: .4byte sCollisions
