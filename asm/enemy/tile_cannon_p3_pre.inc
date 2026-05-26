	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_08078480
FUN_08078480: @ 0x08078480
	push {r4, r5, lr}
	adds r4, r0, #0
	adds r5, r4, #0
	adds r5, #0xb4
	ldr r0, [r5]
	cmp r0, #0
	beq _08078496
	bl isKilled
	cmp r0, #0
	beq _080784AA
_08078496:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _080784B0 @ =0x08367508
	bl SetDDP
	movs r1, #0
	str r1, [r5]
	movs r0, #7
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_080784AA:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080784B0: .4byte 0x08367508
