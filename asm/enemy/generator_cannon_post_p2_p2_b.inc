	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start generatorcannon_0808cc08
generatorcannon_0808cc08: @ 0x0808CC08
	push {r4, r5, r6, r7, lr}
	adds r7, r0, #0
	ldrb r0, [r7, #0xe]
	cmp r0, #0
	beq _0808CC18
	cmp r0, #1
	beq _0808CCF0
	b _0808CD4E
_0808CC18:
	ldr r0, _0808CCB0 @ =gStageRun+232
	adds r1, r7, #0
	adds r1, #0x54
	bl CalcFromCamera
	ldr r1, _0808CCB4 @ =0x00003FFF
	cmp r0, r1
	bhi _0808CC30
	movs r0, #0x85
	lsls r0, r0, #1
	bl PlaySound
_0808CC30:
	adds r1, r7, #0
	adds r1, #0xb8
	movs r0, #1
	strb r0, [r1]
	subs r1, #0x93
	movs r0, #0x18
	strb r0, [r1]
	adds r0, r7, #0
	adds r0, #0x74
	ldr r1, _0808CCB8 @ =0x08368F70
	bl SetDDP
	ldr r0, _0808CCBC @ =pZero2
	ldr r1, [r0]
	ldr r5, [r1, #0x54]
	ldr r0, [r7, #0x54]
	subs r5, r5, r0
	ldr r0, [r7, #0x58]
	movs r2, #0xc0
	lsls r2, r2, #5
	adds r0, r0, r2
	ldr r6, [r1, #0x58]
	subs r6, r6, r0
	asrs r0, r5, #8
	adds r1, r0, #0
	muls r1, r0, r1
	adds r0, r1, #0
	asrs r1, r6, #8
	adds r2, r1, #0
	muls r2, r1, r2
	adds r1, r2, #0
	adds r0, r0, r1
	bl Sqrt
	adds r4, r0, #0
	lsls r4, r4, #0x10
	lsrs r4, r4, #8
	lsls r5, r5, #8
	adds r0, r5, #0
	adds r1, r4, #0
	bl __divsi3
	adds r5, r0, #0
	lsls r6, r6, #8
	adds r0, r6, #0
	adds r1, r4, #0
	bl __divsi3
	lsls r5, r5, #2
	str r5, [r7, #0x5c]
	lsls r0, r0, #2
	str r0, [r7, #0x60]
	movs r1, #0
	cmp r5, #0
	ble _0808CCA0
	movs r1, #1
_0808CCA0:
	adds r2, r1, #0
	cmp r2, #0
	beq _0808CCC0
	ldrb r0, [r7, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _0808CCC6
	.align 2, 0
_0808CCB0: .4byte gStageRun+232
_0808CCB4: .4byte 0x00003FFF
_0808CCB8: .4byte 0x08368F70
_0808CCBC: .4byte pZero2
_0808CCC0:
	ldrb r1, [r7, #0xa]
	movs r0, #0xef
	ands r0, r1
_0808CCC6:
	strb r0, [r7, #0xa]
	adds r1, r2, #0
	adds r0, r7, #0
	adds r0, #0x4c
	strb r1, [r0]
	adds r3, r7, #0
	adds r3, #0x4a
	lsls r1, r1, #4
	ldrb r2, [r3]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r1
	strb r0, [r3]
	ldr r1, _0808CD54 @ =0x00007201
	adds r0, r7, #0
	bl SetMotion
	ldrb r0, [r7, #0xe]
	adds r0, #1
	strb r0, [r7, #0xe]
_0808CCF0:
	ldr r0, [r7, #0x54]
	ldr r1, [r7, #0x5c]
	adds r0, r0, r1
	str r0, [r7, #0x54]
	ldr r0, [r7, #0x58]
	ldr r1, [r7, #0x60]
	adds r0, r0, r1
	str r0, [r7, #0x58]
	adds r0, r7, #0
	bl UpdateMotionGraphic
	ldr r0, _0808CD58 @ =gStageRun+232
	adds r1, r7, #0
	adds r1, #0x54
	bl CalcFromCamera
	movs r1, #0x80
	lsls r1, r1, #7
	cmp r0, r1
	bls _0808CD4E
	ldrb r1, [r7, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r2, #0
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r7, #0xa]
	adds r0, r7, #0
	adds r0, #0x8c
	str r2, [r0]
	adds r0, #4
	str r2, [r0]
	adds r0, #4
	strb r2, [r0]
	ldrb r1, [r7, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r7, #0xa]
	ldr r1, _0808CD5C @ =gEnemyFnTable
	ldrb r0, [r7, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r7, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r7, #0x14]
_0808CD4E:
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_0808CD54: .4byte 0x00007201
_0808CD58: .4byte gStageRun+232
_0808CD5C: .4byte gEnemyFnTable

	thumb_func_start generatorcannon_0808cd60
generatorcannon_0808cd60: @ 0x0808CD60
	push {r4, r5, r6, lr}
	adds r5, r0, #0
	ldrb r0, [r5, #0xe]
	cmp r0, #0
	beq _0808CD70
	cmp r0, #1
	beq _0808CE06
	b _0808CE46
_0808CD70:
	adds r0, r5, #0
	adds r0, #0x74
	ldr r1, _0808CDEC @ =0x083690F0
	bl SetDDP
	movs r1, #0xe4
	lsls r1, r1, #7
	adds r0, r5, #0
	bl SetMotion
	adds r0, r5, #0
	bl UpdateMotionGraphic
	ldr r0, _0808CDF0 @ =pZero2
	ldr r2, [r0]
	ldr r1, [r5, #0x54]
	ldr r0, [r2, #0x54]
	subs r1, r1, r0
	str r1, [r5, #0x5c]
	ldr r0, [r5, #0x58]
	ldr r3, _0808CDF4 @ =0xFFFFE800
	adds r0, r0, r3
	ldr r2, [r2, #0x58]
	subs r0, r0, r2
	str r0, [r5, #0x60]
	asrs r1, r1, #8
	adds r6, r1, #0
	muls r6, r1, r6
	asrs r0, r0, #8
	adds r1, r0, #0
	muls r1, r0, r1
	adds r0, r1, #0
	adds r6, r6, r0
	adds r0, r6, #0
	bl Sqrt
	lsls r0, r0, #0x10
	lsrs r6, r0, #8
	cmp r6, #0
	beq _0808CDF8
	ldr r0, [r5, #0x5c]
	lsls r0, r0, #8
	adds r1, r6, #0
	bl __divsi3
	adds r4, r0, #0
	str r4, [r5, #0x5c]
	ldr r0, [r5, #0x60]
	lsls r0, r0, #8
	adds r1, r6, #0
	bl __divsi3
	lsls r1, r4, #1
	adds r1, r1, r4
	lsls r1, r1, #1
	str r1, [r5, #0x5c]
	lsls r1, r0, #1
	adds r1, r1, r0
	lsls r1, r1, #1
	str r1, [r5, #0x60]
	b _0808CE00
	.align 2, 0
_0808CDEC: .4byte 0x083690F0
_0808CDF0: .4byte pZero2
_0808CDF4: .4byte 0xFFFFE800
_0808CDF8:
	movs r0, #0xc0
	lsls r0, r0, #3
	str r0, [r5, #0x5c]
	str r6, [r5, #0x60]
_0808CE00:
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_0808CE06:
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x5c]
	adds r0, r0, r1
	str r0, [r5, #0x54]
	ldr r0, [r5, #0x60]
	adds r0, #0x40
	str r0, [r5, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _0808CE1E
	str r1, [r5, #0x60]
_0808CE1E:
	ldr r1, [r5, #0x58]
	ldr r0, [r5, #0x60]
	adds r1, r1, r0
	str r1, [r5, #0x58]
	ldr r0, [r5, #0x54]
	bl FUN_080098a4
	lsls r0, r0, #0x10
	cmp r0, #0
	bne _0808CE40
	adds r0, r5, #0
	adds r0, #0x8c
	ldr r0, [r0]
	movs r1, #4
	ands r0, r1
	cmp r0, #0
	beq _0808CE46
_0808CE40:
	adds r0, r5, #0
	bl FUN_0808cefc
_0808CE46:
	pop {r4, r5, r6}
	pop {r0}
	bx r0

	thumb_func_start FUN_0808ce4c
FUN_0808ce4c: @ 0x0808CE4C
	push {r4, r5, lr}
	sub sp, #8
	adds r5, r0, #0
	ldrb r1, [r5, #0xb]
	movs r0, #0xf7
	ands r0, r1
	movs r1, #0
	strb r0, [r5, #0xb]
	adds r0, r5, #0
	adds r0, #0x8c
	str r1, [r0]
	adds r0, #4
	str r1, [r0]
	adds r0, #4
	strb r1, [r0]
	ldrb r1, [r5, #0xa]
	movs r0, #0xfb
	ands r0, r1
	movs r1, #0xfe
	ands r0, r1
	strb r0, [r5, #0xa]
	ldr r0, [r5, #0x54]
	str r0, [sp]
	ldr r0, [r5, #0x58]
	ldr r1, _0808CEE8 @ =0xFFFFF000
	adds r0, r0, r1
	str r0, [sp, #4]
	movs r0, #1
	mov r1, sp
	bl CreateSmoke
	movs r0, #0x2a
	bl PlaySound
	ldr r4, _0808CEEC @ =0x08369124
	adds r0, r5, #0
	mov r1, sp
	adds r2, r4, #0
	movs r3, #3
	bl FUN_080b7f70
	adds r0, r5, #0
	mov r1, sp
	adds r2, r4, #0
	movs r3, #3
	bl FUN_080b7f70
	adds r4, r5, #0
	adds r4, #0x54
	movs r0, #3
	adds r1, r4, #0
	bl TryDropItem
	ldr r2, _0808CEF0 @ =gMission
	ldrh r1, [r2, #0xc]
	ldr r0, _0808CEF4 @ =0x0000270E
	cmp r1, r0
	bhi _0808CEC4
	adds r0, r1, #1
	strh r0, [r2, #0xc]
_0808CEC4:
	adds r0, r5, #0
	adds r1, r4, #0
	bl TryDropZakoDisk
	ldr r1, _0808CEF8 @ =gEnemyFnTable
	ldrb r0, [r5, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #4
	str r1, [r5, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0x10]
	str r0, [r5, #0x14]
	add sp, #8
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_0808CEE8: .4byte 0xFFFFF000
_0808CEEC: .4byte 0x08369124
_0808CEF0: .4byte gMission
_0808CEF4: .4byte 0x0000270E
_0808CEF8: .4byte gEnemyFnTable
