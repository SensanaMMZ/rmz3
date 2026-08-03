	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_0809a31c
FUN_0809a31c: @ 0x0809A31C
	push {r4, r5, r6, lr}
	adds r4, r0, #0
	ldr r6, [r4, #0x28]
	adds r0, r6, #0
	adds r0, #0x31
	ldrb r0, [r0]
	cmp r0, #0
	beq _0809A33C
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _0809A338 @ =0x0836A6D4
	bl SetDDP
	b _0809A49A
	.align 2, 0
_0809A338: .4byte 0x0836A6D4
_0809A33C:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _0809A354 @ =0x0836A704
	bl SetDDP
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _0809A358
	cmp r0, #1
	beq _0809A3BE
	b _0809A49A
	.align 2, 0
_0809A354: .4byte 0x0836A704
_0809A358:
	adds r1, r4, #0
	adds r1, #0x22
	movs r0, #1
	strb r0, [r1]
	ldr r1, _0809A378 @ =0x00003501
	adds r0, r4, #0
	bl SetMotion
	ldrb r2, [r4, #0x12]
	cmp r2, #0
	beq _0809A37C
	ldrb r0, [r4, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _0809A382
	.align 2, 0
_0809A378: .4byte 0x00003501
_0809A37C:
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
_0809A382:
	strb r0, [r4, #0xa]
	movs r1, #1
	ands r1, r2
	adds r0, r4, #0
	adds r0, #0x4c
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
	movs r2, #0x80
	lsls r2, r2, #2
	ldrb r1, [r4, #0x12]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #8
	subs r2, r2, r0
	str r2, [r4, #0x5c]
	ldr r0, _0809A4A0 @ =0xFFFFFEC0
	str r0, [r4, #0x60]
	movs r0, #0x3c
	strb r0, [r4, #0x13]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0809A3BE:
	ldrb r0, [r4, #0x13]
	subs r0, #1
	movs r5, #0
	strb r0, [r4, #0x13]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _0809A3F2
	ldr r2, _0809A4A4 @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _0809A4A8 @ =0x000343FD
	muls r0, r1, r0
	ldr r1, _0809A4AC @ =0x00269EC3
	adds r0, r0, r1
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r2]
	lsrs r0, r0, #0x11
	movs r1, #0x1e
	bl __umodsi3
	adds r0, #0x1e
	strb r0, [r4, #0x13]
	ldr r1, _0809A4B0 @ =0x00003501
	adds r0, r4, #0
	bl SetMotion
_0809A3F2:
	ldr r1, [r4, #0x5c]
	lsls r0, r1, #7
	subs r0, r0, r1
	lsls r0, r0, #1
	cmp r0, #0
	bge _0809A400
	adds r0, #0xff
_0809A400:
	asrs r1, r0, #8
	str r1, [r4, #0x5c]
	ldr r0, [r4, #0x54]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	ldr r2, [r4, #0x60]
	adds r1, r1, r2
	str r1, [r4, #0x58]
	bl PushoutToUp1
	adds r1, r0, #0
	cmp r1, #0
	bge _0809A422
	ldr r0, [r4, #0x58]
	adds r0, r0, r1
	str r0, [r4, #0x58]
_0809A422:
	ldr r0, [r4, #0x60]
	adds r0, #0x10
	str r0, [r4, #0x60]
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x71
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	cmp r0, #2
	bne _0809A450
	ldr r0, _0809A4A0 @ =0xFFFFFEC0
	str r0, [r4, #0x60]
	movs r2, #0x80
	lsls r2, r2, #2
	ldrb r1, [r4, #0x12]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #8
	subs r2, r2, r0
	str r2, [r4, #0x5c]
_0809A450:
	ldr r0, [r4, #0x54]
	ldr r1, _0809A4B4 @ =0xFFFF3000
	adds r0, r0, r1
	movs r1, #0x98
	lsls r1, r1, #9
	cmp r0, r1
	bls _0809A49A
	str r5, [r6, #0x1c]
	adds r0, r6, #0
	adds r0, #0x32
	strb r5, [r0]
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	adds r0, #0x8c
	str r5, [r0]
	adds r0, #4
	str r5, [r0]
	adds r0, #4
	strb r5, [r0]
	ldrb r1, [r4, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r4, #0xa]
	ldr r1, _0809A4B8 @ =gEnemyFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r4, #0x14]
_0809A49A:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_0809A4A0: .4byte 0xFFFFFEC0
_0809A4A4: .4byte RNG_0202f388
_0809A4A8: .4byte 0x000343FD
_0809A4AC: .4byte 0x00269EC3
_0809A4B0: .4byte 0x00003501
_0809A4B4: .4byte 0xFFFF3000
_0809A4B8: .4byte gEnemyFnTable
