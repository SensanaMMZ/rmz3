	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start VFX41_Init
VFX41_Init: @ 0x080BDF00
	push {r4, r5, lr}
	adds r4, r0, #0
	bl InitNonAffineMotion
	ldrb r0, [r4, #0xa]
	movs r1, #1
	movs r5, #0
	orrs r1, r0
	movs r0, #2
	orrs r1, r0
	strb r1, [r4, #0xa]
	adds r0, r4, #0
	bl ResetDynamicMotion
	ldrb r2, [r4, #0x10]
	cmp r2, #0
	bne _080BDF42
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	adds r0, #0x4c
	strb r2, [r0]
	adds r2, r4, #0
	adds r2, #0x4a
	ldrb r1, [r2]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r2]
	movs r0, #0x80
	b _080BDF68
_080BDF42:
	movs r2, #1
	ldrb r0, [r4, #0xa]
	movs r1, #0x10
	orrs r0, r1
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	adds r0, #0x4c
	strb r2, [r0]
	adds r3, r4, #0
	adds r3, #0x4a
	movs r2, #0x10
	ldrb r1, [r3]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	orrs r0, r2
	strb r0, [r3]
	movs r0, #0x80
	rsbs r0, r0, #0
_080BDF68:
	str r0, [r4, #0x5c]
	movs r3, #0
	str r3, [r4, #0x60]
	ldrb r2, [r4, #0x11]
	cmp r2, #0
	bne _080BDF94
	movs r0, #0xff
	strb r0, [r4, #0x12]
	ldr r1, _080BDF90 @ =gVFXFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r4, #0x14]
	strb r1, [r4, #0xd]
	b _080BDFD4
	.align 2, 0
_080BDF90: .4byte gVFXFnTable
_080BDF94:
	cmp r2, #1
	bne _080BDFB4
	movs r0, #0xff
	strb r0, [r4, #0x12]
	ldr r1, _080BDFB0 @ =gVFXFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	str r2, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r4, #0x14]
	strb r3, [r4, #0xd]
	b _080BDFD4
	.align 2, 0
_080BDFB0: .4byte gVFXFnTable
_080BDFB4:
	cmp r2, #2
	beq _080BDFBC
	cmp r2, #3
	bne _080BDFD8
_080BDFBC:
	movs r0, #0xff
	strb r0, [r4, #0x12]
	ldr r1, _080BDFE4 @ =gVFXFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r4, #0x14]
	strb r2, [r4, #0xd]
_080BDFD4:
	strb r3, [r4, #0xe]
	strb r3, [r4, #0xf]
_080BDFD8:
	adds r0, r4, #0
	bl VFX41_Update
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080BDFE4: .4byte gVFXFnTable
