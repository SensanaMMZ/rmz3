	.include "asm/macros.inc"

	.syntax unified
	
	.text


	thumb_func_start FUN_080157b0
FUN_080157b0: @ 0x080157B0
	push {r4, r5, r6, r7, lr}
	mov r7, r8
	push {r7}
	sub sp, #0xc
	adds r6, r0, #0
	ldr r0, [r6, #0x5c]
	lsls r0, r0, #0x10
	lsrs r1, r0, #0x10
	mov r8, r1
	ldrb r5, [r6, #0xe]
	cmp r5, #1
	beq _0801581C
	cmp r5, #1
	bgt _080157D2
	cmp r5, #0
	beq _080157D8
	b _0801587A
_080157D2:
	cmp r5, #2
	beq _0801582E
	b _0801587A
_080157D8:
	lsrs r3, r0, #0x14
	lsls r2, r3, #1
	ldr r4, _08015888 @ =gVideoRegBuffer+4
	adds r2, r2, r4
	ldr r1, [r6, #0x64]
	ldr r7, _0801588C @ =0x00004046
	adds r0, r7, #0
	orrs r1, r0
	strh r1, [r2]
	lsls r3, r3, #2
	adds r4, #8
	adds r3, r3, r4
	str r5, [r3]
	movs r0, #0xf8
	lsls r0, r0, #5
	ands r1, r0
	lsls r1, r1, #3
	movs r2, #0x80
	lsls r2, r2, #5
	movs r0, #0
	bl RequestType2Transfer
	ldr r0, _08015890 @ =gOverworld
	ldr r1, _08015894 @ =0x0002D025
	adds r0, r0, r1
	ldrb r1, [r0]
	adds r0, r6, #0
	adds r0, #0x68
	strb r1, [r0]
	adds r0, #1
	strb r5, [r0]
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_0801581C:
	ldr r0, _08015890 @ =gOverworld
	ldr r5, _08015898 @ =0x0002D024
	adds r0, r0, r5
	ldrb r0, [r0]
	cmp r0, #0
	beq _0801587A
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_0801582E:
	mov r7, r8
	lsrs r4, r7, #4
	lsls r2, r4, #1
	ldr r3, _08015888 @ =gVideoRegBuffer+4
	adds r2, r2, r3
	ldr r1, [r6, #0x64]
	ldr r5, _0801588C @ =0x00004046
	adds r0, r5, #0
	orrs r1, r0
	strh r1, [r2]
	lsls r4, r4, #2
	adds r3, #8
	adds r4, r4, r3
	movs r5, #0
	str r5, [r4]
	movs r0, #0xf8
	lsls r0, r0, #5
	ands r1, r0
	lsls r1, r1, #3
	movs r0, #0xc0
	lsls r0, r0, #0x13
	adds r1, r1, r0
	str r5, [sp, #4]
	ldr r2, _0801589C @ =0x01000400
	add r0, sp, #4
	bl CpuFastSet
	lsls r0, r7, #0x18
	lsrs r0, r0, #0x18
	ldr r1, _080158A0 @ =gBgMapOffsets
	str r5, [sp]
	movs r2, #0x4a
	movs r3, #0
	bl LoadBgMap
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_0801587A:
	add sp, #0xc
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_08015888: .4byte gVideoRegBuffer+4
_0801588C: .4byte 0x00004046
_08015890: .4byte gOverworld
_08015894: .4byte 0x0002D025
_08015898: .4byte 0x0002D024
_0801589C: .4byte 0x01000400
_080158A0: .4byte gBgMapOffsets

	thumb_func_start weilLabo_080158a4
weilLabo_080158a4: @ 0x080158A4
	push {r4, r5, r6, r7, lr}
	mov r7, r8
	push {r7}
	sub sp, #0xc
	adds r6, r0, #0
	ldr r0, [r6, #0x5c]
	lsls r2, r0, #0x10
	lsrs r7, r2, #0x10
	ldr r5, _08015910 @ =gOverworld
	ldr r1, _08015914 @ =0x0002D024
	adds r0, r5, r1
	ldrb r0, [r0]
	cmp r0, #0
	beq _080158C2
	b _08015A3C
_080158C2:
	ldr r3, _08015918 @ =0x0002C002
	adds r0, r5, r3
	ldrh r0, [r0]
	movs r4, #0x68
	adds r4, r4, r6
	mov r8, r4
	cmp r0, #0
	bne _080158E0
	ldr r0, _0801591C @ =0x0002D025
	adds r1, r5, r0
	ldrb r0, [r4]
	lsrs r4, r2, #0x14
	ldrb r1, [r1]
	cmp r0, r1
	beq _08015976
_080158E0:
	ldr r1, _0801591C @ =0x0002D025
	adds r0, r5, r1
	ldrb r0, [r0]
	cmp r0, #1
	bne _0801592C
	ldr r0, _08015920 @ =0x085223C4
	ldr r0, [r0]
	ldr r3, _08015924 @ =0x085223CC
	adds r0, r0, r3
	lsrs r1, r2, #0x14
	lsls r1, r1, #1
	ldr r2, _08015928 @ =gVideoRegBuffer+4
	adds r1, r1, r2
	ldrh r2, [r1]
	movs r1, #0xf8
	lsls r1, r1, #5
	ands r1, r2
	lsls r1, r1, #3
	movs r2, #0x98
	lsls r2, r2, #3
	bl RequestBgMapTransfer
	b _0801594E
	.align 2, 0
_08015910: .4byte gOverworld
_08015914: .4byte 0x0002D024
_08015918: .4byte 0x0002C002
_0801591C: .4byte 0x0002D025
_08015920: .4byte 0x085223C4
_08015924: .4byte 0x085223CC
_08015928: .4byte gVideoRegBuffer+4
_0801592C:
	ldr r0, _08015A04 @ =0x085223C0
	ldr r0, [r0]
	ldr r4, _08015A08 @ =0x085223C8
	adds r0, r0, r4
	lsrs r1, r2, #0x14
	lsls r1, r1, #1
	ldr r2, _08015A0C @ =gVideoRegBuffer+4
	adds r1, r1, r2
	ldrh r2, [r1]
	movs r1, #0xf8
	lsls r1, r1, #5
	ands r1, r2
	lsls r1, r1, #3
	movs r2, #0x98
	lsls r2, r2, #3
	bl RequestBgMapTransfer
_0801594E:
	lsrs r4, r7, #4
	lsls r0, r4, #1
	ldr r1, _08015A0C @ =gVideoRegBuffer+4
	adds r0, r0, r1
	ldrh r0, [r0]
	movs r1, #0xf8
	lsls r1, r1, #5
	ands r1, r0
	lsls r1, r1, #3
	movs r2, #0x80
	lsls r2, r2, #5
	movs r0, #0
	bl RequestType2Transfer
	ldr r0, _08015A10 @ =gOverworld
	ldr r1, _08015A14 @ =0x0002D025
	adds r0, r0, r1
	ldrb r0, [r0]
	mov r2, r8
	strb r0, [r2]
_08015976:
	ldr r1, _08015A10 @ =gOverworld
	ldr r3, _08015A18 @ =0x0002D034
	adds r0, r1, r3
	ldr r2, [r0]
	adds r5, r1, #0
	cmp r2, #0
	beq _080159C2
	ldr r0, _08015A1C @ =0x0002D038
	adds r1, r5, r0
	ldr r0, [r2, #0x54]
	str r0, [r1]
	adds r3, #8
	adds r1, r5, r3
	ldr r0, [r2, #0x58]
	str r0, [r1]
	ldr r0, _08015A20 @ =gWhitePaintFlags
	ldrb r1, [r2, #0x1d]
	lsrs r2, r1, #5
	lsls r2, r2, #2
	adds r2, r2, r0
	movs r0, #0x1f
	ands r0, r1
	movs r1, #1
	lsls r1, r0
	ldr r0, [r2]
	ands r0, r1
	cmp r0, #0
	beq _080159C2
	ldr r1, _08015A24 @ =gPaletteManager
	ldr r0, _08015A28 @ =0x00000404
	adds r2, r1, r0
	movs r0, #0x90
	lsls r0, r0, #1
	strh r0, [r2]
	ldr r2, _08015A2C @ =0x00000406
	adds r1, r1, r2
	movs r0, #0x20
	strh r0, [r1]
_080159C2:
	lsls r3, r4, #2
	ldr r2, _08015A30 @ =gVideoRegBuffer+12
	adds r4, r3, r2
	mov r8, r4
	ldr r1, [r6, #0x34]
	ldr r4, _08015A1C @ =0x0002D038
	adds r0, r5, r4
	ldr r0, [r0]
	asrs r0, r0, #8
	subs r1, r1, r0
	adds r1, #0x30
	ldr r0, [r6, #0x2c]
	asrs r0, r0, #8
	adds r1, r1, r0
	mov r0, r8
	strh r1, [r0]
	adds r2, #2
	adds r3, r3, r2
	ldr r1, [r6, #0x38]
	ldr r2, _08015A34 @ =0x0002D03C
	adds r0, r5, r2
	ldr r0, [r0]
	ldr r4, _08015A38 @ =0xFFFB0000
	adds r0, r0, r4
	asrs r0, r0, #8
	movs r2, #0xa0
	lsls r2, r2, #3
	adds r0, r0, r2
	subs r1, r1, r0
	ldr r0, [r6, #0x30]
	asrs r0, r0, #8
	adds r0, #0x90
	b _08015B06
	.align 2, 0
_08015A04: .4byte 0x085223C0
_08015A08: .4byte 0x085223C8
_08015A0C: .4byte gVideoRegBuffer+4
_08015A10: .4byte gOverworld
_08015A14: .4byte 0x0002D025
_08015A18: .4byte 0x0002D034
_08015A1C: .4byte 0x0002D038
_08015A20: .4byte gWhitePaintFlags
_08015A24: .4byte gPaletteManager
_08015A28: .4byte 0x00000404
_08015A2C: .4byte 0x00000406
_08015A30: .4byte gVideoRegBuffer+12
_08015A34: .4byte 0x0002D03C
_08015A38: .4byte 0xFFFB0000
_08015A3C:
	ldr r3, _08015B74 @ =0x0002C002
	adds r0, r5, r3
	ldrh r0, [r0]
	cmp r0, #0
	beq _08015A7A
	movs r4, #0
	lsrs r0, r2, #0x14
	lsls r0, r0, #1
	ldr r1, _08015B78 @ =gVideoRegBuffer+4
	adds r0, r0, r1
	ldrh r0, [r0]
	movs r1, #0xf8
	lsls r1, r1, #5
	ands r1, r0
	lsls r1, r1, #3
	movs r0, #0xc0
	lsls r0, r0, #0x13
	adds r1, r1, r0
	str r4, [sp, #4]
	ldr r2, _08015B7C @ =0x01000400
	add r0, sp, #4
	bl CpuFastSet
	lsls r0, r7, #0x18
	lsrs r0, r0, #0x18
	ldr r1, _08015B80 @ =gBgMapOffsets
	str r4, [sp]
	movs r2, #0x4a
	movs r3, #0
	bl LoadBgMap
_08015A7A:
	ldr r4, _08015B84 @ =0x0002D040
	adds r0, r5, r4
	ldr r3, [r0]
	cmp r3, #0
	beq _08015AC4
	ldr r0, _08015B88 @ =0x0002D04C
	adds r1, r5, r0
	ldr r2, _08015B8C @ =0x0002D044
	adds r0, r5, r2
	ldr r2, [r0]
	ldr r0, [r2]
	str r0, [r1]
	adds r4, #0x10
	adds r1, r5, r4
	ldr r0, [r2, #4]
	str r0, [r1]
	ldr r0, _08015B90 @ =gWhitePaintFlags
	ldrb r1, [r3, #0x1d]
	lsrs r2, r1, #5
	lsls r2, r2, #2
	adds r2, r2, r0
	movs r0, #0x1f
	ands r0, r1
	movs r1, #1
	lsls r1, r0
	ldr r0, [r2]
	ands r0, r1
	cmp r0, #0
	beq _08015AC4
	ldr r0, _08015B94 @ =gPaletteManager
	ldr r2, _08015B98 @ =0x00000404
	adds r1, r0, r2
	movs r2, #0x40
	strh r2, [r1]
	ldr r3, _08015B9C @ =0x00000406
	adds r0, r0, r3
	strh r2, [r0]
_08015AC4:
	lsrs r3, r7, #4
	lsls r3, r3, #2
	ldr r2, _08015BA0 @ =gVideoRegBuffer+12
	adds r4, r3, r2
	mov r8, r4
	ldr r1, [r6, #0x34]
	ldr r4, _08015B88 @ =0x0002D04C
	adds r0, r5, r4
	ldr r0, [r0]
	asrs r0, r0, #8
	subs r1, r1, r0
	adds r1, #0x50
	ldr r0, [r6, #0x2c]
	asrs r0, r0, #8
	adds r1, r1, r0
	mov r0, r8
	strh r1, [r0]
	adds r2, #2
	adds r3, r3, r2
	ldr r1, [r6, #0x38]
	ldr r2, _08015BA4 @ =0x0002D050
	adds r0, r5, r2
	ldr r0, [r0]
	ldr r4, _08015BA8 @ =0xFFFB0000
	adds r0, r0, r4
	asrs r0, r0, #8
	movs r2, #0xa0
	lsls r2, r2, #3
	adds r0, r0, r2
	subs r1, r1, r0
	ldr r0, [r6, #0x30]
	asrs r0, r0, #8
	adds r0, #0x80
_08015B06:
	adds r1, r1, r0
	lsls r0, r1, #0x10
	lsrs r2, r0, #0x10
	strh r1, [r3]
	ldr r3, _08015BAC @ =0x0002D025
	adds r0, r5, r3
	ldrb r0, [r0]
	cmp r0, #0
	beq _08015BFC
	lsls r0, r2, #0x10
	asrs r3, r0, #0x10
	movs r1, #0xa0
	rsbs r1, r1, #0
	mov ip, r0
	cmp r3, r1
	ble _08015BFC
	ldr r2, _08015BB0 @ =gVideoRegBuffer
	lsls r0, r7, #8
	ldrh r1, [r2]
	orrs r0, r1
	movs r7, #0
	strh r0, [r2]
	movs r0, #0x20
	rsbs r0, r0, #0
	cmp r3, r0
	bge _08015BD4
	adds r0, r6, #0
	adds r0, #0x69
	ldrb r1, [r0]
	adds r4, r0, #0
	ldr r3, _08015BB4 @ =gWindowRegBuffer
	cmp r1, #0
	bne _08015BC6
	ldrh r0, [r3]
	movs r2, #0x80
	lsls r2, r2, #7
	adds r1, r2, #0
	orrs r0, r1
	strh r0, [r3]
	movs r2, #0xff
	strb r2, [r3, #0xd]
	ldrb r1, [r3, #0xe]
	movs r0, #0xe
	orrs r0, r1
	strb r0, [r3, #0xe]
	movs r0, #0xff
	strh r0, [r3, #6]
	ldr r1, _08015BB8 @ =0x0002D024
	adds r0, r5, r1
	ldrb r0, [r0]
	cmp r0, #0
	bne _08015BBC
	movs r0, #0xfb
	b _08015BBE
	.align 2, 0
_08015B74: .4byte 0x0002C002
_08015B78: .4byte gVideoRegBuffer+4
_08015B7C: .4byte 0x01000400
_08015B80: .4byte gBgMapOffsets
_08015B84: .4byte 0x0002D040
_08015B88: .4byte 0x0002D04C
_08015B8C: .4byte 0x0002D044
_08015B90: .4byte gWhitePaintFlags
_08015B94: .4byte gPaletteManager
_08015B98: .4byte 0x00000404
_08015B9C: .4byte 0x00000406
_08015BA0: .4byte gVideoRegBuffer+12
_08015BA4: .4byte 0x0002D050
_08015BA8: .4byte 0xFFFB0000
_08015BAC: .4byte 0x0002D025
_08015BB0: .4byte gVideoRegBuffer
_08015BB4: .4byte gWindowRegBuffer
_08015BB8: .4byte 0x0002D024
_08015BBC:
	movs r0, #0xf3
_08015BBE:
	ands r2, r0
	strb r2, [r3, #0xd]
	movs r0, #1
	strb r0, [r4]
_08015BC6:
	mov r2, ip
	asrs r0, r2, #0x10
	rsbs r0, r0, #0
	movs r1, #0xff
	ands r0, r1
	strh r0, [r3, #0xa]
	b _08015C26
_08015BD4:
	adds r3, r6, #0
	adds r3, #0x69
	ldrb r0, [r3]
	cmp r0, #0
	beq _08015C26
	ldr r1, _08015BF4 @ =gWindowRegBuffer
	ldrh r2, [r1]
	ldr r0, _08015BF8 @ =0x0000BFFF
	ands r0, r2
	strh r0, [r1]
	ldrb r2, [r1, #0xe]
	movs r0, #0xe
	orrs r0, r2
	strb r0, [r1, #0xe]
	strb r7, [r3]
	b _08015C26
	.align 2, 0
_08015BF4: .4byte gWindowRegBuffer
_08015BF8: .4byte 0x0000BFFF
_08015BFC:
	ldr r2, _08015C34 @ =gVideoRegBuffer
	lsls r1, r7, #8
	ldrh r0, [r2]
	bics r0, r1
	strh r0, [r2]
	adds r3, r6, #0
	adds r3, #0x69
	ldrb r0, [r3]
	cmp r0, #0
	beq _08015C26
	ldr r1, _08015C38 @ =gWindowRegBuffer
	ldrh r2, [r1]
	ldr r0, _08015C3C @ =0x0000BFFF
	ands r0, r2
	strh r0, [r1]
	ldrb r2, [r1, #0xe]
	movs r0, #0xe
	orrs r0, r2
	strb r0, [r1, #0xe]
	movs r0, #0
	strb r0, [r3]
_08015C26:
	add sp, #0xc
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_08015C34: .4byte gVideoRegBuffer
_08015C38: .4byte gWindowRegBuffer
_08015C3C: .4byte 0x0000BFFF
