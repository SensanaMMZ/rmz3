	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start changeGoldOmega1Mode
changeGoldOmega1Mode: @ 0x0805B4D8
	push {r4, r5, r6, r7, lr}
	mov r7, r8
	push {r7}
	adds r5, r0, #0
	ldrb r0, [r5, #0xe]
	cmp r0, #0
	beq _0805B586
	ldrb r0, [r5, #0x13]
	cmp r0, #0
	beq _0805B586
	subs r0, #1
	strb r0, [r5, #0x13]
	lsls r0, r0, #0x18
	lsrs r7, r0, #0x18
	cmp r7, #0
	bne _0805B586
	adds r0, r5, #0
	adds r0, #0xb5
	adds r1, r5, #0
	adds r1, #0xb6
	movs r3, #0
	ldrsb r3, [r0, r3]
	movs r2, #0
	ldrsb r2, [r1, r2]
	adds r6, r0, #0
	mov r8, r1
	cmp r3, r2
	bne _0805B558
	ldr r2, _0805B548 @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _0805B54C @ =0x000343FD
	muls r0, r1, r0
	ldr r1, _0805B550 @ =0x00269EC3
	adds r0, r0, r1
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r2]
	lsrs r0, r0, #0x11
	ldr r4, _0805B554 @ =0x080FEFBE
	ldrb r1, [r4]
	bl __umodsi3
	adds r0, #1
	adds r0, r0, r4
	ldrb r1, [r0]
	movs r0, #0
	ldrsb r0, [r6, r0]
	cmp r1, r0
	bne _0805B57A
	adds r0, r5, #0
	bl FUN_0805b8ac
	lsls r0, r0, #0x10
	lsrs r1, r0, #0x10
	b _0805B57A
	.align 2, 0
_0805B548: .4byte RNG_0202f388
_0805B54C: .4byte 0x000343FD
_0805B550: .4byte 0x00269EC3
_0805B554: .4byte 0x080FEFBE
_0805B558:
	ldr r2, _0805B594 @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _0805B598 @ =0x000343FD
	muls r0, r1, r0
	ldr r1, _0805B59C @ =0x00269EC3
	adds r0, r0, r1
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r2]
	lsrs r0, r0, #0x11
	ldr r4, _0805B5A0 @ =0x080FEFBE
	ldrb r1, [r4]
	bl __umodsi3
	adds r0, #1
	adds r0, r0, r4
	ldrb r1, [r0]
_0805B57A:
	strb r1, [r5, #0xd]
	strb r7, [r5, #0xe]
	ldrb r0, [r6]
	mov r2, r8
	strb r0, [r2]
	strb r1, [r6]
_0805B586:
	movs r0, #1
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6, r7}
	pop {r1}
	bx r1
	.align 2, 0
_0805B594: .4byte RNG_0202f388
_0805B598: .4byte 0x000343FD
_0805B59C: .4byte 0x00269EC3
_0805B5A0: .4byte 0x080FEFBE

	thumb_func_start goldOmega1Neutral
goldOmega1Neutral: @ 0x0805B5A4
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r5, [r4, #0xe]
	cmp r5, #0
	beq _0805B5B4
	cmp r5, #1
	beq _0805B5CC
	b _0805B5D2
_0805B5B4:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _0805B5D8 @ =0x08364C8C
	bl SetDDP
	str r5, [r4, #0x60]
	str r5, [r4, #0x5c]
	movs r0, #0x1e
	strb r0, [r4, #0x13]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0805B5CC:
	adds r0, r4, #0
	bl floatGoldOmega1
_0805B5D2:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_0805B5D8: .4byte 0x08364C8C
