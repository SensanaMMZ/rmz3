	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080733b4
FUN_080733b4: @ 0x080733B4
	push {r4, r5, lr}
	sub sp, #0x10
	adds r5, r0, #0
	ldrb r1, [r5, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	bne _080733F8
	movs r0, #0x98
	lsls r0, r0, #5
	str r0, [sp]
	ldr r2, _080733EC @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _080733F0 @ =0x000343FD
	muls r0, r1, r0
	ldr r1, _080733F4 @ =0x00269EC3
	adds r0, r0, r1
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r2]
	lsrs r0, r0, #0x11
	movs r1, #0x1f
	ands r0, r1
	movs r1, #0xb4
	lsls r1, r1, #1
	adds r0, r0, r1
	b _08073418
	.align 2, 0
_080733EC: .4byte RNG_0202f388
_080733F0: .4byte 0x000343FD
_080733F4: .4byte 0x00269EC3
_080733F8:
	ldr r0, _0807344C @ =0xFFFFED00
	str r0, [sp]
	ldr r2, _08073450 @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _08073454 @ =0x000343FD
	muls r1, r0, r1
	ldr r0, _08073458 @ =0x00269EC3
	adds r1, r1, r0
	lsls r1, r1, #1
	lsrs r0, r1, #1
	str r0, [r2]
	lsrs r1, r1, #0x11
	movs r0, #0x1f
	ands r1, r0
	ldr r0, _0807345C @ =0xFFFFFE98
	subs r0, r0, r1
_08073418:
	str r0, [sp, #8]
	ldr r0, [r5, #0x54]
	ldr r1, [sp]
	adds r0, r0, r1
	str r0, [sp]
	ldr r0, [r5, #0x58]
	ldr r1, _08073460 @ =0xFFFFE800
	adds r0, r0, r1
	str r0, [sp, #4]
	movs r0, #0xb4
	lsls r0, r0, #1
	add r4, sp, #8
	str r0, [r4, #4]
	mov r0, sp
	adds r1, r4, #0
	movs r2, #0
	bl FUN_080ba888
	ldrb r1, [r5, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	bne _08073468
	ldr r0, _08073464 @ =0xFFFFFC00
	b _0807346C
	.align 2, 0
_0807344C: .4byte 0xFFFFED00
_08073450: .4byte RNG_0202f388
_08073454: .4byte 0x000343FD
_08073458: .4byte 0x00269EC3
_0807345C: .4byte 0xFFFFFE98
_08073460: .4byte 0xFFFFE800
_08073464: .4byte 0xFFFFFC00
_08073468:
	movs r0, #0x80
	lsls r0, r0, #3
_0807346C:
	str r0, [sp]
	ldr r0, [sp]
	ldr r1, [r5, #0x54]
	adds r0, r0, r1
	str r0, [sp]
	ldr r0, [r5, #0x58]
	ldr r1, _080734A8 @ =0xFFFFE800
	adds r0, r0, r1
	str r0, [sp, #4]
	ldrb r1, [r5, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	bne _080734B8
	ldr r2, _080734AC @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _080734B0 @ =0x000343FD
	muls r0, r1, r0
	ldr r1, _080734B4 @ =0x00269EC3
	adds r0, r0, r1
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r2]
	lsrs r0, r0, #0x11
	movs r1, #0x1f
	ands r0, r1
	movs r1, #0xa4
	lsls r1, r1, #1
	adds r0, r0, r1
	b _080734D4
	.align 2, 0
_080734A8: .4byte 0xFFFFE800
_080734AC: .4byte RNG_0202f388
_080734B0: .4byte 0x000343FD
_080734B4: .4byte 0x00269EC3
_080734B8:
	ldr r2, _080734F0 @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _080734F4 @ =0x000343FD
	muls r1, r0, r1
	ldr r0, _080734F8 @ =0x00269EC3
	adds r1, r1, r0
	lsls r1, r1, #1
	lsrs r0, r1, #1
	str r0, [r2]
	lsrs r1, r1, #0x11
	movs r0, #0x1f
	ands r1, r0
	ldr r0, _080734FC @ =0xFFFFFEB8
	subs r0, r0, r1
_080734D4:
	str r0, [sp, #8]
	movs r0, #0xc4
	lsls r0, r0, #1
	str r0, [r4, #4]
	mov r0, sp
	adds r1, r4, #0
	movs r2, #1
	bl FUN_080ba888
	add sp, #0x10
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080734F0: .4byte RNG_0202f388
_080734F4: .4byte 0x000343FD
_080734F8: .4byte 0x00269EC3
_080734FC: .4byte 0xFFFFFEB8

	thumb_func_start FUN_08073500
FUN_08073500: @ 0x08073500
	push {r4, r5, r6, lr}
	ldr r1, _08073574 @ =pZero2
	ldr r3, [r1]
	ldr r2, [r3, #0x54]
	ldr r1, [r0, #0x54]
	subs r4, r2, r1
	ldr r0, [r0, #0x58]
	movs r1, #0xc0
	lsls r1, r1, #4
	adds r0, r0, r1
	ldr r1, [r3, #0x58]
	subs r5, r1, r0
	asrs r0, r4, #2
	adds r2, r0, #0
	muls r2, r0, r2
	adds r0, r2, #0
	asrs r1, r5, #2
	adds r2, r1, #0
	muls r2, r1, r2
	adds r1, r2, #0
	adds r0, r0, r1
	bl Sqrt
	lsls r0, r0, #0x10
	lsrs r6, r0, #0xe
	cmp r6, #0
	beq _0807354A
	lsls r0, r4, #8
	adds r1, r6, #0
	bl __divsi3
	adds r4, r0, #0
	lsls r0, r5, #8
	adds r1, r6, #0
	bl __divsi3
	adds r5, r0, #0
_0807354A:
	cmp r4, #0
	ble _08073578
	adds r0, r5, #0
	cmp r0, #0
	bge _08073556
	rsbs r0, r0, #0
_08073556:
	cmp r0, #0xec
	bgt _08073584
	adds r1, r5, #0
	cmp r1, #0
	bge _08073562
	rsbs r1, r1, #0
_08073562:
	movs r0, #2
	cmp r1, #0x60
	ble _080735A4
	movs r0, #1
	cmp r5, #0
	ble _080735A4
	movs r0, #3
	b _080735A4
	.align 2, 0
_08073574: .4byte pZero2
_08073578:
	adds r0, r5, #0
	cmp r0, #0
	bge _08073580
	rsbs r0, r0, #0
_08073580:
	cmp r0, #0xec
	ble _0807358E
_08073584:
	movs r0, #0
	cmp r5, #0
	ble _080735A4
	movs r0, #4
	b _080735A4
_0807358E:
	adds r1, r5, #0
	cmp r1, #0
	bge _08073596
	rsbs r1, r1, #0
_08073596:
	movs r0, #6
	cmp r1, #0x60
	ble _080735A4
	movs r0, #7
	cmp r5, #0
	ble _080735A4
	movs r0, #5
_080735A4:
	pop {r4, r5, r6}
	pop {r1}
	bx r1
	.align 2, 0

