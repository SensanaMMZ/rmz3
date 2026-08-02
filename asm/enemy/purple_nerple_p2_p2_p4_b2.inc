	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_08076be4
FUN_08076be4: @ 0x08076BE4
	push {r4, r5, r6, lr}
	sub sp, #0x10
	adds r5, r0, #0
	ldrb r0, [r5, #0xe]
	cmp r0, #0
	beq _08076BF6
	cmp r0, #1
	beq _08076CDC
	b _08076D22
_08076BF6:
	movs r3, #0
	ldr r0, _08076C18 @ =pZero2
	ldr r0, [r0]
	ldr r0, [r0, #0x54]
	ldr r1, [r5, #0x54]
	subs r0, r0, r1
	cmp r0, #0
	ble _08076C08
	movs r3, #1
_08076C08:
	adds r6, r3, #0
	adds r2, r6, #0
	cmp r6, #0
	beq _08076C1C
	ldrb r1, [r5, #0xa]
	movs r0, #0x10
	orrs r0, r1
	b _08076C22
	.align 2, 0
_08076C18: .4byte pZero2
_08076C1C:
	ldrb r1, [r5, #0xa]
	movs r0, #0xef
	ands r0, r1
_08076C22:
	strb r0, [r5, #0xa]
	adds r1, r2, #0
	adds r0, r5, #0
	adds r0, #0x4c
	movs r4, #0
	strb r1, [r0]
	adds r3, r5, #0
	adds r3, #0x4a
	lsls r1, r1, #4
	ldrb r2, [r3]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r1
	strb r0, [r3]
	lsls r1, r6, #8
	ldr r0, [r5, #0x54]
	subs r0, r0, r1
	str r0, [r5, #0x54]
	ldr r1, _08076CB0 @ =0x00002A0C
	adds r0, r5, #0
	bl SetMotion
	adds r0, r5, #0
	adds r0, #0x8c
	str r4, [r0]
	adds r0, #4
	str r4, [r0]
	adds r0, #4
	strb r4, [r0]
	ldrb r1, [r5, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r5, #0xa]
	ldr r0, [r5, #0x54]
	str r0, [sp, #8]
	ldr r0, [r5, #0x58]
	str r0, [sp, #0xc]
	movs r2, #0x80
	lsls r2, r2, #2
	movs r0, #0
	add r1, sp, #8
	adds r3, r6, #0
	bl FUN_080b2b40
	movs r1, #0x60
	lsls r0, r6, #1
	adds r0, r0, r6
	lsls r0, r0, #6
	subs r0, r1, r0
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	asrs r0, r0, #1
	str r0, [r5, #0x5c]
	adds r0, r5, #0
	adds r0, #0xb9
	ldrb r0, [r0]
	cmp r0, #0
	beq _08076CB8
	adds r1, r5, #0
	adds r1, #0x54
	ldr r0, _08076CB4 @ =0x083671F2
	str r0, [sp]
	movs r0, #0x18
	str r0, [sp, #4]
	adds r0, r5, #0
	add r2, sp, #8
	movs r3, #0x40
	bl FUN_080b857c
	b _08076CCE
	.align 2, 0
_08076CB0: .4byte 0x00002A0C
_08076CB4: .4byte 0x083671F2
_08076CB8:
	adds r1, r5, #0
	adds r1, #0x54
	ldr r0, _08076D2C @ =0x083671F2
	str r0, [sp]
	movs r0, #0x18
	str r0, [sp, #4]
	adds r0, r5, #0
	add r2, sp, #8
	movs r3, #0x40
	bl FUN_080b84f4
_08076CCE:
	movs r1, #0
	movs r0, #0x18
	strb r0, [r5, #0x12]
	str r1, [r5, #0x60]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_08076CDC:
	ldr r0, [r5, #0x60]
	adds r0, #0x20
	str r0, [r5, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _08076CEC
	str r1, [r5, #0x60]
_08076CEC:
	ldr r0, [r5, #0x58]
	ldr r1, [r5, #0x60]
	adds r0, r0, r1
	str r0, [r5, #0x58]
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x5c]
	adds r0, r0, r1
	str r0, [r5, #0x54]
	adds r0, r5, #0
	bl UpdateMotionGraphic
	ldrb r0, [r5, #0x12]
	subs r0, #1
	strb r0, [r5, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _08076D1C
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x58]
	bl FUN_080098a4
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _08076D22
_08076D1C:
	adds r0, r5, #0
	bl FUN_08076b30
_08076D22:
	add sp, #0x10
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_08076D2C: .4byte 0x083671F2
