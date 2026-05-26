	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_0807cce0
FUN_0807cce0: @ 0x0807CCE0
	push {r4, r5, r6, r7, lr}
	mov r7, sb
	mov r6, r8
	push {r6, r7}
	sub sp, #4
	adds r7, r0, #0
	adds r6, r1, #0
	movs r5, #0
	movs r3, #0
	ldr r1, _0807CD64 @ =0x083659CC
	mov r8, r1
	ldr r4, _0807CD68 @ =0x08367C24
_0807CCF8:
	ldr r0, _0807CD6C @ =gEnemyHeaderPtr
	ldr r0, [r0]
	str r3, [sp]
	bl AllocEntityLast
	adds r2, r0, #0
	ldr r3, [sp]
	cmp r2, #0
	beq _0807CD4C
	adds r1, r2, #0
	adds r1, #0x25
	movs r0, #0x18
	strb r0, [r1]
	movs r0, #0x21
	strb r0, [r2, #9]
	mov r1, r8
	ldr r0, [r1]
	ldr r0, [r0]
	str r0, [r2, #0x14]
	strh r3, [r2, #0x20]
	adds r0, r2, #0
	adds r0, #0x22
	strb r3, [r0]
	ldrb r0, [r2, #0xb]
	movs r1, #0x10
	orrs r0, r1
	strb r0, [r2, #0xb]
	ldrb r0, [r2, #0x1c]
	strb r0, [r2, #0x1d]
	movs r0, #3
	strb r0, [r2, #0x10]
	strb r5, [r2, #0x11]
	str r7, [r2, #0x54]
	movs r1, #0
	ldrsh r0, [r4, r1]
	adds r0, r7, r0
	str r0, [r2, #0x54]
	str r6, [r2, #0x58]
	movs r1, #2
	ldrsh r0, [r4, r1]
	adds r0, r6, r0
	str r0, [r2, #0x58]
_0807CD4C:
	adds r4, #4
	adds r5, #1
	cmp r5, #3
	ble _0807CCF8
	add sp, #4
	pop {r3, r4}
	mov r8, r3
	mov sb, r4
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_0807CD64: .4byte 0x083659CC
_0807CD68: .4byte 0x08367C24
_0807CD6C: .4byte gEnemyHeaderPtr
