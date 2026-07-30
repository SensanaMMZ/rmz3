	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start ReactorCore_Init
ReactorCore_Init: @ 0x08061758
	push {r4, r5, r6, r7, lr}
	mov r7, sl
	mov r6, sb
	mov r5, r8
	push {r5, r6, r7}
	adds r7, r0, #0
	ldrb r1, [r7, #0xb]
	movs r0, #8
	orrs r0, r1
	strb r0, [r7, #0xb]
	ldr r0, _080618CC @ =0x083656C8
	str r0, [r7, #0x30]
	movs r2, #1
	strh r2, [r7, #0x26]
	ldr r1, _080618D0 @ =gBossFnTable
	ldrb r0, [r7, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	str r2, [r7, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r7, #0x14]
	ldr r1, _080618D4 @ =0x083656D0
	ldrb r0, [r7, #0x10]
	adds r0, r0, r1
	ldrb r0, [r0]
	strb r0, [r7, #0xd]
	ldrb r1, [r7, #0xa]
	movs r0, #2
	orrs r0, r1
	movs r1, #0xfe
	ands r0, r1
	strb r0, [r7, #0xa]
	movs r4, #0
_0806179C:
	adds r0, r7, #0
	adds r0, #0xb4
	adds r0, r0, r4
	movs r1, #7
	strb r1, [r0]
	lsls r1, r4, #0x18
	lsrs r1, r1, #0x18
	ldrb r2, [r7, #0x10]
	adds r0, r7, #0
	bl FUN_080935b4
	adds r4, #1
	cmp r4, #5
	ble _0806179C
	adds r0, r7, #0
	adds r0, #0xbc
	movs r1, #0
	str r1, [r0]
	ldr r5, _080618D8 @ =0x00000ADC
	ldr r2, _080618DC @ =gStaticMotionGraphics
	mov sb, r2
	adds r0, r5, r2
	ldr r1, _080618E0 @ =wStaticGraphicTilenums
	mov r8, r1
	movs r4, #0x8b
	lsls r4, r4, #1
	adds r1, r1, r4
	ldrh r1, [r1]
	ldrh r2, [r0, #6]
	lsrs r2, r2, #6
	subs r1, r1, r2
	lsls r1, r1, #5
	movs r2, #0x80
	lsls r2, r2, #9
	adds r1, r1, r2
	bl LoadGraphic
	ldr r0, _080618E4 @ =gStaticMotionGraphics+12
	mov sl, r0
	add r5, sl
	ldr r6, _080618E8 @ =wStaticMotionPalIDs
	adds r4, r6, r4
	ldrh r1, [r4]
	ldrb r0, [r5, #7]
	subs r1, r1, r0
	lsls r1, r1, #5
	movs r2, #0x80
	lsls r2, r2, #2
	adds r1, r1, r2
	adds r0, r5, #0
	bl LoadPalette
	ldr r4, _080618EC @ =0x0000053C
	add sb, r4
	movs r0, #0x86
	add r8, r0
	mov r2, r8
	ldrh r1, [r2]
	mov r2, sb
	ldrh r0, [r2, #6]
	lsrs r0, r0, #6
	subs r1, r1, r0
	lsls r1, r1, #5
	movs r0, #0x80
	lsls r0, r0, #9
	adds r1, r1, r0
	mov r0, sb
	bl LoadGraphic
	add r4, sl
	adds r6, #0x86
	ldrh r1, [r6]
	ldrb r0, [r4, #7]
	subs r1, r1, r0
	lsls r1, r1, #5
	movs r2, #0x80
	lsls r2, r2, #2
	adds r1, r1, r2
	adds r0, r4, #0
	bl LoadPalette
	ldr r1, _080618F0 @ =sCollisions
	adds r0, r7, #0
	movs r2, #1
	bl ResetBossBody
	ldr r0, [r7, #0x54]
	ldr r1, [r7, #0x58]
	bl FUN_08009f6c
	ldr r1, _080618F4 @ =0xFFFFE800
	adds r0, r0, r1
	ldrb r2, [r7, #0x10]
	lsls r1, r2, #1
	adds r1, r1, r2
	lsls r1, r1, #0xb
	subs r0, r0, r1
	str r0, [r7, #0x58]
	adds r5, r7, #0
	adds r5, #0x22
	movs r2, #0
	strb r2, [r5]
	movs r4, #0x8b
	lsls r4, r4, #8
	adds r0, r7, #0
	adds r1, r4, #0
	bl SetMotion
	adds r0, r7, #0
	bl GetEntityPalID
	adds r1, r0, #0
	lsls r1, r1, #0x18
	lsrs r1, r1, #0x13
	movs r0, #0x80
	lsls r0, r0, #2
	orrs r1, r0
	movs r0, #0xcb
	bl StartPaletteAnimation
	movs r0, #1
	strb r0, [r5]
	adds r0, r7, #0
	adds r1, r4, #0
	bl SetMotion
	adds r0, r7, #0
	bl GetEntityPalID
	adds r1, r0, #0
	lsls r1, r1, #0x18
	lsrs r1, r1, #0x13
	movs r2, #0x80
	lsls r2, r2, #2
	orrs r1, r2
	movs r0, #0xcc
	bl StartPaletteAnimation
	movs r0, #0xe0
	bl PlaySound
	adds r0, r7, #0
	bl ReactorCore_Update
	pop {r3, r4, r5}
	mov r8, r3
	mov sb, r4
	mov sl, r5
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080618CC: .4byte 0x083656C8
_080618D0: .4byte gBossFnTable
_080618D4: .4byte 0x083656D0
_080618D8: .4byte 0x00000ADC
_080618DC: .4byte gStaticMotionGraphics
_080618E0: .4byte wStaticGraphicTilenums
_080618E4: .4byte gStaticMotionGraphics+12
_080618E8: .4byte wStaticMotionPalIDs
_080618EC: .4byte 0x0000053C
_080618F0: .4byte sCollisions
_080618F4: .4byte 0xFFFFE800
