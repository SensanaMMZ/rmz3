	.include "asm/macros.inc"

	.syntax unified

	.text


	thumb_func_start hanu_0805c198
hanu_0805c198: @ 0x0805C198
	push {r4, lr}
	adds r4, r0, #0
	ldrb r1, [r4, #0xe]
	cmp r1, #0
	bne _0805C24E
	adds r0, #0x24
	strb r1, [r0]
	adds r0, r4, #0
	bl InitNonAffineMotion
	adds r0, r4, #0
	bl ResetDynamicMotion
	ldr r1, _0805C200 @ =0x0000B506
	adds r0, r4, #0
	bl SetMotion
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _0805C204 @ =0x08364EC8
	bl SetDDP
	ldrb r0, [r4, #0xa]
	lsrs r0, r0, #4
	movs r2, #1
	eors r0, r2
	ands r0, r2
	adds r1, r4, #0
	adds r1, #0x4c
	strb r0, [r1]
	ldrb r1, [r4, #0xa]
	lsrs r1, r1, #4
	eors r1, r2
	ands r1, r2
	movs r0, #0x4a
	adds r0, r0, r4
	mov ip, r0
	lsls r3, r1, #4
	ldrb r2, [r0]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r3
	mov r2, ip
	strb r0, [r2]
	cmp r1, #0
	beq _0805C208
	ldrb r0, [r4, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _0805C20E
	.align 2, 0
_0805C200: .4byte 0x0000B506
_0805C204: .4byte 0x08364EC8
_0805C208:
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
_0805C20E:
	strb r0, [r4, #0xa]
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _0805C22C
	ldr r0, [r4, #0x54]
	movs r1, #0xa0
	lsls r1, r1, #4
	adds r0, r0, r1
	str r0, [r4, #0x54]
	str r1, [r4, #0x64]
	movs r0, #0x80
	lsls r0, r0, #2
	b _0805C238
_0805C22C:
	ldr r0, [r4, #0x54]
	ldr r1, _0805C298 @ =0xFFFFF600
	adds r0, r0, r1
	str r0, [r4, #0x54]
	str r1, [r4, #0x64]
	ldr r0, _0805C29C @ =0xFFFFFE00
_0805C238:
	str r0, [r4, #0x5c]
	ldr r0, _0805C2A0 @ =0xFFFFFD00
	str r0, [r4, #0x60]
	ldr r0, [r4, #0x58]
	movs r1, #0xb0
	lsls r1, r1, #5
	adds r0, r0, r1
	str r0, [r4, #0x58]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0805C24E:
	adds r0, r4, #0
	bl UpdateMotionGraphic
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
	ble _0805C272
	str r0, [r4, #0x60]
_0805C272:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	bl FUN_080098a4
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _0805C292
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	bl FUN_08009f6c
	str r0, [r4, #0x58]
	movs r1, #0
	movs r0, #7
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_0805C292:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_0805C298: .4byte 0xFFFFF600
_0805C29C: .4byte 0xFFFFFE00
_0805C2A0: .4byte 0xFFFFFD00
