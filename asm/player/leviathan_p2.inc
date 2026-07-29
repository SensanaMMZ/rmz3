	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start leviathanMode0
leviathanMode0: @ 0x08036048
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r5, [r4, #0xe]
	cmp r5, #0
	beq _08036058
	cmp r5, #1
	beq _08036076
	b _080360C2
_08036058:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _080360C8 @ =0x0835EC18
	bl SetDDP
	ldr r0, [r4, #0x58]
	str r0, [r4, #0x64]
	strb r5, [r4, #0x12]
	ldr r1, _080360CC @ =0x0000BD04
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08036076:
	adds r0, r4, #0
	bl FUN_08035e6c
	ldr r2, [r4, #0x64]
	str r2, [r4, #0x58]
	ldr r1, _080360D0 @ =gSineTable
	ldrb r0, [r4, #0x12]
	lsls r0, r0, #1
	adds r0, r0, r1
	movs r3, #0
	ldrsh r1, [r0, r3]
	lsls r0, r1, #2
	adds r0, r0, r1
	lsls r0, r0, #7
	cmp r0, #0
	bge _08036098
	adds r0, #0xff
_08036098:
	asrs r0, r0, #8
	adds r0, r2, r0
	str r0, [r4, #0x58]
	ldrb r0, [r4, #0x12]
	adds r0, #2
	strb r0, [r4, #0x12]
	adds r0, r4, #0
	bl FUN_08035e48
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _080360B4
	movs r0, #0
	str r0, [r4, #0x5c]
_080360B4:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	adds r0, r4, #0
	bl UpdateMotionGraphic
_080360C2:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080360C8: .4byte 0x0835EC18
_080360CC: .4byte 0x0000BD04
_080360D0: .4byte gSineTable
