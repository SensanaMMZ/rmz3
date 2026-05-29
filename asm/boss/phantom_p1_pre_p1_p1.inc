	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start Phantom_Init
Phantom_Init: @ 0x0805ED3C
	push {r4, r5, r6, r7, lr}
	mov r7, sl
	mov r6, sb
	mov r5, r8
	push {r5, r6, r7}
	adds r7, r0, #0
	ldr r1, _0805EEAC @ =gBossFnTable
	ldrb r0, [r7, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r7, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r7, #0x14]
	movs r0, #5
	strb r0, [r7, #0xd]
	movs r0, #0
	strh r0, [r7, #0xe]
	movs r1, #0
	strb r1, [r7, #0x10]
	adds r0, r7, #0
	bl InitNonAffineMotion
	adds r0, r7, #0
	bl ResetDynamicMotion
	ldrb r0, [r7, #0xa]
	movs r1, #1
	orrs r0, r1
	movs r1, #2
	orrs r0, r1
	strb r0, [r7, #0xa]
	ldr r4, [r7, #0x54]
	ldr r1, [r7, #0x58]
	adds r0, r4, #0
	bl FUN_08009f6c
	adds r1, r0, #0
	str r1, [r7, #0x58]
	movs r1, #0xf0
	lsls r1, r1, #8
	adds r0, r4, #0
	bl __divsi3
	lsls r1, r0, #4
	subs r1, r1, r0
	lsls r1, r1, #0xc
	ldr r0, _0805EEB0 @ =0xFFFF9000
	adds r2, r1, r0
	movs r0, #0xe0
	lsls r0, r0, #7
	adds r1, r1, r0
	adds r0, r7, #0
	adds r0, #0xd4
	str r2, [r0]
	adds r0, #4
	str r1, [r0]
	subs r1, r1, r2
	adds r0, #4
	str r1, [r0]
	adds r0, #4
	asrs r1, r1, #1
	adds r2, r2, r1
	str r2, [r0]
	subs r0, #0x1c
	movs r1, #0
	str r1, [r0]
	ldr r5, _0805EEB4 @ =0x00000A78
	ldr r2, _0805EEB8 @ =gStaticMotionGraphics
	mov r8, r2
	adds r0, r5, r2
	ldr r1, _0805EEBC @ =wStaticGraphicTilenums
	mov sb, r1
	movs r4, #0x86
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
	ldr r0, _0805EEC0 @ =gStaticMotionGraphics+12
	adds r5, r5, r0
	ldr r6, _0805EEC4 @ =wStaticMotionPalIDs
	adds r4, r6, r4
	ldrh r1, [r4]
	ldrb r0, [r5, #7]
	subs r1, r1, r0
	lsls r1, r1, #5
	movs r2, #0x80
	lsls r2, r2, #2
	mov sl, r2
	add r1, sl
	adds r0, r5, #0
	bl LoadPalette
	ldr r5, _0805EEC8 @ =0x00000A8C
	mov r1, r8
	adds r0, r5, r1
	movs r4, #0x87
	lsls r4, r4, #1
	mov r2, sb
	adds r1, r2, r4
	ldrh r1, [r1]
	ldrh r2, [r0, #6]
	lsrs r2, r2, #6
	subs r1, r1, r2
	lsls r1, r1, #5
	movs r2, #0x80
	lsls r2, r2, #9
	adds r1, r1, r2
	bl LoadGraphic
	ldr r0, _0805EEC0 @ =gStaticMotionGraphics+12
	adds r5, r5, r0
	adds r4, r6, r4
	ldrh r1, [r4]
	ldrb r0, [r5, #7]
	subs r1, r1, r0
	lsls r1, r1, #5
	add r1, sl
	adds r0, r5, #0
	bl LoadPalette
	movs r4, #0xaa
	lsls r4, r4, #4
	add r8, r4
	movs r5, #0x88
	lsls r5, r5, #1
	add sb, r5
	mov r2, sb
	ldrh r1, [r2]
	mov r2, r8
	ldrh r0, [r2, #6]
	lsrs r0, r0, #6
	subs r1, r1, r0
	lsls r1, r1, #5
	movs r0, #0x80
	lsls r0, r0, #9
	adds r1, r1, r0
	mov r0, r8
	bl LoadGraphic
	ldr r1, _0805EEC0 @ =gStaticMotionGraphics+12
	adds r4, r4, r1
	adds r6, r6, r5
	ldrh r1, [r6]
	ldrb r0, [r4, #7]
	subs r1, r1, r0
	lsls r1, r1, #5
	add r1, sl
	adds r0, r4, #0
	bl LoadPalette
	ldr r1, _0805EECC @ =sCollisions
	adds r0, r7, #0
	movs r2, #0x60
	bl ResetBossBody
	ldr r1, _0805EED0 @ =phantom_0805eed4
	adds r0, r7, #0
	adds r0, #0x74
	str r1, [r0, #0x24]
	adds r0, #0x5c
	movs r2, #0
	str r2, [r0]
	movs r0, #0
	strb r0, [r7, #0x10]
	adds r0, r7, #0
	bl Phantom_Update
	pop {r3, r4, r5}
	mov r8, r3
	mov sb, r4
	mov sl, r5
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_0805EEAC: .4byte gBossFnTable
_0805EEB0: .4byte 0xFFFF9000
_0805EEB4: .4byte 0x00000A78
_0805EEB8: .4byte gStaticMotionGraphics
_0805EEBC: .4byte wStaticGraphicTilenums
_0805EEC0: .4byte gStaticMotionGraphics+12
_0805EEC4: .4byte wStaticMotionPalIDs
_0805EEC8: .4byte 0x00000A8C
_0805EECC: .4byte sCollisions
_0805EED0: .4byte phantom_0805eed4
