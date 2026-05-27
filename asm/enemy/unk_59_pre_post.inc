	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_08091790
FUN_08091790: @ 0x08091790
	push {r4, lr}
	adds r1, r0, #0
	ldr r0, [r1, #0xc]
	ldr r4, [r0, #0x2c]
	ldr r3, [r1, #0x2c]
	ldrb r0, [r3, #0x10]
	cmp r0, #0xc
	bne _080917F4
	ldr r0, [r1, #0x14]
	movs r1, #8
	ands r0, r1
	cmp r0, #0
	beq _08091804
	movs r0, #8
	ldrsb r0, [r4, r0]
	cmp r0, #2
	bne _08091804
	ldrb r0, [r4, #0xd]
	cmp r0, #1
	bne _08091804
	ldrb r0, [r4, #0xe]
	subs r0, #1
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #1
	bhi _08091804
	ldrb r0, [r4, #9]
	cmp r0, #0x15
	bne _08091804
	ldr r0, [r3, #0xc]
	ldr r1, _080917F0 @ =0x00FFFF00
	ands r0, r1
	movs r1, #0xc2
	lsls r1, r1, #0xa
	cmp r0, r1
	bne _08091804
	adds r2, r3, #0
	adds r2, #0xb4
	ldr r0, [r4, #0x54]
	ldr r1, [r3, #0x54]
	subs r0, r0, r1
	str r0, [r2]
	movs r1, #0
	movs r0, #9
	strb r0, [r3, #0xd]
	strb r1, [r3, #0xe]
	b _08091804
	.align 2, 0
_080917F0: .4byte 0x00FFFF00
_080917F4:
	adds r2, r3, #0
	adds r2, #0xb4
	ldr r0, _0809180C @ =pZero2
	ldr r0, [r0]
	ldr r0, [r0, #0x54]
	ldr r1, [r3, #0x54]
	subs r0, r0, r1
	str r0, [r2]
_08091804:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_0809180C: .4byte pZero2

