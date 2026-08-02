	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080623bc
FUN_080623bc: @ 0x080623BC
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #5
	bhi _080624A6
	lsls r0, r0, #2
	ldr r1, _080623D0 @ =_080623D4
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_080623D0: .4byte _080623D4
_080623D4: @ jump table
	.4byte _080623EC @ case 0
	.4byte _08062404 @ case 1
	.4byte _08062420 @ case 2
	.4byte _08062446 @ case 3
	.4byte _08062490 @ case 4
	.4byte _08062496 @ case 5
_080623EC:
	ldr r0, _08062418 @ =gStageRun+232
	ldr r0, [r0, #0x3c]
	ldr r1, _0806241C @ =0xFFFF7000
	adds r0, r0, r1
	str r0, [r4, #0x58]
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
	strb r0, [r4, #0xa]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08062404:
	ldr r0, [r4, #0x18]
	ldrb r1, [r0, #9]
	movs r0, #1
	ands r0, r1
	cmp r0, #0
	beq _080624A6
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
	b _080624A6
	.align 2, 0
_08062418: .4byte gStageRun+232
_0806241C: .4byte 0xFFFF7000
_08062420:
	ldrb r1, [r4, #0xa]
	movs r0, #1
	movs r2, #0
	orrs r0, r1
	strb r0, [r4, #0xa]
	ldr r0, _08062488 @ =gStageRun+232
	ldr r0, [r0, #0x3c]
	ldr r1, _0806248C @ =0xFFFF7000
	adds r0, r0, r1
	str r0, [r4, #0x58]
	str r2, [r4, #0x60]
	movs r1, #0xd6
	lsls r1, r1, #8
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08062446:
	ldr r0, [r4, #0x60]
	adds r0, #0x40
	str r0, [r4, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _08062456
	str r1, [r4, #0x60]
_08062456:
	ldr r1, [r4, #0x58]
	ldr r0, [r4, #0x60]
	adds r1, r1, r0
	str r1, [r4, #0x58]
	ldr r0, [r4, #0x54]
	bl PushoutToUp1
	adds r5, r0, #0
	cmp r5, #0
	bge _08062480
	adds r1, r4, #0
	adds r1, #0x54
	movs r0, #3
	bl AppendQuake
	ldr r0, [r4, #0x58]
	adds r0, r0, r5
	str r0, [r4, #0x58]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08062480:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	b _080624A6
	.align 2, 0
_08062488: .4byte gStageRun+232
_0806248C: .4byte 0xFFFF7000
_08062490:
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08062496:
	ldr r0, _080624AC @ =gStageRun
	ldrb r0, [r0, #0x12]
	movs r1, #1
	ands r1, r0
	cmp r1, #0
	bne _080624A6
	strb r1, [r4, #0xd]
	strb r1, [r4, #0xe]
_080624A6:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080624AC: .4byte gStageRun
