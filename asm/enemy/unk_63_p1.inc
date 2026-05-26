	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_080949d4
FUN_080949d4: @ 0x080949D4
	push {r4, r5, r6, lr}
	adds r5, r0, #0
	adds r6, r1, #0
	lsls r2, r2, #0x18
	lsrs r4, r2, #0x18
	ldr r0, _08094A48 @ =gEnemyHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	adds r3, r0, #0
	cmp r3, #0
	beq _08094A40
	adds r1, r3, #0
	adds r1, #0x25
	movs r2, #0
	movs r0, #0x18
	strb r0, [r1]
	ldr r0, _08094A4C @ =gEnemyFnTable
	movs r1, #0x3f
	strb r1, [r3, #9]
	adds r0, #0xfc
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
	movs r0, #4
	strb r0, [r3, #0x10]
	strb r4, [r3, #0x11]
	str r5, [r3, #0x54]
	str r6, [r3, #0x58]
	ldr r1, _08094A50 @ =0x08369F44
	lsls r2, r4, #2
	adds r0, r2, r1
	movs r4, #0
	ldrsh r0, [r0, r4]
	str r0, [r3, #0x5c]
	adds r1, #2
	adds r2, r2, r1
	movs r1, #0
	ldrsh r0, [r2, r1]
	str r0, [r3, #0x60]
	movs r0, #0xc0
	lsls r0, r0, #1
	str r0, [r3, #0x64]
_08094A40:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_08094A48: .4byte gEnemyHeaderPtr
_08094A4C: .4byte gEnemyFnTable
_08094A50: .4byte 0x08369F44

	thumb_func_start FUN_08094a54
FUN_08094a54: @ 0x08094A54
	push {r4, r5, r6, r7, lr}
	adds r6, r0, #0
	adds r7, r1, #0
	lsls r2, r2, #0x18
	lsrs r5, r2, #0x18
	ldr r0, _08094ACC @ =gEnemyHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	adds r4, r0, #0
	cmp r4, #0
	beq _08094AC4
	adds r1, r4, #0
	adds r1, #0x25
	movs r2, #0
	movs r0, #0x18
	strb r0, [r1]
	ldr r0, _08094AD0 @ =gEnemyFnTable
	movs r1, #0x3f
	strb r1, [r4, #9]
	adds r0, #0xfc
	ldr r0, [r0]
	ldr r0, [r0]
	str r0, [r4, #0x14]
	movs r0, #0
	strh r2, [r4, #0x20]
	adds r1, r4, #0
	adds r1, #0x22
	strb r0, [r1]
	ldrb r1, [r4, #0xb]
	movs r0, #0x10
	orrs r0, r1
	strb r0, [r4, #0xb]
	ldrb r0, [r4, #0x1c]
	strb r0, [r4, #0x1d]
	movs r0, #5
	strb r0, [r4, #0x10]
	str r6, [r4, #0x54]
	str r7, [r4, #0x58]
	ldr r2, _08094AD4 @ =0x08369F44
	lsls r3, r5, #2
	adds r0, r3, r2
	movs r1, #0
	ldrsh r0, [r0, r1]
	lsrs r1, r0, #0x1f
	adds r0, r0, r1
	asrs r0, r0, #1
	str r0, [r4, #0x5c]
	adds r2, #2
	adds r3, r3, r2
	movs r1, #0
	ldrsh r0, [r3, r1]
	lsrs r1, r0, #0x1f
	adds r0, r0, r1
	asrs r0, r0, #1
	str r0, [r4, #0x60]
_08094AC4:
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_08094ACC: .4byte gEnemyHeaderPtr
_08094AD0: .4byte gEnemyFnTable
_08094AD4: .4byte 0x08369F44
