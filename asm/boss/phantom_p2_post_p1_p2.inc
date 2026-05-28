	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080608e0
FUN_080608e0: @ 0x080608E0
	push {lr}
	adds r2, r0, #0
	adds r0, #0x71
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	cmp r0, #1
	bne _0806091E
	adds r0, r2, #0
	adds r0, #0x72
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	cmp r0, #1
	bgt _0806091E
	adds r1, r2, #0
	adds r1, #0x4c
	movs r0, #0
	strb r0, [r1]
	adds r3, r2, #0
	adds r3, #0x4a
	ldrb r1, [r3]
	subs r0, #0x11
	ands r0, r1
	strb r0, [r3]
	ldrb r1, [r2, #0xa]
	movs r0, #0xef
	ands r0, r1
	strb r0, [r2, #0xa]
	movs r0, #1
	b _08060920
_0806091E:
	movs r0, #0
_08060920:
	pop {r1}
	bx r1

	thumb_func_start FUN_08060924
FUN_08060924: @ 0x08060924
	push {r4, r5, lr}
	adds r4, r0, #0
	adds r0, #0x74
	ldr r1, _08060954 @ =0x083653E0
	bl SetDDP
	ldr r5, [r4, #0x60]
	adds r0, r4, #0
	adds r1, r5, #0
	bl FUN_0806089c
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _08060958
	adds r0, r4, #0
	movs r1, #4
	bl FUN_080607a0
	adds r0, r4, #0
	bl FUN_080607f0
	movs r0, #1
	b _0806096C
	.align 2, 0
_08060954: .4byte 0x083653E0
_08060958:
	ldrb r0, [r4, #0xe]
	cmp r0, #5
	bne _08060964
	adds r0, r5, #0
	adds r0, #0xa8
	b _08060968
_08060964:
	adds r0, r5, #0
	adds r0, #0x40
_08060968:
	str r0, [r4, #0x60]
	movs r0, #0
_0806096C:
	pop {r4, r5}
	pop {r1}
	bx r1
	.align 2, 0
