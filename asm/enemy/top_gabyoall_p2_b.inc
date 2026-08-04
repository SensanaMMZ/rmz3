	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_0806f964
FUN_0806f964: @ 0x0806F964
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xd]
	cmp r0, #1
	beq _0806F9C0
	cmp r0, #1
	bgt _0806F978
	cmp r0, #0
	beq _0806F97E
	b _0806FA38
_0806F978:
	cmp r0, #2
	beq _0806FA0C
	b _0806FA38
_0806F97E:
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	bne _0806F9A4
	movs r1, #0xa8
	lsls r1, r1, #5
	adds r0, r4, #0
	bl SetMotion
	ldr r0, [r4, #0x5c]
	cmp r0, #0
	ble _0806F998
	movs r0, #0x80
	b _0806F99C
_0806F998:
	movs r0, #0x80
	rsbs r0, r0, #0
_0806F99C:
	str r0, [r4, #0x5c]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0806F9A4:
	ldr r1, [r4, #0x58]
	asrs r1, r1, #8
	ldr r0, _0806F9BC @ =pZero2
	ldr r0, [r0]
	ldr r0, [r0, #0x58]
	asrs r0, r0, #8
	cmp r1, r0
	bne _0806FA38
	movs r1, #0
	movs r0, #1
	strb r0, [r4, #0xd]
	b _0806FA36
	.align 2, 0
_0806F9BC: .4byte pZero2
_0806F9C0:
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	bne _0806F9EA
	ldr r1, _0806F9DC @ =0x00001501
	adds r0, r4, #0
	bl SetMotion
	ldr r0, [r4, #0x5c]
	cmp r0, #0
	ble _0806F9E0
	movs r0, #0xa0
	lsls r0, r0, #2
	b _0806F9E2
	.align 2, 0
_0806F9DC: .4byte 0x00001501
_0806F9E0:
	ldr r0, _0806FA04 @ =0xFFFFFD80
_0806F9E2:
	str r0, [r4, #0x5c]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0806F9EA:
	ldr r1, [r4, #0x58]
	asrs r1, r1, #8
	ldr r0, _0806FA08 @ =pZero2
	ldr r0, [r0]
	ldr r0, [r0, #0x58]
	asrs r0, r0, #8
	cmp r1, r0
	beq _0806FA38
	movs r0, #0
	strb r0, [r4, #0xd]
	strb r0, [r4, #0xe]
	b _0806FA38
	.align 2, 0
_0806FA04: .4byte 0xFFFFFD80
_0806FA08: .4byte pZero2
_0806FA0C:
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	bne _0806FA24
	ldr r1, _0806FA74 @ =0x00001503
	adds r0, r4, #0
	bl SetMotion
	movs r0, #0x40
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0806FA24:
	ldrb r0, [r4, #0x12]
	subs r0, #1
	movs r1, #0
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0xff
	bne _0806FA38
	strb r1, [r4, #0xd]
_0806FA36:
	strb r1, [r4, #0xe]
_0806FA38:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldrb r0, [r4, #0xd]
	cmp r0, #2
	beq _0806FB02
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	adds r2, r0, r1
	str r2, [r4, #0x54]
	ldrb r0, [r4, #0x11]
	cmp r0, #2
	bne _0806FA88
	ldr r1, [r4, #0x58]
	adds r0, r2, #0
	bl FUN_0800a05c
	adds r1, r0, #0
	str r1, [r4, #0x58]
	ldr r0, [r4, #0x5c]
	cmp r0, #0
	ble _0806FA78
	ldr r0, [r4, #0x54]
	movs r2, #0xa0
	lsls r2, r2, #4
	adds r0, r0, r2
	bl FUN_0800a05c
	b _0806FAAC
	.align 2, 0
_0806FA74: .4byte 0x00001503
_0806FA78:
	ldr r0, [r4, #0x54]
	ldr r2, _0806FA84 @ =0xFFFFF600
	adds r0, r0, r2
	bl FUN_0800a05c
	b _0806FAAC
	.align 2, 0
_0806FA84: .4byte 0xFFFFF600
_0806FA88:
	ldr r1, [r4, #0x58]
	adds r0, r2, #0
	bl FUN_08009f6c
	adds r1, r0, #0
	str r1, [r4, #0x58]
	ldr r0, [r4, #0x5c]
	cmp r0, #0
	ble _0806FAA2
	ldr r0, [r4, #0x54]
	movs r2, #0xa0
	lsls r2, r2, #4
	b _0806FAA6
_0806FAA2:
	ldr r0, [r4, #0x54]
	ldr r2, _0806FAC4 @ =0xFFFFF600
_0806FAA6:
	adds r0, r0, r2
	bl FUN_08009f6c
_0806FAAC:
	ldr r1, [r4, #0x58]
	subs r1, r1, r0
	cmp r1, #0
	bge _0806FAB6
	rsbs r1, r1, #0
_0806FAB6:
	movs r0, #0x80
	lsls r0, r0, #4
	cmp r1, r0
	ble _0806FAC8
	ldr r0, [r4, #0x5c]
	rsbs r0, r0, #0
	b _0806FB00
	.align 2, 0
_0806FAC4: .4byte 0xFFFFF600
_0806FAC8:
	ldrb r0, [r4, #0x11]
	cmp r0, #1
	bne _0806FB02
	ldr r2, [r4, #0x5c]
	cmp r2, #0
	ble _0806FAEC
	adds r0, r4, #0
	adds r0, #0xb4
	ldr r0, [r0]
	ldr r1, [r4, #0x54]
	subs r0, r0, r1
	ldr r1, _0806FAE8 @ =0xFFFFD000
	cmp r0, r1
	bge _0806FB02
	b _0806FAFE
	.align 2, 0
_0806FAE8: .4byte 0xFFFFD000
_0806FAEC:
	adds r0, r4, #0
	adds r0, #0xb4
	ldr r0, [r0]
	ldr r1, [r4, #0x54]
	subs r0, r0, r1
	movs r1, #0xc0
	lsls r1, r1, #6
	cmp r0, r1
	ble _0806FB02
_0806FAFE:
	rsbs r0, r2, #0
_0806FB00:
	str r0, [r4, #0x5c]
_0806FB02:
	pop {r4}
	pop {r0}
	bx r0
