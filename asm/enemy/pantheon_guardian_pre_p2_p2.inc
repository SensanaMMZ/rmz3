	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080641ec
FUN_080641ec: @ 0x080641EC
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _080641FC
	cmp r0, #1
	beq _08064216
	b _08064290
_080641FC:
	movs r1, #0xa0
	lsls r1, r1, #5
	adds r0, r4, #0
	bl SetMotion
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _08064270 @ =sCollisions
	bl SetDDP
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08064216:
	ldr r1, [r4, #0x60]
	ldr r0, _08064274 @ =0x000006FF
	cmp r1, r0
	bgt _08064224
	adds r0, r1, #0
	adds r0, #0x40
	str r0, [r4, #0x60]
_08064224:
	ldr r0, [r4, #0x58]
	ldr r1, [r4, #0x60]
	adds r0, r0, r1
	str r0, [r4, #0x58]
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	bl FUN_080098a4
	lsls r0, r0, #0x10
	lsrs r1, r0, #0x10
	movs r0, #0x10
	ands r0, r1
	lsls r0, r0, #0x10
	lsrs r2, r0, #0x10
	cmp r2, #0
	beq _0806427C
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	bl FUN_08009f6c
	str r0, [r4, #0x58]
	ldr r1, _08064278 @ =gEnemyFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r4, #0x14]
	adds r0, r4, #0
	bl PantheonGuardian_Die
	b _08064290
	.align 2, 0
_08064270: .4byte sCollisions
_08064274: .4byte 0x000006FF
_08064278: .4byte gEnemyFnTable
_0806427C:
	cmp r1, #0
	beq _08064290
	ldr r0, _08064298 @ =0x0000800F
	cmp r1, r0
	beq _08064290
	subs r0, #1
	cmp r1, r0
	beq _08064290
	strb r2, [r4, #0xd]
	strb r2, [r4, #0xe]
_08064290:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_08064298: .4byte 0x0000800F

	thumb_func_start FUN_0806429c
FUN_0806429c: @ 0x0806429C
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #1
	beq _080642C4
	cmp r0, #1
	bgt _080642B0
	cmp r0, #0
	beq _080642B6
	b _08064330
_080642B0:
	cmp r0, #2
	beq _08064304
	b _08064330
_080642B6:
	ldr r1, _080642F8 @ =0x00001402
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080642C4:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _08064330
	ldr r1, _080642FC @ =0x00001403
	adds r0, r4, #0
	bl SetMotion
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _08064300 @ =sCollisions+(24*2)
	bl SetDDP
	movs r0, #0x3a
	bl PlaySound
	movs r0, #0x40
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
	b _08064330
	.align 2, 0
_080642F8: .4byte 0x00001402
_080642FC: .4byte 0x00001403
_08064300: .4byte sCollisions+(24*2)
_08064304:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	lsrs r5, r0, #0x18
	cmp r5, #0
	bne _08064330
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _08064350 @ =sCollisions
	bl SetDDP
	movs r1, #0xa0
	lsls r1, r1, #5
	adds r0, r4, #0
	bl SetMotion
	strb r5, [r4, #0xd]
	strb r5, [r4, #0xe]
_08064330:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	adds r1, #0x40
	bl FUN_080098a4
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _0806434A
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	bl FUN_08009f6c
	str r0, [r4, #0x58]
_0806434A:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_08064350: .4byte sCollisions

	thumb_func_start FUN_08064354
FUN_08064354: @ 0x08064354
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r5, [r4, #0xe]
	cmp r5, #0
	beq _08064364
	cmp r5, #1
	beq _080643E2
	b _08064422
_08064364:
	ldr r1, _080643A4 @ =0x00001404
	adds r0, r4, #0
	bl SetMotion
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _080643A8 @ =sCollisions+(24*4)
	bl SetDDP
	adds r0, r4, #0
	adds r0, #0xb8
	ldrb r0, [r0]
	cmp r0, #0
	beq _080643AC
	movs r0, #0x80
	str r0, [r4, #0x5c]
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	adds r0, #0x4c
	strb r5, [r0]
	adds r2, r4, #0
	adds r2, #0x4a
	ldrb r1, [r2]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r2]
	b _080643D4
	.align 2, 0
_080643A4: .4byte 0x00001404
_080643A8: .4byte sCollisions+(24*4)
_080643AC:
	movs r0, #0x80
	rsbs r0, r0, #0
	str r0, [r4, #0x5c]
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
_080643D4:
	movs r1, #0
	movs r0, #0xc
	strb r0, [r4, #0x12]
	str r1, [r4, #0x60]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080643E2:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	lsls r0, r1, #1
	adds r0, r0, r1
	asrs r0, r0, #2
	str r0, [r4, #0x5c]
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldrb r0, [r4, #0x12]
	cmp r0, #0
	beq _08064408
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _08064422
_08064408:
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	ands r0, r1
	lsls r0, r0, #0x18
	lsrs r1, r0, #0x18
	cmp r1, #0
	bne _0806441A
	movs r0, #1
	b _0806441E
_0806441A:
	movs r1, #0
	movs r0, #2
_0806441E:
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_08064422:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	adds r1, #0x40
	bl FUN_080098a4
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _0806443C
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	bl FUN_08009f6c
	str r0, [r4, #0x58]
_0806443C:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
