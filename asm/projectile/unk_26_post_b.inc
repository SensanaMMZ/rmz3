	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080a8ff0
FUN_080a8ff0: @ 0x080A8FF0
	push {lr}
	adds r2, r0, #0
	ldrb r0, [r2, #0x12]
	adds r0, #1
	movs r1, #0
	strb r0, [r2, #0x12]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0x24
	bne _080A901A
	adds r0, r2, #0
	adds r0, #0x8c
	str r1, [r0]
	adds r0, #4
	str r1, [r0]
	adds r0, #4
	strb r1, [r0]
	ldrb r1, [r2, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r2, #0xa]
_080A901A:
	adds r0, r2, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #4
	bne _080A903E
	ldrb r1, [r2, #0xa]
	movs r0, #0xfe
	ands r0, r1
	strb r0, [r2, #0xa]
	ldr r1, _080A9044 @ =gProjectileFnTable
	ldrb r0, [r2, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r2, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r2, #0x14]
_080A903E:
	pop {r0}
	bx r0
	.align 2, 0
_080A9044: .4byte gProjectileFnTable


