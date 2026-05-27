	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_08060410
FUN_08060410: @ 0x08060410
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xf]
	cmp r0, #1
	beq _0806044A
	cmp r0, #1
	bgt _08060424
	cmp r0, #0
	beq _0806042E
	b _080604D2
_08060424:
	cmp r0, #2
	beq _0806045C
	cmp r0, #3
	beq _08060494
	b _080604D2
_0806042E:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _08060458 @ =0x08365350
	bl SetDDP
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
	strb r0, [r4, #0xa]
	movs r0, #0x18
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0xf]
	adds r0, #1
	strb r0, [r4, #0xf]
_0806044A:
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080604D2
	b _0806047E
	.align 2, 0
_08060458: .4byte 0x08365350
_0806045C:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _08060488 @ =sCollisions
	bl SetDDP
	ldrb r1, [r4, #0xa]
	movs r0, #1
	orrs r0, r1
	strb r0, [r4, #0xa]
	ldr r0, [r4, #0x58]
	ldr r1, _0806048C @ =0xFFFFB000
	adds r0, r0, r1
	str r0, [r4, #0x58]
	ldr r1, _08060490 @ =0x0000BC17
	adds r0, r4, #0
	bl SetMotion
_0806047E:
	ldrb r0, [r4, #0xf]
	adds r0, #1
	strb r0, [r4, #0xf]
	b _080604D2
	.align 2, 0
_08060488: .4byte sCollisions
_0806048C: .4byte 0xFFFFB000
_08060490: .4byte 0x0000BC17
_08060494:
	ldr r0, [r4, #0x70]
	ldr r1, _080604D8 @ =0x00FFFF00
	ands r0, r1
	ldr r1, _080604DC @ =0x00010500
	cmp r0, r1
	bne _080604BE
	movs r0, #0xfc
	bl PlaySound
	adds r0, r4, #0
	movs r1, #0
	bl FUN_0809142c
	adds r0, r4, #0
	movs r1, #1
	bl FUN_0809142c
	adds r0, r4, #0
	movs r1, #2
	bl FUN_0809142c
_080604BE:
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _080604D2
	movs r0, #0
	strb r0, [r4, #0xf]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_080604D2:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080604D8: .4byte 0x00FFFF00
_080604DC: .4byte 0x00010500

	thumb_func_start FUN_080604e0
FUN_080604e0: @ 0x080604E0
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xf]
	cmp r0, #1
	beq _08060514
	cmp r0, #1
	bgt _080604F4
	cmp r0, #0
	beq _080604FE
	b _08060556
_080604F4:
	cmp r0, #2
	beq _08060524
	cmp r0, #3
	beq _08060540
	b _08060556
_080604FE:
	ldr r1, _08060510 @ =0x0000BC18
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xf]
	adds r0, #1
	strb r0, [r4, #0xf]
	b _08060556
	.align 2, 0
_08060510: .4byte 0x0000BC18
_08060514:
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _08060556
	movs r0, #2
	strb r0, [r4, #0xf]
	b _08060556
_08060524:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _0806055C @ =0x08365350
	bl SetDDP
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
	strb r0, [r4, #0xa]
	movs r0, #0x18
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0xf]
	adds r0, #1
	strb r0, [r4, #0xf]
_08060540:
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0
	bne _08060556
	strb r0, [r4, #0xf]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08060556:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_0806055C: .4byte 0x08365350

	thumb_func_start FUN_08060560
FUN_08060560: @ 0x08060560
	push {r4, lr}
	adds r4, r0, #0
	ldrb r1, [r4, #0xf]
	cmp r1, #0
	beq _08060570
	cmp r1, #1
	beq _08060638
	b _08060648
_08060570:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _080605AC @ =sCollisions
	bl SetDDP
	ldrb r1, [r4, #0xa]
	movs r0, #1
	orrs r0, r1
	strb r0, [r4, #0xa]
	ldr r0, [r4, #0x58]
	movs r1, #0xa0
	lsls r1, r1, #7
	adds r0, r0, r1
	str r0, [r4, #0x58]
	adds r0, r4, #0
	adds r0, #0xe0
	ldr r1, [r4, #0x54]
	ldr r0, [r0]
	cmp r1, r0
	bge _080605B4
	ldr r0, _080605B0 @ =0xFFFFC000
	adds r2, r1, r0
	adds r0, r4, #0
	adds r0, #0xd4
	ldr r0, [r0]
	cmp r2, r0
	bge _080605D0
	movs r2, #0x80
	lsls r2, r2, #7
	b _080605C6
	.align 2, 0
_080605AC: .4byte sCollisions
_080605B0: .4byte 0xFFFFC000
_080605B4:
	movs r0, #0x80
	lsls r0, r0, #7
	adds r2, r1, r0
	adds r0, r4, #0
	adds r0, #0xd8
	ldr r0, [r0]
	cmp r2, r0
	ble _080605D0
	ldr r2, _080605CC @ =0xFFFFC000
_080605C6:
	adds r0, r1, r2
	str r0, [r4, #0x54]
	b _080605D2
	.align 2, 0
_080605CC: .4byte 0xFFFFC000
_080605D0:
	str r2, [r4, #0x54]
_080605D2:
	movs r3, #0
	ldr r0, _08060618 @ =pZero2
	ldr r2, [r0]
	ldr r1, [r4, #0x54]
	ldr r0, [r2, #0x54]
	cmp r1, r0
	bge _080605E2
	movs r3, #1
_080605E2:
	adds r0, r4, #0
	adds r0, #0x4c
	strb r3, [r0]
	movs r3, #0
	ldr r1, [r4, #0x54]
	ldr r0, [r2, #0x54]
	cmp r1, r0
	bge _080605F4
	movs r3, #1
_080605F4:
	movs r0, #0x4a
	adds r0, r0, r4
	mov ip, r0
	lsls r2, r3, #4
	ldrb r1, [r0]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	orrs r0, r2
	mov r1, ip
	strb r0, [r1]
	cmp r3, #0
	beq _0806061C
	ldrb r0, [r4, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _08060622
	.align 2, 0
_08060618: .4byte pZero2
_0806061C:
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
_08060622:
	strb r0, [r4, #0xa]
	ldr r1, _08060634 @ =0x0000BC19
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xf]
	adds r0, #1
	strb r0, [r4, #0xf]
	b _08060648
	.align 2, 0
_08060634: .4byte 0x0000BC19
_08060638:
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _08060648
	movs r0, #0
	strb r1, [r4, #0xd]
	strh r0, [r4, #0xe]
_08060648:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start Phantom_Die
Phantom_Die: @ 0x08060650
	push {lr}
	ldr r2, _08060664 @ =sDeads
	ldrb r1, [r0, #0xd]
	lsls r1, r1, #2
	adds r1, r1, r2
	ldr r1, [r1]
	bl _call_via_r1
	pop {r0}
	bx r0
	.align 2, 0
_08060664: .4byte sDeads

	thumb_func_start phantom_08060668
phantom_08060668: @ 0x08060668
	push {r4, r5, lr}
	adds r5, r0, #0
	ldrb r0, [r5, #0xe]
	cmp r0, #6
	bls _08060674
	b _08060794
_08060674:
	lsls r0, r0, #2
	ldr r1, _08060680 @ =_08060684
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_08060680: .4byte _08060684
_08060684: @ jump table
	.4byte _080606A0 @ case 0
	.4byte _080606F2 @ case 1
	.4byte _0806072C @ case 2
	.4byte _0806073A @ case 3
	.4byte _08060758 @ case 4
	.4byte _08060762 @ case 5
	.4byte _08060794 @ case 6
_080606A0:
	ldrb r0, [r5, #0xa]
	movs r1, #1
	orrs r1, r0
	strb r1, [r5, #0xa]
	ldr r3, _08060720 @ =gStageRun
	ldrh r2, [r3, #8]
	movs r4, #1
	adds r0, r4, #0
	ands r0, r2
	cmp r0, #0
	beq _080606CA
	ldrb r1, [r3, #0x12]
	adds r0, r4, #0
	ands r0, r1
	cmp r0, #0
	bne _080606CA
	ldr r0, _08060724 @ =0x0000FFFE
	ands r0, r2
	movs r1, #0x10
	orrs r0, r1
	strh r0, [r3, #8]
_080606CA:
	adds r0, r5, #0
	adds r0, #0x8c
	movs r4, #0
	str r4, [r0]
	adds r0, #4
	str r4, [r0]
	adds r0, #4
	strb r4, [r0]
	ldrb r1, [r5, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r5, #0xa]
	ldr r1, _08060728 @ =0x0000BC0E
	adds r0, r5, #0
	bl SetMotion
	str r4, [r5, #0x60]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_080606F2:
	ldr r1, [r5, #0x60]
	adds r1, #0x40
	str r1, [r5, #0x60]
	ldr r0, [r5, #0x58]
	adds r0, r0, r1
	str r0, [r5, #0x58]
	movs r0, #0xe0
	lsls r0, r0, #3
	cmp r1, r0
	ble _08060708
	str r0, [r5, #0x60]
_08060708:
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x58]
	bl PushoutToUp1
	adds r1, r0, #0
	cmp r1, #0
	bge _0806074C
	ldr r0, [r5, #0x58]
	adds r0, r0, r1
	str r0, [r5, #0x58]
	b _08060746
	.align 2, 0
_08060720: .4byte gStageRun
_08060724: .4byte 0x0000FFFE
_08060728: .4byte 0x0000BC0E
_0806072C:
	ldr r1, _08060754 @ =0x0000BC13
	adds r0, r5, #0
	bl SetMotion
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_0806073A:
	ldr r0, [r5, #0x18]
	ldrb r1, [r0, #9]
	movs r0, #0x80
	ands r0, r1
	cmp r0, #0
	beq _0806074C
_08060746:
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_0806074C:
	adds r0, r5, #0
	bl UpdateMotionGraphic
	b _08060794
	.align 2, 0
_08060754: .4byte 0x0000BC13
_08060758:
	movs r0, #0xa
	strb r0, [r5, #0x12]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_08060762:
	ldrb r0, [r5, #0x12]
	subs r0, #1
	strb r0, [r5, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _08060794
	ldrb r1, [r5, #0xa]
	movs r0, #0xfe
	ands r0, r1
	strb r0, [r5, #0xa]
	ldr r2, _0806079C @ =gStageRun
	ldrb r0, [r2, #0x12]
	movs r1, #2
	orrs r0, r1
	strb r0, [r2, #0x12]
	movs r0, #0x88
	lsls r0, r0, #1
	bl PlaySound
	adds r0, r5, #0
	bl FUN_0805ecc8
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_08060794:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_0806079C: .4byte gStageRun

	thumb_func_start FUN_080607a0
FUN_080607a0: @ 0x080607A0
	push {lr}
	adds r2, r0, #0
	adds r2, #0xb4
	strb r1, [r2]
	ldr r2, _080607B8 @ =sMotions
	lsls r1, r1, #1
	adds r1, r1, r2
	ldrh r1, [r1]
	bl SetMotion
	pop {r0}
	bx r0
	.align 2, 0
_080607B8: .4byte sMotions

	thumb_func_start FUN_080607bc
FUN_080607bc: @ 0x080607BC
	push {r4, lr}
	adds r4, r0, #0
	adds r4, #0xb4
	strb r1, [r4]
	ldr r4, _080607E0 @ =sMotions
	lsls r1, r1, #1
	adds r1, r1, r4
	ldrh r1, [r1]
	lsls r2, r2, #0x10
	lsrs r2, r2, #0x10
	lsls r3, r3, #0x10
	lsrs r3, r3, #0x10
	bl GotoMotion
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080607E0: .4byte sMotions

