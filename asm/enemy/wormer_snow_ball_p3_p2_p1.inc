	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_0807b328
FUN_0807b328: @ 0x0807B328
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _0807B338
	cmp r0, #1
	beq _0807B376
	b _0807B402
_0807B338:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _0807B3E0 @ =0x0836782C
	bl SetDDP
	ldr r0, _0807B3E4 @ =0xFFFFFB00
	str r0, [r4, #0x60]
	ldr r2, _0807B3E8 @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _0807B3EC @ =0x000343FD
	muls r0, r1, r0
	ldr r1, _0807B3F0 @ =0x00269EC3
	adds r0, r0, r1
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r2]
	lsrs r0, r0, #0x11
	movs r1, #0xc0
	lsls r1, r1, #2
	bl __umodsi3
	rsbs r0, r0, #0
	str r0, [r4, #0x5c]
	movs r1, #0x80
	lsls r1, r1, #7
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0807B376:
	ldr r0, [r4, #0x60]
	adds r0, #0x20
	str r0, [r4, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _0807B386
	str r1, [r4, #0x60]
_0807B386:
	ldr r0, [r4, #0x58]
	ldr r1, [r4, #0x60]
	adds r0, r0, r1
	str r0, [r4, #0x58]
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	ldr r0, _0807B3F4 @ =gStageRun+232
	adds r1, r4, #0
	adds r1, #0x54
	bl CalcFromCamera
	movs r1, #0x80
	lsls r1, r1, #3
	cmp r0, r1
	bls _0807B3FC
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r2, #0
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	adds r0, #0x8c
	str r2, [r0]
	adds r0, #4
	str r2, [r0]
	adds r0, #4
	strb r2, [r0]
	ldrb r1, [r4, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r4, #0xa]
	ldr r1, _0807B3F8 @ =gEnemyFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r4, #0x14]
	b _0807B402
	.align 2, 0
_0807B3E0: .4byte 0x0836782C
_0807B3E4: .4byte 0xFFFFFB00
_0807B3E8: .4byte RNG_0202f388
_0807B3EC: .4byte 0x000343FD
_0807B3F0: .4byte 0x00269EC3
_0807B3F4: .4byte gStageRun+232
_0807B3F8: .4byte gEnemyFnTable
_0807B3FC:
	adds r0, r4, #0
	bl UpdateMotionGraphic
_0807B402:
	pop {r4}
	pop {r0}
	bx r0

	thumb_func_start FUN_0807b408
FUN_0807b408: @ 0x0807B408
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r5, [r4, #0xe]
	cmp r5, #0
	beq _0807B418
	cmp r5, #1
	beq _0807B434
	b _0807B48E
_0807B418:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _0807B47C @ =0x0836782C
	bl SetDDP
	strb r5, [r4, #0x12]
	movs r1, #0x80
	lsls r1, r1, #7
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0807B434:
	ldrb r0, [r4, #0x12]
	adds r0, #6
	strb r0, [r4, #0x12]
	ldr r1, _0807B480 @ =gSineTable
	ldrb r0, [r4, #0x12]
	lsls r0, r0, #1
	adds r0, r0, r1
	movs r2, #0
	ldrsh r1, [r0, r2]
	cmp r1, #0
	bge _0807B44C
	adds r1, #3
_0807B44C:
	asrs r1, r1, #2
	ldr r0, [r4, #0x54]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	adds r1, #0x60
	str r1, [r4, #0x58]
	bl FUN_080098a4
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _0807B488
	ldr r1, _0807B484 @ =gEnemyFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r4, #0x14]
	ldrb r0, [r4, #0x10]
	strb r0, [r4, #0xd]
	b _0807B48E
	.align 2, 0
_0807B47C: .4byte 0x0836782C
_0807B480: .4byte gSineTable
_0807B484: .4byte gEnemyFnTable
_0807B488:
	adds r0, r4, #0
	bl UpdateMotionGraphic
_0807B48E:
	pop {r4, r5}
	pop {r0}
	bx r0
