	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start Projectile6_Update
Projectile6_Update: @ 0x0809DC74
	push {lr}
	adds r3, r0, #0
	ldr r2, [r3, #0x28]
	ldrb r0, [r2, #0xc]
	cmp r0, #1
	bhi _0809DCAC
	ldr r0, _0809DCC8 @ =gCurStory
	ldrb r1, [r0, #8]
	movs r0, #0x40
	ands r0, r1
	cmp r0, #0
	beq _0809DCD0
	ldrb r1, [r3, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r1, #0
	strb r0, [r3, #0xa]
	adds r0, r3, #0
	adds r0, #0x8c
	str r1, [r0]
	adds r0, #4
	str r1, [r0]
	adds r0, #4
	strb r1, [r0]
	ldrb r1, [r3, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r3, #0xa]
_0809DCAC:
	ldr r1, _0809DCCC @ =gProjectileFnTable
	ldrb r0, [r3, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r3, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r3, #0x14]
	adds r0, r3, #0
	bl Projectile6_Die
	b _0809DD1A
	.align 2, 0
_0809DCC8: .4byte gCurStory
_0809DCCC: .4byte gProjectileFnTable
_0809DCD0:
	ldrb r0, [r2, #0xa]
	lsrs r2, r0, #4
	movs r0, #1
	ands r2, r0
	cmp r2, #0
	beq _0809DCE4
	ldrb r1, [r3, #0xa]
	movs r0, #0x10
	orrs r0, r1
	b _0809DCEA
_0809DCE4:
	ldrb r1, [r3, #0xa]
	movs r0, #0xef
	ands r0, r1
_0809DCEA:
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
	ldr r1, _0809DD20 @ =sUpdates
	ldrb r0, [r3, #0xd]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r1, [r0]
	adds r0, r3, #0
	bl _call_via_r1
_0809DD1A:
	pop {r0}
	bx r0
	.align 2, 0
_0809DD20: .4byte sUpdates
