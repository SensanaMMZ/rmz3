	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_0807aae8
FUN_0807aae8: @ 0x0807AAE8
	push {r4, r5, lr}
	adds r2, r0, #0
	ldr r0, [r2, #0xc]
	ldr r5, [r0, #0x2c]
	ldr r3, [r2, #0x2c]
	ldr r0, [r2, #0x14]
	movs r1, #1
	ands r0, r1
	cmp r0, #0
	beq _0807AB10
	movs r4, #0
	ldr r0, [r5, #0x54]
	ldr r1, [r3, #0x54]
	subs r0, r0, r1
	cmp r0, #0
	ble _0807AB0A
	movs r4, #1
_0807AB0A:
	adds r0, r3, #0
	adds r0, #0xb4
	strb r4, [r0]
_0807AB10:
	ldr r0, [r2, #0x14]
	movs r1, #4
	ands r0, r1
	cmp r0, #0
	beq _0807AB2A
	adds r0, r5, #0
	adds r0, #0xa4
	movs r1, #0
	ldrsh r0, [r0, r1]
	cmp r0, #0
	bne _0807AB2A
	movs r0, #0xff
	strb r0, [r3, #0x12]
_0807AB2A:
	pop {r4, r5}
	pop {r0}
	bx r0
