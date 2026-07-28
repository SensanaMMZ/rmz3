	push {r4, lr}
	mov ip, r0
	ldr r3, [r0, #0x28]
	movs r2, #0
	ldrb r1, [r0, #0xa]
	movs r0, #0xef
	ands r0, r1
	mov r1, ip
	strb r0, [r1, #0xa]
	mov r0, ip
	adds r0, #0x4c
	strb r2, [r0]
	mov r4, ip
	adds r4, #0x4a
	ldrb r1, [r4]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r4]
	mov r1, ip
	adds r1, #0x25
	movs r0, #9
	strb r0, [r1]
	ldr r0, [r3, #0x54]
	ldr r1, [r3, #0x58]
	mov r3, ip
	str r0, [r3, #0x54]
	str r1, [r3, #0x58]
	strb r2, [r3, #0x12]
	mov r0, ip
	bl VFX56_Update
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
