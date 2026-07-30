	push {r4, r5, r6, r7, lr}
	mov r7, r8
	push {r7}
	sub sp, #0xc
	adds r5, r0, #0
	ldr r0, [r5, #0x5c]
	lsls r6, r0, #0x10
	lsrs r0, r6, #0x10
	mov r8, r0
	ldr r7, _08015D18 @ =gOverworld
	ldr r2, _08015D1C @ =0x0002D024
	adds r0, r7, r2
	ldrb r0, [r0]
	cmp r0, #0
	bne _08015D20
	adds r0, r5, #0
	bl DrawGeneralStageLayer
	b _08015E24
	.align 2, 0
_08015D18: .4byte gOverworld
_08015D1C: .4byte 0x0002D024
_08015D20:
	ldr r3, _08015DF0 @ =0x0002C002
	adds r0, r7, r3
	ldrh r0, [r0]
	cmp r0, #0
	beq _08015D60
	movs r4, #0
	lsrs r0, r6, #0x14
	lsls r0, r0, #1
	ldr r1, _08015DF4 @ =gVideoRegBuffer+4
	adds r0, r0, r1
	ldrh r0, [r0]
	movs r1, #0xf8
	lsls r1, r1, #5
	ands r1, r0
	lsls r1, r1, #3
	movs r0, #0xc0
	lsls r0, r0, #0x13
	adds r1, r1, r0
	str r4, [sp, #4]
	ldr r2, _08015DF8 @ =0x01000400
	add r0, sp, #4
	bl CpuFastSet
	mov r1, r8
	lsls r0, r1, #0x18
	lsrs r0, r0, #0x18
	ldr r1, _08015DFC @ =gBgMapOffsets
	str r4, [sp]
	movs r2, #0x4b
	movs r3, #0
	bl LoadBgMap
_08015D60:
	adds r3, r7, #0
	ldr r2, _08015E00 @ =0x0002D040
	adds r0, r3, r2
	ldr r0, [r0]
	cmp r0, #0
	beq _08015D82
	ldr r0, _08015E04 @ =0x0002D054
	adds r1, r3, r0
	adds r2, #8
	adds r0, r3, r2
	ldr r2, [r0]
	ldr r0, [r2]
	str r0, [r1]
	ldr r0, _08015E08 @ =0x0002D058
	adds r1, r3, r0
	ldr r0, [r2, #4]
	str r0, [r1]
_08015D82:
	lsrs r2, r6, #0x14
	lsls r2, r2, #2
	ldr r4, _08015E0C @ =gVideoRegBuffer+12
	adds r3, r2, r4
	ldr r1, [r5, #0x34]
	ldr r6, _08015E04 @ =0x0002D054
	adds r0, r7, r6
	ldr r0, [r0]
	asrs r0, r0, #8
	subs r1, r1, r0
	adds r1, #0xe0
	ldr r0, [r5, #0x2c]
	asrs r0, r0, #8
	adds r1, r1, r0
	strh r1, [r3]
	adds r0, r4, #2
	adds r2, r2, r0
	ldr r1, [r5, #0x38]
	ldr r3, _08015E08 @ =0x0002D058
	adds r0, r7, r3
	ldr r0, [r0]
	ldr r6, _08015E10 @ =0xFFFB0000
	adds r0, r0, r6
	asrs r0, r0, #8
	movs r3, #0xa0
	lsls r3, r3, #3
	adds r0, r0, r3
	subs r1, r1, r0
	ldr r0, [r5, #0x30]
	asrs r0, r0, #8
	adds r0, #0x70
	adds r1, r1, r0
	lsls r0, r1, #0x10
	lsrs r3, r0, #0x10
	strh r1, [r2]
	ldr r6, _08015E14 @ =0x0002D025
	adds r0, r7, r6
	ldrb r0, [r0]
	cmp r0, #0
	beq _08015E18
	lsls r0, r3, #0x10
	asrs r0, r0, #0x10
	movs r1, #0xa0
	rsbs r1, r1, #0
	cmp r0, r1
	ble _08015E18
	adds r0, r4, #0
	subs r0, #0xc
	mov r2, r8
	lsls r1, r2, #8
	ldrh r2, [r0]
	orrs r1, r2
	strh r1, [r0]
	b _08015E24
	.align 2, 0
_08015DF0: .4byte 0x0002C002
_08015DF4: .4byte gVideoRegBuffer+4
_08015DF8: .4byte 0x01000400
_08015DFC: .4byte gBgMapOffsets
_08015E00: .4byte 0x0002D040
_08015E04: .4byte 0x0002D054
_08015E08: .4byte 0x0002D058
_08015E0C: .4byte gVideoRegBuffer+12
_08015E10: .4byte 0xFFFB0000
_08015E14: .4byte 0x0002D025
_08015E18:
	ldr r2, _08015E30 @ =gVideoRegBuffer
	mov r3, r8
	lsls r1, r3, #8
	ldrh r0, [r2]
	bics r0, r1
	strh r0, [r2]
_08015E24:
	add sp, #0xc
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_08015E30: .4byte gVideoRegBuffer

