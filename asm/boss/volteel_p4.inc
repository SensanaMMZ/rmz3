	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start volteelMode2
volteelMode2: @ 0x0804398C
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _0804399C
	cmp r0, #1
	beq _080439AC
	b _080439C4
_0804399C:
	movs r1, #0xa5
	lsls r1, r1, #8
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080439AC:
	ldr r0, _080439CC @ =gStageRun
	ldrb r0, [r0, #0x12]
	movs r1, #1
	ands r1, r0
	cmp r1, #0
	bne _080439BE
	movs r0, #3
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_080439BE:
	adds r0, r4, #0
	bl UpdateMotionGraphic
_080439C4:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080439CC: .4byte gStageRun
