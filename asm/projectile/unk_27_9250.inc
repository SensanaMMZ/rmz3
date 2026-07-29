	.include "asm/macros.inc"

	.syntax unified

	.text

	push {r4, r5, r6, r7, lr}
	adds r6, r0, #0
	ldr r5, [r6, #0x28]
	ldr r1, _080A9298 @ =gProjectileFnTable
	ldrb r0, [r6, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r4, #1
	str r4, [r6, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r6, #0x14]
	adds r0, r6, #0
	bl InitNonAffineMotion
	ldrb r1, [r6, #0xa]
	movs r0, #1
	movs r7, #0
	orrs r0, r1
	movs r1, #2
	orrs r0, r1
	strb r0, [r6, #0xa]
	movs r1, #0xb8
	lsls r1, r1, #7
	adds r0, r6, #0
	bl SetMotion
	ldrb r0, [r5, #0xa]
	lsrs r2, r0, #4
	ands r2, r4
	cmp r2, #0
	beq _080A929C
	ldrb r0, [r6, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _080A92A2
	.align 2, 0
_080A9298: .4byte gProjectileFnTable
_080A929C:
	ldrb r1, [r6, #0xa]
	movs r0, #0xef
	ands r0, r1
_080A92A2:
	strb r0, [r6, #0xa]
	adds r1, r2, #0
	adds r0, r6, #0
	adds r0, #0x4c
	strb r1, [r0]
	adds r3, r6, #0
	adds r3, #0x4a
	lsls r1, r1, #4
	ldrb r2, [r3]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r1
	strb r0, [r3]
	ldrb r1, [r6, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _080A92E8
	ldr r0, [r6, #0x54]
	movs r1, #0x80
	lsls r1, r1, #5
	adds r0, r0, r1
	str r0, [r6, #0x54]
	movs r0, #0xc0
	lsls r0, r0, #2
	str r0, [r6, #0x5c]
	str r0, [r6, #0x60]
	adds r1, r6, #0
	adds r1, #0xbc
	ldr r0, _080A92E4 @ =0x0000FFE0
	b _080A9300
	.align 2, 0
_080A92E4: .4byte 0x0000FFE0
_080A92E8:
	ldr r0, [r6, #0x54]
	ldr r1, _080A9344 @ =0xFFFFF000
	adds r0, r0, r1
	str r0, [r6, #0x54]
	ldr r0, _080A9348 @ =0xFFFFFD00
	str r0, [r6, #0x5c]
	movs r0, #0xc0
	lsls r0, r0, #2
	str r0, [r6, #0x60]
	adds r1, r6, #0
	adds r1, #0xbc
	movs r0, #0x20
_080A9300:
	strh r0, [r1]
	ldr r0, [r6, #0x58]
	ldr r1, _080A934C @ =0xFFFFEE00
	adds r0, r0, r1
	str r0, [r6, #0x58]
	adds r1, r6, #0
	adds r1, #0xbe
	movs r5, #0
	ldr r0, _080A9350 @ =0x0000FFE0
	strh r0, [r1]
	ldrb r1, [r6, #0xa]
	movs r0, #4
	orrs r0, r1
	strb r0, [r6, #0xa]
	adds r4, r6, #0
	adds r4, #0x74
	ldr r1, _080A9354 @ =0x0836C108
	adds r2, r6, #0
	adds r2, #0x54
	adds r0, r4, #0
	movs r3, #0x40
	bl InitBody
	str r6, [r4, #0x2c]
	str r5, [r4, #0x24]
	movs r0, #0xff
	strb r0, [r6, #0x12]
	adds r0, r6, #0
	bl Projectile27_Update
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080A9344: .4byte 0xFFFFF000
_080A9348: .4byte 0xFFFFFD00
_080A934C: .4byte 0xFFFFEE00
_080A9350: .4byte 0x0000FFE0
_080A9354: .4byte 0x0836C108
