	.include "asm/macros.inc"

	.syntax unified

	.text



	thumb_func_start hanu_0805c30c
hanu_0805c30c: @ 0x0805C30C
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	bne _0805C388
	ldr r1, _0805C364 @ =0x0000B50A
	adds r0, r4, #0
	bl SetMotion
	movs r3, #0
	ldr r0, _0805C368 @ =pZero2
	ldr r2, [r0]
	ldr r1, [r4, #0x54]
	ldr r0, [r2, #0x54]
	cmp r1, r0
	bge _0805C32E
	movs r3, #1
_0805C32E:
	adds r0, r4, #0
	adds r0, #0x4c
	strb r3, [r0]
	movs r3, #0
	ldr r1, [r4, #0x54]
	ldr r0, [r2, #0x54]
	cmp r1, r0
	bge _0805C340
	movs r3, #1
_0805C340:
	movs r0, #0x4a
	adds r0, r0, r4
	mov ip, r0
	lsls r2, r3, #4
	ldrb r1, [r0]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	orrs r0, r2
	mov r1, ip
	strb r0, [r1]
	cmp r3, #0
	beq _0805C36C
	ldrb r0, [r4, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _0805C372
	.align 2, 0
_0805C364: .4byte 0x0000B50A
_0805C368: .4byte pZero2
_0805C36C:
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
_0805C372:
	strb r0, [r4, #0xa]
	movs r0, #0x14
	strb r0, [r4, #0x12]
	movs r0, #3
	strb r0, [r4, #0x13]
	movs r0, #0x4f
	bl PlaySound
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0805C388:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldrb r0, [r4, #0x12]
	cmp r0, #0
	bne _0805C3B6
	ldrb r1, [r4, #0x13]
	subs r1, #1
	lsls r1, r1, #0x18
	lsrs r1, r1, #0x18
	ldrb r2, [r4, #0xa]
	lsrs r2, r2, #4
	movs r0, #1
	ands r2, r0
	adds r0, r4, #0
	bl FUN_080866a4
	movs r0, #8
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0x13]
	subs r0, #1
	strb r0, [r4, #0x13]
	b _0805C3BA
_0805C3B6:
	subs r0, #1
	strb r0, [r4, #0x12]
_0805C3BA:
	ldrb r1, [r4, #0x13]
	cmp r1, #0
	bne _0805C3C6
	movs r0, #9
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_0805C3C6:
	pop {r4}
	pop {r0}
	bx r0
