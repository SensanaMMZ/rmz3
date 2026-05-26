	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_08072fb0
FUN_08072fb0: @ 0x08072FB0
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	bne _08072FCA
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _08072FF0 @ =0x08366C28
	bl SetDDP
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08072FCA:
	adds r5, r4, #0
	adds r5, #0xbc
	ldr r0, [r5]
	bl isKilled
	cmp r0, #0
	beq _08072FEA
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _08072FF4 @ =0x08366C10
	bl SetDDP
	movs r0, #0
	str r0, [r5]
	strb r0, [r4, #0xd]
	strb r0, [r4, #0xe]
_08072FEA:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_08072FF0: .4byte 0x08366C28
_08072FF4: .4byte 0x08366C10
