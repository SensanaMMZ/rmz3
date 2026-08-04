	.include "asm/macros.inc"

	.syntax unified

	.text


	thumb_func_start FUN_08094320
FUN_08094320: @ 0x08094320
	push {r4, r5, r6, r7, lr}
	mov r7, sl
	mov r6, sb
	mov r5, r8
	push {r5, r6, r7}
	sub sp, #4
	adds r4, r0, #0
	ldr r6, [r4, #0x28]
	ldrb r0, [r6, #0xc]
	cmp r0, #1
	bls _08094374
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
	ldr r1, _08094370 @ =gEnemyFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r4, #0x14]
	b _08094522
	.align 2, 0
_08094370: .4byte gEnemyFnTable
_08094374:
	ldrb r5, [r4, #0xe]
	cmp r5, #0
	beq _08094380
	cmp r5, #1
	beq _080943BC
	b _08094522
_08094380:
	adds r0, r4, #0
	bl InitRotatableMotion
	ldr r1, _080944B4 @ =0x00008E01
	adds r0, r4, #0
	bl SetMotion
	adds r1, r4, #0
	adds r1, #0x25
	movs r0, #0x1a
	strb r0, [r1]
	ldrb r0, [r6, #0xa]
	lsrs r0, r0, #4
	movs r1, #1
	eors r0, r1
	ands r0, r1
	strb r0, [r4, #0x12]
	movs r1, #0x80
	lsls r1, r1, #1
	ldrb r0, [r4, #0x12]
	lsls r0, r0, #9
	subs r1, r1, r0
	str r1, [r4, #0x64]
	str r5, [r4, #0x68]
	ldrb r0, [r4, #0x12]
	lsls r0, r0, #7
	strb r0, [r4, #0x13]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080943BC:
	ldr r0, [r6, #0x54]
	str r0, [r4, #0x54]
	ldr r0, [r6, #0x58]
	ldr r1, _080944B8 @ =0xFFFFF300
	adds r0, r0, r1
	str r0, [r4, #0x58]
	adds r0, r6, #0
	bl IsFrozen
	cmp r0, #0
	beq _080943D4
	b _080944F4
_080943D4:
	adds r7, r6, #0
	adds r7, #0xb8
	ldr r2, [r7]
	movs r0, #1
	ands r2, r0
	cmp r2, #0
	beq _080944CC
	ldrb r1, [r4, #0xa]
	orrs r0, r1
	strb r0, [r4, #0xa]
	ldr r2, [r4, #0x54]
	mov r8, r2
	ldr r3, [r4, #0x58]
	mov sb, r3
	ldr r0, _080944BC @ =pZero2
	ldr r0, [r0]
	ldr r5, [r0, #0x54]
	subs r5, r5, r2
	lsls r0, r5, #3
	subs r0, r0, r5
	lsls r0, r0, #5
	cmp r0, #0
	bge _08094404
	adds r0, #0xff
_08094404:
	asrs r5, r0, #8
	adds r0, r5, #0
	movs r1, #0x1e
	bl __divsi3
	adds r5, r0, #0
	ldr r0, _080944C0 @ =0xFFFFFD00
	cmp r5, r0
	bge _08094418
	adds r5, r0, #0
_08094418:
	movs r0, #0xc0
	lsls r0, r0, #2
	cmp r5, r0
	ble _08094422
	adds r5, r0, #0
_08094422:
	ldr r0, _080944C4 @ =0xFFFFFC40
	mov sl, r0
	ldr r1, [r4, #0x64]
	subs r0, r5, r1
	cmp r0, #0
	bge _08094430
	adds r0, #0xf
_08094430:
	asrs r0, r0, #4
	adds r0, r1, r0
	str r0, [r4, #0x64]
	ldr r2, [r4, #0x68]
	mov r3, sl
	subs r1, r3, r2
	cmp r1, #0
	bge _08094442
	adds r1, #0xf
_08094442:
	asrs r1, r1, #4
	adds r1, r2, r1
	str r1, [r4, #0x68]
	lsls r0, r0, #0x10
	asrs r0, r0, #0x10
	lsls r1, r1, #0x10
	asrs r1, r1, #0x10
	bl ArcTan2
	lsrs r0, r0, #8
	strb r0, [r4, #0x13]
	ldr r0, [r7]
	movs r1, #2
	ands r0, r1
	cmp r0, #0
	beq _08094512
	movs r0, #0x2d
	bl PlaySound
	ldr r0, [r7]
	movs r1, #3
	rsbs r1, r1, #0
	ands r0, r1
	str r0, [r7]
	ldr r2, _080944C8 @ =gSineTable
	ldrb r0, [r4, #0x13]
	adds r0, #0x40
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x17
	adds r0, r0, r2
	movs r3, #0
	ldrsh r1, [r0, r3]
	lsls r0, r1, #2
	adds r0, r0, r1
	lsls r0, r0, #2
	subs r0, r0, r1
	add r8, r0
	ldrb r0, [r4, #0x13]
	lsls r0, r0, #1
	adds r0, r0, r2
	movs r2, #0
	ldrsh r1, [r0, r2]
	lsls r0, r1, #2
	adds r0, r0, r1
	lsls r0, r0, #2
	subs r0, r0, r1
	add sb, r0
	ldrb r0, [r6, #0x11]
	str r0, [sp]
	mov r0, r8
	mov r1, sb
	adds r2, r5, #0
	mov r3, sl
	bl FUN_080b1234
	b _08094512
	.align 2, 0
_080944B4: .4byte 0x00008E01
_080944B8: .4byte 0xFFFFF300
_080944BC: .4byte pZero2
_080944C0: .4byte 0xFFFFFD00
_080944C4: .4byte 0xFFFFFC40
_080944C8: .4byte gSineTable
_080944CC:
	movs r0, #0x80
	lsls r0, r0, #1
	str r0, [r4, #0x64]
	adds r3, r0, #0
	ldrb r1, [r6, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	bne _080944E0
	ldr r3, _080944F0 @ =0xFFFFFF00
_080944E0:
	str r3, [r4, #0x64]
	str r2, [r4, #0x68]
	adds r0, r3, #0
	movs r1, #0
	bl ArcTan2
	strb r0, [r4, #0x13]
	b _0809450A
	.align 2, 0
_080944F0: .4byte 0xFFFFFF00
_080944F4:
	adds r0, r6, #0
	adds r0, #0xb8
	ldr r0, [r0]
	movs r1, #1
	ands r0, r1
	cmp r0, #0
	beq _0809450A
	ldrb r1, [r4, #0xa]
	movs r0, #1
	orrs r0, r1
	b _08094510
_0809450A:
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
_08094510:
	strb r0, [r4, #0xa]
_08094512:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldrb r0, [r4, #0x13]
	adds r0, #0x80
	adds r1, r4, #0
	adds r1, #0x24
	strb r0, [r1]
_08094522:
	add sp, #4
	pop {r3, r4, r5}
	mov r8, r3
	mov sb, r4
	mov sl, r5
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
