	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start PurpleNerple_Init
PurpleNerple_Init: @ 0x08075EE0
	push {r4, r5, r6, lr}
	adds r6, r0, #0
	ldrb r1, [r6, #0x10]
	cmp r1, #0
	bne _08075EEE
	adds r0, #0xb9
	strb r1, [r0]
_08075EEE:
	ldrb r0, [r6, #0x10]
	cmp r0, #3
	bne _08075F00
	adds r2, r6, #0
	adds r2, #0xb9
	movs r1, #0
	movs r0, #1
	strb r0, [r2]
	strb r1, [r6, #0x10]
_08075F00:
	ldr r1, _08075F48 @ =gEnemyFnTable
	ldrb r0, [r6, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r6, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r6, #0x14]
	ldr r1, _08075F4C @ =0x083671E8
	ldrb r0, [r6, #0x10]
	adds r0, r0, r1
	ldrb r0, [r0]
	movs r5, #0
	strb r0, [r6, #0xd]
	ldrb r0, [r6, #0xa]
	movs r1, #2
	orrs r0, r1
	movs r1, #1
	movs r4, #0
	orrs r0, r1
	strb r0, [r6, #0xa]
	adds r0, r6, #0
	bl InitNonAffineMotion
	adds r0, r6, #0
	adds r0, #0xb4
	str r5, [r0]
	ldrb r0, [r6, #0x10]
	cmp r0, #1
	beq _08075FD4
	cmp r0, #1
	bgt _08075F50
	cmp r0, #0
	beq _08075F56
	b _08075FF4
	.align 2, 0
_08075F48: .4byte gEnemyFnTable
_08075F4C: .4byte 0x083671E8
_08075F50:
	cmp r0, #2
	beq _08075FD4
	b _08075FF4
_08075F56:
	adds r0, r6, #0
	adds r0, #0xb9
	ldrb r1, [r0]
	adds r0, r6, #0
	bl FUN_08075b74
	ldr r0, _08075F94 @ =gSystemSavedataManager
	ldrb r1, [r0, #0x13]
	movs r0, #8
	ands r0, r1
	cmp r0, #0
	beq _08075FA0
	ldr r0, _08075F98 @ =gCurStory
	ldrb r1, [r0, #4]
	movs r0, #0x40
	ands r0, r1
	cmp r0, #0
	bne _08075FA0
	ldrb r0, [r6, #0xa]
	movs r1, #4
	orrs r0, r1
	strb r0, [r6, #0xa]
	adds r4, r6, #0
	adds r4, #0x74
	ldr r1, _08075F9C @ =0x08367138
	adds r2, r6, #0
	adds r2, #0x54
	adds r0, r4, #0
	movs r3, #8
	b _08075FB8
	.align 2, 0
_08075F94: .4byte gSystemSavedataManager
_08075F98: .4byte gCurStory
_08075F9C: .4byte 0x08367138
_08075FA0:
	ldrb r1, [r6, #0xa]
	movs r0, #4
	movs r5, #0
	orrs r0, r1
	strb r0, [r6, #0xa]
	adds r4, r6, #0
	adds r4, #0x74
	ldr r1, _08075FD0 @ =0x08367138
	adds r2, r6, #0
	adds r2, #0x54
	adds r0, r4, #0
	movs r3, #4
_08075FB8:
	bl InitBody
	str r6, [r4, #0x2c]
	str r5, [r4, #0x24]
	adds r1, r6, #0
	adds r1, #0xb8
	movs r0, #0
	strb r0, [r1]
	adds r1, #8
	ldr r0, [r6, #0x54]
	str r0, [r1]
	b _08075FF4
	.align 2, 0
_08075FD0: .4byte 0x08367138
_08075FD4:
	ldrb r0, [r6, #0xa]
	movs r1, #4
	orrs r0, r1
	strb r0, [r6, #0xa]
	adds r4, r6, #0
	adds r4, #0x74
	ldr r1, _08076000 @ =0x08367138
	adds r2, r6, #0
	adds r2, #0x54
	adds r0, r4, #0
	movs r3, #2
	bl InitBody
	str r6, [r4, #0x2c]
	ldr r0, _08076004 @ =0x08075D3D
	str r0, [r4, #0x24]
_08075FF4:
	adds r0, r6, #0
	bl PurpleNerple_Update
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_08076000: .4byte 0x08367138
_08076004: .4byte 0x08075D3D

