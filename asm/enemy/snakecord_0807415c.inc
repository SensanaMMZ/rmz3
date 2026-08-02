	push {r4, r5, r6, r7, lr}
	adds r3, r0, #0
	ldrb r0, [r3, #0x10]
	cmp r0, #0
	bne _080741FE
	adds r0, r3, #0
	adds r0, #0x8c
	ldr r1, [r0]
	movs r2, #0x80
	lsls r2, r2, #2
	ands r1, r2
	mov ip, r0
	cmp r1, #0
	beq _080741FE
	movs r2, #0
	ldr r1, [r3, #0x28]
	ldr r4, _080741D8 @ =gEnemyFnTable
	cmp r1, #0
	beq _080741A4
	adds r7, r4, #0
	movs r6, #2
	movs r5, #1
_08074188:
	ldrb r0, [r1, #9]
	lsls r0, r0, #2
	adds r0, r0, r7
	str r6, [r1, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r1, #0x14]
	strb r5, [r1, #0xd]
	ldr r1, [r1, #0x28]
	adds r0, r2, #1
	lsls r0, r0, #0x18
	lsrs r2, r0, #0x18
	cmp r1, #0
	bne _08074188
_080741A4:
	ldrb r0, [r3, #0xd]
	subs r0, #1
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #1
	bhi _080741B4
	cmp r2, #2
	bne _080741E0
_080741B4:
	ldrb r0, [r3, #9]
	lsls r0, r0, #2
	adds r0, r0, r4
	movs r2, #2
	str r2, [r3, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r3, #0x14]
	mov r0, ip
	ldr r1, [r0]
	movs r0, #0x80
	lsls r0, r0, #0xa
	ands r1, r0
	cmp r1, #0
	beq _080741DC
	strb r2, [r3, #0xd]
	b _080741F4
	.align 2, 0
_080741D8: .4byte gEnemyFnTable
_080741DC:
	strb r1, [r3, #0xd]
	b _080741F4
_080741E0:
	ldrb r0, [r3, #9]
	lsls r0, r0, #2
	adds r0, r0, r4
	movs r1, #2
	str r1, [r3, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r3, #0x14]
	movs r0, #0
	strb r0, [r3, #0xd]
_080741F4:
	adds r0, r3, #0
	bl Snakecord_Die
	movs r0, #1
	b _08074200
_080741FE:
	movs r0, #0
_08074200:
	pop {r4, r5, r6, r7}
	pop {r1}
	bx r1
	.align 2, 0
