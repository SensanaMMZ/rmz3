	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start _killEyeCannon
_killEyeCannon: @ 0x08084D04
	push {r4, r5, lr}
	sub sp, #8
	adds r4, r0, #0
	adds r0, #0x8c
	movs r1, #0
	str r1, [r0]
	adds r0, #4
	str r1, [r0]
	adds r0, #4
	strb r1, [r0]
	ldrb r1, [r4, #0xa]
	movs r0, #0xfb
	ands r0, r1
	movs r1, #0xfe
	ands r0, r1
	strb r0, [r4, #0xa]
	ldr r0, [r4, #0x54]
	str r0, [sp]
	ldr r0, [r4, #0x58]
	movs r1, #0x90
	lsls r1, r1, #5
	adds r0, r0, r1
	str r0, [sp, #4]
	ldr r2, _08084DB0 @ =0x08368374
	adds r0, r4, #0
	mov r1, sp
	movs r3, #3
	bl FUN_080b7f70
	movs r0, #1
	mov r1, sp
	bl CreateSmoke
	movs r0, #0x2a
	bl PlaySound
	adds r5, r4, #0
	adds r5, #0x54
	movs r0, #3
	adds r1, r5, #0
	bl TryDropItem
	ldr r2, _08084DB4 @ =gMission
	ldrh r1, [r2, #0xc]
	ldr r0, _08084DB8 @ =0x0000270E
	cmp r1, r0
	bhi _08084D66
	adds r0, r1, #1
	strh r0, [r2, #0xc]
_08084D66:
	adds r0, r4, #0
	adds r1, r5, #0
	bl TryDropZakoDisk
	ldr r1, _08084DBC @ =gEnemyFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #4
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0x10]
	str r0, [r4, #0x14]
	ldrb r0, [r4, #0x10]
	cmp r0, #0
	beq _08084DA6
	ldr r3, _08084DC0 @ =gCurStory
	ldr r1, _08084DC4 @ =0x08368358
	subs r0, #1
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r1, [r0]
	lsrs r2, r1, #3
	adds r3, #4
	adds r2, r2, r3
	movs r0, #7
	ands r1, r0
	movs r0, #1
	lsls r0, r1
	ldrb r1, [r2]
	orrs r0, r1
	strb r0, [r2]
_08084DA6:
	add sp, #8
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_08084DB0: .4byte 0x08368374
_08084DB4: .4byte gMission
_08084DB8: .4byte 0x0000270E
_08084DBC: .4byte gEnemyFnTable
_08084DC0: .4byte gCurStory
_08084DC4: .4byte 0x08368358



