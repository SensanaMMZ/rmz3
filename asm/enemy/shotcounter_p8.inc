	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start shotcounter_08066be0
shotcounter_08066be0: @ 0x08066BE0
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _08066BF0
	cmp r0, #1
	beq _08066C12
	b _08066D9A
_08066BF0:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _08066D2C @ =0x08365E54
	bl SetDDP
	ldr r0, _08066D30 @ =pZero2
	ldr r0, [r0]
	ldrb r0, [r0, #0xa]
	lsrs r0, r0, #4
	movs r1, #1
	ands r0, r1
	strb r0, [r4, #0xf]
	movs r0, #0x1a
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08066C12:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	adds r0, r0, r1
	movs r3, #0x80
	lsls r3, r3, #5
	adds r0, r0, r3
	ldr r1, [r4, #0x58]
	ldr r2, [r4, #0x60]
	adds r1, r1, r2
	adds r1, r1, r3
	bl FUN_080098a4
	lsls r0, r0, #0x10
	lsrs r1, r0, #0x10
	cmp r1, #0
	beq _08066C3E
	movs r0, #0x80
	lsls r0, r0, #8
	ands r1, r0
	cmp r1, #0
	bne _08066C3E
	b _08066D7C
_08066C3E:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	subs r0, r0, r1
	ldr r1, _08066D34 @ =0xFFFFF000
	adds r0, r0, r1
	ldr r1, [r4, #0x58]
	ldr r2, [r4, #0x60]
	adds r1, r1, r2
	movs r2, #0x80
	lsls r2, r2, #5
	adds r1, r1, r2
	bl FUN_080098a4
	lsls r0, r0, #0x10
	lsrs r1, r0, #0x10
	cmp r1, #0
	beq _08066C6C
	movs r0, #0x80
	lsls r0, r0, #8
	ands r1, r0
	cmp r1, #0
	bne _08066C6C
	b _08066D7C
_08066C6C:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	adds r0, r0, r1
	movs r3, #0x80
	lsls r3, r3, #5
	adds r0, r0, r3
	ldr r1, [r4, #0x58]
	ldr r2, [r4, #0x60]
	adds r1, r1, r2
	ldr r2, _08066D34 @ =0xFFFFF000
	adds r1, r1, r2
	bl FUN_080098a4
	lsls r0, r0, #0x10
	lsrs r1, r0, #0x10
	cmp r1, #0
	beq _08066C98
	movs r0, #0x80
	lsls r0, r0, #8
	ands r1, r0
	cmp r1, #0
	beq _08066D7C
_08066C98:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	subs r0, r0, r1
	ldr r3, _08066D34 @ =0xFFFFF000
	adds r0, r0, r3
	ldr r1, [r4, #0x58]
	ldr r2, [r4, #0x60]
	adds r1, r1, r2
	adds r1, r1, r3
	bl FUN_080098a4
	lsls r0, r0, #0x10
	lsrs r1, r0, #0x10
	cmp r1, #0
	beq _08066CC0
	movs r0, #0x80
	lsls r0, r0, #8
	ands r1, r0
	cmp r1, #0
	beq _08066D7C
_08066CC0:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	ldr r0, [r4, #0x58]
	ldr r2, [r4, #0x60]
	adds r0, r0, r2
	str r0, [r4, #0x58]
	lsls r0, r1, #4
	subs r0, r1, r0
	asrs r0, r0, #8
	adds r1, r1, r0
	str r1, [r4, #0x5c]
	lsls r0, r2, #4
	subs r0, r2, r0
	asrs r0, r0, #8
	adds r2, r2, r0
	str r2, [r4, #0x60]
	adds r5, r4, #0
	adds r5, #0xc0
	ldr r0, [r5]
	bl isKilled
	cmp r0, #0
	beq _08066CFC
	adds r1, r4, #0
	adds r1, #0xbf
	movs r0, #0
	strb r0, [r1]
	str r0, [r5]
_08066CFC:
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	lsrs r1, r0, #0x18
	cmp r1, #0
	bne _08066D9A
	adds r0, r4, #0
	adds r0, #0xb8
	str r1, [r0]
	ldr r2, [r5]
	cmp r2, #0
	beq _08066D70
	adds r0, #7
	ldrb r2, [r0]
	cmp r2, #1
	bne _08066D38
	subs r0, #0x1b
	movs r3, #0
	ldrsh r0, [r0, r3]
	cmp r0, #1
	ble _08066D7C
	movs r0, #5
	b _08066D6A
	.align 2, 0
_08066D2C: .4byte sCollisions+(24*10)
_08066D30: .4byte pZero2
_08066D34: .4byte 0xFFFFF000
_08066D38:
	cmp r2, #2
	bne _08066D5C
	adds r0, r4, #0
	adds r0, #0xa4
	movs r3, #0
	ldrsh r0, [r0, r3]
	cmp r0, #1
	bgt _08066D58
	ldr r1, _08066D54 @ =gEnemyFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	str r2, [r4, #0xc]
	b _08066D88
	.align 2, 0
_08066D54: .4byte gEnemyFnTable
_08066D58:
	movs r0, #7
	b _08066D6A
_08066D5C:
	adds r0, r4, #0
	adds r0, #0xa4
	movs r2, #0
	ldrsh r0, [r0, r2]
	cmp r0, #1
	ble _08066D7C
	movs r0, #1
_08066D6A:
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
	b _08066D9A
_08066D70:
	adds r0, r4, #0
	adds r0, #0xa4
	movs r3, #0
	ldrsh r0, [r0, r3]
	cmp r0, #1
	bgt _08066D94
_08066D7C:
	ldr r1, _08066D90 @ =gEnemyFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r4, #0xc]
_08066D88:
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r4, #0x14]
	b _08066D9A
	.align 2, 0
_08066D90: .4byte gEnemyFnTable
_08066D94:
	movs r0, #1
	strb r0, [r4, #0xd]
	strb r2, [r4, #0xe]
_08066D9A:
	pop {r4, r5}
	pop {r0}
	bx r0
