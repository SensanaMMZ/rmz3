	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080892c4
FUN_080892c4: @ 0x080892C4
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _080892D4
	cmp r0, #1
	beq _080892F2
	b _08089358
_080892D4:
	str r0, [r4, #0x5c]
	movs r0, #0x3c
	strb r0, [r4, #0x12]
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _08089300 @ =0x08368814
	bl SetDDP
	ldr r1, _08089304 @ =0x0000DD02
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080892F2:
	ldrb r0, [r4, #0x12]
	cmp r0, #0
	beq _08089308
	subs r0, #1
	strb r0, [r4, #0x12]
	ldr r3, [r4, #0x54]
	b _08089338
	.align 2, 0
_08089300: .4byte 0x08368814
_08089304: .4byte 0x0000DD02
_08089308:
	ldr r0, _08089320 @ =pZero2
	ldr r0, [r0]
	ldr r2, [r0, #0x54]
	ldr r0, [r4, #0x54]
	subs r1, r2, r0
	adds r3, r0, #0
	cmp r1, #0
	blt _08089328
	ldr r0, _08089324 @ =0x00005FFF
	cmp r1, r0
	ble _08089330
	b _08089338
	.align 2, 0
_08089320: .4byte pZero2
_08089324: .4byte 0x00005FFF
_08089328:
	subs r1, r3, r2
	ldr r0, _08089360 @ =0x00005FFF
	cmp r1, r0
	bgt _08089338
_08089330:
	movs r1, #0
	movs r0, #1
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_08089338:
	ldr r1, [r4, #0x58]
	movs r0, #0x80
	lsls r0, r0, #3
	adds r1, r1, r0
	adds r0, r3, #0
	bl FUN_0800a40c
	adds r1, r0, #0
	movs r2, #0x80
	lsls r2, r2, #4
	adds r0, r4, #0
	bl FUN_08088bc8
	adds r0, r4, #0
	bl UpdateMotionGraphic
_08089358:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_08089360: .4byte 0x00005FFF

