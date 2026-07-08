	push {r4, r5, r6, r7, lr}
	mov r7, r8
	push {r7}
	sub sp, #8
	adds r7, r0, #0
	ldr r0, [r7, #0x5c]
	lsls r0, r0, #0x10
	ldrb r1, [r7, #0xe]
	mov r8, r1
	cmp r1, #0
	bne _0800B97E
	lsrs r5, r0, #0x14
	lsls r5, r5, #1
	ldr r0, _0800B98C @ =gVideoRegBuffer+4
	adds r5, r5, r0
	ldr r1, [r7, #0x64]
	ldr r2, _0800B990 @ =0x00004046
	adds r0, r2, #0
	orrs r1, r0
	strh r1, [r5]
	ldr r0, _0800B994 @ =gBgMapOffsets+(42*4)
	ldr r0, [r0]
	ldr r2, _0800B998 @ =gBgMapOffsets+(44*4)
	adds r0, r0, r2
	movs r4, #0xf8
	lsls r4, r4, #5
	ands r1, r4
	lsls r1, r1, #3
	movs r2, #0xc0
	lsls r2, r2, #0x13
	adds r1, r1, r2
	movs r6, #0x80
	lsls r6, r6, #2
	adds r2, r6, #0
	bl CpuFastSet
	ldrh r0, [r5]
	ands r4, r0
	lsls r4, r4, #3
	ldr r0, _0800B99C @ =0x06000800
	adds r4, r4, r0
	mov r1, r8
	str r1, [sp]
	movs r2, #0x80
	lsls r2, r2, #0x11
	orrs r2, r6
	mov r0, sp
	adds r1, r4, #0
	bl CpuFastSet
	ldrb r0, [r7, #0xe]
	adds r0, #1
	strb r0, [r7, #0xe]
_0800B97E:
	add sp, #8
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_0800B98C: .4byte gVideoRegBuffer+4
_0800B990: .4byte 0x00004046
_0800B994: .4byte gBgMapOffsets+(42*4)
_0800B998: .4byte gBgMapOffsets+(44*4)
_0800B99C: .4byte 0x06000800
