	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_0805d080
FUN_0805d080: @ 0x0805D080
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

	thumb_func_start FUN_0805d1c4
FUN_0805d1c4: @ 0x0805D1C4
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r5, [r4, #0xe]
	cmp r5, #0
	bne _0805D1E0
	ldr r1, _0805D20C @ =0x0000B50C
	movs r2, #2
	movs r3, #5
	bl GotoMotion
	str r5, [r4, #0x5c]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0805D1E0:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldr r0, [r4, #0x58]
	ldr r1, [r4, #0x60]
	adds r0, r0, r1
	str r0, [r4, #0x58]
	adds r1, #0x40
	str r1, [r4, #0x60]
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _0805D204
	movs r1, #0
	movs r0, #0x1b
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_0805D204:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_0805D20C: .4byte 0x0000B50C

	thumb_func_start FUN_0805d210
FUN_0805d210: @ 0x0805D210
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	bne _0805D268
	adds r0, r4, #0
	bl InitRotatableMotion
	adds r0, r4, #0
	bl ResetDynamicMotion
	ldr r1, _0805D250 @ =0x0000B50D
	adds r0, r4, #0
	bl SetMotion
	adds r1, r4, #0
	adds r1, #0x24
	movs r0, #0xe0
	strb r0, [r1]
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _0805D254 @ =0x08364F58
	bl SetDDP
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _0805D258
	movs r0, #0x80
	lsls r0, r0, #3
	b _0805D25A
	.align 2, 0
_0805D250: .4byte 0x0000B50D
_0805D254: .4byte 0x08364F58
_0805D258:
	ldr r0, _0805D2BC @ =0xFFFFFC00
_0805D25A:
	str r0, [r4, #0x5c]
	movs r0, #0x80
	lsls r0, r0, #3
	str r0, [r4, #0x60]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0805D268:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	bl FUN_080098a4
	lsls r0, r0, #0x10
	lsrs r5, r0, #0x10
	cmp r5, #0
	beq _0805D2C0
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	bl FUN_08010d70
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _0805D29A
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	bl FUN_08010dd8
_0805D29A:
	movs r0, #0x52
	bl PlaySound
	adds r1, r4, #0
	adds r1, #0x54
	movs r0, #5
	bl AppendQuake
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	subs r0, r0, r1
	str r0, [r4, #0x54]
	movs r1, #0
	movs r0, #0x1c
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
	b _0805D308
	.align 2, 0
_0805D2BC: .4byte 0xFFFFFC00
_0805D2C0:
	ldr r1, [r4, #0x58]
	ldr r0, [r4, #0x60]
	adds r1, r1, r0
	str r1, [r4, #0x58]
	ldr r0, [r4, #0x54]
	bl FUN_080098a4
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _0805D308
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	bl FUN_08010d70
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _0805D2EA
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	bl FUN_08010dd8
_0805D2EA:
	movs r0, #0x52
	bl PlaySound
	adds r1, r4, #0
	adds r1, #0x54
	movs r0, #5
	bl AppendQuake
	ldr r0, [r4, #0x58]
	ldr r1, [r4, #0x60]
	subs r0, r0, r1
	str r0, [r4, #0x58]
	movs r0, #0x1c
	strb r0, [r4, #0xd]
	strb r5, [r4, #0xe]
_0805D308:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start FUN_0805d310
FUN_0805d310: @ 0x0805D310
	push {r4, lr}
	adds r4, r0, #0
	ldrb r1, [r4, #0xe]
	cmp r1, #0
	bne _0805D376
	adds r0, #0x24
	strb r1, [r0]
	adds r0, r4, #0
	bl InitNonAffineMotion
	adds r0, r4, #0
	bl ResetDynamicMotion
	ldr r1, _0805D350 @ =0x0000B506
	adds r0, r4, #0
	bl SetMotion
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _0805D354 @ =sCollisions
	bl SetDDP
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _0805D360
	ldr r0, _0805D358 @ =0xFFFFFE80
	str r0, [r4, #0x5c]
	ldr r0, _0805D35C @ =0xFFFFF000
	b _0805D36A
	.align 2, 0
_0805D350: .4byte 0x0000B506
_0805D354: .4byte sCollisions
_0805D358: .4byte 0xFFFFFE80
_0805D35C: .4byte 0xFFFFF000
_0805D360:
	movs r0, #0xc0
	lsls r0, r0, #1
	str r0, [r4, #0x5c]
	movs r0, #0x80
	lsls r0, r0, #5
_0805D36A:
	str r0, [r4, #0x64]
	ldr r0, _0805D3C4 @ =0xFFFFFC40
	str r0, [r4, #0x60]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0805D376:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldr r1, [r4, #0x64]
	adds r0, r4, #0
	movs r2, #0
	bl FUN_0805d594
	lsls r0, r0, #0x10
	cmp r0, #0
	bne _0805D394
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	adds r0, r0, r1
	str r0, [r4, #0x54]
_0805D394:
	ldr r1, [r4, #0x58]
	ldr r0, [r4, #0x60]
	adds r1, r1, r0
	str r1, [r4, #0x58]
	adds r0, #0x40
	str r0, [r4, #0x60]
	ldr r0, [r4, #0x54]
	bl FUN_080098a4
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _0805D3BE
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	bl FUN_08009f6c
	str r0, [r4, #0x58]
	movs r1, #0
	movs r0, #7
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_0805D3BE:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_0805D3C4: .4byte 0xFFFFFC40

	thumb_func_start FUN_0805d3c8
FUN_0805d3c8: @ 0x0805D3C8
	push {r4, r5, lr}
	adds r5, r0, #0
	ldrb r1, [r5, #0xe]
	cmp r1, #0
	beq _0805D3D4
	b _0805D4E2
_0805D3D4:
	adds r0, #0x24
	strb r1, [r0]
	adds r0, r5, #0
	bl InitNonAffineMotion
	adds r0, r5, #0
	bl ResetDynamicMotion
	ldr r1, _0805D438 @ =0x0000B502
	adds r0, r5, #0
	bl SetMotion
	adds r0, r5, #0
	adds r0, #0x74
	ldr r1, _0805D43C @ =sCollisions
	bl SetDDP
	adds r4, r5, #0
	adds r4, #0xbc
	ldrb r1, [r4]
	movs r2, #1
	adds r0, r2, #0
	ands r0, r1
	adds r1, r5, #0
	adds r1, #0x4c
	strb r0, [r1]
	ldrb r0, [r4]
	movs r1, #0x4a
	adds r1, r1, r5
	mov ip, r1
	adds r1, r2, #0
	ands r1, r0
	lsls r1, r1, #4
	mov r0, ip
	ldrb r3, [r0]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r3
	orrs r0, r1
	mov r1, ip
	strb r0, [r1]
	ldrb r0, [r4]
	ands r2, r0
	cmp r2, #0
	beq _0805D440
	ldrb r0, [r5, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _0805D446
	.align 2, 0
_0805D438: .4byte 0x0000B502
_0805D43C: .4byte sCollisions
_0805D440:
	ldrb r1, [r5, #0xa]
	movs r0, #0xef
	ands r0, r1
_0805D446:
	strb r0, [r5, #0xa]
	ldrb r1, [r5, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _0805D498
	ldr r0, [r5, #0x54]
	ldr r2, _0805D488 @ =0xFFFFEE00
	adds r0, r0, r2
	ldr r1, [r5, #0x58]
	ldr r2, _0805D48C @ =0xFFFFF800
	adds r1, r1, r2
	bl FUN_080098a4
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _0805D480
	ldr r0, [r5, #0x54]
	ldr r1, _0805D488 @ =0xFFFFEE00
	adds r0, r0, r1
	ldr r1, [r5, #0x58]
	ldr r2, _0805D48C @ =0xFFFFF800
	adds r1, r1, r2
	bl FUN_0800a31c
	movs r1, #0x90
	lsls r1, r1, #5
	adds r0, r0, r1
	str r0, [r5, #0x54]
_0805D480:
	ldr r0, _0805D490 @ =0xFFFFFE00
	str r0, [r5, #0x5c]
	ldr r0, _0805D494 @ =0xFFFFF000
	b _0805D4D2
	.align 2, 0
_0805D488: .4byte 0xFFFFEE00
_0805D48C: .4byte 0xFFFFF800
_0805D490: .4byte 0xFFFFFE00
_0805D494: .4byte 0xFFFFF000
_0805D498:
	ldr r0, [r5, #0x54]
	movs r2, #0x90
	lsls r2, r2, #5
	adds r0, r0, r2
	ldr r1, [r5, #0x58]
	ldr r2, _0805D518 @ =0xFFFFF800
	adds r1, r1, r2
	bl FUN_080098a4
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _0805D4C8
	ldr r0, [r5, #0x54]
	movs r1, #0x90
	lsls r1, r1, #5
	adds r0, r0, r1
	ldr r1, [r5, #0x58]
	ldr r2, _0805D518 @ =0xFFFFF800
	adds r1, r1, r2
	bl FUN_0800a22c
	ldr r1, _0805D51C @ =0xFFFFEE00
	adds r0, r0, r1
	str r0, [r5, #0x54]
_0805D4C8:
	movs r0, #0x80
	lsls r0, r0, #2
	str r0, [r5, #0x5c]
	movs r0, #0x80
	lsls r0, r0, #5
_0805D4D2:
	str r0, [r5, #0x64]
	ldr r0, _0805D520 @ =0xFFFFFC00
	str r0, [r5, #0x60]
	movs r0, #0x10
	strb r0, [r5, #0x12]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_0805D4E2:
	adds r0, r5, #0
	bl UpdateMotionGraphic
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x5c]
	adds r0, r0, r1
	ldr r1, [r5, #0x64]
	adds r4, r0, r1
	ldr r1, [r5, #0x58]
	adds r0, r4, #0
	bl FUN_080098a4
	lsls r0, r0, #0x10
	cmp r0, #0
	bne _0805D536
	ldrb r1, [r5, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _0805D524
	adds r0, r5, #0
	adds r0, #0xb4
	ldr r0, [r0]
	cmp r4, r0
	ble _0805D536
	b _0805D52E
	.align 2, 0
_0805D518: .4byte 0xFFFFF800
_0805D51C: .4byte 0xFFFFEE00
_0805D520: .4byte 0xFFFFFC00
_0805D524:
	adds r0, r5, #0
	adds r0, #0xb8
	ldr r0, [r0]
	cmp r4, r0
	bge _0805D536
_0805D52E:
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x5c]
	adds r0, r0, r1
	str r0, [r5, #0x54]
_0805D536:
	ldr r1, [r5, #0x58]
	ldr r0, [r5, #0x60]
	adds r1, r1, r0
	str r1, [r5, #0x58]
	adds r0, #0x40
	str r0, [r5, #0x60]
	ldr r0, [r5, #0x54]
	bl FUN_080098a4
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _0805D560
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x58]
	bl FUN_08009f6c
	str r0, [r5, #0x58]
	movs r1, #0
	movs r0, #3
	strb r0, [r5, #0xd]
	strb r1, [r5, #0xe]
_0805D560:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
