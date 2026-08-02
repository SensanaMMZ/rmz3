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
