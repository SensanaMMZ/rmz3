	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_0806cd4c
FUN_0806cd4c: @ 0x0806CD4C
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	bne _0806CD72
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _0806CD9C @ =0x08366638
	bl SetDDP
	ldr r1, [r4, #0x2c]
	adds r1, #0xb4
	ldr r0, [r1]
	movs r2, #2
	orrs r0, r2
	str r0, [r1]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0806CD72:
	adds r5, r4, #0
	adds r5, #0xc0
	ldr r0, [r5]
	bl isKilled
	cmp r0, #0
	beq _0806CD94
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _0806CDA0 @ =0x08366590
	bl SetDDP
	movs r1, #0
	str r1, [r5]
	movs r0, #1
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_0806CD94:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_0806CD9C: .4byte 0x08366638
_0806CDA0: .4byte 0x08366590
