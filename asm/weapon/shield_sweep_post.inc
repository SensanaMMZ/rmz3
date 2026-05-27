	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start incrementShieldHitCount_0803c40c
incrementShieldHitCount_0803c40c: @ 0x0803C40C
	push {lr}
	ldr r0, [r0, #0x14]
	movs r1, #4
	ands r0, r1
	cmp r0, #0
	beq _0803C426
	ldr r2, _0803C42C @ =gMission
	ldrh r1, [r2, #0x22]
	ldr r0, _0803C430 @ =0x0000FFFE
	cmp r1, r0
	bhi _0803C426
	adds r0, r1, #1
	strh r0, [r2, #0x22]
_0803C426:
	pop {r0}
	bx r0
	.align 2, 0
_0803C42C: .4byte gMission
_0803C430: .4byte 0x0000FFFE

