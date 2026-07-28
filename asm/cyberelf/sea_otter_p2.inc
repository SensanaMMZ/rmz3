	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080e4a3c
FUN_080e4a3c: @ 0x080E4A3C
	push {r4, r5, lr}
	adds r4, r0, #0
	adds r0, #0xb4
	ldr r2, [r0]
	ldrb r1, [r4, #0xe]
	cmp r1, #0
	bne _080E4A52
	movs r0, #0x40
	strb r0, [r4, #0xf]
	adds r0, r1, #1
	strb r0, [r4, #0xe]
_080E4A52:
	ldrb r0, [r4, #0xf]
	adds r5, r0, #0
	cmp r5, #0
	beq _080E4A60
	subs r0, #1
	strb r0, [r4, #0xf]
	b _080E4A82
_080E4A60:
	adds r0, r2, #0
	bl CheckPlayerStandStill
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _080E4A82
	adds r0, r4, #0
	adds r0, #0x54
	bl FUN_080e1608
	str r0, [r4, #0x2c]
	cmp r0, #0
	beq _080E4A82
	ldrb r0, [r4, #0xd]
	adds r0, #1
	strb r0, [r4, #0xd]
	strb r5, [r4, #0xe]
_080E4A82:
	pop {r4, r5}
	pop {r0}
	bx r0

