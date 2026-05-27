	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start incrementShieldHitCount
incrementShieldHitCount: @ 0x0803CE10
	push {lr}
	adds r2, r0, #0
	ldr r0, [r2, #0x14]
	movs r1, #4
	ands r0, r1
	cmp r0, #0
	beq _0803CE32
	ldr r2, [r2, #0x2c]
	ldr r3, _0803CE38 @ =gMission
	ldrh r1, [r3, #0x22]
	ldr r0, _0803CE3C @ =0x0000FFFE
	cmp r1, r0
	bhi _0803CE2E
	adds r0, r1, #1
	strh r0, [r3, #0x22]
_0803CE2E:
	movs r0, #1
	strb r0, [r2, #0x11]
_0803CE32:
	pop {r0}
	bx r0
	.align 2, 0
_0803CE38: .4byte gMission
_0803CE3C: .4byte 0x0000FFFE

