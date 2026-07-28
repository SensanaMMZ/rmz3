	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_08078550
FUN_08078550: @ 0x08078550
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _08078560
	cmp r0, #1
	beq _08078576
	b _080785AE
_08078560:
	ldrb r1, [r4, #0x10]
	movs r2, #0xbc
	lsls r2, r2, #6
	adds r0, r2, #0
	orrs r1, r0
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08078576:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x74
	ldr r2, _080785B4 @ =0x0836754A
	adds r1, r4, #0
	adds r1, #0x71
	ldrb r1, [r1]
	lsls r1, r1, #0x18
	asrs r1, r1, #0x18
	adds r1, r1, r2
	ldrb r2, [r1]
	lsls r1, r2, #1
	adds r1, r1, r2
	lsls r1, r1, #3
	ldr r2, _080785B8 @ =0x08367460
	adds r1, r1, r2
	bl SetDDP
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r1, [r0]
	cmp r1, #3
	bne _080785AE
	movs r0, #0
	strb r1, [r4, #0xd]
	strb r0, [r4, #0xe]
_080785AE:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080785B4: .4byte 0x0836754A
_080785B8: .4byte 0x08367460

