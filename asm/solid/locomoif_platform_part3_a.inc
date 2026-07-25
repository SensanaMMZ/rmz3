	.include "asm/macros.inc"
	.syntax unified
	.text

	thumb_func_start FUN_080ce710
FUN_080ce710: @ 0x080CE710
	push {r4, r5, lr}
	adds r4, r0, #0
	ldr r5, [r4, #0x28]
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _080CE722
	cmp r0, #1
	beq _080CE73A
	b _080CE758
_080CE722:
	adds r1, r4, #0
	adds r1, #0x25
	movs r0, #0x17
	strb r0, [r1]
	movs r1, #0xaa
	lsls r1, r1, #7
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080CE73A:
	adds r0, r4, #0
	bl FUN_080ce538
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r5, #0
	adds r0, #0xbd
	ldrb r0, [r0]
	cmp r0, #0
	beq _080CE758
	movs r1, #0
	movs r0, #1
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_080CE758:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0

