	.include "asm/macros.inc"

	.syntax unified
	
	.text


	thumb_func_start Blizzack_Update
Blizzack_Update: @ 0x08059CB4
	push {r4, r5, r6, r7, lr}
	adds r4, r0, #0
	adds r0, #0x8c
	ldr r0, [r0]
	movs r1, #0x80
	lsls r1, r1, #2
	ands r0, r1
	cmp r0, #0
	bne _08059CD2
	adds r0, r4, #0
	adds r0, #0xa4
	movs r1, #0
	ldrsh r0, [r0, r1]
	cmp r0, #0
	bne _08059D08
_08059CD2:
	ldr r0, _08059D00 @ =gStageRun
	ldrh r1, [r0, #8]
	movs r0, #8
	ands r0, r1
	lsls r0, r0, #0x10
	lsrs r2, r0, #0x10
	cmp r2, #0
	bne _08059D08
	ldr r1, _08059D04 @ =gBossFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r4, #0x14]
	strb r2, [r4, #0xd]
	adds r0, r4, #0
	bl Blizzack_Die
	b _08059D8E
	.align 2, 0
_08059D00: .4byte gStageRun
_08059D04: .4byte gBossFnTable
_08059D08:
	adds r0, r4, #0
	bl FUN_0805af14
	adds r6, r4, #0
	adds r6, #0x8c
	ldr r0, [r6]
	movs r7, #1
	ands r0, r7
	cmp r0, #0
	beq _08059D7E
	movs r2, #0
	ldr r0, _08059D94 @ =pZero2
	ldr r0, [r0]
	ldr r1, [r4, #0x54]
	ldr r0, [r0, #0x54]
	cmp r1, r0
	bge _08059D2C
	movs r2, #1
_08059D2C:
	adds r0, r4, #0
	adds r0, #0xc4
	strb r2, [r0]
	adds r5, r4, #0
	adds r5, #0xd4
	ldr r0, [r5]
	cmp r0, #0
	bne _08059D48
	ldr r2, _08059D98 @ =sElementCoord
	movs r0, #0x1a
	adds r1, r4, #0
	bl ApplyElementEffect
	str r0, [r5]
_08059D48:
	ldr r0, [r5]
	bl isKilled
	cmp r0, #0
	beq _08059D56
	movs r0, #0
	str r0, [r5]
_08059D56:
	adds r0, r4, #0
	adds r0, #0x97
	ldrb r1, [r0]
	movs r0, #0xf0
	ands r0, r1
	cmp r0, #0x20
	bne _08059D6C
	adds r1, r4, #0
	adds r1, #0xe0
	movs r0, #0x80
	strb r0, [r1]
_08059D6C:
	ldr r0, [r6]
	movs r1, #0x80
	lsls r1, r1, #0xa
	ands r0, r1
	cmp r0, #0
	beq _08059D7E
	movs r0, #0x13
	strb r0, [r4, #0xd]
	strb r7, [r4, #0xe]
_08059D7E:
	ldr r0, _08059D9C @ =0x08364B50
	ldrb r1, [r4, #0xd]
	lsls r1, r1, #2
	adds r1, r1, r0
	ldr r1, [r1]
	adds r0, r4, #0
	bl _call_via_r1
_08059D8E:
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_08059D94: .4byte pZero2
_08059D98: .4byte sElementCoord
_08059D9C: .4byte sUpdates
