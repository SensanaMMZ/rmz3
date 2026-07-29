	.include "asm/macros.inc"

	.syntax unified

	.text


	thumb_func_start FUN_080c53b8
FUN_080c53b8: @ 0x080C53B8
	push {r4, r5, r6, r7, lr}
	adds r5, r0, #0
	ldr r0, [r5, #0x28]
	ldrb r0, [r0, #0xc]
	cmp r0, #1
	bls _080C53DC
	ldr r1, _080C53D8 @ =gVFXFnTable
	ldrb r0, [r5, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r5, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r5, #0x14]
	b _080C5516
	.align 2, 0
_080C53D8: .4byte gVFXFnTable
_080C53DC:
	ldrb r0, [r5, #0xe]
	cmp r0, #0
	beq _080C53E8
	cmp r0, #1
	beq _080C5454
	b _080C5516
_080C53E8:
	adds r0, r5, #0
	bl InitScalerotMotion1
	adds r0, r5, #0
	adds r0, #0x50
	movs r1, #0
	movs r4, #0x80
	lsls r4, r4, #1
	strh r4, [r0]
	adds r0, #2
	strh r4, [r0]
	subs r0, #0x2e
	strb r1, [r0]
	adds r0, r5, #0
	bl ResetDynamicMotion
	ldrb r0, [r5, #0xa]
	movs r1, #2
	orrs r0, r1
	movs r1, #1
	orrs r0, r1
	strb r0, [r5, #0xa]
	ldr r1, _080C551C @ =0x0000B801
	adds r0, r5, #0
	bl SetMotion
	movs r0, #0x10
	strb r0, [r5, #0x12]
	str r4, [r5, #0x5c]
	ldr r1, _080C5520 @ =0xFFFFCA00
	str r1, [r5, #0x68]
	ldr r2, [r5, #0x28]
	ldr r0, [r2, #0x54]
	adds r0, r0, r1
	str r0, [r5, #0x64]
	ldr r1, [r5, #0x74]
	adds r0, r0, r1
	str r0, [r5, #0x54]
	ldr r1, [r5, #0x78]
	movs r0, #0xe0
	lsls r0, r0, #3
	adds r1, r1, r0
	ldr r0, [r2, #0x58]
	adds r0, r0, r1
	str r0, [r5, #0x58]
	ldrb r1, [r5, #0x11]
	movs r0, #0x2a
	muls r0, r1, r0
	movs r1, #0xff
	ands r0, r1
	str r0, [r5, #0x60]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_080C5454:
	ldr r1, [r5, #0x68]
	movs r0, #0xe0
	lsls r0, r0, #4
	subs r0, r0, r1
	lsls r0, r0, #5
	asrs r0, r0, #8
	adds r1, r1, r0
	str r1, [r5, #0x68]
	ldr r2, [r5, #0x28]
	mov ip, r2
	ldr r0, [r2, #0x54]
	adds r1, r1, r0
	str r1, [r5, #0x64]
	ldr r2, [r5, #0x78]
	rsbs r1, r2, #0
	lsls r0, r1, #2
	adds r0, r0, r1
	lsls r0, r0, #2
	asrs r0, r0, #8
	adds r2, r2, r0
	str r2, [r5, #0x78]
	ldr r1, [r5, #0x60]
	adds r0, r1, #0
	adds r0, #0xa
	str r0, [r5, #0x60]
	cmp r0, #0xff
	ble _080C548E
	subs r0, #0xff
	str r0, [r5, #0x60]
_080C548E:
	ldr r2, [r5, #0x78]
	adds r7, r2, #0
	ldr r3, _080C5524 @ =gSineTable
	ldr r1, [r5, #0x60]
	lsls r0, r1, #0x18
	lsrs r0, r0, #0x17
	adds r0, r0, r3
	movs r4, #0
	ldrsh r0, [r0, r4]
	muls r0, r2, r0
	asrs r0, r0, #8
	adds r6, r0, #0
	adds r1, #0x40
	lsls r1, r1, #0x18
	lsrs r1, r1, #0x17
	adds r1, r1, r3
	movs r3, #0
	ldrsh r1, [r1, r3]
	muls r1, r2, r1
	asrs r7, r1, #8
	lsls r0, r0, #3
	subs r0, r0, r6
	lsls r0, r0, #4
	asrs r6, r0, #8
	ldr r0, [r5, #0x64]
	adds r0, r0, r6
	str r0, [r5, #0x54]
	movs r4, #0xe0
	lsls r4, r4, #3
	adds r1, r7, r4
	mov r2, ip
	ldr r0, [r2, #0x58]
	adds r0, r0, r1
	str r0, [r5, #0x58]
	ldr r1, [r5, #0x5c]
	movs r0, #0x20
	subs r0, r0, r1
	lsls r0, r0, #4
	asrs r0, r0, #8
	adds r1, r1, r0
	str r1, [r5, #0x5c]
	adds r0, r5, #0
	adds r0, #0x50
	strh r1, [r0]
	ldr r0, [r5, #0x5c]
	adds r1, r5, #0
	adds r1, #0x52
	strh r0, [r1]
	ldrb r0, [r5, #0x12]
	cmp r0, #0
	beq _080C54FE
	subs r0, #1
	strb r0, [r5, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080C5510
_080C54FE:
	ldr r1, _080C5528 @ =gVFXFnTable
	ldrb r0, [r5, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r5, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r5, #0x14]
_080C5510:
	adds r0, r5, #0
	bl UpdateMotionGraphic
_080C5516:
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080C551C: .4byte 0x0000B801
_080C5520: .4byte 0xFFFFCA00
_080C5524: .4byte gSineTable
_080C5528: .4byte gVFXFnTable
