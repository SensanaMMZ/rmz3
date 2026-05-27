	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start WormerRockDrone_Init
WormerRockDrone_Init: @ 0x08076F20
	push {r4, r5, lr}
	adds r4, r0, #0
	ldr r1, _08076F80 @ =gEnemyFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r4, #0x14]
	ldr r1, _08076F84 @ =0x08367250
	ldrb r0, [r4, #0x10]
	adds r0, r0, r1
	ldrb r0, [r0]
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
	ldr r1, _08076F88 @ =0x08367220
	adds r2, r4, #0
	adds r2, #0x54
	adds r0, r5, #0
	movs r3, #6
	bl InitBody
	str r4, [r5, #0x2c]
	ldr r0, _08076F8C @ =nop_08076ee0
	str r0, [r5, #0x24]
	adds r0, r4, #0
	bl WormerRockDrone_Update
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_08076F80: .4byte gEnemyFnTable
_08076F84: .4byte 0x08367250
_08076F88: .4byte 0x08367220
_08076F8C: .4byte nop_08076ee0

	thumb_func_start WormerRockDrone_Update
WormerRockDrone_Update: @ 0x08076F90
	push {r4, lr}
	adds r4, r0, #0
	bl FUN_08076ee4
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _08076FBE
	ldr r1, _08076FC4 @ =0x08367214
	ldrb r0, [r4, #0xd]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r1, [r0]
	adds r0, r4, #0
	bl _call_via_r1
	ldr r1, _08076FC8 @ =0x08367218
	ldrb r0, [r4, #0xd]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r1, [r0]
	adds r0, r4, #0
	bl _call_via_r1
_08076FBE:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_08076FC4: .4byte 0x08367214
_08076FC8: .4byte 0x08367218
