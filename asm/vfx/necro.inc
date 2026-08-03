	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_080b8af8
FUN_080b8af8: @ 0x080B8AF8
	push {r4, r5, r6, r7, lr}
	adds r6, r0, #0
	ldr r0, [r6, #0x28]
	ldrb r0, [r0, #0xa]
	lsls r0, r0, #0x18
	lsrs r5, r0, #0x1c
	movs r1, #1
	ands r5, r1
	lsrs r4, r0, #0x1d
	ands r4, r1
	ldrb r7, [r6, #0x11]
	ldrb r0, [r6, #0xe]
	cmp r0, #0
	beq _080B8B1A
	cmp r0, #1
	beq _080B8BD8
	b _080B8C68
_080B8B1A:
	ldrb r1, [r6, #0xa]
	movs r0, #1
	movs r3, #0
	adds r2, r0, #0
	orrs r2, r1
	strb r2, [r6, #0xa]
	adds r1, r5, #0
	cmp r5, #0
	beq _080B8B32
	movs r0, #0x10
	orrs r2, r0
	b _080B8B36
_080B8B32:
	movs r0, #0xef
	ands r2, r0
_080B8B36:
	strb r2, [r6, #0xa]
	adds r0, r6, #0
	adds r0, #0x4c
	strb r1, [r0]
	adds r2, r6, #0
	adds r2, #0x4a
	lsls r1, r1, #4
	ldrb r3, [r2]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r3
	orrs r0, r1
	strb r0, [r2]
	adds r3, r4, #0
	adds r4, r2, #0
	cmp r3, #0
	beq _080B8B60
	ldrb r0, [r6, #0xa]
	movs r1, #0x20
	orrs r0, r1
	b _080B8B66
_080B8B60:
	ldrb r1, [r6, #0xa]
	movs r0, #0xdf
	ands r0, r1
_080B8B66:
	strb r0, [r6, #0xa]
	adds r1, r3, #0
	adds r2, r6, #0
	adds r2, #0x4d
	strb r1, [r2]
	lsls r1, r1, #5
	ldrb r2, [r4]
	movs r0, #0x21
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r1
	strb r0, [r4]
	ldr r1, [r6, #0x74]
	lsls r0, r7, #1
	adds r0, r0, r1
	ldrh r1, [r0]
	adds r0, r6, #0
	bl SetMotion
	cmp r5, #0
	beq _080B8B94
	movs r0, #2
	subs r7, r0, r7
_080B8B94:
	subs r1, r7, #1
	lsls r1, r1, #8
	ldr r5, _080B8BEC @ =RNG_0202f388
	ldr r0, [r5]
	ldr r4, _080B8BF0 @ =0x000343FD
	muls r0, r4, r0
	ldr r3, _080B8BF4 @ =0x00269EC3
	adds r0, r0, r3
	lsls r0, r0, #1
	lsrs r2, r0, #1
	lsls r0, r0, #6
	lsrs r0, r0, #0x17
	adds r1, r1, r0
	ldr r0, _080B8BF8 @ =0xFFFFFF00
	adds r1, r1, r0
	str r1, [r6, #0x5c]
	adds r1, r2, #0
	muls r1, r4, r1
	adds r1, r1, r3
	lsls r1, r1, #1
	lsrs r0, r1, #1
	str r0, [r5]
	lsrs r1, r1, #0x11
	movs r0, #0x80
	lsls r0, r0, #1
	ands r1, r0
	ldr r0, _080B8BFC @ =0xFFFFFE00
	subs r0, r0, r1
	str r0, [r6, #0x60]
	movs r0, #0
	strb r0, [r6, #0x12]
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_080B8BD8:
	ldrb r0, [r6, #0x12]
	adds r0, #1
	strb r0, [r6, #0x12]
	movs r1, #1
	ands r0, r1
	cmp r0, #0
	beq _080B8C00
	ldrb r0, [r6, #0xa]
	orrs r0, r1
	b _080B8C06
	.align 2, 0
_080B8BEC: .4byte RNG_0202f388
_080B8BF0: .4byte 0x000343FD
_080B8BF4: .4byte 0x00269EC3
_080B8BF8: .4byte 0xFFFFFF00
_080B8BFC: .4byte 0xFFFFFE00
_080B8C00:
	ldrb r1, [r6, #0xa]
	movs r0, #0xfe
	ands r0, r1
_080B8C06:
	strb r0, [r6, #0xa]
	ldr r0, [r6, #0x54]
	ldr r1, [r6, #0x5c]
	adds r0, r0, r1
	str r0, [r6, #0x54]
	ldr r0, [r6, #0x58]
	ldr r1, [r6, #0x60]
	adds r0, r0, r1
	str r0, [r6, #0x58]
	adds r1, #0x40
	str r1, [r6, #0x60]
	adds r0, r6, #0
	bl FUN_0801779c
	ldrb r0, [r6, #0x12]
	cmp r0, #0x18
	bls _080B8C68
	ldr r0, [r6, #0x54]
	ldr r1, [r6, #0x58]
	bl FUN_080098a4
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _080B8C68
	adds r0, r6, #0
	adds r0, #0x79
	ldrb r0, [r0]
	cmp r0, #0
	bne _080B8C4C
	adds r1, r6, #0
	adds r1, #0x54
	movs r0, #3
	bl CreateSmoke
	b _080B8C56
_080B8C4C:
	adds r1, r6, #0
	adds r1, #0x54
	movs r0, #2
	bl CreateSmoke
_080B8C56:
	ldr r1, _080B8C70 @ =gVFXFnTable
	ldrb r0, [r6, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r6, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r6, #0x14]
_080B8C68:
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080B8C70: .4byte gVFXFnTable
