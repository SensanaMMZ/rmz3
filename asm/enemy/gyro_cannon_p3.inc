	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_0806da5c
FUN_0806da5c: @ 0x0806DA5C
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	bne _0806DA7A
	movs r1, #0xb8
	lsls r1, r1, #5
	adds r0, r4, #0
	bl SetMotion
	movs r0, #0x78
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0806DA7A:
	adds r1, r4, #0
	adds r1, #0xb4
	movs r5, #0
	movs r0, #1
	strb r0, [r1, #0xb]
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	movs r2, #0xb0
	lsls r2, r2, #4
	adds r1, r1, r2
	bl FUN_080098a4
	lsls r0, r0, #0x10
	cmp r0, #0
	bne _0806DA9C
	strb r5, [r4, #0xd]
	b _0806DAAE
_0806DA9C:
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0xff
	bne _0806DAB0
	movs r0, #3
	strb r0, [r4, #0xd]
_0806DAAE:
	strb r5, [r4, #0xe]
_0806DAB0:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start FUN_0806dab8
FUN_0806dab8: @ 0x0806DAB8
	push {r4, r5, r6, lr}
	adds r4, r0, #0
	ldrb r5, [r4, #0xe]
	cmp r5, #0
	bne _0806DADC
	movs r1, #0xb8
	lsls r1, r1, #5
	bl SetMotion
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _0806DB40 @ =0x083666C0
	bl SetDDP
	str r5, [r4, #0x60]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0806DADC:
	ldr r0, [r4, #0x60]
	adds r0, #0x40
	str r0, [r4, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _0806DAEC
	str r1, [r4, #0x60]
_0806DAEC:
	ldr r1, [r4, #0x58]
	ldr r0, [r4, #0x60]
	adds r1, r1, r0
	str r1, [r4, #0x58]
	ldr r0, [r4, #0x54]
	movs r2, #0xa0
	lsls r2, r2, #4
	adds r1, r1, r2
	bl FUN_080098a4
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _0806DB14
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	bl FUN_08009f6c
	ldr r1, _0806DB44 @ =0xFFFFF600
	adds r0, r0, r1
	str r0, [r4, #0x58]
_0806DB14:
	adds r5, r4, #0
	adds r5, #0xb4
	ldr r0, [r5]
	bl isKilled
	cmp r0, #0
	beq _0806DB52
	movs r6, #0
	str r6, [r5]
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _0806DB48 @ =sCollisions
	bl SetDDP
	ldr r0, [r4, #0x2c]
	cmp r0, #0
	beq _0806DB4C
	movs r0, #9
	strb r0, [r4, #0xd]
	strb r6, [r4, #0xe]
	b _0806DB52
	.align 2, 0
_0806DB40: .4byte sCollisions+(24*1)
_0806DB44: .4byte 0xFFFFF600
_0806DB48: .4byte sCollisions
_0806DB4C:
	strb r0, [r4, #0xd]
	movs r0, #1
	strb r0, [r4, #0xe]
_0806DB52:
	pop {r4, r5, r6}
	pop {r0}
	bx r0

	thumb_func_start FUN_0806db58
FUN_0806db58: @ 0x0806DB58
	push {r4, lr}
	adds r4, r0, #0
	bl UpdateMotionGraphic
	ldr r0, [r4, #0x58]
	ldr r1, _0806DB88 @ =0xFFFFFE00
	adds r0, r0, r1
	str r0, [r4, #0x58]
	adds r1, r4, #0
	adds r1, #0xb4
	ldr r1, [r1, #4]
	cmp r0, r1
	bge _0806DB80
	str r1, [r4, #0x58]
	movs r0, #0
	movs r1, #2
	strb r1, [r4, #0xd]
	strb r0, [r4, #0xe]
	movs r0, #0x7f
	strb r0, [r4, #0x13]
_0806DB80:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_0806DB88: .4byte 0xFFFFFE00

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

	thumb_func_start gyroCannon_0806dccc
gyroCannon_0806dccc: @ 0x0806DCCC
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

