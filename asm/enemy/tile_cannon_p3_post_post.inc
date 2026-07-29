	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_08078664
FUN_08078664: @ 0x08078664
	push {r4, r5, r6, r7, lr}
	adds r5, r0, #0
	ldr r6, [r5, #0x28]
	ldrb r4, [r5, #0xe]
	cmp r4, #0
	beq _08078676
	cmp r4, #1
	beq _0807869A
	b _0807873C
_08078676:
	adds r0, r5, #0
	bl InitRotatableMotion
	ldr r1, _08078744 @ =0x00002F06
	adds r0, r5, #0
	bl SetMotion
	adds r0, r5, #0
	adds r0, #0x24
	strb r4, [r0]
	movs r0, #0x78
	strb r0, [r5, #0x12]
	str r4, [r5, #0x5c]
	adds r0, #0x88
	str r0, [r5, #0x60]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_0807869A:
	adds r0, r6, #0
	bl IsFrozen
	cmp r0, #0
	bne _08078736
	ldr r0, _08078748 @ =pZero2
	ldr r1, [r0]
	ldr r4, [r1, #0x54]
	ldr r0, [r5, #0x54]
	subs r4, r4, r0
	ldr r0, [r5, #0x58]
	movs r2, #0xc0
	lsls r2, r2, #5
	adds r0, r0, r2
	ldr r1, [r1, #0x58]
	subs r7, r1, r0
	asrs r0, r4, #8
	adds r6, r0, #0
	muls r6, r0, r6
	asrs r0, r7, #8
	adds r1, r0, #0
	muls r1, r0, r1
	adds r0, r1, #0
	adds r6, r6, r0
	adds r0, r6, #0
	bl Sqrt
	lsls r0, r0, #0x10
	lsrs r6, r0, #8
	lsls r4, r4, #8
	adds r0, r4, #0
	adds r1, r6, #0
	bl __divsi3
	adds r4, r0, #0
	lsls r0, r7, #8
	adds r1, r6, #0
	bl __divsi3
	adds r7, r0, #0
	ldr r1, [r5, #0x5c]
	subs r0, r4, r1
	cmp r0, #0
	bge _080786F4
	adds r0, #7
_080786F4:
	asrs r0, r0, #3
	adds r4, r1, r0
	str r4, [r5, #0x5c]
	ldr r2, [r5, #0x60]
	subs r0, r7, r2
	cmp r0, #0
	bge _08078704
	adds r0, #7
_08078704:
	asrs r1, r0, #3
	adds r1, r2, r1
	str r1, [r5, #0x60]
	lsls r0, r4, #0x10
	asrs r0, r0, #0x10
	lsls r1, r1, #0x10
	asrs r1, r1, #0x10
	bl ArcTan2
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x18
	subs r0, #0x40
	adds r1, r5, #0
	adds r1, #0x24
	strb r0, [r1]
	ldrb r0, [r5, #0x12]
	subs r0, #1
	strb r0, [r5, #0x12]
	lsls r0, r0, #0x18
	lsrs r1, r0, #0x18
	cmp r1, #0
	bne _08078736
	movs r0, #6
	strb r0, [r5, #0xd]
	strb r1, [r5, #0xe]
_08078736:
	adds r0, r5, #0
	bl UpdateMotionGraphic
_0807873C:
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_08078744: .4byte 0x00002F06
_08078748: .4byte pZero2

