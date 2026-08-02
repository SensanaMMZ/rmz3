	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start phantomMinigame_080fc1b8
phantomMinigame_080fc1b8: @ 0x080FC1B8
	push {r4, r5, r6, lr}
	adds r6, r0, #0
	ldr r0, _080FC2E4 @ =0x00000DCC
	adds r5, r6, r0
	ldr r1, _080FC2E8 @ =gJoypad
	ldrh r0, [r1]
	movs r4, #0
	strh r0, [r5, #0x10]
	ldrh r0, [r1, #4]
	strh r0, [r5, #0x12]
	ldr r3, [r5, #8]
	ldr r1, _080FC2EC @ =0x00000DC4
	adds r2, r6, r1
	ldr r0, [r3, #0x54]
	ldr r1, [r2]
	cmp r0, r1
	bgt _080FC1DC
	b _080FC358
_080FC1DC:
	subs r1, r0, r1
	ldr r0, [r5, #0x30]
	adds r0, r0, r1
	str r0, [r5, #0x30]
	ldr r1, [r3, #0x54]
	ldr r0, [r2]
	subs r1, r1, r0
	ldr r0, [r5, #4]
	adds r0, r0, r1
	str r0, [r5, #4]
	ldr r1, [r3, #0x54]
	ldr r0, [r2]
	subs r1, r1, r0
	ldr r0, [r5, #0x1c]
	adds r0, r0, r1
	str r0, [r5, #0x1c]
	ldr r1, [r3, #0x54]
	ldr r0, [r2]
	subs r1, r1, r0
	ldr r0, [r5, #0x24]
	adds r0, r0, r1
	str r0, [r5, #0x24]
	ldr r1, [r5, #0x28]
	cmp r0, r1
	blt _080FC24A
	ldr r2, _080FC2F0 @ =0xFFFFFF00
	adds r1, r1, r2
	str r1, [r5, #0x28]
	ldr r0, _080FC2F4 @ =0x00003BFF
	cmp r1, r0
	bgt _080FC21E
	adds r0, #1
	str r0, [r5, #0x28]
_080FC21E:
	ldr r1, [r5, #4]
	movs r0, #0xa7
	lsls r0, r0, #0xc
	adds r1, r1, r0
	ldr r3, _080FC2F8 @ =RNG_0202f388
	ldr r2, [r3]
	ldr r0, _080FC2FC @ =0x000343FD
	muls r2, r0, r2
	ldr r0, _080FC300 @ =0x00269EC3
	adds r2, r2, r0
	lsls r2, r2, #1
	lsrs r0, r2, #1
	str r0, [r3]
	lsls r2, r2, #1
	lsrs r2, r2, #0x12
	movs r0, #0xba
	lsls r0, r0, #0xb
	adds r2, r2, r0
	adds r0, r5, #0
	bl CreateIronStar
	str r4, [r5, #0x24]
_080FC24A:
	ldr r1, [r5, #0x1c]
	ldr r0, [r5, #0x20]
	adds r2, r0, #0
	cmp r1, r2
	blt _080FC2CE
	ldrh r0, [r5, #0x2c]
	adds r0, #1
	strh r0, [r5, #0x2c]
	lsls r0, r0, #0x10
	asrs r0, r0, #0x10
	movs r1, #0x80
	lsls r1, r1, #2
	cmp r0, r1
	ble _080FC268
	strh r1, [r5, #0x2c]
_080FC268:
	ldr r0, _080FC2F0 @ =0xFFFFFF00
	adds r1, r2, r0
	str r1, [r5, #0x20]
	ldr r0, _080FC304 @ =0x00004FFF
	cmp r1, r0
	bgt _080FC278
	adds r0, #1
	str r0, [r5, #0x20]
_080FC278:
	ldr r2, [r5, #0x18]
	ldr r1, _080FC308 @ =0xFFFFE000
	adds r2, r2, r1
	ldr r3, _080FC2F8 @ =RNG_0202f388
	ldr r1, [r3]
	ldr r0, _080FC2FC @ =0x000343FD
	muls r0, r1, r0
	ldr r1, _080FC300 @ =0x00269EC3
	adds r0, r0, r1
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r3]
	lsls r0, r0, #1
	lsrs r0, r0, #0x12
	adds r2, r2, r0
	str r2, [r5, #0x18]
	ldr r0, _080FC30C @ =0x0005DFFF
	cmp r2, r0
	bgt _080FC2A2
	adds r0, #1
	str r0, [r5, #0x18]
_080FC2A2:
	ldr r0, [r5, #0x18]
	movs r1, #0xc6
	lsls r1, r1, #0xb
	cmp r0, r1
	ble _080FC2AE
	str r1, [r5, #0x18]
_080FC2AE:
	ldr r1, [r5, #4]
	movs r2, #0xa7
	lsls r2, r2, #0xc
	adds r1, r1, r2
	ldr r2, [r5, #0x18]
	adds r0, r5, #0
	movs r3, #0
	bl FUN_080d91b4
	adds r1, r5, #0
	adds r1, #0xd4
	ldrb r0, [r1]
	adds r0, #1
	strb r0, [r1]
	movs r0, #0
	str r0, [r5, #0x1c]
_080FC2CE:
	ldr r4, [r5, #4]
	movs r1, #0xf0
	lsls r1, r1, #8
	adds r0, r4, #0
	bl __modsi3
	cmp r0, r4
	bge _080FC314
	ldr r0, _080FC310 @ =0xFFFF1000
	b _080FC316
	.align 2, 0
_080FC2E4: .4byte 0x00000DCC
_080FC2E8: .4byte gJoypad
_080FC2EC: .4byte 0x00000DC4
_080FC2F0: .4byte 0xFFFFFF00
_080FC2F4: .4byte 0x00003BFF
_080FC2F8: .4byte RNG_0202f388
_080FC2FC: .4byte 0x000343FD
_080FC300: .4byte 0x00269EC3
_080FC304: .4byte 0x00004FFF
_080FC308: .4byte 0xFFFFE000
_080FC30C: .4byte 0x0005DFFF
_080FC310: .4byte 0xFFFF1000
_080FC314:
	movs r0, #0
_080FC316:
	str r0, [r5, #0x14]
	movs r1, #0xf0
	lsls r1, r1, #8
	adds r0, r4, #0
	bl __modsi3
	str r0, [r5, #4]
	ldr r0, _080FC34C @ =0x00000DC4
	adds r2, r6, r0
	ldr r1, _080FC350 @ =0x0009D800
	str r1, [r2]
	ldr r0, [r5, #4]
	adds r0, r0, r1
	str r0, [r2]
	ldr r1, [r5, #0x30]
	movs r0, #0x80
	lsls r0, r0, #5
	cmp r1, r0
	ble _080FC35A
	ldr r2, _080FC354 @ =0xFFFFF000
	adds r0, r1, r2
	str r0, [r5, #0x30]
	ldr r0, [r5, #0x34]
	adds r0, #1
	str r0, [r5, #0x34]
	b _080FC35A
	.align 2, 0
_080FC34C: .4byte 0x00000DC4
_080FC350: .4byte 0x0009D800
_080FC354: .4byte 0xFFFFF000
_080FC358:
	str r4, [r5, #0x14]
_080FC35A:
	ldr r0, [r5, #8]
	ldr r1, [r0, #0x58]
	movs r0, #0xd2
	lsls r0, r0, #0xb
	cmp r1, r0
	bgt _080FC370
	adds r0, r5, #0
	adds r0, #0xd5
	ldrb r0, [r0]
	cmp r0, #0
	bne _080FC386
_080FC370:
	adds r2, r5, #0
	adds r2, #0xd6
	movs r1, #0
	movs r0, #1
	strb r0, [r2]
	ldrb r0, [r5]
	adds r0, #1
	strb r0, [r5]
	strb r1, [r5, #1]
	strb r1, [r5, #2]
	strb r1, [r5, #3]
_080FC386:
	movs r0, #1
	pop {r4, r5, r6}
	pop {r1}
	bx r1
	.align 2, 0
