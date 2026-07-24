	push {r4, r5, r6, r7, lr}
	sub sp, #8
	adds r4, r0, #0
	ldr r6, _080F8C74 @ =gStageDiskManager
	str r4, [r6]
	movs r5, #0
	str r5, [sp]
	ldr r2, _080F8C78 @ =0x01000008
	mov r0, sp
	adds r1, r4, #0
	bl CpuFastSet
	str r5, [sp, #4]
	add r0, sp, #4
	adds r4, #0x20
	ldr r2, _080F8C7C @ =0x05000004
	adds r1, r4, #0
	bl CpuSet
	movs r7, #3
_080F8C3C:
	ldr r2, [r6]
	lsrs r4, r5, #2
	adds r2, r2, r4
	adds r3, r5, #0
	ands r3, r7
	movs r0, #1
	lsls r0, r3
	ldrb r1, [r2]
	orrs r0, r1
	strb r0, [r2]
	ldr r2, [r6]
	adds r2, r2, r4
	movs r0, #0x10
	lsls r0, r3
	ldrb r1, [r2]
	orrs r0, r1
	strb r0, [r2]
	adds r0, r5, #1
	lsls r0, r0, #0x18
	lsrs r5, r0, #0x18
	cmp r5, #0xb3
	bls _080F8C3C
	bl clearStageDisk
	add sp, #8
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080F8C74: .4byte gStageDiskManager
_080F8C78: .4byte 0x01000008
_080F8C7C: .4byte 0x05000004
