	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_08089694
FUN_08089694: @ 0x08089694
	push {r4, r5, lr}
	sub sp, #8
	adds r5, r0, #0
	ldrb r0, [r5, #0xe]
	cmp r0, #0
	beq _080896A6
	cmp r0, #1
	beq _08089710
	b _0808977E
_080896A6:
	adds r0, r5, #0
	adds r0, #0x74
	ldr r1, _080896D8 @ =0x08368844
	bl SetDDP
	ldr r1, _080896DC @ =0x0000DD04
	adds r0, r5, #0
	bl SetMotion
	movs r2, #0
	ldr r0, _080896E0 @ =pZero2
	ldr r0, [r0]
	ldr r0, [r0, #0x54]
	ldr r1, [r5, #0x54]
	subs r0, r0, r1
	cmp r0, #0
	ble _080896CA
	movs r2, #1
_080896CA:
	cmp r2, #0
	beq _080896E4
	ldrb r1, [r5, #0xa]
	movs r0, #0x10
	orrs r0, r1
	b _080896EA
	.align 2, 0
_080896D8: .4byte 0x08368844
_080896DC: .4byte 0x0000DD04
_080896E0: .4byte pZero2
_080896E4:
	ldrb r1, [r5, #0xa]
	movs r0, #0xef
	ands r0, r1
_080896EA:
	strb r0, [r5, #0xa]
	adds r1, r2, #0
	adds r0, r5, #0
	adds r0, #0x4c
	strb r1, [r0]
	adds r3, r5, #0
	adds r3, #0x4a
	lsls r1, r1, #4
	ldrb r2, [r3]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r1
	strb r0, [r3]
	movs r0, #0x3c
	strb r0, [r5, #0x12]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_08089710:
	ldrb r0, [r5, #0x12]
	subs r0, #1
	strb r0, [r5, #0x12]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0x1e
	bne _08089752
	ldrb r4, [r5, #0xa]
	lsrs r4, r4, #4
	movs r0, #1
	ands r4, r0
	ldr r1, [r5, #0x54]
	ldr r0, _08089788 @ =0xFFFFFA00
	adds r1, r1, r0
	lsls r0, r4, #1
	adds r0, r0, r4
	lsls r0, r0, #0xa
	adds r0, r0, r1
	str r0, [sp]
	ldr r0, [r5, #0x58]
	ldr r1, _0808978C @ =0xFFFFFE00
	adds r0, r0, r1
	str r0, [sp, #4]
	movs r0, #0x2c
	bl PlaySound
	movs r1, #0x80
	lsls r1, r1, #2
	lsls r4, r4, #7
	mov r0, sp
	adds r2, r4, #0
	bl CreateLemon
_08089752:
	ldrb r1, [r5, #0x12]
	cmp r1, #0
	bne _0808975E
	movs r0, #2
	strb r0, [r5, #0xd]
	strb r1, [r5, #0xe]
_0808975E:
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x58]
	movs r2, #0x80
	lsls r2, r2, #3
	adds r1, r1, r2
	bl FUN_0800a40c
	adds r1, r0, #0
	movs r2, #0x80
	lsls r2, r2, #4
	adds r0, r5, #0
	bl FUN_08088bc8
	adds r0, r5, #0
	bl UpdateMotionGraphic
_0808977E:
	add sp, #8
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_08089788: .4byte 0xFFFFFA00
_0808978C: .4byte 0xFFFFFE00

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
