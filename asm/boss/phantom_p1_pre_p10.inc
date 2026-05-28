	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_0805f6c8
FUN_0805f6c8: @ 0x0805F6C8
	push {lr}
	adds r1, r0, #0
	adds r0, #0x72
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	cmp r0, #1
	bgt _0805F6DC
	movs r0, #1
	strb r0, [r1, #0xf]
_0805F6DC:
	pop {r0}
	bx r0

	thumb_func_start FUN_0805f6e0
FUN_0805f6e0: @ 0x0805F6E0
	push {lr}
	adds r1, r0, #0
	ldr r0, [r1, #0x2c]
	ldrb r0, [r0, #0xd]
	cmp r0, #1
	bne _0805F6F8
	movs r0, #2
	strb r0, [r1, #0xf]
	adds r0, r1, #0
	movs r1, #6
	bl FUN_080607a0
_0805F6F8:
	pop {r0}
	bx r0

	thumb_func_start FUN_0805f6fc
FUN_0805f6fc: @ 0x0805F6FC
	push {r4, lr}
	adds r4, r0, #0
	adds r0, #0x72
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	cmp r0, #1
	bgt _0805F716
	movs r0, #0xfc
	bl PlaySound
	movs r0, #3
	strb r0, [r4, #0xf]
_0805F716:
	pop {r4}
	pop {r0}
	bx r0

	thumb_func_start FUN_0805f71c
FUN_0805f71c: @ 0x0805F71C
	push {lr}
	adds r1, r0, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _0805F734
	movs r0, #2
	strh r0, [r1, #0xe]
	adds r0, r1, #0
	movs r1, #0
	bl FUN_080607a0
_0805F734:
	pop {r0}
	bx r0

	thumb_func_start FUN_0805f738
FUN_0805f738: @ 0x0805F738
	push {r4, lr}
	adds r4, r0, #0
	bl FUN_080609a4
	lsls r0, r0, #0x18
	asrs r1, r0, #0x18
	cmp r1, #0
	ble _0805F764
	movs r0, #3
	strh r0, [r4, #0xe]
	adds r0, r4, #0
	adds r0, #0xb7
	strb r1, [r0]
	adds r1, #0x12
	lsls r1, r1, #0x18
	asrs r1, r1, #0x18
	adds r0, r4, #0
	bl FUN_08060a48
	adds r0, r4, #0
	bl FUN_0805f76c
_0805F764:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
