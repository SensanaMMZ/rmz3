	push {r4, r5, r6, r7, lr}
	mov r7, sl
	mov r6, sb
	mov r5, r8
	push {r5, r6, r7}
	sub sp, #0x10
	str r0, [sp, #0xc]
	lsls r1, r1, #0x18
	lsrs r1, r1, #0x18
	mov r8, r1
	movs r0, #0
	mov sl, r0
	ldr r1, _08040290 @ =0x7FFFFFFF
	mov sb, r1
	movs r2, #0
	movs r0, #0xd
	mov r3, r8
	muls r3, r0, r3
	str r3, [sp]
	ldr r0, _08040294 @ =gSineTable
	mov r8, r0
_080401FE:
	ldr r0, _08040298 @ =0x080FEE2C
	adds r0, r2, r0
	ldrb r0, [r0]
	ldr r1, [sp]
	adds r0, r0, r1
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	lsls r1, r0, #1
	add r1, r8
	movs r3, #0
	ldrsh r1, [r1, r3]
	adds r6, r1, #0
	adds r0, #0x40
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x17
	add r0, r8
	movs r3, #0
	ldrsh r0, [r0, r3]
	rsbs r0, r0, #0
	adds r7, r0, #0
	ldr r5, _0804029C @ =0xFFFFE400
	lsls r1, r1, #1
	adds r1, r1, r6
	lsls r1, r1, #0xb
	asrs r4, r1, #8
	lsls r0, r0, #1
	adds r0, r0, r7
	lsls r0, r0, #0xb
	asrs r0, r0, #8
	adds r5, r5, r0
	ldr r1, [sp, #0xc]
	ldr r0, [r1, #0x54]
	adds r4, r4, r0
	ldr r0, [r1, #0x58]
	adds r5, r5, r0
	ldr r0, _080402A0 @ =pZero2
	ldr r1, [r0]
	ldr r0, [r1, #0x54]
	subs r6, r0, r4
	ldr r0, [r1, #0x58]
	subs r7, r0, r5
	asrs r0, r6, #2
	adds r3, r0, #0
	muls r3, r0, r3
	adds r0, r3, #0
	asrs r1, r7, #2
	adds r3, r1, #0
	muls r3, r1, r3
	adds r1, r3, #0
	adds r0, r0, r1
	str r2, [sp, #4]
	bl Sqrt
	lsls r0, r0, #0x10
	lsrs r0, r0, #0xe
	ldr r2, [sp, #4]
	cmp r0, sb
	bge _08040276
	mov sb, r0
	mov sl, r2
_08040276:
	adds r2, #1
	cmp r2, #4
	ble _080401FE
	mov r0, sl
	add sp, #0x10
	pop {r3, r4, r5}
	mov r8, r3
	mov sb, r4
	mov sl, r5
	pop {r4, r5, r6, r7}
	pop {r1}
	bx r1
	.align 2, 0
_08040290: .4byte 0x7FFFFFFF
_08040294: .4byte gSineTable
_08040298: .4byte 0x080FEE2C
_0804029C: .4byte 0xFFFFE400
_080402A0: .4byte pZero2
