	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_08062c78
FUN_08062c78: @ 0x08062C78
	push {r4, r5, r6, lr}
	adds r4, r0, #0
	ldr r1, [r4, #0x28]
	ldr r0, [r1, #0x54]
	str r0, [r4, #0x54]
	ldr r0, [r1, #0x58]
	ldr r1, _08062C9C @ =0xFFFFEE00
	adds r0, r0, r1
	str r0, [r4, #0x58]
	ldrb r0, [r4, #0xe]
	cmp r0, #5
	bls _08062C92
	b _08062E1E
_08062C92:
	lsls r0, r0, #2
	ldr r1, _08062CA0 @ =_08062CA4
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_08062C9C: .4byte 0xFFFFEE00
_08062CA0: .4byte _08062CA4
_08062CA4: @ jump table
	.4byte _08062CBC @ case 0
	.4byte _08062D90 @ case 1
	.4byte _08062CD8 @ case 2
	.4byte _08062D90 @ case 3
	.4byte _08062DBC @ case 4
	.4byte _08062DD2 @ case 5
_08062CBC:
	ldrb r0, [r4, #0x13]
	cmp r0, #0
	bne _08062CC8
	ldr r0, [r4, #0x64]
	adds r0, #1
	b _08062CCA
_08062CC8:
	movs r0, #0
_08062CCA:
	str r0, [r4, #0x64]
	movs r0, #0
	strb r0, [r4, #0x13]
	ldr r1, _08062CD4 @ =0x0000D609
	b _08062D84
	.align 2, 0
_08062CD4: .4byte 0x0000D609
_08062CD8:
	movs r1, #0xa0
	lsls r1, r1, #5
	ldr r2, _08062DA8 @ =0xFFFFBB00
	adds r0, r4, #0
	bl FUN_08061b68
	ldr r5, _08062DAC @ =0xFFFFF500
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _08062CF4
	movs r5, #0xb0
	lsls r5, r5, #4
_08062CF4:
	ldr r3, _08062DB0 @ =gSineTable
	adds r0, r4, #0
	adds r0, #0xb8
	ldrh r0, [r0]
	lsls r0, r0, #0x10
	asrs r1, r0, #0x18
	adds r0, r1, #0
	adds r0, #0x40
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x17
	adds r0, r0, r3
	movs r6, #0
	ldrsh r2, [r0, r6]
	adds r0, r5, #0
	muls r0, r2, r0
	cmp r0, #0
	bge _08062D18
	adds r0, #0xff
_08062D18:
	asrs r6, r0, #8
	lsls r0, r1, #0x18
	lsrs r0, r0, #0x17
	adds r0, r0, r3
	movs r1, #0
	ldrsh r3, [r0, r1]
	rsbs r1, r3, #0
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r1
	lsls r0, r0, #8
	rsbs r0, r0, #0
	cmp r0, #0
	bge _08062D3C
	adds r0, #0xff
_08062D3C:
	asrs r0, r0, #8
	adds r6, r6, r0
	adds r0, r5, #0
	muls r0, r3, r0
	cmp r0, #0
	bge _08062D4A
	adds r0, #0xff
_08062D4A:
	asrs r5, r0, #8
	lsls r0, r2, #1
	adds r0, r0, r2
	lsls r0, r0, #2
	adds r0, r0, r2
	lsls r0, r0, #2
	adds r0, r0, r2
	lsls r0, r0, #8
	rsbs r0, r0, #0
	cmp r0, #0
	bge _08062D62
	adds r0, #0xff
_08062D62:
	asrs r0, r0, #8
	adds r5, r5, r0
	ldr r0, _08062DB4 @ =0x0000012F
	bl PlaySound
	ldr r0, [r4, #0x54]
	adds r0, r0, r6
	ldr r1, [r4, #0x58]
	adds r1, r1, r5
	ldrb r2, [r4, #0xa]
	lsrs r2, r2, #4
	movs r3, #1
	ands r2, r3
	movs r3, #0
	bl FUN_080b1698
	ldr r1, _08062DB8 @ =0x0000D60B
_08062D84:
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08062D90:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _08062E1E
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
	b _08062E1E
	.align 2, 0
_08062DA8: .4byte 0xFFFFBB00
_08062DAC: .4byte 0xFFFFF500
_08062DB0: .4byte gSineTable
_08062DB4: .4byte 0x0000012F
_08062DB8: .4byte 0x0000D60B
_08062DBC:
	movs r0, #0x2d
	str r0, [r4, #0x68]
	ldr r1, _08062DEC @ =0x0000D603
	adds r0, r4, #0
	movs r2, #0xa
	movs r3, #1
	bl GotoMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08062DD2:
	ldr r0, [r4, #0x68]
	subs r3, r0, #1
	str r3, [r4, #0x68]
	cmp r3, #0
	bne _08062E18
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _08062DF0
	movs r0, #0xd
	b _08062E14
	.align 2, 0
_08062DEC: .4byte 0x0000D603
_08062DF0:
	ldr r0, [r4, #0x64]
	cmp r0, #0
	bgt _08062E12
	ldr r2, _08062E24 @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _08062E28 @ =0x000343FD
	muls r0, r1, r0
	ldr r6, _08062E2C @ =0x00269EC3
	adds r0, r0, r6
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r2]
	lsrs r0, r0, #0x11
	movs r1, #0xf
	ands r0, r1
	cmp r0, #5
	bls _08062E16
_08062E12:
	movs r0, #0xc
_08062E14:
	strb r0, [r4, #0xd]
_08062E16:
	strb r3, [r4, #0xe]
_08062E18:
	adds r0, r4, #0
	bl UpdateMotionGraphic
_08062E1E:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_08062E24: .4byte RNG_0202f388
_08062E28: .4byte 0x000343FD
_08062E2C: .4byte 0x00269EC3

	thumb_func_start FUN_08062e30
FUN_08062e30: @ 0x08062E30
	push {r4, r5, r6, lr}
	adds r4, r0, #0
	ldr r1, [r4, #0x28]
	ldr r0, [r1, #0x54]
	str r0, [r4, #0x54]
	ldr r0, [r1, #0x58]
	ldr r1, _08062E54 @ =0xFFFFEE00
	adds r0, r0, r1
	str r0, [r4, #0x58]
	ldrb r0, [r4, #0xe]
	cmp r0, #5
	bls _08062E4A
	b _08062FCE
_08062E4A:
	lsls r0, r0, #2
	ldr r1, _08062E58 @ =_08062E5C
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_08062E54: .4byte 0xFFFFEE00
_08062E58: .4byte _08062E5C
_08062E5C: @ jump table
	.4byte _08062E74 @ case 0
	.4byte _08062F3E @ case 1
	.4byte _08062E90 @ case 2
	.4byte _08062F3E @ case 3
	.4byte _08062F6C @ case 4
	.4byte _08062F82 @ case 5
_08062E74:
	ldrb r0, [r4, #0x13]
	cmp r0, #1
	bne _08062E80
	ldr r0, [r4, #0x64]
	adds r0, #1
	b _08062E82
_08062E80:
	movs r0, #0
_08062E82:
	str r0, [r4, #0x64]
	movs r0, #1
	strb r0, [r4, #0x13]
	ldr r1, _08062E8C @ =0x0000D60A
	b _08062F32
	.align 2, 0
_08062E8C: .4byte 0x0000D60A
_08062E90:
	movs r1, #0xa0
	lsls r1, r1, #5
	ldr r2, _08062F58 @ =0xFFFFBB00
	adds r0, r4, #0
	bl FUN_08061b68
	ldr r5, _08062F5C @ =0xFFFFF500
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _08062EAC
	movs r5, #0xb0
	lsls r5, r5, #4
_08062EAC:
	ldr r3, _08062F60 @ =gSineTable
	adds r0, r4, #0
	adds r0, #0xb8
	ldrh r0, [r0]
	lsls r0, r0, #0x10
	asrs r1, r0, #0x18
	adds r0, r1, #0
	adds r0, #0x40
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x17
	adds r0, r0, r3
	movs r6, #0
	ldrsh r2, [r0, r6]
	adds r0, r5, #0
	muls r0, r2, r0
	cmp r0, #0
	bge _08062ED0
	adds r0, #0xff
_08062ED0:
	asrs r6, r0, #8
	lsls r0, r1, #0x18
	lsrs r0, r0, #0x17
	adds r0, r0, r3
	movs r1, #0
	ldrsh r3, [r0, r1]
	rsbs r1, r3, #0
	lsls r0, r1, #2
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r1
	lsls r0, r0, #8
	rsbs r0, r0, #0
	cmp r0, #0
	bge _08062EF0
	adds r0, #0xff
_08062EF0:
	asrs r0, r0, #8
	adds r6, r6, r0
	adds r0, r5, #0
	muls r0, r3, r0
	cmp r0, #0
	bge _08062EFE
	adds r0, #0xff
_08062EFE:
	asrs r5, r0, #8
	lsls r0, r2, #2
	adds r0, r0, r2
	lsls r0, r0, #2
	adds r0, r0, r2
	lsls r0, r0, #8
	rsbs r0, r0, #0
	cmp r0, #0
	bge _08062F12
	adds r0, #0xff
_08062F12:
	asrs r0, r0, #8
	adds r5, r5, r0
	ldr r0, _08062F64 @ =0x0000012F
	bl PlaySound
	ldr r0, [r4, #0x54]
	adds r0, r0, r6
	ldr r1, [r4, #0x58]
	adds r1, r1, r5
	ldrb r2, [r4, #0xa]
	lsrs r2, r2, #4
	movs r3, #1
	ands r2, r3
	bl FUN_080b1698
	ldr r1, _08062F68 @ =0x0000D60C
_08062F32:
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08062F3E:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _08062FCE
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
	b _08062FCE
	.align 2, 0
_08062F58: .4byte 0xFFFFBB00
_08062F5C: .4byte 0xFFFFF500
_08062F60: .4byte gSineTable
_08062F64: .4byte 0x0000012F
_08062F68: .4byte 0x0000D60C
_08062F6C:
	movs r0, #0x2d
	str r0, [r4, #0x68]
	ldr r1, _08062F9C @ =0x0000D603
	adds r0, r4, #0
	movs r2, #0xa
	movs r3, #1
	bl GotoMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08062F82:
	ldr r0, [r4, #0x68]
	subs r3, r0, #1
	str r3, [r4, #0x68]
	cmp r3, #0
	bne _08062FC8
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _08062FA0
	movs r0, #0xd
	b _08062FC4
	.align 2, 0
_08062F9C: .4byte 0x0000D603
_08062FA0:
	ldr r0, [r4, #0x64]
	cmp r0, #0
	bgt _08062FC2
	ldr r2, _08062FD4 @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _08062FD8 @ =0x000343FD
	muls r0, r1, r0
	ldr r6, _08062FDC @ =0x00269EC3
	adds r0, r0, r6
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r2]
	lsrs r0, r0, #0x11
	movs r1, #0xf
	ands r0, r1
	cmp r0, #4
	bhi _08062FC6
_08062FC2:
	movs r0, #0xb
_08062FC4:
	strb r0, [r4, #0xd]
_08062FC6:
	strb r3, [r4, #0xe]
_08062FC8:
	adds r0, r4, #0
	bl UpdateMotionGraphic
_08062FCE:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_08062FD4: .4byte RNG_0202f388
_08062FD8: .4byte 0x000343FD
_08062FDC: .4byte 0x00269EC3

