	.include "asm/macros.inc"

	.syntax unified
	
	.text


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
