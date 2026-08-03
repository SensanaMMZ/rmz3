	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start childreMode7
childreMode7: @ 0x08041440
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #5
	bls _0804144C
	b _080415AC
_0804144C:
	lsls r0, r0, #2
	ldr r1, _08041458 @ =_0804145C
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_08041458: .4byte _0804145C
_0804145C: @ jump table
	.4byte _08041474 @ case 0
	.4byte _08041494 @ case 1
	.4byte _080414B8 @ case 2
	.4byte _080414EC @ case 3
	.4byte _08041560 @ case 4
	.4byte _08041596 @ case 5
_08041474:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _080414B0 @ =sCollisions+(24*1)
	bl SetDDP
	movs r0, #4
	strb r0, [r4, #0x12]
	movs r0, #3
	strb r0, [r4, #0x13]
	ldr r1, _080414B4 @ =0x0000A404
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08041494:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _080414A8
	b _080415AC
_080414A8:
	ldrb r0, [r4, #0xe]
	adds r0, #1
	b _080415AA
	.align 2, 0
_080414B0: .4byte sCollisions+(24*1)
_080414B4: .4byte 0x0000A404
_080414B8:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	bl CreateSplitMineBomb
	ldr r1, _08041548 @ =0x0000A405
	adds r0, r4, #0
	bl SetMotion
	ldr r0, _0804154C @ =0xFFFFFE00
	str r0, [r4, #0x5c]
	adds r2, r0, #0
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _080414DC
	movs r2, #0x80
	lsls r2, r2, #2
_080414DC:
	str r2, [r4, #0x5c]
	ldr r0, _08041550 @ =0xFFFFFA00
	str r0, [r4, #0x60]
	movs r0, #0
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080414EC:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	ldr r0, [r4, #0x60]
	adds r0, #0x80
	str r0, [r4, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _08041504
	str r1, [r4, #0x60]
_08041504:
	ldrb r0, [r4, #0x12]
	cmp r0, #0
	bne _0804151C
	ldr r0, [r4, #0x60]
	cmp r0, #0
	ble _0804151C
	ldr r1, _08041554 @ =0x0000A406
	adds r0, r4, #0
	bl SetMotion
	movs r0, #1
	strb r0, [r4, #0x12]
_0804151C:
	ldr r0, [r4, #0x58]
	ldr r2, [r4, #0x60]
	adds r1, r0, r2
	str r1, [r4, #0x58]
	ldr r0, _08041558 @ =gOverworld
	ldr r3, _0804155C @ =0x0002C00C
	adds r0, r0, r3
	ldr r0, [r0]
	subs r0, r0, r1
	cmp r0, #0
	bge _08041540
	cmp r2, #0
	ble _08041540
	adds r0, r1, r0
	str r0, [r4, #0x58]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08041540:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	b _080415AC
	.align 2, 0
_08041548: .4byte 0x0000A405
_0804154C: .4byte 0xFFFFFE00
_08041550: .4byte 0xFFFFFA00
_08041554: .4byte 0x0000A406
_08041558: .4byte gOverworld
_0804155C: .4byte 0x0002C00C
_08041560:
	movs r0, #4
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0x13]
	subs r0, #1
	strb r0, [r4, #0x13]
	lsls r0, r0, #0x18
	lsrs r5, r0, #0x18
	cmp r5, #0
	bne _08041588
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	bl CreateSplitMineBomb
	movs r0, #8
	strb r0, [r4, #0xd]
	strb r5, [r4, #0xe]
	adds r0, r4, #0
	bl childreMode8
	b _080415AC
_08041588:
	ldr r1, _080415B4 @ =0x0000A407
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08041596:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080415AC
	movs r0, #2
_080415AA:
	strb r0, [r4, #0xe]
_080415AC:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080415B4: .4byte 0x0000A407
