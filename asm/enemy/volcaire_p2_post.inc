	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_08077b38
FUN_08077b38: @ 0x08077B38
	push {r4, r5, r6, lr}
	adds r4, r0, #0
	ldr r6, [r4, #0x28]
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _08077B4A
	cmp r0, #1
	beq _08077B78
	b _08077C96
_08077B4A:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _08077BA0 @ =0x08367390
	bl SetDDP
	ldr r1, _08077BA4 @ =0x00002E06
	adds r0, r4, #0
	bl SetMotion
	ldr r0, _08077BA8 @ =0xFFFFFE80
	str r0, [r4, #0x5c]
	adds r2, r0, #0
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _08077B70
	movs r2, #0xc0
	lsls r2, r2, #1
_08077B70:
	str r2, [r4, #0x5c]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08077B78:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	bl FUN_08009f6c
	adds r2, r0, #0
	ldr r0, [r4, #0x58]
	subs r0, r2, r0
	movs r1, #0x80
	lsls r1, r1, #4
	cmp r0, r1
	ble _08077BAC
	movs r1, #0
	movs r0, #6
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
	b _08077C3A
	.align 2, 0
_08077BA0: .4byte 0x08367390
_08077BA4: .4byte 0x00002E06
_08077BA8: .4byte 0xFFFFFE80
_08077BAC:
	str r2, [r4, #0x58]
	ldrb r1, [r4, #0xa]
	movs r5, #0x10
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	bne _08077BEC
	ldr r0, [r4, #0x54]
	ldr r1, _08077BE4 @ =0xFFFFF600
	adds r0, r0, r1
	ldr r3, _08077BE8 @ =0xFFFFF800
	adds r1, r2, r3
	bl PushoutToRight1
	cmp r0, #0
	ble _08077C3A
	ldr r0, [r4, #0x5c]
	rsbs r0, r0, #0
	str r0, [r4, #0x5c]
	ldrb r2, [r4, #0xa]
	lsrs r0, r2, #4
	movs r1, #1
	bics r1, r0
	cmp r1, #0
	beq _08077C1C
	adds r0, r5, #0
	orrs r0, r2
	b _08077C20
	.align 2, 0
_08077BE4: .4byte 0xFFFFF600
_08077BE8: .4byte 0xFFFFF800
_08077BEC:
	ldr r0, [r4, #0x54]
	movs r1, #0xa0
	lsls r1, r1, #4
	adds r0, r0, r1
	ldr r3, _08077C18 @ =0xFFFFF800
	adds r1, r2, r3
	bl PushoutToLeft1
	cmp r0, #0
	bge _08077C3A
	ldr r0, [r4, #0x5c]
	rsbs r0, r0, #0
	str r0, [r4, #0x5c]
	ldrb r2, [r4, #0xa]
	lsrs r0, r2, #4
	movs r1, #1
	bics r1, r0
	cmp r1, #0
	beq _08077C1C
	adds r0, r2, #0
	orrs r0, r5
	b _08077C20
	.align 2, 0
_08077C18: .4byte 0xFFFFF800
_08077C1C:
	movs r0, #0xef
	ands r0, r2
_08077C20:
	strb r0, [r4, #0xa]
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
_08077C3A:
	ldr r0, _08077C9C @ =gStageRun+232
	adds r1, r4, #0
	adds r1, #0x54
	bl CalcFromCamera
	movs r1, #0xc0
	lsls r1, r1, #7
	cmp r0, r1
	bls _08077C90
	cmp r6, #0
	beq _08077C5A
	adds r1, r6, #0
	adds r1, #0xb8
	ldrb r0, [r1]
	subs r0, #1
	strb r0, [r1]
_08077C5A:
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
	ldr r1, _08077CA0 @ =gEnemyFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r4, #0x14]
_08077C90:
	adds r0, r4, #0
	bl UpdateMotionGraphic
_08077C96:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_08077C9C: .4byte gStageRun+232
_08077CA0: .4byte gEnemyFnTable

	thumb_func_start FUN_08077ca4
FUN_08077ca4: @ 0x08077CA4
	push {r4, r5, r6, r7, lr}
	adds r4, r0, #0
	ldr r7, [r4, #0x28]
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _08077CB6
	cmp r0, #1
	beq _08077CBE
	b _08077DC0
_08077CB6:
	str r0, [r4, #0x60]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08077CBE:
	adds r0, r4, #0
	adds r0, #0xb9
	ldrb r1, [r0]
	adds r6, r0, #0
	cmp r1, #0
	bne _08077D0C
	ldr r1, [r4, #0x54]
	ldr r0, [r4, #0x5c]
	adds r2, r1, r0
	str r2, [r4, #0x54]
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	bne _08077CF4
	ldr r1, [r4, #0x58]
	ldr r0, _08077CF0 @ =0xFFFFF800
	adds r1, r1, r0
	adds r0, r2, #0
	bl PushoutToRight1
	adds r5, r0, #0
	cmp r5, #0
	ble _08077D0C
	b _08077D06
	.align 2, 0
_08077CF0: .4byte 0xFFFFF800
_08077CF4:
	ldr r1, [r4, #0x58]
	ldr r0, _08077D5C @ =0xFFFFF800
	adds r1, r1, r0
	adds r0, r2, #0
	bl PushoutToLeft1
	adds r5, r0, #0
	cmp r5, #0
	bge _08077D0C
_08077D06:
	ldr r0, [r4, #0x54]
	adds r0, r0, r5
	str r0, [r4, #0x54]
_08077D0C:
	ldr r0, [r4, #0x60]
	adds r0, #0x40
	str r0, [r4, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _08077D1C
	str r1, [r4, #0x60]
_08077D1C:
	ldr r1, [r4, #0x58]
	ldr r0, [r4, #0x60]
	adds r1, r1, r0
	str r1, [r4, #0x58]
	ldr r0, [r4, #0x54]
	bl PushoutToUp1
	adds r5, r0, #0
	cmp r5, #0
	bge _08077D64
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	bl GetMetatileAttr
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	movs r1, #0x10
	ands r0, r1
	cmp r0, #0
	bne _08077D60
	ldrb r0, [r6]
	cmp r0, #0
	bne _08077D60
	ldr r0, [r4, #0x58]
	adds r0, r0, r5
	str r0, [r4, #0x58]
	movs r0, #5
	strb r0, [r4, #0xd]
	movs r0, #1
	strb r0, [r4, #0xe]
	b _08077D64
	.align 2, 0
_08077D5C: .4byte 0xFFFFF800
_08077D60:
	movs r0, #1
	strb r0, [r6]
_08077D64:
	ldr r0, _08077DC8 @ =gStageRun+232
	adds r1, r4, #0
	adds r1, #0x54
	bl CalcFromCamera
	movs r1, #0xc0
	lsls r1, r1, #7
	cmp r0, r1
	bls _08077DBA
	cmp r7, #0
	beq _08077D84
	adds r1, r7, #0
	adds r1, #0xb8
	ldrb r0, [r1]
	subs r0, #1
	strb r0, [r1]
_08077D84:
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
	ldr r1, _08077DCC @ =gEnemyFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r4, #0x14]
_08077DBA:
	adds r0, r4, #0
	bl UpdateMotionGraphic
_08077DC0:
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_08077DC8: .4byte gStageRun+232
_08077DCC: .4byte gEnemyFnTable

	thumb_func_start FUN_08077dd0
FUN_08077dd0: @ 0x08077DD0
	push {r4, r5, r6, lr}
	adds r5, r0, #0
	ldrb r0, [r5, #0xe]
	cmp r0, #0
	beq _08077DE0
	cmp r0, #1
	beq _08077E96
	b _08077F06
_08077DE0:
	ldrb r0, [r5, #0x10]
	cmp r0, #1
	bne _08077E00
	adds r0, r5, #0
	adds r0, #0x74
	ldr r1, _08077DFC @ =0x083673C0
	bl SetDDP
	movs r1, #0xb8
	lsls r1, r1, #6
	adds r0, r5, #0
	bl SetMotion
	b _08077E16
	.align 2, 0
_08077DFC: .4byte 0x083673C0
_08077E00:
	adds r0, r5, #0
	adds r0, #0x74
	ldr r1, _08077E78 @ =0x083673D8
	bl SetDDP
	ldr r1, _08077E7C @ =0x00002E05
	adds r0, r5, #0
	movs r2, #4
	movs r3, #1
	bl GotoMotion
_08077E16:
	ldr r0, _08077E80 @ =pZero2
	ldr r2, [r0]
	ldr r1, [r5, #0x54]
	ldr r0, [r2, #0x54]
	subs r1, r1, r0
	str r1, [r5, #0x5c]
	ldr r0, [r5, #0x58]
	ldr r3, _08077E84 @ =0xFFFFE800
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
	beq _08077E88
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
	b _08077E90
	.align 2, 0
_08077E78: .4byte 0x083673D8
_08077E7C: .4byte 0x00002E05
_08077E80: .4byte pZero2
_08077E84: .4byte 0xFFFFE800
_08077E88:
	movs r0, #0xc0
	lsls r0, r0, #3
	str r0, [r5, #0x5c]
	str r6, [r5, #0x60]
_08077E90:
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_08077E96:
	adds r0, r5, #0
	adds r0, #0xb9
	ldrb r1, [r0]
	adds r4, r0, #0
	cmp r1, #0
	bne _08077EAA
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x5c]
	adds r0, r0, r1
	str r0, [r5, #0x54]
_08077EAA:
	ldr r0, [r5, #0x60]
	adds r0, #0x40
	str r0, [r5, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _08077EBA
	str r1, [r5, #0x60]
_08077EBA:
	ldr r0, [r5, #0x58]
	ldr r1, [r5, #0x60]
	adds r2, r0, r1
	str r2, [r5, #0x58]
	cmp r1, #0
	ble _08077F00
	ldr r0, [r5, #0x54]
	adds r1, r2, #0
	bl PushoutToUp1
	adds r6, r0, #0
	cmp r6, #0
	bge _08077F00
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x58]
	bl GetMetatileAttr
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	movs r1, #0x10
	ands r0, r1
	cmp r0, #0
	bne _08077EFC
	ldrb r0, [r4]
	cmp r0, #0
	bne _08077EFC
	ldr r0, [r5, #0x58]
	adds r0, r0, r6
	str r0, [r5, #0x58]
	adds r0, r5, #0
	bl MaybeKillVolcaire
	b _08077F06
_08077EFC:
	movs r0, #1
	strb r0, [r4]
_08077F00:
	adds r0, r5, #0
	bl UpdateMotionGraphic
_08077F06:
	pop {r4, r5, r6}
	pop {r0}
	bx r0

