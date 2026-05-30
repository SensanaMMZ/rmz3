	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start forceWaterLanding
forceWaterLanding: @ 0x08071220
	push {lr}
	adds r3, r0, #0
	ldr r1, _08071238 @ =gOverworld
	ldr r2, _0807123C @ =0x0002C00C
	adds r1, r1, r2
	ldr r2, [r1]
	ldr r1, [r3, #0x58]
	cmp r2, r1
	ble _08071234
	str r2, [r3, #0x58]
_08071234:
	pop {r1}
	bx r1
	.align 2, 0
_08071238: .4byte gOverworld
_0807123C: .4byte 0x0002C00C
