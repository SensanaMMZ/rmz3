	push {r4, r5, r6, lr}
	sub sp, #0x10
	adds r4, r0, #0
	movs r5, #0x82
	lsls r5, r5, #4
	ldrb r1, [r4, #3]
	cmp r1, #1
	beq _08003408
	cmp r1, #1
	bgt _080033F2
	cmp r1, #0
	beq _080033FE
	b _08003526
_080033F2:
	cmp r1, #2
	beq _080034A0
	cmp r1, #3
	bne _080033FC
	b _08003500
_080033FC:
	b _08003526
_080033FE:
	movs r0, #3
	strh r0, [r4, #4]
	strh r1, [r4, #6]
	movs r0, #1
	strb r0, [r4, #3]
_08003408:
	ldr r0, [r4, #8]
	str r0, [r4, #0xc]
	ldrh r1, [r4, #6]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #1
	ldrb r1, [r4, #1]
	adds r0, r0, r1
	ldr r1, _08003484 @ =0x00000AAA
	muls r0, r1, r0
	movs r2, #0xe0
	lsls r2, r2, #0x14
	adds r0, r0, r2
	str r0, [r4, #0x10]
	ldr r0, [r4, #0x14]
	str r0, [r4, #0x18]
	adds r5, r0, #0
	ldr r0, _08003488 @ =sINTI
	ldr r0, [r0]
	str r0, [sp]
	movs r0, #0
	str r0, [sp, #4]
	adds r3, r5, #0
	ldrb r6, [r4, #1]
	cmp r5, #0
	beq _08003450
_0800343C:
	ldr r0, [r4, #0xc]
	ldrb r2, [r0]
	ldr r1, [sp, #4]
	adds r1, r1, r2
	str r1, [sp, #4]
	adds r0, #1
	str r0, [r4, #0xc]
	subs r5, #1
	cmp r5, #0
	bne _0800343C
_08003450:
	str r3, [sp, #8]
	mov r1, sp
	movs r0, #0xb
	strb r0, [r1, #0xc]
	movs r0, #6
	strb r0, [r1, #0xd]
	mov r0, sp
	strb r6, [r0, #0xe]
	movs r0, #1
	strb r0, [r1, #0xf]
	ldr r1, [r4, #0x10]
	mov r0, sp
	movs r2, #0x10
	bl WriteSramEx
	cmp r0, #0
	beq _08003490
	ldrh r0, [r4, #4]
	subs r0, #1
	strh r0, [r4, #4]
	ldr r1, _0800348C @ =0x0000FFFF
	adds r2, r1, #0
	lsls r0, r0, #0x10
	cmp r0, #0
	bne _08003526
	b _080034D4
	.align 2, 0
_08003484: .4byte 0x00000AAA
_08003488: .4byte sINTI
_0800348C: .4byte 0x0000FFFF
_08003490:
	ldr r0, [r4, #8]
	str r0, [r4, #0xc]
	ldr r0, [r4, #0x10]
	adds r0, #0x10
	str r0, [r4, #0x10]
	movs r0, #2
	strb r0, [r4, #3]
	b _08003526
_080034A0:
	ldr r0, [r4, #0x18]
	cmp r0, r5
	bhi _080034AC
	adds r5, r0, #0
	movs r0, #3
	strb r0, [r4, #3]
_080034AC:
	ldr r0, [r4, #0xc]
	ldr r1, [r4, #0x10]
	adds r2, r5, #0
	bl WriteSramEx
	cmp r0, #0
	beq _080034E8
	ldrh r0, [r4, #4]
	subs r0, #1
	strh r0, [r4, #4]
	ldr r1, _080034D0 @ =0x0000FFFF
	adds r2, r1, #0
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _080034D4
	movs r0, #1
	strb r0, [r4, #3]
	b _08003526
	.align 2, 0
_080034D0: .4byte 0x0000FFFF
_080034D4:
	ldr r0, _080034E4 @ =gSramState
	ldrh r1, [r0, #0x1c]
	orrs r1, r2
	strh r1, [r0, #0x1c]
	movs r0, #3
	strb r0, [r4, #3]
	b _08003526
	.align 2, 0
_080034E4: .4byte gSramState
_080034E8:
	ldr r0, [r4, #0xc]
	movs r1, #0x82
	lsls r1, r1, #4
	adds r0, r0, r1
	str r0, [r4, #0xc]
	ldr r0, [r4, #0x10]
	adds r0, r0, r1
	str r0, [r4, #0x10]
	ldr r0, [r4, #0x18]
	subs r0, r0, r5
	str r0, [r4, #0x18]
	b _08003526
_08003500:
	ldrh r0, [r4, #6]
	cmp r0, #0
	bne _08003512
	strh r1, [r4, #4]
	movs r1, #1
	movs r0, #1
	strh r0, [r4, #6]
	strb r1, [r4, #3]
	b _08003526
_08003512:
	ldr r1, _08003530 @ =gSramState
	movs r2, #0x1c
	ldrsh r0, [r1, r2]
	cmp r0, #0
	bne _08003520
	movs r0, #1
	strh r0, [r1, #0x1c]
_08003520:
	movs r0, #0
	strb r0, [r4]
	strh r0, [r4, #2]
_08003526:
	add sp, #0x10
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_08003530: .4byte gSramState
