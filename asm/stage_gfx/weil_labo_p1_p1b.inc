	.include "asm/macros.inc"

	.syntax unified
	
	.text


	thumb_func_start weilLabo_08015564
weilLabo_08015564: @ 0x08015564
	push {r4, r5, r6, r7, lr}
	adds r6, r0, #0
	ldr r0, [r6, #0x5c]
	lsls r0, r0, #0x10
	lsrs r7, r0, #0x10
	ldrb r0, [r6, #0xe]
	cmp r0, #1
	beq _08015594
	cmp r0, #1
	bgt _0801557E
	cmp r0, #0
	beq _08015584
	b _0801560A
_0801557E:
	cmp r0, #2
	beq _080155FC
	b _0801560A
_08015584:
	ldr r0, _0801561C @ =gOverworld
	ldr r1, _08015620 @ =0x0002D024
	adds r0, r0, r1
	ldrb r0, [r0]
	cmp r0, #0
	beq _0801560A
	movs r0, #1
	strb r0, [r6, #0xe]
_08015594:
	lsrs r4, r7, #4
	lsls r2, r4, #1
	ldr r3, _08015624 @ =gVideoRegBuffer+4
	adds r2, r2, r3
	ldr r0, [r6, #0x64]
	movs r1, #0x47
	orrs r0, r1
	strh r0, [r2]
	lsls r4, r4, #2
	adds r3, #8
	adds r4, r4, r3
	movs r0, #0
	str r0, [r4]
	ldr r0, _08015628 @ =0x085223D0
	ldr r0, [r0]
	ldr r1, _0801562C @ =0x085223D8
	adds r0, r0, r1
	ldr r1, _08015630 @ =gOverworld+180260
	movs r2, #0x80
	lsls r2, r2, #2
	bl CpuFastSet
	ldr r4, _08015634 @ =0x087044F0
	ldr r0, [r4]
	ldr r1, _08015638 @ =0x08704540
	adds r0, r0, r1
	movs r5, #0x80
	lsls r5, r5, #7
	adds r1, r5, #0
	bl LoadGraphic
	ldr r0, [r4]
	ldr r1, _0801563C @ =0x0870454C
	adds r0, r0, r1
	movs r1, #0
	bl LoadPalette
	ldr r0, [r4]
	ldr r1, _08015640 @ =0x08704554
	adds r0, r0, r1
	adds r1, r5, #0
	bl LoadGraphic
	ldr r0, [r4]
	ldr r1, _08015644 @ =0x08704560
	adds r0, r0, r1
	movs r1, #0
	bl LoadPalette
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_080155FC:
	lsrs r0, r7, #4
	lsls r0, r0, #2
	ldr r1, _08015648 @ =0x0200214E
	adds r0, r0, r1
	ldrh r1, [r0]
	adds r1, #4
	strh r1, [r0]
_0801560A:
	ldrb r0, [r6, #0xf]
	cmp r0, #4
	bls _08015612
	b _0801570A
_08015612:
	lsls r0, r0, #2
	ldr r1, _0801564C @ =_08015650
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_0801561C: .4byte gOverworld
_08015620: .4byte 0x0002D024
_08015624: .4byte gVideoRegBuffer+4
_08015628: .4byte 0x085223D0
_0801562C: .4byte 0x085223D8
_08015630: .4byte gOverworld+180260
_08015634: .4byte 0x087044F0
_08015638: .4byte 0x08704540
_0801563C: .4byte 0x0870454C
_08015640: .4byte 0x08704554
_08015644: .4byte 0x08704560
_08015648: .4byte gVideoRegBuffer+0xE
_0801564C: .4byte _08015650
_08015650: @ jump table
	.4byte _08015664 @ case 0
	.4byte _0801567E @ case 1
	.4byte _0801569C @ case 2
	.4byte _080156B2 @ case 3
	.4byte _080156D6 @ case 4
_08015664:
	ldr r0, _08015690 @ =gOverworld
	ldr r1, _08015694 @ =0x0002D027
	adds r0, r0, r1
	ldrb r0, [r0]
	cmp r0, #0
	beq _0801570A
	ldr r0, _08015698 @ =0x0000010D
	movs r1, #0
	bl StartPaletteAnimation
	ldrb r0, [r6, #0xf]
	adds r0, #1
	strb r0, [r6, #0xf]
_0801567E:
	ldr r0, _08015698 @ =0x0000010D
	bl StepPaletteAnimation
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #4
	bne _0801570A
	b _08015704
	.align 2, 0
_08015690: .4byte gOverworld
_08015694: .4byte 0x0002D027
_08015698: .4byte 0x0000010D
_0801569C:
	ldr r0, _080156EC @ =0x0000010D
	bl RemovePaletteAnimation
	movs r0, #0x87
	lsls r0, r0, #1
	movs r1, #0
	bl StartPaletteAnimation
	ldrb r0, [r6, #0xf]
	adds r0, #1
	strb r0, [r6, #0xf]
_080156B2:
	movs r0, #0x87
	lsls r0, r0, #1
	bl StepPaletteAnimation
	ldr r0, _080156F0 @ =gOverworld
	ldr r1, _080156F4 @ =0x0002D027
	adds r0, r0, r1
	ldrb r0, [r0]
	cmp r0, #1
	beq _0801570A
	movs r0, #0x1f
	movs r1, #8
	movs r2, #0x60
	bl LoadScreenIntoMetatileMap
	ldrb r0, [r6, #0xf]
	adds r0, #1
	strb r0, [r6, #0xf]
_080156D6:
	ldr r0, _080156F0 @ =gOverworld
	ldr r1, _080156F8 @ =0x0002D024
	adds r0, r0, r1
	ldrb r0, [r0]
	cmp r0, #0
	bne _080156FC
	movs r0, #0x87
	lsls r0, r0, #1
	bl StepPaletteAnimation
	b _0801570A
	.align 2, 0
_080156EC: .4byte 0x0000010D
_080156F0: .4byte gOverworld
_080156F4: .4byte 0x0002D027
_080156F8: .4byte 0x0002D024
_080156FC:
	movs r0, #0x87
	lsls r0, r0, #1
	bl RemovePaletteAnimation
_08015704:
	ldrb r0, [r6, #0xf]
	adds r0, #1
	strb r0, [r6, #0xf]
_0801570A:
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
