	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start ctrlOceanBG3Scroll
ctrlOceanBG3Scroll: @ 0x0800D31C
	push {r4, r5, r6, r7, lr}
	mov r7, sl
	mov r6, sb
	mov r5, r8
	push {r5, r6, r7}
	sub sp, #0xc
	adds r5, r0, #0
	movs r6, #0x9f
	movs r0, #0xa0
	lsls r0, r0, #2
	bl Malloc
	str r0, [sp]
	cmp r0, #0
	bne _0800D33C
	b _0800D462
_0800D33C:
	ldr r2, _0800D474 @ =gIntrManager
	movs r1, #0xba
	lsls r1, r1, #1
	adds r0, r2, r1
	ldr r3, [sp]
	str r3, [r0]
	movs r7, #0xbc
	lsls r7, r7, #1
	adds r1, r2, r7
	ldr r0, _0800D478 @ =0x0400001C
	str r0, [r1]
	movs r0, #0xbe
	lsls r0, r0, #1
	adds r1, r2, r0
	ldr r0, _0800D47C @ =0xA6600001
	str r0, [r1]
	ldr r0, [r5, #0x34]
	subs r0, #0xf0
	lsls r0, r0, #0xf
	lsrs r0, r0, #0x10
	str r0, [sp, #4]
	ldr r0, [r5, #0x38]
	subs r0, #0xc0
	lsls r0, r0, #0xf
	lsrs r0, r0, #0x10
	mov sb, r0
	mov r8, sb
	mov r1, r8
	lsls r0, r1, #0x10
	asrs r2, r0, #0x10
	adds r0, r2, #0
	adds r0, #0x9f
	cmp r0, #0x87
	ble _0800D39E
	movs r7, #0x9f
	lsls r7, r7, #2
	adds r1, r3, r7
	adds r3, r2, #0
	lsls r2, r3, #0x10
	ldr r0, [sp, #4]
	orrs r2, r0
_0800D38E:
	str r2, [r1]
	subs r1, #4
	subs r6, #1
	cmp r6, #0
	blt _0800D39E
	adds r0, r6, r3
	cmp r0, #0x87
	bgt _0800D38E
_0800D39E:
	ldr r4, [r5, #0x34]
	subs r4, #0xf0
	adds r0, r4, #0
	movs r1, #3
	bl __divsi3
	lsls r4, r4, #0xe
	ldr r1, [r5, #0x38]
	subs r1, #0xc0
	lsls r2, r1, #1
	adds r2, r2, r1
	lsls r2, r2, #5
	asrs r2, r2, #8
	adds r2, #0x10
	lsls r2, r2, #0x10
	lsls r0, r0, #0x10
	asrs r0, r0, #0x10
	mov sl, r0
	lsrs r1, r4, #0x10
	str r1, [sp, #4]
	asrs r4, r4, #0x10
	subs r4, r0, r4
	lsls r4, r4, #0xc
	lsrs r3, r2, #0x10
	mov sb, r3
	asrs r7, r2, #0x10
	mov r1, r8
	lsls r0, r1, #0x10
	asrs r0, r0, #0x10
	mov r8, r0
	subs r5, r7, r0
	adds r5, #0x10
	adds r0, r4, #0
	adds r1, r5, #0
	bl __divsi3
	str r0, [sp, #8]
	movs r0, #0x80
	lsls r0, r0, #9
	adds r1, r5, #0
	bl __divsi3
	ldr r3, _0800D480 @ =0xFFFFF000
	adds r3, r3, r0
	mov ip, r3
	cmp r6, #0
	blt _0800D462
	adds r0, r6, r7
	cmp r0, #0x77
	ble _0800D446
	mov r4, r8
	mov r8, sl
	adds r5, r7, #0
	lsls r0, r6, #2
	ldr r7, [sp]
	adds r2, r0, r7
	ldr r0, _0800D484 @ =0x0000FFFF
	mov sl, r0
	rsbs r0, r6, #0
	adds r0, #0x87
	subs r3, r0, r4
_0800D418:
	mov r1, ip
	muls r1, r3, r1
	asrs r1, r1, #0xc
	subs r1, r4, r1
	lsls r1, r1, #0x10
	ldr r7, [sp, #8]
	adds r0, r3, #0
	muls r0, r7, r0
	asrs r0, r0, #0xc
	mov r7, r8
	subs r0, r7, r0
	mov r7, sl
	ands r0, r7
	orrs r1, r0
	str r1, [r2]
	subs r2, #4
	adds r3, #1
	subs r6, #1
	cmp r6, #0
	blt _0800D462
	adds r0, r6, r5
	cmp r0, #0x77
	bgt _0800D418
_0800D446:
	cmp r6, #0
	blt _0800D462
	mov r0, sb
	lsls r2, r0, #0x10
	ldr r1, [sp, #4]
	orrs r2, r1
	lsls r0, r6, #2
	ldr r3, [sp]
	adds r0, r0, r3
_0800D458:
	str r2, [r0]
	subs r0, #4
	subs r6, #1
	cmp r6, #0
	bge _0800D458
_0800D462:
	add sp, #0xc
	pop {r3, r4, r5}
	mov r8, r3
	mov sb, r4
	mov sl, r5
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_0800D474: .4byte gIntrManager
_0800D478: .4byte 0x0400001C
_0800D47C: .4byte 0xA6600001
_0800D480: .4byte 0xFFFFF000
_0800D484: .4byte 0x0000FFFF

