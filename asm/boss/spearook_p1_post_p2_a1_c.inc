	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_08062848
FUN_08062848: @ 0x08062848
	push {r4, r5, r6, lr}
	adds r6, r0, #0
	ldr r2, [r6, #0x2c]
	ldr r1, [r2, #0x54]
	str r1, [r6, #0x54]
	ldr r5, _08062898 @ =gSineTable
	adds r3, r2, #0
	adds r3, #0xb8
	ldrh r0, [r3]
	lsrs r0, r0, #8
	lsls r0, r0, #1
	adds r0, r0, r5
	movs r4, #0
	ldrsh r0, [r0, r4]
	movs r4, #0xb
	muls r0, r4, r0
	adds r1, r1, r0
	str r1, [r6, #0x54]
	ldr r1, [r2, #0x58]
	str r1, [r6, #0x58]
	ldrh r0, [r3]
	lsls r0, r0, #0x10
	asrs r0, r0, #0x18
	adds r0, #0x40
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x17
	adds r0, r0, r5
	movs r2, #0
	ldrsh r0, [r0, r2]
	muls r0, r4, r0
	subs r1, r1, r0
	str r1, [r6, #0x58]
	ldrb r0, [r6, #0xe]
	cmp r0, #1
	beq _080628B4
	cmp r0, #1
	bgt _0806289C
	cmp r0, #0
	beq _080628A6
	b _08062932
	.align 2, 0
_08062898: .4byte gSineTable
_0806289C:
	cmp r0, #2
	beq _080628D0
	cmp r0, #3
	beq _0806291C
	b _08062932
_080628A6:
	ldr r1, _080628CC @ =0x0000D60E
	adds r0, r6, #0
	bl SetMotion
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_080628B4:
	adds r0, r6, #0
	bl UpdateMotionGraphic
	adds r0, r6, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _08062932
	ldrb r0, [r6, #0xe]
	adds r0, #1
	b _08062930
	.align 2, 0
_080628CC: .4byte 0x0000D60E
_080628D0:
	ldrb r0, [r6, #0xa]
	lsrs r0, r0, #4
	movs r2, #1
	eors r0, r2
	ands r0, r2
	adds r1, r6, #0
	adds r1, #0x4c
	strb r0, [r1]
	ldrb r1, [r6, #0xa]
	lsrs r1, r1, #4
	eors r1, r2
	ands r1, r2
	adds r4, r6, #0
	adds r4, #0x4a
	lsls r3, r1, #4
	ldrb r2, [r4]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r3
	strb r0, [r4]
	cmp r1, #0
	beq _08062906
	ldrb r0, [r6, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _0806290C
_08062906:
	ldrb r1, [r6, #0xa]
	movs r0, #0xef
	ands r0, r1
_0806290C:
	strb r0, [r6, #0xa]
	ldr r1, _08062938 @ =0x0000D60F
	adds r0, r6, #0
	bl SetMotion
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_0806291C:
	adds r0, r6, #0
	bl UpdateMotionGraphic
	adds r0, r6, #0
	adds r0, #0x73
	ldrb r1, [r0]
	cmp r1, #3
	bne _08062932
	movs r0, #0
	strb r1, [r6, #0xd]
_08062930:
	strb r0, [r6, #0xe]
_08062932:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_08062938: .4byte 0x0000D60F

