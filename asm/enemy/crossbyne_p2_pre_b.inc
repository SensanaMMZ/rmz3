	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start Crossbyne_Update
Crossbyne_Update: @ 0x0807CF00
	push {r4, lr}
	adds r4, r0, #0
	bl FUN_0807cd74
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _0807CF34
	adds r0, r4, #0
	bl crossbyne_0807cdc4
	ldr r1, _0807CF3C @ =0x08367B58
	ldrb r0, [r4, #0xd]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r1, [r0]
	adds r0, r4, #0
	bl _call_via_r1
	ldr r1, _0807CF40 @ =0x08367B74
	ldrb r0, [r4, #0xd]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r1, [r0]
	adds r0, r4, #0
	bl _call_via_r1
_0807CF34:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_0807CF3C: .4byte 0x08367B58
_0807CF40: .4byte 0x08367B74
