	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	bne _0805D16C
	ldr r1, _0805D0D4 @ =0x0000B506
	adds r0, r4, #0
	bl SetMotion
	movs r3, #0
	ldr r0, _0805D0D8 @ =pZero2
	ldr r2, [r0]
	ldr r1, [r4, #0x54]
	ldr r0, [r2, #0x54]
	cmp r1, r0
	bge _0805D0A2
	movs r3, #1
_0805D0A2:
	adds r0, r4, #0
	adds r0, #0x4c
	strb r3, [r0]
	movs r3, #0
	ldr r1, [r4, #0x54]
	ldr r0, [r2, #0x54]
	cmp r1, r0
	bge _0805D0B4
	movs r3, #1
_0805D0B4:
	adds r5, r4, #0
	adds r5, #0x4a
	lsls r2, r3, #4
	ldrb r1, [r5]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	orrs r0, r2
	strb r0, [r5]
	cmp r3, #0
	beq _0805D0DC
	ldrb r0, [r4, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _0805D0E2
	.align 2, 0
_0805D0D4: .4byte 0x0000B506
_0805D0D8: .4byte pZero2
_0805D0DC:
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
_0805D0E2:
	strb r0, [r4, #0xa]
	ldr r0, _0805D128 @ =pZero2
	ldr r0, [r0]
	adds r1, r4, #0
	adds r1, #0xb4
	ldr r0, [r0, #0x54]
	ldr r5, [r1]
	subs r2, r0, r5
	movs r1, #0xc0
	lsls r1, r1, #6
	adds r0, r2, #0
	bl __divsi3
	lsls r1, r0, #1
	adds r1, r1, r0
	lsls r1, r1, #0xc
	movs r0, #0xc0
	lsls r0, r0, #5
	adds r2, r1, r0
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _0805D134
	adds r0, r5, r2
	ldr r1, _0805D12C @ =0xFFFFB800
	adds r2, r0, r1
	adds r0, r4, #0
	adds r0, #0xb8
	ldr r1, [r0]
	ldr r3, _0805D130 @ =0xFFFFE800
	adds r0, r1, r3
	cmp r2, r0
	ble _0805D148
	b _0805D146
	.align 2, 0
_0805D128: .4byte pZero2
_0805D12C: .4byte 0xFFFFB800
_0805D130: .4byte 0xFFFFE800
_0805D134:
	adds r0, r5, r2
	movs r1, #0x90
	lsls r1, r1, #7
	adds r2, r0, r1
	movs r3, #0xc0
	lsls r3, r3, #5
	adds r0, r5, r3
	cmp r2, r0
	bge _0805D148
_0805D146:
	adds r2, r0, #0
_0805D148:
	ldr r0, [r4, #0x54]
	subs r0, r2, r0
	movs r1, #0x1c
	bl __divsi3
	str r0, [r4, #0x5c]
	cmp r0, #0
	ble _0805D15E
	movs r0, #0x80
	lsls r0, r0, #5
	b _0805D160
_0805D15E:
	ldr r0, _0805D1BC @ =0xFFFFF000
_0805D160:
	str r0, [r4, #0x64]
	ldr r0, _0805D1C0 @ =0xFFFFF900
	str r0, [r4, #0x60]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0805D16C:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldr r1, [r4, #0x64]
	adds r0, r4, #0
	movs r2, #0
	bl FUN_0805d594
	lsls r0, r0, #0x10
	cmp r0, #0
	bne _0805D18A
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	adds r0, r0, r1
	str r0, [r4, #0x54]
_0805D18A:
	ldr r2, [r4, #0x60]
	adds r0, r4, #0
	movs r1, #0
	bl FUN_0805d594
	lsls r0, r0, #0x10
	cmp r0, #0
	bne _0805D1A2
	ldr r0, [r4, #0x58]
	ldr r1, [r4, #0x60]
	adds r0, r0, r1
	str r0, [r4, #0x58]
_0805D1A2:
	ldr r0, [r4, #0x60]
	adds r0, #0x40
	str r0, [r4, #0x60]
	cmp r0, #0
	blt _0805D1B4
	movs r1, #0
	movs r0, #0x1a
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_0805D1B4:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_0805D1BC: .4byte 0xFFFFF000
_0805D1C0: .4byte 0xFFFFF900
