	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_0803b4b0
FUN_0803b4b0: @ 0x0803B4B0
	push {lr}
	adds r2, r0, #0
	ldr r0, [r2, #0x14]
	movs r1, #4
	ands r0, r1
	cmp r0, #0
	beq _0803B4DA
	ldr r1, [r2, #0x2c]
	ldr r3, _0803B4E0 @ =gMission
	ldrh r2, [r3, #0x20]
	ldr r0, _0803B4E4 @ =0x0000FFFE
	cmp r2, r0
	bhi _0803B4CE
	adds r0, r2, #1
	strh r0, [r3, #0x20]
_0803B4CE:
	ldrb r0, [r1, #0x11]
	cmp r0, #0
	bne _0803B4DA
	adds r1, #0xb4
	movs r0, #1
	strb r0, [r1, #0xc]
_0803B4DA:
	pop {r0}
	bx r0
	.align 2, 0
_0803B4E0: .4byte gMission
_0803B4E4: .4byte 0x0000FFFE

	thumb_func_start FUN_0803b4e8
FUN_0803b4e8: @ 0x0803B4E8
	push {lr}
	bl FUN_080098a4
	lsls r0, r0, #0x10
	lsrs r1, r0, #0x10
	ldr r0, _0803B500 @ =0x0000800F
	cmp r1, r0
	bne _0803B4FA
	movs r1, #0
_0803B4FA:
	adds r0, r1, #0
	pop {r1}
	bx r1
	.align 2, 0
_0803B500: .4byte 0x0000800F

