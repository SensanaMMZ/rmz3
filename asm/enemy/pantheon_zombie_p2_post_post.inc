	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_08080674
FUN_08080674: @ 0x08080674
	push {r4, lr}
	sub sp, #8
	adds r4, r0, #0
	adds r0, #0x8c
	movs r1, #0
	str r1, [r0]
	adds r0, #4
	str r1, [r0]
	adds r0, #4
	strb r1, [r0]
	ldrb r1, [r4, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r4, #0xa]
	ldr r0, [r4, #0x54]
	str r0, [sp]
	ldr r0, [r4, #0x58]
	ldr r1, _080806D8 @ =0xFFFFF000
	adds r0, r0, r1
	str r0, [sp, #4]
	movs r0, #1
	mov r1, sp
	bl CreateSmoke
	movs r0, #0x56
	bl PlaySound
	ldr r0, [sp]
	ldr r1, [sp, #4]
	bl FUN_080bf52c
	ldr r1, _080806DC @ =gEnemyFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #4
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0x10]
	str r0, [r4, #0x14]
	ldr r1, [r4, #0x28]
	adds r1, #0xcb
	ldrb r0, [r1]
	subs r0, #1
	strb r0, [r1]
	add sp, #8
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080806D8: .4byte 0xFFFFF000
_080806DC: .4byte gEnemyFnTable
