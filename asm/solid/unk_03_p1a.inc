	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_080cb3b8
FUN_080cb3b8: @ 0x080CB3B8
	push {r4, r5, r6, lr}
	adds r4, r0, #0
	adds r5, r1, #0
	adds r6, r2, #0
	movs r3, #0
	ldr r0, _080CB49C @ =gSolidHeaderPtr
	ldr r1, [r0]
	movs r2, #0xa
	ldrsh r0, [r1, r2]
	cmp r0, #7
	ble _080CB42E
	adds r0, r1, #0
	bl AllocEntityFirst
	adds r3, r0, #0
	cmp r3, #0
	beq _080CB432
	adds r1, r3, #0
	adds r1, #0x25
	movs r2, #0
	movs r0, #0x1e
	strb r0, [r1]
	ldr r1, _080CB4A0 @ =gSolidFnTable
	movs r0, #3
	strb r0, [r3, #9]
	ldr r0, [r1, #0xc]
	ldr r0, [r0]
	str r0, [r3, #0x14]
	movs r0, #0
	strh r2, [r3, #0x20]
	adds r1, r3, #0
	adds r1, #0x22
	strb r0, [r1]
	ldrb r1, [r3, #0xb]
	movs r0, #0x10
	orrs r0, r1
	strb r0, [r3, #0xb]
	ldrb r0, [r3, #0x1c]
	strb r0, [r3, #0x1d]
	ldr r2, _080CB4A4 @ =0xFFFFF000
	adds r0, r5, #0
	ands r0, r2
	movs r1, #0x80
	lsls r1, r1, #4
	adds r0, r0, r1
	str r0, [r3, #0x54]
	adds r0, r6, #0
	ands r0, r2
	movs r1, #0x80
	lsls r1, r1, #5
	adds r0, r0, r1
	str r0, [r3, #0x58]
	ldrb r0, [r4, #0x10]
	strb r0, [r3, #0x10]
	ldrb r0, [r4, #0x11]
	cmp r0, #0xfe
	bhi _080CB42C
	adds r0, #1
_080CB42C:
	strb r0, [r3, #0x11]
_080CB42E:
	cmp r3, #0
	bne _080CB48C
_080CB432:
	ldr r0, _080CB4A8 @ =gVFXHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	adds r3, r0, #0
	cmp r3, #0
	beq _080CB4B8
	adds r1, r3, #0
	adds r1, #0x25
	movs r2, #0
	movs r0, #1
	strb r0, [r1]
	ldr r1, _080CB4AC @ =gVFXFnTable
	movs r0, #0x1d
	strb r0, [r3, #9]
	ldr r0, [r1, #0x74]
	ldr r0, [r0]
	str r0, [r3, #0x14]
	movs r0, #0
	strh r2, [r3, #0x20]
	adds r1, r3, #0
	adds r1, #0x22
	strb r0, [r1]
	ldr r2, _080CB4A4 @ =0xFFFFF000
	adds r0, r5, #0
	ands r0, r2
	movs r1, #0x80
	lsls r1, r1, #4
	adds r0, r0, r1
	str r0, [r3, #0x54]
	adds r0, r6, #0
	ands r0, r2
	movs r2, #0x80
	lsls r2, r2, #5
	adds r0, r0, r2
	str r0, [r3, #0x58]
	ldrb r0, [r4, #0x10]
	strb r0, [r3, #0x10]
	ldrb r0, [r4, #0x11]
	cmp r0, #0xfe
	bhi _080CB486
	adds r0, #1
_080CB486:
	strb r0, [r3, #0x11]
	cmp r3, #0
	beq _080CB4B8
_080CB48C:
	ldrb r0, [r4, #0x10]
	cmp r0, #0
	bne _080CB4B0
	adds r0, r5, #0
	adds r1, r6, #0
	bl FUN_0800e2c4
	b _080CB4B8
	.align 2, 0
_080CB49C: .4byte gSolidHeaderPtr
_080CB4A0: .4byte gSolidFnTable
_080CB4A4: .4byte 0xFFFFF000
_080CB4A8: .4byte gVFXHeaderPtr
_080CB4AC: .4byte gVFXFnTable
_080CB4B0:
	adds r0, r5, #0
	adds r1, r6, #0
	bl FUN_08010d20
_080CB4B8:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
