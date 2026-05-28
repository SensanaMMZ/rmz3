	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080a2dec
FUN_080a2dec: @ 0x080A2DEC
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #1
	beq _080A2E20
	cmp r0, #1
	bgt _080A2E00
	cmp r0, #0
	beq _080A2E0A
	b _080A2E92
_080A2E00:
	cmp r0, #2
	beq _080A2E4C
	cmp r0, #3
	beq _080A2E62
	b _080A2E92
_080A2E0A:
	ldr r1, _080A2E48 @ =0x00004202
	adds r0, r4, #0
	bl SetMotion
	movs r0, #0x14
	strb r0, [r4, #0x12]
	movs r0, #0x40
	str r0, [r4, #0x60]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080A2E20:
	ldr r0, [r4, #0x58]
	ldr r1, [r4, #0x60]
	subs r0, r0, r1
	str r0, [r4, #0x58]
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldrb r0, [r4, #0x12]
	cmp r0, #0
	beq _080A2E3E
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080A2E92
_080A2E3E:
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
	b _080A2E92
	.align 2, 0
_080A2E48: .4byte 0x00004202
_080A2E4C:
	ldr r1, _080A2E98 @ =0x00004203
	adds r0, r4, #0
	bl SetMotion
	movs r0, #0x14
	strb r0, [r4, #0x12]
	movs r0, #0x20
	str r0, [r4, #0x60]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080A2E62:
	ldr r0, [r4, #0x58]
	ldr r1, [r4, #0x60]
	subs r0, r0, r1
	str r0, [r4, #0x58]
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldrb r0, [r4, #0x12]
	cmp r0, #0
	beq _080A2E80
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080A2E92
_080A2E80:
	ldr r1, _080A2E9C @ =gProjectileFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r4, #0x14]
_080A2E92:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080A2E98: .4byte 0x00004203
_080A2E9C: .4byte gProjectileFnTable

