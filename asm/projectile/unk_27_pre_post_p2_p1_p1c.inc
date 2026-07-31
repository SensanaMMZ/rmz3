	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080a9920
FUN_080a9920: @ 0x080A9920
	push {r4, r5, r6, lr}
	adds r4, r0, #0
	ldr r1, _080A99C4 @ =gProjectileFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r4, #0x14]
	adds r0, r4, #0
	bl InitRotatableMotion
	ldrb r1, [r4, #0xa]
	movs r0, #1
	orrs r0, r1
	movs r1, #2
	orrs r0, r1
	strb r0, [r4, #0xa]
	ldr r1, _080A99C8 @ =0x00005C03
	adds r0, r4, #0
	bl SetMotion
	movs r6, #0
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	adds r0, #0x4c
	strb r6, [r0]
	adds r2, r4, #0
	adds r2, #0x4a
	ldrb r1, [r2]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r2]
	ldr r3, _080A99CC @ =gSineTable
	ldrb r2, [r4, #0x11]
	adds r1, r2, #0
	adds r1, #0xc0
	lsls r0, r2, #1
	adds r0, r0, r3
	movs r5, #0
	ldrsh r0, [r0, r5]
	lsls r0, r0, #2
	str r0, [r4, #0x5c]
	lsls r1, r1, #0x18
	lsrs r1, r1, #0x17
	adds r1, r1, r3
	movs r3, #0
	ldrsh r0, [r1, r3]
	lsls r0, r0, #2
	str r0, [r4, #0x60]
	movs r0, #8
	strb r0, [r4, #0x12]
	adds r0, r4, #0
	adds r0, #0x24
	strb r2, [r0]
	ldrb r1, [r4, #0xa]
	movs r0, #4
	orrs r0, r1
	strb r0, [r4, #0xa]
	adds r5, r4, #0
	adds r5, #0x74
	ldr r1, _080A99D0 @ =0x0836C1C8
	adds r2, r4, #0
	adds r2, #0x54
	adds r0, r5, #0
	movs r3, #0x40
	bl InitBody
	str r4, [r5, #0x2c]
	str r6, [r5, #0x24]
	adds r0, r4, #0
	bl Projectile27_Update
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_080A99C4: .4byte gProjectileFnTable
_080A99C8: .4byte 0x00005C03
_080A99CC: .4byte gSineTable
_080A99D0: .4byte 0x0836C1C8
