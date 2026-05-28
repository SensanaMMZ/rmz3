	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start blazinKnockBackDamage
blazinKnockBackDamage: @ 0x0803FD5C
	push {r4, r5, r6, lr}
	adds r5, r0, #0
	ldrb r6, [r5, #0xe]
	cmp r6, #0
	beq _0803FD6C
	cmp r6, #1
	beq _0803FE0C
	b _0803FED2
_0803FD6C:
	movs r0, #0x74
	bl PlaySound
	adds r1, r5, #0
	adds r1, #0xd0
	ldrb r0, [r1]
	cmp r0, #1
	bne _0803FD94
	strb r6, [r1]
	adds r4, r5, #0
	adds r4, #0xc4
	str r6, [r4]
	adds r0, r5, #0
	movs r1, #2
	bl createBlazinTail
	str r0, [r4]
	adds r0, r5, #0
	adds r0, #0xc8
	strh r6, [r0]
_0803FD94:
	adds r0, r5, #0
	adds r0, #0xcc
	ldr r0, [r0]
	cmp r0, #0
	bne _0803FDB6
	adds r0, r5, #0
	adds r0, #0xc8
	ldrh r1, [r0]
	adds r1, #3
	ldr r2, _0803FDE8 @ =0xFFFFA200
	adds r0, r2, #0
	orrs r1, r0
	lsls r1, r1, #0x10
	lsrs r1, r1, #0x10
	adds r0, r5, #0
	bl SetMotion
_0803FDB6:
	movs r0, #0x48
	bl isSoundPlaying
	cmp r0, #0
	beq _0803FDC6
	movs r0, #0x48
	bl StopSound
_0803FDC6:
	movs r0, #0x72
	bl isSoundPlaying
	cmp r0, #0
	beq _0803FDD6
	movs r0, #0x72
	bl StopSound
_0803FDD6:
	ldr r0, _0803FDEC @ =pZero2
	ldr r0, [r0]
	ldr r1, [r0, #0x54]
	ldr r0, [r5, #0x54]
	cmp r1, r0
	ble _0803FDF4
	ldr r0, _0803FDF0 @ =0xFFFFFE00
	b _0803FDF8
	.align 2, 0
_0803FDE8: .4byte 0xFFFFA200
_0803FDEC: .4byte pZero2
_0803FDF0: .4byte 0xFFFFFE00
_0803FDF4:
	movs r0, #0x80
	lsls r0, r0, #2
_0803FDF8:
	str r0, [r5, #0x5c]
	adds r1, r5, #0
	adds r1, #0xc0
	movs r0, #0
	str r0, [r1]
	movs r0, #0x28
	strb r0, [r5, #0x12]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_0803FE0C:
	adds r0, r5, #0
	bl UpdateMotionGraphic
	ldr r0, [r5, #0x5c]
	rsbs r1, r0, #0
	lsls r1, r1, #3
	asrs r1, r1, #8
	adds r0, r0, r1
	str r0, [r5, #0x5c]
	ldr r0, [r5, #0x60]
	adds r0, #0x40
	str r0, [r5, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _0803FE2E
	str r1, [r5, #0x60]
_0803FE2E:
	ldr r1, [r5, #0x58]
	ldr r0, [r5, #0x60]
	adds r2, r1, r0
	str r2, [r5, #0x58]
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x5c]
	adds r0, r0, r1
	str r0, [r5, #0x54]
	cmp r1, #0
	ble _0803FE5C
	movs r3, #0x80
	lsls r3, r3, #6
	adds r0, r0, r3
	ldr r3, _0803FEC0 @ =0xFFFFF800
	adds r1, r2, r3
	bl PushoutToLeft1
	adds r1, r0, #0
	cmp r1, #0
	beq _0803FE5C
	ldr r0, [r5, #0x54]
	adds r0, r0, r1
	str r0, [r5, #0x54]
_0803FE5C:
	ldr r0, [r5, #0x5c]
	cmp r0, #0
	bge _0803FE7E
	ldr r0, [r5, #0x54]
	ldr r1, _0803FEC4 @ =0xFFFFE000
	adds r0, r0, r1
	ldr r1, [r5, #0x58]
	ldr r2, _0803FEC0 @ =0xFFFFF800
	adds r1, r1, r2
	bl PushoutToRight1
	adds r1, r0, #0
	cmp r1, #0
	beq _0803FE7E
	ldr r0, [r5, #0x54]
	adds r0, r0, r1
	str r0, [r5, #0x54]
_0803FE7E:
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x58]
	bl PushoutToUp1
	adds r1, r0, #0
	cmp r1, #0
	beq _0803FE92
	ldr r0, [r5, #0x58]
	adds r0, r0, r1
	str r0, [r5, #0x58]
_0803FE92:
	ldrb r0, [r5, #0x12]
	cmp r0, #0
	beq _0803FEA2
	subs r0, #1
	strb r0, [r5, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _0803FED2
_0803FEA2:
	adds r2, r5, #0
	adds r2, #0xcc
	ldr r1, [r2]
	cmp r1, #0
	beq _0803FEC8
	ldrb r0, [r1, #0xc]
	cmp r0, #1
	bls _0803FED2
	movs r0, #0
	str r0, [r2]
	movs r1, #3
	strb r1, [r5, #0xd]
	strb r0, [r5, #0xe]
	b _0803FECE
	.align 2, 0
_0803FEC0: .4byte 0xFFFFF800
_0803FEC4: .4byte 0xFFFFE000
_0803FEC8:
	movs r0, #3
	strb r0, [r5, #0xd]
	strb r1, [r5, #0xe]
_0803FECE:
	movs r0, #0xff
	strb r0, [r5, #0xf]
_0803FED2:
	pop {r4, r5, r6}
	pop {r0}
	bx r0

	thumb_func_start blazin_0803fed8
blazin_0803fed8: @ 0x0803FED8
	push {r4, r5, r6, lr}
	adds r4, r0, #0
	adds r5, r4, #0
	adds r5, #0xc0
	ldr r6, [r5]
	cmp r6, #0
	bne _0803FF1E
	adds r0, #0x8c
	ldr r0, [r0]
	movs r1, #1
	ands r0, r1
	cmp r0, #0
	beq _0803FF1E
	ldr r2, _0803FF18 @ =gBlazinCoords
	movs r0, #9
	adds r1, r4, #0
	bl ApplyElementEffect
	str r0, [r5]
	cmp r0, #0
	beq _0803FF1E
	adds r0, r4, #0
	adds r0, #0x97
	ldrb r1, [r0]
	movs r0, #0xf0
	ands r0, r1
	cmp r0, #0x10
	bne _0803FF1C
	movs r0, #0xa
	strb r0, [r4, #0xd]
	strb r6, [r4, #0xe]
	b _0803FF1E
	.align 2, 0
_0803FF18: .4byte gBlazinCoords
_0803FF1C:
	str r6, [r5]
_0803FF1E:
	movs r0, #1
	pop {r4, r5, r6}
	pop {r1}
	bx r1
	.align 2, 0

	thumb_func_start FUN_0803ff28
FUN_0803ff28: @ 0x0803FF28
	push {r4, lr}
	adds r3, r0, #0
	adds r4, r1, #0
	ldr r0, [r3, #0xc]
	ldr r2, [r0, #4]
	ldrb r0, [r2, #4]
	cmp r0, #3
	beq _0803FF40
	cmp r0, #0xe
	beq _0803FF40
	cmp r0, #0xf
	bne _0803FF80
_0803FF40:
	ldr r2, [r3, #0x2c]
	adds r0, r2, #0
	adds r0, #0x8c
	ldr r0, [r0]
	movs r1, #0x80
	lsls r1, r1, #2
	ands r0, r1
	cmp r0, #0
	bne _0803FF5E
	adds r0, r2, #0
	adds r0, #0xa4
	movs r1, #0
	ldrsh r0, [r0, r1]
	cmp r0, #0
	bne _0803FF80
_0803FF5E:
	ldr r0, _0803FF78 @ =gStageRun
	ldrh r1, [r0, #8]
	movs r0, #8
	ands r0, r1
	cmp r0, #0
	bne _0803FF80
	ldr r1, [r2, #0x54]
	ldr r0, [r4]
	cmp r1, r0
	bge _0803FF7C
	movs r0, #0xff
	b _0803FF7E
	.align 2, 0
_0803FF78: .4byte gStageRun
_0803FF7C:
	movs r0, #0xfe
_0803FF7E:
	strb r0, [r2, #0x11]
_0803FF80:
	ldr r0, [r3, #0xc]
	ldr r2, [r0, #4]
	ldr r1, [r3, #4]
	ldrb r0, [r1]
	cmp r0, #2
	beq _0803FFB6
	ldr r1, [r1, #0xc]
	movs r0, #1
	rsbs r0, r0, #0
	cmp r1, r0
	beq _0803FFB6
	ldr r0, [r2, #4]
	ldr r1, _0803FFBC @ =0x000200FF
	ands r0, r1
	subs r1, #0xfd
	cmp r0, r1
	bne _0803FFB6
	ldr r2, [r3, #0x2c]
	ldrb r0, [r2, #0xd]
	cmp r0, #0xb
	beq _0803FFB6
	cmp r0, #5
	beq _0803FFB6
	movs r1, #0
	movs r0, #0xb
	strb r0, [r2, #0xd]
	strb r1, [r2, #0xe]
_0803FFB6:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_0803FFBC: .4byte 0x000200FF

	thumb_func_start FUN_0803ffc0
FUN_0803ffc0: @ 0x0803FFC0
	push {lr}
	sub sp, #8
	ldr r1, [r0, #0x54]
	str r1, [sp]
	ldr r1, [r0, #0x58]
	str r1, [sp, #4]
	mov r1, sp
	bl FUN_0809c430
	movs r0, #1
	add sp, #8
	pop {r1}
	bx r1
	.align 2, 0

	thumb_func_start blazin_0803ffdc
blazin_0803ffdc: @ 0x0803FFDC
	push {r4, lr}
	sub sp, #0x10
	adds r4, r0, #0
	lsls r1, r1, #0x18
	lsrs r2, r1, #0x18
	ldr r0, [r4, #0x54]
	str r0, [sp]
	ldr r0, [r4, #0x58]
	ldr r1, _08040008 @ =0xFFFFD800
	adds r0, r0, r1
	str r0, [sp, #4]
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	bne _08040010
	ldr r0, _0804000C @ =0x080FEE20
	lsls r1, r2, #2
	adds r1, r1, r0
	ldr r0, [r1]
	rsbs r0, r0, #0
	b _08040018
	.align 2, 0
_08040008: .4byte 0xFFFFD800
_0804000C: .4byte 0x080FEE20
_08040010:
	ldr r0, _08040040 @ =0x080FEE20
	lsls r1, r2, #2
	adds r1, r1, r0
	ldr r0, [r1]
_08040018:
	str r0, [sp, #8]
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	bl FUN_08009f6c
	add r2, sp, #8
	str r0, [r2, #4]
	ldr r1, [sp]
	ldr r0, [sp, #8]
	adds r0, r0, r1
	str r0, [sp, #8]
	adds r0, r4, #0
	mov r1, sp
	bl FUN_0809e55c
	movs r0, #1
	add sp, #0x10
	pop {r4}
	pop {r1}
	bx r1
	.align 2, 0
_08040040: .4byte 0x080FEE20

	thumb_func_start blazin_08040044
blazin_08040044: @ 0x08040044
	push {r4, r5, r6, r7, lr}
	sub sp, #0x10
	adds r6, r0, #0
	lsls r1, r1, #0x18
	lsrs r5, r1, #0x18
	adds r7, r5, #0
	lsls r2, r2, #0x18
	lsrs r3, r2, #0x18
	ldr r0, [r6, #0x54]
	str r0, [sp]
	ldr r0, [r6, #0x58]
	str r0, [sp, #4]
	ldrb r1, [r6, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	bne _0804009C
	ldr r0, _08040080 @ =0x080FEDA8
	adds r0, r3, r0
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	movs r1, #0xc0
	lsls r1, r1, #0x18
	adds r0, r0, r1
	lsrs r4, r0, #0x18
	cmp r3, #6
	bhi _08040084
	adds r0, r4, r5
	b _08040086
	.align 2, 0
_08040080: .4byte 0x080FEDA8
_08040084:
	subs r0, r4, r5
_08040086:
	lsls r0, r0, #0x18
	lsrs r4, r0, #0x18
	ldr r2, _08040098 @ =0x080FEDB8
	lsls r3, r3, #3
	adds r0, r3, r2
	ldr r0, [r0]
	ldr r1, [sp]
	adds r0, r0, r1
	b _080400CA
	.align 2, 0
_08040098: .4byte 0x080FEDB8
_0804009C:
	ldr r0, _080400B4 @ =0x080FEDA8
	adds r0, r3, r0
	ldrb r1, [r0]
	movs r0, #0x40
	subs r0, r0, r1
	lsls r0, r0, #0x18
	lsrs r4, r0, #0x18
	cmp r3, #6
	bhi _080400B8
	subs r0, r4, r5
	b _080400BA
	.align 2, 0
_080400B4: .4byte 0x080FEDA8
_080400B8:
	adds r0, r4, r7
_080400BA:
	lsls r0, r0, #0x18
	lsrs r4, r0, #0x18
	ldr r2, _08040108 @ =0x080FEDB8
	lsls r3, r3, #3
	adds r0, r3, r2
	ldr r1, [r0]
	ldr r0, [sp]
	subs r0, r0, r1
_080400CA:
	str r0, [sp]
	adds r0, r2, #4
	adds r0, r3, r0
	ldr r0, [r0]
	ldr r1, [sp, #4]
	adds r0, r0, r1
	str r0, [sp, #4]
	ldr r1, _0804010C @ =gSineTable
	lsls r0, r4, #1
	adds r0, r0, r1
	movs r2, #0
	ldrsh r0, [r0, r2]
	str r0, [sp, #8]
	adds r0, r4, #0
	adds r0, #0x40
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x17
	adds r0, r0, r1
	movs r1, #0
	ldrsh r0, [r0, r1]
	add r2, sp, #8
	str r0, [r2, #4]
	adds r0, r6, #0
	mov r1, sp
	bl FUN_0809e500
	movs r0, #1
	add sp, #0x10
	pop {r4, r5, r6, r7}
	pop {r1}
	bx r1
	.align 2, 0
_08040108: .4byte 0x080FEDB8
_0804010C: .4byte gSineTable

	thumb_func_start createBlazinEXFireBall
createBlazinEXFireBall: @ 0x08040110
	push {r4, r5, lr}
	sub sp, #0x10
	adds r4, r0, #0
	adds r5, r3, #0
	lsls r1, r1, #0x18
	lsrs r3, r1, #0x18
	lsls r2, r2, #0x18
	lsrs r2, r2, #0x18
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	bne _08040140
	ldr r0, _0804013C @ =0x080FEE2C
	adds r0, r3, r0
	movs r1, #0xd
	muls r1, r2, r1
	ldrb r0, [r0]
	adds r1, r1, r0
	lsls r1, r1, #0x18
	lsrs r3, r1, #0x18
	b _08040150
	.align 2, 0
_0804013C: .4byte 0x080FEE2C
_08040140:
	ldr r0, _080401C8 @ =0x080FEE2C
	adds r0, r3, r0
	movs r1, #0xd
	muls r1, r2, r1
	ldrb r0, [r0]
	subs r0, r0, r1
	lsls r0, r0, #0x18
	lsrs r3, r0, #0x18
_08040150:
	ldr r1, _080401CC @ =gSineTable
	lsls r0, r3, #1
	adds r0, r0, r1
	movs r2, #0
	ldrsh r0, [r0, r2]
	str r0, [sp]
	adds r0, r3, #0
	adds r0, #0x40
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x17
	adds r0, r0, r1
	movs r1, #0
	ldrsh r0, [r0, r1]
	rsbs r0, r0, #0
	str r0, [sp, #4]
	movs r0, #0
	str r0, [sp, #8]
	ldr r0, _080401D0 @ =0xFFFFE400
	add r1, sp, #8
	str r0, [r1, #4]
	ldr r2, [sp]
	lsls r0, r2, #1
	adds r0, r0, r2
	lsls r0, r0, #0xb
	asrs r0, r0, #8
	ldr r2, [sp, #8]
	adds r0, r0, r2
	str r0, [sp, #8]
	ldr r2, [sp, #4]
	lsls r0, r2, #1
	adds r0, r0, r2
	lsls r0, r0, #0xb
	asrs r0, r0, #8
	ldr r2, [r1, #4]
	adds r0, r0, r2
	str r0, [r1, #4]
	ldr r0, [r4, #0x54]
	ldr r2, [sp, #8]
	adds r0, r0, r2
	str r0, [sp, #8]
	ldr r0, [r4, #0x58]
	ldr r2, [r1, #4]
	adds r0, r0, r2
	str r0, [r1, #4]
	adds r3, #0x80
	lsls r3, r3, #0x18
	lsrs r3, r3, #0x18
	adds r0, r4, #0
	mov r2, sp
	bl _createBlazinEXFireBall
	cmp r0, #0
	beq _080401BE
	adds r0, #0xbc
	str r5, [r0]
_080401BE:
	movs r0, #1
	add sp, #0x10
	pop {r4, r5}
	pop {r1}
	bx r1
	.align 2, 0
_080401C8: .4byte 0x080FEE2C
_080401CC: .4byte gSineTable
_080401D0: .4byte 0xFFFFE400

	thumb_func_start FUN_080401d4
FUN_080401d4: @ 0x080401D4
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

	thumb_func_start blazin_080402a4
blazin_080402a4: @ 0x080402A4
	push {r4, lr}
	sub sp, #0x10
	adds r2, r0, #0
	movs r3, #0x54
	ldrb r1, [r2, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	bne _080402B8
	movs r3, #0xac
_080402B8:
	ldr r1, _080402F4 @ =gSineTable
	lsls r0, r3, #1
	adds r0, r0, r1
	movs r4, #0
	ldrsh r0, [r0, r4]
	str r0, [sp]
	adds r0, r3, #0
	adds r0, #0x40
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x17
	adds r0, r0, r1
	movs r1, #0
	ldrsh r0, [r0, r1]
	rsbs r0, r0, #0
	str r0, [sp, #4]
	ldr r0, [r2, #0x54]
	str r0, [sp, #8]
	ldr r0, [r2, #0x58]
	add r1, sp, #8
	ldr r3, _080402F8 @ =0xFFFFF800
	adds r0, r0, r3
	str r0, [r1, #4]
	adds r0, r2, #0
	mov r2, sp
	bl blazin_0809e620
	add sp, #0x10
	pop {r4}
	pop {r1}
	bx r1
	.align 2, 0
_080402F4: .4byte gSineTable
_080402F8: .4byte 0xFFFFF800

	thumb_func_start blazin_080402fc
blazin_080402fc: @ 0x080402FC
	push {r4, r5, lr}
	adds r4, r1, #0
	cmp r2, #1
	bne _0804032A
	movs r2, #0
	ldr r5, _0804031C @ =0x080FED5A
	adds r3, r5, #0
_0804030A:
	ldrh r1, [r3]
	cmp r1, r4
	beq _08040320
	adds r3, #2
	adds r2, #1
	cmp r2, #4
	ble _0804030A
	b _0804035C
	.align 2, 0
_0804031C: .4byte 0x080FED5A
_08040320:
	adds r0, r2, #1
	movs r1, #5
	bl __modsi3
	b _08040346
_0804032A:
	movs r2, #0
	ldr r5, _08040350 @ =0x080FED5A
	adds r3, r5, #0
_08040330:
	ldrh r1, [r3]
	cmp r1, r4
	bne _08040354
	adds r1, r2, #1
	adds r0, r1, #0
	cmp r1, #0
	bge _08040340
	adds r0, r2, #4
_08040340:
	asrs r0, r0, #2
	lsls r0, r0, #2
	subs r0, r1, r0
_08040346:
	lsls r0, r0, #1
	adds r0, r0, r5
	ldrh r0, [r0]
	b _0804035C
	.align 2, 0
_08040350: .4byte 0x080FED5A
_08040354:
	adds r3, #2
	adds r2, #1
	cmp r2, #3
	ble _08040330
_0804035C:
	pop {r4, r5}
	pop {r1}
	bx r1
	.align 2, 0

	thumb_func_start howFarBlazin
howFarBlazin: @ 0x08040364
	push {lr}
	ldr r1, _08040380 @ =pZero2
	ldr r1, [r1]
	ldr r2, [r1, #0x54]
	ldr r0, [r0, #0x54]
	subs r1, r2, r0
	cmp r1, #0
	bgt _08040376
	subs r1, r0, r2
_08040376:
	ldr r0, _08040384 @ =0x00004EFF
	cmp r1, r0
	bgt _08040388
	movs r0, #0
	b _0804039A
	.align 2, 0
_08040380: .4byte pZero2
_08040384: .4byte 0x00004EFF
_08040388:
	ldr r0, _08040394 @ =0x00008EFF
	cmp r1, r0
	ble _08040398
	movs r0, #2
	b _0804039A
	.align 2, 0
_08040394: .4byte 0x00008EFF
_08040398:
	movs r0, #1
_0804039A:
	pop {r1}
	bx r1
	.align 2, 0

	thumb_func_start blazin_080403a0
blazin_080403a0: @ 0x080403A0
	push {lr}
	cmp r1, #0
	bne _080403AA
	adds r0, #0xd4
	b _080403BC
_080403AA:
	cmp r1, #1
	bne _080403B2
	adds r0, #0xd8
	b _080403BC
_080403B2:
	cmp r1, #2
	beq _080403BA
	adds r0, #0xe0
	b _080403BC
_080403BA:
	adds r0, #0xdc
_080403BC:
	ldr r0, [r0]
	pop {r1}
	bx r1
	.align 2, 0
