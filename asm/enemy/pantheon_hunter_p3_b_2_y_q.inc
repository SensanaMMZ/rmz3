	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start explodePHunter
explodePHunter: @ 0x08065370
	push {r4, r5, r6, r7, lr}
	mov r7, r8
	push {r7}
	sub sp, #0x10
	adds r7, r0, #0
	ldrb r0, [r7, #0xf]
	cmp r0, #0
	bne _0806538E
	ldr r1, _080653C8 @ =0x00001303
	adds r0, r7, #0
	bl SetMotion
	ldrb r0, [r7, #0xf]
	adds r0, #1
	strb r0, [r7, #0xf]
_0806538E:
	adds r0, r7, #0
	bl UpdateMotionGraphic
	adds r0, r7, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	beq _080653A0
	b _08065500
_080653A0:
	ldr r0, [r7, #0x54]
	str r0, [sp]
	ldr r0, [r7, #0x58]
	ldr r1, _080653CC @ =0xFFFFE800
	adds r0, r0, r1
	str r0, [sp, #4]
	ldr r6, _080653D0 @ =sSlashedEnemies
	adds r2, r7, #0
	adds r2, #0xbc
	ldrb r4, [r2]
	ldrb r1, [r7, #0xa]
	movs r3, #0x10
	adds r0, r3, #0
	ands r0, r1
	adds r5, r2, #0
	cmp r0, #0
	beq _080653D4
	orrs r3, r4
	b _080653D6
	.align 2, 0
_080653C8: .4byte 0x00001303
_080653CC: .4byte 0xFFFFE800
_080653D0: .4byte sSlashedEnemies
_080653D4:
	adds r3, r4, #0
_080653D6:
	mov r0, sp
	adds r1, r6, #0
	movs r2, #0
	bl CreateSlashedEnemy
	mov r4, sp
	ldr r6, _080653F8 @ =sSlashedEnemies+28
	ldrb r2, [r5]
	ldrb r1, [r7, #0xa]
	movs r3, #0x10
	adds r0, r3, #0
	ands r0, r1
	cmp r0, #0
	beq _080653FC
	orrs r3, r2
	b _080653FE
	.align 2, 0
_080653F8: .4byte sSlashedEnemies+28
_080653FC:
	adds r3, r2, #0
_080653FE:
	adds r0, r4, #0
	adds r1, r6, #0
	movs r2, #0
	bl CreateSlashedEnemy
	mov r4, sp
	ldr r6, _08065420 @ =sSlashedEnemies+56
	ldrb r2, [r5]
	ldrb r1, [r7, #0xa]
	movs r3, #0x10
	adds r0, r3, #0
	ands r0, r1
	cmp r0, #0
	beq _08065424
	orrs r3, r2
	b _08065426
	.align 2, 0
_08065420: .4byte sSlashedEnemies+56
_08065424:
	adds r3, r2, #0
_08065426:
	adds r0, r4, #0
	adds r1, r6, #0
	movs r2, #0
	bl CreateSlashedEnemy
	ldr r0, [r7, #0x58]
	ldr r1, _0806550C @ =0xFFFFF000
	adds r0, r0, r1
	str r0, [sp, #4]
	movs r0, #1
	mov r1, sp
	bl CreateSmoke
	ldr r3, _08065510 @ =RNG_0202f388
	ldr r0, [r3]
	ldr r2, _08065514 @ =0x000343FD
	adds r1, r0, #0
	muls r1, r2, r1
	ldr r5, _08065518 @ =0x00269EC3
	adds r1, r1, r5
	lsls r1, r1, #1
	lsrs r0, r1, #1
	mov r8, r0
	lsrs r1, r1, #0x11
	movs r6, #0x1f
	ands r1, r6
	movs r4, #0x10
	subs r1, r4, r1
	lsls r1, r1, #8
	ldr r0, [r7, #0x54]
	adds r0, r0, r1
	str r0, [sp]
	mov r0, r8
	muls r0, r2, r0
	adds r0, r0, r5
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r3]
	lsrs r0, r0, #0x11
	ands r0, r6
	lsls r0, r0, #8
	ldr r1, [r7, #0x58]
	subs r1, r1, r0
	str r1, [sp, #4]
	movs r0, #2
	mov r1, sp
	str r2, [sp, #8]
	str r3, [sp, #0xc]
	bl CreateSmoke
	ldr r3, [sp, #0xc]
	ldr r0, [r3]
	ldr r2, [sp, #8]
	muls r0, r2, r0
	adds r0, r0, r5
	lsls r0, r0, #1
	lsrs r1, r0, #1
	lsrs r0, r0, #0x11
	ands r0, r6
	subs r4, r4, r0
	lsls r4, r4, #8
	ldr r0, [r7, #0x54]
	adds r0, r0, r4
	str r0, [sp]
	adds r0, r1, #0
	muls r0, r2, r0
	adds r0, r0, r5
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r3]
	lsrs r0, r0, #0x11
	ands r0, r6
	lsls r0, r0, #8
	ldr r1, [r7, #0x58]
	subs r1, r1, r0
	str r1, [sp, #4]
	movs r0, #2
	mov r1, sp
	bl CreateSmoke
	movs r0, #0x2a
	bl PlaySound
	adds r4, r7, #0
	adds r4, #0x54
	movs r0, #4
	adds r1, r4, #0
	bl TryDropItem
	ldr r2, _0806551C @ =gMission
	ldrh r1, [r2, #0xc]
	ldr r0, _08065520 @ =0x0000270E
	cmp r1, r0
	bhi _080654E6
	adds r0, r1, #1
	strh r0, [r2, #0xc]
_080654E6:
	adds r0, r7, #0
	adds r1, r4, #0
	bl TryDropZakoDisk
	ldr r1, _08065524 @ =gEnemyFnTable
	ldrb r0, [r7, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #4
	str r1, [r7, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0x10]
	str r0, [r7, #0x14]
_08065500:
	add sp, #0x10
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_0806550C: .4byte 0xFFFFF000
_08065510: .4byte RNG_0202f388
_08065514: .4byte 0x000343FD
_08065518: .4byte 0x00269EC3
_0806551C: .4byte gMission
_08065520: .4byte 0x0000270E
_08065524: .4byte gEnemyFnTable
