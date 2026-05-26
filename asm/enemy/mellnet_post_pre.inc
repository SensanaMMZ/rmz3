	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_0807d994
FUN_0807d994: @ 0x0807D994
	push {lr}
	adds r2, r0, #0
	adds r0, #0x8c
	ldr r0, [r0]
	ldr r1, _0807D9B0 @ =0x00020001
	ands r0, r1
	cmp r0, r1
	bne _0807D9AC
	movs r1, #0
	movs r0, #6
	strb r0, [r2, #0xd]
	strb r1, [r2, #0xe]
_0807D9AC:
	pop {r0}
	bx r0
	.align 2, 0
_0807D9B0: .4byte 0x00020001

	thumb_func_start FUN_0807d9b4
FUN_0807d9b4: @ 0x0807D9B4
	push {r4, r5, lr}
	adds r4, r0, #0
	adds r5, r4, #0
	adds r5, #0xb4
	ldr r0, [r5]
	cmp r0, #0
	beq _0807D9CA
	bl isKilled
	cmp r0, #0
	beq _0807D9EA
_0807D9CA:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _0807DA08 @ =0x08367CF4
	bl SetDDP
	movs r0, #0
	str r0, [r5]
	adds r0, r4, #0
	bl IsFrozen
	adds r1, r0, #0
	cmp r1, #0
	bne _0807D9EA
	movs r0, #4
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_0807D9EA:
	adds r0, r4, #0
	adds r0, #0x8c
	ldr r0, [r0]
	ldr r1, _0807DA0C @ =0x00020001
	ands r0, r1
	cmp r0, r1
	bne _0807DA00
	movs r1, #0
	movs r0, #6
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_0807DA00:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_0807DA08: .4byte 0x08367CF4
_0807DA0C: .4byte 0x00020001
