	.include "asm/macros.inc"

	.syntax unified

	.text


	thumb_func_start createStretchedGrabArm
createStretchedGrabArm: @ 0x08080A90
	push {r4, r5, r6, r7, lr}
	mov r7, sl
	mov r6, sb
	mov r5, r8
	push {r5, r6, r7}
	mov r8, r0
	lsls r1, r1, #0x18
	lsrs r6, r1, #0x18
	ldr r0, _08080B68 @ =gEnemyHeaderPtr
	ldr r0, [r0]
	bl AllocEntityLast
	adds r4, r0, #0
	cmp r4, #0
	beq _08080B06
	adds r1, r4, #0
	adds r1, #0x25
	movs r2, #0
	movs r0, #0x18
	strb r0, [r1]
	ldr r0, _08080B6C @ =gEnemyFnTable
	movs r1, #0x26
	strb r1, [r4, #9]
	adds r0, #0x98
	ldr r0, [r0]
	ldr r0, [r0]
	str r0, [r4, #0x14]
	movs r0, #0
	strh r2, [r4, #0x20]
	adds r1, r4, #0
	adds r1, #0x22
	strb r0, [r1]
	ldrb r1, [r4, #0xb]
	movs r0, #0x10
	orrs r0, r1
	strb r0, [r4, #0xb]
	ldrb r0, [r4, #0x1c]
	strb r0, [r4, #0x1d]
	movs r0, #5
	strb r0, [r4, #0x10]
	strb r6, [r4, #0x11]
	mov r0, r8
	ldr r1, [r0, #0x54]
	ldr r0, _08080B70 @ =0xFFFFE900
	adds r1, r1, r0
	lsls r0, r6, #1
	adds r0, r0, r6
	lsls r0, r0, #3
	subs r0, r0, r6
	lsls r0, r0, #9
	adds r1, r1, r0
	str r1, [r4, #0x54]
	mov r1, r8
	ldr r0, [r1, #0x58]
	ldr r1, _08080B74 @ =0xFFFFFC00
	adds r0, r0, r1
	str r0, [r4, #0x58]
	mov r0, r8
	str r0, [r4, #0x28]
_08080B06:
	movs r5, #0
	movs r7, #0
	ldr r0, _08080B78 @ =0x083659E0
	mov sb, r0
_08080B0E:
	ldr r0, _08080B68 @ =gEnemyHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	adds r2, r0, #0
	adds r3, r5, #1
	cmp r2, #0
	beq _08080B54
	adds r1, r2, #0
	adds r1, #0x25
	movs r0, #0x18
	strb r0, [r1]
	movs r0, #0x26
	strb r0, [r2, #9]
	mov r1, sb
	ldr r0, [r1]
	ldr r0, [r0]
	str r0, [r2, #0x14]
	strh r7, [r2, #0x20]
	adds r0, r2, #0
	adds r0, #0x22
	strb r7, [r0]
	ldrb r0, [r2, #0xb]
	movs r1, #0x10
	orrs r0, r1
	strb r0, [r2, #0xb]
	ldrb r0, [r2, #0x1c]
	strb r0, [r2, #0x1d]
	movs r0, #4
	strb r0, [r2, #0x10]
	strb r6, [r2, #0x11]
	mov r0, r8
	str r0, [r2, #0x28]
	str r4, [r2, #0x2c]
	strb r3, [r2, #0x12]
_08080B54:
	adds r5, r3, #0
	cmp r5, #5
	ble _08080B0E
	pop {r3, r4, r5}
	mov r8, r3
	mov sb, r4
	mov sl, r5
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_08080B68: .4byte gEnemyHeaderPtr
_08080B6C: .4byte gEnemyFnTable
_08080B70: .4byte 0xFFFFE900
_08080B74: .4byte 0xFFFFFC00
_08080B78: .4byte 0x083659E0

	thumb_func_start createStretchedArms
createStretchedArms: @ 0x08080B7C
	push {r4, r5, r6, r7, lr}
	mov r7, sl
	mov r6, sb
	mov r5, r8
	push {r5, r6, r7}
	adds r7, r0, #0
	movs r6, #0
_08080B8A:
	ldr r0, _08080C58 @ =gEnemyHeaderPtr
	ldr r0, [r0]
	bl AllocEntityLast
	adds r4, r0, #0
	cmp r4, #0
	beq _08080BEA
	adds r1, r4, #0
	adds r1, #0x25
	movs r0, #0x18
	strb r0, [r1]
	movs r0, #0x26
	strb r0, [r4, #9]
	ldr r1, _08080C5C @ =0x083659E0
	ldr r0, [r1]
	ldr r0, [r0]
	str r0, [r4, #0x14]
	movs r0, #0
	strh r0, [r4, #0x20]
	adds r0, r4, #0
	adds r0, #0x22
	movs r1, #0
	strb r1, [r0]
	ldrb r0, [r4, #0xb]
	movs r1, #0x10
	orrs r0, r1
	strb r0, [r4, #0xb]
	ldrb r0, [r4, #0x1c]
	strb r0, [r4, #0x1d]
	movs r0, #7
	strb r0, [r4, #0x10]
	strb r6, [r4, #0x11]
	ldr r1, [r7, #0x54]
	ldr r0, _08080C60 @ =0xFFFFE900
	adds r1, r1, r0
	lsls r0, r6, #1
	adds r0, r0, r6
	lsls r0, r0, #3
	subs r0, r0, r6
	lsls r0, r0, #9
	adds r1, r1, r0
	str r1, [r4, #0x54]
	ldr r0, [r7, #0x58]
	movs r1, #0x80
	lsls r1, r1, #3
	adds r0, r0, r1
	str r0, [r4, #0x58]
	str r7, [r4, #0x28]
_08080BEA:
	movs r5, #0
	adds r0, r6, #1
	mov sb, r0
	mov r8, r5
	ldr r1, _08080C5C @ =0x083659E0
	mov sl, r1
_08080BF6:
	ldr r0, _08080C58 @ =gEnemyHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	adds r2, r0, #0
	adds r3, r5, #1
	cmp r2, #0
	beq _08080C3E
	adds r1, r2, #0
	adds r1, #0x25
	movs r0, #0x18
	strb r0, [r1]
	movs r0, #0x26
	strb r0, [r2, #9]
	mov r1, sl
	ldr r0, [r1]
	ldr r0, [r0]
	str r0, [r2, #0x14]
	mov r0, r8
	strh r0, [r2, #0x20]
	adds r0, r2, #0
	adds r0, #0x22
	mov r1, r8
	strb r1, [r0]
	ldrb r0, [r2, #0xb]
	movs r1, #0x10
	orrs r0, r1
	strb r0, [r2, #0xb]
	ldrb r0, [r2, #0x1c]
	strb r0, [r2, #0x1d]
	movs r0, #4
	strb r0, [r2, #0x10]
	strb r6, [r2, #0x11]
	str r7, [r2, #0x28]
	str r4, [r2, #0x2c]
	strb r3, [r2, #0x12]
_08080C3E:
	adds r5, r3, #0
	cmp r5, #5
	ble _08080BF6
	mov r6, sb
	cmp r6, #1
	ble _08080B8A
	pop {r3, r4, r5}
	mov r8, r3
	mov sb, r4
	mov sl, r5
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_08080C58: .4byte gEnemyHeaderPtr
_08080C5C: .4byte 0x083659E0
_08080C60: .4byte 0xFFFFE900
