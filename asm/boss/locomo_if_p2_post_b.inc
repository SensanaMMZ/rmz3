	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start locomoIF_08054f18
locomoIF_08054f18: @ 0x08054F18
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #1
	beq _08054F44
	cmp r0, #1
	bgt _08054F2C
	cmp r0, #0
	beq _08054F36
	b _08054FC0
_08054F2C:
	cmp r0, #2
	beq _08054F7C
	cmp r0, #3
	beq _08054FA6
	b _08054FC0
_08054F36:
	ldr r1, _08054F74 @ =0x00005403
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08054F44:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _08054F5A
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08054F5A:
	adds r0, r4, #0
	adds r0, #0x71
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	cmp r0, #2
	bne _08054FC0
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _08054F78 @ =0x08363B28
	bl SetDDP
	b _08054FC0
	.align 2, 0
_08054F74: .4byte 0x00005403
_08054F78: .4byte 0x08363B28
_08054F7C:
	movs r0, #0x1e
	strb r0, [r4, #0x12]
	adds r0, r4, #0
	adds r0, #0xbc
	ldrb r0, [r0]
	cmp r0, #0
	beq _08054F98
	ldr r1, _08054F94 @ =0x00005406
	adds r0, r4, #0
	bl SetMotion
	b _08054FA0
	.align 2, 0
_08054F94: .4byte 0x00005406
_08054F98:
	ldr r1, _08054FC8 @ =0x00005407
	adds r0, r4, #0
	bl SetMotion
_08054FA0:
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08054FA6:
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	lsrs r1, r0, #0x18
	cmp r1, #0
	bne _08054FBA
	movs r0, #6
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_08054FBA:
	adds r0, r4, #0
	bl UpdateMotionGraphic
_08054FC0:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_08054FC8: .4byte 0x00005407
