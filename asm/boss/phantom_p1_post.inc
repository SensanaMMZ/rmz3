	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_0805f794
FUN_0805f794: @ 0x0805F794
	push {r4, lr}
	adds r4, r0, #0
	bl FUN_080608e0
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _0805F7CA
	movs r2, #0
	movs r0, #2
	strb r0, [r4, #0xf]
	adds r3, r4, #0
	adds r3, #0xb7
	ldrb r1, [r3]
	adds r0, r1, #1
	lsls r0, r0, #6
	rsbs r0, r0, #0
	str r0, [r4, #0x60]
	adds r1, #8
	strb r1, [r3]
	adds r1, r4, #0
	adds r1, #0xb8
	ldr r0, [r4, #0x54]
	str r0, [r1]
	strb r2, [r4, #0x12]
	adds r0, r4, #0
	bl FUN_0805f7d0
_0805F7CA:
	pop {r4}
	pop {r0}
	bx r0

	thumb_func_start FUN_0805f7d0
FUN_0805f7d0: @ 0x0805F7D0
	push {r4, r5, lr}
	adds r5, r0, #0
	ldrb r1, [r5, #0x12]
	adds r1, #1
	strb r1, [r5, #0x12]
	adds r0, #0xbc
	adds r2, r5, #0
	adds r2, #0xb8
	ldr r0, [r0]
	ldr r4, [r2]
	subs r0, r0, r4
	muls r0, r1, r0
	adds r1, r5, #0
	adds r1, #0xb7
	ldrb r1, [r1]
	bl __divsi3
	adds r4, r4, r0
	str r4, [r5, #0x54]
	adds r0, r5, #0
	bl FUN_08060924
	ldr r0, [r5, #0x60]
	cmp r0, #0
	ble _0805F818
	ldr r0, [r5, #0x2c]
	ldr r0, [r0, #0x58]
	subs r0, #0x80
	ldr r1, [r5, #0x58]
	cmp r1, r0
	blt _0805F818
	movs r0, #4
	strh r0, [r5, #0xe]
	adds r0, r5, #0
	bl FUN_0805f820
_0805F818:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start FUN_0805f820
FUN_0805f820: @ 0x0805F820
	push {lr}
	ldr r2, _0805F834 @ =0x083654C4
	ldrb r1, [r0, #0xf]
	lsls r1, r1, #2
	adds r1, r1, r2
	ldr r1, [r1]
	bl _call_via_r1
	pop {r0}
	bx r0
	.align 2, 0
_0805F834: .4byte 0x083654C4

	thumb_func_start FUN_0805f838
FUN_0805f838: @ 0x0805F838
	push {r4, lr}
	adds r4, r0, #0
	adds r0, #0x74
	ldr r1, _0805F858 @ =0x083653E0
	bl SetDDP
	movs r0, #1
	strb r0, [r4, #0xf]
	adds r0, r4, #0
	movs r1, #9
	bl FUN_080607a0
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_0805F858: .4byte 0x083653E0

	thumb_func_start FUN_0805f85c
FUN_0805f85c: @ 0x0805F85C
	push {lr}
	adds r1, r0, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _0805F86C
	movs r0, #2
	strb r0, [r1, #0xf]
_0805F86C:
	pop {r0}
	bx r0

	thumb_func_start FUN_0805f870
FUN_0805f870: @ 0x0805F870
	push {r4, r5, lr}
	adds r5, r0, #0
	ldr r1, _0805F89C @ =gStageRun+232
	ldr r0, [r5, #0x58]
	movs r2, #0xa0
	lsls r2, r2, #7
	adds r0, r0, r2
	ldr r1, [r1, #0x3c]
	subs r1, r1, r0
	ldr r0, _0805F8A0 @ =0xFFFFD000
	cmp r1, r0
	bge _0805F8A4
	movs r4, #0
	movs r0, #3
	strb r0, [r5, #0xf]
	adds r0, r5, #0
	movs r1, #0xa
	bl FUN_080607a0
	strb r4, [r5, #0x12]
	b _0805F8B8
	.align 2, 0
_0805F89C: .4byte gStageRun+232
_0805F8A0: .4byte 0xFFFFD000
_0805F8A4:
	ldr r0, _0805F8C0 @ =0xFFFFE000
	cmp r1, r0
	ble _0805F8B8
	movs r0, #5
	strh r0, [r5, #0xe]
	movs r0, #0
	str r0, [r5, #0x2c]
	adds r0, r5, #0
	bl FUN_0805f934
_0805F8B8:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_0805F8C0: .4byte 0xFFFFE000

	thumb_func_start FUN_0805f8c4
FUN_0805f8c4: @ 0x0805F8C4
	push {r4, r5, lr}
	sub sp, #8
	adds r5, r0, #0
	ldrb r0, [r5, #0x12]
	adds r0, #1
	strb r0, [r5, #0x12]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0xf
	bne _0805F91A
	ldr r0, [r5, #0x54]
	str r0, [sp]
	ldr r0, [r5, #0x58]
	str r0, [sp, #4]
	movs r0, #0xfc
	bl PlaySound
	movs r4, #0xf0
	lsls r4, r4, #2
	mov r0, sp
	adds r1, r4, #0
	movs r2, #0x10
	movs r3, #1
	bl FUN_080afbfc
	mov r0, sp
	adds r1, r4, #0
	movs r2, #0x30
	movs r3, #1
	bl FUN_080afbfc
	mov r0, sp
	adds r1, r4, #0
	movs r2, #0x50
	movs r3, #1
	bl FUN_080afbfc
	mov r0, sp
	adds r1, r4, #0
	movs r2, #0x70
	movs r3, #1
	bl FUN_080afbfc
_0805F91A:
	adds r0, r5, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _0805F928
	movs r0, #2
	strb r0, [r5, #0xf]
_0805F928:
	add sp, #8
	pop {r4, r5}
	pop {r0}
	bx r0

