	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start PillerCannon_Init
PillerCannon_Init: @ 0x0806832C
	push {r4, r5, r6, lr}
	adds r6, r0, #0
	bl InitNonAffineMotion
	ldrb r1, [r6, #0xa]
	movs r0, #1
	movs r3, #0
	adds r2, r0, #0
	orrs r2, r1
	movs r0, #2
	orrs r2, r0
	orrs r2, r3
	strb r2, [r6, #0xa]
	ldr r0, _08068378 @ =gSystemSavedataManager
	ldrb r1, [r0, #0x14]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _08068384
	ldr r0, _0806837C @ =gCurStory
	ldrb r1, [r0, #4]
	movs r0, #0x40
	ands r0, r1
	lsls r0, r0, #0x18
	lsrs r5, r0, #0x18
	cmp r5, #0
	bne _08068384
	movs r0, #4
	orrs r2, r0
	strb r2, [r6, #0xa]
	adds r4, r6, #0
	adds r4, #0x74
	ldr r1, _08068380 @ =0x0836609C
	adds r2, r6, #0
	adds r2, #0x54
	adds r0, r4, #0
	movs r3, #0xc
	b _0806839C
	.align 2, 0
_08068378: .4byte gSystemSavedataManager
_0806837C: .4byte gCurStory
_08068380: .4byte 0x0836609C
_08068384:
	ldrb r1, [r6, #0xa]
	movs r0, #4
	movs r5, #0
	orrs r0, r1
	strb r0, [r6, #0xa]
	adds r4, r6, #0
	adds r4, #0x74
	ldr r1, _080683F8 @ =0x0836609C
	adds r2, r6, #0
	adds r2, #0x54
	adds r0, r4, #0
	movs r3, #8
_0806839C:
	bl InitBody
	str r6, [r4, #0x2c]
	str r5, [r4, #0x24]
	ldr r0, _080683FC @ =FUN_08068f68
	str r0, [r4, #0x24]
	adds r1, r6, #0
	adds r1, #0xb4
	ldr r0, [r6, #0x54]
	str r0, [r1]
	ldr r0, [r6, #0x54]
	ldr r1, [r6, #0x58]
	str r0, [r6, #0x5c]
	str r1, [r6, #0x60]
	adds r0, r6, #0
	adds r0, #0xb8
	movs r2, #0
	strb r2, [r0]
	adds r0, #4
	str r2, [r0]
	subs r0, #3
	strb r2, [r0]
	adds r0, #2
	strb r2, [r0]
	adds r0, #5
	strb r2, [r0]
	ldr r0, [r6, #0x54]
	movs r1, #0x80
	lsls r1, r1, #4
	adds r0, r0, r1
	str r0, [r6, #0x54]
	ldrb r0, [r6, #0x10]
	cmp r0, #0
	bne _08068404
	ldr r1, _08068400 @ =gEnemyFnTable
	ldrb r0, [r6, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r6, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r6, #0x14]
	strb r1, [r6, #0xd]
	b _0806841A
	.align 2, 0
_080683F8: .4byte 0x0836609C
_080683FC: .4byte FUN_08068f68
_08068400: .4byte gEnemyFnTable
_08068404:
	ldr r1, _08068444 @ =gEnemyFnTable
	ldrb r0, [r6, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r6, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r6, #0x14]
	movs r0, #2
	strb r0, [r6, #0xd]
_0806841A:
	strb r2, [r6, #0xe]
	strb r2, [r6, #0xf]
	adds r0, r6, #0
	bl IsFrozen
	cmp r0, #0
	beq _08068438
	movs r1, #0x80
	lsls r1, r1, #4
	adds r0, r6, #0
	bl SetMotion
	adds r0, r6, #0
	bl UpdateMotionGraphic
_08068438:
	adds r0, r6, #0
	bl PillerCannon_Update
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_08068444: .4byte gEnemyFnTable

	thumb_func_start PillerCannon_Update
PillerCannon_Update: @ 0x08068448
	push {r4, r5, lr}
	adds r4, r0, #0
	adds r0, #0x8c
	ldr r0, [r0]
	movs r1, #0x80
	lsls r1, r1, #2
	ands r0, r1
	cmp r0, #0
	beq _08068478
	ldr r1, _08068474 @ =gEnemyFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r4, #0x14]
	adds r0, r4, #0
	bl PillerCannon_Die
	b _08068508
	.align 2, 0
_08068474: .4byte gEnemyFnTable
_08068478:
	ldr r0, _080684AC @ =0x08366054
	ldrb r1, [r4, #0xd]
	lsls r1, r1, #2
	adds r1, r1, r0
	ldr r1, [r1]
	adds r0, r4, #0
	bl _call_via_r1
	adds r0, r4, #0
	bl FUN_08068f08
	ldrb r0, [r4, #0xd]
	cmp r0, #6
	beq _080684B0
	cmp r0, #8
	beq _080684B0
	adds r0, r4, #0
	bl IsFrozen
	cmp r0, #0
	beq _080684B0
	ldrb r1, [r4, #0xd]
	adds r0, r4, #0
	adds r0, #0xba
	strb r1, [r0]
	b _08068508
	.align 2, 0
_080684AC: .4byte 0x08366054
_080684B0:
	adds r5, r4, #0
	adds r5, #0xbc
	ldr r0, [r5]
	cmp r0, #0
	beq _080684E2
	bl isKilled
	cmp r0, #0
	bne _080684D4
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _080684D0 @ =0x083661BC
	bl SetDDP
	b _08068508
	.align 2, 0
_080684D0: .4byte 0x083661BC
_080684D4:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _080684F4 @ =0x083661A4
	bl SetDDP
	movs r0, #0
	str r0, [r5]
_080684E2:
	adds r1, r4, #0
	adds r1, #0xc0
	ldrb r0, [r1]
	cmp r0, #0
	beq _080684F8
	subs r0, #1
	strb r0, [r1]
	b _08068508
	.align 2, 0
_080684F4: .4byte 0x083661A4
_080684F8:
	ldr r0, _08068510 @ =0x08366078
	ldrb r1, [r4, #0xd]
	lsls r1, r1, #2
	adds r1, r1, r0
	ldr r1, [r1]
	adds r0, r4, #0
	bl _call_via_r1
_08068508:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_08068510: .4byte 0x08366078

	thumb_func_start PillerCannon_Die
PillerCannon_Die: @ 0x08068514
	push {r4, r5, lr}
	sub sp, #8
	adds r4, r0, #0
	ldr r0, _0806855C @ =gCurStory
	ldrb r1, [r0, #8]
	movs r0, #0x40
	ands r0, r1
	cmp r0, #0
	beq _08068564
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r2, #0
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	adds r0, #0x8c
	str r2, [r0]
	adds r0, #4
	str r2, [r0]
	adds r0, #4
	strb r2, [r0]
	ldrb r1, [r4, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r4, #0xa]
	ldr r1, _08068560 @ =gEnemyFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	b _080685F4
	.align 2, 0
_0806855C: .4byte gCurStory
_08068560: .4byte gEnemyFnTable
_08068564:
	ldrb r1, [r4, #0xe]
	cmp r1, #1
	beq _08068594
	cmp r1, #1
	bgt _08068574
	cmp r1, #0
	beq _0806857A
	b _080685F6
_08068574:
	cmp r1, #2
	beq _080685A4
	b _080685F6
_0806857A:
	movs r0, #1
	strb r0, [r4, #0xe]
	adds r0, r4, #0
	adds r0, #0x8c
	str r1, [r0]
	adds r0, #4
	str r1, [r0]
	adds r0, #4
	strb r1, [r0]
	ldrb r1, [r4, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r4, #0xa]
_08068594:
	ldr r0, [r4, #0x54]
	str r0, [sp]
	ldr r0, [r4, #0x58]
	str r0, [sp, #4]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
	b _080685F6
_080685A4:
	ldr r0, [r4, #0x5c]
	str r0, [sp]
	ldr r0, [r4, #0x60]
	str r0, [sp, #4]
	movs r0, #1
	mov r1, sp
	bl CreateSmoke
	movs r0, #0x2a
	bl PlaySound
	adds r5, r4, #0
	adds r5, #0x54
	movs r0, #4
	adds r1, r5, #0
	bl TryDropItem
	ldr r2, _08068600 @ =gMission
	ldrh r1, [r2, #0xc]
	ldr r0, _08068604 @ =0x0000270E
	cmp r1, r0
	bhi _080685D4
	adds r0, r1, #1
	strh r0, [r2, #0xc]
_080685D4:
	adds r0, r4, #0
	adds r1, r5, #0
	bl TryDropZakoDisk
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
	strb r0, [r4, #0xa]
	ldr r1, _08068608 @ =gEnemyFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #4
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0x10]
_080685F4:
	str r0, [r4, #0x14]
_080685F6:
	add sp, #8
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_08068600: .4byte gMission
_08068604: .4byte 0x0000270E
_08068608: .4byte gEnemyFnTable
