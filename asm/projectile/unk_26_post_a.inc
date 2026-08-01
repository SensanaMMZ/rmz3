	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start Projectile26_Die
Projectile26_Die: @ 0x080A8990
	push {lr}
	adds r2, r0, #0
	ldr r3, [r2, #0x28]
	ldrb r0, [r2, #0x10]
	cmp r0, #1
	bhi _080A89F8
	ldrb r0, [r2, #0x12]
	subs r0, #1
	movs r1, #0
	strb r0, [r2, #0x12]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0xff
	bne _080A8A2E
	adds r0, r2, #0
	adds r0, #0x8c
	str r1, [r0]
	adds r0, #4
	str r1, [r0]
	adds r0, #4
	strb r1, [r0]
	ldrb r1, [r2, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r2, #0xa]
	ldr r1, _080A89F4 @ =gProjectileFnTable
	ldrb r0, [r2, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #4
	str r1, [r2, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0x10]
	str r0, [r2, #0x14]
	adds r1, r3, #0
	adds r1, #0xcf
	ldrb r0, [r1]
	subs r0, #1
	strb r0, [r1]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080A8A2E
	adds r0, r2, #0
	adds r0, #0xc0
	movs r1, #0
	ldrsh r0, [r0, r1]
	bl StopSound
	b _080A8A2E
	.align 2, 0
_080A89F4: .4byte gProjectileFnTable
_080A89F8:
	adds r0, r2, #0
	adds r0, #0x8c
	movs r1, #0
	str r1, [r0]
	adds r0, #4
	str r1, [r0]
	adds r0, #4
	strb r1, [r0]
	ldrb r1, [r2, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r2, #0xa]
	ldr r1, _080A8A34 @ =gProjectileFnTable
	ldrb r0, [r2, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #4
	str r1, [r2, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0x10]
	str r0, [r2, #0x14]
	adds r0, r2, #0
	adds r0, #0xc0
	movs r1, #0
	ldrsh r0, [r0, r1]
	bl StopSound
_080A8A2E:
	pop {r0}
	bx r0
	.align 2, 0
_080A8A34: .4byte gProjectileFnTable
