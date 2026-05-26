	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start createPAquaModRubble
createPAquaModRubble: @ 0x08080804
	push {r4, lr}
	adds r4, r0, #0
	ldr r0, _08080850 @ =gEnemyHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	adds r3, r0, #0
	cmp r3, #0
	beq _0808084A
	adds r1, r3, #0
	adds r1, #0x25
	movs r2, #0
	movs r0, #0x18
	strb r0, [r1]
	ldr r0, _08080854 @ =gEnemyFnTable
	movs r1, #0x26
	strb r1, [r3, #9]
	adds r0, #0x98
	ldr r0, [r0]
	ldr r0, [r0]
	str r0, [r3, #0x14]
	movs r0, #0
	strh r2, [r3, #0x20]
	adds r1, r3, #0
	adds r1, #0x22
	strb r0, [r1]
	ldrb r1, [r3, #0xb]
	movs r0, #0x10
	orrs r0, r1
	strb r0, [r3, #0xb]
	ldrb r0, [r3, #0x1c]
	strb r0, [r3, #0x1d]
	movs r0, #8
	strb r0, [r3, #0x10]
	str r4, [r3, #0x54]
_0808084A:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_08080850: .4byte gEnemyHeaderPtr
_08080854: .4byte gEnemyFnTable

	thumb_func_start FUN_08080858
FUN_08080858: @ 0x08080858
	push {r4, lr}
	adds r4, r0, #0
	ldr r0, _080808AC @ =gEnemyHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	adds r3, r0, #0
	cmp r3, #0
	beq _080808A6
	adds r1, r3, #0
	adds r1, #0x25
	movs r2, #0
	movs r0, #0x18
	strb r0, [r1]
	ldr r0, _080808B0 @ =gEnemyFnTable
	movs r1, #0x26
	strb r1, [r3, #9]
	adds r0, #0x98
	ldr r0, [r0]
	ldr r0, [r0]
	str r0, [r3, #0x14]
	movs r0, #0
	strh r2, [r3, #0x20]
	adds r1, r3, #0
	adds r1, #0x22
	strb r0, [r1]
	ldrb r1, [r3, #0xb]
	movs r0, #0x10
	orrs r0, r1
	strb r0, [r3, #0xb]
	ldrb r0, [r3, #0x1c]
	strb r0, [r3, #0x1d]
	movs r0, #6
	strb r0, [r3, #0x10]
	ldr r0, [r4, #0x54]
	str r0, [r3, #0x54]
	ldr r0, [r4, #0x58]
	str r0, [r3, #0x58]
	str r4, [r3, #0x28]
_080808A6:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080808AC: .4byte gEnemyHeaderPtr
_080808B0: .4byte gEnemyFnTable

	thumb_func_start FUN_080808b4
FUN_080808b4: @ 0x080808B4
	push {r4, lr}
	adds r4, r0, #0
	ldr r0, _08080900 @ =gEnemyHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	adds r3, r0, #0
	cmp r3, #0
	beq _080808FA
	adds r1, r3, #0
	adds r1, #0x25
	movs r2, #0
	movs r0, #0x18
	strb r0, [r1]
	ldr r0, _08080904 @ =gEnemyFnTable
	movs r1, #0x26
	strb r1, [r3, #9]
	adds r0, #0x98
	ldr r0, [r0]
	ldr r0, [r0]
	str r0, [r3, #0x14]
	movs r0, #0
	strh r2, [r3, #0x20]
	adds r1, r3, #0
	adds r1, #0x22
	strb r0, [r1]
	ldrb r1, [r3, #0xb]
	movs r0, #0x10
	orrs r0, r1
	strb r0, [r3, #0xb]
	ldrb r0, [r3, #0x1c]
	strb r0, [r3, #0x1d]
	movs r0, #3
	strb r0, [r3, #0x10]
	str r4, [r3, #0x28]
_080808FA:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_08080900: .4byte gEnemyHeaderPtr
_08080904: .4byte gEnemyFnTable

	thumb_func_start FUN_08080908
FUN_08080908: @ 0x08080908
	push {r4, r5, lr}
	adds r5, r0, #0
	ldr r0, _0808095C @ =gEnemyHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	adds r4, r0, #0
	cmp r4, #0
	beq _08080954
	adds r1, r4, #0
	adds r1, #0x25
	movs r3, #0
	movs r0, #0x18
	strb r0, [r1]
	ldr r0, _08080960 @ =gEnemyFnTable
	movs r1, #0x26
	strb r1, [r4, #9]
	adds r0, #0x98
	ldr r0, [r0]
	ldr r0, [r0]
	str r0, [r4, #0x14]
	movs r2, #0
	strh r3, [r4, #0x20]
	adds r0, r4, #0
	adds r0, #0x22
	strb r2, [r0]
	ldrb r1, [r4, #0xb]
	movs r0, #0x10
	orrs r0, r1
	strb r0, [r4, #0xb]
	ldrb r0, [r4, #0x1c]
	strb r0, [r4, #0x1d]
	strb r2, [r4, #0x10]
	ldr r0, [r5, #0x54]
	str r0, [r4, #0x54]
	ldr r0, [r5, #0x58]
	str r0, [r4, #0x58]
	str r5, [r4, #0x28]
_08080954:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_0808095C: .4byte gEnemyHeaderPtr
_08080960: .4byte gEnemyFnTable

	thumb_func_start FUN_08080964
FUN_08080964: @ 0x08080964
	push {r4, lr}
	adds r4, r0, #0
	ldr r0, _080809B8 @ =gEnemyHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	adds r3, r0, #0
	cmp r3, #0
	beq _080809B2
	adds r1, r3, #0
	adds r1, #0x25
	movs r2, #0
	movs r0, #0x18
	strb r0, [r1]
	ldr r0, _080809BC @ =gEnemyFnTable
	movs r1, #0x26
	strb r1, [r3, #9]
	adds r0, #0x98
	ldr r0, [r0]
	ldr r0, [r0]
	str r0, [r3, #0x14]
	movs r0, #0
	strh r2, [r3, #0x20]
	adds r1, r3, #0
	adds r1, #0x22
	strb r0, [r1]
	ldrb r1, [r3, #0xb]
	movs r0, #0x10
	orrs r0, r1
	strb r0, [r3, #0xb]
	ldrb r0, [r3, #0x1c]
	strb r0, [r3, #0x1d]
	movs r0, #1
	strb r0, [r3, #0x10]
	ldr r0, [r4, #0x54]
	str r0, [r3, #0x54]
	ldr r0, [r4, #0x58]
	str r0, [r3, #0x58]
	str r4, [r3, #0x28]
_080809B2:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080809B8: .4byte gEnemyHeaderPtr
_080809BC: .4byte gEnemyFnTable

	thumb_func_start createLaserSign2
createLaserSign2: @ 0x080809C0
	push {r4, lr}
	adds r4, r0, #0
	ldr r0, _08080A1C @ =gEnemyHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	adds r3, r0, #0
	cmp r3, #0
	beq _08080A16
	adds r1, r3, #0
	adds r1, #0x25
	movs r2, #0
	movs r0, #0x18
	strb r0, [r1]
	ldr r0, _08080A20 @ =gEnemyFnTable
	movs r1, #0x26
	strb r1, [r3, #9]
	adds r0, #0x98
	ldr r0, [r0]
	ldr r0, [r0]
	str r0, [r3, #0x14]
	movs r0, #0
	strh r2, [r3, #0x20]
	adds r1, r3, #0
	adds r1, #0x22
	strb r0, [r1]
	ldrb r1, [r3, #0xb]
	movs r0, #0x10
	orrs r0, r1
	strb r0, [r3, #0xb]
	ldrb r0, [r3, #0x1c]
	strb r0, [r3, #0x1d]
	movs r0, #2
	strb r0, [r3, #0x10]
	movs r0, #1
	strb r0, [r3, #0x11]
	ldr r0, [r4, #0x54]
	str r0, [r3, #0x54]
	ldr r0, [r4, #0x58]
	ldr r1, _08080A24 @ =0xFFFFF400
	adds r0, r0, r1
	str r0, [r3, #0x58]
	str r4, [r3, #0x28]
_08080A16:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_08080A1C: .4byte gEnemyHeaderPtr
_08080A20: .4byte gEnemyFnTable
_08080A24: .4byte 0xFFFFF400

	thumb_func_start createSweepLaserSign
createSweepLaserSign: @ 0x08080A28
	push {r4, lr}
	adds r4, r0, #0
	ldr r0, _08080A84 @ =gEnemyHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	adds r3, r0, #0
	cmp r3, #0
	beq _08080A7E
	adds r1, r3, #0
	adds r1, #0x25
	movs r2, #0
	movs r0, #0x18
	strb r0, [r1]
	ldr r0, _08080A88 @ =gEnemyFnTable
	movs r1, #0x26
	strb r1, [r3, #9]
	adds r0, #0x98
	ldr r0, [r0]
	ldr r0, [r0]
	str r0, [r3, #0x14]
	movs r0, #0
	strh r2, [r3, #0x20]
	adds r1, r3, #0
	adds r1, #0x22
	strb r0, [r1]
	ldrb r1, [r3, #0xb]
	movs r0, #0x10
	orrs r0, r1
	strb r0, [r3, #0xb]
	ldrb r0, [r3, #0x1c]
	strb r0, [r3, #0x1d]
	movs r0, #2
	strb r0, [r3, #0x10]
	movs r0, #1
	strb r0, [r3, #0x11]
	ldr r0, [r4, #0x54]
	str r0, [r3, #0x54]
	ldr r0, [r4, #0x58]
	ldr r1, _08080A8C @ =0xFFFFF400
	adds r0, r0, r1
	str r0, [r3, #0x58]
	str r4, [r3, #0x28]
_08080A7E:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_08080A84: .4byte gEnemyHeaderPtr
_08080A88: .4byte gEnemyFnTable
_08080A8C: .4byte 0xFFFFF400

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

	thumb_func_start FUN_08080c64
FUN_08080c64: @ 0x08080C64
	push {r4, r5, lr}
	adds r4, r0, #0
	adds r5, r1, #0
	ldr r0, _08080CB4 @ =gEnemyHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	adds r3, r0, #0
	cmp r3, #0
	beq _08080CAE
	adds r1, r3, #0
	adds r1, #0x25
	movs r2, #0
	movs r0, #0x18
	strb r0, [r1]
	ldr r0, _08080CB8 @ =gEnemyFnTable
	movs r1, #0x26
	strb r1, [r3, #9]
	adds r0, #0x98
	ldr r0, [r0]
	ldr r0, [r0]
	str r0, [r3, #0x14]
	movs r0, #0
	strh r2, [r3, #0x20]
	adds r1, r3, #0
	adds r1, #0x22
	strb r0, [r1]
	ldrb r1, [r3, #0xb]
	movs r0, #0x10
	orrs r0, r1
	strb r0, [r3, #0xb]
	ldrb r0, [r3, #0x1c]
	strb r0, [r3, #0x1d]
	movs r0, #9
	strb r0, [r3, #0x10]
	str r4, [r3, #0x54]
	str r5, [r3, #0x58]
_08080CAE:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_08080CB4: .4byte gEnemyHeaderPtr
_08080CB8: .4byte gEnemyFnTable

	thumb_func_start FUN_08080cbc
FUN_08080cbc: @ 0x08080CBC
	push {r4, r5, r6, r7, lr}
	mov r7, sl
	mov r6, sb
	mov r5, r8
	push {r5, r6, r7}
	sub sp, #0x24
	adds r6, r1, #0
	ldr r4, [r0, #8]
	movs r5, #0xa0
	lsls r5, r5, #1
	adds r0, r5, #0
	bl Malloc
	str r0, [sp]
	cmp r0, #0
	bne _08080CDE
	b _08080E96
_08080CDE:
	movs r0, #0
	ldr r1, [sp]
	adds r2, r5, #0
	bl FillMemory
	ldr r0, [r4, #0x54]
	ldr r1, [r6, #8]
	subs r0, r0, r1
	lsls r0, r0, #8
	lsrs r0, r0, #0x10
	str r0, [sp, #4]
	ldr r0, [r4, #0x58]
	ldr r1, [r6, #0xc]
	subs r0, r0, r1
	lsls r0, r0, #8
	lsrs r0, r0, #0x10
	str r0, [sp, #8]
	movs r2, #0
	adds r4, #0xb4
	str r4, [sp, #0x1c]
_08080D06:
	lsls r2, r2, #0x10
	asrs r0, r2, #0x10
	mov sb, r0
	ldr r0, [sp, #0x1c]
	add r0, sb
	ldrb r1, [r0]
	adds r1, #0x40
	lsls r1, r1, #0x18
	lsrs r1, r1, #0x17
	ldr r3, _08080DF0 @ =gSineTable
	adds r1, r1, r3
	ldrb r0, [r0]
	lsls r0, r0, #1
	adds r0, r0, r3
	ldrh r6, [r0]
	ldrh r5, [r1]
	mov ip, r5
	movs r0, #0
	ldrsh r3, [r1, r0]
	movs r1, #1
	mov sl, r1
	str r2, [sp, #0x20]
	cmp r3, #0
	bge _08080D3A
	ldr r2, _08080DF4 @ =0x0000FFFF
	mov sl, r2
_08080D3A:
	mov r5, sl
	str r5, [sp, #0xc]
	lsls r0, r6, #0x10
	asrs r1, r0, #0x10
	movs r0, #1
	mov r8, r0
	cmp r1, #0
	bge _08080D4E
	ldr r2, _08080DF4 @ =0x0000FFFF
	mov r8, r2
_08080D4E:
	mov r5, r8
	str r5, [sp, #0x10]
	cmp r3, #0
	bge _08080D5E
	rsbs r0, r3, #0
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	mov ip, r0
_08080D5E:
	cmp r1, #0
	bge _08080D68
	rsbs r0, r1, #0
	lsls r0, r0, #0x10
	lsrs r6, r0, #0x10
_08080D68:
	mov r1, ip
	lsls r0, r1, #0x10
	asrs r5, r0, #0x10
	lsls r1, r6, #0x10
	asrs r3, r1, #0x10
	adds r2, r0, #0
	cmp r5, r3
	ble _08080DF8
	ldr r7, [sp, #4]
	ldr r4, [sp, #8]
	movs r1, #1
	ldr r5, [sp, #0xc]
	lsls r0, r5, #0x10
	mov r5, sb
	lsls r5, r5, #3
	mov sl, r5
	asrs r0, r0, #0x10
	mov sb, r0
	mov r8, r3
	asrs r6, r2, #0x10
	ldr r2, [sp, #0x10]
	lsls r0, r2, #0x10
	asrs r5, r0, #0x10
_08080D96:
	lsls r3, r7, #0x10
	cmp r1, #0
	beq _08080DB2
	lsls r0, r4, #0x10
	asrs r0, r0, #0xf
	ldr r1, [sp]
	adds r0, r0, r1
	asrs r1, r3, #0x10
	mov r2, sl
	lsls r1, r2
	ldrh r2, [r0]
	orrs r1, r2
	strh r1, [r0]
	movs r1, #0
_08080DB2:
	asrs r0, r3, #0x10
	add r0, sb
	lsls r0, r0, #0x10
	lsrs r7, r0, #0x10
	cmp r7, #0xef
	bhi _08080E60
	mov r3, ip
	lsls r0, r3, #0x10
	asrs r0, r0, #0x10
	mov r2, r8
	subs r0, r0, r2
	lsls r0, r0, #0x10
	lsrs r3, r0, #0x10
	mov ip, r3
	asrs r0, r0, #0x10
	cmp r0, #0
	bgt _08080D96
	movs r1, #1
	adds r0, r0, r6
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	mov ip, r0
	lsls r0, r4, #0x10
	asrs r0, r0, #0x10
	adds r0, r0, r5
	lsls r0, r0, #0x10
	lsrs r4, r0, #0x10
	cmp r4, #0x9f
	bls _08080D96
	b _08080E60
	.align 2, 0
_08080DF0: .4byte gSineTable
_08080DF4: .4byte 0x0000FFFF
_08080DF8:
	ldr r7, [sp, #4]
	ldr r4, [sp, #8]
	mov r2, r8
	lsls r0, r2, #0x10
	mov r3, sb
	lsls r3, r3, #3
	str r3, [sp, #0x14]
	asrs r0, r0, #0x10
	str r0, [sp, #0x18]
	mov ip, r5
	asrs r1, r1, #0x10
	mov sb, r1
	mov r5, sl
	lsls r0, r5, #0x10
	asrs r0, r0, #0x10
	mov r8, r0
_08080E18:
	lsls r2, r4, #0x10
	asrs r2, r2, #0x10
	lsls r3, r2, #1
	ldr r0, [sp]
	adds r3, r3, r0
	lsls r0, r7, #0x10
	asrs r5, r0, #0x10
	adds r0, r5, #0
	ldr r1, [sp, #0x14]
	lsls r0, r1
	ldrh r1, [r3]
	orrs r0, r1
	strh r0, [r3]
	ldr r3, [sp, #0x18]
	adds r2, r2, r3
	lsls r2, r2, #0x10
	lsrs r4, r2, #0x10
	cmp r4, #0x9f
	bhi _08080E60
	lsls r0, r6, #0x10
	asrs r0, r0, #0x10
	mov r1, ip
	subs r0, r0, r1
	lsls r0, r0, #0x10
	lsrs r6, r0, #0x10
	asrs r0, r0, #0x10
	cmp r0, #0
	bgt _08080E18
	add r0, sb
	lsls r0, r0, #0x10
	lsrs r6, r0, #0x10
	mov r2, r8
	adds r0, r5, r2
	lsls r0, r0, #0x10
	lsrs r7, r0, #0x10
	b _08080E18
_08080E60:
	ldr r3, [sp, #0x20]
	movs r5, #0x80
	lsls r5, r5, #9
	adds r0, r3, r5
	lsrs r2, r0, #0x10
	asrs r0, r0, #0x10
	cmp r0, #1
	bgt _08080E72
	b _08080D06
_08080E72:
	movs r0, #0xa0
	ldr r1, _08080EA8 @ =gWindowRegBuffer
	strh r0, [r1, #0xa]
	ldr r2, _08080EAC @ =gIntrManager
	movs r3, #0xba
	lsls r3, r3, #1
	adds r0, r2, r3
	ldr r5, [sp]
	str r5, [r0]
	movs r0, #0xbc
	lsls r0, r0, #1
	adds r1, r2, r0
	ldr r0, _08080EB0 @ =0x04000042
	str r0, [r1]
	adds r3, #8
	adds r1, r2, r3
	ldr r0, _08080EB4 @ =0xA2600001
	str r0, [r1]
_08080E96:
	add sp, #0x24
	pop {r3, r4, r5}
	mov r8, r3
	mov sb, r4
	mov sl, r5
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_08080EA8: .4byte gWindowRegBuffer
_08080EAC: .4byte gIntrManager
_08080EB0: .4byte 0x04000042
_08080EB4: .4byte 0xA2600001
