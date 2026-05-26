	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_08083e18
FUN_08083e18: @ 0x08083E18
	push {lr}
	adds r2, r0, #0
	ldrb r3, [r2, #0xe]
	cmp r3, #0
	beq _08083E28
	cmp r3, #1
	beq _08083E48
	b _08083E64
_08083E28:
	adds r0, r2, #0
	adds r0, #0x8c
	str r3, [r0]
	adds r0, #4
	str r3, [r0]
	adds r0, #4
	strb r3, [r0]
	ldrb r1, [r2, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r2, #0xa]
	str r3, [r2, #0x5c]
	str r3, [r2, #0x60]
	ldrb r0, [r2, #0xe]
	adds r0, #1
	strb r0, [r2, #0xe]
_08083E48:
	ldr r0, [r2, #0x60]
	adds r0, #0x40
	str r0, [r2, #0x60]
	cmp r0, #0x40
	ble _08083E56
	movs r0, #0x40
	str r0, [r2, #0x60]
_08083E56:
	ldr r0, [r2, #0x58]
	ldr r1, [r2, #0x60]
	adds r0, r0, r1
	str r0, [r2, #0x58]
	adds r0, r2, #0
	bl UpdateMotionGraphic
_08083E64:
	pop {r0}
	bx r0

	thumb_func_start FUN_08083e68
FUN_08083e68: @ 0x08083E68
	push {lr}
	adds r2, r0, #0
	ldrb r3, [r2, #0xe]
	cmp r3, #0
	beq _08083E78
	cmp r3, #1
	beq _08083EA2
	b _08083EA8
_08083E78:
	ldrb r1, [r2, #0xa]
	movs r0, #0xef
	ands r0, r1
	strb r0, [r2, #0xa]
	adds r0, r2, #0
	adds r0, #0x4c
	strb r3, [r0]
	movs r0, #0x4a
	adds r0, r0, r2
	mov ip, r0
	ldrb r1, [r0]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	mov r1, ip
	strb r0, [r1]
	str r3, [r2, #0x60]
	str r3, [r2, #0x5c]
	ldrb r0, [r2, #0xe]
	adds r0, #1
	strb r0, [r2, #0xe]
_08083EA2:
	adds r0, r2, #0
	bl UpdateMotionGraphic
_08083EA8:
	pop {r0}
	bx r0

	thumb_func_start nop_08083eac
nop_08083eac: @ 0x08083EAC
	bx lr
	.align 2, 0

	thumb_func_start FUN_08083eb0
FUN_08083eb0: @ 0x08083EB0
	adds r3, r0, #0
	adds r3, #0xc1
	movs r2, #0
	movs r1, #1
	strb r1, [r3]
	movs r1, #4
	strb r1, [r0, #0xd]
	strb r2, [r0, #0xe]
	movs r0, #1
	bx lr

	thumb_func_start FUN_08083ec4
FUN_08083ec4: @ 0x08083EC4
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r5, [r4, #0xe]
	cmp r5, #0
	beq _08083ED4
	cmp r5, #1
	beq _08083F0C
	b _08083F40
_08083ED4:
	movs r1, #0x90
	lsls r1, r1, #4
	adds r0, r4, #0
	bl SetMotion
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	adds r0, #0x4c
	strb r5, [r0]
	adds r2, r4, #0
	adds r2, #0x4a
	ldrb r1, [r2]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r2]
	str r5, [r4, #0x60]
	str r5, [r4, #0x5c]
	strb r5, [r4, #0x12]
	adds r0, r4, #0
	adds r0, #0xc1
	strb r5, [r0]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08083F0C:
	ldrb r0, [r4, #0x12]
	adds r0, #2
	strb r0, [r4, #0x12]
	ldr r1, _08083F48 @ =gSineTable
	ldrb r0, [r4, #0x12]
	lsls r0, r0, #1
	adds r0, r0, r1
	movs r1, #0
	ldrsh r3, [r0, r1]
	adds r0, r4, #0
	adds r0, #0xb8
	ldr r2, [r4, #0x28]
	ldr r0, [r0]
	ldr r1, [r2, #0x58]
	adds r0, r0, r1
	adds r0, r0, r3
	str r0, [r4, #0x58]
	adds r0, r4, #0
	adds r0, #0xb4
	ldr r0, [r0]
	ldr r1, [r2, #0x54]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	adds r0, r4, #0
	bl UpdateMotionGraphic
_08083F40:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_08083F48: .4byte gSineTable

	thumb_func_start FUN_08083f4c
FUN_08083f4c: @ 0x08083F4C
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r5, [r4, #0xe]
	cmp r5, #0
	beq _08083F5C
	cmp r5, #1
	beq _08083FAA
	b _08083FE0
_08083F5C:
	ldr r1, _08083FE8 @ =0x00000901
	adds r0, r4, #0
	bl SetMotion
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	adds r0, #0x4c
	strb r5, [r0]
	adds r2, r4, #0
	adds r2, #0x4a
	ldrb r1, [r2]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r2]
	ldrb r1, [r4, #0xa]
	movs r0, #0xdf
	ands r0, r1
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	adds r0, #0x4d
	strb r5, [r0]
	ldrb r1, [r2]
	movs r0, #0x21
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r2]
	str r5, [r4, #0x60]
	str r5, [r4, #0x5c]
	strb r5, [r4, #0x12]
	adds r0, r4, #0
	adds r0, #0xc1
	strb r5, [r0]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08083FAA:
	ldrb r0, [r4, #0x12]
	adds r0, #2
	strb r0, [r4, #0x12]
	ldr r1, _08083FEC @ =gSineTable
	ldrb r0, [r4, #0x12]
	lsls r0, r0, #1
	adds r0, r0, r1
	movs r1, #0
	ldrsh r2, [r0, r1]
	lsls r2, r2, #1
	adds r0, r4, #0
	adds r0, #0xb8
	ldr r3, [r4, #0x28]
	ldr r0, [r0]
	ldr r1, [r3, #0x58]
	adds r0, r0, r1
	adds r0, r0, r2
	str r0, [r4, #0x58]
	adds r0, r4, #0
	adds r0, #0xb4
	ldr r0, [r0]
	ldr r1, [r3, #0x54]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	adds r0, r4, #0
	bl UpdateMotionGraphic
_08083FE0:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_08083FE8: .4byte 0x00000901
_08083FEC: .4byte gSineTable
