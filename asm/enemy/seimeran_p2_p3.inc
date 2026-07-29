	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_0808fa70
FUN_0808fa70: @ 0x0808FA70
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _0808FA80
	cmp r0, #1
	beq _0808FAE0
	b _0808FB06
_0808FA80:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _0808FA98 @ =0x08369434
	bl SetDDP
	ldrb r2, [r4, #0x12]
	cmp r2, #0
	beq _0808FA9C
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	orrs r0, r1
	b _0808FAA2
	.align 2, 0
_0808FA98: .4byte 0x08369434
_0808FA9C:
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
_0808FAA2:
	strb r0, [r4, #0xa]
	movs r1, #1
	ands r1, r2
	adds r0, r4, #0
	adds r0, #0x4c
	strb r1, [r0]
	adds r3, r4, #0
	adds r3, #0x4a
	lsls r1, r1, #4
	ldrb r2, [r3]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r1
	strb r0, [r3]
	movs r0, #0x80
	lsls r0, r0, #2
	bl Sqrt
	strb r0, [r4, #0x13]
	ldrb r0, [r4, #0x13]
	lsls r0, r0, #6
	rsbs r0, r0, #0
	str r0, [r4, #0x60]
	ldr r1, _0808FB0C @ =0x00007707
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0808FAE0:
	ldrb r0, [r4, #0x13]
	subs r0, #1
	strb r0, [r4, #0x13]
	lsls r0, r0, #0x18
	lsrs r1, r0, #0x18
	cmp r1, #0
	bne _0808FAF4
	movs r0, #6
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_0808FAF4:
	ldr r1, [r4, #0x60]
	adds r1, #0x40
	str r1, [r4, #0x60]
	ldr r0, [r4, #0x58]
	adds r0, r0, r1
	str r0, [r4, #0x58]
	adds r0, r4, #0
	bl UpdateMotionGraphic
_0808FB06:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_0808FB0C: .4byte 0x00007707

