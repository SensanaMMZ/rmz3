	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_0806cdb0
FUN_0806cdb0: @ 0x0806CDB0
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r5, [r4, #0xe]
	cmp r5, #0
	bne _0806CDD6
	adds r0, #0x74
	ldr r1, _0806CE00 @ =0x08366638
	bl SetDDP
	ldr r1, [r4, #0x2c]
	adds r1, #0xb4
	ldr r0, [r1]
	movs r2, #2
	orrs r0, r2
	str r0, [r1]
	str r5, [r4, #0x60]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0806CDD6:
	adds r5, r4, #0
	adds r5, #0xc0
	ldr r0, [r5]
	bl isKilled
	cmp r0, #0
	beq _0806CDF8
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _0806CE04 @ =0x08366590
	bl SetDDP
	movs r1, #0
	str r1, [r5]
	movs r0, #1
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_0806CDF8:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_0806CE00: .4byte 0x08366638
_0806CE04: .4byte 0x08366590

	thumb_func_start lamplort_0806ce08
lamplort_0806ce08: @ 0x0806CE08
	push {r4, r5, r6, lr}
	adds r4, r0, #0
	adds r6, r4, #0
	adds r6, #0xc0
	ldr r5, [r6]
	cmp r5, #0
	bne _0806CE52
	adds r0, #0x8c
	ldr r0, [r0]
	movs r1, #1
	ands r0, r1
	cmp r0, #0
	beq _0806CE52
	ldr r2, _0806CE44 @ =0x08366650
	movs r0, #0
	adds r1, r4, #0
	bl ApplyElementEffect
	str r0, [r6]
	cmp r0, #0
	beq _0806CE52
	adds r0, r4, #0
	adds r0, #0x97
	ldrb r0, [r0]
	movs r1, #0xf0
	ands r1, r0
	cmp r1, #0x10
	bne _0806CE48
	movs r0, #7
	b _0806CE4E
	.align 2, 0
_0806CE44: .4byte 0x08366650
_0806CE48:
	cmp r1, #0x30
	bne _0806CE52
	movs r0, #9
_0806CE4E:
	strb r0, [r4, #0xd]
	strb r5, [r4, #0xe]
_0806CE52:
	movs r0, #1
	pop {r4, r5, r6}
	pop {r1}
	bx r1
	.align 2, 0
