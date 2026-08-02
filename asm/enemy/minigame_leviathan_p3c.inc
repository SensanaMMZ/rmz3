	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_0809ac28
FUN_0809ac28: @ 0x0809AC28
	push {r4, r5, r6, lr}
	sub sp, #0xc
	adds r5, r0, #0
	ldr r4, [r5, #0x28]
	adds r0, r4, #0
	adds r0, #0x34
	ldrb r0, [r0]
	cmp r0, #0
	bne _0809AC7A
	ldr r0, [r4, #0x20]
	adds r0, #0x3c
	str r0, [r4, #0x20]
	adds r6, r4, #0
	adds r6, #0x35
	ldrb r0, [r6]
	adds r0, #1
	strb r0, [r6]
	ldr r0, [r4, #0x1c]
	adds r0, #1
	str r0, [r4, #0x1c]
	adds r1, r4, #0
	adds r1, #0x32
	ldrb r0, [r1]
	adds r0, #1
	strb r0, [r1]
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x58]
	ldr r2, [r4, #0x1c]
	movs r3, #1
	bl FUN_08099f54
	ldr r1, [r4, #0x1c]
	adds r1, #1
	cmp r1, #4
	ble _0809AC70
	movs r1, #4
_0809AC70:
	ldrb r0, [r6]
	muls r1, r0, r1
	ldr r0, [r4, #0x24]
	adds r0, r0, r1
	str r0, [r4, #0x24]
_0809AC7A:
	adds r0, r5, #0
	adds r0, #0x8c
	movs r1, #0
	str r1, [r0]
	adds r0, #4
	str r1, [r0]
	adds r0, #4
	strb r1, [r0]
	ldrb r1, [r5, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r5, #0xa]
	ldr r0, [r5, #0x54]
	str r0, [sp, #4]
	ldr r0, [r5, #0x58]
	str r0, [sp, #8]
	movs r0, #1
	add r1, sp, #4
	bl CreateSmoke
	movs r0, #0x31
	bl PlaySound
	ldr r2, _0809ACD4 @ =0x0836A77E
	movs r0, #1
	str r0, [sp]
	adds r0, r5, #0
	add r1, sp, #4
	movs r3, #3
	bl FUN_080b822c
	ldr r1, _0809ACD8 @ =gEnemyFnTable
	ldrb r0, [r5, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #4
	str r1, [r5, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0x10]
	str r0, [r5, #0x14]
	add sp, #0xc
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_0809ACD4: .4byte 0x0836A77E
_0809ACD8: .4byte gEnemyFnTable
