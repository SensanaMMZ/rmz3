	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_080b9070
FUN_080b9070: @ 0x080B9070
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _080B9080
	cmp r0, #1
	beq _080B9090
	b _080B90B2
_080B9080:
	movs r1, #0xd0
	lsls r1, r1, #4
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080B9090:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _080B90B2
	ldr r1, _080B90B8 @ =gVFXFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r4, #0x14]
_080B90B2:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080B90B8: .4byte gVFXFnTable
