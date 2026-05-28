	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start Ghost68_Die
Ghost68_Die: @ 0x080C4D0C
	ldrb r2, [r0, #0xa]
	movs r1, #0xfe
	ands r1, r2
	movs r2, #0xfd
	ands r1, r2
	strb r1, [r0, #0xa]
	ldr r2, _080C4D2C @ =gVFXFnTable
	ldrb r1, [r0, #9]
	lsls r1, r1, #2
	adds r1, r1, r2
	movs r2, #3
	str r2, [r0, #0xc]
	ldr r1, [r1]
	ldr r1, [r1, #0xc]
	str r1, [r0, #0x14]
	bx lr
	.align 2, 0
_080C4D2C: .4byte gVFXFnTable

	thumb_func_start FUN_080c4d30
FUN_080c4d30: @ 0x080C4D30
	push {r4, lr}
	adds r4, r0, #0
	ldrb r1, [r4, #0xa]
	movs r0, #1
	orrs r0, r1
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	bl InitNonAffineMotion
	ldr r1, _080C4D5C @ =gVFXFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r4, #0x14]
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080C4D5C: .4byte gVFXFnTable

	thumb_func_start FUN_080c4d60
FUN_080c4d60: @ 0x080C4D60
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xd]
	cmp r0, #0
	beq _080C4D70
	cmp r0, #1
	beq _080C4D80
	b _080C4DAC
_080C4D70:
	movs r1, #0x87
	lsls r1, r1, #8
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xd]
	adds r0, #1
	strb r0, [r4, #0xd]
_080C4D80:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r2, [r0]
	cmp r2, #3
	bne _080C4DAC
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r4, #0xa]
	ldr r1, _080C4DB4 @ =gVFXFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	str r2, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r4, #0x14]
_080C4DAC:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080C4DB4: .4byte gVFXFnTable

	thumb_func_start FUN_080c4db8
FUN_080c4db8: @ 0x080C4DB8
	push {r4, lr}
	adds r4, r0, #0
	ldrb r1, [r4, #0xa]
	movs r0, #1
	orrs r0, r1
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	bl InitNonAffineMotion
	ldr r1, _080C4DE4 @ =gVFXFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r4, #0x14]
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080C4DE4: .4byte gVFXFnTable

	thumb_func_start FUN_080c4de8
FUN_080c4de8: @ 0x080C4DE8
	push {r4, r5, lr}
	adds r4, r0, #0
	ldr r5, [r4, #0x2c]
	ldrb r0, [r4, #0xd]
	cmp r0, #0
	beq _080C4DFA
	cmp r0, #1
	beq _080C4E08
	b _080C4E4A
_080C4DFA:
	ldr r1, _080C4E50 @ =0x00008701
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xd]
	adds r0, #1
	strb r0, [r4, #0xd]
_080C4E08:
	ldr r2, [r4, #0x54]
	ldr r0, [r4, #0x5c]
	adds r2, r2, r0
	str r2, [r4, #0x54]
	ldr r0, [r4, #0x58]
	ldr r1, [r4, #0x60]
	adds r0, r0, r1
	str r0, [r4, #0x58]
	str r2, [r5, #0x54]
	ldr r0, [r4, #0x58]
	str r0, [r5, #0x58]
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r2, [r0]
	cmp r2, #3
	bne _080C4E4A
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r4, #0xa]
	ldr r1, _080C4E54 @ =gVFXFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	str r2, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r4, #0x14]
_080C4E4A:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080C4E50: .4byte 0x00008701
_080C4E54: .4byte gVFXFnTable


