	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080bd180
FUN_080bd180: @ 0x080BD180
	push {r4, r5, lr}
	sub sp, #8
	adds r5, r0, #0
	ldrb r0, [r5, #0x12]
	subs r0, #1
	strb r0, [r5, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080BD208
	adds r1, r5, #0
	adds r1, #0x54
	movs r0, #2
	bl CreateSmoke
	ldr r2, _080BD1F0 @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _080BD1F4 @ =0x000343FD
	adds r4, r1, #0
	muls r4, r0, r4
	ldr r0, _080BD1F8 @ =0x00269EC3
	adds r4, r4, r0
	lsls r4, r4, #1
	lsrs r0, r4, #1
	str r0, [r2]
	lsrs r4, r4, #0x11
	movs r0, #3
	ands r4, r0
	ldr r0, [r5, #0x54]
	str r0, [sp]
	ldr r0, [r5, #0x58]
	str r0, [sp, #4]
	ldrb r1, [r5, #0x10]
	ldr r2, _080BD1FC @ =0x00003506
	mov r0, sp
	adds r3, r4, #0
	bl FUN_080bcfbc
	ldrb r1, [r5, #0x10]
	ldr r2, _080BD200 @ =0x00003508
	mov r0, sp
	adds r3, r4, #0
	bl FUN_080bcfbc
	movs r0, #0x31
	bl PlaySound
	ldr r1, _080BD204 @ =gVFXFnTable
	ldrb r0, [r5, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r5, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r5, #0x14]
	b _080BD26A
	.align 2, 0
_080BD1F0: .4byte RNG_0202f388
_080BD1F4: .4byte 0x000343FD
_080BD1F8: .4byte 0x00269EC3
_080BD1FC: .4byte 0x00003506
_080BD200: .4byte 0x00003508
_080BD204: .4byte gVFXFnTable
_080BD208:
	ldrb r0, [r5, #0xe]
	cmp r0, #0
	beq _080BD214
	cmp r0, #1
	beq _080BD244
	b _080BD26A
_080BD214:
	movs r0, #0x28
	strb r0, [r5, #0x12]
	ldr r2, _080BD274 @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _080BD278 @ =0x000343FD
	muls r0, r1, r0
	ldr r1, _080BD27C @ =0x00269EC3
	adds r0, r0, r1
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r2]
	lsrs r0, r0, #0x11
	movs r1, #0x1f
	ands r0, r1
	ldr r1, _080BD280 @ =0xFFFFFE80
	adds r0, r0, r1
	str r0, [r5, #0x60]
	ldr r1, _080BD284 @ =0x00003505
	adds r0, r5, #0
	bl SetMotion
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_080BD244:
	ldr r0, [r5, #0x60]
	adds r0, #0x10
	str r0, [r5, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _080BD254
	str r1, [r5, #0x60]
_080BD254:
	ldr r0, [r5, #0x58]
	ldr r1, [r5, #0x60]
	adds r0, r0, r1
	str r0, [r5, #0x58]
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x5c]
	adds r0, r0, r1
	str r0, [r5, #0x54]
	adds r0, r5, #0
	bl UpdateMotionGraphic
_080BD26A:
	add sp, #8
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080BD274: .4byte RNG_0202f388
_080BD278: .4byte 0x000343FD
_080BD27C: .4byte 0x00269EC3
_080BD280: .4byte 0xFFFFFE80
_080BD284: .4byte 0x00003505

	thumb_func_start FUN_080bd288
FUN_080bd288: @ 0x080BD288
	push {r4, r5, r6, r7, lr}
	mov r7, sb
	mov r6, r8
	push {r6, r7}
	adds r7, r0, #0
	ldrb r0, [r7, #0x12]
	subs r0, #1
	strb r0, [r7, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _080BD2BE
	ldr r0, [r7, #0x54]
	ldr r1, [r7, #0x58]
	bl FUN_080098a4
	lsls r0, r0, #0x10
	lsrs r1, r0, #0x10
	cmp r1, #0
	beq _080BD2E0
	movs r0, #0x80
	lsls r0, r0, #8
	ands r0, r1
	cmp r0, #0
	bne _080BD2E0
	ldr r0, [r7, #0x60]
	cmp r0, #0
	ble _080BD2E0
_080BD2BE:
	adds r1, r7, #0
	adds r1, #0x54
	movs r0, #2
	bl CreateSmoke
	ldr r1, _080BD2DC @ =gVFXFnTable
	ldrb r0, [r7, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r7, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r7, #0x14]
	b _080BD3AE
	.align 2, 0
_080BD2DC: .4byte gVFXFnTable
_080BD2E0:
	ldrb r0, [r7, #0xe]
	mov sb, r0
	cmp r0, #0
	beq _080BD2EE
	cmp r0, #1
	beq _080BD358
	b _080BD3AE
_080BD2EE:
	ldr r4, _080BD370 @ =0x0836EE90
	movs r1, #0x74
	adds r1, r1, r7
	mov r8, r1
	ldrh r0, [r1]
	movs r1, #3
	bl __umodsi3
	lsls r0, r0, #0x10
	lsrs r0, r0, #0xe
	adds r0, r0, r4
	ldr r0, [r0]
	ldr r2, [r7, #0x78]
	lsls r2, r2, #3
	adds r2, r2, r0
	ldr r3, _080BD374 @ =RNG_0202f388
	ldr r0, [r3]
	ldr r6, _080BD378 @ =0x000343FD
	adds r1, r0, #0
	muls r1, r6, r1
	ldr r5, _080BD37C @ =0x00269EC3
	adds r1, r1, r5
	lsls r1, r1, #1
	lsrs r4, r1, #1
	str r4, [r3]
	lsrs r1, r1, #0x11
	movs r0, #0x1f
	ands r1, r0
	ldr r0, [r2, #4]
	adds r0, r0, r1
	str r0, [r7, #0x60]
	adds r1, r4, #0
	muls r1, r6, r1
	adds r1, r1, r5
	lsls r1, r1, #1
	lsrs r0, r1, #1
	str r0, [r3]
	lsrs r1, r1, #0x11
	movs r0, #0x3f
	ands r1, r0
	ldr r0, [r2]
	subs r0, r0, r1
	str r0, [r7, #0x5c]
	mov r0, r8
	ldrh r1, [r0]
	adds r0, r7, #0
	bl SetMotion
	mov r1, sb
	strb r1, [r7, #0x13]
	ldrb r0, [r7, #0xe]
	adds r0, #1
	strb r0, [r7, #0xe]
_080BD358:
	ldrb r0, [r7, #0x13]
	adds r0, #1
	strb r0, [r7, #0x13]
	movs r1, #0xff
	ands r0, r1
	movs r1, #1
	ands r0, r1
	cmp r0, #0
	beq _080BD380
	ldrb r0, [r7, #0xa]
	orrs r0, r1
	b _080BD386
	.align 2, 0
_080BD370: .4byte 0x0836EE90
_080BD374: .4byte RNG_0202f388
_080BD378: .4byte 0x000343FD
_080BD37C: .4byte 0x00269EC3
_080BD380:
	ldrb r1, [r7, #0xa]
	movs r0, #0xfe
	ands r0, r1
_080BD386:
	strb r0, [r7, #0xa]
	ldr r0, [r7, #0x60]
	adds r0, #0x10
	str r0, [r7, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _080BD398
	str r1, [r7, #0x60]
_080BD398:
	ldr r0, [r7, #0x58]
	ldr r1, [r7, #0x60]
	adds r0, r0, r1
	str r0, [r7, #0x58]
	ldr r0, [r7, #0x54]
	ldr r1, [r7, #0x5c]
	adds r0, r0, r1
	str r0, [r7, #0x54]
	adds r0, r7, #0
	bl UpdateMotionGraphic
_080BD3AE:
	pop {r3, r4}
	mov r8, r3
	mov sb, r4
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
