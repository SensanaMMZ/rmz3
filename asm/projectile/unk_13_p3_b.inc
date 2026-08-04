	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080a04d4
FUN_080a04d4: @ 0x080A04D4
	push {r4, r5, r6, r7, lr}
	mov r7, sl
	mov r6, sb
	mov r5, r8
	push {r5, r6, r7}
	sub sp, #4
	adds r4, r0, #0
	ldr r7, [r4, #0x28]
	ldrb r0, [r4, #0xe]
	cmp r0, #5
	bls _080A04EC
	b _080A05F4
_080A04EC:
	lsls r0, r0, #2
	ldr r1, _080A04F8 @ =_080A04FC
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_080A04F8: .4byte _080A04FC
_080A04FC: @ jump table
	.4byte _080A0514 @ case 0
	.4byte _080A053E @ case 1
	.4byte _080A055C @ case 2
	.4byte _080A056E @ case 3
	.4byte _080A05CC @ case 4
	.4byte _080A05D2 @ case 5
_080A0514:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _080A0550 @ =0x0836B098
	bl SetDDP
	movs r0, #0
	str r0, [r4, #0x68]
	ldr r1, _080A0554 @ =0x0836B0CE
	ldrb r0, [r4, #0x12]
	lsls r0, r0, #1
	adds r0, r0, r1
	movs r1, #0
	ldrsh r0, [r0, r1]
	str r0, [r4, #0x5c]
	ldr r1, _080A0558 @ =0x00003401
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080A053E:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _080A05F4
	b _080A05B2
	.align 2, 0
_080A0550: .4byte 0x0836B098
_080A0554: .4byte 0x0836B0CE
_080A0558: .4byte 0x00003401
_080A055C:
	movs r0, #0
	str r0, [r4, #0x64]
	ldr r1, _080A05BC @ =0x00003402
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080A056E:
	ldr r0, [r4, #0x64]
	adds r0, #4
	str r0, [r4, #0x64]
	movs r1, #0x80
	lsls r1, r1, #2
	cmp r0, r1
	ble _080A057E
	str r1, [r4, #0x64]
_080A057E:
	ldr r0, [r4, #0x68]
	ldr r1, [r4, #0x64]
	adds r0, r0, r1
	str r0, [r4, #0x68]
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r7, #0
	adds r0, #0xce
	ldrb r0, [r0]
	cmp r0, #0
	beq _080A05F4
	ldr r1, [r4, #0x68]
	adds r0, r1, #0
	cmp r1, #0
	bge _080A05A2
	ldr r2, _080A05C0 @ =0x0000FFFF
	adds r0, r1, r2
_080A05A2:
	asrs r0, r0, #0x10
	lsls r0, r0, #0x10
	subs r0, r1, r0
	ldr r3, _080A05C4 @ =0xFFFFA100
	adds r0, r0, r3
	ldr r1, _080A05C8 @ =0x000001FF
	cmp r0, r1
	bhi _080A05F4
_080A05B2:
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
	b _080A05F4
	.align 2, 0
_080A05BC: .4byte 0x00003402
_080A05C0: .4byte 0x0000FFFF
_080A05C4: .4byte 0xFFFFA100
_080A05C8: .4byte 0x000001FF
_080A05CC:
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080A05D2:
	ldr r0, [r4, #0x64]
	adds r1, r0, #0
	subs r1, #0x10
	str r1, [r4, #0x64]
	cmp r1, #0
	bne _080A05E6
	str r1, [r4, #0x68]
	movs r0, #6
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_080A05E6:
	ldr r0, [r4, #0x68]
	ldr r1, [r4, #0x64]
	adds r0, r0, r1
	str r0, [r4, #0x68]
	adds r0, r4, #0
	bl UpdateMotionGraphic
_080A05F4:
	ldr r1, [r7, #0x54]
	str r1, [r4, #0x54]
	ldr r5, _080A06B8 @ =gSineTable
	ldr r0, [r4, #0x68]
	asrs r3, r0, #8
	adds r0, r3, #0
	adds r0, #0x40
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x17
	adds r0, r0, r5
	movs r2, #0
	ldrsh r0, [r0, r2]
	ldr r2, [r4, #0x5c]
	muls r0, r2, r0
	cmp r0, #0
	bge _080A0616
	adds r0, #0xff
_080A0616:
	asrs r0, r0, #8
	adds r0, r1, r0
	str r0, [r4, #0x54]
	ldr r1, [r7, #0x58]
	str r1, [r4, #0x58]
	lsls r0, r3, #0x18
	lsrs r0, r0, #0x17
	adds r0, r0, r5
	movs r3, #0
	ldrsh r0, [r0, r3]
	muls r0, r2, r0
	cmp r0, #0
	bge _080A0632
	adds r0, #0xff
_080A0632:
	asrs r0, r0, #8
	adds r0, r1, r0
	str r0, [r4, #0x58]
	ldrb r0, [r7, #0xc]
	cmp r0, #1
	bls _080A06A8
	movs r0, #0x8c
	adds r0, r0, r4
	mov r8, r0
	movs r1, #0x90
	adds r1, r1, r4
	mov sb, r1
	movs r2, #0x94
	adds r2, r2, r4
	mov sl, r2
	movs r6, #0x80
	lsls r6, r6, #0x16
	movs r5, #3
_080A0656:
	ldr r1, [r4, #0x54]
	ldr r2, [r4, #0x58]
	lsrs r0, r6, #0x18
	str r0, [sp]
	adds r0, r7, #0
	movs r3, #0x80
	lsls r3, r3, #1
	bl FUN_080bc6ac
	movs r3, #0x80
	lsls r3, r3, #0x17
	adds r6, r6, r3
	subs r5, #1
	cmp r5, #0
	bge _080A0656
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r2, #0
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r4, #0xa]
	mov r0, r8
	str r2, [r0]
	mov r1, sb
	str r2, [r1]
	mov r3, sl
	strb r2, [r3]
	ldrb r1, [r4, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r4, #0xa]
	ldr r1, _080A06BC @ =gProjectileFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r4, #0x14]
_080A06A8:
	add sp, #4
	pop {r3, r4, r5}
	mov r8, r3
	mov sb, r4
	mov sl, r5
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080A06B8: .4byte gSineTable
_080A06BC: .4byte gProjectileFnTable
