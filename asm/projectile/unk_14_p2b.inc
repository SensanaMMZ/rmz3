	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_080a133c
FUN_080a133c: @ 0x080A133C
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _080A134C
	cmp r0, #1
	beq _080A139E
	b _080A1408
_080A134C:
	adds r1, r4, #0
	adds r1, #0x25
	movs r0, #0x18
	strb r0, [r1]
	ldr r0, _080A1370 @ =0x00003702
	adds r1, r0, #0
	ldrb r0, [r4, #0x12]
	adds r1, r1, r0
	adds r0, r4, #0
	bl SetMotion
	ldrb r2, [r4, #0x13]
	cmp r2, #0
	beq _080A1374
	ldrb r0, [r4, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _080A137A
	.align 2, 0
_080A1370: .4byte 0x00003702
_080A1374:
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
_080A137A:
	strb r0, [r4, #0xa]
	movs r1, #1
	ands r1, r2
	adds r0, r4, #0
	adds r0, #0x4c
	strb r1, [r0]
	adds r3, r4, #0
	adds r3, #0x4a
	lsls r1, r1, #4
	ldrb r2, [r3]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r1
	strb r0, [r3]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080A139E:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x74
	ldr r3, _080A1410 @ =0x0836B211
	adds r1, r4, #0
	adds r1, #0x71
	ldrb r1, [r1]
	lsls r1, r1, #0x18
	asrs r1, r1, #0x18
	ldrb r2, [r4, #0x12]
	eors r1, r2
	adds r1, r1, r3
	ldrb r2, [r1]
	lsls r1, r2, #1
	adds r1, r1, r2
	lsls r1, r1, #3
	ldr r2, _080A1414 @ =0x0836B11C
	adds r1, r1, r2
	bl SetDDP
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r3, [r0]
	cmp r3, #3
	bne _080A1408
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r2, #0
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	adds r0, #0x8c
	str r2, [r0]
	adds r0, #4
	str r2, [r0]
	adds r0, #4
	strb r2, [r0]
	ldrb r1, [r4, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r4, #0xa]
	ldr r1, _080A1418 @ =gProjectileFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	str r3, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r4, #0x14]
_080A1408:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080A1410: .4byte 0x0836B211
_080A1414: .4byte 0x0836B11C
_080A1418: .4byte gProjectileFnTable
