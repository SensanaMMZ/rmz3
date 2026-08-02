	.include "asm/macros.inc"

	.syntax unified

	.text


	thumb_func_start blazin_08040044
blazin_08040044: @ 0x08040044
	push {r4, r5, r6, r7, lr}
	sub sp, #0x10
	adds r6, r0, #0
	lsls r1, r1, #0x18
	lsrs r5, r1, #0x18
	adds r7, r5, #0
	lsls r2, r2, #0x18
	lsrs r3, r2, #0x18
	ldr r0, [r6, #0x54]
	str r0, [sp]
	ldr r0, [r6, #0x58]
	str r0, [sp, #4]
	ldrb r1, [r6, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	bne _0804009C
	ldr r0, _08040080 @ =0x080FEDA8
	adds r0, r3, r0
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	movs r1, #0xc0
	lsls r1, r1, #0x18
	adds r0, r0, r1
	lsrs r4, r0, #0x18
	cmp r3, #6
	bhi _08040084
	adds r0, r4, r5
	b _08040086
	.align 2, 0
_08040080: .4byte 0x080FEDA8
_08040084:
	subs r0, r4, r5
_08040086:
	lsls r0, r0, #0x18
	lsrs r4, r0, #0x18
	ldr r2, _08040098 @ =0x080FEDB8
	lsls r3, r3, #3
	adds r0, r3, r2
	ldr r0, [r0]
	ldr r1, [sp]
	adds r0, r0, r1
	b _080400CA
	.align 2, 0
_08040098: .4byte 0x080FEDB8
_0804009C:
	ldr r0, _080400B4 @ =0x080FEDA8
	adds r0, r3, r0
	ldrb r1, [r0]
	movs r0, #0x40
	subs r0, r0, r1
	lsls r0, r0, #0x18
	lsrs r4, r0, #0x18
	cmp r3, #6
	bhi _080400B8
	subs r0, r4, r5
	b _080400BA
	.align 2, 0
_080400B4: .4byte 0x080FEDA8
_080400B8:
	adds r0, r4, r7
_080400BA:
	lsls r0, r0, #0x18
	lsrs r4, r0, #0x18
	ldr r2, _08040108 @ =0x080FEDB8
	lsls r3, r3, #3
	adds r0, r3, r2
	ldr r1, [r0]
	ldr r0, [sp]
	subs r0, r0, r1
_080400CA:
	str r0, [sp]
	adds r0, r2, #4
	adds r0, r3, r0
	ldr r0, [r0]
	ldr r1, [sp, #4]
	adds r0, r0, r1
	str r0, [sp, #4]
	ldr r1, _0804010C @ =gSineTable
	lsls r0, r4, #1
	adds r0, r0, r1
	movs r2, #0
	ldrsh r0, [r0, r2]
	str r0, [sp, #8]
	adds r0, r4, #0
	adds r0, #0x40
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x17
	adds r0, r0, r1
	movs r1, #0
	ldrsh r0, [r0, r1]
	add r2, sp, #8
	str r0, [r2, #4]
	adds r0, r6, #0
	mov r1, sp
	bl FUN_0809e500
	movs r0, #1
	add sp, #0x10
	pop {r4, r5, r6, r7}
	pop {r1}
	bx r1
	.align 2, 0
_08040108: .4byte 0x080FEDB8
_0804010C: .4byte gSineTable
