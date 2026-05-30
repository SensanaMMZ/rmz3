	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080616b8
FUN_080616b8: @ 0x080616B8
	push {lr}
	adds r3, r0, #0
	ldr r1, [r3, #0x2c]
	ldr r2, [r1, #0x2c]
	cmp r2, #0
	beq _080616D8
	ldrb r0, [r2, #0xc]
	cmp r0, #1
	bls _080616D0
	movs r0, #0
	str r0, [r1, #0x2c]
	b _080616D8
_080616D0:
	ldrb r1, [r2, #0xa]
	movs r0, #0xfe
	ands r0, r1
	strb r0, [r2, #0xa]
_080616D8:
	ldr r0, [r3, #0x2c]
	adds r1, r0, #0
	adds r1, #0xbc
	ldr r2, [r1]
	cmp r2, #0
	beq _080616F8
	ldrb r0, [r2, #0xc]
	cmp r0, #1
	bls _080616F0
	movs r0, #0
	str r0, [r1]
	b _080616F8
_080616F0:
	ldrb r1, [r2, #0xa]
	movs r0, #0xfe
	ands r0, r1
	strb r0, [r2, #0xa]
_080616F8:
	pop {r0}
	bx r0
