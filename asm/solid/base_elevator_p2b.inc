	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080d0224
FUN_080d0224: @ 0x080D0224
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	bne _080D024C
	adds r5, r4, #0
	adds r5, #0xbe
	movs r0, #0
	ldrsh r1, [r5, r0]
	movs r0, #1
	rsbs r0, r0, #0
	cmp r1, r0
	bne _080D0246
	movs r0, #0xa0
	bl PlaySound
	strh r0, [r5]
_080D0246:
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080D024C:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldr r0, [r4, #0x58]
	ldr r1, [r4, #0x60]
	adds r5, r0, r1
	str r5, [r4, #0x58]
	cmp r1, #0
	ble _080D0276
	adds r2, r4, #0
	adds r2, #0xb8
	ldrb r0, [r4, #0x11]
	adds r3, r0, #1
	lsls r1, r3, #2
	adds r1, r1, r3
	lsls r1, r1, #0xd
	ldr r0, [r2]
	adds r0, r0, r1
	cmp r5, r0
	blt _080D0294
	b _080D028C
_080D0276:
	adds r2, r4, #0
	adds r2, #0xb8
	ldrb r0, [r4, #0x11]
	subs r3, r0, #1
	lsls r1, r3, #2
	adds r1, r1, r3
	lsls r1, r1, #0xd
	ldr r0, [r2]
	adds r0, r0, r1
	cmp r5, r0
	bgt _080D0294
_080D028C:
	movs r0, #0
	strb r3, [r4, #0x11]
	strb r0, [r4, #0xd]
	strb r0, [r4, #0xe]
_080D0294:
	ldr r2, _080D02C8 @ =gOverworld
	ldr r0, _080D02CC @ =0x0002C014
	adds r1, r2, r0
	movs r0, #0xc7
	lsls r0, r0, #0xb
	str r0, [r1]
	ldr r0, _080D02D0 @ =0x0002C01C
	adds r1, r2, r0
	movs r0, #0xcd
	lsls r0, r0, #0xb
	str r0, [r1]
	ldr r1, _080D02D4 @ =0x0002C018
	adds r3, r2, r1
	ldr r0, [r4, #0x58]
	ldr r4, _080D02D8 @ =0xFFFFC000
	adds r1, r0, r4
	str r1, [r3]
	ldr r1, _080D02DC @ =0x0002C020
	adds r2, r2, r1
	movs r4, #0x80
	lsls r4, r4, #3
	adds r0, r0, r4
	str r0, [r2]
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080D02C8: .4byte gOverworld
_080D02CC: .4byte 0x0002C014
_080D02D0: .4byte 0x0002C01C
_080D02D4: .4byte 0x0002C018
_080D02D8: .4byte 0xFFFFC000
_080D02DC: .4byte 0x0002C020
