	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start Solid3_Update
Solid3_Update: @ 0x080CB7C8
	push {r4, r5, r6, r7, lr}
	mov r7, sl
	mov r6, sb
	mov r5, r8
	push {r5, r6, r7}
	adds r4, r0, #0
	ldrb r0, [r4, #0x11]
	cmp r0, #0
	beq _080CB7DC
	b _080CB926
_080CB7DC:
	ldr r1, _080CB890 @ =gStageRun+232
	ldr r0, [r1, #0x38]
	str r0, [r4, #0x54]
	ldr r0, [r1, #0x3c]
	str r0, [r4, #0x58]
	ldrb r0, [r4, #0xd]
	cmp r0, #0
	bne _080CB7EE
	b _080CB968
_080CB7EE:
	ldr r7, [r4, #0x64]
	ldr r5, [r4, #0x68]
	ldr r0, [r4, #0x5c]
	mov sl, r0
	ldr r0, [r4, #0x60]
	mov r8, r0
	ldrb r0, [r4, #0x10]
	cmp r0, #0
	bne _080CB894
	adds r0, r7, #0
	adds r1, r5, #0
	bl FUN_0800e284
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _080CB818
	adds r0, r4, #0
	adds r1, r7, #0
	adds r2, r5, #0
	bl FUN_080cb3b8
_080CB818:
	mov r0, sl
	adds r6, r7, r0
	adds r0, r5, #0
	add r0, r8
	mov sb, r0
	adds r0, r6, #0
	mov r1, sb
	bl FUN_0800e284
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _080CB83A
	adds r0, r4, #0
	adds r1, r6, #0
	mov r2, sb
	bl FUN_080cb3b8
_080CB83A:
	mov r0, r8
	subs r0, r5, r0
	mov r8, r0
	adds r0, r6, #0
	mov r1, r8
	bl FUN_0800e284
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _080CB858
	adds r0, r4, #0
	adds r1, r6, #0
	mov r2, r8
	bl FUN_080cb3b8
_080CB858:
	mov r0, sl
	subs r5, r7, r0
	adds r0, r5, #0
	mov r1, sb
	bl FUN_0800e284
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _080CB874
	adds r0, r4, #0
	adds r1, r5, #0
	mov r2, sb
	bl FUN_080cb3b8
_080CB874:
	adds r0, r5, #0
	mov r1, r8
	bl FUN_0800e284
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _080CB920
	adds r0, r4, #0
	adds r1, r5, #0
	mov r2, r8
	bl FUN_080cb3b8
	b _080CB920
	.align 2, 0
_080CB890: .4byte gStageRun+232
_080CB894:
	adds r0, r7, #0
	adds r1, r5, #0
	bl FUN_08010cd0
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _080CB8AC
	adds r0, r4, #0
	adds r1, r7, #0
	adds r2, r5, #0
	bl FUN_080cb3b8
_080CB8AC:
	mov r0, sl
	adds r6, r7, r0
	adds r0, r5, #0
	add r0, r8
	mov sb, r0
	adds r0, r6, #0
	mov r1, sb
	bl FUN_08010cd0
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _080CB8CE
	adds r0, r4, #0
	adds r1, r6, #0
	mov r2, sb
	bl FUN_080cb3b8
_080CB8CE:
	mov r0, r8
	subs r0, r5, r0
	mov r8, r0
	adds r0, r6, #0
	mov r1, r8
	bl FUN_08010cd0
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _080CB8EC
	adds r0, r4, #0
	adds r1, r6, #0
	mov r2, r8
	bl FUN_080cb3b8
_080CB8EC:
	mov r0, sl
	subs r5, r7, r0
	adds r0, r5, #0
	mov r1, sb
	bl FUN_08010cd0
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _080CB908
	adds r0, r4, #0
	adds r1, r5, #0
	mov r2, sb
	bl FUN_080cb3b8
_080CB908:
	adds r0, r5, #0
	mov r1, r8
	bl FUN_08010cd0
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _080CB920
	adds r0, r4, #0
	adds r1, r5, #0
	mov r2, r8
	bl FUN_080cb3b8
_080CB920:
	movs r0, #0
	strb r0, [r4, #0xd]
	b _080CB968
_080CB926:
	adds r0, r4, #0
	bl FUN_080cb528
	lsls r0, r0, #0x10
	asrs r2, r0, #0x10
	cmp r2, #0
	bne _080CB968
	ldrb r1, [r4, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r4, #0xa]
	adds r0, r4, #0
	adds r0, #0x8c
	str r2, [r0]
	adds r0, #4
	str r2, [r0]
	adds r0, #4
	strb r2, [r0]
	ldrb r1, [r4, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r4, #0xa]
	ldr r1, _080CB978 @ =gSolidFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r4, #0x14]
_080CB968:
	pop {r3, r4, r5}
	mov r8, r3
	mov sb, r4
	mov sl, r5
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080CB978: .4byte gSolidFnTable

