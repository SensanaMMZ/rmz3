	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_0808cf94
FUN_0808cf94: @ 0x0808CF94
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	adds r5, r0, #0
	ldrb r6, [r5, #0xe]
	cmp r6, #0
	beq _0808CFA6
	cmp r6, #1
	beq _0808D05E
	b _0808D0A4
_0808CFA6:
	movs r7, #0
	ldr r0, _0808D020 @ =pZero2
	ldr r0, [r0]
	ldr r0, [r0, #0x54]
	ldr r1, [r5, #0x54]
	subs r0, r0, r1
	cmp r0, #0
	ble _0808CFB8
	movs r7, #1
_0808CFB8:
	lsls r4, r7, #8
	subs r0, r1, r4
	str r0, [r5, #0x54]
	ldr r1, _0808D024 @ =0x00007202
	adds r0, r5, #0
	bl SetMotion
	adds r0, r5, #0
	adds r0, #0x8c
	str r6, [r0]
	adds r0, #4
	str r6, [r0]
	adds r0, #4
	strb r6, [r0]
	ldrb r1, [r5, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r5, #0xa]
	ldr r0, [r5, #0x54]
	str r0, [sp, #0xc]
	ldr r0, [r5, #0x58]
	str r0, [sp, #0x10]
	movs r2, #0x80
	lsls r2, r2, #2
	movs r0, #0
	add r1, sp, #0xc
	adds r3, r7, #0
	bl FUN_080b2b40
	movs r0, #0x80
	subs r0, r0, r4
	str r0, [sp, #0xc]
	movs r0, #0x60
	str r0, [sp, #0x10]
	adds r0, r5, #0
	adds r0, #0xb8
	ldrb r0, [r0]
	cmp r0, #0
	beq _0808D02C
	adds r1, r5, #0
	adds r1, #0x54
	ldr r0, _0808D028 @ =0x08369130
	str r0, [sp]
	movs r0, #0x18
	str r0, [sp, #4]
	adds r0, r5, #0
	add r2, sp, #0xc
	movs r3, #0x20
	bl FUN_080b84f4
	b _0808D046
	.align 2, 0
_0808D020: .4byte pZero2
_0808D024: .4byte 0x00007202
_0808D028: .4byte 0x08369130
_0808D02C:
	adds r1, r5, #0
	adds r1, #0x54
	ldr r0, _0808D0AC @ =0x08369130
	str r0, [sp]
	movs r0, #0x18
	str r0, [sp, #4]
	movs r0, #0x19
	str r0, [sp, #8]
	adds r0, r5, #0
	add r2, sp, #0xc
	movs r3, #0x20
	bl FUN_080b85fc
_0808D046:
	ldr r0, [sp, #0xc]
	lsrs r1, r0, #0x1f
	adds r0, r0, r1
	asrs r0, r0, #1
	str r0, [r5, #0x5c]
	movs r0, #0
	str r0, [r5, #0x60]
	movs r0, #0x18
	strb r0, [r5, #0x12]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_0808D05E:
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x5c]
	adds r0, r0, r1
	str r0, [r5, #0x54]
	ldr r0, [r5, #0x60]
	adds r0, #0x15
	str r0, [r5, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _0808D076
	str r1, [r5, #0x60]
_0808D076:
	ldr r0, [r5, #0x58]
	ldr r1, [r5, #0x60]
	adds r0, r0, r1
	str r0, [r5, #0x58]
	adds r0, r5, #0
	bl UpdateMotionGraphic
	ldrb r0, [r5, #0x12]
	subs r0, #1
	strb r0, [r5, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _0808D09E
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x58]
	bl FUN_080098a4
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _0808D0A4
_0808D09E:
	adds r0, r5, #0
	bl FUN_0808cefc
_0808D0A4:
	add sp, #0x14
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_0808D0AC: .4byte 0x08369130
