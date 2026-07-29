	.include "asm/macros.inc"

	.syntax unified

	.text


	thumb_func_start hanu_0805bdc0
hanu_0805bdc0: @ 0x0805BDC0
	push {r4, r5, r6, lr}
	adds r5, r0, #0
	bl UpdateMotionGraphic
	adds r4, r5, #0
	adds r4, #0xb4
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x58]
	bl FUN_0800a31c
	ldr r1, [r4]
	cmp r1, r0
	bne _0805BDEA
	adds r4, #4
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x58]
	bl FUN_0800a22c
	ldr r1, [r4]
	cmp r1, r0
	beq _0805BDF6
_0805BDEA:
	movs r1, #0
	movs r0, #0xd
	strb r0, [r5, #0xd]
	strb r1, [r5, #0xf]
	strb r1, [r5, #0xe]
	b _0805BF0A
_0805BDF6:
	adds r1, r5, #0
	adds r1, #0xbd
	ldrb r2, [r1]
	movs r0, #1
	ands r0, r2
	adds r4, r1, #0
	cmp r0, #0
	beq _0805BE68
	ldr r0, _0805BE2C @ =gMission
	ldr r1, [r0]
	ldrb r1, [r1, #1]
	adds r6, r0, #0
	cmp r1, #4
	bls _0805BE3C
	ldr r2, _0805BE30 @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _0805BE34 @ =0x000343FD
	muls r0, r1, r0
	ldr r1, _0805BE38 @ =0x00269EC3
	adds r0, r0, r1
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r2]
	lsrs r1, r0, #0x11
	movs r0, #7
	ands r1, r0
	b _0805BE6E
	.align 2, 0
_0805BE2C: .4byte gMission
_0805BE30: .4byte RNG_0202f388
_0805BE34: .4byte 0x000343FD
_0805BE38: .4byte 0x00269EC3
_0805BE3C:
	ldr r2, _0805BE5C @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _0805BE60 @ =0x000343FD
	muls r0, r1, r0
	ldr r1, _0805BE64 @ =0x00269EC3
	adds r0, r0, r1
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r2]
	lsrs r0, r0, #0x11
	movs r1, #7
	bl __umodsi3
	lsls r0, r0, #0x18
	lsrs r1, r0, #0x18
	b _0805BE6E
	.align 2, 0
_0805BE5C: .4byte RNG_0202f388
_0805BE60: .4byte 0x000343FD
_0805BE64: .4byte 0x00269EC3
_0805BE68:
	lsls r0, r2, #0x18
	lsrs r1, r0, #0x19
	ldr r6, _0805BE7C @ =gMission
_0805BE6E:
	cmp r1, #7
	bhi _0805BEDE
	lsls r0, r1, #2
	ldr r1, _0805BE80 @ =_0805BE84
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_0805BE7C: .4byte gMission
_0805BE80: .4byte _0805BE84
_0805BE84: @ jump table
	.4byte _0805BEA4 @ case 0
	.4byte _0805BEAE @ case 1
	.4byte _0805BEB2 @ case 2
	.4byte _0805BEB6 @ case 3
	.4byte _0805BEC8 @ case 4
	.4byte _0805BED2 @ case 5
	.4byte _0805BED6 @ case 6
	.4byte _0805BEDA @ case 7
_0805BEA4:
	movs r0, #0xd
	strb r0, [r5, #0xd]
	movs r0, #1
	strb r0, [r5, #0xf]
	b _0805BEDE
_0805BEAE:
	movs r0, #8
	b _0805BEDC
_0805BEB2:
	movs r0, #0xa
	b _0805BEDC
_0805BEB6:
	adds r0, r5, #0
	adds r0, #0xbe
	ldrb r0, [r0]
	cmp r0, #0
	beq _0805BEC4
	movs r0, #0x16
	b _0805BEDC
_0805BEC4:
	movs r0, #4
	b _0805BEDC
_0805BEC8:
	movs r1, #0
	movs r0, #0xd
	strb r0, [r5, #0xd]
	strb r1, [r5, #0xf]
	b _0805BEDE
_0805BED2:
	movs r0, #0x16
	b _0805BEDC
_0805BED6:
	movs r0, #0x19
	b _0805BEDC
_0805BEDA:
	movs r0, #0x13
_0805BEDC:
	strb r0, [r5, #0xd]
_0805BEDE:
	adds r2, r4, #0
	ldrb r0, [r2]
	adds r1, r0, #1
	movs r3, #0
	strb r1, [r2]
	ldr r0, [r6]
	ldrb r0, [r0, #1]
	cmp r0, #4
	bls _0805BEFC
	lsls r0, r1, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0xf
	bls _0805BF06
	strb r3, [r2]
	b _0805BF06
_0805BEFC:
	lsls r0, r1, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0xd
	bls _0805BF06
	strb r3, [r4]
_0805BF06:
	movs r0, #0
	strb r0, [r5, #0xe]
_0805BF0A:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
