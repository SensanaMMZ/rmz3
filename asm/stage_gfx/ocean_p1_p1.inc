	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start ocean_0800d110
ocean_0800d110: @ 0x0800D110
	push {r4, r5, r6, r7, lr}
	adds r7, r0, #0
	ldrb r4, [r7, #0xe]
	cmp r4, #0
	bne _0800D18E
	ldr r0, [r7, #0x5c]
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x14
	lsls r5, r0, #1
	ldr r3, _0800D1A0 @ =gVideoRegBuffer+4
	adds r5, r5, r3
	ldr r1, [r7, #0x60]
	ldr r2, [r7, #0x64]
	orrs r1, r2
	ldr r6, _0800D1A4 @ =0x00008044
	adds r2, r6, #0
	orrs r1, r2
	strh r1, [r5]
	lsls r0, r0, #2
	adds r3, #8
	adds r0, r0, r3
	str r4, [r0]
	ldr r0, _0800D1A8 @ =0x08522354
	ldr r0, [r0]
	ldr r2, _0800D1AC @ =0x0852235C
	adds r0, r0, r2
	movs r4, #0xf8
	lsls r4, r4, #5
	ands r1, r4
	lsls r1, r1, #3
	movs r2, #0xc0
	lsls r2, r2, #0x13
	adds r1, r1, r2
	movs r6, #0x80
	lsls r6, r6, #2
	adds r2, r6, #0
	bl CpuFastSet
	ldr r0, _0800D1B0 @ =0x08522358
	ldr r0, [r0]
	ldr r1, _0800D1B4 @ =0x08522360
	adds r0, r0, r1
	ldrh r1, [r5]
	ands r4, r1
	lsls r4, r4, #3
	ldr r2, _0800D1B8 @ =0x06000800
	adds r4, r4, r2
	adds r1, r4, #0
	adds r2, r6, #0
	bl CpuFastSet
	ldr r1, _0800D1BC @ =gBlendRegBuffer
	movs r2, #0
	ldr r0, _0800D1C0 @ =0x00003B44
	strh r0, [r1]
	ldr r0, _0800D1C4 @ =0x00000C04
	strh r0, [r1, #2]
	adds r0, r7, #0
	adds r0, #0x68
	strb r2, [r0]
	ldrb r0, [r7, #0xe]
	adds r0, #1
	strb r0, [r7, #0xe]
_0800D18E:
	adds r1, r7, #0
	adds r1, #0x68
	ldrb r0, [r1]
	adds r0, #1
	strb r0, [r1]
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_0800D1A0: .4byte gVideoRegBuffer+4
_0800D1A4: .4byte 0x00008044
_0800D1A8: .4byte 0x08522354
_0800D1AC: .4byte 0x0852235C
_0800D1B0: .4byte 0x08522358
_0800D1B4: .4byte 0x08522360
_0800D1B8: .4byte 0x06000800
_0800D1BC: .4byte gBlendRegBuffer
_0800D1C0: .4byte 0x00003B44
_0800D1C4: .4byte 0x00000C04

	thumb_func_start FUN_0800d1c8
FUN_0800d1c8: @ 0x0800D1C8
	push {r4, r5, r6, lr}
	adds r5, r0, #0
	ldr r0, [r5, #0x5c]
	lsls r0, r0, #0x10
	lsrs r3, r0, #0x10
	ldr r0, _0800D22C @ =gOverworld
	ldr r1, _0800D230 @ =0x0002C00C
	adds r0, r0, r1
	ldr r0, [r0]
	asrs r0, r0, #8
	ldr r1, [r5, #0x38]
	subs r1, r1, r0
	ldr r2, _0800D234 @ =gSineTable
	adds r0, r5, #0
	adds r0, #0x68
	ldrb r0, [r0]
	lsls r0, r0, #1
	adds r0, r0, r2
	ldrh r0, [r0]
	lsls r0, r0, #0x10
	asrs r0, r0, #0x16
	subs r0, #5
	subs r4, r1, r0
	movs r0, #0xb4
	rsbs r0, r0, #0
	cmp r4, r0
	bge _0800D200
	adds r4, r0, #0
_0800D200:
	cmp r4, #0
	bge _0800D23C
	ldr r1, _0800D238 @ =gWindowRegBuffer
	ldrh r2, [r1]
	movs r6, #0x80
	lsls r6, r6, #7
	adds r0, r6, #0
	orrs r0, r2
	strh r0, [r1]
	movs r0, #0xfb
	strb r0, [r1, #0xd]
	ldrb r2, [r1, #0xe]
	movs r0, #0xe
	orrs r0, r2
	strb r0, [r1, #0xe]
	movs r2, #0xff
	movs r0, #0xff
	strh r0, [r1, #6]
	rsbs r0, r4, #0
	ands r0, r2
	b _0800D240
	.align 2, 0
_0800D22C: .4byte gOverworld
_0800D230: .4byte 0x0002C00C
_0800D234: .4byte gSineTable
_0800D238: .4byte gWindowRegBuffer
_0800D23C:
	ldr r1, _0800D25C @ =gWindowRegBuffer
	movs r0, #0
_0800D240:
	strh r0, [r1, #0xa]
	lsrs r2, r3, #4
	lsls r2, r2, #2
	ldr r0, _0800D260 @ =gVideoRegBuffer+12
	adds r3, r2, r0
	ldr r1, [r5, #0x34]
	strh r1, [r3]
	adds r0, #2
	adds r2, r2, r0
	strh r4, [r2]
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_0800D25C: .4byte gWindowRegBuffer
_0800D260: .4byte gVideoRegBuffer+12
