	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start Weapon5_Init
Weapon5_Init: @ 0x0803A758
	push {r4, r5, r6, r7, lr}
	mov r7, sb
	mov r6, r8
	push {r6, r7}
	sub sp, #8
	adds r6, r0, #0
	adds r0, #0xb4
	ldr r1, [r0, #4]
	mov sb, r1
	ldr r0, [r0]
	mov r8, r0
	ldr r1, _0803A7C4 @ =gWeaponFnTable
	ldrb r0, [r6, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r4, #1
	str r4, [r6, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r6, #0x14]
	adds r0, r6, #0
	bl InitScalerotMotion1
	ldrb r1, [r6, #0xb]
	movs r0, #0xfb
	ands r0, r1
	movs r1, #0
	strb r0, [r6, #0xb]
	movs r0, #0
	strh r1, [r6, #0x20]
	adds r1, r6, #0
	adds r1, #0x22
	strb r0, [r1]
	ldrb r0, [r6, #0xa]
	movs r1, #1
	movs r5, #0
	orrs r0, r1
	movs r1, #2
	orrs r0, r1
	strb r0, [r6, #0xa]
	adds r0, r6, #0
	movs r1, #0x1c
	bl SetMotion
	mov r1, r8
	ldrb r0, [r1, #0xa]
	lsrs r2, r0, #4
	ands r2, r4
	cmp r2, #0
	beq _0803A7C8
	ldrb r0, [r6, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _0803A7CE
	.align 2, 0
_0803A7C4: .4byte gWeaponFnTable
_0803A7C8:
	ldrb r1, [r6, #0xa]
	movs r0, #0xef
	ands r0, r1
_0803A7CE:
	strb r0, [r6, #0xa]
	adds r1, r2, #0
	adds r0, r6, #0
	adds r0, #0x4c
	strb r1, [r0]
	adds r2, r6, #0
	adds r2, #0x4a
	lsls r1, r1, #4
	ldrb r3, [r2]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r3
	orrs r0, r1
	strb r0, [r2]
	ldrb r3, [r6, #0x10]
	adds r4, r2, #0
	cmp r3, #0
	beq _0803A7FA
	ldrb r0, [r6, #0xa]
	movs r1, #0x20
	orrs r0, r1
	b _0803A800
_0803A7FA:
	ldrb r1, [r6, #0xa]
	movs r0, #0xdf
	ands r0, r1
_0803A800:
	strb r0, [r6, #0xa]
	movs r0, #1
	ands r0, r3
	adds r1, r6, #0
	adds r1, #0x4d
	strb r0, [r1]
	lsls r0, r0, #5
	ldrb r2, [r4]
	movs r1, #0x21
	rsbs r1, r1, #0
	ands r1, r2
	orrs r1, r0
	strb r1, [r4]
	ldrb r7, [r6, #0x10]
	cmp r7, #0
	bne _0803A8A8
	ldrb r0, [r6, #0xa]
	movs r1, #4
	orrs r0, r1
	strb r0, [r6, #0xa]
	adds r4, r6, #0
	adds r4, #0x74
	ldr r5, _0803A880 @ =0x08361338
	adds r2, r6, #0
	adds r2, #0x54
	adds r0, r4, #0
	adds r1, r5, #0
	movs r3, #1
	bl InitBody
	str r6, [r4, #0x2c]
	str r7, [r4, #0x24]
	mov r0, sb
	bl CalcSaberBonus
	adds r2, r0, #0
	adds r2, #8
	lsls r2, r2, #0x18
	lsrs r2, r2, #0x18
	movs r3, #1
	rsbs r3, r3, #0
	str r3, [sp]
	str r3, [sp, #4]
	adds r0, r4, #0
	adds r1, r5, #0
	bl InitWeaponBody
	ldrb r1, [r6, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _0803A884
	mov r1, r8
	ldr r0, [r1, #0x54]
	movs r1, #0x88
	lsls r1, r1, #6
	adds r0, r0, r1
	str r0, [r6, #0x54]
	movs r0, #0x80
	lsls r0, r0, #3
	str r0, [r6, #0x5c]
	movs r0, #0x55
	rsbs r0, r0, #0
	b _0803A894
	.align 2, 0
_0803A880: .4byte 0x08361338
_0803A884:
	mov r1, r8
	ldr r0, [r1, #0x54]
	ldr r1, _0803A8BC @ =0xFFFFDE00
	adds r0, r0, r1
	str r0, [r6, #0x54]
	ldr r0, _0803A8C0 @ =0xFFFFFC00
	str r0, [r6, #0x5c]
	movs r0, #0x55
_0803A894:
	str r0, [r6, #0x64]
	mov r1, r8
	ldr r0, [r1, #0x58]
	ldr r1, _0803A8C4 @ =0xFFFFEC00
	adds r0, r0, r1
	str r0, [r6, #0x58]
	movs r0, #0x12
	strb r0, [r6, #0x12]
	ldr r0, _0803A8C8 @ =hitZSaber
	str r0, [r4, #0x24]
_0803A8A8:
	adds r0, r6, #0
	bl Weapon5_Update
	add sp, #8
	pop {r3, r4}
	mov r8, r3
	mov sb, r4
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_0803A8BC: .4byte 0xFFFFDE00
_0803A8C0: .4byte 0xFFFFFC00
_0803A8C4: .4byte 0xFFFFEC00
_0803A8C8: .4byte hitZSaber

