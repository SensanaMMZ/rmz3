	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080607f0
FUN_080607f0: @ 0x080607F0
	push {r4, r5, lr}
	adds r5, r0, #0
	bl FUN_08060838
	movs r4, #1
	adds r1, r4, #0
	ands r1, r0
	adds r0, r5, #0
	adds r0, #0x4c
	strb r1, [r0]
	adds r0, r5, #0
	bl FUN_08060838
	adds r3, r5, #0
	adds r3, #0x4a
	ands r4, r0
	lsls r2, r4, #4
	ldrb r1, [r3]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	orrs r0, r2
	strb r0, [r3]
	cmp r4, #0
	beq _0806082A
	ldrb r0, [r5, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _08060830
_0806082A:
	ldrb r1, [r5, #0xa]
	movs r0, #0xef
	ands r0, r1
_08060830:
	strb r0, [r5, #0xa]
	pop {r4, r5}
	pop {r0}
	bx r0

	thumb_func_start FUN_08060838
FUN_08060838: @ 0x08060838
	push {lr}
	adds r2, r0, #0
	ldr r3, [r2, #0x54]
	ldr r0, _08060854 @ =pZero2
	ldr r0, [r0]
	ldr r1, [r0, #0x54]
	cmp r3, r1
	beq _08060858
	movs r0, #0
	cmp r3, r1
	bge _08060860
	movs r0, #1
	b _08060860
	.align 2, 0
_08060854: .4byte pZero2
_08060858:
	ldrb r0, [r2, #0xa]
	lsrs r0, r0, #4
	movs r1, #1
	ands r0, r1
_08060860:
	pop {r1}
	bx r1

