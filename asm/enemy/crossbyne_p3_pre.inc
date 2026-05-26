	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_0807cf60
FUN_0807cf60: @ 0x0807CF60
	push {r4, r5, lr}
	adds r4, r0, #0
	adds r5, r4, #0
	adds r5, #0xb4
	ldr r0, [r5]
	cmp r0, #0
	beq _0807CF76
	bl isKilled
	cmp r0, #0
	beq _0807CF80
_0807CF76:
	movs r1, #0
	str r1, [r5]
	movs r0, #2
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_0807CF80:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
