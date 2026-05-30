	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start goldOmega1Neutral
goldOmega1Neutral: @ 0x0805B5A4
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r5, [r4, #0xe]
	cmp r5, #0
	beq _0805B5B4
	cmp r5, #1
	beq _0805B5CC
	b _0805B5D2
_0805B5B4:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _0805B5D8 @ =0x08364C8C
	bl SetDDP
	str r5, [r4, #0x60]
	str r5, [r4, #0x5c]
	movs r0, #0x1e
	strb r0, [r4, #0x13]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0805B5CC:
	adds r0, r4, #0
	bl floatGoldOmega1
_0805B5D2:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_0805B5D8: .4byte 0x08364C8C
