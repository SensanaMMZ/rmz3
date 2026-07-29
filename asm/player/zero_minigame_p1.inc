	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_080366fc
FUN_080366fc: @ 0x080366FC
	push {r4, r5, r6, r7, lr}
	adds r5, r0, #0
	ldrb r4, [r5, #0xe]
	cmp r4, #0
	beq _0803670C
	cmp r4, #1
	beq _0803673A
	b _0803683C
_0803670C:
	movs r1, #0x9f
	lsls r1, r1, #2
	adds r0, r5, r1
	strb r4, [r0]
	adds r1, #1
	adds r0, r5, r1
	strb r4, [r0]
	adds r0, r5, #0
	movs r1, #0
	bl SetMotion
	adds r0, r5, #0
	adds r0, #0x74
	ldr r1, _080367C8 @ =sCollisions
	bl SetDDP
	movs r1, #0xa2
	lsls r1, r1, #2
	adds r0, r5, r1
	strh r4, [r0]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_0803673A:
	movs r0, #0xa2
	lsls r0, r0, #2
	adds r3, r5, r0
	ldrh r0, [r3]
	adds r0, #1
	movs r7, #0
	strh r0, [r3]
	ldr r0, [r5, #0x28]
	movs r1, #4
	ldrsh r6, [r0, r1]
	cmp r6, #1
	bne _08036822
	ldr r4, _080367CC @ =gJoypad
	ldrh r1, [r4]
	movs r0, #0x20
	ands r0, r1
	cmp r0, #0
	beq _0803677A
	adds r0, r5, #0
	adds r0, #0x4c
	strb r7, [r0]
	adds r2, r5, #0
	adds r2, #0x4a
	ldrb r1, [r2]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r2]
	ldrb r1, [r5, #0xa]
	movs r0, #0xef
	ands r0, r1
	strb r0, [r5, #0xa]
_0803677A:
	ldrh r4, [r4]
	movs r0, #0x10
	ands r0, r4
	cmp r0, #0
	beq _0803679C
	adds r0, r5, #0
	adds r0, #0x4c
	strb r6, [r0]
	adds r2, r5, #0
	adds r2, #0x4a
	ldrb r0, [r2]
	movs r1, #0x10
	orrs r0, r1
	strb r0, [r2]
	ldrb r0, [r5, #0xa]
	orrs r1, r0
	strb r1, [r5, #0xa]
_0803679C:
	movs r0, #2
	ands r0, r4
	cmp r0, #0
	beq _08036814
	movs r1, #0x9f
	lsls r1, r1, #2
	adds r0, r5, r1
	ldrb r0, [r0]
	cmp r0, #0x27
	bhi _080367D0
	ldrh r0, [r3]
	movs r1, #0x14
	bl __umodsi3
	lsls r0, r0, #0x10
	cmp r0, #0
	bne _080367E4
	movs r0, #0x17
	bl PlaySound
	b _080367E4
	.align 2, 0
_080367C8: .4byte sCollisions
_080367CC: .4byte gJoypad
_080367D0:
	ldrh r0, [r3]
	movs r1, #0x14
	bl __umodsi3
	lsls r0, r0, #0x10
	cmp r0, #0
	bne _080367E4
	movs r0, #0x18
	bl PlaySound
_080367E4:
	movs r0, #0x9f
	lsls r0, r0, #2
	adds r6, r5, r0
	ldrb r0, [r6]
	cmp r0, #0xa
	bne _08036808
	adds r4, r5, #0
	adds r4, #0x54
	adds r0, r5, #0
	adds r1, r4, #0
	movs r2, #0
	bl FUN_080c825c
	adds r0, r5, #0
	adds r1, r4, #0
	movs r2, #1
	bl FUN_080c825c
_08036808:
	ldrb r0, [r6]
	cmp r0, #0xc7
	bhi _08036822
	adds r0, #1
	strb r0, [r6]
	b _08036822
_08036814:
	movs r1, #0x9f
	lsls r1, r1, #2
	adds r0, r5, r1
	strb r7, [r0]
	adds r1, #1
	adds r0, r5, r1
	strb r7, [r0]
_08036822:
	movs r1, #0x9f
	lsls r1, r1, #2
	adds r0, r5, r1
	ldrb r0, [r0]
	cmp r0, #0x28
	bls _08036836
	ldr r0, _08036844 @ =0x0000027D
	adds r1, r5, r0
	movs r0, #1
	strb r0, [r1]
_08036836:
	adds r0, r5, #0
	bl UpdateMotionGraphic
_0803683C:
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_08036844: .4byte 0x0000027D
