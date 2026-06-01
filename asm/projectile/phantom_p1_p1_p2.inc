	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080af5f4
FUN_080af5f4: @ 0x080AF5F4
	push {r4, lr}
	adds r4, r0, #0
	ldr r0, [r4, #0x28]
	adds r1, r4, #0
	adds r1, #0x54
	adds r2, r4, #0
	adds r2, #0x5c
	adds r3, r4, #0
	adds r3, #0x64
	bl FUN_080afe38
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _080AF614
	movs r0, #1
	strb r0, [r4, #0xe]
_080AF614:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
