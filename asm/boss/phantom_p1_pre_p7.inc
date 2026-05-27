	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_0805f3e8
FUN_0805f3e8: @ 0x0805F3E8
	push {r4, lr}
	adds r4, r0, #0
	movs r0, #1
	strh r0, [r4, #0xe]
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _0805F420 @ =sCollisions
	bl SetDDP
	adds r0, r4, #0
	bl FUN_080608c8
	ldr r2, _0805F424 @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _0805F428 @ =0x000343FD
	muls r0, r1, r0
	ldr r1, _0805F42C @ =0x00269EC3
	adds r0, r0, r1
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r2]
	lsrs r0, r0, #0x11
	movs r1, #6
	ands r0, r1
	cmp r0, #0
	beq _0805F434
	ldr r0, _0805F430 @ =0xFFFFFA40
	b _0805F436
	.align 2, 0
_0805F420: .4byte sCollisions
_0805F424: .4byte RNG_0202f388
_0805F428: .4byte 0x000343FD
_0805F42C: .4byte 0x00269EC3
_0805F430: .4byte 0xFFFFFA40
_0805F434:
	ldr r0, _0805F440 @ =0xFFFFF940
_0805F436:
	str r0, [r4, #0x60]
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_0805F440: .4byte 0xFFFFF940

	thumb_func_start FUN_0805f444
FUN_0805f444: @ 0x0805F444
	push {r4, lr}
	adds r4, r0, #0
	bl FUN_080608e0
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _0805F45C
	movs r0, #2
	strh r0, [r4, #0xe]
	adds r0, r4, #0
	bl FUN_0805f464
_0805F45C:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start FUN_0805f464
FUN_0805f464: @ 0x0805F464
	push {r4, lr}
	adds r4, r0, #0
	bl FUN_08060924
	ldr r0, [r4, #0x60]
	cmp r0, #0
	ble _0805F482
	movs r0, #4
	strh r0, [r4, #0xe]
	adds r0, r4, #0
	movs r1, #8
	bl FUN_080607a0
	movs r0, #0
	strb r0, [r4, #0x12]
_0805F482:
	pop {r4}
	pop {r0}
	bx r0

	thumb_func_start FUN_0805f488
FUN_0805f488: @ 0x0805F488
	push {r4, lr}
	adds r4, r0, #0
	bl FUN_08060974
	lsls r0, r0, #0x18
	cmp r0, #0
	bge _0805F49C
	movs r0, #0
	strb r0, [r4, #0xd]
	strh r0, [r4, #0xe]
_0805F49C:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start FUN_0805f4a4
FUN_0805f4a4: @ 0x0805F4A4
	push {r4, r5, lr}
	sub sp, #8
	adds r5, r0, #0
	ldrb r0, [r5, #0x12]
	adds r0, #1
	strb r0, [r5, #0x12]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0x14
	bne _0805F508
	ldr r3, [r5, #0x54]
	str r3, [sp]
	ldr r2, [r5, #0x58]
	str r2, [sp, #4]
	ldr r0, _0805F4EC @ =pZero2
	ldr r1, [r0]
	ldr r0, [r1, #0x54]
	ldr r1, [r1, #0x58]
	subs r0, r0, r3
	subs r1, r1, r2
	ldr r2, _0805F4F0 @ =0xFFFFE800
	adds r1, r1, r2
	lsls r0, r0, #8
	asrs r0, r0, #0x10
	lsls r1, r1, #8
	asrs r1, r1, #0x10
	bl ArcTan2
	lsls r0, r0, #0x10
	lsrs r4, r0, #0x18
	cmp r4, #0x80
	bls _0805F4F6
	cmp r4, #0xc0
	bls _0805F4F4
	movs r4, #0
	b _0805F4F6
	.align 2, 0
_0805F4EC: .4byte pZero2
_0805F4F0: .4byte 0xFFFFE800
_0805F4F4:
	movs r4, #0x80
_0805F4F6:
	movs r0, #0xfc
	bl PlaySound
	movs r1, #0xc0
	lsls r1, r1, #2
	mov r0, sp
	adds r2, r4, #0
	bl FUN_080afcec
_0805F508:
	adds r0, r5, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _0805F522
	adds r0, r5, #0
	movs r1, #3
	movs r2, #2
	movs r3, #1
	bl FUN_080607bc
	movs r0, #5
	strh r0, [r5, #0xe]
_0805F522:
	add sp, #8
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start FUN_0805f52c
FUN_0805f52c:
	.byte 0x10, 0xB5, 0x04, 0x1C
	.byte 0x01, 0xF0, 0xF8, 0xF9, 0x00, 0x06, 0x00, 0x28, 0x05, 0xD0, 0x03, 0x20, 0xE0, 0x81, 0x20, 0x1C
	.byte 0x04, 0x21, 0x01, 0xF0, 0x2D, 0xF9, 0x10, 0xBC, 0x01, 0xBC, 0x00, 0x47
