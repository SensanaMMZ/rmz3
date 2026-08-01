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

	thumb_func_start childreMode8
childreMode8: @ 0x080415B8
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r5, [r4, #0xe]
	cmp r5, #1
	beq _080415F8
	cmp r5, #1
	bgt _080415CC
	cmp r5, #0
	beq _080415D6
	b _080416DE
_080415CC:
	cmp r5, #2
	beq _08041638
	cmp r5, #3
	beq _0804164A
	b _080416DE
_080415D6:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _08041630 @ =sCollisions+(24*1)
	bl SetDDP
	ldrb r1, [r4, #0xa]
	movs r0, #1
	orrs r0, r1
	strb r0, [r4, #0xa]
	ldr r1, _08041634 @ =0x0000A406
	adds r0, r4, #0
	bl SetMotion
	str r5, [r4, #0x60]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080415F8:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldr r0, [r4, #0x60]
	adds r0, #0x40
	str r0, [r4, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _0804160E
	str r1, [r4, #0x60]
_0804160E:
	ldr r1, [r4, #0x58]
	ldr r0, [r4, #0x60]
	adds r1, r1, r0
	str r1, [r4, #0x58]
	ldr r0, [r4, #0x54]
	bl PushoutToUp1
	adds r1, r0, #0
	cmp r1, #0
	bge _080416DE
	ldr r0, [r4, #0x58]
	adds r0, r0, r1
	str r0, [r4, #0x58]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	b _080416DC
	.align 2, 0
_08041630: .4byte sCollisions+(24*1)
_08041634: .4byte 0x0000A406
_08041638:
	ldr r0, _080416C8 @ =0xFFFFFE00
	str r0, [r4, #0x60]
	ldr r1, _080416CC @ =0x0000A408
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0804164A:
	ldr r0, [r4, #0x60]
	adds r0, #0x40
	str r0, [r4, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _0804165A
	str r1, [r4, #0x60]
_0804165A:
	ldr r1, [r4, #0x58]
	ldr r0, [r4, #0x60]
	adds r2, r1, r0
	str r2, [r4, #0x58]
	adds r0, r4, #0
	adds r0, #0xc0
	ldr r0, [r0]
	subs r1, r0, r2
	cmp r1, #0
	bge _08041672
	adds r0, r2, r1
	str r0, [r4, #0x58]
_08041672:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _080416DE
	movs r1, #0xa4
	lsls r1, r1, #8
	adds r0, r4, #0
	bl SetMotion
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldrb r0, [r4, #0xa]
	lsrs r0, r0, #4
	movs r2, #1
	eors r0, r2
	ands r0, r2
	adds r1, r4, #0
	adds r1, #0x4c
	strb r0, [r1]
	ldrb r1, [r4, #0xa]
	lsrs r1, r1, #4
	eors r1, r2
	ands r1, r2
	adds r5, r4, #0
	adds r5, #0x4a
	lsls r3, r1, #4
	ldrb r2, [r5]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r3
	strb r0, [r5]
	cmp r1, #0
	beq _080416D0
	ldrb r0, [r4, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _080416D6
	.align 2, 0
_080416C8: .4byte 0xFFFFFE00
_080416CC: .4byte 0x0000A408
_080416D0:
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
_080416D6:
	strb r0, [r4, #0xa]
	movs r0, #0
	strb r0, [r4, #0xd]
_080416DC:
	strb r0, [r4, #0xe]
_080416DE:
	pop {r4, r5}
	pop {r0}
	bx r0

	thumb_func_start childreStartScrewIce
childreStartScrewIce: @ 0x080416E4
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #1
	beq _08041720
	cmp r0, #1
	bgt _080416F8
	cmp r0, #0
	beq _08041702
	b _080417FA
_080416F8:
	cmp r0, #2
	beq _08041734
	cmp r0, #3
	beq _08041762
	b _080417FA
_08041702:
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	bl InitNonAffineMotion
	adds r0, r4, #0
	bl ResetDynamicMotion
	movs r0, #0x10
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08041720:
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080417FA
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
	b _080417FA
_08041734:
	movs r0, #0x6a
	bl PlaySound
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _080417D0 @ =0x08361F24
	bl SetDDP
	ldr r0, _080417D4 @ =pZero2
	ldr r0, [r0]
	ldr r0, [r0, #0x54]
	str r0, [r4, #0x54]
	ldrb r1, [r4, #0xa]
	movs r0, #1
	orrs r0, r1
	strb r0, [r4, #0xa]
	ldr r1, _080417D8 @ =0x0000A40B
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08041762:
	ldr r0, [r4, #0x58]
	movs r2, #0xa0
	lsls r2, r2, #3
	adds r1, r0, r2
	str r1, [r4, #0x58]
	adds r5, r4, #0
	adds r5, #0xc0
	ldr r0, [r5]
	subs r0, r0, r1
	cmp r0, #0
	bge _080417F4
	adds r1, r1, r0
	str r1, [r4, #0x58]
	ldr r0, [r4, #0x54]
	ldr r2, _080417DC @ =0xFFFFFB00
	adds r0, r0, r2
	movs r2, #0x68
	bl CreateChildreScrewIce
	ldr r0, [r4, #0x54]
	movs r1, #0xa0
	lsls r1, r1, #3
	adds r0, r0, r1
	ldr r1, [r4, #0x58]
	movs r2, #0x18
	bl CreateChildreScrewIce
	ldr r0, [r4, #0x54]
	ldr r2, _080417DC @ =0xFFFFFB00
	adds r0, r0, r2
	ldr r1, [r4, #0x58]
	movs r2, #0x78
	bl CreateChildreScrewIce
	ldr r0, [r4, #0x54]
	movs r1, #0xa0
	lsls r1, r1, #3
	adds r0, r0, r1
	ldr r1, [r4, #0x58]
	movs r2, #8
	bl CreateChildreScrewIce
	ldr r0, _080417E0 @ =gOverworld
	ldr r2, _080417E4 @ =0x0002C00C
	adds r0, r0, r2
	ldr r0, [r0]
	ldr r1, [r5]
	subs r0, r0, r1
	ldr r1, _080417E8 @ =0xFFFFE000
	cmp r0, r1
	ble _080417EC
	movs r1, #0
	movs r0, #0xa
	b _080417F0
	.align 2, 0
_080417D0: .4byte 0x08361F24
_080417D4: .4byte pZero2
_080417D8: .4byte 0x0000A40B
_080417DC: .4byte 0xFFFFFB00
_080417E0: .4byte gOverworld
_080417E4: .4byte 0x0002C00C
_080417E8: .4byte 0xFFFFE000
_080417EC:
	movs r1, #0
	movs r0, #0xb
_080417F0:
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_080417F4:
	adds r0, r4, #0
	bl UpdateMotionGraphic
_080417FA:
	pop {r4, r5}
	pop {r0}
	bx r0

	thumb_func_start childreMaybeMiddleScrewIce
childreMaybeMiddleScrewIce: @ 0x08041800
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _08041810
	cmp r0, #1
	beq _08041832
	b _0804184C
_08041810:
	movs r0, #0x40
	bl PlaySound
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _08041854 @ =0x08361F54
	bl SetDDP
	movs r0, #0x30
	strb r0, [r4, #0x12]
	ldr r1, _08041858 @ =0x0000A40C
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08041832:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	lsrs r1, r0, #0x18
	cmp r1, #0
	bne _0804184C
	movs r0, #0xb
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_0804184C:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_08041854: .4byte 0x08361F54
_08041858: .4byte 0x0000A40C
