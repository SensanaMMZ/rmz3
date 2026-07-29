	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080af760
FUN_080af760: @ 0x080AF760
	push {r4, lr}
	adds r4, r0, #0
	adds r0, #0x8c
	movs r1, #0
	str r1, [r0]
	adds r0, #4
	str r1, [r0]
	adds r0, #4
	strb r1, [r0]
	ldrb r1, [r4, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r4, #0xa]
	ldr r1, _080AF7A8 @ =0x00008605
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0x12]
	adds r0, #0x20
	adds r1, r4, #0
	adds r1, #0x24
	strb r0, [r1]
	ldr r0, [r4, #0x60]
	ldr r1, _080AF7AC @ =0xFFFFFA00
	adds r0, r0, r1
	str r0, [r4, #0x60]
	movs r0, #0x1c
	strb r0, [r4, #0x13]
	movs r0, #1
	strb r0, [r4, #0xd]
	adds r0, r4, #0
	bl FUN_080af7b0
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080AF7A8: .4byte 0x00008605
_080AF7AC: .4byte 0xFFFFFA00

