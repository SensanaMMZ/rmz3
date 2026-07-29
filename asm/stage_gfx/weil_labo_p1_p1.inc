	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_080153e8
FUN_080153e8: @ 0x080153E8
	push {r4, r5, r6, r7, lr}
	mov r7, sl
	mov r6, sb
	mov r5, r8
	push {r5, r6, r7}
	sub sp, #0xc
	mov r8, r0
	ldr r0, [r0, #0x5c]
	lsls r5, r0, #0x10
	mov r0, r8
	bl DrawGeneralStageLayer
	lsrs r1, r5, #0x14
	lsls r1, r1, #2
	ldr r0, _080154F8 @ =gVideoRegBuffer+12
	adds r4, r1, r0
	ldrh r2, [r4]
	str r2, [sp]
	adds r0, #2
	adds r1, r1, r0
	ldrh r0, [r1]
	adds r0, #2
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	mov sb, r0
	movs r0, #0xa0
	lsls r0, r0, #2
	bl Malloc
	adds r7, r0, #0
	cmp r7, #0
	beq _080154E8
	ldr r2, _080154FC @ =gIntrManager
	movs r3, #0xba
	lsls r3, r3, #1
	adds r0, r2, r3
	str r7, [r0]
	movs r0, #0xbc
	lsls r0, r0, #1
	adds r1, r2, r0
	ldr r0, _08015500 @ =0x0400001C
	str r0, [r1]
	adds r3, #8
	adds r1, r2, r3
	ldr r0, _08015504 @ =0xA6600001
	str r0, [r1]
	lsrs r5, r5, #0x14
	str r5, [sp, #4]
	adds r1, r4, #0
	adds r2, r7, #0
	movs r5, #0xf
_0801544E:
	ldr r0, [r1]
	stm r2!, {r0}
	subs r5, #1
	cmp r5, #0
	bge _0801544E
	movs r5, #0x10
	ldr r2, _08015508 @ =gSineTable
	mov r6, sb
	adds r6, #0x80
	movs r0, #0x40
	adds r0, r0, r7
	mov sl, r0
_08015466:
	mov r3, r8
	ldrh r1, [r3, #0x10]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x17
	adds r0, r0, r2
	movs r3, #0
	ldrsh r0, [r0, r3]
	lsls r4, r0, #1
	adds r4, r4, r0
	lsls r0, r1, #2
	adds r0, r6, r0
	lsls r0, r0, #0x19
	lsrs r0, r0, #0x17
	adds r0, r0, r2
	movs r3, #0
	ldrsh r0, [r0, r3]
	lsls r0, r0, #1
	adds r4, r4, r0
	asrs r4, r4, #8
	adds r4, #4
	add r4, sb
	lsls r4, r4, #0x10
	lsls r0, r5, #1
	adds r1, r1, r0
	lsls r1, r1, #0x18
	lsrs r1, r1, #0x17
	adds r1, r1, r2
	movs r3, #0
	ldrsh r0, [r1, r3]
	movs r1, #0x13
	str r2, [sp, #8]
	bl __divsi3
	lsls r0, r0, #0x10
	asrs r0, r0, #0x10
	ldr r1, [sp]
	adds r0, r1, r0
	ldr r1, _0801550C @ =0x0000FFFF
	ands r0, r1
	orrs r4, r0
	mov r3, sl
	adds r3, #4
	mov sl, r3
	subs r3, #4
	stm r3!, {r4}
	adds r6, #8
	adds r5, #1
	ldr r2, [sp, #8]
	cmp r5, #0x5f
	ble _08015466
	cmp r5, #0x9f
	bgt _080154E8
	ldr r1, [sp, #4]
	lsls r0, r1, #2
	ldr r1, _080154F8 @ =gVideoRegBuffer+12
	adds r1, r0, r1
	lsls r0, r5, #2
	adds r2, r0, r7
_080154DE:
	ldr r0, [r1]
	stm r2!, {r0}
	adds r5, #1
	cmp r5, #0x9f
	ble _080154DE
_080154E8:
	add sp, #0xc
	pop {r3, r4, r5}
	mov r8, r3
	mov sb, r4
	mov sl, r5
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080154F8: .4byte gVideoRegBuffer+12
_080154FC: .4byte gIntrManager
_08015500: .4byte 0x0400001C
_08015504: .4byte 0xA6600001
_08015508: .4byte gSineTable
_0801550C: .4byte 0x0000FFFF
