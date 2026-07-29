	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_08077fa4
FUN_08077fa4: @ 0x08077FA4
	push {r4, r5, r6, r7, lr}
	sub sp, #0x10
	adds r6, r0, #0
	ldrb r0, [r6, #0xe]
	cmp r0, #0
	beq _08077FB6
	cmp r0, #1
	beq _0807806E
	b _080780B4
_08077FB6:
	movs r3, #0
	ldr r0, _08077FD8 @ =pZero2
	ldr r0, [r0]
	ldr r0, [r0, #0x54]
	ldr r1, [r6, #0x54]
	subs r0, r0, r1
	cmp r0, #0
	ble _08077FC8
	movs r3, #1
_08077FC8:
	adds r7, r3, #0
	adds r2, r7, #0
	cmp r7, #0
	beq _08077FDC
	ldrb r1, [r6, #0xa]
	movs r0, #0x10
	orrs r0, r1
	b _08077FE2
	.align 2, 0
_08077FD8: .4byte pZero2
_08077FDC:
	ldrb r1, [r6, #0xa]
	movs r0, #0xef
	ands r0, r1
_08077FE2:
	strb r0, [r6, #0xa]
	adds r1, r2, #0
	adds r0, r6, #0
	adds r0, #0x4c
	movs r4, #0
	strb r1, [r0]
	adds r3, r6, #0
	adds r3, #0x4a
	lsls r1, r1, #4
	ldrb r2, [r3]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r1
	strb r0, [r3]
	lsls r5, r7, #8
	ldr r0, [r6, #0x54]
	subs r0, r0, r5
	str r0, [r6, #0x54]
	ldr r1, _080780BC @ =0x00002E07
	adds r0, r6, #0
	bl SetMotion
	adds r0, r6, #0
	adds r0, #0x8c
	str r4, [r0]
	adds r0, #4
	str r4, [r0]
	adds r0, #4
	strb r4, [r0]
	ldrb r1, [r6, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r6, #0xa]
	ldr r0, [r6, #0x54]
	str r0, [sp, #8]
	ldr r0, [r6, #0x58]
	str r0, [sp, #0xc]
	movs r2, #0x80
	lsls r2, r2, #2
	movs r0, #0
	add r1, sp, #8
	adds r3, r7, #0
	bl FUN_080b2b40
	movs r0, #0x80
	subs r0, r0, r5
	str r0, [sp, #8]
	movs r1, #0x60
	str r1, [sp, #0xc]
	movs r1, #3
	bl __divsi3
	str r0, [r6, #0x5c]
	str r4, [r6, #0x60]
	adds r1, r6, #0
	adds r1, #0x54
	ldr r0, _080780C0 @ =0x08367402
	str r0, [sp]
	movs r4, #0x18
	str r4, [sp, #4]
	adds r0, r6, #0
	add r2, sp, #8
	movs r3, #0x20
	bl FUN_080b84f4
	strb r4, [r6, #0x12]
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_0807806E:
	ldr r0, [r6, #0x54]
	ldr r1, [r6, #0x5c]
	adds r0, r0, r1
	str r0, [r6, #0x54]
	ldr r0, [r6, #0x60]
	adds r0, #0x15
	str r0, [r6, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _08078086
	str r1, [r6, #0x60]
_08078086:
	ldr r0, [r6, #0x58]
	ldr r1, [r6, #0x60]
	adds r0, r0, r1
	str r0, [r6, #0x58]
	adds r0, r6, #0
	bl UpdateMotionGraphic
	ldrb r0, [r6, #0x12]
	subs r0, #1
	strb r0, [r6, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _080780AE
	ldr r0, [r6, #0x54]
	ldr r1, [r6, #0x58]
	bl FUN_080098a4
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _080780B4
_080780AE:
	adds r0, r6, #0
	bl MaybeKillVolcaire
_080780B4:
	add sp, #0x10
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080780BC: .4byte 0x00002E07
_080780C0: .4byte 0x08367402

