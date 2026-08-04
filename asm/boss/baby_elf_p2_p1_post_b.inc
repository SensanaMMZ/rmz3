	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start babyelf_08047338
babyelf_08047338: @ 0x08047338
	push {r4, r5, r6, r7, lr}
	sub sp, #4
	adds r6, r0, #0
	ldrb r0, [r6, #0xe]
	cmp r0, #4
	bls _08047346
	b _08047518
_08047346:
	lsls r0, r0, #2
	ldr r1, _08047350 @ =_08047354
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_08047350: .4byte _08047354
_08047354: @ jump table
	.4byte _08047368 @ case 0
	.4byte _08047376 @ case 1
	.4byte _080473C0 @ case 2
	.4byte _080473EE @ case 3
	.4byte _080474F4 @ case 4
_08047368:
	adds r1, r6, #0
	adds r1, #0xc4
	movs r0, #0
	strh r0, [r1]
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_08047376:
	adds r2, r6, #0
	adds r2, #0xc4
	adds r3, r6, #0
	adds r3, #0xc7
	ldrb r1, [r3]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #1
	ldr r1, _080473B8 @ =0x0000FFFD
	adds r0, r0, r1
	ldrh r4, [r2]
	adds r0, r0, r4
	strh r0, [r2]
	lsls r0, r0, #0x10
	lsrs r1, r0, #0x10
	ldr r0, _080473BC @ =0x0000FF7F
	cmp r1, r0
	bhi _080473A0
	ldrb r0, [r3]
	cmp r0, #0
	beq _080473AA
_080473A0:
	cmp r1, #0x80
	bls _080473B0
	ldrb r0, [r3]
	cmp r0, #1
	bne _080473B0
_080473AA:
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_080473B0:
	adds r0, r6, #0
	bl babyelf_08045c84
	b _08047518
	.align 2, 0
_080473B8: .4byte 0x0000FFFD
_080473BC: .4byte 0x0000FF7F
_080473C0:
	movs r0, #0
	strb r0, [r6, #0x13]
	str r0, [r6, #0x5c]
	ldr r0, [r6, #0x54]
	str r0, [r6, #0x64]
	adds r1, r6, #0
	adds r1, #0xb4
	ldr r1, [r1]
	subs r0, r0, r1
	str r0, [r6, #0x64]
	ldr r0, [r6, #0x58]
	str r0, [r6, #0x68]
	movs r1, #0xa0
	lsls r1, r1, #7
	adds r0, r0, r1
	adds r1, r6, #0
	adds r1, #0xb8
	ldr r1, [r1]
	subs r0, r0, r1
	str r0, [r6, #0x68]
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_080473EE:
	ldrb r0, [r6, #0x10]
	cmp r0, #0
	bne _08047416
	ldrb r0, [r6, #0x13]
	adds r0, #1
	strb r0, [r6, #0x13]
	ldrb r0, [r6, #0x13]
	movs r1, #0x1f
	ands r0, r1
	strb r0, [r6, #0x13]
	cmp r0, #0xf
	bhi _0804740E
	adds r1, r6, #0
	adds r1, #0x25
	movs r0, #0x19
	b _08047414
_0804740E:
	adds r1, r6, #0
	adds r1, #0x25
	movs r0, #0x18
_08047414:
	strb r0, [r1]
_08047416:
	ldr r7, [r6, #0x5c]
	asrs r0, r7, #8
	lsls r0, r0, #0x18
	ldr r2, _080474DC @ =gSineTable
	lsrs r1, r0, #0x18
	movs r3, #0x80
	lsls r3, r3, #0x17
	adds r0, r0, r3
	lsrs r0, r0, #0x17
	adds r0, r0, r2
	movs r4, #0
	ldrsh r5, [r0, r4]
	ldr r4, [r6, #0x64]
	adds r0, r5, #0
	muls r0, r4, r0
	cmp r0, #0
	bge _0804743A
	adds r0, #0xff
_0804743A:
	asrs r3, r0, #8
	lsls r0, r1, #1
	adds r0, r0, r2
	movs r2, #0
	ldrsh r1, [r0, r2]
	ldr r2, [r6, #0x68]
	adds r0, r1, #0
	muls r0, r2, r0
	cmp r0, #0
	bge _08047450
	adds r0, #0xff
_08047450:
	asrs r0, r0, #8
	adds r3, r3, r0
	adds r0, r1, #0
	muls r0, r4, r0
	cmp r0, #0
	bge _0804745E
	adds r0, #0xff
_0804745E:
	asrs r0, r0, #8
	rsbs r1, r0, #0
	adds r0, r5, #0
	muls r0, r2, r0
	cmp r0, #0
	bge _0804746C
	adds r0, #0xff
_0804746C:
	asrs r0, r0, #8
	adds r2, r1, r0
	adds r0, r7, #0
	adds r0, #0x14
	str r0, [r6, #0x5c]
	str r3, [r6, #0x64]
	str r2, [r6, #0x68]
	adds r0, r6, #0
	adds r0, #0xb4
	ldr r0, [r0]
	adds r0, r0, r3
	str r0, [r6, #0x54]
	adds r0, r6, #0
	adds r0, #0xb8
	ldr r4, _080474E0 @ =0xFFFFB000
	adds r1, r2, r4
	ldr r0, [r0]
	adds r0, r0, r1
	str r0, [r6, #0x58]
	lsls r0, r3, #5
	subs r0, r0, r3
	lsls r0, r0, #3
	cmp r0, #0
	bge _0804749E
	adds r0, #0xff
_0804749E:
	asrs r3, r0, #8
	str r3, [r6, #0x64]
	lsls r0, r2, #5
	subs r0, r0, r2
	lsls r0, r0, #3
	cmp r0, #0
	bge _080474AE
	adds r0, #0xff
_080474AE:
	asrs r1, r0, #8
	str r1, [r6, #0x68]
	movs r2, #0x80
	lsls r2, r2, #2
	adds r0, r3, r2
	ldr r2, _080474E4 @ =0x000003FF
	cmp r0, r2
	bhi _08047518
	movs r3, #0x80
	lsls r3, r3, #2
	adds r0, r1, r3
	cmp r0, r2
	bhi _08047518
	ldrb r4, [r6, #0x10]
	cmp r4, #0
	bne _080474EC
	ldr r0, _080474E8 @ =0x00000117
	bl PlaySound
	movs r0, #8
	strb r0, [r6, #0xd]
	strb r4, [r6, #0xe]
	b _08047518
	.align 2, 0
_080474DC: .4byte gSineTable
_080474E0: .4byte 0xFFFFB000
_080474E4: .4byte 0x000003FF
_080474E8: .4byte 0x00000117
_080474EC:
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
	b _08047518
_080474F4:
	ldrb r1, [r6, #0xa]
	movs r0, #0xfe
	ands r0, r1
	strb r0, [r6, #0xa]
	adds r0, r6, #0
	adds r0, #0x74
	ldr r1, _0804758C @ =sCollisions
	bl SetDDP
	adds r4, r6, #0
	adds r4, #0xc6
	ldrb r0, [r4]
	cmp r0, #0
	beq _08047518
	bl RemovePaletteAnimation
	movs r0, #0
	strb r0, [r4]
_08047518:
	ldrb r0, [r6, #0xe]
	cmp r0, #4
	beq _08047584
	ldrb r0, [r6, #0x12]
	adds r0, #1
	strb r0, [r6, #0x12]
	ldrb r0, [r6, #0x12]
	movs r1, #7
	bl __umodsi3
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _08047574
	ldr r5, _08047590 @ =RNG_0202f388
	ldr r0, [r5]
	ldr r4, _08047594 @ =0x000343FD
	adds r1, r0, #0
	muls r1, r4, r1
	ldr r3, _08047598 @ =0x00269EC3
	adds r1, r1, r3
	lsls r1, r1, #1
	lsrs r2, r1, #1
	lsls r1, r1, #4
	lsrs r1, r1, #0x15
	ldr r0, _0804759C @ =0xFFFFFC00
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
_08047574:
	adds r0, r6, #0
	adds r0, #0xc6
	ldrb r0, [r0]
	bl StepPaletteAnimation
	adds r0, r6, #0
	bl UpdateMotionGraphic
_08047584:
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_0804758C: .4byte sCollisions
_08047590: .4byte RNG_0202f388
_08047594: .4byte 0x000343FD
_08047598: .4byte 0x00269EC3
_0804759C: .4byte 0xFFFFFC00
