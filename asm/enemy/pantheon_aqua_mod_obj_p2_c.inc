	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start PantheonAquaModObj_Die
PantheonAquaModObj_Die: @ 0x08080F94
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
	str r0, [sp, #4]
	ldr r2, _08080FE0 @ =0x083680FA
	adds r0, r4, #0
	mov r1, sp
	movs r3, #3
	bl FUN_080b81a0
	ldr r1, _08080FE4 @ =gEnemyFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #4
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0x10]
	str r0, [r4, #0x14]
	add sp, #8
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_08080FE0: .4byte 0x083680FA
_08080FE4: .4byte gEnemyFnTable
