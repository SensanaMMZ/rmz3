	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start CarryArm_Update
CarryArm_Update: @ 0x08071654
	push {r4, lr}
	adds r4, r0, #0
	bl FUN_0807156c
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _08071682
	ldr r1, _08071688 @ =0x08366B48
	ldrb r0, [r4, #0xd]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r1, [r0]
	adds r0, r4, #0
	bl _call_via_r1
	ldr r1, _0807168C @ =0x08366B60
	ldrb r0, [r4, #0xd]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r1, [r0]
	adds r0, r4, #0
	bl _call_via_r1
_08071682:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_08071688: .4byte 0x08366B48
_0807168C: .4byte 0x08366B60
