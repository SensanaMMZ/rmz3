	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_08071bf0
FUN_08071bf0: @ 0x08071BF0
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
	ldr r1, _08071C64 @ =0xFFFFF000
	adds r0, r0, r1
	str r0, [sp, #4]
	movs r0, #1
	mov r1, sp
	bl CreateSmoke
	movs r0, #0x2a
	bl PlaySound
	ldr r2, _08071C68 @ =0x08366BB2
	adds r0, r4, #0
	mov r1, sp
	movs r3, #4
	bl FUN_080b7f70
	adds r0, r4, #0
	adds r0, #0xb4
	ldr r1, [r0]
	adds r0, r1, #0
	adds r0, #0x2f
	ldrb r0, [r0]
	cmp r0, #0
	bne _08071C48
	ldr r0, [r1, #0x20]
	adds r0, #5
	str r0, [r1, #0x20]
_08071C48:
	ldr r1, _08071C6C @ =gEnemyFnTable
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
_08071C64: .4byte 0xFFFFF000
_08071C68: .4byte 0x08366BB2
_08071C6C: .4byte gEnemyFnTable
