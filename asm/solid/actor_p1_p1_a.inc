	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start Actor8_Update
Actor8_Update: @ 0x080D1748
	push {r4, r5, r6, r7, lr}
	mov r7, sb
	mov r6, r8
	push {r6, r7}
	sub sp, #0x10
	adds r7, r0, #0
	ldrb r0, [r7, #0xd]
	cmp r0, #4
	bls _080D175C
	b _080D1CD8
_080D175C:
	lsls r0, r0, #2
	ldr r1, _080D1768 @ =_080D176C
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_080D1768: .4byte _080D176C
_080D176C: @ jump table
	.4byte _080D1780 @ case 0
	.4byte _080D1A60 @ case 1
	.4byte _080D1ADA @ case 2
	.4byte _080D1B8C @ case 3
	.4byte _080D1C1E @ case 4
_080D1780:
	adds r0, r7, #0
	bl UpdateMotionGraphic
	ldrb r0, [r7, #0x11]
	cmp r0, #0
	bne _080D17CC
	ldrb r0, [r7, #0x12]
	subs r0, #1
	strb r0, [r7, #0x12]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0xff
	bne _080D17CC
	ldr r2, _080D1908 @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _080D190C @ =0x000343FD
	muls r0, r1, r0
	ldr r1, _080D1910 @ =0x00269EC3
	adds r0, r0, r1
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r2]
	lsrs r0, r0, #0x11
	movs r1, #0x7f
	ands r0, r1
	adds r0, #0x1e
	strb r0, [r7, #0x12]
	ldr r2, [r7, #0x54]
	ldr r3, _080D1914 @ =0xFFFFF000
	adds r2, r2, r3
	ldr r3, [r7, #0x68]
	movs r4, #0x80
	lsls r4, r4, #4
	adds r3, r3, r4
	movs r0, #1
	movs r1, #0
	bl FUN_080c5628
_080D17CC:
	ldr r0, [r7, #0x64]
	ldr r1, [r7, #0x68]
	bl FUN_080098a4
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _080D17DC
	b _080D1CD8
_080D17DC:
	ldrb r0, [r7, #0xa]
	movs r1, #1
	orrs r1, r0
	strb r1, [r7, #0xa]
	ldrb r0, [r7, #0x11]
	cmp r0, #0
	beq _080D17EC
	b _080D1920
_080D17EC:
	adds r1, r7, #0
	adds r1, #0x54
	movs r0, #4
	bl AppendQuake
	ldr r4, _080D1918 @ =0x0000011D
	adds r0, r4, #0
	bl isSoundPlaying
	cmp r0, #0
	bne _080D1808
	adds r0, r4, #0
	bl PlaySound
_080D1808:
	ldr r0, [r7, #0x54]
	ldr r1, _080D1914 @ =0xFFFFF000
	mov sb, r1
	add r0, sb
	str r0, [sp, #8]
	ldr r0, [r7, #0x68]
	ldr r2, _080D191C @ =0xFFFFFE00
	adds r0, r0, r2
	str r0, [sp, #0xc]
	movs r0, #3
	add r1, sp, #8
	bl CreateSmoke
	ldr r0, [r7, #0x68]
	movs r4, #0x80
	lsls r4, r4, #4
	adds r0, r0, r4
	str r0, [sp, #0xc]
	movs r0, #3
	add r1, sp, #8
	bl CreateSmoke
	ldr r2, [r7, #0x54]
	add r2, sb
	ldr r3, [r7, #0x68]
	adds r3, r3, r4
	mov ip, r3
	ldr r3, _080D1908 @ =RNG_0202f388
	mov r8, r3
	ldr r0, [r3]
	ldr r6, _080D190C @ =0x000343FD
	muls r0, r6, r0
	ldr r4, _080D1910 @ =0x00269EC3
	adds r0, r0, r4
	lsls r0, r0, #1
	lsrs r1, r0, #1
	lsrs r0, r0, #0x11
	movs r5, #7
	ands r0, r5
	subs r0, #4
	lsls r0, r0, #7
	str r0, [sp]
	adds r0, r1, #0
	muls r0, r6, r0
	adds r0, r0, r4
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r3]
	lsrs r0, r0, #0x11
	ands r0, r5
	rsbs r0, r0, #0
	lsls r0, r0, #7
	str r0, [sp, #4]
	movs r0, #1
	movs r1, #3
	mov r3, ip
	bl FUN_080c5684
	ldr r2, [r7, #0x54]
	add r2, sb
	ldr r3, [r7, #0x68]
	movs r0, #0x80
	lsls r0, r0, #3
	adds r0, r0, r3
	mov ip, r0
	mov r1, r8
	ldr r0, [r1]
	muls r0, r6, r0
	adds r0, r0, r4
	lsls r0, r0, #1
	lsrs r1, r0, #1
	lsrs r0, r0, #0x11
	ands r0, r5
	subs r0, #4
	lsls r0, r0, #7
	str r0, [sp]
	adds r0, r1, #0
	muls r0, r6, r0
	adds r0, r0, r4
	lsls r0, r0, #1
	lsrs r1, r0, #1
	mov r3, r8
	str r1, [r3]
	lsrs r0, r0, #0x11
	ands r0, r5
	rsbs r0, r0, #0
	lsls r0, r0, #7
	str r0, [sp, #4]
	movs r0, #1
	movs r1, #5
	mov r3, ip
	bl FUN_080c5684
	ldr r2, [r7, #0x54]
	add r2, sb
	ldr r3, [r7, #0x68]
	mov r1, r8
	ldr r0, [r1]
	muls r0, r6, r0
	adds r0, r0, r4
	lsls r0, r0, #1
	lsrs r1, r0, #1
	lsrs r0, r0, #0x11
	ands r0, r5
	subs r0, #4
	lsls r0, r0, #7
	str r0, [sp]
	adds r0, r1, #0
	muls r0, r6, r0
	adds r0, r0, r4
	lsls r0, r0, #1
	lsrs r1, r0, #1
	mov r4, r8
	str r1, [r4]
	lsrs r0, r0, #0x11
	ands r0, r5
	rsbs r0, r0, #0
	lsls r0, r0, #7
	str r0, [sp, #4]
	movs r0, #1
	movs r1, #4
	bl FUN_080c5684
	ldrb r0, [r7, #0xd]
	adds r0, #1
	strb r0, [r7, #0xd]
	b _080D1CD8
	.align 2, 0
_080D1908: .4byte RNG_0202f388
_080D190C: .4byte 0x000343FD
_080D1910: .4byte 0x00269EC3
_080D1914: .4byte 0xFFFFF000
_080D1918: .4byte 0x0000011D
_080D191C: .4byte 0xFFFFFE00
_080D1920:
	adds r1, r7, #0
	adds r1, #0x54
	movs r0, #0x10
	bl AppendQuake
	movs r0, #0x41
	bl PlaySound
	ldr r0, [r7, #0x54]
	ldr r1, _080D1A4C @ =0xFFFFF000
	adds r0, r0, r1
	str r0, [sp, #8]
	ldr r0, [r7, #0x58]
	str r0, [sp, #0xc]
	movs r0, #3
	add r1, sp, #8
	bl CreateSmoke
	ldr r0, [r7, #0x54]
	ldr r2, _080D1A50 @ =0xFFFFF800
	mov sb, r2
	add r0, sb
	str r0, [sp, #8]
	ldr r0, [r7, #0x58]
	movs r3, #0x80
	lsls r3, r3, #5
	adds r0, r0, r3
	str r0, [sp, #0xc]
	movs r0, #3
	add r1, sp, #8
	bl CreateSmoke
	ldrb r0, [r7, #0x11]
	cmp r0, #2
	bne _080D1976
	ldr r0, [r7, #0x54]
	str r0, [sp, #8]
	ldr r0, [r7, #0x68]
	str r0, [sp, #0xc]
	movs r0, #1
	add r1, sp, #8
	bl CreateSmoke
_080D1976:
	ldr r2, [r7, #0x54]
	ldr r4, _080D1A4C @ =0xFFFFF000
	adds r2, r2, r4
	ldr r3, [r7, #0x68]
	add r3, sb
	mov ip, r3
	ldr r0, _080D1A54 @ =RNG_0202f388
	mov r8, r0
	ldr r0, [r0]
	ldr r6, _080D1A58 @ =0x000343FD
	muls r0, r6, r0
	ldr r4, _080D1A5C @ =0x00269EC3
	adds r0, r0, r4
	lsls r0, r0, #1
	lsrs r1, r0, #1
	lsrs r0, r0, #0x11
	movs r5, #7
	ands r0, r5
	subs r0, #6
	lsls r0, r0, #8
	str r0, [sp]
	adds r0, r1, #0
	muls r0, r6, r0
	adds r0, r0, r4
	lsls r0, r0, #1
	lsrs r1, r0, #1
	mov r3, r8
	str r1, [r3]
	lsrs r0, r0, #0x11
	ands r0, r5
	rsbs r0, r0, #0
	lsls r0, r0, #7
	str r0, [sp, #4]
	movs r0, #1
	movs r1, #3
	mov r3, ip
	bl FUN_080c5684
	ldr r2, [r7, #0x54]
	add r2, sb
	ldr r3, [r7, #0x68]
	add r3, sb
	mov ip, r3
	mov r1, r8
	ldr r0, [r1]
	muls r0, r6, r0
	adds r0, r0, r4
	lsls r0, r0, #1
	lsrs r1, r0, #1
	lsrs r0, r0, #0x11
	ands r0, r5
	subs r0, #6
	lsls r0, r0, #8
	str r0, [sp]
	adds r0, r1, #0
	muls r0, r6, r0
	adds r0, r0, r4
	lsls r0, r0, #1
	lsrs r1, r0, #1
	mov r3, r8
	str r1, [r3]
	lsrs r0, r0, #0x11
	ands r0, r5
	rsbs r0, r0, #0
	lsls r0, r0, #7
	str r0, [sp, #4]
	movs r0, #1
	movs r1, #5
	mov r3, ip
	bl FUN_080c5684
	ldr r2, [r7, #0x54]
	add r2, sb
	ldr r3, [r7, #0x68]
	movs r0, #0x80
	lsls r0, r0, #4
	adds r3, r3, r0
	mov r1, r8
	ldr r0, [r1]
	muls r0, r6, r0
	adds r0, r0, r4
	lsls r0, r0, #1
	lsrs r1, r0, #1
	lsrs r0, r0, #0x11
	ands r0, r5
	subs r0, #6
	lsls r0, r0, #8
	str r0, [sp]
	adds r0, r1, #0
	muls r0, r6, r0
	adds r0, r0, r4
	lsls r0, r0, #1
	lsrs r1, r0, #1
	mov r4, r8
	str r1, [r4]
	lsrs r0, r0, #0x11
	ands r0, r5
	rsbs r0, r0, #0
	lsls r0, r0, #7
	str r0, [sp, #4]
	movs r0, #1
	movs r1, #4
	bl FUN_080c5684
	movs r0, #3
	strb r0, [r7, #0xd]
	b _080D1CD8
	.align 2, 0
_080D1A4C: .4byte 0xFFFFF000
_080D1A50: .4byte 0xFFFFF800
_080D1A54: .4byte RNG_0202f388
_080D1A58: .4byte 0x000343FD
_080D1A5C: .4byte 0x00269EC3
_080D1A60:
	ldr r0, [r7, #0x54]
	str r0, [sp, #8]
	ldr r1, [r7, #0x58]
	movs r2, #0x80
	lsls r2, r2, #5
	adds r1, r1, r2
	str r1, [sp, #0xc]
	bl PushoutToUp2
	cmp r0, #0
	beq _080D1ADA
	ldr r0, [r7, #0x54]
	ldr r3, _080D1AF8 @ =0xFFFFF800
	adds r0, r0, r3
	str r0, [sp, #8]
	ldr r0, [r7, #0x58]
	movs r4, #0x80
	lsls r4, r4, #5
	adds r0, r0, r4
	str r0, [sp, #0xc]
	movs r0, #3
	add r1, sp, #8
	bl CreateSmoke
	ldr r0, [sp, #8]
	adds r0, r0, r4
	str r0, [sp, #8]
	movs r0, #3
	add r1, sp, #8
	bl CreateSmoke
	movs r0, #0x41
	bl isSoundPlaying
	cmp r0, #0
	bne _080D1AAE
	movs r0, #0x41
	bl PlaySound
_080D1AAE:
	adds r0, r7, #0
	adds r0, #0x8c
	movs r4, #0
	str r4, [r0]
	adds r0, #4
	str r4, [r0]
	adds r0, #4
	strb r4, [r0]
	ldrb r1, [r7, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r7, #0xa]
	str r4, [r7, #0x60]
	adds r1, r7, #0
	adds r1, #0x54
	movs r0, #2
	bl AppendQuake
	strb r4, [r7, #0x13]
	ldrb r0, [r7, #0xd]
	adds r0, #1
	strb r0, [r7, #0xd]
_080D1ADA:
	ldrb r0, [r7, #0xd]
	cmp r0, #2
	bne _080D1B0C
	ldrb r1, [r7, #0x13]
	adds r0, r1, #1
	strb r0, [r7, #0x13]
	movs r0, #1
	ands r0, r1
	cmp r0, #0
	beq _080D1AFC
	ldrb r1, [r7, #0xa]
	movs r0, #0xfe
	ands r0, r1
	b _080D1B02
	.align 2, 0
_080D1AF8: .4byte 0xFFFFF800
_080D1AFC:
	ldrb r0, [r7, #0xa]
	movs r1, #1
	orrs r0, r1
_080D1B02:
	strb r0, [r7, #0xa]
	ldr r0, [r7, #0x54]
	ldr r1, [r7, #0x5c]
	adds r0, r0, r1
	str r0, [r7, #0x54]
_080D1B0C:
	adds r0, r7, #0
	bl UpdateMotionGraphic
	ldr r1, [r7, #0x60]
	ldr r0, _080D1B80 @ =0x000006FF
	cmp r1, r0
	bgt _080D1B20
	adds r0, r1, #0
	adds r0, #0x2a
	str r0, [r7, #0x60]
_080D1B20:
	ldr r1, [r7, #0x60]
	cmp r1, #0
	ble _080D1B2C
	ldr r0, [r7, #0x58]
	adds r0, r0, r1
	str r0, [r7, #0x58]
_080D1B2C:
	ldr r0, _080D1B84 @ =gStageRun+232
	adds r1, r7, #0
	adds r1, #0x54
	bl CalcFromCamera
	movs r1, #0xc0
	lsls r1, r1, #6
	cmp r0, r1
	bls _080D1B78
	ldrb r1, [r7, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r1, #0
	strb r0, [r7, #0xa]
	adds r0, r7, #0
	adds r0, #0x8c
	str r1, [r0]
	adds r0, #4
	str r1, [r0]
	adds r0, #4
	strb r1, [r0]
	ldrb r1, [r7, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r7, #0xa]
	ldrb r1, [r7, #0xb]
	movs r0, #0xf7
	ands r0, r1
	strb r0, [r7, #0xb]
	ldr r1, _080D1B88 @ =gSolidFnTable
	ldrb r0, [r7, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #4
	str r1, [r7, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0x10]
	str r0, [r7, #0x14]
_080D1B78:
	adds r0, r7, #0
	bl UpdateMotionGraphic
	b _080D1CD8
	.align 2, 0
_080D1B80: .4byte 0x000006FF
_080D1B84: .4byte gStageRun+232
_080D1B88: .4byte gSolidFnTable
_080D1B8C:
	ldr r0, [r7, #0x54]
	str r0, [sp, #8]
	ldr r1, [r7, #0x58]
	movs r2, #0x80
	lsls r2, r2, #4
	adds r1, r1, r2
	str r1, [sp, #0xc]
	bl PushoutToUp2
	cmp r0, #0
	beq _080D1C1E
	ldr r0, [r7, #0x54]
	ldr r3, _080D1C3C @ =0xFFFFF800
	adds r0, r0, r3
	str r0, [sp, #8]
	ldr r0, [r7, #0x58]
	movs r4, #0x80
	lsls r4, r4, #5
	adds r0, r0, r4
	str r0, [sp, #0xc]
	movs r0, #3
	add r1, sp, #8
	bl CreateSmoke
	ldr r0, [sp, #8]
	adds r0, r0, r4
	str r0, [sp, #8]
	movs r0, #3
	add r1, sp, #8
	bl CreateSmoke
	adds r0, r7, #0
	adds r0, #0x8c
	movs r4, #0
	str r4, [r0]
	adds r0, #4
	str r4, [r0]
	adds r0, #4
	strb r4, [r0]
	ldrb r1, [r7, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r7, #0xa]
	ldr r0, [r7, #0x60]
	rsbs r0, r0, #0
	asrs r0, r0, #1
	str r0, [r7, #0x60]
	ldr r0, [r7, #0x5c]
	asrs r0, r0, #1
	str r0, [r7, #0x5c]
	ldr r2, _080D1C40 @ =RNG_0202f388
	ldr r1, [r2]
	ldr r0, _080D1C44 @ =0x000343FD
	muls r0, r1, r0
	ldr r1, _080D1C48 @ =0x00269EC3
	adds r0, r0, r1
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r2]
	lsrs r0, r0, #0x11
	movs r1, #0xf
	ands r0, r1
	subs r0, #7
	strb r0, [r7, #0x12]
	adds r1, r7, #0
	adds r1, #0x54
	movs r0, #2
	bl AppendQuake
	strb r4, [r7, #0x13]
	ldrb r0, [r7, #0xd]
	adds r0, #1
	strb r0, [r7, #0xd]
_080D1C1E:
	ldrb r0, [r7, #0xd]
	cmp r0, #4
	bne _080D1C54
	ldrb r1, [r7, #0x13]
	adds r0, r1, #1
	strb r0, [r7, #0x13]
	movs r0, #1
	ands r0, r1
	cmp r0, #0
	beq _080D1C4C
	ldrb r1, [r7, #0xa]
	movs r0, #0xfe
	ands r0, r1
	b _080D1C52
	.align 2, 0
_080D1C3C: .4byte 0xFFFFF800
_080D1C40: .4byte RNG_0202f388
_080D1C44: .4byte 0x000343FD
_080D1C48: .4byte 0x00269EC3
_080D1C4C:
	ldrb r0, [r7, #0xa]
	movs r1, #1
	orrs r0, r1
_080D1C52:
	strb r0, [r7, #0xa]
_080D1C54:
	adds r0, r7, #0
	bl UpdateMotionGraphic
	ldr r1, [r7, #0x60]
	ldr r0, _080D1CE8 @ =0x000006FF
	cmp r1, r0
	bgt _080D1C68
	adds r0, r1, #0
	adds r0, #0x2a
	str r0, [r7, #0x60]
_080D1C68:
	ldr r1, [r7, #0x60]
	cmp r1, #0
	ble _080D1C74
	ldr r0, [r7, #0x58]
	adds r0, r0, r1
	str r0, [r7, #0x58]
_080D1C74:
	ldr r0, [r7, #0x54]
	ldr r1, [r7, #0x5c]
	adds r0, r0, r1
	str r0, [r7, #0x54]
	adds r1, r7, #0
	adds r1, #0x24
	ldrb r0, [r7, #0x12]
	ldrb r2, [r1]
	adds r0, r0, r2
	movs r4, #0
	strb r0, [r1]
	ldr r0, _080D1CEC @ =gStageRun+232
	adds r1, #0x30
	bl CalcFromCamera
	movs r1, #0xc0
	lsls r1, r1, #6
	cmp r0, r1
	bls _080D1CD2
	ldrb r1, [r7, #0xa]
	movs r0, #0xfe
	ands r0, r1
	strb r0, [r7, #0xa]
	adds r0, r7, #0
	adds r0, #0x8c
	str r4, [r0]
	adds r0, #4
	str r4, [r0]
	adds r0, #4
	strb r4, [r0]
	ldrb r1, [r7, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r7, #0xa]
	ldrb r1, [r7, #0xb]
	movs r0, #0xf7
	ands r0, r1
	strb r0, [r7, #0xb]
	ldr r1, _080D1CF0 @ =gSolidFnTable
	ldrb r0, [r7, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #4
	str r1, [r7, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0x10]
	str r0, [r7, #0x14]
_080D1CD2:
	adds r0, r7, #0
	bl UpdateMotionGraphic
_080D1CD8:
	add sp, #0x10
	pop {r3, r4}
	mov r8, r3
	mov sb, r4
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080D1CE8: .4byte 0x000006FF
_080D1CEC: .4byte gStageRun+232
_080D1CF0: .4byte gSolidFnTable
