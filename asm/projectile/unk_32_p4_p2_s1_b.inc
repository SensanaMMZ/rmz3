	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080ab668
FUN_080ab668: @ 0x080AB668
	push {r4, r5, lr}
	sub sp, #8
	adds r4, r0, #0
	ldr r5, [r4, #0x28]
	ldr r1, [r4, #0x5c]
	ldrb r0, [r4, #0x13]
	adds r0, r0, r1
	strb r0, [r4, #0x13]
	ldrb r1, [r4, #0x12]
	movs r0, #7
	ands r0, r1
	cmp r0, #0
	bne _080AB6D4
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	ands r0, r1
	adds r3, r1, #0
	cmp r0, #0
	beq _080AB696
	ldr r0, [r4, #0x54]
	movs r1, #0x80
	lsls r1, r1, #5
	b _080AB69A
_080AB696:
	ldr r0, [r4, #0x54]
	ldr r1, _080AB710 @ =0xFFFFF000
_080AB69A:
	adds r0, r0, r1
	str r0, [sp]
	ldr r2, _080AB714 @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _080AB718 @ =0x000343FD
	muls r1, r0, r1
	ldr r0, _080AB71C @ =0x00269EC3
	adds r1, r1, r0
	lsls r1, r1, #1
	lsrs r0, r1, #1
	str r0, [r2]
	lsrs r1, r1, #0x11
	movs r0, #0x3f
	ands r1, r0
	lsls r1, r1, #8
	ldr r0, [r4, #0x58]
	subs r0, r0, r1
	movs r1, #0xf8
	lsls r1, r1, #5
	adds r0, r0, r1
	str r0, [sp, #4]
	lsls r1, r3, #0x18
	lsrs r1, r1, #0x1c
	movs r0, #1
	ands r1, r0
	mov r0, sp
	adds r2, r4, #0
	bl FUN_080aad0c
_080AB6D4:
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0xff
	beq _080AB6EE
	ldrb r0, [r5, #0xc]
	cmp r0, #1
	bhi _080AB6EE
	ldrb r0, [r5, #0xd]
	cmp r0, #0x13
	bne _080AB706
_080AB6EE:
	ldr r1, _080AB720 @ =gProjectileFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r4, #0x14]
	adds r0, r4, #0
	bl Projectile32_Die
_080AB706:
	add sp, #8
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080AB710: .4byte 0xFFFFF000
_080AB714: .4byte RNG_0202f388
_080AB718: .4byte 0x000343FD
_080AB71C: .4byte 0x00269EC3
_080AB720: .4byte gProjectileFnTable
