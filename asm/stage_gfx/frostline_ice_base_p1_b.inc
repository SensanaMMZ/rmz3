	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_0801126c
FUN_0801126c: @ 0x0801126C
	push {r4, r5, r6, r7, lr}
	mov r7, sb
	mov r6, r8
	push {r6, r7}
	mov sb, r0
	movs r0, #0xa0
	lsls r0, r0, #2
	bl Malloc
	adds r7, r0, #0
	cmp r7, #0
	bne _08011286
	b _080113B8
_08011286:
	ldr r2, _080113C4 @ =gIntrManager
	movs r1, #0xba
	lsls r1, r1, #1
	adds r0, r2, r1
	str r7, [r0]
	movs r0, #0xbc
	lsls r0, r0, #1
	adds r1, r2, r0
	ldr r0, _080113C8 @ =0x0400001C
	str r0, [r1]
	movs r0, #0xbe
	lsls r0, r0, #1
	adds r1, r2, r0
	ldr r0, _080113CC @ =0xA6600001
	str r0, [r1]
	mov r1, sb
	ldr r0, [r1, #0x34]
	movs r1, #3
	bl __divsi3
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	mov r8, r0
	mov r1, sb
	ldr r0, [r1, #0x38]
	subs r0, #0xe0
	movs r1, #3
	bl __divsi3
	adds r0, #1
	movs r2, #0
	lsls r0, r0, #0x10
	asrs r0, r0, #0x10
	cmp r0, #0x8b
	bgt _080112E4
	adds r4, r7, #0
	adds r3, r0, #0
	lsls r1, r3, #0x10
	mov r0, r8
	orrs r1, r0
_080112D6:
	stm r4!, {r1}
	adds r2, #1
	cmp r2, #0x9f
	bgt _080112E4
	adds r0, r3, r2
	cmp r0, #0x8b
	ble _080112D6
_080112E4:
	mov r1, sb
	ldr r0, [r1, #0x34]
	lsls r0, r0, #0xf
	lsrs r0, r0, #0x10
	mov r8, r0
	ldr r0, [r1, #0x38]
	ldr r1, _080113D0 @ =0xFFFFFEA0
	adds r0, r0, r1
	asrs r0, r0, #1
	adds r0, #3
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	cmp r2, #0x9f
	bgt _08011352
	lsls r0, r0, #0x10
	asrs r3, r0, #0x10
	adds r1, r3, r2
	adds r5, r0, #0
	cmp r1, #0x8f
	bgt _0801132C
	adds r4, r3, #0
	lsls r0, r2, #0x10
	movs r1, #0x90
	lsls r1, r1, #0x10
	subs r1, r1, r0
	lsls r0, r2, #2
	adds r3, r0, r7
	ldr r6, _080113D4 @ =0xFFFF0000
_0801131C:
	stm r3!, {r1}
	adds r1, r1, r6
	adds r2, #1
	cmp r2, #0x9f
	bgt _08011352
	adds r0, r4, r2
	cmp r0, #0x8f
	ble _0801131C
_0801132C:
	cmp r2, #0x9f
	bgt _08011352
	asrs r1, r5, #0x10
	adds r0, r1, r2
	cmp r0, #0xe0
	bgt _08011352
	lsls r0, r2, #2
	adds r4, r0, r7
	adds r3, r1, #0
	lsls r1, r3, #0x10
	mov r0, r8
	orrs r1, r0
_08011344:
	stm r4!, {r1}
	adds r2, #1
	cmp r2, #0x9f
	bgt _08011352
	adds r0, r3, r2
	cmp r0, #0xe0
	ble _08011344
_08011352:
	mov r0, sb
	ldr r1, [r0, #0x34]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #0xe
	lsrs r0, r0, #0x10
	mov r8, r0
	mov r0, sb
	ldr r1, [r0, #0x38]
	ldr r0, _080113D8 @ =0xFFFFFE20
	adds r1, r1, r0
	lsls r0, r1, #1
	adds r0, r0, r1
	asrs r0, r0, #2
	adds r0, #5
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	cmp r2, #0x9f
	bgt _080113B8
	lsls r0, r0, #0x10
	asrs r3, r0, #0x10
	adds r1, r3, r2
	adds r5, r0, #0
	cmp r1, #0xdf
	bgt _080113A4
	adds r4, r3, #0
	lsls r0, r2, #0x10
	movs r1, #0xf0
	lsls r1, r1, #0x10
	subs r1, r1, r0
	lsls r0, r2, #2
	adds r3, r0, r7
	ldr r6, _080113D4 @ =0xFFFF0000
_08011394:
	stm r3!, {r1}
	adds r1, r1, r6
	adds r2, #1
	cmp r2, #0x9f
	bgt _080113B8
	adds r0, r4, r2
	cmp r0, #0xdf
	ble _08011394
_080113A4:
	cmp r2, #0x9f
	bgt _080113B8
	mov r1, r8
	orrs r1, r5
	lsls r0, r2, #2
	adds r0, r0, r7
_080113B0:
	stm r0!, {r1}
	adds r2, #1
	cmp r2, #0x9f
	ble _080113B0
_080113B8:
	pop {r3, r4}
	mov r8, r3
	mov sb, r4
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080113C4: .4byte gIntrManager
_080113C8: .4byte 0x0400001C
_080113CC: .4byte 0xA6600001
_080113D0: .4byte 0xFFFFFEA0
_080113D4: .4byte 0xFFFF0000
_080113D8: .4byte 0xFFFFFE20

