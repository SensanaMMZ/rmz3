	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080be330
FUN_080be330: @ 0x080BE330
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _080BE340
	cmp r0, #1
	beq _080BE3E0
	b _080BE454
_080BE340:
	ldrb r0, [r4, #0x10]
	cmp r0, #0
	bne _080BE350
	ldr r1, _080BE34C @ =0x0000A907
	b _080BE37A
	.align 2, 0
_080BE34C: .4byte 0x0000A907
_080BE350:
	cmp r0, #1
	bne _080BE35C
	ldr r1, _080BE358 @ =0x0000A907
	b _080BE37A
	.align 2, 0
_080BE358: .4byte 0x0000A907
_080BE35C:
	cmp r0, #2
	bne _080BE368
	ldr r1, _080BE364 @ =0x0000A907
	b _080BE37A
	.align 2, 0
_080BE364: .4byte 0x0000A907
_080BE368:
	cmp r0, #3
	bne _080BE374
	ldr r1, _080BE370 @ =0x0000A907
	b _080BE37A
	.align 2, 0
_080BE370: .4byte 0x0000A907
_080BE374:
	cmp r0, #4
	bne _080BE388
	ldr r1, _080BE384 @ =0x0000A90B
_080BE37A:
	adds r0, r4, #0
	bl SetMotion
	b _080BE394
	.align 2, 0
_080BE384: .4byte 0x0000A90B
_080BE388:
	cmp r0, #5
	bne _080BE394
	ldr r1, _080BE3AC @ =0x0000A90B
	adds r0, r4, #0
	bl SetMotion
_080BE394:
	adds r0, r4, #0
	adds r0, #0x7c
	ldrb r0, [r0]
	movs r2, #1
	ands r2, r0
	cmp r2, #0
	beq _080BE3B0
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	orrs r0, r1
	b _080BE3B6
	.align 2, 0
_080BE3AC: .4byte 0x0000A90B
_080BE3B0:
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
_080BE3B6:
	strb r0, [r4, #0xa]
	adds r1, r2, #0
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
	movs r0, #3
	strb r0, [r4, #0x13]
	movs r0, #0xa
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080BE3E0:
	ldrb r0, [r4, #0x12]
	cmp r0, #0
	beq _080BE3F0
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080BE44E
_080BE3F0:
	movs r0, #0xa
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0x13]
	cmp r0, #0
	beq _080BE404
	subs r0, #1
	strb r0, [r4, #0x13]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080BE41C
_080BE404:
	ldr r1, _080BE418 @ =gVFXFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r4, #0x14]
	b _080BE44E
	.align 2, 0
_080BE418: .4byte gVFXFnTable
_080BE41C:
	ldrb r0, [r4, #0x10]
	cmp r0, #3
	bhi _080BE43C
	ldr r0, _080BE438 @ =0x0836EF74
	ldrb r1, [r4, #0x13]
	subs r1, #1
	lsls r1, r1, #1
	adds r1, r1, r0
	ldrh r1, [r1]
	adds r0, r4, #0
	bl SetMotion
	b _080BE44E
	.align 2, 0
_080BE438: .4byte 0x0836EF74
_080BE43C:
	ldr r0, _080BE45C @ =0x0836EF7A
	ldrb r1, [r4, #0x13]
	subs r1, #1
	lsls r1, r1, #1
	adds r1, r1, r0
	ldrh r1, [r1]
	adds r0, r4, #0
	bl SetMotion
_080BE44E:
	adds r0, r4, #0
	bl UpdateMotionGraphic
_080BE454:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080BE45C: .4byte 0x0836EF7A


