	push {r4, r5, r6, r7, lr}
	adds r6, r0, #0
	adds r0, #0xb8
	ldr r7, [r0]
	adds r0, r6, #0
	movs r1, #1
	bl SetMotion
	ldrb r0, [r7, #0xa]
	lsrs r0, r0, #4
	movs r2, #1
	ands r0, r2
	adds r1, r6, #0
	adds r1, #0x4c
	strb r0, [r1]
	ldrb r1, [r7, #0xa]
	lsrs r1, r1, #4
	ands r1, r2
	adds r4, r6, #0
	adds r4, #0x4a
	lsls r3, r1, #4
	ldrb r2, [r4]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r3
	strb r0, [r4]
	cmp r1, #0
	beq _080E564A
	ldrb r0, [r6, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _080E5650
_080E564A:
	ldrb r1, [r6, #0xa]
	movs r0, #0xef
	ands r0, r1
_080E5650:
	strb r0, [r6, #0xa]
	adds r0, r6, #0
	bl UpdateMotionGraphic
	bl GetArchimAtkBoost
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	ldrb r2, [r6, #0xa]
	movs r1, #4
	movs r5, #0
	orrs r1, r2
	strb r1, [r6, #0xa]
	adds r4, r6, #0
	adds r4, #0x74
	lsls r1, r0, #1
	adds r1, r1, r0
	lsls r1, r1, #3
	ldr r0, _080E569C @ =0x08371F08
	adds r1, r1, r0
	adds r2, r6, #0
	adds r2, #0x54
	adds r0, r4, #0
	movs r3, #1
	bl InitBody
	str r6, [r4, #0x2c]
	str r5, [r4, #0x24]
	ldr r0, [r7, #0x54]
	ldr r1, [r7, #0x58]
	str r0, [r6, #0x54]
	str r1, [r6, #0x58]
	movs r0, #0x27
	bl PlaySound
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080E569C: .4byte sCollisions+(24*10)

