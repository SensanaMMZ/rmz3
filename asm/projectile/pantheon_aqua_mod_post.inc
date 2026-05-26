	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080a5cfc
FUN_080a5cfc: @ 0x080A5CFC
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _080A5D0C
	cmp r0, #1
	beq _080A5DC8
	b _080A5DFA
_080A5D0C:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _080A5D94 @ =0x0836BB18
	bl SetDDP
	ldr r1, _080A5D98 @ =0x0836BB4A
	ldrb r0, [r4, #0x12]
	lsls r0, r0, #1
	adds r0, r0, r1
	ldrh r1, [r0]
	adds r0, r4, #0
	bl SetMotion
	adds r0, r4, #0
	bl GetEntityPalID
	adds r1, r0, #0
	lsls r1, r1, #0x18
	lsrs r1, r1, #0x13
	movs r2, #0x80
	lsls r2, r2, #2
	adds r0, r2, #0
	orrs r1, r0
	movs r0, #0x57
	bl LoadBlink
	ldr r2, _080A5D9C @ =gSineTable
	ldrb r1, [r4, #0x12]
	lsls r1, r1, #5
	movs r3, #0x40
	rsbs r3, r3, #0
	adds r0, r3, #0
	subs r0, r0, r1
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x17
	adds r0, r0, r2
	movs r3, #0
	ldrsh r1, [r0, r3]
	lsls r0, r1, #1
	adds r0, r0, r1
	str r0, [r4, #0x5c]
	ldrb r1, [r4, #0x12]
	lsls r1, r1, #5
	movs r3, #0x80
	rsbs r3, r3, #0
	adds r0, r3, #0
	subs r0, r0, r1
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x17
	adds r0, r0, r2
	movs r2, #0
	ldrsh r1, [r0, r2]
	lsls r0, r1, #1
	adds r0, r0, r1
	str r0, [r4, #0x60]
	movs r1, #0
	ldrb r0, [r4, #0x12]
	cmp r0, #2
	bls _080A5D84
	movs r1, #1
_080A5D84:
	adds r2, r1, #0
	cmp r2, #0
	beq _080A5DA0
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	orrs r0, r1
	b _080A5DA6
	.align 2, 0
_080A5D94: .4byte 0x0836BB18
_080A5D98: .4byte 0x0836BB4A
_080A5D9C: .4byte gSineTable
_080A5DA0:
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
_080A5DA6:
	strb r0, [r4, #0xa]
	adds r1, r2, #0
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
_080A5DC8:
	movs r0, #0x57
	bl UpdateBlinkMotionState
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	ldr r0, [r4, #0x58]
	ldr r1, [r4, #0x60]
	adds r0, r0, r1
	str r0, [r4, #0x58]
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	bl FUN_080098a4
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _080A5DFA
	movs r1, #0
	movs r0, #1
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_080A5DFA:
	pop {r4}
	pop {r0}
	bx r0

	thumb_func_start FUN_080a5e00
FUN_080a5e00: @ 0x080A5E00
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _080A5E10
	cmp r0, #1
	beq _080A5E34
	b _080A5E54
_080A5E10:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _080A5E5C @ =0x0836BB30
	bl SetDDP
	ldr r1, _080A5E60 @ =0x0836BB54
	ldrb r0, [r4, #0x12]
	lsls r0, r0, #1
	adds r0, r0, r1
	ldrh r1, [r0]
	adds r0, r4, #0
	bl SetMotion
	movs r0, #0x30
	strb r0, [r4, #0x13]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080A5E34:
	movs r0, #0x57
	bl UpdateBlinkMotionState
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldrb r0, [r4, #0x13]
	subs r0, #1
	strb r0, [r4, #0x13]
	lsls r0, r0, #0x18
	lsrs r1, r0, #0x18
	cmp r1, #0
	bne _080A5E54
	movs r0, #2
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_080A5E54:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080A5E5C: .4byte 0x0836BB30
_080A5E60: .4byte 0x0836BB54

	thumb_func_start FUN_080a5e64
FUN_080a5e64: @ 0x080A5E64
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r1, [r4, #0xe]
	cmp r1, #0
	beq _080A5E74
	cmp r1, #1
	beq _080A5E94
	b _080A5EF6
_080A5E74:
	adds r0, r4, #0
	adds r0, #0x8c
	str r1, [r0]
	adds r0, #4
	str r1, [r0]
	adds r0, #4
	strb r1, [r0]
	ldrb r1, [r4, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r4, #0xa]
	movs r0, #0xa
	strb r0, [r4, #0x13]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080A5E94:
	ldrb r1, [r4, #0x13]
	movs r0, #1
	ands r0, r1
	adds r2, r1, #0
	cmp r0, #0
	beq _080A5EA8
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
	b _080A5EAE
_080A5EA8:
	ldrb r0, [r4, #0xa]
	movs r1, #1
	orrs r0, r1
_080A5EAE:
	strb r0, [r4, #0xa]
	subs r0, r2, #1
	strb r0, [r4, #0x13]
	lsls r0, r0, #0x18
	lsrs r5, r0, #0x18
	cmp r5, #0
	bne _080A5EF6
	movs r0, #0x57
	bl ClearBlink
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	adds r0, #0x8c
	str r5, [r0]
	adds r0, #4
	str r5, [r0]
	adds r0, #4
	strb r5, [r0]
	ldrb r1, [r4, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r4, #0xa]
	ldr r1, _080A5EFC @ =gProjectileFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r4, #0x14]
_080A5EF6:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080A5EFC: .4byte gProjectileFnTable

