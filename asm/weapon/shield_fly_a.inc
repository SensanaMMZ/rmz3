	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start shield_08039e28
shield_08039e28: @ 0x08039E28
	push {r4, r5, r6, r7, lr}
	mov r7, sl
	mov r6, sb
	mov r5, r8
	push {r5, r6, r7}
	sub sp, #0x10
	adds r6, r0, #0
	adds r5, r6, #0
	adds r5, #0xb4
	ldr r0, [r5]
	mov r8, r0
	ldrb r7, [r6, #0xe]
	cmp r7, #0
	beq _08039E46
	b _08039F48
_08039E46:
	ldrb r1, [r6, #0xa]
	movs r0, #4
	movs r2, #0
	mov sl, r2
	orrs r0, r1
	strb r0, [r6, #0xa]
	adds r4, r6, #0
	adds r4, #0x74
	ldr r3, _08039EB8 @ =0x083612AC
	mov sb, r3
	adds r2, r6, #0
	adds r2, #0x54
	adds r0, r4, #0
	mov r1, sb
	movs r3, #1
	bl InitBody
	str r6, [r4, #0x2c]
	str r7, [r4, #0x24]
	mov r0, r8
	bl CalcShieldBonus
	adds r2, r0, #0
	adds r2, #0xc
	lsls r2, r2, #0x18
	lsrs r2, r2, #0x18
	ldr r1, _08039EBC @ =0x08361284
	ldrb r0, [r5, #0xd]
	adds r0, r0, r1
	ldrb r3, [r0]
	movs r0, #1
	rsbs r0, r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	adds r0, r4, #0
	mov r1, sb
	bl InitWeaponBody
	ldr r0, _08039EC0 @ =onHit
	str r0, [r4, #0x24]
	ldr r1, _08039EC4 @ =0x00006D01
	adds r0, r6, #0
	bl SetMotion
	ldrb r0, [r6, #0x10]
	cmp r0, #2
	bne _08039EE6
	ldrb r2, [r6, #0xa]
	lsrs r0, r2, #4
	movs r1, #1
	bics r1, r0
	cmp r1, #0
	beq _08039EC8
	movs r0, #0x10
	orrs r0, r2
	b _08039ECC
	.align 2, 0
_08039EB8: .4byte 0x083612AC
_08039EBC: .4byte 0x08361284
_08039EC0: .4byte onHit
_08039EC4: .4byte 0x00006D01
_08039EC8:
	movs r0, #0xef
	ands r0, r2
_08039ECC:
	strb r0, [r6, #0xa]
	adds r0, r6, #0
	adds r0, #0x4c
	strb r1, [r0]
	adds r3, r6, #0
	adds r3, #0x4a
	lsls r1, r1, #4
	ldrb r2, [r3]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r1
	strb r0, [r3]
_08039EE6:
	ldrb r1, [r6, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _08039F10
	ldr r2, _08039F0C @ =0x0836128C
	ldrb r0, [r6, #0x10]
	lsls r0, r0, #2
	adds r0, r0, r2
	movs r3, #0
	ldrsh r1, [r0, r3]
	ldr r0, [r6, #0x54]
	adds r0, r0, r1
	str r0, [r6, #0x54]
	adds r1, r6, #0
	adds r1, #0xb4
	movs r0, #0
	b _08039F28
	.align 2, 0
_08039F0C: .4byte 0x0836128C
_08039F10:
	ldr r2, _08039F84 @ =0x0836128C
	ldrb r0, [r6, #0x10]
	lsls r0, r0, #2
	adds r0, r0, r2
	movs r3, #0
	ldrsh r1, [r0, r3]
	ldr r0, [r6, #0x54]
	subs r0, r0, r1
	str r0, [r6, #0x54]
	adds r1, r6, #0
	adds r1, #0xb4
	movs r0, #0x80
_08039F28:
	strb r0, [r1, #0xc]
	ldrb r0, [r6, #0x10]
	lsls r0, r0, #2
	adds r1, r2, #2
	adds r0, r0, r1
	movs r2, #0
	ldrsh r1, [r0, r2]
	ldr r0, [r6, #0x58]
	adds r0, r0, r1
	str r0, [r6, #0x58]
	ldr r0, _08039F88 @ =0x08361288
	ldrb r0, [r0, #2]
	strb r0, [r6, #0x12]
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_08039F48:
	ldr r0, [r6, #0x54]
	ldr r1, [r6, #0x58]
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	ldrb r1, [r6, #0xa]
	movs r0, #0x10
	ands r0, r1
	lsls r0, r0, #0x18
	lsrs r4, r0, #0x18
	cmp r4, #0
	beq _08039F8C
	ldr r0, [r6, #0x54]
	movs r1, #0xc0
	lsls r1, r1, #3
	adds r0, r0, r1
	str r0, [r6, #0x54]
	ldr r1, [r6, #0x58]
	bl PushoutToLeft1
	adds r1, r0, #0
	cmp r1, #0
	beq _08039FAC
	ldr r0, [r6, #0x54]
	adds r0, r0, r1
	str r0, [r6, #0x54]
	adds r1, r6, #0
	adds r1, #0xb4
	movs r0, #0x80
	strb r0, [r1, #0xc]
	b _08039FAC
	.align 2, 0
_08039F84: .4byte 0x0836128C
_08039F88: .4byte 0x08361288
_08039F8C:
	ldr r0, [r6, #0x54]
	ldr r2, _08039FF8 @ =0xFFFFFA00
	adds r0, r0, r2
	str r0, [r6, #0x54]
	ldr r1, [r6, #0x58]
	bl PushoutToRight1
	adds r1, r0, #0
	cmp r1, #0
	beq _08039FAC
	ldr r0, [r6, #0x54]
	adds r0, r0, r1
	str r0, [r6, #0x54]
	adds r0, r6, #0
	adds r0, #0xb4
	strb r4, [r0, #0xc]
_08039FAC:
	adds r0, r6, #0
	adds r0, #0x8c
	ldr r0, [r0]
	movs r1, #0x80
	lsls r1, r1, #1
	ands r0, r1
	cmp r0, #0
	beq _08039FD2
	ldr r0, [sp, #8]
	ldr r1, [sp, #0xc]
	str r0, [r6, #0x54]
	str r1, [r6, #0x58]
	adds r0, r6, #0
	adds r0, #0xb4
	ldrb r1, [r0, #0xc]
	adds r1, #0x80
	strb r1, [r0, #0xc]
	movs r0, #1
	strb r0, [r6, #0x12]
_08039FD2:
	ldrb r0, [r6, #0x12]
	subs r0, #1
	strb r0, [r6, #0x12]
	lsls r0, r0, #0x18
	lsrs r1, r0, #0x18
	cmp r1, #0
	bne _08039FE8
	ldrb r0, [r6, #0xd]
	adds r0, #1
	strb r0, [r6, #0xd]
	strb r1, [r6, #0xe]
_08039FE8:
	add sp, #0x10
	pop {r3, r4, r5}
	mov r8, r3
	mov sb, r4
	mov sl, r5
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_08039FF8: .4byte 0xFFFFFA00
