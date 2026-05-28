	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start CreatePetatria
CreatePetatria: @ 0x0808FE74
	push {r4, r5, lr}
	adds r5, r0, #0
	lsls r1, r1, #0x18
	lsrs r4, r1, #0x18
	ldr r0, _0808FECC @ =gEnemyHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	adds r3, r0, #0
	cmp r3, #0
	beq _0808FEC2
	adds r1, r3, #0
	adds r1, #0x25
	movs r2, #0
	movs r0, #0x18
	strb r0, [r1]
	ldr r0, _0808FED0 @ =gEnemyFnTable
	movs r1, #0x3a
	strb r1, [r3, #9]
	adds r0, #0xe8
	ldr r0, [r0]
	ldr r0, [r0]
	str r0, [r3, #0x14]
	movs r0, #0
	strh r2, [r3, #0x20]
	adds r1, r3, #0
	adds r1, #0x22
	strb r0, [r1]
	ldrb r1, [r3, #0xb]
	movs r0, #0x10
	orrs r0, r1
	strb r0, [r3, #0xb]
	ldrb r0, [r3, #0x1c]
	strb r0, [r3, #0x1d]
	ldr r0, [r5]
	ldr r1, [r5, #4]
	str r0, [r3, #0x54]
	str r1, [r3, #0x58]
	strb r4, [r3, #0x10]
_0808FEC2:
	adds r0, r3, #0
	pop {r4, r5}
	pop {r1}
	bx r1
	.align 2, 0
_0808FECC: .4byte gEnemyHeaderPtr
_0808FED0: .4byte gEnemyFnTable

	thumb_func_start Petatria_Init
Petatria_Init: @ 0x0808FED4
	push {r4, r5, r6, lr}
	adds r6, r0, #0
	bl InitNonAffineMotion
	ldrb r1, [r6, #0xa]
	movs r0, #1
	movs r3, #0
	movs r2, #0
	orrs r0, r1
	movs r1, #2
	orrs r0, r1
	strb r0, [r6, #0xa]
	ldr r1, _0808FF14 @ =nop_0809127c
	adds r0, r6, #0
	adds r0, #0x74
	str r1, [r0, #0x24]
	adds r0, #0x4c
	str r2, [r0]
	subs r0, #7
	strb r2, [r0]
	ldrb r0, [r6, #0x10]
	cmp r0, #2
	bne _0808FF50
	ldr r0, _0808FF18 @ =pZero2
	ldr r0, [r0]
	ldr r0, [r0, #0x54]
	ldr r2, [r6, #0x54]
	cmp r2, r0
	ble _0808FF1C
	movs r0, #0xcc
	rsbs r0, r0, #0
	b _0808FF1E
	.align 2, 0
_0808FF14: .4byte nop_0809127c
_0808FF18: .4byte pZero2
_0808FF1C:
	movs r0, #0xcc
_0808FF1E:
	str r0, [r6, #0x5c]
	ldr r1, [r6, #0x58]
	adds r0, r2, #0
	bl FUN_08009f6c
	str r0, [r6, #0x58]
	adds r0, r6, #0
	adds r0, #0xb8
	movs r2, #0
	strb r2, [r0]
	ldr r1, _0808FF4C @ =gEnemyFnTable
	ldrb r0, [r6, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r6, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r6, #0x14]
	strb r2, [r6, #0xd]
	strb r2, [r6, #0xe]
	strb r2, [r6, #0xf]
	b _0808FFE6
	.align 2, 0
_0808FF4C: .4byte gEnemyFnTable
_0808FF50:
	cmp r0, #0
	bne _0808FF74
	adds r1, r6, #0
	adds r1, #0xb8
	movs r0, #1
	strb r0, [r1]
	ldr r0, [r6, #0x54]
	ldr r1, _0808FF6C @ =0xFFFFF600
	adds r0, r0, r1
	ldr r1, [r6, #0x58]
	bl FUN_0800a22c
	ldr r1, _0808FF70 @ =0xFFFFE000
	b _0808FFAE
	.align 2, 0
_0808FF6C: .4byte 0xFFFFF600
_0808FF70: .4byte 0xFFFFE000
_0808FF74:
	adds r0, r6, #0
	adds r0, #0xb8
	strb r2, [r0]
	movs r2, #1
	ldrb r0, [r6, #0xa]
	movs r1, #0x10
	orrs r0, r1
	strb r0, [r6, #0xa]
	adds r0, r6, #0
	adds r0, #0x4c
	strb r2, [r0]
	adds r3, r6, #0
	adds r3, #0x4a
	movs r2, #0x10
	ldrb r1, [r3]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	orrs r0, r2
	strb r0, [r3]
	ldr r0, [r6, #0x54]
	movs r1, #0xa0
	lsls r1, r1, #4
	adds r0, r0, r1
	ldr r1, [r6, #0x58]
	bl FUN_0800a31c
	movs r1, #0x80
	lsls r1, r1, #6
_0808FFAE:
	adds r0, r0, r1
	str r0, [r6, #0x54]
	ldr r0, _0808FFC4 @ =pZero2
	ldr r0, [r0]
	ldr r1, [r6, #0x58]
	ldr r0, [r0, #0x58]
	cmp r1, r0
	ble _0808FFC8
	movs r0, #0xcc
	rsbs r0, r0, #0
	b _0808FFCA
	.align 2, 0
_0808FFC4: .4byte pZero2
_0808FFC8:
	movs r0, #0xcc
_0808FFCA:
	str r0, [r6, #0x60]
	ldr r1, _0809000C @ =gEnemyFnTable
	ldrb r0, [r6, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r6, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r6, #0x14]
	movs r0, #0
	strb r1, [r6, #0xd]
	strb r0, [r6, #0xe]
	strb r0, [r6, #0xf]
_0808FFE6:
	adds r0, r6, #0
	bl IsFrozen
	adds r5, r0, #0
	cmp r5, #0
	beq _08090060
	ldrb r0, [r6, #0x10]
	cmp r0, #2
	bne _08090014
	ldrb r1, [r6, #0xa]
	movs r0, #4
	movs r5, #0
	orrs r0, r1
	strb r0, [r6, #0xa]
	adds r4, r6, #0
	adds r4, #0x74
	ldr r1, _08090010 @ =0x08369608
	b _08090024
	.align 2, 0
_0809000C: .4byte gEnemyFnTable
_08090010: .4byte 0x08369608
_08090014:
	ldrb r1, [r6, #0xa]
	movs r0, #4
	movs r5, #0
	orrs r0, r1
	strb r0, [r6, #0xa]
	adds r4, r6, #0
	adds r4, #0x74
	ldr r1, _08090048 @ =0x08369638
_08090024:
	adds r2, r6, #0
	adds r2, #0x54
	adds r0, r4, #0
	movs r3, #6
	bl InitBody
	str r6, [r4, #0x2c]
	str r5, [r4, #0x24]
	ldrb r0, [r6, #0x10]
	cmp r0, #2
	bne _0809004C
	movs r1, #0xfc
	lsls r1, r1, #7
	adds r0, r6, #0
	bl SetMotion
	b _08090054
	.align 2, 0
_08090048: .4byte 0x08369638
_0809004C:
	ldr r1, _0809005C @ =0x00007E06
	adds r0, r6, #0
	bl SetMotion
_08090054:
	adds r0, r6, #0
	bl UpdateMotionGraphic
	b _0809009A
	.align 2, 0
_0809005C: .4byte 0x00007E06
_08090060:
	ldrb r0, [r6, #0x10]
	cmp r0, #2
	bne _0809007C
	ldrb r1, [r6, #0xa]
	movs r0, #4
	orrs r0, r1
	strb r0, [r6, #0xa]
	adds r4, r6, #0
	adds r4, #0x74
	ldr r1, _08090078 @ =0x08369608
	b _0809008A
	.align 2, 0
_08090078: .4byte 0x08369608
_0809007C:
	ldrb r1, [r6, #0xa]
	movs r0, #4
	orrs r0, r1
	strb r0, [r6, #0xa]
	adds r4, r6, #0
	adds r4, #0x74
	ldr r1, _080900A8 @ =0x08369638
_0809008A:
	adds r2, r6, #0
	adds r2, #0x54
	adds r0, r4, #0
	movs r3, #6
	bl InitBody
	str r6, [r4, #0x2c]
	str r5, [r4, #0x24]
_0809009A:
	adds r0, r6, #0
	bl Petatria_Update
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_080900A8: .4byte 0x08369638

	thumb_func_start Petatria_Update
Petatria_Update: @ 0x080900AC
	push {r4, r5, r6, lr}
	adds r4, r0, #0
	adds r0, #0x8c
	ldr r0, [r0]
	movs r1, #0x80
	lsls r1, r1, #2
	ands r0, r1
	cmp r0, #0
	beq _080900DC
	ldr r1, _080900D8 @ =gEnemyFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r4, #0x14]
	adds r0, r4, #0
	bl Petatria_Die
	b _08090122
	.align 2, 0
_080900D8: .4byte gEnemyFnTable
_080900DC:
	ldr r0, _08090128 @ =0x083695B8
	ldrb r1, [r4, #0xd]
	lsls r1, r1, #2
	adds r1, r1, r0
	ldr r1, [r1]
	adds r0, r4, #0
	bl _call_via_r1
	adds r0, r4, #0
	bl FUN_08091188
	adds r0, r4, #0
	bl IsFrozen
	adds r6, r0, #0
	cmp r6, #0
	bne _08090122
	adds r5, r4, #0
	adds r5, #0xc0
	ldr r0, [r5]
	cmp r0, #0
	beq _08090112
	bl isKilled
	cmp r0, #0
	beq _08090122
	str r6, [r5]
_08090112:
	ldr r0, _0809012C @ =0x083695E0
	ldrb r1, [r4, #0xd]
	lsls r1, r1, #2
	adds r1, r1, r0
	ldr r1, [r1]
	adds r0, r4, #0
	bl _call_via_r1
_08090122:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_08090128: .4byte 0x083695B8
_0809012C: .4byte 0x083695E0

	thumb_func_start Petatria_Die
Petatria_Die: @ 0x08090130
	push {r4, r5, r6, r7, lr}
	mov r7, r8
	push {r7}
	sub sp, #0x10
	adds r7, r0, #0
	ldr r0, _0809017C @ =gCurStory
	ldrb r1, [r0, #8]
	movs r0, #0x40
	ands r0, r1
	cmp r0, #0
	beq _08090184
	ldrb r1, [r7, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r2, #0
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r7, #0xa]
	adds r0, r7, #0
	adds r0, #0x8c
	str r2, [r0]
	adds r0, #4
	str r2, [r0]
	adds r0, #4
	strb r2, [r0]
	ldrb r1, [r7, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r7, #0xa]
	ldr r1, _08090180 @ =gEnemyFnTable
	ldrb r0, [r7, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r7, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	b _08090270
	.align 2, 0
_0809017C: .4byte gCurStory
_08090180: .4byte gEnemyFnTable
_08090184:
	ldrb r2, [r7, #0xe]
	cmp r2, #1
	beq _080901BC
	cmp r2, #1
	bgt _08090194
	cmp r2, #0
	beq _0809019E
	b _08090272
_08090194:
	cmp r2, #0xa
	beq _080901BC
	cmp r2, #0xb
	beq _080901C4
	b _08090272
_0809019E:
	movs r0, #0xa
	strb r0, [r7, #0xe]
	adds r0, r7, #0
	adds r0, #0x8c
	str r2, [r0]
	adds r0, #4
	str r2, [r0]
	adds r0, #4
	strb r2, [r0]
	ldrb r1, [r7, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r7, #0xa]
	str r2, [r7, #0x60]
	str r2, [r7, #0x5c]
_080901BC:
	ldrb r0, [r7, #0xe]
	adds r0, #1
	strb r0, [r7, #0xe]
	b _08090272
_080901C4:
	ldr r0, [r7, #0x54]
	str r0, [sp]
	ldr r0, [r7, #0x58]
	str r0, [sp, #4]
	movs r0, #1
	mov r1, sp
	bl CreateSmoke
	movs r0, #0x2a
	bl PlaySound
	movs r0, #0x54
	adds r0, r0, r7
	mov r8, r0
	movs r0, #4
	mov r1, r8
	bl TryDropItem
	ldr r2, _08090280 @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _08090284 @ =0x000343FD
	adds r4, r1, #0
	muls r4, r0, r4
	ldr r1, _08090288 @ =0x00269EC3
	adds r4, r4, r1
	lsls r4, r4, #1
	lsrs r0, r4, #1
	str r0, [r2]
	lsrs r4, r4, #0x11
	movs r0, #3
	ands r4, r0
	ldr r0, [r7, #0x54]
	str r0, [sp, #8]
	ldr r0, [r7, #0x58]
	ldr r1, _0809028C @ =0xFFFFF400
	adds r0, r0, r1
	add r6, sp, #8
	str r0, [r6, #4]
	ldrb r1, [r7, #0xa]
	lsrs r1, r1, #4
	movs r5, #1
	ands r1, r5
	ldr r2, _08090290 @ =0x00007E1A
	adds r0, r6, #0
	adds r3, r4, #0
	bl FUN_080c4914
	ldrb r1, [r7, #0xa]
	lsrs r1, r1, #4
	ands r1, r5
	ldr r2, _08090294 @ =0x00007E1B
	adds r0, r6, #0
	adds r3, r4, #0
	bl FUN_080c4914
	ldrb r1, [r7, #0xa]
	lsrs r1, r1, #4
	ands r1, r5
	ldr r2, _08090298 @ =0x00007E1C
	adds r0, r6, #0
	adds r3, r4, #0
	bl FUN_080c4914
	ldr r2, _0809029C @ =gMission
	ldrh r1, [r2, #0xc]
	ldr r0, _080902A0 @ =0x0000270E
	cmp r1, r0
	bhi _08090250
	adds r0, r1, #1
	strh r0, [r2, #0xc]
_08090250:
	adds r0, r7, #0
	mov r1, r8
	bl TryDropZakoDisk
	ldrb r1, [r7, #0xa]
	movs r0, #0xfe
	ands r0, r1
	strb r0, [r7, #0xa]
	ldr r1, _080902A4 @ =gEnemyFnTable
	ldrb r0, [r7, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #4
	str r1, [r7, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0x10]
_08090270:
	str r0, [r7, #0x14]
_08090272:
	add sp, #0x10
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_08090280: .4byte RNG_0202f388
_08090284: .4byte 0x000343FD
_08090288: .4byte 0x00269EC3
_0809028C: .4byte 0xFFFFF400
_08090290: .4byte 0x00007E1A
_08090294: .4byte 0x00007E1B
_08090298: .4byte 0x00007E1C
_0809029C: .4byte gMission
_080902A0: .4byte 0x0000270E
_080902A4: .4byte gEnemyFnTable
