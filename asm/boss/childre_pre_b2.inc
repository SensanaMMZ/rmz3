	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start childreRising
childreRising: @ 0x0804113C
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #5
	bls _08041148
	b _08041314
_08041148:
	lsls r0, r0, #2
	ldr r1, _08041154 @ =_08041158
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_08041154: .4byte _08041158
_08041158: @ jump table
	.4byte _08041170 @ case 0
	.4byte _080411A6 @ case 1
	.4byte _080411C8 @ case 2
	.4byte _080411F4 @ case 3
	.4byte _080412EC @ case 4
	.4byte _080412FE @ case 5
_08041170:
	movs r0, #0x68
	bl PlaySound
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _080411C0 @ =sCollisions+(24*1)
	bl SetDDP
	adds r0, r4, #0
	bl InitRotatableMotion
	adds r0, r4, #0
	bl ResetDynamicMotion
	adds r1, r4, #0
	adds r1, #0x24
	movs r0, #0x40
	strb r0, [r1]
	movs r0, #4
	strb r0, [r4, #0x12]
	ldr r1, _080411C4 @ =0x0000A404
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080411A6:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _080411BA
	b _08041314
_080411BA:
	ldrb r0, [r4, #0xe]
	adds r0, #1
	b _08041312
	.align 2, 0
_080411C0: .4byte sCollisions+(24*1)
_080411C4: .4byte 0x0000A404
_080411C8:
	movs r0, #0x67
	bl PlaySound
	ldr r1, _08041220 @ =0x0000A405
	adds r0, r4, #0
	bl SetMotion
	ldr r2, _08041224 @ =0xFFFFFC00
	str r2, [r4, #0x60]
	str r2, [r4, #0x5c]
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	bne _080411EA
	rsbs r0, r2, #0
	str r0, [r4, #0x5c]
_080411EA:
	movs r0, #0
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080411F4:
	ldrb r0, [r4, #0xa]
	lsrs r5, r0, #4
	movs r0, #1
	ands r5, r0
	ldr r0, [r4, #0x58]
	ldr r1, [r4, #0x60]
	adds r0, r0, r1
	str r0, [r4, #0x58]
	ldr r0, [r4, #0x5c]
	subs r0, #0x40
	lsls r1, r5, #7
	adds r1, r0, r1
	str r1, [r4, #0x5c]
	ldrb r0, [r4, #0x12]
	cmp r0, #0
	bne _08041238
	cmp r1, #0
	bge _08041228
	cmp r5, #1
	bne _0804122C
	b _08041238
	.align 2, 0
_08041220: .4byte 0x0000A405
_08041224: .4byte 0xFFFFFC00
_08041228:
	cmp r5, #0
	beq _08041238
_0804122C:
	ldr r1, _08041260 @ =0x0000A406
	adds r0, r4, #0
	bl SetMotion
	movs r0, #1
	strb r0, [r4, #0x12]
_08041238:
	ldr r1, [r4, #0x54]
	ldr r3, [r4, #0x5c]
	adds r1, r1, r3
	str r1, [r4, #0x54]
	adds r2, r4, #0
	adds r2, #0xbc
	ldr r0, [r2]
	subs r0, r0, r1
	movs r1, #0xd0
	lsls r1, r1, #7
	adds r0, r0, r1
	movs r1, #0xd0
	lsls r1, r1, #8
	cmp r0, r1
	bls _08041282
	cmp r3, #0
	bge _08041264
	cmp r5, #1
	bne _08041268
	b _08041282
	.align 2, 0
_08041260: .4byte 0x0000A406
_08041264:
	cmp r5, #0
	beq _08041282
_08041268:
	ldr r0, [r2]
	ldr r3, _080412C8 @ =0xFFFF9800
	adds r0, r0, r3
	lsls r1, r5, #1
	adds r1, r1, r5
	lsls r1, r1, #2
	adds r1, r1, r5
	lsls r1, r1, #0xc
	adds r0, r0, r1
	str r0, [r4, #0x54]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08041282:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0xc0
	ldr r0, [r0]
	ldr r1, _080412CC @ =0xFFFE8000
	adds r2, r0, r1
	ldr r1, [r4, #0x58]
	cmp r1, r2
	blt _080412A4
	ldr r0, _080412D0 @ =gStageRun+232
	ldr r0, [r0, #0x3c]
	ldr r3, _080412D4 @ =0xFFFF7000
	adds r0, r0, r3
	cmp r1, r0
	bge _08041314
_080412A4:
	str r2, [r4, #0x58]
	ldr r2, _080412D8 @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _080412DC @ =0x000343FD
	muls r0, r1, r0
	ldr r1, _080412E0 @ =0x00269EC3
	adds r0, r0, r1
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r2]
	lsrs r0, r0, #0x11
	movs r1, #1
	ands r0, r1
	cmp r0, #0
	beq _080412E4
	movs r0, #6
	b _080412E6
	.align 2, 0
_080412C8: .4byte 0xFFFF9800
_080412CC: .4byte 0xFFFE8000
_080412D0: .4byte gStageRun+232
_080412D4: .4byte 0xFFFF7000
_080412D8: .4byte RNG_0202f388
_080412DC: .4byte 0x000343FD
_080412E0: .4byte 0x00269EC3
_080412E4:
	movs r0, #9
_080412E6:
	strb r0, [r4, #0xd]
	movs r0, #0
	b _08041312
_080412EC:
	movs r0, #4
	strb r0, [r4, #0x12]
	ldr r1, _0804131C @ =0x0000A407
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080412FE:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _08041314
	movs r0, #2
_08041312:
	strb r0, [r4, #0xe]
_08041314:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_0804131C: .4byte 0x0000A407
