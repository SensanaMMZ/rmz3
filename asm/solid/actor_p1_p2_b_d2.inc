	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start Actor47_Update
Actor47_Update: @ 0x080D5AF4
	push {r4, r5, r6, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xd]
	cmp r0, #1
	beq _080D5B32
	cmp r0, #1
	bgt _080D5B08
	cmp r0, #0
	beq _080D5B0E
	b _080D5C08
_080D5B08:
	cmp r0, #2
	beq _080D5BE8
	b _080D5C08
_080D5B0E:
	ldr r0, _080D5B60 @ =wDynamicGraphicTilenums
	movs r2, #0xc5
	lsls r2, r2, #1
	adds r0, r0, r2
	movs r1, #0xb6
	lsls r1, r1, #1
	strh r1, [r0]
	ldr r0, _080D5B64 @ =wDynamicMotionPalIDs
	adds r0, r0, r2
	movs r1, #6
	strh r1, [r0]
	ldr r1, _080D5B68 @ =0x0000C501
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xd]
	adds r0, #1
	strb r0, [r4, #0xd]
_080D5B32:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	adds r5, r4, #0
	adds r5, #0x70
	cmp r0, #3
	bne _080D5B78
	ldrb r0, [r4, #0x1e]
	lsls r0, r0, #8
	ldrb r1, [r5]
	orrs r0, r1
	ldr r1, _080D5B6C @ =0x0000C502
	cmp r0, r1
	bne _080D5B70
	adds r1, #1
	adds r0, r4, #0
	bl SetMotion
	b _080D5B78
	.align 2, 0
_080D5B60: .4byte wDynamicGraphicTilenums
_080D5B64: .4byte wDynamicMotionPalIDs
_080D5B68: .4byte 0x0000C501
_080D5B6C: .4byte 0x0000C502
_080D5B70:
	ldr r1, _080D5BE0 @ =0x0000C501
	adds r0, r4, #0
	bl SetMotion
_080D5B78:
	ldr r0, [r4, #0x18]
	ldrb r1, [r0, #9]
	movs r6, #1
	adds r0, r6, #0
	ands r0, r1
	cmp r0, #0
	beq _080D5BA8
	ldrb r0, [r4, #0x1e]
	lsls r0, r0, #8
	ldrb r1, [r5]
	orrs r0, r1
	ldr r1, _080D5BE0 @ =0x0000C501
	cmp r0, r1
	bne _080D5B9C
	adds r1, #1
	adds r0, r4, #0
	bl SetMotion
_080D5B9C:
	ldr r0, [r4, #0x18]
	ldrb r1, [r0, #9]
	adds r0, r6, #0
	ands r0, r1
	cmp r0, #0
	bne _080D5BBE
_080D5BA8:
	ldrb r0, [r4, #0x1e]
	lsls r0, r0, #8
	ldrb r1, [r5]
	orrs r0, r1
	ldr r1, _080D5BE4 @ =0x0000C503
	cmp r0, r1
	bne _080D5BBE
	adds r1, #1
	adds r0, r4, #0
	bl SetMotion
_080D5BBE:
	ldr r0, [r4, #0x18]
	ldrb r1, [r0, #9]
	movs r0, #2
	ands r0, r1
	cmp r0, #0
	beq _080D5C08
	ldrb r0, [r4, #0x1e]
	lsls r1, r0, #8
	ldrb r0, [r5]
	orrs r1, r0
	ldr r0, _080D5BE0 @ =0x0000C501
	cmp r1, r0
	beq _080D5C02
	adds r0, #2
	cmp r1, r0
	bne _080D5C08
	b _080D5C02
	.align 2, 0
_080D5BE0: .4byte 0x0000C501
_080D5BE4: .4byte 0x0000C503
_080D5BE8:
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
	beq _080D5C08
_080D5C02:
	ldrb r0, [r4, #0xd]
	adds r0, #1
	strb r0, [r4, #0xd]
_080D5C08:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
