	.include "asm/macros.inc"

	.syntax unified
	
	.text


	thumb_func_start deathtanzMode8
deathtanzMode8: @ 0x08049C54
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r5, [r4, #0xe]
	cmp r5, #1
	beq _08049CB4
	cmp r5, #1
	bgt _08049C68
	cmp r5, #0
	beq _08049C72
	b _08049D2C
_08049C68:
	cmp r5, #2
	beq _08049CFC
	cmp r5, #3
	beq _08049D14
	b _08049D2C
_08049C72:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _08049CEC @ =sCollisions+(24*15)
	bl SetDDP
	ldr r0, _08049CF0 @ =0xFFFFD000
	str r0, [r4, #0x5c]
	ldr r0, _08049CF4 @ =0x00000666
	bl Sqrt
	adds r1, r0, #0
	lsls r1, r1, #0x10
	lsrs r1, r1, #0x10
	ldr r0, [r4, #0x5c]
	bl __divsi3
	adds r2, r0, #0
	str r2, [r4, #0x5c]
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _08049CA4
	rsbs r0, r2, #0
	str r0, [r4, #0x5c]
_08049CA4:
	str r5, [r4, #0x60]
	ldr r1, _08049CF8 @ =0x0000A70B
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08049CB4:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	ldr r0, [r4, #0x60]
	adds r0, #0x19
	str r0, [r4, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _08049CCC
	str r1, [r4, #0x60]
_08049CCC:
	ldr r1, [r4, #0x58]
	ldr r0, [r4, #0x60]
	adds r1, r1, r0
	str r1, [r4, #0x58]
	adds r0, r4, #0
	adds r0, #0xb8
	ldr r0, [r0]
	cmp r1, r0
	ble _08049CE4
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08049CE4:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	b _08049D2C
	.align 2, 0
_08049CEC: .4byte sCollisions+(24*15)
_08049CF0: .4byte 0xFFFFD000
_08049CF4: .4byte 0x00000666
_08049CF8: .4byte 0x0000A70B
_08049CFC:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _08049D34 @ =sCollisions+(24*9)
	bl SetDDP
	ldr r1, _08049D38 @ =0x0000A709
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08049D14:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _08049D2C
	movs r1, #0
	movs r0, #1
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_08049D2C:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_08049D34: .4byte sCollisions+(24*9)
_08049D38: .4byte 0x0000A709

	thumb_func_start deathtanzMode9
deathtanzMode9: @ 0x08049D3C
	push {r4, r5, r6, lr}
	adds r5, r0, #0
	ldrb r4, [r5, #0xe]
	cmp r4, #1
	beq _08049E00
	cmp r4, #1
	bgt _08049D50
	cmp r4, #0
	beq _08049D5C
	b _08049ED6
_08049D50:
	cmp r4, #2
	beq _08049E48
	cmp r4, #3
	bne _08049D5A
	b _08049EBE
_08049D5A:
	b _08049ED6
_08049D5C:
	adds r0, r5, #0
	adds r0, #0x74
	ldr r1, _08049D9C @ =sCollisions+(24*12)
	bl SetDDP
	adds r0, r5, #0
	adds r0, #0xbf
	strb r4, [r0]
	adds r3, r5, #0
	adds r3, #0xb4
	ldr r1, [r5, #0x54]
	ldr r0, [r3]
	cmp r1, r0
	bge _08049DA0
	adds r1, r5, #0
	adds r1, #0x4c
	movs r0, #1
	strb r0, [r1]
	adds r2, r5, #0
	adds r2, #0x4a
	ldrb r0, [r2]
	movs r1, #0x10
	orrs r0, r1
	strb r0, [r2]
	ldrb r0, [r5, #0xa]
	orrs r0, r1
	strb r0, [r5, #0xa]
	ldr r0, [r3]
	movs r1, #0xa8
	lsls r1, r1, #7
	b _08049DC0
	.align 2, 0
_08049D9C: .4byte sCollisions+(24*12)
_08049DA0:
	adds r0, r5, #0
	adds r0, #0x4c
	strb r4, [r0]
	adds r2, r5, #0
	adds r2, #0x4a
	ldrb r1, [r2]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r2]
	ldrb r1, [r5, #0xa]
	movs r0, #0xef
	ands r0, r1
	strb r0, [r5, #0xa]
	ldr r0, [r3]
	ldr r1, _08049E3C @ =0xFFFFAC00
_08049DC0:
	adds r6, r0, r1
	str r6, [r5, #0x64]
	ldr r4, _08049E40 @ =0x00000851
	adds r0, r4, #0
	bl Sqrt
	adds r0, #0x10
	strb r0, [r5, #0x12]
	ldr r0, [r5, #0x54]
	subs r0, r6, r0
	ldrb r1, [r5, #0x12]
	bl __divsi3
	str r0, [r5, #0x5c]
	adds r0, r4, #0
	bl Sqrt
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	lsls r1, r0, #1
	adds r1, r1, r0
	lsls r1, r1, #3
	adds r1, r1, r0
	rsbs r1, r1, #0
	str r1, [r5, #0x60]
	ldr r1, _08049E44 @ =0x0000A70A
	adds r0, r5, #0
	bl SetMotion
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_08049E00:
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x5c]
	adds r0, r0, r1
	str r0, [r5, #0x54]
	ldr r0, [r5, #0x60]
	adds r0, #0x19
	str r0, [r5, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _08049E18
	str r1, [r5, #0x60]
_08049E18:
	ldr r0, [r5, #0x58]
	ldr r1, [r5, #0x60]
	adds r0, r0, r1
	str r0, [r5, #0x58]
	adds r0, r5, #0
	bl UpdateMotionGraphic
	ldrb r0, [r5, #0x12]
	subs r0, #1
	strb r0, [r5, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _08049ED6
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
	b _08049ED6
	.align 2, 0
_08049E3C: .4byte 0xFFFFAC00
_08049E40: .4byte 0x00000851
_08049E44: .4byte 0x0000A70A
_08049E48:
	adds r0, r5, #0
	adds r0, #0x74
	ldr r1, _08049E88 @ =sCollisions+(24*35)
	bl SetDDP
	ldrb r0, [r5, #0xa]
	lsrs r0, r0, #4
	movs r2, #1
	eors r0, r2
	ands r0, r2
	adds r1, r5, #0
	adds r1, #0x4c
	strb r0, [r1]
	ldrb r1, [r5, #0xa]
	lsrs r1, r1, #4
	eors r1, r2
	ands r1, r2
	adds r4, r5, #0
	adds r4, #0x4a
	lsls r3, r1, #4
	ldrb r2, [r4]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r3
	strb r0, [r4]
	cmp r1, #0
	beq _08049E8C
	ldrb r0, [r5, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _08049E92
	.align 2, 0
_08049E88: .4byte sCollisions+(24*35)
_08049E8C:
	ldrb r1, [r5, #0xa]
	movs r0, #0xef
	ands r0, r1
_08049E92:
	strb r0, [r5, #0xa]
	adds r0, r5, #0
	adds r0, #0xb4
	ldr r1, [r5, #0x54]
	ldr r0, [r0]
	cmp r1, r0
	bge _08049EA8
	ldr r1, _08049EA4 @ =0xFFFFAC00
	b _08049EAC
	.align 2, 0
_08049EA4: .4byte 0xFFFFAC00
_08049EA8:
	movs r1, #0xa8
	lsls r1, r1, #7
_08049EAC:
	adds r0, r0, r1
	str r0, [r5, #0x54]
	ldr r1, _08049EDC @ =0x0000A70C
	adds r0, r5, #0
	bl SetMotion
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_08049EBE:
	adds r0, r5, #0
	bl UpdateMotionGraphic
	adds r0, r5, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _08049ED6
	movs r1, #0
	movs r0, #0xa
	strb r0, [r5, #0xd]
	strb r1, [r5, #0xe]
_08049ED6:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_08049EDC: .4byte 0x0000A70C

	thumb_func_start deathtanzMode10
deathtanzMode10: @ 0x08049EE0
	push {r4, r5, r6, lr}
	adds r5, r0, #0
	ldrb r0, [r5, #0xe]
	cmp r0, #5
	bls _08049EEC
	b _0804A0A2
_08049EEC:
	lsls r0, r0, #2
	ldr r1, _08049EF8 @ =_08049EFC
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_08049EF8: .4byte _08049EFC
_08049EFC: @ jump table
	.4byte _08049F14 @ case 0
	.4byte _08049FA2 @ case 1
	.4byte _08049FDC @ case 2
	.4byte _08049FEE @ case 3
	.4byte _0804A05C @ case 4
	.4byte _0804A074 @ case 5
_08049F14:
	movs r0, #0x5d
	bl PlaySound
	adds r0, r5, #0
	adds r0, #0x74
	ldr r1, _08049FD0 @ =sCollisions+(24*15)
	bl SetDDP
	adds r0, r5, #0
	adds r0, #0xb4
	ldr r3, [r0]
	ldr r1, _08049FD4 @ =0xFFFFEC00
	adds r0, r3, r1
	str r0, [r5, #0x5c]
	adds r2, r0, #0
	ldrb r1, [r5, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _08049F42
	movs r0, #0xa0
	lsls r0, r0, #5
	adds r2, r3, r0
_08049F42:
	ldr r1, [r5, #0x54]
	subs r1, r2, r1
	str r1, [r5, #0x5c]
	adds r0, r5, #0
	adds r0, #0xb8
	ldr r0, [r0]
	ldr r2, [r5, #0x58]
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
	lsls r4, r4, #3
	str r4, [r5, #0x5c]
	lsls r0, r0, #3
	str r0, [r5, #0x60]
	adds r0, r6, #0
	asrs r0, r0, #0xb
	strb r0, [r5, #0x12]
	ldr r1, _08049FD8 @ =0x0000A70B
	adds r0, r5, #0
	bl SetMotion
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_08049FA2:
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x5c]
	adds r0, r0, r1
	str r0, [r5, #0x54]
	ldr r0, [r5, #0x58]
	ldr r1, [r5, #0x60]
	adds r0, r0, r1
	str r0, [r5, #0x58]
	ldrb r0, [r5, #0x12]
	subs r0, #1
	strb r0, [r5, #0x12]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0x17
	bhi _08049FC6
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_08049FC6:
	adds r0, r5, #0
	bl UpdateMotionGraphic
	b _0804A0A2
	.align 2, 0
_08049FD0: .4byte sCollisions+(24*15)
_08049FD4: .4byte 0xFFFFEC00
_08049FD8: .4byte 0x0000A70B
_08049FDC:
	movs r0, #0
	strb r0, [r5, #0x12]
	ldr r1, _0804A050 @ =0x0000A726
	adds r0, r5, #0
	bl SetMotion
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_08049FEE:
	ldrb r0, [r5, #0x12]
	cmp r0, #0
	bne _0804A014
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x5c]
	adds r0, r0, r1
	str r0, [r5, #0x54]
	ldr r1, [r5, #0x58]
	ldr r0, [r5, #0x60]
	adds r1, r1, r0
	str r1, [r5, #0x58]
	adds r0, r5, #0
	adds r0, #0xb8
	ldr r0, [r0]
	cmp r1, r0
	ble _0804A014
	str r0, [r5, #0x58]
	movs r0, #1
	strb r0, [r5, #0x12]
_0804A014:
	adds r0, r5, #0
	bl UpdateMotionGraphic
	adds r0, r5, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _0804A02A
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_0804A02A:
	adds r0, r5, #0
	adds r0, #0x74
	ldr r2, _0804A054 @ =0x08362EB6
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
	ldr r2, _0804A058 @ =sCollisions
	adds r1, r1, r2
	bl SetDDP
	b _0804A0A2
	.align 2, 0
_0804A050: .4byte 0x0000A726
_0804A054: .4byte sPostures
_0804A058: .4byte sCollisions
_0804A05C:
	adds r0, r5, #0
	adds r0, #0x74
	ldr r1, _0804A094 @ =sCollisions+(24*7)
	bl SetDDP
	ldr r1, _0804A098 @ =0x0000A708
	adds r0, r5, #0
	bl SetMotion
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_0804A074:
	adds r0, r5, #0
	bl UpdateMotionGraphic
	adds r0, r5, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _0804A0A2
	adds r0, r5, #0
	adds r0, #0xbf
	ldrb r1, [r0]
	cmp r1, #0
	beq _0804A09C
	movs r1, #0
	movs r0, #5
	b _0804A09E
	.align 2, 0
_0804A094: .4byte sCollisions+(24*7)
_0804A098: .4byte 0x0000A708
_0804A09C:
	movs r0, #0xb
_0804A09E:
	strb r0, [r5, #0xd]
	strb r1, [r5, #0xe]
_0804A0A2:
	pop {r4, r5, r6}
	pop {r0}
	bx r0

	thumb_func_start deathtanzMode11
deathtanzMode11: @ 0x0804A0A8
	push {r4, r5, r6, lr}
	adds r5, r0, #0
	ldrb r0, [r5, #0xe]
	cmp r0, #1
	beq _0804A154
	cmp r0, #1
	bgt _0804A0BC
	cmp r0, #0
	beq _0804A0C8
	b _0804A22A
_0804A0BC:
	cmp r0, #2
	beq _0804A190
	cmp r0, #3
	bne _0804A0C6
	b _0804A20A
_0804A0C6:
	b _0804A22A
_0804A0C8:
	adds r0, r5, #0
	adds r0, #0x74
	ldr r1, _0804A180 @ =sCollisions+(24*12)
	bl SetDDP
	adds r0, r5, #0
	adds r0, #0xb4
	ldr r3, [r0]
	ldr r1, _0804A184 @ =0xFFFFAC00
	adds r0, r3, r1
	str r0, [r5, #0x5c]
	adds r2, r0, #0
	ldrb r1, [r5, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _0804A0F0
	movs r0, #0xa8
	lsls r0, r0, #7
	adds r2, r3, r0
_0804A0F0:
	ldr r1, [r5, #0x54]
	subs r1, r2, r1
	str r1, [r5, #0x5c]
	adds r0, r5, #0
	adds r0, #0xb8
	ldr r0, [r0]
	ldr r2, _0804A188 @ =0xFFFF9800
	adds r0, r0, r2
	ldr r2, [r5, #0x58]
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
	lsls r4, r4, #3
	str r4, [r5, #0x5c]
	lsls r0, r0, #3
	str r0, [r5, #0x60]
	adds r0, r6, #0
	asrs r0, r0, #0xb
	strb r0, [r5, #0x12]
	ldr r1, _0804A18C @ =0x0000A70A
	adds r0, r5, #0
	bl SetMotion
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_0804A154:
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x5c]
	adds r0, r0, r1
	str r0, [r5, #0x54]
	ldr r0, [r5, #0x58]
	ldr r1, [r5, #0x60]
	adds r0, r0, r1
	str r0, [r5, #0x58]
	ldrb r0, [r5, #0x12]
	subs r0, #1
	strb r0, [r5, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _0804A176
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_0804A176:
	adds r0, r5, #0
	bl UpdateMotionGraphic
	b _0804A22A
	.align 2, 0
_0804A180: .4byte sCollisions+(24*12)
_0804A184: .4byte 0xFFFFAC00
_0804A188: .4byte 0xFFFF9800
_0804A18C: .4byte 0x0000A70A
_0804A190:
	adds r0, r5, #0
	adds r0, #0x74
	ldr r1, _0804A1D0 @ =sCollisions+(24*35)
	bl SetDDP
	ldrb r0, [r5, #0xa]
	lsrs r0, r0, #4
	movs r2, #1
	eors r0, r2
	ands r0, r2
	adds r1, r5, #0
	adds r1, #0x4c
	strb r0, [r1]
	ldrb r1, [r5, #0xa]
	lsrs r1, r1, #4
	eors r1, r2
	ands r1, r2
	adds r4, r5, #0
	adds r4, #0x4a
	lsls r3, r1, #4
	ldrb r2, [r4]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r3
	strb r0, [r4]
	cmp r1, #0
	beq _0804A1D4
	ldrb r0, [r5, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _0804A1DA
	.align 2, 0
_0804A1D0: .4byte sCollisions+(24*35)
_0804A1D4:
	ldrb r1, [r5, #0xa]
	movs r0, #0xef
	ands r0, r1
_0804A1DA:
	strb r0, [r5, #0xa]
	adds r0, r5, #0
	adds r0, #0xb4
	ldr r1, [r5, #0x54]
	ldr r0, [r0]
	cmp r1, r0
	bge _0804A1F4
	ldr r1, _0804A1F0 @ =0xFFFFAC00
	adds r0, r0, r1
	b _0804A1FA
	.align 2, 0
_0804A1F0: .4byte 0xFFFFAC00
_0804A1F4:
	movs r2, #0xa8
	lsls r2, r2, #7
	adds r0, r0, r2
_0804A1FA:
	str r0, [r5, #0x54]
	ldr r1, _0804A230 @ =0x0000A70C
	adds r0, r5, #0
	bl SetMotion
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_0804A20A:
	adds r0, r5, #0
	bl UpdateMotionGraphic
	adds r0, r5, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _0804A22A
	adds r2, r5, #0
	adds r2, #0xbf
	movs r0, #0
	movs r1, #1
	strb r1, [r2]
	movs r1, #0xa
	strb r1, [r5, #0xd]
	strb r0, [r5, #0xe]
_0804A22A:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_0804A230: .4byte 0x0000A70C

	thumb_func_start deathtanzMode12
deathtanzMode12: @ 0x0804A234
	push {r4, r5, r6, lr}
	sub sp, #4
	adds r4, r0, #0
	ldrb r5, [r4, #0xe]
	cmp r5, #1
	beq _0804A29A
	cmp r5, #1
	bgt _0804A24A
	cmp r5, #0
	beq _0804A254
	b _0804A35E
_0804A24A:
	cmp r5, #2
	beq _0804A314
	cmp r5, #3
	beq _0804A344
	b _0804A35E
_0804A254:
	adds r1, r4, #0
	adds r1, #0xb4
	ldr r0, [r4, #0x54]
	ldr r1, [r1]
	subs r0, r0, r1
	movs r1, #0xc8
	lsls r1, r1, #6
	adds r0, r0, r1
	movs r1, #0xc8
	lsls r1, r1, #7
	cmp r0, r1
	bls _0804A27A
	movs r0, #2
	strb r0, [r4, #0xd]
	strb r5, [r4, #0xe]
	adds r0, r4, #0
	bl UpdateMotionGraphic
	b _0804A35E
_0804A27A:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _0804A304 @ =sCollisions+(24*60)
	bl SetDDP
	adds r0, r4, #0
	adds r0, #0xbe
	strb r5, [r0]
	ldr r1, _0804A308 @ =0x0000A70D
	adds r0, r4, #0
	bl SetMotion
	strb r5, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0804A29A:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x71
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	cmp r0, #6
	bne _0804A2F2
	ldrb r5, [r4, #0x12]
	cmp r5, #0
	bne _0804A2F2
	movs r6, #1
	strb r6, [r4, #0x12]
	movs r0, #0x5d
	bl PlaySound
	ldr r2, [r4, #0x54]
	ldr r0, _0804A30C @ =0xFFFFC900
	adds r1, r2, r0
	ldrb r3, [r4, #0xa]
	movs r0, #0x10
	ands r0, r3
	cmp r0, #0
	beq _0804A2D4
	movs r0, #0xdc
	lsls r0, r0, #6
	adds r1, r2, r0
_0804A2D4:
	ldr r2, [r4, #0x58]
	ldr r0, _0804A310 @ =0xFFFFCE00
	adds r2, r2, r0
	lsrs r3, r3, #4
	ands r3, r6
	str r5, [sp]
	adds r0, r4, #0
	bl deathtanz_080a0934
	adds r2, r4, #0
	adds r2, #0xc1
	ldrb r1, [r2]
	movs r0, #0xfd
	ands r0, r1
	strb r0, [r2]
_0804A2F2:
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _0804A35E
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
	b _0804A35E
	.align 2, 0
_0804A304: .4byte sCollisions+(24*60)
_0804A308: .4byte 0x0000A70D
_0804A30C: .4byte 0xFFFFC900
_0804A310: .4byte 0xFFFFCE00
_0804A314:
	ldr r2, _0804A368 @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _0804A36C @ =0x000343FD
	muls r1, r0, r1
	ldr r0, _0804A370 @ =0x00269EC3
	adds r1, r1, r0
	lsls r1, r1, #1
	lsrs r0, r1, #1
	str r0, [r2]
	lsrs r1, r1, #0x11
	movs r0, #1
	ands r1, r0
	lsls r0, r1, #3
	adds r0, r0, r1
	lsls r0, r0, #1
	adds r0, #0x3c
	strb r0, [r4, #0x12]
	ldr r1, _0804A374 @ =0x0000A70E
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0804A344:
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	lsrs r1, r0, #0x18
	cmp r1, #0
	bne _0804A358
	movs r0, #0xd
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_0804A358:
	adds r0, r4, #0
	bl UpdateMotionGraphic
_0804A35E:
	add sp, #4
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_0804A368: .4byte RNG_0202f388
_0804A36C: .4byte 0x000343FD
_0804A370: .4byte 0x00269EC3
_0804A374: .4byte 0x0000A70E

	thumb_func_start deathtanzMode13
deathtanzMode13: @ 0x0804A378
	push {r4, r5, lr}
	sub sp, #4
	adds r4, r0, #0
	ldrb r5, [r4, #0xe]
	cmp r5, #1
	beq _0804A3A8
	cmp r5, #1
	bgt _0804A38E
	cmp r5, #0
	beq _0804A398
	b _0804A446
_0804A38E:
	cmp r5, #2
	beq _0804A420
	cmp r5, #3
	beq _0804A42E
	b _0804A446
_0804A398:
	ldr r1, _0804A414 @ =0x0000A70F
	adds r0, r4, #0
	bl SetMotion
	strb r5, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0804A3A8:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x71
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	cmp r0, #5
	bne _0804A400
	ldrb r0, [r4, #0x12]
	cmp r0, #0
	bne _0804A400
	movs r5, #1
	strb r5, [r4, #0x12]
	movs r0, #0x5d
	bl PlaySound
	ldr r2, [r4, #0x54]
	ldr r0, _0804A418 @ =0xFFFFC900
	adds r1, r2, r0
	ldrb r3, [r4, #0xa]
	movs r0, #0x10
	ands r0, r3
	cmp r0, #0
	beq _0804A3E2
	movs r0, #0xdc
	lsls r0, r0, #6
	adds r1, r2, r0
_0804A3E2:
	ldr r2, [r4, #0x58]
	ldr r0, _0804A41C @ =0xFFFFCE00
	adds r2, r2, r0
	lsrs r3, r3, #4
	ands r3, r5
	str r5, [sp]
	adds r0, r4, #0
	bl deathtanz_080a0934
	adds r2, r4, #0
	adds r2, #0xc1
	ldrb r1, [r2]
	movs r0, #0xfe
	ands r0, r1
	strb r0, [r2]
_0804A400:
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _0804A446
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
	b _0804A446
	.align 2, 0
_0804A414: .4byte 0x0000A70F
_0804A418: .4byte 0xFFFFC900
_0804A41C: .4byte 0xFFFFCE00
_0804A420:
	ldr r1, _0804A450 @ =0x0000A710
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0804A42E:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0xbe
	ldrb r0, [r0]
	cmp r0, #0
	beq _0804A446
	movs r1, #0
	movs r0, #0xe
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_0804A446:
	add sp, #4
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_0804A450: .4byte 0x0000A710

	thumb_func_start deathtanzMode14
deathtanzMode14: @ 0x0804A454
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #5
	bhi _0804A530
	lsls r0, r0, #2
	ldr r1, _0804A468 @ =_0804A46C
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_0804A468: .4byte _0804A46C
_0804A46C: @ jump table
	.4byte _0804A484 @ case 0
	.4byte _0804A4A6 @ case 1
	.4byte _0804A4BC @ case 2
	.4byte _0804A4D4 @ case 3
	.4byte _0804A4F4 @ case 4
	.4byte _0804A518 @ case 5
_0804A484:
	adds r3, r4, #0
	adds r3, #0xc1
	ldrb r1, [r3]
	movs r0, #2
	movs r2, #0
	orrs r0, r1
	strb r0, [r3]
	adds r0, r4, #0
	adds r0, #0xbe
	strb r2, [r0]
	ldr r1, _0804A4B8 @ =0x0000A711
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0804A4A6:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _0804A530
	b _0804A4E4
	.align 2, 0
_0804A4B8: .4byte 0x0000A711
_0804A4BC:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _0804A4EC @ =0x08362DAC
	bl SetDDP
	ldr r1, _0804A4F0 @ =0x0000A713
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0804A4D4:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0xbe
	ldrb r0, [r0]
	cmp r0, #0
	beq _0804A530
_0804A4E4:
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
	b _0804A530
	.align 2, 0
_0804A4EC: .4byte sCollisions+(24*62)
_0804A4F0: .4byte 0x0000A713
_0804A4F4:
	adds r2, r4, #0
	adds r2, #0xc1
	ldrb r1, [r2]
	movs r0, #1
	orrs r0, r1
	strb r0, [r2]
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _0804A538 @ =sCollisions+(24*60)
	bl SetDDP
	ldr r1, _0804A53C @ =0x0000A715
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0804A518:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _0804A530
	movs r1, #0
	movs r0, #5
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_0804A530:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_0804A538: .4byte sCollisions+(24*60)
_0804A53C: .4byte 0x0000A715

	thumb_func_start deathtanzMode15
deathtanzMode15: @ 0x0804A540
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r5, [r4, #0xe]
	cmp r5, #0
	beq _0804A550
	cmp r5, #1
	beq _0804A574
	b _0804A58C
_0804A550:
	movs r0, #0x5c
	bl PlaySound
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _0804A594 @ =sCollisions+(24*1)
	bl SetDDP
	adds r0, r4, #0
	adds r0, #0xbe
	strb r5, [r0]
	ldr r1, _0804A598 @ =0x0000A716
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0804A574:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _0804A58C
	movs r1, #0
	movs r0, #0x10
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_0804A58C:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_0804A594: .4byte sCollisions+(24*1)
_0804A598: .4byte 0x0000A716
