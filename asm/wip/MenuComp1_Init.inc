	push {r4, r5, lr}
	adds r5, r0, #0
	ldr r4, [r5, #0x28]
	bl InitNonAffineMotion
	ldrb r1, [r5, #0xa]
	movs r0, #1
	movs r2, #0
	orrs r0, r1
	movs r1, #2
	orrs r0, r1
	strb r0, [r5, #0xa]
	adds r0, r5, #0
	adds r0, #0x4c
	strb r2, [r0]
	adds r2, r5, #0
	adds r2, #0x4a
	ldrb r1, [r2]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r2]
	ldrb r1, [r5, #0xa]
	movs r0, #0xef
	ands r0, r1
	strb r0, [r5, #0xa]
	ldr r0, _080E62E8 @ =0x00000DCC
	adds r4, r4, r0
	ldrb r0, [r4]
	strb r0, [r5, #0x12]
	ldrb r0, [r5, #0x10]
	ldrb r4, [r4]
	cmp r0, r4
	bne _080E62F0
	ldr r0, _080E62EC @ =sMenuComp1Motions
	ldrb r1, [r5, #0x10]
	lsls r1, r1, #2
	adds r0, #2
	adds r1, r1, r0
	ldrh r1, [r1]
	adds r0, r5, #0
	bl SetMotion
	b _080E6300
	.align 2, 0
_080E62E8: .4byte 0x00000DCC
_080E62EC: .4byte sMenuComp1Motions
_080E62F0:
	ldr r0, _080E6340 @ =sMenuComp1Motions
	ldrb r1, [r5, #0x10]
	lsls r1, r1, #2
	adds r1, r1, r0
	ldrh r1, [r1]
	adds r0, r5, #0
	bl SetMotion
_080E6300:
	ldr r1, _080E6344 @ =u8_ARRAY_08372020
	ldrb r0, [r5, #0x10]
	adds r0, r0, r1
	ldrb r0, [r0]
	lsls r0, r0, #8
	str r0, [r5, #0x54]
	ldr r1, _080E6348 @ =u8_ARRAY_08372027
	ldrb r0, [r5, #0x10]
	adds r0, r0, r1
	ldrb r0, [r0]
	lsls r0, r0, #8
	str r0, [r5, #0x58]
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x58]
	str r0, [r5, #0x64]
	str r1, [r5, #0x68]
	ldr r1, _080E634C @ =gWidgetFnTable
	ldrb r0, [r5, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r5, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r5, #0x14]
	adds r0, r5, #0
	bl MenuComp1_Update
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080E6340: .4byte sMenuComp1Motions
_080E6344: .4byte u8_ARRAY_08372020
_080E6348: .4byte u8_ARRAY_08372027
_080E634C: .4byte gWidgetFnTable
