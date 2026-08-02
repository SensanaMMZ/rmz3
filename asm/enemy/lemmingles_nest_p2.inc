	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_0806e3b0
FUN_0806e3b0: @ 0x0806E3B0
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _0806E3C0
	cmp r0, #1
	beq _0806E40E
	b _0806E4B6
_0806E3C0:
	strb r0, [r4, #0x12]
	strb r0, [r4, #0x13]
	adds r3, r4, #0
	adds r3, #0xb4
	ldr r2, [r3]
	movs r0, #1
	ands r2, r0
	str r2, [r4, #0x5c]
	ldr r0, [r3]
	movs r1, #2
	ands r0, r1
	lsrs r0, r0, #1
	adds r2, r2, r0
	str r2, [r4, #0x5c]
	ldr r0, [r3]
	movs r1, #4
	ands r0, r1
	lsrs r0, r0, #2
	adds r2, r2, r0
	str r2, [r4, #0x5c]
	ldr r0, [r3]
	movs r1, #8
	ands r0, r1
	lsrs r0, r0, #3
	adds r2, r2, r0
	str r2, [r4, #0x5c]
	ldr r0, [r3]
	subs r1, #0x19
	ands r0, r1
	subs r1, #0x10
	ands r0, r1
	subs r1, #0x20
	ands r0, r1
	subs r1, #0x40
	ands r0, r1
	str r0, [r3]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0806E40E:
	ldrb r0, [r4, #0x12]
	cmp r0, #0
	bne _0806E4B2
	movs r0, #0x20
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0x13]
	adds r0, #1
	strb r0, [r4, #0x13]
	ldrb r3, [r4, #0x13]
	ldr r0, [r4, #0x5c]
	cmp r0, r3
	bne _0806E470
	adds r0, r4, #0
	adds r0, #0xb4
	adds r2, r3, #7
	movs r5, #1
	adds r1, r5, #0
	lsls r1, r2
	ldr r0, [r0]
	ands r0, r1
	lsrs r0, r2
	cmp r0, #0
	beq _0806E452
	ldrb r2, [r4, #0xa]
	lsrs r2, r2, #4
	ands r2, r5
	subs r3, #1
	lsls r3, r3, #0x18
	lsrs r3, r3, #0x18
	adds r0, r4, #0
	movs r1, #2
	bl FUN_0806e590
	b _0806E466
_0806E452:
	ldrb r2, [r4, #0xa]
	lsrs r2, r2, #4
	ands r2, r5
	subs r3, #1
	lsls r3, r3, #0x18
	lsrs r3, r3, #0x18
	adds r0, r4, #0
	movs r1, #0
	bl FUN_0806e590
_0806E466:
	movs r1, #0
	movs r0, #3
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
	b _0806E4B6
_0806E470:
	adds r0, r4, #0
	adds r0, #0xb4
	adds r2, r3, #7
	movs r5, #1
	adds r1, r5, #0
	lsls r1, r2
	ldr r0, [r0]
	ands r0, r1
	lsrs r0, r2
	cmp r0, #0
	beq _0806E49C
	ldrb r2, [r4, #0xa]
	lsrs r2, r2, #4
	ands r2, r5
	subs r3, #1
	lsls r3, r3, #0x18
	lsrs r3, r3, #0x18
	adds r0, r4, #0
	movs r1, #3
	bl FUN_0806e590
	b _0806E4B6
_0806E49C:
	ldrb r2, [r4, #0xa]
	lsrs r2, r2, #4
	ands r2, r5
	subs r3, #1
	lsls r3, r3, #0x18
	lsrs r3, r3, #0x18
	adds r0, r4, #0
	movs r1, #1
	bl FUN_0806e590
	b _0806E4B6
_0806E4B2:
	subs r0, #1
	strb r0, [r4, #0x12]
_0806E4B6:
	pop {r4, r5}
	pop {r0}
	bx r0
