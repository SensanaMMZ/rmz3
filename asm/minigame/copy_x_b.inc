	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start copyx_minigame_080fa764
copyx_minigame_080fa764: @ 0x080FA764
	push {r4, r5, lr}
	sub sp, #0x14
	ldr r1, _080FA780 @ =0x00000DCC
	adds r5, r0, r1
	movs r1, #6
	ldrsh r0, [r5, r1]
	cmp r0, #5
	bhi _080FA800
	lsls r0, r0, #2
	ldr r1, _080FA784 @ =_080FA788
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_080FA780: .4byte 0x00000DCC
_080FA784: .4byte _080FA788
_080FA788: @ jump table
	.4byte _080FA7A0 @ case 0
	.4byte _080FA7AA @ case 1
	.4byte _080FA7B8 @ case 2
	.4byte _080FA7CC @ case 3
	.4byte _080FA7DC @ case 4
	.4byte _080FA7E8 @ case 5
_080FA7A0:
	movs r0, #0x3c
	strh r0, [r5]
	ldrh r0, [r5, #6]
	adds r0, #1
	strh r0, [r5, #6]
_080FA7AA:
	ldrh r0, [r5]
	subs r0, #1
	strh r0, [r5]
	lsls r0, r0, #0x10
	cmp r0, #0
	bne _080FA800
	b _080FA7D4
_080FA7B8:
	movs r0, #4
	bl CreateMissionAlert
	str r0, [r5, #0x10]
	movs r0, #0xb3
	bl fadeoutBGM
	ldrh r0, [r5, #6]
	adds r0, #1
	strh r0, [r5, #6]
_080FA7CC:
	ldr r0, [r5, #0x10]
	ldrb r0, [r0, #0xc]
	cmp r0, #1
	bls _080FA800
_080FA7D4:
	ldrh r0, [r5, #6]
	adds r0, #1
	strh r0, [r5, #6]
	b _080FA800
_080FA7DC:
	ldr r1, _080FA7FC @ =gGameState
	movs r0, #0x40
	strh r0, [r1, #4]
	ldrh r0, [r5, #6]
	adds r0, #1
	strh r0, [r5, #6]
_080FA7E8:
	ldr r0, _080FA7FC @ =gGameState
	movs r1, #4
	ldrsh r0, [r0, r1]
	cmp r0, #0x20
	bne _080FA800
	movs r0, #0
	strh r0, [r5]
	strh r0, [r5, #6]
	b _080FA84C
	.align 2, 0
_080FA7FC: .4byte gGameState
_080FA800:
	ldr r1, _080FA854 @ =0x0810E25C
	mov r0, sp
	movs r2, #6
	bl memcpy
	mov r0, sp
	movs r1, #0x12
	movs r2, #0
	bl PrintUnicodeString
	ldr r4, [r5, #0x1c]
	adds r0, r4, #0
	movs r1, #0x1b
	movs r2, #0
	bl PrintMinigameNumber
	ldr r0, [r5, #0x24]
	cmp r4, r0
	bls _080FA828
	str r4, [r5, #0x24]
_080FA828:
	add r4, sp, #8
	ldr r1, _080FA858 @ =0x0810E264
	adds r0, r4, #0
	movs r2, #9
	bl memcpy
	adds r0, r4, #0
	movs r1, #0xf
	movs r2, #1
	bl PrintUnicodeString
	ldr r4, [r5, #0x24]
	adds r0, r4, #0
	movs r1, #0x1b
	movs r2, #1
	bl PrintMinigameNumber
	movs r0, #1
_080FA84C:
	add sp, #0x14
	pop {r4, r5}
	pop {r1}
	bx r1
	.align 2, 0
_080FA854: .4byte 0x0810E25C
_080FA858: .4byte 0x0810E264

