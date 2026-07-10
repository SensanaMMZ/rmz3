	push {r4, lr}
	adds r4, r0, #0
	ldr r0, [r4, #0x28]
	ldr r1, _080E7318 @ =0x000064AC
	adds r0, r0, r1
	ldr r3, [r0]
	ldr r1, _080E731C @ =gWidgetFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r4, #0x14]
	ldrb r1, [r4, #0xa]
	movs r0, #1
	movs r2, #0
	orrs r0, r1
	movs r1, #2
	orrs r0, r1
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	adds r0, #0x4c
	strb r2, [r0]
	adds r2, r4, #0
	adds r2, #0x4a
	ldrb r1, [r2]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r2]
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
	strb r0, [r4, #0xa]
	ldr r0, _080E7320 @ =0x00012100
	str r0, [r4, #0x54]
	adds r3, #0xb4
	ldrb r0, [r3, #0x1a]
	cmp r0, #1
	bne _080E7324
	movs r0, #0xe0
	lsls r0, r0, #6
	b _080E7332
	.align 2, 0
_080E7318: .4byte 0x000064AC
_080E731C: .4byte gWidgetFnTable
_080E7320: .4byte 0x00012100
_080E7324:
	ldrb r1, [r4, #0x10]
	lsls r0, r1, #2
	adds r0, r0, r1
	lsls r0, r0, #0xa
	movs r1, #0x80
	lsls r1, r1, #5
	adds r0, r0, r1
_080E7332:
	str r0, [r4, #0x58]
	ldr r1, _080E736C @ =0xFFFFFF00
	str r1, [r4, #0x5c]
	movs r0, #0x80
	rsbs r0, r0, #0
	str r0, [r4, #0x60]
	ldr r0, [r4, #0x54]
	str r0, [r4, #0x74]
	lsls r1, r1, #3
	adds r0, r0, r1
	str r0, [r4, #0x78]
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	str r0, [r4, #0x64]
	str r1, [r4, #0x68]
	ldrb r0, [r4, #0x10]
	cmp r0, #0
	bne _080E7360
	movs r1, #0xc0
	lsls r1, r1, #2
	movs r0, #0x5b
	bl LoadBlink
_080E7360:
	adds r0, r4, #0
	bl ElfMenuItem_Update
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080E736C: .4byte 0xFFFFFF00
