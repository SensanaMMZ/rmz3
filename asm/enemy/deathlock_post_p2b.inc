	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_0808db64
FUN_0808db64: @ 0x0808DB64
	push {r4, r5, r6, r7, lr}
	mov r7, sb
	mov r6, r8
	push {r6, r7}
	sub sp, #8
	adds r7, r0, #0
	ldrb r0, [r7, #0xe]
	cmp r0, #0
	beq _0808DB7C
	cmp r0, #1
	beq _0808DBC8
	b _0808DD4E
_0808DB7C:
	ldr r0, [r7, #0x54]
	str r0, [r7, #0x64]
	ldr r1, _0808DBA0 @ =0x08369300
	adds r4, r7, #0
	adds r4, #0xb9
	ldrb r0, [r4]
	lsls r0, r0, #1
	adds r0, r0, r1
	ldrh r1, [r0]
	adds r0, r7, #0
	bl SetMotion
	ldrb r0, [r4]
	cmp r0, #0
	bne _0808DBA4
	movs r0, #8
	b _0808DBA6
	.align 2, 0
_0808DBA0: .4byte 0x08369300
_0808DBA4:
	movs r0, #0x18
_0808DBA6:
	strb r0, [r7, #0x12]
	adds r0, r7, #0
	adds r0, #0x74
	ldr r2, _0808DC14 @ =0x0836930C
	ldrb r1, [r4]
	adds r1, r1, r2
	ldrb r2, [r1]
	lsls r1, r2, #1
	adds r1, r1, r2
	lsls r1, r1, #3
	ldr r2, _0808DC18 @ =sCollisions
	adds r1, r1, r2
	bl SetDDP
	ldrb r0, [r7, #0xe]
	adds r0, #1
	strb r0, [r7, #0xe]
_0808DBC8:
	ldr r0, [r7, #0x54]
	ldr r1, _0808DC1C @ =0xFFFFEE00
	adds r0, r0, r1
	ldr r1, [r7, #0x58]
	movs r2, #0x80
	lsls r2, r2, #3
	adds r1, r1, r2
	bl FUN_0800a40c
	adds r1, r0, #0
	cmp r1, #0
	bne _0808DBF6
	ldr r0, [r7, #0x54]
	movs r3, #0x90
	lsls r3, r3, #5
	adds r0, r0, r3
	ldr r1, [r7, #0x58]
	movs r2, #0x80
	lsls r2, r2, #3
	adds r1, r1, r2
	bl FUN_0800a40c
	adds r1, r0, #0
_0808DBF6:
	ldr r0, [r7, #0x64]
	str r0, [r7, #0x54]
	cmp r1, #0
	beq _0808DC0A
	adds r0, r7, #0
	bl FUN_0808d160
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _0808DC20
_0808DC0A:
	movs r1, #0
	movs r0, #1
	strb r0, [r7, #0xd]
	strb r1, [r7, #0xe]
	b _0808DC40
	.align 2, 0
_0808DC14: .4byte 0x0836930C
_0808DC18: .4byte sCollisions
_0808DC1C: .4byte 0xFFFFEE00
_0808DC20:
	ldr r2, [r7, #0x54]
	ldr r3, _0808DD5C @ =0xFFFFFE00
	adds r2, r2, r3
	ldr r3, _0808DD60 @ =RNG_0202f388
	ldr r1, [r3]
	ldr r0, _0808DD64 @ =0x000343FD
	muls r0, r1, r0
	ldr r1, _0808DD68 @ =0x00269EC3
	adds r0, r0, r1
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r3]
	lsls r0, r0, #5
	lsrs r0, r0, #0x16
	adds r2, r2, r0
	str r2, [r7, #0x54]
_0808DC40:
	ldrb r0, [r7, #0x12]
	movs r1, #7
	bl __umodsi3
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _0808DC94
	ldr r1, [r7, #0x54]
	ldr r2, _0808DD6C @ =0xFFFFF000
	mov r8, r2
	add r1, r8
	ldr r3, _0808DD60 @ =RNG_0202f388
	mov sb, r3
	ldr r0, [r3]
	ldr r6, _0808DD64 @ =0x000343FD
	muls r0, r6, r0
	ldr r3, _0808DD68 @ =0x00269EC3
	adds r0, r0, r3
	lsls r0, r0, #1
	lsrs r4, r0, #1
	lsrs r0, r0, #0x11
	ldr r5, _0808DD70 @ =0x00001FFF
	ands r0, r5
	adds r0, r0, r1
	str r0, [sp]
	ldr r2, [r7, #0x58]
	add r2, r8
	adds r0, r4, #0
	muls r0, r6, r0
	adds r0, r0, r3
	lsls r0, r0, #1
	lsrs r1, r0, #1
	mov r3, sb
	str r1, [r3]
	lsrs r0, r0, #0x11
	ands r0, r5
	adds r0, r0, r2
	str r0, [sp, #4]
	movs r0, #3
	mov r1, sp
	bl CreateSmoke
_0808DC94:
	adds r0, r7, #0
	bl UpdateMotionGraphic
	ldrb r0, [r7, #0x12]
	subs r0, #1
	strb r0, [r7, #0x12]
	lsls r0, r0, #0x18
	lsrs r6, r0, #0x18
	cmp r6, #0
	bne _0808DD06
	movs r0, #0x56
	bl PlaySound
	ldr r0, [r7, #0x54]
	ldr r1, [r7, #0x58]
	adds r5, r7, #0
	adds r5, #0xb9
	ldrb r2, [r5]
	ldrb r3, [r7, #0xa]
	lsrs r3, r3, #4
	movs r4, #1
	ands r3, r4
	bl CreateGhost65
	ldrb r0, [r5]
	adds r0, #1
	strb r0, [r5]
	strb r6, [r7, #0xe]
	ldrb r0, [r5]
	cmp r0, #5
	bls _0808DD06
	ldrb r1, [r7, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r7, #0xa]
	adds r0, r7, #0
	adds r0, #0x8c
	str r6, [r0]
	adds r0, #4
	str r6, [r0]
	adds r0, #4
	strb r6, [r0]
	ldrb r1, [r7, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r7, #0xa]
	ldr r1, _0808DD74 @ =gEnemyFnTable
	ldrb r0, [r7, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r7, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r7, #0x14]
_0808DD06:
	ldr r0, _0808DD78 @ =gStageRun+232
	adds r1, r7, #0
	adds r1, #0x54
	bl CalcFromCamera
	movs r1, #0xc0
	lsls r1, r1, #7
	cmp r0, r1
	bls _0808DD4E
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
	ldr r1, _0808DD74 @ =gEnemyFnTable
	ldrb r0, [r7, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r7, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r7, #0x14]
_0808DD4E:
	add sp, #8
	pop {r3, r4}
	mov r8, r3
	mov sb, r4
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_0808DD5C: .4byte 0xFFFFFE00
_0808DD60: .4byte RNG_0202f388
_0808DD64: .4byte 0x000343FD
_0808DD68: .4byte 0x00269EC3
_0808DD6C: .4byte 0xFFFFF000
_0808DD70: .4byte 0x00001FFF
_0808DD74: .4byte gEnemyFnTable
_0808DD78: .4byte gStageRun+232
