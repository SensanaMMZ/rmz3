	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start childreMode3
childreMode3: @ 0x08040E60
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #5
	bls _08040E6C
	b _08041026
_08040E6C:
	lsls r0, r0, #2
	ldr r1, _08040E78 @ =_08040E7C
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_08040E78: .4byte _08040E7C
_08040E7C: @ jump table
	.4byte _08040E94 @ case 0
	.4byte _08040EB0 @ case 1
	.4byte _08040ED4 @ case 2
	.4byte _08040F4A @ case 3
	.4byte _08040FCC @ case 4
	.4byte _08040FDE @ case 5
_08040E94:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _08040ECC @ =sCollisions+(24*1)
	bl SetDDP
	movs r0, #4
	strb r0, [r4, #0x12]
	ldr r1, _08040ED0 @ =0x0000A404
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08040EB0:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _08040EC4
	b _08041026
_08040EC4:
	ldrb r0, [r4, #0xe]
	adds r0, #1
	b _08041024
	.align 2, 0
_08040ECC: .4byte sCollisions+(24*1)
_08040ED0: .4byte 0x0000A404
_08040ED4:
	movs r0, #0x67
	bl PlaySound
	adds r0, r4, #0
	adds r0, #0xbc
	ldr r1, [r0]
	ldr r0, [r4, #0x54]
	subs r2, r1, r0
	movs r0, #0xc0
	lsls r0, r0, #6
	adds r1, r2, r0
	movs r0, #0xc0
	lsls r0, r0, #7
	cmp r1, r0
	bls _08040F1E
	movs r3, #0
	cmp r2, #0
	ble _08040EFA
	movs r3, #1
_08040EFA:
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _08040F0A
	cmp r3, #0
	beq _08040F0E
	b _08040F1E
_08040F0A:
	cmp r3, #0
	beq _08040F1E
_08040F0E:
	movs r1, #0
	movs r0, #4
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
	adds r0, r4, #0
	bl childreStartRising
	b _08041026
_08040F1E:
	ldr r1, _08040FBC @ =0x0000A405
	adds r0, r4, #0
	bl SetMotion
	ldr r0, _08040FC0 @ =0xFFFFFD00
	str r0, [r4, #0x5c]
	adds r2, r0, #0
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _08040F3A
	movs r2, #0xc0
	lsls r2, r2, #2
_08040F3A:
	str r2, [r4, #0x5c]
	ldr r0, _08040FC4 @ =0xFFFFFC00
	str r0, [r4, #0x60]
	movs r0, #0
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08040F4A:
	ldr r0, [r4, #0x54]
	ldr r5, [r4, #0x5c]
	adds r3, r0, r5
	str r3, [r4, #0x54]
	adds r0, r4, #0
	adds r0, #0xbc
	ldr r0, [r0]
	subs r2, r0, r3
	movs r0, #0xc0
	lsls r0, r0, #7
	adds r1, r2, r0
	movs r0, #0xc0
	lsls r0, r0, #8
	cmp r1, r0
	bls _08040F6C
	subs r0, r3, r5
	str r0, [r4, #0x54]
_08040F6C:
	ldr r0, [r4, #0x60]
	adds r0, #0x40
	str r0, [r4, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _08040F7C
	str r1, [r4, #0x60]
_08040F7C:
	ldrb r0, [r4, #0x12]
	cmp r0, #0
	bne _08040F94
	ldr r0, [r4, #0x60]
	cmp r0, #0
	ble _08040F94
	ldr r1, _08040FC8 @ =0x0000A406
	adds r0, r4, #0
	bl SetMotion
	movs r0, #1
	strb r0, [r4, #0x12]
_08040F94:
	ldr r1, [r4, #0x58]
	ldr r0, [r4, #0x60]
	adds r1, r1, r0
	str r1, [r4, #0x58]
	ldr r0, [r4, #0x54]
	bl PushoutToUp1
	adds r2, r0, #0
	cmp r2, #0
	bge _08040FB4
	ldr r0, [r4, #0x58]
	adds r0, r0, r2
	str r0, [r4, #0x58]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08040FB4:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	b _08041026
	.align 2, 0
_08040FBC: .4byte 0x0000A405
_08040FC0: .4byte 0xFFFFFD00
_08040FC4: .4byte 0xFFFFFC00
_08040FC8: .4byte 0x0000A406
_08040FCC:
	movs r0, #4
	strb r0, [r4, #0x12]
	ldr r1, _08041014 @ =0x0000A407
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08040FDE:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _08041026
	movs r2, #0
	adds r0, r4, #0
	adds r0, #0xb8
	ldr r0, [r0]
	ldr r1, [r4, #0x54]
	subs r0, r0, r1
	cmp r0, #0
	ble _08041002
	movs r2, #1
_08041002:
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _08041018
	cmp r2, #0
	beq _0804101C
	b _08041022
	.align 2, 0
_08041014: .4byte 0x0000A407
_08041018:
	cmp r2, #0
	beq _08041022
_0804101C:
	movs r0, #0
	strb r0, [r4, #0xd]
	b _08041024
_08041022:
	movs r0, #2
_08041024:
	strb r0, [r4, #0xe]
_08041026:
	pop {r4, r5}
	pop {r0}
	bx r0
