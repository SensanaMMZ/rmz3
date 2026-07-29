	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_080c3cbc
FUN_080c3cbc: @ 0x080C3CBC
	push {r4, r5, r6, r7, lr}
	adds r4, r0, #0
	adds r5, r4, #0
	adds r5, #0x34
	ldr r6, [r4, #0x28]
	adds r7, r6, #0
	adds r7, #0x34
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _080C3CD6
	cmp r0, #1
	beq _080C3CDE
	b _080C3D78
_080C3CD6:
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080C3CDE:
	ldrb r0, [r4, #0x12]
	adds r0, #1
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0x13]
	adds r0, #1
	strb r0, [r4, #0x13]
	ldrb r0, [r4, #0x13]
	movs r1, #3
	bl __umodsi3
	strb r0, [r4, #0x13]
	movs r2, #0x9c
	lsls r2, r2, #1
	ldr r1, _080C3D80 @ =gSineTable
	ldrb r0, [r4, #0x12]
	lsls r0, r0, #1
	adds r0, r0, r1
	movs r1, #0
	ldrsh r0, [r0, r1]
	cmp r0, #0
	bge _080C3D0A
	adds r0, #0xf
_080C3D0A:
	asrs r0, r0, #4
	adds r2, r0, r2
	ldrb r1, [r4, #0x13]
	lsls r1, r1, #4
	movs r0, #0x88
	lsls r0, r0, #1
	subs r0, r0, r1
	adds r1, r2, #0
	muls r1, r0, r1
	cmp r1, #0
	bge _080C3D22
	adds r1, #0xff
_080C3D22:
	asrs r1, r1, #8
	adds r0, r4, #0
	adds r0, #0x50
	strh r1, [r0]
	ldrb r1, [r4, #0x13]
	lsls r1, r1, #4
	movs r0, #0x80
	lsls r0, r0, #1
	subs r0, r0, r1
	muls r0, r2, r0
	cmp r0, #0
	bge _080C3D3C
	adds r0, #0xff
_080C3D3C:
	asrs r0, r0, #8
	adds r1, r4, #0
	adds r1, #0x52
	strh r0, [r1]
	ldr r0, [r7, #8]
	str r0, [r5, #8]
	ldrb r0, [r7, #0x1a]
	strb r0, [r5, #0x1a]
	ldrb r0, [r6, #0xa]
	lsrs r0, r0, #4
	movs r2, #1
	ands r0, r2
	strb r0, [r5, #0x18]
	ldrb r1, [r6, #0xa]
	lsrs r1, r1, #4
	ands r1, r2
	lsls r1, r1, #4
	ldrb r2, [r5, #0x16]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r1
	strb r0, [r5, #0x16]
	ldrb r0, [r6, #0xc]
	cmp r0, #1
	bls _080C3D78
	movs r0, #1
	strb r0, [r4, #0xd]
	movs r0, #0
	strb r0, [r4, #0xe]
_080C3D78:
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080C3D80: .4byte gSineTable
