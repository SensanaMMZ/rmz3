	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start childreNeutral
childreNeutral: @ 0x0804078C
	push {r4, r5, r6, r7, lr}
	mov r7, r8
	push {r7}
	sub sp, #4
	adds r4, r0, #0
	adds r0, #0x8c
	ldr r1, [r0]
	movs r0, #1
	ands r0, r1
	cmp r0, #0
	bne _080407A4
	b _080408D8
_080407A4:
	movs r0, #0x80
	lsls r0, r0, #0xa
	ands r1, r0
	cmp r1, #0
	beq _080407DE
	ldrb r0, [r4, #0xd]
	cmp r0, #5
	bne _080407D6
	ldr r3, [r4, #0x54]
	movs r5, #0x80
	lsls r5, r5, #4
	adds r0, r3, r5
	str r0, [r4, #0x54]
	adds r2, r0, #0
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _080407CE
	ldr r0, _08040858 @ =0xFFFFF800
	adds r2, r3, r0
_080407CE:
	str r2, [r4, #0x54]
	ldr r0, [r4, #0x58]
	adds r0, r0, r5
	str r0, [r4, #0x58]
_080407D6:
	movs r1, #0
	movs r0, #0x12
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_080407DE:
	adds r0, r4, #0
	adds r0, #0x97
	ldrb r1, [r0]
	movs r0, #0xf0
	ands r0, r1
	cmp r0, #0x20
	bne _080408D8
	ldr r0, [r4, #0x58]
	ldr r2, _0804085C @ =0xFFFFF000
	adds r0, r0, r2
	ldr r1, _08040860 @ =gOverworld
	ldr r3, _08040864 @ =0x0002C00C
	adds r1, r1, r3
	ldr r1, [r1]
	cmp r0, r1
	ble _080408C0
	ldr r3, _08040868 @ =RNG_0202f388
	ldr r5, _0804086C @ =0x000343FD
	ldr r7, _08040870 @ =0x00001FFF
	adds r6, r2, #0
	movs r0, #4
	mov r8, r0
_0804080A:
	ldr r0, [r3]
	muls r0, r5, r0
	ldr r1, _08040874 @ =0x00269EC3
	adds r0, r0, r1
	lsls r0, r0, #1
	lsrs r2, r0, #1
	str r2, [r3]
	lsrs r0, r0, #0x11
	movs r1, #1
	ands r0, r1
	cmp r0, #0
	bne _08040878
	adds r1, r2, #0
	muls r1, r5, r1
	ldr r0, _08040874 @ =0x00269EC3
	adds r1, r1, r0
	lsls r1, r1, #1
	lsrs r2, r1, #1
	lsrs r1, r1, #0x11
	ands r1, r7
	adds r1, r1, r6
	ldr r0, [r4, #0x54]
	adds r0, r0, r1
	muls r2, r5, r2
	ldr r1, _08040874 @ =0x00269EC3
	adds r2, r2, r1
	lsls r2, r2, #1
	lsrs r1, r2, #1
	str r1, [r3]
	lsrs r2, r2, #0x11
	ands r2, r7
	adds r2, r2, r6
	ldr r1, [r4, #0x58]
	adds r1, r1, r2
	movs r2, #0
	str r3, [sp]
	bl CreateBubble
	b _080408AC
	.align 2, 0
_08040858: .4byte 0xFFFFF800
_0804085C: .4byte 0xFFFFF000
_08040860: .4byte gOverworld
_08040864: .4byte 0x0002C00C
_08040868: .4byte RNG_0202f388
_0804086C: .4byte 0x000343FD
_08040870: .4byte 0x00001FFF
_08040874: .4byte 0x00269EC3
_08040878:
	adds r1, r2, #0
	muls r1, r5, r1
	ldr r0, _080408BC @ =0x00269EC3
	adds r1, r1, r0
	lsls r1, r1, #1
	lsrs r2, r1, #1
	lsrs r1, r1, #0x11
	ands r1, r7
	adds r1, r1, r6
	ldr r0, [r4, #0x54]
	adds r0, r0, r1
	muls r2, r5, r2
	ldr r1, _080408BC @ =0x00269EC3
	adds r2, r2, r1
	lsls r2, r2, #1
	lsrs r1, r2, #1
	str r1, [r3]
	lsrs r2, r2, #0x11
	ands r2, r7
	adds r2, r2, r6
	ldr r1, [r4, #0x58]
	adds r1, r1, r2
	movs r2, #1
	str r3, [sp]
	bl CreateBubble
_080408AC:
	ldr r3, [sp]
	movs r0, #1
	rsbs r0, r0, #0
	add r8, r0
	mov r1, r8
	cmp r1, #0
	bge _0804080A
	b _080408D0
	.align 2, 0
_080408BC: .4byte 0x00269EC3
_080408C0:
	ldr r2, _080408E4 @ =0x08362064
	movs r0, #0xa
	adds r1, r4, #0
	bl ApplyElementEffect
	adds r1, r4, #0
	adds r1, #0xb4
	str r0, [r1]
_080408D0:
	movs r1, #0
	movs r0, #0x11
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_080408D8:
	add sp, #4
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080408E4: .4byte 0x08362064
