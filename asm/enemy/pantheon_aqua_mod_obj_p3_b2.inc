	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_08081e00
FUN_08081e00: @ 0x08081E00
	push {r4, r5, lr}
	adds r4, r0, #0
	ldr r5, [r4, #0x28]
	ldrb r0, [r5, #0xc]
	cmp r0, #1
	bls _08081E0E
	b _08081F80
_08081E0E:
	ldrb r0, [r4, #0xe]
	cmp r0, #5
	bls _08081E16
	b _08081FB6
_08081E16:
	lsls r0, r0, #2
	ldr r1, _08081E20 @ =_08081E24
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_08081E20: .4byte _08081E24
_08081E24: @ jump table
	.4byte _08081E3C @ case 0
	.4byte _08081E98 @ case 1
	.4byte _08081EC8 @ case 2
	.4byte _08081EF8 @ case 3
	.4byte _08081F1C @ case 4
	.4byte _08081F3E @ case 5
_08081E3C:
	ldrb r1, [r4, #0xb]
	movs r0, #0x10
	orrs r0, r1
	strb r0, [r4, #0xb]
	ldrb r0, [r5, #0x1c]
	strb r0, [r4, #0x1d]
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _08081E6C @ =0x083680C0
	bl SetDDP
	adds r1, r4, #0
	adds r1, #0x25
	movs r0, #0xe
	strb r0, [r1]
	ldrb r0, [r4, #0x11]
	cmp r0, #0
	bne _08081E74
	ldr r1, _08081E70 @ =0x00004D05
	adds r0, r4, #0
	bl SetMotion
	b _08081E7C
	.align 2, 0
_08081E6C: .4byte 0x083680C0
_08081E70: .4byte 0x00004D05
_08081E74:
	ldr r1, _08081EBC @ =0x00004D0A
	adds r0, r4, #0
	bl SetMotion
_08081E7C:
	ldrb r1, [r4, #0x11]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #9
	ldr r1, _08081EC0 @ =0xFFFFFD00
	adds r0, r0, r1
	str r0, [r4, #0x5c]
	ldr r0, _08081EC4 @ =0xFFFFFF00
	str r0, [r4, #0x60]
	movs r0, #0
	str r0, [r4, #0x64]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08081E98:
	ldr r0, [r4, #0x64]
	adds r0, #1
	str r0, [r4, #0x64]
	ldr r0, [r4, #0x54]
	ldr r3, [r4, #0x5c]
	adds r0, r0, r3
	str r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	ldr r2, [r4, #0x60]
	adds r1, r1, r2
	str r1, [r4, #0x58]
	lsls r3, r3, #1
	adds r0, r0, r3
	bl FUN_080098a4
	lsls r0, r0, #0x10
	b _08081F04
	.align 2, 0
_08081EBC: .4byte 0x00004D0A
_08081EC0: .4byte 0xFFFFFD00
_08081EC4: .4byte 0xFFFFFF00
_08081EC8:
	ldrb r0, [r4, #0x11]
	cmp r0, #0
	bne _08081EDC
	ldr r1, _08081ED8 @ =0x00004D0C
	adds r0, r4, #0
	bl SetMotion
	b _08081EE4
	.align 2, 0
_08081ED8: .4byte 0x00004D0C
_08081EDC:
	ldr r1, _08081F18 @ =0x00004D0D
	adds r0, r4, #0
	bl SetMotion
_08081EE4:
	adds r2, r5, #0
	adds r2, #0xb4
	ldr r0, [r2]
	movs r1, #0x80
	lsls r1, r1, #2
	orrs r0, r1
	str r0, [r2]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08081EF8:
	adds r0, r5, #0
	adds r0, #0xb4
	ldr r0, [r0]
	movs r1, #0x80
	lsls r1, r1, #3
	ands r0, r1
_08081F04:
	cmp r0, #0
	beq _08081F0E
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08081F0E:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	b _08081FB6
	.align 2, 0
_08081F18: .4byte 0x00004D0D
_08081F1C:
	ldrb r0, [r4, #0x11]
	cmp r0, #0
	bne _08081F30
	ldr r1, _08081F2C @ =0x00004D05
	adds r0, r4, #0
	bl SetMotion
	b _08081F38
	.align 2, 0
_08081F2C: .4byte 0x00004D05
_08081F30:
	ldr r1, _08081F70 @ =0x00004D0A
	adds r0, r4, #0
	bl SetMotion
_08081F38:
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08081F3E:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	subs r0, r0, r1
	str r0, [r4, #0x54]
	ldr r0, [r4, #0x58]
	ldr r1, [r4, #0x60]
	subs r0, r0, r1
	str r0, [r4, #0x58]
	ldr r0, [r4, #0x64]
	subs r0, #1
	str r0, [r4, #0x64]
	cmp r0, #0
	bne _08081FB6
	ldrb r0, [r4, #0x11]
	cmp r0, #0
	bne _08081F74
	adds r0, r5, #0
	adds r0, #0xb4
	ldr r1, [r0]
	movs r2, #0x81
	rsbs r2, r2, #0
	b _08081F7C
	.align 2, 0
_08081F70: .4byte 0x00004D0A
_08081F74:
	adds r0, r5, #0
	adds r0, #0xb4
	ldr r1, [r0]
	ldr r2, _08081FBC @ =0xFFFFFEFF
_08081F7C:
	ands r1, r2
	str r1, [r0]
_08081F80:
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r2, #0
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	adds r0, #0x8c
	str r2, [r0]
	adds r0, #4
	str r2, [r0]
	adds r0, #4
	strb r2, [r0]
	ldrb r1, [r4, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r4, #0xa]
	ldr r1, _08081FC0 @ =gEnemyFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r4, #0x14]
_08081FB6:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_08081FBC: .4byte 0xFFFFFEFF
_08081FC0: .4byte gEnemyFnTable

	thumb_func_start FUN_08081fc4
FUN_08081fc4: @ 0x08081FC4
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r5, [r4, #0xe]
	cmp r5, #0
	beq _08081FD4
	cmp r5, #1
	beq _08082006
	b _080820AC
_08081FD4:
	adds r1, r4, #0
	adds r1, #0x25
	movs r0, #0xe
	strb r0, [r1]
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _08082064 @ =0x08368090
	bl SetDDP
	strb r5, [r4, #0x12]
	strb r5, [r4, #0x13]
	ldr r0, _08082068 @ =gStageRun+232
	ldr r0, [r0, #0x3c]
	ldr r1, _0808206C @ =0xFFFF9000
	adds r0, r0, r1
	str r0, [r4, #0x58]
	str r5, [r4, #0x60]
	movs r1, #0x9e
	lsls r1, r1, #7
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08082006:
	ldrb r0, [r4, #0x13]
	adds r0, #1
	strb r0, [r4, #0x13]
	ldrb r0, [r4, #0x13]
	movs r1, #3
	ands r0, r1
	cmp r0, #0
	bne _0808203A
	ldr r2, _08082070 @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _08082074 @ =0x000343FD
	muls r1, r0, r1
	ldr r0, _08082078 @ =0x00269EC3
	adds r1, r1, r0
	lsls r1, r1, #1
	lsrs r0, r1, #1
	str r0, [r2]
	lsls r1, r1, #3
	lsrs r1, r1, #0x14
	ldr r2, _0808207C @ =0xFFFFF800
	adds r1, r1, r2
	ldr r0, [r4, #0x54]
	adds r0, r0, r1
	ldr r1, [r4, #0x58]
	bl FUN_080c02f4
_0808203A:
	ldr r0, [r4, #0x60]
	adds r0, #0x15
	str r0, [r4, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _0808204A
	str r1, [r4, #0x60]
_0808204A:
	ldr r0, [r4, #0x58]
	ldr r1, [r4, #0x60]
	adds r0, r0, r1
	str r0, [r4, #0x58]
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldrb r0, [r4, #0x12]
	cmp r0, #0x1d
	bhi _08082080
	adds r0, #1
	strb r0, [r4, #0x12]
	b _080820AC
	.align 2, 0
_08082064: .4byte 0x08368090
_08082068: .4byte gStageRun+232
_0808206C: .4byte 0xFFFF9000
_08082070: .4byte RNG_0202f388
_08082074: .4byte 0x000343FD
_08082078: .4byte 0x00269EC3
_0808207C: .4byte 0xFFFFF800
_08082080:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	movs r2, #0xa0
	lsls r2, r2, #4
	adds r1, r1, r2
	bl FUN_080098a4
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _080820AC
	movs r0, #0xe2
	bl PlaySound
	ldr r1, _080820B4 @ =gEnemyFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r4, #0x14]
_080820AC:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080820B4: .4byte gEnemyFnTable
