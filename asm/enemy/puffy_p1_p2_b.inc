	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start Puffy_Update
Puffy_Update: @ 0x0807C6F8
	push {r4, lr}
	adds r4, r0, #0
	adds r0, #0x8c
	ldr r0, [r0]
	movs r1, #0x80
	lsls r1, r1, #2
	ands r0, r1
	cmp r0, #0
	beq _0807C728
	ldr r1, _0807C724 @ =gEnemyFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r4, #0x14]
	adds r0, r4, #0
	bl Puffy_Die
	b _0807C768
	.align 2, 0
_0807C724: .4byte gEnemyFnTable
_0807C728:
	ldr r1, _0807C754 @ =0x08367AEC
	ldrb r0, [r4, #0xd]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r1, [r0]
	adds r0, r4, #0
	bl _call_via_r1
	adds r0, r4, #0
	bl FUN_0807cb50
	adds r0, r4, #0
	bl IsFrozen
	cmp r0, #0
	beq _0807C758
	ldrb r1, [r4, #0xd]
	adds r0, r4, #0
	adds r0, #0xba
	strb r1, [r0]
	b _0807C768
	.align 2, 0
_0807C754: .4byte 0x08367AEC
_0807C758:
	ldr r0, _0807C770 @ =0x08367AFC
	ldrb r1, [r4, #0xd]
	lsls r1, r1, #2
	adds r1, r1, r0
	ldr r1, [r1]
	adds r0, r4, #0
	bl _call_via_r1
_0807C768:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_0807C770: .4byte 0x08367AFC

