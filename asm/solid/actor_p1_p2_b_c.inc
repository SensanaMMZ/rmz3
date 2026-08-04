	.include "asm/macros.inc"

	.syntax unified
	
	.text


	thumb_func_start Actor37_Update
Actor37_Update: @ 0x080D444C
	push {r4, r5, r6, lr}
	adds r6, r0, #0
	ldrb r0, [r6, #0xd]
	cmp r0, #4
	bls _080D4458
	b _080D45E4
_080D4458:
	lsls r0, r0, #2
	ldr r1, _080D4464 @ =_080D4468
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_080D4464: .4byte _080D4468
_080D4468: @ jump table
	.4byte _080D447C @ case 0
	.4byte _080D454C @ case 1
	.4byte _080D459C @ case 2
	.4byte _080D45BC @ case 3
	.4byte _080D45E4 @ case 4
_080D447C:
	ldr r0, [r6, #0x54]
	ldr r1, [r6, #0x58]
	bl FUN_08009f6c
	str r0, [r6, #0x58]
	ldrb r0, [r6, #0x11]
	cmp r0, #0
	bne _080D44F4
	movs r4, #0x82
	ldr r0, _080D44E4 @ =wStaticGraphicTilenums
	lsls r2, r4, #1
	adds r0, r0, r2
	movs r1, #0x98
	lsls r1, r1, #2
	strh r1, [r0]
	ldr r5, _080D44E8 @ =wStaticMotionPalIDs
	adds r5, r5, r2
	movs r0, #6
	strh r0, [r5]
	lsls r4, r4, #2
	adds r4, #0x82
	lsls r4, r4, #2
	ldr r2, _080D44EC @ =gStaticMotionGraphics
	adds r0, r4, r2
	ldrh r2, [r0, #6]
	lsrs r2, r2, #6
	subs r1, r1, r2
	lsls r1, r1, #5
	movs r2, #0x80
	lsls r2, r2, #9
	adds r1, r1, r2
	bl LoadGraphic
	ldr r0, _080D44F0 @ =gStaticMotionGraphics+12
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
	movs r1, #0x82
	lsls r1, r1, #8
	adds r0, r6, #0
	bl SetMotion
	b _080D4546
	.align 2, 0
_080D44E4: .4byte wStaticGraphicTilenums
_080D44E8: .4byte wStaticMotionPalIDs
_080D44EC: .4byte gStaticMotionGraphics
_080D44F0: .4byte gStaticMotionGraphics+12
_080D44F4:
	movs r4, #0x8c
	ldr r1, _080D4584 @ =wStaticGraphicTilenums
	lsls r2, r4, #1
	adds r1, r1, r2
	ldr r0, _080D4588 @ =0x00000296
	strh r0, [r1]
	ldr r5, _080D458C @ =wStaticMotionPalIDs
	adds r5, r5, r2
	movs r0, #6
	strh r0, [r5]
	lsls r4, r4, #2
	adds r4, #0x8c
	lsls r4, r4, #2
	ldr r2, _080D4590 @ =gStaticMotionGraphics
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
	ldr r0, _080D4594 @ =gStaticMotionGraphics+12
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
	ldr r1, _080D4598 @ =0x00008C05
	adds r0, r6, #0
	bl SetMotion
_080D4546:
	ldrb r0, [r6, #0xd]
	adds r0, #1
	strb r0, [r6, #0xd]
_080D454C:
	adds r0, r6, #0
	bl UpdateMotionGraphic
	ldr r0, [r6, #0x18]
	ldrb r1, [r0, #9]
	movs r0, #1
	ands r0, r1
	cmp r0, #0
	beq _080D45E4
	movs r2, #0
	ldrb r1, [r6, #0xa]
	movs r0, #0xef
	ands r0, r1
	strb r0, [r6, #0xa]
	adds r0, r6, #0
	adds r0, #0x4c
	strb r2, [r0]
	adds r2, r6, #0
	adds r2, #0x4a
	ldrb r1, [r2]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r2]
	movs r0, #8
	strb r0, [r6, #0x12]
	b _080D45DE
	.align 2, 0
_080D4584: .4byte wStaticGraphicTilenums
_080D4588: .4byte 0x00000296
_080D458C: .4byte wStaticMotionPalIDs
_080D4590: .4byte gStaticMotionGraphics
_080D4594: .4byte gStaticMotionGraphics+12
_080D4598: .4byte 0x00008C05
_080D459C:
	adds r0, r6, #0
	bl UpdateMotionGraphic
	ldrb r0, [r6, #0x12]
	subs r0, #1
	strb r0, [r6, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080D45E4
	ldr r1, _080D45B8 @ =0x00008C07
	adds r0, r6, #0
	bl SetMotion
	b _080D45DE
	.align 2, 0
_080D45B8: .4byte 0x00008C07
_080D45BC:
	adds r0, r6, #0
	bl UpdateMotionGraphic
	ldr r1, [r6, #0x54]
	ldr r0, _080D45EC @ =0xFFFFFF00
	adds r1, r1, r0
	str r1, [r6, #0x54]
	ldr r0, _080D45F0 @ =gStageRun+232
	ldr r0, [r0, #0x38]
	ldr r2, _080D45F4 @ =0xFFFF7000
	adds r0, r0, r2
	cmp r1, r0
	bge _080D45E4
	ldrb r0, [r6, #0xa]
	movs r1, #0xfe
	ands r1, r0
	strb r1, [r6, #0xa]
_080D45DE:
	ldrb r0, [r6, #0xd]
	adds r0, #1
	strb r0, [r6, #0xd]
_080D45E4:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_080D45EC: .4byte 0xFFFFFF00
_080D45F0: .4byte gStageRun+232
_080D45F4: .4byte 0xFFFF7000
