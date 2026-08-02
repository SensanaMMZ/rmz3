	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_080c6a1c
FUN_080c6a1c: @ 0x080C6A1C
	push {r4, r5, r6, r7, lr}
	mov r7, r8
	push {r7}
	adds r5, r0, #0
	ldr r6, [r5, #0x28]
	movs r0, #0x54
	adds r0, r0, r6
	mov r8, r0
	ldrb r4, [r6, #0xa]
	lsrs r4, r4, #4
	movs r0, #1
	ands r4, r0
	ldrb r1, [r5, #0xa]
	movs r7, #0
	orrs r0, r1
	strb r0, [r5, #0xa]
	adds r0, r5, #0
	bl InitNonAffineMotion
	ldr r1, _080C6A58 @ =0x0000DB0A
	adds r0, r5, #0
	bl SetMotion
	cmp r4, #0
	beq _080C6A5C
	ldrb r0, [r5, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _080C6A62
	.align 2, 0
_080C6A58: .4byte 0x0000DB0A
_080C6A5C:
	ldrb r1, [r5, #0xa]
	movs r0, #0xef
	ands r0, r1
_080C6A62:
	strb r0, [r5, #0xa]
	movs r7, #1
	adds r1, r7, #0
	ands r1, r4
	adds r0, r5, #0
	adds r0, #0x4c
	strb r1, [r0]
	adds r3, r5, #0
	adds r3, #0x4a
	lsls r1, r1, #4
	ldrb r2, [r3]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r1
	strb r0, [r3]
	mov r1, r8
	ldr r0, [r1]
	str r0, [r5, #0x54]
	ldr r0, [r1, #4]
	str r0, [r5, #0x58]
	ldr r1, [r6, #0x5c]
	lsls r0, r1, #2
	adds r0, r0, r1
	lsls r0, r0, #5
	cmp r0, #0
	bge _080C6A9A
	adds r0, #0xff
_080C6A9A:
	asrs r0, r0, #8
	str r0, [r5, #0x5c]
	ldr r0, [r6, #0x60]
	str r0, [r5, #0x60]
	movs r1, #0
	ldrb r0, [r6, #0xf]
	cmp r0, #1
	bne _080C6AAC
	movs r1, #1
_080C6AAC:
	strb r1, [r5, #0x13]
	movs r0, #0x16
	strb r0, [r5, #0x12]
	ldr r1, _080C6AD4 @ =gVFXFnTable
	ldrb r0, [r5, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	str r7, [r5, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r5, #0x14]
	adds r0, r5, #0
	bl Ghost72_Update
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080C6AD4: .4byte gVFXFnTable
