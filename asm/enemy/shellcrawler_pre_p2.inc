	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_08096484
FUN_08096484: @ 0x08096484
	push {r4, lr}
	adds r4, r0, #0
	bl FUN_08095d80
	lsls r0, r0, #0x18
	lsrs r1, r0, #0x18
	cmp r1, #0
	bne _0809649A
	movs r0, #1
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_0809649A:
	adds r0, r4, #0
	adds r0, #0x8c
	ldr r0, [r0]
	ldr r1, _080964B8 @ =0x00020001
	ands r0, r1
	cmp r0, r1
	bne _080964B0
	movs r1, #0
	movs r0, #0xa
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_080964B0:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080964B8: .4byte 0x00020001
