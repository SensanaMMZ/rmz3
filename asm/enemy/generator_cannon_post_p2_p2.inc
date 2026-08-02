	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start generatorcannon_0808c868
generatorcannon_0808c868: @ 0x0808C868
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _0808C878
	cmp r0, #1
	beq _0808C894
	b _0808C8CE
_0808C878:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _0808C8B4 @ =0x08369090
	bl SetDDP
	movs r0, #0x30
	strb r0, [r4, #0x12]
	ldr r1, _0808C8B8 @ =0x00007106
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0808C894:
	ldrb r0, [r4, #0x12]
	adds r5, r0, #0
	cmp r5, #0
	bne _0808C8C4
	ldr r0, _0808C8BC @ =gStageRun+232
	adds r1, r4, #0
	adds r1, #0x54
	bl CalcFromCamera
	ldr r1, _0808C8C0 @ =0x00000FFF
	cmp r0, r1
	bhi _0808C8C8
	movs r0, #2
	strb r0, [r4, #0xd]
	strb r5, [r4, #0xe]
	b _0808C8C8
	.align 2, 0
_0808C8B4: .4byte 0x08369090
_0808C8B8: .4byte 0x00007106
_0808C8BC: .4byte gStageRun+232
_0808C8C0: .4byte 0x00000FFF
_0808C8C4:
	subs r0, #1
	strb r0, [r4, #0x12]
_0808C8C8:
	adds r0, r4, #0
	bl UpdateMotionGraphic
_0808C8CE:
	pop {r4, r5}
	pop {r0}
	bx r0

	thumb_func_start generatorcannon_0808c8d4
generatorcannon_0808c8d4: @ 0x0808C8D4
	push {r4, lr}
	adds r4, r0, #0
	ldrb r1, [r4, #0xe]
	cmp r1, #0
	beq _0808C8E4
	cmp r1, #1
	beq _0808C8FA
	b _0808C95E
_0808C8E4:
	movs r0, #0x30
	strb r0, [r4, #0x12]
	strb r1, [r4, #0x13]
	movs r1, #0xe2
	lsls r1, r1, #7
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0808C8FA:
	ldrb r0, [r4, #0x12]
	movs r1, #0xc
	bl __umodsi3
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _0808C922
	ldrb r0, [r4, #0x13]
	cmp r0, #2
	bhi _0808C922
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x58]
	ldr r2, _0808C964 @ =0xFFFFF000
	adds r1, r1, r2
	ldrb r2, [r4, #0x13]
	bl CreateGeneratorCannon
	ldrb r0, [r4, #0x13]
	adds r0, #1
	strb r0, [r4, #0x13]
_0808C922:
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	lsrs r1, r0, #0x18
	cmp r1, #0
	bne _0808C936
	movs r0, #3
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_0808C936:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x74
	ldr r2, _0808C968 @ =0x0836911C
	adds r1, r4, #0
	adds r1, #0x71
	ldrb r1, [r1]
	lsls r1, r1, #0x18
	asrs r1, r1, #0x18
	adds r1, r1, r2
	ldrb r2, [r1]
	lsls r1, r2, #1
	adds r1, r1, r2
	lsls r1, r1, #3
	ldr r2, _0808C96C @ =0x08368F58
	adds r1, r1, r2
	bl SetDDP
_0808C95E:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_0808C964: .4byte 0xFFFFF000
_0808C968: .4byte 0x0836911C
_0808C96C: .4byte 0x08368F58

	thumb_func_start generatorcannon_0808c970
generatorcannon_0808c970: @ 0x0808C970
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #1
	beq _0808C99C
	cmp r0, #1
	bgt _0808C984
	cmp r0, #0
	beq _0808C98E
	b _0808CA1A
_0808C984:
	cmp r0, #2
	beq _0808C9E4
	cmp r0, #3
	beq _0808CA00
	b _0808CA1A
_0808C98E:
	ldr r1, _0808C9D8 @ =0x00007101
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0808C99C:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	adds r0, r4, #0
	adds r0, #0x73
	ldrb r0, [r0]
	cmp r0, #3
	bne _0808C9B2
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0808C9B2:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r2, _0808C9DC @ =0x08369120
	adds r1, r4, #0
	adds r1, #0x71
	ldrb r1, [r1]
	lsls r1, r1, #0x18
	asrs r1, r1, #0x18
	adds r1, r1, r2
	ldrb r2, [r1]
	lsls r1, r2, #1
	adds r1, r1, r2
	lsls r1, r1, #3
	ldr r2, _0808C9E0 @ =0x08368F58
	adds r1, r1, r2
	bl SetDDP
	b _0808CA1A
	.align 2, 0
_0808C9D8: .4byte 0x00007101
_0808C9DC: .4byte 0x08369120
_0808C9E0: .4byte 0x08368F58
_0808C9E4:
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _0808CA20 @ =0x08369090
	bl SetDDP
	movs r0, #0x50
	strb r0, [r4, #0x12]
	ldr r1, _0808CA24 @ =0x00007106
	adds r0, r4, #0
	bl SetMotion
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_0808CA00:
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	lsrs r1, r0, #0x18
	cmp r1, #0
	bne _0808CA14
	movs r0, #4
	strb r0, [r4, #0xd]
	strb r1, [r4, #0xe]
_0808CA14:
	adds r0, r4, #0
	bl UpdateMotionGraphic
_0808CA1A:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_0808CA20: .4byte 0x08369090
_0808CA24: .4byte 0x00007106
