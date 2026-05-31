	.include "asm/macros.inc"

	.syntax unified
	
	.text


	thumb_func_start FUN_080913c0
FUN_080913c0: @ 0x080913C0
	push {r4, r5, lr}
	adds r4, r0, #0
	lsls r1, r1, #0x18
	lsrs r5, r1, #0x18
	ldr r0, _08091424 @ =gEnemyHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	adds r3, r0, #0
	cmp r3, #0
	beq _0809141E
	adds r1, r3, #0
	adds r1, #0x25
	movs r2, #0
	movs r0, #0x18
	strb r0, [r1]
	ldr r0, _08091428 @ =gEnemyFnTable
	movs r1, #0x3b
	strb r1, [r3, #9]
	adds r0, #0xec
	ldr r0, [r0]
	ldr r0, [r0]
	str r0, [r3, #0x14]
	movs r0, #0
	strh r2, [r3, #0x20]
	adds r1, r3, #0
	adds r1, #0x22
	strb r0, [r1]
	ldrb r1, [r3, #0xb]
	movs r0, #0x10
	orrs r0, r1
	strb r0, [r3, #0xb]
	ldrb r0, [r3, #0x1c]
	strb r0, [r3, #0x1d]
	ldr r0, [r4, #0x54]
	str r0, [r3, #0x54]
	ldr r0, [r4, #0x58]
	str r0, [r3, #0x58]
	strb r5, [r3, #0x10]
	movs r1, #0
	adds r0, r4, #0
	adds r0, #0xb4
	ldr r0, [r0]
	cmp r0, #0
	ble _0809141C
	movs r1, #1
_0809141C:
	strb r1, [r3, #0x13]
_0809141E:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_08091424: .4byte gEnemyHeaderPtr
_08091428: .4byte gEnemyFnTable
