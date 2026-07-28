	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_0807762c
FUN_0807762c: @ 0x0807762C
	push {r4, r5, lr}
	adds r4, r0, #0
	adds r5, r4, #0
	adds r5, #0xb4
	ldr r0, [r5]
	cmp r0, #0
	beq _08077642
	bl isKilled
	cmp r0, #0
	beq _0807768A
_08077642:
	movs r0, #0
	str r0, [r5]
	ldrb r0, [r4, #0x10]
	cmp r0, #1
	bne _0807765C
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _08077658 @ =0x083672D0
	bl SetDDP
	b _08077666
	.align 2, 0
_08077658: .4byte 0x083672D0
_0807765C:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _08077680 @ =0x08367360
	bl SetDDP
_08077666:
	adds r0, r4, #0
	bl IsFrozen
	adds r1, r0, #0
	cmp r1, #0
	bne _0807768A
	ldrb r0, [r4, #0x10]
	cmp r0, #1
	bne _08077684
	movs r0, #2
	strb r0, [r4, #0xd]
	strb r0, [r4, #0xe]
	b _0807768A
	.align 2, 0
_08077680: .4byte 0x08367360
_08077684:
	movs r0, #3
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_0807768A:
	adds r0, r4, #0
	adds r0, #0x8c
	ldr r0, [r0]
	ldr r1, _080776A8 @ =0x00020001
	ands r0, r1
	cmp r0, r1
	bne _080776A0
	movs r1, #0
	movs r0, #7
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_080776A0:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080776A8: .4byte 0x00020001

	thumb_func_start FUN_080776ac
FUN_080776ac: @ 0x080776AC
	push {r4, r5, r6, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _080776BC
	cmp r0, #1
	beq _080776FC
	b _080777BE
_080776BC:
	ldrb r0, [r4, #0x10]
	cmp r0, #1
	bne _080776DC
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _080776D8 @ =0x083672E8
	bl SetDDP
	movs r1, #0xb8
	lsls r1, r1, #6
	adds r0, r4, #0
	bl SetMotion
	b _080776F2
	.align 2, 0
_080776D8: .4byte 0x083672E8
_080776DC:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _08077750 @ =0x08367378
	bl SetDDP
	ldr r1, _08077754 @ =0x00002E05
	adds r0, r4, #0
	movs r2, #4
	movs r3, #1
	bl GotoMotion
_080776F2:
	movs r0, #0
	str r0, [r4, #0x60]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080776FC:
	adds r0, r4, #0
	bl IsFrozen
	cmp r0, #0
	bne _080777B8
	ldr r0, [r4, #0x60]
	adds r0, #0x40
	str r0, [r4, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _08077716
	str r1, [r4, #0x60]
_08077716:
	ldr r1, [r4, #0x58]
	ldr r0, [r4, #0x60]
	adds r1, r1, r0
	str r1, [r4, #0x58]
	ldr r0, [r4, #0x54]
	bl PushoutToUp1
	adds r5, r0, #0
	cmp r5, #0
	bge _080777B8
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	bl GetMetatileAttr
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	movs r1, #0x10
	ands r0, r1
	adds r6, r4, #0
	adds r6, #0xb9
	cmp r0, #0
	bne _08077758
	ldrb r0, [r6]
	cmp r0, #0
	bne _08077758
	ldr r0, [r4, #0x58]
	adds r0, r0, r5
	str r0, [r4, #0x58]
	b _080777B8
	.align 2, 0
_08077750: .4byte 0x08367378
_08077754: .4byte 0x00002E05
_08077758:
	ldr r0, _080777C4 @ =gStageRun+232
	adds r1, r4, #0
	adds r1, #0x54
	bl CalcFromCamera
	movs r1, #0x80
	lsls r1, r1, #7
	cmp r0, r1
	bls _080777B4
	ldrb r0, [r4, #0x10]
	cmp r0, #2
	bne _0807777E
	ldr r1, [r4, #0x28]
	cmp r1, #0
	beq _0807777E
	adds r1, #0xb8
	ldrb r0, [r1]
	subs r0, #1
	strb r0, [r1]
_0807777E:
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
	ldr r1, _080777C8 @ =gEnemyFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r4, #0x14]
_080777B4:
	movs r0, #1
	strb r0, [r6]
_080777B8:
	adds r0, r4, #0
	bl UpdateMotionGraphic
_080777BE:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_080777C4: .4byte gStageRun+232
_080777C8: .4byte gEnemyFnTable

