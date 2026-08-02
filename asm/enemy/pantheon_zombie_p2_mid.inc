	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_08080324
FUN_08080324: @ 0x08080324
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r5, [r4, #0xe]
	cmp r5, #1
	beq _08080364
	cmp r5, #1
	bgt _08080338
	cmp r5, #0
	beq _08080342
	b _080803D0
_08080338:
	cmp r5, #2
	beq _080803A4
	cmp r5, #3
	beq _080803B6
	b _080803D0
_08080342:
	ldrb r1, [r4, #0xa]
	movs r0, #1
	orrs r0, r1
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _0808039C @ =0x08367EE8
	bl SetDDP
	str r5, [r4, #0x60]
	ldr r1, _080803A0 @ =0x00004C02
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08080364:
	ldr r0, [r4, #0x60]
	adds r0, #0x40
	str r0, [r4, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _08080374
	str r1, [r4, #0x60]
_08080374:
	ldr r1, [r4, #0x58]
	ldr r0, [r4, #0x60]
	adds r1, r1, r0
	str r1, [r4, #0x58]
	ldr r0, [r4, #0x54]
	bl PushoutToUp1
	adds r1, r0, #0
	cmp r1, #0
	bge _08080394
	ldr r0, [r4, #0x58]
	adds r0, r0, r1
	str r0, [r4, #0x58]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08080394:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	b _080803D0
	.align 2, 0
_0808039C: .4byte 0x08367EE8
_080803A0: .4byte 0x00004C02
_080803A4:
	ldr r1, _080803D8 @ =0x00004C04
	adds r0, r4, #0
	bl SetMotion
	movs r0, #0x10
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080803B6:
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	lsrs r1, r0, #0x18
	cmp r1, #0
	bne _080803CA
	movs r0, #1
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_080803CA:
	adds r0, r4, #0
	bl UpdateMotionGraphic
_080803D0:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080803D8: .4byte 0x00004C04

	thumb_func_start FUN_080803dc
FUN_080803dc: @ 0x080803DC
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r5, [r4, #0xe]
	cmp r5, #0
	beq _080803EC
	cmp r5, #1
	beq _08080468
	b _08080494
_080803EC:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _0808042C @ =0x08367F48
	bl SetDDP
	adds r1, r4, #0
	adds r1, #0x25
	movs r0, #0xf
	strb r0, [r1]
	ldr r0, _08080430 @ =pZero2
	ldr r0, [r0]
	ldr r1, [r4, #0x54]
	ldr r0, [r0, #0x54]
	cmp r1, r0
	ble _08080434
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	adds r0, #0x4c
	strb r5, [r0]
	adds r2, r4, #0
	adds r2, #0x4a
	ldrb r1, [r2]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r2]
	movs r0, #0x80
	lsls r0, r0, #4
	b _08080458
	.align 2, 0
_0808042C: .4byte 0x08367F48
_08080430: .4byte pZero2
_08080434:
	movs r2, #1
	ldrb r0, [r4, #0xa]
	movs r1, #0x10
	orrs r0, r1
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	adds r0, #0x4c
	strb r2, [r0]
	adds r3, r4, #0
	adds r3, #0x4a
	movs r2, #0x10
	ldrb r1, [r3]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	orrs r0, r2
	strb r0, [r3]
	ldr r0, _0808049C @ =0xFFFFF800
_08080458:
	str r0, [r4, #0x64]
	ldr r1, _080804A0 @ =0x00004C03
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08080468:
	adds r0, r4, #0
	adds r0, #0xb8
	ldrb r0, [r0]
	cmp r0, #0
	beq _08080478
	ldr r0, [r4, #0x58]
	adds r0, #0x20
	str r0, [r4, #0x58]
_08080478:
	ldr r0, _080804A4 @ =pZero2
	ldr r2, [r0]
	ldr r0, [r2, #0x54]
	ldr r1, [r4, #0x64]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	ldr r0, [r2, #0x58]
	ldr r1, [r4, #0x58]
	cmp r0, r1
	ble _0808048E
	str r1, [r2, #0x58]
_0808048E:
	adds r0, r4, #0
	bl UpdateMotionGraphic
_08080494:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_0808049C: .4byte 0xFFFFF800
_080804A0: .4byte 0x00004C03
_080804A4: .4byte pZero2
