	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_0806e604
FUN_0806e604: @ 0x0806E604
	push {r4, lr}
	adds r3, r0, #0
	adds r4, r3, #0
	adds r4, #0x8c
	ldr r0, [r4]
	movs r1, #0x80
	lsls r1, r1, #2
	ands r0, r1
	cmp r0, #0
	beq _0806E66A
	ldr r2, [r3, #0x28]
	cmp r2, #0
	beq _0806E62C
	adds r2, #0xb4
	movs r1, #1
	ldrb r0, [r3, #0x11]
	lsls r1, r0
	ldr r0, [r2]
	bics r0, r1
	str r0, [r2]
_0806E62C:
	ldr r1, _0806E658 @ =gEnemyFnTable
	ldrb r0, [r3, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r2, #2
	str r2, [r3, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r3, #0x14]
	ldr r1, [r4]
	movs r0, #0x80
	lsls r0, r0, #9
	ands r0, r1
	cmp r0, #0
	bne _0806E65C
	movs r0, #0x80
	lsls r0, r0, #0xa
	ands r0, r1
	cmp r0, #0
	beq _0806E65E
	strb r2, [r3, #0xd]
	b _0806E660
	.align 2, 0
_0806E658: .4byte gEnemyFnTable
_0806E65C:
	movs r0, #1
_0806E65E:
	strb r0, [r3, #0xd]
_0806E660:
	adds r0, r3, #0
	bl Lemmingles_Die
	movs r0, #1
	b _0806E66C
_0806E66A:
	movs r0, #0
_0806E66C:
	pop {r4}
	pop {r1}
	bx r1
	.align 2, 0

	thumb_func_start FUN_0806e674
FUN_0806e674: @ 0x0806E674
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xd]
	cmp r0, #6
	beq _0806E6FA
	adds r0, r4, #0
	adds r0, #0xb4
	ldr r5, [r0]
	cmp r5, #0
	bne _0806E6FA
	ldrb r0, [r4, #0xf]
	cmp r0, #0
	beq _0806E694
	cmp r0, #1
	beq _0806E6D8
	b _0806E6FA
_0806E694:
	adds r0, r4, #0
	bl IsFrozen
	cmp r0, #0
	beq _0806E6FA
	ldr r1, _0806E6D0 @ =0x08366828
	ldrb r0, [r4, #0xd]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r1, [r0]
	adds r0, r4, #0
	bl _call_via_r1
	ldr r1, _0806E6D4 @ =0x08366844
	ldrb r0, [r4, #0xd]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r1, [r0]
	adds r0, r4, #0
	bl _call_via_r1
	ldrb r0, [r4, #0xf]
	adds r0, #1
	strb r0, [r4, #0xf]
	adds r0, r4, #0
	bl UpdateMotionGraphic
_0806E6CA:
	movs r0, #1
	b _0806E6FC
	.align 2, 0
_0806E6D0: .4byte 0x08366828
_0806E6D4: .4byte 0x08366844
_0806E6D8:
	adds r0, r4, #0
	bl IsFrozen
	cmp r0, #0
	beq _0806E6F8
	adds r0, r4, #0
	adds r0, #0x8c
	ldr r0, [r0]
	ldr r1, _0806E6F4 @ =0x00020001
	ands r0, r1
	cmp r0, r1
	bne _0806E6CA
	strb r5, [r4, #0xf]
	b _0806E6FA
	.align 2, 0
_0806E6F4: .4byte 0x00020001
_0806E6F8:
	strb r0, [r4, #0xf]
_0806E6FA:
	movs r0, #0
_0806E6FC:
	pop {r4, r5}
	pop {r1}
	bx r1
	.align 2, 0
