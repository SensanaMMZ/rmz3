	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start hirondelle_080da398
hirondelle_080da398: @ 0x080DA398
	push {lr}
	ldr r2, _080DA3BC @ =gCurStory
	ldrb r1, [r2, #6]
	movs r3, #1
	adds r0, r3, #0
	ands r0, r1
	cmp r0, #0
	beq _080DA3D0
	ldr r0, _080DA3C0 @ =gStageDiskManager
	ldr r0, [r0]
	adds r0, #0x2b
	ldrb r1, [r0]
	adds r0, r3, #0
	ands r0, r1
	cmp r0, #0
	beq _080DA3C8
	ldr r0, _080DA3C4 @ =0x00000272
	b _080DA416
	.align 2, 0
_080DA3BC: .4byte gCurStory
_080DA3C0: .4byte gStageDiskManager
_080DA3C4: .4byte 0x00000272
_080DA3C8:
	ldr r0, _080DA3CC @ =0x00000271
	b _080DA416
	.align 2, 0
_080DA3CC: .4byte 0x00000271
_080DA3D0:
	ldrb r1, [r2, #5]
	movs r0, #8
	ands r0, r1
	cmp r0, #0
	beq _080DA402
	ldrb r0, [r2, #0x13]
	cmp r0, #1
	bhi _080DA3EC
	movs r0, #2
	strb r0, [r2, #0x13]
	ldr r0, _080DA3E8 @ =0x0000026E
	b _080DA416
	.align 2, 0
_080DA3E8: .4byte 0x0000026E
_080DA3EC:
	cmp r0, #2
	bhi _080DA3FC
	movs r0, #3
	strb r0, [r2, #0x13]
	ldr r0, _080DA3F8 @ =0x0000026F
	b _080DA416
	.align 2, 0
_080DA3F8: .4byte 0x0000026F
_080DA3FC:
	movs r0, #0x9c
	lsls r0, r0, #2
	b _080DA416
_080DA402:
	ldrb r0, [r2, #0x13]
	cmp r0, #0
	beq _080DA410
	ldr r0, _080DA40C @ =0x0000026D
	b _080DA416
	.align 2, 0
_080DA40C: .4byte 0x0000026D
_080DA410:
	strb r3, [r2, #0x13]
	movs r0, #0x9b
	lsls r0, r0, #2
_080DA416:
	pop {r1}
	bx r1
	.align 2, 0

	thumb_func_start FUN_080da41c
FUN_080da41c: @ 0x080DA41C
	push {r4, r5, r6, lr}
	adds r6, r0, #0
	ldrb r1, [r6, #0xa]
	movs r0, #4
	movs r5, #0
	orrs r0, r1
	strb r0, [r6, #0xa]
	adds r4, r6, #0
	adds r4, #0x74
	ldr r1, _080DA48C @ =sCollisions+24
	adds r2, r6, #0
	adds r2, #0x54
	adds r0, r4, #0
	movs r3, #1
	bl InitBody
	str r6, [r4, #0x2c]
	str r5, [r4, #0x24]
	ldr r2, _080DA490 @ =sMotions
	ldrb r0, [r6, #0x10]
	lsls r0, r0, #1
	adds r0, r0, r2
	ldrh r0, [r0]
	adds r1, r6, #0
	adds r1, #0xbe
	movs r3, #0
	strh r0, [r1]
	ldrb r0, [r6, #0x10]
	lsls r0, r0, #1
	adds r0, r0, r2
	ldrh r1, [r0]
	adds r0, r6, #0
	adds r0, #0xc0
	strh r1, [r0]
	ldrb r0, [r6, #0x10]
	lsls r0, r0, #1
	adds r0, r0, r2
	ldrh r0, [r0]
	adds r1, r6, #0
	adds r1, #0xc2
	strh r0, [r1]
	adds r0, r6, #0
	adds r0, #0xb9
	strb r3, [r0]
	subs r0, #1
	strb r3, [r0]
	adds r0, #4
	strh r5, [r0]
	strb r3, [r6, #0xd]
	adds r0, r6, #0
	bl MobNPC_Update
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_080DA48C: .4byte sCollisions+24
_080DA490: .4byte sMotions

	thumb_func_start pic_080da494
pic_080da494: @ 0x080DA494
	push {lr}
	ldr r2, _080DA4B4 @ =gCurStory
	ldrb r1, [r2, #6]
	movs r3, #1
	adds r0, r3, #0
	ands r0, r1
	cmp r0, #0
	beq _080DA4C2
	ldrb r0, [r2, #0x14]
	cmp r0, #2
	bhi _080DA4BC
	movs r0, #3
	strb r0, [r2, #0x14]
	ldr r0, _080DA4B8 @ =0x00000277
	b _080DA4F8
	.align 2, 0
_080DA4B4: .4byte gCurStory
_080DA4B8: .4byte 0x00000277
_080DA4BC:
	movs r0, #0x9e
	lsls r0, r0, #2
	b _080DA4F8
_080DA4C2:
	ldrb r1, [r2, #5]
	movs r0, #8
	ands r0, r1
	cmp r0, #0
	beq _080DA4E8
	ldrb r0, [r2, #0x14]
	cmp r0, #1
	bhi _080DA4E0
	movs r0, #2
	strb r0, [r2, #0x14]
	ldr r0, _080DA4DC @ =0x00000275
	b _080DA4F8
	.align 2, 0
_080DA4DC: .4byte 0x00000275
_080DA4E0:
	ldr r0, _080DA4E4 @ =0x00000276
	b _080DA4F8
	.align 2, 0
_080DA4E4: .4byte 0x00000276
_080DA4E8:
	ldrb r0, [r2, #0x14]
	cmp r0, #0
	beq _080DA4F4
	movs r0, #0x9d
	lsls r0, r0, #2
	b _080DA4F8
_080DA4F4:
	strb r3, [r2, #0x14]
	ldr r0, _080DA4FC @ =0x00000273
_080DA4F8:
	pop {r1}
	bx r1
	.align 2, 0
_080DA4FC: .4byte 0x00000273

	thumb_func_start FUN_080da500
FUN_080da500: @ 0x080DA500
	push {r4, r5, r6, lr}
	adds r6, r0, #0
	ldr r2, _080DA574 @ =sMotions
	ldrb r0, [r6, #0x10]
	lsls r0, r0, #1
	adds r0, r0, r2
	ldrh r0, [r0]
	adds r1, r6, #0
	adds r1, #0xbe
	movs r5, #0
	strh r0, [r1]
	ldrb r0, [r6, #0x10]
	lsls r0, r0, #1
	adds r0, r0, r2
	ldrh r0, [r0]
	adds r0, #1
	adds r1, #2
	strh r0, [r1]
	ldrb r0, [r6, #0x10]
	lsls r0, r0, #1
	adds r0, r0, r2
	ldrh r0, [r0]
	adds r1, #2
	strh r0, [r1]
	ldrb r1, [r6, #0xa]
	movs r0, #4
	orrs r0, r1
	strb r0, [r6, #0xa]
	adds r4, r6, #0
	adds r4, #0x74
	ldr r1, _080DA578 @ =sCollisions
	adds r2, r6, #0
	adds r2, #0x54
	adds r0, r4, #0
	movs r3, #1
	bl InitBody
	str r6, [r4, #0x2c]
	str r5, [r4, #0x24]
	adds r0, r6, #0
	adds r0, #0xb9
	movs r2, #1
	strb r2, [r0]
	adds r1, r6, #0
	adds r1, #0xb8
	movs r0, #0x30
	strb r0, [r1]
	adds r1, #4
	adds r0, #0xd0
	strh r0, [r1]
	strb r2, [r6, #0xd]
	adds r0, r6, #0
	bl MobNPC_Update
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_080DA574: .4byte sMotions
_080DA578: .4byte sCollisions

	thumb_func_start perroquiet_080da57c
perroquiet_080da57c: @ 0x080DA57C
	push {lr}
	ldr r2, _080DA59C @ =gCurStory
	ldrb r1, [r2, #6]
	movs r3, #1
	adds r0, r3, #0
	ands r0, r1
	cmp r0, #0
	beq _080DA5AC
	ldrb r0, [r2, #0x15]
	cmp r0, #2
	bhi _080DA5A4
	movs r0, #3
	strb r0, [r2, #0x15]
	ldr r0, _080DA5A0 @ =0x0000027D
	b _080DA5E0
	.align 2, 0
_080DA59C: .4byte gCurStory
_080DA5A0: .4byte 0x0000027D
_080DA5A4:
	ldr r0, _080DA5A8 @ =0x0000027E
	b _080DA5E0
	.align 2, 0
_080DA5A8: .4byte 0x0000027E
_080DA5AC:
	ldrb r1, [r2, #5]
	movs r0, #8
	ands r0, r1
	cmp r0, #0
	beq _080DA5CE
	ldrb r0, [r2, #0x15]
	cmp r0, #1
	bhi _080DA5C8
	movs r0, #2
	strb r0, [r2, #0x15]
	ldr r0, _080DA5C4 @ =0x0000027B
	b _080DA5E0
	.align 2, 0
_080DA5C4: .4byte 0x0000027B
_080DA5C8:
	movs r0, #0x9f
	lsls r0, r0, #2
	b _080DA5E0
_080DA5CE:
	ldrb r0, [r2, #0x15]
	cmp r0, #0
	beq _080DA5DC
	ldr r0, _080DA5D8 @ =0x0000027A
	b _080DA5E0
	.align 2, 0
_080DA5D8: .4byte 0x0000027A
_080DA5DC:
	strb r3, [r2, #0x15]
	ldr r0, _080DA5E4 @ =0x00000279
_080DA5E0:
	pop {r1}
	bx r1
	.align 2, 0
_080DA5E4: .4byte 0x00000279

