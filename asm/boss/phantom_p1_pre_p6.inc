	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_0805f350
FUN_0805f350: @ 0x0805F350
	push {r4, lr}
	adds r4, r0, #0
	adds r0, #0x74
	ldr r1, _0805F390 @ =sCollisions
	bl SetDDP
	movs r2, #0xc0
	lsls r2, r2, #2
	str r2, [r4, #0x5c]
	adds r0, r4, #0
	adds r0, #0xcb
	ldrb r1, [r0]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #9
	subs r2, r2, r0
	str r2, [r4, #0x5c]
	ldrb r1, [r4, #0xa]
	movs r0, #1
	orrs r0, r1
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	movs r1, #0x11
	bl FUN_080607a0
	movs r0, #0x1e
	strb r0, [r4, #0x12]
	movs r0, #1
	strb r0, [r4, #0xf]
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_0805F390: .4byte sCollisions

	thumb_func_start FUN_0805f394
FUN_0805f394: @ 0x0805F394
	push {r4, r5, lr}
	adds r4, r0, #0
	ldr r1, [r4, #0x5c]
	bl FUN_08060864
	ldr r1, [r4, #0x5c]
	movs r0, #0xe6
	muls r0, r1, r0
	cmp r0, #0
	bge _0805F3AA
	adds r0, #0xff
_0805F3AA:
	asrs r0, r0, #8
	str r0, [r4, #0x5c]
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	lsrs r5, r0, #0x18
	cmp r5, #0
	bne _0805F3C8
	adds r0, r4, #0
	movs r1, #0x12
	bl FUN_080607a0
	strb r5, [r4, #0xd]
	strh r5, [r4, #0xe]
_0805F3C8:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
