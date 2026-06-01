	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_08035330
FUN_08035330: @ 0x08035330
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _08035340
	cmp r0, #1
	beq _08035352
	b _08035370
_08035340:
	ldr r1, _08035378 @ =0x0000BE21
	adds r0, r4, #0
	bl SetMotion
	movs r0, #0x3c
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08035352:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldrb r0, [r4, #0x12]
	cmp r0, #0
	beq _08035368
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _08035370
_08035368:
	movs r1, #0
	movs r0, #1
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_08035370:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_08035378: .4byte 0x0000BE21

	thumb_func_start FUN_0803537c
FUN_0803537c: @ 0x0803537C
	push {lr}
	adds r2, r0, #0
	ldr r0, [r2, #0x28]
	movs r1, #4
	ldrsh r0, [r0, r1]
	cmp r0, #1
	bne _0803539E
	ldr r0, _080353A4 @ =gJoypad
	ldrh r1, [r0, #4]
	movs r0, #2
	ands r0, r1
	cmp r0, #0
	beq _0803539E
	movs r1, #0
	movs r0, #3
	strb r0, [r2, #0xd]
	strb r1, [r2, #0xe]
_0803539E:
	movs r0, #1
	pop {r1}
	bx r1
	.align 2, 0
_080353A4: .4byte gJoypad

	thumb_func_start FUN_080353a8
FUN_080353a8: @ 0x080353A8
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _080353B8
	cmp r0, #1
	beq _080353D0
	b _080353D6
_080353B8:
	ldr r1, _080353DC @ =0x0000BE21
	adds r0, r4, #0
	bl SetMotion
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _080353E0 @ =0x0835EAF8
	bl SetDDP
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080353D0:
	adds r0, r4, #0
	bl UpdateMotionGraphic
_080353D6:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080353DC: .4byte 0x0000BE21
_080353E0: .4byte 0x0835EAF8
