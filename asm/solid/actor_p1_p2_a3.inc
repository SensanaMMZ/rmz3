	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start Actor27_Update
Actor27_Update: @ 0x080D36B8
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xd]
	cmp r0, #9
	bls _080D36C4
	b _080D3890
_080D36C4:
	lsls r0, r0, #2
	ldr r1, _080D36D0 @ =_080D36D4
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_080D36D0: .4byte _080D36D4
_080D36D4: @ jump table
	.4byte _080D36FC @ case 0
	.4byte _080D3732 @ case 1
	.4byte _080D374C @ case 2
	.4byte _080D3760 @ case 3
	.4byte _080D378E @ case 4
	.4byte _080D37B4 @ case 5
	.4byte _080D37C6 @ case 6
	.4byte _080D37FA @ case 7
	.4byte _080D3828 @ case 8
	.4byte _080D3890 @ case 9
_080D36FC:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	bl FUN_08009f6c
	str r0, [r4, #0x58]
	ldr r2, _080D3740 @ =wDynamicGraphicTilenums
	movs r3, #0xa4
	lsls r3, r3, #1
	adds r2, r2, r3
	ldrh r0, [r2]
	str r0, [r4, #0x64]
	ldr r1, _080D3744 @ =wDynamicMotionPalIDs
	adds r1, r1, r3
	ldrh r0, [r1]
	str r0, [r4, #0x68]
	ldr r0, _080D3748 @ =0x00000305
	strh r0, [r2]
	movs r0, #9
	strh r0, [r1]
	movs r1, #0xa4
	lsls r1, r1, #8
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xd]
	adds r0, #1
	strb r0, [r4, #0xd]
_080D3732:
	ldr r0, [r4, #0x18]
	ldrb r1, [r0, #9]
	movs r0, #1
	ands r0, r1
	cmp r0, #0
	beq _080D37A8
	b _080D379A
	.align 2, 0
_080D3740: .4byte wDynamicGraphicTilenums
_080D3744: .4byte wDynamicMotionPalIDs
_080D3748: .4byte 0x00000305
_080D374C:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	beq _080D375E
	b _080D3890
_080D375E:
	b _080D388A
_080D3760:
	movs r1, #0xa4
	lsls r1, r1, #8
	adds r0, r4, #0
	bl SetMotion
	movs r2, #0
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	adds r0, #0x4c
	strb r2, [r0]
	adds r2, r4, #0
	adds r2, #0x4a
	ldrb r1, [r2]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r2]
	ldrb r0, [r4, #0xd]
	adds r0, #1
	strb r0, [r4, #0xd]
_080D378E:
	ldr r0, [r4, #0x18]
	ldrb r1, [r0, #9]
	movs r0, #1
	ands r0, r1
	cmp r0, #0
	bne _080D37A8
_080D379A:
	ldr r1, _080D37B0 @ =0x0000A408
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xd]
	adds r0, #1
	strb r0, [r4, #0xd]
_080D37A8:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	b _080D3890
	.align 2, 0
_080D37B0: .4byte 0x0000A408
_080D37B4:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _080D3890
	b _080D388A
_080D37C6:
	movs r1, #0xa4
	lsls r1, r1, #8
	adds r0, r4, #0
	bl SetMotion
	movs r2, #1
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	orrs r0, r1
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	adds r0, #0x4c
	strb r2, [r0]
	adds r3, r4, #0
	adds r3, #0x4a
	movs r2, #0x10
	ldrb r1, [r3]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	orrs r0, r2
	strb r0, [r3]
	strb r2, [r4, #0x12]
	ldrb r0, [r4, #0xd]
	adds r0, #1
	strb r0, [r4, #0xd]
_080D37FA:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080D3890
	ldr r1, _080D3820 @ =0x0000A405
	adds r0, r4, #0
	bl SetMotion
	ldr r0, _080D3824 @ =0xFFFFFB00
	str r0, [r4, #0x60]
	ldr r0, [r4, #0x58]
	str r0, [r4, #0x5c]
	b _080D388A
	.align 2, 0
_080D3820: .4byte 0x0000A405
_080D3824: .4byte 0xFFFFFB00
_080D3828:
	ldr r0, [r4, #0x54]
	movs r1, #0xb8
	lsls r1, r1, #1
	adds r0, r0, r1
	str r0, [r4, #0x54]
	ldr r0, [r4, #0x58]
	ldr r1, [r4, #0x60]
	adds r0, r0, r1
	str r0, [r4, #0x58]
	adds r1, #0x40
	str r1, [r4, #0x60]
	cmp r1, #0
	ble _080D385A
	ldrb r0, [r4, #0x1e]
	lsls r0, r0, #8
	adds r1, r4, #0
	adds r1, #0x70
	ldrb r1, [r1]
	orrs r0, r1
	ldr r1, _080D3898 @ =0x0000A406
	cmp r0, r1
	beq _080D385A
	adds r0, r4, #0
	bl SetMotion
_080D385A:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldr r0, [r4, #0x5c]
	movs r1, #0xd0
	lsls r1, r1, #6
	adds r0, r0, r1
	ldr r1, [r4, #0x58]
	cmp r0, r1
	bge _080D3890
	ldr r0, _080D389C @ =wDynamicGraphicTilenums
	movs r2, #0xa4
	lsls r2, r2, #1
	adds r0, r0, r2
	ldr r1, [r4, #0x64]
	strh r1, [r0]
	ldr r0, _080D38A0 @ =wDynamicMotionPalIDs
	adds r0, r0, r2
	ldr r1, [r4, #0x68]
	strh r1, [r0]
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
	strb r0, [r4, #0xa]
_080D388A:
	ldrb r0, [r4, #0xd]
	adds r0, #1
	strb r0, [r4, #0xd]
_080D3890:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080D3898: .4byte 0x0000A406
_080D389C: .4byte wDynamicGraphicTilenums
_080D38A0: .4byte wDynamicMotionPalIDs

