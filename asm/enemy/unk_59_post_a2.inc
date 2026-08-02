	.include "asm/macros.inc"

	.syntax unified

	.text

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
