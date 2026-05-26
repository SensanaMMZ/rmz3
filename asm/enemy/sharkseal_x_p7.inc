	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start sharksealxMode5
sharksealxMode5: @ 0x08070F40
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	bne _08070F5A
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _08070F84 @ =0x08366AA4
	bl SetDDP
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08070F5A:
	adds r5, r4, #0
	adds r5, #0xc0
	ldr r0, [r5]
	bl isKilled
	cmp r0, #0
	beq _08070F7C
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _08070F88 @ =0x08366A44
	bl SetDDP
	movs r1, #0
	str r1, [r5]
	movs r0, #1
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_08070F7C:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_08070F84: .4byte 0x08366AA4
_08070F88: .4byte 0x08366A44
