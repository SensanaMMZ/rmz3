	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start glacierle_08057f38
glacierle_08057f38: @ 0x08057F38
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #1
	beq _08057F60
	cmp r0, #1
	bgt _08057F4C
	cmp r0, #0
	beq _08057F52
	b _08058010
_08057F4C:
	cmp r0, #2
	beq _08057FA8
	b _08058010
_08057F52:
	ldr r1, _08057F9C @ =0x0000B201
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08057F60:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _08057F76
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08057F76:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r2, _08057FA0 @ =0x08364AAE
	adds r1, r4, #0
	adds r1, #0x71
	ldrb r1, [r1]
	lsls r1, r1, #0x18
	asrs r1, r1, #0x18
	adds r1, r1, r2
	ldrb r2, [r1]
	lsls r1, r2, #1
	adds r1, r1, r2
	lsls r1, r1, #3
	ldr r2, _08057FA4 @ =sCollisions
	adds r1, r1, r2
	bl SetDDP
	b _08058010
	.align 2, 0
_08057F9C: .4byte 0x0000B201
_08057FA0: .4byte 0x08364AAE
_08057FA4: .4byte sCollisions
_08057FA8:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _08057FEC @ =0x08363DE4
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
	beq _08057FF0
	ldrb r0, [r4, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _08057FF6
	.align 2, 0
_08057FEC: .4byte 0x08363DE4
_08057FF0:
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
_08057FF6:
	strb r0, [r4, #0xa]
	movs r1, #0xb2
	lsls r1, r1, #8
	adds r0, r4, #0
	bl SetMotion
	adds r0, r4, #0
	bl UpdateMotionGraphic
	movs r0, #0
	strb r0, [r4, #0xd]
	movs r0, #1
	strb r0, [r4, #0xe]
_08058010:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0

