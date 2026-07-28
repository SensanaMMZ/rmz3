	push {r4, r5, r6, lr}
	adds r5, r0, #0
	ldr r2, [r5, #0x5c]
	lsls r2, r2, #0x10
	ldr r0, _08013AFC @ =gOverworld
	ldr r1, _08013B00 @ =0x0002C00C
	adds r0, r0, r1
	ldr r0, [r0]
	asrs r0, r0, #8
	ldr r3, [r5, #0x38]
	subs r3, r3, r0
	adds r3, #5
	lsrs r2, r2, #0x14
	lsls r2, r2, #2
	ldr r0, _08013B04 @ =gVideoRegBuffer+12
	adds r4, r2, r0
	ldr r1, [r5, #0x34]
	strh r1, [r4]
	adds r0, #2
	adds r2, r2, r0
	strh r3, [r2]
	ldr r6, _08013B08 @ =gStageTilesetOffsets+(18*4)
	ldrh r0, [r5, #0x10]
	lsrs r0, r0, #2
	lsls r1, r0, #2
	adds r1, r1, r0
	lsls r1, r1, #2
	ldr r4, _08013B0C @ =0x08704B10
	adds r1, r1, r4
	ldr r0, [r6]
	adds r0, r0, r1
	movs r1, #0x80
	lsls r1, r1, #7
	bl RequestGraphicTransfer
	ldrh r0, [r5, #0x10]
	lsrs r0, r0, #2
	lsls r1, r0, #2
	adds r1, r1, r0
	lsls r1, r1, #2
	adds r1, r1, r4
	ldr r0, [r6]
	adds r0, r0, r1
	adds r0, #0xc
	movs r1, #0
	bl LoadPalette
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_08013AFC: .4byte gOverworld
_08013B00: .4byte 0x0002C00C
_08013B04: .4byte gVideoRegBuffer+12
_08013B08: .4byte gStageTilesetOffsets+(18*4)
_08013B0C: .4byte 0x08704B10

