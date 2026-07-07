	push {r4, r5, lr}
	adds r4, r0, #0
	bl InitNonAffineMotion
	ldrb r0, [r4, #0xa]
	movs r1, #1
	movs r5, #0
	orrs r1, r0
	movs r0, #2
	orrs r1, r0
	strb r1, [r4, #0xa]
	adds r0, r4, #0
	bl ResetDynamicMotion
	ldrb r2, [r4, #0x10]
	cmp r2, #0
	bne _080BA3A8
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	adds r0, #0x4c
	strb r2, [r0]
	adds r2, r4, #0
	adds r2, #0x4a
	ldrb r1, [r2]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r2]
	b _080BA3CA
_080BA3A8:
	movs r2, #1
	ldrb r0, [r4, #0xa]
	movs r1, #0x10
	orrs r0, r1
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	adds r0, #0x4c
	strb r2, [r0]
	adds r3, r4, #0
	adds r3, #0x4a
	movs r2, #0x10
	ldrb r1, [r3]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	orrs r0, r2
	strb r0, [r3]
_080BA3CA:
	ldrb r0, [r4, #0x10]
	cmp r0, #0
	bne _080BA3D4
	movs r0, #0x80
	b _080BA3D8
_080BA3D4:
	movs r0, #0x80
	rsbs r0, r0, #0
_080BA3D8:
	str r0, [r4, #0x5c]
	movs r2, #0
	str r2, [r4, #0x60]
	movs r0, #0xff
	strb r0, [r4, #0x12]
	ldr r1, _080BA408 @ =gVFXFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r4, #0x14]
	strb r1, [r4, #0xd]
	strb r2, [r4, #0xe]
	strb r2, [r4, #0xf]
	adds r0, r4, #0
	bl Ghost30_Update
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080BA408: .4byte gVFXFnTable
