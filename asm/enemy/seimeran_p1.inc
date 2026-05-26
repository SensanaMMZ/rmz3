	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_0808f27c
FUN_0808f27c: @ 0x0808F27C
	push {r4, r5, r6, r7, lr}
	adds r7, r0, #0
	adds r4, r1, #0
	adds r6, r2, #0
	lsls r3, r3, #0x18
	lsrs r5, r3, #0x18
	ldr r0, _0808F2DC @ =gEnemyHeaderPtr
	ldr r0, [r0]
	bl AllocEntityLast
	adds r3, r0, #0
	cmp r3, #0
	beq _0808F2D2
	adds r1, r3, #0
	adds r1, #0x25
	movs r2, #0
	movs r0, #0x18
	strb r0, [r1]
	ldr r0, _0808F2E0 @ =gEnemyFnTable
	movs r1, #0x39
	strb r1, [r3, #9]
	adds r0, #0xe4
	ldr r0, [r0]
	ldr r0, [r0]
	str r0, [r3, #0x14]
	movs r0, #0
	strh r2, [r3, #0x20]
	adds r1, r3, #0
	adds r1, #0x22
	strb r0, [r1]
	ldrb r1, [r3, #0xb]
	movs r0, #0x10
	orrs r0, r1
	strb r0, [r3, #0xb]
	ldrb r0, [r3, #0x1c]
	strb r0, [r3, #0x1d]
	movs r0, #1
	strb r0, [r3, #0x10]
	str r4, [r3, #0x64]
	str r4, [r3, #0x54]
	str r6, [r3, #0x58]
	strb r5, [r3, #0x12]
	str r7, [r3, #0x28]
_0808F2D2:
	adds r0, r3, #0
	pop {r4, r5, r6, r7}
	pop {r1}
	bx r1
	.align 2, 0
_0808F2DC: .4byte gEnemyHeaderPtr
_0808F2E0: .4byte gEnemyFnTable

	thumb_func_start FUN_0808f2e4
FUN_0808f2e4: @ 0x0808F2E4
	push {r4, r5, r6, lr}
	adds r5, r0, #0
	adds r6, r1, #0
	lsls r2, r2, #0x18
	lsrs r4, r2, #0x18
	ldr r0, _0808F33C @ =gEnemyHeaderPtr
	ldr r0, [r0]
	bl AllocEntityLast
	adds r3, r0, #0
	cmp r3, #0
	beq _0808F334
	adds r1, r3, #0
	adds r1, #0x25
	movs r2, #0
	movs r0, #0x18
	strb r0, [r1]
	ldr r0, _0808F340 @ =gEnemyFnTable
	movs r1, #0x39
	strb r1, [r3, #9]
	adds r0, #0xe4
	ldr r0, [r0]
	ldr r0, [r0]
	str r0, [r3, #0x14]
	movs r0, #0
	strh r2, [r3, #0x20]
	adds r1, r3, #0
	adds r1, #0x22
	strb r0, [r1]
	ldrb r1, [r3, #0xb]
	movs r0, #0x10
	orrs r0, r1
	strb r0, [r3, #0xb]
	ldrb r0, [r3, #0x1c]
	strb r0, [r3, #0x1d]
	movs r0, #2
	strb r0, [r3, #0x10]
	str r5, [r3, #0x54]
	str r6, [r3, #0x58]
	strb r4, [r3, #0x12]
_0808F334:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_0808F33C: .4byte gEnemyHeaderPtr
_0808F340: .4byte gEnemyFnTable
_0808F344:
	.byte 0x70, 0x47, 0x00, 0x00

	thumb_func_start FUN_0808f348
FUN_0808f348: @ 0x0808F348
	push {lr}
	adds r2, r0, #0
	adds r3, r2, #0
	adds r3, #0x8c
	ldr r0, [r3]
	movs r1, #0x80
	lsls r1, r1, #2
	ands r0, r1
	cmp r0, #0
	beq _0808F3A2
	ldr r1, _0808F390 @ =gEnemyFnTable
	ldrb r0, [r2, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r2, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r2, #0x14]
	ldrb r0, [r2, #0x10]
	cmp r0, #2
	beq _0808F394
	ldr r0, [r3]
	movs r1, #0x80
	lsls r1, r1, #9
	ands r0, r1
	cmp r0, #0
	beq _0808F394
	adds r0, r2, #0
	adds r0, #0xc0
	ldrb r0, [r0]
	cmp r0, #9
	bls _0808F394
	movs r0, #1
	b _0808F396
	.align 2, 0
_0808F390: .4byte gEnemyFnTable
_0808F394:
	movs r0, #0
_0808F396:
	strb r0, [r2, #0xd]
	adds r0, r2, #0
	bl Seimeran_Die
	movs r0, #1
	b _0808F3A4
_0808F3A2:
	movs r0, #0
_0808F3A4:
	pop {r1}
	bx r1

	thumb_func_start FUN_0808f3a8
FUN_0808f3a8: @ 0x0808F3A8
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0x10]
	cmp r0, #2
	beq _0808F41C
	adds r0, r4, #0
	adds r0, #0xb4
	ldr r0, [r0]
	cmp r0, #0
	bne _0808F41C
	ldrb r0, [r4, #0xf]
	cmp r0, #0
	beq _0808F3C8
	cmp r0, #1
	beq _0808F40C
	b _0808F41C
_0808F3C8:
	adds r0, r4, #0
	bl IsFrozen
	cmp r0, #0
	beq _0808F41C
	ldr r1, _0808F404 @ =0x083693D4
	ldrb r0, [r4, #0xd]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r1, [r0]
	adds r0, r4, #0
	bl _call_via_r1
	ldr r1, _0808F408 @ =0x083693F4
	ldrb r0, [r4, #0xd]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r1, [r0]
	adds r0, r4, #0
	bl _call_via_r1
	ldrb r0, [r4, #0xf]
	adds r0, #1
	strb r0, [r4, #0xf]
	adds r0, r4, #0
	bl UpdateMotionGraphic
	movs r0, #1
	b _0808F41E
	.align 2, 0
_0808F404: .4byte 0x083693D4
_0808F408: .4byte 0x083693F4
_0808F40C:
	adds r0, r4, #0
	bl IsFrozen
	cmp r0, #0
	beq _0808F41A
	movs r0, #1
	b _0808F41E
_0808F41A:
	strb r0, [r4, #0xf]
_0808F41C:
	movs r0, #0
_0808F41E:
	pop {r4}
	pop {r1}
	bx r1

	thumb_func_start FUN_0808f424
FUN_0808f424: @ 0x0808F424
	push {r4, r5, r6, lr}
	adds r4, r0, #0
	adds r6, r4, #0
	adds r6, #0xb4
	ldr r5, [r6]
	cmp r5, #0
	bne _0808F464
	ldrb r0, [r4, #0x10]
	cmp r0, #2
	beq _0808F464
	ldrb r0, [r4, #0xd]
	cmp r0, #5
	beq _0808F464
	cmp r0, #6
	beq _0808F464
	adds r0, r4, #0
	adds r0, #0x8c
	ldr r0, [r0]
	movs r1, #1
	ands r0, r1
	cmp r0, #0
	beq _0808F464
	ldr r2, _0808F46C @ =0x08369594
	movs r0, #0
	adds r1, r4, #0
	bl ApplyElementEffect
	str r0, [r6]
	cmp r0, #0
	beq _0808F464
	strb r5, [r4, #0xd]
	strb r5, [r4, #0xe]
_0808F464:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_0808F46C: .4byte 0x08369594

	thumb_func_start Seimeran_Init
Seimeran_Init: @ 0x0808F470
	push {r4, r5, r6, lr}
	adds r5, r0, #0
	ldr r1, _0808F4C4 @ =gEnemyFnTable
	ldrb r0, [r5, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r5, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r5, #0x14]
	ldr r1, _0808F4C8 @ =0x0836959C
	ldrb r0, [r5, #0x10]
	adds r0, r0, r1
	ldrb r0, [r0]
	movs r6, #0
	strb r0, [r5, #0xd]
	ldrb r0, [r5, #0xa]
	movs r1, #2
	orrs r0, r1
	movs r1, #1
	movs r4, #0
	orrs r0, r1
	strb r0, [r5, #0xa]
	adds r0, r5, #0
	bl InitNonAffineMotion
	ldrb r0, [r5, #0x10]
	cmp r0, #2
	bne _0808F4D0
	ldrb r0, [r5, #0xa]
	movs r1, #4
	orrs r0, r1
	strb r0, [r5, #0xa]
	adds r4, r5, #0
	adds r4, #0x74
	ldr r1, _0808F4CC @ =0x0836941C
	adds r2, r5, #0
	adds r2, #0x54
	adds r0, r4, #0
	movs r3, #4
	b _0808F4E6
	.align 2, 0
_0808F4C4: .4byte gEnemyFnTable
_0808F4C8: .4byte 0x0836959C
_0808F4CC: .4byte 0x0836941C
_0808F4D0:
	ldrb r0, [r5, #0xa]
	movs r1, #4
	orrs r0, r1
	strb r0, [r5, #0xa]
	adds r4, r5, #0
	adds r4, #0x74
	ldr r1, _0808F528 @ =0x0836941C
	adds r2, r5, #0
	adds r2, #0x54
	adds r0, r4, #0
	movs r3, #6
_0808F4E6:
	bl InitBody
	str r5, [r4, #0x2c]
	str r6, [r4, #0x24]
	ldr r0, _0808F52C @ =0x0808F345
	str r0, [r4, #0x24]
	adds r0, r5, #0
	adds r0, #0xb4
	movs r4, #0
	str r4, [r0]
	ldrb r0, [r5, #0x10]
	cmp r0, #0
	bne _0808F514
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x58]
	bl FUN_08009f6c
	str r0, [r5, #0x58]
	adds r0, r5, #0
	adds r0, #0xb8
	str r4, [r0]
	adds r0, #4
	str r4, [r0]
_0808F514:
	adds r0, r5, #0
	adds r0, #0xc0
	strb r4, [r0]
	adds r0, r5, #0
	bl Seimeran_Update
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_0808F528: .4byte 0x0836941C
_0808F52C: .4byte 0x0808F345

	thumb_func_start Seimeran_Update
Seimeran_Update: @ 0x0808F530
	push {r4, r5, lr}
	adds r4, r0, #0
	ldr r0, _0808F564 @ =gCurStory
	ldrb r3, [r0, #8]
	movs r0, #2
	ands r0, r3
	lsls r0, r0, #0x18
	lsrs r2, r0, #0x18
	cmp r2, #0
	beq _0808F568
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
	b _0808F68E
	.align 2, 0
_0808F564: .4byte gCurStory
_0808F568:
	ldrb r1, [r4, #0x10]
	cmp r1, #0
	bne _0808F5C8
	adds r2, r4, #0
	adds r2, #0xb8
	ldr r0, [r2]
	cmp r0, #0
	beq _0808F580
	ldrb r0, [r0, #0xc]
	cmp r0, #1
	bls _0808F580
	str r1, [r2]
_0808F580:
	adds r1, r4, #0
	adds r1, #0xbc
	ldr r0, [r1]
	cmp r0, #0
	beq _0808F594
	ldrb r0, [r0, #0xc]
	cmp r0, #1
	bls _0808F594
	movs r0, #0
	str r0, [r1]
_0808F594:
	ldr r0, _0808F5C4 @ =gStageRun+232
	adds r1, r4, #0
	adds r1, #0x54
	bl CalcFromCamera
	movs r1, #0xc0
	lsls r1, r1, #7
	cmp r0, r1
	bls _0808F61C
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
	b _0808F68E
	.align 2, 0
_0808F5C4: .4byte gStageRun+232
_0808F5C8:
	movs r0, #0x40
	ands r0, r3
	lsls r0, r0, #0x18
	lsrs r3, r0, #0x18
	cmp r3, #0
	beq _0808F5F0
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
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
	b _0808F68E
_0808F5F0:
	cmp r1, #1
	bne _0808F61C
	ldr r5, [r4, #0x28]
	cmp r5, #0
	bne _0808F614
	ldr r0, _0808F610 @ =gStageRun+232
	adds r1, r4, #0
	adds r1, #0x54
	bl CalcFromCamera
	movs r1, #0x80
	lsls r1, r1, #5
	cmp r0, r1
	bls _0808F61C
	b _0808F674
	.align 2, 0
_0808F610: .4byte gStageRun+232
_0808F614:
	ldrb r0, [r5, #0xc]
	cmp r0, #1
	bls _0808F61C
	str r3, [r4, #0x28]
_0808F61C:
	adds r0, r4, #0
	bl FUN_0808f348
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _0808F6A8
	adds r0, r4, #0
	bl FUN_0808f424
	adds r0, r4, #0
	bl FUN_0808f3a8
	lsls r0, r0, #0x18
	lsrs r5, r0, #0x18
	cmp r5, #0
	bne _0808F6A8
	ldr r1, _0808F6B0 @ =0x083693D4
	ldrb r0, [r4, #0xd]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r1, [r0]
	adds r0, r4, #0
	bl _call_via_r1
	ldr r1, _0808F6B4 @ =0x083693F4
	ldrb r0, [r4, #0xd]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r1, [r0]
	adds r0, r4, #0
	bl _call_via_r1
	ldrb r0, [r4, #0x10]
	cmp r0, #1
	bne _0808F6A8
	ldr r0, _0808F6B8 @ =gStageRun+232
	adds r1, r4, #0
	adds r1, #0x54
	bl CalcFromCamera
	movs r1, #0xc0
	lsls r1, r1, #7
	cmp r0, r1
	bls _0808F6A8
_0808F674:
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
_0808F68E:
	ldrb r1, [r4, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r4, #0xa]
	ldr r1, _0808F6BC @ =gEnemyFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r4, #0x14]
_0808F6A8:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_0808F6B0: .4byte 0x083693D4
_0808F6B4: .4byte 0x083693F4
_0808F6B8: .4byte gStageRun+232
_0808F6BC: .4byte gEnemyFnTable

	thumb_func_start Seimeran_Die
Seimeran_Die: @ 0x0808F6C0
	push {lr}
	adds r3, r0, #0
	ldr r0, _0808F708 @ =gCurStory
	ldrb r1, [r0, #8]
	movs r0, #0x40
	ands r0, r1
	cmp r0, #0
	beq _0808F710
	ldrb r1, [r3, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r2, #0
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r3, #0xa]
	adds r0, r3, #0
	adds r0, #0x8c
	str r2, [r0]
	adds r0, #4
	str r2, [r0]
	adds r0, #4
	strb r2, [r0]
	ldrb r1, [r3, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r3, #0xa]
	ldr r1, _0808F70C @ =gEnemyFnTable
	ldrb r0, [r3, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r3, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r3, #0x14]
	b _0808F720
	.align 2, 0
_0808F708: .4byte gCurStory
_0808F70C: .4byte gEnemyFnTable
_0808F710:
	ldr r0, _0808F724 @ =0x08369414
	ldrb r1, [r3, #0xd]
	lsls r1, r1, #2
	adds r1, r1, r0
	ldr r1, [r1]
	adds r0, r3, #0
	bl _call_via_r1
_0808F720:
	pop {r0}
	bx r0
	.align 2, 0
_0808F724: .4byte 0x08369414
