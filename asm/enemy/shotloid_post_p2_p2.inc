	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_08093ee4
FUN_08093ee4: @ 0x08093EE4
	push {r4, r5, r6, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _08093EF4
	cmp r0, #1
	beq _08093F14
	b _08093FDA
_08093EF4:
	adds r2, r4, #0
	adds r2, #0xb8
	ldr r0, [r2]
	movs r1, #1
	orrs r0, r1
	str r0, [r2]
	movs r0, #0x28
	strb r0, [r4, #0x12]
	movs r1, #0x8e
	lsls r1, r1, #8
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08093F14:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	movs r2, #0
	ldr r0, _08093F3C @ =pZero2
	ldr r0, [r0]
	ldr r1, [r4, #0x54]
	ldr r0, [r0, #0x54]
	cmp r1, r0
	bge _08093F2A
	movs r2, #1
_08093F2A:
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _08093F40
	cmp r2, #0
	beq _08093F44
	b _08093F4A
	.align 2, 0
_08093F3C: .4byte pZero2
_08093F40:
	cmp r2, #0
	beq _08093F4A
_08093F44:
	movs r1, #0
	movs r0, #4
	b _08093FD6
_08093F4A:
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	lsrs r5, r0, #0x18
	cmp r5, #0
	bne _08093FC4
	adds r0, r4, #0
	bl FUN_08093a20
	lsls r0, r0, #0x18
	lsrs r2, r0, #0x18
	cmp r2, #2
	bne _08093F6E
	movs r0, #3
	strb r0, [r4, #0xd]
	strb r5, [r4, #0xe]
	b _08093FC4
_08093F6E:
	ldr r0, _08093FB4 @ =pZero2
	ldr r0, [r0]
	ldr r1, [r0, #0x54]
	ldr r0, _08093FB8 @ =0xFFFFA000
	adds r1, r1, r0
	lsls r0, r2, #1
	adds r0, r0, r2
	lsls r0, r0, #0xe
	adds r1, r1, r0
	ldr r0, [r4, #0x54]
	movs r5, #1
	rsbs r5, r5, #0
	cmp r0, r1
	bge _08093F8C
	movs r5, #1
_08093F8C:
	adds r0, r4, #0
	adds r1, r5, #0
	bl FUN_08093a98
	lsls r0, r0, #0x18
	lsrs r6, r0, #0x18
	cmp r6, #0
	bne _08093FBC
	adds r0, r4, #0
	adds r1, r5, #0
	bl FUN_080939e8
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _08093FBC
	movs r0, #2
	strb r0, [r4, #0xd]
	strb r6, [r4, #0xe]
	b _08093FC4
	.align 2, 0
_08093FB4: .4byte pZero2
_08093FB8: .4byte 0xFFFFA000
_08093FBC:
	movs r1, #0
	movs r0, #3
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_08093FC4:
	adds r0, r4, #0
	movs r1, #1
	bl FUN_08093a64
	lsls r0, r0, #0x18
	lsrs r1, r0, #0x18
	cmp r1, #0
	bne _08093FDA
	movs r0, #5
_08093FD6:
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_08093FDA:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
