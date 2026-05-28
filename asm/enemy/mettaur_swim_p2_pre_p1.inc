	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_0808926c
FUN_0808926c: @ 0x0808926C
	push {r4, lr}
	adds r4, r0, #0
	bl FUN_08088ba8
	lsls r0, r0, #0x18
	lsrs r1, r0, #0x18
	cmp r1, #0
	bne _08089282
	movs r0, #5
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_08089282:
	adds r0, r4, #0
	adds r0, #0x8c
	ldr r0, [r0]
	ldr r1, _080892A0 @ =0x00020001
	ands r0, r1
	cmp r0, r1
	bne _08089298
	movs r1, #0
	movs r0, #0xc
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_08089298:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080892A0: .4byte 0x00020001
