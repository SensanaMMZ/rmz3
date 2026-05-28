	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start Elf5_Die
Elf5_Die: @ 0x080E35A8
	push {r4, r5, lr}
	adds r4, r0, #0
	adds r0, #0xb4
	ldr r2, [r0]
	ldr r1, _080E3610 @ =gPause
	movs r0, #0
	strb r0, [r1]
	ldr r1, _080E3614 @ =gUnlockedElfPtr
	adds r3, r2, #0
	adds r3, #0xb4
	ldr r5, _080E3618 @ =0x00000121
	adds r0, r2, r5
	ldrb r0, [r0]
	ldr r1, [r1]
	adds r1, r1, r0
	ldrb r0, [r1]
	movs r2, #2
	orrs r0, r2
	strb r0, [r1]
	ldrh r0, [r3, #4]
	adds r0, #3
	strh r0, [r3, #4]
	ldr r0, _080E361C @ =gMission
	ldr r0, [r0]
	adds r1, r0, #0
	adds r1, #0x4c
	ldrb r0, [r1]
	cmp r0, #0x62
	bhi _080E35E6
	adds r0, #1
	strb r0, [r1]
_080E35E6:
	adds r0, r4, #0
	adds r0, #0x54
	movs r1, #0
	bl FUN_080bfce8
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
	strb r0, [r4, #0xa]
	ldr r1, _080E3620 @ =gElfFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #4
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0x10]
	str r0, [r4, #0x14]
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080E3610: .4byte gPause
_080E3614: .4byte gUnlockedElfPtr
_080E3618: .4byte 0x00000121
_080E361C: .4byte gMission
_080E3620: .4byte gElfFnTable
