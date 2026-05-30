	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start MegamilpaNode_Update
MegamilpaNode_Update: @ 0x08065820
	push {r4, lr}
	adds r4, r0, #0
	adds r0, #0xb4
	ldr r0, [r0]
	ldrb r0, [r0, #0xc]
	cmp r0, #1
	bls _0806584C
	ldr r1, _08065848 @ =gEnemyFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r4, #0x14]
	adds r0, r4, #0
	bl MegamilpaNode_Die
	b _0806586C
	.align 2, 0
_08065848: .4byte gEnemyFnTable
_0806584C:
	ldr r1, _08065874 @ =0x08365CA8
	ldrb r0, [r4, #0xd]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r1, [r0]
	adds r0, r4, #0
	bl _call_via_r1
	ldr r1, _08065878 @ =0x08365CB4
	ldrb r0, [r4, #0xd]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r1, [r0]
	adds r0, r4, #0
	bl _call_via_r1
_0806586C:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_08065874: .4byte 0x08365CA8
_08065878: .4byte 0x08365CB4

