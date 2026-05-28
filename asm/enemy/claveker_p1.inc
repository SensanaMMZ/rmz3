	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start Claveker_Init
Claveker_Init: @ 0x0808E52C
	push {r4, r5, r6, lr}
	adds r6, r0, #0
	bl InitNonAffineMotion
	ldrb r1, [r6, #0xa]
	movs r0, #1
	movs r3, #0
	adds r2, r0, #0
	orrs r2, r1
	movs r0, #2
	orrs r2, r0
	orrs r2, r3
	strb r2, [r6, #0xa]
	ldr r0, _0808E578 @ =gSystemSavedataManager
	ldrb r1, [r0, #0x13]
	movs r0, #0x80
	ands r0, r1
	cmp r0, #0
	beq _0808E584
	ldr r0, _0808E57C @ =gCurStory
	ldrb r1, [r0, #4]
	movs r0, #0x40
	ands r0, r1
	lsls r0, r0, #0x18
	lsrs r5, r0, #0x18
	cmp r5, #0
	bne _0808E584
	movs r0, #4
	orrs r2, r0
	strb r2, [r6, #0xa]
	adds r4, r6, #0
	adds r4, #0x74
	ldr r1, _0808E580 @ =0x08369388
	adds r2, r6, #0
	adds r2, #0x54
	adds r0, r4, #0
	movs r3, #0xe
	b _0808E59C
	.align 2, 0
_0808E578: .4byte gSystemSavedataManager
_0808E57C: .4byte gCurStory
_0808E580: .4byte 0x08369388
_0808E584:
	ldrb r1, [r6, #0xa]
	movs r0, #4
	movs r5, #0
	orrs r0, r1
	strb r0, [r6, #0xa]
	adds r4, r6, #0
	adds r4, #0x74
	ldr r1, _0808E60C @ =0x08369388
	adds r2, r6, #0
	adds r2, #0x54
	adds r0, r4, #0
	movs r3, #0xa
_0808E59C:
	bl InitBody
	str r6, [r4, #0x2c]
	str r5, [r4, #0x24]
	ldr r0, _0808E610 @ =FUN_0808f234
	str r0, [r4, #0x24]
	ldr r0, [r6, #0x54]
	ldr r1, [r6, #0x58]
	bl FUN_0800a134
	str r0, [r6, #0x58]
	adds r1, r6, #0
	adds r1, #0xb4
	ldr r0, [r6, #0x54]
	str r0, [r1]
	adds r0, r6, #0
	adds r0, #0xb8
	movs r4, #0
	strb r4, [r0]
	adds r0, #4
	str r4, [r0]
	ldr r1, _0808E614 @ =gEnemyFnTable
	ldrb r0, [r6, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r6, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r6, #0x14]
	strb r4, [r6, #0xd]
	strb r4, [r6, #0xe]
	strb r4, [r6, #0xf]
	adds r0, r6, #0
	bl IsFrozen
	cmp r0, #0
	beq _0808E5F8
	movs r1, #0xea
	lsls r1, r1, #7
	adds r0, r6, #0
	bl SetMotion
	adds r0, r6, #0
	bl UpdateMotionGraphic
_0808E5F8:
	adds r0, r6, #0
	adds r0, #0xbb
	strb r4, [r0]
	adds r0, r6, #0
	bl Claveker_Update
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_0808E60C: .4byte 0x08369388
_0808E610: .4byte FUN_0808f234
_0808E614: .4byte gEnemyFnTable

	thumb_func_start Claveker_Update
Claveker_Update: @ 0x0808E618
	push {r4, r5, lr}
	adds r4, r0, #0
	adds r0, #0x8c
	ldr r5, [r0]
	movs r0, #0x80
	lsls r0, r0, #2
	ands r5, r0
	cmp r5, #0
	beq _0808E648
	ldr r1, _0808E644 @ =gEnemyFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r4, #0x14]
	adds r0, r4, #0
	bl Claveker_Die
	b _0808E6FC
	.align 2, 0
_0808E644: .4byte gEnemyFnTable
_0808E648:
	ldr r1, _0808E6A0 @ =0x08369340
	ldrb r0, [r4, #0xd]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r1, [r0]
	adds r0, r4, #0
	bl _call_via_r1
	adds r0, r4, #0
	bl FUN_0808f1e0
	adds r0, r4, #0
	bl IsFrozen
	cmp r0, #0
	beq _0808E67E
	ldrb r0, [r4, #0xd]
	cmp r0, #2
	beq _0808E67E
	cmp r0, #3
	beq _0808E67E
	cmp r0, #5
	beq _0808E67E
	cmp r0, #4
	beq _0808E67E
	strb r5, [r4, #0xd]
	strb r5, [r4, #0xe]
_0808E67E:
	adds r0, r4, #0
	adds r0, #0xbc
	ldr r1, [r0]
	adds r5, r0, #0
	cmp r1, #0
	bne _0808E6A4
	adds r0, r4, #0
	bl IsFrozen
	cmp r0, #0
	beq _0808E6A4
	ldrb r1, [r4, #0xd]
	adds r0, r4, #0
	adds r0, #0xba
	strb r1, [r0]
	b _0808E6FC
	.align 2, 0
_0808E6A0: .4byte 0x08369340
_0808E6A4:
	adds r0, r4, #0
	bl IsFrozen
	cmp r0, #0
	beq _0808E6B4
	movs r0, #0
	strb r0, [r4, #0xd]
	strb r0, [r4, #0xe]
_0808E6B4:
	ldr r0, [r5]
	cmp r0, #0
	beq _0808E6EC
	bl isKilled
	cmp r0, #0
	beq _0808E6DC
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _0808E6D8 @ =0x08369388
	bl SetDDP
	movs r0, #0
	str r0, [r5]
	strb r0, [r4, #0xd]
	strb r0, [r4, #0xe]
	b _0808E6FC
	.align 2, 0
_0808E6D8: .4byte 0x08369388
_0808E6DC:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _0808E6E8 @ =0x083693A0
	bl SetDDP
	b _0808E6FC
	.align 2, 0
_0808E6E8: .4byte 0x083693A0
_0808E6EC:
	ldr r0, _0808E704 @ =0x08369358
	ldrb r1, [r4, #0xd]
	lsls r1, r1, #2
	adds r1, r1, r0
	ldr r1, [r1]
	adds r0, r4, #0
	bl _call_via_r1
_0808E6FC:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_0808E704: .4byte 0x08369358

	thumb_func_start Claveker_Die
Claveker_Die: @ 0x0808E708
	push {r4, r5, r6, r7, lr}
	mov r7, r8
	push {r7}
	sub sp, #0x20
	adds r7, r0, #0
	ldr r0, _0808E754 @ =gCurStory
	ldrb r1, [r0, #8]
	movs r0, #0x40
	ands r0, r1
	cmp r0, #0
	beq _0808E75C
	ldrb r1, [r7, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r2, #0
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r7, #0xa]
	adds r0, r7, #0
	adds r0, #0x8c
	str r2, [r0]
	adds r0, #4
	str r2, [r0]
	adds r0, #4
	strb r2, [r0]
	ldrb r1, [r7, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r7, #0xa]
	ldr r1, _0808E758 @ =gEnemyFnTable
	ldrb r0, [r7, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r7, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	b _0808EAEE
	.align 2, 0
_0808E754: .4byte gCurStory
_0808E758: .4byte gEnemyFnTable
_0808E75C:
	ldrb r0, [r7, #0xe]
	cmp r0, #0xb
	bls _0808E764
	b _0808EAF0
_0808E764:
	lsls r0, r0, #2
	ldr r1, _0808E770 @ =_0808E774
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_0808E770: .4byte _0808E774
_0808E774: @ jump table
	.4byte _0808E7A4 @ case 0
	.4byte _0808E8C8 @ case 1
	.4byte _0808E7F4 @ case 2
	.4byte _0808E808 @ case 3
	.4byte _0808E8D0 @ case 4
	.4byte _0808EAF0 @ case 5
	.4byte _0808EAF0 @ case 6
	.4byte _0808EAF0 @ case 7
	.4byte _0808EAF0 @ case 8
	.4byte _0808EAF0 @ case 9
	.4byte _0808E8C8 @ case 10
	.4byte _0808EA50 @ case 11
_0808E7A4:
	ldr r1, _0808E7CC @ =0x00007505
	adds r0, r7, #0
	bl SetMotion
	adds r1, r7, #0
	adds r1, #0x8c
	ldr r2, [r1]
	movs r0, #0x80
	lsls r0, r0, #2
	ands r0, r2
	adds r3, r1, #0
	cmp r0, #0
	beq _0808E7D0
	movs r0, #0x80
	lsls r0, r0, #9
	ands r2, r0
	cmp r2, #0
	beq _0808E7D0
	movs r0, #1
	b _0808E7D2
	.align 2, 0
_0808E7CC: .4byte 0x00007505
_0808E7D0:
	movs r0, #0xa
_0808E7D2:
	strb r0, [r7, #0xe]
	movs r1, #0
	str r1, [r3]
	adds r0, r7, #0
	adds r0, #0x90
	str r1, [r0]
	adds r0, #4
	strb r1, [r0]
	ldrb r2, [r7, #0xa]
	movs r0, #0xfb
	ands r0, r2
	strb r0, [r7, #0xa]
	adds r0, r7, #0
	adds r0, #0x5c
	str r1, [r0, #4]
	str r1, [r7, #0x5c]
	b _0808E8C8
_0808E7F4:
	adds r0, r7, #0
	bl UpdateMotionGraphic
	adds r0, r7, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	beq _0808E806
	b _0808EAF0
_0808E806:
	b _0808E8C8
_0808E808:
	ldr r1, _0808E84C @ =0x00007505
	adds r0, r7, #0
	bl SetMotion
	adds r0, r7, #0
	bl UpdateMotionGraphic
	movs r0, #0
	strb r0, [r7, #0x13]
	str r0, [r7, #0x60]
	ldr r0, [r7, #0x54]
	str r0, [sp]
	ldr r0, [r7, #0x58]
	str r0, [sp, #4]
	adds r4, r7, #0
	adds r4, #0xb8
	ldrb r1, [r4]
	mov r0, sp
	bl FUN_080c4450
	ldrb r0, [r4]
	cmp r0, #0
	bne _0808E854
	ldr r0, [sp]
	ldr r1, _0808E850 @ =0xFFFFF800
	adds r0, r0, r1
	str r0, [sp]
	ldr r0, [sp, #4]
	movs r1, #0x80
	lsls r1, r1, #4
	adds r0, r0, r1
	str r0, [sp, #4]
	movs r0, #0x80
	b _0808E868
	.align 2, 0
_0808E84C: .4byte 0x00007505
_0808E850: .4byte 0xFFFFF800
_0808E854:
	ldr r0, [sp]
	movs r1, #0x80
	lsls r1, r1, #4
	adds r0, r0, r1
	str r0, [sp]
	ldr r0, [sp, #4]
	adds r0, r0, r1
	str r0, [sp, #4]
	movs r0, #0x80
	rsbs r0, r0, #0
_0808E868:
	str r0, [r7, #0x5c]
	adds r0, r7, #0
	adds r0, #0xbb
	ldrb r0, [r0]
	cmp r0, #0xff
	beq _0808E894
	cmp r0, #0xfe
	bne _0808E888
	movs r2, #0x80
	lsls r2, r2, #2
	movs r0, #0
	mov r1, sp
	movs r3, #0
	bl FUN_080b2b40
	b _0808E8B6
_0808E888:
	ldr r0, _0808E8A4 @ =pZero2
	ldr r0, [r0]
	ldr r1, [r0, #0x54]
	ldr r0, [r7, #0x54]
	cmp r1, r0
	ble _0808E8A8
_0808E894:
	movs r2, #0x80
	lsls r2, r2, #2
	movs r0, #0
	mov r1, sp
	movs r3, #1
	bl FUN_080b2b40
	b _0808E8B6
	.align 2, 0
_0808E8A4: .4byte pZero2
_0808E8A8:
	movs r2, #0x80
	lsls r2, r2, #2
	movs r0, #0
	mov r1, sp
	movs r3, #0
	bl FUN_080b2b40
_0808E8B6:
	adds r1, r7, #0
	adds r1, #0x54
	movs r0, #1
	bl TryDropItem
	movs r0, #0x80
	str r0, [r7, #0x60]
	movs r0, #0x32
	strb r0, [r7, #0x12]
_0808E8C8:
	ldrb r0, [r7, #0xe]
	adds r0, #1
	strb r0, [r7, #0xe]
	b _0808EAF0
_0808E8D0:
	adds r0, r7, #0
	bl UpdateMotionGraphic
	ldr r0, [r7, #0x60]
	adds r0, #0x20
	str r0, [r7, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _0808E8E6
	str r1, [r7, #0x60]
_0808E8E6:
	ldr r1, [r7, #0x58]
	ldr r0, [r7, #0x60]
	adds r1, r1, r0
	str r1, [r7, #0x58]
	ldr r2, [r7, #0x5c]
	rsbs r0, r2, #0
	lsls r0, r0, #2
	asrs r0, r0, #8
	adds r2, r2, r0
	str r2, [r7, #0x5c]
	ldr r0, [r7, #0x54]
	adds r0, r0, r2
	str r0, [r7, #0x54]
	bl FUN_080098a4
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _0808E9A4
	ldr r0, [r7, #0x54]
	str r0, [sp]
	ldr r0, [r7, #0x58]
	str r0, [sp, #4]
	movs r0, #2
	mov r1, sp
	bl CreateSmoke
	ldr r2, _0808E984 @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _0808E988 @ =0x000343FD
	adds r4, r1, #0
	muls r4, r0, r4
	ldr r0, _0808E98C @ =0x00269EC3
	adds r4, r4, r0
	lsls r4, r4, #1
	lsrs r0, r4, #1
	str r0, [r2]
	lsrs r4, r4, #0x11
	movs r0, #3
	ands r4, r0
	ldr r0, [r7, #0x54]
	str r0, [sp, #8]
	ldr r0, [r7, #0x58]
	add r6, sp, #8
	str r0, [r6, #4]
	adds r5, r7, #0
	adds r5, #0xb8
	ldrb r1, [r5]
	ldr r2, _0808E990 @ =0x00007507
	adds r0, r6, #0
	adds r3, r4, #0
	bl FUN_080c44a8
	ldrb r1, [r5]
	ldr r2, _0808E994 @ =0x00007508
	adds r0, r6, #0
	adds r3, r4, #0
	bl FUN_080c44a8
	ldrb r1, [r5]
	ldr r2, _0808E998 @ =0x00007509
	adds r0, r6, #0
	adds r3, r4, #0
	bl FUN_080c44a8
	movs r0, #0x2a
	bl PlaySound
	ldr r2, _0808E99C @ =gMission
	ldrh r1, [r2, #0xc]
	ldr r0, _0808E9A0 @ =0x0000270E
	cmp r1, r0
	bhi _0808E97A
	adds r0, r1, #1
	strh r0, [r2, #0xc]
_0808E97A:
	adds r1, r7, #0
	adds r1, #0x54
	adds r0, r7, #0
	b _0808EAD2
	.align 2, 0
_0808E984: .4byte RNG_0202f388
_0808E988: .4byte 0x000343FD
_0808E98C: .4byte 0x00269EC3
_0808E990: .4byte 0x00007507
_0808E994: .4byte 0x00007508
_0808E998: .4byte 0x00007509
_0808E99C: .4byte gMission
_0808E9A0: .4byte 0x0000270E
_0808E9A4:
	ldrb r0, [r7, #0x12]
	cmp r0, #0
	bne _0808E9AC
	b _0808EAF0
_0808E9AC:
	subs r0, #1
	strb r0, [r7, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _0808E9B8
	b _0808EAF0
_0808E9B8:
	ldr r0, [r7, #0x54]
	str r0, [sp]
	ldr r0, [r7, #0x58]
	str r0, [sp, #4]
	movs r0, #2
	mov r1, sp
	bl CreateSmoke
	ldr r2, _0808EA30 @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _0808EA34 @ =0x000343FD
	adds r4, r1, #0
	muls r4, r0, r4
	ldr r1, _0808EA38 @ =0x00269EC3
	adds r4, r4, r1
	lsls r4, r4, #1
	lsrs r0, r4, #1
	str r0, [r2]
	lsrs r4, r4, #0x11
	movs r0, #3
	ands r4, r0
	ldr r0, [r7, #0x54]
	str r0, [sp, #0x10]
	ldr r0, [r7, #0x58]
	add r6, sp, #0x10
	str r0, [r6, #4]
	adds r5, r7, #0
	adds r5, #0xb8
	ldrb r1, [r5]
	ldr r2, _0808EA3C @ =0x00007507
	adds r0, r6, #0
	adds r3, r4, #0
	bl FUN_080c44a8
	ldrb r1, [r5]
	ldr r2, _0808EA40 @ =0x00007508
	adds r0, r6, #0
	adds r3, r4, #0
	bl FUN_080c44a8
	ldrb r1, [r5]
	ldr r2, _0808EA44 @ =0x00007509
	adds r0, r6, #0
	adds r3, r4, #0
	bl FUN_080c44a8
	movs r0, #0x2a
	bl PlaySound
	ldr r2, _0808EA48 @ =gMission
	ldrh r1, [r2, #0xc]
	ldr r0, _0808EA4C @ =0x0000270E
	cmp r1, r0
	bhi _0808EA28
	adds r0, r1, #1
	strh r0, [r2, #0xc]
_0808EA28:
	adds r1, r7, #0
	adds r1, #0x54
	adds r0, r7, #0
	b _0808EAD2
	.align 2, 0
_0808EA30: .4byte RNG_0202f388
_0808EA34: .4byte 0x000343FD
_0808EA38: .4byte 0x00269EC3
_0808EA3C: .4byte 0x00007507
_0808EA40: .4byte 0x00007508
_0808EA44: .4byte 0x00007509
_0808EA48: .4byte gMission
_0808EA4C: .4byte 0x0000270E
_0808EA50:
	ldr r0, [r7, #0x54]
	str r0, [sp]
	ldr r0, [r7, #0x58]
	str r0, [sp, #4]
	movs r0, #1
	mov r1, sp
	bl CreateSmoke
	movs r0, #0x2a
	bl PlaySound
	movs r0, #0x54
	adds r0, r0, r7
	mov r8, r0
	movs r0, #1
	mov r1, r8
	bl TryDropItem
	ldr r2, _0808EAFC @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _0808EB00 @ =0x000343FD
	adds r4, r1, #0
	muls r4, r0, r4
	ldr r1, _0808EB04 @ =0x00269EC3
	adds r4, r4, r1
	lsls r4, r4, #1
	lsrs r0, r4, #1
	str r0, [r2]
	lsrs r4, r4, #0x11
	movs r0, #3
	ands r4, r0
	ldr r0, [r7, #0x54]
	str r0, [sp, #0x18]
	ldr r0, [r7, #0x58]
	add r6, sp, #0x18
	str r0, [r6, #4]
	adds r5, r7, #0
	adds r5, #0xb8
	ldrb r1, [r5]
	ldr r2, _0808EB08 @ =0x00007507
	adds r0, r6, #0
	adds r3, r4, #0
	bl FUN_080c44a8
	ldrb r1, [r5]
	ldr r2, _0808EB0C @ =0x00007508
	adds r0, r6, #0
	adds r3, r4, #0
	bl FUN_080c44a8
	ldrb r1, [r5]
	ldr r2, _0808EB10 @ =0x00007509
	adds r0, r6, #0
	adds r3, r4, #0
	bl FUN_080c44a8
	ldr r2, _0808EB14 @ =gMission
	ldrh r1, [r2, #0xc]
	ldr r0, _0808EB18 @ =0x0000270E
	cmp r1, r0
	bhi _0808EACE
	adds r0, r1, #1
	strh r0, [r2, #0xc]
_0808EACE:
	adds r0, r7, #0
	mov r1, r8
_0808EAD2:
	bl TryDropZakoDisk
	ldrb r1, [r7, #0xa]
	movs r0, #0xfe
	ands r0, r1
	strb r0, [r7, #0xa]
	ldr r1, _0808EB1C @ =gEnemyFnTable
	ldrb r0, [r7, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #4
	str r1, [r7, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0x10]
_0808EAEE:
	str r0, [r7, #0x14]
_0808EAF0:
	add sp, #0x20
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_0808EAFC: .4byte RNG_0202f388
_0808EB00: .4byte 0x000343FD
_0808EB04: .4byte 0x00269EC3
_0808EB08: .4byte 0x00007507
_0808EB0C: .4byte 0x00007508
_0808EB10: .4byte 0x00007509
_0808EB14: .4byte gMission
_0808EB18: .4byte 0x0000270E
_0808EB1C: .4byte gEnemyFnTable
