	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_080b8d4c
FUN_080b8d4c: @ 0x080B8D4C
	push {r4, r5, r6, lr}
	adds r4, r0, #0
	ldr r0, [r4, #0x28]
	ldrb r0, [r0, #0xa]
	lsls r0, r0, #0x18
	lsrs r3, r0, #0x1c
	movs r1, #1
	ands r3, r1
	lsrs r5, r0, #0x1d
	ands r5, r1
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _080B8D6C
	cmp r0, #1
	beq _080B8DE0
	b _080B8E32
_080B8D6C:
	ldrb r1, [r4, #0xa]
	movs r0, #1
	movs r6, #0
	adds r2, r0, #0
	orrs r2, r1
	strb r2, [r4, #0xa]
	adds r1, r3, #0
	cmp r1, #0
	beq _080B8D84
	movs r0, #0x10
	orrs r2, r0
	b _080B8D88
_080B8D84:
	movs r0, #0xef
	ands r2, r0
_080B8D88:
	strb r2, [r4, #0xa]
	adds r0, r4, #0
	adds r0, #0x4c
	strb r1, [r0]
	adds r2, r4, #0
	adds r2, #0x4a
	lsls r1, r1, #4
	ldrb r3, [r2]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r3
	orrs r0, r1
	strb r0, [r2]
	adds r3, r5, #0
	adds r5, r2, #0
	cmp r3, #0
	beq _080B8DB2
	ldrb r0, [r4, #0xa]
	movs r1, #0x20
	orrs r0, r1
	b _080B8DB8
_080B8DB2:
	ldrb r1, [r4, #0xa]
	movs r0, #0xdf
	ands r0, r1
_080B8DB8:
	strb r0, [r4, #0xa]
	adds r1, r3, #0
	adds r2, r4, #0
	adds r2, #0x4d
	strb r1, [r2]
	lsls r1, r1, #5
	ldrb r2, [r5]
	movs r0, #0x21
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r1
	strb r0, [r5]
	ldr r0, [r4, #0x74]
	ldrh r1, [r0]
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080B8DE0:
	ldr r1, [r4, #0x54]
	ldr r0, [r4, #0x5c]
	adds r3, r1, r0
	str r3, [r4, #0x54]
	ldr r1, [r4, #0x58]
	ldr r0, [r4, #0x60]
	adds r2, r1, r0
	str r2, [r4, #0x58]
	ldr r1, [r4, #0x68]
	adds r0, r0, r1
	str r0, [r4, #0x60]
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _080B8E10
	adds r0, r3, #0
	adds r1, r2, #0
	bl FUN_080098a4
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _080B8E2C
_080B8E10:
	adds r1, r4, #0
	adds r1, #0x54
	movs r0, #1
	bl CreateSmoke
	ldr r1, _080B8E38 @ =gVFXFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r4, #0x14]
_080B8E2C:
	adds r0, r4, #0
	bl UpdateMotionGraphic
_080B8E32:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_080B8E38: .4byte gVFXFnTable
