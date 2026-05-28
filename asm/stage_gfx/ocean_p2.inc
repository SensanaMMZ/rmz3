	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_0800d5bc
FUN_0800d5bc: @ 0x0800D5BC
	push {r4, r5, r6, lr}
	adds r3, r0, #0
	adds r5, r1, #0
	ldr r0, _0800D5D0 @ =0xFFFE2000
	adds r1, r5, r0
	ldr r0, _0800D5D4 @ =0x0001DFFF
	cmp r1, r0
	bls _0800D5D8
	movs r0, #0
	b _0800D610
	.align 2, 0
_0800D5D0: .4byte 0xFFFE2000
_0800D5D4: .4byte 0x0001DFFF
_0800D5D8:
	ldr r2, _0800D618 @ =gOverworld
	movs r6, #0xfc
	lsls r6, r6, #3
	adds r2, r2, r6
	ldrh r4, [r2]
	asrs r0, r5, #0xc
	adds r1, r4, #0
	muls r1, r0, r1
	asrs r3, r3, #0xc
	adds r1, r1, r3
	adds r1, #2
	lsls r1, r1, #1
	adds r1, r1, r2
	movs r6, #0xc8
	lsls r6, r6, #0xa
	adds r0, r5, r6
	asrs r0, r0, #0xc
	muls r0, r4, r0
	adds r0, r0, r3
	adds r0, #2
	lsls r0, r0, #1
	adds r0, r0, r2
	ldrh r1, [r1]
	ldrh r0, [r0]
	eors r1, r0
	rsbs r0, r1, #0
	orrs r0, r1
	lsrs r0, r0, #0x1f
_0800D610:
	pop {r4, r5, r6}
	pop {r1}
	bx r1
	.align 2, 0
_0800D618: .4byte gOverworld

	thumb_func_start FUN_0800d61c
FUN_0800d61c: @ 0x0800D61C
	push {r4, r5, lr}
	sub sp, #8
	adds r5, r0, #0
	adds r4, r1, #0
	ldr r0, _0800D660 @ =Coord_080fecc4
	ldr r1, [r0, #4]
	ldr r0, [r0]
	str r0, [sp]
	str r1, [sp, #4]
	adds r0, r5, #0
	adds r1, r4, #0
	bl FUN_0800d5bc
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _0800D664
	asrs r0, r5, #0xc
	lsls r2, r0, #0x10
	movs r3, #0xc8
	lsls r3, r3, #0xa
	adds r1, r4, r3
	lsls r1, r1, #4
	lsrs r1, r1, #0x10
	lsls r1, r1, #0x10
	lsrs r2, r2, #0x10
	orrs r2, r1
	str r2, [sp]
	asrs r1, r4, #0xc
	mov r2, sp
	bl ShiftMetatile
	movs r0, #1
	b _0800D666
	.align 2, 0
_0800D660: .4byte Coord_080fecc4
_0800D664:
	movs r0, #0
_0800D666:
	add sp, #8
	pop {r4, r5}
	pop {r1}
	bx r1
	.align 2, 0
