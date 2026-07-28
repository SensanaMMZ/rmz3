	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_080c143c
FUN_080c143c: @ 0x080C143C
	push {r4, r5, lr}
	adds r4, r0, #0
	ldr r5, [r4, #0x28]
	bl UpdateMotionGraphic
	movs r0, #0x61
	bl StepPaletteAnimation
	ldrb r0, [r5, #0xa]
	lsrs r2, r0, #4
	movs r0, #1
	ands r2, r0
	cmp r2, #0
	beq _080C1460
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	orrs r0, r1
	b _080C1466
_080C1460:
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
_080C1466:
	strb r0, [r4, #0xa]
	movs r3, #1
	adds r1, r3, #0
	ands r1, r2
	adds r0, r4, #0
	adds r0, #0x4c
	strb r1, [r0]
	movs r0, #0x4a
	adds r0, r0, r4
	mov ip, r0
	lsls r1, r1, #4
	ldrb r2, [r0]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r1
	mov r1, ip
	strb r0, [r1]
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x58]
	str r0, [r4, #0x54]
	str r1, [r4, #0x58]
	ldrb r0, [r4, #0x12]
	adds r0, #1
	strb r0, [r4, #0x12]
	ands r0, r3
	cmp r0, #0
	beq _080C14A6
	ldrb r0, [r4, #0xa]
	movs r1, #1
	orrs r0, r1
	b _080C14AC
_080C14A6:
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
_080C14AC:
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	beq _080C14CA
	ldrb r0, [r5, #0x1e]
	lsls r0, r0, #8
	adds r1, r5, #0
	adds r1, #0x70
	ldrb r1, [r1]
	orrs r0, r1
	ldr r1, _080C14F0 @ =0x0000B31C
	cmp r0, r1
	beq _080C14E8
_080C14CA:
	movs r0, #0x61
	bl RemovePaletteAnimation
	ldr r1, _080C14F4 @ =gVFXFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r4, #0x14]
	adds r0, r4, #0
	bl VFX55_Die
_080C14E8:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080C14F0: .4byte 0x0000B31C
_080C14F4: .4byte gVFXFnTable
