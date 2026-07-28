	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080a9dcc
FUN_080a9dcc: @ 0x080A9DCC
	push {r4, r5, r6, lr}
	adds r4, r0, #0
	ldr r5, [r4, #0x28]
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x58]
	str r0, [r4, #0x54]
	str r1, [r4, #0x58]
	ldrb r0, [r5, #0xa]
	lsrs r2, r0, #4
	movs r0, #1
	ands r2, r0
	cmp r2, #0
	beq _080A9DEE
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	orrs r0, r1
	b _080A9DF4
_080A9DEE:
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
_080A9DF4:
	strb r0, [r4, #0xa]
	movs r6, #1
	adds r1, r6, #0
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
	adds r0, r5, #0
	adds r0, #0xc6
	ldrb r0, [r0]
	cmp r0, #0
	beq _080A9E40
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _080A9E2C
	ldr r1, _080A9E3C @ =0x00005F01
	adds r0, r4, #0
	bl SetMotion
_080A9E2C:
	ldrb r0, [r4, #0xa]
	movs r1, #1
	orrs r0, r1
	strb r0, [r4, #0xa]
	movs r0, #0
	strb r0, [r4, #0xe]
	b _080A9E4A
	.align 2, 0
_080A9E3C: .4byte 0x00005F01
_080A9E40:
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
	strb r0, [r4, #0xa]
	strb r6, [r4, #0xe]
_080A9E4A:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldrb r0, [r5, #0xc]
	cmp r0, #1
	bls _080A9E68
	ldr r1, _080A9E70 @ =gProjectileFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r4, #0x14]
_080A9E68:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_080A9E70: .4byte gProjectileFnTable

