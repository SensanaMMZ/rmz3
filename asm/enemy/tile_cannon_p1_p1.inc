	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_080780c4
FUN_080780c4: @ 0x080780C4
	push {r4, r5, lr}
	adds r4, r0, #0
	ldr r1, [r4, #0x2c]
	ldrb r0, [r1, #0xc]
	cmp r0, #1
	bls _080780FE
	adds r0, r1, #0
	adds r0, #0xa4
	movs r1, #0
	ldrsh r5, [r0, r1]
	cmp r5, #0
	bne _080780FE
	ldrb r1, [r4, #0x10]
	movs r2, #0xbc
	lsls r2, r2, #6
	adds r0, r2, #0
	orrs r1, r0
	adds r0, r4, #0
	bl SetMotion
	adds r0, r4, #0
	bl UpdateMotionGraphic
	movs r0, #0x78
	strb r0, [r4, #0x12]
	movs r0, #1
	strb r0, [r4, #0xd]
	strb r5, [r4, #0xe]
	b _08078100
_080780FE:
	movs r0, #0
_08078100:
	pop {r4, r5}
	pop {r1}
	bx r1
	.align 2, 0
