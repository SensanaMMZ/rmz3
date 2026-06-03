	push {r4, lr}
	adds r3, r0, #0
	adds r3, #0x74
	ldrb r1, [r3]
	ldr r2, _080C0254 @ =gSineTable
	lsls r1, r1, #0x1a
	lsrs r1, r1, #0x17
	adds r1, r1, r2
	movs r4, #0
	ldrsh r2, [r1, r4]
	lsls r2, r2, #1
	ldr r1, [r0, #0x78]
	adds r1, r1, r2
	str r1, [r0, #0x54]
	ldrb r1, [r3]
	adds r2, r1, #1
	adds r0, r2, #0
	cmp r2, #0
	bge _080C0246
	adds r0, r1, #0
	adds r0, #0x40
_080C0246:
	asrs r0, r0, #6
	lsls r0, r0, #6
	subs r0, r2, r0
	strb r0, [r3]
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080C0254: .4byte gSineTable

