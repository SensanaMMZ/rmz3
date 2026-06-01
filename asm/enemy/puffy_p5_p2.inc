	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start dragInSea
dragInSea: @ 0x0807CBD4
	push {lr}
	adds r3, r0, #0
	ldr r1, _0807CBEC @ =gOverworld
	ldr r2, _0807CBF0 @ =0x0002C00C
	adds r1, r1, r2
	ldr r2, [r1]
	ldr r1, [r3, #0x58]
	cmp r2, r1
	ble _0807CBE8
	str r2, [r3, #0x58]
_0807CBE8:
	pop {r1}
	bx r1
	.align 2, 0
_0807CBEC: .4byte gOverworld
_0807CBF0: .4byte 0x0002C00C
