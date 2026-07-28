	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start Snakecord_Init
Snakecord_Init: @ 0x08074360
	push {r4, r5, r6, r7, lr}
	mov r7, sl
	mov r6, sb
	mov r5, r8
	push {r5, r6, r7}
	sub sp, #4
	adds r6, r0, #0
	ldr r1, _080743D4 @ =gEnemyFnTable
	ldrb r0, [r6, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r6, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r6, #0x14]
	ldr r1, _080743D8 @ =0x0836700C
	ldrb r0, [r6, #0x10]
	adds r0, r0, r1
	ldrb r0, [r0]
	strb r0, [r6, #0xd]
	ldrb r0, [r6, #0xa]
	movs r1, #2
	orrs r0, r1
	movs r4, #0
	movs r1, #0xfe
	ands r0, r1
	strb r0, [r6, #0xa]
	adds r0, r6, #0
	bl InitNonAffineMotion
	ldr r0, _080743DC @ =gSystemSavedataManager
	ldrb r1, [r0, #0x14]
	movs r2, #0x40
	adds r0, r2, #0
	ands r0, r1
	cmp r0, #0
	beq _080743E8
	ldr r0, _080743E0 @ =gCurStory
	ldrb r1, [r0, #4]
	adds r0, r2, #0
	ands r0, r1
	lsls r0, r0, #0x18
	lsrs r5, r0, #0x18
	cmp r5, #0
	bne _080743E8
	ldrb r0, [r6, #0xa]
	movs r1, #4
	orrs r0, r1
	strb r0, [r6, #0xa]
	adds r4, r6, #0
	adds r4, #0x74
	ldr r1, _080743E4 @ =sCollisions
	adds r2, r6, #0
	adds r2, #0x54
	adds r0, r4, #0
	movs r3, #0xc
	b _08074400
	.align 2, 0
_080743D4: .4byte gEnemyFnTable
_080743D8: .4byte 0x0836700C
_080743DC: .4byte gSystemSavedataManager
_080743E0: .4byte gCurStory
_080743E4: .4byte sCollisions
_080743E8:
	ldrb r1, [r6, #0xa]
	movs r0, #4
	movs r5, #0
	orrs r0, r1
	strb r0, [r6, #0xa]
	adds r4, r6, #0
	adds r4, #0x74
	ldr r1, _080744C4 @ =sCollisions
	adds r2, r6, #0
	adds r2, #0x54
	adds r0, r4, #0
	movs r3, #8
_08074400:
	bl InitBody
	str r6, [r4, #0x2c]
	str r5, [r4, #0x24]
	ldr r0, _080744C8 @ =FUN_08074134
	str r0, [r4, #0x24]
	adds r1, r6, #0
	adds r1, #0xb4
	movs r0, #0
	str r0, [r1]
	ldrb r0, [r6, #0x10]
	cmp r0, #0
	bne _080744D8
	movs r7, #0
	ldr r4, [r6, #0x54]
	ldr r1, [r6, #0x58]
	adds r0, r4, #0
	bl FUN_0800a134
	adds r5, r0, #0
	movs r3, #0
	mov sb, r3
	ldr r0, _080744CC @ =gSineTable
	mov r8, r0
	movs r1, #0x64
	add r1, r8
	mov sl, r1
_08074436:
	ldr r0, _080744D0 @ =gEnemyHeaderPtr
	ldr r0, [r0]
	str r3, [sp]
	bl AllocEntityLast
	adds r2, r0, #0
	ldr r3, [sp]
	cmp r2, #0
	beq _080744AA
	adds r1, r2, #0
	adds r1, #0x25
	movs r0, #0x18
	strb r0, [r1]
	ldr r1, _080744D4 @ =gEnemyFnTable
	movs r0, #0x14
	strb r0, [r2, #9]
	ldr r0, [r1, #0x50]
	ldr r0, [r0]
	str r0, [r2, #0x14]
	mov r0, sb
	strh r0, [r2, #0x20]
	adds r0, r2, #0
	adds r0, #0x22
	mov r1, sb
	strb r1, [r0]
	ldrb r0, [r2, #0xb]
	movs r1, #0x10
	orrs r0, r1
	strb r0, [r2, #0xb]
	ldrb r0, [r2, #0x1c]
	strb r0, [r2, #0x1d]
	movs r0, #1
	strb r0, [r2, #0x10]
	strb r3, [r2, #0x12]
	str r4, [r2, #0x54]
	str r5, [r2, #0x58]
	str r4, [r2, #0x64]
	str r5, [r2, #0x68]
	str r7, [r2, #0x28]
	cmp r7, #0
	beq _0807448A
	str r2, [r7, #0x2c]
_0807448A:
	adds r7, r2, #0
	mov r0, r8
	adds r0, #0xe4
	movs r2, #0
	ldrsh r1, [r0, r2]
	lsls r0, r1, #3
	subs r0, r0, r1
	lsls r0, r0, #1
	adds r4, r4, r0
	mov r0, sl
	movs r2, #0
	ldrsh r1, [r0, r2]
	lsls r0, r1, #3
	subs r0, r0, r1
	lsls r0, r0, #1
	adds r5, r5, r0
_080744AA:
	adds r3, #1
	cmp r3, #3
	ble _08074436
	movs r0, #0
	strb r3, [r6, #0x12]
	str r7, [r6, #0x28]
	str r0, [r6, #0x2c]
	cmp r7, #0
	beq _080744BE
	str r6, [r7, #0x2c]
_080744BE:
	str r4, [r6, #0x54]
	str r5, [r6, #0x58]
	b _080744DE
	.align 2, 0
_080744C4: .4byte sCollisions
_080744C8: .4byte FUN_08074134
_080744CC: .4byte gSineTable
_080744D0: .4byte gEnemyHeaderPtr
_080744D4: .4byte gEnemyFnTable
_080744D8:
	adds r0, r6, #0
	bl Snakecord_Update
_080744DE:
	add sp, #4
	pop {r3, r4, r5}
	mov r8, r3
	mov sb, r4
	mov sl, r5
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
