	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080bc974
FUN_080bc974: @ 0x080BC974
	push {r4, r5, lr}
	adds r5, r0, #0
	ldrb r0, [r5, #0xe]
	cmp r0, #0
	beq _080BC984
	cmp r0, #1
	beq _080BC9C4
	b _080BCA50
_080BC984:
	adds r1, r5, #0
	adds r1, #0x25
	movs r0, #0x19
	strb r0, [r1]
	ldrb r0, [r5, #0x12]
	subs r1, #3
	strb r0, [r1]
	ldr r4, _080BCA00 @ =0x0836EDF8
	ldr r2, _080BCA04 @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _080BCA08 @ =0x000343FD
	muls r0, r1, r0
	ldr r1, _080BCA0C @ =0x00269EC3
	adds r0, r0, r1
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r2]
	lsrs r0, r0, #0x11
	movs r1, #3
	bl __umodsi3
	lsls r0, r0, #1
	adds r0, r0, r4
	ldrh r1, [r0]
	adds r0, r5, #0
	bl SetMotion
	movs r0, #0x28
	strb r0, [r5, #0x12]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_080BC9C4:
	adds r0, r5, #0
	bl UpdateMotionGraphic
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x5c]
	adds r0, r0, r1
	str r0, [r5, #0x54]
	ldr r1, [r5, #0x60]
	adds r1, #0xc
	str r1, [r5, #0x60]
	ldr r0, [r5, #0x58]
	adds r0, r0, r1
	str r0, [r5, #0x58]
	ldrb r0, [r5, #0x12]
	subs r1, r0, #1
	movs r2, #0
	strb r1, [r5, #0x12]
	lsls r0, r1, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #7
	bhi _080BCA10
	movs r0, #2
	ands r1, r0
	cmp r1, #0
	bne _080BCA24
	ldrb r0, [r5, #0xa]
	movs r1, #1
	orrs r0, r1
	b _080BCA2A
	.align 2, 0
_080BCA00: .4byte 0x0836EDF8
_080BCA04: .4byte RNG_0202f388
_080BCA08: .4byte 0x000343FD
_080BCA0C: .4byte 0x00269EC3
_080BCA10:
	cmp r0, #0xf
	bhi _080BCA2C
	movs r0, #1
	ands r1, r0
	cmp r1, #0
	bne _080BCA24
	ldrb r0, [r5, #0xa]
	movs r1, #1
	orrs r0, r1
	b _080BCA2A
_080BCA24:
	ldrb r1, [r5, #0xa]
	movs r0, #0xfe
	ands r0, r1
_080BCA2A:
	strb r0, [r5, #0xa]
_080BCA2C:
	ldrb r0, [r5, #0x12]
	cmp r0, #0
	bne _080BCA50
	ldrb r1, [r5, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r5, #0xa]
	ldr r1, _080BCA58 @ =gVFXFnTable
	ldrb r0, [r5, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r5, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r5, #0x14]
_080BCA50:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080BCA58: .4byte gVFXFnTable
