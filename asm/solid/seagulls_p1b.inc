	.include "asm/macros.inc"

	.syntax unified
	
	.text


	thumb_func_start FUN_080dd11c
FUN_080dd11c: @ 0x080DD11C
	push {r4, r5, r6, lr}
	adds r5, r0, #0
	ldrb r1, [r5, #0xe]
	cmp r1, #0
	bne _080DD134
	ldr r0, [r5, #0x28]
	ldrb r0, [r0, #0xc]
	cmp r0, #1
	bls _080DD138
	adds r0, r1, #1
	strb r0, [r5, #0xe]
	b _080DD138
_080DD134:
	movs r0, #0xf
	strb r0, [r5, #0x12]
_080DD138:
	adds r0, r5, #0
	bl UpdateMotionGraphic
	ldrb r4, [r5, #0xd]
	cmp r4, #1
	bne _080DD146
	b _080DD260
_080DD146:
	cmp r4, #1
	bgt _080DD150
	cmp r4, #0
	beq _080DD158
	b _080DD352
_080DD150:
	cmp r4, #2
	bne _080DD156
	b _080DD2B4
_080DD156:
	b _080DD352
_080DD158:
	ldr r0, [r5, #0x54]
	ldr r2, [r5, #0x5c]
	adds r0, r0, r2
	str r0, [r5, #0x54]
	ldrb r1, [r5, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _080DD1AE
	ldr r0, _080DD178 @ =0x000001BF
	cmp r2, r0
	bgt _080DD17C
	adds r0, r2, #4
	str r0, [r5, #0x5c]
	b _080DD198
	.align 2, 0
_080DD178: .4byte 0x000001BF
_080DD17C:
	adds r0, r5, #0
	adds r0, #0x71
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	cmp r0, #3
	bne _080DD198
	movs r1, #0xda
	lsls r1, r1, #8
	adds r0, r5, #0
	movs r2, #3
	movs r3, #4
	bl GotoMotion
_080DD198:
	ldrb r0, [r5, #0x12]
	ldr r6, [r5, #0x54]
	adds r4, r0, #0
	cmp r4, #0xf
	beq _080DD206
	adds r0, r5, #0
	adds r0, #0xb8
	ldr r0, [r0]
	cmp r0, r6
	bge _080DD200
	b _080DD1F0
_080DD1AE:
	ldr r0, _080DD1BC @ =0xFFFFFE40
	cmp r2, r0
	ble _080DD1C0
	subs r0, r2, #4
	str r0, [r5, #0x5c]
	b _080DD1DC
	.align 2, 0
_080DD1BC: .4byte 0xFFFFFE40
_080DD1C0:
	adds r0, r5, #0
	adds r0, #0x71
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	cmp r0, #3
	bne _080DD1DC
	movs r1, #0xda
	lsls r1, r1, #8
	adds r0, r5, #0
	movs r2, #3
	movs r3, #4
	bl GotoMotion
_080DD1DC:
	ldrb r0, [r5, #0x12]
	ldr r6, [r5, #0x54]
	adds r4, r0, #0
	cmp r4, #0xf
	beq _080DD206
	adds r0, r5, #0
	adds r0, #0xb8
	ldr r0, [r0]
	cmp r0, r6
	ble _080DD200
_080DD1F0:
	ldr r0, [r5, #0x5c]
	movs r1, #0x18
	bl __divsi3
	str r0, [r5, #0x64]
	ldrb r0, [r5, #0xd]
	adds r0, #1
	strb r0, [r5, #0xd]
_080DD200:
	cmp r4, #0xf
	beq _080DD206
	b _080DD352
_080DD206:
	ldrb r1, [r5, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _080DD230
	movs r0, #0x8a
	lsls r0, r0, #0xb
	cmp r6, r0
	bgt _080DD23E
	ldr r0, _080DD228 @ =gStageRun+232
	ldr r0, [r0, #0x38]
	ldr r1, _080DD22C @ =0x000097FF
	adds r0, r0, r1
	cmp r6, r0
	bgt _080DD226
	b _080DD352
_080DD226:
	b _080DD23E
	.align 2, 0
_080DD228: .4byte gStageRun+232
_080DD22C: .4byte 0x000097FF
_080DD230:
	ldr r0, _080DD254 @ =gStageRun+232
	ldr r0, [r0, #0x38]
	ldr r1, _080DD258 @ =0xFFFF6800
	adds r0, r0, r1
	cmp r6, r0
	blt _080DD23E
	b _080DD352
_080DD23E:
	ldr r1, _080DD25C @ =gSolidFnTable
	ldrb r0, [r5, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r5, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r5, #0x14]
	b _080DD352
	.align 2, 0
_080DD254: .4byte gStageRun+232
_080DD258: .4byte 0xFFFF6800
_080DD25C: .4byte gSolidFnTable
_080DD260:
	ldr r1, _080DD27C @ =0x0000DA01
	adds r0, r5, #0
	bl SetMotion
	ldrb r1, [r5, #0xa]
	lsrs r0, r1, #4
	adds r2, r4, #0
	bics r2, r0
	cmp r2, #0
	beq _080DD280
	movs r0, #0x10
	orrs r0, r1
	b _080DD284
	.align 2, 0
_080DD27C: .4byte 0x0000DA01
_080DD280:
	movs r0, #0xef
	ands r0, r1
_080DD284:
	strb r0, [r5, #0xa]
	movs r1, #1
	ands r1, r2
	adds r0, r5, #0
	adds r0, #0x4c
	strb r1, [r0]
	adds r3, r5, #0
	adds r3, #0x4a
	lsls r1, r1, #4
	ldrb r2, [r3]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r1
	strb r0, [r3]
	adds r0, r5, #0
	bl UpdateMotionGraphic
	ldrb r0, [r5, #0x12]
	adds r0, #1
	strb r0, [r5, #0x12]
	ldrb r0, [r5, #0xd]
	adds r0, #1
	strb r0, [r5, #0xd]
_080DD2B4:
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x5c]
	adds r0, r0, r1
	str r0, [r5, #0x54]
	ldr r0, [r5, #0x64]
	subs r1, r1, r0
	str r1, [r5, #0x5c]
	adds r0, r5, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _080DD352
	movs r1, #0xda
	lsls r1, r1, #8
	adds r0, r5, #0
	bl SetMotion
	adds r0, r5, #0
	bl UpdateMotionGraphic
	ldrb r1, [r5, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _080DD320
	adds r4, r5, #0
	adds r4, #0xb8
	adds r3, r5, #0
	adds r3, #0xb4
	ldr r2, _080DD314 @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _080DD318 @ =0x000343FD
	muls r0, r1, r0
	ldr r1, _080DD31C @ =0x00269EC3
	adds r0, r0, r1
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r2]
	lsrs r0, r0, #0x11
	movs r1, #0x3f
	ands r0, r1
	lsls r0, r0, #8
	movs r1, #0x80
	lsls r1, r1, #6
	adds r0, r0, r1
	ldr r1, [r3]
	adds r1, r1, r0
	b _080DD34C
	.align 2, 0
_080DD314: .4byte RNG_0202f388
_080DD318: .4byte 0x000343FD
_080DD31C: .4byte 0x00269EC3
_080DD320:
	adds r4, r5, #0
	adds r4, #0xb8
	adds r3, r5, #0
	adds r3, #0xb4
	ldr r2, _080DD358 @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _080DD35C @ =0x000343FD
	muls r0, r1, r0
	ldr r1, _080DD360 @ =0x00269EC3
	adds r0, r0, r1
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r2]
	lsrs r0, r0, #0x11
	movs r1, #0x3f
	ands r0, r1
	lsls r0, r0, #8
	movs r1, #0x80
	lsls r1, r1, #6
	adds r0, r0, r1
	ldr r1, [r3]
	subs r1, r1, r0
_080DD34C:
	str r1, [r4]
	movs r0, #0
	strb r0, [r5, #0xd]
_080DD352:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_080DD358: .4byte RNG_0202f388
_080DD35C: .4byte 0x000343FD
_080DD360: .4byte 0x00269EC3
