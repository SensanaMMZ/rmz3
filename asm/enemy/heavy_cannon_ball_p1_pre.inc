	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start CreateHeavyCannonBall
CreateHeavyCannonBall: @ 0x0807AA8C
	push {r4, r5, r6, r7, lr}
	adds r6, r0, #0
	adds r7, r1, #0
	lsls r2, r2, #0x18
	lsrs r5, r2, #0x18
	ldr r0, _0807AAE0 @ =gEnemyHeaderPtr
	ldr r0, [r0]
	bl AllocEntityLast
	adds r4, r0, #0
	cmp r4, #0
	beq _0807AAD8
	adds r1, r4, #0
	adds r1, #0x25
	movs r3, #0
	movs r0, #0x18
	strb r0, [r1]
	ldr r1, _0807AAE4 @ =gEnemyFnTable
	movs r0, #0x1c
	strb r0, [r4, #9]
	ldr r0, [r1, #0x70]
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
	strb r2, [r4, #0x10]
	strb r5, [r4, #0x12]
	str r6, [r4, #0x54]
	str r7, [r4, #0x58]
_0807AAD8:
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_0807AAE0: .4byte gEnemyHeaderPtr
_0807AAE4: .4byte gEnemyFnTable

	thumb_func_start FUN_0807aae8
FUN_0807aae8: @ 0x0807AAE8
	push {r4, r5, lr}
	adds r2, r0, #0
	ldr r0, [r2, #0xc]
	ldr r5, [r0, #0x2c]
	ldr r3, [r2, #0x2c]
	ldr r0, [r2, #0x14]
	movs r1, #1
	ands r0, r1
	cmp r0, #0
	beq _0807AB10
	movs r4, #0
	ldr r0, [r5, #0x54]
	ldr r1, [r3, #0x54]
	subs r0, r0, r1
	cmp r0, #0
	ble _0807AB0A
	movs r4, #1
_0807AB0A:
	adds r0, r3, #0
	adds r0, #0xb4
	strb r4, [r0]
_0807AB10:
	ldr r0, [r2, #0x14]
	movs r1, #4
	ands r0, r1
	cmp r0, #0
	beq _0807AB2A
	adds r0, r5, #0
	adds r0, #0xa4
	movs r1, #0
	ldrsh r0, [r0, r1]
	cmp r0, #0
	bne _0807AB2A
	movs r0, #0xff
	strb r0, [r3, #0x12]
_0807AB2A:
	pop {r4, r5}
	pop {r0}
	bx r0
