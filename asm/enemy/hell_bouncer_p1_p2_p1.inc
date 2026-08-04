	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start HellBouncer_Update
HellBouncer_Update: @ 0x0807E400
	push {r4, r5, r6, lr}
	sub sp, #8
	adds r6, r0, #0
	adds r1, r6, #0
	adds r1, #0xbb
	movs r0, #0
	strb r0, [r1]
	ldr r3, _0807E434 @ =gWhitePaintFlags
	ldr r0, [r6, #0x28]
	ldrb r1, [r0, #0x1d]
	lsrs r2, r1, #5
	lsls r2, r2, #2
	adds r2, r2, r3
	movs r0, #0x1f
	ands r0, r1
	movs r1, #1
	lsls r1, r0
	ldr r0, [r2]
	ands r0, r1
	cmp r0, #0
	beq _0807E438
	adds r0, r6, #0
	bl PaintEntityWhite
	b _0807E43E
	.align 2, 0
_0807E434: .4byte gWhitePaintFlags
_0807E438:
	adds r0, r6, #0
	bl UpdateEntityPaletteID
_0807E43E:
	ldr r0, [r6, #0x28]
	adds r0, #0x94
	ldrb r0, [r0]
	cmp r0, #0
	beq _0807E452
	adds r1, r6, #0
	adds r1, #0x94
	movs r0, #0x80
	strb r0, [r1]
	b _0807E45E
_0807E452:
	adds r2, r6, #0
	adds r2, #0x94
	ldrb r1, [r2]
	movs r0, #0x7f
	ands r0, r1
	strb r0, [r2]
_0807E45E:
	adds r0, r6, #0
	adds r0, #0x8c
	ldr r1, [r0]
	movs r2, #1
	ands r1, r2
	adds r4, r0, #0
	cmp r1, #0
	beq _0807E496
	adds r2, r6, #0
	adds r2, #0xb4
	adds r0, #0x18
	movs r3, #0
	ldrsh r1, [r0, r3]
	ldr r0, [r2]
	subs r0, r0, r1
	adds r2, #7
	strb r0, [r2]
	ldr r1, [r6, #0x28]
	adds r0, r1, #0
	adds r0, #0x94
	ldrb r0, [r0]
	cmp r0, #0
	bne _0807E496
	adds r0, r1, #0
	adds r0, #0x74
	ldrb r1, [r2]
	bl CalcPutitedSpikeDamage
_0807E496:
	adds r2, r6, #0
	adds r2, #0xc2
	ldrb r0, [r2]
	cmp r0, #0
	bne _0807E4B6
	ldr r0, [r4]
	movs r1, #4
	ands r0, r1
	cmp r0, #0
	beq _0807E4BA
	movs r0, #0x3c
	strb r0, [r2]
	movs r0, #0x52
	bl PlaySound
	b _0807E4BA
_0807E4B6:
	subs r0, #1
	strb r0, [r2]
_0807E4BA:
	ldr r0, [r6, #0x28]
	ldrb r0, [r0, #0xc]
	cmp r0, #1
	bls _0807E554
	ldr r1, _0807E534 @ =gEnemyFnTable
	ldrb r0, [r6, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r6, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r6, #0x14]
	ldr r2, _0807E538 @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _0807E53C @ =0x000343FD
	adds r4, r1, #0
	muls r4, r0, r4
	ldr r0, _0807E540 @ =0x00269EC3
	adds r4, r4, r0
	lsls r4, r4, #1
	lsrs r0, r4, #1
	str r0, [r2]
	lsrs r4, r4, #0x11
	movs r0, #3
	ands r4, r0
	ldr r0, [r6, #0x54]
	str r0, [sp]
	ldr r0, [r6, #0x58]
	str r0, [sp, #4]
	adds r5, r6, #0
	adds r5, #0xb8
	ldrb r1, [r5]
	ldr r2, _0807E544 @ =0x0000AB28
	mov r0, sp
	adds r3, r4, #0
	bl FUN_080becf8
	ldrb r1, [r5]
	ldr r2, _0807E548 @ =0x0000AB29
	mov r0, sp
	adds r3, r4, #0
	bl FUN_080becf8
	ldrb r1, [r5]
	ldr r2, _0807E54C @ =0x0000AB2A
	mov r0, sp
	adds r3, r4, #0
	bl FUN_080becf8
	ldrb r1, [r5]
	ldr r2, _0807E550 @ =0x0000AB2B
	mov r0, sp
	adds r3, r4, #0
	bl FUN_080becf8
	adds r0, r6, #0
	bl HellBouncer_Die
	b _0807E59A
	.align 2, 0
_0807E534: .4byte gEnemyFnTable
_0807E538: .4byte RNG_0202f388
_0807E53C: .4byte 0x000343FD
_0807E540: .4byte 0x00269EC3
_0807E544: .4byte 0x0000AB28
_0807E548: .4byte 0x0000AB29
_0807E54C: .4byte 0x0000AB2A
_0807E550: .4byte 0x0000AB2B
_0807E554:
	ldr r1, _0807E578 @ =0x08367D80
	ldrb r0, [r6, #0xd]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r1, [r0]
	adds r0, r6, #0
	bl _call_via_r1
	adds r0, r6, #0
	bl IsFrozen
	cmp r0, #0
	beq _0807E57C
	ldrb r1, [r6, #0xd]
	adds r0, r6, #0
	adds r0, #0xba
	strb r1, [r0]
	b _0807E59A
	.align 2, 0
_0807E578: .4byte 0x08367D80
_0807E57C:
	ldr r1, _0807E5A4 @ =0x08367D8C
	ldrb r0, [r6, #0xd]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r1, [r0]
	adds r0, r6, #0
	bl _call_via_r1
	adds r1, r6, #0
	adds r1, #0xb4
	adds r0, r6, #0
	adds r0, #0xa4
	movs r2, #0
	ldrsh r0, [r0, r2]
	str r0, [r1]
_0807E59A:
	add sp, #8
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_0807E5A4: .4byte 0x08367D8C
