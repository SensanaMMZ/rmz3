	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_080bba8c
FUN_080bba8c: @ 0x080BBA8C
	push {r4, r5, r6, r7, lr}
	adds r6, r0, #0
	ldr r5, [r6, #0x28]
	ldrb r0, [r5, #0xc]
	cmp r0, #1
	bhi _080BBB00
	ldrb r0, [r6, #0xe]
	cmp r0, #0
	beq _080BBAA4
	cmp r0, #1
	beq _080BBAB2
	b _080BBB1E
_080BBAA4:
	ldr r1, _080BBB24 @ =0x00002802
	adds r0, r6, #0
	bl SetMotion
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_080BBAB2:
	ldr r3, [r5, #0x54]
	str r3, [r6, #0x54]
	ldr r4, [r5, #0x58]
	str r4, [r6, #0x58]
	adds r0, r5, #0
	adds r0, #0x24
	ldrb r1, [r0]
	ldr r5, _080BBB28 @ =gSineTable
	adds r0, r1, #0
	adds r0, #0xc0
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x17
	adds r0, r0, r5
	movs r7, #0
	ldrsh r2, [r0, r7]
	lsls r0, r2, #2
	adds r0, r0, r2
	lsls r0, r0, #1
	adds r3, r3, r0
	str r3, [r6, #0x54]
	adds r1, #0x80
	lsls r1, r1, #0x18
	lsrs r1, r1, #0x17
	adds r1, r1, r5
	movs r0, #0
	ldrsh r1, [r1, r0]
	lsls r0, r1, #2
	adds r0, r0, r1
	lsls r0, r0, #1
	adds r4, r4, r0
	str r4, [r6, #0x58]
	adds r0, r6, #0
	bl UpdateMotionGraphic
	adds r0, r6, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #4
	bne _080BBB1E
_080BBB00:
	ldrb r1, [r6, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r6, #0xa]
	ldr r1, _080BBB2C @ =gVFXFnTable
	ldrb r0, [r6, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r6, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r6, #0x14]
_080BBB1E:
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080BBB24: .4byte 0x00002802
_080BBB28: .4byte gSineTable
_080BBB2C: .4byte gVFXFnTable

	thumb_func_start FUN_080bbb30
FUN_080bbb30: @ 0x080BBB30
	push {r4, r5, r6, r7, lr}
	adds r6, r0, #0
	ldr r5, [r6, #0x28]
	ldrb r0, [r5, #0xc]
	cmp r0, #1
	bhi _080BBBA4
	ldrb r0, [r6, #0xe]
	cmp r0, #0
	beq _080BBB48
	cmp r0, #1
	beq _080BBB56
	b _080BBBC2
_080BBB48:
	ldr r1, _080BBBC8 @ =0x00002804
	adds r0, r6, #0
	bl SetMotion
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_080BBB56:
	ldr r3, [r5, #0x54]
	str r3, [r6, #0x54]
	ldr r4, [r5, #0x58]
	str r4, [r6, #0x58]
	adds r0, r5, #0
	adds r0, #0x24
	ldrb r1, [r0]
	ldr r5, _080BBBCC @ =gSineTable
	adds r0, r1, #0
	adds r0, #0xc0
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x17
	adds r0, r0, r5
	movs r7, #0
	ldrsh r2, [r0, r7]
	lsls r0, r2, #2
	adds r0, r0, r2
	lsls r0, r0, #1
	adds r3, r3, r0
	str r3, [r6, #0x54]
	adds r1, #0x80
	lsls r1, r1, #0x18
	lsrs r1, r1, #0x17
	adds r1, r1, r5
	movs r0, #0
	ldrsh r1, [r1, r0]
	lsls r0, r1, #2
	adds r0, r0, r1
	lsls r0, r0, #1
	adds r4, r4, r0
	str r4, [r6, #0x58]
	adds r0, r6, #0
	bl UpdateMotionGraphic
	adds r0, r6, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #4
	bne _080BBBC2
_080BBBA4:
	ldrb r1, [r6, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r6, #0xa]
	ldr r1, _080BBBD0 @ =gVFXFnTable
	ldrb r0, [r6, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r6, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r6, #0x14]
_080BBBC2:
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080BBBC8: .4byte 0x00002804
_080BBBCC: .4byte gSineTable
_080BBBD0: .4byte gVFXFnTable
