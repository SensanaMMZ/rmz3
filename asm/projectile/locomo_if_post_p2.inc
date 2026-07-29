	.include "asm/macros.inc"

	.syntax unified

	.text


	thumb_func_start FUN_080a7e9c
FUN_080a7e9c: @ 0x080A7E9C
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _080A7EAC
	cmp r0, #1
	beq _080A7EDA
	b _080A7F62
_080A7EAC:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _080A7EF4 @ =0x0836BE64
	bl SetDDP
	ldrb r1, [r4, #0x12]
	lsls r0, r1, #2
	adds r0, r0, r1
	lsls r0, r0, #7
	ldr r1, _080A7EF8 @ =0xFFFFFEC0
	adds r0, r0, r1
	str r0, [r4, #0x5c]
	movs r0, #0x80
	rsbs r0, r0, #0
	str r0, [r4, #0x60]
	movs r1, #0xae
	lsls r1, r1, #7
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080A7EDA:
	ldr r0, _080A7EFC @ =pZero2
	ldr r0, [r0]
	adds r0, #0x94
	ldrb r0, [r0]
	cmp r0, #0
	beq _080A7F04
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _080A7F00 @ =0x0836BEAC
	bl SetDDP
	b _080A7F0E
	.align 2, 0
_080A7EF4: .4byte 0x0836BE64
_080A7EF8: .4byte 0xFFFFFEC0
_080A7EFC: .4byte pZero2
_080A7F00: .4byte 0x0836BEAC
_080A7F04:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _080A7F68 @ =0x0836BE64
	bl SetDDP
_080A7F0E:
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
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r3, [r0]
	cmp r3, #3
	bne _080A7F62
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
	ldr r1, _080A7F6C @ =gProjectileFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	str r3, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r4, #0x14]
_080A7F62:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080A7F68: .4byte 0x0836BE64
_080A7F6C: .4byte gProjectileFnTable
