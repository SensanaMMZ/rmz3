	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start glacierle_08057f38
glacierle_08057f38: @ 0x08057F38
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #1
	beq _08057F60
	cmp r0, #1
	bgt _08057F4C
	cmp r0, #0
	beq _08057F52
	b _08058010
_08057F4C:
	cmp r0, #2
	beq _08057FA8
	b _08058010
_08057F52:
	ldr r1, _08057F9C @ =0x0000B201
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08057F60:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _08057F76
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08057F76:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r2, _08057FA0 @ =0x08364AAE
	adds r1, r4, #0
	adds r1, #0x71
	ldrb r1, [r1]
	lsls r1, r1, #0x18
	asrs r1, r1, #0x18
	adds r1, r1, r2
	ldrb r2, [r1]
	lsls r1, r2, #1
	adds r1, r1, r2
	lsls r1, r1, #3
	ldr r2, _08057FA4 @ =sCollisions
	adds r1, r1, r2
	bl SetDDP
	b _08058010
	.align 2, 0
_08057F9C: .4byte 0x0000B201
_08057FA0: .4byte 0x08364AAE
_08057FA4: .4byte sCollisions
_08057FA8:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _08057FEC @ =0x08363DE4
	bl SetDDP
	ldrb r0, [r4, #0xa]
	lsrs r0, r0, #4
	movs r2, #1
	eors r0, r2
	ands r0, r2
	adds r1, r4, #0
	adds r1, #0x4c
	strb r0, [r1]
	ldrb r1, [r4, #0xa]
	lsrs r1, r1, #4
	eors r1, r2
	ands r1, r2
	movs r0, #0x4a
	adds r0, r0, r4
	mov ip, r0
	lsls r3, r1, #4
	ldrb r2, [r0]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r3
	mov r2, ip
	strb r0, [r2]
	cmp r1, #0
	beq _08057FF0
	ldrb r0, [r4, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _08057FF6
	.align 2, 0
_08057FEC: .4byte 0x08363DE4
_08057FF0:
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
_08057FF6:
	strb r0, [r4, #0xa]
	movs r1, #0xb2
	lsls r1, r1, #8
	adds r0, r4, #0
	bl SetMotion
	adds r0, r4, #0
	bl UpdateMotionGraphic
	movs r0, #0
	strb r0, [r4, #0xd]
	movs r0, #1
	strb r0, [r4, #0xe]
_08058010:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start glacierle_08058018
glacierle_08058018: @ 0x08058018
	push {r4, r5, r6, lr}
	adds r4, r0, #0
	ldrb r5, [r4, #0xe]
	cmp r5, #0
	beq _08058028
	cmp r5, #1
	beq _08058098
	b _08058162
_08058028:
	ldr r2, [r4, #0x54]
	ldr r0, _08058068 @ =0xFFFFCE00
	adds r3, r2, r0
	ldrb r1, [r4, #0xa]
	movs r6, #0x10
	adds r0, r6, #0
	ands r0, r1
	cmp r0, #0
	beq _08058040
	movs r0, #0xc8
	lsls r0, r0, #6
	adds r3, r2, r0
_08058040:
	ldr r1, [r4, #0x58]
	ldr r0, _0805806C @ =0xFFFFF000
	adds r1, r1, r0
	adds r0, r3, #0
	bl FUN_080098a4
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _08058070
	adds r0, r4, #0
	bl UpdateMotionGraphic
	strb r5, [r4, #0xd]
	strb r5, [r4, #0xe]
	adds r1, r4, #0
	adds r1, #0xc1
	movs r0, #0xa
	strb r0, [r1]
	b _08058162
	.align 2, 0
_08058068: .4byte 0xFFFFCE00
_0805806C: .4byte 0xFFFFF000
_08058070:
	movs r0, #0x80
	strb r0, [r4, #0x12]
	movs r0, #0xc0
	rsbs r0, r0, #0
	str r0, [r4, #0x5c]
	adds r2, r0, #0
	ldrb r1, [r4, #0xa]
	adds r0, r6, #0
	ands r0, r1
	cmp r0, #0
	beq _08058088
	movs r2, #0xc0
_08058088:
	str r2, [r4, #0x5c]
	ldr r1, _08058138 @ =0x0000B205
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08058098:
	movs r6, #0
	ldr r2, [r4, #0x54]
	ldr r0, _0805813C @ =0xFFFFCE00
	adds r3, r2, r0
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _080580B0
	movs r0, #0xc8
	lsls r0, r0, #6
	adds r3, r2, r0
_080580B0:
	ldr r1, [r4, #0x58]
	ldr r0, _08058140 @ =0xFFFFF000
	adds r1, r1, r0
	adds r0, r3, #0
	bl FUN_080098a4
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _080580C4
	movs r6, #1
_080580C4:
	ldrb r0, [r4, #0x12]
	cmp r0, #0
	beq _080580CE
	subs r0, #1
	strb r0, [r4, #0x12]
_080580CE:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x71
	movs r1, #0
	ldrsb r1, [r0, r1]
	adds r5, r0, #0
	cmp r1, #1
	beq _080580F2
	cmp r1, #5
	beq _080580F2
	cmp r6, #0
	bne _080580F2
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	adds r0, r0, r1
	str r0, [r4, #0x54]
_080580F2:
	ldr r1, [r4, #0x70]
	ldr r0, _08058144 @ =0x00FFFF00
	ands r1, r0
	movs r0, #0x80
	lsls r0, r0, #9
	cmp r1, r0
	beq _08058108
	movs r0, #0x82
	lsls r0, r0, #9
	cmp r1, r0
	bne _0805810E
_08058108:
	movs r0, #0x8c
	bl PlaySound
_0805810E:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r2, _08058148 @ =0x08364AB1
	movs r1, #0
	ldrsb r1, [r5, r1]
	adds r1, r1, r2
	ldrb r2, [r1]
	lsls r1, r2, #1
	adds r1, r1, r2
	lsls r1, r1, #3
	ldr r2, _0805814C @ =sCollisions
	adds r1, r1, r2
	bl SetDDP
	cmp r6, #0
	beq _08058150
	movs r0, #0
	strb r0, [r4, #0xd]
	strb r0, [r4, #0xe]
	b _08058162
	.align 2, 0
_08058138: .4byte 0x0000B205
_0805813C: .4byte 0xFFFFCE00
_08058140: .4byte 0xFFFFF000
_08058144: .4byte 0x00FFFF00
_08058148: .4byte 0x08364AB1
_0805814C: .4byte sCollisions
_08058150:
	ldrb r1, [r4, #0x12]
	cmp r1, #0
	bne _08058162
	movs r0, #0
	ldrsb r0, [r5, r0]
	cmp r0, #2
	bne _08058162
	strb r1, [r4, #0xd]
	strb r1, [r4, #0xe]
_08058162:
	pop {r4, r5, r6}
	pop {r0}
	bx r0

	thumb_func_start glacierle_08058168
glacierle_08058168: @ 0x08058168
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _08058178
	cmp r0, #1
	beq _0805818C
	b _080581C6
_08058178:
	movs r0, #0x90
	bl PlaySound
	ldr r1, _080581CC @ =0x0000B206
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0805818C:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _080581A4
	movs r1, #0
	movs r0, #5
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_080581A4:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r2, _080581D0 @ =0x08364AB9
	adds r1, r4, #0
	adds r1, #0x71
	ldrb r1, [r1]
	lsls r1, r1, #0x18
	asrs r1, r1, #0x18
	adds r1, r1, r2
	ldrb r2, [r1]
	lsls r1, r2, #1
	adds r1, r1, r2
	lsls r1, r1, #3
	ldr r2, _080581D4 @ =sCollisions
	adds r1, r1, r2
	bl SetDDP
_080581C6:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080581CC: .4byte 0x0000B206
_080581D0: .4byte 0x08364AB9
_080581D4: .4byte sCollisions

	thumb_func_start glacierle_080581d8
glacierle_080581d8: @ 0x080581D8
	push {r4, r5, lr}
	adds r5, r0, #0
	ldrb r0, [r5, #0xe]
	cmp r0, #1
	beq _08058284
	cmp r0, #1
	bgt _080581EC
	cmp r0, #0
	beq _080581FA
	b _0805835E
_080581EC:
	cmp r0, #2
	bne _080581F2
	b _08058318
_080581F2:
	cmp r0, #3
	bne _080581F8
	b _08058322
_080581F8:
	b _0805835E
_080581FA:
	ldr r1, _08058244 @ =0x0000B207
	adds r0, r5, #0
	bl SetMotion
	movs r4, #0x80
	lsls r4, r4, #3
	adds r0, r4, #0
	bl Sqrt
	strb r0, [r5, #0x12]
	adds r0, r4, #0
	bl Sqrt
	lsls r0, r0, #0x10
	lsrs r0, r0, #0xb
	rsbs r0, r0, #0
	str r0, [r5, #0x60]
	ldr r0, _08058248 @ =pZero2
	ldr r0, [r0]
	ldr r1, [r0, #0x54]
	ldr r0, [r5, #0x54]
	subs r4, r1, r0
	ldrb r1, [r5, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	bne _08058254
	ldr r0, _0805824C @ =0xFFFF8000
	cmp r4, r0
	bge _08058238
	adds r4, r0, #0
_08058238:
	ldr r0, _08058250 @ =0xFFFFE000
	cmp r4, r0
	ble _08058268
	adds r4, r0, #0
	b _08058268
	.align 2, 0
_08058244: .4byte 0x0000B207
_08058248: .4byte pZero2
_0805824C: .4byte 0xFFFF8000
_08058250: .4byte 0xFFFFE000
_08058254:
	movs r0, #0x80
	lsls r0, r0, #8
	cmp r4, r0
	ble _0805825E
	adds r4, r0, #0
_0805825E:
	ldr r0, _08058304 @ =0x00001FFF
	cmp r4, r0
	bgt _08058268
	movs r4, #0x80
	lsls r4, r4, #6
_08058268:
	movs r0, #0x80
	lsls r0, r0, #3
	bl Sqrt
	adds r1, r0, #0
	lsls r1, r1, #0x10
	lsrs r1, r1, #0x10
	adds r0, r4, #0
	bl __divsi3
	str r0, [r5, #0x5c]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_08058284:
	ldrb r0, [r5, #0x12]
	subs r0, #1
	strb r0, [r5, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _08058296
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_08058296:
	ldr r1, [r5, #0x54]
	ldr r0, _08058308 @ =0xFFFFE600
	adds r2, r1, r0
	ldr r0, [r5, #0x5c]
	cmp r0, #0
	ble _080582A8
	movs r0, #0xd0
	lsls r0, r0, #5
	adds r2, r1, r0
_080582A8:
	ldr r1, [r5, #0x58]
	ldr r0, _0805830C @ =0xFFFFF000
	adds r1, r1, r0
	adds r0, r2, #0
	bl FUN_080098a4
	lsls r0, r0, #0x10
	cmp r0, #0
	bne _080582C2
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x5c]
	adds r0, r0, r1
	str r0, [r5, #0x54]
_080582C2:
	ldr r0, [r5, #0x60]
	adds r0, #0x20
	str r0, [r5, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _080582D2
	str r1, [r5, #0x60]
_080582D2:
	ldr r0, [r5, #0x58]
	ldr r1, [r5, #0x60]
	adds r0, r0, r1
	str r0, [r5, #0x58]
	adds r0, r5, #0
	bl UpdateMotionGraphic
	adds r0, r5, #0
	adds r0, #0x74
	ldr r2, _08058310 @ =0x08364ABC
	adds r1, r5, #0
	adds r1, #0x71
	ldrb r1, [r1]
	lsls r1, r1, #0x18
	asrs r1, r1, #0x18
	adds r1, r1, r2
	ldrb r2, [r1]
	lsls r1, r2, #1
	adds r1, r1, r2
	lsls r1, r1, #3
	ldr r2, _08058314 @ =sCollisions
	adds r1, r1, r2
	bl SetDDP
	b _0805835E
	.align 2, 0
_08058304: .4byte 0x00001FFF
_08058308: .4byte 0xFFFFE600
_0805830C: .4byte 0xFFFFF000
_08058310: .4byte 0x08364ABC
_08058314: .4byte sCollisions
_08058318:
	movs r0, #0xc
	strb r0, [r5, #0x12]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_08058322:
	ldrb r0, [r5, #0x12]
	subs r0, #1
	strb r0, [r5, #0x12]
	lsls r0, r0, #0x18
	lsrs r1, r0, #0x18
	cmp r1, #0
	bne _08058336
	movs r0, #6
	strb r0, [r5, #0xd]
	strb r1, [r5, #0xe]
_08058336:
	adds r0, r5, #0
	bl UpdateMotionGraphic
	adds r0, r5, #0
	adds r0, #0x74
	ldr r2, _08058364 @ =0x08364ABC
	adds r1, r5, #0
	adds r1, #0x71
	ldrb r1, [r1]
	lsls r1, r1, #0x18
	asrs r1, r1, #0x18
	adds r1, r1, r2
	ldrb r2, [r1]
	lsls r1, r2, #1
	adds r1, r1, r2
	lsls r1, r1, #3
	ldr r2, _08058368 @ =sCollisions
	adds r1, r1, r2
	bl SetDDP
_0805835E:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_08058364: .4byte 0x08364ABC
_08058368: .4byte sCollisions

