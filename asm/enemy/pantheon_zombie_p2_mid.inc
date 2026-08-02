	.include "asm/macros.inc"

	.syntax unified
	
	.text

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
