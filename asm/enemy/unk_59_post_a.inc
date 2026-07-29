	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_08091814
FUN_08091814: @ 0x08091814
	push {r4, r5, lr}
	adds r4, r0, #0
	ldr r5, [r4, #0x28]
	adds r0, #0x34
	adds r2, r5, #0
	adds r2, #0x34
	ldrb r1, [r4, #0xe]
	cmp r1, #0
	beq _0809182C
	cmp r1, #1
	beq _0809183C
	b _080918E2
_0809182C:
	ldr r1, [r2, #8]
	adds r2, r4, #0
	adds r2, #0x54
	bl InitNonAffineSprite
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0809183C:
	adds r0, r5, #0
	adds r0, #0xc4
	ldr r1, [r0]
	movs r2, #8
	ands r1, r2
	adds r5, r0, #0
	cmp r1, #0
	beq _08091856
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _08091868 @ =0x08369864
	bl SetDDP
_08091856:
	ldrb r0, [r4, #0x12]
	adds r2, r0, #0
	cmp r2, #0
	bne _0809186C
	ldrb r1, [r4, #0xa]
	movs r0, #1
	orrs r0, r1
	b _08091872
	.align 2, 0
_08091868: .4byte 0x08369864
_0809186C:
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
_08091872:
	strb r0, [r4, #0xa]
	adds r0, r2, #1
	movs r2, #0
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #3
	bne _08091884
	strb r2, [r4, #0x12]
_08091884:
	adds r3, r5, #0
	ldr r0, [r3]
	movs r1, #1
	ands r0, r1
	cmp r0, #0
	beq _080918C4
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
	ldr r1, _080918E8 @ =gEnemyFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r4, #0x14]
_080918C4:
	ldr r0, [r3]
	movs r1, #2
	ands r0, r1
	cmp r0, #0
	beq _080918D4
	movs r0, #3
	strb r0, [r4, #0xd]
	strb r2, [r4, #0xe]
_080918D4:
	ldr r0, [r5]
	movs r1, #4
	ands r0, r1
	cmp r0, #0
	beq _080918E2
	strb r1, [r4, #0xd]
	strb r2, [r4, #0xe]
_080918E2:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080918E8: .4byte gEnemyFnTable

