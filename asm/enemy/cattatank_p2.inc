	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start cattatank_08099094
cattatank_08099094: @ 0x08099094
	push {lr}
	adds r2, r0, #0
	ldrb r0, [r2, #0xe]
	cmp r0, #0
	beq _080990A4
	cmp r0, #1
	beq _080990B6
	b _080990CE
_080990A4:
	ldrb r1, [r2, #0xa]
	movs r0, #0xfe
	ands r0, r1
	strb r0, [r2, #0xa]
	movs r0, #0x32
	strb r0, [r2, #0x12]
	ldrb r0, [r2, #0xe]
	adds r0, #1
	strb r0, [r2, #0xe]
_080990B6:
	ldrb r0, [r2, #0x12]
	cmp r0, #0
	beq _080990C6
	subs r0, #1
	strb r0, [r2, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080990CE
_080990C6:
	movs r1, #0
	movs r0, #1
	strb r0, [r2, #0xd]
	strb r1, [r2, #0xe]
_080990CE:
	pop {r0}
	bx r0
	.align 2, 0
