	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start mothjiro_08088a20
mothjiro_08088a20: @ 0x08088A20
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	bne _08088A3A
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _08088A40 @ =0x083687E0
	bl SetDDP
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08088A3A:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_08088A40: .4byte 0x083687E0
