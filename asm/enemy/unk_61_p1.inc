	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_080935b4
FUN_080935b4: @ 0x080935B4
	push {r4, r5, r6, r7, lr}
	adds r5, r0, #0
	lsls r1, r1, #0x18
	lsrs r7, r1, #0x18
	lsls r2, r2, #0x18
	lsrs r6, r2, #0x18
	ldr r0, _08093620 @ =gEnemyHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	adds r4, r0, #0
	cmp r4, #0
	beq _08093618
	adds r1, r4, #0
	adds r1, #0x25
	movs r3, #0
	movs r0, #0x18
	strb r0, [r1]
	ldr r0, _08093624 @ =gEnemyFnTable
	movs r1, #0x3d
	strb r1, [r4, #9]
	adds r0, #0xf4
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
	strb r2, [r4, #0x10]
	ldr r0, [r5, #0x54]
	str r0, [r4, #0x54]
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x58]
	bl FUN_08009f6c
	lsls r1, r6, #0xc
	subs r0, r0, r1
	ldr r1, _08093628 @ =0xFFFFE400
	adds r0, r0, r1
	str r0, [r4, #0x58]
	strb r7, [r4, #0x12]
	str r5, [r4, #0x28]
_08093618:
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_08093620: .4byte gEnemyHeaderPtr
_08093624: .4byte gEnemyFnTable
_08093628: .4byte 0xFFFFE400
