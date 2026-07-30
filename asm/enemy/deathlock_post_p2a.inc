	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_0808d78c
FUN_0808d78c: @ 0x0808D78C
	push {r4, r5, r6, lr}
	adds r4, r0, #0
	ldrb r5, [r4, #0xe]
	cmp r5, #0
	beq _0808D79C
	cmp r5, #1
	beq _0808D7D8
	b _0808D88C
_0808D79C:
	ldr r1, _0808D850 @ =0x08369300
	adds r6, r4, #0
	adds r6, #0xb9
	ldrb r0, [r6]
	lsls r0, r0, #1
	adds r0, r0, r1
	ldrh r1, [r0]
	adds r0, r4, #0
	bl SetMotion
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x74
	ldr r2, _0808D854 @ =0x0836931C
	ldrb r1, [r6]
	adds r1, r1, r2
	ldrb r2, [r1]
	lsls r1, r2, #1
	adds r1, r1, r2
	lsls r1, r1, #3
	ldr r2, _0808D858 @ =sCollisions
	adds r1, r1, r2
	bl SetDDP
	str r5, [r4, #0x60]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0808D7D8:
	ldr r0, [r4, #0x54]
	ldr r1, _0808D85C @ =0xFFFFEE00
	adds r0, r0, r1
	ldr r1, [r4, #0x58]
	movs r2, #0x80
	lsls r2, r2, #3
	adds r1, r1, r2
	bl FUN_0800a40c
	adds r5, r0, #0
	cmp r5, #0
	bne _0808D80A
	ldr r0, [r4, #0x54]
	movs r1, #0x90
	lsls r1, r1, #5
	adds r0, r0, r1
	ldr r1, [r4, #0x58]
	movs r2, #0x80
	lsls r2, r2, #3
	adds r1, r1, r2
	bl FUN_0800a40c
	adds r5, r0, #0
	cmp r5, #0
	beq _0808D812
_0808D80A:
	adds r0, r4, #0
	adds r1, r5, #0
	bl FUN_0808d160
_0808D812:
	adds r0, r4, #0
	bl IsFrozen
	adds r6, r0, #0
	cmp r6, #0
	bne _0808D88C
	adds r0, r4, #0
	movs r1, #1
	bl FUN_0808d268
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _0808D860
	ldr r0, [r4, #0x60]
	adds r0, #0x40
	str r0, [r4, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _0808D83C
	str r1, [r4, #0x60]
_0808D83C:
	ldr r0, [r4, #0x58]
	ldr r1, [r4, #0x60]
	adds r0, r0, r1
	str r0, [r4, #0x58]
	adds r0, r4, #0
	movs r1, #1
	bl FUN_0808d268
	b _0808D88C
	.align 2, 0
_0808D850: .4byte 0x08369300
_0808D854: .4byte 0x0836931C
_0808D858: .4byte sCollisions
_0808D85C: .4byte 0xFFFFEE00
_0808D860:
	str r6, [r4, #0x60]
	ldrb r0, [r4, #0x11]
	cmp r0, #0
	beq _0808D88C
	cmp r5, #0
	bne _0808D88C
	adds r0, r4, #0
	adds r0, #0xbb
	strb r5, [r0]
	adds r0, #1
	movs r2, #1
	strb r2, [r0]
	ldr r1, _0808D894 @ =gEnemyFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r4, #0x14]
	strb r2, [r4, #0xd]
_0808D88C:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_0808D894: .4byte gEnemyFnTable

	thumb_func_start FUN_0808d898
FUN_0808d898: @ 0x0808D898
	push {r4, r5, r6, lr}
	adds r5, r0, #0
	ldrb r6, [r5, #0xe]
	cmp r6, #0
	beq _0808D8A8
	cmp r6, #1
	beq _0808D958
	b _0808DA12
_0808D8A8:
	adds r0, r5, #0
	adds r0, #0x74
	ldr r2, _0808D8F0 @ =0x0836930C
	adds r4, r5, #0
	adds r4, #0xb9
	ldrb r1, [r4]
	adds r1, r1, r2
	ldrb r2, [r1]
	lsls r1, r2, #1
	adds r1, r1, r2
	lsls r1, r1, #3
	ldr r2, _0808D8F4 @ =sCollisions
	adds r1, r1, r2
	bl SetDDP
	ldrb r0, [r5, #0x10]
	cmp r0, #0
	beq _0808D8D0
	cmp r0, #2
	bne _0808D8F8
_0808D8D0:
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
	b _0808D91A
	.align 2, 0
_0808D8F0: .4byte 0x0836930C
_0808D8F4: .4byte sCollisions
_0808D8F8:
	movs r2, #1
	ldrb r1, [r5, #0xa]
	movs r0, #0x10
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
_0808D91A:
	ldrb r0, [r4]
	cmp r0, #0
	beq _0808D930
	ldr r0, _0808D92C @ =0x08369300
	ldrb r1, [r4]
	lsls r1, r1, #1
	adds r1, r1, r0
	ldrh r1, [r1]
	b _0808D938
	.align 2, 0
_0808D92C: .4byte 0x08369300
_0808D930:
	ldrb r0, [r5, #0x10]
	cmp r0, #1
	bhi _0808D944
	ldr r1, _0808D940 @ =0x00007402
_0808D938:
	adds r0, r5, #0
	bl SetMotion
	b _0808D94C
	.align 2, 0
_0808D940: .4byte 0x00007402
_0808D944:
	ldr r1, _0808D9CC @ =0x00007401
	adds r0, r5, #0
	bl SetMotion
_0808D94C:
	adds r0, r5, #0
	bl UpdateMotionGraphic
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_0808D958:
	ldr r0, [r5, #0x54]
	ldr r1, _0808D9D0 @ =0xFFFFEE00
	adds r0, r0, r1
	ldr r1, [r5, #0x58]
	movs r2, #0x80
	lsls r2, r2, #3
	adds r1, r1, r2
	bl FUN_0800a40c
	adds r1, r0, #0
	cmp r1, #0
	bne _0808D98A
	ldr r0, [r5, #0x54]
	movs r1, #0x90
	lsls r1, r1, #5
	adds r0, r0, r1
	ldr r1, [r5, #0x58]
	movs r2, #0x80
	lsls r2, r2, #3
	adds r1, r1, r2
	bl FUN_0800a40c
	adds r1, r0, #0
	cmp r1, #0
	beq _0808D9A4
_0808D98A:
	adds r0, r5, #0
	bl FUN_0808d160
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _0808D99E
	movs r1, #0
	movs r0, #3
	strb r0, [r5, #0xd]
	strb r1, [r5, #0xe]
_0808D99E:
	adds r0, r5, #0
	bl UpdateMotionGraphic
_0808D9A4:
	adds r0, r5, #0
	movs r1, #1
	bl FUN_0808d268
	lsls r0, r0, #0x18
	lsrs r1, r0, #0x18
	cmp r1, #0
	bne _0808D9BA
	movs r0, #2
	strb r0, [r5, #0xd]
	strb r1, [r5, #0xe]
_0808D9BA:
	adds r1, r5, #0
	adds r1, #0xba
	ldrb r0, [r1]
	cmp r0, #0
	beq _0808D9D4
	subs r0, #1
	strb r0, [r1]
	b _0808DA12
	.align 2, 0
_0808D9CC: .4byte 0x00007401
_0808D9D0: .4byte 0xFFFFEE00
_0808D9D4:
	adds r0, r5, #0
	adds r0, #0xb9
	ldrb r3, [r0]
	cmp r3, #0
	bne _0808DA12
	ldrb r0, [r5, #0x10]
	cmp r0, #1
	bhi _0808DA12
	ldr r0, _0808DA18 @ =pZero2
	ldr r2, [r0]
	ldr r0, [r2, #0x54]
	ldr r1, [r5, #0x54]
	subs r0, r0, r1
	movs r1, #0x90
	lsls r1, r1, #7
	adds r0, r0, r1
	ldr r1, _0808DA1C @ =0x00008FFF
	cmp r0, r1
	bhi _0808DA12
	ldr r0, [r2, #0x58]
	ldr r1, [r5, #0x58]
	subs r0, r0, r1
	movs r2, #0x80
	lsls r2, r2, #6
	adds r0, r0, r2
	ldr r1, _0808DA20 @ =0x00003FFF
	cmp r0, r1
	bhi _0808DA12
	movs r0, #4
	strb r0, [r5, #0xd]
	strb r3, [r5, #0xe]
_0808DA12:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_0808DA18: .4byte pZero2
_0808DA1C: .4byte 0x00008FFF
_0808DA20: .4byte 0x00003FFF

