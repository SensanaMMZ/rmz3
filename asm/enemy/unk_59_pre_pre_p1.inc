	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_08091280
FUN_08091280: @ 0x08091280
	push {r4, r5, r6, lr}
	mov r6, sl
	mov r5, sb
	mov r4, r8
	push {r4, r5, r6}
	mov sl, r0
	ldr r0, _08091300 @ =RNG_0202f388
	mov sb, r0
	ldr r0, [r0]
	ldr r6, _08091304 @ =0x000343FD
	muls r0, r6, r0
	ldr r4, _08091308 @ =0x00269EC3
	adds r0, r0, r4
	lsls r0, r0, #1
	lsrs r2, r0, #1
	lsrs r0, r0, #0x11
	movs r1, #0x1f
	ands r0, r1
	subs r0, #0x10
	lsls r0, r0, #8
	mov r1, sl
	ldr r5, [r1, #0x54]
	adds r5, r5, r0
	adds r0, r2, #0
	muls r0, r6, r0
	adds r0, r0, r4
	lsls r0, r0, #1
	lsrs r2, r0, #1
	mov r8, r2
	mov r1, sb
	str r2, [r1]
	lsrs r0, r0, #0x11
	rsbs r0, r0, #0
	movs r1, #0x30
	bl __umodsi3
	lsls r0, r0, #8
	mov r2, sl
	ldr r1, [r2, #0x58]
	subs r1, r1, r0
	movs r2, #0x80
	lsls r2, r2, #1
	mov r3, r8
	muls r3, r6, r3
	adds r3, r3, r4
	lsls r3, r3, #1
	lsrs r0, r3, #1
	mov r4, sb
	str r0, [r4]
	lsrs r3, r3, #0x11
	movs r0, #0x7f
	ands r3, r0
	movs r0, #0x80
	orrs r3, r0
	adds r0, r5, #0
	bl FUN_080c4c2c
	pop {r3, r4, r5}
	mov r8, r3
	mov sb, r4
	mov sl, r5
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_08091300: .4byte RNG_0202f388
_08091304: .4byte 0x000343FD
_08091308: .4byte 0x00269EC3

	thumb_func_start FUN_0809130c
FUN_0809130c: @ 0x0809130C
	push {r4, r5, r6, r7, lr}
	adds r5, r0, #0
	lsls r1, r1, #0x18
	lsrs r6, r1, #0x18
	adds r7, r6, #0
	ldr r0, _080913B8 @ =gEnemyHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	adds r4, r0, #0
	cmp r4, #0
	beq _080913B2
	adds r1, r4, #0
	adds r1, #0x25
	movs r2, #0
	movs r0, #0x18
	strb r0, [r1]
	ldr r0, _080913BC @ =gEnemyFnTable
	movs r1, #0x3b
	strb r1, [r4, #9]
	adds r0, #0xec
	ldr r0, [r0]
	ldr r0, [r0]
	str r0, [r4, #0x14]
	movs r0, #0
	strh r2, [r4, #0x20]
	adds r1, r4, #0
	adds r1, #0x22
	strb r0, [r1]
	ldrb r1, [r4, #0xb]
	movs r0, #0x10
	orrs r0, r1
	strb r0, [r4, #0xb]
	ldrb r0, [r4, #0x1c]
	strb r0, [r4, #0x1d]
	ldr r0, [r5, #0x54]
	str r0, [r4, #0x54]
	ldr r0, [r5, #0x58]
	str r0, [r4, #0x58]
	cmp r6, #3
	bhi _08091372
	subs r0, r6, #2
	lsls r1, r0, #1
	adds r1, r1, r0
	lsls r1, r1, #0xc
	movs r0, #0xc0
	lsls r0, r0, #5
	adds r1, r1, r0
	ldr r0, [r5, #0x54]
	adds r0, r0, r1
	str r0, [r4, #0x64]
_08091372:
	cmp r6, #4
	bls _0809138A
	subs r0, r6, #7
	lsls r1, r0, #1
	adds r1, r1, r0
	lsls r1, r1, #0xc
	movs r0, #0xc0
	lsls r0, r0, #5
	adds r1, r1, r0
	ldr r0, [r5, #0x54]
	adds r0, r0, r1
	str r0, [r4, #0x54]
_0809138A:
	str r5, [r4, #0x28]
	adds r0, r4, #0
	bl InitNonAffineMotion
	adds r0, r4, #0
	bl ResetDynamicMotion
	ldr r0, [r5, #8]
	str r0, [r4, #0x3c]
	ldrb r1, [r5, #0x15]
	adds r3, r4, #0
	adds r3, #0x49
	lsrs r1, r1, #4
	lsls r1, r1, #4
	ldrb r2, [r3]
	movs r0, #0xf
	ands r0, r2
	orrs r0, r1
	strb r0, [r3]
	strb r7, [r4, #0x10]
_080913B2:
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080913B8: .4byte gEnemyHeaderPtr
_080913BC: .4byte gEnemyFnTable

	thumb_func_start FUN_080913c0
FUN_080913c0: @ 0x080913C0
	push {r4, r5, lr}
	adds r4, r0, #0
	lsls r1, r1, #0x18
	lsrs r5, r1, #0x18
	ldr r0, _08091424 @ =gEnemyHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	adds r3, r0, #0
	cmp r3, #0
	beq _0809141E
	adds r1, r3, #0
	adds r1, #0x25
	movs r2, #0
	movs r0, #0x18
	strb r0, [r1]
	ldr r0, _08091428 @ =gEnemyFnTable
	movs r1, #0x3b
	strb r1, [r3, #9]
	adds r0, #0xec
	ldr r0, [r0]
	ldr r0, [r0]
	str r0, [r3, #0x14]
	movs r0, #0
	strh r2, [r3, #0x20]
	adds r1, r3, #0
	adds r1, #0x22
	strb r0, [r1]
	ldrb r1, [r3, #0xb]
	movs r0, #0x10
	orrs r0, r1
	strb r0, [r3, #0xb]
	ldrb r0, [r3, #0x1c]
	strb r0, [r3, #0x1d]
	ldr r0, [r4, #0x54]
	str r0, [r3, #0x54]
	ldr r0, [r4, #0x58]
	str r0, [r3, #0x58]
	strb r5, [r3, #0x10]
	movs r1, #0
	adds r0, r4, #0
	adds r0, #0xb4
	ldr r0, [r0]
	cmp r0, #0
	ble _0809141C
	movs r1, #1
_0809141C:
	strb r1, [r3, #0x13]
_0809141E:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_08091424: .4byte gEnemyHeaderPtr
_08091428: .4byte gEnemyFnTable
