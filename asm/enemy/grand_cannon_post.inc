	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start slashGrandCannon
slashGrandCannon: @ 0x080696CC
	push {r4, r5, r6, lr}
	sub sp, #0x10
	adds r5, r0, #0
	ldrb r0, [r5, #0xe]
	cmp r0, #0
	beq _080696DE
	cmp r0, #1
	beq _08069792
	b _080697AA
_080696DE:
	movs r3, #0
	ldr r0, _08069700 @ =pZero2
	ldr r0, [r0]
	ldr r0, [r0, #0x54]
	ldr r1, [r5, #0x54]
	subs r0, r0, r1
	cmp r0, #0
	ble _080696F0
	movs r3, #1
_080696F0:
	adds r6, r3, #0
	adds r2, r6, #0
	cmp r6, #0
	beq _08069704
	ldrb r1, [r5, #0xa]
	movs r0, #0x10
	orrs r0, r1
	b _0806970A
	.align 2, 0
_08069700: .4byte pZero2
_08069704:
	ldrb r1, [r5, #0xa]
	movs r0, #0xef
	ands r0, r1
_0806970A:
	strb r0, [r5, #0xa]
	adds r1, r2, #0
	adds r0, r5, #0
	adds r0, #0x4c
	movs r4, #0
	strb r1, [r0]
	adds r3, r5, #0
	adds r3, #0x4a
	lsls r1, r1, #4
	ldrb r2, [r3]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r1
	strb r0, [r3]
	lsls r1, r6, #8
	ldr r0, [r5, #0x54]
	subs r0, r0, r1
	str r0, [r5, #0x54]
	ldr r1, _080697B4 @ =0x00000701
	adds r0, r5, #0
	bl SetMotion
	adds r0, r5, #0
	adds r0, #0x8c
	str r4, [r0]
	adds r0, #4
	str r4, [r0]
	adds r0, #4
	strb r4, [r0]
	ldrb r1, [r5, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r5, #0xa]
	ldr r0, [r5, #0x54]
	str r0, [sp, #8]
	ldr r0, [r5, #0x58]
	str r0, [sp, #0xc]
	movs r2, #0x80
	lsls r2, r2, #2
	movs r0, #0
	add r1, sp, #8
	adds r3, r6, #0
	bl FUN_080b2b40
	movs r1, #0x60
	lsls r0, r6, #1
	adds r0, r0, r6
	lsls r0, r0, #6
	subs r1, r1, r0
	str r1, [sp, #8]
	movs r0, #0x40
	str r0, [sp, #0xc]
	adds r1, r5, #0
	adds r1, #0x54
	ldr r0, _080697B8 @ =0x083662C2
	str r0, [sp]
	movs r4, #0x18
	str r4, [sp, #4]
	adds r0, r5, #0
	add r2, sp, #8
	movs r3, #0
	bl FUN_080b834c
	strb r4, [r5, #0x12]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_08069792:
	adds r0, r5, #0
	bl UpdateMotionGraphic
	ldrb r0, [r5, #0x12]
	subs r0, #1
	strb r0, [r5, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080697AA
	adds r0, r5, #0
	bl explodeGrandCannon
_080697AA:
	add sp, #0x10
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_080697B4: .4byte 0x00000701
_080697B8: .4byte sMotions+6
