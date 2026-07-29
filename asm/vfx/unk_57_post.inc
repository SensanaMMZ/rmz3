	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080c1a3c
FUN_080c1a3c: @ 0x080C1A3C
	push {r4, r5, lr}
	adds r4, r0, #0
	ldr r1, _080C1A94 @ =gVFXFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r4, #0x14]
	adds r0, r4, #0
	bl InitNonAffineMotion
	ldrb r1, [r4, #0xa]
	movs r0, #1
	movs r5, #0
	orrs r0, r1
	movs r1, #2
	orrs r0, r1
	strb r0, [r4, #0xa]
	ldr r0, _080C1A98 @ =0x00006203
	adds r1, r0, #0
	ldrb r0, [r4, #0x11]
	adds r1, r1, r0
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0x11]
	cmp r0, #1
	beq _080C1A9C
	movs r1, #0
	ldr r0, [r4, #0x5c]
	cmp r0, #0
	ble _080C1A84
	movs r1, #1
_080C1A84:
	adds r2, r1, #0
	cmp r2, #0
	beq _080C1AB4
	ldrb r0, [r4, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _080C1ABA
	.align 2, 0
_080C1A94: .4byte gVFXFnTable
_080C1A98: .4byte 0x00006203
_080C1A9C:
	movs r1, #0
	ldr r0, [r4, #0x5c]
	cmp r0, #0
	bgt _080C1AA6
	movs r1, #1
_080C1AA6:
	adds r2, r1, #0
	cmp r2, #0
	beq _080C1AB4
	ldrb r0, [r4, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _080C1ABA
_080C1AB4:
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
_080C1ABA:
	strb r0, [r4, #0xa]
	adds r1, r2, #0
	adds r0, r4, #0
	adds r0, #0x4c
	strb r1, [r0]
	adds r3, r4, #0
	adds r3, #0x4a
	lsls r1, r1, #4
	ldrb r2, [r3]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r1
	strb r0, [r3]
	movs r0, #0
	strb r0, [r4, #0x12]
	movs r0, #0x3f
	bl PlaySound
	adds r0, r4, #0
	bl VFX57_Update
	pop {r4, r5}
	pop {r0}
	bx r0
