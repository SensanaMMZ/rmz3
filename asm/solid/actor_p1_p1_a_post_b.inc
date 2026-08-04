	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start ActorFefnir12_Update
ActorFefnir12_Update: @ 0x080D23B0
	push {r4, r5, r6, r7, lr}
	sub sp, #8
	adds r7, r0, #0
	ldrb r0, [r7, #0xd]
	cmp r0, #0x14
	bls _080D23BE
	b _080D27FC
_080D23BE:
	lsls r0, r0, #2
	ldr r1, _080D23C8 @ =_080D23CC
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_080D23C8: .4byte _080D23CC
_080D23CC: @ jump table
	.4byte _080D2420 @ case 0
	.4byte _080D24A0 @ case 1
	.4byte _080D24EC @ case 2
	.4byte _080D2558 @ case 3
	.4byte _080D25B0 @ case 4
	.4byte _080D25D8 @ case 5
	.4byte _080D264C @ case 6
	.4byte _080D2688 @ case 7
	.4byte _080D264C @ case 8
	.4byte _080D2688 @ case 9
	.4byte _080D264C @ case 10
	.4byte _080D2688 @ case 11
	.4byte _080D269C @ case 12
	.4byte _080D27FC @ case 13
	.4byte _080D26B0 @ case 14
	.4byte _080D26E4 @ case 15
	.4byte _080D2750 @ case 16
	.4byte _080D27A8 @ case 17
	.4byte _080D27C8 @ case 18
	.4byte _080D27E4 @ case 19
	.4byte _080D27FC @ case 20
_080D2420:
	ldr r0, _080D24CC @ =wDynamicGraphicTilenums
	movs r2, #0xa1
	lsls r2, r2, #1
	adds r0, r0, r2
	ldr r1, _080D24D0 @ =0x0000034D
	strh r1, [r0]
	ldr r0, _080D24D4 @ =wDynamicMotionPalIDs
	adds r0, r0, r2
	movs r1, #9
	strh r1, [r0]
	ldr r1, _080D24D8 @ =0x0000A114
	adds r0, r7, #0
	bl SetMotion
	movs r2, #1
	ldrb r1, [r7, #0xa]
	movs r0, #0x10
	orrs r0, r1
	strb r0, [r7, #0xa]
	adds r0, r7, #0
	adds r0, #0x4c
	movs r5, #0
	strb r2, [r0]
	adds r3, r7, #0
	adds r3, #0x4a
	movs r2, #0x10
	ldrb r1, [r3]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	orrs r0, r2
	strb r0, [r3]
	ldrb r1, [r7, #0xa]
	movs r0, #4
	orrs r0, r1
	strb r0, [r7, #0xa]
	adds r4, r7, #0
	adds r4, #0x74
	ldr r1, _080D24DC @ =sCollisions_08370B58+(24*1)
	adds r2, r7, #0
	adds r2, #0x54
	adds r0, r4, #0
	movs r3, #9
	bl InitBody
	str r7, [r4, #0x2c]
	str r5, [r4, #0x24]
	adds r1, r7, #0
	adds r1, #0x94
	movs r0, #0x5a
	strb r0, [r1]
	movs r0, #0xf4
	bl PlaySound
	ldr r0, _080D24E0 @ =gStageRun+232
	ldr r0, [r0, #0x38]
	ldr r1, _080D24E4 @ =0x000087FF
	adds r0, r0, r1
	str r0, [r7, #0x54]
	movs r0, #0x14
	strb r0, [r7, #0x12]
	ldrb r0, [r7, #0xd]
	adds r0, #1
	strb r0, [r7, #0xd]
_080D24A0:
	adds r0, r7, #0
	bl UpdateMotionGraphic
	ldr r0, [r7, #0x54]
	ldr r2, _080D24E8 @ =0xFFFFFD00
	adds r0, r0, r2
	str r0, [r7, #0x54]
	ldrb r0, [r7, #0x12]
	subs r0, #1
	strb r0, [r7, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _080D24BC
	b _080D27FC
_080D24BC:
	movs r0, #8
	strb r0, [r7, #0x12]
	movs r1, #0xa1
	lsls r1, r1, #8
	adds r0, r7, #0
	bl SetMotion
	b _080D27F6
	.align 2, 0
_080D24CC: .4byte wDynamicGraphicTilenums
_080D24D0: .4byte 0x0000034D
_080D24D4: .4byte wDynamicMotionPalIDs
_080D24D8: .4byte 0x0000A114
_080D24DC: .4byte sCollisions_08370B58+(24*1)
_080D24E0: .4byte gStageRun+232
_080D24E4: .4byte 0x000087FF
_080D24E8: .4byte 0xFFFFFD00
_080D24EC:
	adds r0, r7, #0
	bl UpdateMotionGraphic
	ldr r2, [r7, #0x54]
	ldr r1, _080D254C @ =0xFFFFFE00
	adds r0, r2, r1
	str r0, [r7, #0x54]
	ldrb r1, [r7, #0x12]
	movs r0, #3
	ands r0, r1
	cmp r0, #0
	bne _080D2528
	ldr r1, _080D2550 @ =0xFFFFF200
	adds r0, r2, r1
	str r0, [sp]
	ldr r0, [r7, #0x58]
	str r0, [sp, #4]
	movs r0, #3
	mov r1, sp
	bl CreateSmoke
	ldr r0, [r7, #0x54]
	movs r2, #0x80
	lsls r2, r2, #4
	adds r0, r0, r2
	str r0, [sp]
	movs r0, #3
	mov r1, sp
	bl CreateSmoke
_080D2528:
	ldrb r0, [r7, #0x12]
	subs r0, #1
	strb r0, [r7, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _080D2536
	b _080D27FC
_080D2536:
	ldr r1, _080D2554 @ =0x0000A11B
	adds r0, r7, #0
	bl SetMotion
	movs r0, #0x80
	lsls r0, r0, #2
	str r0, [r7, #0x5c]
	movs r0, #0x20
	strb r0, [r7, #0x12]
	b _080D27F6
	.align 2, 0
_080D254C: .4byte 0xFFFFFE00
_080D2550: .4byte 0xFFFFF200
_080D2554: .4byte 0x0000A11B
_080D2558:
	adds r0, r7, #0
	bl UpdateMotionGraphic
	ldr r1, [r7, #0x5c]
	lsls r0, r1, #4
	subs r0, r0, r1
	asrs r0, r0, #4
	str r0, [r7, #0x5c]
	ldr r1, [r7, #0x54]
	subs r2, r1, r0
	str r2, [r7, #0x54]
	ldrb r1, [r7, #0x12]
	movs r0, #7
	ands r0, r1
	cmp r0, #0
	bne _080D259C
	ldr r1, _080D25AC @ =0xFFFFF400
	adds r0, r2, r1
	str r0, [sp]
	ldr r0, [r7, #0x58]
	str r0, [sp, #4]
	movs r0, #3
	mov r1, sp
	bl CreateSmoke
	ldr r0, [r7, #0x54]
	movs r2, #0x80
	lsls r2, r2, #4
	adds r0, r0, r2
	str r0, [sp]
	movs r0, #3
	mov r1, sp
	bl CreateSmoke
_080D259C:
	ldrb r0, [r7, #0x12]
	subs r0, #1
	strb r0, [r7, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _080D25AA
	b _080D27FC
_080D25AA:
	b _080D27F6
	.align 2, 0
_080D25AC: .4byte 0xFFFFF400
_080D25B0:
	adds r0, r7, #0
	bl UpdateMotionGraphic
	ldr r0, [r7, #0x18]
	ldrb r1, [r0, #9]
	movs r0, #1
	ands r0, r1
	cmp r0, #0
	bne _080D25C4
	b _080D27FC
_080D25C4:
	ldr r1, _080D25D4 @ =0x0000A11C
	adds r0, r7, #0
	bl SetMotion
	movs r0, #0x3c
	strb r0, [r7, #0x12]
	b _080D27F6
	.align 2, 0
_080D25D4: .4byte 0x0000A11C
_080D25D8:
	adds r0, r7, #0
	bl UpdateMotionGraphic
	ldrb r0, [r7, #0x12]
	subs r0, #1
	strb r0, [r7, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _080D25EC
	b _080D27FC
_080D25EC:
	ldr r1, _080D2638 @ =0x0000A109
	adds r0, r7, #0
	bl SetMotion
	ldr r0, _080D263C @ =wStaticGraphicTilenums
	adds r0, #0x42
	movs r6, #0x80
	lsls r6, r6, #2
	strh r6, [r0]
	ldr r5, _080D2640 @ =wStaticMotionPalIDs
	adds r5, #0x42
	movs r0, #4
	strh r0, [r5]
	movs r4, #0xa5
	lsls r4, r4, #2
	ldr r1, _080D2644 @ =gStaticMotionGraphics
	adds r0, r4, r1
	ldrh r1, [r0, #6]
	lsrs r1, r1, #6
	subs r1, r6, r1
	lsls r1, r1, #5
	movs r2, #0x80
	lsls r2, r2, #9
	adds r1, r1, r2
	bl LoadGraphic
	ldr r0, _080D2648 @ =gStaticMotionGraphics+12
	adds r4, r4, r0
	ldrh r1, [r5]
	ldrb r0, [r4, #7]
	subs r1, r1, r0
	lsls r1, r1, #5
	adds r1, r1, r6
	adds r0, r4, #0
	bl LoadPalette
	b _080D27F6
	.align 2, 0
_080D2638: .4byte 0x0000A109
_080D263C: .4byte wStaticGraphicTilenums
_080D2640: .4byte wStaticMotionPalIDs
_080D2644: .4byte gStaticMotionGraphics
_080D2648: .4byte gStaticMotionGraphics+12
_080D264C:
	adds r0, r7, #0
	bl UpdateMotionGraphic
	ldr r0, [r7, #0x18]
	ldrb r1, [r0, #9]
	movs r0, #2
	ands r0, r1
	cmp r0, #0
	bne _080D2660
	b _080D27FC
_080D2660:
	ldr r1, _080D2684 @ =0x0000A10B
	adds r0, r7, #0
	bl SetMotion
	adds r0, r7, #0
	movs r1, #0xd
	bl CreateScriptActor
	movs r0, #0xf5
	bl PlaySound
	adds r1, r7, #0
	adds r1, #0x54
	movs r0, #2
	bl AppendQuake
	b _080D27F6
	.align 2, 0
_080D2684: .4byte 0x0000A10B
_080D2688:
	adds r0, r7, #0
	bl UpdateMotionGraphic
	adds r0, r7, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	beq _080D269A
	b _080D27FC
_080D269A:
	b _080D27F6
_080D269C:
	adds r0, r7, #0
	bl UpdateMotionGraphic
	movs r1, #0xa1
	lsls r1, r1, #8
	adds r0, r7, #0
	bl SetMotion
	movs r0, #0xe
	b _080D27FA
_080D26B0:
	adds r0, r7, #0
	bl UpdateMotionGraphic
	adds r0, r7, #0
	adds r0, #0x8c
	ldr r0, [r0]
	movs r1, #1
	ands r0, r1
	cmp r0, #0
	bne _080D26C6
	b _080D27FC
_080D26C6:
	ldr r1, _080D2740 @ =0x0000A114
	adds r0, r7, #0
	bl SetMotion
	movs r0, #0xf4
	bl PlaySound
	movs r0, #0x52
	bl PlaySound
	movs r0, #8
	strb r0, [r7, #0x12]
	ldrb r0, [r7, #0xd]
	adds r0, #1
	strb r0, [r7, #0xd]
_080D26E4:
	adds r0, r7, #0
	bl UpdateMotionGraphic
	ldr r2, [r7, #0x54]
	ldr r1, _080D2744 @ =0xFFFFFE00
	adds r0, r2, r1
	str r0, [r7, #0x54]
	ldrb r1, [r7, #0x12]
	movs r0, #3
	ands r0, r1
	cmp r0, #0
	bne _080D2720
	ldr r1, _080D2748 @ =0xFFFFF200
	adds r0, r2, r1
	str r0, [sp]
	ldr r0, [r7, #0x58]
	str r0, [sp, #4]
	movs r0, #3
	mov r1, sp
	bl CreateSmoke
	ldr r0, [r7, #0x54]
	movs r2, #0x80
	lsls r2, r2, #4
	adds r0, r0, r2
	str r0, [sp]
	movs r0, #3
	mov r1, sp
	bl CreateSmoke
_080D2720:
	ldrb r0, [r7, #0x12]
	subs r0, #1
	strb r0, [r7, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080D27FC
	ldr r1, _080D274C @ =0x0000A11B
	adds r0, r7, #0
	bl SetMotion
	movs r0, #0x80
	lsls r0, r0, #3
	str r0, [r7, #0x5c]
	movs r0, #0x18
	strb r0, [r7, #0x12]
	b _080D27F6
	.align 2, 0
_080D2740: .4byte 0x0000A114
_080D2744: .4byte 0xFFFFFE00
_080D2748: .4byte 0xFFFFF200
_080D274C: .4byte 0x0000A11B
_080D2750:
	adds r0, r7, #0
	bl UpdateMotionGraphic
	ldr r1, [r7, #0x5c]
	lsls r0, r1, #3
	subs r0, r0, r1
	asrs r0, r0, #3
	str r0, [r7, #0x5c]
	ldr r1, [r7, #0x54]
	subs r2, r1, r0
	str r2, [r7, #0x54]
	ldrb r1, [r7, #0x12]
	movs r0, #7
	ands r0, r1
	cmp r0, #0
	bne _080D2794
	ldr r1, _080D27A4 @ =0xFFFFF400
	adds r0, r2, r1
	str r0, [sp]
	ldr r0, [r7, #0x58]
	str r0, [sp, #4]
	movs r0, #3
	mov r1, sp
	bl CreateSmoke
	ldr r0, [r7, #0x54]
	movs r2, #0x80
	lsls r2, r2, #4
	adds r0, r0, r2
	str r0, [sp]
	movs r0, #3
	mov r1, sp
	bl CreateSmoke
_080D2794:
	ldrb r0, [r7, #0x12]
	subs r0, #1
	strb r0, [r7, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080D27FC
	b _080D27F6
	.align 2, 0
_080D27A4: .4byte 0xFFFFF400
_080D27A8:
	adds r0, r7, #0
	bl UpdateMotionGraphic
	ldr r0, [r7, #0x18]
	ldrb r1, [r0, #9]
	movs r0, #4
	ands r0, r1
	cmp r0, #0
	beq _080D27FC
	ldr r1, _080D27C4 @ =0x0000A11C
	adds r0, r7, #0
	bl SetMotion
	b _080D27F6
	.align 2, 0
_080D27C4: .4byte 0x0000A11C
_080D27C8:
	adds r0, r7, #0
	bl UpdateMotionGraphic
	adds r0, r7, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _080D27FC
	movs r1, #0xa1
	lsls r1, r1, #8
	adds r0, r7, #0
	bl SetMotion
	b _080D27F6
_080D27E4:
	movs r1, #0xa1
	lsls r1, r1, #8
	adds r0, r7, #0
	movs r2, #1
	bl FUN_080d0934
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _080D27FC
_080D27F6:
	ldrb r0, [r7, #0xd]
	adds r0, #1
_080D27FA:
	strb r0, [r7, #0xd]
_080D27FC:
	add sp, #8
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
