	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_0806ce60
FUN_0806ce60: @ 0x0806CE60
	push {r4, lr}
	adds r3, r0, #0
	adds r4, r1, #0
	ldr r0, [r3, #0xc]
	ldr r0, [r0, #4]
	ldrb r0, [r0, #4]
	cmp r0, #3
	beq _0806CE78
	cmp r0, #0xe
	beq _0806CE78
	cmp r0, #0xf
	bne _0806CEA2
_0806CE78:
	ldr r2, [r3, #0x2c]
	adds r0, r2, #0
	adds r0, #0x8c
	ldr r0, [r0]
	movs r1, #0x80
	lsls r1, r1, #2
	ands r0, r1
	cmp r0, #0
	beq _0806CEA2
	ldr r1, [r2, #0x54]
	ldr r0, [r4]
	cmp r1, r0
	bge _0806CE9A
	adds r1, r2, #0
	adds r1, #0xbb
	movs r0, #0xff
	b _0806CEA0
_0806CE9A:
	adds r1, r2, #0
	adds r1, #0xbb
	movs r0, #0xfe
_0806CEA0:
	strb r0, [r1]
_0806CEA2:
	ldr r0, [r3, #4]
	ldrb r0, [r0]
	cmp r0, #2
	bne _0806CF20
	ldr r0, [r3, #0xc]
	ldr r0, [r0, #4]
	ldr r0, [r0, #4]
	ldr r1, _0806CEEC @ =0x000200FF
	ands r0, r1
	subs r1, #0xfd
	cmp r0, r1
	bne _0806CF20
	ldr r2, [r3, #0x2c]
	ldrb r0, [r2, #0xd]
	subs r0, #5
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #1
	bls _0806CF20
	ldrb r1, [r2, #0xa]
	movs r0, #0x10
	ands r0, r1
	lsls r0, r0, #0x18
	lsrs r3, r0, #0x18
	cmp r3, #0
	bne _0806CEF4
	ldr r0, _0806CEF0 @ =pZero2
	ldr r0, [r0]
	ldr r1, [r0, #0x54]
	ldr r0, [r2, #0x54]
	cmp r1, r0
	bge _0806CF08
	movs r0, #5
	strb r0, [r2, #0xd]
	strb r3, [r2, #0xe]
	b _0806CF08
	.align 2, 0
_0806CEEC: .4byte 0x000200FF
_0806CEF0: .4byte pZero2
_0806CEF4:
	ldr r0, _0806CF28 @ =pZero2
	ldr r0, [r0]
	ldr r1, [r0, #0x54]
	ldr r0, [r2, #0x54]
	cmp r1, r0
	ble _0806CF08
	movs r1, #0
	movs r0, #5
	strb r0, [r2, #0xd]
	strb r1, [r2, #0xe]
_0806CF08:
	adds r0, r2, #0
	adds r0, #0x8c
	ldr r0, [r0]
	movs r1, #0x80
	lsls r1, r1, #2
	ands r0, r1
	cmp r0, #0
	beq _0806CF20
	adds r1, r2, #0
	adds r1, #0xa4
	movs r0, #1
	strh r0, [r1]
_0806CF20:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_0806CF28: .4byte pZero2
