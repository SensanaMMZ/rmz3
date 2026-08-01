	push {r4, r5, r6, lr}
	adds r5, r0, #0
	ldrb r0, [r5, #0xe]
	cmp r0, #0
	beq _0809469C
	cmp r0, #1
	beq _08094714
	b _080947B8
_0809469C:
	adds r2, r5, #0
	adds r2, #0xb8
	ldr r0, [r2]
	movs r1, #2
	rsbs r1, r1, #0
	ands r0, r1
	str r0, [r2]
	ldr r1, _080946CC @ =0x00008E06
	adds r0, r5, #0
	bl SetMotion
	adds r2, r5, #0
	adds r2, #0xbd
	ldrb r1, [r2]
	movs r0, #1
	adds r3, r0, #0
	eors r3, r1
	adds r6, r2, #0
	cmp r3, #0
	beq _080946D0
	ldrb r1, [r5, #0xa]
	movs r0, #0x10
	orrs r0, r1
	b _080946D6
	.align 2, 0
_080946CC: .4byte 0x00008E06
_080946D0:
	ldrb r1, [r5, #0xa]
	movs r0, #0xef
	ands r0, r1
_080946D6:
	strb r0, [r5, #0xa]
	movs r1, #1
	ands r1, r3
	adds r0, r5, #0
	adds r0, #0x4c
	movs r4, #0
	strb r1, [r0]
	adds r3, r5, #0
	adds r3, #0x4a
	lsls r1, r1, #4
	ldrb r2, [r3]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r1
	strb r0, [r3]
	movs r1, #0x80
	lsls r1, r1, #1
	str r1, [r5, #0x5c]
	ldrb r0, [r6]
	lsls r0, r0, #9
	subs r1, r1, r0
	str r1, [r5, #0x5c]
	adds r0, r5, #0
	bl UpdateMotionGraphic
	str r4, [r5, #0x60]
	strb r4, [r5, #0x12]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_08094714:
	ldr r1, [r5, #0x5c]
	adds r0, r5, #0
	bl FUN_08093a98
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _0809479A
	movs r4, #0
	ldr r0, [r5, #0x60]
	ldr r1, [r5, #0x5c]
	adds r2, r0, r1
	str r2, [r5, #0x60]
	movs r3, #0x80
	lsls r3, r3, #1
	adds r6, r1, #0
	cmp r2, r3
	ble _08094744
	ldr r1, _08094740 @ =0xFFFFFF00
	adds r0, r2, r1
	str r0, [r5, #0x60]
	b _08094754
	.align 2, 0
_08094740: .4byte 0xFFFFFF00
_08094744:
	ldr r0, _08094774 @ =0xFFFFFF00
	cmp r2, r0
	bge _08094750
	adds r0, r2, r3
	str r0, [r5, #0x60]
	movs r4, #1
_08094750:
	cmp r4, #0
	beq _0809479A
_08094754:
	ldrb r0, [r5, #0x12]
	movs r1, #7
	ands r0, r1
	strb r0, [r5, #0x12]
	movs r2, #0
	cmp r6, #0
	ble _08094764
	movs r2, #1
_08094764:
	ldrb r1, [r5, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _08094778
	cmp r2, #0
	beq _0809477C
	b _08094782
	.align 2, 0
_08094774: .4byte 0xFFFFFF00
_08094778:
	cmp r2, #0
	beq _08094782
_0809477C:
	ldrb r0, [r5, #0x12]
	subs r0, #1
	b _08094786
_08094782:
	ldrb r0, [r5, #0x12]
	adds r0, #1
_08094786:
	strb r0, [r5, #0x12]
	ldr r1, _080947C0 @ =0x00008E06
	ldrb r2, [r5, #0x12]
	adds r0, r5, #0
	movs r3, #1
	bl GotoMotion
	adds r0, r5, #0
	bl UpdateMotionGraphic
_0809479A:
	adds r0, r5, #0
	movs r1, #1
	bl FUN_08093a64
	lsls r0, r0, #0x18
	lsrs r2, r0, #0x18
	cmp r2, #0
	bne _080947B8
	adds r0, r5, #0
	adds r0, #0xbc
	movs r1, #2
	strb r1, [r0]
	movs r0, #5
	strb r0, [r5, #0xd]
	strb r2, [r5, #0xe]
_080947B8:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_080947C0: .4byte 0x00008E06
