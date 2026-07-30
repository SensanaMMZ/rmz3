	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start gyroCannon_0806db8c
gyroCannon_0806db8c: @ 0x0806DB8C
	push {r4, r5, r6, r7, lr}
	mov r7, r8
	push {r7}
	adds r4, r0, #0
	adds r5, r4, #0
	adds r5, #0x54
	ldr r6, _0806DBB0 @ =0x08366758
	adds r0, #0xb4
	ldrb r2, [r0, #8]
	ldrb r1, [r4, #0xa]
	movs r3, #0x10
	adds r0, r3, #0
	ands r0, r1
	cmp r0, #0
	beq _0806DBB4
	orrs r3, r2
	b _0806DBB6
	.align 2, 0
_0806DBB0: .4byte sSlashedEnemies+(28*2)
_0806DBB4:
	adds r3, r2, #0
_0806DBB6:
	adds r0, r5, #0
	adds r1, r6, #0
	movs r2, #0
	bl CreateSlashedEnemy
	adds r7, r4, #0
	adds r7, #0x54
	ldr r0, _0806DBE4 @ =0x08366758
	mov ip, r0
	adds r2, r4, #0
	adds r2, #0xb4
	ldrb r6, [r2, #8]
	ldrb r1, [r4, #0xa]
	movs r3, #0x10
	adds r0, r3, #0
	ands r0, r1
	adds r5, r7, #0
	mov r8, r2
	cmp r0, #0
	beq _0806DBE8
	orrs r3, r6
	b _0806DBEA
	.align 2, 0
_0806DBE4: .4byte sSlashedEnemies+(28*2)
_0806DBE8:
	adds r3, r6, #0
_0806DBEA:
	adds r0, r7, #0
	mov r1, ip
	movs r2, #0
	bl CreateSlashedEnemy
	adds r6, r5, #0
	ldr r7, _0806DC0C @ =0x08366774
	mov r0, r8
	ldrb r2, [r0, #8]
	ldrb r1, [r4, #0xa]
	movs r3, #0x10
	adds r0, r3, #0
	ands r0, r1
	cmp r0, #0
	beq _0806DC10
	orrs r3, r2
	b _0806DC12
	.align 2, 0
_0806DC0C: .4byte sSlashedEnemies+(28*3)
_0806DC10:
	adds r3, r2, #0
_0806DC12:
	adds r0, r6, #0
	adds r1, r7, #0
	movs r2, #0
	bl CreateSlashedEnemy
	adds r6, r5, #0
	ldr r7, _0806DC34 @ =0x08366774
	mov r0, r8
	ldrb r2, [r0, #8]
	ldrb r1, [r4, #0xa]
	movs r3, #0x10
	adds r0, r3, #0
	ands r0, r1
	cmp r0, #0
	beq _0806DC38
	orrs r3, r2
	b _0806DC3A
	.align 2, 0
_0806DC34: .4byte sSlashedEnemies+(28*3)
_0806DC38:
	adds r3, r2, #0
_0806DC3A:
	adds r0, r6, #0
	adds r1, r7, #0
	movs r2, #0
	bl CreateSlashedEnemy
	movs r0, #1
	adds r1, r5, #0
	bl CreateSmoke
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _0806DC68
	movs r0, #2
	adds r1, r5, #0
	bl CreateSmoke
	movs r0, #2
	adds r1, r5, #0
	bl CreateSmoke
	b _0806DC78
_0806DC68:
	movs r0, #2
	adds r1, r5, #0
	bl CreateSmoke
	movs r0, #2
	adds r1, r5, #0
	bl CreateSmoke
_0806DC78:
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
	strb r0, [r4, #0xa]
	movs r0, #0x2a
	bl PlaySound
	adds r1, r5, #0
	movs r0, #4
	bl TryDropItem
	ldr r2, _0806DCC0 @ =gMission
	ldrh r1, [r2, #0xc]
	ldr r0, _0806DCC4 @ =0x0000270E
	cmp r1, r0
	bhi _0806DC9C
	adds r0, r1, #1
	strh r0, [r2, #0xc]
_0806DC9C:
	adds r0, r4, #0
	adds r1, r5, #0
	bl TryDropZakoDisk
	ldr r1, _0806DCC8 @ =gEnemyFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #4
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0x10]
	str r0, [r4, #0x14]
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_0806DCC0: .4byte gMission
_0806DCC4: .4byte 0x0000270E
_0806DCC8: .4byte gEnemyFnTable
