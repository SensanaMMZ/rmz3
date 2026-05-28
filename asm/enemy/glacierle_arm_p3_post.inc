	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_08082af8
FUN_08082af8: @ 0x08082AF8
	push {r4, r5, r6, lr}
	adds r6, r0, #0
	ldrb r0, [r6, #0xe]
	cmp r0, #0
	beq _08082B08
	cmp r0, #1
	beq _08082B24
	b _08082B2A
_08082B08:
	adds r4, r6, #0
	adds r4, #0x24
	ldrb r5, [r4]
	adds r0, r6, #0
	bl InitRotatableMotion
	ldr r1, _08082B50 @ =0x00005902
	adds r0, r6, #0
	bl SetMotion
	strb r5, [r4]
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_08082B24:
	adds r0, r6, #0
	bl UpdateMotionGraphic
_08082B2A:
	adds r0, r6, #0
	adds r0, #0xbc
	ldr r0, [r0]
	ldrb r0, [r0, #0xc]
	cmp r0, #1
	bls _08082B48
	ldr r1, _08082B54 @ =gEnemyFnTable
	ldrb r0, [r6, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r6, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r6, #0x14]
_08082B48:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_08082B50: .4byte 0x00005902
_08082B54: .4byte gEnemyFnTable

