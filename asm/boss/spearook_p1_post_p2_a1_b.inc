	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_08062588
FUN_08062588: @ 0x08062588
	push {r4, r5, r6, r7, lr}
	adds r5, r0, #0
	ldr r6, [r5, #0x28]
	ldr r7, [r5, #0x2c]
	ldrb r4, [r5, #0xe]
	cmp r4, #0
	beq _0806259C
	cmp r4, #1
	beq _080625B0
	b _0806266E
_0806259C:
	ldr r1, _080625F0 @ =0x0000D60D
	adds r0, r5, #0
	bl SetMotion
	strb r4, [r5, #0x12]
	movs r0, #1
	strb r0, [r5, #0x13]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_080625B0:
	ldrb r0, [r5, #0x12]
	cmp r0, #0
	bne _080625F8
	ldrb r0, [r5, #0x13]
	cmp r0, #0
	bne _080625D2
	adds r0, r5, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _080625D2
	ldr r1, _080625F0 @ =0x0000D60D
	adds r0, r5, #0
	bl SetMotion
	movs r0, #1
	strb r0, [r5, #0x13]
_080625D2:
	adds r0, r6, #0
	adds r0, #0xbc
	ldr r1, [r0]
	movs r2, #2
	ands r1, r2
	adds r6, r0, #0
	cmp r1, #0
	beq _08062614
	ldr r1, _080625F4 @ =0x0000D60E
	adds r0, r5, #0
	bl SetMotion
	movs r0, #1
	strb r0, [r5, #0x12]
	b _08062614
	.align 2, 0
_080625F0: .4byte 0x0000D60D
_080625F4: .4byte 0x0000D60E
_080625F8:
	adds r1, r6, #0
	adds r1, #0xbc
	ldr r4, [r1]
	movs r0, #2
	ands r4, r0
	adds r6, r1, #0
	cmp r4, #0
	bne _08062614
	ldr r1, _08062674 @ =0x0000D60F
	adds r0, r5, #0
	bl SetMotion
	strb r4, [r5, #0x12]
	strb r4, [r5, #0x13]
_08062614:
	adds r0, r5, #0
	bl UpdateMotionGraphic
	ldr r1, [r6]
	movs r0, #1
	ands r0, r1
	cmp r0, #0
	beq _08062634
	movs r0, #2
	rsbs r0, r0, #0
	ands r1, r0
	str r1, [r6]
	movs r1, #0
	movs r0, #6
	strb r0, [r5, #0xd]
	strb r1, [r5, #0xe]
_08062634:
	ldr r1, [r7, #0x54]
	str r1, [r5, #0x54]
	ldr r4, _08062678 @ =gSineTable
	adds r2, r7, #0
	adds r2, #0xb8
	ldrh r0, [r2]
	lsrs r0, r0, #8
	lsls r0, r0, #1
	adds r0, r0, r4
	movs r3, #0
	ldrsh r0, [r0, r3]
	movs r3, #0xb
	muls r0, r3, r0
	adds r1, r1, r0
	str r1, [r5, #0x54]
	ldr r1, [r7, #0x58]
	str r1, [r5, #0x58]
	ldrh r0, [r2]
	lsls r0, r0, #0x10
	asrs r0, r0, #0x18
	adds r0, #0x40
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x17
	adds r0, r0, r4
	movs r2, #0
	ldrsh r0, [r0, r2]
	muls r0, r3, r0
	subs r1, r1, r0
	str r1, [r5, #0x58]
_0806266E:
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_08062674: .4byte 0x0000D60F
_08062678: .4byte gSineTable
