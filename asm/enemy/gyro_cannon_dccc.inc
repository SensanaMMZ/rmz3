	push {r4, r5, r6, r7, lr}
	mov r7, r8
	push {r7}
	adds r4, r0, #0
	ldrb r0, [r4, #0xf]
	cmp r0, #0
	bne _0806DD02
	ldr r1, _0806DD1C @ =0x00001707
	adds r0, r4, #0
	bl SetMotion
	adds r0, r4, #0
	adds r0, #0x54
	ldrb r1, [r4, #0xa]
	lsrs r1, r1, #4
	movs r2, #1
	ands r1, r2
	bl CreateGhost27
	ldr r0, [r4, #0x2c]
	ldr r1, [r0, #0x58]
	ldr r0, [r0, #0x54]
	str r0, [r4, #0x54]
	str r1, [r4, #0x58]
	ldrb r0, [r4, #0xf]
	adds r0, #1
	strb r0, [r4, #0xf]
_0806DD02:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldr r1, [r4, #0x2c]
	cmp r1, #0
	beq _0806DD2E
	ldrb r0, [r1, #0xc]
	cmp r0, #1
	bls _0806DD20
	movs r0, #0
	str r0, [r4, #0x2c]
	b _0806DD28
	.align 2, 0
_0806DD1C: .4byte 0x00001707
_0806DD20:
	ldr r0, [r1, #0x58]
	ldr r1, _0806DD50 @ =0xFFFFFE00
	adds r0, r0, r1
	str r0, [r4, #0x58]
_0806DD28:
	ldr r0, [r4, #0x2c]
	cmp r0, #0
	bne _0806DDE6
_0806DD2E:
	adds r7, r4, #0
	adds r7, #0x54
	ldr r0, _0806DD54 @ =0x08366758
	mov ip, r0
	adds r2, r4, #0
	adds r2, #0xb4
	ldrb r5, [r2, #8]
	ldrb r1, [r4, #0xa]
	movs r3, #0x10
	adds r0, r3, #0
	ands r0, r1
	adds r6, r7, #0
	mov r8, r2
	cmp r0, #0
	beq _0806DD58
	orrs r3, r5
	b _0806DD5A
	.align 2, 0
_0806DD50: .4byte 0xFFFFFE00
_0806DD54: .4byte sSlashedEnemies+(28*2)
_0806DD58:
	adds r3, r5, #0
_0806DD5A:
	adds r0, r7, #0
	mov r1, ip
	movs r2, #0
	bl CreateSlashedEnemy
	adds r5, r6, #0
	ldr r7, _0806DD7C @ =0x08366774
	mov r1, r8
	ldrb r2, [r1, #8]
	ldrb r1, [r4, #0xa]
	movs r3, #0x10
	adds r0, r3, #0
	ands r0, r1
	cmp r0, #0
	beq _0806DD80
	orrs r3, r2
	b _0806DD82
	.align 2, 0
_0806DD7C: .4byte sSlashedEnemies+(28*3)
_0806DD80:
	adds r3, r2, #0
_0806DD82:
	adds r0, r5, #0
	adds r1, r7, #0
	movs r2, #0
	bl CreateSlashedEnemy
	movs r0, #1
	adds r1, r6, #0
	bl CreateSmoke
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _0806DDA8
	movs r0, #2
	adds r1, r6, #0
	bl CreateSmoke
	b _0806DDB0
_0806DDA8:
	movs r0, #2
	adds r1, r6, #0
	bl CreateSmoke
_0806DDB0:
	adds r1, r6, #0
	movs r0, #4
	bl TryDropItem
	movs r0, #0x2a
	bl PlaySound
	ldr r2, _0806DDF0 @ =gMission
	ldrh r1, [r2, #0xc]
	ldr r0, _0806DDF4 @ =0x0000270E
	cmp r1, r0
	bhi _0806DDCC
	adds r0, r1, #1
	strh r0, [r2, #0xc]
_0806DDCC:
	adds r0, r4, #0
	adds r1, r6, #0
	bl TryDropZakoDisk
	ldr r1, _0806DDF8 @ =gEnemyFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #4
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0x10]
	str r0, [r4, #0x14]
_0806DDE6:
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_0806DDF0: .4byte gMission
_0806DDF4: .4byte 0x0000270E
_0806DDF8: .4byte gEnemyFnTable

