	push {r4, r5, r6, r7, lr}
	ldr r1, _080E98E4 @ =gTextPrinter
	movs r2, #0xb1
	lsls r2, r2, #3
	adds r0, r1, r2
	ldr r2, [r0]
	ldr r7, _080E98E8 @ =0x0000058C
	adds r1, r1, r7
	cmp r2, #0
	beq _080E9888
	ldr r3, [r1]
_080E987A:
	ldr r0, [r2]
	str r3, [r2]
	adds r3, r2, #0
	adds r2, r0, #0
	cmp r2, #0
	bne _080E987A
	str r3, [r1]
_080E9888:
	ldr r3, _080E98E4 @ =gTextPrinter
	movs r1, #0xb1
	lsls r1, r1, #3
	adds r0, r3, r1
	movs r1, #0
	str r1, [r0]
	movs r5, #0
	movs r2, #4
	ldrsh r0, [r3, r2]
	cmp r5, r0
	bge _080E98D6
	adds r6, r3, #0
_080E98A0:
	movs r7, #0xc4
	lsls r7, r7, #1
	adds r0, r6, r7
	adds r0, r5, r0
	ldrb r0, [r0]
	movs r2, #0xf4
	lsls r2, r2, #1
	adds r1, r6, r2
	adds r1, r5, r1
	ldrb r1, [r1]
	lsls r2, r5, #2
	adds r3, r6, #0
	adds r3, #8
	adds r2, r2, r3
	ldr r2, [r2]
	lsls r3, r5, #1
	adds r7, #0xc0
	adds r4, r6, r7
	adds r3, r3, r4
	ldrh r3, [r3]
	bl printStringWithLen
	adds r5, #1
	movs r1, #4
	ldrsh r0, [r6, r1]
	cmp r5, r0
	blt _080E98A0
_080E98D6:
	ldr r1, _080E98E4 @ =gTextPrinter
	movs r0, #0
	strh r0, [r1, #4]
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080E98E4: .4byte gTextPrinter
_080E98E8: .4byte 0x0000058C
