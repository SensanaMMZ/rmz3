	.include "asm/macros.inc"

	.syntax unified

	.text

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
