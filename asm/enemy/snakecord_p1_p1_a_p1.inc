	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_08073ea8
FUN_08073ea8: @ 0x08073EA8
	push {r4, lr}
	adds r4, r0, #0
	cmp r1, #0
	beq _08073EE6
	ldr r0, [r4, #0x54]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	cmp r1, #0
	bge _08073ED0
	ldr r1, [r4, #0x58]
	bl PushoutToRight2
	adds r1, r0, #0
	cmp r1, #0
	ble _08073EE6
	ldr r0, [r4, #0x54]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	movs r0, #2
	b _08073EE8
_08073ED0:
	ldr r1, [r4, #0x58]
	bl PushoutToLeft2
	adds r1, r0, #0
	cmp r1, #0
	bge _08073EE6
	ldr r0, [r4, #0x54]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	movs r0, #1
	b _08073EE8
_08073EE6:
	movs r0, #0
_08073EE8:
	pop {r4}
	pop {r1}
	bx r1
	.align 2, 0

	thumb_func_start FUN_08073ef0
FUN_08073ef0: @ 0x08073EF0
	push {r4, lr}
	adds r4, r0, #0
	cmp r1, #0
	beq _08073F32
	ldr r0, [r4, #0x58]
	adds r2, r0, r1
	str r2, [r4, #0x58]
	cmp r1, #0
	bge _08073F1A
	ldr r0, [r4, #0x54]
	adds r1, r2, #0
	bl PushoutToDown2
	adds r1, r0, #0
	cmp r1, #0
	ble _08073F32
	ldr r0, [r4, #0x58]
	adds r0, r0, r1
	str r0, [r4, #0x58]
	movs r0, #2
	b _08073F34
_08073F1A:
	ldr r0, [r4, #0x54]
	adds r1, r2, #0
	bl PushoutToUp2
	adds r1, r0, #0
	cmp r1, #0
	bge _08073F32
	ldr r0, [r4, #0x58]
	adds r0, r0, r1
	str r0, [r4, #0x58]
	movs r0, #1
	b _08073F34
_08073F32:
	movs r0, #0
_08073F34:
	pop {r4}
	pop {r1}
	bx r1
	.align 2, 0

	thumb_func_start FUN_08073f3c
FUN_08073f3c: @ 0x08073F3C
	push {r4, r5, r6, r7, lr}
	mov r7, sl
	mov r6, sb
	mov r5, r8
	push {r5, r6, r7}
	adds r4, r0, #0
	mov sb, r4
	cmp r4, #0
	beq _08073F8A
_08073F4E:
	ldr r0, [r4, #0x60]
	adds r2, r0, #0
	adds r2, #0x40
	str r2, [r4, #0x60]
	ldrb r0, [r4, #0x12]
	cmp r0, #0
	beq _08073F84
	mov r1, sb
	ldrb r0, [r1, #0xd]
	cmp r0, #1
	bne _08073F74
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	ldr r0, [r4, #0x58]
	adds r0, r0, r2
	str r0, [r4, #0x58]
	b _08073F84
_08073F74:
	ldr r1, [r4, #0x5c]
	adds r0, r4, #0
	bl FUN_08073ea8
	ldr r1, [r4, #0x60]
	adds r0, r4, #0
	bl FUN_08073ef0
_08073F84:
	ldr r4, [r4, #0x28]
	cmp r4, #0
	bne _08073F4E
_08073F8A:
	mov r4, sb
	ldr r0, [r4, #0x28]
	mov r8, r0
	movs r1, #0
	mov sl, r1
	cmp r0, #0
	bne _08073F9A
	b _0807409C
_08073F9A:
	mov r0, r8
	ldr r1, [r0, #0x54]
	ldr r0, [r4, #0x54]
	subs r5, r1, r0
	mov r0, r8
	ldr r1, [r0, #0x58]
	ldr r0, [r4, #0x58]
	subs r7, r1, r0
	lsls r0, r5, #0x10
	asrs r0, r0, #0x10
	lsls r1, r7, #0x10
	asrs r1, r1, #0x10
	bl ArcTan2
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x18
	adds r0, #0x40
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	adds r2, r0, #0
	mov r1, sl
	cmp r1, #0
	bne _08073FD2
	adds r1, r0, #0
	adds r1, #0xc0
	adds r0, r4, #0
	adds r0, #0x24
	strb r1, [r0]
_08073FD2:
	mov r0, r8
	adds r0, #0x24
	strb r2, [r0]
	adds r0, r5, #0
	muls r0, r5, r0
	adds r1, r7, #0
	muls r1, r7, r1
	adds r0, r0, r1
	bl Sqrt
	lsls r0, r0, #0x10
	lsrs r6, r0, #0x10
	cmp r6, #0
	beq _08074084
	lsls r0, r5, #8
	adds r1, r6, #0
	bl __divsi3
	adds r5, r0, #0
	lsls r0, r7, #8
	adds r1, r6, #0
	bl __divsi3
	adds r7, r0, #0
	ldr r0, _08074058 @ =0xFFFFF200
	adds r1, r6, r0
	lsls r0, r1, #2
	adds r0, r0, r1
	lsls r0, r0, #5
	cmp r0, #0
	bge _08074012
	adds r0, #0xff
_08074012:
	asrs r1, r0, #8
	adds r0, r5, #0
	muls r0, r1, r0
	cmp r0, #0
	bge _0807401E
	adds r0, #0xff
_0807401E:
	asrs r5, r0, #8
	adds r0, r7, #0
	muls r0, r1, r0
	cmp r0, #0
	bge _0807402A
	adds r0, #0xff
_0807402A:
	asrs r7, r0, #8
	mov r1, sb
	ldrb r0, [r1, #0xd]
	cmp r0, #1
	bne _0807405C
	ldr r0, [r4, #0x54]
	adds r0, r0, r5
	str r0, [r4, #0x54]
	ldr r0, [r4, #0x58]
	adds r0, r0, r7
	str r0, [r4, #0x58]
	mov r1, r8
	ldrb r0, [r1, #0x12]
	cmp r0, #0
	beq _08074084
	ldr r0, [r1, #0x54]
	subs r0, r0, r5
	str r0, [r1, #0x54]
	ldr r0, [r1, #0x58]
	subs r0, r0, r7
	str r0, [r1, #0x58]
	b _08074084
	.align 2, 0
_08074058: .4byte 0xFFFFF200
_0807405C:
	adds r0, r4, #0
	adds r1, r5, #0
	bl FUN_08073ea8
	adds r0, r4, #0
	adds r1, r7, #0
	bl FUN_08073ef0
	mov r1, r8
	ldrb r0, [r1, #0x12]
	cmp r0, #0
	beq _08074084
	rsbs r1, r5, #0
	mov r0, r8
	bl FUN_08073ea8
	rsbs r1, r7, #0
	mov r0, r8
	bl FUN_08073ef0
_08074084:
	mov r4, r8
	ldr r0, [r4, #0x28]
	mov r8, r0
	mov r0, sl
	adds r0, #1
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	mov sl, r0
	mov r1, r8
	cmp r1, #0
	beq _0807409C
	b _08073F9A
_0807409C:
	mov r4, sb
	cmp r4, #0
	beq _080740D6
	movs r6, #0xfe
_080740A4:
	ldr r2, [r4, #0x54]
	ldr r0, [r4, #0x64]
	subs r5, r2, r0
	ldr r1, [r4, #0x58]
	ldr r0, [r4, #0x68]
	subs r7, r1, r0
	adds r0, r5, #0
	muls r0, r6, r0
	cmp r0, #0
	bge _080740BA
	adds r0, #0xff
_080740BA:
	asrs r0, r0, #8
	str r0, [r4, #0x5c]
	adds r0, r7, #0
	muls r0, r6, r0
	cmp r0, #0
	bge _080740C8
	adds r0, #0xff
_080740C8:
	asrs r0, r0, #8
	str r0, [r4, #0x60]
	str r2, [r4, #0x64]
	str r1, [r4, #0x68]
	ldr r4, [r4, #0x28]
	cmp r4, #0
	bne _080740A4
_080740D6:
	pop {r3, r4, r5}
	mov r8, r3
	mov sb, r4
	mov sl, r5
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0

	thumb_func_start FUN_080740e4
FUN_080740e4: @ 0x080740E4
	push {r4, lr}
	adds r2, r0, #0
	b _080740EC
_080740EA:
	ldr r2, [r2, #0x28]
_080740EC:
	ldr r0, [r2, #0x28]
	cmp r0, #0
	bne _080740EA
	cmp r2, #0
	beq _0807412A
	ldr r4, _08074130 @ =gEnemyFnTable
	movs r3, #0
_080740FA:
	ldrb r0, [r2, #0x12]
	cmp r0, #1
	bhi _08074118
	ldrb r1, [r2, #9]
	lsls r1, r1, #2
	adds r1, r1, r4
	movs r0, #2
	str r0, [r2, #0xc]
	ldr r0, [r1]
	ldr r0, [r0, #8]
	str r0, [r2, #0x14]
	movs r0, #1
	strb r0, [r2, #0xd]
	ldr r0, [r2, #0x2c]
	str r3, [r0, #0x28]
_08074118:
	ldrb r1, [r2, #0x10]
	cmp r1, #0
	bne _08074124
	movs r0, #3
	strb r0, [r2, #0xd]
	strb r1, [r2, #0xe]
_08074124:
	ldr r2, [r2, #0x2c]
	cmp r2, #0
	bne _080740FA
_0807412A:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_08074130: .4byte gEnemyFnTable
