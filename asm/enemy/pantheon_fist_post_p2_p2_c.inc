	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_08095778
FUN_08095778: @ 0x08095778
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _08095788
	cmp r0, #1
	beq _080957A4
	b _080957C6
_08095788:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _080957CC @ =0x08369FEC
	bl SetDDP
	ldr r1, _080957D0 @ =0x0000D403
	adds r0, r4, #0
	bl SetMotion
	movs r0, #0x10
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080957A4:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	lsrs r1, r0, #0x18
	cmp r1, #0
	bne _080957BE
	movs r0, #5
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_080957BE:
	adds r0, r4, #0
	movs r1, #1
	bl FUN_08094fe0
_080957C6:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080957CC: .4byte 0x08369FEC
_080957D0: .4byte 0x0000D403
