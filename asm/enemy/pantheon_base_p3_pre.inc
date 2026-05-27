	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start pBase_0808a3f8
pBase_0808a3f8: @ 0x0808A3F8
	push {r4, r5, lr}
	adds r4, r0, #0
	adds r5, r4, #0
	adds r5, #0xb4
	ldr r0, [r5]
	cmp r0, #0
	beq _0808A40E
	bl isKilled
	cmp r0, #0
	beq _0808A42E
_0808A40E:
	movs r0, #0
	str r0, [r5]
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _0808A434 @ =0x08368984
	bl SetDDP
	adds r0, r4, #0
	bl IsFrozen
	adds r1, r0, #0
	cmp r1, #0
	bne _0808A42E
	movs r0, #1
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_0808A42E:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_0808A434: .4byte 0x08368984
