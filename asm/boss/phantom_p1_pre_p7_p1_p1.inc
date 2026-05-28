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
