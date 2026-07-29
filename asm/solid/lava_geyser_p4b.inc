	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080ccb50
FUN_080ccb50: @ 0x080CCB50
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r5, [r4, #0xe]
	cmp r5, #0
	beq _080CCB60
	cmp r5, #1
	beq _080CCBAA
	b _080CCBFA
_080CCB60:
	ldrb r1, [r4, #0xb]
	movs r0, #8
	orrs r0, r1
	strb r0, [r4, #0xb]
	ldr r0, _080CCC00 @ =0x0836FFDC
	str r0, [r4, #0x30]
	ldr r0, _080CCC04 @ =0x00000811
	strh r0, [r4, #0x26]
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _080CCC08 @ =0x0836FFAC
	bl SetDDP
	ldr r0, [r4, #0x54]
	str r0, [r4, #0x64]
	str r5, [r4, #0x60]
	ldrb r2, [r4, #0x10]
	lsrs r2, r2, #2
	movs r0, #0xc0
	lsls r0, r0, #8
	lsls r1, r2, #1
	adds r1, r1, r2
	lsls r2, r1, #3
	lsls r1, r1, #0xb
	subs r0, r0, r1
	str r0, [r4, #0x68]
	movs r1, #0x64
	subs r1, r1, r2
	adds r2, r1, #0
	muls r2, r1, r2
	adds r1, r2, #0
	bl __divsi3
	str r0, [r4, #0x68]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080CCBAA:
	adds r0, r4, #0
	adds r0, #0xc0
	ldr r2, [r0]
	ldr r0, _080CCC0C @ =0xFFFFFE00
	adds r2, r2, r0
	ldr r3, _080CCC10 @ =RNG_0202f388
	ldr r1, [r3]
	ldr r0, _080CCC14 @ =0x000343FD
	muls r0, r1, r0
	ldr r1, _080CCC18 @ =0x00269EC3
	adds r0, r0, r1
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r3]
	lsls r0, r0, #6
	lsrs r0, r0, #0x17
	adds r2, r2, r0
	str r2, [r4, #0x54]
	ldr r2, [r4, #0x58]
	ldr r0, [r4, #0x60]
	adds r2, r2, r0
	str r2, [r4, #0x58]
	ldr r1, [r4, #0x68]
	adds r0, r0, r1
	str r0, [r4, #0x60]
	adds r1, r4, #0
	adds r1, #0xb8
	ldr r0, [r1]
	cmp r2, r0
	ble _080CCBF4
	ldr r0, [r4, #0x64]
	str r0, [r4, #0x54]
	ldr r0, [r1]
	str r0, [r4, #0x58]
	movs r0, #0
	strb r0, [r4, #0xd]
	strb r0, [r4, #0xe]
_080CCBF4:
	adds r0, r4, #0
	bl UpdateMotionGraphic
_080CCBFA:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080CCC00: .4byte 0x0836FFDC
_080CCC04: .4byte 0x00000811
_080CCC08: .4byte 0x0836FFAC
_080CCC0C: .4byte 0xFFFFFE00
_080CCC10: .4byte RNG_0202f388
_080CCC14: .4byte 0x000343FD
_080CCC18: .4byte 0x00269EC3

