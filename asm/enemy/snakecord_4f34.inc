	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r5, [r4, #0xe]
	cmp r5, #0
	beq _08074F44
	cmp r5, #1
	beq _08074F6E
	b _08074FB6
_08074F44:
	adds r1, r4, #0
	adds r1, #0x25
	movs r0, #0xf
	strb r0, [r1]
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _08074FBC @ =0x08366F5C
	bl SetDDP
	ldr r1, _08074FC0 @ =0x0000280B
	adds r0, r4, #0
	bl SetMotion
	adds r0, r4, #0
	bl FUN_080bb830
	str r0, [r4, #0x2c]
	strb r5, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08074F6E:
	ldrb r0, [r4, #0x12]
	cmp r0, #0
	bne _08074F7E
	movs r0, #0x18
	strb r0, [r4, #0x12]
	movs r0, #0x3b
	bl PlaySound
_08074F7E:
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	ldr r0, _08074FC4 @ =pZero2
	ldr r3, [r0]
	ldr r2, [r3, #0x54]
	movs r1, #0x80
	lsls r1, r1, #4
	adds r0, r2, r1
	str r0, [r4, #0x54]
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	ands r0, r1
	movs r5, #0xfe
	lsls r5, r5, #3
	adds r1, r2, r5
	cmp r0, #0
	beq _08074FA6
	ldr r0, _08074FC8 @ =0xFFFFF800
	adds r1, r2, r0
_08074FA6:
	str r1, [r4, #0x54]
	ldr r0, [r3, #0x58]
	ldr r1, _08074FC8 @ =0xFFFFF800
	adds r0, r0, r1
	str r0, [r4, #0x58]
	adds r0, r4, #0
	bl UpdateMotionGraphic
_08074FB6:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_08074FBC: .4byte 0x08366F5C
_08074FC0: .4byte 0x0000280B
_08074FC4: .4byte pZero2
_08074FC8: .4byte 0xFFFFF800

