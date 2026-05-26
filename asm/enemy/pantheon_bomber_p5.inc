	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080865d4
FUN_080865d4: @ 0x080865D4
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	bne _080865EE
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _080865F4 @ =0x08368564
	bl SetDDP
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080865EE:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080865F4: .4byte 0x08368564
