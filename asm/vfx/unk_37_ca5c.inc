	.include "asm/macros.inc"

	.syntax unified

	.text

	push {r4, r5, r6, r7, lr}
	mov r7, r8
	push {r7}
	adds r4, r0, #0
	ldr r0, [r4, #0x28]
	mov r8, r0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _080BCA74
	cmp r0, #1
	beq _080BCA88
	b _080BCB5E
_080BCA74:
	ldr r0, _080BCB0C @ =0x00003302
	adds r1, r0, #0
	ldrb r0, [r4, #0x12]
	adds r1, r1, r0
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080BCA88:
	ldr r1, _080BCB10 @ =gStageRun+232
	mov ip, r1
	ldr r1, [r1, #0x38]
	subs r0, r1, #1
	adds r5, r0, r1
	lsrs r0, r5, #0x1f
	adds r0, r5, r0
	asrs r0, r0, #1
	adds r5, r0, #0
	mov r0, ip
	ldr r1, [r0, #0x3c]
	subs r0, r1, #1
	adds r3, r0, r1
	lsrs r0, r3, #0x1f
	adds r0, r3, r0
	asrs r7, r0, #1
	adds r3, r7, #0
	mov r1, r8
	ldr r0, [r1, #0x54]
	subs r2, r0, r5
	ldr r1, _080BCB14 @ =0x0836EDFE
	ldrb r0, [r4, #0x12]
	lsls r0, r0, #1
	adds r0, r0, r1
	movs r1, #0
	ldrsh r6, [r0, r1]
	adds r0, r2, #0
	muls r0, r6, r0
	cmp r0, #0
	bge _080BCAC6
	adds r0, #0xff
_080BCAC6:
	asrs r2, r0, #8
	mov r1, r8
	ldr r0, [r1, #0x58]
	subs r1, r0, r7
	adds r0, r1, #0
	muls r0, r6, r0
	cmp r0, #0
	bge _080BCAD8
	adds r0, #0xff
_080BCAD8:
	asrs r1, r0, #8
	adds r0, r5, r2
	str r0, [r4, #0x54]
	adds r0, r3, r1
	str r0, [r4, #0x58]
	ldrb r0, [r4, #0x13]
	adds r0, #1
	strb r0, [r4, #0x13]
	mov r1, r8
	adds r1, #0x54
	mov r0, ip
	bl CalcFromCamera
	cmp r0, #0
	bne _080BCB00
	ldrb r1, [r4, #0x13]
	movs r0, #1
	ands r0, r1
	cmp r0, #0
	beq _080BCB18
_080BCB00:
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
	strb r0, [r4, #0xa]
	b _080BCB24
	.align 2, 0
_080BCB0C: .4byte 0x00003302
_080BCB10: .4byte gStageRun+232
_080BCB14: .4byte 0x0836EDFE
_080BCB18:
	ldrb r0, [r4, #0xa]
	movs r1, #0xfe
	ands r1, r0
	movs r0, #1
	orrs r1, r0
	strb r1, [r4, #0xa]
_080BCB24:
	mov r0, r8
	adds r0, #0xc8
	ldrb r0, [r0]
	cmp r0, #0
	bne _080BCB3A
	mov r1, r8
	ldrb r0, [r1, #0xc]
	cmp r0, #1
	bhi _080BCB3A
	cmp r0, #4
	bne _080BCB58
_080BCB3A:
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r4, #0xa]
	ldr r1, _080BCB68 @ =gVFXFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r4, #0x14]
_080BCB58:
	adds r0, r4, #0
	bl UpdateMotionGraphic
_080BCB5E:
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080BCB68: .4byte gVFXFnTable
