	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_0806d684
FUN_0806d684: @ 0x0806D684
	push {r4, r5, r6, lr}
	adds r5, r0, #0
	ldrb r0, [r5, #0xe]
	cmp r0, #0
	bne _0806D77A
	movs r1, #0xb8
	lsls r1, r1, #5
	adds r0, r5, #0
	bl SetMotion
	ldr r4, _0806D6F4 @ =pZero2
	ldr r2, [r4]
	ldr r1, [r5, #0x54]
	ldr r0, [r2, #0x54]
	subs r1, r1, r0
	str r1, [r5, #0x5c]
	ldr r0, [r5, #0x58]
	ldr r2, [r2, #0x58]
	subs r0, r0, r2
	ldr r2, _0806D6F8 @ =0xFFFFE800
	adds r0, r0, r2
	str r0, [r5, #0x60]
	asrs r1, r1, #8
	adds r6, r1, #0
	muls r6, r1, r6
	asrs r0, r0, #8
	adds r1, r0, #0
	muls r1, r0, r1
	adds r0, r1, #0
	adds r6, r6, r0
	adds r0, r6, #0
	bl Sqrt
	lsls r0, r0, #0x10
	lsrs r6, r0, #0x10
	cmp r6, #0
	beq _0806D6FC
	ldr r0, [r5, #0x5c]
	adds r1, r6, #0
	bl __divsi3
	adds r4, r0, #0
	str r4, [r5, #0x5c]
	ldr r0, [r5, #0x60]
	adds r1, r6, #0
	bl __divsi3
	lsls r1, r4, #1
	adds r1, r1, r4
	lsls r1, r1, #1
	str r1, [r5, #0x5c]
	lsls r1, r0, #1
	adds r1, r1, r0
	lsls r1, r1, #1
	str r1, [r5, #0x60]
	b _0806D716
	.align 2, 0
_0806D6F4: .4byte pZero2
_0806D6F8: .4byte 0xFFFFE800
_0806D6FC:
	ldr r0, [r4]
	ldrb r1, [r0, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _0806D70E
	movs r0, #0xc0
	lsls r0, r0, #3
	b _0806D710
_0806D70E:
	ldr r0, _0806D73C @ =0xFFFFFA00
_0806D710:
	str r0, [r5, #0x5c]
	movs r0, #0
	str r0, [r5, #0x60]
_0806D716:
	ldr r0, [r5, #0x5c]
	cmp r0, #0
	ble _0806D740
	movs r2, #0
	ldrb r1, [r5, #0xa]
	movs r0, #0xef
	ands r0, r1
	strb r0, [r5, #0xa]
	adds r0, r5, #0
	adds r0, #0x4c
	strb r2, [r0]
	adds r2, r5, #0
	adds r2, #0x4a
	ldrb r1, [r2]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r2]
	b _0806D762
	.align 2, 0
_0806D73C: .4byte 0xFFFFFA00
_0806D740:
	movs r2, #1
	ldrb r1, [r5, #0xa]
	movs r0, #0x10
	orrs r0, r1
	strb r0, [r5, #0xa]
	adds r0, r5, #0
	adds r0, #0x4c
	strb r2, [r0]
	adds r3, r5, #0
	adds r3, #0x4a
	movs r2, #0x10
	ldrb r1, [r3]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	orrs r0, r2
	strb r0, [r3]
_0806D762:
	adds r1, r5, #0
	adds r1, #0xb4
	movs r0, #1
	strb r0, [r1, #0xa]
	adds r0, r5, #0
	adds r0, #0x74
	ldr r1, _0806D7D4 @ =0x08366708
	bl SetDDP
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_0806D77A:
	adds r0, r5, #0
	bl UpdateMotionGraphic
	ldr r0, [r5, #0x54]
	ldr r3, [r5, #0x5c]
	adds r0, r0, r3
	str r0, [r5, #0x54]
	ldr r1, [r5, #0x58]
	ldr r2, [r5, #0x60]
	adds r1, r1, r2
	str r1, [r5, #0x58]
	adds r2, #0x40
	str r2, [r5, #0x60]
	adds r0, r0, r3
	bl FUN_080098a4
	lsls r0, r0, #0x10
	cmp r0, #0
	bne _0806D7B6
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x5c]
	adds r0, r0, r1
	ldr r1, [r5, #0x58]
	ldr r2, _0806D7D8 @ =0xFFFFE800
	adds r1, r1, r2
	bl FUN_080098a4
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _0806D7CE
_0806D7B6:
	ldr r1, _0806D7DC @ =gEnemyFnTable
	ldrb r0, [r5, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r5, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r5, #0x14]
	adds r0, r5, #0
	bl GyroCannon_Die
_0806D7CE:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_0806D7D4: .4byte sCollisions+(24*4)
_0806D7D8: .4byte 0xFFFFE800
_0806D7DC: .4byte gEnemyFnTable

	thumb_func_start FUN_0806d7e0
FUN_0806d7e0: @ 0x0806D7E0
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	bne _0806D7FE
	movs r1, #0xb8
	lsls r1, r1, #5
	adds r0, r4, #0
	bl SetMotion
	movs r0, #0x78
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0806D7FE:
	movs r2, #0
	ldr r0, _0806D81C @ =pZero2
	ldr r0, [r0]
	ldr r1, [r4, #0x54]
	ldr r0, [r0, #0x54]
	cmp r1, r0
	bge _0806D80E
	movs r2, #1
_0806D80E:
	cmp r2, #0
	beq _0806D820
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	orrs r0, r1
	b _0806D826
	.align 2, 0
_0806D81C: .4byte pZero2
_0806D820:
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
_0806D826:
	strb r0, [r4, #0xa]
	adds r1, r2, #0
	adds r0, r4, #0
	adds r0, #0x4c
	strb r1, [r0]
	adds r3, r4, #0
	adds r3, #0x4a
	lsls r1, r1, #4
	ldrb r2, [r3]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r1
	strb r0, [r3]
	adds r2, r4, #0
	adds r2, #0xb4
	ldr r1, _0806D890 @ =gSineTable
	ldrb r0, [r4, #0x13]
	lsls r0, r0, #1
	adds r0, r0, r1
	movs r3, #0
	ldrsh r1, [r0, r3]
	lsls r1, r1, #5
	ldr r0, [r2, #4]
	adds r0, r0, r1
	str r0, [r4, #0x58]
	ldrb r0, [r4, #0x13]
	adds r0, #1
	strb r0, [r4, #0x13]
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0xff
	bne _0806D8A8
	ldr r2, _0806D894 @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _0806D898 @ =0x000343FD
	muls r0, r1, r0
	ldr r1, _0806D89C @ =0x00269EC3
	adds r0, r0, r1
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r2]
	lsrs r0, r0, #0x11
	movs r1, #0xf
	ands r0, r1
	cmp r0, #9
	bhi _0806D8A0
	movs r0, #3
	b _0806D8A2
	.align 2, 0
_0806D890: .4byte gSineTable
_0806D894: .4byte RNG_0202f388
_0806D898: .4byte 0x000343FD
_0806D89C: .4byte 0x00269EC3
_0806D8A0:
	movs r0, #5
_0806D8A2:
	strb r0, [r4, #0xd]
	movs r0, #0
	strb r0, [r4, #0xe]
_0806D8A8:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start FUN_0806d8b0
FUN_0806d8b0: @ 0x0806D8B0
	push {r4, r5, lr}
	sub sp, #8
	adds r5, r0, #0
	ldrb r0, [r5, #0xe]
	cmp r0, #0
	bne _0806D944
	ldr r1, _0806D904 @ =0x00001703
	adds r0, r5, #0
	bl SetMotion
	ldr r0, [r5, #0x58]
	movs r1, #0x80
	lsls r1, r1, #4
	adds r0, r0, r1
	str r0, [sp, #4]
	ldrb r1, [r5, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _0806D90C
	ldr r0, [r5, #0x54]
	movs r2, #0x80
	lsls r2, r2, #5
	adds r0, r0, r2
	str r0, [sp]
	movs r4, #0xc0
	lsls r4, r4, #1
	mov r0, sp
	adds r1, r4, #0
	movs r2, #0x90
	bl CreateLemon
	ldr r0, [r5, #0x58]
	ldr r1, _0806D908 @ =0xFFFFFB00
	adds r0, r0, r1
	str r0, [sp, #4]
	mov r0, sp
	adds r1, r4, #0
	movs r2, #0x70
	bl CreateLemon
	b _0806D934
	.align 2, 0
_0806D904: .4byte 0x00001703
_0806D908: .4byte 0xFFFFFB00
_0806D90C:
	ldr r0, [r5, #0x54]
	ldr r2, _0806D964 @ =0xFFFFF000
	adds r0, r0, r2
	str r0, [sp]
	movs r4, #0xc0
	lsls r4, r4, #1
	mov r0, sp
	adds r1, r4, #0
	movs r2, #0xef
	bl CreateLemon
	ldr r0, [r5, #0x58]
	ldr r1, _0806D968 @ =0xFFFFFB00
	adds r0, r0, r1
	str r0, [sp, #4]
	mov r0, sp
	adds r1, r4, #0
	movs r2, #0x10
	bl CreateLemon
_0806D934:
	movs r0, #0x2c
	bl PlaySound
	movs r0, #0x30
	strb r0, [r5, #0x12]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_0806D944:
	ldr r4, [r5, #0x2c]
	cmp r4, #0
	bne _0806D96C
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x58]
	movs r2, #0xa0
	lsls r2, r2, #4
	adds r1, r1, r2
	bl FUN_080098a4
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _0806D96C
	strb r4, [r5, #0xd]
	strb r4, [r5, #0xe]
	b _0806D990
	.align 2, 0
_0806D964: .4byte 0xFFFFF000
_0806D968: .4byte 0xFFFFFB00
_0806D96C:
	ldrb r0, [r5, #0x12]
	subs r0, #1
	strb r0, [r5, #0x12]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0xff
	bne _0806D990
	ldr r1, [r5, #0x2c]
	cmp r1, #0
	beq _0806D98A
	movs r0, #4
	strb r0, [r5, #0xd]
	movs r0, #0
	strb r0, [r5, #0xe]
	b _0806D990
_0806D98A:
	movs r0, #7
	strb r0, [r5, #0xd]
	strb r1, [r5, #0xe]
_0806D990:
	add sp, #8
	pop {r4, r5}
	pop {r0}
	bx r0

