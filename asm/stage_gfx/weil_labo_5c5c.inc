	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	adds r6, r0, #0
	ldr r0, [r6, #0x5c]
	lsls r4, r0, #0x10
	lsrs r7, r4, #0x10
	ldrb r0, [r6, #0xe]
	cmp r0, #1
	beq _08015C86
	cmp r0, #1
	bgt _08015CD0
	cmp r0, #0
	bne _08015CD0
	ldr r0, _08015CD8 @ =gOverworld
	ldr r1, _08015CDC @ =0x0002D024
	adds r0, r0, r1
	ldrb r0, [r0]
	cmp r0, #0
	beq _08015CD0
	movs r0, #1
	strb r0, [r6, #0xe]
_08015C86:
	lsrs r4, r4, #0x14
	lsls r2, r4, #1
	ldr r3, _08015CE0 @ =gVideoRegBuffer+4
	adds r2, r2, r3
	ldr r1, [r6, #0x64]
	ldr r5, _08015CE4 @ =0x00004046
	adds r0, r5, #0
	orrs r1, r0
	strh r1, [r2]
	lsls r4, r4, #2
	adds r3, #8
	adds r4, r4, r3
	movs r5, #0
	str r5, [r4]
	movs r0, #0xf8
	lsls r0, r0, #5
	ands r1, r0
	lsls r1, r1, #3
	movs r0, #0xc0
	lsls r0, r0, #0x13
	adds r1, r1, r0
	str r5, [sp, #4]
	ldr r2, _08015CE8 @ =0x01000400
	add r0, sp, #4
	bl CpuFastSet
	lsls r0, r7, #0x18
	lsrs r0, r0, #0x18
	ldr r1, _08015CEC @ =gBgMapOffsets
	str r5, [sp]
	movs r2, #0x4b
	movs r3, #0
	bl LoadBgMap
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_08015CD0:
	add sp, #0xc
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_08015CD8: .4byte gOverworld
_08015CDC: .4byte 0x0002D024
_08015CE0: .4byte gVideoRegBuffer+4
_08015CE4: .4byte 0x00004046
_08015CE8: .4byte 0x01000400
_08015CEC: .4byte gBgMapOffsets

