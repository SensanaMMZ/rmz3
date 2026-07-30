	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080aaed8
FUN_080aaed8: @ 0x080AAED8
	push {r4, r5, r6, r7, lr}
	mov r7, sb
	mov r6, r8
	push {r6, r7}
	adds r7, r0, #0
	ldr r6, [r7, #0x28]
	ldr r1, _080AAF4C @ =gProjectileFnTable
	ldrb r0, [r7, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	mov sb, r1
	str r1, [r7, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r7, #0x14]
	adds r0, r7, #0
	bl InitNonAffineMotion
	ldrb r1, [r7, #0xa]
	movs r0, #1
	movs r5, #0
	movs r2, #0
	mov r8, r2
	orrs r0, r1
	movs r1, #2
	orrs r0, r1
	strb r0, [r7, #0xa]
	ldr r1, _080AAF50 @ =0x00006208
	adds r0, r7, #0
	bl SetMotion
	ldrb r0, [r7, #0xa]
	movs r1, #4
	orrs r0, r1
	strb r0, [r7, #0xa]
	adds r4, r7, #0
	adds r4, #0x74
	ldr r1, _080AAF54 @ =0x0836C42C
	adds r2, r7, #0
	adds r2, #0x54
	adds r0, r4, #0
	movs r3, #0x40
	bl InitBody
	str r7, [r4, #0x2c]
	mov r0, r8
	str r0, [r4, #0x24]
	ldrb r0, [r6, #0xa]
	lsrs r2, r0, #4
	mov r1, sb
	ands r2, r1
	cmp r2, #0
	beq _080AAF58
	ldrb r0, [r7, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _080AAF5E
	.align 2, 0
_080AAF4C: .4byte gProjectileFnTable
_080AAF50: .4byte 0x00006208
_080AAF54: .4byte 0x0836C42C
_080AAF58:
	ldrb r1, [r7, #0xa]
	movs r0, #0xef
	ands r0, r1
_080AAF5E:
	strb r0, [r7, #0xa]
	adds r1, r2, #0
	adds r0, r7, #0
	adds r0, #0x4c
	strb r1, [r0]
	adds r3, r7, #0
	adds r3, #0x4a
	lsls r1, r1, #4
	ldrb r2, [r3]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r1
	strb r0, [r3]
	ldr r0, [r6, #0x54]
	str r0, [r7, #0x54]
	ldr r0, [r6, #0x58]
	ldr r2, _080AAFAC @ =0xFFFFF000
	adds r0, r0, r2
	str r0, [r7, #0x58]
	adds r1, r7, #0
	adds r1, #0xb8
	adds r0, r6, #0
	adds r0, #0xbc
	ldr r0, [r0]
	str r0, [r1]
	ldrb r1, [r7, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _080AAFB0
	ldrb r0, [r7, #0x11]
	cmp r0, #0x80
	bhi _080AAFC2
	cmp r0, #0x4f
	bhi _080AAFC6
	movs r0, #0x50
	b _080AAFC4
	.align 2, 0
_080AAFAC: .4byte 0xFFFFF000
_080AAFB0:
	ldrb r0, [r7, #0x11]
	lsls r1, r0, #0x18
	lsrs r0, r1, #0x18
	cmp r0, #0xc0
	bls _080AAFBE
	movs r0, #0xc0
	b _080AAFC4
_080AAFBE:
	cmp r1, #0
	blt _080AAFC6
_080AAFC2:
	movs r0, #0x80
_080AAFC4:
	strb r0, [r7, #0x11]
_080AAFC6:
	ldr r3, _080AB000 @ =gSineTable
	ldrb r0, [r7, #0x11]
	adds r1, r0, #0
	adds r1, #0xc0
	lsls r0, r0, #1
	adds r0, r0, r3
	movs r4, #0
	ldrsh r2, [r0, r4]
	lsls r0, r2, #2
	adds r0, r0, r2
	str r0, [r7, #0x5c]
	lsls r1, r1, #0x18
	lsrs r1, r1, #0x17
	adds r1, r1, r3
	movs r0, #0
	ldrsh r1, [r1, r0]
	lsls r0, r1, #2
	adds r0, r0, r1
	str r0, [r7, #0x60]
	adds r0, r7, #0
	bl Projectile32_Update
	pop {r3, r4}
	mov r8, r3
	mov sb, r4
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080AB000: .4byte gSineTable
