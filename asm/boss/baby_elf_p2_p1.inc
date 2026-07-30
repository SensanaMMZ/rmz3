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
