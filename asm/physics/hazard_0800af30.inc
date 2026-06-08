	push {r4, r5, r6, r7, lr}
	mov r7, sl
	mov r6, sb
	mov r5, r8
	push {r5, r6, r7}
	sub sp, #4
	str r0, [sp]
	adds r7, r1, #0
	adds r5, r2, #0
	cmp r5, r7
	bge _0800AF4E
	adds r1, r5, #0
	bl CalcPushout_Up
	b _0800AFC0
_0800AF4E:
	subs r0, r5, r7
	asrs r0, r0, #1
	mov sl, r0
	add r7, sl
	ldr r0, _0800AFD0 @ =gOverworld
	movs r2, #0xe9
	lsls r2, r2, #1
	adds r1, r0, r2
	ldrb r1, [r1]
	cmp r1, #0
	beq _0800AFBE
	movs r3, #0xf0
	lsls r3, r3, #1
	adds r3, r3, r0
	mov sb, r3
	adds r2, #0xa
	adds r2, r2, r0
	mov r8, r2
	mov ip, r0
	adds r6, r1, #0
_0800AF76:
	movs r0, #0xec
	lsls r0, r0, #1
	add r0, ip
	ldrh r1, [r0]
	lsls r2, r1, #1
	mov r3, r8
	ldr r0, [r3]
	ldr r3, [sp]
	subs r0, r3, r0
	adds r0, r0, r1
	cmp r2, r0
	bls _0800AFB0
	movs r0, #0xed
	lsls r0, r0, #1
	add r0, ip
	ldrh r4, [r0]
	mov r1, sl
	adds r0, r4, r1
	lsls r2, r0, #1
	mov r1, sb
	ldr r3, [r1]
	subs r1, r7, r3
	adds r1, r1, r0
	cmp r2, r1
	bls _0800AFB0
	subs r0, r3, r4
	cmp r5, r0
	ble _0800AFB0
	adds r5, r0, #0
_0800AFB0:
	movs r2, #0x18
	add sb, r2
	add r8, r2
	add ip, r2
	subs r6, #1
	cmp r6, #0
	bne _0800AF76
_0800AFBE:
	adds r0, r5, #0
_0800AFC0:
	add sp, #4
	pop {r3, r4, r5}
	mov r8, r3
	mov sb, r4
	mov sl, r5
	pop {r4, r5, r6, r7}
	pop {r1}
	bx r1
	.align 2, 0
_0800AFD0: .4byte gOverworld
