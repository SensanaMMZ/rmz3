	push {r4, r5, r6, r7, lr}
	mov r7, sl
	mov r6, sb
	mov r5, r8
	push {r5, r6, r7}
	sub sp, #0x10
	adds r6, r0, #0
	mov sb, r1
	mov sl, r2
	ldr r0, [r6, #0x54]
	subs r1, r1, r0
	mov sb, r1
	ldr r0, [r6, #0x58]
	subs r2, r2, r0
	mov sl, r2
	asrs r0, r1, #8
	adds r5, r0, #0
	muls r5, r0, r5
	asrs r0, r2, #8
	adds r1, r0, #0
	muls r1, r0, r1
	adds r0, r1, #0
	adds r5, r5, r0
	adds r0, r5, #0
	bl Sqrt
	lsls r0, r0, #0x10
	lsrs r5, r0, #8
	ldr r2, [r6, #0x54]
	mov r8, r2
	ldr r7, [r6, #0x58]
	cmp r5, #0
	beq _080824FA
	mov r1, sb
	lsls r0, r1, #8
	adds r1, r5, #0
	bl __divsi3
	adds r4, r0, #0
	lsls r2, r4, #2
	mov r8, r2
	ldr r0, [r6, #0x54]
	add r8, r0
	mov r1, sl
	lsls r0, r1, #8
	adds r1, r5, #0
	bl __divsi3
	lsls r7, r0, #2
	ldr r1, [r6, #0x58]
	adds r7, r7, r1
	lsls r4, r4, #3
	mov r2, sb
	subs r2, r2, r4
	mov sb, r2
	lsls r0, r0, #3
	mov r1, sl
	subs r1, r1, r0
	mov sl, r1
_080824FA:
	ldr r4, [r6, #0x2c]
	adds r1, r6, #0
	adds r1, #0xb4
	ldrb r0, [r1]
	cmp r0, #1
	bne _08082522
	mov r2, sb
	asrs r2, r2, #8
	str r2, [sp]
	mov r0, sl
	asrs r0, r0, #8
	str r0, [sp, #4]
	adds r6, #0x24
	str r6, [sp, #8]
	cmp r4, #0
	beq _08082572
	mov r1, r8
	str r1, [r4, #0x54]
	str r7, [r4, #0x58]
	b _08082572
_08082522:
	mov r2, sb
	asrs r2, r2, #8
	str r2, [sp]
	mov r0, sl
	asrs r0, r0, #8
	str r0, [sp, #4]
	adds r6, #0x24
	str r6, [sp, #8]
	cmp r4, #0
	beq _08082572
	adds r5, r1, #0
	movs r1, #0
	str r1, [sp, #0xc]
	movs r6, #0
_0808253E:
	mov r2, r8
	str r2, [r4, #0x54]
	ldrb r1, [r5]
	subs r1, #1
	adds r0, r6, #0
	bl __divsi3
	add r0, r8
	str r0, [r4, #0x54]
	str r0, [r4, #0x64]
	str r7, [r4, #0x58]
	ldrb r1, [r5]
	subs r1, #1
	ldr r0, [sp, #0xc]
	bl __divsi3
	adds r0, r7, r0
	str r0, [r4, #0x58]
	str r0, [r4, #0x68]
	ldr r0, [sp, #0xc]
	add r0, sl
	str r0, [sp, #0xc]
	add r6, sb
	ldr r4, [r4, #0x2c]
	cmp r4, #0
	bne _0808253E
_08082572:
	ldr r1, [sp]
	lsls r0, r1, #0x10
	asrs r0, r0, #0x10
	ldr r2, [sp, #4]
	lsls r1, r2, #0x10
	asrs r1, r1, #0x10
	bl ArcTan2
	lsrs r0, r0, #8
	ldr r1, [sp, #8]
	strb r0, [r1]
	add sp, #0x10
	pop {r3, r4, r5}
	mov r8, r3
	mov sb, r4
	mov sl, r5
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
