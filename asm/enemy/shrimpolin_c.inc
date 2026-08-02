	.include "asm/macros.inc"

	.syntax unified
	
	.text



	thumb_func_start slashShrimporin
slashShrimporin: @ 0x0806A40C
	push {r4, r5, r6, lr}
	sub sp, #0x18
	adds r5, r0, #0
	ldrb r6, [r5, #0xe]
	cmp r6, #0
	beq _0806A41E
	cmp r6, #1
	beq _0806A49A
	b _0806A4D8
_0806A41E:
	movs r4, #0
	ldr r0, _0806A4E0 @ =pZero2
	ldr r0, [r0]
	ldr r0, [r0, #0x54]
	ldr r1, [r5, #0x54]
	subs r0, r0, r1
	cmp r0, #0
	ble _0806A430
	movs r4, #1
_0806A430:
	ldr r1, _0806A4E4 @ =0x00000D04
	adds r0, r5, #0
	bl SetMotion
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
	ldr r0, [r5, #0x54]
	str r0, [sp, #0x10]
	ldr r0, [r5, #0x58]
	str r0, [sp, #0x14]
	movs r2, #0x80
	lsls r2, r2, #2
	movs r0, #0
	add r1, sp, #0x10
	adds r3, r4, #0
	bl FUN_080b2b40
	movs r1, #0x60
	lsls r0, r4, #1
	adds r0, r0, r4
	lsls r0, r0, #6
	subs r0, r1, r0
	str r0, [sp, #0x10]
	str r1, [sp, #0x14]
	adds r1, r5, #0
	adds r1, #0x54
	ldr r0, _0806A4E8 @ =sMotions+6
	str r0, [sp]
	movs r4, #0x18
	str r4, [sp, #4]
	movs r0, #1
	str r0, [sp, #8]
	ldrb r0, [r5, #0x11]
	str r0, [sp, #0xc]
	adds r0, r5, #0
	add r2, sp, #0x10
	movs r3, #0x40
	bl FUN_080b869c
	strb r4, [r5, #0x12]
	str r6, [r5, #0x60]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_0806A49A:
	ldr r0, [r5, #0x60]
	adds r0, #0x30
	str r0, [r5, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _0806A4AA
	str r1, [r5, #0x60]
_0806A4AA:
	ldr r0, [r5, #0x58]
	ldr r1, [r5, #0x60]
	adds r0, r0, r1
	str r0, [r5, #0x58]
	adds r0, r5, #0
	bl UpdateMotionGraphic
	ldrb r0, [r5, #0x12]
	subs r0, #1
	strb r0, [r5, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _0806A4D2
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x58]
	bl GetGroundMetatileAttr
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _0806A4D8
_0806A4D2:
	adds r0, r5, #0
	bl explodeShrimpolin
_0806A4D8:
	add sp, #0x18
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_0806A4E0: .4byte pZero2
_0806A4E4: .4byte 0x00000D04
_0806A4E8: .4byte sMotions+6
