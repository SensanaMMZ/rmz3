	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_0808fc10
FUN_0808fc10: @ 0x0808FC10
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _0808FC20
	cmp r0, #1
	beq _0808FC8E
	b _0808FCD8
_0808FC20:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _0808FC38 @ =0x08369554
	bl SetDDP
	ldrb r2, [r4, #0x12]
	cmp r2, #0
	beq _0808FC3C
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	orrs r0, r1
	b _0808FC42
	.align 2, 0
_0808FC38: .4byte 0x08369554
_0808FC3C:
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
_0808FC42:
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
	ldrb r1, [r4, #0x12]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #8
	ldr r1, _0808FCE0 @ =0xFFFFFE80
	adds r0, r0, r1
	str r0, [r4, #0x5c]
	movs r0, #0x80
	lsls r0, r0, #2
	bl Sqrt
	strb r0, [r4, #0x13]
	ldrb r0, [r4, #0x13]
	lsls r0, r0, #6
	rsbs r0, r0, #0
	str r0, [r4, #0x60]
	ldr r1, _0808FCE4 @ =0x0000770B
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0808FC8E:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	ldr r0, [r4, #0x60]
	adds r0, #0x40
	str r0, [r4, #0x60]
	movs r2, #0xe0
	lsls r2, r2, #3
	cmp r0, r2
	ble _0808FCAC
	str r2, [r4, #0x60]
_0808FCAC:
	ldr r1, [r4, #0x58]
	ldr r0, [r4, #0x60]
	adds r1, r1, r0
	str r1, [r4, #0x58]
	ldr r0, [r4, #0x54]
	adds r1, r1, r2
	bl FUN_080098a4
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _0808FCD8
	ldr r1, _0808FCE8 @ =gEnemyFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r4, #0x14]
	movs r0, #0
	strb r0, [r4, #0xd]
_0808FCD8:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_0808FCE0: .4byte 0xFFFFFE80
_0808FCE4: .4byte 0x0000770B
_0808FCE8: .4byte gEnemyFnTable
