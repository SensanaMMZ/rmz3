	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_08095778
FUN_08095778: @ 0x08095778
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _08095788
	cmp r0, #1
	beq _080957A4
	b _080957C6
_08095788:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _080957CC @ =0x08369FEC
	bl SetDDP
	ldr r1, _080957D0 @ =0x0000D403
	adds r0, r4, #0
	bl SetMotion
	movs r0, #0x10
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080957A4:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	lsrs r1, r0, #0x18
	cmp r1, #0
	bne _080957BE
	movs r0, #5
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_080957BE:
	adds r0, r4, #0
	movs r1, #1
	bl FUN_08094fe0
_080957C6:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080957CC: .4byte 0x08369FEC
_080957D0: .4byte 0x0000D403

	thumb_func_start FUN_080957d4
FUN_080957d4: @ 0x080957D4
	push {r4, r5, r6, r7, lr}
	mov r7, r8
	push {r7}
	adds r5, r0, #0
	ldrb r0, [r5, #0xe]
	cmp r0, #0
	beq _080957E8
	cmp r0, #1
	beq _0809583E
	b _08095900
_080957E8:
	ldr r0, _08095820 @ =0x00000109
	bl PlaySound
	adds r0, r5, #0
	adds r0, #0x74
	ldr r1, _08095824 @ =0x0836A01C
	bl SetDDP
	movs r4, #0x10
	str r4, [r5, #0x64]
	movs r0, #0xa0
	lsls r0, r0, #3
	bl Sqrt
	strb r0, [r5, #0x12]
	ldrb r0, [r5, #0x12]
	ldr r2, [r5, #0x64]
	adds r1, r0, #0
	muls r1, r2, r1
	str r1, [r5, #0x5c]
	ldrb r0, [r5, #0xa]
	ands r4, r0
	cmp r4, #0
	bne _08095828
	rsbs r0, r1, #0
	str r0, [r5, #0x5c]
	b _0809582C
	.align 2, 0
_08095820: .4byte 0x00000109
_08095824: .4byte 0x0836A01C
_08095828:
	rsbs r0, r2, #0
	str r0, [r5, #0x64]
_0809582C:
	movs r0, #0
	strb r0, [r5, #0x13]
	ldr r1, _0809590C @ =0x0000D404
	adds r0, r5, #0
	bl SetMotion
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_0809583E:
	adds r0, r5, #0
	bl UpdateMotionGraphic
	ldr r7, _08095910 @ =pZero2
	ldr r0, [r7]
	adds r0, #0x8c
	ldr r0, [r0]
	movs r6, #1
	ands r0, r6
	cmp r0, #0
	beq _0809588C
	adds r0, r5, #0
	adds r0, #0x8c
	ldr r0, [r0]
	movs r1, #4
	mov r8, r1
	ands r0, r1
	cmp r0, #0
	beq _0809588C
	ldrb r0, [r5, #0x12]
	cmp r0, #0x10
	bls _0809588C
	ldrb r4, [r5, #0x13]
	cmp r4, #0
	bne _0809588C
	movs r0, #0x52
	bl PlaySound
	strb r6, [r5, #0x13]
	ldr r0, [r7]
	movs r1, #0x91
	lsls r1, r1, #1
	adds r0, r0, r1
	strb r6, [r0]
	ldr r0, [r7]
	mov r1, r8
	strb r1, [r0, #0xd]
	ldr r0, [r7]
	strb r4, [r0, #0xe]
_0809588C:
	ldr r0, [r5, #0x5c]
	ldr r1, [r5, #0x64]
	adds r0, r0, r1
	str r0, [r5, #0x5c]
	ldrb r0, [r5, #0x12]
	subs r0, #1
	strb r0, [r5, #0x12]
	ldrb r1, [r5, #0x12]
	movs r0, #3
	ands r0, r1
	cmp r0, #0
	bne _080958B2
	cmp r1, #8
	bls _080958B2
	adds r1, r5, #0
	adds r1, #0x54
	movs r0, #3
	bl CreateSmoke
_080958B2:
	ldr r1, [r5, #0x5c]
	adds r0, r5, #0
	bl FUN_08094fa8
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _080958D4
	ldrb r0, [r5, #0x12]
	cmp r0, #0
	beq _080958D4
	ldr r1, [r5, #0x5c]
	adds r0, r5, #0
	bl FUN_08095014
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _080958DC
_080958D4:
	movs r1, #0
	movs r0, #1
	strb r0, [r5, #0xd]
	strb r1, [r5, #0xe]
_080958DC:
	adds r0, r5, #0
	bl UpdateMotionGraphic
	adds r0, r5, #0
	movs r1, #1
	bl FUN_08094fe0
	lsls r0, r0, #0x18
	lsrs r1, r0, #0x18
	cmp r1, #0
	bne _080958F8
	movs r0, #2
	strb r0, [r5, #0xd]
	strb r1, [r5, #0xe]
_080958F8:
	adds r0, r5, #0
	movs r1, #1
	bl FUN_08094fe0
_08095900:
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_0809590C: .4byte 0x0000D404
_08095910: .4byte pZero2
