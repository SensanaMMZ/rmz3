	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080b116c
FUN_080b116c: @ 0x080B116C
	push {r4, r5, r6, lr}
	adds r5, r0, #0
	ldr r0, [r5, #0x28]
	ldrb r0, [r0, #0xc]
	cmp r0, #1
	bhi _080B11EA
	cmp r0, #4
	beq _080B11EA
	ldrb r6, [r5, #0xe]
	cmp r6, #0
	beq _080B1188
	cmp r6, #1
	beq _080B11B4
	b _080B1220
_080B1188:
	ldrb r1, [r5, #0xa]
	movs r0, #4
	orrs r0, r1
	strb r0, [r5, #0xa]
	adds r4, r5, #0
	adds r4, #0x74
	ldr r1, _080B1228 @ =0x0836D48C
	adds r2, r5, #0
	adds r2, #0x54
	adds r0, r4, #0
	movs r3, #1
	bl InitBody
	str r5, [r4, #0x2c]
	str r6, [r4, #0x24]
	ldrb r1, [r5, #0xa]
	movs r0, #2
	orrs r0, r1
	strb r0, [r5, #0xa]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_080B11B4:
	ldr r2, [r5, #0x2c]
	ldr r0, [r2, #0x54]
	ldr r1, [r2, #0x58]
	str r0, [r5, #0x54]
	str r1, [r5, #0x58]
	ldr r0, _080B122C @ =pZero2
	ldr r0, [r0]
	ldr r0, [r0, #0x54]
	str r0, [r5, #0x54]
	adds r2, #0xbc
	ldr r1, [r2]
	asrs r1, r1, #9
	adds r0, r5, #0
	adds r0, #0x74
	movs r2, #0x10
	subs r2, r2, r1
	lsls r1, r2, #1
	adds r1, r1, r2
	lsls r1, r1, #3
	ldr r2, _080B1228 @ =0x0836D48C
	adds r1, r1, r2
	bl SetDDP
	ldr r0, [r5, #0x2c]
	ldrb r0, [r0, #0xe]
	cmp r0, #9
	bls _080B1220
_080B11EA:
	ldrb r1, [r5, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r2, #0
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r5, #0xa]
	adds r0, r5, #0
	adds r0, #0x8c
	str r2, [r0]
	adds r0, #4
	str r2, [r0]
	adds r0, #4
	strb r2, [r0]
	ldrb r1, [r5, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r5, #0xa]
	ldr r1, _080B1230 @ =gProjectileFnTable
	ldrb r0, [r5, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r5, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r5, #0x14]
_080B1220:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_080B1228: .4byte 0x0836D48C
_080B122C: .4byte pZero2
_080B1230: .4byte gProjectileFnTable
