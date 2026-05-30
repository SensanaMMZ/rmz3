	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start WormerSnowBall_Update
WormerSnowBall_Update: @ 0x0807B2B4
	push {r4, lr}
	adds r4, r0, #0
	bl FUN_0807b1e0
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _0807B2E2
	ldr r1, _0807B2E8 @ =0x083677E8
	ldrb r0, [r4, #0xd]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r1, [r0]
	adds r0, r4, #0
	bl _call_via_r1
	ldr r1, _0807B2EC @ =0x083677F8
	ldrb r0, [r4, #0xd]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r1, [r0]
	adds r0, r4, #0
	bl _call_via_r1
_0807B2E2:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_0807B2E8: .4byte 0x083677E8
_0807B2EC: .4byte 0x083677F8
