	push {r4, r5, r6, r7, lr}
	mov r7, sb
	mov r6, r8
	push {r6, r7}
	sub sp, #8
	ldr r2, [r0, #0x2c]
	ldrb r1, [r2, #0x10]
	cmp r1, #1
	bne _08061D5C
	ldr r0, [r0, #0x14]
	movs r1, #8
	ands r0, r1
	cmp r0, #0
	beq _08061DF8
	movs r3, #0
	ldr r0, _08061D58 @ =pZero2
	ldr r0, [r0]
	ldr r1, [r2, #0x54]
	ldr r0, [r0, #0x54]
	cmp r1, r0
	bge _08061D50
	movs r3, #1
_08061D50:
	adds r0, r2, #0
	adds r0, #0xc0
	strb r3, [r0]
	b _08061DF8
	.align 2, 0
_08061D58: .4byte pZero2
_08061D5C:
	cmp r1, #0
	bne _08061DF8
	ldr r0, [r0, #0x14]
	movs r1, #1
	ands r0, r1
	cmp r0, #0
	beq _08061DF8
	movs r3, #0
	ldr r0, _08061E08 @ =pZero2
	ldr r0, [r0]
	ldr r1, [r2, #0x54]
	ldr r0, [r0, #0x54]
	cmp r1, r0
	bge _08061D7A
	movs r3, #1
_08061D7A:
	adds r0, r2, #0
	adds r0, #0xc0
	strb r3, [r0]
	subs r0, #4
	ldr r1, [r0]
	movs r0, #2
	ands r1, r0
	adds r7, r2, #0
	adds r7, #0xa4
	movs r0, #0xc1
	adds r0, r0, r2
	mov sb, r0
	cmp r1, #0
	beq _08061DF2
	ldrh r0, [r7]
	lsls r0, r0, #1
	mov r3, sb
	ldrb r1, [r3]
	subs r0, r0, r1
	strh r0, [r7]
	ldr r1, [r2, #0x54]
	ldr r4, _08061E0C @ =0xFFFFF800
	adds r1, r1, r4
	ldr r3, _08061E10 @ =RNG_0202f388
	ldr r0, [r3]
	ldr r4, _08061E14 @ =0x000343FD
	mov r8, r4
	mov r4, r8
	muls r4, r0, r4
	adds r0, r4, #0
	ldr r6, _08061E18 @ =0x00269EC3
	adds r0, r0, r6
	lsls r0, r0, #1
	lsrs r4, r0, #1
	str r4, [r3]
	lsrs r0, r0, #0x11
	ldr r5, _08061E1C @ =0x000007FF
	ands r0, r5
	adds r0, r0, r1
	str r0, [sp]
	ldr r2, [r2, #0x58]
	ldr r0, _08061E20 @ =0xFFFFEC00
	adds r2, r2, r0
	mov r0, r8
	muls r0, r4, r0
	adds r0, r0, r6
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r3]
	lsrs r0, r0, #0x11
	ands r0, r5
	adds r0, r0, r2
	str r0, [sp, #4]
	movs r0, #1
	mov r1, sp
	bl CreateSmoke
	movs r0, #0x2a
	bl PlaySound
_08061DF2:
	ldrh r0, [r7]
	mov r1, sb
	strb r0, [r1]
_08061DF8:
	add sp, #8
	pop {r3, r4}
	mov r8, r3
	mov sb, r4
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_08061E08: .4byte pZero2
_08061E0C: .4byte 0xFFFFF800
_08061E10: .4byte RNG_0202f388
_08061E14: .4byte 0x000343FD
_08061E18: .4byte 0x00269EC3
_08061E1C: .4byte 0x000007FF
_08061E20: .4byte 0xFFFFEC00

