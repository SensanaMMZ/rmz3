	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_08061068
FUN_08061068: @ 0x08061068
	push {r4, r5, lr}
	sub sp, #8
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _0806107A
	cmp r0, #1
	beq _0806107E
	b _0806109C
_0806107A:
	movs r0, #1
	strb r0, [r4, #0xe]
_0806107E:
	ldr r0, _080610A4 @ =gStageRun
	ldrb r0, [r0, #0x12]
	movs r5, #1
	ands r5, r0
	cmp r5, #0
	bne _0806109C
	mov r0, sp
	movs r1, #0
	adds r2, r4, #0
	bl FUN_080c4e58
	str r0, [r4, #0x2c]
	movs r0, #3
	strb r0, [r4, #0xd]
	strb r5, [r4, #0xe]
_0806109C:
	add sp, #8
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080610A4: .4byte gStageRun
