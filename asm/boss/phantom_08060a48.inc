	push {r4, r5, r6, r7, lr}
	mov r7, sl
	mov r6, sb
	mov r5, r8
	push {r5, r6, r7}
	sub sp, #0x1c
	adds r6, r0, #0
	lsls r1, r1, #0x18
	lsrs r7, r1, #0x18
	ldr r2, [r6, #0x2c]
	ldr r0, [r2, #0x54]
	ldr r1, [r2, #0x58]
	str r0, [sp]
	str r1, [sp, #4]
	ldr r0, [r2, #0x5c]
	ldr r1, [r2, #0x60]
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	ldr r0, [r2, #0x64]
	ldr r1, [r2, #0x68]
	str r0, [sp, #0x10]
	str r1, [sp, #0x14]
	movs r5, #0
	ldrb r0, [r2, #0xe]
	cmp r0, #1
	bls _08060A7E
	movs r5, #1
_08060A7E:
	add r0, sp, #8
	mov sb, r0
	add r1, sp, #0x10
	mov r8, r1
	movs r0, #0xbc
	adds r0, r0, r6
	mov sl, r0
	adds r1, r6, #0
	adds r1, #0xc0
	str r1, [sp, #0x18]
_08060A92:
	ldr r1, _08060AE0 @ =PTR_ARRAY_08365568
	lsls r0, r5, #2
	adds r0, r0, r1
	ldr r4, [r0]
	adds r0, r6, #0
	mov r1, sp
	mov r2, sb
	mov r3, r8
	bl _call_via_r4
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _08060AB6
	movs r0, #0
	cmp r5, #0
	bne _08060AB4
	movs r0, #1
_08060AB4:
	adds r5, r0, #0
_08060AB6:
	lsls r0, r7, #0x18
	movs r1, #0xff
	lsls r1, r1, #0x18
	adds r0, r0, r1
	lsrs r7, r0, #0x18
	cmp r0, #0
	bne _08060A92
	ldr r0, [sp]
	mov r1, sl
	str r0, [r1]
	ldr r0, [sp, #4]
	ldr r1, [sp, #0x18]
	str r0, [r1]
	add sp, #0x1c
	pop {r3, r4, r5}
	mov r8, r3
	mov sb, r4
	mov sl, r5
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_08060AE0: .4byte PTR_ARRAY_08365568
