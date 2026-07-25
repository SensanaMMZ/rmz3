	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start snowyplains_0801326c
snowyplains_0801326c: @ 0x0801326C
	push {r4, r5, r6, r7, lr}
	mov r7, r8
	push {r7}
	mov r8, r0
	movs r4, #0x9f
	movs r0, #0xa0
	lsls r0, r0, #2
	bl Malloc
	adds r6, r0, #0
	cmp r6, #0
	bne _08013286
	b _08013396
_08013286:
	ldr r2, _080133A0 @ =gIntrManager
	movs r1, #0xba
	lsls r1, r1, #1
	adds r0, r2, r1
	str r6, [r0]
	movs r0, #0xbc
	lsls r0, r0, #1
	adds r1, r2, r0
	ldr r0, _080133A4 @ =0x0400001C
	str r0, [r1]
	movs r0, #0xbe
	lsls r0, r0, #1
	adds r1, r2, r0
	ldr r0, _080133A8 @ =0xA6600001
	str r0, [r1]
	mov r1, r8
	ldr r0, [r1, #0x34]
	lsls r0, r0, #0xe
	lsrs r5, r0, #0x10
	ldr r0, [r1, #0x38]
	ldr r2, _080133AC @ =0xFFFFFCE0
	adds r0, r0, r2
	asrs r0, r0, #5
	subs r0, #0x20
	lsls r0, r0, #0x10
	lsrs r1, r0, #0x10
	mov ip, r1
	asrs r1, r0, #0x10
	adds r0, r1, #0
	adds r0, #0x9f
	cmp r0, #0x4f
	ble _080132E6
	adds r3, r1, #0
	ldr r2, _080133B0 @ =0xFFB00000
	movs r0, #0x9f
	lsls r0, r0, #2
	adds r1, r6, r0
	movs r7, #0x80
	lsls r7, r7, #9
_080132D4:
	str r2, [r1]
	adds r2, r2, r7
	subs r1, #4
	subs r4, #1
	cmp r4, #0
	blt _08013310
	adds r0, r3, r4
	cmp r0, #0x4f
	bgt _080132D4
_080132E6:
	cmp r4, #0
	blt _08013310
	mov r1, ip
	lsls r0, r1, #0x10
	asrs r2, r0, #0x10
	adds r0, r2, r4
	cmp r0, #0x2f
	ble _08013310
	lsls r0, r4, #2
	adds r1, r0, r6
	adds r3, r2, #0
	lsls r2, r3, #0x10
	orrs r2, r5
_08013300:
	str r2, [r1]
	subs r1, #4
	subs r4, #1
	cmp r4, #0
	blt _08013310
	adds r0, r3, r4
	cmp r0, #0x2f
	bgt _08013300
_08013310:
	mov r2, r8
	ldr r0, [r2, #0x34]
	lsls r0, r0, #0xd
	lsrs r5, r0, #0x10
	cmp r4, #0
	blt _08013342
	mov r1, ip
	lsls r0, r1, #0x10
	asrs r2, r0, #0x10
	adds r0, r2, r4
	cmp r0, #0x27
	ble _08013342
	lsls r0, r4, #2
	adds r1, r0, r6
	adds r3, r2, #0
	lsls r2, r3, #0x10
	orrs r2, r5
_08013332:
	str r2, [r1]
	subs r1, #4
	subs r4, #1
	cmp r4, #0
	blt _08013342
	adds r0, r3, r4
	cmp r0, #0x27
	bgt _08013332
_08013342:
	mov r2, r8
	ldr r0, [r2, #0x34]
	lsls r0, r0, #0xc
	lsrs r5, r0, #0x10
	cmp r4, #0
	blt _08013396
	mov r1, ip
	lsls r0, r1, #0x10
	asrs r2, r0, #0x10
	adds r0, r2, r4
	cmp r0, #0x1f
	ble _08013374
	lsls r0, r4, #2
	adds r1, r0, r6
	adds r3, r2, #0
	lsls r2, r3, #0x10
	orrs r2, r5
_08013364:
	str r2, [r1]
	subs r1, #4
	subs r4, #1
	cmp r4, #0
	blt _08013396
	adds r0, r3, r4
	cmp r0, #0x1f
	bgt _08013364
_08013374:
	cmp r4, #0
	blt _08013396
	lsls r0, r4, #0x10
	rsbs r0, r0, #0
	movs r2, #0x80
	lsls r2, r2, #0xd
	adds r1, r0, r2
	lsls r0, r4, #2
	adds r0, r0, r6
	movs r2, #0x80
	lsls r2, r2, #9
_0801338A:
	str r1, [r0]
	adds r1, r1, r2
	subs r0, #4
	subs r4, #1
	cmp r4, #0
	bge _0801338A
_08013396:
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080133A0: .4byte gIntrManager
_080133A4: .4byte 0x0400001C
_080133A8: .4byte 0xA6600001
_080133AC: .4byte 0xFFFFFCE0
_080133B0: .4byte 0xFFB00000

