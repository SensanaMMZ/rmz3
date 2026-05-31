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

