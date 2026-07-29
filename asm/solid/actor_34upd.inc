	.include "asm/macros.inc"

	.syntax unified
	
	.text

	push {r4, r5, r6, r7, lr}
	adds r6, r0, #0
	ldrb r0, [r6, #0xd]
	cmp r0, #0
	beq _080D4124
	cmp r0, #1
	beq _080D418C
	b _080D4220
_080D4124:
	ldr r0, [r6, #0x54]
	ldr r1, [r6, #0x58]
	bl FUN_08009f6c
	ldr r1, _080D41EC @ =0xFFFFE800
	adds r0, r0, r1
	str r0, [r6, #0x58]
	movs r4, #0xb8
	ldr r1, _080D41F0 @ =wStaticGraphicTilenums
	lsls r2, r4, #1
	adds r1, r1, r2
	ldr r0, _080D41F4 @ =0x00000385
	strh r0, [r1]
	ldr r5, _080D41F8 @ =wStaticMotionPalIDs
	adds r5, r5, r2
	movs r0, #5
	strh r0, [r5]
	lsls r4, r4, #4
	movs r2, #0xb8
	lsls r2, r2, #2
	adds r4, r4, r2
	ldr r2, _080D41FC @ =gStaticMotionGraphics
	adds r0, r4, r2
	ldrh r1, [r1]
	ldrh r2, [r0, #6]
	lsrs r2, r2, #6
	subs r1, r1, r2
	lsls r1, r1, #5
	movs r2, #0x80
	lsls r2, r2, #9
	adds r1, r1, r2
	bl LoadGraphic
	ldr r0, _080D4200 @ =gStaticMotionGraphics+12
	adds r4, r4, r0
	ldrh r1, [r5]
	ldrb r0, [r4, #7]
	subs r1, r1, r0
	lsls r1, r1, #5
	movs r2, #0x80
	lsls r2, r2, #2
	adds r1, r1, r2
	adds r0, r4, #0
	bl LoadPalette
	ldr r1, _080D4204 @ =0x0000B802
	adds r0, r6, #0
	bl SetMotion
	ldrb r0, [r6, #0xd]
	adds r0, #1
	strb r0, [r6, #0xd]
_080D418C:
	adds r0, r6, #0
	bl UpdateMotionGraphic
	adds r0, r6, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _080D41A4
	ldr r1, _080D4204 @ =0x0000B802
	adds r0, r6, #0
	bl SetMotion
_080D41A4:
	ldr r4, _080D4208 @ =RNG_0202f388
	ldr r0, [r4]
	ldr r7, _080D420C @ =0x000343FD
	muls r0, r7, r0
	ldr r5, _080D4210 @ =0x00269EC3
	adds r0, r0, r5
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r4]
	lsrs r0, r0, #0x11
	movs r1, #0x1f
	ands r0, r1
	cmp r0, #0
	bne _080D41C8
	ldr r1, _080D4214 @ =0x0000B803
	adds r0, r6, #0
	bl SetMotion
_080D41C8:
	ldrb r0, [r6, #0x11]
	cmp r0, #0
	beq _080D4220
	ldr r0, [r4]
	muls r0, r7, r0
	adds r0, r0, r5
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r4]
	lsrs r0, r0, #0x11
	movs r1, #1
	ands r0, r1
	cmp r0, #0
	beq _080D4218
	ldrb r1, [r6, #0xa]
	movs r0, #1
	orrs r0, r1
	b _080D421E
	.align 2, 0
_080D41EC: .4byte 0xFFFFE800
_080D41F0: .4byte wStaticGraphicTilenums
_080D41F4: .4byte 0x00000385
_080D41F8: .4byte wStaticMotionPalIDs
_080D41FC: .4byte gStaticMotionGraphics
_080D4200: .4byte gStaticMotionGraphics+12
_080D4204: .4byte 0x0000B802
_080D4208: .4byte RNG_0202f388
_080D420C: .4byte 0x000343FD
_080D4210: .4byte 0x00269EC3
_080D4214: .4byte 0x0000B803
_080D4218:
	ldrb r1, [r6, #0xa]
	movs r0, #0xfe
	ands r0, r1
_080D421E:
	strb r0, [r6, #0xa]
_080D4220:
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
