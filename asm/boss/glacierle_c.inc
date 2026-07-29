	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start glacierle_08059674
glacierle_08059674: @ 0x08059674
	push {r4, r5, r6, lr}
	adds r5, r0, #0
	ldrb r0, [r5, #0xe]
	cmp r0, #0
	beq _08059684
	cmp r0, #1
	beq _0805970A
	b _08059794
_08059684:
	movs r0, #0x97
	bl PlaySound
	ldr r1, _08059728 @ =0x0000B204
	adds r0, r5, #0
	bl SetMotion
	adds r0, r5, #0
	adds r0, #0xc8
	ldr r1, [r5, #0x54]
	ldr r0, [r0]
	subs r1, r1, r0
	str r1, [r5, #0x5c]
	ldr r0, [r5, #0x58]
	ldr r2, _0805972C @ =0xFFFFD000
	adds r0, r0, r2
	adds r2, r5, #0
	adds r2, #0xcc
	ldr r2, [r2]
	subs r0, r0, r2
	str r0, [r5, #0x60]
	asrs r1, r1, #8
	adds r6, r1, #0
	muls r6, r1, r6
	asrs r0, r0, #8
	adds r3, r0, #0
	muls r3, r0, r3
	adds r0, r3, #0
	adds r6, r6, r0
	adds r0, r6, #0
	bl Sqrt
	lsls r0, r0, #0x10
	lsrs r6, r0, #8
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
	adds r1, r0, #0
	str r1, [r5, #0x60]
	lsls r0, r4, #2
	adds r0, r0, r4
	lsls r0, r0, #7
	cmp r0, #0
	bge _080596F0
	adds r0, #0xff
_080596F0:
	asrs r0, r0, #8
	str r0, [r5, #0x5c]
	lsls r0, r1, #2
	adds r0, r0, r1
	lsls r0, r0, #7
	cmp r0, #0
	bge _08059700
	adds r0, #0xff
_08059700:
	asrs r0, r0, #8
	str r0, [r5, #0x60]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_0805970A:
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x5c]
	adds r1, r0, r1
	str r1, [r5, #0x54]
	adds r0, r5, #0
	adds r0, #0xbc
	ldr r0, [r0]
	movs r3, #0x9a
	lsls r3, r3, #8
	adds r2, r0, r3
	cmp r1, r2
	ble _08059730
	str r2, [r5, #0x54]
	b _0805973A
	.align 2, 0
_08059728: .4byte 0x0000B204
_0805972C: .4byte 0xFFFFD000
_08059730:
	ldr r2, _08059774 @ =0xFFFF6600
	adds r0, r0, r2
	cmp r1, r0
	bge _0805973A
	str r0, [r5, #0x54]
_0805973A:
	ldr r0, [r5, #0x60]
	adds r0, #0x20
	str r0, [r5, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _0805974A
	str r1, [r5, #0x60]
_0805974A:
	ldr r0, [r5, #0x58]
	ldr r1, [r5, #0x60]
	adds r2, r0, r1
	str r2, [r5, #0x58]
	cmp r1, #0
	ble _08059778
	ldr r0, [r5, #0x54]
	adds r1, r2, #0
	bl PushoutToUp1
	adds r6, r0, #0
	cmp r6, #0
	bge _0805978E
	ldr r0, [r5, #0x58]
	adds r0, r0, r6
	str r0, [r5, #0x58]
	movs r0, #0
	strb r0, [r5, #0xd]
	strb r0, [r5, #0xe]
	b _0805978E
	.align 2, 0
_08059774: .4byte 0xFFFF6600
_08059778:
	ldr r0, [r5, #0x54]
	ldr r3, _0805979C @ =0xFFFFD000
	adds r1, r2, r3
	bl PushoutToDown1
	adds r6, r0, #0
	cmp r6, #0
	bge _0805978E
	ldr r0, [r5, #0x58]
	adds r0, r0, r6
	str r0, [r5, #0x58]
_0805978E:
	adds r0, r5, #0
	bl UpdateMotionGraphic
_08059794:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_0805979C: .4byte 0xFFFFD000

	thumb_func_start glacierleDeath0
glacierleDeath0: @ 0x080597A0
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #4
	bhi _08059884
	lsls r0, r0, #2
	ldr r1, _080597B4 @ =_080597B8
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_080597B4: .4byte _080597B8
_080597B8: @ jump table
	.4byte _080597CC @ case 0
	.4byte _0805983E @ case 1
	.4byte _0805985C @ case 2
	.4byte _0805986C @ case 3
	.4byte _08059884 @ case 4
_080597CC:
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
	ldr r3, _08059824 @ =gStageRun
	ldrh r2, [r3, #8]
	movs r5, #1
	adds r0, r5, #0
	ands r0, r2
	cmp r0, #0
	beq _08059806
	ldrb r1, [r3, #0x12]
	adds r0, r5, #0
	ands r0, r1
	cmp r0, #0
	bne _08059806
	ldr r0, _08059828 @ =0x0000FFFE
	ands r0, r2
	movs r1, #0x10
	orrs r0, r1
	strh r0, [r3, #8]
_08059806:
	movs r0, #0x50
	strb r0, [r4, #0x12]
	adds r0, r4, #0
	adds r0, #0xb4
	ldr r0, [r0]
	movs r1, #1
	ands r0, r1
	cmp r0, #0
	beq _08059830
	ldr r1, _0805982C @ =0x0000B204
	adds r0, r4, #0
	bl SetMotion
	b _08059838
	.align 2, 0
_08059824: .4byte gStageRun
_08059828: .4byte 0x0000FFFE
_0805982C: .4byte 0x0000B204
_08059830:
	ldr r1, _08059858 @ =0x0000B21D
	adds r0, r4, #0
	bl SetMotion
_08059838:
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0805983E:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	ldr r0, [r4, #0x18]
	ldrb r1, [r0, #9]
	movs r0, #0x80
	ands r0, r1
	cmp r0, #0
	beq _08059884
	b _0805987E
	.align 2, 0
_08059858: .4byte 0x0000B21D
_0805985C:
	ldr r1, _0805988C @ =0x08364B2C
	adds r0, r4, #0
	bl CreateBossExplosion
	str r0, [r4, #0x2c]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0805986C:
	ldr r0, [r4, #0x2c]
	ldrb r0, [r0, #0xc]
	cmp r0, #1
	bls _08059884
	ldr r2, _08059890 @ =gStageRun
	ldrb r1, [r2, #0x12]
	movs r0, #2
	orrs r0, r1
	strb r0, [r2, #0x12]
_0805987E:
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08059884:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_0805988C: .4byte 0x08364B2C
_08059890: .4byte gStageRun

	thumb_func_start glacierleDeath1
glacierleDeath1: @ 0x08059894
	push {r4, r5, r6, lr}
	sub sp, #8
	adds r5, r0, #0
	ldrb r0, [r5, #0xe]
	cmp r0, #4
	bls _080598A2
	b _08059A3A
_080598A2:
	lsls r0, r0, #2
	ldr r1, _080598AC @ =_080598B0
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_080598AC: .4byte _080598B0
_080598B0: @ jump table
	.4byte _080598C4 @ case 0
	.4byte _080599A6 @ case 1
	.4byte _08059A12 @ case 2
	.4byte _08059A22 @ case 3
	.4byte _08059A3A @ case 4
_080598C4:
	movs r0, #0x2f
	bl PlaySound
	adds r0, r5, #0
	adds r0, #0xc2
	ldrb r6, [r0]
	ldr r0, _080599C4 @ =gBossHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	adds r4, r0, #0
	cmp r4, #0
	beq _0805992C
	adds r1, r4, #0
	adds r1, #0x25
	movs r3, #0
	movs r0, #0x18
	strb r0, [r1]
	ldr r2, _080599C8 @ =gBossFnTable
	movs r1, #0x10
	movs r0, #0x10
	strb r0, [r4, #9]
	ldr r0, [r2, #0x40]
	ldr r0, [r0]
	str r0, [r4, #0x14]
	movs r0, #0
	strh r3, [r4, #0x20]
	adds r2, r4, #0
	adds r2, #0x22
	strb r0, [r2]
	ldrb r0, [r4, #0xb]
	orrs r1, r0
	strb r1, [r4, #0xb]
	ldrb r0, [r4, #0x1c]
	strb r0, [r4, #0x1d]
	ldr r0, [r5, #0x54]
	str r0, [r4, #0x54]
	ldr r0, [r5, #0x58]
	str r0, [r4, #0x58]
	movs r0, #0x80
	lsls r0, r0, #1
	lsls r1, r6, #9
	subs r0, r0, r1
	str r0, [r4, #0x5c]
	str r5, [r4, #0x28]
	movs r1, #1
	strb r1, [r4, #0x10]
	ldrb r0, [r5, #0xa]
	lsrs r0, r0, #4
	ands r0, r1
	eors r0, r6
	strb r0, [r4, #0x13]
_0805992C:
	ldr r1, _080599CC @ =0x0000B203
	adds r0, r5, #0
	bl SetMotion
	adds r0, r5, #0
	adds r0, #0x8c
	movs r1, #0
	str r1, [r0]
	adds r0, #4
	str r1, [r0]
	adds r0, #4
	strb r1, [r0]
	ldrb r1, [r5, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r5, #0xa]
	ldr r3, _080599D0 @ =gStageRun
	ldrh r2, [r3, #8]
	movs r4, #1
	adds r0, r4, #0
	ands r0, r2
	cmp r0, #0
	beq _0805996E
	ldrb r1, [r3, #0x12]
	adds r0, r4, #0
	ands r0, r1
	cmp r0, #0
	bne _0805996E
	ldr r0, _080599D4 @ =0x0000FFFE
	ands r0, r2
	movs r1, #0x10
	orrs r0, r1
	strh r0, [r3, #8]
_0805996E:
	movs r0, #0x80
	lsls r0, r0, #1
	lsls r1, r6, #9
	subs r0, r0, r1
	str r0, [r5, #0x5c]
	ldr r0, [r5, #0x54]
	movs r1, #0x80
	lsls r1, r1, #4
	adds r0, r0, r1
	lsls r1, r6, #0xc
	subs r0, r0, r1
	str r0, [sp]
	ldr r0, [r5, #0x58]
	ldr r1, _080599D8 @ =0xFFFFD800
	adds r0, r0, r1
	str r0, [sp, #4]
	movs r2, #0x80
	lsls r2, r2, #2
	movs r0, #0
	mov r1, sp
	adds r3, r6, #0
	bl FUN_080b2b40
	movs r0, #0x32
	strb r0, [r5, #0x12]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_080599A6:
	ldr r0, [r5, #0x54]
	ldr r2, [r5, #0x5c]
	adds r0, r0, r2
	str r0, [r5, #0x54]
	adds r0, r5, #0
	adds r0, #0xc2
	ldrb r3, [r0]
	ldrb r1, [r5, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _080599DC
	cmp r3, #1
	bne _080599E0
	b _080599E4
	.align 2, 0
_080599C4: .4byte gBossHeaderPtr
_080599C8: .4byte gBossFnTable
_080599CC: .4byte 0x0000B203
_080599D0: .4byte gStageRun
_080599D4: .4byte 0x0000FFFE
_080599D8: .4byte 0xFFFFD800
_080599DC:
	cmp r3, #0
	beq _080599E4
_080599E0:
	movs r0, #0xfa
	b _080599E6
_080599E4:
	movs r0, #0xf6
_080599E6:
	muls r0, r2, r0
	cmp r0, #0
	bge _080599EE
	adds r0, #0xff
_080599EE:
	asrs r0, r0, #8
	str r0, [r5, #0x5c]
	ldrb r0, [r5, #0x12]
	subs r0, #1
	strb r0, [r5, #0x12]
	ldr r0, [r5, #0x18]
	ldrb r1, [r0, #9]
	movs r0, #0x80
	ands r0, r1
	cmp r0, #0
	beq _08059A0A
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_08059A0A:
	adds r0, r5, #0
	bl UpdateMotionGraphic
	b _08059A3A
_08059A12:
	ldr r1, _08059A44 @ =0x08364B34
	adds r0, r5, #0
	bl CreateBossExplosion
	str r0, [r5, #0x2c]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_08059A22:
	ldr r0, [r5, #0x2c]
	ldrb r0, [r0, #0xc]
	cmp r0, #1
	bls _08059A3A
	ldr r2, _08059A48 @ =gStageRun
	ldrb r1, [r2, #0x12]
	movs r0, #2
	orrs r0, r1
	strb r0, [r2, #0x12]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_08059A3A:
	add sp, #8
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_08059A44: .4byte 0x08364B34
_08059A48: .4byte gStageRun
