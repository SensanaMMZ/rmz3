	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_08096b84
FUN_08096b84: @ 0x08096B84
	push {r4, r5, lr}
	sub sp, #8
	adds r4, r0, #0
	ldrb r2, [r4, #0xe]
	cmp r2, #0
	beq _08096B96
	cmp r2, #1
	beq _08096BBA
	b _08096C10
_08096B96:
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
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
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08096BBA:
	ldr r0, [r4, #0x54]
	str r0, [sp]
	ldr r0, [r4, #0x58]
	ldr r1, _08096C18 @ =0xFFFFF800
	adds r0, r0, r1
	str r0, [sp, #4]
	movs r0, #1
	mov r1, sp
	bl CreateSmoke
	adds r0, r4, #0
	mov r1, sp
	bl FUN_080c68cc
	movs r0, #0x2a
	bl PlaySound
	adds r5, r4, #0
	adds r5, #0x54
	movs r0, #2
	adds r1, r5, #0
	bl TryDropItem
	ldr r2, _08096C1C @ =gMission
	ldrh r1, [r2, #0xc]
	ldr r0, _08096C20 @ =0x0000270E
	cmp r1, r0
	bhi _08096BF6
	adds r0, r1, #1
	strh r0, [r2, #0xc]
_08096BF6:
	adds r0, r4, #0
	adds r1, r5, #0
	bl TryDropZakoDisk
	ldr r1, _08096C24 @ =gEnemyFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #4
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0x10]
	str r0, [r4, #0x14]
_08096C10:
	add sp, #8
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_08096C18: .4byte 0xFFFFF800
_08096C1C: .4byte gMission
_08096C20: .4byte 0x0000270E
_08096C24: .4byte gEnemyFnTable

	thumb_func_start FUN_08096c28
FUN_08096c28: @ 0x08096C28
	push {r4, r5, r6, lr}
	sub sp, #8
	adds r5, r0, #0
	ldrb r0, [r5, #0xe]
	cmp r0, #1
	beq _08096CC4
	cmp r0, #1
	bgt _08096C3E
	cmp r0, #0
	beq _08096C46
	b _08096D76
_08096C3E:
	cmp r0, #2
	bne _08096C44
	b _08096D50
_08096C44:
	b _08096D76
_08096C46:
	adds r1, r5, #0
	adds r1, #0xbc
	ldrb r0, [r1]
	adds r4, r5, #0
	adds r4, #0xb4
	cmp r0, #0
	bne _08096C68
	movs r0, #1
	strb r0, [r1]
	movs r1, #0
	ldr r0, [r4]
	cmp r0, #0
	ble _08096C62
	movs r1, #1
_08096C62:
	adds r0, r5, #0
	bl FUN_080c6934
_08096C68:
	ldr r0, [r5, #0x54]
	str r0, [sp]
	ldr r0, [r5, #0x58]
	ldr r1, _08096D40 @ =0xFFFFF800
	adds r0, r0, r1
	str r0, [sp, #4]
	movs r6, #0
	ldr r0, [r4]
	cmp r0, #0
	ble _08096C7E
	movs r6, #1
_08096C7E:
	movs r4, #0x80
	lsls r4, r4, #2
	movs r0, #0
	mov r1, sp
	adds r2, r4, #0
	adds r3, r6, #0
	bl FUN_080b2b40
	ldr r1, _08096D44 @ =0x0000DB09
	adds r0, r5, #0
	bl SetMotion
	lsls r0, r6, #0xa
	subs r4, r4, r0
	str r4, [r5, #0x5c]
	movs r1, #0
	movs r0, #0x14
	strb r0, [r5, #0x12]
	adds r0, r5, #0
	adds r0, #0x8c
	str r1, [r0]
	adds r0, #4
	str r1, [r0]
	adds r0, #4
	strb r1, [r0]
	ldrb r1, [r5, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r5, #0xa]
	adds r0, r5, #0
	bl FUN_080c6880
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_08096CC4:
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x5c]
	adds r0, r0, r1
	str r0, [r5, #0x54]
	lsls r0, r1, #4
	subs r0, r0, r1
	lsls r0, r0, #4
	cmp r0, #0
	bge _08096CD8
	adds r0, #0xff
_08096CD8:
	asrs r0, r0, #8
	str r0, [r5, #0x5c]
	adds r0, r5, #0
	bl FUN_08095e28
	ldrb r0, [r5, #0x12]
	subs r0, #1
	strb r0, [r5, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _08096D38
	ldrb r1, [r5, #0xa]
	movs r0, #0xfe
	ands r0, r1
	strb r0, [r5, #0xa]
	ldr r0, [r5, #0x54]
	str r0, [sp]
	ldr r0, [r5, #0x58]
	ldr r1, _08096D40 @ =0xFFFFF800
	adds r0, r0, r1
	str r0, [sp, #4]
	movs r0, #1
	mov r1, sp
	bl CreateSmoke
	movs r0, #0x2a
	bl PlaySound
	adds r4, r5, #0
	adds r4, #0x54
	movs r0, #2
	adds r1, r4, #0
	bl TryDropItem
	ldr r2, _08096D48 @ =gMission
	ldrh r1, [r2, #0xc]
	ldr r0, _08096D4C @ =0x0000270E
	cmp r1, r0
	bhi _08096D2A
	adds r0, r1, #1
	strh r0, [r2, #0xc]
_08096D2A:
	adds r0, r5, #0
	adds r1, r4, #0
	bl TryDropZakoDisk
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_08096D38:
	adds r0, r5, #0
	bl UpdateMotionGraphic
	b _08096D76
	.align 2, 0
_08096D40: .4byte 0xFFFFF800
_08096D44: .4byte 0x0000DB09
_08096D48: .4byte gMission
_08096D4C: .4byte 0x0000270E
_08096D50:
	ldrb r1, [r5, #0xa]
	movs r0, #0xfe
	ands r0, r1
	strb r0, [r5, #0xa]
	ldrb r0, [r5, #0x12]
	cmp r0, #0
	beq _08096D64
	subs r0, #1
	strb r0, [r5, #0x12]
	b _08096D76
_08096D64:
	ldr r1, _08096D80 @ =gEnemyFnTable
	ldrb r0, [r5, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #4
	str r1, [r5, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0x10]
	str r0, [r5, #0x14]
_08096D76:
	add sp, #8
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_08096D80: .4byte gEnemyFnTable

	thumb_func_start FUN_08096d84
FUN_08096d84: @ 0x08096D84
	push {r4, r5, lr}
	sub sp, #8
	adds r4, r0, #0
	ldrb r1, [r4, #0xe]
	cmp r1, #1
	beq _08096DE0
	cmp r1, #1
	bgt _08096D9A
	cmp r1, #0
	beq _08096DA0
	b _08096E9E
_08096D9A:
	cmp r1, #2
	beq _08096E78
	b _08096E9E
_08096DA0:
	adds r0, r4, #0
	adds r0, #0x8c
	str r1, [r0]
	adds r0, #4
	str r1, [r0]
	adds r0, #4
	strb r1, [r0]
	ldrb r1, [r4, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r4, #0xa]
	movs r2, #0
	adds r0, r4, #0
	adds r0, #0xb4
	ldr r0, [r0]
	cmp r0, #0
	ble _08096DC4
	movs r2, #1
_08096DC4:
	lsls r1, r2, #2
	adds r1, r1, r2
	lsls r1, r1, #8
	movs r0, #0xa0
	lsls r0, r0, #2
	subs r0, r0, r1
	str r0, [r4, #0x5c]
	ldr r0, _08096E6C @ =0xFFFFFB80
	str r0, [r4, #0x60]
	movs r0, #0x14
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08096DE0:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	ldr r0, [r4, #0x58]
	ldr r1, [r4, #0x60]
	adds r0, r0, r1
	str r0, [r4, #0x58]
	adds r1, #0x40
	str r1, [r4, #0x60]
	movs r0, #0xe0
	lsls r0, r0, #3
	cmp r1, r0
	ble _08096DFE
	str r0, [r4, #0x60]
_08096DFE:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _08096E1E
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	bl FUN_080098a4
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _08096E9E
_08096E1E:
	ldr r0, [r4, #0x54]
	str r0, [sp]
	ldr r0, [r4, #0x58]
	movs r1, #0x80
	lsls r1, r1, #1
	adds r0, r0, r1
	str r0, [sp, #4]
	movs r0, #1
	mov r1, sp
	bl CreateSmoke
	adds r0, r4, #0
	mov r1, sp
	bl FUN_080c68cc
	movs r0, #0x2a
	bl PlaySound
	adds r5, r4, #0
	adds r5, #0x54
	movs r0, #2
	adds r1, r5, #0
	bl TryDropItem
	ldr r2, _08096E70 @ =gMission
	ldrh r1, [r2, #0xc]
	ldr r0, _08096E74 @ =0x0000270E
	cmp r1, r0
	bhi _08096E5C
	adds r0, r1, #1
	strh r0, [r2, #0xc]
_08096E5C:
	adds r0, r4, #0
	adds r1, r5, #0
	bl TryDropZakoDisk
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
	b _08096E9E
	.align 2, 0
_08096E6C: .4byte 0xFFFFFB80
_08096E70: .4byte gMission
_08096E74: .4byte 0x0000270E
_08096E78:
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
	strb r0, [r4, #0xa]
	ldrb r0, [r4, #0x12]
	cmp r0, #0
	beq _08096E8C
	subs r0, #1
	strb r0, [r4, #0x12]
	b _08096E9E
_08096E8C:
	ldr r1, _08096EA8 @ =gEnemyFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #4
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0x10]
	str r0, [r4, #0x14]
_08096E9E:
	add sp, #8
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_08096EA8: .4byte gEnemyFnTable

	thumb_func_start FUN_08096eac
FUN_08096eac: @ 0x08096EAC
	push {r4, r5, r6, lr}
	adds r5, r0, #0
	ldrb r0, [r5, #0xe]
	cmp r0, #0
	beq _08096EBC
	cmp r0, #1
	beq _08096F6A
	b _08096FAA
_08096EBC:
	adds r0, r5, #0
	adds r0, #0x74
	ldr r1, _08096ED8 @ =0x0836A17C
	bl SetDDP
	ldrb r0, [r5, #0x10]
	cmp r0, #0
	bne _08096EE0
	ldr r1, _08096EDC @ =0x0000DB04
	adds r0, r5, #0
	bl SetMotion
	b _08096EE8
	.align 2, 0
_08096ED8: .4byte 0x0836A17C
_08096EDC: .4byte 0x0000DB04
_08096EE0:
	ldr r1, _08096F50 @ =0x0000DB0F
	adds r0, r5, #0
	bl SetMotion
_08096EE8:
	adds r0, r5, #0
	bl UpdateMotionGraphic
	ldr r0, _08096F54 @ =pZero2
	ldr r2, [r0]
	ldr r1, [r5, #0x54]
	ldr r0, [r2, #0x54]
	subs r1, r1, r0
	str r1, [r5, #0x5c]
	ldr r0, [r5, #0x58]
	ldr r3, _08096F58 @ =0xFFFFE800
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
	beq _08096F5C
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
	b _08096F64
	.align 2, 0
_08096F50: .4byte 0x0000DB0F
_08096F54: .4byte pZero2
_08096F58: .4byte 0xFFFFE800
_08096F5C:
	movs r0, #0xc0
	lsls r0, r0, #3
	str r0, [r5, #0x5c]
	str r6, [r5, #0x60]
_08096F64:
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_08096F6A:
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x5c]
	adds r0, r0, r1
	str r0, [r5, #0x54]
	ldr r0, [r5, #0x60]
	adds r0, #0x40
	str r0, [r5, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _08096F82
	str r1, [r5, #0x60]
_08096F82:
	ldr r1, [r5, #0x58]
	ldr r0, [r5, #0x60]
	adds r1, r1, r0
	str r1, [r5, #0x58]
	ldr r0, [r5, #0x54]
	bl FUN_080098a4
	lsls r0, r0, #0x10
	cmp r0, #0
	bne _08096FA4
	adds r0, r5, #0
	adds r0, #0x8c
	ldr r0, [r0]
	movs r1, #4
	ands r0, r1
	cmp r0, #0
	beq _08096FAA
_08096FA4:
	adds r0, r5, #0
	bl FUN_08096b84
_08096FAA:
	pop {r4, r5, r6}
	pop {r0}
	bx r0


