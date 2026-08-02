	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start blizzackMode7
blizzackMode7: @ 0x0805A368
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _0805A3F2
	ldr r1, _0805A3D4 @ =0x0000B407
	adds r0, r4, #0
	bl SetMotion
	ldr r0, [r4, #0x2c]
	movs r5, #1
	strb r5, [r0, #0xe]
	ldr r0, [r4, #0x2c]
	adds r0, #0xbc
	movs r2, #0
	ldr r1, _0805A3D8 @ =0x00006407
	strh r1, [r0]
	strb r2, [r4, #0xe]
	movs r3, #0
	ldr r0, _0805A3DC @ =pZero2
	ldr r2, [r0]
	ldr r1, [r2, #0x54]
	ldr r0, [r4, #0x54]
	cmp r1, r0
	ble _0805A39C
	movs r3, #1
_0805A39C:
	adds r0, r4, #0
	adds r0, #0x4c
	strb r3, [r0]
	movs r3, #0
	ldr r1, [r2, #0x54]
	ldr r0, [r4, #0x54]
	cmp r1, r0
	ble _0805A3AE
	movs r3, #1
_0805A3AE:
	movs r0, #0x4a
	adds r0, r0, r4
	mov ip, r0
	adds r1, r5, #0
	ands r1, r3
	lsls r3, r1, #4
	ldrb r2, [r0]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r3
	mov r2, ip
	strb r0, [r2]
	cmp r1, #0
	beq _0805A3E0
	ldrb r0, [r4, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _0805A3E6
	.align 2, 0
_0805A3D4: .4byte 0x0000B407
_0805A3D8: .4byte 0x00006407
_0805A3DC: .4byte pZero2
_0805A3E0:
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
_0805A3E6:
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _0805A410 @ =0x08364BE0
	bl SetDDP
_0805A3F2:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _0805A40A
	movs r0, #8
	strb r0, [r4, #0xd]
	movs r0, #1
	strb r0, [r4, #0xe]
_0805A40A:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_0805A410: .4byte sCollisions+(24*2)
