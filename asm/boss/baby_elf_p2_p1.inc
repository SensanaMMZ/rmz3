	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start babyelf_08046154
babyelf_08046154: @ 0x08046154
	push {r4, r5, r6, r7, lr}
	mov r7, r8
	push {r7}
	sub sp, #4
	adds r6, r0, #0
	ldr r0, [r6, #0x28]
	mov r8, r0
	ldrb r0, [r6, #0xe]
	cmp r0, #9
	bls _0804616A
	b _08046618
_0804616A:
	lsls r0, r0, #2
	ldr r1, _08046174 @ =_08046178
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_08046174: .4byte _08046178
_08046178: @ jump table
	.4byte _080461A0 @ case 0
	.4byte _080461C8 @ case 1
	.4byte _08046618 @ case 2
	.4byte _08046618 @ case 3
	.4byte _0804633C @ case 4
	.4byte _0804636E @ case 5
	.4byte _08046410 @ case 6
	.4byte _08046472 @ case 7
	.4byte _080464A0 @ case 8
	.4byte _08046530 @ case 9
_080461A0:
	movs r1, #0xc0
	lsls r1, r1, #6
	adds r0, r6, #0
	bl SetMotion
	adds r0, r6, #0
	adds r0, #0xc4
	movs r4, #0
	strh r4, [r0]
	adds r0, r6, #0
	bl babyelf_08045c84
	ldr r0, [r6, #0x54]
	str r0, [r6, #0x64]
	ldr r0, [r6, #0x58]
	str r0, [r6, #0x68]
	str r4, [r6, #0x5c]
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_080461C8:
	adds r4, r6, #0
	adds r4, #0xc4
	ldrb r1, [r6, #0x10]
	lsls r1, r1, #2
	subs r1, #2
	ldrh r0, [r4]
	subs r0, r0, r1
	strh r0, [r4]
	ldrh r0, [r4]
	ldr r1, _08046240 @ =0x000001FF
	ands r0, r1
	strh r0, [r4]
	ldr r0, [r6, #0x54]
	str r0, [r6, #0x64]
	ldr r0, [r6, #0x58]
	str r0, [r6, #0x68]
	adds r0, r6, #0
	bl babyelf_08045c84
	ldrb r2, [r6, #0x10]
	cmp r2, #0
	bne _08046200
	ldr r0, [r6, #0x18]
	ldrb r1, [r0, #9]
	movs r0, #0x80
	ands r0, r1
	cmp r0, #0
	bne _08046212
_08046200:
	cmp r2, #1
	bne _08046248
	mov r1, r8
	ldr r0, [r1, #0x18]
	ldrb r1, [r0, #9]
	movs r0, #0x40
	ands r0, r1
	cmp r0, #0
	beq _08046248
_08046212:
	ldr r3, _08046244 @ =gSineTable
	ldr r2, [r6, #0x5c]
	lsls r0, r2, #0x18
	lsrs r0, r0, #0x17
	adds r0, r0, r3
	movs r5, #0
	ldrsh r1, [r0, r5]
	lsls r1, r1, #1
	ldr r0, [r6, #0x54]
	adds r0, r0, r1
	str r0, [r6, #0x54]
	lsls r0, r2, #0x19
	lsrs r0, r0, #0x17
	adds r0, r0, r3
	movs r3, #0
	ldrsh r1, [r0, r3]
	lsls r1, r1, #1
	ldr r0, [r6, #0x58]
	adds r0, r0, r1
	str r0, [r6, #0x58]
	adds r2, #0x20
	str r2, [r6, #0x5c]
	b _0804624C
	.align 2, 0
_08046240: .4byte 0x000001FF
_08046244: .4byte gSineTable
_08046248:
	movs r0, #0
	str r0, [r6, #0x5c]
_0804624C:
	adds r0, r6, #0
	bl UpdateMotionGraphic
	ldrh r0, [r4]
	adds r1, r6, #0
	adds r1, #0xd1
	ldrb r2, [r1]
	lsls r1, r2, #2
	adds r1, r1, r2
	lsls r1, r1, #1
	adds r1, #7
	bl __modsi3
	cmp r0, #0
	bne _080462B2
	ldr r5, [r6, #0x58]
	mov ip, r5
	ldr r0, [r6, #0x68]
	subs r0, r5, r0
	lsls r7, r0, #1
	cmp r7, #0
	bge _0804627A
	movs r7, #0
_0804627A:
	ldr r5, _080462D0 @ =RNG_0202f388
	ldr r0, [r5]
	ldr r4, _080462D4 @ =0x000343FD
	adds r1, r0, #0
	muls r1, r4, r1
	ldr r3, _080462D8 @ =0x00269EC3
	adds r1, r1, r3
	lsls r1, r1, #1
	lsrs r2, r1, #1
	lsls r1, r1, #4
	lsrs r1, r1, #0x15
	ldr r0, _080462DC @ =0xFFFFFC00
	adds r1, r1, r0
	ldr r0, [r6, #0x54]
	adds r0, r0, r1
	adds r1, r2, #0
	muls r1, r4, r1
	adds r1, r1, r3
	lsls r1, r1, #1
	lsrs r2, r1, #1
	str r2, [r5]
	lsls r1, r1, #5
	lsrs r1, r1, #0x16
	add r1, ip
	movs r2, #0
	adds r3, r7, #0
	bl FUN_080bc540
_080462B2:
	ldrb r1, [r6, #0x10]
	cmp r1, #1
	bne _08046300
	mov r3, r8
	ldrb r2, [r3, #0x11]
	cmp r2, #2
	bne _080462F0
	ldr r0, [r3, #0x18]
	ldrb r1, [r0, #9]
	ands r2, r1
	cmp r2, #0
	beq _080462E0
	movs r1, #0
	movs r0, #0x11
	b _08046322
	.align 2, 0
_080462D0: .4byte RNG_0202f388
_080462D4: .4byte 0x000343FD
_080462D8: .4byte 0x00269EC3
_080462DC: .4byte 0xFFFFFC00
_080462E0:
	movs r0, #4
	ands r0, r1
	cmp r0, #0
	bne _080462EA
	b _08046618
_080462EA:
	movs r0, #0x12
	strb r0, [r6, #0xd]
	b _08046616
_080462F0:
	mov r5, r8
	ldr r0, [r5, #0x18]
	ldrb r0, [r0, #9]
	ands r1, r0
	cmp r1, #0
	bne _080462FE
	b _08046618
_080462FE:
	b _08046336
_08046300:
	ldrb r1, [r6, #0x11]
	cmp r1, #2
	bne _08046328
	ldr r0, [r6, #0x18]
	ldrb r2, [r0, #9]
	ands r1, r2
	cmp r1, #0
	beq _08046316
	movs r1, #0
	movs r0, #0x11
	b _08046322
_08046316:
	movs r0, #4
	ands r0, r2
	cmp r0, #0
	bne _08046320
	b _08046618
_08046320:
	movs r0, #0x12
_08046322:
	strb r0, [r6, #0xd]
	strb r1, [r6, #0xe]
	b _08046618
_08046328:
	ldr r0, [r6, #0x18]
	ldrb r1, [r0, #9]
	movs r0, #1
	ands r0, r1
	cmp r0, #0
	bne _08046336
	b _08046618
_08046336:
	movs r0, #4
	strb r0, [r6, #0xe]
	b _08046618
_0804633C:
	movs r0, #0
	str r0, [r6, #0x5c]
	str r0, [r6, #0x60]
	adds r0, r6, #0
	bl GetEntityPalID
	adds r1, r0, #0
	lsls r1, r1, #0x18
	lsrs r1, r1, #0x13
	movs r2, #0x80
	lsls r2, r2, #2
	adds r0, r2, #0
	orrs r1, r0
	movs r0, #0xc
	bl StartPaletteAnimation
	adds r1, r6, #0
	adds r1, #0xc6
	movs r0, #0xc
	strb r0, [r1]
	movs r0, #0x50
	strb r0, [r6, #0x12]
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_0804636E:
	adds r0, r6, #0
	adds r0, #0xb4
	ldr r0, [r0]
	ldr r5, [r6, #0x54]
	subs r2, r0, r5
	ldr r3, _0804640C @ =0xFFFFA800
	adds r2, r2, r3
	ldrb r1, [r6, #0x10]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	subs r0, r0, r1
	lsls r0, r0, #0xc
	adds r2, r2, r0
	adds r0, r6, #0
	adds r0, #0xb8
	ldr r4, [r6, #0x58]
	movs r3, #0xa0
	lsls r3, r3, #7
	adds r1, r4, r3
	ldr r0, [r0]
	subs r3, r0, r1
	adds r0, r2, #0
	cmp r2, #0
	bge _080463A2
	adds r0, #0x1f
_080463A2:
	asrs r2, r0, #5
	adds r0, r3, #0
	cmp r3, #0
	bge _080463AC
	adds r0, #0x1f
_080463AC:
	asrs r3, r0, #5
	ldr r1, [r6, #0x5c]
	subs r0, r2, r1
	cmp r0, #0
	bge _080463B8
	adds r0, #0xf
_080463B8:
	asrs r0, r0, #4
	adds r1, r1, r0
	str r1, [r6, #0x5c]
	ldr r2, [r6, #0x60]
	subs r0, r3, r2
	cmp r0, #0
	bge _080463C8
	adds r0, #0xf
_080463C8:
	asrs r0, r0, #4
	adds r0, r2, r0
	str r0, [r6, #0x60]
	adds r1, r5, r1
	str r1, [r6, #0x54]
	adds r0, r4, r0
	str r0, [r6, #0x58]
	adds r0, r6, #0
	bl UpdateMotionGraphic
	adds r4, r6, #0
	adds r4, #0xc6
	ldrb r0, [r4]
	bl StepPaletteAnimation
	ldrb r0, [r6, #0x12]
	subs r0, #1
	strb r0, [r6, #0x12]
	lsls r0, r0, #0x18
	lsrs r5, r0, #0x18
	cmp r5, #0
	beq _080463F6
	b _08046618
_080463F6:
	ldrb r0, [r4]
	cmp r0, #0
	beq _08046402
	bl RemovePaletteAnimation
	strb r5, [r4]
_08046402:
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
	b _08046618
	.align 2, 0
_0804640C: .4byte 0xFFFFA800
_08046410:
	ldrb r0, [r6, #0x10]
	adds r1, r6, #0
	adds r1, #0x22
	strb r0, [r1]
	movs r1, #0xc4
	lsls r1, r1, #6
	adds r0, r6, #0
	bl SetMotion
	ldrb r0, [r6, #0x10]
	cmp r0, #0
	bne _0804644A
	adds r0, r6, #0
	bl GetEntityPalID
	adds r1, r0, #0
	lsls r1, r1, #0x18
	lsrs r1, r1, #0x13
	movs r5, #0x80
	lsls r5, r5, #2
	adds r0, r5, #0
	orrs r1, r0
	movs r0, #0x13
	bl StartPaletteAnimation
	adds r1, r6, #0
	adds r1, #0xc6
	movs r0, #0x13
	b _0804646A
_0804644A:
	adds r0, r6, #0
	bl GetEntityPalID
	adds r1, r0, #0
	lsls r1, r1, #0x18
	lsrs r1, r1, #0x13
	movs r2, #0x80
	lsls r2, r2, #2
	adds r0, r2, #0
	orrs r1, r0
	movs r0, #0xe
	bl StartPaletteAnimation
	adds r1, r6, #0
	adds r1, #0xc6
	movs r0, #0xe
_0804646A:
	strb r0, [r1]
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_08046472:
	adds r4, r6, #0
	adds r4, #0xc6
	ldrb r0, [r4]
	bl StepPaletteAnimation
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #3
	bne _08046498
	ldrb r0, [r4]
	cmp r0, #0
	beq _08046492
	bl RemovePaletteAnimation
	movs r0, #0
	strb r0, [r4]
_08046492:
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_08046498:
	adds r0, r6, #0
	bl UpdateMotionGraphic
	b _08046618
_080464A0:
	movs r4, #0
	adds r5, r6, #0
	adds r5, #0xbc
	adds r7, r6, #0
	adds r7, #0xc0
_080464AA:
	ldr r0, [r6, #0x54]
	ldr r1, [r6, #0x58]
	lsls r3, r4, #0x1d
	lsrs r3, r3, #0x18
	ldrb r2, [r6, #0x10]
	str r2, [sp]
	movs r2, #0x80
	lsls r2, r2, #1
	bl FUN_080bc7a4
	adds r4, #1
	cmp r4, #7
	ble _080464AA
	movs r1, #0xc4
	lsls r1, r1, #6
	adds r0, r6, #0
	bl SetMotion
	ldr r0, [r6, #0x54]
	str r0, [r5]
	ldr r0, [r6, #0x58]
	str r0, [r7]
	movs r1, #0
	strb r1, [r6, #0x12]
	adds r0, r6, #0
	adds r0, #0xc4
	strh r1, [r0]
	ldrb r0, [r6, #0x10]
	cmp r0, #0
	bne _08046508
	adds r0, r6, #0
	bl GetEntityPalID
	adds r1, r0, #0
	lsls r1, r1, #0x18
	lsrs r1, r1, #0x13
	movs r3, #0x80
	lsls r3, r3, #2
	adds r0, r3, #0
	orrs r1, r0
	movs r0, #0x14
	bl StartPaletteAnimation
	adds r1, r6, #0
	adds r1, #0xc6
	movs r0, #0x14
	b _08046528
_08046508:
	adds r0, r6, #0
	bl GetEntityPalID
	adds r1, r0, #0
	lsls r1, r1, #0x18
	lsrs r1, r1, #0x13
	movs r5, #0x80
	lsls r5, r5, #2
	adds r0, r5, #0
	orrs r1, r0
	movs r0, #0xf
	bl StartPaletteAnimation
	adds r1, r6, #0
	adds r1, #0xc6
	movs r0, #0xf
_08046528:
	strb r0, [r1]
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_08046530:
	adds r7, r6, #0
	adds r7, #0xc4
	ldrb r1, [r6, #0x10]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #1
	ldr r1, _080465D4 @ =0x0000FFFD
	adds r0, r0, r1
	ldrh r2, [r7]
	adds r0, r0, r2
	strh r0, [r7]
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
	bne _080465A2
	ldr r5, _080465D8 @ =RNG_0202f388
	ldr r0, [r5]
	ldr r4, _080465DC @ =0x000343FD
	adds r1, r0, #0
	muls r1, r4, r1
	ldr r3, _080465E0 @ =0x00269EC3
	adds r1, r1, r3
	lsls r1, r1, #1
	lsrs r2, r1, #1
	lsls r1, r1, #4
	lsrs r1, r1, #0x15
	ldr r0, _080465E4 @ =0xFFFFFC00
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
_080465A2:
	adds r0, r6, #0
	adds r0, #0xc6
	ldrb r0, [r0]
	bl StepPaletteAnimation
	adds r0, r6, #0
	bl UpdateMotionGraphic
	ldrb r2, [r6, #0x10]
	cmp r2, #1
	bne _080465F0
	ldr r0, _080465E8 @ =gStageRun
	ldrb r1, [r0, #0x12]
	adds r0, r2, #0
	ands r0, r1
	cmp r0, #0
	bne _08046618
	movs r3, #0
	ldrsh r1, [r7, r3]
	adds r0, r1, #0
	cmp r1, #0
	bge _0804660C
	ldr r5, _080465EC @ =0x000001FF
	adds r0, r1, r5
	b _0804660C
	.align 2, 0
_080465D4: .4byte 0x0000FFFD
_080465D8: .4byte RNG_0202f388
_080465DC: .4byte 0x000343FD
_080465E0: .4byte 0x00269EC3
_080465E4: .4byte 0xFFFFFC00
_080465E8: .4byte gStageRun
_080465EC: .4byte 0x000001FF
_080465F0:
	ldr r0, _08046624 @ =gStageRun
	ldrb r1, [r0, #0x12]
	movs r2, #1
	adds r0, r2, #0
	ands r0, r1
	cmp r0, #0
	bne _08046618
	movs r0, #0
	ldrsh r1, [r7, r0]
	adds r0, r1, #0
	cmp r1, #0
	bge _0804660C
	ldr r3, _08046628 @ =0x000001FF
	adds r0, r1, r3
_0804660C:
	asrs r0, r0, #9
	lsls r0, r0, #9
	subs r0, r1, r0
	strh r0, [r7]
	strb r2, [r6, #0xd]
_08046616:
	strb r2, [r6, #0xe]
_08046618:
	add sp, #4
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_08046624: .4byte gStageRun
_08046628: .4byte 0x000001FF

	thumb_func_start babyelf_0804662c
babyelf_0804662c: @ 0x0804662C
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

	thumb_func_start babyelf_080467c4
babyelf_080467c4: @ 0x080467C4
	push {r4, r5, r6, lr}
	sub sp, #4
	adds r6, r0, #0
	ldrb r0, [r6, #0xe]
	cmp r0, #5
	bls _080467D2
	b _08046A02
_080467D2:
	lsls r0, r0, #2
	ldr r1, _080467E4 @ =0x080467E8
	adds r0, r0, r1
	ldr r0, [r0]
	adds r2, r6, #0
	adds r2, #0xc4
	adds r5, r6, #0
	adds r5, #0xc7
	mov pc, r0
	.align 2, 0
_080467E4: .4byte 0x080467E8
_080467E8:
	.byte 0x00, 0x68, 0x04, 0x08, 0x10, 0x68, 0x04, 0x08
	.byte 0x58, 0x68, 0x04, 0x08, 0xE4, 0x68, 0x04, 0x08, 0x68, 0x69, 0x04, 0x08, 0xB4, 0x69, 0x04, 0x08
	.byte 0x31, 0x1C, 0xC4, 0x31, 0x00, 0x20, 0x08, 0x80, 0xB0, 0x7B, 0x01, 0x30, 0xB0, 0x73, 0x0A, 0x1C
	.byte 0x33, 0x1C, 0xC7, 0x33, 0x18, 0x78, 0x41, 0x00, 0x09, 0x18, 0x49, 0x00, 0x0C, 0x48, 0x09, 0x18
	.byte 0x10, 0x88, 0x09, 0x18, 0x11, 0x80, 0x09, 0x04, 0x09, 0x0C, 0x0A, 0x48, 0x81, 0x42, 0x02, 0xD8
	.byte 0x18, 0x78, 0x00, 0x28, 0x04, 0xD0, 0x80, 0x29, 0x05, 0xD9, 0x18, 0x78, 0x01, 0x28, 0x02, 0xD1
	.byte 0xB0, 0x7B, 0x01, 0x30, 0xB0, 0x73, 0x30, 0x1C, 0xFF, 0xF7, 0x1C, 0xFA, 0x80, 0xE0, 0x00, 0x00
	.byte 0xFD, 0xFF, 0x00, 0x00, 0x7F, 0xFF, 0x00, 0x00, 0x09, 0x4A, 0x11, 0x68, 0x09, 0x48, 0x48, 0x43
	.byte 0x09, 0x49, 0x40, 0x18, 0x40, 0x00, 0x41, 0x08, 0x11, 0x60, 0x40, 0x0C, 0x01, 0x21, 0x08, 0x40
	.byte 0x00, 0x28, 0x0B, 0xD0, 0x8A, 0x20, 0x40, 0x00, 0xBD, 0xF7, 0x92, 0xFE, 0x09, 0xE0, 0x00, 0x00
	.byte 0x88, 0xF3, 0x02, 0x02, 0xFD, 0x43, 0x03, 0x00, 0xC3, 0x9E, 0x26, 0x00, 0x0B, 0x48, 0xBD, 0xF7
	.byte 0x87, 0xFE, 0x32, 0x1C, 0xC4, 0x32, 0x00, 0x20, 0x10, 0x80, 0x33, 0x1C, 0xC0, 0x33, 0xB0, 0x6D
	.byte 0x18, 0x60, 0xB0, 0x24, 0x24, 0x02, 0xF4, 0x65, 0x30, 0x1C, 0xC7, 0x30, 0x01, 0x78, 0x05, 0x1C
	.byte 0x00, 0x29, 0x07, 0xD1, 0x18, 0x68, 0x02, 0x49, 0x09, 0xE0, 0x00, 0x00, 0x15, 0x01, 0x00, 0x00
	.byte 0x00, 0xE8, 0xFF, 0xFF, 0x60, 0x42, 0xF0, 0x65, 0x18, 0x68, 0xC0, 0x21, 0x49, 0x01, 0x40, 0x18
	.byte 0x18, 0x60, 0xF0, 0x6D, 0x00, 0x28, 0x00, 0xDA, 0x7F, 0x30, 0xC0, 0x11, 0xF0, 0x65, 0xB0, 0x7B
	.byte 0x01, 0x30, 0xB0, 0x73, 0x70, 0x6D, 0xF1, 0x6D, 0x40, 0x18, 0x70, 0x65, 0x30, 0x1C, 0xC0, 0x30
	.byte 0x00, 0x68, 0xB0, 0x65, 0x10, 0x88, 0x04, 0x30, 0x10, 0x80, 0x00, 0x04, 0x0B, 0x49, 0x88, 0x42
	.byte 0x02, 0xD9, 0xB0, 0x7B, 0x01, 0x30, 0xB0, 0x73, 0x28, 0x78, 0x00, 0x28, 0x12, 0xD1, 0x08, 0x49
	.byte 0x10, 0x78, 0x40, 0x30, 0x00, 0x06, 0xC0, 0x0D, 0x40, 0x18, 0x00, 0x21, 0x40, 0x5E, 0x41, 0x00
	.byte 0x09, 0x18, 0xC9, 0x00, 0xB0, 0x6D, 0x40, 0x18, 0x11, 0xE0, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x01
	.byte 0x74, 0xEA, 0x0F, 0x08, 0x0B, 0x49, 0x10, 0x78, 0x40, 0x30, 0x00, 0x06, 0xC0, 0x0D, 0x40, 0x18
	.byte 0x00, 0x21, 0x40, 0x5E, 0x41, 0x00, 0x09, 0x18, 0xC9, 0x00, 0xB0, 0x6D, 0x40, 0x1A, 0xB0, 0x65
	.byte 0x30, 0x1C, 0xC6, 0x30, 0x00, 0x78, 0xBD, 0xF7, 0x87, 0xFB, 0x30, 0x1C, 0xD0, 0xF7, 0x7E, 0xFE
	.byte 0x4F, 0xE0, 0x00, 0x00, 0x74, 0xEA, 0x0F, 0x08, 0x31, 0x1C, 0xBC, 0x31, 0x70, 0x6D, 0x08, 0x60
	.byte 0x33, 0x1C, 0xC0, 0x33, 0xB0, 0x6D, 0x18, 0x60, 0x32, 0x1C, 0xC7, 0x32, 0x10, 0x78, 0x01, 0x21
	.byte 0x48, 0x40, 0x10, 0x70, 0x15, 0x1C, 0x00, 0x28, 0x08, 0xD1, 0x18, 0x68, 0x80, 0x21, 0x89, 0x01
	.byte 0x40, 0x18, 0x18, 0x60, 0x31, 0x1C, 0xC4, 0x31, 0x80, 0x20, 0x06, 0xE0, 0x18, 0x68, 0x30, 0x49
	.byte 0x40, 0x18, 0x18, 0x60, 0x31, 0x1C, 0xC4, 0x31, 0x2E, 0x48, 0x08, 0x80, 0x0A, 0x1C, 0xB0, 0x7B
	.byte 0x01, 0x30, 0xB0, 0x73, 0x2B, 0x1C, 0x19, 0x78, 0x48, 0x00, 0x40, 0x18, 0x40, 0x00, 0x03, 0x38
	.byte 0x11, 0x88, 0x09, 0x1A, 0x11, 0x80, 0x09, 0x04, 0x09, 0x0C, 0x80, 0x20, 0x40, 0x00, 0x81, 0x42
	.byte 0x02, 0xD9, 0x18, 0x78, 0x00, 0x28, 0x05, 0xD0, 0x23, 0x48, 0x81, 0x42, 0x06, 0xD8, 0x28, 0x78
	.byte 0x01, 0x28, 0x03, 0xD1, 0x00, 0x21, 0x01, 0x20, 0x70, 0x73, 0xB1, 0x73, 0x30, 0x1C, 0xFF, 0xF7
	.byte 0x49, 0xF9, 0x30, 0x1C, 0xC6, 0x30, 0x00, 0x78, 0xBD, 0xF7, 0x36, 0xFB, 0x30, 0x1C, 0xD0, 0xF7
	.byte 0x2D, 0xFE
_08046A02:
	ldrb r0, [r6, #0x12]
	adds r0, #1
	strb r0, [r6, #0x12]
	ldrb r0, [r6, #0x12]
	movs r1, #7
	bl __umodsi3
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _08046A58
	ldr r5, _08046A6C @ =RNG_0202f388
	ldr r0, [r5]
	ldr r4, _08046A70 @ =0x000343FD
	adds r1, r0, #0
	muls r1, r4, r1
	ldr r3, _08046A74 @ =0x00269EC3
	adds r1, r1, r3
	lsls r1, r1, #1
	lsrs r2, r1, #1
	lsls r1, r1, #4
	lsrs r1, r1, #0x15
	ldr r0, _08046A78 @ =0xFFFFFC00
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
_08046A58:
	add sp, #4
	pop {r4, r5, r6}
	pop {r0}
	bx r0
_08046A60:
	.byte 0x00, 0xE0, 0xFF, 0xFF, 0x80, 0xFF, 0x00, 0x00, 0xFF, 0xFE, 0x00, 0x00
_08046A6C: .4byte RNG_0202f388
_08046A70: .4byte 0x000343FD
_08046A74: .4byte 0x00269EC3
_08046A78: .4byte 0xFFFFFC00

	thumb_func_start babyelf_08046a7c
babyelf_08046a7c: @ 0x08046A7C
	push {r4, r5, r6, r7, lr}
	adds r4, r0, #0
	ldrb r5, [r4, #0xe]
	cmp r5, #1
	beq _08046AFC
	cmp r5, #1
	bgt _08046A90
	cmp r5, #0
	beq _08046A9C
	b _08046CBE
_08046A90:
	cmp r5, #2
	beq _08046B58
	cmp r5, #3
	bne _08046A9A
	b _08046C3E
_08046A9A:
	b _08046CBE
_08046A9C:
	adds r6, r4, #0
	adds r6, #0xc6
	ldrb r0, [r6]
	cmp r0, #0
	beq _08046AAC
	bl RemovePaletteAnimation
	strb r5, [r6]
_08046AAC:
	ldrb r0, [r4, #0x10]
	cmp r0, #0
	bne _08046AD0
	adds r0, r4, #0
	bl GetEntityPalID
	adds r1, r0, #0
	lsls r1, r1, #0x18
	lsrs r1, r1, #0x13
	movs r2, #0x80
	lsls r2, r2, #2
	adds r0, r2, #0
	orrs r1, r0
	movs r0, #0x15
	bl StartPaletteAnimation
	movs r0, #0x15
	b _08046AEC
_08046AD0:
	adds r0, r4, #0
	bl GetEntityPalID
	adds r1, r0, #0
	lsls r1, r1, #0x18
	lsrs r1, r1, #0x13
	movs r3, #0x80
	lsls r3, r3, #2
	adds r0, r3, #0
	orrs r1, r0
	movs r0, #0x10
	bl StartPaletteAnimation
	movs r0, #0x10
_08046AEC:
	strb r0, [r6]
	adds r1, r4, #0
	adds r1, #0xc4
	movs r0, #0
	strh r0, [r1]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08046AFC:
	adds r2, r4, #0
	adds r2, #0xc4
	adds r3, r4, #0
	adds r3, #0xc7
	ldrb r1, [r3]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #1
	ldr r1, _08046B50 @ =0x0000FFFD
	adds r0, r0, r1
	ldrh r1, [r2]
	adds r0, r0, r1
	strh r0, [r2]
	lsls r0, r0, #0x10
	lsrs r1, r0, #0x10
	ldr r0, _08046B54 @ =0x0000FF7F
	cmp r1, r0
	bhi _08046B26
	ldrb r0, [r3]
	cmp r0, #0
	beq _08046B30
_08046B26:
	cmp r1, #0x80
	bls _08046B36
	ldrb r0, [r3]
	cmp r0, #1
	bne _08046B36
_08046B30:
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08046B36:
	adds r0, r4, #0
	bl babyelf_08045c84
	adds r0, r4, #0
	adds r0, #0xc6
	ldrb r0, [r0]
	bl StepPaletteAnimation
	adds r0, r4, #0
	bl UpdateMotionGraphic
	b _08046CBE
	.align 2, 0
_08046B50: .4byte 0x0000FFFD
_08046B54: .4byte 0x0000FF7F
_08046B58:
	movs r0, #0x8b
	lsls r0, r0, #1
	bl PlaySound
	adds r0, r4, #0
	adds r0, #0xc8
	movs r6, #0
	strb r6, [r0]
	adds r0, r4, #0
	movs r1, #0
	bl FUN_080bc5fc
	adds r5, r4, #0
	adds r5, #0xc6
	ldrb r0, [r5]
	cmp r0, #0
	beq _08046B80
	bl RemovePaletteAnimation
	strb r6, [r5]
_08046B80:
	adds r0, r4, #0
	adds r0, #0x22
	strb r6, [r0]
	ldr r1, _08046BEC @ =0x00003301
	adds r0, r4, #0
	bl SetMotion
	ldrb r6, [r4, #0x10]
	cmp r6, #0
	bne _08046BC2
	adds r0, r4, #0
	bl GetEntityPalID
	adds r1, r0, #0
	lsls r1, r1, #0x18
	lsrs r1, r1, #0x13
	movs r2, #0x80
	lsls r2, r2, #2
	adds r0, r2, #0
	orrs r1, r0
	movs r0, #0x18
	bl StartPaletteAnimation
	movs r0, #0x18
	strb r0, [r5]
	bl StepPaletteAnimation
	ldrb r0, [r5]
	cmp r0, #0
	beq _08046BC2
	bl RemovePaletteAnimation
	strb r6, [r5]
_08046BC2:
	adds r0, r4, #0
	adds r0, #0xc7
	ldrb r0, [r0]
	cmp r0, #0
	bne _08046BF4
	ldr r2, _08046BF0 @ =gSineTable
	adds r0, r2, #0
	adds r0, #0xa0
	movs r3, #0
	ldrsh r1, [r0, r3]
	lsls r0, r1, #3
	subs r0, r0, r1
	lsls r0, r0, #7
	cmp r0, #0
	bge _08046BE2
	adds r0, #0xff
_08046BE2:
	asrs r0, r0, #8
	str r0, [r4, #0x5c]
	movs r0, #0x20
	ldrsh r1, [r2, r0]
	b _08046C1A
	.align 2, 0
_08046BEC: .4byte 0x00003301
_08046BF0: .4byte gSineTable
_08046BF4:
	ldr r2, _08046CC4 @ =gSineTable
	movs r1, #0xd8
	lsls r1, r1, #1
	adds r0, r2, r1
	movs r3, #0
	ldrsh r1, [r0, r3]
	lsls r0, r1, #3
	subs r0, r0, r1
	lsls r0, r0, #7
	cmp r0, #0
	bge _08046C0C
	adds r0, #0xff
_08046C0C:
	asrs r0, r0, #8
	str r0, [r4, #0x5c]
	movs r1, #0x98
	lsls r1, r1, #1
	adds r0, r2, r1
	movs r2, #0
	ldrsh r1, [r0, r2]
_08046C1A:
	lsls r0, r1, #3
	subs r0, r0, r1
	lsls r0, r0, #7
	cmp r0, #0
	bge _08046C26
	adds r0, #0xff
_08046C26:
	asrs r0, r0, #8
	rsbs r0, r0, #0
	str r0, [r4, #0x60]
	movs r0, #0xa
	strb r0, [r4, #0x12]
	movs r0, #0x1a
	strb r0, [r4, #0x13]
	movs r0, #0x5a
	str r0, [r4, #0x64]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08046C3E:
	ldr r0, [r4, #0x64]
	subs r1, r0, #1
	str r1, [r4, #0x64]
	cmp r1, #0
	bne _08046C4E
	movs r0, #4
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_08046C4E:
	ldrb r0, [r4, #0x10]
	cmp r0, #0
	bne _08046CA8
	ldrb r0, [r4, #0x12]
	cmp r0, #0
	beq _08046C78
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _08046C78
	adds r0, r4, #0
	adds r0, #0xb4
	ldr r0, [r0]
	adds r1, r4, #0
	adds r1, #0xb8
	ldr r1, [r1]
	ldr r3, _08046CC8 @ =0xFFFFB000
	adds r1, r1, r3
	bl FUN_080bc660
_08046C78:
	ldrb r0, [r4, #0x13]
	cmp r0, #0
	beq _08046CA8
	subs r0, #1
	strb r0, [r4, #0x13]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _08046CA8
	movs r5, #0
	adds r7, r4, #0
	adds r7, #0xb4
	adds r6, r4, #0
	adds r6, #0xb8
_08046C92:
	ldr r0, [r7]
	ldr r1, [r6]
	ldr r2, _08046CC8 @ =0xFFFFB000
	adds r1, r1, r2
	lsls r2, r5, #0x1d
	lsrs r2, r2, #0x18
	bl FUN_0809f8fc
	adds r5, #1
	cmp r5, #7
	ble _08046C92
_08046CA8:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	ldr r0, [r4, #0x58]
	ldr r1, [r4, #0x60]
	adds r0, r0, r1
	str r0, [r4, #0x58]
	adds r0, r4, #0
	bl UpdateMotionGraphic
_08046CBE:
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_08046CC4: .4byte gSineTable
_08046CC8: .4byte 0xFFFFB000
