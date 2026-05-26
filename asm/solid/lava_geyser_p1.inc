	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start Solid7_Update
Solid7_Update: @ 0x080CC8F8
	push {r4, lr}
	adds r4, r0, #0
	ldr r1, _080CC924 @ =0x0836FF7C
	ldrb r0, [r4, #0xd]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r1, [r0]
	adds r0, r4, #0
	bl _call_via_r1
	ldr r1, _080CC928 @ =0x0836FF94
	ldrb r0, [r4, #0xd]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r1, [r0]
	adds r0, r4, #0
	bl _call_via_r1
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080CC924: .4byte 0x0836FF7C
_080CC928: .4byte 0x0836FF94
