	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080818b8
FUN_080818b8: @ 0x080818B8
	push {r4, r5, r6, r7, lr}
	adds r6, r0, #0
	ldr r5, [r6, #0x28]
	ldrb r0, [r5, #0xc]
	cmp r0, #1
	bhi _080818CC
	ldr r7, [r6, #0x2c]
	ldrb r0, [r7, #0xc]
	cmp r0, #4
	bne _08081908
_080818CC:
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
	ldr r1, _08081904 @ =gEnemyFnTable
	ldrb r0, [r6, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r6, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r6, #0x14]
	b _0808197C
	.align 2, 0
_08081904: .4byte gEnemyFnTable
_08081908:
	ldrb r0, [r6, #0xe]
	cmp r0, #0
	beq _08081914
	cmp r0, #1
	beq _08081936
	b _0808197C
_08081914:
	adds r1, r6, #0
	adds r1, #0x25
	movs r0, #0xf
	strb r0, [r1]
	ldrb r1, [r6, #0xb]
	movs r0, #0x10
	orrs r0, r1
	strb r0, [r6, #0xb]
	ldrb r0, [r5, #0x1c]
	strb r0, [r6, #0x1d]
	ldr r1, _08081984 @ =0x00004D04
	adds r0, r6, #0
	bl SetMotion
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_08081936:
	ldrb r1, [r6, #0x11]
	lsls r0, r1, #2
	adds r0, r0, r1
	lsls r0, r0, #0xb
	ldr r1, _08081988 @ =0xFFFFEC00
	adds r0, r0, r1
	ldr r1, [r5, #0x54]
	adds r1, r1, r0
	ldr r4, [r7, #0x54]
	subs r1, r1, r4
	ldr r5, [r5, #0x58]
	ldr r0, _0808198C @ =0xFFFFFB00
	adds r5, r5, r0
	ldr r0, [r7, #0x58]
	subs r5, r5, r0
	str r4, [r6, #0x54]
	ldrb r0, [r6, #0x12]
	muls r0, r1, r0
	movs r1, #6
	bl __divsi3
	adds r4, r4, r0
	str r4, [r6, #0x54]
	ldr r4, [r7, #0x58]
	str r4, [r6, #0x58]
	ldrb r0, [r6, #0x12]
	muls r0, r5, r0
	movs r1, #6
	bl __divsi3
	adds r4, r4, r0
	str r4, [r6, #0x58]
	adds r0, r6, #0
	bl UpdateMotionGraphic
_0808197C:
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_08081984: .4byte 0x00004D04
_08081988: .4byte 0xFFFFEC00
_0808198C: .4byte 0xFFFFFB00

	thumb_func_start FUN_08081990
FUN_08081990: @ 0x08081990
	push {r4, r5, r6, lr}
	adds r5, r0, #0
	ldr r6, [r5, #0x28]
	ldrb r0, [r6, #0xc]
	cmp r0, #1
	bls _080819B4
	ldrb r1, [r5, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r2, #0
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r5, #0xa]
	adds r0, r5, #0
	adds r0, #0x8c
	str r2, [r0]
	adds r0, #4
	b _08081C08
_080819B4:
	ldrb r0, [r5, #0xe]
	adds r4, r5, #0
	adds r4, #0x8c
	cmp r0, #7
	bls _080819C0
	b _08081C3A
_080819C0:
	lsls r0, r0, #2
	ldr r1, _080819CC @ =_080819D0
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_080819CC: .4byte _080819D0
_080819D0: @ jump table
	.4byte _080819F0 @ case 0
	.4byte _08081AC8 @ case 1
	.4byte _08081B1C @ case 2
	.4byte _08081B26 @ case 3
	.4byte _08081B44 @ case 4
	.4byte _08081B6A @ case 5
	.4byte _08081BAE @ case 6
	.4byte _08081BBE @ case 7
_080819F0:
	adds r0, r5, #0
	adds r0, #0x74
	ldr r1, _08081A6C @ =0x08368030
	bl SetDDP
	adds r1, r5, #0
	adds r1, #0x25
	movs r2, #0
	movs r0, #0xe
	strb r0, [r1]
	ldrb r1, [r5, #0xb]
	movs r0, #0x10
	orrs r0, r1
	strb r0, [r5, #0xb]
	ldrb r0, [r6, #0x1c]
	strb r0, [r5, #0x1d]
	str r2, [r5, #0x68]
	ldr r0, [r5, #0x54]
	ldr r1, _08081A70 @ =pZero2
	ldr r3, [r1]
	ldr r1, [r3, #0x54]
	subs r0, r0, r1
	ldr r1, [r5, #0x58]
	movs r4, #0xc0
	lsls r4, r4, #5
	adds r2, r1, r4
	ldr r1, [r3, #0x58]
	subs r1, r2, r1
	lsls r0, r0, #8
	asrs r0, r0, #0x10
	lsls r1, r1, #8
	asrs r1, r1, #0x10
	bl ArcTan2
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x18
	adds r0, #0x80
	lsls r0, r0, #0x18
	lsrs r4, r0, #0x18
	ldrb r0, [r5, #0x11]
	cmp r0, #0
	bne _08081A78
	adds r0, r4, #0
	subs r0, #0x48
	lsls r0, r0, #0x18
	lsrs r4, r0, #0x18
	cmp r4, #0x40
	bls _08081A5A
	movs r0, #0
	cmp r4, #0x9f
	bhi _08081A58
	movs r0, #0x40
_08081A58:
	adds r4, r0, #0
_08081A5A:
	adds r0, r4, #0
	adds r0, #0x48
	lsls r0, r0, #0x18
	lsrs r4, r0, #0x18
	ldr r1, _08081A74 @ =0x00004D05
	adds r0, r5, #0
	bl SetMotion
	b _08081A9E
	.align 2, 0
_08081A6C: .4byte 0x08368030
_08081A70: .4byte pZero2
_08081A74: .4byte 0x00004D05
_08081A78:
	adds r0, r4, #0
	adds r0, #8
	lsls r0, r0, #0x18
	lsrs r4, r0, #0x18
	cmp r4, #0x40
	bls _08081A8E
	movs r0, #0
	cmp r4, #0x9f
	bhi _08081A8C
	movs r0, #0x40
_08081A8C:
	adds r4, r0, #0
_08081A8E:
	adds r0, r4, #0
	subs r0, #8
	lsls r0, r0, #0x18
	lsrs r4, r0, #0x18
	ldr r1, _08081AE4 @ =0x00004D0A
	adds r0, r5, #0
	bl SetMotion
_08081A9E:
	ldr r1, _08081AE8 @ =gSineTable
	adds r0, r4, #0
	adds r0, #0x40
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x17
	adds r0, r0, r1
	movs r2, #0
	ldrsh r0, [r0, r2]
	lsls r0, r0, #2
	str r0, [r5, #0x5c]
	lsls r0, r4, #1
	adds r0, r0, r1
	movs r4, #0
	ldrsh r0, [r0, r4]
	lsls r0, r0, #2
	str r0, [r5, #0x60]
	movs r0, #0
	str r0, [r5, #0x64]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_08081AC8:
	adds r0, r5, #0
	adds r0, #0x8c
	ldr r1, [r0]
	movs r2, #0x80
	lsls r2, r2, #4
	ands r1, r2
	adds r4, r0, #0
	cmp r1, #0
	beq _08081AEC
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
	b _08081C3A
	.align 2, 0
_08081AE4: .4byte 0x00004D0A
_08081AE8: .4byte gSineTable
_08081AEC:
	ldr r0, [r5, #0x64]
	adds r0, #1
	str r0, [r5, #0x64]
	ldr r0, [r5, #0x54]
	ldr r3, [r5, #0x5c]
	adds r0, r0, r3
	str r0, [r5, #0x54]
	ldr r1, [r5, #0x58]
	ldr r2, [r5, #0x60]
	adds r1, r1, r2
	str r1, [r5, #0x58]
	lsls r3, r3, #2
	adds r0, r0, r3
	lsls r2, r2, #2
	adds r1, r1, r2
	bl FUN_080098a4
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _08081BA6
_08081B14:
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
	b _08081BA6
_08081B1C:
	movs r0, #0x10
	strb r0, [r5, #0x12]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_08081B26:
	ldrb r0, [r5, #0x12]
	subs r0, #1
	strb r0, [r5, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _08081B38
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_08081B38:
	adds r0, r5, #0
	bl UpdateMotionGraphic
	adds r4, r5, #0
	adds r4, #0x8c
	b _08081C3A
_08081B44:
	ldr r0, [r5, #0x5c]
	movs r4, #3
	rsbs r4, r4, #0
	adds r1, r4, #0
	bl __divsi3
	str r0, [r5, #0x5c]
	ldr r0, [r5, #0x60]
	adds r1, r4, #0
	bl __divsi3
	str r0, [r5, #0x60]
	ldr r1, [r5, #0x64]
	lsls r0, r1, #1
	adds r0, r0, r1
	str r0, [r5, #0x64]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_08081B6A:
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x5c]
	adds r0, r0, r1
	str r0, [r5, #0x54]
	ldr r0, [r5, #0x58]
	ldr r1, [r5, #0x60]
	adds r0, r0, r1
	str r0, [r5, #0x58]
	ldr r0, [r5, #0x64]
	subs r0, #1
	str r0, [r5, #0x64]
	adds r4, r5, #0
	adds r4, #0x8c
	cmp r0, #7
	bgt _08081BA6
	ldr r0, [r4]
	movs r1, #0x80
	lsls r1, r1, #4
	ands r0, r1
	cmp r0, #0
	bne _08081B14
	ldrb r0, [r5, #0x11]
	cmp r0, #0
	bne _08081BE8
	adds r0, r6, #0
	adds r0, #0xb4
	ldr r1, [r0]
	movs r2, #0x81
	rsbs r2, r2, #0
	b _08081BF0
_08081BA6:
	adds r0, r5, #0
	bl UpdateMotionGraphic
	b _08081C3A
_08081BAE:
	adds r0, r5, #0
	adds r0, #0x74
	ldr r1, _08081BE4 @ =0x083680D8
	bl SetDDP
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_08081BBE:
	adds r0, r5, #0
	adds r0, #0x8c
	ldr r1, [r0]
	movs r2, #0x80
	lsls r2, r2, #4
	ands r1, r2
	adds r4, r0, #0
	cmp r1, #0
	bne _08081C34
	ldrb r0, [r5, #0x11]
	cmp r0, #0
	bne _08081BE8
	adds r0, r6, #0
	adds r0, #0xb4
	ldr r1, [r0]
	movs r2, #0x81
	rsbs r2, r2, #0
	b _08081BF0
	.align 2, 0
_08081BE4: .4byte 0x083680D8
_08081BE8:
	adds r0, r6, #0
	adds r0, #0xb4
	ldr r1, [r0]
	ldr r2, _08081C2C @ =0xFFFFFEFF
_08081BF0:
	ands r1, r2
	str r1, [r0]
	ldrb r1, [r5, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r2, #0
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r5, #0xa]
	str r2, [r4]
	adds r0, r5, #0
	adds r0, #0x90
_08081C08:
	str r2, [r0]
	adds r0, #4
	strb r2, [r0]
	ldrb r1, [r5, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r5, #0xa]
	ldr r1, _08081C30 @ =gEnemyFnTable
	ldrb r0, [r5, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r5, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r5, #0x14]
	b _08081D22
	.align 2, 0
_08081C2C: .4byte 0xFFFFFEFF
_08081C30: .4byte gEnemyFnTable
_08081C34:
	adds r0, r5, #0
	bl UpdateMotionGraphic
_08081C3A:
	ldr r0, [r5, #0x68]
	cmp r0, #0
	beq _08081CB4
	ldr r1, [r4]
	movs r0, #0x80
	lsls r0, r0, #4
	ands r1, r0
	cmp r1, #0
	bne _08081C8C
	str r1, [r5, #0x68]
	str r1, [r4]
	adds r0, r5, #0
	adds r0, #0x90
	str r1, [r0]
	adds r0, #4
	strb r1, [r0]
	ldrb r1, [r5, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r5, #0xa]
	ldrb r0, [r5, #0x11]
	cmp r0, #0
	bne _08081C78
	ldr r1, _08081C74 @ =0x00004D05
	adds r0, r5, #0
	bl SetMotion
	b _08081C80
	.align 2, 0
_08081C74: .4byte 0x00004D05
_08081C78:
	ldr r1, _08081C88 @ =0x00004D0A
	adds r0, r5, #0
	bl SetMotion
_08081C80:
	adds r0, r5, #0
	bl UpdateMotionGraphic
	b _08081D22
	.align 2, 0
_08081C88: .4byte 0x00004D0A
_08081C8C:
	ldr r0, _08081CB0 @ =pZero2
	ldr r2, [r0]
	ldr r0, [r5, #0x54]
	str r0, [r2, #0x54]
	adds r1, r5, #0
	adds r1, #0xb8
	ldr r1, [r1]
	adds r0, r0, r1
	str r0, [r2, #0x54]
	ldr r0, [r5, #0x58]
	str r0, [r2, #0x58]
	adds r1, r5, #0
	adds r1, #0xbc
	ldr r1, [r1]
	adds r0, r0, r1
	str r0, [r2, #0x58]
	b _08081D22
	.align 2, 0
_08081CB0: .4byte pZero2
_08081CB4:
	ldr r0, [r4]
	movs r1, #0x80
	lsls r1, r1, #4
	ands r0, r1
	cmp r0, #0
	beq _08081D22
	adds r0, r5, #0
	adds r0, #0x74
	ldr r1, _08081D08 @ =0x08368060
	bl SetDDP
	adds r2, r6, #0
	adds r2, #0xb4
	ldr r0, [r2]
	movs r1, #0x40
	orrs r0, r1
	str r0, [r2]
	movs r0, #1
	str r0, [r5, #0x68]
	adds r2, r5, #0
	adds r2, #0xb8
	ldr r0, _08081D0C @ =pZero2
	ldr r3, [r0]
	ldr r0, [r3, #0x54]
	str r0, [r2]
	ldr r1, [r5, #0x54]
	subs r0, r0, r1
	str r0, [r2]
	adds r2, #4
	ldr r0, [r3, #0x58]
	str r0, [r2]
	ldr r1, [r5, #0x58]
	subs r0, r0, r1
	str r0, [r2]
	ldrb r0, [r5, #0x11]
	cmp r0, #0
	bne _08081D14
	ldr r1, _08081D10 @ =0x00004D06
	adds r0, r5, #0
	bl SetMotion
	b _08081D1C
	.align 2, 0
_08081D08: .4byte 0x08368060
_08081D0C: .4byte pZero2
_08081D10: .4byte 0x00004D06
_08081D14:
	ldr r1, _08081D28 @ =0x00004D0B
	adds r0, r5, #0
	bl SetMotion
_08081D1C:
	adds r0, r5, #0
	bl UpdateMotionGraphic
_08081D22:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_08081D28: .4byte 0x00004D0B

	thumb_func_start FUN_08081d2c
FUN_08081d2c: @ 0x08081D2C
	push {r4, r5, r6, lr}
	adds r4, r0, #0
	ldr r6, [r4, #0x28]
	ldrb r5, [r4, #0xe]
	cmp r5, #0
	beq _08081D3E
	cmp r5, #1
	beq _08081D78
	b _08081DF4
_08081D3E:
	movs r0, #0x49
	bl PlaySound
	adds r1, r4, #0
	adds r1, #0x25
	movs r0, #0xe
	strb r0, [r1]
	movs r1, #0xa0
	lsls r1, r1, #7
	adds r0, r4, #0
	bl SetMotion
	adds r0, r4, #0
	bl GetEntityPalID
	adds r1, r0, #0
	lsls r1, r1, #0x18
	lsrs r1, r1, #0x13
	movs r2, #0x80
	lsls r2, r2, #2
	adds r0, r2, #0
	orrs r1, r0
	movs r0, #0x55
	bl StartPaletteAnimation
	strb r5, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08081D78:
	ldrb r1, [r4, #0x12]
	movs r0, #3
	ands r0, r1
	adds r2, r1, #0
	cmp r0, #0
	bne _08081D8C
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
	b _08081D92
_08081D8C:
	ldrb r1, [r4, #0xa]
	movs r0, #1
	orrs r0, r1
_08081D92:
	strb r0, [r4, #0xa]
	adds r0, r2, #1
	movs r5, #0
	strb r0, [r4, #0x12]
	movs r0, #0x55
	bl StepPaletteAnimation
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r6, #0
	adds r0, #0xb4
	ldr r0, [r0]
	movs r1, #0x20
	ands r0, r1
	cmp r0, #0
	beq _08081DBA
	ldrb r0, [r6, #0xc]
	cmp r0, #1
	bls _08081DF4
_08081DBA:
	movs r0, #0x55
	bl RemovePaletteAnimation
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	adds r0, #0x8c
	str r5, [r0]
	adds r0, #4
	str r5, [r0]
	adds r0, #4
	strb r5, [r0]
	ldrb r1, [r4, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r4, #0xa]
	ldr r1, _08081DFC @ =gEnemyFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r4, #0x14]
_08081DF4:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_08081DFC: .4byte gEnemyFnTable

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

	thumb_func_start FUN_080820b8
FUN_080820b8: @ 0x080820B8
	push {r4, r5, lr}
	sub sp, #8
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _080820CA
	cmp r0, #1
	beq _08082104
	b _08082180
_080820CA:
	strb r0, [r4, #0x12]
	adds r1, r4, #0
	adds r1, #0x25
	movs r0, #0x1b
	strb r0, [r1]
	movs r2, #1
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	orrs r0, r1
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	adds r0, #0x4c
	strb r2, [r0]
	adds r3, r4, #0
	adds r3, #0x4a
	movs r2, #0x10
	ldrb r1, [r3]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	orrs r0, r2
	strb r0, [r3]
	ldr r1, _08082188 @ =0x0000270B
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08082104:
	ldrb r0, [r4, #0x12]
	cmp r0, #0
	bne _08082118
	ldr r0, [r4, #0x54]
	str r0, [sp]
	ldr r0, [r4, #0x58]
	str r0, [sp, #4]
	mov r0, sp
	bl FUN_080ba9a0
_08082118:
	ldrb r0, [r4, #0x12]
	adds r0, #1
	movs r5, #0
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0x12]
	movs r1, #0xa
	bl __umodsi3
	strb r0, [r4, #0x12]
	ldr r0, [r4, #0x54]
	movs r1, #0x90
	lsls r1, r1, #2
	adds r0, r0, r1
	str r0, [r4, #0x54]
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldr r0, _0808218C @ =gStageRun+232
	adds r1, r4, #0
	adds r1, #0x54
	bl CalcFromCamera
	movs r1, #0x80
	lsls r1, r1, #6
	cmp r0, r1
	bls _08082180
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	adds r0, #0x8c
	str r5, [r0]
	adds r0, #4
	str r5, [r0]
	adds r0, #4
	strb r5, [r0]
	ldrb r1, [r4, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r4, #0xa]
	ldr r1, _08082190 @ =gEnemyFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r4, #0x14]
_08082180:
	add sp, #8
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_08082188: .4byte 0x0000270B
_0808218C: .4byte gStageRun+232
_08082190: .4byte gEnemyFnTable
