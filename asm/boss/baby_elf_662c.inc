	push {r4, r5, r6, lr}
	sub sp, #4
	adds r6, r0, #0
	ldrb r4, [r6, #0xe]
	cmp r4, #0
	beq _0804663E
	cmp r4, #1
	beq _080466C4
	b _0804679A
_0804663E:
	movs r1, #0xc4
	lsls r1, r1, #6
	adds r0, r6, #0
	bl SetMotion
	adds r1, r6, #0
	adds r1, #0xbc
	ldr r0, [r6, #0x54]
	str r0, [r1]
	adds r1, #4
	ldr r0, [r6, #0x58]
	str r0, [r1]
	strb r4, [r6, #0x12]
	adds r0, r6, #0
	adds r0, #0xc4
	strh r4, [r0]
	ldrb r0, [r6, #0x10]
	cmp r0, #0
	bne _08046686
	adds r0, r6, #0
	bl GetEntityPalID
	adds r1, r0, #0
	lsls r1, r1, #0x18
	lsrs r1, r1, #0x13
	movs r2, #0x80
	lsls r2, r2, #2
	adds r0, r2, #0
	orrs r1, r0
	movs r0, #0x14
	bl StartPaletteAnimation
	adds r1, r6, #0
	adds r1, #0xc6
	movs r0, #0x14
	b _080466A6
_08046686:
	adds r0, r6, #0
	bl GetEntityPalID
	adds r1, r0, #0
	lsls r1, r1, #0x18
	lsrs r1, r1, #0x13
	movs r2, #0x80
	lsls r2, r2, #2
	adds r0, r2, #0
	orrs r1, r0
	movs r0, #0xf
	bl StartPaletteAnimation
	adds r1, r6, #0
	adds r1, #0xc6
	movs r0, #0xf
_080466A6:
	strb r0, [r1]
	movs r2, #0
	adds r0, r6, #0
	adds r0, #0xb4
	ldr r1, [r6, #0x54]
	ldr r0, [r0]
	cmp r1, r0
	ble _080466B8
	movs r2, #1
_080466B8:
	adds r0, r6, #0
	adds r0, #0xc7
	strb r2, [r0]
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_080466C4:
	adds r0, r6, #0
	adds r0, #0x74
	ldr r1, _080467A4 @ =0x08362674
	bl SetDDP
	adds r2, r6, #0
	adds r2, #0xc4
	adds r3, r6, #0
	adds r3, #0xc7
	ldrb r1, [r3]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #1
	ldr r1, _080467A8 @ =0x0000FFFD
	adds r0, r0, r1
	ldrh r1, [r2]
	adds r4, r0, r1
	strh r4, [r2]
	ldrb r0, [r6, #0x10]
	cmp r0, #0
	bne _0804672E
	ldr r0, _080467AC @ =pZero2
	ldr r1, [r0]
	adds r0, r1, #0
	adds r0, #0x8c
	ldr r0, [r0]
	movs r2, #0x80
	lsls r2, r2, #2
	ands r0, r2
	cmp r0, #0
	bne _0804672E
	adds r0, r1, #0
	adds r0, #0xa4
	movs r1, #0
	ldrsh r0, [r0, r1]
	cmp r0, #0
	beq _0804672E
	lsls r0, r4, #0x10
	lsrs r1, r0, #0x10
	ldr r0, _080467B0 @ =0x0000FDFF
	cmp r1, r0
	bhi _0804671E
	ldrb r0, [r3]
	cmp r0, #0
	beq _08046728
_0804671E:
	cmp r1, r2
	bls _0804672E
	ldrb r0, [r3]
	cmp r0, #1
	bne _0804672E
_08046728:
	adds r0, r6, #0
	bl babyelf_08045bc4
_0804672E:
	adds r0, r6, #0
	bl babyelf_08045c84
	ldrb r0, [r6, #0x12]
	adds r0, #1
	strb r0, [r6, #0x12]
	ldrb r0, [r6, #0x12]
	movs r1, #7
	bl __umodsi3
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _0804678A
	ldr r5, _080467B4 @ =RNG_0202f388
	ldr r0, [r5]
	ldr r4, _080467B8 @ =0x000343FD
	adds r1, r0, #0
	muls r1, r4, r1
	ldr r3, _080467BC @ =0x00269EC3
	adds r1, r1, r3
	lsls r1, r1, #1
	lsrs r2, r1, #1
	lsls r1, r1, #4
	lsrs r1, r1, #0x15
	ldr r0, _080467C0 @ =0xFFFFFC00
	adds r1, r1, r0
	ldr r0, [r6, #0x54]
	adds r0, r0, r1
	muls r2, r4, r2
	adds r2, r2, r3
	lsls r2, r2, #1
	lsrs r1, r2, #1
	str r1, [r5]
	lsls r2, r2, #5
	lsrs r2, r2, #0x16
	movs r1, #0x80
	lsls r1, r1, #4
	adds r2, r2, r1
	ldr r1, [r6, #0x58]
	adds r1, r1, r2
	ldrb r2, [r6, #0x10]
	str r2, [sp]
	movs r2, #0
	movs r3, #0
	bl FUN_080bc594
_0804678A:
	adds r0, r6, #0
	adds r0, #0xc6
	ldrb r0, [r0]
	bl StepPaletteAnimation
	adds r0, r6, #0
	bl UpdateMotionGraphic
_0804679A:
	add sp, #4
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_080467A4: .4byte 0x08362674
_080467A8: .4byte 0x0000FFFD
_080467AC: .4byte pZero2
_080467B0: .4byte 0x0000FDFF
_080467B4: .4byte RNG_0202f388
_080467B8: .4byte 0x000343FD
_080467BC: .4byte 0x00269EC3
_080467C0: .4byte 0xFFFFFC00
