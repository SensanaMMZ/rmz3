	.include "asm/macros.inc"

	.syntax unified

	.text


	thumb_func_start FUN_0809596c
FUN_0809596c: @ 0x0809596C
	push {r4, r5, r6, lr}
	adds r5, r0, #0
	ldrb r0, [r5, #0xe]
	cmp r0, #0
	beq _0809597C
	cmp r0, #1
	beq _08095A12
	b _08095AB6
_0809597C:
	adds r0, r5, #0
	adds r0, #0x74
	ldr r1, _080959F4 @ =0x0836A04C
	bl SetDDP
	ldr r1, _080959F8 @ =0x0000D406
	adds r0, r5, #0
	bl SetMotion
	adds r0, r5, #0
	bl UpdateMotionGraphic
	ldr r0, _080959FC @ =pZero2
	ldr r2, [r0]
	ldr r1, [r5, #0x54]
	ldr r0, [r2, #0x54]
	subs r1, r1, r0
	str r1, [r5, #0x5c]
	ldr r0, [r5, #0x58]
	ldr r3, _08095A00 @ =0xFFFFE800
	adds r0, r0, r3
	ldr r2, [r2, #0x58]
	subs r0, r0, r2
	str r0, [r5, #0x60]
	asrs r1, r1, #8
	adds r6, r1, #0
	muls r6, r1, r6
	asrs r0, r0, #8
	adds r1, r0, #0
	muls r1, r0, r1
	adds r0, r1, #0
	adds r6, r6, r0
	adds r0, r6, #0
	bl Sqrt
	lsls r0, r0, #0x10
	lsrs r6, r0, #8
	cmp r6, #0
	beq _08095A04
	ldr r0, [r5, #0x5c]
	lsls r0, r0, #8
	adds r1, r6, #0
	bl __divsi3
	adds r4, r0, #0
	str r4, [r5, #0x5c]
	ldr r0, [r5, #0x60]
	lsls r0, r0, #8
	adds r1, r6, #0
	bl __divsi3
	lsls r1, r4, #1
	adds r1, r1, r4
	lsls r1, r1, #1
	str r1, [r5, #0x5c]
	lsls r1, r0, #1
	adds r1, r1, r0
	lsls r1, r1, #1
	str r1, [r5, #0x60]
	b _08095A0C
	.align 2, 0
_080959F4: .4byte 0x0836A04C
_080959F8: .4byte 0x0000D406
_080959FC: .4byte pZero2
_08095A00: .4byte 0xFFFFE800
_08095A04:
	movs r0, #0xc0
	lsls r0, r0, #3
	str r0, [r5, #0x5c]
	str r6, [r5, #0x60]
_08095A0C:
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_08095A12:
	adds r0, r5, #0
	bl UpdateMotionGraphic
	ldr r1, [r5, #0x5c]
	adds r0, r5, #0
	bl FUN_08095014
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _08095A34
	adds r6, r5, #0
	adds r6, #0x8c
	ldr r4, [r6]
	movs r0, #4
	ands r4, r0
	cmp r4, #0
	beq _08095A3C
_08095A34:
	adds r0, r5, #0
	bl FUN_08095b70
	b _08095AB6
_08095A3C:
	ldr r0, [r5, #0x60]
	adds r0, #0x40
	str r0, [r5, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _08095A4C
	str r1, [r5, #0x60]
_08095A4C:
	ldr r1, [r5, #0x58]
	ldr r0, [r5, #0x60]
	adds r1, r1, r0
	str r1, [r5, #0x58]
	ldr r0, [r5, #0x54]
	bl PushoutToUp1
	adds r1, r0, #0
	cmp r1, #0
	bge _08095A6C
	ldr r0, [r5, #0x58]
	adds r0, r0, r1
	str r0, [r5, #0x58]
	adds r0, r5, #0
	bl FUN_08095b70
_08095A6C:
	ldrb r0, [r5, #0x11]
	cmp r0, #0
	beq _08095AB6
	ldr r0, _08095ABC @ =gStageRun+232
	adds r1, r5, #0
	adds r1, #0x54
	bl CalcFromCamera
	movs r1, #0xc0
	lsls r1, r1, #7
	cmp r0, r1
	bls _08095AB6
	ldrb r1, [r5, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r5, #0xa]
	str r4, [r6]
	adds r0, r5, #0
	adds r0, #0x90
	str r4, [r0]
	adds r0, #4
	strb r4, [r0]
	ldrb r1, [r5, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r5, #0xa]
	ldr r1, _08095AC0 @ =gEnemyFnTable
	ldrb r0, [r5, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r5, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r5, #0x14]
_08095AB6:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_08095ABC: .4byte gStageRun+232
_08095AC0: .4byte gEnemyFnTable

	thumb_func_start FUN_08095ac4
FUN_08095ac4: @ 0x08095AC4
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _08095AD4
	cmp r0, #1
	beq _08095B3E
	b _08095B68
_08095AD4:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _08095B00 @ =0x08369FEC
	bl SetDDP
	ldr r1, _08095B04 @ =0x0000D402
	adds r0, r4, #0
	bl SetMotion
	adds r2, r4, #0
	adds r2, #0xb9
	ldrb r1, [r2]
	movs r0, #1
	adds r3, r0, #0
	eors r3, r1
	adds r5, r2, #0
	cmp r3, #0
	beq _08095B08
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	orrs r0, r1
	b _08095B0E
	.align 2, 0
_08095B00: .4byte 0x08369FEC
_08095B04: .4byte 0x0000D402
_08095B08:
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
_08095B0E:
	strb r0, [r4, #0xa]
	movs r1, #1
	ands r1, r3
	adds r0, r4, #0
	adds r0, #0x4c
	strb r1, [r0]
	adds r3, r4, #0
	adds r3, #0x4a
	lsls r1, r1, #4
	ldrb r2, [r3]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r1
	strb r0, [r3]
	movs r1, #0x80
	str r1, [r4, #0x5c]
	ldrb r0, [r5]
	lsls r0, r0, #8
	subs r1, r1, r0
	str r1, [r4, #0x5c]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08095B3E:
	ldr r1, [r4, #0x5c]
	adds r0, r4, #0
	bl FUN_08095014
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	movs r1, #1
	bl FUN_08094fe0
	lsls r0, r0, #0x18
	lsrs r2, r0, #0x18
	cmp r2, #0
	bne _08095B68
	adds r1, r4, #0
	adds r1, #0xb8
	movs r0, #2
	strb r0, [r1]
	strb r0, [r4, #0xd]
	strb r2, [r4, #0xe]
_08095B68:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start FUN_08095b70
FUN_08095b70: @ 0x08095B70
	push {r4, r5, lr}
	sub sp, #8
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
	movs r1, #0xfe
	ands r0, r1
	strb r0, [r4, #0xa]
	ldr r0, [r4, #0x54]
	str r0, [sp]
	ldr r0, [r4, #0x58]
	ldr r1, _08095BC0 @ =0xFFFFF000
	adds r0, r0, r1
	str r0, [sp, #4]
	movs r0, #1
	mov r1, sp
	bl CreateSmoke
	movs r0, #0x2a
	bl PlaySound
	ldrb r0, [r4, #0x11]
	cmp r0, #0
	bne _08095BC8
	ldr r2, _08095BC4 @ =0x0836A06E
	adds r0, r4, #0
	mov r1, sp
	movs r3, #3
	bl FUN_080b7f70
	b _08095BD4
	.align 2, 0
_08095BC0: .4byte 0xFFFFF000
_08095BC4: .4byte 0x0836A06E
_08095BC8:
	ldr r2, _08095C10 @ =0x0836A06E
	adds r0, r4, #0
	mov r1, sp
	movs r3, #3
	bl FUN_080b7ffc
_08095BD4:
	adds r5, r4, #0
	adds r5, #0x54
	movs r0, #4
	adds r1, r5, #0
	bl TryDropItem
	ldr r2, _08095C14 @ =gMission
	ldrh r1, [r2, #0xc]
	ldr r0, _08095C18 @ =0x0000270E
	cmp r1, r0
	bhi _08095BEE
	adds r0, r1, #1
	strh r0, [r2, #0xc]
_08095BEE:
	adds r0, r4, #0
	adds r1, r5, #0
	bl TryDropZakoDisk
	ldr r1, _08095C1C @ =gEnemyFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #4
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0x10]
	str r0, [r4, #0x14]
	add sp, #8
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_08095C10: .4byte 0x0836A06E
_08095C14: .4byte gMission
_08095C18: .4byte 0x0000270E
_08095C1C: .4byte gEnemyFnTable

	thumb_func_start FUN_08095c20
FUN_08095c20: @ 0x08095C20
	push {r4, r5, r6, lr}
	sub sp, #0x10
	adds r4, r0, #0
	ldrb r5, [r4, #0xe]
	cmp r5, #0
	beq _08095C34
	cmp r5, #1
	bne _08095C32
	b _08095D34
_08095C32:
	b _08095D72
_08095C34:
	movs r6, #0
	ldr r0, _08095CB8 @ =pZero2
	ldr r0, [r0]
	ldr r0, [r0, #0x54]
	ldr r1, [r4, #0x54]
	subs r0, r0, r1
	cmp r0, #0
	ble _08095C46
	movs r6, #1
_08095C46:
	ldr r1, _08095CBC @ =0x0000D408
	adds r0, r4, #0
	bl SetMotion
	adds r0, r4, #0
	adds r0, #0x8c
	str r5, [r0]
	adds r0, #4
	str r5, [r0]
	adds r0, #4
	strb r5, [r0]
	ldrb r1, [r4, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r4, #0xa]
	ldr r0, [r4, #0x54]
	str r0, [sp, #8]
	ldr r0, [r4, #0x58]
	str r0, [sp, #0xc]
	movs r2, #0x80
	lsls r2, r2, #2
	movs r0, #0
	add r1, sp, #8
	adds r3, r6, #0
	bl FUN_080b2b40
	movs r1, #0x60
	lsls r0, r6, #1
	adds r0, r0, r6
	lsls r0, r0, #6
	subs r0, r1, r0
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	adds r0, r4, #0
	movs r1, #1
	bl FUN_08094fe0
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _08095CE0
	movs r0, #0x20
	str r0, [r4, #0x68]
	ldrb r0, [r4, #0x11]
	cmp r0, #0
	bne _08095CC4
	adds r1, r4, #0
	adds r1, #0x54
	ldr r0, _08095CC0 @ =0x0836A074
	str r0, [sp]
	movs r0, #0x18
	str r0, [sp, #4]
	adds r0, r4, #0
	add r2, sp, #8
	movs r3, #0x15
	bl FUN_080b84f4
	b _08095D1A
	.align 2, 0
_08095CB8: .4byte pZero2
_08095CBC: .4byte 0x0000D408
_08095CC0: .4byte 0x0836A074
_08095CC4:
	adds r1, r4, #0
	adds r1, #0x54
	ldr r0, _08095CDC @ =0x0836A074
	str r0, [sp]
	movs r0, #0x18
	str r0, [sp, #4]
	adds r0, r4, #0
	add r2, sp, #8
	movs r3, #0x15
	bl FUN_080b857c
	b _08095D1A
	.align 2, 0
_08095CDC: .4byte 0x0836A074
_08095CE0:
	str r5, [r4, #0x68]
	ldrb r0, [r4, #0x11]
	cmp r0, #0
	bne _08095D04
	adds r1, r4, #0
	adds r1, #0x54
	ldr r0, _08095D00 @ =0x0836A074
	str r0, [sp]
	movs r0, #0x18
	str r0, [sp, #4]
	adds r0, r4, #0
	add r2, sp, #8
	movs r3, #0
	bl FUN_080b834c
	b _08095D1A
	.align 2, 0
_08095D00: .4byte 0x0836A074
_08095D04:
	adds r1, r4, #0
	adds r1, #0x54
	ldr r0, _08095D7C @ =0x0836A074
	str r0, [sp]
	movs r0, #0x18
	str r0, [sp, #4]
	adds r0, r4, #0
	add r2, sp, #8
	movs r3, #0
	bl FUN_080b83d4
_08095D1A:
	ldr r0, [sp, #8]
	cmp r0, #0
	bge _08095D22
	adds r0, #3
_08095D22:
	asrs r0, r0, #2
	str r0, [r4, #0x5c]
	movs r0, #0
	str r0, [r4, #0x60]
	movs r0, #0x18
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08095D34:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldr r1, [r4, #0x68]
	cmp r1, #0
	beq _08095D58
	ldr r0, [r4, #0x60]
	adds r0, r0, r1
	str r0, [r4, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _08095D50
	str r1, [r4, #0x60]
_08095D50:
	ldr r1, [r4, #0x60]
	adds r0, r4, #0
	bl FUN_08094fe0
_08095D58:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _08095D72
	adds r0, r4, #0
	bl FUN_08095b70
_08095D72:
	add sp, #0x10
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_08095D7C: .4byte 0x0836A074
