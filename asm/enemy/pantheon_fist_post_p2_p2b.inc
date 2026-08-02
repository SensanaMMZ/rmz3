	.include "asm/macros.inc"

	.syntax unified

	.text


	thumb_func_start FUN_0809596c
FUN_0809596c: @ 0x0809596C
	push {r4, r5, r6, lr}
	adds r5, r0, #0
	ldrb r0, [r5, #0xe]
	cmp r0, #0
	beq _0809597C
	cmp r0, #1
	beq _08095A12
	b _08095AB6
_0809597C:
	adds r0, r5, #0
	adds r0, #0x74
	ldr r1, _080959F4 @ =0x0836A04C
	bl SetDDP
	ldr r1, _080959F8 @ =0x0000D406
	adds r0, r5, #0
	bl SetMotion
	adds r0, r5, #0
	bl UpdateMotionGraphic
	ldr r0, _080959FC @ =pZero2
	ldr r2, [r0]
	ldr r1, [r5, #0x54]
	ldr r0, [r2, #0x54]
	subs r1, r1, r0
	str r1, [r5, #0x5c]
	ldr r0, [r5, #0x58]
	ldr r3, _08095A00 @ =0xFFFFE800
	adds r0, r0, r3
	ldr r2, [r2, #0x58]
	subs r0, r0, r2
	str r0, [r5, #0x60]
	asrs r1, r1, #8
	adds r6, r1, #0
	muls r6, r1, r6
	asrs r0, r0, #8
	adds r1, r0, #0
	muls r1, r0, r1
	adds r0, r1, #0
	adds r6, r6, r0
	adds r0, r6, #0
	bl Sqrt
	lsls r0, r0, #0x10
	lsrs r6, r0, #8
	cmp r6, #0
	beq _08095A04
	ldr r0, [r5, #0x5c]
	lsls r0, r0, #8
	adds r1, r6, #0
	bl __divsi3
	adds r4, r0, #0
	str r4, [r5, #0x5c]
	ldr r0, [r5, #0x60]
	lsls r0, r0, #8
	adds r1, r6, #0
	bl __divsi3
	lsls r1, r4, #1
	adds r1, r1, r4
	lsls r1, r1, #1
	str r1, [r5, #0x5c]
	lsls r1, r0, #1
	adds r1, r1, r0
	lsls r1, r1, #1
	str r1, [r5, #0x60]
	b _08095A0C
	.align 2, 0
_080959F4: .4byte 0x0836A04C
_080959F8: .4byte 0x0000D406
_080959FC: .4byte pZero2
_08095A00: .4byte 0xFFFFE800
_08095A04:
	movs r0, #0xc0
	lsls r0, r0, #3
	str r0, [r5, #0x5c]
	str r6, [r5, #0x60]
_08095A0C:
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_08095A12:
	adds r0, r5, #0
	bl UpdateMotionGraphic
	ldr r1, [r5, #0x5c]
	adds r0, r5, #0
	bl FUN_08095014
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _08095A34
	adds r6, r5, #0
	adds r6, #0x8c
	ldr r4, [r6]
	movs r0, #4
	ands r4, r0
	cmp r4, #0
	beq _08095A3C
_08095A34:
	adds r0, r5, #0
	bl FUN_08095b70
	b _08095AB6
_08095A3C:
	ldr r0, [r5, #0x60]
	adds r0, #0x40
	str r0, [r5, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _08095A4C
	str r1, [r5, #0x60]
_08095A4C:
	ldr r1, [r5, #0x58]
	ldr r0, [r5, #0x60]
	adds r1, r1, r0
	str r1, [r5, #0x58]
	ldr r0, [r5, #0x54]
	bl PushoutToUp1
	adds r1, r0, #0
	cmp r1, #0
	bge _08095A6C
	ldr r0, [r5, #0x58]
	adds r0, r0, r1
	str r0, [r5, #0x58]
	adds r0, r5, #0
	bl FUN_08095b70
_08095A6C:
	ldrb r0, [r5, #0x11]
	cmp r0, #0
	beq _08095AB6
	ldr r0, _08095ABC @ =gStageRun+232
	adds r1, r5, #0
	adds r1, #0x54
	bl CalcFromCamera
	movs r1, #0xc0
	lsls r1, r1, #7
	cmp r0, r1
	bls _08095AB6
	ldrb r1, [r5, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r5, #0xa]
	str r4, [r6]
	adds r0, r5, #0
	adds r0, #0x90
	str r4, [r0]
	adds r0, #4
	strb r4, [r0]
	ldrb r1, [r5, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r5, #0xa]
	ldr r1, _08095AC0 @ =gEnemyFnTable
	ldrb r0, [r5, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r5, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r5, #0x14]
_08095AB6:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_08095ABC: .4byte gStageRun+232
_08095AC0: .4byte gEnemyFnTable

	thumb_func_start FUN_08095ac4
FUN_08095ac4: @ 0x08095AC4
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _08095AD4
	cmp r0, #1
	beq _08095B3E
	b _08095B68
_08095AD4:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _08095B00 @ =0x08369FEC
	bl SetDDP
	ldr r1, _08095B04 @ =0x0000D402
	adds r0, r4, #0
	bl SetMotion
	adds r2, r4, #0
	adds r2, #0xb9
	ldrb r1, [r2]
	movs r0, #1
	adds r3, r0, #0
	eors r3, r1
	adds r5, r2, #0
	cmp r3, #0
	beq _08095B08
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	orrs r0, r1
	b _08095B0E
	.align 2, 0
_08095B00: .4byte 0x08369FEC
_08095B04: .4byte 0x0000D402
_08095B08:
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
_08095B0E:
	strb r0, [r4, #0xa]
	movs r1, #1
	ands r1, r3
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
	movs r1, #0x80
	str r1, [r4, #0x5c]
	ldrb r0, [r5]
	lsls r0, r0, #8
	subs r1, r1, r0
	str r1, [r4, #0x5c]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08095B3E:
	ldr r1, [r4, #0x5c]
	adds r0, r4, #0
	bl FUN_08095014
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	movs r1, #1
	bl FUN_08094fe0
	lsls r0, r0, #0x18
	lsrs r2, r0, #0x18
	cmp r2, #0
	bne _08095B68
	adds r1, r4, #0
	adds r1, #0xb8
	movs r0, #2
	strb r0, [r1]
	strb r0, [r4, #0xd]
	strb r2, [r4, #0xe]
_08095B68:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
