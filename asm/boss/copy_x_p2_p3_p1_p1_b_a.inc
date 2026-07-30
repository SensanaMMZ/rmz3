	.include "asm/macros.inc"

	.syntax unified
	
	.text


	thumb_func_start copyxMode16
copyxMode16: @ 0x08056270
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _080562FA
	ldr r1, _080562C8 @ =0x0000B310
	adds r0, r4, #0
	bl SetMotion
	movs r3, #0
	ldr r0, _080562CC @ =pZero2
	ldr r2, [r0]
	ldr r1, [r2, #0x54]
	ldr r0, [r4, #0x54]
	cmp r1, r0
	ble _08056292
	movs r3, #1
_08056292:
	adds r0, r4, #0
	adds r0, #0x4c
	strb r3, [r0]
	movs r3, #0
	ldr r1, [r2, #0x54]
	ldr r0, [r4, #0x54]
	cmp r1, r0
	ble _080562A4
	movs r3, #1
_080562A4:
	movs r0, #0x4a
	adds r0, r0, r4
	mov ip, r0
	lsls r2, r3, #4
	ldrb r1, [r0]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	orrs r0, r2
	mov r1, ip
	strb r0, [r1]
	cmp r3, #0
	beq _080562D0
	ldrb r0, [r4, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _080562D6
	.align 2, 0
_080562C8: .4byte 0x0000B310
_080562CC: .4byte pZero2
_080562D0:
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
_080562D6:
	strb r0, [r4, #0xa]
	movs r0, #0
	strb r0, [r4, #0xe]
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _080562F0
	ldr r0, _080562EC @ =0xFFFFFD00
	b _080562F4
	.align 2, 0
_080562EC: .4byte 0xFFFFFD00
_080562F0:
	movs r0, #0xc0
	lsls r0, r0, #2
_080562F4:
	str r0, [r4, #0x5c]
	ldr r0, _08056334 @ =0xFFFFFD00
	str r0, [r4, #0x60]
_080562FA:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	ldr r2, [r4, #0x60]
	adds r1, r1, r2
	str r1, [r4, #0x58]
	adds r2, #0x40
	str r2, [r4, #0x60]
	bl FUN_08009f6c
	ldr r1, [r4, #0x58]
	cmp r0, r1
	bge _0805632E
	ldr r0, [r4, #0x54]
	bl FUN_08009f6c
	str r0, [r4, #0x58]
	movs r0, #0xc
	strb r0, [r4, #0xd]
	movs r0, #1
	strb r0, [r4, #0xe]
_0805632E:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_08056334: .4byte 0xFFFFFD00
