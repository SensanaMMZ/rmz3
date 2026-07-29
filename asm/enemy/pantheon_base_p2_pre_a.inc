	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start pBase_0808a194
pBase_0808a194: @ 0x0808A194
	push {r4, lr}
	adds r4, r0, #0
	adds r0, #0xb4
	ldr r0, [r0]
	cmp r0, #0
	bne _0808A208
	ldr r1, [r4, #0x28]
	ldrb r0, [r4, #0xf]
	cmp r0, #0
	beq _0808A1AE
	cmp r0, #1
	beq _0808A1F0
	b _0808A208
_0808A1AE:
	adds r0, r4, #0
	bl IsFrozen
	cmp r0, #0
	beq _0808A208
	ldr r1, _0808A1E8 @ =0x0836896C
	ldrb r0, [r4, #0xd]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r1, [r0]
	adds r0, r4, #0
	bl _call_via_r1
	ldr r1, _0808A1EC @ =0x08368974
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
	movs r0, #1
	b _0808A20A
	.align 2, 0
_0808A1E8: .4byte 0x0836896C
_0808A1EC: .4byte 0x08368974
_0808A1F0:
	ldr r0, [r1, #0x54]
	str r0, [r4, #0x54]
	ldr r0, [r1, #0x58]
	str r0, [r4, #0x58]
	adds r0, r4, #0
	bl IsFrozen
	cmp r0, #0
	beq _0808A206
	movs r0, #1
	b _0808A20A
_0808A206:
	strb r0, [r4, #0xf]
_0808A208:
	movs r0, #0
_0808A20A:
	pop {r4}
	pop {r1}
	bx r1
