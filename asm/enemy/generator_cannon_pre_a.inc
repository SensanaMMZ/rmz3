	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_0808c450
FUN_0808c450: @ 0x0808C450
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xd]
	cmp r0, #7
	beq _0808C4DE
	adds r0, r4, #0
	adds r0, #0xb4
	ldr r5, [r0]
	cmp r5, #0
	bne _0808C4DE
	ldrb r0, [r4, #0xf]
	cmp r0, #0
	beq _0808C470
	cmp r0, #1
	beq _0808C4B4
	b _0808C4DE
_0808C470:
	adds r0, r4, #0
	bl IsFrozen
	cmp r0, #0
	beq _0808C4DE
	ldr r1, _0808C4AC @ =0x08368F08
	ldrb r0, [r4, #0xd]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r1, [r0]
	adds r0, r4, #0
	bl _call_via_r1
	ldr r1, _0808C4B0 @ =0x08368F28
	ldrb r0, [r4, #0xd]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r1, [r0]
	adds r0, r4, #0
	bl _call_via_r1
	ldrb r0, [r4, #0xf]
	adds r0, #1
	strb r0, [r4, #0xf]
	adds r0, r4, #0
	bl UpdateMotionGraphic
_0808C4A6:
	movs r0, #1
	b _0808C4E0
	.align 2, 0
_0808C4AC: .4byte 0x08368F08
_0808C4B0: .4byte 0x08368F28
_0808C4B4:
	adds r0, r4, #0
	bl IsFrozen
	cmp r0, #0
	beq _0808C4DC
	ldrb r0, [r4, #0x10]
	cmp r0, #1
	bne _0808C4A6
	adds r0, r4, #0
	adds r0, #0x8c
	ldr r0, [r0]
	ldr r1, _0808C4D8 @ =0x00020001
	ands r0, r1
	cmp r0, r1
	bne _0808C4A6
	strb r5, [r4, #0xf]
	b _0808C4DE
	.align 2, 0
_0808C4D8: .4byte 0x00020001
_0808C4DC:
	strb r0, [r4, #0xf]
_0808C4DE:
	movs r0, #0
_0808C4E0:
	pop {r4, r5}
	pop {r1}
	bx r1
	.align 2, 0
