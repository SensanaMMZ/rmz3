	.include "asm/macros.inc"

	.syntax unified

	.text

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
