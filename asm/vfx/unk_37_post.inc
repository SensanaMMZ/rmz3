	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080bc8c0
FUN_080bc8c0: @ 0x080BC8C0
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _080BC8D0
	cmp r0, #1
	beq _080BC8EA
	b _080BC968
_080BC8D0:
	adds r1, r4, #0
	adds r1, #0x25
	movs r0, #0x19
	strb r0, [r1]
	ldr r1, _080BC924 @ =0x00003001
	adds r0, r4, #0
	bl SetMotion
	movs r0, #0x20
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080BC8EA:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	ldr r1, [r4, #0x60]
	adds r1, #3
	str r1, [r4, #0x60]
	ldr r0, [r4, #0x58]
	adds r0, r0, r1
	str r0, [r4, #0x58]
	ldrb r0, [r4, #0x12]
	subs r1, r0, #1
	movs r2, #0
	strb r1, [r4, #0x12]
	lsls r0, r1, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #7
	bhi _080BC928
	movs r0, #2
	ands r1, r0
	cmp r1, #0
	bne _080BC93C
	ldrb r0, [r4, #0xa]
	movs r1, #1
	orrs r0, r1
	b _080BC942
	.align 2, 0
_080BC924: .4byte 0x00003001
_080BC928:
	cmp r0, #0xf
	bhi _080BC944
	movs r0, #1
	ands r1, r0
	cmp r1, #0
	bne _080BC93C
	ldrb r0, [r4, #0xa]
	movs r1, #1
	orrs r0, r1
	b _080BC942
_080BC93C:
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
_080BC942:
	strb r0, [r4, #0xa]
_080BC944:
	ldrb r0, [r4, #0x12]
	cmp r0, #0
	bne _080BC968
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r4, #0xa]
	ldr r1, _080BC970 @ =gVFXFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r4, #0x14]
_080BC968:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080BC970: .4byte gVFXFnTable

	thumb_func_start FUN_080bc974
FUN_080bc974: @ 0x080BC974
	push {r4, r5, lr}
	adds r5, r0, #0
	ldrb r0, [r5, #0xe]
	cmp r0, #0
	beq _080BC984
	cmp r0, #1
	beq _080BC9C4
	b _080BCA50
_080BC984:
	adds r1, r5, #0
	adds r1, #0x25
	movs r0, #0x19
	strb r0, [r1]
	ldrb r0, [r5, #0x12]
	subs r1, #3
	strb r0, [r1]
	ldr r4, _080BCA00 @ =0x0836EDF8
	ldr r2, _080BCA04 @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _080BCA08 @ =0x000343FD
	muls r0, r1, r0
	ldr r1, _080BCA0C @ =0x00269EC3
	adds r0, r0, r1
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r2]
	lsrs r0, r0, #0x11
	movs r1, #3
	bl __umodsi3
	lsls r0, r0, #1
	adds r0, r0, r4
	ldrh r1, [r0]
	adds r0, r5, #0
	bl SetMotion
	movs r0, #0x28
	strb r0, [r5, #0x12]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_080BC9C4:
	adds r0, r5, #0
	bl UpdateMotionGraphic
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x5c]
	adds r0, r0, r1
	str r0, [r5, #0x54]
	ldr r1, [r5, #0x60]
	adds r1, #0xc
	str r1, [r5, #0x60]
	ldr r0, [r5, #0x58]
	adds r0, r0, r1
	str r0, [r5, #0x58]
	ldrb r0, [r5, #0x12]
	subs r1, r0, #1
	movs r2, #0
	strb r1, [r5, #0x12]
	lsls r0, r1, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #7
	bhi _080BCA10
	movs r0, #2
	ands r1, r0
	cmp r1, #0
	bne _080BCA24
	ldrb r0, [r5, #0xa]
	movs r1, #1
	orrs r0, r1
	b _080BCA2A
	.align 2, 0
_080BCA00: .4byte 0x0836EDF8
_080BCA04: .4byte RNG_0202f388
_080BCA08: .4byte 0x000343FD
_080BCA0C: .4byte 0x00269EC3
_080BCA10:
	cmp r0, #0xf
	bhi _080BCA2C
	movs r0, #1
	ands r1, r0
	cmp r1, #0
	bne _080BCA24
	ldrb r0, [r5, #0xa]
	movs r1, #1
	orrs r0, r1
	b _080BCA2A
_080BCA24:
	ldrb r1, [r5, #0xa]
	movs r0, #0xfe
	ands r0, r1
_080BCA2A:
	strb r0, [r5, #0xa]
_080BCA2C:
	ldrb r0, [r5, #0x12]
	cmp r0, #0
	bne _080BCA50
	ldrb r1, [r5, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r5, #0xa]
	ldr r1, _080BCA58 @ =gVFXFnTable
	ldrb r0, [r5, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r5, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r5, #0x14]
_080BCA50:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080BCA58: .4byte gVFXFnTable

	thumb_func_start FUN_080bca5c
FUN_080bca5c: @ 0x080BCA5C
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

	thumb_func_start FUN_080bcb6c
FUN_080bcb6c: @ 0x080BCB6C
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #5
	bls _080BCB78
	b _080BCC8E
_080BCB78:
	lsls r0, r0, #2
	ldr r1, _080BCB84 @ =_080BCB88
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_080BCB84: .4byte _080BCB88
_080BCB88: @ jump table
	.4byte _080BCBA0 @ case 0
	.4byte _080BCBBC @ case 1
	.4byte _080BCBEA @ case 2
	.4byte _080BCC12 @ case 3
	.4byte _080BCC2E @ case 4
	.4byte _080BCC3E @ case 5
_080BCBA0:
	adds r1, r4, #0
	adds r1, #0x25
	movs r0, #0x11
	strb r0, [r1]
	movs r0, #6
	strb r0, [r4, #0x12]
	movs r1, #0xcc
	lsls r1, r1, #6
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080BCBBC:
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080BCBCE
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080BCBCE:
	ldrb r1, [r4, #0x12]
	movs r0, #1
	ands r0, r1
	cmp r0, #0
	beq _080BCBE0
	ldrb r0, [r4, #0xa]
	movs r1, #1
	orrs r0, r1
	b _080BCBE6
_080BCBE0:
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
_080BCBE6:
	strb r0, [r4, #0xa]
	b _080BCC26
_080BCBEA:
	ldrb r1, [r4, #0xa]
	movs r0, #1
	orrs r0, r1
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	bl GetEntityPalID
	adds r1, r0, #0
	lsls r1, r1, #0x18
	lsrs r1, r1, #0x13
	movs r2, #0x80
	lsls r2, r2, #2
	adds r0, r2, #0
	orrs r1, r0
	movs r0, #0x18
	bl StartPaletteAnimation
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080BCC12:
	movs r0, #0x18
	bl StepPaletteAnimation
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #3
	bne _080BCC26
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080BCC26:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	b _080BCC8E
_080BCC2E:
	movs r0, #0x18
	bl RemovePaletteAnimation
	movs r0, #6
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080BCC3E:
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080BCC68
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r4, #0xa]
	ldr r1, _080BCC7C @ =gVFXFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r4, #0x14]
_080BCC68:
	ldrb r1, [r4, #0x12]
	movs r0, #1
	ands r0, r1
	cmp r0, #0
	beq _080BCC80
	ldrb r0, [r4, #0xa]
	movs r1, #1
	orrs r0, r1
	b _080BCC86
	.align 2, 0
_080BCC7C: .4byte gVFXFnTable
_080BCC80:
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
_080BCC86:
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	bl UpdateMotionGraphic
_080BCC8E:
	pop {r4}
	pop {r0}
	bx r0
