	.include "asm/macros.inc"

	.syntax unified

	.text

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

