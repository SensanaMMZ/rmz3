	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_08076220
FUN_08076220: @ 0x08076220
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r5, [r4, #0xe]
	cmp r5, #0
	beq _08076230
	cmp r5, #1
	beq _0807626E
	b _080762D4
_08076230:
	str r5, [r4, #0x60]
	adds r0, r4, #0
	adds r0, #0xb8
	ldrb r0, [r0]
	cmp r0, #0
	beq _0807624C
	ldr r1, _08076248 @ =0x00002A04
	adds r0, r4, #0
	bl SetMotion
	strb r5, [r4, #0x12]
	b _08076258
	.align 2, 0
_08076248: .4byte 0x00002A04
_0807624C:
	ldr r1, _080762DC @ =0x00002A02
	adds r0, r4, #0
	bl SetMotion
	movs r0, #1
	strb r0, [r4, #0x12]
_08076258:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _080762E0 @ =0x08367168
	bl SetDDP
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0807626E:
	adds r0, r4, #0
	adds r0, #0xb8
	ldrb r0, [r0]
	cmp r0, #0
	beq _08076296
	ldrb r0, [r4, #0x12]
	cmp r0, #0
	beq _08076290
	movs r0, #0
	strb r0, [r4, #0x12]
	ldr r1, _080762E4 @ =0x00002A04
	adds r0, r4, #0
	bl SetMotion
	adds r0, r4, #0
	bl UpdateMotionGraphic
_08076290:
	adds r0, r4, #0
	bl FUN_08075aa8
_08076296:
	adds r0, r4, #0
	bl IsFrozen
	adds r5, r0, #0
	cmp r5, #0
	bne _080762D4
	ldr r0, [r4, #0x60]
	adds r0, #0x40
	str r0, [r4, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _080762B2
	str r1, [r4, #0x60]
_080762B2:
	ldr r1, [r4, #0x58]
	ldr r0, [r4, #0x60]
	adds r1, r1, r0
	str r1, [r4, #0x58]
	ldr r0, [r4, #0x54]
	bl PushoutToUp1
	adds r1, r0, #0
	cmp r1, #0
	bge _080762D4
	ldr r0, _080762E8 @ =0xFFFFF800
	cmp r1, r0
	ble _080762D4
	str r5, [r4, #0x60]
	ldr r0, [r4, #0x58]
	adds r0, r0, r1
	str r0, [r4, #0x58]
_080762D4:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080762DC: .4byte 0x00002A02
_080762E0: .4byte 0x08367168
_080762E4: .4byte 0x00002A04
_080762E8: .4byte 0xFFFFF800

	thumb_func_start FUN_080762ec
FUN_080762ec: @ 0x080762EC
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #1
	beq _08076368
	cmp r0, #1
	bgt _08076300
	cmp r0, #0
	beq _0807630A
	b _080763EC
_08076300:
	cmp r0, #2
	beq _080763C0
	cmp r0, #3
	beq _080763CC
	b _080763EC
_0807630A:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _08076330 @ =0x08367150
	bl SetDDP
	movs r2, #0
	ldr r0, _08076334 @ =pZero2
	ldr r0, [r0]
	ldr r1, [r4, #0x54]
	ldr r0, [r0, #0x54]
	cmp r1, r0
	bge _08076324
	movs r2, #1
_08076324:
	cmp r2, #0
	beq _08076338
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	orrs r0, r1
	b _0807633E
	.align 2, 0
_08076330: .4byte 0x08367150
_08076334: .4byte pZero2
_08076338:
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
_0807633E:
	strb r0, [r4, #0xa]
	adds r1, r2, #0
	adds r0, r4, #0
	adds r0, #0x4c
	strb r1, [r0]
	adds r3, r4, #0
	adds r3, #0x4a
	lsls r1, r1, #4
	ldrb r2, [r3]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r1
	strb r0, [r3]
	ldr r1, _080763AC @ =0x00002A02
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08076368:
	ldr r1, _080763B0 @ =gStageRun+232
	ldr r0, [r1, #0x3c]
	ldr r2, _080763B4 @ =0xFFFF9000
	adds r0, r0, r2
	str r0, [r4, #0x58]
	ldr r3, [r4, #0x54]
	movs r2, #0xf0
	lsls r2, r2, #7
	adds r0, r3, r2
	ldr r2, [r1, #0x38]
	subs r0, r0, r2
	movs r1, #0x80
	lsls r1, r1, #6
	cmp r0, r1
	ble _08076392
	ldr r1, _080763B8 @ =0xFFFF8801
	adds r0, r3, r1
	subs r0, r0, r2
	ldr r1, _080763BC @ =0xFFFFE000
	cmp r0, r1
	blt _0807639C
_08076392:
	adds r0, r4, #0
	adds r0, #0xb9
	ldrb r0, [r0]
	cmp r0, #0
	beq _080763A2
_0807639C:
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080763A2:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	b _080763EC
	.align 2, 0
_080763AC: .4byte 0x00002A02
_080763B0: .4byte gStageRun+232
_080763B4: .4byte 0xFFFF9000
_080763B8: .4byte 0xFFFF8801
_080763BC: .4byte 0xFFFFE000
_080763C0:
	movs r0, #0xc0
	lsls r0, r0, #2
	str r0, [r4, #0x60]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080763CC:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldr r1, [r4, #0x58]
	ldr r0, [r4, #0x60]
	adds r1, r1, r0
	str r1, [r4, #0x58]
	ldr r0, _080763F4 @ =pZero2
	ldr r0, [r0]
	ldr r0, [r0, #0x58]
	cmp r1, r0
	ble _080763EC
	movs r1, #0
	movs r0, #2
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_080763EC:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080763F4: .4byte pZero2
