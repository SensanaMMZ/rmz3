	push {r4, r5, lr}
	sub sp, #8
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _08097F50
	cmp r0, #1
	bne _08097F4E
	b _0809805E
_08097F4E:
	b _080980FA
_08097F50:
	adds r0, r4, #0
	adds r0, #0xbe
	ldrb r0, [r0]
	cmp r0, #2
	beq _08097F8C
	cmp r0, #2
	bgt _08097F64
	cmp r0, #1
	beq _08097F6E
	b _08098038
_08097F64:
	cmp r0, #3
	beq _08097FB0
	cmp r0, #4
	beq _08097FE4
	b _08098038
_08097F6E:
	ldr r3, [r4, #0x58]
	ldr r1, _08097F88 @ =0xFFFFEE00
	adds r0, r3, r1
	str r0, [r4, #0x58]
	adds r2, r0, #0
	ldrb r1, [r4, #0xa]
	movs r0, #0x20
	ands r0, r1
	cmp r0, #0
	beq _08097FA6
	movs r0, #0x90
	lsls r0, r0, #5
	b _08097FA4
	.align 2, 0
_08097F88: .4byte 0xFFFFEE00
_08097F8C:
	ldr r3, [r4, #0x58]
	ldr r1, _08097FAC @ =0xFFFFE800
	adds r0, r3, r1
	str r0, [r4, #0x58]
	adds r2, r0, #0
	ldrb r1, [r4, #0xa]
	movs r0, #0x20
	ands r0, r1
	cmp r0, #0
	beq _08097FA6
	movs r0, #0xc0
	lsls r0, r0, #5
_08097FA4:
	adds r2, r3, r0
_08097FA6:
	str r2, [r4, #0x58]
	b _08098038
	.align 2, 0
_08097FAC: .4byte 0xFFFFE800
_08097FB0:
	ldr r3, [r4, #0x58]
	ldr r1, _08097FE0 @ =0xFFFFDD00
	adds r0, r3, r1
	str r0, [r4, #0x58]
	adds r2, r0, #0
	ldrb r1, [r4, #0xa]
	movs r0, #0x20
	ands r0, r1
	cmp r0, #0
	beq _08097FCA
	movs r0, #0x8c
	lsls r0, r0, #6
	adds r2, r3, r0
_08097FCA:
	str r2, [r4, #0x58]
	lsls r0, r1, #0x18
	lsrs r0, r0, #0x1d
	movs r2, #1
	bics r2, r0
	cmp r2, #0
	beq _08098018
	movs r0, #0x20
	orrs r0, r1
	b _0809801C
	.align 2, 0
_08097FE0: .4byte 0xFFFFDD00
_08097FE4:
	ldr r3, [r4, #0x58]
	ldr r1, _08098014 @ =0xFFFFD500
	adds r0, r3, r1
	str r0, [r4, #0x58]
	adds r2, r0, #0
	ldrb r1, [r4, #0xa]
	movs r0, #0x20
	ands r0, r1
	cmp r0, #0
	beq _08097FFE
	movs r0, #0xac
	lsls r0, r0, #6
	adds r2, r3, r0
_08097FFE:
	str r2, [r4, #0x58]
	lsls r0, r1, #0x18
	lsrs r0, r0, #0x1d
	movs r2, #1
	bics r2, r0
	cmp r2, #0
	beq _08098018
	movs r0, #0x20
	orrs r0, r1
	b _0809801C
	.align 2, 0
_08098014: .4byte 0xFFFFD500
_08098018:
	movs r0, #0xdf
	ands r0, r1
_0809801C:
	strb r0, [r4, #0xa]
	adds r0, r2, #0
	adds r1, r4, #0
	adds r1, #0x4d
	strb r0, [r1]
	adds r3, r4, #0
	adds r3, #0x4a
	lsls r0, r0, #5
	ldrb r2, [r3]
	movs r1, #0x21
	rsbs r1, r1, #0
	ands r1, r2
	orrs r1, r0
	strb r1, [r3]
_08098038:
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r1, #0
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	adds r0, #0x8c
	str r1, [r0]
	adds r0, #4
	str r1, [r0]
	adds r0, #4
	strb r1, [r0]
	ldrb r1, [r4, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r4, #0xa]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0809805E:
	ldr r0, [r4, #0x54]
	str r0, [sp]
	ldr r0, [r4, #0x58]
	ldr r1, _080980B0 @ =0xFFFFF800
	adds r0, r0, r1
	str r0, [sp, #4]
	movs r0, #1
	mov r1, sp
	bl CreateSmoke
	adds r0, r4, #0
	mov r1, sp
	bl FUN_080c6e70
	movs r0, #0x2a
	bl PlaySound
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	bl FUN_080098a4
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _080980C6
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	bl PushoutToUp1
	adds r5, r0, #0
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	bl PushoutToDown1
	adds r1, r0, #0
	cmp r5, #0
	bgt _080980C0
	cmp r1, #0
	bge _080980B4
	ldr r0, [r4, #0x58]
	adds r0, r0, r5
	b _080980C4
	.align 2, 0
_080980B0: .4byte 0xFFFFF800
_080980B4:
	rsbs r0, r5, #0
	cmp r0, r1
	bge _080980C0
	ldr r0, [r4, #0x58]
	adds r0, r0, r5
	b _080980C4
_080980C0:
	ldr r0, [r4, #0x58]
	adds r0, r0, r1
_080980C4:
	str r0, [r4, #0x58]
_080980C6:
	adds r5, r4, #0
	adds r5, #0x54
	movs r0, #1
	adds r1, r5, #0
	bl TryDropItem
	ldr r2, _08098104 @ =gMission
	ldrh r1, [r2, #0xc]
	ldr r0, _08098108 @ =0x0000270E
	cmp r1, r0
	bhi _080980E0
	adds r0, r1, #1
	strh r0, [r2, #0xc]
_080980E0:
	adds r0, r4, #0
	adds r1, r5, #0
	bl TryDropZakoDisk
	ldr r1, _0809810C @ =gEnemyFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #4
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0x10]
	str r0, [r4, #0x14]
_080980FA:
	add sp, #8
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_08098104: .4byte gMission
_08098108: .4byte 0x0000270E
_0809810C: .4byte gEnemyFnTable
