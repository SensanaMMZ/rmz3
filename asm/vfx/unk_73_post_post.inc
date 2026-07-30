	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080c6f60
FUN_080c6f60: @ 0x080C6F60
	push {r4, r5, r6, r7, lr}
	mov r7, sb
	mov r6, r8
	push {r6, r7}
	adds r5, r0, #0
	ldr r0, [r5, #0x28]
	mov r8, r0
	movs r1, #0x54
	add r1, r8
	mov sb, r1
	ldrb r0, [r0, #0xa]
	lsls r0, r0, #0x18
	lsrs r4, r0, #0x1c
	movs r1, #1
	ands r4, r1
	lsrs r6, r0, #0x1d
	ands r6, r1
	ldrb r1, [r5, #0xa]
	movs r0, #1
	movs r7, #0
	orrs r0, r1
	strb r0, [r5, #0xa]
	adds r0, r5, #0
	bl InitNonAffineMotion
	ldr r1, _080C6FA8 @ =0x0000DC06
	adds r0, r5, #0
	bl SetMotion
	cmp r4, #0
	beq _080C6FAC
	ldrb r0, [r5, #0xa]
	movs r1, #0x10
	orrs r0, r1
	b _080C6FB2
	.align 2, 0
_080C6FA8: .4byte 0x0000DC06
_080C6FAC:
	ldrb r1, [r5, #0xa]
	movs r0, #0xef
	ands r0, r1
_080C6FB2:
	strb r0, [r5, #0xa]
	adds r1, r4, #0
	adds r0, r5, #0
	adds r0, #0x4c
	strb r1, [r0]
	adds r2, r5, #0
	adds r2, #0x4a
	lsls r1, r1, #4
	ldrb r3, [r2]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r3
	orrs r0, r1
	strb r0, [r2]
	adds r3, r6, #0
	adds r4, r2, #0
	cmp r3, #0
	beq _080C6FDE
	ldrb r0, [r5, #0xa]
	movs r1, #0x20
	orrs r0, r1
	b _080C6FE4
_080C6FDE:
	ldrb r1, [r5, #0xa]
	movs r0, #0xdf
	ands r0, r1
_080C6FE4:
	strb r0, [r5, #0xa]
	movs r6, #1
	adds r1, r6, #0
	ands r1, r3
	adds r0, r5, #0
	adds r0, #0x4d
	strb r1, [r0]
	lsls r1, r1, #5
	ldrb r2, [r4]
	movs r0, #0x21
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r1
	strb r0, [r4]
	mov r2, sb
	ldr r0, [r2]
	str r0, [r5, #0x54]
	ldr r0, [r2, #4]
	str r0, [r5, #0x58]
	mov r1, r8
	ldr r0, [r1, #0x5c]
	str r0, [r5, #0x5c]
	movs r1, #0
	mov r2, r8
	ldrb r0, [r2, #0xf]
	subs r0, #1
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #1
	bhi _080C7022
	movs r1, #1
_080C7022:
	strb r1, [r5, #0x13]
	movs r0, #0
	cmp r1, #0
	beq _080C702E
	mov r1, r8
	ldr r0, [r1, #0x60]
_080C702E:
	str r0, [r5, #0x60]
	movs r0, #0x16
	strb r0, [r5, #0x12]
	ldr r1, _080C7058 @ =gVFXFnTable
	ldrb r0, [r5, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	str r6, [r5, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r5, #0x14]
	adds r0, r5, #0
	bl Ghost73_Update
	pop {r3, r4}
	mov r8, r3
	mov sb, r4
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080C7058: .4byte gVFXFnTable

	thumb_func_start FUN_080c705c
FUN_080c705c: @ 0x080C705C
	push {r4, r5, lr}
	adds r5, r0, #0
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x5c]
	adds r0, r0, r1
	str r0, [r5, #0x54]
	movs r0, #0xf5
	muls r0, r1, r0
	cmp r0, #0
	bge _080C7072
	adds r0, #0xff
_080C7072:
	asrs r0, r0, #8
	str r0, [r5, #0x5c]
	ldr r0, [r5, #0x58]
	ldr r1, [r5, #0x60]
	adds r0, r0, r1
	str r0, [r5, #0x58]
	ldrb r0, [r5, #0x13]
	cmp r0, #0
	beq _080C7094
	adds r0, r1, #0
	adds r0, #0x20
	str r0, [r5, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _080C7094
	str r1, [r5, #0x60]
_080C7094:
	adds r0, r5, #0
	bl UpdateMotionGraphic
	ldrb r0, [r5, #0x12]
	subs r0, #1
	strb r0, [r5, #0x12]
	ldrb r0, [r5, #0x13]
	cmp r0, #0
	beq _080C70D8
	ldr r4, [r5, #0x54]
	ldr r2, [r5, #0x58]
	ldr r0, _080C70D4 @ =0xFFFFFE00
	adds r3, r2, r0
	ldrb r1, [r5, #0xa]
	movs r0, #0x20
	ands r0, r1
	cmp r0, #0
	beq _080C70BE
	movs r0, #0x80
	lsls r0, r0, #2
	adds r3, r2, r0
_080C70BE:
	adds r0, r4, #0
	adds r1, r3, #0
	bl FUN_080098a4
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _080C70EA
	movs r0, #0
	strb r0, [r5, #0x12]
	b _080C70EA
	.align 2, 0
_080C70D4: .4byte 0xFFFFFE00
_080C70D8:
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x58]
	bl FUN_08009f6c
	adds r1, r0, #0
	ldr r0, [r5, #0x58]
	cmp r0, r1
	ble _080C70EA
	str r1, [r5, #0x58]
_080C70EA:
	ldrb r0, [r5, #0x12]
	cmp r0, #0
	bne _080C7116
	ldr r0, [r5, #0x28]
	adds r4, r5, #0
	adds r4, #0x54
	adds r1, r4, #0
	bl FUN_080c6e70
	movs r0, #1
	adds r1, r4, #0
	bl CreateSmoke
	ldr r1, _080C711C @ =gVFXFnTable
	ldrb r0, [r5, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #2
	str r1, [r5, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #8]
	str r0, [r5, #0x14]
_080C7116:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080C711C: .4byte gVFXFnTable
