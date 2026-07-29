	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_08089eb0
FUN_08089eb0: @ 0x08089EB0
	push {r4, r5, lr}
	sub sp, #8
	adds r5, r0, #0
	ldrb r2, [r5, #0xe]
	cmp r2, #0
	beq _08089EC2
	cmp r2, #1
	beq _08089F40
	b _08089F52
_08089EC2:
	ldrb r1, [r5, #0xa]
	movs r0, #0xfe
	ands r0, r1
	strb r0, [r5, #0xa]
	adds r0, r5, #0
	adds r0, #0x8c
	str r2, [r0]
	adds r0, #4
	str r2, [r0]
	adds r0, #4
	strb r2, [r0]
	ldrb r1, [r5, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r5, #0xa]
	ldr r0, [r5, #0x54]
	str r0, [sp]
	ldr r0, [r5, #0x58]
	ldr r1, _08089F04 @ =0xFFFFF800
	adds r0, r0, r1
	str r0, [sp, #4]
	movs r0, #1
	mov r1, sp
	bl CreateSmoke
	ldrb r0, [r5, #0x10]
	cmp r0, #2
	bne _08089F08
	movs r0, #0x31
	bl PlaySound
	b _08089F0E
	.align 2, 0
_08089F04: .4byte 0xFFFFF800
_08089F08:
	movs r0, #0x2a
	bl PlaySound
_08089F0E:
	ldr r2, _08089F38 @ =gMission
	ldrh r1, [r2, #0xc]
	ldr r0, _08089F3C @ =0x0000270E
	cmp r1, r0
	bhi _08089F1C
	adds r0, r1, #1
	strh r0, [r2, #0xc]
_08089F1C:
	adds r4, r5, #0
	adds r4, #0x54
	adds r0, r5, #0
	adds r1, r4, #0
	bl TryDropZakoDisk
	movs r0, #4
	adds r1, r4, #0
	bl TryDropItem
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
	b _08089F52
	.align 2, 0
_08089F38: .4byte gMission
_08089F3C: .4byte 0x0000270E
_08089F40:
	ldr r1, _08089F5C @ =gEnemyFnTable
	ldrb r0, [r5, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #4
	str r1, [r5, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0x10]
	str r0, [r5, #0x14]
_08089F52:
	add sp, #8
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_08089F5C: .4byte gEnemyFnTable
