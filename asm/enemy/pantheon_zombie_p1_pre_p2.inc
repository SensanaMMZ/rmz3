	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_0807fda8
FUN_0807fda8: @ 0x0807FDA8
	push {r4, lr}
	adds r2, r0, #0
	adds r3, r2, #0
	adds r3, #0x8c
	ldr r0, [r3]
	movs r1, #0x80
	lsls r1, r1, #2
	ands r0, r1
	cmp r0, #0
	beq _0807FDF0
	ldr r1, _0807FDE0 @ =gEnemyFnTable
	ldrb r0, [r2, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r4, #2
	str r4, [r2, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r2, #0x14]
	ldr r1, [r3]
	movs r0, #0x80
	lsls r0, r0, #0xa
	ands r1, r0
	cmp r1, #0
	beq _0807FDE4
	strb r4, [r2, #0xd]
	b _0807FDE6
	.align 2, 0
_0807FDE0: .4byte gEnemyFnTable
_0807FDE4:
	strb r1, [r2, #0xd]
_0807FDE6:
	adds r0, r2, #0
	bl PantheonZombie_Die
	movs r0, #1
	b _0807FDF2
_0807FDF0:
	movs r0, #0
_0807FDF2:
	pop {r4}
	pop {r1}
	bx r1

	thumb_func_start FUN_0807fdf8
FUN_0807fdf8: @ 0x0807FDF8
	push {r4, r5, r6, lr}
	adds r4, r0, #0
	adds r6, r4, #0
	adds r6, #0xb4
	ldr r5, [r6]
	cmp r5, #0
	bne _0807FE26
	adds r0, #0x8c
	ldr r0, [r0]
	movs r1, #1
	ands r0, r1
	cmp r0, #0
	beq _0807FE26
	ldr r2, _0807FE2C @ =0x08367F90
	movs r0, #0
	adds r1, r4, #0
	bl ApplyElementEffect
	str r0, [r6]
	cmp r0, #0
	beq _0807FE26
	strb r5, [r4, #0xd]
	strb r5, [r4, #0xe]
_0807FE26:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_0807FE2C: .4byte 0x08367F90

	thumb_func_start PantheonZombie_Init
PantheonZombie_Init: @ 0x0807FE30
	push {r4, r5, r6, lr}
	adds r4, r0, #0
	ldr r1, _0807FE9C @ =gEnemyFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r4, #0x14]
	ldr r1, _0807FEA0 @ =0x08367F98
	ldrb r0, [r4, #0x10]
	adds r0, r0, r1
	ldrb r0, [r0]
	movs r6, #0
	strb r0, [r4, #0xd]
	ldrb r0, [r4, #0xa]
	movs r1, #2
	orrs r0, r1
	movs r1, #1
	orrs r0, r1
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	bl InitNonAffineMotion
	ldrb r1, [r4, #0xa]
	movs r0, #4
	orrs r0, r1
	strb r0, [r4, #0xa]
	adds r5, r4, #0
	adds r5, #0x74
	ldr r1, _0807FEA4 @ =0x08367ED0
	adds r2, r4, #0
	adds r2, #0x54
	adds r0, r5, #0
	movs r3, #0x14
	bl InitBody
	str r4, [r5, #0x2c]
	ldr r0, _0807FEA8 @ =FUN_0807fd84
	str r0, [r5, #0x24]
	adds r0, r4, #0
	adds r0, #0xb4
	str r6, [r0]
	adds r0, #4
	strb r6, [r0]
	adds r0, r4, #0
	bl PantheonZombie_Update
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_0807FE9C: .4byte gEnemyFnTable
_0807FEA0: .4byte 0x08367F98
_0807FEA4: .4byte 0x08367ED0
_0807FEA8: .4byte FUN_0807fd84

	thumb_func_start PantheonZombie_Update
PantheonZombie_Update: @ 0x0807FEAC
	push {r4, lr}
	adds r4, r0, #0
	ldr r0, [r4, #0x28]
	adds r0, #0xc0
	ldr r0, [r0]
	movs r1, #0x80
	lsls r1, r1, #1
	ands r0, r1
	cmp r0, #0
	beq _0807FEE4
	ldr r1, _0807FEE0 @ =gEnemyFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r4, #0x14]
	movs r0, #1
	strb r0, [r4, #0xd]
	adds r0, r4, #0
	bl PantheonZombie_Die
	b _0807FF16
	.align 2, 0
_0807FEE0: .4byte gEnemyFnTable
_0807FEE4:
	adds r0, r4, #0
	bl FUN_0807fda8
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _0807FF16
	adds r0, r4, #0
	bl FUN_0807fdf8
	ldr r1, _0807FF1C @ =0x08367E84
	ldrb r0, [r4, #0xd]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r1, [r0]
	adds r0, r4, #0
	bl _call_via_r1
	ldr r1, _0807FF20 @ =0x08367EA4
	ldrb r0, [r4, #0xd]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r1, [r0]
	adds r0, r4, #0
	bl _call_via_r1
_0807FF16:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_0807FF1C: .4byte 0x08367E84
_0807FF20: .4byte 0x08367EA4
