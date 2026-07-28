	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0x10]
	cmp r0, #0
	bne _08074354
	ldrb r0, [r4, #0xd]
	cmp r0, #1
	beq _08074354
	adds r0, r4, #0
	adds r0, #0xb4
	ldr r2, [r0]
	adds r5, r0, #0
	cmp r2, #0
	bne _08074354
	subs r0, #0x28
	ldr r1, [r0]
	movs r0, #1
	ands r0, r1
	cmp r0, #0
	beq _08074354
	movs r0, #0x80
	lsls r0, r0, #0xa
	ands r1, r0
	cmp r1, #0
	beq _08074326
	movs r0, #0xa
	strb r0, [r4, #0xd]
	strb r2, [r4, #0xe]
	b _08074354
_08074326:
	adds r0, r4, #0
	adds r0, #0x97
	ldrb r1, [r0]
	movs r0, #0xf0
	ands r0, r1
	cmp r0, #0x20
	bne _0807433C
	ldr r2, _08074338 @ =0x08367004
	b _0807433E
	.align 2, 0
_08074338: .4byte 0x08367004
_0807433C:
	ldr r2, _0807435C @ =0x08366FFC
_0807433E:
	movs r0, #0
	adds r1, r4, #0
	bl ApplyElementEffect
	str r0, [r5]
	ldr r0, [r5]
	cmp r0, #0
	beq _08074354
	movs r0, #0
	strb r0, [r4, #0xd]
	strb r0, [r4, #0xe]
_08074354:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_0807435C: .4byte 0x08366FFC

