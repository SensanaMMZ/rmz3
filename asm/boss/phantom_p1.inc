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

	thumb_func_start phantom_0805eed4
phantom_0805eed4: @ 0x0805EED4
	push {r4, lr}
	ldr r4, [r0, #0x2c]
	ldr r0, [r0, #0x14]
	movs r1, #1
	ands r0, r1
	cmp r0, #0
	beq _0805EEE8
	movs r0, #0xff
	bl PlaySound
_0805EEE8:
	movs r2, #0
	ldr r0, _0805EF08 @ =pZero2
	ldr r0, [r0]
	ldr r0, [r0, #0x54]
	ldr r1, [r4, #0x54]
	subs r0, r0, r1
	cmp r0, #0
	ble _0805EEFA
	movs r2, #1
_0805EEFA:
	adds r0, r4, #0
	adds r0, #0xcb
	strb r2, [r0]
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_0805EF08: .4byte pZero2

	thumb_func_start Phantom_Update
Phantom_Update: @ 0x0805EF0C
	push {r4, lr}
	adds r4, r0, #0
	adds r0, #0x8c
	ldr r0, [r0]
	movs r1, #0x80
	lsls r1, r1, #2
	ands r0, r1
	cmp r0, #0
	bne _0805EF2A
	adds r0, r4, #0
	adds r0, #0xa4
	movs r1, #0
	ldrsh r0, [r0, r1]
	cmp r0, #0
	bne _0805EF6C
_0805EF2A:
	ldr r0, _0805EF64 @ =gStageRun
	ldrh r1, [r0, #8]
	movs r0, #8
	ands r0, r1
	lsls r0, r0, #0x10
	lsrs r2, r0, #0x10
	cmp r2, #0
	bne _0805EF6C
	adds r1, r4, #0
	adds r1, #0xd0
	ldr r0, [r1]
	cmp r0, #0
	beq _0805EF46
	str r2, [r1]
_0805EF46:
	ldr r1, _0805EF68 @ =gBossFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r4, #0x14]
	strb r2, [r4, #0xd]
	adds r0, r4, #0
	bl Phantom_Die
	b _0805EF82
	.align 2, 0
_0805EF64: .4byte gStageRun
_0805EF68: .4byte gBossFnTable
_0805EF6C:
	ldr r0, _0805EF88 @ =0x08365414
	ldrb r1, [r4, #0x10]
	lsls r1, r1, #2
	adds r1, r1, r0
	ldr r1, [r1]
	adds r0, r4, #0
	bl _call_via_r1
	adds r0, r4, #0
	bl phantom_080607e4
_0805EF82:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_0805EF88: .4byte 0x08365414

	thumb_func_start callPhantomBossModeTable
callPhantomBossModeTable: @ 0x0805EF8C
	push {lr}
	ldr r2, _0805EFA0 @ =0x08365418
	ldrb r1, [r0, #0xd]
	lsls r1, r1, #2
	adds r1, r1, r2
	ldr r1, [r1]
	bl _call_via_r1
	pop {r0}
	bx r0
	.align 2, 0
_0805EFA0: .4byte 0x08365418

	thumb_func_start phantom_0805efa4
phantom_0805efa4: @ 0x0805EFA4
	push {lr}
	ldr r2, _0805EFB8 @ =0x08365434
	ldrb r1, [r0, #0xe]
	lsls r1, r1, #2
	adds r1, r1, r2
	ldr r1, [r1]
	bl _call_via_r1
	pop {r0}
	bx r0
	.align 2, 0
_0805EFB8: .4byte 0x08365434

	thumb_func_start FUN_0805efbc
FUN_0805efbc: @ 0x0805EFBC
	push {r4, r5, lr}
	adds r4, r0, #0
	adds r0, #0x74
	ldr r1, _0805EFF4 @ =sCollisions
	bl SetDDP
	movs r5, #1
	strh r5, [r4, #0xe]
	adds r0, r4, #0
	movs r1, #0
	bl FUN_080607a0
	ldr r2, _0805EFF8 @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _0805EFFC @ =0x000343FD
	muls r0, r1, r0
	ldr r1, _0805F000 @ =0x00269EC3
	adds r0, r0, r1
	lsls r0, r0, #1
	lsrs r0, r0, #1
	str r0, [r2]
	strb r5, [r4, #0x12]
	adds r0, r4, #0
	bl FUN_0805f004
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_0805EFF4: .4byte sCollisions
_0805EFF8: .4byte RNG_0202f388
_0805EFFC: .4byte 0x000343FD
_0805F000: .4byte 0x00269EC3

	thumb_func_start FUN_0805f004
FUN_0805f004: @ 0x0805F004
	push {r4, lr}
	adds r4, r0, #0
	bl FUN_080607f0
	ldrb r0, [r4, #0x12]
	subs r3, r0, #1
	strb r3, [r4, #0x12]
	cmp r3, #0
	bne _0805F09A
	adds r0, r4, #0
	adds r0, #0xa4
	movs r1, #0
	ldrsh r0, [r0, r1]
	cmp r0, #0x2f
	bgt _0805F060
	ldr r2, _0805F044 @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _0805F048 @ =0x000343FD
	muls r0, r1, r0
	ldr r1, _0805F04C @ =0x00269EC3
	adds r0, r0, r1
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r2]
	lsrs r1, r0, #0x11
	movs r0, #0x1f
	ands r1, r0
	cmp r1, #9
	bhi _0805F050
	movs r0, #1
	b _0805F096
	.align 2, 0
_0805F044: .4byte RNG_0202f388
_0805F048: .4byte 0x000343FD
_0805F04C: .4byte 0x00269EC3
_0805F050:
	cmp r1, #0x10
	bhi _0805F058
	movs r0, #3
	b _0805F096
_0805F058:
	cmp r1, #0x17
	bls _0805F094
	movs r0, #6
	b _0805F096
_0805F060:
	ldr r2, _0805F080 @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _0805F084 @ =0x000343FD
	muls r0, r1, r0
	ldr r1, _0805F088 @ =0x00269EC3
	adds r0, r0, r1
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r2]
	lsrs r1, r0, #0x11
	movs r0, #0x1f
	ands r1, r0
	cmp r1, #0xd
	bhi _0805F08C
	movs r0, #1
	b _0805F096
	.align 2, 0
_0805F080: .4byte RNG_0202f388
_0805F084: .4byte 0x000343FD
_0805F088: .4byte 0x00269EC3
_0805F08C:
	cmp r1, #0x16
	bhi _0805F094
	movs r0, #3
	b _0805F096
_0805F094:
	movs r0, #4
_0805F096:
	strb r0, [r4, #0xd]
	strh r3, [r4, #0xe]
_0805F09A:
	pop {r4}
	pop {r0}
	bx r0

	thumb_func_start phantom_0805f0a0
phantom_0805f0a0: @ 0x0805F0A0
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #3
	beq _0805F0BC
	adds r0, r4, #0
	adds r0, #0x8c
	ldr r0, [r0]
	movs r1, #1
	ands r0, r1
	cmp r0, #0
	beq _0805F0BC
	movs r0, #3
	strh r0, [r4, #0xe]
_0805F0BC:
	ldr r1, _0805F0F0 @ =0x0836543C
	ldrb r0, [r4, #0xe]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r1, [r0]
	adds r0, r4, #0
	bl _call_via_r1
	ldrb r0, [r4, #0x13]
	subs r0, #1
	strb r0, [r4, #0x13]
	cmp r0, #0
	bne _0805F0EA
	adds r0, r4, #0
	adds r0, #0x54
	ldrb r2, [r4, #0xa]
	lsrs r2, r2, #4
	movs r1, #1
	ands r2, r1
	bl CreateParticle
	movs r0, #3
	strb r0, [r4, #0x13]
_0805F0EA:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_0805F0F0: .4byte 0x0836543C

	thumb_func_start FUN_0805f0f4
FUN_0805f0f4: @ 0x0805F0F4
	push {r4, r5, lr}
	adds r4, r0, #0
	adds r0, #0x74
	ldr r1, _0805F144 @ =sCollisions
	bl SetDDP
	movs r0, #1
	strh r0, [r4, #0xe]
	adds r0, r4, #0
	movs r1, #1
	bl FUN_080607a0
	adds r0, r4, #0
	bl FUN_08060838
	lsls r0, r0, #0x18
	lsrs r5, r0, #0x18
	movs r0, #1
	adds r1, r5, #0
	ands r1, r0
	adds r0, r4, #0
	adds r0, #0x4c
	strb r1, [r0]
	movs r0, #0x4a
	adds r0, r0, r4
	mov ip, r0
	lsls r3, r1, #4
	ldrb r2, [r0]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r3
	mov r2, ip
	strb r0, [r2]
	cmp r1, #0
	beq _0805F148
	ldrb r0, [r4, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _0805F14E
	.align 2, 0
_0805F144: .4byte sCollisions
_0805F148:
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
_0805F14E:
	strb r0, [r4, #0xa]
	lsls r1, r5, #1
	subs r1, #1
	lsls r0, r1, #4
	subs r0, r0, r1
	lsls r0, r0, #6
	str r0, [r4, #0x5c]
	adds r0, r4, #0
	adds r0, #0x54
	ldrb r2, [r4, #0xa]
	lsrs r2, r2, #4
	movs r1, #1
	ands r2, r1
	movs r1, #0
	bl CreateParticle
	movs r0, #3
	strb r0, [r4, #0x13]
	adds r0, r4, #0
	bl FUN_0805f180
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start FUN_0805f180
FUN_0805f180: @ 0x0805F180
	push {lr}
	ldr r2, _0805F194 @ =0x0836544C
	ldrb r1, [r0, #0xf]
	lsls r1, r1, #2
	adds r1, r1, r2
	ldr r1, [r1]
	bl _call_via_r1
	pop {r0}
	bx r0
	.align 2, 0
_0805F194: .4byte 0x0836544C

	thumb_func_start phantom_0805f198
phantom_0805f198: @ 0x0805F198
	push {r4, r5, r6, lr}
	adds r5, r0, #0
	ldr r1, [r5, #0x5c]
	bl FUN_08060864
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _0805F208
	ldrb r4, [r5, #0xa]
	lsrs r4, r4, #4
	movs r6, #1
	ands r4, r6
	adds r0, r5, #0
	bl FUN_08060838
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r4, r0
	bne _0805F208
	ldr r4, _0805F1F8 @ =pZero2
	ldr r0, [r4]
	ldr r0, [r0, #0x54]
	ldr r2, [r5, #0x54]
	subs r1, r0, r2
	ldr r0, _0805F1FC @ =0x000040C0
	adds r1, r1, r0
	ldr r0, _0805F200 @ =0x00008180
	cmp r1, r0
	bhi _0805F20C
	ldr r1, [r5, #0x58]
	adds r0, r2, #0
	bl FUN_08009f6c
	ldr r1, [r4]
	ldr r1, [r1, #0x58]
	subs r1, r0, r1
	ldr r0, _0805F204 @ =0x000013FF
	cmp r1, r0
	bgt _0805F20C
	movs r0, #0xfb
	bl PlaySound
	strb r6, [r5, #0xf]
	adds r0, r5, #0
	movs r1, #7
	bl FUN_080607a0
	b _0805F20C
	.align 2, 0
_0805F1F8: .4byte pZero2
_0805F1FC: .4byte 0x000040C0
_0805F200: .4byte 0x00008180
_0805F204: .4byte 0x000013FF
_0805F208:
	movs r0, #2
	strh r0, [r5, #0xe]
_0805F20C:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start FUN_0805f214
FUN_0805f214: @ 0x0805F214
	push {r4, r5, lr}
	adds r4, r0, #0
	adds r5, r4, #0
	adds r5, #0x71
	movs r0, #0
	ldrsb r0, [r5, r0]
	cmp r0, #2
	bne _0805F22E
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _0805F264 @ =0x08365320
	bl SetDDP
_0805F22E:
	movs r0, #0
	ldrsb r0, [r5, r0]
	cmp r0, #3
	bne _0805F240
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _0805F268 @ =sCollisions
	bl SetDDP
_0805F240:
	ldr r1, [r4, #0x5c]
	adds r0, r4, #0
	bl FUN_08060864
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _0805F25E
	movs r0, #2
	strh r0, [r4, #0xe]
	adds r0, r4, #0
	movs r1, #1
	bl FUN_080607a0
_0805F25E:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_0805F264: .4byte 0x08365320
_0805F268: .4byte sCollisions

	thumb_func_start FUN_0805f26c
FUN_0805f26c: @ 0x0805F26C
	push {lr}
	ldr r2, _0805F280 @ =0x08365454
	ldrb r1, [r0, #0xf]
	lsls r1, r1, #2
	adds r1, r1, r2
	ldr r1, [r1]
	bl _call_via_r1
	pop {r0}
	bx r0
	.align 2, 0
_0805F280: .4byte 0x08365454

	thumb_func_start FUN_0805f284
FUN_0805f284: @ 0x0805F284
	push {r4, lr}
	adds r4, r0, #0
	adds r0, #0x74
	ldr r1, _0805F2C8 @ =sCollisions
	bl SetDDP
	movs r0, #1
	strb r0, [r4, #0xf]
	ldr r0, [r4, #0x5c]
	movs r1, #0xf0
	lsls r1, r1, #2
	bl __divsi3
	str r0, [r4, #0x5c]
	ldr r1, _0805F2CC @ =0x00006CC0
	muls r0, r1, r0
	movs r1, #0x1e
	bl __divsi3
	adds r1, r0, #0
	adds r0, r4, #0
	bl FUN_08060864
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _0805F2D0
	adds r0, r4, #0
	movs r1, #2
	movs r2, #0
	movs r3, #2
	bl FUN_080607bc
	b _0805F2D8
	.align 2, 0
_0805F2C8: .4byte sCollisions
_0805F2CC: .4byte 0x00006CC0
_0805F2D0:
	adds r0, r4, #0
	movs r1, #2
	bl FUN_080607a0
_0805F2D8:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start FUN_0805f2e0
FUN_0805f2e0: @ 0x0805F2E0
	push {r4, lr}
	adds r4, r0, #0
	adds r0, #0x71
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	cmp r0, #0
	bne _0805F320
	adds r0, r4, #0
	adds r0, #0x72
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	subs r0, #2
	cmp r0, #0
	ble _0805F330
	lsls r1, r0, #5
	ldr r0, [r4, #0x5c]
	muls r1, r0, r1
	adds r0, r4, #0
	bl FUN_08060864
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _0805F330
	adds r0, r4, #0
	movs r1, #2
	movs r2, #0
	movs r3, #1
	bl FUN_080607bc
	b _0805F330
_0805F320:
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #2
	bne _0805F330
	movs r0, #0
	strb r0, [r4, #0xd]
	strh r0, [r4, #0xe]
_0805F330:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start FUN_0805f338
FUN_0805f338: @ 0x0805F338
	push {lr}
	ldr r2, _0805F34C @ =0x0836545C
	ldrb r1, [r0, #0xf]
	lsls r1, r1, #2
	adds r1, r1, r2
	ldr r1, [r1]
	bl _call_via_r1
	pop {r0}
	bx r0
	.align 2, 0
_0805F34C: .4byte 0x0836545C

	thumb_func_start FUN_0805f350
FUN_0805f350: @ 0x0805F350
	push {r4, lr}
	adds r4, r0, #0
	adds r0, #0x74
	ldr r1, _0805F390 @ =sCollisions
	bl SetDDP
	movs r2, #0xc0
	lsls r2, r2, #2
	str r2, [r4, #0x5c]
	adds r0, r4, #0
	adds r0, #0xcb
	ldrb r1, [r0]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #9
	subs r2, r2, r0
	str r2, [r4, #0x5c]
	ldrb r1, [r4, #0xa]
	movs r0, #1
	orrs r0, r1
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	movs r1, #0x11
	bl FUN_080607a0
	movs r0, #0x1e
	strb r0, [r4, #0x12]
	movs r0, #1
	strb r0, [r4, #0xf]
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_0805F390: .4byte sCollisions

	thumb_func_start FUN_0805f394
FUN_0805f394: @ 0x0805F394
	push {r4, r5, lr}
	adds r4, r0, #0
	ldr r1, [r4, #0x5c]
	bl FUN_08060864
	ldr r1, [r4, #0x5c]
	movs r0, #0xe6
	muls r0, r1, r0
	cmp r0, #0
	bge _0805F3AA
	adds r0, #0xff
_0805F3AA:
	asrs r0, r0, #8
	str r0, [r4, #0x5c]
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	lsrs r5, r0, #0x18
	cmp r5, #0
	bne _0805F3C8
	adds r0, r4, #0
	movs r1, #0x12
	bl FUN_080607a0
	strb r5, [r4, #0xd]
	strh r5, [r4, #0xe]
_0805F3C8:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start FUN_0805f3d0
FUN_0805f3d0: @ 0x0805F3D0
	push {lr}
	ldr r2, _0805F3E4 @ =0x08365464
	ldrb r1, [r0, #0xe]
	lsls r1, r1, #2
	adds r1, r1, r2
	ldr r1, [r1]
	bl _call_via_r1
	pop {r0}
	bx r0
	.align 2, 0
_0805F3E4: .4byte 0x08365464

	thumb_func_start FUN_0805f3e8
FUN_0805f3e8: @ 0x0805F3E8
	push {r4, lr}
	adds r4, r0, #0
	movs r0, #1
	strh r0, [r4, #0xe]
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _0805F420 @ =sCollisions
	bl SetDDP
	adds r0, r4, #0
	bl FUN_080608c8
	ldr r2, _0805F424 @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _0805F428 @ =0x000343FD
	muls r0, r1, r0
	ldr r1, _0805F42C @ =0x00269EC3
	adds r0, r0, r1
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r2]
	lsrs r0, r0, #0x11
	movs r1, #6
	ands r0, r1
	cmp r0, #0
	beq _0805F434
	ldr r0, _0805F430 @ =0xFFFFFA40
	b _0805F436
	.align 2, 0
_0805F420: .4byte sCollisions
_0805F424: .4byte RNG_0202f388
_0805F428: .4byte 0x000343FD
_0805F42C: .4byte 0x00269EC3
_0805F430: .4byte 0xFFFFFA40
_0805F434:
	ldr r0, _0805F440 @ =0xFFFFF940
_0805F436:
	str r0, [r4, #0x60]
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_0805F440: .4byte 0xFFFFF940

	thumb_func_start FUN_0805f444
FUN_0805f444: @ 0x0805F444
	push {r4, lr}
	adds r4, r0, #0
	bl FUN_080608e0
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _0805F45C
	movs r0, #2
	strh r0, [r4, #0xe]
	adds r0, r4, #0
	bl FUN_0805f464
_0805F45C:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start FUN_0805f464
FUN_0805f464: @ 0x0805F464
	push {r4, lr}
	adds r4, r0, #0
	bl FUN_08060924
	ldr r0, [r4, #0x60]
	cmp r0, #0
	ble _0805F482
	movs r0, #4
	strh r0, [r4, #0xe]
	adds r0, r4, #0
	movs r1, #8
	bl FUN_080607a0
	movs r0, #0
	strb r0, [r4, #0x12]
_0805F482:
	pop {r4}
	pop {r0}
	bx r0

	thumb_func_start FUN_0805f488
FUN_0805f488: @ 0x0805F488
	push {r4, lr}
	adds r4, r0, #0
	bl FUN_08060974
	lsls r0, r0, #0x18
	cmp r0, #0
	bge _0805F49C
	movs r0, #0
	strb r0, [r4, #0xd]
	strh r0, [r4, #0xe]
_0805F49C:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start FUN_0805f4a4
FUN_0805f4a4: @ 0x0805F4A4
	push {r4, r5, lr}
	sub sp, #8
	adds r5, r0, #0
	ldrb r0, [r5, #0x12]
	adds r0, #1
	strb r0, [r5, #0x12]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0x14
	bne _0805F508
	ldr r3, [r5, #0x54]
	str r3, [sp]
	ldr r2, [r5, #0x58]
	str r2, [sp, #4]
	ldr r0, _0805F4EC @ =pZero2
	ldr r1, [r0]
	ldr r0, [r1, #0x54]
	ldr r1, [r1, #0x58]
	subs r0, r0, r3
	subs r1, r1, r2
	ldr r2, _0805F4F0 @ =0xFFFFE800
	adds r1, r1, r2
	lsls r0, r0, #8
	asrs r0, r0, #0x10
	lsls r1, r1, #8
	asrs r1, r1, #0x10
	bl ArcTan2
	lsls r0, r0, #0x10
	lsrs r4, r0, #0x18
	cmp r4, #0x80
	bls _0805F4F6
	cmp r4, #0xc0
	bls _0805F4F4
	movs r4, #0
	b _0805F4F6
	.align 2, 0
_0805F4EC: .4byte pZero2
_0805F4F0: .4byte 0xFFFFE800
_0805F4F4:
	movs r4, #0x80
_0805F4F6:
	movs r0, #0xfc
	bl PlaySound
	movs r1, #0xc0
	lsls r1, r1, #2
	mov r0, sp
	adds r2, r4, #0
	bl FUN_080afcec
_0805F508:
	adds r0, r5, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _0805F522
	adds r0, r5, #0
	movs r1, #3
	movs r2, #2
	movs r3, #1
	bl FUN_080607bc
	movs r0, #5
	strh r0, [r5, #0xe]
_0805F522:
	add sp, #8
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start FUN_0805f52c
FUN_0805f52c:
	.byte 0x10, 0xB5, 0x04, 0x1C
	.byte 0x01, 0xF0, 0xF8, 0xF9, 0x00, 0x06, 0x00, 0x28, 0x05, 0xD0, 0x03, 0x20, 0xE0, 0x81, 0x20, 0x1C
	.byte 0x04, 0x21, 0x01, 0xF0, 0x2D, 0xF9, 0x10, 0xBC, 0x01, 0xBC, 0x00, 0x47

	thumb_func_start FUN_0805f54c
FUN_0805f54c: @ 0x0805F54C
	push {lr}
	ldr r2, _0805F560 @ =0x0836547C
	ldrb r1, [r0, #0xe]
	lsls r1, r1, #2
	adds r1, r1, r2
	ldr r1, [r1]
	bl _call_via_r1
	pop {r0}
	bx r0
	.align 2, 0
_0805F560: .4byte 0x0836547C

	thumb_func_start FUN_0805f564
FUN_0805f564: @ 0x0805F564
	push {lr}
	ldr r2, _0805F578 @ =0x08365494
	ldrb r1, [r0, #0xf]
	lsls r1, r1, #2
	adds r1, r1, r2
	ldr r1, [r1]
	bl _call_via_r1
	pop {r0}
	bx r0
	.align 2, 0
_0805F578: .4byte 0x08365494

	thumb_func_start FUN_0805f57c
FUN_0805f57c: @ 0x0805F57C
	push {r4, lr}
	adds r4, r0, #0
	adds r0, #0x74
	ldr r1, _0805F5A4 @ =sCollisions
	bl SetDDP
	movs r0, #1
	strb r0, [r4, #0xf]
	adds r0, r4, #0
	bl FUN_080608c8
	adds r0, r4, #0
	movs r1, #0
	bl FUN_080afbb0
	str r0, [r4, #0x2c]
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_0805F5A4: .4byte sCollisions

	thumb_func_start FUN_0805f5a8
FUN_0805f5a8: @ 0x0805F5A8
	push {r4, lr}
	adds r4, r0, #0
	bl FUN_080608e0
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _0805F626
	movs r0, #2
	strb r0, [r4, #0xf]
	ldr r0, _0805F5DC @ =pZero2
	ldr r0, [r0]
	ldr r1, [r0, #0x54]
	adds r0, r4, #0
	adds r0, #0xe0
	ldr r0, [r0]
	cmp r1, r0
	bne _0805F5F2
	ldr r2, [r4, #0x54]
	cmp r2, r1
	ble _0805F5E4
	adds r0, r4, #0
	adds r0, #0xd8
	ldr r0, [r0]
	ldr r1, _0805F5E0 @ =0xFFFFE800
	adds r0, r0, r1
	b _0805F612
	.align 2, 0
_0805F5DC: .4byte pZero2
_0805F5E0: .4byte 0xFFFFE800
_0805F5E4:
	adds r0, r4, #0
	adds r0, #0xd4
	ldr r0, [r0]
	movs r1, #0xc0
	lsls r1, r1, #5
	adds r0, r0, r1
	b _0805F612
_0805F5F2:
	cmp r1, r0
	bge _0805F604
	adds r0, r4, #0
	adds r0, #0xd8
	ldr r0, [r0]
	ldr r1, _0805F600 @ =0xFFFFE800
	b _0805F60E
	.align 2, 0
_0805F600: .4byte 0xFFFFE800
_0805F604:
	adds r0, r4, #0
	adds r0, #0xd4
	ldr r0, [r0]
	movs r1, #0xc0
	lsls r1, r1, #5
_0805F60E:
	adds r0, r0, r1
	ldr r2, [r4, #0x54]
_0805F612:
	subs r0, r0, r2
	movs r1, #0x2e
	bl __divsi3
	str r0, [r4, #0x5c]
	ldr r0, _0805F62C @ =0xFFFFFA40
	str r0, [r4, #0x60]
	adds r0, r4, #0
	bl FUN_0805f630
_0805F626:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_0805F62C: .4byte 0xFFFFFA40

	thumb_func_start FUN_0805f630
FUN_0805f630: @ 0x0805F630
	push {r4, lr}
	adds r4, r0, #0
	adds r0, #0x74
	ldr r1, _0805F65C @ =0x083653E0
	bl SetDDP
	ldr r1, [r4, #0x5c]
	adds r0, r4, #0
	bl FUN_08060864
	adds r0, r4, #0
	bl FUN_08060924
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _0805F654
	movs r0, #3
	strb r0, [r4, #0xf]
_0805F654:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_0805F65C: .4byte 0x083653E0

	thumb_func_start FUN_0805f660
FUN_0805f660: @ 0x0805F660
	push {r4, r5, lr}
	adds r5, r0, #0
	adds r0, #0x74
	ldr r1, _0805F68C @ =sCollisions
	bl SetDDP
	adds r0, r5, #0
	bl FUN_08060974
	lsls r0, r0, #0x18
	cmp r0, #0
	ble _0805F686
	movs r4, #4
	strb r4, [r5, #0xf]
	adds r0, r5, #0
	movs r1, #0
	bl FUN_080607a0
	strb r4, [r5, #0x12]
_0805F686:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_0805F68C: .4byte sCollisions

	thumb_func_start FUN_0805f690
FUN_0805f690: @ 0x0805F690
	push {lr}
	adds r1, r0, #0
	ldrb r0, [r1, #0x12]
	subs r0, #1
	strb r0, [r1, #0x12]
	cmp r0, #0
	bne _0805F6AA
	movs r0, #1
	strh r0, [r1, #0xe]
	adds r0, r1, #0
	movs r1, #5
	bl FUN_080607a0
_0805F6AA:
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start FUN_0805f6b0
FUN_0805f6b0: @ 0x0805F6B0
	push {lr}
	ldr r2, _0805F6C4 @ =0x083654A8
	ldrb r1, [r0, #0xf]
	lsls r1, r1, #2
	adds r1, r1, r2
	ldr r1, [r1]
	bl _call_via_r1
	pop {r0}
	bx r0
	.align 2, 0
_0805F6C4: .4byte 0x083654A8

	thumb_func_start FUN_0805f6c8
FUN_0805f6c8: @ 0x0805F6C8
	push {lr}
	adds r1, r0, #0
	adds r0, #0x72
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	cmp r0, #1
	bgt _0805F6DC
	movs r0, #1
	strb r0, [r1, #0xf]
_0805F6DC:
	pop {r0}
	bx r0

	thumb_func_start FUN_0805f6e0
FUN_0805f6e0: @ 0x0805F6E0
	push {lr}
	adds r1, r0, #0
	ldr r0, [r1, #0x2c]
	ldrb r0, [r0, #0xd]
	cmp r0, #1
	bne _0805F6F8
	movs r0, #2
	strb r0, [r1, #0xf]
	adds r0, r1, #0
	movs r1, #6
	bl FUN_080607a0
_0805F6F8:
	pop {r0}
	bx r0

	thumb_func_start FUN_0805f6fc
FUN_0805f6fc: @ 0x0805F6FC
	push {r4, lr}
	adds r4, r0, #0
	adds r0, #0x72
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	cmp r0, #1
	bgt _0805F716
	movs r0, #0xfc
	bl PlaySound
	movs r0, #3
	strb r0, [r4, #0xf]
_0805F716:
	pop {r4}
	pop {r0}
	bx r0

	thumb_func_start FUN_0805f71c
FUN_0805f71c: @ 0x0805F71C
	push {lr}
	adds r1, r0, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _0805F734
	movs r0, #2
	strh r0, [r1, #0xe]
	adds r0, r1, #0
	movs r1, #0
	bl FUN_080607a0
_0805F734:
	pop {r0}
	bx r0

	thumb_func_start FUN_0805f738
FUN_0805f738: @ 0x0805F738
	push {r4, lr}
	adds r4, r0, #0
	bl FUN_080609a4
	lsls r0, r0, #0x18
	asrs r1, r0, #0x18
	cmp r1, #0
	ble _0805F764
	movs r0, #3
	strh r0, [r4, #0xe]
	adds r0, r4, #0
	adds r0, #0xb7
	strb r1, [r0]
	adds r1, #0x12
	lsls r1, r1, #0x18
	asrs r1, r1, #0x18
	adds r0, r4, #0
	bl FUN_08060a48
	adds r0, r4, #0
	bl FUN_0805f76c
_0805F764:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start FUN_0805f76c
FUN_0805f76c: @ 0x0805F76C
	push {lr}
	ldr r2, _0805F780 @ =0x083654B8
	ldrb r1, [r0, #0xf]
	lsls r1, r1, #2
	adds r1, r1, r2
	ldr r1, [r1]
	bl _call_via_r1
	pop {r0}
	bx r0
	.align 2, 0
_0805F780: .4byte 0x083654B8

	thumb_func_start FUN_0805f784
FUN_0805f784: @ 0x0805F784
	push {lr}
	movs r1, #1
	strb r1, [r0, #0xf]
	bl FUN_080608c8
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start FUN_0805f794
FUN_0805f794: @ 0x0805F794
	push {r4, lr}
	adds r4, r0, #0
	bl FUN_080608e0
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _0805F7CA
	movs r2, #0
	movs r0, #2
	strb r0, [r4, #0xf]
	adds r3, r4, #0
	adds r3, #0xb7
	ldrb r1, [r3]
	adds r0, r1, #1
	lsls r0, r0, #6
	rsbs r0, r0, #0
	str r0, [r4, #0x60]
	adds r1, #8
	strb r1, [r3]
	adds r1, r4, #0
	adds r1, #0xb8
	ldr r0, [r4, #0x54]
	str r0, [r1]
	strb r2, [r4, #0x12]
	adds r0, r4, #0
	bl FUN_0805f7d0
_0805F7CA:
	pop {r4}
	pop {r0}
	bx r0

	thumb_func_start FUN_0805f7d0
FUN_0805f7d0: @ 0x0805F7D0
	push {r4, r5, lr}
	adds r5, r0, #0
	ldrb r1, [r5, #0x12]
	adds r1, #1
	strb r1, [r5, #0x12]
	adds r0, #0xbc
	adds r2, r5, #0
	adds r2, #0xb8
	ldr r0, [r0]
	ldr r4, [r2]
	subs r0, r0, r4
	muls r0, r1, r0
	adds r1, r5, #0
	adds r1, #0xb7
	ldrb r1, [r1]
	bl __divsi3
	adds r4, r4, r0
	str r4, [r5, #0x54]
	adds r0, r5, #0
	bl FUN_08060924
	ldr r0, [r5, #0x60]
	cmp r0, #0
	ble _0805F818
	ldr r0, [r5, #0x2c]
	ldr r0, [r0, #0x58]
	subs r0, #0x80
	ldr r1, [r5, #0x58]
	cmp r1, r0
	blt _0805F818
	movs r0, #4
	strh r0, [r5, #0xe]
	adds r0, r5, #0
	bl FUN_0805f820
_0805F818:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start FUN_0805f820
FUN_0805f820: @ 0x0805F820
	push {lr}
	ldr r2, _0805F834 @ =0x083654C4
	ldrb r1, [r0, #0xf]
	lsls r1, r1, #2
	adds r1, r1, r2
	ldr r1, [r1]
	bl _call_via_r1
	pop {r0}
	bx r0
	.align 2, 0
_0805F834: .4byte 0x083654C4

	thumb_func_start FUN_0805f838
FUN_0805f838: @ 0x0805F838
	push {r4, lr}
	adds r4, r0, #0
	adds r0, #0x74
	ldr r1, _0805F858 @ =0x083653E0
	bl SetDDP
	movs r0, #1
	strb r0, [r4, #0xf]
	adds r0, r4, #0
	movs r1, #9
	bl FUN_080607a0
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_0805F858: .4byte 0x083653E0

	thumb_func_start FUN_0805f85c
FUN_0805f85c: @ 0x0805F85C
	push {lr}
	adds r1, r0, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _0805F86C
	movs r0, #2
	strb r0, [r1, #0xf]
_0805F86C:
	pop {r0}
	bx r0

	thumb_func_start FUN_0805f870
FUN_0805f870: @ 0x0805F870
	push {r4, r5, lr}
	adds r5, r0, #0
	ldr r1, _0805F89C @ =gStageRun+232
	ldr r0, [r5, #0x58]
	movs r2, #0xa0
	lsls r2, r2, #7
	adds r0, r0, r2
	ldr r1, [r1, #0x3c]
	subs r1, r1, r0
	ldr r0, _0805F8A0 @ =0xFFFFD000
	cmp r1, r0
	bge _0805F8A4
	movs r4, #0
	movs r0, #3
	strb r0, [r5, #0xf]
	adds r0, r5, #0
	movs r1, #0xa
	bl FUN_080607a0
	strb r4, [r5, #0x12]
	b _0805F8B8
	.align 2, 0
_0805F89C: .4byte gStageRun+232
_0805F8A0: .4byte 0xFFFFD000
_0805F8A4:
	ldr r0, _0805F8C0 @ =0xFFFFE000
	cmp r1, r0
	ble _0805F8B8
	movs r0, #5
	strh r0, [r5, #0xe]
	movs r0, #0
	str r0, [r5, #0x2c]
	adds r0, r5, #0
	bl FUN_0805f934
_0805F8B8:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_0805F8C0: .4byte 0xFFFFE000

	thumb_func_start FUN_0805f8c4
FUN_0805f8c4: @ 0x0805F8C4
	push {r4, r5, lr}
	sub sp, #8
	adds r5, r0, #0
	ldrb r0, [r5, #0x12]
	adds r0, #1
	strb r0, [r5, #0x12]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0xf
	bne _0805F91A
	ldr r0, [r5, #0x54]
	str r0, [sp]
	ldr r0, [r5, #0x58]
	str r0, [sp, #4]
	movs r0, #0xfc
	bl PlaySound
	movs r4, #0xf0
	lsls r4, r4, #2
	mov r0, sp
	adds r1, r4, #0
	movs r2, #0x10
	movs r3, #1
	bl FUN_080afbfc
	mov r0, sp
	adds r1, r4, #0
	movs r2, #0x30
	movs r3, #1
	bl FUN_080afbfc
	mov r0, sp
	adds r1, r4, #0
	movs r2, #0x50
	movs r3, #1
	bl FUN_080afbfc
	mov r0, sp
	adds r1, r4, #0
	movs r2, #0x70
	movs r3, #1
	bl FUN_080afbfc
_0805F91A:
	adds r0, r5, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _0805F928
	movs r0, #2
	strb r0, [r5, #0xf]
_0805F928:
	add sp, #8
	pop {r4, r5}
	pop {r0}
	bx r0
