	.include "asm/macros.inc"

	.syntax unified
	
	.text


	thumb_func_start FUN_08075dc8
FUN_08075dc8: @ 0x08075DC8
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xd]
	cmp r0, #8
	beq _08075E82
	adds r0, r4, #0
	adds r0, #0xb4
	ldr r0, [r0]
	cmp r0, #0
	bne _08075E82
	ldrb r0, [r4, #0xf]
	cmp r0, #0
	beq _08075DE8
	cmp r0, #1
	beq _08075E30
	b _08075E82
_08075DE8:
	ldrb r0, [r4, #0x10]
	cmp r0, #1
	beq _08075E82
	adds r0, r4, #0
	bl IsFrozen
	cmp r0, #0
	beq _08075E82
	ldr r1, _08075E28 @ =0x083670D0
	ldrb r0, [r4, #0xd]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r1, [r0]
	adds r0, r4, #0
	bl _call_via_r1
	ldr r1, _08075E2C @ =0x083670F8
	ldrb r0, [r4, #0xd]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r1, [r0]
	adds r0, r4, #0
	bl _call_via_r1
	ldrb r0, [r4, #0xf]
	adds r0, #1
	strb r0, [r4, #0xf]
	adds r0, r4, #0
	bl UpdateMotionGraphic
_08075E24:
	movs r0, #1
	b _08075E84
	.align 2, 0
_08075E28: .4byte 0x083670D0
_08075E2C: .4byte 0x083670F8
_08075E30:
	ldrb r0, [r4, #0x10]
	cmp r0, #0
	beq _08075E3A
	cmp r0, #3
	bne _08075E58
_08075E3A:
	adds r0, r4, #0
	adds r0, #0xb8
	ldrb r0, [r0]
	cmp r0, #0
	beq _08075E58
	adds r0, r4, #0
	bl FUN_08075aa8
	ldr r1, _08075E78 @ =0x00002A04
	adds r0, r4, #0
	bl SetMotion
	adds r0, r4, #0
	bl UpdateMotionGraphic
_08075E58:
	adds r0, r4, #0
	bl IsFrozen
	cmp r0, #0
	beq _08075E80
	adds r0, r4, #0
	adds r0, #0x8c
	ldr r0, [r0]
	ldr r1, _08075E7C @ =0x00020001
	ands r0, r1
	cmp r0, r1
	bne _08075E24
	movs r0, #0
	strb r0, [r4, #0xf]
	b _08075E84
	.align 2, 0
_08075E78: .4byte 0x00002A04
_08075E7C: .4byte 0x00020001
_08075E80:
	strb r0, [r4, #0xf]
_08075E82:
	movs r0, #0
_08075E84:
	pop {r4}
	pop {r1}
	bx r1
	.align 2, 0
