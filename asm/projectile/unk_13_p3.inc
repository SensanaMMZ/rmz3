	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_0809fcfc
FUN_0809fcfc: @ 0x0809FCFC
	push {r4, r5, r6, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #5
	bls _0809FD08
	b _0809FF6A
_0809FD08:
	lsls r0, r0, #2
	ldr r1, _0809FD14 @ =_0809FD18
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_0809FD14: .4byte _0809FD18
_0809FD18: @ jump table
	.4byte _0809FD30 @ case 0
	.4byte _0809FD66 @ case 1
	.4byte _0809FE40 @ case 2
	.4byte _0809FE70 @ case 3
	.4byte _0809FEDC @ case 4
	.4byte _0809FEE6 @ case 5
_0809FD30:
	movs r0, #8
	strb r0, [r4, #0x13]
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _0809FE20 @ =0x0836B068
	bl SetDDP
	ldr r2, _0809FE24 @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _0809FE28 @ =0x000343FD
	muls r1, r0, r1
	ldr r0, _0809FE2C @ =0x00269EC3
	adds r1, r1, r0
	lsls r1, r1, #1
	lsrs r0, r1, #1
	str r0, [r2]
	lsrs r1, r1, #0x11
	movs r0, #1
	ands r1, r0
	ldr r0, _0809FE30 @ =0x00003203
	adds r1, r1, r0
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0809FD66:
	ldrb r2, [r4, #0x12]
	cmp r2, #2
	bhi _0809FD8A
	ldrb r0, [r4, #0x13]
	cmp r0, #0
	beq _0809FD8A
	subs r0, #1
	strb r0, [r4, #0x13]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _0809FD8A
	ldr r0, [r4, #0x64]
	ldr r1, [r4, #0x68]
	adds r2, #1
	lsls r2, r2, #0x18
	lsrs r2, r2, #0x18
	bl FUN_0809f970
_0809FD8A:
	adds r0, r4, #0
	adds r0, #0x8c
	ldr r1, [r0]
	movs r2, #4
	ands r1, r2
	adds r6, r0, #0
	cmp r1, #0
	beq _0809FDC4
	ldr r5, _0809FE34 @ =pZero2
	ldr r0, [r5]
	movs r1, #0
	bl makeZeroSlower
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0x5f
	bhi _0809FDC4
	ldr r2, [r5]
	ldr r0, [r4, #0x54]
	ldr r1, [r2, #0x54]
	subs r0, r0, r1
	str r0, [r4, #0x64]
	ldr r0, [r4, #0x58]
	ldr r1, [r2, #0x58]
	subs r0, r0, r1
	str r0, [r4, #0x68]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0809FDC4:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldr r0, [r4, #0x58]
	movs r1, #0x80
	lsls r1, r1, #1
	adds r0, r0, r1
	str r0, [r4, #0x58]
	ldr r0, _0809FE38 @ =gStageRun+232
	adds r1, r4, #0
	adds r1, #0x54
	bl CalcFromCamera
	movs r1, #0x80
	lsls r1, r1, #6
	cmp r0, r1
	bhi _0809FDE8
	b _0809FF6A
_0809FDE8:
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r2, #0
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r4, #0xa]
	str r2, [r6]
	adds r0, r4, #0
	adds r0, #0x90
	str r2, [r0]
	adds r0, #4
	strb r2, [r0]
	ldrb r1, [r4, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r4, #0xa]
	ldr r1, _0809FE3C @ =gProjectileFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r4, #0x14]
	b _0809FF6A
	.align 2, 0
_0809FE20: .4byte 0x0836B068
_0809FE24: .4byte RNG_0202f388
_0809FE28: .4byte 0x000343FD
_0809FE2C: .4byte 0x00269EC3
_0809FE30: .4byte 0x00003203
_0809FE34: .4byte pZero2
_0809FE38: .4byte gStageRun+232
_0809FE3C: .4byte gProjectileFnTable
_0809FE40:
	adds r0, r4, #0
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
	ldr r0, _0809FED8 @ =pZero2
	ldr r0, [r0]
	movs r1, #0xc
	bl makeZeroSlower
	movs r0, #0x80
	strb r0, [r4, #0x12]
	movs r0, #0x18
	str r0, [r4, #0x5c]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0809FE70:
	ldr r5, _0809FED8 @ =pZero2
	ldr r0, [r5]
	ldr r1, [r0, #0x54]
	ldr r2, [r4, #0x64]
	adds r1, r1, r2
	str r1, [r4, #0x54]
	ldr r1, [r0, #0x58]
	ldr r2, [r4, #0x68]
	adds r1, r1, r2
	str r1, [r4, #0x58]
	bl CountButtonMashing
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	ldr r1, [r4, #0x5c]
	subs r1, r1, r0
	str r1, [r4, #0x5c]
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _0809FEC0
	cmp r1, #0
	blt _0809FEC0
	ldr r2, [r5]
	adds r0, r2, #0
	adds r0, #0x8c
	ldr r0, [r0]
	movs r1, #0x80
	lsls r1, r1, #2
	ands r0, r1
	cmp r0, #0
	bne _0809FEC0
	adds r0, r2, #0
	adds r0, #0xa4
	movs r1, #0
	ldrsh r0, [r0, r1]
	cmp r0, #0
	bne _0809FED0
_0809FEC0:
	ldr r0, _0809FED8 @ =pZero2
	ldr r0, [r0]
	movs r1, #0xc
	bl makeZeroFaster
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0809FED0:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	b _0809FF6A
	.align 2, 0
_0809FED8: .4byte pZero2
_0809FEDC:
	movs r0, #8
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0809FEE6:
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	lsrs r2, r0, #0x18
	cmp r2, #0
	bne _0809FF28
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
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
	ldr r1, _0809FF3C @ =gProjectileFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r4, #0x14]
_0809FF28:
	ldrb r1, [r4, #0x12]
	movs r0, #1
	ands r0, r1
	cmp r0, #0
	beq _0809FF40
	ldrb r0, [r4, #0xa]
	movs r1, #1
	orrs r0, r1
	b _0809FF46
	.align 2, 0
_0809FF3C: .4byte gProjectileFnTable
_0809FF40:
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
_0809FF46:
	strb r0, [r4, #0xa]
	ldr r0, _0809FF70 @ =pZero2
	ldr r2, [r0]
	ldr r0, [r2, #0x54]
	ldr r1, [r4, #0x64]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	ldr r0, [r2, #0x58]
	ldr r1, [r4, #0x68]
	adds r0, r0, r1
	str r0, [r4, #0x58]
	movs r0, #0x80
	lsls r0, r0, #1
	adds r1, r1, r0
	str r1, [r4, #0x68]
	adds r0, r4, #0
	bl UpdateMotionGraphic
_0809FF6A:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_0809FF70: .4byte pZero2

	thumb_func_start FUN_0809ff74
FUN_0809ff74: @ 0x0809FF74
	push {r4, r5, r6, lr}
	adds r6, r0, #0
	ldrb r0, [r6, #0xe]
	cmp r0, #7
	bls _0809FF80
	b _080A01D8
_0809FF80:
	lsls r0, r0, #2
	ldr r1, _0809FF8C @ =_0809FF90
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_0809FF8C: .4byte _0809FF90
_0809FF90: @ jump table
	.4byte _0809FFB0 @ case 0
	.4byte _080A0012 @ case 1
	.4byte _080A0030 @ case 2
	.4byte _080A0042 @ case 3
	.4byte _080A00D4 @ case 4
	.4byte _080A00DE @ case 5
	.4byte _080A016C @ case 6
	.4byte _080A0182 @ case 7
_0809FFB0:
	adds r0, r6, #0
	adds r0, #0x74
	ldr r1, _0809FFD0 @ =0x0836B080
	bl SetDDP
	ldrb r1, [r6, #0x12]
	movs r0, #1
	adds r2, r0, #0
	eors r2, r1
	cmp r2, #0
	beq _0809FFD4
	ldrb r1, [r6, #0xa]
	movs r0, #0x10
	orrs r0, r1
	b _0809FFDA
	.align 2, 0
_0809FFD0: .4byte 0x0836B080
_0809FFD4:
	ldrb r1, [r6, #0xa]
	movs r0, #0xef
	ands r0, r1
_0809FFDA:
	strb r0, [r6, #0xa]
	movs r3, #1
	adds r1, r3, #0
	ands r1, r2
	adds r0, r6, #0
	adds r0, #0x4c
	movs r4, #0
	strb r1, [r0]
	adds r5, r6, #0
	adds r5, #0x4a
	lsls r1, r1, #4
	ldrb r2, [r5]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r1
	strb r0, [r5]
	adds r0, r6, #0
	adds r0, #0x22
	strb r3, [r0]
	str r4, [r6, #0x60]
	ldr r1, _080A002C @ =0x00003101
	adds r0, r6, #0
	bl SetMotion
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_080A0012:
	adds r0, r6, #0
	bl UpdateMotionGraphic
	adds r0, r6, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	beq _080A0024
	b _080A01D8
_080A0024:
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
	b _080A01D8
	.align 2, 0
_080A002C: .4byte 0x00003101
_080A0030:
	movs r0, #0
	strb r0, [r6, #0x13]
	ldr r1, _080A0080 @ =0x00003102
	adds r0, r6, #0
	bl SetMotion
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_080A0042:
	ldrb r0, [r6, #0x13]
	adds r0, #1
	strb r0, [r6, #0x13]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0x2a
	bls _080A0056
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_080A0056:
	ldrb r0, [r6, #0x12]
	cmp r0, #0
	beq _080A0088
	ldr r4, _080A0084 @ =gSineTable
	ldrb r1, [r6, #0x13]
	lsls r0, r1, #4
	subs r0, r0, r1
	movs r1, #0xa
	bl __divsi3
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x17
	adds r0, r0, r4
	movs r1, #0
	ldrsh r0, [r0, r1]
	lsls r1, r0, #1
	adds r1, r1, r0
	ldr r0, [r6, #0x54]
	subs r0, r0, r1
	b _080A00A8
	.align 2, 0
_080A0080: .4byte 0x00003102
_080A0084: .4byte gSineTable
_080A0088:
	ldr r4, _080A00D0 @ =gSineTable
	ldrb r1, [r6, #0x13]
	lsls r0, r1, #4
	subs r0, r0, r1
	movs r1, #0xa
	bl __divsi3
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x17
	adds r0, r0, r4
	movs r1, #0
	ldrsh r0, [r0, r1]
	lsls r1, r0, #1
	adds r1, r1, r0
	ldr r0, [r6, #0x54]
	adds r0, r0, r1
_080A00A8:
	str r0, [r6, #0x54]
	adds r5, r4, #0
	ldrb r1, [r6, #0x13]
	lsls r0, r1, #4
	subs r0, r0, r1
	movs r1, #0xa
	bl __divsi3
	adds r0, #0x40
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x17
	adds r0, r0, r5
	movs r1, #0
	ldrsh r0, [r0, r1]
	lsls r1, r0, #1
	adds r1, r1, r0
	ldr r0, [r6, #0x58]
	adds r0, r0, r1
	b _080A015C
	.align 2, 0
_080A00D0: .4byte gSineTable
_080A00D4:
	movs r0, #0
	str r0, [r6, #0x64]
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_080A00DE:
	ldr r0, [r6, #0x64]
	adds r0, #3
	str r0, [r6, #0x64]
	cmp r0, #0xaa
	ble _080A00EE
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_080A00EE:
	ldrb r0, [r6, #0x12]
	cmp r0, #0
	beq _080A011C
	ldr r5, _080A0118 @ =gSineTable
	ldr r4, [r6, #0x64]
	lsls r0, r4, #4
	subs r0, r0, r4
	movs r1, #0xa
	bl __divsi3
	adds r0, #0x40
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x17
	adds r0, r0, r5
	movs r1, #0
	ldrsh r0, [r0, r1]
	lsls r1, r0, #1
	adds r1, r1, r0
	ldr r0, [r6, #0x54]
	subs r0, r0, r1
	b _080A013E
	.align 2, 0
_080A0118: .4byte gSineTable
_080A011C:
	ldr r5, _080A0168 @ =gSineTable
	ldr r4, [r6, #0x64]
	lsls r0, r4, #4
	subs r0, r0, r4
	movs r1, #0xa
	bl __divsi3
	adds r0, #0x40
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x17
	adds r0, r0, r5
	movs r1, #0
	ldrsh r0, [r0, r1]
	lsls r1, r0, #1
	adds r1, r1, r0
	ldr r0, [r6, #0x54]
	adds r0, r0, r1
_080A013E:
	str r0, [r6, #0x54]
	lsls r0, r4, #4
	subs r0, r0, r4
	movs r1, #0xa
	bl __divsi3
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x17
	adds r0, r0, r5
	movs r1, #0
	ldrsh r0, [r0, r1]
	lsls r1, r0, #1
	adds r1, r1, r0
	ldr r0, [r6, #0x58]
	subs r0, r0, r1
_080A015C:
	str r0, [r6, #0x58]
	adds r0, r6, #0
	bl UpdateMotionGraphic
	b _080A01D8
	.align 2, 0
_080A0168: .4byte gSineTable
_080A016C:
	movs r2, #0xc0
	lsls r2, r2, #2
	ldrb r1, [r6, #0x12]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #9
	subs r2, r2, r0
	str r2, [r6, #0x5c]
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_080A0182:
	ldr r0, [r6, #0x54]
	ldr r1, [r6, #0x5c]
	adds r0, r0, r1
	str r0, [r6, #0x54]
	ldr r0, _080A01F4 @ =gStageRun+232
	adds r1, r6, #0
	adds r1, #0x54
	bl CalcFromCamera
	movs r1, #0x80
	lsls r1, r1, #6
	cmp r0, r1
	bls _080A01D2
	ldrb r1, [r6, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r2, #0
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r6, #0xa]
	adds r0, r6, #0
	adds r0, #0x8c
	str r2, [r0]
	adds r0, #4
	str r2, [r0]
	adds r0, #4
	strb r2, [r0]
	ldrb r1, [r6, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r6, #0xa]
	ldr r1, _080A01F8 @ =gProjectileFnTable
	ldrb r0, [r6, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r6, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r6, #0x14]
_080A01D2:
	adds r0, r6, #0
	bl UpdateMotionGraphic
_080A01D8:
	ldr r0, [r6, #0x28]
	ldrb r0, [r0, #0xc]
	cmp r0, #1
	bls _080A0250
	ldr r0, [r6, #0x60]
	adds r1, r0, #1
	str r1, [r6, #0x60]
	cmp r1, #0xf
	ble _080A01FC
	movs r0, #2
	ands r1, r0
	cmp r1, #0
	bne _080A0204
	b _080A020C
	.align 2, 0
_080A01F4: .4byte gStageRun+232
_080A01F8: .4byte gProjectileFnTable
_080A01FC:
	movs r0, #1
	ands r1, r0
	cmp r1, #0
	beq _080A020C
_080A0204:
	ldrb r1, [r6, #0xa]
	movs r0, #1
	orrs r0, r1
	b _080A0212
_080A020C:
	ldrb r1, [r6, #0xa]
	movs r0, #0xfe
	ands r0, r1
_080A0212:
	strb r0, [r6, #0xa]
	ldr r0, [r6, #0x60]
	cmp r0, #0x1e
	ble _080A0250
	ldrb r1, [r6, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r2, #0
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r6, #0xa]
	adds r0, r6, #0
	adds r0, #0x8c
	str r2, [r0]
	adds r0, #4
	str r2, [r0]
	adds r0, #4
	strb r2, [r0]
	ldrb r1, [r6, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r6, #0xa]
	ldr r1, _080A0258 @ =gProjectileFnTable
	ldrb r0, [r6, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r6, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r6, #0x14]
_080A0250:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_080A0258: .4byte gProjectileFnTable

	thumb_func_start FUN_080a025c
FUN_080a025c: @ 0x080A025C
	push {r4, r5, r6, r7, lr}
	sub sp, #4
	adds r4, r0, #0
	ldr r7, [r4, #0x28]
	ldrb r0, [r4, #0xe]
	cmp r0, #1
	beq _080A029E
	cmp r0, #1
	bgt _080A0274
	cmp r0, #0
	beq _080A027E
	b _080A039A
_080A0274:
	cmp r0, #2
	beq _080A02C0
	cmp r0, #3
	beq _080A02D2
	b _080A039A
_080A027E:
	adds r1, r4, #0
	adds r1, #0x25
	movs r0, #0x18
	strb r0, [r1]
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _080A02B8 @ =0x0836B098
	bl SetDDP
	ldr r1, _080A02BC @ =0x00003401
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080A029E:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _080A039A
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
	b _080A039A
	.align 2, 0
_080A02B8: .4byte 0x0836B098
_080A02BC: .4byte 0x00003401
_080A02C0:
	movs r0, #1
	strb r0, [r4, #0x13]
	ldr r1, _080A03A4 @ =0x00003402
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080A02D2:
	ldrb r3, [r4, #0x12]
	cmp r3, #1
	bhi _080A02F8
	ldrb r0, [r4, #0x13]
	cmp r0, #0
	beq _080A02F8
	subs r0, #1
	strb r0, [r4, #0x13]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080A02F8
	ldr r1, [r4, #0x64]
	ldr r2, [r4, #0x68]
	adds r3, #1
	lsls r3, r3, #0x18
	lsrs r3, r3, #0x18
	adds r0, r7, #0
	bl FUN_0809fa44
_080A02F8:
	ldr r1, [r4, #0x58]
	movs r0, #0xa0
	lsls r0, r0, #2
	adds r1, r1, r0
	str r1, [r4, #0x58]
	ldr r0, [r4, #0x54]
	bl PushoutToUp1
	adds r1, r0, #0
	cmp r1, #0
	bge _080A0394
	ldr r0, [r4, #0x58]
	adds r0, r0, r1
	str r0, [r4, #0x58]
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
	ldr r1, _080A03A8 @ =gProjectileFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r4, #0x14]
	ldrb r0, [r4, #0x12]
	cmp r0, #0
	bne _080A037C
	movs r6, #0x80
	lsls r6, r6, #0x16
	movs r5, #2
_080A0356:
	ldr r1, [r4, #0x54]
	ldr r2, [r4, #0x58]
	lsrs r0, r6, #0x18
	str r0, [sp]
	adds r0, r7, #0
	movs r3, #0x80
	lsls r3, r3, #1
	bl FUN_080bc6ac
	movs r0, #0x80
	lsls r0, r0, #0x16
	adds r6, r6, r0
	subs r5, #1
	cmp r5, #0
	bge _080A0356
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	bl FUN_080bc758
_080A037C:
	ldr r1, [r4, #0x54]
	ldr r2, [r4, #0x58]
	adds r0, r7, #0
	movs r3, #0
	bl FUN_0809fa9c
	ldr r1, [r4, #0x54]
	ldr r2, [r4, #0x58]
	adds r0, r7, #0
	movs r3, #1
	bl FUN_0809fa9c
_080A0394:
	adds r0, r4, #0
	bl UpdateMotionGraphic
_080A039A:
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080A03A4: .4byte 0x00003402
_080A03A8: .4byte gProjectileFnTable
