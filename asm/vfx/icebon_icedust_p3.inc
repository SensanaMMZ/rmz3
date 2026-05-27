	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start ice_080b996c
ice_080b996c: @ 0x080B996C
	push {r4, r5, r6, lr}
	adds r5, r0, #0
	ldrb r0, [r5, #0xe]
	cmp r0, #0
	beq _080B997C
	cmp r0, #1
	beq _080B99BA
	b _080B99EC
_080B997C:
	ldr r1, _080B99F4 @ =0x00001109
	adds r0, r5, #0
	bl SetMotion
	ldr r4, _080B99F8 @ =RNG_0202f388
	ldr r0, [r4]
	ldr r3, _080B99FC @ =0x000343FD
	muls r0, r3, r0
	ldr r2, _080B9A00 @ =0x00269EC3
	adds r0, r0, r2
	lsls r0, r0, #1
	lsrs r1, r0, #1
	lsls r0, r0, #6
	lsrs r0, r0, #0x17
	ldr r6, _080B9A04 @ =0xFFFFFF00
	adds r0, r0, r6
	str r0, [r5, #0x5c]
	adds r0, r1, #0
	muls r0, r3, r0
	adds r0, r0, r2
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r4]
	lsrs r0, r0, #0x11
	movs r1, #0x7f
	ands r0, r1
	adds r0, #0x80
	str r0, [r5, #0x60]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_080B99BA:
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x5c]
	adds r0, r0, r1
	str r0, [r5, #0x54]
	ldr r0, [r5, #0x58]
	ldr r1, [r5, #0x60]
	adds r0, r0, r1
	str r0, [r5, #0x58]
	adds r0, r5, #0
	bl UpdateMotionGraphic
	adds r0, r5, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _080B99EC
	ldr r1, _080B9A08 @ =gVFXFnTable
	ldrb r0, [r5, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r5, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r5, #0x14]
_080B99EC:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_080B99F4: .4byte 0x00001109
_080B99F8: .4byte RNG_0202f388
_080B99FC: .4byte 0x000343FD
_080B9A00: .4byte 0x00269EC3
_080B9A04: .4byte 0xFFFFFF00
_080B9A08: .4byte gVFXFnTable

	thumb_func_start ice_080b9a0c
ice_080b9a0c: @ 0x080B9A0C
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _080B9A1C
	cmp r0, #1
	beq _080B9A2A
	b _080B9A4C
_080B9A1C:
	ldr r1, _080B9A54 @ =0x00001109
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080B9A2A:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _080B9A4C
	ldr r1, _080B9A58 @ =gVFXFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r4, #0x14]
_080B9A4C:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080B9A54: .4byte 0x00001109
_080B9A58: .4byte gVFXFnTable
