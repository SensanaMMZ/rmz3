	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start Enemy63_Init
Enemy63_Init: @ 0x08094ADC
	push {r4, r5, lr}
	adds r5, r0, #0
	ldr r1, _08094B6C @ =gEnemyFnTable
	ldrb r0, [r5, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r5, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r5, #0x14]
	ldr r1, _08094B70 @ =0x08369F54
	ldrb r0, [r5, #0x10]
	adds r0, r0, r1
	ldrb r0, [r0]
	strb r0, [r5, #0xd]
	ldrb r0, [r5, #0xa]
	movs r1, #2
	orrs r0, r1
	movs r1, #1
	orrs r0, r1
	strb r0, [r5, #0xa]
	adds r0, r5, #0
	bl InitNonAffineMotion
	ldrb r1, [r5, #0xa]
	movs r0, #4
	orrs r0, r1
	strb r0, [r5, #0xa]
	adds r4, r5, #0
	adds r4, #0x74
	ldr r1, _08094B74 @ =0x08369EFC
	adds r2, r5, #0
	adds r2, #0x54
	adds r0, r4, #0
	movs r3, #1
	bl InitBody
	str r5, [r4, #0x2c]
	ldr r0, _08094B78 @ =nop_08094ad8
	str r0, [r4, #0x24]
	ldrb r0, [r5, #0x10]
	cmp r0, #3
	bhi _08094B5E
	ldr r2, _08094B7C @ =0x08369F5A
	lsls r0, r0, #1
	adds r0, r0, r2
	movs r1, #0
	ldrsb r1, [r0, r1]
	lsls r1, r1, #8
	ldr r0, [r5, #0x54]
	adds r0, r0, r1
	str r0, [r5, #0x54]
	ldrb r0, [r5, #0x10]
	lsls r0, r0, #1
	adds r2, #1
	adds r0, r0, r2
	movs r1, #0
	ldrsb r1, [r0, r1]
	lsls r1, r1, #8
	ldr r0, [r5, #0x58]
	adds r0, r0, r1
	str r0, [r5, #0x58]
	movs r0, #0x1e
	strb r0, [r5, #0x12]
_08094B5E:
	adds r0, r5, #0
	bl Enemy63_Update
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_08094B6C: .4byte gEnemyFnTable
_08094B70: .4byte 0x08369F54
_08094B74: .4byte 0x08369EFC
_08094B78: .4byte nop_08094ad8
_08094B7C: .4byte 0x08369F5A
