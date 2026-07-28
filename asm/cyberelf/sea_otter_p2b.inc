	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080e4ae8
FUN_080e4ae8: @ 0x080E4AE8
	push {r4, r5, lr}
	adds r4, r0, #0
	adds r0, #0xb4
	ldr r2, [r0]
	ldr r5, [r4, #0x2c]
	ldrb r1, [r4, #0xe]
	cmp r1, #0
	bne _080E4B00
	movs r0, #0x40
	strb r0, [r4, #0xf]
	adds r0, r1, #1
	strb r0, [r4, #0xe]
_080E4B00:
	ldrb r0, [r5, #0xc]
	cmp r0, #1
	bhi _080E4B12
	adds r0, r2, #0
	bl CheckPlayerStandStill
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080E4B26
_080E4B12:
	ldrb r1, [r5, #0xb]
	movs r0, #0x7f
	ands r0, r1
	movs r1, #0
	strb r0, [r5, #0xb]
	str r1, [r4, #0x2c]
	movs r0, #3
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
	b _080E4B50
_080E4B26:
	ldrb r0, [r4, #0xf]
	subs r0, #1
	movs r2, #0
	strb r0, [r4, #0xf]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0xff
	bne _080E4B48
	ldrb r0, [r5, #0xb]
	movs r1, #0x7f
	ands r1, r0
	strb r1, [r5, #0xb]
	str r2, [r4, #0x2c]
	movs r0, #3
	strb r0, [r4, #0xd]
	strb r2, [r4, #0xe]
	b _080E4B50
_080E4B48:
	ldrb r0, [r5, #0xb]
	movs r1, #0x80
	orrs r0, r1
	strb r0, [r5, #0xb]
_080E4B50:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
