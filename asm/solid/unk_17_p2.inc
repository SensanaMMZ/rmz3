	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080cf378
FUN_080cf378: @ 0x080CF378
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _080CF388
	cmp r0, #1
	beq _080CF38C
	b _080CF414
_080CF388:
	movs r0, #1
	strb r0, [r4, #0xe]
_080CF38C:
	ldr r5, _080CF41C @ =0x0000FFFF
	ldrh r0, [r4, #0x12]
	cmp r0, #1
	bne _080CF3BA
	ldr r1, _080CF420 @ =0x0837060C
	ldrb r0, [r4, #0x10]
	lsls r0, r0, #1
	adds r0, r0, r1
	ldrh r1, [r0]
	adds r0, r4, #0
	adds r0, #0x71
	movs r2, #0
	ldrsb r2, [r0, r2]
	lsls r2, r2, #0x10
	lsrs r2, r2, #0x10
	adds r0, #1
	movs r3, #0
	ldrsb r3, [r0, r3]
	lsls r3, r3, #0x10
	lsrs r3, r3, #0x10
	adds r0, r4, #0
	bl GotoMotion
_080CF3BA:
	ldrh r0, [r4, #0x12]
	ands r5, r0
	movs r0, #0x80
	lsls r0, r0, #1
	cmp r5, r0
	bne _080CF3EC
	ldr r1, _080CF424 @ =0x08370614
	ldrb r0, [r4, #0x10]
	lsls r0, r0, #1
	adds r0, r0, r1
	ldrh r1, [r0]
	adds r0, r4, #0
	adds r0, #0x71
	movs r2, #0
	ldrsb r2, [r0, r2]
	lsls r2, r2, #0x10
	lsrs r2, r2, #0x10
	adds r0, #1
	movs r3, #0
	ldrsb r3, [r0, r3]
	lsls r3, r3, #0x10
	lsrs r3, r3, #0x10
	adds r0, r4, #0
	bl GotoMotion
_080CF3EC:
	ldr r1, [r4, #0x54]
	ldr r0, [r4, #0x5c]
	subs r1, r1, r0
	str r1, [r4, #0x54]
	ldr r2, [r4, #0x58]
	ldr r0, [r4, #0x60]
	subs r2, r2, r0
	str r2, [r4, #0x58]
	ldr r0, [r4, #0x64]
	cmp r1, r0
	bne _080CF40E
	ldr r0, [r4, #0x68]
	cmp r2, r0
	bne _080CF40E
	movs r0, #0
	strb r0, [r4, #0xd]
	strb r0, [r4, #0xe]
_080CF40E:
	adds r0, r4, #0
	bl UpdateMotionGraphic
_080CF414:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080CF41C: .4byte 0x0000FFFF
_080CF420: .4byte 0x0837060C
_080CF424: .4byte 0x08370614
