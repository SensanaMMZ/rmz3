	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start copyx_08057204
copyx_08057204: @ 0x08057204
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _080572B4
	ldr r1, _08057260 @ =0x0000B311
	adds r0, r4, #0
	bl SetMotion
	movs r0, #0
	strb r0, [r4, #0xe]
	strb r0, [r4, #0xf]
	movs r3, #0
	ldr r0, _08057264 @ =pZero2
	ldr r2, [r0]
	ldr r1, [r2, #0x54]
	ldr r0, [r4, #0x54]
	cmp r1, r0
	ble _0805722C
	movs r3, #1
_0805722C:
	adds r0, r4, #0
	adds r0, #0x4c
	strb r3, [r0]
	movs r3, #0
	ldr r1, [r2, #0x54]
	ldr r0, [r4, #0x54]
	cmp r1, r0
	ble _0805723E
	movs r3, #1
_0805723E:
	movs r0, #0x4a
	adds r0, r0, r4
	mov ip, r0
	lsls r2, r3, #4
	ldrb r1, [r0]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	orrs r0, r2
	mov r1, ip
	strb r0, [r1]
	cmp r3, #0
	beq _08057268
	ldrb r0, [r4, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _0805726E
	.align 2, 0
_08057260: .4byte 0x0000B311
_08057264: .4byte pZero2
_08057268:
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
_0805726E:
	strb r0, [r4, #0xa]
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _08057284
	ldr r0, _08057280 @ =0xFFFFFE00
	b _08057288
	.align 2, 0
_08057280: .4byte 0xFFFFFE00
_08057284:
	movs r0, #0x80
	lsls r0, r0, #2
_08057288:
	str r0, [r4, #0x5c]
	ldr r0, _080572C8 @ =0xFFFFFE00
	str r0, [r4, #0x60]
	movs r0, #8
	strb r0, [r4, #0x12]
	ldr r3, _080572CC @ =gStageRun
	ldrh r2, [r3, #8]
	movs r5, #1
	adds r0, r5, #0
	ands r0, r2
	cmp r0, #0
	beq _080572B4
	ldrb r1, [r3, #0x12]
	adds r0, r5, #0
	ands r0, r1
	cmp r0, #0
	bne _080572B4
	ldr r0, _080572D0 @ =0x0000FFFE
	ands r0, r2
	movs r1, #0x10
	orrs r0, r1
	strh r0, [r3, #8]
_080572B4:
	ldrb r0, [r4, #0xf]
	cmp r0, #5
	bls _080572BC
	b _0805740C
_080572BC:
	lsls r0, r0, #2
	ldr r1, _080572D4 @ =_080572D8
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_080572C8: .4byte 0xFFFFFE00
_080572CC: .4byte gStageRun
_080572D0: .4byte 0x0000FFFE
_080572D4: .4byte _080572D8
_080572D8: @ jump table
	.4byte _080572F0 @ case 0
	.4byte _08057324 @ case 1
	.4byte _08057354 @ case 2
	.4byte _08057390 @ case 3
	.4byte _080573E8 @ case 4
	.4byte _08057406 @ case 5
_080572F0:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	ldr r0, [r4, #0x58]
	ldr r1, [r4, #0x60]
	adds r0, r0, r1
	str r0, [r4, #0x58]
	adds r1, #0x40
	str r1, [r4, #0x60]
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0xff
	beq _08057314
	b _0805740C
_08057314:
	ldr r1, _08057320 @ =0x0000B308
	adds r0, r4, #0
	bl SetMotion
	b _080573FE
	.align 2, 0
_08057320: .4byte 0x0000B308
_08057324:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	ldr r0, [r4, #0x60]
	adds r1, r1, r0
	str r1, [r4, #0x58]
	adds r0, #0x40
	str r0, [r4, #0x60]
	adds r0, r4, #0
	adds r0, #0xd4
	ldr r0, [r0]
	cmp r0, r1
	bge _0805740C
	str r0, [r4, #0x58]
	ldr r1, _08057350 @ =0x0000B305
	adds r0, r4, #0
	bl SetMotion
	b _080573FE
	.align 2, 0
_08057350: .4byte 0x0000B305
_08057354:
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _0805740C
	ldr r1, _08057384 @ =0x0000B306
	adds r0, r4, #0
	bl SetMotion
	adds r0, r4, #0
	adds r0, #0xb4
	ldr r1, [r4, #0x54]
	ldr r2, _08057388 @ =0xFFFF1000
	adds r1, r1, r2
	ldr r0, [r0]
	subs r0, r0, r1
	movs r1, #0x28
	bl __divsi3
	str r0, [r4, #0x5c]
	ldr r0, _0805738C @ =0xFFFFFB00
	str r0, [r4, #0x60]
	b _080573FE
	.align 2, 0
_08057384: .4byte 0x0000B306
_08057388: .4byte 0xFFFF1000
_0805738C: .4byte 0xFFFFFB00
_08057390:
	ldr r0, [r4, #0x60]
	cmp r0, #0
	ble _080573B2
	adds r1, r4, #0
	adds r1, #0x4c
	movs r0, #0
	strb r0, [r1]
	adds r2, r4, #0
	adds r2, #0x4a
	ldrb r1, [r2]
	subs r0, #0x11
	ands r0, r1
	strb r0, [r2]
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
	strb r0, [r4, #0xa]
_080573B2:
	ldr r1, [r4, #0x54]
	ldr r0, [r4, #0x5c]
	adds r2, r1, r0
	str r2, [r4, #0x54]
	ldr r1, [r4, #0x58]
	ldr r0, [r4, #0x60]
	adds r1, r1, r0
	str r1, [r4, #0x58]
	adds r0, #0x40
	str r0, [r4, #0x60]
	adds r0, r4, #0
	adds r0, #0xd4
	ldr r0, [r0]
	cmp r0, r1
	bge _0805740C
	adds r0, r2, #0
	bl FUN_08009f6c
	str r0, [r4, #0x58]
	ldr r1, _080573E4 @ =0x0000B313
	adds r0, r4, #0
	bl SetMotion
	b _080573FE
	.align 2, 0
_080573E4: .4byte 0x0000B313
_080573E8:
	ldr r0, [r4, #0x18]
	ldrb r1, [r0, #9]
	movs r0, #0x80
	ands r0, r1
	cmp r0, #0
	beq _0805740C
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _0805740C
_080573FE:
	ldrb r0, [r4, #0xf]
	adds r0, #1
	strb r0, [r4, #0xf]
	b _0805740C
_08057406:
	movs r0, #1
	strb r0, [r4, #0xd]
	strb r0, [r4, #0xe]
_0805740C:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	pop {r4, r5}
	pop {r0}
	bx r0
