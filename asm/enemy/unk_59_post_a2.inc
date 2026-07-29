	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_08091980
FUN_08091980: @ 0x08091980
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #7
	bls _0809198C
	b _08091AA6
_0809198C:
	lsls r0, r0, #2
	ldr r1, _08091998 @ =_0809199C
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_08091998: .4byte _0809199C
_0809199C: @ jump table
	.4byte _080919BC @ case 0
	.4byte _080919D0 @ case 1
	.4byte _080919E0 @ case 2
	.4byte _080919EA @ case 3
	.4byte _08091A08 @ case 4
	.4byte _08091A12 @ case 5
	.4byte _08091A3C @ case 6
	.4byte _08091A46 @ case 7
_080919BC:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _080919DC @ =0x08369894
	bl SetDDP
	movs r0, #0x1b
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080919D0:
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	b _08091A30
	.align 2, 0
_080919DC: .4byte 0x08369894
_080919E0:
	movs r0, #0xf
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080919EA:
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0x12]
	movs r1, #3
	bl __umodsi3
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #2
	beq _08091A26
	ldrb r0, [r4, #0xa]
	movs r1, #1
	orrs r0, r1
	b _08091A2C
_08091A08:
	movs r0, #0xf
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08091A12:
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	movs r1, #1
	ands r0, r1
	cmp r0, #0
	beq _08091A26
	ldrb r0, [r4, #0xa]
	orrs r0, r1
	b _08091A2C
_08091A26:
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
_08091A2C:
	strb r0, [r4, #0xa]
	ldrb r0, [r4, #0x12]
_08091A30:
	cmp r0, #0
	bne _08091AA6
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
	b _08091AA6
_08091A3C:
	movs r0, #0xf
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08091A46:
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0x12]
	movs r1, #3
	bl __umodsi3
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #2
	bne _08091A64
	ldrb r0, [r4, #0xa]
	movs r1, #1
	orrs r0, r1
	b _08091A6A
_08091A64:
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
_08091A6A:
	strb r0, [r4, #0xa]
	ldrb r2, [r4, #0x12]
	cmp r2, #0
	bne _08091AA6
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	adds r0, #0x8c
	str r2, [r0]
	adds r0, #4
	str r2, [r0]
	adds r0, #4
	strb r2, [r0]
	ldrb r1, [r4, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r4, #0xa]
	ldr r1, _08091AAC @ =gEnemyFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r4, #0x14]
_08091AA6:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_08091AAC: .4byte gEnemyFnTable

	thumb_func_start FUN_08091ab0
FUN_08091ab0: @ 0x08091AB0
	push {r4, r5, lr}
	adds r4, r0, #0
	ldr r5, [r4, #0x28]
	adds r0, #0x34
	adds r2, r5, #0
	adds r2, #0x34
	ldrb r1, [r4, #0xe]
	cmp r1, #0
	beq _08091AC8
	cmp r1, #1
	beq _08091AE2
	b _08091B56
_08091AC8:
	ldr r1, [r2, #8]
	adds r2, r4, #0
	adds r2, #0x54
	bl InitNonAffineSprite
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _08091AF4 @ =0x08369894
	bl SetDDP
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08091AE2:
	ldrb r0, [r4, #0x12]
	adds r2, r0, #0
	cmp r2, #0
	bne _08091AF8
	ldrb r1, [r4, #0xa]
	movs r0, #1
	orrs r0, r1
	b _08091AFE
	.align 2, 0
_08091AF4: .4byte 0x08369894
_08091AF8:
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
_08091AFE:
	strb r0, [r4, #0xa]
	adds r0, r2, #1
	movs r2, #0
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #4
	bne _08091B10
	strb r2, [r4, #0x12]
_08091B10:
	ldr r0, [r5, #0x58]
	str r0, [r4, #0x58]
	adds r0, r5, #0
	adds r0, #0xc4
	ldr r0, [r0]
	movs r1, #1
	ands r0, r1
	cmp r0, #0
	beq _08091B56
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	adds r0, #0x8c
	str r2, [r0]
	adds r0, #4
	str r2, [r0]
	adds r0, #4
	strb r2, [r0]
	ldrb r1, [r4, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r4, #0xa]
	ldr r1, _08091B5C @ =gEnemyFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r4, #0x14]
_08091B56:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_08091B5C: .4byte gEnemyFnTable

	thumb_func_start FUN_08091b60
FUN_08091b60: @ 0x08091B60
	push {r4, r5, r6, r7, lr}
	mov r7, r8
	push {r7}
	adds r4, r0, #0
	ldr r0, [r4, #0x28]
	mov r8, r0
	adds r7, r4, #0
	adds r7, #0x34
	mov r6, r8
	adds r6, #0x34
	ldrb r5, [r4, #0xe]
	cmp r5, #0
	beq _08091B80
	cmp r5, #1
	beq _08091BB8
	b _08091C46
_08091B80:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _08091BD0 @ =0x08369894
	bl SetDDP
	ldr r1, [r6, #8]
	adds r2, r4, #0
	adds r2, #0x54
	adds r0, r7, #0
	bl InitScalerotSprite1
	ldrb r1, [r4, #0xa]
	movs r0, #0x40
	orrs r0, r1
	strb r0, [r4, #0xa]
	ldrb r1, [r4, #0xb]
	movs r0, #1
	orrs r0, r1
	strb r0, [r4, #0xb]
	adds r0, r4, #0
	adds r0, #0x24
	strb r5, [r0]
	strb r5, [r4, #0x12]
	movs r0, #0x20
	strb r0, [r4, #0x13]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08091BB8:
	ldrb r0, [r4, #0x12]
	adds r3, r0, #0
	ldrb r2, [r4, #0x13]
	cmp r3, #0
	bne _08091BD4
	cmp r2, #0x55
	bhi _08091BD4
	ldrb r1, [r4, #0xa]
	movs r0, #1
	orrs r0, r1
	b _08091BDA
	.align 2, 0
_08091BD0: .4byte 0x08369894
_08091BD4:
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
_08091BDA:
	strb r0, [r4, #0xa]
	adds r0, r3, #1
	movs r3, #0
	strb r0, [r4, #0x12]
	lsls r1, r2, #0x18
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	lsrs r1, r1, #0x1c
	cmp r0, r1
	bne _08091BF4
	adds r0, r2, #3
	strb r0, [r4, #0x13]
	strb r3, [r4, #0x12]
_08091BF4:
	mov r0, r8
	adds r0, #0x52
	ldrh r0, [r0]
	adds r1, r4, #0
	adds r1, #0x52
	strh r0, [r1]
	mov r0, r8
	adds r0, #0xc4
	ldr r0, [r0]
	movs r1, #1
	ands r0, r1
	cmp r0, #0
	beq _08091C46
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	adds r0, #0x8c
	str r3, [r0]
	adds r0, #4
	str r3, [r0]
	adds r1, r4, #0
	adds r1, #0x94
	movs r0, #0
	strb r0, [r1]
	ldrb r1, [r4, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r4, #0xa]
	ldr r1, _08091C50 @ =gEnemyFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r4, #0x14]
_08091C46:
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_08091C50: .4byte gEnemyFnTable

	thumb_func_start FUN_08091c54
FUN_08091c54: @ 0x08091C54
	push {r4, r5, r6, r7, lr}
	mov r7, r8
	push {r7}
	adds r4, r0, #0
	ldr r0, [r4, #0x28]
	mov r8, r0
	adds r7, r4, #0
	adds r7, #0x34
	mov r6, r8
	adds r6, #0x34
	ldrb r5, [r4, #0xe]
	cmp r5, #0
	beq _08091C74
	cmp r5, #1
	beq _08091CAC
	b _08091D00
_08091C74:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _08091CBC @ =0x08369894
	bl SetDDP
	ldr r1, [r6, #8]
	adds r2, r4, #0
	adds r2, #0x54
	adds r0, r7, #0
	bl InitScalerotSprite1
	ldrb r1, [r4, #0xa]
	movs r0, #0x40
	orrs r0, r1
	strb r0, [r4, #0xa]
	ldrb r1, [r4, #0xb]
	movs r0, #1
	orrs r0, r1
	strb r0, [r4, #0xb]
	adds r0, r4, #0
	adds r0, #0x24
	strb r5, [r0]
	strb r5, [r4, #0x12]
	movs r0, #0x59
	strb r0, [r4, #0x13]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08091CAC:
	ldrb r0, [r4, #0x12]
	adds r2, r0, #0
	cmp r2, #0
	bne _08091CC0
	ldrb r1, [r4, #0xa]
	movs r0, #1
	orrs r0, r1
	b _08091CC6
	.align 2, 0
_08091CBC: .4byte 0x08369894
_08091CC0:
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
_08091CC6:
	strb r0, [r4, #0xa]
	adds r0, r2, #1
	strb r0, [r4, #0x12]
	ldrb r2, [r4, #0x13]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	lsrs r1, r2, #4
	cmp r0, r1
	bne _08091CE0
	movs r0, #0
	strb r0, [r4, #0x12]
	subs r0, r2, #3
	strb r0, [r4, #0x13]
_08091CE0:
	mov r0, r8
	adds r0, #0x52
	ldrh r0, [r0]
	adds r1, r4, #0
	adds r1, #0x52
	movs r2, #0
	strh r0, [r1]
	mov r0, r8
	adds r0, #0xc4
	ldr r0, [r0]
	movs r1, #8
	ands r0, r1
	cmp r0, #0
	beq _08091D00
	strb r2, [r4, #0xd]
	strb r2, [r4, #0xe]
_08091D00:
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0

