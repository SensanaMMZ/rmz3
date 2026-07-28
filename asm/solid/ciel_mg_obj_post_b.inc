	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080ddef4
FUN_080ddef4: @ 0x080DDEF4
	push {r4, r5, lr}
	adds r4, r0, #0
	ldr r0, [r4, #0x28]
	ldr r1, _080DDF28 @ =0x00000DCC
	adds r2, r0, r1
	adds r1, #0x22
	adds r0, r0, r1
	ldrb r1, [r0]
	ldr r0, _080DDF2C @ =0x083716D0
	lsls r1, r1, #2
	adds r0, r1, r0
	ldr r0, [r0]
	str r0, [r4, #0x54]
	ldr r0, _080DDF30 @ =0x083716F8
	adds r1, r1, r0
	ldr r0, [r1]
	str r0, [r4, #0x58]
	ldrb r0, [r4, #0xd]
	cmp r0, #0
	bne _080DDF38
	ldrb r5, [r2, #5]
	cmp r5, #1
	bne _080DDF48
	ldr r1, _080DDF34 @ =0x0000E80B
	b _080DDF40
	.align 2, 0
_080DDF28: .4byte 0x00000DCC
_080DDF2C: .4byte 0x083716D0
_080DDF30: .4byte 0x083716F8
_080DDF34: .4byte 0x0000E80B
_080DDF38:
	ldrb r5, [r2, #5]
	cmp r5, #0
	bne _080DDF48
	ldr r1, _080DDF54 @ =0x0000E80C
_080DDF40:
	adds r0, r4, #0
	bl SetMotion
	strb r5, [r4, #0xd]
_080DDF48:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080DDF54: .4byte 0x0000E80C


