	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080834fc
FUN_080834fc: @ 0x080834FC
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r5, [r4, #0xe]
	cmp r5, #0
	beq _0808350C
	cmp r5, #1
	beq _0808356C
	b _080835A2
_0808350C:
	ldrb r1, [r4, #0xb]
	movs r0, #0x10
	orrs r0, r1
	strb r0, [r4, #0xb]
	ldr r0, [r4, #0x28]
	ldrb r0, [r0, #0x1c]
	strb r0, [r4, #0x1d]
	ldr r1, _080835A8 @ =0x00000901
	adds r0, r4, #0
	bl SetMotion
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	adds r0, #0x4c
	strb r5, [r0]
	adds r2, r4, #0
	adds r2, #0x4a
	ldrb r1, [r2]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r2]
	ldrb r1, [r4, #0xa]
	movs r0, #0xdf
	ands r0, r1
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	adds r0, #0x4d
	strb r5, [r0]
	ldrb r1, [r2]
	movs r0, #0x21
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r2]
	str r5, [r4, #0x60]
	str r5, [r4, #0x5c]
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _080835AC @ =0x08368268
	bl SetDDP
	strb r5, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0808356C:
	ldrb r0, [r4, #0x12]
	adds r0, #2
	strb r0, [r4, #0x12]
	ldr r1, _080835B0 @ =gSineTable
	ldrb r0, [r4, #0x12]
	lsls r0, r0, #1
	adds r0, r0, r1
	movs r1, #0
	ldrsh r2, [r0, r1]
	lsls r2, r2, #1
	adds r0, r4, #0
	adds r0, #0xb8
	ldr r3, [r4, #0x28]
	ldr r0, [r0]
	ldr r1, [r3, #0x58]
	adds r0, r0, r1
	adds r0, r0, r2
	str r0, [r4, #0x58]
	adds r0, r4, #0
	adds r0, #0xb4
	ldr r0, [r0]
	ldr r1, [r3, #0x54]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	adds r0, r4, #0
	bl UpdateMotionGraphic
_080835A2:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080835A8: .4byte 0x00000901
_080835AC: .4byte 0x08368268
_080835B0: .4byte gSineTable
