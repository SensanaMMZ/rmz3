	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080609a4
FUN_080609a4: @ 0x080609A4
	push {r4, r5, lr}
	adds r4, r0, #0
	ldr r5, [r4, #0x2c]
	ldr r1, [r5, #0x60]
	movs r0, #0x80
	rsbs r0, r0, #0
	cmp r1, r0
	bgt _08060A3C
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	bl FUN_08009f6c
	ldr r3, [r4, #0x54]
	ldr r2, [r5, #0x54]
	ldr r1, [r5, #0x58]
	subs r1, r1, r0
	ldr r0, _080609F8 @ =0xFFFFFB00
	adds r1, r1, r0
	subs r2, r2, r3
	movs r0, #0x80
	lsls r0, r0, #5
	adds r2, r2, r0
	movs r0, #0x80
	lsls r0, r0, #6
	cmp r2, r0
	bhi _08060A04
	movs r3, #0
	ldr r4, _080609FC @ =0xFFFFF700
	ldr r2, _08060A00 @ =s32_ARRAY_08365240
_080609DE:
	adds r2, #4
	adds r3, #1
	subs r1, #0x80
	ldr r0, [r2]
	adds r0, r0, r4
	rsbs r0, r0, #0
	cmp r0, r1
	bge _080609DE
	subs r0, r3, #1
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	b _08060A40
	.align 2, 0
_080609F8: .4byte 0xFFFFFB00
_080609FC: .4byte 0xFFFFF700
_08060A00: .4byte s32_ARRAY_08365240
_08060A04:
	movs r3, #0
	ldr r5, _08060A30 @ =0xFFFFF700
	adds r4, r0, #0
	ldr r2, _08060A34 @ =s32_ARRAY_08365240
_08060A0C:
	adds r2, #4
	adds r3, #1
	ldr r0, [r2]
	adds r0, r0, r5
	cmp r0, r4
	ble _08060A0C
	subs r3, #1
	adds r0, r3, #0
	adds r0, #8
	lsls r0, r0, #7
	subs r1, r1, r0
	ldr r0, _08060A38 @ =0xFFFFE000
	cmp r1, r0
	bgt _08060A3C
	lsls r0, r3, #0x18
	asrs r0, r0, #0x18
	b _08060A40
	.align 2, 0
_08060A30: .4byte 0xFFFFF700
_08060A34: .4byte s32_ARRAY_08365240
_08060A38: .4byte 0xFFFFE000
_08060A3C:
	movs r0, #1
	rsbs r0, r0, #0
_08060A40:
	pop {r4, r5}
	pop {r1}
	bx r1
	.align 2, 0
