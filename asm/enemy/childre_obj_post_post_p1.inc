	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_08073a74
FUN_08073a74: @ 0x08073A74
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _08073A84
	cmp r0, #1
	beq _08073AE0
	b _08073B16
_08073A84:
	adds r0, r4, #0
	bl InitRotatableMotion
	ldrb r1, [r4, #0x12]
	movs r0, #0x80
	subs r0, r0, r1
	adds r1, r4, #0
	adds r1, #0x24
	strb r0, [r1]
	ldr r1, _08073B1C @ =0x00002502
	adds r0, r4, #0
	bl SetMotion
	ldr r2, _08073B20 @ =gSineTable
	ldrb r0, [r4, #0x12]
	adds r0, #0x40
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x17
	adds r0, r0, r2
	movs r3, #0
	ldrsh r1, [r0, r3]
	lsls r0, r1, #2
	adds r0, r0, r1
	lsls r0, r0, #7
	cmp r0, #0
	bge _08073ABA
	adds r0, #0xff
_08073ABA:
	asrs r0, r0, #8
	str r0, [r4, #0x5c]
	ldrb r0, [r4, #0x12]
	lsls r0, r0, #1
	adds r0, r0, r2
	movs r2, #0
	ldrsh r1, [r0, r2]
	lsls r0, r1, #2
	adds r0, r0, r1
	lsls r0, r0, #7
	cmp r0, #0
	bge _08073AD4
	adds r0, #0xff
_08073AD4:
	asrs r0, r0, #8
	rsbs r0, r0, #0
	str r0, [r4, #0x60]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08073AE0:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	ldr r2, [r4, #0x60]
	adds r1, r1, r2
	str r1, [r4, #0x58]
	bl FUN_080098a4
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _08073B10
	ldr r1, _08073B24 @ =gEnemyFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r4, #0x14]
	ldrb r0, [r4, #0x10]
	strb r0, [r4, #0xd]
_08073B10:
	adds r0, r4, #0
	bl UpdateMotionGraphic
_08073B16:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_08073B1C: .4byte 0x00002502
_08073B20: .4byte gSineTable
_08073B24: .4byte gEnemyFnTable
