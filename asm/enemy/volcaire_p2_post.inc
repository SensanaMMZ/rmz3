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
