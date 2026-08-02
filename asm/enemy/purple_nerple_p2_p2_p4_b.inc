	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_08076638
FUN_08076638: @ 0x08076638
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r5, [r4, #0xe]
	cmp r5, #1
	beq _08076676
	cmp r5, #1
	bgt _0807664C
	cmp r5, #0
	beq _08076656
	b _080766D8
_0807664C:
	cmp r5, #2
	beq _08076698
	cmp r5, #3
	beq _080766AA
	b _080766D8
_08076656:
	str r5, [r4, #0x60]
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _08076690 @ =0x08367150
	bl SetDDP
	ldr r1, _08076694 @ =0x00002A04
	adds r0, r4, #0
	bl SetMotion
	movs r0, #0x64
	strb r0, [r4, #0x12]
	strb r5, [r4, #0x13]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08076676:
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _08076688
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08076688:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	b _080766D8
	.align 2, 0
_08076690: .4byte 0x08367150
_08076694: .4byte 0x00002A04
_08076698:
	movs r0, #0x3c
	strb r0, [r4, #0x12]
	ldr r1, _08076704 @ =0x00002A05
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080766AA:
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080766D2
	ldr r1, _08076708 @ =gEnemyFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r4, #0x14]
	movs r0, #3
	strb r0, [r4, #0xd]
	adds r0, r4, #0
	bl FUN_08075bd0
_080766D2:
	adds r0, r4, #0
	bl UpdateMotionGraphic
_080766D8:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	movs r5, #0x80
	lsls r5, r5, #2
	adds r1, r1, r5
	bl FUN_0800a40c
	adds r1, r0, #0
	cmp r1, #0
	beq _08076724
	cmp r1, #0
	bge _08076710
	ldr r0, [r4, #0x54]
	adds r1, r0, #0
	subs r1, #0x80
	str r1, [r4, #0x54]
	ldr r1, _0807670C @ =0xFFFFFD80
	adds r0, r0, r1
	ldr r1, [r4, #0x58]
	adds r1, r1, r5
	b _0807672E
	.align 2, 0
_08076704: .4byte 0x00002A05
_08076708: .4byte gEnemyFnTable
_0807670C: .4byte 0xFFFFFD80
_08076710:
	ldr r1, [r4, #0x54]
	adds r0, r1, #0
	adds r0, #0x80
	str r0, [r4, #0x54]
	movs r2, #0xa0
	lsls r2, r2, #2
	adds r0, r1, r2
	ldr r1, [r4, #0x58]
	adds r1, r1, r5
	b _0807672E
_08076724:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	movs r2, #0x80
	lsls r2, r2, #2
	adds r1, r1, r2
_0807672E:
	bl GetMetatileAttr
	movs r1, #0x80
	lsls r1, r1, #3
	ands r1, r0
	cmp r1, #0
	beq _08076740
	movs r0, #1
	strb r0, [r4, #0x13]
_08076740:
	ldrb r5, [r4, #0x13]
	cmp r5, #0
	bne _08076774
	ldr r0, [r4, #0x60]
	adds r0, #0x40
	str r0, [r4, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _08076756
	str r1, [r4, #0x60]
_08076756:
	ldr r1, [r4, #0x58]
	ldr r0, [r4, #0x60]
	adds r1, r1, r0
	str r1, [r4, #0x58]
	ldr r0, [r4, #0x54]
	bl PushoutToUp1
	adds r1, r0, #0
	cmp r1, #0
	bge _0807677A
	ldr r0, [r4, #0x58]
	adds r0, r0, r1
	str r0, [r4, #0x58]
	str r5, [r4, #0x60]
	b _0807677A
_08076774:
	ldr r0, [r4, #0x58]
	adds r0, #0x80
	str r0, [r4, #0x58]
_0807677A:
	pop {r4, r5}
	pop {r0}
	bx r0
