	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_08096348
FUN_08096348: @ 0x08096348
	push {r4, lr}
	ldr r4, [r0, #0x2c]
	adds r3, r4, #0
	adds r3, #0xb4
	ldr r1, _08096370 @ =pZero2
	ldr r1, [r1]
	ldr r1, [r1, #0x54]
	ldr r2, [r4, #0x54]
	subs r1, r1, r2
	str r1, [r3]
	ldr r0, [r0, #0x14]
	movs r1, #1
	ands r0, r1
	cmp r0, #0
	beq _0809642E
	ldrb r0, [r4, #0x10]
	cmp r0, #4
	bne _08096374
	ldr r4, [r4, #0x28]
	b _08096384
	.align 2, 0
_08096370: .4byte pZero2
_08096374:
	ldrb r1, [r4, #0xd]
	subs r0, r1, #3
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #1
	bls _0809642E
	cmp r1, #8
	beq _0809642E
_08096384:
	adds r1, r4, #0
	adds r1, #0xbc
	ldrb r2, [r1]
	cmp r2, #0
	bne _0809642E
	movs r0, #1
	strb r0, [r1]
	ldrb r0, [r4, #0x10]
	cmp r0, #4
	beq _080963D2
	ldr r0, [r4, #0x2c]
	cmp r0, #0
	beq _080963D2
	str r2, [r4, #0x2c]
	ldrb r1, [r2, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r2, #0xa]
	movs r0, #0x8c
	str r2, [r0]
	movs r0, #0x90
	str r2, [r0]
	movs r0, #0x94
	strb r2, [r0]
	ldrb r1, [r2, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r2, #0xa]
	ldr r1, _08096404 @ =gEnemyFnTable
	ldrb r0, [r2, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r2, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r2, #0x14]
_080963D2:
	movs r1, #0
	movs r0, #1
	strb r0, [r4, #0x10]
	movs r0, #7
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
	ldr r1, _08096408 @ =0x0000DB08
	adds r0, r4, #0
	bl SetMotion
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0xb8
	ldr r0, [r0]
	cmp r0, #0
	bne _08096410
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _0809640C @ =0x0836A0BC
	bl SetDDP
	b _0809641A
	.align 2, 0
_08096404: .4byte gEnemyFnTable
_08096408: .4byte 0x0000DB08
_0809640C: .4byte 0x0836A0BC
_08096410:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _08096434 @ =0x0836A1AC
	bl SetDDP
_0809641A:
	movs r1, #0
	adds r0, r4, #0
	adds r0, #0xb4
	ldr r0, [r0]
	cmp r0, #0
	ble _08096428
	movs r1, #1
_08096428:
	adds r0, r4, #0
	bl FUN_080c6934
_0809642E:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_08096434: .4byte 0x0836A1AC

