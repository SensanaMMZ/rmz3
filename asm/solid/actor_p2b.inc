	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start Actor62_Update
Actor62_Update: @ 0x080D76BC
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xd]
	cmp r0, #9
	bls _080D76C8
	b _080D7868
_080D76C8:
	lsls r0, r0, #2
	ldr r1, _080D76D4 @ =_080D76D8
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_080D76D4: .4byte _080D76D8
_080D76D8: @ jump table
	.4byte _080D7700 @ case 0
	.4byte _080D7718 @ case 1
	.4byte _080D7738 @ case 2
	.4byte _080D775A @ case 3
	.4byte _080D778C @ case 4
	.4byte _080D77AC @ case 5
	.4byte _080D77BE @ case 6
	.4byte _080D77EA @ case 7
	.4byte _080D7828 @ case 8
	.4byte _080D7868 @ case 9
_080D7700:
	adds r0, r4, #0
	movs r1, #0
	bl SetMotion
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	bl FUN_08009f6c
	str r0, [r4, #0x58]
	ldrb r0, [r4, #0xd]
	adds r0, #1
	strb r0, [r4, #0xd]
_080D7718:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldr r0, [r4, #0x18]
	ldrb r1, [r0, #9]
	movs r0, #1
	ands r0, r1
	cmp r0, #0
	bne _080D772C
	b _080D7868
_080D772C:
	movs r1, #0xcc
	lsls r1, r1, #6
	adds r0, r4, #0
	bl SetMotion
	b _080D7862
_080D7738:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #4
	beq _080D774A
	b _080D7868
_080D774A:
	movs r1, #0xc4
	lsls r1, r1, #8
	adds r0, r4, #0
	bl SetMotion
	movs r0, #0
	strb r0, [r4, #0x12]
	b _080D7862
_080D775A:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldr r0, [r4, #0x54]
	adds r0, #0x60
	str r0, [r4, #0x54]
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #4
	bne _080D7776
	ldrb r0, [r4, #0x12]
	adds r0, #1
	strb r0, [r4, #0x12]
_080D7776:
	ldrb r0, [r4, #0x12]
	cmp r0, #2
	bne _080D7868
	ldr r1, _080D7788 @ =0x00003303
	adds r0, r4, #0
	bl SetMotion
	b _080D7862
	.align 2, 0
_080D7788: .4byte 0x00003303
_080D778C:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldr r0, [r4, #0x18]
	ldrb r1, [r0, #9]
	movs r0, #2
	ands r0, r1
	cmp r0, #0
	beq _080D7868
	ldr r1, _080D77A8 @ =0x00003301
	adds r0, r4, #0
	bl SetMotion
	b _080D7862
	.align 2, 0
_080D77A8: .4byte 0x00003301
_080D77AC:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _080D7868
	b _080D7862
_080D77BE:
	ldr r1, _080D7824 @ =0x00000301
	adds r0, r4, #0
	bl SetMotion
	movs r2, #0
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
	ldrb r0, [r4, #0xd]
	adds r0, #1
	strb r0, [r4, #0xd]
_080D77EA:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _080D7868
	movs r1, #0xc0
	lsls r1, r1, #2
	adds r0, r4, #0
	bl SetMotion
	adds r0, r4, #0
	adds r0, #0x54
	ldrb r2, [r4, #0xa]
	lsrs r2, r2, #4
	movs r1, #1
	ands r2, r1
	movs r1, #0
	bl CreateParticle
	movs r0, #8
	bl PlaySound
	movs r0, #0
	str r0, [r4, #0x2c]
	b _080D7862
	.align 2, 0
_080D7824: .4byte 0x00000301
_080D7828:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldr r0, [r4, #0x2c]
	cmp r0, #0
	bne _080D783C
	adds r0, r4, #0
	bl CreateAfterImages
	str r0, [r4, #0x2c]
_080D783C:
	ldr r1, [r4, #0x54]
	ldr r0, _080D7870 @ =0xFFFFFC80
	adds r1, r1, r0
	str r1, [r4, #0x54]
	ldr r0, _080D7874 @ =gStageRun+232
	ldr r0, [r0, #0x38]
	ldr r2, _080D7878 @ =0xFFFF6800
	adds r0, r0, r2
	cmp r1, r0
	bge _080D7868
	ldr r1, [r4, #0x2c]
	cmp r1, #0
	beq _080D785A
	movs r0, #1
	strb r0, [r1, #0x11]
_080D785A:
	ldrb r0, [r4, #0xa]
	movs r1, #0xfe
	ands r1, r0
	strb r1, [r4, #0xa]
_080D7862:
	ldrb r0, [r4, #0xd]
	adds r0, #1
	strb r0, [r4, #0xd]
_080D7868:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080D7870: .4byte 0xFFFFFC80
_080D7874: .4byte gStageRun+232
_080D7878: .4byte 0xFFFF6800
