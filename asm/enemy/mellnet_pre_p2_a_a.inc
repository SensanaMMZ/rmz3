	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_0807d780
FUN_0807d780: @ 0x0807D780
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xd]
	cmp r0, #6
	beq _0807D806
	adds r0, r4, #0
	adds r0, #0xb4
	ldr r5, [r0]
	cmp r5, #0
	bne _0807D806
	ldrb r0, [r4, #0xf]
	cmp r0, #0
	beq _0807D7A0
	cmp r0, #1
	beq _0807D7E4
	b _0807D806
_0807D7A0:
	adds r0, r4, #0
	bl IsFrozen
	cmp r0, #0
	beq _0807D806
	ldr r1, _0807D7DC @ =0x08367C98
	ldrb r0, [r4, #0xd]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r1, [r0]
	adds r0, r4, #0
	bl _call_via_r1
	ldr r1, _0807D7E0 @ =0x08367CB4
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
_0807D7D6:
	movs r0, #1
	b _0807D808
	.align 2, 0
_0807D7DC: .4byte 0x08367C98
_0807D7E0: .4byte 0x08367CB4
_0807D7E4:
	adds r0, r4, #0
	bl IsFrozen
	cmp r0, #0
	beq _0807D804
	adds r0, r4, #0
	adds r0, #0x8c
	ldr r0, [r0]
	ldr r1, _0807D800 @ =0x00020001
	ands r0, r1
	cmp r0, r1
	bne _0807D7D6
	strb r5, [r4, #0xf]
	b _0807D806
	.align 2, 0
_0807D800: .4byte 0x00020001
_0807D804:
	strb r0, [r4, #0xf]
_0807D806:
	movs r0, #0
_0807D808:
	pop {r4, r5}
	pop {r1}
	bx r1
	.align 2, 0
