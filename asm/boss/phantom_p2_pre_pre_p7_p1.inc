	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_08060114
FUN_08060114: @ 0x08060114
	push {r4, lr}
	adds r4, r0, #0
	ldr r0, _08060160 @ =pZero2
	ldr r0, [r0]
	ldr r0, [r0, #0x54]
	str r0, [r4, #0x54]
	ldr r0, _08060164 @ =gStageRun+232
	ldr r0, [r0, #0x3c]
	ldr r1, _08060168 @ =0xFFFFD000
	adds r0, r0, r1
	str r0, [r4, #0x58]
	adds r0, r4, #0
	movs r1, #0
	bl FUN_08060864
	movs r0, #0
	str r0, [r4, #0x60]
	adds r0, r4, #0
	movs r1, #0xc
	bl FUN_080607a0
	movs r0, #1
	strb r0, [r4, #0xf]
	movs r0, #0xfe
	bl PlaySound
	adds r0, r4, #0
	bl FUN_0805ecc8
	movs r0, #0xc
	strb r0, [r4, #0x12]
	adds r0, r4, #0
	bl FUN_0806016c
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_08060160: .4byte pZero2
_08060164: .4byte gStageRun+232
_08060168: .4byte 0xFFFFD000

	thumb_func_start FUN_0806016c
FUN_0806016c: @ 0x0806016C
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _08060192
	ldrb r0, [r4, #0xa]
	movs r1, #1
	orrs r0, r1
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _08060198 @ =sCollisions+(24*2)
	bl SetDDP
	movs r0, #2
	strb r0, [r4, #0xf]
_08060192:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_08060198: .4byte sCollisions+(24*2)

	thumb_func_start FUN_0806019c
FUN_0806019c: @ 0x0806019C
	push {r4, r5, lr}
	adds r4, r0, #0
	ldr r0, [r4, #0x60]
	adds r0, #0x40
	str r0, [r4, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _080601B0
	str r1, [r4, #0x60]
_080601B0:
	adds r0, r4, #0
	adds r0, #0x8c
	ldr r0, [r0]
	movs r5, #4
	ands r0, r5
	cmp r0, #0
	beq _080601CC
	ldr r0, _080601EC @ =0xFFFFFD00
	str r0, [r4, #0x60]
	adds r0, r4, #0
	movs r1, #0xd
	bl FUN_080607a0
	strb r5, [r4, #0xf]
_080601CC:
	ldr r1, [r4, #0x60]
	adds r0, r4, #0
	bl FUN_0806089c
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _080601E6
	adds r0, r4, #0
	movs r1, #4
	bl FUN_080607a0
	movs r0, #3
	strb r0, [r4, #0xf]
_080601E6:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080601EC: .4byte 0xFFFFFD00
