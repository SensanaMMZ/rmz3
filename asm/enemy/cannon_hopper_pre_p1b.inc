	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_08097428
FUN_08097428: @ 0x08097428
	push {r4, r5, lr}
	sub sp, #4
	adds r5, r0, #0
	mov r2, sp
	mov r1, sp
	movs r0, #0
	strb r0, [r1, #1]
	strb r0, [r2]
	ldr r0, [r5, #0x54]
	ldr r1, _08097454 @ =0xFFFFF900
	adds r2, r0, r1
	ldr r4, [r5, #0x58]
	ldrb r1, [r5, #0xa]
	movs r0, #0x20
	ands r0, r1
	cmp r0, #0
	beq _08097458
	movs r0, #0xb8
	lsls r0, r0, #6
	adds r4, r4, r0
	b _0809745C
	.align 2, 0
_08097454: .4byte 0xFFFFF900
_08097458:
	ldr r1, _080974B8 @ =0xFFFFD200
	adds r4, r4, r1
_0809745C:
	adds r0, r2, #0
	adds r1, r4, #0
	bl PushoutToDown1
	cmp r0, #0
	ble _0809746E
	mov r1, sp
	movs r0, #1
	strb r0, [r1]
_0809746E:
	ldr r2, [r5, #0x54]
	adds r0, r2, #0
	adds r1, r4, #0
	bl PushoutToDown1
	cmp r0, #0
	ble _08097482
	mov r1, sp
	movs r0, #1
	strb r0, [r1]
_08097482:
	ldr r0, [r5, #0x54]
	movs r1, #0xe0
	lsls r1, r1, #3
	adds r2, r0, r1
	adds r0, r2, #0
	adds r1, r4, #0
	bl PushoutToDown1
	cmp r0, #0
	ble _0809749C
	mov r1, sp
	movs r0, #1
	strb r0, [r1]
_0809749C:
	ldr r0, [r5, #0x54]
	ldr r1, _080974BC @ =0xFFFFF900
	adds r2, r0, r1
	ldr r4, [r5, #0x58]
	ldrb r1, [r5, #0xa]
	movs r0, #0x20
	ands r0, r1
	cmp r0, #0
	beq _080974C0
	movs r0, #0x80
	lsls r0, r0, #1
	adds r4, r4, r0
	b _080974C4
	.align 2, 0
_080974B8: .4byte 0xFFFFD200
_080974BC: .4byte 0xFFFFF900
_080974C0:
	ldr r1, _08097518 @ =0xFFFFFF00
	adds r4, r4, r1
_080974C4:
	adds r0, r2, #0
	adds r1, r4, #0
	bl PushoutToUp1
	cmp r0, #0
	bge _080974D6
	mov r1, sp
	movs r0, #1
	strb r0, [r1, #1]
_080974D6:
	ldr r2, [r5, #0x54]
	adds r0, r2, #0
	adds r1, r4, #0
	bl PushoutToUp1
	cmp r0, #0
	bge _080974EA
	mov r1, sp
	movs r0, #1
	strb r0, [r1, #1]
_080974EA:
	ldr r0, [r5, #0x54]
	movs r1, #0xe0
	lsls r1, r1, #3
	adds r2, r0, r1
	adds r0, r2, #0
	adds r1, r4, #0
	bl PushoutToUp1
	cmp r0, #0
	bge _08097504
	mov r1, sp
	movs r0, #1
	strb r0, [r1, #1]
_08097504:
	mov r0, sp
	mov r1, sp
	ldrb r0, [r0]
	ldrb r1, [r1, #1]
	ands r0, r1
	add sp, #4
	pop {r4, r5}
	pop {r1}
	bx r1
	.align 2, 0
_08097518: .4byte 0xFFFFFF00
