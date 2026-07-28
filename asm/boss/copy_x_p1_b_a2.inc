	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start copyx_08056794
copyx_08056794: @ 0x08056794
	push {r4, r5, r6, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _08056862
	ldr r1, _080567B8 @ =0x0000B317
	adds r0, r4, #0
	bl SetMotion
	movs r0, #0
	strb r0, [r4, #0xe]
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _080567C0
	ldr r0, _080567BC @ =0xFFFFFE00
	b _080567C4
	.align 2, 0
_080567B8: .4byte 0x0000B317
_080567BC: .4byte 0xFFFFFE00
_080567C0:
	movs r0, #0x80
	lsls r0, r0, #2
_080567C4:
	str r0, [r4, #0x5c]
	ldr r0, _080567F4 @ =0xFFFFFE00
	str r0, [r4, #0x60]
	adds r5, r4, #0
	adds r5, #0xc6
	ldrb r6, [r5]
	cmp r6, #0
	beq _080567F8
	adds r0, r4, #0
	movs r1, #3
	movs r2, #0
	bl FUN_080a83e4
	movs r1, #0
	strb r1, [r5]
	movs r0, #0xc
	strb r0, [r4, #0x12]
	adds r0, r4, #0
	adds r0, #0xc7
	strb r1, [r0]
	movs r0, #0x46
	bl PlaySound
	b _08056862
	.align 2, 0
_080567F4: .4byte 0xFFFFFE00
_080567F8:
	adds r0, r4, #0
	adds r0, #0xc5
	ldrb r0, [r0]
	cmp r0, #1
	beq _08056822
	cmp r0, #1
	bgt _0805680C
	cmp r0, #0
	beq _08056816
	b _08056862
_0805680C:
	cmp r0, #2
	beq _0805683A
	cmp r0, #3
	beq _08056848
	b _08056862
_08056816:
	adds r0, r4, #0
	movs r1, #2
	movs r2, #0
	bl FUN_080a83e4
	b _08056852
_08056822:
	adds r0, r4, #0
	movs r1, #1
	movs r2, #6
	bl FUN_080a88a4
	movs r0, #0xc
	strb r0, [r4, #0x12]
	adds r1, r4, #0
	adds r1, #0xc7
	movs r0, #6
	strb r0, [r1]
	b _08056862
_0805683A:
	adds r0, r4, #0
	movs r1, #1
	movs r2, #0
	bl FUN_080a9048
	movs r0, #0x49
	b _08056854
_08056848:
	adds r0, r4, #0
	movs r1, #4
	movs r2, #0
	bl FUN_080a9048
_08056852:
	movs r0, #0x46
_08056854:
	bl PlaySound
	movs r0, #6
	strb r0, [r4, #0x12]
	adds r0, r4, #0
	adds r0, #0xc7
	strb r6, [r0]
_08056862:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r1, r4, #0
	adds r1, #0xc7
	ldrb r0, [r1]
	cmp r0, #0
	beq _08056878
	subs r0, #1
	strb r0, [r1]
	b _080568B4
_08056878:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	ldr r0, [r4, #0x58]
	ldr r1, [r4, #0x60]
	adds r0, r0, r1
	str r0, [r4, #0x58]
	adds r1, #0x40
	str r1, [r4, #0x60]
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	movs r1, #0xff
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0xff
	bne _080568B4
	ldrb r0, [r4, #0x13]
	subs r0, #1
	strb r0, [r4, #0x13]
	ands r0, r1
	cmp r0, #0
	bne _080568AC
	movs r0, #0x19
	b _080568AE
_080568AC:
	movs r0, #0x17
_080568AE:
	strb r0, [r4, #0xd]
	movs r0, #1
	strb r0, [r4, #0xe]
_080568B4:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
