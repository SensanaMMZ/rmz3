	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_0805f464
FUN_0805f464: @ 0x0805F464
	push {r4, lr}
	adds r4, r0, #0
	bl FUN_08060924
	ldr r0, [r4, #0x60]
	cmp r0, #0
	ble _0805F482
	movs r0, #4
	strh r0, [r4, #0xe]
	adds r0, r4, #0
	movs r1, #8
	bl FUN_080607a0
	movs r0, #0
	strb r0, [r4, #0x12]
_0805F482:
	pop {r4}
	pop {r0}
	bx r0
