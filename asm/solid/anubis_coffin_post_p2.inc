	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start coffin_080cdf38
coffin_080cdf38: @ 0x080CDF38
	push {r4, r5, lr}
	adds r4, r0, #0
	ldr r5, [r4, #0x28]
	ldrb r0, [r4, #0xe]
	cmp r0, #1
	beq _080CE03A
	cmp r0, #1
	bgt _080CDF4E
	cmp r0, #0
	beq _080CDF5C
	b _080CE0C4
_080CDF4E:
	cmp r0, #2
	bne _080CDF54
	b _080CE054
_080CDF54:
	cmp r0, #3
	bne _080CDF5A
	b _080CE098
_080CDF5A:
	b _080CE0C4
_080CDF5C:
	ldrb r1, [r4, #0xb]
	movs r0, #8
	orrs r0, r1
	strb r0, [r4, #0xb]
	ldr r0, _080CDF8C @ =0x08370238
	str r0, [r4, #0x30]
	movs r0, #1
	strh r0, [r4, #0x26]
	ldrb r0, [r4, #0x13]
	cmp r0, #0
	beq _080CDFBC
	ldrb r0, [r4, #0x12]
	cmp r0, #0
	bne _080CDF94
	movs r1, #0x96
	lsls r1, r1, #7
	adds r0, r4, #0
	bl SetMotion
	adds r1, r5, #0
	adds r1, #0xb8
	ldr r0, [r1]
	ldr r2, _080CDF90 @ =0xFFFF7800
	b _080CDFA6
	.align 2, 0
_080CDF8C: .4byte 0x08370238
_080CDF90: .4byte 0xFFFF7800
_080CDF94:
	ldr r1, _080CDFB8 @ =0x00004B01
	adds r0, r4, #0
	bl SetMotion
	adds r1, r5, #0
	adds r1, #0xb8
	ldr r0, [r1]
	movs r2, #0x88
	lsls r2, r2, #8
_080CDFA6:
	adds r0, r0, r2
	str r0, [r4, #0x54]
	adds r2, r1, #0
	adds r1, r4, #0
	adds r1, #0xb8
	ldr r0, [r2]
	str r0, [r1]
	b _080CE000
	.align 2, 0
_080CDFB8: .4byte 0x00004B01
_080CDFBC:
	ldr r0, _080CDFDC @ =pZero2
	ldr r0, [r0]
	ldr r0, [r0, #0x54]
	str r0, [r4, #0x54]
	ldrb r0, [r4, #0x12]
	cmp r0, #0
	bne _080CDFE4
	movs r1, #0x96
	lsls r1, r1, #7
	adds r0, r4, #0
	bl SetMotion
	ldr r1, [r4, #0x54]
	ldr r2, _080CDFE0 @ =0xFFFFD000
	b _080CDFF2
	.align 2, 0
_080CDFDC: .4byte pZero2
_080CDFE0: .4byte 0xFFFFD000
_080CDFE4:
	ldr r1, _080CE050 @ =0x00004B01
	adds r0, r4, #0
	bl SetMotion
	ldr r1, [r4, #0x54]
	movs r2, #0xc0
	lsls r2, r2, #6
_080CDFF2:
	adds r0, r1, r2
	str r0, [r4, #0x54]
	adds r0, r4, #0
	adds r0, #0xb8
	str r1, [r0]
	adds r2, r5, #0
	adds r2, #0xb8
_080CE000:
	movs r0, #0xc
	strb r0, [r4, #0x13]
	ldr r0, [r2]
	adds r1, r5, #0
	adds r1, #0xbc
	ldr r1, [r1]
	bl FUN_08009f6c
	str r0, [r4, #0x58]
	adds r1, r4, #0
	adds r1, #0xb4
	str r0, [r1]
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	movs r2, #0
	bl FUN_080bf438
	ldr r0, [r4, #0x58]
	movs r1, #0x80
	lsls r1, r1, #6
	adds r0, r0, r1
	str r0, [r4, #0x58]
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
	strb r0, [r4, #0xa]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080CE03A:
	ldrb r0, [r4, #0x13]
	subs r0, #1
	strb r0, [r4, #0x13]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080CE0C4
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
	b _080CE0C4
	.align 2, 0
_080CE050: .4byte 0x00004B01
_080CE054:
	adds r0, r4, #0
	bl GetEntityPalID
	adds r1, r0, #0
	lsls r1, r1, #0x18
	lsrs r1, r1, #0x13
	movs r2, #0x80
	lsls r2, r2, #2
	adds r0, r2, #0
	orrs r1, r0
	movs r0, #0x46
	bl StartPaletteAnimation
	ldrb r0, [r4, #0x12]
	lsls r0, r0, #2
	adds r0, #0x16
	adds r1, r4, #0
	adds r1, #0x25
	strb r0, [r1]
	ldrb r1, [r4, #0xa]
	movs r0, #1
	orrs r0, r1
	strb r0, [r4, #0xa]
	ldr r0, _080CE0CC @ =0xFFFFFD00
	str r0, [r4, #0x60]
	adds r2, r4, #0
	adds r2, #0x49
	ldrb r0, [r2]
	movs r1, #0xc
	orrs r0, r1
	strb r0, [r2]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080CE098:
	ldr r1, [r4, #0x58]
	ldr r0, [r4, #0x60]
	adds r1, r1, r0
	str r1, [r4, #0x58]
	adds r0, r4, #0
	adds r0, #0xb4
	ldr r0, [r0]
	ldr r2, _080CE0D0 @ =0xFFFFE400
	adds r0, r0, r2
	cmp r1, r0
	bge _080CE0B8
	str r0, [r4, #0x58]
	movs r1, #0
	movs r0, #1
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_080CE0B8:
	movs r0, #0x46
	bl StepPaletteAnimation
	adds r0, r4, #0
	bl UpdateMotionGraphic
_080CE0C4:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080CE0CC: .4byte 0xFFFFFD00
_080CE0D0: .4byte 0xFFFFE400
