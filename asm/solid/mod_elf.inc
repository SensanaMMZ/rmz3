	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start ModElf_Update
ModElf_Update: @ 0x080DFA24
	push {r4, lr}
	adds r4, r0, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0xb4
	ldr r0, [r0]
	str r0, [r4, #0x64]
	adds r2, r4, #0
	adds r2, #0xb8
	ldr r1, _080DFA78 @ =gSineTable
	ldrb r0, [r4, #0x12]
	lsls r0, r0, #1
	adds r0, r0, r1
	movs r1, #0
	ldrsh r0, [r0, r1]
	lsls r1, r0, #1
	adds r1, r1, r0
	lsls r1, r1, #2
	ldr r0, [r2]
	adds r0, r0, r1
	str r0, [r4, #0x68]
	subs r2, #0x54
	str r2, [r4, #0x40]
	ldrb r0, [r4, #0x12]
	adds r0, #1
	strb r0, [r4, #0x12]
	movs r1, #0x1f
	ands r0, r1
	cmp r0, #0
	bne _080DFA6A
	adds r0, r2, #0
	movs r1, #2
	bl FUN_080bfc94
_080DFA6A:
	ldrb r0, [r4, #0xd]
	cmp r0, #0
	beq _080DFA7C
	cmp r0, #1
	beq _080DFAD0
	b _080DFADE
	.align 2, 0
_080DFA78: .4byte gSineTable
_080DFA7C:
	adds r0, r4, #0
	adds r0, #0x8c
	ldr r0, [r0]
	movs r1, #0x80
	lsls r1, r1, #0x16
	ands r0, r1
	cmp r0, #0
	beq _080DFADE
	ldr r0, _080DFAB4 @ =gInChat
	ldrb r0, [r0]
	cmp r0, #0
	beq _080DFADE
	ldr r0, _080DFAB8 @ =gCollisionManager
	movs r1, #0xc5
	lsls r1, r1, #3
	adds r0, r0, r1
	adds r1, r4, #0
	adds r1, #0x74
	ldr r0, [r0]
	cmp r0, r1
	bne _080DFADE
	ldrb r0, [r4, #0x10]
	cmp r0, #0
	bne _080DFAC0
	ldr r0, _080DFABC @ =0x000002D5
	bl PrintNormalMessage
	b _080DFAC8
	.align 2, 0
_080DFAB4: .4byte gInChat
_080DFAB8: .4byte gCollisionManager
_080DFABC: .4byte 0x000002D5
_080DFAC0:
	movs r0, #0xb5
	lsls r0, r0, #2
	bl PrintNormalMessage
_080DFAC8:
	ldrb r0, [r4, #0xd]
	adds r0, #1
	strb r0, [r4, #0xd]
	b _080DFADE
_080DFAD0:
	ldr r0, _080DFAE4 @ =gTextWindow+8
	ldrh r1, [r0, #2]
	cmp r1, #0
	bne _080DFADE
	ldr r0, _080DFAE8 @ =gInChat
	strb r1, [r0]
	strb r1, [r4, #0xd]
_080DFADE:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080DFAE4: .4byte gTextWindow+8
_080DFAE8: .4byte gInChat
