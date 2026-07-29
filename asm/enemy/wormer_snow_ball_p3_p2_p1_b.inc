	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_0807b5b8
FUN_0807b5b8: @ 0x0807B5B8
	push {r4, r5, lr}
	adds r5, r0, #0
	ldrb r0, [r5, #0xe]
	cmp r0, #1
	beq _0807B5F4
	cmp r0, #1
	bgt _0807B5CC
	cmp r0, #0
	beq _0807B5D6
	b _0807B7AC
_0807B5CC:
	cmp r0, #2
	beq _0807B644
	cmp r0, #3
	beq _0807B660
	b _0807B7AC
_0807B5D6:
	adds r0, r5, #0
	adds r0, #0x74
	ldr r1, _0807B63C @ =0x0836785C
	bl SetDDP
	ldr r1, _0807B640 @ =0x00004004
	adds r0, r5, #0
	bl SetMotion
	movs r0, #0xc0
	lsls r0, r0, #3
	str r0, [r5, #0x68]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_0807B5F4:
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x5c]
	adds r0, r0, r1
	str r0, [r5, #0x54]
	ldr r0, [r5, #0x60]
	adds r0, #0x20
	str r0, [r5, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _0807B60C
	str r1, [r5, #0x60]
_0807B60C:
	ldr r1, [r5, #0x58]
	ldr r0, [r5, #0x60]
	adds r1, r1, r0
	str r1, [r5, #0x58]
	ldr r0, [r5, #0x54]
	ldr r2, [r5, #0x68]
	adds r1, r1, r2
	bl PushoutToUp1
	adds r2, r0, #0
	cmp r2, #0
	bge _0807B634
	movs r0, #0
	str r0, [r5, #0x60]
	ldr r0, [r5, #0x58]
	adds r0, r0, r2
	str r0, [r5, #0x58]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_0807B634:
	adds r0, r5, #0
	bl UpdateMotionGraphic
	b _0807B7AC
	.align 2, 0
_0807B63C: .4byte 0x0836785C
_0807B640: .4byte 0x00004004
_0807B644:
	adds r0, r5, #0
	bl InitScalerotMotion1
	movs r1, #0
	movs r0, #0x80
	strb r0, [r5, #0x12]
	str r1, [r5, #0x64]
	ldr r1, _0807B71C @ =0x00004005
	adds r0, r5, #0
	bl SetMotion
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_0807B660:
	adds r4, r5, #0
	adds r4, #0x74
	ldrb r0, [r5, #0x12]
	subs r0, #0x80
	movs r1, #0x15
	bl __divsi3
	lsls r1, r0, #1
	adds r1, r1, r0
	lsls r1, r1, #4
	ldr r0, _0807B720 @ =0x0836785C
	adds r1, r1, r0
	adds r0, r4, #0
	bl SetDDP
	ldrb r1, [r5, #0x12]
	adds r0, r1, #0
	cmp r0, #0xff
	beq _0807B68A
	adds r0, r1, #1
	strb r0, [r5, #0x12]
_0807B68A:
	ldrb r1, [r5, #0x12]
	adds r0, r5, #0
	adds r0, #0x50
	strh r1, [r0]
	ldrb r0, [r5, #0x12]
	adds r1, r5, #0
	adds r1, #0x52
	strh r0, [r1]
	ldrb r1, [r5, #0x12]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	str r0, [r5, #0x68]
	ldr r0, [r5, #0x64]
	ldr r1, [r5, #0x5c]
	adds r0, r0, r1
	str r0, [r5, #0x64]
	asrs r0, r0, #8
	lsls r0, r0, #1
	adds r1, r5, #0
	adds r1, #0x24
	strb r0, [r1]
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x5c]
	adds r0, r0, r1
	str r0, [r5, #0x54]
	ldr r0, [r5, #0x60]
	adds r0, #0x30
	str r0, [r5, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _0807B6CE
	str r1, [r5, #0x60]
_0807B6CE:
	ldr r1, [r5, #0x58]
	ldr r0, [r5, #0x60]
	adds r1, r1, r0
	str r1, [r5, #0x58]
	ldr r0, [r5, #0x54]
	ldr r2, [r5, #0x68]
	adds r1, r1, r2
	bl PushoutToUp1
	adds r2, r0, #0
	cmp r2, #0
	bge _0807B75E
	movs r0, #0
	str r0, [r5, #0x60]
	ldr r0, [r5, #0x58]
	adds r2, r0, r2
	str r2, [r5, #0x58]
	ldr r0, [r5, #0x5c]
	cmp r0, #0
	bge _0807B724
	ldr r0, [r5, #0x54]
	subs r0, #0x30
	ldr r1, [r5, #0x68]
	adds r1, r2, r1
	bl FUN_08009f6c
	adds r2, r0, #0
	ldr r0, [r5, #0x58]
	ldr r1, [r5, #0x68]
	adds r0, r0, r1
	subs r2, r2, r0
	cmp r2, #0
	bge _0807B714
	adds r0, r2, #3
	asrs r2, r0, #2
_0807B714:
	ldr r0, [r5, #0x5c]
	subs r0, r0, r2
	b _0807B746
	.align 2, 0
_0807B71C: .4byte 0x00004005
_0807B720: .4byte 0x0836785C
_0807B724:
	ldr r0, [r5, #0x54]
	adds r0, #0x30
	ldr r1, [r5, #0x68]
	adds r1, r2, r1
	bl FUN_08009f6c
	adds r2, r0, #0
	ldr r0, [r5, #0x58]
	ldr r1, [r5, #0x68]
	adds r0, r0, r1
	subs r2, r2, r0
	cmp r2, #0
	bge _0807B742
	adds r0, r2, #3
	asrs r2, r0, #2
_0807B742:
	ldr r0, [r5, #0x5c]
	adds r0, r0, r2
_0807B746:
	str r0, [r5, #0x5c]
	ldr r0, [r5, #0x5c]
	ldr r1, _0807B7B4 @ =0xFFFFFE00
	cmp r0, r1
	bge _0807B752
	str r1, [r5, #0x5c]
_0807B752:
	ldr r0, [r5, #0x5c]
	movs r1, #0x80
	lsls r1, r1, #2
	cmp r0, r1
	ble _0807B75E
	str r1, [r5, #0x5c]
_0807B75E:
	adds r0, r5, #0
	bl UpdateMotionGraphic
	ldr r0, _0807B7B8 @ =gStageRun+232
	adds r1, r5, #0
	adds r1, #0x54
	bl CalcFromCamera
	movs r1, #0x80
	lsls r1, r1, #6
	cmp r0, r1
	bls _0807B7AC
	ldrb r1, [r5, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r2, #0
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r5, #0xa]
	adds r0, r5, #0
	adds r0, #0x8c
	str r2, [r0]
	adds r0, #4
	str r2, [r0]
	adds r0, #4
	strb r2, [r0]
	ldrb r1, [r5, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r5, #0xa]
	ldr r1, _0807B7BC @ =gEnemyFnTable
	ldrb r0, [r5, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r5, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r5, #0x14]
_0807B7AC:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_0807B7B4: .4byte 0xFFFFFE00
_0807B7B8: .4byte gStageRun+232
_0807B7BC: .4byte gEnemyFnTable
