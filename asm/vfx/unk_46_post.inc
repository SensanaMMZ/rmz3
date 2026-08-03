	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080bef44
FUN_080bef44: @ 0x080BEF44
	push {r4, r5, r6, r7, lr}
	mov r7, sb
	mov r6, r8
	push {r6, r7}
	adds r7, r0, #0
	ldrb r0, [r7, #0x12]
	subs r0, #1
	strb r0, [r7, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _080BEF7A
	ldr r0, [r7, #0x54]
	ldr r1, [r7, #0x58]
	bl FUN_080098a4
	lsls r0, r0, #0x10
	lsrs r1, r0, #0x10
	cmp r1, #0
	beq _080BEF9C
	movs r0, #0x80
	lsls r0, r0, #8
	ands r0, r1
	cmp r0, #0
	bne _080BEF9C
	ldr r0, [r7, #0x60]
	cmp r0, #0
	ble _080BEF9C
_080BEF7A:
	adds r1, r7, #0
	adds r1, #0x54
	movs r0, #2
	bl CreateSmoke
	ldr r1, _080BEF98 @ =gVFXFnTable
	ldrb r0, [r7, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r7, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r7, #0x14]
	b _080BF092
	.align 2, 0
_080BEF98: .4byte gVFXFnTable
_080BEF9C:
	ldrb r6, [r7, #0xe]
	cmp r6, #0
	beq _080BEFA8
	cmp r6, #1
	beq _080BF032
	b _080BF092
_080BEFA8:
	ldr r4, _080BF050 @ =0x0836F0CC
	movs r0, #0x74
	adds r0, r0, r7
	mov r8, r0
	ldrh r0, [r0]
	movs r1, #5
	bl __umodsi3
	lsls r0, r0, #0x10
	lsrs r0, r0, #0xe
	adds r0, r0, r4
	ldr r0, [r0]
	ldr r2, [r7, #0x78]
	lsls r2, r2, #3
	adds r2, r2, r0
	ldr r4, _080BF054 @ =RNG_0202f388
	ldr r0, [r4]
	ldr r1, _080BF058 @ =0x000343FD
	mov sb, r1
	mov r1, sb
	muls r1, r0, r1
	ldr r5, _080BF05C @ =0x00269EC3
	adds r1, r1, r5
	lsls r1, r1, #1
	lsrs r3, r1, #1
	str r3, [r4]
	lsrs r1, r1, #0x11
	movs r0, #0xff
	ands r1, r0
	ldr r0, [r2, #4]
	subs r0, r0, r1
	str r0, [r7, #0x60]
	ldr r2, [r2]
	ldr r0, _080BF060 @ =0xFFFFFE80
	adds r2, r2, r0
	mov r0, sb
	muls r0, r3, r0
	adds r0, r0, r5
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r4]
	lsls r0, r0, #6
	lsrs r0, r0, #0x17
	adds r2, r2, r0
	str r2, [r7, #0x5c]
	mov r0, r8
	ldrh r1, [r0]
	adds r0, r7, #0
	bl SetMotion
	movs r0, #0x5a
	strb r0, [r7, #0x12]
	strb r6, [r7, #0x13]
	ldr r0, [r4]
	mov r1, sb
	muls r1, r0, r1
	adds r0, r1, #0
	adds r0, r0, r5
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r4]
	lsrs r0, r0, #0x11
	movs r1, #7
	ands r0, r1
	adds r0, #0x1e
	str r0, [r7, #0x64]
	ldrb r0, [r7, #0xe]
	adds r0, #1
	strb r0, [r7, #0xe]
_080BF032:
	ldrb r0, [r7, #0x13]
	adds r0, #1
	strb r0, [r7, #0x13]
	ldrb r1, [r7, #0x13]
	ldr r0, [r7, #0x64]
	cmp r1, r0
	ble _080BF06C
	movs r0, #1
	ands r1, r0
	cmp r1, #0
	beq _080BF064
	ldrb r0, [r7, #0xa]
	movs r1, #1
	orrs r0, r1
	b _080BF06A
	.align 2, 0
_080BF050: .4byte 0x0836F0CC
_080BF054: .4byte RNG_0202f388
_080BF058: .4byte 0x000343FD
_080BF05C: .4byte 0x00269EC3
_080BF060: .4byte 0xFFFFFE80
_080BF064:
	ldrb r1, [r7, #0xa]
	movs r0, #0xfe
	ands r0, r1
_080BF06A:
	strb r0, [r7, #0xa]
_080BF06C:
	ldr r0, [r7, #0x60]
	adds r0, #0x20
	str r0, [r7, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _080BF07C
	str r1, [r7, #0x60]
_080BF07C:
	ldr r0, [r7, #0x58]
	ldr r1, [r7, #0x60]
	adds r0, r0, r1
	str r0, [r7, #0x58]
	ldr r0, [r7, #0x54]
	ldr r1, [r7, #0x5c]
	adds r0, r0, r1
	str r0, [r7, #0x54]
	adds r0, r7, #0
	bl UpdateMotionGraphic
_080BF092:
	pop {r3, r4}
	mov r8, r3
	mov sb, r4
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
