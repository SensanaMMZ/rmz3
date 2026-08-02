	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_08010044
FUN_08010044: @ 0x08010044
	push {r4, r5, r6, r7, lr}
	ldr r1, [r0, #0x5c]
	lsls r1, r1, #0x10
	lsrs r6, r1, #0x10
	movs r7, #0x20
	ldr r0, [r0, #0x38]
	ldr r2, _08010094 @ =0xFFFFFE20
	adds r0, r0, r2
	lsls r0, r0, #0x10
	lsrs r5, r0, #0x10
	lsrs r1, r1, #0x14
	lsls r4, r1, #2
	ldr r2, _08010098 @ =gVideoRegBuffer+12
	adds r3, r4, r2
	movs r0, #0
	strh r0, [r3]
	adds r0, r2, #2
	adds r4, r4, r0
	strh r5, [r4]
	lsls r1, r1, #1
	subs r2, #8
	adds r2, r1, r2
	ldrh r1, [r2]
	ldr r3, _0801009C @ =0x0000FFFC
	adds r0, r3, #0
	ands r0, r1
	movs r1, #2
	orrs r0, r1
	strh r0, [r2]
	ldr r0, _080100A0 @ =gOverworld
	ldr r1, _080100A4 @ =0x0002D02A
	adds r0, r0, r1
	ldrb r0, [r0]
	cmp r0, #0
	bne _080100A8
	ldrh r0, [r4]
	subs r0, #0x80
	strh r0, [r4]
	b _080100D8
	.align 2, 0
_08010094: .4byte 0xFFFFFE20
_08010098: .4byte gVideoRegBuffer+12
_0801009C: .4byte 0x0000FFFC
_080100A0: .4byte gOverworld
_080100A4: .4byte 0x0002D02A
_080100A8:
	cmp r0, #1
	bne _080100B6
	ldrh r0, [r4]
	subs r0, #0x40
	strh r0, [r4]
	movs r7, #0x40
	b _080100D8
_080100B6:
	cmp r0, #2
	bne _080100C2
	ldrh r0, [r4]
	subs r0, #0x20
	strh r0, [r4]
	b _080100D8
_080100C2:
	cmp r0, #4
	bne _080100D8
	ldrh r0, [r4]
	adds r0, #0x20
	strh r0, [r4]
	ldrh r1, [r2]
	adds r0, r3, #0
	ands r0, r1
	movs r1, #1
	orrs r0, r1
	strh r0, [r2]
_080100D8:
	movs r3, #0xa0
	subs r1, r3, r7
	lsls r0, r5, #0x10
	asrs r0, r0, #0x10
	subs r1, r1, r0
	lsls r1, r1, #0x10
	lsrs r5, r1, #0x10
	asrs r1, r1, #0x10
	cmp r1, #0x9f
	ble _080100FC
	ldr r2, _080100F8 @ =gVideoRegBuffer
	lsls r1, r6, #8
	ldrh r0, [r2]
	bics r0, r1
	strh r0, [r2]
	b _08010110
	.align 2, 0
_080100F8: .4byte gVideoRegBuffer
_080100FC:
	ldr r2, _08010118 @ =gVideoRegBuffer
	lsls r0, r6, #8
	ldrh r1, [r2]
	orrs r0, r1
	strh r0, [r2]
	ldr r1, _0801011C @ =gWindowRegBuffer
	lsls r0, r5, #0x10
	asrs r0, r0, #8
	orrs r0, r3
	strh r0, [r1, #0xa]
_08010110:
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_08010118: .4byte gVideoRegBuffer
_0801011C: .4byte gWindowRegBuffer
