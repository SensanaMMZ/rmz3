	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_08091280
FUN_08091280: @ 0x08091280
	push {r4, r5, r6, lr}
	mov r6, sl
	mov r5, sb
	mov r4, r8
	push {r4, r5, r6}
	mov sl, r0
	ldr r0, _08091300 @ =RNG_0202f388
	mov sb, r0
	ldr r0, [r0]
	ldr r6, _08091304 @ =0x000343FD
	muls r0, r6, r0
	ldr r4, _08091308 @ =0x00269EC3
	adds r0, r0, r4
	lsls r0, r0, #1
	lsrs r2, r0, #1
	lsrs r0, r0, #0x11
	movs r1, #0x1f
	ands r0, r1
	subs r0, #0x10
	lsls r0, r0, #8
	mov r1, sl
	ldr r5, [r1, #0x54]
	adds r5, r5, r0
	adds r0, r2, #0
	muls r0, r6, r0
	adds r0, r0, r4
	lsls r0, r0, #1
	lsrs r2, r0, #1
	mov r8, r2
	mov r1, sb
	str r2, [r1]
	lsrs r0, r0, #0x11
	rsbs r0, r0, #0
	movs r1, #0x30
	bl __umodsi3
	lsls r0, r0, #8
	mov r2, sl
	ldr r1, [r2, #0x58]
	subs r1, r1, r0
	movs r2, #0x80
	lsls r2, r2, #1
	mov r3, r8
	muls r3, r6, r3
	adds r3, r3, r4
	lsls r3, r3, #1
	lsrs r0, r3, #1
	mov r4, sb
	str r0, [r4]
	lsrs r3, r3, #0x11
	movs r0, #0x7f
	ands r3, r0
	movs r0, #0x80
	orrs r3, r0
	adds r0, r5, #0
	bl FUN_080c4c2c
	pop {r3, r4, r5}
	mov r8, r3
	mov sb, r4
	mov sl, r5
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_08091300: .4byte RNG_0202f388
_08091304: .4byte 0x000343FD
_08091308: .4byte 0x00269EC3

	thumb_func_start FUN_0809130c
FUN_0809130c: @ 0x0809130C
	push {r4, r5, r6, r7, lr}
	adds r5, r0, #0
	lsls r1, r1, #0x18
	lsrs r6, r1, #0x18
	adds r7, r6, #0
	ldr r0, _080913B8 @ =gEnemyHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	adds r4, r0, #0
	cmp r4, #0
	beq _080913B2
	adds r1, r4, #0
	adds r1, #0x25
	movs r2, #0
	movs r0, #0x18
	strb r0, [r1]
	ldr r0, _080913BC @ =gEnemyFnTable
	movs r1, #0x3b
	strb r1, [r4, #9]
	adds r0, #0xec
	ldr r0, [r0]
	ldr r0, [r0]
	str r0, [r4, #0x14]
	movs r0, #0
	strh r2, [r4, #0x20]
	adds r1, r4, #0
	adds r1, #0x22
	strb r0, [r1]
	ldrb r1, [r4, #0xb]
	movs r0, #0x10
	orrs r0, r1
	strb r0, [r4, #0xb]
	ldrb r0, [r4, #0x1c]
	strb r0, [r4, #0x1d]
	ldr r0, [r5, #0x54]
	str r0, [r4, #0x54]
	ldr r0, [r5, #0x58]
	str r0, [r4, #0x58]
	cmp r6, #3
	bhi _08091372
	subs r0, r6, #2
	lsls r1, r0, #1
	adds r1, r1, r0
	lsls r1, r1, #0xc
	movs r0, #0xc0
	lsls r0, r0, #5
	adds r1, r1, r0
	ldr r0, [r5, #0x54]
	adds r0, r0, r1
	str r0, [r4, #0x64]
_08091372:
	cmp r6, #4
	bls _0809138A
	subs r0, r6, #7
	lsls r1, r0, #1
	adds r1, r1, r0
	lsls r1, r1, #0xc
	movs r0, #0xc0
	lsls r0, r0, #5
	adds r1, r1, r0
	ldr r0, [r5, #0x54]
	adds r0, r0, r1
	str r0, [r4, #0x54]
_0809138A:
	str r5, [r4, #0x28]
	adds r0, r4, #0
	bl InitNonAffineMotion
	adds r0, r4, #0
	bl ResetDynamicMotion
	ldr r0, [r5, #8]
	str r0, [r4, #0x3c]
	ldrb r1, [r5, #0x15]
	adds r3, r4, #0
	adds r3, #0x49
	lsrs r1, r1, #4
	lsls r1, r1, #4
	ldrb r2, [r3]
	movs r0, #0xf
	ands r0, r2
	orrs r0, r1
	strb r0, [r3]
	strb r7, [r4, #0x10]
_080913B2:
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080913B8: .4byte gEnemyHeaderPtr
_080913BC: .4byte gEnemyFnTable

	thumb_func_start FUN_080913c0
FUN_080913c0: @ 0x080913C0
	push {r4, r5, lr}
	adds r4, r0, #0
	lsls r1, r1, #0x18
	lsrs r5, r1, #0x18
	ldr r0, _08091424 @ =gEnemyHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	adds r3, r0, #0
	cmp r3, #0
	beq _0809141E
	adds r1, r3, #0
	adds r1, #0x25
	movs r2, #0
	movs r0, #0x18
	strb r0, [r1]
	ldr r0, _08091428 @ =gEnemyFnTable
	movs r1, #0x3b
	strb r1, [r3, #9]
	adds r0, #0xec
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
	ldr r0, [r4, #0x54]
	str r0, [r3, #0x54]
	ldr r0, [r4, #0x58]
	str r0, [r3, #0x58]
	strb r5, [r3, #0x10]
	movs r1, #0
	adds r0, r4, #0
	adds r0, #0xb4
	ldr r0, [r0]
	cmp r0, #0
	ble _0809141C
	movs r1, #1
_0809141C:
	strb r1, [r3, #0x13]
_0809141E:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_08091424: .4byte gEnemyHeaderPtr
_08091428: .4byte gEnemyFnTable

	thumb_func_start FUN_0809142c
FUN_0809142c: @ 0x0809142C
	push {r4, r5, lr}
	adds r4, r0, #0
	lsls r1, r1, #0x18
	lsrs r5, r1, #0x18
	ldr r0, _0809148C @ =gEnemyHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	adds r3, r0, #0
	cmp r3, #0
	beq _08091484
	adds r1, r3, #0
	adds r1, #0x25
	movs r2, #0
	movs r0, #0x18
	strb r0, [r1]
	ldr r0, _08091490 @ =gEnemyFnTable
	movs r1, #0x3b
	strb r1, [r3, #9]
	adds r0, #0xec
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
	ldr r0, [r4, #0x54]
	str r0, [r3, #0x54]
	ldr r0, [r4, #0x58]
	ldr r1, _08091494 @ =0xFFFFF600
	adds r0, r0, r1
	str r0, [r3, #0x58]
	movs r0, #0xc
	strb r0, [r3, #0x10]
	strb r5, [r3, #0x12]
	str r4, [r3, #0x28]
_08091484:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_0809148C: .4byte gEnemyHeaderPtr
_08091490: .4byte gEnemyFnTable
_08091494: .4byte 0xFFFFF600

	thumb_func_start Enemy59_Init
Enemy59_Init: @ 0x08091498
	push {r4, r5, lr}
	adds r5, r0, #0
	ldrb r0, [r5, #0x10]
	cmp r0, #0xc
	bne _08091500
	ldr r1, _080914F0 @ =gEnemyFnTable
	ldrb r0, [r5, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r5, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r5, #0x14]
	ldrb r1, [r5, #0xa]
	movs r0, #2
	orrs r0, r1
	movs r1, #1
	orrs r0, r1
	movs r1, #4
	orrs r0, r1
	strb r0, [r5, #0xa]
	adds r4, r5, #0
	adds r4, #0x74
	ldr r1, _080914F4 @ =0x08369864
	adds r2, r5, #0
	adds r2, #0x54
	adds r0, r4, #0
	movs r3, #6
	bl InitBody
	str r5, [r4, #0x2c]
	ldr r0, _080914F8 @ =FUN_08091790
	str r0, [r4, #0x24]
	ldr r1, _080914FC @ =0x08369A14
	ldrb r0, [r5, #0x10]
	adds r0, r0, r1
	ldrb r0, [r0]
	strb r0, [r5, #0xd]
	adds r0, r5, #0
	bl Enemy59_Update
	b _08091586
	.align 2, 0
_080914F0: .4byte gEnemyFnTable
_080914F4: .4byte 0x08369864
_080914F8: .4byte FUN_08091790
_080914FC: .4byte 0x08369A14
_08091500:
	cmp r0, #8
	bls _0809153C
	ldr r1, _08091534 @ =gEnemyFnTable
	ldrb r0, [r5, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r5, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r5, #0x14]
	ldrb r1, [r5, #0xa]
	movs r0, #2
	orrs r0, r1
	movs r1, #1
	orrs r0, r1
	strb r0, [r5, #0xa]
	ldr r1, _08091538 @ =0x08369A14
	ldrb r0, [r5, #0x10]
	adds r0, r0, r1
	ldrb r0, [r0]
	strb r0, [r5, #0xd]
	adds r0, r5, #0
	bl Enemy59_Die
	b _08091586
	.align 2, 0
_08091534: .4byte gEnemyFnTable
_08091538: .4byte 0x08369A14
_0809153C:
	ldr r1, _0809158C @ =gEnemyFnTable
	ldrb r0, [r5, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r5, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r5, #0x14]
	ldrb r1, [r5, #0xa]
	movs r0, #2
	orrs r0, r1
	movs r1, #1
	orrs r0, r1
	movs r1, #4
	orrs r0, r1
	strb r0, [r5, #0xa]
	adds r4, r5, #0
	adds r4, #0x74
	ldr r1, _08091590 @ =0x08369864
	adds r2, r5, #0
	adds r2, #0x54
	adds r0, r4, #0
	movs r3, #1
	bl InitBody
	str r5, [r4, #0x2c]
	ldr r0, _08091594 @ =FUN_08091790
	str r0, [r4, #0x24]
	ldr r1, _08091598 @ =0x08369A14
	ldrb r0, [r5, #0x10]
	adds r0, r0, r1
	ldrb r0, [r0]
	strb r0, [r5, #0xd]
	adds r0, r5, #0
	bl Enemy59_Update
_08091586:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_0809158C: .4byte gEnemyFnTable
_08091590: .4byte 0x08369864
_08091594: .4byte FUN_08091790
_08091598: .4byte 0x08369A14

	thumb_func_start Enemy59_Update
Enemy59_Update: @ 0x0809159C
	push {r4, r5, r6, r7, lr}
	mov r7, r8
	push {r7}
	sub sp, #8
	adds r6, r0, #0
	ldr r4, [r6, #0x28]
	adds r5, r6, #0
	adds r5, #0x34
	ldrb r0, [r6, #0x10]
	cmp r0, #0xc
	bne _080915E8
	adds r0, r6, #0
	adds r0, #0x8c
	ldr r0, [r0]
	movs r1, #0x80
	lsls r1, r1, #2
	ands r0, r1
	cmp r0, #0
	bne _080915C4
	b _080916F4
_080915C4:
	ldr r1, _080915E4 @ =gEnemyFnTable
	ldrb r0, [r6, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r6, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r6, #0x14]
	movs r0, #3
	strb r0, [r6, #0xd]
	adds r0, r6, #0
	bl Enemy59_Die
	b _0809175E
	.align 2, 0
_080915E4: .4byte gEnemyFnTable
_080915E8:
	ldrb r0, [r4, #0xc]
	cmp r0, #1
	bls _08091614
	ldrb r1, [r6, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r2, #0
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r6, #0xa]
	adds r0, r6, #0
	adds r0, #0x8c
	str r2, [r0]
	adds r0, #4
	str r2, [r0]
	adds r0, #4
	strb r2, [r0]
	ldrb r1, [r6, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r6, #0xa]
	b _080916DC
_08091614:
	adds r1, r6, #0
	adds r1, #0x8c
	ldr r0, [r1]
	movs r2, #0x80
	lsls r2, r2, #2
	mov r8, r2
	ands r0, r2
	adds r7, r1, #0
	cmp r0, #0
	beq _080916F4
	adds r0, r6, #0
	bl FUN_08091280
	adds r2, r4, #0
	adds r2, #0xc4
	ldr r0, [r2]
	movs r1, #0x10
	orrs r0, r1
	str r0, [r2]
	ldr r0, [r6, #0x54]
	str r0, [sp]
	ldr r0, [r6, #0x58]
	ldr r1, _08091680 @ =0xFFFFEC00
	adds r0, r0, r1
	str r0, [sp, #4]
	ldr r0, [r7]
	movs r1, #0x80
	lsls r1, r1, #9
	ands r0, r1
	cmp r0, #0
	beq _080916A6
	movs r3, #0
	adds r0, r6, #0
	adds r0, #0xb4
	ldr r0, [r0]
	cmp r0, #0
	ble _08091660
	movs r3, #1
_08091660:
	movs r0, #0
	mov r1, sp
	mov r2, r8
	bl FUN_080b2b40
	ldr r0, [r7]
	movs r1, #0x80
	lsls r1, r1, #8
	ands r0, r1
	cmp r0, #0
	beq _08091684
	adds r0, r6, #0
	movs r1, #0xb
	bl FUN_080913c0
	b _080916AE
	.align 2, 0
_08091680: .4byte 0xFFFFEC00
_08091684:
	ldr r0, [r6, #0x54]
	ldr r1, [r6, #0x58]
	bl FUN_08009f6c
	ldr r1, [r6, #0x58]
	cmp r1, r0
	bne _0809169C
	adds r0, r6, #0
	movs r1, #0xa
	bl FUN_080913c0
	b _080916AE
_0809169C:
	adds r0, r6, #0
	movs r1, #9
	bl FUN_080913c0
	b _080916AE
_080916A6:
	adds r0, r6, #0
	movs r1, #9
	bl FUN_080913c0
_080916AE:
	movs r3, #0
	str r3, [r7]
	adds r5, r6, #0
	adds r5, #0x90
	str r3, [r5]
	adds r4, r6, #0
	adds r4, #0x94
	strb r3, [r4]
	ldrb r1, [r6, #0xa]
	movs r2, #0xfb
	adds r0, r2, #0
	ands r0, r1
	movs r1, #0xfe
	ands r0, r1
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r6, #0xa]
	str r3, [r7]
	str r3, [r5]
	strb r3, [r4]
	ldrb r0, [r6, #0xa]
	ands r2, r0
	strb r2, [r6, #0xa]
_080916DC:
	ldr r1, _080916F0 @ =gEnemyFnTable
	ldrb r0, [r6, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r6, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r6, #0x14]
	b _0809175E
	.align 2, 0
_080916F0: .4byte gEnemyFnTable
_080916F4:
	ldr r1, _0809176C @ =0x083699B4
	ldrb r0, [r6, #0xd]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r1, [r0]
	adds r0, r6, #0
	bl _call_via_r1
	ldr r1, _08091770 @ =0x083699DC
	ldrb r0, [r6, #0xd]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r1, [r0]
	adds r0, r6, #0
	bl _call_via_r1
	ldrb r0, [r6, #0x10]
	cmp r0, #0xc
	beq _0809175E
	adds r0, r4, #0
	adds r0, #0x70
	ldrb r1, [r0]
	ldr r0, [r4, #0x6c]
	lsls r1, r1, #2
	adds r1, r1, r0
	adds r0, r4, #0
	adds r0, #0x71
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	ldr r1, [r1]
	lsls r0, r0, #1
	adds r0, r0, r1
	ldrb r0, [r0]
	strb r0, [r5, #0x1a]
	adds r1, r4, #0
	adds r1, #0x34
	ldr r0, [r1, #8]
	str r0, [r5, #8]
	ldrh r1, [r1, #0x14]
	lsls r1, r1, #0x16
	lsrs r1, r1, #0x16
	ldrh r2, [r5, #0x14]
	ldr r0, _08091774 @ =0xFFFFFC00
	ands r0, r2
	orrs r0, r1
	strh r0, [r5, #0x14]
	adds r0, r4, #0
	adds r0, #0x23
	ldrb r1, [r0]
	adds r0, r6, #0
	adds r0, #0x23
	strb r1, [r0]
_0809175E:
	add sp, #8
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_0809176C: .4byte 0x083699B4
_08091770: .4byte 0x083699DC
_08091774: .4byte 0xFFFFFC00

	thumb_func_start Enemy59_Die
Enemy59_Die: @ 0x08091778
	push {lr}
	ldr r2, _0809178C @ =0x08369A04
	ldrb r1, [r0, #0xd]
	lsls r1, r1, #2
	adds r1, r1, r2
	ldr r1, [r1]
	bl _call_via_r1
	pop {r0}
	bx r0
	.align 2, 0
_0809178C: .4byte 0x08369A04

	thumb_func_start FUN_08091790
FUN_08091790: @ 0x08091790
	push {r4, lr}
	adds r1, r0, #0
	ldr r0, [r1, #0xc]
	ldr r4, [r0, #0x2c]
	ldr r3, [r1, #0x2c]
	ldrb r0, [r3, #0x10]
	cmp r0, #0xc
	bne _080917F4
	ldr r0, [r1, #0x14]
	movs r1, #8
	ands r0, r1
	cmp r0, #0
	beq _08091804
	movs r0, #8
	ldrsb r0, [r4, r0]
	cmp r0, #2
	bne _08091804
	ldrb r0, [r4, #0xd]
	cmp r0, #1
	bne _08091804
	ldrb r0, [r4, #0xe]
	subs r0, #1
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #1
	bhi _08091804
	ldrb r0, [r4, #9]
	cmp r0, #0x15
	bne _08091804
	ldr r0, [r3, #0xc]
	ldr r1, _080917F0 @ =0x00FFFF00
	ands r0, r1
	movs r1, #0xc2
	lsls r1, r1, #0xa
	cmp r0, r1
	bne _08091804
	adds r2, r3, #0
	adds r2, #0xb4
	ldr r0, [r4, #0x54]
	ldr r1, [r3, #0x54]
	subs r0, r0, r1
	str r0, [r2]
	movs r1, #0
	movs r0, #9
	strb r0, [r3, #0xd]
	strb r1, [r3, #0xe]
	b _08091804
	.align 2, 0
_080917F0: .4byte 0x00FFFF00
_080917F4:
	adds r2, r3, #0
	adds r2, #0xb4
	ldr r0, _0809180C @ =pZero2
	ldr r0, [r0]
	ldr r0, [r0, #0x54]
	ldr r1, [r3, #0x54]
	subs r0, r0, r1
	str r0, [r2]
_08091804:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_0809180C: .4byte pZero2
