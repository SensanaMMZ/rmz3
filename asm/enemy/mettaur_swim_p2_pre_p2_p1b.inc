	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_08089790
FUN_08089790: @ 0x08089790
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #5
	bls _0808979C
	b _080898B2
_0808979C:
	lsls r0, r0, #2
	ldr r1, _080897A8 @ =_080897AC
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_080897A8: .4byte _080897AC
_080897AC: @ jump table
	.4byte _080897C4 @ case 0
	.4byte _080897E0 @ case 1
	.4byte _08089830 @ case 2
	.4byte _0808983E @ case 3
	.4byte _08089874 @ case 4
	.4byte _08089882 @ case 5
_080897C4:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _08089828 @ =0x08368814
	bl SetDDP
	ldr r1, _0808982C @ =0x0000DD01
	adds r0, r4, #0
	bl SetMotion
	movs r0, #0
	str r0, [r4, #0x60]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080897E0:
	ldr r1, [r4, #0x5c]
	ldr r2, [r4, #0x60]
	adds r0, r4, #0
	bl FUN_08088bc8
	ldr r1, [r4, #0x5c]
	lsls r0, r1, #4
	subs r0, r0, r1
	lsls r0, r0, #4
	cmp r0, #0
	bge _080897F8
	adds r0, #0xff
_080897F8:
	asrs r0, r0, #8
	str r0, [r4, #0x5c]
	ldr r0, [r4, #0x60]
	adds r0, #0x40
	str r0, [r4, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _0808980C
	str r1, [r4, #0x60]
_0808980C:
	adds r0, r4, #0
	bl FUN_08088ba8
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _0808981E
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0808981E:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	b _080898B2
	.align 2, 0
_08089828: .4byte 0x08368814
_0808982C: .4byte 0x0000DD01
_08089830:
	ldr r1, _08089870 @ =0x0000DD02
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0808983E:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _08089854
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08089854:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	movs r2, #0x80
	lsls r2, r2, #3
	adds r1, r1, r2
	bl FUN_0800a40c
	adds r1, r0, #0
	movs r2, #0x80
	lsls r2, r2, #1
	adds r0, r4, #0
	bl FUN_08088bc8
	b _080898B2
	.align 2, 0
_08089870: .4byte 0x0000DD02
_08089874:
	ldr r1, _080898B8 @ =0x0000DD0D
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08089882:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _08089898
	movs r0, #0
	strb r0, [r4, #0xd]
	strb r0, [r4, #0xe]
_08089898:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	movs r2, #0x80
	lsls r2, r2, #3
	adds r1, r1, r2
	bl FUN_0800a40c
	adds r1, r0, #0
	movs r2, #0x80
	lsls r2, r2, #1
	adds r0, r4, #0
	bl FUN_08088bc8
_080898B2:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080898B8: .4byte 0x0000DD0D
