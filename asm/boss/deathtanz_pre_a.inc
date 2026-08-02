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
