	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start deathtanzEX1
deathtanzEX1: @ 0x0804A6B4
	push {r4, r5, lr}
	sub sp, #4
	adds r5, r0, #0
	ldrb r0, [r5, #0xe]
	cmp r0, #8
	bls _0804A6C2
	b _0804A8AE
_0804A6C2:
	lsls r0, r0, #2
	ldr r1, _0804A6CC @ =_0804A6D0
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_0804A6CC: .4byte _0804A6D0
_0804A6D0: @ jump table
	.4byte _0804A6F4 @ case 0
	.4byte _0804A77E @ case 1
	.4byte _0804A79C @ case 2
	.4byte _0804A7FE @ case 3
	.4byte _0804A814 @ case 4
	.4byte _0804A824 @ case 5
	.4byte _0804A84C @ case 6
	.4byte _0804A882 @ case 7
	.4byte _0804A894 @ case 8
_0804A6F4:
	adds r1, r5, #0
	adds r1, #0xc0
	movs r2, #0
	movs r0, #3
	strb r0, [r1]
	strb r2, [r5, #0x12]
	movs r1, #0
	ldr r0, _0804A744 @ =pZero2
	ldr r0, [r0]
	ldr r2, [r5, #0x54]
	ldr r0, [r0, #0x54]
	cmp r2, r0
	bge _0804A710
	movs r1, #1
_0804A710:
	adds r4, r1, #0
	adds r0, r5, #0
	adds r0, #0xb4
	ldr r3, [r0]
	subs r0, r2, r3
	movs r1, #0xa0
	lsls r1, r1, #6
	adds r0, r0, r1
	movs r1, #0xa0
	lsls r1, r1, #7
	cmp r0, r1
	bls _0804A748
	movs r0, #0
	cmp r2, r3
	bge _0804A730
	movs r0, #1
_0804A730:
	cmp r4, r0
	beq _0804A748
	movs r0, #1
	strb r0, [r5, #0xd]
	strb r0, [r5, #0xe]
	strb r0, [r5, #0x12]
	adds r0, r5, #0
	bl UpdateMotionGraphic
	b _0804A8AE
	.align 2, 0
_0804A744: .4byte pZero2
_0804A748:
	ldrb r1, [r5, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _0804A758
	cmp r4, #0
	beq _0804A762
	b _0804A75C
_0804A758:
	cmp r4, #0
	bne _0804A762
_0804A75C:
	movs r0, #2
	strb r0, [r5, #0xe]
	b _0804A8AE
_0804A762:
	adds r0, r5, #0
	adds r0, #0x74
	ldr r1, _0804A794 @ =sCollisions+(24*4)
	bl SetDDP
	movs r0, #1
	strb r0, [r5, #0x12]
	ldr r1, _0804A798 @ =0x0000A707
	adds r0, r5, #0
	bl SetMotion
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_0804A77E:
	adds r0, r5, #0
	bl UpdateMotionGraphic
	adds r0, r5, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	beq _0804A790
	b _0804A8AE
_0804A790:
	b _0804A86A
	.align 2, 0
_0804A794: .4byte sCollisions+(24*4)
_0804A798: .4byte 0x0000A707
_0804A79C:
	adds r0, r5, #0
	adds r0, #0x74
	ldr r1, _0804A7E4 @ =0x08362E3C
	bl SetDDP
	ldrb r0, [r5, #0x12]
	cmp r0, #0
	beq _0804A7F0
	ldrb r0, [r5, #0xa]
	lsrs r0, r0, #4
	movs r2, #1
	eors r0, r2
	ands r0, r2
	adds r1, r5, #0
	adds r1, #0x4c
	strb r0, [r1]
	ldrb r1, [r5, #0xa]
	lsrs r1, r1, #4
	eors r1, r2
	ands r1, r2
	adds r4, r5, #0
	adds r4, #0x4a
	lsls r3, r1, #4
	ldrb r2, [r4]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r3
	strb r0, [r4]
	cmp r1, #0
	beq _0804A7E8
	ldrb r0, [r5, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _0804A7EE
	.align 2, 0
_0804A7E4: .4byte sCollisions+(24*68)
_0804A7E8:
	ldrb r1, [r5, #0xa]
	movs r0, #0xef
	ands r0, r1
_0804A7EE:
	strb r0, [r5, #0xa]
_0804A7F0:
	ldr r1, _0804A810 @ =0x0000A727
	adds r0, r5, #0
	bl SetMotion
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_0804A7FE:
	adds r0, r5, #0
	bl UpdateMotionGraphic
	adds r0, r5, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _0804A8AE
	b _0804A86A
	.align 2, 0
_0804A810: .4byte 0x0000A727
_0804A814:
	movs r0, #0x5f
	bl PlaySound
	movs r0, #0
	strb r0, [r5, #0x12]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_0804A824:
	ldr r1, [r5, #0x54]
	ldr r2, [r5, #0x58]
	ldr r0, _0804A874 @ =0xFFFFB700
	adds r2, r2, r0
	ldrb r3, [r5, #0x12]
	ldrb r0, [r5, #0xa]
	lsrs r0, r0, #4
	movs r4, #1
	ands r0, r4
	str r0, [sp]
	adds r0, r5, #0
	bl deathtanz_080a09f4
	ldr r1, _0804A878 @ =0x0000A729
	adds r0, r5, #0
	bl SetMotion
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_0804A84C:
	adds r0, r5, #0
	bl UpdateMotionGraphic
	adds r0, r5, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _0804A8AE
	ldrb r0, [r5, #0x12]
	adds r0, #1
	strb r0, [r5, #0x12]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #2
	bls _0804A87C
_0804A86A:
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
	b _0804A8AE
	.align 2, 0
_0804A874: .4byte 0xFFFFB700
_0804A878: .4byte 0x0000A729
_0804A87C:
	movs r0, #5
	strb r0, [r5, #0xe]
	b _0804A8AE
_0804A882:
	ldr r1, _0804A8B8 @ =0x0000A72A
	adds r0, r5, #0
	bl SetMotion
	movs r0, #0x5a
	strb r0, [r5, #0x12]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_0804A894:
	adds r0, r5, #0
	bl UpdateMotionGraphic
	ldrb r0, [r5, #0x12]
	subs r0, #1
	strb r0, [r5, #0x12]
	lsls r0, r0, #0x18
	lsrs r1, r0, #0x18
	cmp r1, #0
	bne _0804A8AE
	movs r0, #0x12
	strb r0, [r5, #0xd]
	strb r1, [r5, #0xe]
_0804A8AE:
	add sp, #4
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_0804A8B8: .4byte 0x0000A72A
