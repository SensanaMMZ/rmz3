	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _0805ABA2
	ldr r1, _0805ABE8 @ =0x0000B40B
	adds r0, r4, #0
	bl SetMotion
	ldr r1, [r4, #0x2c]
	movs r0, #1
	strb r0, [r1, #0xe]
	ldr r0, [r4, #0x2c]
	adds r0, #0xbc
	movs r2, #0
	ldr r1, _0805ABEC @ =0x0000640B
	strh r1, [r0]
	strb r2, [r4, #0xe]
	movs r1, #0x80
	lsls r1, r1, #1
	str r1, [r4, #0x5c]
	ldr r0, _0805ABF0 @ =0xFFFFFD00
	str r0, [r4, #0x60]
	adds r0, r4, #0
	adds r0, #0xc4
	ldrb r0, [r0]
	cmp r0, #0
	beq _0805AB98
	rsbs r0, r1, #0
	str r0, [r4, #0x5c]
_0805AB98:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _0805ABF4 @ =sCollisions
	bl SetDDP
_0805ABA2:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldr r0, [r4, #0x58]
	ldr r1, [r4, #0x60]
	adds r0, r0, r1
	str r0, [r4, #0x58]
	adds r1, #0x60
	str r1, [r4, #0x60]
	movs r0, #0xe0
	lsls r0, r0, #3
	cmp r1, r0
	ble _0805ABBE
	str r0, [r4, #0x60]
_0805ABBE:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	bl FUN_08009f6c
	ldr r1, [r4, #0x58]
	cmp r0, r1
	bge _0805ABF8
	ldr r0, [r4, #0x54]
	bl FUN_08009f6c
	str r0, [r4, #0x58]
	adds r0, r4, #0
	adds r0, #0xd4
	ldr r0, [r0]
	cmp r0, #0
	bne _0805AC00
	movs r0, #0x14
	strb r0, [r4, #0xd]
	movs r0, #1
	strb r0, [r4, #0xe]
	b _0805AC00
	.align 2, 0
_0805ABE8: .4byte 0x0000B40B
_0805ABEC: .4byte 0x0000640B
_0805ABF0: .4byte 0xFFFFFD00
_0805ABF4: .4byte sCollisions
_0805ABF8:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	adds r0, r0, r1
	str r0, [r4, #0x54]
_0805AC00:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
