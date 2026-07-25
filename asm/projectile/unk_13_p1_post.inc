	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_0809f970
FUN_0809f970: @ 0x0809F970
	push {r4, r5, r6, lr}
	adds r5, r0, #0
	adds r6, r1, #0
	lsls r2, r2, #0x18
	lsrs r4, r2, #0x18
	ldr r0, _0809F9D8 @ =gProjectileHeaderPtr
	ldr r0, [r0]
	bl AllocEntityLast
	adds r3, r0, #0
	cmp r3, #0
	beq _0809F9D2
	adds r1, r3, #0
	adds r1, #0x25
	movs r2, #0
	movs r0, #8
	strb r0, [r1]
	ldr r1, _0809F9DC @ =gProjectileFnTable
	movs r0, #0xd
	strb r0, [r3, #9]
	ldr r0, [r1, #0x34]
	ldr r0, [r0]
	str r0, [r3, #0x14]
	movs r0, #0
	strh r2, [r3, #0x20]
	adds r1, r3, #0
	adds r1, #0x22
	strb r0, [r1]
	movs r0, #1
	strb r0, [r3, #0x10]
	strb r4, [r3, #0x12]
	str r5, [r3, #0x64]
	str r6, [r3, #0x68]
	ldr r2, _0809F9E0 @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _0809F9E4 @ =0x000343FD
	muls r0, r1, r0
	ldr r1, _0809F9E8 @ =0x00269EC3
	adds r0, r0, r1
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r2]
	lsls r0, r0, #4
	lsrs r0, r0, #0x15
	ldr r1, _0809F9EC @ =0xFFFFFC00
	adds r0, r0, r1
	adds r0, r5, r0
	str r0, [r3, #0x54]
	str r6, [r3, #0x58]
_0809F9D2:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_0809F9D8: .4byte gProjectileHeaderPtr
_0809F9DC: .4byte gProjectileFnTable
_0809F9E0: .4byte RNG_0202f388
_0809F9E4: .4byte 0x000343FD
_0809F9E8: .4byte 0x00269EC3
_0809F9EC: .4byte 0xFFFFFC00
