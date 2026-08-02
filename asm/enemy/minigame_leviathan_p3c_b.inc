	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_0809ad8c
FUN_0809ad8c: @ 0x0809AD8C
	push {r4, r5, r6, lr}
	adds r4, r0, #0
	ldr r6, [r4, #0x28]
	ldrb r5, [r4, #0xe]
	cmp r5, #0
	beq _0809AD9E
	cmp r5, #1
	beq _0809ADF0
	b _0809AE5C
_0809AD9E:
	adds r0, r6, #0
	adds r0, #0x34
	ldrb r0, [r0]
	cmp r0, #0
	bne _0809ADCC
	adds r0, r6, #0
	adds r0, #0x35
	strb r5, [r0]
	str r5, [r6, #0x1c]
	subs r0, #3
	strb r5, [r0]
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	movs r2, #1
	rsbs r2, r2, #0
	movs r3, #5
	rsbs r3, r3, #0
	bl FUN_08099f54
	ldr r0, [r6, #0x20]
	ldr r1, _0809AE04 @ =0xFFFFFED4
	adds r0, r0, r1
	str r0, [r6, #0x20]
_0809ADCC:
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
	str r5, [r4, #0x60]
	movs r0, #0x18
	strb r0, [r4, #0x12]
	strb r5, [r4, #0x13]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0809ADF0:
	ldrb r0, [r4, #0x13]
	adds r0, #1
	strb r0, [r4, #0x13]
	movs r1, #1
	ands r0, r1
	cmp r0, #0
	beq _0809AE08
	ldrb r0, [r4, #0xa]
	orrs r0, r1
	b _0809AE0E
	.align 2, 0
_0809AE04: .4byte 0xFFFFFED4
_0809AE08:
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
_0809AE0E:
	strb r0, [r4, #0xa]
	adds r0, r6, #0
	adds r0, #0x31
	ldrb r0, [r0]
	cmp r0, #0
	bne _0809AE5C
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _0809AE38
	ldr r1, _0809AE64 @ =gEnemyFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #4
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0x10]
	str r0, [r4, #0x14]
_0809AE38:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	lsls r0, r1, #5
	subs r0, r0, r1
	lsls r0, r0, #3
	cmp r0, #0
	bge _0809AE4C
	adds r0, #0xff
_0809AE4C:
	asrs r0, r0, #8
	str r0, [r4, #0x5c]
	ldr r0, [r4, #0x58]
	ldr r1, [r4, #0x60]
	adds r0, r0, r1
	str r0, [r4, #0x58]
	adds r1, #0x10
	str r1, [r4, #0x60]
_0809AE5C:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_0809AE64: .4byte gEnemyFnTable

	thumb_func_start FUN_0809ae68
FUN_0809ae68: @ 0x0809AE68
	push {r4, r5, r6, lr}
	adds r4, r0, #0
	ldr r6, [r4, #0x28]
	ldrb r5, [r4, #0xe]
	cmp r5, #0
	beq _0809AE7A
	cmp r5, #1
	beq _0809AECA
	b _0809AF14
_0809AE7A:
	adds r0, r6, #0
	adds r0, #0x34
	ldrb r0, [r0]
	cmp r0, #0
	bne _0809AEA8
	adds r0, r6, #0
	adds r0, #0x35
	strb r5, [r0]
	str r5, [r6, #0x1c]
	subs r0, #3
	strb r5, [r0]
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	movs r2, #1
	rsbs r2, r2, #0
	movs r3, #5
	rsbs r3, r3, #0
	bl FUN_08099f54
	ldr r0, [r6, #0x20]
	ldr r1, _0809AEE0 @ =0xFFFFFED4
	adds r0, r0, r1
	str r0, [r6, #0x20]
_0809AEA8:
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
	movs r0, #0x18
	strb r0, [r4, #0x12]
	strb r5, [r4, #0x13]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0809AECA:
	ldrb r0, [r4, #0x13]
	adds r0, #1
	strb r0, [r4, #0x13]
	movs r1, #1
	ands r0, r1
	cmp r0, #0
	beq _0809AEE4
	ldrb r0, [r4, #0xa]
	orrs r0, r1
	b _0809AEEA
	.align 2, 0
_0809AEE0: .4byte 0xFFFFFED4
_0809AEE4:
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
_0809AEEA:
	strb r0, [r4, #0xa]
	adds r0, r6, #0
	adds r0, #0x31
	ldrb r0, [r0]
	cmp r0, #0
	bne _0809AF14
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _0809AF14
	ldr r1, _0809AF1C @ =gEnemyFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #4
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0x10]
	str r0, [r4, #0x14]
_0809AF14:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_0809AF1C: .4byte gEnemyFnTable
