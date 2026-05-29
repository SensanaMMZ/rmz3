	.include "asm/macros.inc"

	.syntax unified

	.text

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
