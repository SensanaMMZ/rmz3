	push {r4, r5, r6, r7, lr}
	mov r7, sb
	mov r6, r8
	push {r6, r7}
	ldr r4, [sp, #0x1c]
	lsls r2, r2, #0x18
	lsls r4, r4, #0x18
	asrs r4, r4, #0x13
	lsls r3, r3, #0x18
	asrs r3, r3, #0x18
	adds r4, r4, r3
	lsls r4, r4, #1
	adds r7, r0, r4
	lsrs r2, r2, #0x16
	adds r0, r2, r1
	ldr r0, [r0]
	adds r1, r1, r0
	adds r1, r1, r2
	ldrh r0, [r1, #4]
	ldrh r4, [r1, #6]
	adds r5, r1, #0
	adds r5, #8
	cmp r4, #0
	beq _0800429E
	lsls r6, r0, #1
	lsrs r0, r6, #1
	mov r8, r0
	ldr r3, _080042AC @ =0x001FFFFF
	mov sb, r3
_08004282:
	adds r0, r5, #0
	adds r1, r7, #0
	mov r2, r8
	mov r3, sb
	ands r2, r3
	bl CpuSet
	subs r0, r4, #1
	lsls r0, r0, #0x10
	lsrs r4, r0, #0x10
	adds r5, r5, r6
	adds r7, #0x40
	cmp r4, #0
	bne _08004282
_0800429E:
	pop {r3, r4}
	mov r8, r3
	mov sb, r4
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080042AC: .4byte 0x001FFFFF
