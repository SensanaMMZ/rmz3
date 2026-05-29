	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start Phantom_Update
Phantom_Update: @ 0x0805EF0C
	push {r4, lr}
	adds r4, r0, #0
	adds r0, #0x8c
	ldr r0, [r0]
	movs r1, #0x80
	lsls r1, r1, #2
	ands r0, r1
	cmp r0, #0
	bne _0805EF2A
	adds r0, r4, #0
	adds r0, #0xa4
	movs r1, #0
	ldrsh r0, [r0, r1]
	cmp r0, #0
	bne _0805EF6C
_0805EF2A:
	ldr r0, _0805EF64 @ =gStageRun
	ldrh r1, [r0, #8]
	movs r0, #8
	ands r0, r1
	lsls r0, r0, #0x10
	lsrs r2, r0, #0x10
	cmp r2, #0
	bne _0805EF6C
	adds r1, r4, #0
	adds r1, #0xd0
	ldr r0, [r1]
	cmp r0, #0
	beq _0805EF46
	str r2, [r1]
_0805EF46:
	ldr r1, _0805EF68 @ =gBossFnTable
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
	bl Phantom_Die
	b _0805EF82
	.align 2, 0
_0805EF64: .4byte gStageRun
_0805EF68: .4byte gBossFnTable
_0805EF6C:
	ldr r0, _0805EF88 @ =0x08365414
	ldrb r1, [r4, #0x10]
	lsls r1, r1, #2
	adds r1, r1, r0
	ldr r1, [r1]
	adds r0, r4, #0
	bl _call_via_r1
	adds r0, r4, #0
	bl phantom_080607e4
_0805EF82:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_0805EF88: .4byte 0x08365414
