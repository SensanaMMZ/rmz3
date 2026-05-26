	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_08084934
FUN_08084934: @ 0x08084934
	push {r4, r5, lr}
	adds r4, r0, #0
	adds r5, r4, #0
	adds r5, #0xb4
	ldr r0, [r5]
	cmp r0, #0
	beq _0808494A
	bl isKilled
	cmp r0, #0
	beq _0808496A
_0808494A:
	movs r0, #0
	str r0, [r5]
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _08084970 @ =0x08368328
	bl SetDDP
	adds r0, r4, #0
	bl IsFrozen
	adds r1, r0, #0
	cmp r1, #0
	bne _0808496A
	movs r0, #1
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_0808496A:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_08084970: .4byte 0x08368328
