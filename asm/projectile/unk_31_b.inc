	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start Projectile31_Init
Projectile31_Init: @ 0x080AA808
	push {r4, r5, r6, r7, lr}
	adds r6, r0, #0
	ldr r7, [r6, #0x28]
	bl InitRotatableMotion
	ldrb r1, [r6, #0xa]
	movs r0, #1
	movs r5, #0
	orrs r0, r1
	movs r1, #2
	orrs r0, r1
	strb r0, [r6, #0xa]
	ldr r1, _080AA894 @ =0x0000640F
	adds r0, r6, #0
	bl SetMotion
	ldrb r1, [r6, #0xa]
	movs r0, #4
	orrs r0, r1
	strb r0, [r6, #0xa]
	adds r4, r6, #0
	adds r4, #0x74
	ldr r1, _080AA898 @ =0x0836C32C
	adds r2, r6, #0
	adds r2, #0x54
	adds r0, r4, #0
	movs r3, #0x40
	bl InitBody
	str r6, [r4, #0x2c]
	str r5, [r4, #0x24]
	ldrb r1, [r6, #0xa]
	movs r0, #0xef
	ands r0, r1
	strb r0, [r6, #0xa]
	adds r0, r6, #0
	adds r0, #0x4c
	strb r5, [r0]
	adds r2, r6, #0
	adds r2, #0x4a
	ldrb r1, [r2]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r2]
	ldr r0, [r7, #0x54]
	ldr r1, [r7, #0x58]
	str r0, [r6, #0x54]
	str r1, [r6, #0x58]
	ldrb r1, [r7, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _080AA8A4
	ldr r2, _080AA89C @ =0x0836C35C
	ldrb r1, [r6, #0x11]
	movs r0, #3
	ands r0, r1
	lsls r0, r0, #2
	adds r0, r0, r2
	ldr r1, [r7, #0x54]
	ldr r0, [r0]
	adds r1, r1, r0
	str r1, [r6, #0x54]
	ldr r1, _080AA8A0 @ =0x0836C36C
	ldrb r0, [r6, #0x11]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r0, [r0]
	b _080AA8C4
	.align 2, 0
_080AA894: .4byte 0x0000640F
_080AA898: .4byte 0x0836C32C
_080AA89C: .4byte 0x0836C35C
_080AA8A0: .4byte 0x0836C36C
_080AA8A4:
	ldr r2, _080AA91C @ =0x0836C35C
	ldrb r1, [r6, #0x11]
	movs r0, #3
	ands r0, r1
	lsls r0, r0, #2
	adds r0, r0, r2
	ldr r1, [r7, #0x54]
	ldr r0, [r0]
	subs r1, r1, r0
	str r1, [r6, #0x54]
	ldr r1, _080AA920 @ =0x0836C36C
	ldrb r0, [r6, #0x11]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r0, [r0]
	rsbs r0, r0, #0
_080AA8C4:
	str r0, [r6, #0x5c]
	ldrb r2, [r6, #0x11]
	ldr r0, [r7, #0x58]
	ldr r1, _080AA924 @ =0xFFFFD000
	adds r0, r0, r1
	str r0, [r6, #0x58]
	ldr r1, _080AA928 @ =0x0836C38C
	lsls r0, r2, #2
	adds r0, r0, r1
	ldr r1, [r0]
	str r1, [r6, #0x60]
	ldr r0, [r6, #0x5c]
	lsls r0, r0, #0x10
	asrs r0, r0, #0x10
	lsls r1, r1, #0x10
	asrs r1, r1, #0x10
	bl ArcTan2
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	movs r1, #0x80
	lsls r1, r1, #7
	adds r0, r0, r1
	asrs r0, r0, #8
	strb r0, [r6, #0x13]
	adds r1, r6, #0
	adds r1, #0x24
	strb r0, [r1]
	ldr r1, _080AA92C @ =gProjectileFnTable
	ldrb r0, [r6, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r6, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r6, #0x14]
	adds r0, r6, #0
	bl Projectile31_Update
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080AA91C: .4byte 0x0836C35C
_080AA920: .4byte 0x0836C36C
_080AA924: .4byte 0xFFFFD000
_080AA928: .4byte 0x0836C38C
_080AA92C: .4byte gProjectileFnTable

	thumb_func_start Projectile31_Update
Projectile31_Update: @ 0x080AA930
	push {r4, r5, r6, r7, lr}
	mov r7, sl
	mov r6, sb
	mov r5, r8
	push {r5, r6, r7}
	sub sp, #4
	adds r7, r0, #0
	bl UpdateMotionGraphic
	ldr r0, [r7, #0x5c]
	lsls r0, r0, #0x10
	asrs r0, r0, #0x10
	ldr r1, [r7, #0x60]
	lsls r1, r1, #0x10
	asrs r1, r1, #0x10
	bl ArcTan2
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	movs r1, #0x80
	lsls r1, r1, #7
	adds r0, r0, r1
	asrs r0, r0, #8
	strb r0, [r7, #0x13]
	adds r1, r7, #0
	adds r1, #0x24
	strb r0, [r1]
	ldr r0, [r7, #0x54]
	ldr r1, [r7, #0x5c]
	adds r0, r0, r1
	str r0, [r7, #0x54]
	ldr r1, [r7, #0x58]
	ldr r2, [r7, #0x60]
	adds r1, r1, r2
	str r1, [r7, #0x58]
	adds r2, #0x40
	str r2, [r7, #0x60]
	bl FUN_080098a4
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _080AAA2A
	movs r2, #0x54
	adds r2, r2, r7
	mov sl, r2
	ldr r0, _080AAA3C @ =RNG_0202f388
	mov r8, r0
	ldr r0, [r0]
	ldr r6, _080AAA40 @ =0x000343FD
	adds r3, r0, #0
	muls r3, r6, r3
	ldr r5, _080AAA44 @ =0x00269EC3
	adds r3, r3, r5
	lsls r3, r3, #1
	lsrs r0, r3, #1
	lsrs r3, r3, #0x11
	movs r1, #0xff
	ands r3, r1
	movs r2, #0x80
	lsls r2, r2, #1
	adds r4, r2, #0
	orrs r3, r4
	muls r0, r6, r0
	adds r0, r0, r5
	lsls r0, r0, #1
	lsrs r1, r0, #1
	mov r2, r8
	str r1, [r2]
	lsrs r0, r0, #0x11
	ldr r1, _080AAA48 @ =0x000003FF
	mov sb, r1
	mov r2, sb
	ands r0, r2
	adds r0, r0, r4
	rsbs r0, r0, #0
	lsls r0, r0, #0x10
	asrs r0, r0, #0x10
	str r0, [sp]
	mov r0, sl
	movs r1, #1
	movs r2, #1
	bl CreateVFX57
	mov r1, r8
	ldr r0, [r1]
	adds r3, r0, #0
	muls r3, r6, r3
	adds r3, r3, r5
	lsls r3, r3, #1
	lsrs r0, r3, #1
	lsrs r3, r3, #0x11
	movs r2, #0xff
	ands r3, r2
	adds r3, r3, r4
	rsbs r3, r3, #0
	lsls r3, r3, #0x10
	asrs r3, r3, #0x10
	muls r0, r6, r0
	adds r0, r0, r5
	lsls r0, r0, #1
	lsrs r1, r0, #1
	mov r2, r8
	str r1, [r2]
	lsrs r0, r0, #0x11
	mov r1, sb
	ands r0, r1
	adds r0, r0, r4
	rsbs r0, r0, #0
	lsls r0, r0, #0x10
	asrs r0, r0, #0x10
	str r0, [sp]
	mov r0, sl
	movs r1, #1
	movs r2, #3
	bl CreateVFX57
	ldr r1, _080AAA4C @ =gProjectileFnTable
	ldrb r0, [r7, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r7, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r7, #0x14]
_080AAA2A:
	add sp, #4
	pop {r3, r4, r5}
	mov r8, r3
	mov sb, r4
	mov sl, r5
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080AAA3C: .4byte RNG_0202f388
_080AAA40: .4byte 0x000343FD
_080AAA44: .4byte 0x00269EC3
_080AAA48: .4byte 0x000003FF
_080AAA4C: .4byte gProjectileFnTable
