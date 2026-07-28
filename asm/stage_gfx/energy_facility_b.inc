	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_08012988
FUN_08012988: @ 0x08012988
	push {r4, r5, r6, r7, lr}
	sub sp, #4
	adds r6, r0, #0
	ldrb r0, [r6, #0xe]
	cmp r0, #0
	bne _080129B6
	movs r3, #0
	movs r2, #0
_08012998:
	lsls r1, r3, #0x10
	asrs r1, r1, #0x10
	lsls r0, r1, #2
	adds r0, r0, r6
	str r2, [r0, #0x68]
	adds r1, #1
	lsls r1, r1, #0x10
	lsrs r3, r1, #0x10
	asrs r1, r1, #0x10
	cmp r1, #3
	ble _08012998
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
	b _080129F2
_080129B6:
	movs r3, #0
	movs r7, #1
_080129BA:
	lsls r2, r3, #0x10
	asrs r4, r2, #0x10
	lsls r0, r4, #2
	adds r5, r0, r6
	ldr r0, [r5, #0x68]
	cmp r0, #0
	bne _080129E6
	lsls r1, r4, #1
	adds r1, r1, r4
	adds r1, #0x13
	lsls r1, r1, #4
	adds r1, #8
	lsls r1, r1, #8
	asrs r2, r2, #0x11
	lsls r2, r2, #0x18
	lsrs r2, r2, #0x18
	ands r3, r7
	str r7, [sp]
	ldr r0, _080129FC @ =0x00272000
	bl CreateStructuralSteel
	str r0, [r5, #0x68]
_080129E6:
	adds r0, r4, #1
	lsls r0, r0, #0x10
	lsrs r3, r0, #0x10
	asrs r0, r0, #0x10
	cmp r0, #3
	ble _080129BA
_080129F2:
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080129FC: .4byte 0x00272000

