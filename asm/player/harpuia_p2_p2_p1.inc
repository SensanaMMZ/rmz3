	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_0803540c
FUN_0803540c: @ 0x0803540C
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #1
	beq _0803543C
	cmp r0, #1
	bgt _08035420
	cmp r0, #0
	beq _0803542A
	b _0803549E
_08035420:
	cmp r0, #2
	beq _08035464
	cmp r0, #3
	beq _08035480
	b _0803549E
_0803542A:
	ldr r1, _08035460 @ =0x0000BE21
	adds r0, r4, #0
	bl SetMotion
	movs r0, #0xa
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0803543C:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	beq _08035474
	ldrb r0, [r4, #0x12]
	cmp r0, #0
	beq _08035478
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _0803549E
	b _08035478
	.align 2, 0
_08035460: .4byte 0x0000BE21
_08035464:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _0803549E
_08035474:
	movs r0, #0xa
	strb r0, [r4, #0x12]
_08035478:
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
	b _0803549E
_08035480:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldrb r0, [r4, #0x12]
	cmp r0, #0
	beq _08035496
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _0803549E
_08035496:
	movs r1, #0
	movs r0, #1
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_0803549E:
	pop {r4}
	pop {r0}
	bx r0
