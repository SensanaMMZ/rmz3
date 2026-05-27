	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_0803b73c
FUN_0803b73c: @ 0x0803B73C
	push {lr}
	ldr r0, [r0, #0x14]
	movs r1, #4
	ands r0, r1
	cmp r0, #0
	beq _0803B756
	ldr r2, _0803B75C @ =gMission
	ldrh r1, [r2, #0x1c]
	ldr r0, _0803B760 @ =0x0000FFFE
	cmp r1, r0
	bhi _0803B756
	adds r0, r1, #1
	strh r0, [r2, #0x1c]
_0803B756:
	pop {r0}
	bx r0
	.align 2, 0
_0803B75C: .4byte gMission
_0803B760: .4byte 0x0000FFFE

