	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start blazinMode2
blazinMode2: @ 0x0803EF68
	push {r4, r5, lr}
	adds r5, r0, #0
	ldrb r0, [r5, #0xe]
	cmp r0, #0
	beq _0803EF78
	cmp r0, #1
	beq _0803EFA2
	b _0803EFBA
_0803EF78:
	adds r4, r5, #0
	adds r4, #0xc4
	str r0, [r4]
	adds r0, r5, #0
	movs r1, #2
	bl createBlazinTail
	str r0, [r4]
	adds r0, r5, #0
	adds r0, #0xc8
	ldrh r0, [r0]
	movs r2, #0xa2
	lsls r2, r2, #8
	adds r1, r2, #0
	orrs r1, r0
	adds r0, r5, #0
	bl SetMotion
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_0803EFA2:
	ldr r0, _0803EFC0 @ =gStageRun
	ldrb r0, [r0, #0x12]
	movs r1, #1
	ands r1, r0
	cmp r1, #0
	bne _0803EFB4
	movs r0, #3
	strb r0, [r5, #0xd]
	strb r1, [r5, #0xe]
_0803EFB4:
	adds r0, r5, #0
	bl UpdateMotionGraphic
_0803EFBA:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_0803EFC0: .4byte gStageRun
