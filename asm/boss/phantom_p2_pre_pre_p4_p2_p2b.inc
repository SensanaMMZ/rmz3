	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_0805fc7c
FUN_0805fc7c: @ 0x0805FC7C
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0x12]
	adds r0, #1
	strb r0, [r4, #0x12]
	movs r1, #3
	ands r0, r1
	cmp r0, #0
	beq _0805FC96
	ldrb r0, [r4, #0xa]
	movs r1, #1
	orrs r0, r1
	b _0805FC9C
_0805FC96:
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
_0805FC9C:
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	adds r0, #0xc4
	ldr r1, [r0]
	movs r2, #0x10
	ands r1, r2
	adds r5, r0, #0
	cmp r1, #0
	beq _0805FCB6
	movs r0, #1
	str r0, [r5]
	movs r0, #5
	b _0805FD52
_0805FCB6:
	ldrb r1, [r4, #0x12]
	ldrb r0, [r4, #0x13]
	subs r0, #0x3c
	cmp r1, r0
	ble _0805FCF4
	movs r0, #8
	str r0, [r5]
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _0805FCF0 @ =0x08365380
	bl SetDDP
	adds r0, r4, #0
	adds r0, #0x8c
	ldr r0, [r0]
	movs r1, #1
	ands r0, r1
	cmp r0, #0
	beq _0805FCF4
	adds r1, r4, #0
	adds r1, #0xc8
	ldrb r0, [r1]
	subs r0, #1
	strb r0, [r1]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _0805FD50
	movs r0, #4
	b _0805FD52
	.align 2, 0
_0805FCF0: .4byte 0x08365380
_0805FCF4:
	ldrb r0, [r4, #0x12]
	ldrb r1, [r4, #0x13]
	cmp r0, r1
	bls _0805FD54
	ldr r0, _0805FD14 @ =pZero2
	ldr r0, [r0]
	ldr r0, [r0, #0x54]
	ldr r1, [r4, #0x54]
	subs r2, r0, r1
	cmp r2, #0
	blt _0805FD1C
	ldr r0, _0805FD18 @ =0x00003FFF
	cmp r2, r0
	ble _0805FD24
	b _0805FD3C
	.align 2, 0
_0805FD14: .4byte pZero2
_0805FD18: .4byte 0x00003FFF
_0805FD1C:
	subs r1, r1, r0
	ldr r0, _0805FD38 @ =0x00003FFF
	cmp r1, r0
	bgt _0805FD3C
_0805FD24:
	ldrb r1, [r4, #0xa]
	movs r0, #1
	movs r2, #0
	orrs r0, r1
	strb r0, [r4, #0xa]
	movs r0, #1
	str r0, [r5]
	strb r0, [r4, #0xd]
	strh r2, [r4, #0xe]
	b _0805FD54
	.align 2, 0
_0805FD38: .4byte 0x00003FFF
_0805FD3C:
	adds r1, r4, #0
	adds r1, #0xc8
	ldrb r0, [r1]
	subs r0, #1
	strb r0, [r1]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _0805FD50
	movs r0, #4
	b _0805FD52
_0805FD50:
	movs r0, #3
_0805FD52:
	strh r0, [r4, #0xe]
_0805FD54:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
