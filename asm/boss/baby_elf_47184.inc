	push {r4, r5, r6, lr}
	sub sp, #4
	adds r6, r0, #0
	ldr r4, [r6, #0x28]
	ldrb r0, [r6, #0xe]
	cmp r0, #5
	bls _08047194
	b _080472BA
_08047194:
	lsls r0, r0, #2
	ldr r1, _080471A0 @ =_080471A4
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_080471A0: .4byte _080471A4
_080471A4: @ jump table
	.4byte _080471BC @ case 0
	.4byte _080471F0 @ case 1
	.4byte _08047210 @ case 2
	.4byte _08047260 @ case 3
	.4byte _08047276 @ case 4
	.4byte _080472AE @ case 5
_080471BC:
	adds r1, r6, #0
	adds r1, #0xc9
	movs r0, #0
	strb r0, [r1]
	adds r2, r6, #0
	adds r2, #0xc4
	adds r0, r6, #0
	adds r0, #0xc7
	ldrb r1, [r0]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #1
	ldr r1, _080471EC @ =0x0000FFFD
	adds r0, r0, r1
	ldrh r3, [r2]
	adds r0, r0, r3
	strh r0, [r2]
	adds r0, r4, #0
	adds r0, #0xc9
	ldrb r0, [r0]
	cmp r0, #0
	beq _0804724A
	b _08047244
	.align 2, 0
_080471EC: .4byte 0x0000FFFD
_080471F0:
	adds r2, r6, #0
	adds r2, #0xc4
	movs r0, #0
	ldrsh r1, [r2, r0]
	adds r0, r1, #0
	cmp r1, #0
	bge _08047202
	ldr r3, _08047254 @ =0x000001FF
	adds r0, r1, r3
_08047202:
	asrs r0, r0, #9
	lsls r0, r0, #9
	subs r0, r1, r0
	strh r0, [r2]
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_08047210:
	adds r2, r6, #0
	adds r2, #0xc4
	adds r3, r6, #0
	adds r3, #0xc7
	ldrb r1, [r3]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #1
	ldr r1, _08047258 @ =0x0000FFFD
	adds r0, r0, r1
	ldrh r1, [r2]
	adds r0, r0, r1
	strh r0, [r2]
	lsls r0, r0, #0x10
	lsrs r1, r0, #0x10
	ldr r0, _0804725C @ =0x0000FE7F
	cmp r1, r0
	bhi _0804723A
	ldrb r0, [r3]
	cmp r0, #0
	beq _08047244
_0804723A:
	cmp r1, #0x80
	bls _0804724A
	ldrb r0, [r3]
	cmp r0, #1
	bne _0804724A
_08047244:
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_0804724A:
	adds r0, r6, #0
	bl babyelf_08045c84
	b _080472BA
	.align 2, 0
_08047254: .4byte 0x000001FF
_08047258: .4byte 0x0000FFFD
_0804725C: .4byte 0x0000FE7F
_08047260:
	movs r0, #0x8a
	lsls r0, r0, #1
	bl PlaySound
	movs r0, #0
	str r0, [r6, #0x64]
	movs r0, #8
	strb r0, [r6, #0x13]
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_08047276:
	ldrb r0, [r6, #0x13]
	subs r0, #1
	strb r0, [r6, #0x13]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080472BA
	ldr r1, [r6, #0x54]
	ldr r2, [r6, #0x58]
	adds r0, r6, #0
	adds r0, #0xc7
	ldrb r3, [r0]
	adds r0, r4, #0
	bl babyelf_0809f9f0
	movs r0, #8
	strb r0, [r6, #0x13]
	ldr r0, [r6, #0x64]
	adds r0, #1
	str r0, [r6, #0x64]
	cmp r0, #3
	ble _080472BA
	adds r1, r6, #0
	adds r1, #0xc9
	movs r0, #1
	strb r0, [r1]
	ldrb r0, [r6, #0xe]
	adds r0, #1
	b _080472B8
_080472AE:
	ldrb r0, [r4, #0xd]
	cmp r0, #5
	beq _080472BA
	movs r0, #1
	strb r0, [r6, #0xd]
_080472B8:
	strb r0, [r6, #0xe]
_080472BA:
	ldrb r0, [r6, #0x12]
	adds r0, #1
	strb r0, [r6, #0x12]
	ldrb r0, [r6, #0x12]
	movs r1, #7
	bl __umodsi3
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _08047310
	ldr r5, _08047328 @ =RNG_0202f388
	ldr r0, [r5]
	ldr r4, _0804732C @ =0x000343FD
	adds r1, r0, #0
	muls r1, r4, r1
	ldr r3, _08047330 @ =0x00269EC3
	adds r1, r1, r3
	lsls r1, r1, #1
	lsrs r2, r1, #1
	lsls r1, r1, #4
	lsrs r1, r1, #0x15
	ldr r0, _08047334 @ =0xFFFFFC00
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
_08047310:
	adds r0, r6, #0
	adds r0, #0xc6
	ldrb r0, [r0]
	bl StepPaletteAnimation
	adds r0, r6, #0
	bl UpdateMotionGraphic
	add sp, #4
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_08047328: .4byte RNG_0202f388
_0804732C: .4byte 0x000343FD
_08047330: .4byte 0x00269EC3
_08047334: .4byte 0xFFFFFC00
