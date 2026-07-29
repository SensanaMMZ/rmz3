	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080d751c
FUN_080d751c: @ 0x080D751C
	push {r4, r5, r6, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xd]
	cmp r0, #1
	beq _080D755A
	cmp r0, #1
	bgt _080D7530
	cmp r0, #0
	beq _080D7536
	b _080D7630
_080D7530:
	cmp r0, #2
	beq _080D7610
	b _080D7630
_080D7536:
	ldr r0, _080D7588 @ =wDynamicGraphicTilenums
	movs r2, #0xc5
	lsls r2, r2, #1
	adds r0, r0, r2
	movs r1, #0xb0
	lsls r1, r1, #2
	strh r1, [r0]
	ldr r0, _080D758C @ =wDynamicMotionPalIDs
	adds r0, r0, r2
	movs r1, #9
	strh r1, [r0]
	ldr r1, _080D7590 @ =0x0000C501
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xd]
	adds r0, #1
	strb r0, [r4, #0xd]
_080D755A:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	adds r5, r4, #0
	adds r5, #0x70
	cmp r0, #3
	bne _080D75A0
	ldrb r0, [r4, #0x1e]
	lsls r0, r0, #8
	ldrb r1, [r5]
	orrs r0, r1
	ldr r1, _080D7594 @ =0x0000C502
	cmp r0, r1
	bne _080D7598
	adds r1, #1
	adds r0, r4, #0
	bl SetMotion
	b _080D75A0
	.align 2, 0
_080D7588: .4byte wDynamicGraphicTilenums
_080D758C: .4byte wDynamicMotionPalIDs
_080D7590: .4byte 0x0000C501
_080D7594: .4byte 0x0000C502
_080D7598:
	ldr r1, _080D7608 @ =0x0000C501
	adds r0, r4, #0
	bl SetMotion
_080D75A0:
	ldr r0, [r4, #0x18]
	ldrb r1, [r0, #9]
	movs r6, #1
	adds r0, r6, #0
	ands r0, r1
	cmp r0, #0
	beq _080D75D0
	ldrb r0, [r4, #0x1e]
	lsls r0, r0, #8
	ldrb r1, [r5]
	orrs r0, r1
	ldr r1, _080D7608 @ =0x0000C501
	cmp r0, r1
	bne _080D75C4
	adds r1, #1
	adds r0, r4, #0
	bl SetMotion
_080D75C4:
	ldr r0, [r4, #0x18]
	ldrb r1, [r0, #9]
	adds r0, r6, #0
	ands r0, r1
	cmp r0, #0
	bne _080D75E6
_080D75D0:
	ldrb r0, [r4, #0x1e]
	lsls r0, r0, #8
	ldrb r1, [r5]
	orrs r0, r1
	ldr r1, _080D760C @ =0x0000C503
	cmp r0, r1
	bne _080D75E6
	adds r1, #1
	adds r0, r4, #0
	bl SetMotion
_080D75E6:
	ldr r0, [r4, #0x18]
	ldrb r1, [r0, #9]
	movs r0, #2
	ands r0, r1
	cmp r0, #0
	beq _080D7630
	ldrb r0, [r4, #0x1e]
	lsls r1, r0, #8
	ldrb r0, [r5]
	orrs r1, r0
	ldr r0, _080D7608 @ =0x0000C501
	cmp r1, r0
	beq _080D762A
	adds r0, #2
	cmp r1, r0
	bne _080D7630
	b _080D762A
	.align 2, 0
_080D7608: .4byte 0x0000C501
_080D760C: .4byte 0x0000C503
_080D7610:
	ldrb r0, [r4, #0x1e]
	lsls r0, r0, #8
	adds r1, r4, #0
	adds r1, #0x70
	ldrb r1, [r1]
	orrs r1, r0
	adds r0, r4, #0
	movs r2, #1
	bl FUN_080d0934
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _080D7630
_080D762A:
	ldrb r0, [r4, #0xd]
	adds r0, #1
	strb r0, [r4, #0xd]
_080D7630:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
