	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_08012a64
FUN_08012a64: @ 0x08012A64
	push {r4, lr}
	sub sp, #8
	adds r4, r0, #0
	ldr r0, [r4]
	asrs r0, r0, #8
	str r0, [sp]
	ldr r0, [r4, #4]
	asrs r0, r0, #8
	str r0, [sp, #4]
	ldr r0, _08012AB8 @ =gOverworld
	movs r1, #0xe8
	lsls r1, r1, #1
	adds r0, r0, r1
	ldrh r1, [r0]
	movs r0, #0x7f
	ands r0, r1
	cmp r0, #0xb
	bne _08012AD0
	mov r0, sp
	bl FUN_08012518
	lsls r0, r0, #0x18
	lsrs r2, r0, #0x18
	cmp r2, #6
	beq _08012AD0
	ldr r0, _08012ABC @ =gCurStory
	adds r0, #0x54
	ldrb r0, [r0]
	asrs r0, r2
	movs r1, #1
	ands r0, r1
	cmp r0, #0
	beq _08012AD0
	cmp r2, #2
	bne _08012AC4
	ldr r1, [r4]
	movs r0, #0x87
	lsls r0, r0, #0xc
	cmp r1, r0
	ble _08012AC4
	ldr r0, _08012AC0 @ =Coord_083427b4
	b _08012AD2
	.align 2, 0
_08012AB8: .4byte gOverworld
_08012ABC: .4byte gCurStory
_08012AC0: .4byte Coord_083427b4
_08012AC4:
	lsls r0, r2, #3
	ldr r1, _08012ACC @ =Coord_ARRAY_08342784
	adds r0, r0, r1
	b _08012AD2
	.align 2, 0
_08012ACC: .4byte Coord_ARRAY_08342784
_08012AD0:
	movs r0, #0
_08012AD2:
	add sp, #8
	pop {r4}
	pop {r1}
	bx r1
	.align 2, 0
