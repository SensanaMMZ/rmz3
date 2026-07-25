	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_080aab38
FUN_080aab38: @ 0x080AAB38
	push {r4, r5, lr}
	adds r4, r0, #0
	adds r5, r1, #0
	ldr r0, _080AAB90 @ =gProjectileHeaderPtr
	ldr r0, [r0]
	bl AllocEntityLast
	adds r3, r0, #0
	cmp r3, #0
	beq _080AABCE
	adds r1, r3, #0
	adds r1, #0x25
	movs r2, #0
	movs r0, #8
	strb r0, [r1]
	ldr r0, _080AAB94 @ =gProjectileFnTable
	movs r1, #0x20
	strb r1, [r3, #9]
	adds r0, #0x80
	ldr r0, [r0]
	ldr r0, [r0]
	str r0, [r3, #0x14]
	movs r1, #0
	strh r2, [r3, #0x20]
	adds r0, r3, #0
	adds r0, #0x22
	strb r1, [r0]
	movs r0, #2
	strb r0, [r3, #0x10]
	strb r1, [r3, #0x11]
	str r5, [r3, #0x28]
	movs r1, #0
	ldr r0, [r4, #0x5c]
	cmp r0, #0
	ble _080AAB80
	movs r1, #1
_080AAB80:
	adds r2, r1, #0
	cmp r2, #0
	beq _080AAB98
	ldrb r0, [r3, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _080AAB9E
	.align 2, 0
_080AAB90: .4byte gProjectileHeaderPtr
_080AAB94: .4byte gProjectileFnTable
_080AAB98:
	ldrb r1, [r3, #0xa]
	movs r0, #0xef
	ands r0, r1
_080AAB9E:
	strb r0, [r3, #0xa]
	adds r1, r2, #0
	adds r0, r3, #0
	adds r0, #0x4c
	strb r1, [r0]
	movs r0, #0x4a
	adds r0, r0, r3
	mov ip, r0
	lsls r1, r1, #4
	ldrb r2, [r0]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r1
	mov r1, ip
	strb r0, [r1]
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	str r0, [r3, #0x54]
	str r1, [r3, #0x58]
	adds r0, r4, #0
	adds r0, #0xb8
	ldr r0, [r0]
	str r0, [r3, #0x58]
_080AABCE:
	pop {r4, r5}
	pop {r0}
	bx r0
