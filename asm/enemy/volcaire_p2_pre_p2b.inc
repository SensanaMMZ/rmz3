	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_08077910
FUN_08077910: @ 0x08077910
	push {r4, r5, r6, r7, lr}
	adds r4, r0, #0
	ldr r7, [r4, #0x28]
	ldrb r0, [r4, #0xe]
	cmp r0, #5
	bls _0807791E
	b _08077A2C
_0807791E:
	lsls r0, r0, #2
	ldr r1, _08077928 @ =_0807792C
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_08077928: .4byte _0807792C
_0807792C: @ jump table
	.4byte _08077944 @ case 0
	.4byte _080779FE @ case 1
	.4byte _080779A8 @ case 2
	.4byte _080779FE @ case 3
	.4byte _08077A18 @ case 4
	.4byte _08077A2C @ case 5
_08077944:
	ldrb r0, [r4, #0x12]
	cmp r0, #0
	bne _08077968
	ldr r1, _08077960 @ =0x00002E02
	adds r0, r4, #0
	bl SetMotion
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _08077964 @ =0x08367300
	bl SetDDP
	b _0807797A
	.align 2, 0
_08077960: .4byte 0x00002E02
_08077964: .4byte 0x08367300
_08077968:
	ldr r1, _0807799C @ =0x00002E03
	adds r0, r4, #0
	bl SetMotion
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _080779A0 @ =0x08367330
	bl SetDDP
_0807797A:
	movs r0, #8
	strb r0, [r4, #0x13]
	ldrb r0, [r4, #0x12]
	lsls r1, r0, #0xf
	ldr r2, _080779A4 @ =0xFFFFC000
	adds r0, r1, r2
	str r0, [r4, #0x5c]
	cmp r0, #0
	bge _08077990
	adds r2, #0x1f
	adds r0, r1, r2
_08077990:
	asrs r0, r0, #5
	str r0, [r4, #0x5c]
	movs r0, #0
	str r0, [r4, #0x60]
	b _080779F8
	.align 2, 0
_0807799C: .4byte 0x00002E03
_080779A0: .4byte 0x08367330
_080779A4: .4byte 0xFFFFC000
_080779A8:
	movs r0, #8
	strb r0, [r4, #0x13]
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _080779CC @ =0x08367360
	bl SetDDP
	ldr r1, _080779D0 @ =0x00002E04
	adds r0, r4, #0
	bl SetMotion
	ldrb r2, [r4, #0x12]
	cmp r2, #0
	beq _080779D4
	ldrb r0, [r4, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _080779DA
	.align 2, 0
_080779CC: .4byte 0x08367360
_080779D0: .4byte 0x00002E04
_080779D4:
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
_080779DA:
	strb r0, [r4, #0xa]
	movs r1, #1
	ands r1, r2
	adds r0, r4, #0
	adds r0, #0x4c
	strb r1, [r0]
	adds r3, r4, #0
	adds r3, #0x4a
	lsls r1, r1, #4
	ldrb r2, [r3]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r1
	strb r0, [r3]
_080779F8:
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080779FE:
	ldrb r0, [r4, #0x13]
	subs r0, #1
	strb r0, [r4, #0x13]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _08077A10
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08077A10:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	b _08077A2C
_08077A18:
	ldr r1, _08077A7C @ =0x00002E05
	adds r0, r4, #0
	bl SetMotion
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08077A2C:
	ldr r0, [r4, #0x60]
	adds r0, #0x40
	str r0, [r4, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _08077A3C
	str r1, [r4, #0x60]
_08077A3C:
	ldr r1, [r4, #0x58]
	ldr r0, [r4, #0x60]
	adds r1, r1, r0
	str r1, [r4, #0x58]
	ldr r0, [r4, #0x54]
	bl PushoutToUp1
	adds r6, r0, #0
	adds r5, r4, #0
	adds r5, #0xb9
	cmp r6, #0
	bge _08077A84
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	bl GetMetatileAttr
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	movs r1, #0x10
	ands r0, r1
	cmp r0, #0
	bne _08077A80
	ldrb r1, [r5]
	cmp r1, #0
	bne _08077A80
	ldr r0, [r4, #0x58]
	adds r0, r0, r6
	str r0, [r4, #0x58]
	movs r0, #4
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
	b _08077A84
	.align 2, 0
_08077A7C: .4byte 0x00002E05
_08077A80:
	movs r0, #1
	strb r0, [r5]
_08077A84:
	ldrb r0, [r5]
	cmp r0, #0
	bne _08077A92
	ldr r1, [r4, #0x5c]
	adds r0, r4, #0
	bl FUN_08077110
_08077A92:
	ldr r0, _08077AF0 @ =gStageRun+232
	adds r1, r4, #0
	adds r1, #0x54
	bl CalcFromCamera
	movs r1, #0xc0
	lsls r1, r1, #7
	cmp r0, r1
	bls _08077AE8
	cmp r7, #0
	beq _08077AB2
	adds r1, r7, #0
	adds r1, #0xb8
	ldrb r0, [r1]
	subs r0, #1
	strb r0, [r1]
_08077AB2:
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
	ldr r1, _08077AF4 @ =gEnemyFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r4, #0x14]
_08077AE8:
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_08077AF0: .4byte gStageRun+232
_08077AF4: .4byte gEnemyFnTable
