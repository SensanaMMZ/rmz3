	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_08094bf0
FUN_08094bf0: @ 0x08094BF0
	push {r4, r5, lr}
	sub sp, #8
	adds r4, r0, #0
	adds r5, r4, #0
	adds r5, #0x8c
	ldr r0, [r5]
	movs r1, #0x80
	lsls r1, r1, #4
	ands r0, r1
	cmp r0, #0
	beq _08094C16
	ldr r0, _08094C70 @ =pZero2
	ldr r0, [r0]
	adds r0, #0x8c
	ldr r0, [r0]
	movs r1, #1
	ands r0, r1
	cmp r0, #0
	beq _08094C68
_08094C16:
	movs r0, #0x3f
	bl PlaySound
	ldr r0, [r4, #0x54]
	str r0, [sp]
	ldr r0, [r4, #0x58]
	ldr r1, _08094C74 @ =0xFFFFF000
	adds r0, r0, r1
	str r0, [sp, #4]
	ldr r2, _08094C78 @ =0x08369F62
	adds r0, r4, #0
	mov r1, sp
	movs r3, #4
	bl FUN_080b7ffc
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r2, #0
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r4, #0xa]
	str r2, [r5]
	adds r0, r4, #0
	adds r0, #0x90
	str r2, [r0]
	adds r0, #4
	strb r2, [r0]
	ldrb r1, [r4, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r4, #0xa]
	ldr r1, _08094C7C @ =gEnemyFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r4, #0x14]
_08094C68:
	add sp, #8
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_08094C70: .4byte pZero2
_08094C74: .4byte 0xFFFFF000
_08094C78: .4byte 0x08369F62
_08094C7C: .4byte gEnemyFnTable

	thumb_func_start FUN_08094c80
FUN_08094c80: @ 0x08094C80
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #5
	bhi _08094D40
	lsls r0, r0, #2
	ldr r1, _08094C94 @ =_08094C98
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_08094C94: .4byte _08094C98
_08094C98: @ jump table
	.4byte _08094CB0 @ case 0
	.4byte _08094CC2 @ case 1
	.4byte _08094CD0 @ case 2
	.4byte _08094CE4 @ case 3
	.4byte _08094D0A @ case 4
	.4byte _08094D14 @ case 5
_08094CB0:
	movs r0, #2
	strb r0, [r4, #0x13]
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
	strb r0, [r4, #0xa]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08094CC2:
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _08094D40
	b _08094CFC
_08094CD0:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	ldrb r2, [r4, #0x10]
	bl FUN_08094a54
	movs r0, #0x1e
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08094CE4:
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _08094D40
	ldrb r0, [r4, #0x13]
	subs r0, #1
	strb r0, [r4, #0x13]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _08094D04
_08094CFC:
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
	b _08094D40
_08094D04:
	movs r0, #2
	strb r0, [r4, #0xe]
	b _08094D40
_08094D0A:
	movs r0, #0x3c
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08094D14:
	ldrb r0, [r4, #0x12]
	movs r1, #9
	bl __umodsi3
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _08094D2C
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	ldrb r2, [r4, #0x10]
	bl FUN_080949d4
_08094D2C:
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0
	bne _08094D40
	strb r0, [r4, #0xe]
	movs r0, #0x78
	strb r0, [r4, #0x12]
_08094D40:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start FUN_08094d48
FUN_08094d48: @ 0x08094D48
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r5, [r4, #0xe]
	cmp r5, #0
	beq _08094D58
	cmp r5, #1
	beq _08094D6A
	b _08094DFC
_08094D58:
	movs r1, #0xc8
	lsls r1, r1, #8
	adds r0, r4, #0
	bl SetMotion
	str r5, [r4, #0x68]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08094D6A:
	ldr r0, _08094D84 @ =pZero2
	ldr r0, [r0]
	adds r0, #0x94
	ldrb r0, [r0]
	cmp r0, #0
	beq _08094D8C
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _08094D88 @ =0x08369EFC
	bl SetDDP
	b _08094D96
	.align 2, 0
_08094D84: .4byte pZero2
_08094D88: .4byte 0x08369EFC
_08094D8C:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _08094E04 @ =0x08369F14
	bl SetDDP
_08094D96:
	ldr r1, [r4, #0x54]
	ldr r0, [r4, #0x5c]
	adds r5, r1, r0
	str r5, [r4, #0x54]
	ldr r1, [r4, #0x58]
	ldr r0, [r4, #0x60]
	adds r3, r1, r0
	str r3, [r4, #0x58]
	ldr r0, [r4, #0x68]
	ldr r1, [r4, #0x64]
	adds r0, r0, r1
	str r0, [r4, #0x68]
	movs r1, #0xe0
	lsls r1, r1, #6
	cmp r0, r1
	ble _08094DF6
	ldrb r2, [r4, #0x11]
	adds r0, r5, #0
	adds r1, r3, #0
	bl FUN_08094a54
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
	ldr r1, _08094E08 @ =gEnemyFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r4, #0x14]
_08094DF6:
	adds r0, r4, #0
	bl UpdateMotionGraphic
_08094DFC:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_08094E04: .4byte 0x08369F14
_08094E08: .4byte gEnemyFnTable

	thumb_func_start FUN_08094e0c
FUN_08094e0c: @ 0x08094E0C
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #1
	beq _08094E34
	cmp r0, #1
	bgt _08094E20
	cmp r0, #0
	beq _08094E26
	b _08094E96
_08094E20:
	cmp r0, #2
	beq _08094E60
	b _08094E96
_08094E26:
	ldr r1, _08094E5C @ =0x0000C801
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08094E34:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	ldr r0, [r4, #0x58]
	ldr r1, [r4, #0x60]
	adds r0, r0, r1
	str r0, [r4, #0x58]
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _08094E96
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
	b _08094E96
	.align 2, 0
_08094E5C: .4byte 0x0000C801
_08094E60:
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
	ldr r1, _08094E9C @ =gEnemyFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r4, #0x14]
_08094E96:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_08094E9C: .4byte gEnemyFnTable

	thumb_func_start FUN_08094ea0
FUN_08094ea0: @ 0x08094EA0
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r5, [r4, #0xe]
	cmp r5, #0
	beq _08094EB0
	cmp r5, #1
	beq _08094EDA
	b _08094F38
_08094EB0:
	adds r1, r4, #0
	adds r1, #0x25
	movs r0, #0xf
	strb r0, [r1]
	movs r0, #0x40
	bl PlaySound
	strb r5, [r4, #0x12]
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _08094F14 @ =0x08369F2C
	bl SetDDP
	movs r1, #0xb0
	lsls r1, r1, #7
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08094EDA:
	ldr r2, _08094F18 @ =pZero2
	ldr r0, [r2]
	ldr r1, _08094F1C @ =0x00000143
	adds r3, r0, r1
	ldrb r1, [r3]
	movs r0, #0x10
	rsbs r0, r0, #0
	ands r0, r1
	movs r5, #1
	orrs r0, r5
	strb r0, [r3]
	ldr r0, [r2]
	ldr r1, _08094F1C @ =0x00000143
	adds r3, r0, r1
	ldrb r1, [r3]
	movs r0, #0xf
	ands r0, r1
	strb r0, [r3]
	ldrb r0, [r4, #0x12]
	adds r0, #1
	strb r0, [r4, #0x12]
	movs r1, #1
	ands r0, r1
	cmp r0, #0
	beq _08094F20
	ldrb r0, [r4, #0xa]
	orrs r0, r5
	b _08094F26
	.align 2, 0
_08094F14: .4byte 0x08369F2C
_08094F18: .4byte pZero2
_08094F1C: .4byte 0x00000143
_08094F20:
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
_08094F26:
	strb r0, [r4, #0xa]
	ldr r0, [r2]
	ldr r1, [r0, #0x54]
	str r1, [r4, #0x54]
	ldr r0, [r0, #0x58]
	str r0, [r4, #0x58]
	adds r0, r4, #0
	bl UpdateMotionGraphic
_08094F38:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
