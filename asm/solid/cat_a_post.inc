	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_080dd69c
FUN_080dd69c: @ 0x080DD69C
	push {r4, r5, lr}
	adds r4, r0, #0
	bl UpdateMotionGraphic
	ldrb r0, [r4, #0xd]
	cmp r0, #1
	beq _080DD744
	cmp r0, #1
	bgt _080DD6B4
	cmp r0, #0
	beq _080DD6C0
	b _080DD87E
_080DD6B4:
	cmp r0, #2
	beq _080DD7A0
	cmp r0, #3
	bne _080DD6BE
	b _080DD834
_080DD6BE:
	b _080DD87E
_080DD6C0:
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r5, [r0]
	cmp r5, #3
	beq _080DD6CC
	b _080DD87E
_080DD6CC:
	ldrb r0, [r4, #0x13]
	cmp r0, #0
	bne _080DD710
	ldr r2, _080DD700 @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _080DD704 @ =0x000343FD
	muls r0, r1, r0
	ldr r1, _080DD708 @ =0x00269EC3
	adds r0, r0, r1
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r2]
	lsrs r0, r0, #0x11
	movs r1, #1
	ands r0, r1
	cmp r0, #0
	beq _080DD710
	ldr r1, _080DD70C @ =0x0000D801
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0x13]
	adds r0, #1
	strb r0, [r4, #0x13]
	strb r5, [r4, #0xd]
	b _080DD724
	.align 2, 0
_080DD700: .4byte RNG_0202f388
_080DD704: .4byte 0x000343FD
_080DD708: .4byte 0x00269EC3
_080DD70C: .4byte 0x0000D801
_080DD710:
	movs r1, #0xd8
	lsls r1, r1, #8
	adds r0, r4, #0
	bl SetMotion
	movs r0, #0
	strb r0, [r4, #0x13]
	ldrb r0, [r4, #0xd]
	adds r0, #1
	strb r0, [r4, #0xd]
_080DD724:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldr r2, _080DD738 @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _080DD73C @ =0x000343FD
	muls r0, r1, r0
	ldr r3, _080DD740 @ =0x00269EC3
	adds r0, r0, r3
	b _080DD810
	.align 2, 0
_080DD738: .4byte RNG_0202f388
_080DD73C: .4byte 0x000343FD
_080DD740: .4byte 0x00269EC3
_080DD744:
	ldr r2, [r4, #0x54]
	adds r1, r2, #0
	adds r1, #0xc0
	str r1, [r4, #0x54]
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0xff
	beq _080DD782
	adds r0, r4, #0
	adds r0, #0xb4
	ldr r0, [r0]
	movs r3, #0x80
	lsls r3, r3, #7
	adds r0, r0, r3
	cmp r1, r0
	bgt _080DD782
	movs r1, #0xcc
	lsls r1, r1, #4
	adds r0, r2, r1
	ldr r1, [r4, #0x58]
	ldr r2, _080DD798 @ =0xFFFFF800
	adds r1, r1, r2
	bl FUN_080098a4
	lsls r0, r0, #0x10
	cmp r0, #0
	bne _080DD782
	b _080DD87E
_080DD782:
	ldr r1, _080DD79C @ =0x0000D802
	adds r0, r4, #0
	bl SetMotion
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldrb r0, [r4, #0xd]
	adds r0, #1
	b _080DD87C
	.align 2, 0
_080DD798: .4byte 0xFFFFF800
_080DD79C: .4byte 0x0000D802
_080DD7A0:
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _080DD87E
	ldrb r0, [r4, #0x13]
	cmp r0, #0
	bne _080DD7EC
	ldr r2, _080DD7E0 @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _080DD7E4 @ =0x000343FD
	muls r0, r1, r0
	ldr r3, _080DD7E8 @ =0x00269EC3
	adds r0, r0, r3
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r2]
	lsrs r0, r0, #0x11
	movs r5, #1
	ands r0, r5
	cmp r0, #0
	beq _080DD7EC
	movs r1, #0xd8
	lsls r1, r1, #8
	adds r0, r4, #0
	bl SetMotion
	strb r5, [r4, #0xd]
	ldrb r0, [r4, #0x13]
	adds r0, #1
	strb r0, [r4, #0x13]
	b _080DD7FE
	.align 2, 0
_080DD7E0: .4byte RNG_0202f388
_080DD7E4: .4byte 0x000343FD
_080DD7E8: .4byte 0x00269EC3
_080DD7EC:
	ldr r1, _080DD824 @ =0x0000D801
	adds r0, r4, #0
	bl SetMotion
	movs r0, #0
	strb r0, [r4, #0x13]
	ldrb r0, [r4, #0xd]
	adds r0, #1
	strb r0, [r4, #0xd]
_080DD7FE:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldr r2, _080DD828 @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _080DD82C @ =0x000343FD
	muls r0, r1, r0
	ldr r1, _080DD830 @ =0x00269EC3
	adds r0, r0, r1
_080DD810:
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r2]
	lsrs r0, r0, #0x11
	movs r1, #0x3f
	ands r0, r1
	adds r0, #0x28
	strb r0, [r4, #0x12]
	b _080DD87E
	.align 2, 0
_080DD824: .4byte 0x0000D801
_080DD828: .4byte RNG_0202f388
_080DD82C: .4byte 0x000343FD
_080DD830: .4byte 0x00269EC3
_080DD834:
	ldr r2, [r4, #0x54]
	adds r1, r2, #0
	subs r1, #0xc0
	str r1, [r4, #0x54]
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0xff
	beq _080DD86C
	adds r0, r4, #0
	adds r0, #0xb4
	ldr r0, [r0]
	ldr r3, _080DD884 @ =0xFFFFC000
	adds r0, r0, r3
	cmp r1, r0
	blt _080DD86C
	ldr r1, _080DD888 @ =0xFFFFF340
	adds r0, r2, r1
	ldr r1, [r4, #0x58]
	ldr r2, _080DD88C @ =0xFFFFF800
	adds r1, r1, r2
	bl FUN_080098a4
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _080DD87E
_080DD86C:
	ldr r1, _080DD890 @ =0x0000D803
	adds r0, r4, #0
	bl SetMotion
	adds r0, r4, #0
	bl UpdateMotionGraphic
	movs r0, #0
_080DD87C:
	strb r0, [r4, #0xd]
_080DD87E:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080DD884: .4byte 0xFFFFC000
_080DD888: .4byte 0xFFFFF340
_080DD88C: .4byte 0xFFFFF800
_080DD890: .4byte 0x0000D803
