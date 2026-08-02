	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_08095578
FUN_08095578: @ 0x08095578
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r5, [r4, #0xe]
	cmp r5, #1
	beq _080955A8
	cmp r5, #1
	bgt _0809558C
	cmp r5, #0
	beq _08095596
	b _0809565E
_0809558C:
	cmp r5, #2
	beq _08095614
	cmp r5, #3
	beq _08095622
	b _0809565E
_08095596:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _08095610 @ =0x08369FEC
	bl SetDDP
	str r5, [r4, #0x60]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080955A8:
	movs r1, #0xd4
	lsls r1, r1, #8
	adds r0, r4, #0
	bl SetMotion
	adds r0, r4, #0
	adds r0, #0xb8
	ldrb r0, [r0]
	cmp r0, #2
	bne _080955D6
	ldr r3, [r4, #0x54]
	adds r0, r3, #0
	subs r0, #0x80
	str r0, [r4, #0x54]
	adds r2, r0, #0
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _080955D4
	adds r2, r3, #0
	adds r2, #0x80
_080955D4:
	str r2, [r4, #0x54]
_080955D6:
	ldr r0, [r4, #0x60]
	adds r0, #0x40
	str r0, [r4, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _080955E6
	str r1, [r4, #0x60]
_080955E6:
	ldr r1, [r4, #0x58]
	ldr r0, [r4, #0x60]
	adds r1, r1, r0
	str r1, [r4, #0x58]
	ldr r0, [r4, #0x54]
	bl PushoutToUp1
	adds r1, r0, #0
	cmp r1, #0
	bge _08095606
	ldr r0, [r4, #0x58]
	adds r0, r0, r1
	str r0, [r4, #0x58]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08095606:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	b _0809565E
	.align 2, 0
_08095610: .4byte 0x08369FEC
_08095614:
	ldr r1, _08095644 @ =0x0000D401
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08095622:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r2, [r0]
	cmp r2, #3
	bne _08095656
	adds r1, r4, #0
	adds r1, #0xb8
	ldrb r0, [r1]
	cmp r0, #0
	bne _08095648
	movs r0, #1
	strb r0, [r1]
	movs r0, #8
	b _08095650
	.align 2, 0
_08095644: .4byte 0x0000D401
_08095648:
	cmp r0, #2
	bne _0809564E
	strb r2, [r1]
_0809564E:
	movs r0, #1
_08095650:
	strb r0, [r4, #0xd]
	movs r0, #0
	strb r0, [r4, #0xe]
_08095656:
	adds r0, r4, #0
	movs r1, #1
	bl FUN_08094fe0
_0809565E:
	pop {r4, r5}
	pop {r0}
	bx r0
