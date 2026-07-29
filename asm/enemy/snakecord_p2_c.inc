	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_08074fcc
FUN_08074fcc: @ 0x08074FCC
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _08074FDC
	cmp r0, #1
	beq _08074FEC
	b _08075058
_08074FDC:
	strb r0, [r4, #0x12]
	ldr r1, _08075020 @ =0x0000280C
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08074FEC:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	bl PushoutToUp1
	adds r1, r0, #0
	cmp r1, #0
	bge _08075028
	ldr r2, _08075024 @ =0xFFFFFC00
	cmp r1, r2
	bge _0807500C
	ldrb r0, [r4, #0x12]
	muls r0, r2, r0
	cmp r0, #0
	bge _0807500A
	adds r0, #0xff
_0807500A:
	asrs r1, r0, #8
_0807500C:
	ldr r0, [r4, #0x58]
	adds r0, r0, r1
	str r0, [r4, #0x58]
	ldrb r0, [r4, #0x12]
	adds r0, #4
	movs r1, #0x3f
	ands r0, r1
	strb r0, [r4, #0x12]
	b _08075030
	.align 2, 0
_08075020: .4byte 0x0000280C
_08075024: .4byte 0xFFFFFC00
_08075028:
	movs r1, #0
	movs r0, #4
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_08075030:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x74
	ldr r2, _08075060 @ =0x08366FEC
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
	ldr r2, _08075064 @ =sCollisions
	adds r1, r1, r2
	bl SetDDP
_08075058:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_08075060: .4byte 0x08366FEC
_08075064: .4byte sCollisions
