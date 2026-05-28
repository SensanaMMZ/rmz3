	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_080780c4
FUN_080780c4: @ 0x080780C4
	push {r4, r5, lr}
	adds r4, r0, #0
	ldr r1, [r4, #0x2c]
	ldrb r0, [r1, #0xc]
	cmp r0, #1
	bls _080780FE
	adds r0, r1, #0
	adds r0, #0xa4
	movs r1, #0
	ldrsh r5, [r0, r1]
	cmp r5, #0
	bne _080780FE
	ldrb r1, [r4, #0x10]
	movs r2, #0xbc
	lsls r2, r2, #6
	adds r0, r2, #0
	orrs r1, r0
	adds r0, r4, #0
	bl SetMotion
	adds r0, r4, #0
	bl UpdateMotionGraphic
	movs r0, #0x78
	strb r0, [r4, #0x12]
	movs r0, #1
	strb r0, [r4, #0xd]
	strb r5, [r4, #0xe]
	b _08078100
_080780FE:
	movs r0, #0
_08078100:
	pop {r4, r5}
	pop {r1}
	bx r1
	.align 2, 0

	thumb_func_start FUN_08078108
FUN_08078108: @ 0x08078108
	push {r4, r5, lr}
	adds r5, r0, #0
	ldr r0, _08078168 @ =gEnemyHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	adds r4, r0, #0
	cmp r4, #0
	beq _08078160
	adds r1, r4, #0
	adds r1, #0x25
	movs r3, #0
	movs r2, #0
	movs r0, #0x18
	strb r0, [r1]
	ldr r1, _0807816C @ =gEnemyFnTable
	movs r0, #0x19
	strb r0, [r4, #9]
	ldr r0, [r1, #0x64]
	ldr r0, [r0]
	str r0, [r4, #0x14]
	movs r0, #0
	strh r2, [r4, #0x20]
	adds r1, r4, #0
	adds r1, #0x22
	strb r0, [r1]
	ldrb r1, [r4, #0xb]
	movs r2, #0x10
	orrs r1, r2
	orrs r1, r3
	strb r1, [r4, #0xb]
	ldrb r0, [r4, #0x1c]
	strb r0, [r4, #0x1d]
	movs r0, #2
	strb r0, [r4, #0x10]
	ldr r0, [r5, #0x54]
	str r0, [r4, #0x54]
	ldr r0, [r5, #0x58]
	str r0, [r4, #0x58]
	str r5, [r4, #0x28]
	orrs r1, r2
	strb r1, [r4, #0xb]
	ldrb r0, [r5, #0x1c]
	strb r0, [r4, #0x1d]
_08078160:
	adds r0, r4, #0
	pop {r4, r5}
	pop {r1}
	bx r1
	.align 2, 0
_08078168: .4byte gEnemyHeaderPtr
_0807816C: .4byte gEnemyFnTable
