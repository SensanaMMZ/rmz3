	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_0809f7d4
FUN_0809f7d4: @ 0x0809F7D4
	push {r4, lr}
	adds r4, r0, #0
	ldr r0, [r4, #0x28]
	ldrb r0, [r0, #0xc]
	cmp r0, #1
	bls _0809F7F8
	adds r0, r4, #0
	adds r0, #0x8c
	movs r1, #0
	str r1, [r0]
	adds r0, #4
	str r1, [r0]
	adds r0, #4
	strb r1, [r0]
	ldrb r1, [r4, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r4, #0xa]
_0809F7F8:
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _0809F804
	cmp r0, #1
	beq _0809F854
	b _0809F8A0
_0809F804:
	movs r1, #0xa6
	lsls r1, r1, #8
	adds r0, r4, #0
	bl SetMotion
	movs r2, #1
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	orrs r0, r1
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	adds r0, #0x4c
	strb r2, [r0]
	adds r3, r4, #0
	adds r3, #0x4a
	movs r2, #0x10
	ldrb r1, [r3]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	orrs r0, r2
	strb r0, [r3]
	movs r0, #0xff
	strb r0, [r4, #0x12]
	ldr r0, [r4, #0x5c]
	lsls r0, r0, #0xa
	asrs r0, r0, #8
	str r0, [r4, #0x64]
	ldr r0, [r4, #0x60]
	lsls r0, r0, #0xa
	asrs r0, r0, #8
	str r0, [r4, #0x68]
	adds r0, r4, #0
	adds r0, #0xb4
	ldrb r1, [r0]
	subs r0, #0x90
	strb r1, [r0]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0809F854:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x64]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	ldr r0, [r4, #0x58]
	ldr r1, [r4, #0x68]
	adds r0, r0, r1
	str r0, [r4, #0x58]
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	lsrs r1, r0, #0x18
	cmp r1, #0
	bne _0809F8A0
	adds r0, r4, #0
	adds r0, #0x8c
	str r1, [r0]
	adds r0, #4
	str r1, [r0]
	adds r0, #4
	strb r1, [r0]
	ldrb r1, [r4, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r4, #0xa]
	ldr r1, _0809F8A8 @ =gProjectileFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r4, #0x14]
_0809F8A0:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_0809F8A8: .4byte gProjectileFnTable

