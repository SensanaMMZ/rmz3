	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_0808db64
FUN_0808db64: @ 0x0808DB64
	push {r4, r5, r6, r7, lr}
	mov r7, sb
	mov r6, r8
	push {r6, r7}
	sub sp, #8
	adds r7, r0, #0
	ldrb r0, [r7, #0xe]
	cmp r0, #0
	beq _0808DB7C
	cmp r0, #1
	beq _0808DBC8
	b _0808DD4E
_0808DB7C:
	ldr r0, [r7, #0x54]
	str r0, [r7, #0x64]
	ldr r1, _0808DBA0 @ =0x08369300
	adds r4, r7, #0
	adds r4, #0xb9
	ldrb r0, [r4]
	lsls r0, r0, #1
	adds r0, r0, r1
	ldrh r1, [r0]
	adds r0, r7, #0
	bl SetMotion
	ldrb r0, [r4]
	cmp r0, #0
	bne _0808DBA4
	movs r0, #8
	b _0808DBA6
	.align 2, 0
_0808DBA0: .4byte 0x08369300
_0808DBA4:
	movs r0, #0x18
_0808DBA6:
	strb r0, [r7, #0x12]
	adds r0, r7, #0
	adds r0, #0x74
	ldr r2, _0808DC14 @ =0x0836930C
	ldrb r1, [r4]
	adds r1, r1, r2
	ldrb r2, [r1]
	lsls r1, r2, #1
	adds r1, r1, r2
	lsls r1, r1, #3
	ldr r2, _0808DC18 @ =sCollisions
	adds r1, r1, r2
	bl SetDDP
	ldrb r0, [r7, #0xe]
	adds r0, #1
	strb r0, [r7, #0xe]
_0808DBC8:
	ldr r0, [r7, #0x54]
	ldr r1, _0808DC1C @ =0xFFFFEE00
	adds r0, r0, r1
	ldr r1, [r7, #0x58]
	movs r2, #0x80
	lsls r2, r2, #3
	adds r1, r1, r2
	bl FUN_0800a40c
	adds r1, r0, #0
	cmp r1, #0
	bne _0808DBF6
	ldr r0, [r7, #0x54]
	movs r3, #0x90
	lsls r3, r3, #5
	adds r0, r0, r3
	ldr r1, [r7, #0x58]
	movs r2, #0x80
	lsls r2, r2, #3
	adds r1, r1, r2
	bl FUN_0800a40c
	adds r1, r0, #0
_0808DBF6:
	ldr r0, [r7, #0x64]
	str r0, [r7, #0x54]
	cmp r1, #0
	beq _0808DC0A
	adds r0, r7, #0
	bl FUN_0808d160
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _0808DC20
_0808DC0A:
	movs r1, #0
	movs r0, #1
	strb r0, [r7, #0xd]
	strb r1, [r7, #0xe]
	b _0808DC40
	.align 2, 0
_0808DC14: .4byte 0x0836930C
_0808DC18: .4byte sCollisions
_0808DC1C: .4byte 0xFFFFEE00
_0808DC20:
	ldr r2, [r7, #0x54]
	ldr r3, _0808DD5C @ =0xFFFFFE00
	adds r2, r2, r3
	ldr r3, _0808DD60 @ =RNG_0202f388
	ldr r1, [r3]
	ldr r0, _0808DD64 @ =0x000343FD
	muls r0, r1, r0
	ldr r1, _0808DD68 @ =0x00269EC3
	adds r0, r0, r1
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r3]
	lsls r0, r0, #5
	lsrs r0, r0, #0x16
	adds r2, r2, r0
	str r2, [r7, #0x54]
_0808DC40:
	ldrb r0, [r7, #0x12]
	movs r1, #7
	bl __umodsi3
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _0808DC94
	ldr r1, [r7, #0x54]
	ldr r2, _0808DD6C @ =0xFFFFF000
	mov r8, r2
	add r1, r8
	ldr r3, _0808DD60 @ =RNG_0202f388
	mov sb, r3
	ldr r0, [r3]
	ldr r6, _0808DD64 @ =0x000343FD
	muls r0, r6, r0
	ldr r3, _0808DD68 @ =0x00269EC3
	adds r0, r0, r3
	lsls r0, r0, #1
	lsrs r4, r0, #1
	lsrs r0, r0, #0x11
	ldr r5, _0808DD70 @ =0x00001FFF
	ands r0, r5
	adds r0, r0, r1
	str r0, [sp]
	ldr r2, [r7, #0x58]
	add r2, r8
	adds r0, r4, #0
	muls r0, r6, r0
	adds r0, r0, r3
	lsls r0, r0, #1
	lsrs r1, r0, #1
	mov r3, sb
	str r1, [r3]
	lsrs r0, r0, #0x11
	ands r0, r5
	adds r0, r0, r2
	str r0, [sp, #4]
	movs r0, #3
	mov r1, sp
	bl CreateSmoke
_0808DC94:
	adds r0, r7, #0
	bl UpdateMotionGraphic
	ldrb r0, [r7, #0x12]
	subs r0, #1
	strb r0, [r7, #0x12]
	lsls r0, r0, #0x18
	lsrs r6, r0, #0x18
	cmp r6, #0
	bne _0808DD06
	movs r0, #0x56
	bl PlaySound
	ldr r0, [r7, #0x54]
	ldr r1, [r7, #0x58]
	adds r5, r7, #0
	adds r5, #0xb9
	ldrb r2, [r5]
	ldrb r3, [r7, #0xa]
	lsrs r3, r3, #4
	movs r4, #1
	ands r3, r4
	bl CreateGhost65
	ldrb r0, [r5]
	adds r0, #1
	strb r0, [r5]
	strb r6, [r7, #0xe]
	ldrb r0, [r5]
	cmp r0, #5
	bls _0808DD06
	ldrb r1, [r7, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r7, #0xa]
	adds r0, r7, #0
	adds r0, #0x8c
	str r6, [r0]
	adds r0, #4
	str r6, [r0]
	adds r0, #4
	strb r6, [r0]
	ldrb r1, [r7, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r7, #0xa]
	ldr r1, _0808DD74 @ =gEnemyFnTable
	ldrb r0, [r7, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r7, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r7, #0x14]
_0808DD06:
	ldr r0, _0808DD78 @ =gStageRun+232
	adds r1, r7, #0
	adds r1, #0x54
	bl CalcFromCamera
	movs r1, #0xc0
	lsls r1, r1, #7
	cmp r0, r1
	bls _0808DD4E
	ldrb r1, [r7, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r2, #0
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r7, #0xa]
	adds r0, r7, #0
	adds r0, #0x8c
	str r2, [r0]
	adds r0, #4
	str r2, [r0]
	adds r0, #4
	strb r2, [r0]
	ldrb r1, [r7, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r7, #0xa]
	ldr r1, _0808DD74 @ =gEnemyFnTable
	ldrb r0, [r7, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r7, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r7, #0x14]
_0808DD4E:
	add sp, #8
	pop {r3, r4}
	mov r8, r3
	mov sb, r4
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_0808DD5C: .4byte 0xFFFFFE00
_0808DD60: .4byte RNG_0202f388
_0808DD64: .4byte 0x000343FD
_0808DD68: .4byte 0x00269EC3
_0808DD6C: .4byte 0xFFFFF000
_0808DD70: .4byte 0x00001FFF
_0808DD74: .4byte gEnemyFnTable
_0808DD78: .4byte gStageRun+232

	thumb_func_start FUN_0808dd7c
FUN_0808dd7c: @ 0x0808DD7C
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #1
	beq _0808DDAC
	cmp r0, #1
	bgt _0808DD90
	cmp r0, #0
	beq _0808DD9A
	b _0808DDFE
_0808DD90:
	cmp r0, #2
	beq _0808DDD0
	cmp r0, #3
	beq _0808DDDE
	b _0808DDFE
_0808DD9A:
	movs r0, #0x18
	strb r0, [r4, #0x12]
	ldr r1, _0808DDCC @ =0x00007402
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0808DDAC:
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _0808DDC4
	adds r0, r4, #0
	bl FUN_0808d10c
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0808DDC4:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	b _0808DDFE
	.align 2, 0
_0808DDCC: .4byte 0x00007402
_0808DDD0:
	ldr r1, _0808DEA8 @ =0x00007403
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0808DDDE:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _0808DDFE
	adds r2, r4, #0
	adds r2, #0xba
	movs r0, #0
	movs r1, #0x20
	strb r1, [r2]
	movs r1, #1
	strb r1, [r4, #0xd]
	strb r0, [r4, #0xe]
_0808DDFE:
	ldr r0, [r4, #0x54]
	ldr r1, _0808DEAC @ =0xFFFFEE00
	adds r0, r0, r1
	ldr r1, [r4, #0x58]
	movs r2, #0x80
	lsls r2, r2, #3
	adds r1, r1, r2
	bl FUN_0800a40c
	adds r1, r0, #0
	cmp r1, #0
	bne _0808DE30
	ldr r0, [r4, #0x54]
	movs r1, #0x90
	lsls r1, r1, #5
	adds r0, r0, r1
	ldr r1, [r4, #0x58]
	movs r2, #0x80
	lsls r2, r2, #3
	adds r1, r1, r2
	bl FUN_0800a40c
	adds r1, r0, #0
	cmp r1, #0
	beq _0808DE44
_0808DE30:
	adds r0, r4, #0
	bl FUN_0808d160
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _0808DE44
	movs r1, #0
	movs r0, #3
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_0808DE44:
	adds r0, r4, #0
	movs r1, #1
	bl FUN_0808d268
	lsls r0, r0, #0x18
	lsrs r1, r0, #0x18
	cmp r1, #0
	bne _0808DE5A
	movs r0, #2
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_0808DE5A:
	ldr r0, _0808DEB0 @ =gStageRun+232
	adds r1, r4, #0
	adds r1, #0x54
	bl CalcFromCamera
	movs r1, #0xc0
	lsls r1, r1, #7
	cmp r0, r1
	bls _0808DEA2
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r2, #0
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	adds r0, #0x8c
	str r2, [r0]
	adds r0, #4
	str r2, [r0]
	adds r0, #4
	strb r2, [r0]
	ldrb r1, [r4, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r4, #0xa]
	ldr r1, _0808DEB4 @ =gEnemyFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r4, #0x14]
_0808DEA2:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_0808DEA8: .4byte 0x00007403
_0808DEAC: .4byte 0xFFFFEE00
_0808DEB0: .4byte gStageRun+232
_0808DEB4: .4byte gEnemyFnTable

	thumb_func_start FUN_0808deb8
FUN_0808deb8: @ 0x0808DEB8
	push {r4, r5, lr}
	adds r4, r0, #0
	ldr r5, [r4, #0x28]
	cmp r5, #0
	beq _0808DECC
	ldrb r0, [r5, #0xc]
	cmp r0, #1
	bls _0808DECC
	movs r5, #0
	str r5, [r4, #0x28]
_0808DECC:
	ldrb r0, [r4, #0xe]
	cmp r0, #1
	beq _0808DF16
	cmp r0, #1
	bgt _0808DEDC
	cmp r0, #0
	beq _0808DEE6
	b _0808E006
_0808DEDC:
	cmp r0, #2
	beq _0808DF7C
	cmp r0, #3
	beq _0808DFB6
	b _0808E006
_0808DEE6:
	movs r0, #0x83
	lsls r0, r0, #1
	bl PlaySound
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _0808DF60 @ =0x083691B0
	bl SetDDP
	adds r1, r4, #0
	adds r1, #0x25
	movs r0, #0x19
	strb r0, [r1]
	ldr r0, _0808DF64 @ =0xFFFFE400
	str r0, [r4, #0x68]
	movs r0, #0x20
	strb r0, [r4, #0x12]
	ldr r1, _0808DF68 @ =0x00007410
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0808DF16:
	ldr r2, [r5, #0x54]
	ldr r0, _0808DF6C @ =0xFFFFFE00
	adds r2, r2, r0
	ldr r3, _0808DF70 @ =RNG_0202f388
	ldr r1, [r3]
	ldr r0, _0808DF74 @ =0x000343FD
	muls r0, r1, r0
	ldr r1, _0808DF78 @ =0x00269EC3
	adds r0, r0, r1
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r3]
	lsls r0, r0, #5
	lsrs r0, r0, #0x16
	adds r2, r2, r0
	str r2, [r4, #0x54]
	ldr r0, [r5, #0x58]
	ldr r1, [r4, #0x68]
	adds r0, r0, r1
	str r0, [r4, #0x58]
	subs r1, #0x80
	str r1, [r4, #0x68]
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _0808DF52
	cmp r5, #0
	bne _0808DF58
_0808DF52:
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0808DF58:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	b _0808E006
	.align 2, 0
_0808DF60: .4byte 0x083691B0
_0808DF64: .4byte 0xFFFFE400
_0808DF68: .4byte 0x00007410
_0808DF6C: .4byte 0xFFFFFE00
_0808DF70: .4byte RNG_0202f388
_0808DF74: .4byte 0x000343FD
_0808DF78: .4byte 0x00269EC3
_0808DF7C:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _0808E00C @ =sCollisions
	bl SetDDP
	ldr r0, _0808E010 @ =0xFFFFFE00
	str r0, [r4, #0x5c]
	adds r2, r0, #0
	ldr r0, _0808E014 @ =pZero2
	ldr r0, [r0]
	ldr r1, [r4, #0x54]
	ldr r0, [r0, #0x54]
	cmp r1, r0
	bge _0808DF9C
	movs r2, #0x80
	lsls r2, r2, #2
_0808DF9C:
	str r2, [r4, #0x5c]
	movs r0, #0xc0
	lsls r0, r0, #1
	bl Sqrt
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0x12]
	lsls r0, r0, #6
	rsbs r0, r0, #0
	str r0, [r4, #0x60]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0808DFB6:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	ldr r0, [r4, #0x60]
	adds r0, #0x40
	str r0, [r4, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _0808DFD4
	str r1, [r4, #0x60]
_0808DFD4:
	ldr r1, [r4, #0x58]
	ldr r0, [r4, #0x60]
	adds r1, r1, r0
	str r1, [r4, #0x58]
	ldr r0, [r4, #0x54]
	bl FUN_080098a4
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _0808E006
	adds r1, r4, #0
	adds r1, #0xbc
	movs r2, #0
	movs r0, #1
	strb r0, [r1]
	ldr r1, _0808E018 @ =gEnemyFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r4, #0x14]
	strb r2, [r4, #0xd]
_0808E006:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_0808E00C: .4byte sCollisions
_0808E010: .4byte 0xFFFFFE00
_0808E014: .4byte pZero2
_0808E018: .4byte gEnemyFnTable

	thumb_func_start FUN_0808e01c
FUN_0808e01c: @ 0x0808E01C
	push {r4, r5, r6, lr}
	adds r5, r0, #0
	ldrb r0, [r5, #0xe]
	cmp r0, #0
	beq _0808E02C
	cmp r0, #1
	beq _0808E0E2
	b _0808E17C
_0808E02C:
	ldr r1, _0808E0C0 @ =0x08369300
	adds r4, r5, #0
	adds r4, #0xb9
	ldrb r0, [r4]
	lsls r0, r0, #1
	adds r0, r0, r1
	ldrh r1, [r0]
	adds r0, r5, #0
	bl SetMotion
	adds r0, r5, #0
	adds r0, #0x74
	ldr r2, _0808E0C4 @ =0x0836930C
	ldrb r1, [r4]
	adds r1, r1, r2
	ldrb r2, [r1]
	lsls r1, r2, #1
	adds r1, r1, r2
	lsls r1, r1, #3
	ldr r2, _0808E0C8 @ =sCollisions
	adds r1, r1, r2
	bl SetDDP
	adds r0, r5, #0
	bl UpdateMotionGraphic
	ldr r0, _0808E0CC @ =pZero2
	ldr r2, [r0]
	ldr r1, [r5, #0x54]
	ldr r0, [r2, #0x54]
	subs r1, r1, r0
	str r1, [r5, #0x5c]
	ldr r0, [r5, #0x58]
	ldr r3, _0808E0D0 @ =0xFFFFE800
	adds r0, r0, r3
	ldr r2, [r2, #0x58]
	subs r0, r0, r2
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
	lsrs r6, r0, #8
	cmp r6, #0
	beq _0808E0D4
	ldr r0, [r5, #0x5c]
	lsls r0, r0, #8
	adds r1, r6, #0
	bl __divsi3
	adds r4, r0, #0
	str r4, [r5, #0x5c]
	ldr r0, [r5, #0x60]
	lsls r0, r0, #8
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
	b _0808E0DC
	.align 2, 0
_0808E0C0: .4byte 0x08369300
_0808E0C4: .4byte 0x0836930C
_0808E0C8: .4byte sCollisions
_0808E0CC: .4byte pZero2
_0808E0D0: .4byte 0xFFFFE800
_0808E0D4:
	movs r0, #0xc0
	lsls r0, r0, #3
	str r0, [r5, #0x5c]
	str r6, [r5, #0x60]
_0808E0DC:
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_0808E0E2:
	ldr r1, [r5, #0x5c]
	adds r0, r5, #0
	bl FUN_0808d160
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _0808E0FE
	adds r6, r5, #0
	adds r6, #0x8c
	ldr r4, [r6]
	movs r0, #4
	ands r4, r0
	cmp r4, #0
	beq _0808E10E
_0808E0FE:
	adds r1, r5, #0
	adds r1, #0xbb
	movs r0, #0
	strb r0, [r1]
	adds r0, r5, #0
	bl maybeKillDeathlock
	b _0808E17C
_0808E10E:
	ldr r0, [r5, #0x60]
	adds r0, #0x40
	str r0, [r5, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _0808E11E
	str r1, [r5, #0x60]
_0808E11E:
	ldr r1, [r5, #0x60]
	adds r0, r5, #0
	bl FUN_0808d268
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _0808E138
	adds r0, r5, #0
	adds r0, #0xbb
	strb r4, [r0]
	adds r0, r5, #0
	bl maybeKillDeathlock
_0808E138:
	ldr r0, _0808E184 @ =gStageRun+232
	adds r1, r5, #0
	adds r1, #0x54
	bl CalcFromCamera
	movs r1, #0xc0
	lsls r1, r1, #7
	cmp r0, r1
	bls _0808E17C
	ldrb r1, [r5, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r5, #0xa]
	str r4, [r6]
	adds r0, r5, #0
	adds r0, #0x90
	str r4, [r0]
	adds r0, #4
	strb r4, [r0]
	ldrb r1, [r5, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r5, #0xa]
	ldr r1, _0808E188 @ =gEnemyFnTable
	ldrb r0, [r5, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r5, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r5, #0x14]
_0808E17C:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_0808E184: .4byte gStageRun+232
_0808E188: .4byte gEnemyFnTable
