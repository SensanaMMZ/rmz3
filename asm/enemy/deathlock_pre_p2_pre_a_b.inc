	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start Deathlock_Init
Deathlock_Init: @ 0x0808D4F8
	push {r4, r5, r6, lr}
	adds r6, r0, #0
	ldr r1, _0808D524 @ =gEnemyFnTable
	ldrb r0, [r6, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r6, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r6, #0x14]
	strb r1, [r6, #0x11]
	ldrb r0, [r6, #0x10]
	cmp r0, #8
	bne _0808D52C
	movs r0, #7
	strb r0, [r6, #0xd]
	ldr r0, [r6, #0x58]
	ldr r1, _0808D528 @ =0xFFFFF800
	adds r0, r0, r1
	str r0, [r6, #0x58]
	b _0808D538
	.align 2, 0
_0808D524: .4byte gEnemyFnTable
_0808D528: .4byte 0xFFFFF800
_0808D52C:
	cmp r0, #9
	bne _0808D536
	movs r0, #5
	strb r0, [r6, #0xd]
	b _0808D538
_0808D536:
	strb r1, [r6, #0xd]
_0808D538:
	ldrb r0, [r6, #0xa]
	movs r1, #2
	orrs r1, r0
	movs r0, #1
	movs r4, #0
	orrs r1, r0
	strb r1, [r6, #0xa]
	adds r0, r6, #0
	bl InitNonAffineMotion
	ldrb r0, [r6, #0x10]
	cmp r0, #7
	bhi _0808D5C0
	ldr r0, _0808D58C @ =gSystemSavedataManager
	ldrb r1, [r0, #0x15]
	movs r0, #0x80
	ands r0, r1
	cmp r0, #0
	beq _0808D598
	ldr r0, _0808D590 @ =gCurStory
	ldrb r1, [r0, #4]
	movs r0, #0x40
	ands r0, r1
	cmp r0, #0
	bne _0808D598
	ldrb r0, [r6, #0xa]
	movs r1, #4
	orrs r0, r1
	strb r0, [r6, #0xa]
	adds r4, r6, #0
	adds r4, #0x74
	ldr r1, _0808D594 @ =sCollisions
	adds r2, r6, #0
	adds r2, #0x54
	adds r0, r4, #0
	movs r3, #0xe
	bl InitBody
	str r6, [r4, #0x2c]
	movs r0, #0
	str r0, [r4, #0x24]
	b _0808D5E0
	.align 2, 0
_0808D58C: .4byte gSystemSavedataManager
_0808D590: .4byte gCurStory
_0808D594: .4byte sCollisions
_0808D598:
	ldrb r1, [r6, #0xa]
	movs r0, #4
	movs r5, #0
	orrs r0, r1
	strb r0, [r6, #0xa]
	adds r4, r6, #0
	adds r4, #0x74
	ldr r1, _0808D5BC @ =sCollisions
	adds r2, r6, #0
	adds r2, #0x54
	adds r0, r4, #0
	movs r3, #0xa
	bl InitBody
	str r6, [r4, #0x2c]
	str r5, [r4, #0x24]
	b _0808D5E0
	.align 2, 0
_0808D5BC: .4byte sCollisions
_0808D5C0:
	cmp r0, #9
	bne _0808D5E4
	ldrb r0, [r6, #0xa]
	movs r1, #4
	orrs r0, r1
	strb r0, [r6, #0xa]
	adds r4, r6, #0
	adds r4, #0x74
	ldr r1, _0808D600 @ =sCollisions
	adds r2, r6, #0
	adds r2, #0x54
	adds r0, r4, #0
	movs r3, #4
	bl InitBody
	str r6, [r4, #0x2c]
_0808D5E0:
	ldr r0, _0808D604 @ =nop_0808d2f4
	str r0, [r4, #0x24]
_0808D5E4:
	adds r1, r6, #0
	adds r1, #0xb4
	movs r0, #0
	str r0, [r1]
	ldrb r0, [r6, #0x10]
	cmp r0, #3
	bhi _0808D608
	ldr r0, [r6, #0x54]
	ldr r1, [r6, #0x58]
	bl FUN_08009f6c
	str r0, [r6, #0x58]
	b _0808D618
	.align 2, 0
_0808D600: .4byte sCollisions
_0808D604: .4byte nop_0808d2f4
_0808D608:
	subs r1, r0, #4
	lsls r0, r1, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #3
	bhi _0808D618
	strb r1, [r6, #0x10]
	movs r0, #1
	strb r0, [r6, #0x11]
_0808D618:
	adds r0, r6, #0
	adds r0, #0xb8
	movs r1, #0
	strb r1, [r0]
	adds r0, #1
	strb r1, [r0]
	adds r0, #1
	strb r1, [r0]
	adds r0, #2
	strb r1, [r0]
	adds r0, r6, #0
	bl Deathlock_Update
	pop {r4, r5, r6}
	pop {r0}
	bx r0

