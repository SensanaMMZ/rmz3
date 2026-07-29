	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_0806ea64
FUN_0806ea64: @ 0x0806EA64
	push {r4, r5, r6, r7, lr}
	adds r4, r0, #0
	ldr r6, [r4, #0x28]
	ldrb r0, [r4, #0xe]
	cmp r0, #1
	beq _0806EAC0
	cmp r0, #1
	bgt _0806EA7A
	cmp r0, #0
	beq _0806EA80
	b _0806EC44
_0806EA7A:
	cmp r0, #2
	beq _0806EB00
	b _0806EC44
_0806EA80:
	adds r1, r4, #0
	adds r1, #0xbd
	movs r0, #8
	strb r0, [r1]
	ldrb r2, [r4, #0x12]
	cmp r2, #0
	beq _0806EA96
	ldrb r0, [r4, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _0806EA9C
_0806EA96:
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
_0806EA9C:
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
_0806EAC0:
	adds r2, r4, #0
	adds r2, #0x74
	ldrb r0, [r4, #0x10]
	ldr r1, _0806EB40 @ =0x08366884
	cmp r0, #1
	bls _0806EACE
	adds r1, #0x30
_0806EACE:
	adds r0, r2, #0
	bl SetDDP
	ldr r0, _0806EB44 @ =0xFFFFFDC0
	str r0, [r4, #0x5c]
	adds r2, r0, #0
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _0806EAE8
	movs r2, #0x90
	lsls r2, r2, #2
_0806EAE8:
	str r2, [r4, #0x5c]
	ldr r1, _0806EB48 @ =0x08366920
	ldrb r0, [r4, #0x10]
	lsls r0, r0, #1
	adds r0, r0, r1
	ldrh r1, [r0]
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0806EB00:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	bl FUN_08009f6c
	adds r5, r0, #0
	movs r7, #0
	adds r0, r4, #0
	adds r0, #0xb8
	ldr r1, [r4, #0x54]
	ldr r0, [r0]
	subs r2, r1, r0
	movs r0, #0xf0
	lsls r0, r0, #8
	adds r1, r2, r0
	movs r0, #0xf0
	lsls r0, r0, #9
	cmp r1, r0
	bls _0806EB50
	movs r1, #0
	cmp r2, #0
	ble _0806EB32
	movs r1, #1
_0806EB32:
	ldr r0, [r4, #0x5c]
	cmp r0, #0
	bge _0806EB4C
	cmp r1, #0
	beq _0806EB7E
	b _0806EB50
	.align 2, 0
_0806EB40: .4byte 0x08366884
_0806EB44: .4byte 0xFFFFFDC0
_0806EB48: .4byte 0x08366920
_0806EB4C:
	cmp r1, #0
	bne _0806EB7E
_0806EB50:
	ldr r2, [r4, #0x54]
	ldr r1, _0806EB98 @ =0xFFFFF600
	adds r3, r2, r1
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _0806EB66
	movs r0, #0xa0
	lsls r0, r0, #4
	adds r3, r2, r0
_0806EB66:
	ldr r1, [r4, #0x58]
	ldr r2, _0806EB9C @ =0xFFFFF800
	adds r1, r1, r2
	adds r0, r3, #0
	bl FUN_080098a4
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _0806EB7A
	movs r7, #1
_0806EB7A:
	cmp r7, #0
	beq _0806EBBE
_0806EB7E:
	ldr r0, [r4, #0x5c]
	rsbs r0, r0, #0
	str r0, [r4, #0x5c]
	ldrb r2, [r4, #0xa]
	lsrs r0, r2, #4
	movs r1, #1
	bics r1, r0
	cmp r1, #0
	beq _0806EBA0
	movs r0, #0x10
	orrs r0, r2
	b _0806EBA4
	.align 2, 0
_0806EB98: .4byte 0xFFFFF600
_0806EB9C: .4byte 0xFFFFF800
_0806EBA0:
	movs r0, #0xef
	ands r0, r2
_0806EBA4:
	strb r0, [r4, #0xa]
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
_0806EBBE:
	ldr r0, _0806EBE8 @ =pZero2
	ldr r0, [r0]
	ldr r3, [r0, #0x54]
	ldr r2, [r4, #0x54]
	subs r0, r3, r2
	movs r1, #0xc0
	lsls r1, r1, #6
	adds r0, r0, r1
	ldr r1, _0806EBEC @ =0x00005FFF
	cmp r0, r1
	bhi _0806EC0A
	movs r1, #0
	cmp r2, r3
	bge _0806EBDC
	movs r1, #1
_0806EBDC:
	ldr r0, [r4, #0x5c]
	cmp r0, #0
	bge _0806EBF0
	cmp r1, #0
	beq _0806EBF4
	b _0806EC0A
	.align 2, 0
_0806EBE8: .4byte pZero2
_0806EBEC: .4byte 0x00005FFF
_0806EBF0:
	cmp r1, #0
	beq _0806EC0A
_0806EBF4:
	adds r2, r4, #0
	adds r2, #0xbc
	ldrb r0, [r2]
	cmp r0, #0
	beq _0806EC12
	movs r1, #0
	strb r1, [r2]
	movs r0, #3
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
	b _0806EC12
_0806EC0A:
	adds r1, r4, #0
	adds r1, #0xbc
	movs r0, #1
	strb r0, [r1]
_0806EC12:
	ldr r0, [r4, #0x58]
	subs r0, r5, r0
	ldr r1, _0806EC28 @ =0x000009FF
	cmp r0, r1
	ble _0806EC2C
	movs r1, #0
	movs r0, #2
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
	b _0806EC3E
	.align 2, 0
_0806EC28: .4byte 0x000009FF
_0806EC2C:
	adds r1, r4, #0
	adds r1, #0xbd
	ldrb r0, [r1]
	cmp r0, #0
	bne _0806EC3A
	str r5, [r4, #0x58]
	b _0806EC3E
_0806EC3A:
	subs r0, #1
	strb r0, [r1]
_0806EC3E:
	adds r0, r4, #0
	bl UpdateMotionGraphic
_0806EC44:
	cmp r6, #0
	beq _0806ECF6
	ldr r1, [r6, #0x54]
	ldr r0, [r4, #0x54]
	subs r5, r1, r0
	movs r2, #0
	cmp r5, #0
	ble _0806EC56
	movs r2, #1
_0806EC56:
	ldrb r1, [r6, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _0806EC66
	cmp r2, #0
	beq _0806EC6A
	b _0806ECF6
_0806EC66:
	cmp r2, #0
	beq _0806ECF6
_0806EC6A:
	movs r2, #0
	ldr r0, [r4, #0x5c]
	cmp r0, #0
	ble _0806EC74
	movs r2, #1
_0806EC74:
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _0806EC82
	cmp r2, #0
	beq _0806EC86
	b _0806ECF6
_0806EC82:
	cmp r2, #0
	beq _0806ECF6
_0806EC86:
	ldr r1, [r4, #0x58]
	ldr r0, [r6, #0x58]
	cmp r1, r0
	bgt _0806ECF6
	ldr r2, _0806ECFC @ =0xFFFFE800
	adds r0, r0, r2
	cmp r1, r0
	ble _0806ECF6
	movs r0, #0xb0
	lsls r0, r0, #2
	adds r1, r5, r0
	ldr r0, _0806ED00 @ =0x0000057F
	cmp r1, r0
	bhi _0806ECF6
	adds r3, r6, #0
	adds r3, #0xb4
	ldrb r1, [r4, #0x11]
	adds r1, #4
	movs r2, #1
	adds r0, r2, #0
	lsls r0, r1
	ldr r1, [r3]
	orrs r1, r0
	str r1, [r3]
	ldrb r0, [r4, #0x11]
	adds r0, #8
	lsls r2, r0
	orrs r1, r2
	str r1, [r3]
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
	ldr r1, _0806ED04 @ =gEnemyFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r4, #0x14]
_0806ECF6:
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_0806ECFC: .4byte 0xFFFFE800
_0806ED00: .4byte 0x0000057F
_0806ED04: .4byte gEnemyFnTable

