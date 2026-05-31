	.include "asm/macros.inc"

	.syntax unified

	.text


	thumb_func_start FUN_0809dd60
FUN_0809dd60: @ 0x0809DD60
	push {r4, r5, r6, lr}
	adds r4, r0, #0
	ldr r1, [r4, #0x28]
	ldrb r0, [r1, #0xc]
	cmp r0, #1
	bls _0809DD8C
	ldr r1, _0809DD88 @ =gProjectileFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r4, #0x14]
	adds r0, r4, #0
	bl Projectile6_Die
	b _0809DDFA
	.align 2, 0
_0809DD88: .4byte gProjectileFnTable
_0809DD8C:
	ldrb r0, [r1, #0xa]
	lsrs r2, r0, #4
	movs r0, #1
	ands r2, r0
	cmp r2, #0
	beq _0809DDA0
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	orrs r0, r1
	b _0809DDA6
_0809DDA0:
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
_0809DDA6:
	strb r0, [r4, #0xa]
	movs r5, #1
	adds r1, r5, #0
	ands r1, r2
	adds r0, r4, #0
	adds r0, #0x4c
	movs r6, #0
	strb r1, [r0]
	adds r3, r4, #0
	adds r3, #0x4a
	lsls r1, r1, #4
	ldrb r2, [r3]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r1
	strb r0, [r3]
	adds r1, r4, #0
	adds r1, #0xb4
	ldr r0, [r1]
	ands r0, r5
	cmp r0, #0
	beq _0809DDDC
	str r6, [r1]
	strb r5, [r4, #0xd]
	strb r6, [r4, #0xe]
	b _0809DDFA
_0809DDDC:
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	bne _0809DDFA
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _0809DE00 @ =0x0836ABF8
	bl SetDDP
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0809DDFA:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_0809DE00: .4byte 0x0836ABF8

	thumb_func_start FUN_0809de04
FUN_0809de04: @ 0x0809DE04
	push {r4, r5, r6, lr}
	adds r4, r0, #0
	ldr r1, [r4, #0x28]
	ldrb r0, [r1, #0xc]
	cmp r0, #1
	bls _0809DE30
	ldr r1, _0809DE2C @ =gProjectileFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r4, #0x14]
	adds r0, r4, #0
	bl Projectile6_Die
	b _0809DF0C
	.align 2, 0
_0809DE2C: .4byte gProjectileFnTable
_0809DE30:
	ldrb r0, [r1, #0xa]
	lsrs r2, r0, #4
	movs r0, #1
	ands r2, r0
	cmp r2, #0
	beq _0809DE44
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	orrs r0, r1
	b _0809DE4A
_0809DE44:
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
_0809DE4A:
	strb r0, [r4, #0xa]
	adds r1, r2, #0
	adds r0, r4, #0
	adds r0, #0x4c
	movs r5, #0
	strb r1, [r0]
	adds r3, r4, #0
	adds r3, #0x4a
	lsls r1, r1, #4
	ldrb r2, [r3]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r1
	strb r0, [r3]
	adds r1, r4, #0
	adds r1, #0xb4
	ldr r6, [r1]
	movs r0, #2
	ands r6, r0
	cmp r6, #0
	beq _0809DE7E
	str r5, [r1]
	strb r5, [r4, #0xd]
	strb r5, [r4, #0xe]
	b _0809DF0C
_0809DE7E:
	ldrb r5, [r4, #0xe]
	cmp r5, #1
	beq _0809DEB4
	cmp r5, #1
	bgt _0809DE8E
	cmp r5, #0
	beq _0809DE94
	b _0809DF0C
_0809DE8E:
	cmp r5, #2
	beq _0809DEF8
	b _0809DF0C
_0809DE94:
	ldrb r0, [r4, #0xa]
	movs r1, #1
	orrs r0, r1
	strb r0, [r4, #0xa]
	ldr r1, _0809DEEC @ =0x00001905
	adds r0, r4, #0
	bl SetMotion
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _0809DEF0 @ =0x0836AC10
	bl SetDDP
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0809DEB4:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x71
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	cmp r0, #1
	bne _0809DED8
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _0809DEF4 @ =0x0836AC28
	bl SetDDP
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0809DED8:
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _0809DF0C
	movs r1, #0
	movs r0, #2
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
	b _0809DF0C
	.align 2, 0
_0809DEEC: .4byte 0x00001905
_0809DEF0: .4byte 0x0836AC10
_0809DEF4: .4byte 0x0836AC28
_0809DEF8:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _0809DF0C
	strb r5, [r4, #0xd]
	strb r6, [r4, #0xe]
_0809DF0C:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0

