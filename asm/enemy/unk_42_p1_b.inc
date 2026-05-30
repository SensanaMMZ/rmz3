	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_080852f4
FUN_080852f4: @ 0x080852F4
	push {r4, lr}
	adds r4, r0, #0
	bl UpdateMotionGraphic
	ldrb r2, [r4, #0xf]
	adds r3, r2, #0
	cmp r3, #0
	bne _08085328
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	ldr r0, [r4, #0x64]
	adds r1, r1, r0
	str r1, [r4, #0x5c]
	ldrb r0, [r4, #0x12]
	adds r1, r0, #1
	strb r1, [r4, #0x12]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0x40
	bls _08085342
	adds r0, r2, #1
	strb r0, [r4, #0xf]
	strb r3, [r4, #0x12]
	b _08085342
_08085328:
	ldr r0, [r4, #0x28]
	ldrb r0, [r0, #0xf]
	cmp r0, #3
	bls _08085342
	ldr r1, _08085348 @ =gEnemyFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r4, #0x14]
_08085342:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_08085348: .4byte gEnemyFnTable

