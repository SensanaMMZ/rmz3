	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0x10]
	lsls r1, r0, #1
	adds r1, r1, r0
	ldr r0, _080DC6F4 @ =gOverworld
	ldr r2, _080DC6F8 @ =0x0002D02C
	adds r0, r0, r2
	lsls r1, r1, #5
	ldrh r0, [r0]
	adds r1, r1, r0
	lsls r0, r1, #0x10
	lsrs r0, r0, #0x10
	movs r1, #0xc0
	lsls r1, r1, #1
	bl __umodsi3
	lsls r0, r0, #0x10
	lsrs r1, r0, #0x10
	cmp r1, #0xbf
	bhi _080DC700
	lsls r0, r1, #2
	adds r0, r0, r1
	lsls r0, r0, #0xd
	movs r1, #0xc0
	bl __udivsi3
	ldr r1, _080DC6FC @ =0xFFFFB000
	adds r0, r0, r1
	ldr r1, [r4, #0x68]
	adds r1, r1, r0
	b _080DC716
	.align 2, 0
_080DC6F4: .4byte gOverworld
_080DC6F8: .4byte 0x0002D02C
_080DC6FC: .4byte 0xFFFFB000
_080DC700:
	subs r1, #0xc0
	lsls r0, r1, #2
	adds r0, r0, r1
	lsls r0, r0, #0xd
	movs r1, #0xc0
	bl __udivsi3
	ldr r2, _080DC73C @ =0xFFFFB000
	adds r0, r0, r2
	ldr r1, [r4, #0x68]
	subs r1, r1, r0
_080DC716:
	str r1, [r4, #0x58]
	ldr r0, _080DC740 @ =pZero2
	ldr r0, [r0]
	ldr r0, [r0, #0x58]
	ldr r1, _080DC744 @ =0xFFFFF400
	adds r0, r0, r1
	ldr r1, [r4, #0x58]
	cmp r1, r0
	ble _080DC750
	ldrb r1, [r4, #0xb]
	movs r0, #8
	orrs r0, r1
	strb r0, [r4, #0xb]
	ldr r0, _080DC748 @ =0x083715FC
	str r0, [r4, #0x30]
	ldr r0, _080DC74C @ =0x0000A001
	strh r0, [r4, #0x26]
	b _080DC758
	.align 2, 0
_080DC73C: .4byte 0xFFFFB000
_080DC740: .4byte pZero2
_080DC744: .4byte 0xFFFFF400
_080DC748: .4byte sSize
_080DC74C: .4byte 0x0000A001
_080DC750:
	ldrb r1, [r4, #0xb]
	movs r0, #0xf7
	ands r0, r1
	strb r0, [r4, #0xb]
_080DC758:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	pop {r4}
	pop {r0}
	bx r0
