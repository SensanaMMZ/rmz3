	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_08098838
FUN_08098838: @ 0x08098838
	push {r4, r5, lr}
	adds r5, r0, #0
	lsls r1, r1, #0x18
	lsrs r4, r1, #0x18
	ldr r0, _08098894 @ =gEnemyHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	adds r3, r0, #0
	cmp r3, #0
	beq _0809888C
	adds r1, r3, #0
	adds r1, #0x25
	movs r2, #0
	movs r0, #0x18
	strb r0, [r1]
	ldr r0, _08098898 @ =gEnemyFnTable
	movs r1, #0x43
	strb r1, [r3, #9]
	adds r1, #0xc9
	adds r0, r0, r1
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
	ldr r0, [r5]
	ldr r1, [r5, #4]
	str r0, [r3, #0x54]
	str r1, [r3, #0x58]
	strb r4, [r3, #0x10]
	movs r0, #1
	strb r0, [r3, #0x11]
_0809888C:
	adds r0, r3, #0
	pop {r4, r5}
	pop {r1}
	bx r1
	.align 2, 0
_08098894: .4byte gEnemyHeaderPtr
_08098898: .4byte gEnemyFnTable

	thumb_func_start Cattatank_Init
Cattatank_Init: @ 0x0809889C
	push {r4, r5, r6, r7, lr}
	mov r7, r8
	push {r7}
	adds r6, r0, #0
	bl InitNonAffineMotion
	ldrb r1, [r6, #0xa]
	movs r0, #1
	movs r5, #0
	orrs r0, r1
	movs r1, #2
	orrs r0, r1
	movs r1, #0
	mov r8, r1
	movs r1, #4
	orrs r0, r1
	strb r0, [r6, #0xa]
	adds r4, r6, #0
	adds r4, #0x74
	ldr r1, _08098910 @ =0x0836A4D8
	adds r2, r6, #0
	adds r2, #0x54
	adds r0, r4, #0
	movs r3, #8
	bl InitBody
	str r6, [r4, #0x2c]
	ldr r0, _08098914 @ =FUN_08099eb4
	str r0, [r4, #0x24]
	adds r7, r6, #0
	adds r7, #0xb8
	strb r5, [r7]
	adds r0, r6, #0
	adds r0, #0xbc
	str r5, [r0]
	ldrb r0, [r6, #0x10]
	cmp r0, #0
	bne _08098918
	movs r5, #1
	ldrb r0, [r6, #0xa]
	movs r1, #0x10
	orrs r0, r1
	strb r0, [r6, #0xa]
	subs r4, #0x28
	strb r5, [r4]
	adds r2, r6, #0
	adds r2, #0x4a
	movs r3, #0x10
	ldrb r1, [r2]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	orrs r0, r3
	strb r0, [r2]
	strb r5, [r7]
	adds r3, r2, #0
	b _0809893A
	.align 2, 0
_08098910: .4byte 0x0836A4D8
_08098914: .4byte FUN_08099eb4
_08098918:
	ldrb r1, [r6, #0xa]
	movs r0, #0xef
	ands r0, r1
	strb r0, [r6, #0xa]
	adds r3, r6, #0
	adds r3, #0x4c
	strb r5, [r3]
	adds r1, r6, #0
	adds r1, #0x4a
	ldrb r2, [r1]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	strb r0, [r1]
	strb r5, [r7]
	adds r4, r3, #0
	adds r3, r1, #0
_0809893A:
	ldrb r5, [r6, #0x11]
	cmp r5, #1
	bne _080989A4
	ldr r0, _08098968 @ =pZero2
	ldr r0, [r0]
	ldr r1, [r0, #0x54]
	ldr r0, [r6, #0x54]
	cmp r1, r0
	bge _0809896C
	movs r2, #0
	ldrb r1, [r6, #0xa]
	movs r0, #0xef
	ands r0, r1
	strb r0, [r6, #0xa]
	strb r2, [r4]
	ldrb r1, [r3]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r3]
	strb r2, [r7]
	b _08098986
	.align 2, 0
_08098968: .4byte pZero2
_0809896C:
	ldrb r1, [r6, #0xa]
	movs r0, #0x10
	orrs r0, r1
	strb r0, [r6, #0xa]
	strb r5, [r4]
	movs r2, #0x10
	ldrb r1, [r3]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	orrs r0, r2
	strb r0, [r3]
	strb r5, [r7]
_08098986:
	ldr r1, _080989A0 @ =gEnemyFnTable
	ldrb r0, [r6, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r6, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r6, #0x14]
	movs r0, #0
	strb r0, [r6, #0xd]
	b _080989BA
	.align 2, 0
_080989A0: .4byte gEnemyFnTable
_080989A4:
	ldr r1, _08098A00 @ =gEnemyFnTable
	ldrb r0, [r6, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r6, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r6, #0x14]
	movs r0, #0
	strb r1, [r6, #0xd]
_080989BA:
	strb r0, [r6, #0xe]
	strb r0, [r6, #0xf]
	movs r4, #0
	str r4, [r6, #0x60]
	str r4, [r6, #0x5c]
	adds r0, r6, #0
	adds r0, #0xbb
	strb r4, [r0]
	str r4, [r6, #0x5c]
	adds r0, r6, #0
	bl IsFrozen
	cmp r0, #0
	beq _080989E4
	ldr r1, _08098A04 @ =0x0000D503
	adds r0, r6, #0
	bl SetMotion
	adds r0, r6, #0
	bl UpdateMotionGraphic
_080989E4:
	adds r0, r6, #0
	adds r0, #0xc0
	strb r4, [r0]
	subs r0, #6
	strb r4, [r0]
	adds r0, r6, #0
	bl Cattatank_Update
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_08098A00: .4byte gEnemyFnTable
_08098A04: .4byte 0x0000D503

	thumb_func_start Cattatank_Update
Cattatank_Update: @ 0x08098A08
	push {r4, r5, r6, lr}
	adds r4, r0, #0
	adds r0, #0x8c
	ldr r0, [r0]
	movs r1, #0x80
	lsls r1, r1, #2
	ands r0, r1
	cmp r0, #0
	beq _08098A4C
	ldrb r0, [r4, #0xd]
	cmp r0, #6
	bne _08098A2A
	adds r0, r4, #0
	bl IsFrozen
	cmp r0, #0
	beq _08098AD0
_08098A2A:
	movs r0, #0
	strb r0, [r4, #0xf]
	ldr r1, _08098A48 @ =gEnemyFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r4, #0x14]
	adds r0, r4, #0
	bl Cattatank_Die
	b _08098B10
	.align 2, 0
_08098A48: .4byte gEnemyFnTable
_08098A4C:
	ldr r6, _08098ABC @ =gStageRun+232
	adds r5, r4, #0
	adds r5, #0x54
	adds r0, r6, #0
	adds r1, r5, #0
	bl CalcFromCamera
	movs r1, #0xc0
	lsls r1, r1, #6
	cmp r0, r1
	bls _08098AD0
	ldr r1, [r6, #0x3c]
	ldr r0, _08098AC0 @ =0x00004FFF
	adds r1, r1, r0
	ldr r0, [r4, #0x58]
	movs r2, #0x80
	lsls r2, r2, #6
	adds r0, r0, r2
	cmp r1, r0
	bge _08098AD0
	ldrb r0, [r4, #0x11]
	cmp r0, #1
	bne _08098AD0
	strb r0, [r4, #0xf]
	movs r0, #0x2a
	bl PlaySound
	movs r0, #1
	adds r1, r5, #0
	bl TryDropItem
	ldr r2, _08098AC4 @ =gMission
	ldrh r1, [r2, #0xc]
	ldr r0, _08098AC8 @ =0x0000270E
	cmp r1, r0
	bhi _08098A98
	adds r0, r1, #1
	strh r0, [r2, #0xc]
_08098A98:
	adds r0, r4, #0
	adds r1, r5, #0
	bl TryDropZakoDisk
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
	strb r0, [r4, #0xa]
	ldr r1, _08098ACC @ =gEnemyFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #4
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0x10]
	str r0, [r4, #0x14]
	b _08098B10
	.align 2, 0
_08098ABC: .4byte gStageRun+232
_08098AC0: .4byte 0x00004FFF
_08098AC4: .4byte gMission
_08098AC8: .4byte 0x0000270E
_08098ACC: .4byte gEnemyFnTable
_08098AD0:
	ldr r1, _08098B18 @ =0x0836A470
	ldrb r0, [r4, #0xd]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r1, [r0]
	adds r0, r4, #0
	bl _call_via_r1
	adds r0, r4, #0
	bl cattatank_08099e20
	ldrb r1, [r4, #0xd]
	subs r0, r1, #6
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #1
	bls _08098B00
	cmp r1, #9
	beq _08098B00
	adds r0, r4, #0
	bl IsFrozen
	cmp r0, #0
	bne _08098B10
_08098B00:
	ldr r0, _08098B1C @ =0x0836A498
	ldrb r1, [r4, #0xd]
	lsls r1, r1, #2
	adds r1, r1, r0
	ldr r1, [r1]
	adds r0, r4, #0
	bl _call_via_r1
_08098B10:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_08098B18: .4byte 0x0836A470
_08098B1C: .4byte 0x0836A498

	thumb_func_start Cattatank_Die
Cattatank_Die: @ 0x08098B20
	push {r4, r5, r6, r7, lr}
	mov r7, sl
	mov r6, sb
	mov r5, r8
	push {r5, r6, r7}
	sub sp, #0x20
	adds r6, r0, #0
	ldr r0, _08098B78 @ =gCurStory
	ldrb r1, [r0, #8]
	movs r0, #0x40
	ands r0, r1
	cmp r0, #0
	beq _08098B80
	ldrb r0, [r6, #0x11]
	cmp r0, #1
	beq _08098B80
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
	ldr r1, _08098B7C @ =gEnemyFnTable
	ldrb r0, [r6, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r6, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	b _0809906E
	.align 2, 0
_08098B78: .4byte gCurStory
_08098B7C: .4byte gEnemyFnTable
_08098B80:
	ldr r5, _08098C44 @ =gStageRun+232
	adds r4, r6, #0
	adds r4, #0x54
	adds r0, r5, #0
	adds r1, r4, #0
	bl CalcFromCamera
	movs r1, #0xc0
	lsls r1, r1, #6
	mov sb, r4
	cmp r0, r1
	bls _08098C78
	ldr r1, [r5, #0x3c]
	ldr r0, _08098C48 @ =0x00004FFF
	adds r1, r1, r0
	ldr r2, [r6, #0x58]
	movs r3, #0x80
	lsls r3, r3, #6
	mov sl, r3
	adds r0, r2, r3
	cmp r1, r0
	bge _08098C78
	ldr r0, [r6, #0x54]
	str r0, [sp]
	str r2, [sp, #4]
	movs r0, #1
	mov r1, sp
	bl CreateSmoke
	movs r0, #0x2a
	bl PlaySound
	movs r0, #1
	mov r1, sb
	bl TryDropItem
	ldrb r0, [r6, #0xf]
	cmp r0, #0
	beq _08098BD0
	b _08099040
_08098BD0:
	ldr r2, _08098C4C @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _08098C50 @ =0x000343FD
	muls r0, r1, r0
	ldr r1, _08098C54 @ =0x00269EC3
	adds r0, r0, r1
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r2]
	lsrs r7, r0, #0x11
	movs r0, #3
	ands r7, r0
	ldr r0, [r6, #0x54]
	str r0, [sp, #8]
	ldr r0, [r6, #0x58]
	add r5, sp, #8
	str r0, [r5, #4]
	movs r3, #0xb8
	adds r3, r3, r6
	mov r8, r3
	ldrb r1, [r3]
	ldr r2, _08098C58 @ =0x0000D50F
	adds r0, r5, #0
	adds r3, r7, #0
	bl FUN_080c7570
	mov r0, r8
	ldrb r1, [r0]
	ldr r4, _08098C5C @ =0x0000D50E
	adds r0, r5, #0
	adds r2, r4, #0
	adds r3, r7, #0
	bl FUN_080c7570
	mov r3, r8
	ldrb r1, [r3]
	ldr r2, _08098C60 @ =0x0000D510
	adds r0, r5, #0
	adds r3, r7, #0
	bl FUN_080c7570
	mov r0, r8
	ldrb r1, [r0]
	adds r0, r5, #0
	adds r2, r4, #0
	adds r3, r7, #0
	bl FUN_080c7570
	ldrb r1, [r6, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	bne _08098C68
	ldr r0, [r6, #0x54]
	ldr r1, _08098C64 @ =0xFFFFE000
	adds r0, r0, r1
	str r0, [sp, #8]
	b _08098FF0
	.align 2, 0
_08098C44: .4byte gStageRun+232
_08098C48: .4byte 0x00004FFF
_08098C4C: .4byte RNG_0202f388
_08098C50: .4byte 0x000343FD
_08098C54: .4byte 0x00269EC3
_08098C58: .4byte 0x0000D50F
_08098C5C: .4byte 0x0000D50E
_08098C60: .4byte 0x0000D510
_08098C64: .4byte 0xFFFFE000
_08098C68:
	ldr r0, [r6, #0x54]
	add r0, sl
	str r0, [sp, #8]
	ldr r0, [r6, #0x58]
	str r0, [r5, #4]
	mov r0, r8
	ldrb r1, [r0]
	b _08099036
_08098C78:
	ldrb r0, [r6, #0xe]
	cmp r0, #0xb
	bls _08098C80
	b _08099070
_08098C80:
	lsls r0, r0, #2
	ldr r1, _08098C8C @ =_08098C90
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_08098C8C: .4byte _08098C90
_08098C90: @ jump table
	.4byte _08098CC0 @ case 0
	.4byte _08098E24 @ case 1
	.4byte _08098D08 @ case 2
	.4byte _08098D1C @ case 3
	.4byte _08098E44 @ case 4
	.4byte _08099070 @ case 5
	.4byte _08099070 @ case 6
	.4byte _08099070 @ case 7
	.4byte _08099070 @ case 8
	.4byte _08099070 @ case 9
	.4byte _08098E24 @ case 10
	.4byte _08098F20 @ case 11
_08098CC0:
	ldr r1, _08098CE8 @ =0x0000D505
	adds r0, r6, #0
	bl SetMotion
	adds r1, r6, #0
	adds r1, #0x8c
	ldr r2, [r1]
	movs r0, #0x80
	lsls r0, r0, #2
	ands r0, r2
	adds r3, r1, #0
	cmp r0, #0
	beq _08098CEC
	movs r0, #0x80
	lsls r0, r0, #9
	ands r2, r0
	cmp r2, #0
	beq _08098CEC
	movs r0, #1
	b _08098CEE
	.align 2, 0
_08098CE8: .4byte 0x0000D505
_08098CEC:
	movs r0, #0xa
_08098CEE:
	strb r0, [r6, #0xe]
	movs r1, #0
	str r1, [r3]
	adds r0, r6, #0
	adds r0, #0x90
	str r1, [r0]
	adds r0, #4
	strb r1, [r0]
	ldrb r1, [r6, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r6, #0xa]
	b _08098E24
_08098D08:
	adds r0, r6, #0
	bl UpdateMotionGraphic
	adds r0, r6, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	beq _08098D1A
	b _08099070
_08098D1A:
	b _08098E24
_08098D1C:
	ldr r1, _08098D68 @ =0x0000D505
	adds r0, r6, #0
	bl SetMotion
	adds r0, r6, #0
	bl UpdateMotionGraphic
	movs r0, #0
	strb r0, [r6, #0x13]
	str r0, [r6, #0x60]
	ldr r0, [r6, #0x54]
	str r0, [sp]
	ldr r0, [r6, #0x58]
	str r0, [sp, #4]
	ldrb r0, [r6, #0xf]
	adds r7, r6, #0
	adds r7, #0xb8
	cmp r0, #0
	bne _08098D4A
	ldrb r1, [r7]
	mov r0, sp
	bl FUN_080c7518
_08098D4A:
	ldrb r0, [r7]
	cmp r0, #0
	bne _08098D70
	ldr r0, [sp]
	ldr r1, _08098D6C @ =0xFFFFF800
	adds r0, r0, r1
	str r0, [sp]
	ldr r0, [sp, #4]
	movs r3, #0x80
	lsls r3, r3, #4
	adds r0, r0, r3
	str r0, [sp, #4]
	movs r0, #0x80
	b _08098D84
	.align 2, 0
_08098D68: .4byte 0x0000D505
_08098D6C: .4byte 0xFFFFF800
_08098D70:
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
_08098D84:
	str r0, [r6, #0x5c]
	adds r0, r6, #0
	adds r0, #0xba
	ldrb r0, [r0]
	cmp r0, #0xff
	beq _08098DB0
	cmp r0, #0xfe
	bne _08098DA4
	movs r2, #0x80
	lsls r2, r2, #2
	movs r0, #0
	mov r1, sp
	movs r3, #0
	bl FUN_080b2b40
	b _08098DD2
_08098DA4:
	ldr r0, _08098DC0 @ =pZero2
	ldr r0, [r0]
	ldr r1, [r0, #0x54]
	ldr r0, [r6, #0x54]
	cmp r1, r0
	ble _08098DC4
_08098DB0:
	movs r2, #0x80
	lsls r2, r2, #2
	movs r0, #0
	mov r1, sp
	movs r3, #1
	bl FUN_080b2b40
	b _08098DD2
	.align 2, 0
_08098DC0: .4byte pZero2
_08098DC4:
	movs r2, #0x80
	lsls r2, r2, #2
	movs r0, #0
	mov r1, sp
	movs r3, #0
	bl FUN_080b2b40
_08098DD2:
	movs r0, #1
	mov r1, sb
	bl TryDropItem
	ldrb r0, [r6, #0xf]
	cmp r0, #0
	bne _08098E1C
	ldr r2, _08098E2C @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _08098E30 @ =0x000343FD
	adds r4, r1, #0
	muls r4, r0, r4
	ldr r0, _08098E34 @ =0x00269EC3
	adds r4, r4, r0
	lsls r4, r4, #1
	lsrs r0, r4, #1
	str r0, [r2]
	lsrs r4, r4, #0x11
	movs r0, #3
	ands r4, r0
	ldr r0, [r6, #0x54]
	str r0, [sp, #0x10]
	ldr r0, [r6, #0x58]
	add r5, sp, #0x10
	str r0, [r5, #4]
	ldrb r1, [r7]
	ldr r2, _08098E38 @ =0x0000D50F
	adds r0, r5, #0
	adds r3, r4, #0
	bl FUN_080c7570
	ldrb r1, [r7]
	ldr r2, _08098E3C @ =0x0000D510
	adds r0, r5, #0
	adds r3, r4, #0
	bl FUN_080c7570
_08098E1C:
	ldr r0, _08098E40 @ =0xFFFFFE00
	str r0, [r6, #0x60]
	movs r0, #0x1e
	strb r0, [r6, #0x12]
_08098E24:
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
	b _08099070
	.align 2, 0
_08098E2C: .4byte RNG_0202f388
_08098E30: .4byte 0x000343FD
_08098E34: .4byte 0x00269EC3
_08098E38: .4byte 0x0000D50F
_08098E3C: .4byte 0x0000D510
_08098E40: .4byte 0xFFFFFE00
_08098E44:
	adds r0, r6, #0
	bl UpdateMotionGraphic
	ldr r0, [r6, #0x60]
	adds r0, #0x20
	str r0, [r6, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _08098E5A
	str r1, [r6, #0x60]
_08098E5A:
	ldr r1, [r6, #0x58]
	ldr r0, [r6, #0x60]
	adds r1, r1, r0
	str r1, [r6, #0x58]
	ldr r2, [r6, #0x5c]
	rsbs r0, r2, #0
	lsls r0, r0, #2
	asrs r0, r0, #8
	adds r2, r2, r0
	str r2, [r6, #0x5c]
	ldr r0, [r6, #0x54]
	adds r0, r0, r2
	str r0, [r6, #0x54]
	bl FUN_080098a4
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _08098ED8
	ldr r0, [r6, #0x60]
	cmp r0, #0
	ble _08098ED8
	adds r0, r6, #0
	adds r0, #0xbc
	ldr r0, [r0]
	bl isKilled
	cmp r0, #0
	beq _08098ED8
	ldr r0, [r6, #0x54]
	str r0, [sp]
	ldr r0, [r6, #0x58]
	str r0, [sp, #4]
	movs r0, #2
	mov r1, sp
	bl CreateSmoke
	movs r0, #0x2a
	bl PlaySound
	ldr r2, _08098F14 @ =gMission
	ldrh r1, [r2, #0xc]
	ldr r0, _08098F18 @ =0x0000270E
	cmp r1, r0
	bhi _08098EB6
	adds r0, r1, #1
	strh r0, [r2, #0xc]
_08098EB6:
	adds r0, r6, #0
	mov r1, sb
	bl TryDropZakoDisk
	ldrb r1, [r6, #0xa]
	movs r0, #0xfe
	ands r0, r1
	strb r0, [r6, #0xa]
	ldr r1, _08098F1C @ =gEnemyFnTable
	ldrb r0, [r6, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #4
	str r1, [r6, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0x10]
	str r0, [r6, #0x14]
_08098ED8:
	ldrb r0, [r6, #0x12]
	cmp r0, #0
	beq _08098EEA
	subs r0, #1
	strb r0, [r6, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _08098EEA
	b _08099070
_08098EEA:
	adds r0, r6, #0
	adds r0, #0xbc
	ldr r0, [r0]
	bl isKilled
	cmp r0, #0
	bne _08098EFA
	b _08099070
_08098EFA:
	ldr r0, [r6, #0x54]
	str r0, [sp]
	ldr r0, [r6, #0x58]
	str r0, [sp, #4]
	movs r0, #2
	mov r1, sp
	bl CreateSmoke
	movs r0, #0x2a
	bl PlaySound
	b _08099040
	.align 2, 0
_08098F14: .4byte gMission
_08098F18: .4byte 0x0000270E
_08098F1C: .4byte gEnemyFnTable
_08098F20:
	ldr r0, [r6, #0x60]
	adds r0, #0x20
	str r0, [r6, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _08098F30
	str r1, [r6, #0x60]
_08098F30:
	ldr r0, [r6, #0x58]
	ldr r1, [r6, #0x60]
	adds r0, r0, r1
	str r0, [r6, #0x58]
	ldr r1, [r6, #0x5c]
	rsbs r0, r1, #0
	lsls r0, r0, #2
	asrs r0, r0, #8
	adds r1, r1, r0
	str r1, [r6, #0x5c]
	ldr r0, [r6, #0x54]
	adds r0, r0, r1
	str r0, [r6, #0x54]
	adds r0, r6, #0
	adds r0, #0xbc
	ldr r0, [r0]
	bl isKilled
	cmp r0, #0
	bne _08098F5A
	b _08099070
_08098F5A:
	ldr r0, [r6, #0x54]
	str r0, [sp]
	ldr r0, [r6, #0x58]
	str r0, [sp, #4]
	movs r0, #1
	mov r1, sp
	bl CreateSmoke
	movs r0, #0x2a
	bl PlaySound
	movs r0, #1
	mov r1, sb
	bl TryDropItem
	ldrb r0, [r6, #0xf]
	cmp r0, #0
	bne _08099040
	ldr r2, _08099004 @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _08099008 @ =0x000343FD
	muls r0, r1, r0
	ldr r1, _0809900C @ =0x00269EC3
	adds r0, r0, r1
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r2]
	lsrs r7, r0, #0x11
	movs r0, #3
	ands r7, r0
	ldr r0, [r6, #0x54]
	str r0, [sp, #0x18]
	ldr r0, [r6, #0x58]
	add r5, sp, #0x18
	str r0, [r5, #4]
	movs r3, #0xb8
	adds r3, r3, r6
	mov r8, r3
	ldrb r1, [r3]
	ldr r2, _08099010 @ =0x0000D50F
	adds r0, r5, #0
	adds r3, r7, #0
	bl FUN_080c7570
	mov r0, r8
	ldrb r1, [r0]
	ldr r4, _08099014 @ =0x0000D50E
	adds r0, r5, #0
	adds r2, r4, #0
	adds r3, r7, #0
	bl FUN_080c7570
	mov r3, r8
	ldrb r1, [r3]
	ldr r2, _08099018 @ =0x0000D510
	adds r0, r5, #0
	adds r3, r7, #0
	bl FUN_080c7570
	mov r0, r8
	ldrb r1, [r0]
	adds r0, r5, #0
	adds r2, r4, #0
	adds r3, r7, #0
	bl FUN_080c7570
	ldrb r1, [r6, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	bne _08099024
	ldr r0, [r6, #0x54]
	ldr r1, _0809901C @ =0xFFFFE000
	adds r0, r0, r1
	str r0, [sp, #0x18]
_08098FF0:
	ldr r0, [r6, #0x58]
	str r0, [r5, #4]
	mov r3, r8
	ldrb r1, [r3]
	ldr r2, _08099020 @ =0x0000D50D
	adds r0, r5, #0
	adds r3, r7, #0
	bl FUN_080c7570
	b _08099040
	.align 2, 0
_08099004: .4byte RNG_0202f388
_08099008: .4byte 0x000343FD
_0809900C: .4byte 0x00269EC3
_08099010: .4byte 0x0000D50F
_08099014: .4byte 0x0000D50E
_08099018: .4byte 0x0000D510
_0809901C: .4byte 0xFFFFE000
_08099020: .4byte 0x0000D50D
_08099024:
	ldr r0, [r6, #0x54]
	movs r1, #0x80
	lsls r1, r1, #6
	adds r0, r0, r1
	str r0, [sp, #0x18]
	ldr r0, [r6, #0x58]
	str r0, [r5, #4]
	mov r3, r8
	ldrb r1, [r3]
_08099036:
	ldr r2, _08099080 @ =0x0000D50D
	adds r0, r5, #0
	adds r3, r7, #0
	bl FUN_080c7570
_08099040:
	ldr r2, _08099084 @ =gMission
	ldrh r1, [r2, #0xc]
	ldr r0, _08099088 @ =0x0000270E
	cmp r1, r0
	bhi _0809904E
	adds r0, r1, #1
	strh r0, [r2, #0xc]
_0809904E:
	adds r0, r6, #0
	mov r1, sb
	bl TryDropZakoDisk
	ldrb r1, [r6, #0xa]
	movs r0, #0xfe
	ands r0, r1
	strb r0, [r6, #0xa]
	ldr r1, _0809908C @ =gEnemyFnTable
	ldrb r0, [r6, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #4
	str r1, [r6, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0x10]
_0809906E:
	str r0, [r6, #0x14]
_08099070:
	add sp, #0x20
	pop {r3, r4, r5}
	mov r8, r3
	mov sb, r4
	mov sl, r5
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_08099080: .4byte 0x0000D50D
_08099084: .4byte gMission
_08099088: .4byte 0x0000270E
_0809908C: .4byte gEnemyFnTable
