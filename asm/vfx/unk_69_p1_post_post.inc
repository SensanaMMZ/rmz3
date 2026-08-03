	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080c521c
FUN_080c521c: @ 0x080C521C
	push {r4, r5, r6, r7, lr}
	adds r5, r0, #0
	ldr r0, [r5, #0x28]
	ldrb r0, [r0, #0xc]
	cmp r0, #1
	bls _080C5240
	ldr r1, _080C523C @ =gVFXFnTable
	ldrb r0, [r5, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r5, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r5, #0x14]
	b _080C5318
	.align 2, 0
_080C523C: .4byte gVFXFnTable
_080C5240:
	ldrb r0, [r5, #0xe]
	cmp r0, #0
	beq _080C524C
	cmp r0, #1
	beq _080C52AA
	b _080C5318
_080C524C:
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
	ldr r1, _080C5320 @ =0x0000B801
	adds r0, r5, #0
	bl SetMotion
	movs r0, #0x10
	strb r0, [r5, #0x12]
	str r4, [r5, #0x5c]
	ldr r2, [r5, #0x28]
	ldr r1, [r5, #0x64]
	movs r0, #0xe0
	lsls r0, r0, #4
	adds r1, r1, r0
	ldr r0, [r2, #0x54]
	adds r0, r0, r1
	str r0, [r5, #0x54]
	ldr r1, [r5, #0x68]
	movs r0, #0xe0
	lsls r0, r0, #3
	adds r1, r1, r0
	ldr r0, [r2, #0x58]
	adds r0, r0, r1
	str r0, [r5, #0x58]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_080C52AA:
	ldr r1, [r5, #0x28]
	ldr r0, [r1, #0x54]
	movs r2, #0xe0
	lsls r2, r2, #4
	adds r6, r0, r2
	ldr r0, [r1, #0x58]
	movs r1, #0xe0
	lsls r1, r1, #3
	adds r7, r0, r1
	ldr r1, [r5, #0x54]
	subs r0, r6, r1
	lsls r0, r0, #5
	asrs r0, r0, #8
	adds r1, r1, r0
	str r1, [r5, #0x54]
	ldr r1, [r5, #0x58]
	subs r0, r7, r1
	lsls r0, r0, #5
	asrs r0, r0, #8
	adds r1, r1, r0
	str r1, [r5, #0x58]
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
	beq _080C5300
	subs r0, #1
	strb r0, [r5, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080C5312
_080C5300:
	ldr r1, _080C5324 @ =gVFXFnTable
	ldrb r0, [r5, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r5, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r5, #0x14]
_080C5312:
	adds r0, r5, #0
	bl UpdateMotionGraphic
_080C5318:
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080C5320: .4byte 0x0000B801
_080C5324: .4byte gVFXFnTable
