	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_0807d178
FUN_0807d178: @ 0x0807D178
	push {r4, r5, r6, lr}
	adds r6, r0, #0
	ldrb r0, [r6, #0xe]
	cmp r0, #0
	beq _0807D188
	cmp r0, #1
	beq _0807D244
	b _0807D2A2
_0807D188:
	adds r0, r6, #0
	adds r0, #0x74
	ldr r1, _0807D1B0 @ =0x08367BE4
	bl SetDDP
	ldrb r0, [r6, #0x11]
	cmp r0, #1
	bhi _0807D1F0
	ldr r1, _0807D1B4 @ =0x00004313
	adds r0, r6, #0
	bl SetMotion
	ldrb r2, [r6, #0x11]
	cmp r2, #0
	beq _0807D1B8
	ldrb r1, [r6, #0xa]
	movs r0, #0x10
	orrs r0, r1
	b _0807D1BE
	.align 2, 0
_0807D1B0: .4byte 0x08367BE4
_0807D1B4: .4byte 0x00004313
_0807D1B8:
	ldrb r1, [r6, #0xa]
	movs r0, #0xef
	ands r0, r1
_0807D1BE:
	strb r0, [r6, #0xa]
	movs r1, #1
	ands r1, r2
	adds r0, r6, #0
	adds r0, #0x4c
	movs r3, #0
	strb r1, [r0]
	adds r4, r6, #0
	adds r4, #0x4a
	lsls r1, r1, #4
	ldrb r2, [r4]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r1
	strb r0, [r4]
	ldrb r0, [r6, #0x11]
	lsls r0, r0, #0xa
	ldr r1, _0807D1EC @ =0xFFFFFE00
	adds r0, r0, r1
	str r0, [r6, #0x5c]
	str r3, [r6, #0x60]
	b _0807D23E
	.align 2, 0
_0807D1EC: .4byte 0xFFFFFE00
_0807D1F0:
	movs r2, #1
	ands r2, r0
	cmp r2, #0
	beq _0807D200
	ldrb r1, [r6, #0xa]
	movs r0, #0x20
	orrs r0, r1
	b _0807D206
_0807D200:
	ldrb r1, [r6, #0xa]
	movs r0, #0xdf
	ands r0, r1
_0807D206:
	strb r0, [r6, #0xa]
	movs r4, #1
	adds r1, r4, #0
	ands r1, r2
	adds r0, r6, #0
	adds r0, #0x4d
	movs r5, #0
	strb r1, [r0]
	adds r3, r6, #0
	adds r3, #0x4a
	lsls r1, r1, #5
	ldrb r2, [r3]
	movs r0, #0x21
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r1
	strb r0, [r3]
	ldr r1, _0807D2A8 @ =0x00004312
	adds r0, r6, #0
	bl SetMotion
	str r5, [r6, #0x5c]
	ldrb r0, [r6, #0x11]
	ands r4, r0
	lsls r4, r4, #0xa
	ldr r0, _0807D2AC @ =0xFFFFFE00
	adds r4, r4, r0
	str r4, [r6, #0x60]
_0807D23E:
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_0807D244:
	ldr r0, [r6, #0x54]
	ldr r1, [r6, #0x5c]
	adds r0, r0, r1
	str r0, [r6, #0x54]
	ldr r0, [r6, #0x58]
	ldr r1, [r6, #0x60]
	adds r0, r0, r1
	str r0, [r6, #0x58]
	adds r0, r6, #0
	bl UpdateMotionGraphic
	ldr r0, _0807D2B0 @ =gStageRun+232
	adds r1, r6, #0
	adds r1, #0x54
	bl CalcFromCamera
	movs r1, #0x80
	lsls r1, r1, #5
	cmp r0, r1
	bls _0807D2A2
	ldrb r1, [r6, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r2, #0
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r6, #0xa]
	adds r0, r6, #0
	adds r0, #0x8c
	str r2, [r0]
	adds r0, #4
	str r2, [r0]
	adds r0, #4
	strb r2, [r0]
	ldrb r1, [r6, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r6, #0xa]
	ldr r1, _0807D2B4 @ =gEnemyFnTable
	ldrb r0, [r6, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r6, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r6, #0x14]
_0807D2A2:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_0807D2A8: .4byte 0x00004312
_0807D2AC: .4byte 0xFFFFFE00
_0807D2B0: .4byte gStageRun+232
_0807D2B4: .4byte gEnemyFnTable

	thumb_func_start FUN_0807d2b8
FUN_0807d2b8: @ 0x0807D2B8
	push {r4, r5, lr}
	adds r5, r0, #0
	ldrb r0, [r5, #0xe]
	cmp r0, #0
	beq _0807D2C8
	cmp r0, #1
	beq _0807D37A
	b _0807D3D8
_0807D2C8:
	adds r0, r5, #0
	adds r0, #0x74
	ldr r1, _0807D314 @ =0x08367BE4
	bl SetDDP
	ldr r1, _0807D318 @ =0x00004314
	adds r0, r5, #0
	bl SetMotion
	ldr r4, _0807D31C @ =0xFFFFFEA0
	ldrb r1, [r5, #0x11]
	movs r3, #1
	movs r2, #1
	ands r2, r1
	lsls r0, r2, #1
	adds r0, r0, r2
	lsls r0, r0, #2
	subs r0, r0, r2
	lsls r0, r0, #6
	adds r0, r0, r4
	str r0, [r5, #0x5c]
	lsls r1, r1, #0x18
	lsrs r1, r1, #0x19
	ands r1, r3
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	subs r0, r0, r1
	lsls r0, r0, #6
	adds r0, r0, r4
	str r0, [r5, #0x60]
	cmp r2, #0
	beq _0807D320
	ldrb r1, [r5, #0xa]
	movs r0, #0x10
	orrs r0, r1
	b _0807D326
	.align 2, 0
_0807D314: .4byte 0x08367BE4
_0807D318: .4byte 0x00004314
_0807D31C: .4byte 0xFFFFFEA0
_0807D320:
	ldrb r1, [r5, #0xa]
	movs r0, #0xef
	ands r0, r1
_0807D326:
	strb r0, [r5, #0xa]
	movs r4, #1
	adds r1, r2, #0
	adds r0, r5, #0
	adds r0, #0x4c
	strb r1, [r0]
	adds r3, r5, #0
	adds r3, #0x4a
	lsls r1, r1, #4
	ldrb r2, [r3]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r1
	strb r0, [r3]
	ldrb r0, [r5, #0x11]
	lsrs r2, r0, #1
	ands r2, r4
	cmp r2, #0
	beq _0807D356
	ldrb r0, [r5, #0xa]
	movs r1, #0x20
	orrs r0, r1
	b _0807D35C
_0807D356:
	ldrb r1, [r5, #0xa]
	movs r0, #0xdf
	ands r0, r1
_0807D35C:
	strb r0, [r5, #0xa]
	adds r1, r2, #0
	adds r2, r5, #0
	adds r2, #0x4d
	strb r1, [r2]
	lsls r1, r1, #5
	ldrb r2, [r3]
	movs r0, #0x21
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r1
	strb r0, [r3]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_0807D37A:
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x5c]
	adds r0, r0, r1
	str r0, [r5, #0x54]
	ldr r0, [r5, #0x58]
	ldr r1, [r5, #0x60]
	adds r0, r0, r1
	str r0, [r5, #0x58]
	adds r0, r5, #0
	bl UpdateMotionGraphic
	ldr r0, _0807D3E0 @ =gStageRun+232
	adds r1, r5, #0
	adds r1, #0x54
	bl CalcFromCamera
	movs r1, #0x80
	lsls r1, r1, #5
	cmp r0, r1
	bls _0807D3D8
	ldrb r1, [r5, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r2, #0
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r5, #0xa]
	adds r0, r5, #0
	adds r0, #0x8c
	str r2, [r0]
	adds r0, #4
	str r2, [r0]
	adds r0, #4
	strb r2, [r0]
	ldrb r1, [r5, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r5, #0xa]
	ldr r1, _0807D3E4 @ =gEnemyFnTable
	ldrb r0, [r5, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r5, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r5, #0x14]
_0807D3D8:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_0807D3E0: .4byte gStageRun+232
_0807D3E4: .4byte gEnemyFnTable
