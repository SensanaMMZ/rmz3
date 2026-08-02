	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_08062588
FUN_08062588: @ 0x08062588
	push {r4, r5, r6, r7, lr}
	adds r5, r0, #0
	ldr r6, [r5, #0x28]
	ldr r7, [r5, #0x2c]
	ldrb r4, [r5, #0xe]
	cmp r4, #0
	beq _0806259C
	cmp r4, #1
	beq _080625B0
	b _0806266E
_0806259C:
	ldr r1, _080625F0 @ =0x0000D60D
	adds r0, r5, #0
	bl SetMotion
	strb r4, [r5, #0x12]
	movs r0, #1
	strb r0, [r5, #0x13]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_080625B0:
	ldrb r0, [r5, #0x12]
	cmp r0, #0
	bne _080625F8
	ldrb r0, [r5, #0x13]
	cmp r0, #0
	bne _080625D2
	adds r0, r5, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _080625D2
	ldr r1, _080625F0 @ =0x0000D60D
	adds r0, r5, #0
	bl SetMotion
	movs r0, #1
	strb r0, [r5, #0x13]
_080625D2:
	adds r0, r6, #0
	adds r0, #0xbc
	ldr r1, [r0]
	movs r2, #2
	ands r1, r2
	adds r6, r0, #0
	cmp r1, #0
	beq _08062614
	ldr r1, _080625F4 @ =0x0000D60E
	adds r0, r5, #0
	bl SetMotion
	movs r0, #1
	strb r0, [r5, #0x12]
	b _08062614
	.align 2, 0
_080625F0: .4byte 0x0000D60D
_080625F4: .4byte 0x0000D60E
_080625F8:
	adds r1, r6, #0
	adds r1, #0xbc
	ldr r4, [r1]
	movs r0, #2
	ands r4, r0
	adds r6, r1, #0
	cmp r4, #0
	bne _08062614
	ldr r1, _08062674 @ =0x0000D60F
	adds r0, r5, #0
	bl SetMotion
	strb r4, [r5, #0x12]
	strb r4, [r5, #0x13]
_08062614:
	adds r0, r5, #0
	bl UpdateMotionGraphic
	ldr r1, [r6]
	movs r0, #1
	ands r0, r1
	cmp r0, #0
	beq _08062634
	movs r0, #2
	rsbs r0, r0, #0
	ands r1, r0
	str r1, [r6]
	movs r1, #0
	movs r0, #6
	strb r0, [r5, #0xd]
	strb r1, [r5, #0xe]
_08062634:
	ldr r1, [r7, #0x54]
	str r1, [r5, #0x54]
	ldr r4, _08062678 @ =gSineTable
	adds r2, r7, #0
	adds r2, #0xb8
	ldrh r0, [r2]
	lsrs r0, r0, #8
	lsls r0, r0, #1
	adds r0, r0, r4
	movs r3, #0
	ldrsh r0, [r0, r3]
	movs r3, #0xb
	muls r0, r3, r0
	adds r1, r1, r0
	str r1, [r5, #0x54]
	ldr r1, [r7, #0x58]
	str r1, [r5, #0x58]
	ldrh r0, [r2]
	lsls r0, r0, #0x10
	asrs r0, r0, #0x18
	adds r0, #0x40
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x17
	adds r0, r0, r4
	movs r2, #0
	ldrsh r0, [r0, r2]
	muls r0, r3, r0
	subs r1, r1, r0
	str r1, [r5, #0x58]
_0806266E:
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_08062674: .4byte 0x0000D60F
_08062678: .4byte gSineTable

	thumb_func_start FUN_0806267c
FUN_0806267c: @ 0x0806267C
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #1
	beq _080626AA
	cmp r0, #1
	bgt _08062690
	cmp r0, #0
	beq _08062696
	b _0806274C
_08062690:
	cmp r0, #2
	beq _080626B4
	b _0806274C
_08062696:
	adds r0, r4, #0
	adds r0, #0xbc
	ldr r0, [r0]
	movs r1, #0x20
	ands r0, r1
	cmp r0, #0
	bne _0806274C
	movs r0, #1
	strb r0, [r4, #0xe]
	b _0806274C
_080626AA:
	movs r0, #0x78
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080626B4:
	ldr r0, _080626D4 @ =pZero2
	ldr r0, [r0]
	ldr r3, [r0, #0x54]
	ldr r2, [r4, #0x54]
	subs r0, r3, r2
	movs r1, #0xc0
	lsls r1, r1, #7
	adds r0, r0, r1
	ldr r1, _080626D8 @ =0x0000BFFF
	cmp r0, r1
	bhi _080626DC
	movs r0, #0
	strb r0, [r4, #0xd]
	strb r0, [r4, #0xe]
	b _0806274C
	.align 2, 0
_080626D4: .4byte pZero2
_080626D8: .4byte 0x0000BFFF
_080626DC:
	movs r5, #0
	cmp r2, r3
	ble _08062704
	ldr r1, _08062700 @ =0xFFFFEA00
	adds r0, r2, r1
	ldr r1, [r4, #0x58]
	movs r2, #0x80
	lsls r2, r2, #3
	adds r1, r1, r2
	bl FUN_080098a4
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _08062724
	ldr r0, [r4, #0x54]
	subs r0, #0x80
	str r0, [r4, #0x54]
	b _08062726
	.align 2, 0
_08062700: .4byte 0xFFFFEA00
_08062704:
	movs r1, #0xb0
	lsls r1, r1, #5
	adds r0, r2, r1
	ldr r1, [r4, #0x58]
	movs r2, #0x80
	lsls r2, r2, #3
	adds r1, r1, r2
	bl FUN_080098a4
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _08062724
	ldr r0, [r4, #0x54]
	adds r0, #0x80
	str r0, [r4, #0x54]
	b _08062726
_08062724:
	movs r5, #1
_08062726:
	ldrb r0, [r4, #0x12]
	subs r0, #1
	movs r1, #0
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _08062738
	cmp r5, #0
	beq _0806273C
_08062738:
	strb r1, [r4, #0xd]
	strb r1, [r4, #0xe]
_0806273C:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	bl FUN_08009f6c
	str r0, [r4, #0x58]
_0806274C:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start FUN_08062754
FUN_08062754: @ 0x08062754
	push {r4, r5, lr}
	adds r4, r0, #0
	ldr r5, [r4, #0x28]
	ldr r0, [r5, #0x54]
	str r0, [r4, #0x54]
	ldr r0, [r5, #0x58]
	ldr r1, _08062778 @ =0xFFFFEE00
	adds r0, r0, r1
	str r0, [r4, #0x58]
	ldrb r0, [r4, #0xe]
	cmp r0, #1
	beq _08062794
	cmp r0, #1
	bgt _0806277C
	cmp r0, #0
	beq _08062786
	b _0806283C
	.align 2, 0
_08062778: .4byte 0xFFFFEE00
_0806277C:
	cmp r0, #2
	beq _080627B0
	cmp r0, #3
	beq _08062824
	b _0806283C
_08062786:
	ldr r1, _080627AC @ =0x0000D605
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08062794:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _0806283C
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
	b _0806283C
	.align 2, 0
_080627AC: .4byte 0x0000D605
_080627B0:
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
	movs r2, #0x4a
	adds r2, r2, r4
	mov ip, r2
	lsls r3, r1, #4
	ldrb r2, [r2]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r3
	mov r2, ip
	strb r0, [r2]
	cmp r1, #0
	beq _080627EA
	ldrb r0, [r4, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _080627F0
_080627EA:
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
_080627F0:
	strb r0, [r4, #0xa]
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _08062808
	adds r0, r5, #0
	adds r0, #0xbc
	ldr r1, [r0]
	movs r2, #8
	orrs r1, r2
	b _08062814
_08062808:
	adds r0, r5, #0
	adds r0, #0xbc
	ldr r1, [r0]
	movs r2, #9
	rsbs r2, r2, #0
	ands r1, r2
_08062814:
	str r1, [r0]
	ldr r1, _08062844 @ =0x0000D606
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08062824:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _0806283C
	movs r1, #0
	movs r0, #2
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_0806283C:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_08062844: .4byte 0x0000D606

	thumb_func_start FUN_08062848
FUN_08062848: @ 0x08062848
	push {r4, r5, r6, lr}
	adds r6, r0, #0
	ldr r2, [r6, #0x2c]
	ldr r1, [r2, #0x54]
	str r1, [r6, #0x54]
	ldr r5, _08062898 @ =gSineTable
	adds r3, r2, #0
	adds r3, #0xb8
	ldrh r0, [r3]
	lsrs r0, r0, #8
	lsls r0, r0, #1
	adds r0, r0, r5
	movs r4, #0
	ldrsh r0, [r0, r4]
	movs r4, #0xb
	muls r0, r4, r0
	adds r1, r1, r0
	str r1, [r6, #0x54]
	ldr r1, [r2, #0x58]
	str r1, [r6, #0x58]
	ldrh r0, [r3]
	lsls r0, r0, #0x10
	asrs r0, r0, #0x18
	adds r0, #0x40
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x17
	adds r0, r0, r5
	movs r2, #0
	ldrsh r0, [r0, r2]
	muls r0, r4, r0
	subs r1, r1, r0
	str r1, [r6, #0x58]
	ldrb r0, [r6, #0xe]
	cmp r0, #1
	beq _080628B4
	cmp r0, #1
	bgt _0806289C
	cmp r0, #0
	beq _080628A6
	b _08062932
	.align 2, 0
_08062898: .4byte gSineTable
_0806289C:
	cmp r0, #2
	beq _080628D0
	cmp r0, #3
	beq _0806291C
	b _08062932
_080628A6:
	ldr r1, _080628CC @ =0x0000D60E
	adds r0, r6, #0
	bl SetMotion
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_080628B4:
	adds r0, r6, #0
	bl UpdateMotionGraphic
	adds r0, r6, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _08062932
	ldrb r0, [r6, #0xe]
	adds r0, #1
	b _08062930
	.align 2, 0
_080628CC: .4byte 0x0000D60E
_080628D0:
	ldrb r0, [r6, #0xa]
	lsrs r0, r0, #4
	movs r2, #1
	eors r0, r2
	ands r0, r2
	adds r1, r6, #0
	adds r1, #0x4c
	strb r0, [r1]
	ldrb r1, [r6, #0xa]
	lsrs r1, r1, #4
	eors r1, r2
	ands r1, r2
	adds r4, r6, #0
	adds r4, #0x4a
	lsls r3, r1, #4
	ldrb r2, [r4]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r3
	strb r0, [r4]
	cmp r1, #0
	beq _08062906
	ldrb r0, [r6, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _0806290C
_08062906:
	ldrb r1, [r6, #0xa]
	movs r0, #0xef
	ands r0, r1
_0806290C:
	strb r0, [r6, #0xa]
	ldr r1, _08062938 @ =0x0000D60F
	adds r0, r6, #0
	bl SetMotion
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_0806291C:
	adds r0, r6, #0
	bl UpdateMotionGraphic
	adds r0, r6, #0
	adds r0, #0x73
	ldrb r1, [r0]
	cmp r1, #3
	bne _08062932
	movs r0, #0
	strb r1, [r6, #0xd]
_08062930:
	strb r0, [r6, #0xe]
_08062932:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_08062938: .4byte 0x0000D60F

