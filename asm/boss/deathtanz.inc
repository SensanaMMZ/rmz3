	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start deathtanzMode0
deathtanzMode0: @ 0x080490B8
	push {r4, r5, lr}
	sub sp, #8
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0xb
	bls _080490C6
	b _0804931E
_080490C6:
	lsls r0, r0, #2
	ldr r1, _080490D0 @ =_080490D4
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_080490D0: .4byte _080490D4
_080490D4: @ jump table
	.4byte _08049104 @ case 0
	.4byte _08049112 @ case 1
	.4byte _0804912C @ case 2
	.4byte _0804913A @ case 3
	.4byte _08049160 @ case 4
	.4byte _080491AC @ case 5
	.4byte _08049200 @ case 6
	.4byte _08049228 @ case 7
	.4byte _08049254 @ case 8
	.4byte _08049290 @ case 9
	.4byte _080492E4 @ case 10
	.4byte _08049306 @ case 11
_08049104:
	ldr r1, _08049128 @ =0x0000A701
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08049112:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldr r0, [r4, #0x18]
	ldrb r1, [r0, #9]
	movs r0, #1
	ands r0, r1
	cmp r0, #0
	bne _08049126
	b _0804931E
_08049126:
	b _080492D8
	.align 2, 0
_08049128: .4byte 0x0000A701
_0804912C:
	ldr r1, _08049158 @ =0x0000A702
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0804913A:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldr r0, [r4, #0x70]
	ldr r1, _0804915C @ =0x00FFFF00
	ands r0, r1
	movs r1, #0x83
	lsls r1, r1, #9
	cmp r0, r1
	beq _08049150
	b _080492CE
_08049150:
	movs r0, #0x5b
	bl PlaySound
	b _080492CE
	.align 2, 0
_08049158: .4byte 0x0000A702
_0804915C: .4byte 0x00FFFF00
_08049160:
	ldr r1, _080491F8 @ =0x0000A703
	adds r0, r4, #0
	bl SetMotion
	ldr r0, [r4, #0x54]
	str r0, [sp]
	ldr r0, [r4, #0x58]
	ldr r1, _080491FC @ =0xFFFFE000
	adds r0, r0, r1
	str r0, [sp, #4]
	mov r0, sp
	movs r1, #1
	movs r2, #0
	bl CreateVFX39
	adds r3, r0, #0
	str r3, [r4, #0x2c]
	cmp r3, #0
	beq _0804919E
	adds r1, r3, #0
	adds r1, #0x74
	movs r2, #0
	movs r0, #0x10
	strb r0, [r1]
	adds r1, #1
	movs r0, #6
	strb r0, [r1]
	adds r1, #1
	movs r0, #0x18
	strb r0, [r1]
	str r2, [r3, #0x78]
_0804919E:
	movs r1, #0
	movs r0, #0x1e
	strb r0, [r4, #0x12]
	str r1, [r4, #0x5c]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080491AC:
	ldr r1, [r4, #0x5c]
	movs r0, #0x80
	lsls r0, r0, #7
	subs r0, r0, r1
	cmp r0, #0
	bge _080491BA
	adds r0, #0xf
_080491BA:
	asrs r0, r0, #4
	adds r5, r1, r0
	str r5, [r4, #0x5c]
	ldr r3, [r4, #0x2c]
	cmp r3, #0
	beq _080491DC
	adds r2, r5, #0
	cmp r5, #0
	bge _080491CE
	adds r2, r5, #7
_080491CE:
	asrs r2, r2, #3
	ldrb r1, [r4, #0x12]
	movs r0, #1
	ands r0, r1
	muls r0, r2, r0
	adds r0, r5, r0
	str r0, [r3, #0x78]
_080491DC:
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080491EE
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080491EE:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	b _0804931E
	.align 2, 0
_080491F8: .4byte 0x0000A703
_080491FC: .4byte 0xFFFFE000
_08049200:
	ldr r1, _08049250 @ =0x0000A704
	adds r0, r4, #0
	bl SetMotion
	adds r0, r4, #0
	bl GetEntityPalID
	adds r1, r0, #0
	lsls r1, r1, #0x18
	lsrs r1, r1, #0x13
	movs r2, #0x80
	lsls r2, r2, #2
	adds r0, r2, #0
	orrs r1, r0
	movs r0, #0x29
	bl StartPaletteAnimation
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08049228:
	ldr r3, [r4, #0x2c]
	cmp r3, #0
	beq _08049246
	ldr r5, [r4, #0x5c]
	adds r2, r5, #0
	cmp r5, #0
	bge _08049238
	adds r2, r5, #7
_08049238:
	asrs r2, r2, #3
	ldrb r1, [r4, #0x12]
	movs r0, #1
	ands r0, r1
	muls r0, r2, r0
	adds r0, r5, r0
	str r0, [r3, #0x78]
_08049246:
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	movs r0, #0x29
	b _080492C4
	.align 2, 0
_08049250: .4byte 0x0000A704
_08049254:
	ldr r1, _080492E0 @ =0x0000A705
	adds r0, r4, #0
	bl SetMotion
	movs r0, #0x29
	bl RemovePaletteAnimation
	adds r0, r4, #0
	bl GetEntityPalID
	adds r1, r0, #0
	lsls r1, r1, #0x18
	lsrs r1, r1, #0x13
	movs r2, #0x80
	lsls r2, r2, #2
	adds r0, r2, #0
	orrs r1, r0
	movs r0, #0x2a
	bl StartPaletteAnimation
	movs r0, #0x45
	bl PlaySound
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	bl FUN_080bdaf8
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08049290:
	ldr r1, [r4, #0x5c]
	rsbs r0, r1, #0
	cmp r0, #0
	bge _0804929A
	adds r0, #0xf
_0804929A:
	asrs r0, r0, #4
	adds r5, r1, r0
	str r5, [r4, #0x5c]
	ldr r3, [r4, #0x2c]
	cmp r3, #0
	beq _080492BC
	adds r2, r5, #0
	cmp r5, #0
	bge _080492AE
	adds r2, r5, #7
_080492AE:
	asrs r2, r2, #3
	ldrb r1, [r4, #0x12]
	movs r0, #1
	ands r0, r1
	muls r0, r2, r0
	adds r0, r5, r0
	str r0, [r3, #0x78]
_080492BC:
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	movs r0, #0x2a
_080492C4:
	bl StepPaletteAnimation
	adds r0, r4, #0
	bl UpdateMotionGraphic
_080492CE:
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _0804931E
_080492D8:
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
	b _0804931E
	.align 2, 0
_080492E0: .4byte 0x0000A705
_080492E4:
	ldr r3, [r4, #0x2c]
	cmp r3, #0
	beq _080492F2
	adds r1, r3, #0
	adds r1, #0x77
	movs r0, #1
	strb r0, [r1]
_080492F2:
	movs r0, #0x2a
	bl RemovePaletteAnimation
	ldr r1, _08049328 @ =0x0000A706
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08049306:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldr r0, _0804932C @ =gStageRun
	ldrb r0, [r0, #0x12]
	movs r2, #1
	adds r1, r2, #0
	ands r1, r0
	cmp r1, #0
	bne _0804931E
	strb r2, [r4, #0xd]
	strb r1, [r4, #0xe]
_0804931E:
	add sp, #8
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_08049328: .4byte 0x0000A706
_0804932C: .4byte gStageRun

	thumb_func_start deathtanzNeutral
deathtanzNeutral: @ 0x08049330
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _08049340
	cmp r0, #1
	beq _080493B2
	b _080493EA
_08049340:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _08049390 @ =sCollisions+(24*1)
	bl SetDDP
	adds r0, r4, #0
	adds r0, #0xbd
	ldrb r1, [r0]
	adds r5, r0, #0
	cmp r1, #0
	beq _0804939C
	ldrb r0, [r4, #0xa]
	lsrs r0, r0, #4
	movs r2, #1
	eors r0, r2
	ands r0, r2
	adds r1, r4, #0
	adds r1, #0x4c
	strb r0, [r1]
	ldrb r1, [r4, #0xa]
	lsrs r1, r1, #4
	eors r1, r2
	ands r1, r2
	movs r0, #0x4a
	adds r0, r0, r4
	mov ip, r0
	lsls r3, r1, #4
	ldrb r2, [r0]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r3
	mov r2, ip
	strb r0, [r2]
	cmp r1, #0
	beq _08049394
	ldrb r0, [r4, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _0804939A
	.align 2, 0
_08049390: .4byte sCollisions+(24*1)
_08049394:
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
_0804939A:
	strb r0, [r4, #0xa]
_0804939C:
	movs r0, #0
	strb r0, [r5]
	movs r0, #8
	strb r0, [r4, #0x12]
	ldr r1, _080493F0 @ =0x0000A706
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080493B2:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080493EA
	ldr r0, _080493F4 @ =pZero2
	ldr r2, [r0]
	adds r0, r2, #0
	adds r0, #0x8c
	ldr r0, [r0]
	movs r1, #0x80
	lsls r1, r1, #2
	ands r0, r1
	cmp r0, #0
	bne _080493EA
	adds r0, r2, #0
	adds r0, #0xa4
	movs r1, #0
	ldrsh r0, [r0, r1]
	cmp r0, #0
	beq _080493EA
	adds r0, r4, #0
	bl calcNextAction
_080493EA:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080493F0: .4byte 0x0000A706
_080493F4: .4byte pZero2

	thumb_func_start deathtanzMode2
deathtanzMode2: @ 0x080493F8
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #1
	beq _0804945E
	cmp r0, #1
	bgt _0804940C
	cmp r0, #0
	beq _08049418
	b _0804959C
_0804940C:
	cmp r0, #2
	beq _08049480
	cmp r0, #3
	bne _08049416
	b _08049538
_08049416:
	b _0804959C
_08049418:
	strb r0, [r4, #0x12]
	movs r2, #0
	adds r0, r4, #0
	adds r0, #0xb4
	ldr r1, [r4, #0x54]
	ldr r0, [r0]
	cmp r1, r0
	ble _0804942A
	movs r2, #1
_0804942A:
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _0804943A
	cmp r2, #0
	beq _0804943E
	b _08049442
_0804943A:
	cmp r2, #0
	beq _08049442
_0804943E:
	movs r0, #2
	b _0804959A
_08049442:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _08049478 @ =sCollisions+(24*4)
	bl SetDDP
	movs r0, #1
	strb r0, [r4, #0x12]
	ldr r1, _0804947C @ =0x0000A707
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0804945E:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	beq _08049470
	b _0804959C
_08049470:
	ldrb r0, [r4, #0xe]
	adds r0, #1
	b _0804959A
	.align 2, 0
_08049478: .4byte sCollisions+(24*4)
_0804947C: .4byte 0x0000A707
_08049480:
	ldrb r0, [r4, #0x12]
	cmp r0, #0
	beq _080494C8
	ldrb r0, [r4, #0xa]
	lsrs r0, r0, #4
	movs r2, #1
	eors r0, r2
	ands r0, r2
	adds r1, r4, #0
	adds r1, #0x4c
	strb r0, [r1]
	ldrb r1, [r4, #0xa]
	lsrs r1, r1, #4
	eors r1, r2
	ands r1, r2
	movs r0, #0x4a
	adds r0, r0, r4
	mov ip, r0
	lsls r3, r1, #4
	ldrb r2, [r0]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r3
	mov r2, ip
	strb r0, [r2]
	cmp r1, #0
	beq _080494C0
	ldrb r0, [r4, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _080494C6
_080494C0:
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
_080494C6:
	strb r0, [r4, #0xa]
_080494C8:
	ldr r3, _08049508 @ =u8_ARRAY_08362ea6
	ldr r2, _0804950C @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _08049510 @ =0x000343FD
	muls r0, r1, r0
	ldr r1, _08049514 @ =0x00269EC3
	adds r0, r0, r1
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r2]
	lsrs r0, r0, #0x11
	movs r1, #0xf
	ands r0, r1
	adds r0, r0, r3
	ldrb r0, [r0]
	adds r1, r4, #0
	adds r1, #0xbc
	strb r0, [r1]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _08049520
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _08049518 @ =sCollisions+(24*7)
	bl SetDDP
	ldr r1, _0804951C @ =0x0000A708
	adds r0, r4, #0
	bl SetMotion
	b _08049532
	.align 2, 0
_08049508: .4byte u8_ARRAY_08362ea6
_0804950C: .4byte RNG_0202f388
_08049510: .4byte 0x000343FD
_08049514: .4byte 0x00269EC3
_08049518: .4byte sCollisions+(24*7)
_0804951C: .4byte 0x0000A708
_08049520:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _0804957C @ =sCollisions+(24*9)
	bl SetDDP
	ldr r1, _08049580 @ =0x0000A709
	adds r0, r4, #0
	bl SetMotion
_08049532:
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08049538:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r5, [r0]
	cmp r5, #3
	bne _0804959C
	movs r0, #0x5c
	bl PlaySound
	adds r0, r4, #0
	adds r0, #0xbc
	ldrb r0, [r0]
	cmp r0, #0
	bne _08049596
	ldr r2, _08049584 @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _08049588 @ =0x000343FD
	muls r0, r1, r0
	ldr r1, _0804958C @ =0x00269EC3
	adds r0, r0, r1
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r2]
	lsrs r0, r0, #0x11
	movs r1, #1
	ands r0, r1
	cmp r0, #0
	beq _08049590
	movs r0, #6
	strb r0, [r4, #0xd]
	b _08049598
	.align 2, 0
_0804957C: .4byte sCollisions+(24*9)
_08049580: .4byte 0x0000A709
_08049584: .4byte RNG_0202f388
_08049588: .4byte 0x000343FD
_0804958C: .4byte 0x00269EC3
_08049590:
	movs r0, #9
	strb r0, [r4, #0xd]
	b _08049598
_08049596:
	strb r5, [r4, #0xd]
_08049598:
	movs r0, #0
_0804959A:
	strb r0, [r4, #0xe]
_0804959C:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start deathtanzMode3
deathtanzMode3: @ 0x080495A4
	push {r4, r5, r6, lr}
	adds r5, r0, #0
	ldrb r0, [r5, #0xe]
	cmp r0, #5
	bls _080495B0
	b _08049764
_080495B0:
	lsls r0, r0, #2
	ldr r1, _080495BC @ =_080495C0
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_080495BC: .4byte _080495C0
_080495C0: @ jump table
	.4byte _080495D8 @ case 0
	.4byte _08049658 @ case 1
	.4byte _08049694 @ case 2
	.4byte _080496AC @ case 3
	.4byte _080496EC @ case 4
	.4byte _08049704 @ case 5
_080495D8:
	adds r0, r5, #0
	adds r0, #0x74
	ldr r1, _08049604 @ =sCollisions+(24*12)
	bl SetDDP
	adds r0, r5, #0
	adds r0, #0xbc
	ldrb r0, [r0]
	lsls r0, r0, #5
	adds r0, #0x10
	lsls r6, r0, #8
	adds r0, r5, #0
	adds r0, #0xb4
	ldr r1, [r5, #0x54]
	ldr r2, [r0]
	cmp r1, r2
	bge _0804960C
	ldr r1, _08049608 @ =0xFFFF8800
	adds r0, r6, r1
	subs r6, r2, r0
	b _08049612
	.align 2, 0
_08049604: .4byte sCollisions+(24*12)
_08049608: .4byte 0xFFFF8800
_0804960C:
	ldr r1, _0804968C @ =0xFFFF8800
	adds r0, r6, r1
	adds r6, r2, r0
_08049612:
	movs r4, #0xc3
	lsls r4, r4, #3
	adds r0, r4, #0
	bl Sqrt
	adds r1, r0, #0
	ldr r0, [r5, #0x54]
	subs r0, r6, r0
	lsls r1, r1, #0x10
	lsrs r1, r1, #0xf
	bl __divsi3
	str r0, [r5, #0x5c]
	adds r0, r4, #0
	bl Sqrt
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	lsls r1, r0, #2
	adds r1, r1, r0
	lsls r1, r1, #2
	adds r1, r1, r0
	lsls r1, r1, #2
	rsbs r1, r1, #0
	lsrs r0, r1, #0x1f
	adds r1, r1, r0
	asrs r1, r1, #1
	str r1, [r5, #0x60]
	ldr r1, _08049690 @ =0x0000A70A
	adds r0, r5, #0
	bl SetMotion
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_08049658:
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x5c]
	adds r0, r0, r1
	str r0, [r5, #0x54]
	ldr r0, [r5, #0x60]
	adds r0, #0x2a
	str r0, [r5, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _08049670
	str r1, [r5, #0x60]
_08049670:
	ldr r0, [r5, #0x58]
	ldr r1, [r5, #0x60]
	adds r0, r0, r1
	str r0, [r5, #0x58]
	cmp r1, #0
	ble _08049682
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_08049682:
	adds r0, r5, #0
	bl UpdateMotionGraphic
	b _08049764
	.align 2, 0
_0804968C: .4byte 0xFFFF8800
_08049690: .4byte 0x0000A70A
_08049694:
	adds r0, r5, #0
	adds r0, #0x74
	ldr r1, _080496E4 @ =sCollisions+(24*15)
	bl SetDDP
	ldr r1, _080496E8 @ =0x0000A70B
	adds r0, r5, #0
	bl SetMotion
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_080496AC:
	adds r0, r5, #0
	bl UpdateMotionGraphic
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x5c]
	adds r0, r0, r1
	str r0, [r5, #0x54]
	ldr r0, [r5, #0x60]
	adds r0, #0x2a
	str r0, [r5, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _080496CA
	str r1, [r5, #0x60]
_080496CA:
	ldr r0, [r5, #0x58]
	ldr r1, [r5, #0x60]
	adds r0, r0, r1
	str r0, [r5, #0x58]
	adds r1, r5, #0
	adds r1, #0xb8
	ldr r1, [r1]
	cmp r0, r1
	ble _08049764
	str r1, [r5, #0x58]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	b _08049762
	.align 2, 0
_080496E4: .4byte sCollisions+(24*15)
_080496E8: .4byte 0x0000A70B
_080496EC:
	adds r0, r5, #0
	adds r0, #0x74
	ldr r1, _08049730 @ =sCollisions+(24*9)
	bl SetDDP
	ldr r1, _08049734 @ =0x0000A709
	adds r0, r5, #0
	bl SetMotion
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_08049704:
	adds r0, r5, #0
	bl UpdateMotionGraphic
	adds r0, r5, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _08049764
	ldrb r1, [r5, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	bne _08049740
	ldr r0, _08049738 @ =pZero2
	ldr r0, [r0]
	ldr r0, [r0, #0x54]
	ldr r1, [r5, #0x54]
	subs r0, r0, r1
	ldr r1, _0804973C @ =0x000045FF
	cmp r0, r1
	bls _08049750
	b _0804975C
	.align 2, 0
_08049730: .4byte sCollisions+(24*9)
_08049734: .4byte 0x0000A709
_08049738: .4byte pZero2
_0804973C: .4byte 0x000045FF
_08049740:
	ldr r0, _08049754 @ =pZero2
	ldr r1, [r0]
	ldr r0, [r5, #0x54]
	ldr r1, [r1, #0x54]
	subs r0, r0, r1
	ldr r1, _08049758 @ =0x000045FF
	cmp r0, r1
	bhi _0804975C
_08049750:
	movs r0, #4
	b _0804975E
	.align 2, 0
_08049754: .4byte pZero2
_08049758: .4byte 0x000045FF
_0804975C:
	movs r0, #5
_0804975E:
	strb r0, [r5, #0xd]
	movs r0, #0
_08049762:
	strb r0, [r5, #0xe]
_08049764:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start deathtanzMode4
deathtanzMode4: @ 0x0804976C
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #7
	bls _08049778
	b _08049894
_08049778:
	lsls r0, r0, #2
	ldr r1, _08049784 @ =_08049788
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_08049784: .4byte _08049788
_08049788: @ jump table
	.4byte _080497A8 @ case 0
	.4byte _080497CE @ case 1
	.4byte _080497C0 @ case 2
	.4byte _080497CE @ case 3
	.4byte _080497EC @ case 4
	.4byte _08049826 @ case 5
	.4byte _08049864 @ case 6
	.4byte _0804987C @ case 7
_080497A8:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _080497B8 @ =sCollisions+(24*1)
	bl SetDDP
	ldr r1, _080497BC @ =0x0000A732
	b _080497C2
	.align 2, 0
_080497B8: .4byte sCollisions+(24*1)
_080497BC: .4byte 0x0000A732
_080497C0:
	ldr r1, _080497E8 @ =0x0000A733
_080497C2:
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080497CE:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _08049894
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
	b _08049894
	.align 2, 0
_080497E8: .4byte 0x0000A733
_080497EC:
	movs r0, #0x5e
	bl PlaySound
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _08049844 @ =0x0836298C
	bl SetDDP
	movs r0, #0xe0
	lsls r0, r0, #1
	bl Sqrt
	lsls r0, r0, #0x10
	lsrs r0, r0, #0xa
	rsbs r2, r0, #0
	str r0, [r4, #0x5c]
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _08049818
	str r2, [r4, #0x5c]
_08049818:
	ldr r1, _08049848 @ =0x0000A734
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08049826:
	ldr r0, [r4, #0x54]
	ldr r2, [r4, #0x5c]
	adds r0, r0, r2
	str r0, [r4, #0x54]
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _0804984C
	adds r0, r2, #0
	adds r0, #0x40
	str r0, [r4, #0x5c]
	cmp r0, #0
	ble _0804985C
	b _08049856
	.align 2, 0
_08049844: .4byte sCollisions+(24*18)
_08049848: .4byte 0x0000A734
_0804984C:
	adds r0, r2, #0
	subs r0, #0x40
	str r0, [r4, #0x5c]
	cmp r0, #0
	bge _0804985C
_08049856:
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0804985C:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	b _08049894
_08049864:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _0804989C @ =sCollisions+(24*1)
	bl SetDDP
	ldr r1, _080498A0 @ =0x0000A735
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0804987C:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _08049894
	movs r1, #0
	movs r0, #5
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_08049894:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_0804989C: .4byte sCollisions+(24*1)
_080498A0: .4byte 0x0000A735

