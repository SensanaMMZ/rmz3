	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start HarpuiaMinigameEnemy_Die
HarpuiaMinigameEnemy_Die: @ 0x0809B310
	adds r3, r0, #0
	ldrb r1, [r3, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r2, #0
	strb r0, [r3, #0xa]
	adds r0, r3, #0
	adds r0, #0x8c
	str r2, [r0]
	adds r0, #4
	str r2, [r0]
	adds r0, #4
	strb r2, [r0]
	ldrb r1, [r3, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r3, #0xa]
	ldr r1, _0809B34C @ =gEnemyFnTable
	ldrb r0, [r3, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #4
	str r1, [r3, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0x10]
	str r0, [r3, #0x14]
	strb r2, [r3, #0xd]
	strb r2, [r3, #0xe]
	strb r2, [r3, #0xf]
	bx lr
	.align 2, 0
_0809B34C: .4byte gEnemyFnTable
