	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_080af368
FUN_080af368: @ 0x080AF368
	push {r4, r5, r6, r7, lr}
	adds r3, r0, #0
	ldr r0, [r3, #0x28]
	ldr r6, [r0, #0x54]
	ldr r7, [r0, #0x58]
	ldrb r0, [r0, #0xa]
	lsrs r4, r0, #4
	movs r0, #1
	ands r4, r0
	adds r2, r4, #0
	cmp r2, #0
	beq _080AF388
	ldrb r1, [r3, #0xa]
	movs r0, #0x10
	orrs r0, r1
	b _080AF38E
_080AF388:
	ldrb r1, [r3, #0xa]
	movs r0, #0xef
	ands r0, r1
_080AF38E:
	strb r0, [r3, #0xa]
	movs r5, #1
	adds r1, r5, #0
	ands r1, r2
	adds r0, r3, #0
	adds r0, #0x4c
	strb r1, [r0]
	movs r0, #0x4a
	adds r0, r0, r3
	mov ip, r0
	lsls r1, r1, #4
	ldrb r2, [r0]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r1
	mov r1, ip
	strb r0, [r1]
	movs r0, #1
	rsbs r0, r0, #0
	cmp r4, #0
	bne _080AF3BC
	movs r0, #1
_080AF3BC:
	lsls r0, r0, #0xc
	adds r0, r6, r0
	str r0, [r3, #0x54]
	ldr r1, _080AF3E4 @ =0xFFFFE400
	adds r0, r7, r1
	str r0, [r3, #0x58]
	adds r0, r3, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _080AF3DC
	strb r5, [r3, #0xd]
	ldr r1, _080AF3E8 @ =0x00008601
	adds r0, r3, #0
	bl SetMotion
_080AF3DC:
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080AF3E4: .4byte 0xFFFFE400
_080AF3E8: .4byte 0x00008601

	thumb_func_start FUN_080af3ec
FUN_080af3ec: @ 0x080AF3EC
	push {r4, r5, r6, lr}
	adds r3, r0, #0
	ldr r1, [r3, #0x28]
	ldrb r0, [r1, #0xf]
	cmp r0, #2
	bls _080AF408
	movs r1, #0
	movs r0, #2
	strb r0, [r3, #0xd]
	strb r1, [r3, #0xe]
	adds r0, r3, #0
	bl FUN_080af46c
	b _080AF462
_080AF408:
	ldr r5, [r1, #0x54]
	ldr r6, [r1, #0x58]
	ldrb r0, [r1, #0xa]
	lsrs r4, r0, #4
	movs r0, #1
	ands r4, r0
	adds r2, r4, #0
	cmp r2, #0
	beq _080AF422
	ldrb r1, [r3, #0xa]
	movs r0, #0x10
	orrs r0, r1
	b _080AF428
_080AF422:
	ldrb r1, [r3, #0xa]
	movs r0, #0xef
	ands r0, r1
_080AF428:
	strb r0, [r3, #0xa]
	adds r1, r2, #0
	adds r0, r3, #0
	adds r0, #0x4c
	strb r1, [r0]
	movs r0, #0x4a
	adds r0, r0, r3
	mov ip, r0
	lsls r1, r1, #4
	ldrb r2, [r0]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r1
	mov r1, ip
	strb r0, [r1]
	movs r1, #1
	rsbs r1, r1, #0
	cmp r4, #0
	bne _080AF452
	movs r1, #1
_080AF452:
	lsls r0, r1, #3
	subs r0, r0, r1
	lsls r0, r0, #9
	adds r0, r5, r0
	str r0, [r3, #0x54]
	ldr r1, _080AF468 @ =0xFFFFE900
	adds r0, r6, r1
	str r0, [r3, #0x58]
_080AF462:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_080AF468: .4byte 0xFFFFE900

	thumb_func_start FUN_080af46c
FUN_080af46c: @ 0x080AF46C
	push {r4, r5, lr}
	adds r4, r0, #0
	ldr r5, [r4, #0x28]
	ldrb r0, [r5, #0xc]
	cmp r0, #1
	bls _080AF490
	ldr r1, _080AF48C @ =gProjectileFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	b _080AF506
	.align 2, 0
_080AF48C: .4byte gProjectileFnTable
_080AF490:
	ldr r1, _080AF4BC @ =0x0836D424
	ldrb r0, [r4, #0xe]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r1, [r0]
	adds r0, r4, #0
	bl _call_via_r1
	ldr r0, [r5, #0x2c]
	cmp r0, r4
	bne _080AF4C0
	ldrb r0, [r5, #0xe]
	cmp r0, #4
	bhi _080AF4C0
	cmp r0, #4
	bne _080AF508
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	str r0, [r5, #0x54]
	str r1, [r5, #0x58]
	b _080AF508
	.align 2, 0
_080AF4BC: .4byte 0x0836D424
_080AF4C0:
	ldr r0, _080AF510 @ =gStageRun+232
	adds r1, r4, #0
	adds r1, #0x54
	bl CalcFromCamera
	movs r1, #0x80
	lsls r1, r1, #6
	cmp r0, r1
	bls _080AF508
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r2, #0
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	adds r0, #0x8c
	str r2, [r0]
	adds r0, #4
	str r2, [r0]
	adds r0, #4
	strb r2, [r0]
	ldrb r1, [r4, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r4, #0xa]
	ldr r1, _080AF514 @ =gProjectileFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
_080AF506:
	str r0, [r4, #0x14]
_080AF508:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080AF510: .4byte gStageRun+232
_080AF514: .4byte gProjectileFnTable

	thumb_func_start FUN_080af518
FUN_080af518: @ 0x080AF518
	push {r4, r5, r6, r7, lr}
	adds r6, r0, #0
	ldrb r1, [r6, #0xa]
	movs r0, #4
	movs r7, #0
	movs r5, #0
	orrs r0, r1
	strb r0, [r6, #0xa]
	adds r4, r6, #0
	adds r4, #0x74
	ldr r1, _080AF570 @ =0x0836D358
	adds r2, r6, #0
	adds r2, #0x54
	adds r0, r4, #0
	movs r3, #0
	bl InitBody
	str r6, [r4, #0x2c]
	str r5, [r4, #0x24]
	movs r4, #1
	strb r4, [r6, #0xe]
	movs r1, #0x86
	lsls r1, r1, #8
	adds r0, r6, #0
	bl SetMotion
	ldr r0, [r6, #0x28]
	ldr r5, [r0, #0x54]
	ldr r1, [r0, #0x58]
	mov ip, r1
	ldrb r0, [r0, #0xa]
	lsrs r3, r0, #4
	ands r3, r4
	movs r1, #0
	cmp r3, #0
	bne _080AF562
	movs r1, #1
_080AF562:
	adds r2, r1, #0
	cmp r2, #0
	beq _080AF574
	ldrb r0, [r6, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _080AF57A
	.align 2, 0
_080AF570: .4byte 0x0836D358
_080AF574:
	ldrb r1, [r6, #0xa]
	movs r0, #0xef
	ands r0, r1
_080AF57A:
	strb r0, [r6, #0xa]
	adds r1, r2, #0
	adds r0, r6, #0
	adds r0, #0x4c
	strb r1, [r0]
	adds r4, r6, #0
	adds r4, #0x4a
	lsls r1, r1, #4
	ldrb r2, [r4]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r1
	strb r0, [r4]
	movs r0, #1
	rsbs r0, r0, #0
	cmp r3, #0
	beq _080AF5A0
	movs r0, #1
_080AF5A0:
	adds r3, r0, #0
	lsls r0, r3, #5
	adds r0, r0, r3
	lsls r0, r0, #8
	adds r0, r5, r0
	str r0, [r6, #0x54]
	ldr r0, _080AF5C8 @ =0xFFFFF200
	add r0, ip
	str r0, [r6, #0x58]
	lsls r0, r3, #0xa
	str r0, [r6, #0x5c]
	movs r0, #0
	str r0, [r6, #0x60]
	lsls r0, r3, #6
	rsbs r0, r0, #0
	str r0, [r6, #0x64]
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080AF5C8: .4byte 0xFFFFF200

	thumb_func_start FUN_080af5cc
FUN_080af5cc: @ 0x080AF5CC
	push {r4, lr}
	adds r4, r0, #0
	ldr r0, [r4, #0x28]
	adds r1, r4, #0
	adds r1, #0x54
	adds r2, r4, #0
	adds r2, #0x5c
	adds r3, r4, #0
	adds r3, #0x64
	bl FUN_080afdf0
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _080AF5EC
	movs r0, #2
	strb r0, [r4, #0xe]
_080AF5EC:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start FUN_080af5f4
FUN_080af5f4: @ 0x080AF5F4
	push {r4, lr}
	adds r4, r0, #0
	ldr r0, [r4, #0x28]
	adds r1, r4, #0
	adds r1, #0x54
	adds r2, r4, #0
	adds r2, #0x5c
	adds r3, r4, #0
	adds r3, #0x64
	bl FUN_080afe38
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _080AF614
	movs r0, #1
	strb r0, [r4, #0xe]
_080AF614:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start FUN_080af61c
FUN_080af61c: @ 0x080AF61C
	push {lr}
	ldr r2, _080AF630 @ =0x0836D430
	ldrb r1, [r0, #0xd]
	lsls r1, r1, #2
	adds r1, r1, r2
	ldr r1, [r1]
	bl _call_via_r1
	pop {r0}
	bx r0
	.align 2, 0
_080AF630: .4byte 0x0836D430

	thumb_func_start FUN_080af634
FUN_080af634: @ 0x080AF634
	push {r4, lr}
	adds r4, r0, #0
	ldr r1, _080AF658 @ =0x00008605
	bl SetMotion
	ldrb r0, [r4, #0x12]
	adds r0, #0x20
	adds r1, r4, #0
	adds r1, #0x24
	strb r0, [r1]
	movs r0, #1
	strb r0, [r4, #0xd]
	adds r0, r4, #0
	bl FUN_080af65c
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080AF658: .4byte 0x00008605

	thumb_func_start FUN_080af65c
FUN_080af65c: @ 0x080AF65C
	push {r4, r5, lr}
	adds r4, r0, #0
	ldr r1, [r4, #0x54]
	ldr r0, [r4, #0x5c]
	adds r5, r1, r0
	str r5, [r4, #0x54]
	ldr r1, [r4, #0x58]
	ldr r0, [r4, #0x60]
	adds r3, r1, r0
	str r3, [r4, #0x58]
	ldrb r0, [r4, #0x11]
	cmp r0, #0
	beq _080AF6B2
	ldr r2, _080AF700 @ =gSineTable
	ldrb r0, [r4, #0x12]
	adds r0, #0x40
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x17
	adds r0, r0, r2
	movs r1, #0
	ldrsh r0, [r0, r1]
	lsls r0, r0, #3
	ldrb r1, [r4, #0x12]
	lsls r1, r1, #1
	adds r1, r1, r2
	movs r2, #0
	ldrsh r1, [r1, r2]
	lsls r1, r1, #3
	adds r0, r5, r0
	adds r1, r3, r1
	bl FUN_080098a4
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _080AF6B2
	movs r0, #0x80
	lsls r0, r0, #1
	bl PlaySound
	movs r1, #0
	movs r0, #4
	strb r0, [r4, #0x10]
	strb r1, [r4, #0xd]
_080AF6B2:
	ldr r0, _080AF704 @ =gStageRun+232
	adds r1, r4, #0
	adds r1, #0x54
	bl CalcFromCamera
	movs r1, #0xc0
	lsls r1, r1, #7
	cmp r0, r1
	bls _080AF6FA
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r2, #0
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	adds r0, #0x8c
	str r2, [r0]
	adds r0, #4
	str r2, [r0]
	adds r0, #4
	strb r2, [r0]
	ldrb r1, [r4, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r4, #0xa]
	ldr r1, _080AF708 @ =gProjectileFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r4, #0x14]
_080AF6FA:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080AF700: .4byte gSineTable
_080AF704: .4byte gStageRun+232
_080AF708: .4byte gProjectileFnTable

	thumb_func_start FUN_080af70c
FUN_080af70c: @ 0x080AF70C
	push {lr}
	adds r3, r0, #0
	adds r0, #0x8c
	movs r2, #0
	str r2, [r0]
	adds r0, #4
	str r2, [r0]
	adds r0, #4
	strb r2, [r0]
	ldrb r1, [r3, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r3, #0xa]
	ldr r1, _080AF744 @ =gProjectileFnTable
	ldrb r0, [r3, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r3, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r3, #0x14]
	strb r2, [r3, #0xd]
	adds r0, r3, #0
	bl PhantomProjectile_Update
	pop {r0}
	bx r0
	.align 2, 0
_080AF744: .4byte gProjectileFnTable

	thumb_func_start FUN_080af748
FUN_080af748: @ 0x080AF748
	push {lr}
	ldr r2, _080AF75C @ =0x0836D438
	ldrb r1, [r0, #0xd]
	lsls r1, r1, #2
	adds r1, r1, r2
	ldr r1, [r1]
	bl _call_via_r1
	pop {r0}
	bx r0
	.align 2, 0
_080AF75C: .4byte 0x0836D438

	thumb_func_start FUN_080af760
FUN_080af760: @ 0x080AF760
	push {r4, lr}
	adds r4, r0, #0
	adds r0, #0x8c
	movs r1, #0
	str r1, [r0]
	adds r0, #4
	str r1, [r0]
	adds r0, #4
	strb r1, [r0]
	ldrb r1, [r4, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r4, #0xa]
	ldr r1, _080AF7A8 @ =0x00008605
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0x12]
	adds r0, #0x20
	adds r1, r4, #0
	adds r1, #0x24
	strb r0, [r1]
	ldr r0, [r4, #0x60]
	ldr r1, _080AF7AC @ =0xFFFFFA00
	adds r0, r0, r1
	str r0, [r4, #0x60]
	movs r0, #0x1c
	strb r0, [r4, #0x13]
	movs r0, #1
	strb r0, [r4, #0xd]
	adds r0, r4, #0
	bl FUN_080af7b0
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080AF7A8: .4byte 0x00008605
_080AF7AC: .4byte 0xFFFFFA00

	thumb_func_start FUN_080af7b0
FUN_080af7b0: @ 0x080AF7B0
	push {r4, r5, r6, lr}
	adds r5, r0, #0
	ldrb r0, [r5, #0x13]
	subs r0, #1
	strb r0, [r5, #0x13]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x19
	movs r1, #1
	ands r0, r1
	cmp r0, #0
	beq _080AF7CE
	ldrb r1, [r5, #0xa]
	movs r0, #0xfe
	ands r0, r1
	b _080AF7D2
_080AF7CE:
	ldrb r0, [r5, #0xa]
	orrs r0, r1
_080AF7D2:
	strb r0, [r5, #0xa]
	ldrb r2, [r5, #0x13]
	cmp r2, #0
	bne _080AF814
	ldrb r1, [r5, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r5, #0xa]
	adds r0, r5, #0
	adds r0, #0x8c
	str r2, [r0]
	adds r0, #4
	str r2, [r0]
	adds r0, #4
	strb r2, [r0]
	ldrb r1, [r5, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r5, #0xa]
	ldr r1, _080AF810 @ =gProjectileFnTable
	ldrb r0, [r5, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r5, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r5, #0x14]
	b _080AF8A8
	.align 2, 0
_080AF810: .4byte gProjectileFnTable
_080AF814:
	ldr r0, [r5, #0x60]
	adds r0, #0x40
	str r0, [r5, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _080AF824
	str r1, [r5, #0x60]
_080AF824:
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x5c]
	adds r0, r0, r1
	str r0, [r5, #0x54]
	ldr r1, [r5, #0x58]
	ldr r2, [r5, #0x60]
	adds r1, r1, r2
	str r1, [r5, #0x58]
	ldr r4, _080AF898 @ =gSineTable
	ldrb r2, [r5, #0x12]
	adds r2, #0x40
	lsls r2, r2, #0x18
	lsrs r2, r2, #0x17
	adds r2, r2, r4
	movs r6, #0
	ldrsh r3, [r2, r6]
	lsls r3, r3, #3
	ldrb r2, [r5, #0x12]
	lsls r2, r2, #1
	adds r2, r2, r4
	movs r4, #0
	ldrsh r2, [r2, r4]
	lsls r2, r2, #3
	adds r0, r0, r3
	adds r1, r1, r2
	bl PushoutToUp1
	adds r4, r0, #0
	cmp r4, #0
	bge _080AF88A
	movs r0, #0x80
	lsls r0, r0, #1
	bl PlaySound
	ldr r0, [r5, #0x58]
	adds r0, r0, r4
	str r0, [r5, #0x58]
	ldr r1, [r5, #0x60]
	lsls r0, r1, #3
	subs r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r1
	lsls r0, r0, #2
	subs r0, r0, r1
	lsls r0, r0, #1
	rsbs r0, r0, #0
	cmp r0, #0
	bge _080AF886
	adds r0, #0xff
_080AF886:
	asrs r0, r0, #8
	str r0, [r5, #0x60]
_080AF88A:
	ldrb r1, [r5, #0x12]
	ldr r0, [r5, #0x5c]
	cmp r0, #0
	ble _080AF89C
	adds r1, #8
	b _080AF89E
	.align 2, 0
_080AF898: .4byte gSineTable
_080AF89C:
	subs r1, #8
_080AF89E:
	strb r1, [r5, #0x12]
	adds r1, #0x20
	adds r0, r5, #0
	adds r0, #0x24
	strb r1, [r0]
_080AF8A8:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start FUN_080af8b0
FUN_080af8b0: @ 0x080AF8B0
	push {lr}
	ldr r2, _080AF8C4 @ =0x0836D440
	ldrb r1, [r0, #0xd]
	lsls r1, r1, #2
	adds r1, r1, r2
	ldr r1, [r1]
	bl _call_via_r1
	pop {r0}
	bx r0
	.align 2, 0
_080AF8C4: .4byte 0x0836D440

	thumb_func_start FUN_080af8c8
FUN_080af8c8: @ 0x080AF8C8
	push {r4, lr}
	adds r4, r0, #0
	ldr r1, _080AF8E4 @ =0x00008605
	bl SetMotion
	movs r0, #1
	strb r0, [r4, #0xd]
	adds r0, r4, #0
	bl FUN_080af8e8
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080AF8E4: .4byte 0x00008605

	thumb_func_start FUN_080af8e8
FUN_080af8e8: @ 0x080AF8E8
	push {r4, r5, r6, lr}
	adds r4, r0, #0
	ldr r5, [r4, #0x28]
	ldrb r0, [r5, #0xc]
	cmp r0, #1
	bls _080AF912
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r2, #0
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	adds r0, #0x8c
	str r2, [r0]
	adds r0, #4
	str r2, [r0]
	adds r0, #4
	strb r2, [r0]
	b _080AF97E
_080AF912:
	ldr r1, [r5, #0x54]
	str r1, [r4, #0x54]
	ldr r3, _080AF9A0 @ =gSineTable
	ldrb r2, [r4, #0x12]
	adds r0, r2, #0
	adds r0, #0x40
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x17
	adds r0, r0, r3
	movs r6, #0
	ldrsh r0, [r0, r6]
	lsls r0, r0, #3
	adds r1, r1, r0
	str r1, [r4, #0x54]
	ldr r1, [r5, #0x58]
	str r1, [r4, #0x58]
	ldrb r0, [r4, #0x12]
	lsls r0, r0, #1
	adds r0, r0, r3
	movs r3, #0
	ldrsh r0, [r0, r3]
	lsls r0, r0, #3
	adds r1, r1, r0
	str r1, [r4, #0x58]
	adds r2, #0x20
	adds r0, r4, #0
	adds r0, #0x24
	movs r5, #0
	strb r2, [r0]
	ldrb r0, [r4, #0x12]
	adds r0, #8
	strb r0, [r4, #0x12]
	ldr r0, _080AF9A4 @ =gStageRun+232
	adds r1, r4, #0
	adds r1, #0x54
	bl CalcFromCamera
	movs r1, #0xc0
	lsls r1, r1, #7
	cmp r0, r1
	bls _080AF998
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	adds r0, #0x8c
	str r5, [r0]
	adds r0, #4
	str r5, [r0]
	adds r0, #4
	strb r5, [r0]
_080AF97E:
	ldrb r1, [r4, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r4, #0xa]
	ldr r1, _080AF9A8 @ =gProjectileFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r4, #0x14]
_080AF998:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_080AF9A0: .4byte gSineTable
_080AF9A4: .4byte gStageRun+232
_080AF9A8: .4byte gProjectileFnTable
