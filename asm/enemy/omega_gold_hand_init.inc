	push {r4, r5, r6, r7, lr}
	mov r7, r8
	push {r7}
	adds r5, r0, #0
	bl InitScalerotMotion1
	adds r0, r5, #0
	adds r0, #0x24
	movs r6, #0
	strb r6, [r0]
	ldrb r1, [r5, #0xa]
	movs r0, #0xef
	ands r0, r1
	movs r7, #0
	strb r0, [r5, #0xa]
	movs r2, #1
	movs r0, #1
	mov r8, r0
	adds r0, r5, #0
	adds r0, #0x4c
	strb r7, [r0]
	adds r3, r5, #0
	adds r3, #0x4a
	ldrb r1, [r3]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r3]
	ldrb r0, [r5, #0xa]
	orrs r0, r2
	movs r1, #2
	orrs r0, r1
	movs r1, #4
	orrs r0, r1
	strb r0, [r5, #0xa]
	adds r4, r5, #0
	adds r4, #0x74
	ldr r1, _08082CA0 @ =0x08368220
	adds r2, r5, #0
	adds r2, #0x54
	adds r0, r4, #0
	movs r3, #1
	bl InitBody
	str r5, [r4, #0x2c]
	ldr r0, _08082CA4 @ =nop_08083eac
	str r0, [r4, #0x24]
	adds r0, r5, #0
	adds r0, #0x5c
	str r7, [r0, #4]
	str r7, [r5, #0x5c]
	ldrb r0, [r5, #0x11]
	cmp r0, #0
	bne _08082CAC
	ldr r1, _08082CA8 @ =gEnemyFnTable
	ldrb r0, [r5, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	mov r1, r8
	str r1, [r5, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r5, #0x14]
	strb r7, [r5, #0xd]
	strb r7, [r5, #0xe]
	strb r7, [r5, #0xf]
	b _08082CE2
	.align 2, 0
_08082CA0: .4byte 0x08368220
_08082CA4: .4byte nop_08083eac
_08082CA8: .4byte gEnemyFnTable
_08082CAC:
	adds r0, r5, #0
	adds r0, #0x8c
	str r6, [r0]
	adds r0, #4
	str r6, [r0]
	adds r0, #4
	strb r6, [r0]
	ldrb r1, [r5, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r5, #0xa]
	adds r0, r5, #0
	adds r0, #0xc1
	strb r6, [r0]
	ldr r1, _08082D0C @ =gEnemyFnTable
	ldrb r0, [r5, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	mov r1, r8
	str r1, [r5, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r5, #0x14]
	movs r0, #2
	strb r0, [r5, #0xd]
	strb r6, [r5, #0xe]
	strb r6, [r5, #0xf]
_08082CE2:
	ldrb r0, [r5, #0x10]
	cmp r0, #0
	bne _08082D18
	adds r2, r5, #0
	adds r2, #0x49
	ldrb r0, [r2]
	movs r1, #0xc
	orrs r0, r1
	strb r0, [r2]
	adds r1, r5, #0
	adds r1, #0xb4
	ldr r0, _08082D10 @ =0xFFFFED00
	str r0, [r1]
	adds r1, #4
	ldr r0, _08082D14 @ =0xFFFFC600
	str r0, [r1]
	adds r1, #8
	movs r0, #1
	strb r0, [r1]
	b _08082D4C
	.align 2, 0
_08082D0C: .4byte gEnemyFnTable
_08082D10: .4byte 0xFFFFED00
_08082D14: .4byte 0xFFFFC600
_08082D18:
	adds r1, r5, #0
	adds r1, #0x25
	movs r0, #0x17
	strb r0, [r1]
	adds r1, #0x8f
	movs r0, #0xa8
	lsls r0, r0, #5
	str r0, [r1]
	adds r1, #4
	ldr r0, _08082D6C @ =0xFFFFC800
	str r0, [r1]
	movs r2, #0
	ldrb r1, [r5, #0xa]
	movs r0, #0xdf
	ands r0, r1
	strb r0, [r5, #0xa]
	adds r0, r5, #0
	adds r0, #0x4d
	strb r2, [r0]
	adds r2, r5, #0
	adds r2, #0x4a
	ldrb r1, [r2]
	movs r0, #0x21
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r2]
_08082D4C:
	ldrb r1, [r5, #0xb]
	movs r0, #0x10
	orrs r0, r1
	strb r0, [r5, #0xb]
	ldr r0, [r5, #0x28]
	ldrb r0, [r0, #0x1c]
	strb r0, [r5, #0x1d]
	adds r0, r5, #0
	bl OmegaGoldHand_Update
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_08082D6C: .4byte 0xFFFFC800
