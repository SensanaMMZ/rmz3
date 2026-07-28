	.include "asm/macros.inc"

	.syntax unified
	
	.text

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

