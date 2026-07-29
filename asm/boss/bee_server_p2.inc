	.include "asm/macros.inc"

	.syntax unified

	.text


	thumb_func_start FUN_0804d0f8
FUN_0804d0f8: @ 0x0804D0F8
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _0804D108
	cmp r0, #1
	beq _0804D126
	b _0804D18E
_0804D108:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _0804D194 @ =0x08363270
	bl SetDDP
	movs r0, #0xff
	strb r0, [r4, #0x12]
	movs r1, #0x8c
	lsls r1, r1, #7
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0804D126:
	adds r2, r4, #0
	adds r2, #0xba
	movs r1, #0
	ldrsh r0, [r2, r1]
	cmp r0, #0
	bne _0804D174
	adds r0, r4, #0
	adds r0, #0x8c
	ldr r0, [r0]
	ldr r1, _0804D198 @ =0x00020008
	ands r0, r1
	cmp r0, r1
	bne _0804D174
	movs r0, #0x78
	strh r0, [r2]
	ldr r3, _0804D19C @ =RNG_0202f388
	ldr r1, [r3]
	ldr r0, _0804D1A0 @ =0x000343FD
	adds r2, r1, #0
	muls r2, r0, r2
	ldr r0, _0804D1A4 @ =0x00269EC3
	adds r2, r2, r0
	lsls r2, r2, #1
	lsrs r0, r2, #1
	str r0, [r3]
	lsrs r2, r2, #0x11
	movs r0, #3
	ands r2, r0
	ldr r0, [r4, #0x54]
	lsrs r3, r2, #1
	lsls r3, r3, #0xe
	ldr r1, _0804D1A8 @ =0xFFFFE000
	adds r3, r3, r1
	ldr r1, [r4, #0x58]
	adds r1, r1, r3
	movs r3, #1
	ands r2, r3
	bl FUN_0807d6c0
_0804D174:
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	lsrs r1, r0, #0x18
	cmp r1, #0
	bne _0804D188
	movs r0, #2
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_0804D188:
	adds r0, r4, #0
	bl UpdateMotionGraphic
_0804D18E:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_0804D194: .4byte 0x08363270
_0804D198: .4byte 0x00020008
_0804D19C: .4byte RNG_0202f388
_0804D1A0: .4byte 0x000343FD
_0804D1A4: .4byte 0x00269EC3
_0804D1A8: .4byte 0xFFFFE000
