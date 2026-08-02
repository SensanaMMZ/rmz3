	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_080defa8
FUN_080defa8: @ 0x080DEFA8
	push {r4, r5, r6, r7, lr}
	adds r5, r0, #0
	ldrb r6, [r5, #0xd]
	cmp r6, #0
	beq _080DEFB8
	cmp r6, #1
	beq _080DF032
	b _080DF158
_080DEFB8:
	ldr r0, _080DF08C @ =gStageRun+232
	adds r7, r5, #0
	adds r7, #0x54
	adds r1, r7, #0
	bl CalcFromCamera
	movs r1, #0x80
	lsls r1, r1, #5
	cmp r0, r1
	bls _080DEFCE
	b _080DF158
_080DEFCE:
	ldrb r1, [r5, #0xa]
	movs r0, #1
	orrs r0, r1
	strb r0, [r5, #0xa]
	adds r0, r5, #0
	bl InitNonAffineMotion
	ldr r1, [r5, #0x64]
	ldr r3, _080DF090 @ =gOverworld
	ldrb r0, [r5, #0x11]
	movs r2, #3
	ands r2, r0
	lsrs r0, r0, #2
	adds r0, #4
	lsls r0, r0, #2
	adds r2, r2, r0
	ldr r0, _080DF094 @ =0x0002D028
	adds r3, r3, r0
	adds r2, r2, r3
	ldrb r0, [r2]
	lsls r0, r0, #1
	adds r1, r1, r0
	lsls r1, r1, #0x10
	lsrs r1, r1, #0x10
	adds r0, r5, #0
	bl SetMotion
	ldrb r1, [r5, #0xa]
	movs r0, #4
	orrs r0, r1
	strb r0, [r5, #0xa]
	adds r4, r5, #0
	adds r4, #0x74
	ldr r1, _080DF098 @ =0x08371804
	adds r0, r4, #0
	adds r2, r7, #0
	movs r3, #0
	bl InitBody
	str r5, [r4, #0x2c]
	str r6, [r4, #0x24]
	ldrb r1, [r5, #0xb]
	movs r0, #0xef
	ands r0, r1
	strb r0, [r5, #0xb]
	ldrb r0, [r5, #0x1c]
	strb r0, [r5, #0x1d]
	ldrb r0, [r5, #0xd]
	adds r0, #1
	strb r0, [r5, #0xd]
_080DF032:
	adds r0, r5, #0
	bl UpdateMotionGraphic
	adds r0, r5, #0
	adds r0, #0x8c
	ldr r1, [r0]
	movs r2, #4
	ands r1, r2
	adds r4, r0, #0
	cmp r1, #0
	bne _080DF070
	ldr r0, [r5, #0x54]
	ldr r1, _080DF09C @ =0xFFFFFC00
	adds r0, r0, r1
	ldr r1, [r5, #0x58]
	bl PushoutToUp1
	cmp r0, #0
	bne _080DF070
	ldrb r0, [r5, #0x11]
	cmp r0, #4
	beq _080DF0A0
	ldr r0, [r5, #0x54]
	movs r3, #0x80
	lsls r3, r3, #3
	adds r0, r0, r3
	ldr r1, [r5, #0x58]
	bl PushoutToUp1
	cmp r0, #0
	beq _080DF0A0
_080DF070:
	ldr r2, _080DF090 @ =gOverworld
	ldrb r0, [r5, #0x11]
	movs r1, #3
	ands r1, r0
	lsrs r0, r0, #2
	adds r0, #4
	lsls r0, r0, #2
	adds r1, r1, r0
	ldr r3, _080DF094 @ =0x0002D028
	adds r0, r2, r3
	adds r1, r1, r0
	movs r0, #1
	b _080DF0B8
	.align 2, 0
_080DF08C: .4byte gStageRun+232
_080DF090: .4byte gOverworld
_080DF094: .4byte 0x0002D028
_080DF098: .4byte 0x08371804
_080DF09C: .4byte 0xFFFFFC00
_080DF0A0:
	ldr r2, _080DF0FC @ =gOverworld
	ldrb r0, [r5, #0x11]
	movs r1, #3
	ands r1, r0
	lsrs r0, r0, #2
	adds r0, #4
	lsls r0, r0, #2
	adds r1, r1, r0
	ldr r3, _080DF100 @ =0x0002D028
	adds r0, r2, r3
	adds r1, r1, r0
	movs r0, #0
_080DF0B8:
	strb r0, [r1]
	ldrb r0, [r5, #0x11]
	movs r1, #3
	ands r1, r0
	lsrs r0, r0, #2
	adds r0, #4
	lsls r0, r0, #2
	adds r1, r1, r0
	ldr r3, _080DF100 @ =0x0002D028
	adds r0, r2, r3
	adds r1, r1, r0
	ldrb r0, [r1]
	cmp r0, #0
	beq _080DF104
	ldrb r0, [r5, #0x1e]
	lsls r2, r0, #8
	adds r0, r5, #0
	adds r0, #0x70
	ldrb r0, [r0]
	orrs r2, r0
	ldr r0, [r5, #0x64]
	adds r1, r0, #1
	cmp r2, r1
	beq _080DF126
	adds r0, #2
	cmp r2, r0
	beq _080DF126
	lsls r1, r1, #0x10
	lsrs r1, r1, #0x10
	adds r0, r5, #0
	bl SetMotion
	b _080DF126
	.align 2, 0
_080DF0FC: .4byte gOverworld
_080DF100: .4byte 0x0002D028
_080DF104:
	ldrb r0, [r5, #0x1e]
	lsls r2, r0, #8
	adds r0, r5, #0
	adds r0, #0x70
	ldrb r0, [r0]
	orrs r2, r0
	ldr r1, [r5, #0x64]
	cmp r2, r1
	beq _080DF126
	adds r1, #3
	cmp r2, r1
	beq _080DF126
	lsls r1, r1, #0x10
	lsrs r1, r1, #0x10
	adds r0, r5, #0
	bl SetMotion
_080DF126:
	ldr r0, _080DF160 @ =gStageRun+232
	adds r1, r5, #0
	adds r1, #0x54
	bl CalcFromCamera
	movs r1, #0x80
	lsls r1, r1, #5
	cmp r0, r1
	bls _080DF158
	ldrb r1, [r5, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r2, #0
	strb r0, [r5, #0xa]
	str r2, [r4]
	adds r0, r5, #0
	adds r0, #0x90
	str r2, [r0]
	adds r0, #4
	strb r2, [r0]
	ldrb r1, [r5, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r5, #0xa]
	strb r2, [r5, #0xd]
_080DF158:
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080DF160: .4byte gStageRun+232
