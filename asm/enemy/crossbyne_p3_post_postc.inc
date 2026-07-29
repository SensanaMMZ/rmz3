	.include "asm/macros.inc"

	.syntax unified

	.text


	thumb_func_start FUN_0807d478
FUN_0807d478: @ 0x0807D478
	push {r4, r5, r6, r7, lr}
	sub sp, #0x10
	adds r6, r0, #0
	ldrb r0, [r6, #0xe]
	cmp r0, #0
	beq _0807D48C
	cmp r0, #1
	bne _0807D48A
	b _0807D5A0
_0807D48A:
	b _0807D5B8
_0807D48C:
	movs r2, #0
	ldr r0, _0807D4AC @ =pZero2
	ldr r0, [r0]
	ldr r0, [r0, #0x54]
	ldr r1, [r6, #0x54]
	subs r0, r0, r1
	cmp r0, #0
	ble _0807D49E
	movs r2, #1
_0807D49E:
	adds r7, r2, #0
	ldrb r0, [r6, #0x10]
	cmp r0, #1
	bne _0807D4B0
	eors r0, r7
	b _0807D4B4
	.align 2, 0
_0807D4AC: .4byte pZero2
_0807D4B0:
	lsls r0, r7, #0x18
	lsrs r0, r0, #0x18
_0807D4B4:
	adds r7, r0, #0
	adds r2, r7, #0
	cmp r7, #0
	beq _0807D4C4
	ldrb r1, [r6, #0xa]
	movs r0, #0x10
	orrs r0, r1
	b _0807D4CA
_0807D4C4:
	ldrb r1, [r6, #0xa]
	movs r0, #0xef
	ands r0, r1
_0807D4CA:
	strb r0, [r6, #0xa]
	movs r1, #1
	ands r1, r2
	adds r0, r6, #0
	adds r0, #0x4c
	movs r4, #0
	strb r1, [r0]
	adds r3, r6, #0
	adds r3, #0x4a
	lsls r1, r1, #4
	ldrb r2, [r3]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r1
	strb r0, [r3]
	lsls r1, r7, #8
	ldr r0, [r6, #0x54]
	subs r0, r0, r1
	str r0, [r6, #0x54]
	ldr r1, _0807D53C @ =0x08367C56
	ldrb r0, [r6, #0x10]
	adds r5, r6, #0
	adds r5, #0xb8
	lsls r0, r0, #1
	ldrb r2, [r5]
	adds r0, r0, r2
	lsls r0, r0, #1
	adds r0, r0, r1
	ldrh r1, [r0]
	adds r0, r6, #0
	bl SetMotion
	adds r0, r6, #0
	adds r0, #0x8c
	str r4, [r0]
	adds r0, #4
	str r4, [r0]
	adds r0, #4
	strb r4, [r0]
	ldrb r1, [r6, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r6, #0xa]
	ldr r0, [r6, #0x54]
	str r0, [sp, #8]
	ldr r0, [r6, #0x58]
	str r0, [sp, #0xc]
	ldrb r0, [r6, #0x10]
	cmp r0, #1
	bne _0807D540
	adds r3, r7, #0
	eors r3, r0
	movs r0, #0xff
	ands r3, r0
	b _0807D544
	.align 2, 0
_0807D53C: .4byte 0x08367C56
_0807D540:
	movs r3, #0xff
	ands r3, r7
_0807D544:
	movs r0, #0
	add r1, sp, #8
	movs r2, #0x80
	lsls r2, r2, #2
	bl FUN_080b2b40
	movs r1, #0x60
	str r1, [sp, #8]
	ldrb r0, [r6, #0x10]
	cmp r0, #1
	bne _0807D568
	eors r0, r7
	lsls r1, r0, #1
	adds r1, r1, r0
	lsls r1, r1, #6
	movs r0, #0x60
	subs r0, r0, r1
	b _0807D570
_0807D568:
	lsls r0, r7, #1
	adds r0, r0, r7
	lsls r0, r0, #6
	subs r0, r1, r0
_0807D570:
	str r0, [sp, #8]
	movs r0, #0x60
	str r0, [sp, #0xc]
	adds r1, r6, #0
	adds r1, #0x54
	ldrb r0, [r6, #0x10]
	lsls r0, r0, #1
	ldrb r5, [r5]
	adds r0, r0, r5
	lsls r0, r0, #1
	ldr r2, _0807D5C0 @ =0x08367C5E
	adds r0, r0, r2
	str r0, [sp]
	movs r4, #0x18
	str r4, [sp, #4]
	adds r0, r6, #0
	add r2, sp, #8
	movs r3, #0
	bl FUN_080b83d4
	strb r4, [r6, #0x12]
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_0807D5A0:
	adds r0, r6, #0
	bl UpdateMotionGraphic
	ldrb r0, [r6, #0x12]
	subs r0, #1
	strb r0, [r6, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _0807D5B8
	adds r0, r6, #0
	bl MaybeKillCrossbyne
_0807D5B8:
	add sp, #0x10
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_0807D5C0: .4byte 0x08367C5E

	thumb_func_start FUN_0807d5c4
FUN_0807d5c4: @ 0x0807D5C4
	push {r4, lr}
	sub sp, #8
	adds r4, r0, #0
	adds r0, #0x8c
	movs r1, #0
	str r1, [r0]
	adds r0, #4
	str r1, [r0]
	adds r0, #4
	strb r1, [r0]
	ldrb r1, [r4, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r4, #0xa]
	ldr r0, [r4, #0x54]
	str r0, [sp]
	ldr r0, [r4, #0x58]
	str r0, [sp, #4]
	movs r0, #2
	mov r1, sp
	bl CreateSmoke
	ldr r1, _0807D60C @ =gEnemyFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #4
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0x10]
	str r0, [r4, #0x14]
	add sp, #8
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_0807D60C: .4byte gEnemyFnTable
