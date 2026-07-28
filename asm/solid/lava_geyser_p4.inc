	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080cca14
FUN_080cca14: @ 0x080CCA14
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r5, [r4, #0xe]
	cmp r5, #0
	beq _080CCA24
	cmp r5, #1
	beq _080CCA58
	b _080CCAC2
_080CCA24:
	movs r0, #0x77
	bl PlaySound
	ldr r0, [r4, #0x54]
	str r0, [r4, #0x64]
	str r5, [r4, #0x60]
	ldrb r0, [r4, #0x10]
	lsrs r5, r0, #2
	lsls r0, r5, #1
	adds r0, r0, r5
	lsls r0, r0, #0xb
	ldr r1, _080CCAC8 @ =0xFFFF4000
	adds r0, r0, r1
	str r0, [r4, #0x68]
	lsls r2, r5, #2
	movs r1, #0x18
	subs r1, r1, r2
	adds r2, r1, #0
	muls r2, r1, r2
	adds r1, r2, #0
	bl __divsi3
	str r0, [r4, #0x68]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080CCA58:
	ldrb r0, [r4, #0x10]
	lsrs r5, r0, #2
	adds r0, r4, #0
	adds r0, #0xc0
	ldr r2, [r0]
	ldr r0, _080CCACC @ =0xFFFFFE00
	adds r2, r2, r0
	ldr r3, _080CCAD0 @ =RNG_0202f388
	ldr r1, [r3]
	ldr r0, _080CCAD4 @ =0x000343FD
	muls r0, r1, r0
	ldr r1, _080CCAD8 @ =0x00269EC3
	adds r0, r0, r1
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r3]
	lsls r0, r0, #5
	lsrs r0, r0, #0x16
	adds r2, r2, r0
	str r2, [r4, #0x54]
	ldr r2, [r4, #0x58]
	ldr r0, [r4, #0x60]
	adds r2, r2, r0
	str r2, [r4, #0x58]
	ldr r1, [r4, #0x68]
	adds r0, r0, r1
	str r0, [r4, #0x60]
	adds r3, r4, #0
	adds r3, #0xb8
	ldr r1, [r3]
	subs r1, r1, r2
	lsls r0, r5, #1
	adds r0, r0, r5
	lsls r2, r0, #0xb
	movs r0, #0xc0
	lsls r0, r0, #7
	subs r0, r0, r2
	cmp r1, r0
	ble _080CCABC
	ldr r0, [r4, #0x64]
	str r0, [r4, #0x54]
	ldr r0, [r3]
	ldr r1, _080CCADC @ =0xFFFFA000
	adds r0, r0, r1
	adds r0, r0, r2
	str r0, [r4, #0x58]
	movs r1, #0
	movs r0, #2
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_080CCABC:
	adds r0, r4, #0
	bl UpdateMotionGraphic
_080CCAC2:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080CCAC8: .4byte 0xFFFF4000
_080CCACC: .4byte 0xFFFFFE00
_080CCAD0: .4byte RNG_0202f388
_080CCAD4: .4byte 0x000343FD
_080CCAD8: .4byte 0x00269EC3
_080CCADC: .4byte 0xFFFFA000

