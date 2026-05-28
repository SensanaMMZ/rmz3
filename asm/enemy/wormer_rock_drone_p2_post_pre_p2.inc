	.include "asm/macros.inc"

	.syntax unified

	.text

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
