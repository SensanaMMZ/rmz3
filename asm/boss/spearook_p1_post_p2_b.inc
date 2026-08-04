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
