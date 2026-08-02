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
