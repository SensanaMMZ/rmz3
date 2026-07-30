	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start _pantheonBombAI
_pantheonBombAI: @ 0x080AD240
	push {r4, r5, lr}
	adds r5, r0, #0
	adds r2, r5, #0
	adds r2, #0x8c
	ldr r0, [r2]
	movs r1, #0x80
	lsls r1, r1, #2
	ands r0, r1
	cmp r0, #0
	beq _080AD276
	movs r1, #0
	str r1, [r2]
	adds r0, r5, #0
	adds r0, #0x90
	str r1, [r0]
	adds r0, #4
	strb r1, [r0]
	ldrb r1, [r5, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r5, #0xa]
	adds r1, r5, #0
	adds r1, #0x54
	movs r0, #2
	bl CreateSmoke
	b _080AD3E2
_080AD276:
	ldrb r0, [r5, #0xe]
	cmp r0, #7
	bls _080AD27E
	b _080AD3F4
_080AD27E:
	lsls r0, r0, #2
	ldr r1, _080AD288 @ =_080AD28C
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_080AD288: .4byte _080AD28C
_080AD28C: @ jump table
	.4byte _080AD2AC @ case 0
	.4byte _080AD2DE @ case 1
	.4byte _080AD322 @ case 2
	.4byte _080AD334 @ case 3
	.4byte _080AD34C @ case 4
	.4byte _080AD35A @ case 5
	.4byte _080AD37C @ case 6
	.4byte _080AD3BA @ case 7
_080AD2AC:
	ldr r1, _080AD2C0 @ =0x0000690B
	adds r0, r5, #0
	bl SetMotion
	ldrb r0, [r5, #0x10]
	cmp r0, #0
	bne _080AD2C8
	ldr r0, _080AD2C4 @ =0xFFFFFE80
	b _080AD2CC
	.align 2, 0
_080AD2C0: .4byte 0x0000690B
_080AD2C4: .4byte 0xFFFFFE80
_080AD2C8:
	movs r0, #0xc0
	lsls r0, r0, #1
_080AD2CC:
	str r0, [r5, #0x5c]
	movs r0, #0x80
	lsls r0, r0, #1
	str r0, [r5, #0x60]
	movs r0, #0
	strb r0, [r5, #0x13]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_080AD2DE:
	ldr r0, [r5, #0x60]
	adds r0, #0x40
	str r0, [r5, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _080AD2EE
	str r1, [r5, #0x60]
_080AD2EE:
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x5c]
	adds r0, r0, r1
	str r0, [r5, #0x54]
	ldr r1, [r5, #0x58]
	ldr r2, [r5, #0x60]
	adds r1, r1, r2
	str r1, [r5, #0x58]
	movs r2, #0xa0
	lsls r2, r2, #3
	adds r1, r1, r2
	bl PushoutToUp1
	adds r1, r0, #0
	cmp r1, #0
	beq _080AD31A
	ldr r0, [r5, #0x58]
	adds r0, r0, r1
	str r0, [r5, #0x58]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_080AD31A:
	adds r0, r5, #0
	bl UpdateMotionGraphic
	b _080AD3F4
_080AD322:
	ldr r1, _080AD348 @ =0x0000690C
	adds r0, r5, #0
	bl SetMotion
	movs r0, #0x30
	strb r0, [r5, #0x13]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_080AD334:
	adds r0, r5, #0
	bl UpdateMotionGraphic
	adds r0, r5, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _080AD3F4
	b _080AD370
	.align 2, 0
_080AD348: .4byte 0x0000690C
_080AD34C:
	ldr r1, _080AD378 @ =0x0000690D
	adds r0, r5, #0
	bl SetMotion
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_080AD35A:
	adds r0, r5, #0
	bl UpdateMotionGraphic
	ldrb r0, [r5, #0x13]
	cmp r0, #0
	beq _080AD370
	subs r0, #1
	strb r0, [r5, #0x13]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080AD3F4
_080AD370:
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
	b _080AD3F4
	.align 2, 0
_080AD378: .4byte 0x0000690D
_080AD37C:
	ldrb r1, [r5, #0xa]
	movs r0, #0xfe
	ands r0, r1
	strb r0, [r5, #0xa]
	adds r0, r5, #0
	adds r0, #0x74
	ldr r1, _080AD3FC @ =0x0836C87C
	bl SetDDP
	movs r0, #0x14
	strb r0, [r5, #0x13]
	adds r4, r5, #0
	adds r4, #0x54
	movs r0, #1
	adds r1, r4, #0
	bl CreateSmoke
	movs r0, #0x35
	bl PlaySound
	adds r0, r4, #0
	movs r1, #0
	bl createPantheonBombBlast
	adds r0, r4, #0
	movs r1, #1
	bl createPantheonBombBlast
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_080AD3BA:
	ldrb r0, [r5, #0x13]
	cmp r0, #0
	beq _080AD3CA
	subs r0, #1
	strb r0, [r5, #0x13]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080AD3F4
_080AD3CA:
	adds r0, r5, #0
	adds r0, #0x8c
	movs r1, #0
	str r1, [r0]
	adds r0, #4
	str r1, [r0]
	adds r0, #4
	strb r1, [r0]
	ldrb r1, [r5, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r5, #0xa]
_080AD3E2:
	ldr r1, _080AD400 @ =gProjectileFnTable
	ldrb r0, [r5, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r5, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r5, #0x14]
_080AD3F4:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080AD3FC: .4byte 0x0836C87C
_080AD400: .4byte gProjectileFnTable
