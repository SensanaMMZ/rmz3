	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_080866a4
FUN_080866a4: @ 0x080866A4
	push {r4, r5, r6, lr}
	adds r5, r0, #0
	lsls r1, r1, #0x18
	lsrs r6, r1, #0x18
	lsls r2, r2, #0x18
	lsrs r4, r2, #0x18
	ldr r0, _08086700 @ =gEnemyHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	mov ip, r0
	cmp r0, #0
	beq _08086738
	mov r1, ip
	adds r1, #0x25
	movs r2, #0
	movs r0, #0x18
	strb r0, [r1]
	ldr r0, _08086704 @ =gEnemyFnTable
	movs r1, #0x2d
	mov r3, ip
	strb r1, [r3, #9]
	adds r0, #0xb4
	ldr r0, [r0]
	ldr r0, [r0]
	str r0, [r3, #0x14]
	movs r0, #0
	strh r2, [r3, #0x20]
	mov r1, ip
	adds r1, #0x22
	strb r0, [r1]
	ldrb r0, [r3, #0xb]
	movs r1, #0x10
	orrs r0, r1
	strb r0, [r3, #0xb]
	ldrb r0, [r3, #0x1c]
	strb r0, [r3, #0x1d]
	str r5, [r3, #0x28]
	adds r2, r4, #0
	cmp r2, #0
	beq _08086708
	ldrb r0, [r3, #0xa]
	orrs r0, r1
	strb r0, [r3, #0xa]
	b _08086714
	.align 2, 0
_08086700: .4byte gEnemyHeaderPtr
_08086704: .4byte gEnemyFnTable
_08086708:
	mov r0, ip
	ldrb r1, [r0, #0xa]
	movs r0, #0xef
	ands r0, r1
	mov r1, ip
	strb r0, [r1, #0xa]
_08086714:
	movs r1, #1
	ands r1, r2
	mov r0, ip
	adds r0, #0x4c
	movs r3, #0
	strb r1, [r0]
	mov r4, ip
	adds r4, #0x4a
	lsls r1, r1, #4
	ldrb r2, [r4]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r1
	strb r0, [r4]
	mov r2, ip
	strb r6, [r2, #0x10]
	strb r3, [r2, #0x11]
_08086738:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start HanumachineObj_Init
HanumachineObj_Init:
	.byte 0xF0, 0xB5, 0x06, 0x1C, 0xB7, 0x6A, 0x19, 0x49, 0x70, 0x7A, 0x80, 0x00, 0x40, 0x18, 0x01, 0x21
	.byte 0xF1, 0x60, 0x00, 0x68, 0x40, 0x68, 0x70, 0x61, 0x30, 0x1C, 0x90, 0xF7, 0xAF, 0xFE, 0xB1, 0x7A
	.byte 0x01, 0x20, 0x00, 0x25, 0x08, 0x43, 0x02, 0x21, 0x08, 0x43, 0xB0, 0x72, 0x10, 0x49, 0x30, 0x1C
	.byte 0x90, 0xF7, 0xFA, 0xFE, 0xB1, 0x7A, 0x04, 0x20, 0x08, 0x43, 0xB0, 0x72, 0x34, 0x1C, 0x74, 0x34
	.byte 0x0C, 0x49, 0x32, 0x1C, 0x54, 0x32, 0x20, 0x1C, 0x08, 0x23, 0x80, 0xF7, 0x31, 0xFD, 0xE6, 0x62
	.byte 0x65, 0x62, 0xB1, 0x7A, 0x10, 0x20, 0x08, 0x40, 0x00, 0x28, 0x0D, 0xD0, 0x78, 0x6D, 0xB0, 0x21
	.byte 0x49, 0x01, 0x40, 0x18, 0x70, 0x65, 0x80, 0x20, 0xC0, 0x00, 0x0A, 0xE0, 0x48, 0x59, 0x36, 0x08
	.byte 0x03, 0x6A, 0x00, 0x00, 0xE8, 0x85, 0x36, 0x08, 0x78, 0x6D, 0x0F, 0x49, 0x40, 0x18, 0x70, 0x65
	.byte 0x0E, 0x48, 0xF0, 0x65, 0xB8, 0x6D, 0x0E, 0x49, 0x40, 0x18, 0xB0, 0x65, 0x31, 0x1C, 0xC0, 0x31
	.byte 0x00, 0x22, 0x00, 0x23, 0x96, 0x20, 0x80, 0x00, 0x08, 0x80, 0x30, 0x1C, 0xBD, 0x30, 0x02, 0x70
	.byte 0x33, 0x66, 0x6D, 0x38, 0x40, 0x21, 0x01, 0x80, 0x02, 0x30, 0x01, 0x80, 0x30, 0x1C, 0x00, 0xF0
	.byte 0x09, 0xF8, 0xF0, 0xBC, 0x01, 0xBC, 0x00, 0x47, 0x00, 0xEA, 0xFF, 0xFF, 0x00, 0xFC, 0xFF, 0xFF
	.byte 0x00, 0xF1, 0xFF, 0xFF

	thumb_func_start HanumachineObj_Update
HanumachineObj_Update: @ 0x08086804
	push {r4, r5, lr}
	sub sp, #0x10
	adds r5, r0, #0
	adds r4, r5, #0
	adds r4, #0xc0
	ldrh r0, [r4]
	cmp r0, #0
	bne _0808685C
	ldr r0, [r5, #0x54]
	str r0, [sp]
	ldr r0, [r5, #0x58]
	ldr r1, _08086844 @ =0xFFFFF800
	adds r0, r0, r1
	str r0, [sp, #4]
	movs r0, #0x2a
	bl PlaySound
	movs r0, #1
	mov r1, sp
	bl CreateSmoke
	adds r0, r5, #0
	adds r0, #0xbd
	ldrb r0, [r0]
	cmp r0, #0
	beq _0808684C
	adds r0, r5, #0
	adds r0, #0x74
	ldr r1, _08086848 @ =0x08368660
	bl SetDDP
	b _080868B4
	.align 2, 0
_08086844: .4byte 0xFFFFF800
_08086848: .4byte 0x08368660
_0808684C:
	adds r0, r5, #0
	adds r0, #0x74
	ldr r1, _08086858 @ =0x08368630
	bl SetDDP
	b _080868B4
	.align 2, 0
_08086858: .4byte 0x08368630
_0808685C:
	ldrb r0, [r5, #0xd]
	cmp r0, #7
	beq _0808687E
	adds r2, r5, #0
	adds r2, #0x8c
	ldr r0, [r2]
	ldr r1, _08086888 @ =0x00020001
	ands r0, r1
	cmp r0, r1
	bne _08086878
	movs r1, #0
	movs r0, #7
	strb r0, [r5, #0xd]
	strb r1, [r5, #0xe]
_08086878:
	ldrb r0, [r5, #0xd]
	cmp r0, #7
	bne _0808688C
_0808687E:
	adds r0, r5, #0
	bl FUN_08086e34
	b _08086912
	.align 2, 0
_08086888: .4byte 0x00020001
_0808688C:
	ldr r0, [r2]
	movs r1, #0x80
	lsls r1, r1, #2
	ands r0, r1
	cmp r0, #0
	beq _080868D8
	ldr r0, [r5, #0x54]
	str r0, [sp, #8]
	ldr r0, [r5, #0x58]
	ldr r1, _080868D0 @ =0xFFFFF800
	adds r0, r0, r1
	add r4, sp, #8
	str r0, [r4, #4]
	movs r0, #0x2a
	bl PlaySound
	movs r0, #1
	adds r1, r4, #0
	bl CreateSmoke
_080868B4:
	ldr r1, _080868D4 @ =gEnemyFnTable
	ldrb r0, [r5, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r5, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r5, #0x14]
	adds r0, r5, #0
	bl HanumachineObj_Die
	b _08086912
	.align 2, 0
_080868D0: .4byte 0xFFFFF800
_080868D4: .4byte gEnemyFnTable
_080868D8:
	ldr r1, _08086908 @ =0x083685C8
	ldrb r0, [r5, #0xd]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r1, [r0]
	adds r0, r5, #0
	bl _call_via_r1
	ldrh r0, [r4]
	subs r1, r0, #1
	strh r1, [r4]
	lsls r0, r1, #0x10
	lsrs r0, r0, #0x10
	cmp r0, #0x3b
	bhi _08086912
	movs r0, #3
	ands r1, r0
	cmp r1, #1
	bhi _0808690C
	adds r0, r5, #0
	bl PaintEntityWhite
	b _08086912
	.align 2, 0
_08086908: .4byte 0x083685C8
_0808690C:
	adds r0, r5, #0
	bl UpdateEntityPaletteID
_08086912:
	add sp, #0x10
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
