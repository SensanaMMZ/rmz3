	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_0808d6f8
FUN_0808d6f8: @ 0x0808D6F8
	push {r4, r5, lr}
	adds r4, r0, #0
	adds r5, r4, #0
	adds r5, #0xb4
	ldr r0, [r5]
	cmp r0, #0
	beq _0808D70E
	bl isKilled
	cmp r0, #0
	beq _0808D742
_0808D70E:
	movs r0, #0
	str r0, [r5]
	adds r0, r4, #0
	adds r0, #0x74
	ldr r2, _0808D760 @ =0x0836930C
	adds r1, r4, #0
	adds r1, #0xb9
	ldrb r1, [r1]
	adds r1, r1, r2
	ldrb r2, [r1]
	lsls r1, r2, #1
	adds r1, r1, r2
	lsls r1, r1, #3
	ldr r2, _0808D764 @ =sCollisions
	adds r1, r1, r2
	bl SetDDP
	adds r0, r4, #0
	bl IsFrozen
	adds r1, r0, #0
	cmp r1, #0
	bne _0808D742
	movs r0, #2
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_0808D742:
	adds r0, r4, #0
	adds r0, #0x8c
	ldr r0, [r0]
	ldr r1, _0808D768 @ =0x00020001
	ands r0, r1
	cmp r0, r1
	bne _0808D758
	movs r1, #0
	movs r0, #6
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_0808D758:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_0808D760: .4byte 0x0836930C
_0808D764: .4byte sCollisions
_0808D768: .4byte 0x00020001
