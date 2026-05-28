	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_0809c3b4
FUN_0809c3b4: @ 0x0809C3B4
	push {r4, r5, r6, r7, lr}
	mov r7, r8
	push {r7}
	mov r8, r0
	adds r6, r1, #0
	lsls r2, r2, #0x10
	lsrs r7, r2, #0x10
	lsls r3, r3, #0x18
	lsrs r5, r3, #0x18
	ldr r0, _0809C428 @ =gEnemyHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	adds r4, r0, #0
	cmp r4, #0
	beq _0809C41A
	adds r1, r4, #0
	adds r1, #0x25
	movs r3, #0
	movs r0, #0x18
	strb r0, [r1]
	ldr r0, _0809C42C @ =gEnemyFnTable
	movs r1, #0x48
	strb r1, [r4, #9]
	adds r1, #0xd8
	adds r0, r0, r1
	ldr r0, [r0]
	ldr r0, [r0]
	str r0, [r4, #0x14]
	movs r2, #0
	strh r3, [r4, #0x20]
	adds r0, r4, #0
	adds r0, #0x22
	strb r2, [r0]
	ldrb r1, [r4, #0xb]
	movs r0, #0x10
	orrs r0, r1
	strb r0, [r4, #0xb]
	ldrb r0, [r4, #0x1c]
	strb r0, [r4, #0x1d]
	ldr r0, [r6]
	ldr r1, [r6, #4]
	str r0, [r4, #0x54]
	str r1, [r4, #0x58]
	strb r5, [r4, #0x10]
	strb r2, [r4, #0x11]
	adds r0, r4, #0
	adds r0, #0xb4
	strh r7, [r0]
	mov r0, r8
	str r0, [r4, #0x28]
_0809C41A:
	adds r0, r4, #0
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6, r7}
	pop {r1}
	bx r1
	.align 2, 0
_0809C428: .4byte gEnemyHeaderPtr
_0809C42C: .4byte gEnemyFnTable

	thumb_func_start FUN_0809c430
FUN_0809c430: @ 0x0809C430
	push {r4, r5, r6, lr}
	adds r6, r0, #0
	adds r5, r1, #0
	ldr r0, _0809C48C @ =gEnemyHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	adds r4, r0, #0
	cmp r4, #0
	beq _0809C484
	adds r1, r4, #0
	adds r1, #0x25
	movs r3, #0
	movs r0, #0x18
	strb r0, [r1]
	ldr r0, _0809C490 @ =gEnemyFnTable
	movs r1, #0x48
	strb r1, [r4, #9]
	adds r1, #0xd8
	adds r0, r0, r1
	ldr r0, [r0]
	ldr r0, [r0]
	str r0, [r4, #0x14]
	movs r2, #0
	strh r3, [r4, #0x20]
	adds r0, r4, #0
	adds r0, #0x22
	strb r2, [r0]
	ldrb r1, [r4, #0xb]
	movs r0, #0x10
	orrs r0, r1
	strb r0, [r4, #0xb]
	ldrb r0, [r4, #0x1c]
	strb r0, [r4, #0x1d]
	ldr r0, [r5]
	ldr r1, [r5, #4]
	str r0, [r4, #0x54]
	str r1, [r4, #0x58]
	strb r2, [r4, #0x10]
	movs r0, #1
	strb r0, [r4, #0x11]
	str r6, [r4, #0x28]
_0809C484:
	adds r0, r4, #0
	pop {r4, r5, r6}
	pop {r1}
	bx r1
	.align 2, 0
_0809C48C: .4byte gEnemyHeaderPtr
_0809C490: .4byte gEnemyFnTable

	thumb_func_start Enemy72_Init
Enemy72_Init: @ 0x0809C494
	push {r4, r5, r6, lr}
	adds r5, r0, #0
	bl InitNonAffineMotion
	ldrb r1, [r5, #0xa]
	movs r0, #1
	movs r4, #0
	movs r6, #0
	orrs r0, r1
	movs r1, #2
	orrs r0, r1
	strb r0, [r5, #0xa]
	adds r0, r5, #0
	bl ResetDynamicMotion
	ldrb r0, [r5, #0x11]
	cmp r0, #0
	bne _0809C534
	ldrb r0, [r5, #0x10]
	cmp r0, #0
	bne _0809C4DE
	ldrb r1, [r5, #0xa]
	movs r0, #0xef
	ands r0, r1
	strb r0, [r5, #0xa]
	adds r0, r5, #0
	adds r0, #0x4c
	strb r6, [r0]
	adds r2, r5, #0
	adds r2, #0x4a
	ldrb r1, [r2]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r2]
	movs r0, #0x80
	b _0809C504
_0809C4DE:
	movs r2, #1
	ldrb r0, [r5, #0xa]
	movs r1, #0x10
	orrs r0, r1
	strb r0, [r5, #0xa]
	adds r0, r5, #0
	adds r0, #0x4c
	strb r2, [r0]
	adds r3, r5, #0
	adds r3, #0x4a
	movs r2, #0x10
	ldrb r1, [r3]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	orrs r0, r2
	strb r0, [r3]
	movs r0, #0x80
	rsbs r0, r0, #0
_0809C504:
	str r0, [r5, #0x5c]
	ldrb r1, [r5, #0xb]
	movs r0, #0x10
	movs r2, #0
	orrs r0, r1
	strb r0, [r5, #0xb]
	ldr r0, [r5, #0x28]
	ldrb r0, [r0, #0x1c]
	strb r0, [r5, #0x1d]
	ldr r1, _0809C530 @ =gEnemyFnTable
	ldrb r0, [r5, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r5, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r5, #0x14]
	strb r2, [r5, #0xd]
	strb r2, [r5, #0xe]
	strb r2, [r5, #0xf]
	b _0809C56E
	.align 2, 0
_0809C530: .4byte gEnemyFnTable
_0809C534:
	movs r0, #0xff
	strb r0, [r5, #0x12]
	ldrb r0, [r5, #0xa]
	movs r1, #4
	orrs r0, r1
	strb r0, [r5, #0xa]
	adds r4, r5, #0
	adds r4, #0x74
	ldr r1, _0809C57C @ =0x0836A8DC
	adds r2, r5, #0
	adds r2, #0x54
	adds r0, r4, #0
	movs r3, #0x10
	bl InitBody
	str r5, [r4, #0x2c]
	str r6, [r4, #0x24]
	ldr r1, _0809C580 @ =gEnemyFnTable
	ldrb r0, [r5, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r5, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r5, #0x14]
	strb r1, [r5, #0xd]
	strb r6, [r5, #0xe]
	strb r6, [r5, #0xf]
_0809C56E:
	adds r0, r5, #0
	bl Enemy72_Update
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_0809C57C: .4byte 0x0836A8DC
_0809C580: .4byte gEnemyFnTable
