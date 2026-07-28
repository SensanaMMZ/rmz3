	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_080cb528
FUN_080cb528: @ 0x080CB528
	push {r4, r5, r6, r7, lr}
	mov r7, sb
	mov r6, r8
	push {r6, r7}
	adds r5, r0, #0
	movs r6, #0
	movs r4, #0
	bl UpdateMotionGraphic
	ldrb r0, [r5, #0x12]
	cmp r0, #0
	beq _080CB546
	subs r0, #1
	strb r0, [r5, #0x12]
	b _080CB742
_080CB546:
	ldr r0, [r5, #0x54]
	mov r8, r0
	ldr r7, [r5, #0x58]
	ldr r1, _080CB5B4 @ =0xFFFFF800
	adds r1, r1, r7
	mov sb, r1
	ldrb r0, [r5, #0x10]
	cmp r0, #0
	bne _080CB5C0
	ldr r2, _080CB5B8 @ =0xFFFFE800
	adds r1, r7, r2
	mov r0, r8
	bl FUN_0800e284
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _080CB56C
	movs r6, #1
	movs r4, #1
_080CB56C:
	movs r0, #0x80
	lsls r0, r0, #5
	add r0, r8
	mov r1, sb
	bl FUN_0800e284
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _080CB588
	adds r0, r6, #1
	lsls r0, r0, #0x18
	lsrs r6, r0, #0x18
	movs r0, #2
	orrs r4, r0
_080CB588:
	movs r0, #0x80
	lsls r0, r0, #4
	adds r1, r7, r0
	mov r0, r8
	bl FUN_0800e284
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _080CB5A8
	adds r0, r6, #1
	lsls r0, r0, #0x18
	lsrs r6, r0, #0x18
	movs r0, #4
	orrs r4, r0
	lsls r0, r4, #0x18
	lsrs r4, r0, #0x18
_080CB5A8:
	ldr r0, _080CB5BC @ =0xFFFFF000
	add r0, r8
	mov r1, sb
	bl FUN_0800e284
	b _080CB61A
	.align 2, 0
_080CB5B4: .4byte 0xFFFFF800
_080CB5B8: .4byte 0xFFFFE800
_080CB5BC: .4byte 0xFFFFF000
_080CB5C0:
	ldr r2, _080CB638 @ =0xFFFFE800
	adds r1, r7, r2
	mov r0, r8
	bl FUN_08010cd0
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _080CB5D4
	movs r6, #1
	movs r4, #1
_080CB5D4:
	movs r0, #0x80
	lsls r0, r0, #5
	add r0, r8
	mov r1, sb
	bl FUN_08010cd0
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _080CB5F0
	adds r0, r6, #1
	lsls r0, r0, #0x18
	lsrs r6, r0, #0x18
	movs r0, #2
	orrs r4, r0
_080CB5F0:
	movs r0, #0x80
	lsls r0, r0, #4
	adds r1, r7, r0
	mov r0, r8
	bl FUN_08010cd0
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _080CB610
	adds r0, r6, #1
	lsls r0, r0, #0x18
	lsrs r6, r0, #0x18
	movs r0, #4
	orrs r4, r0
	lsls r0, r4, #0x18
	lsrs r4, r0, #0x18
_080CB610:
	ldr r0, _080CB63C @ =0xFFFFF000
	add r0, r8
	mov r1, sb
	bl FUN_08010cd0
_080CB61A:
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _080CB62E
	adds r0, r6, #1
	lsls r0, r0, #0x18
	lsrs r6, r0, #0x18
	movs r0, #8
	orrs r4, r0
	lsls r0, r4, #0x18
	lsrs r4, r0, #0x18
_080CB62E:
	cmp r6, #0
	bne _080CB640
	movs r0, #0
	b _080CB744
	.align 2, 0
_080CB638: .4byte 0xFFFFE800
_080CB63C: .4byte 0xFFFFF000
_080CB640:
	ldr r0, _080CB670 @ =gSolidHeaderPtr
	ldr r0, [r0]
	movs r2, #0xa
	ldrsh r1, [r0, r2]
	ldr r0, _080CB674 @ =gVFXHeaderPtr
	ldr r0, [r0]
	movs r2, #0xa
	ldrsh r0, [r0, r2]
	adds r1, r1, r0
	subs r0, r6, #1
	cmp r1, r0
	blt _080CB742
	movs r0, #1
	ands r0, r4
	cmp r0, #0
	beq _080CB67C
	ldr r0, [r5, #0x58]
	ldr r1, _080CB678 @ =0xFFFFF000
	adds r0, r0, r1
	str r0, [r5, #0x58]
	movs r0, #1
	eors r4, r0
	b _080CB6C0
	.align 2, 0
_080CB670: .4byte gSolidHeaderPtr
_080CB674: .4byte gVFXHeaderPtr
_080CB678: .4byte 0xFFFFF000
_080CB67C:
	movs r0, #2
	ands r0, r4
	cmp r0, #0
	beq _080CB692
	ldr r0, [r5, #0x54]
	movs r2, #0x80
	lsls r2, r2, #5
	adds r0, r0, r2
	str r0, [r5, #0x54]
	movs r0, #2
	b _080CB6BA
_080CB692:
	movs r0, #4
	ands r0, r4
	cmp r0, #0
	beq _080CB6A8
	ldr r0, [r5, #0x58]
	movs r1, #0x80
	lsls r1, r1, #5
	adds r0, r0, r1
	str r0, [r5, #0x58]
	movs r0, #4
	b _080CB6BA
_080CB6A8:
	movs r0, #8
	ands r0, r4
	cmp r0, #0
	beq _080CB6C0
	ldr r0, [r5, #0x54]
	ldr r2, _080CB6D4 @ =0xFFFFF000
	adds r0, r0, r2
	str r0, [r5, #0x54]
	movs r0, #8
_080CB6BA:
	eors r4, r0
	lsls r0, r4, #0x18
	lsrs r4, r0, #0x18
_080CB6C0:
	ldrb r0, [r5, #0x10]
	cmp r0, #0
	bne _080CB6DC
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x58]
	ldr r2, _080CB6D8 @ =0xFFFFF800
	adds r1, r1, r2
	bl FUN_0800e2c4
	b _080CB6E8
	.align 2, 0
_080CB6D4: .4byte 0xFFFFF000
_080CB6D8: .4byte 0xFFFFF800
_080CB6DC:
	ldr r0, [r5, #0x54]
	ldr r1, [r5, #0x58]
	ldr r2, _080CB750 @ =0xFFFFF800
	adds r1, r1, r2
	bl FUN_08010d20
_080CB6E8:
	movs r0, #1
	ands r0, r4
	cmp r0, #0
	beq _080CB6FC
	ldr r2, _080CB754 @ =0xFFFFF000
	add r2, sb
	adds r0, r5, #0
	mov r1, r8
	bl FUN_080cb3b8
_080CB6FC:
	movs r0, #2
	ands r0, r4
	cmp r0, #0
	beq _080CB712
	movs r1, #0x80
	lsls r1, r1, #5
	add r1, r8
	adds r0, r5, #0
	mov r2, sb
	bl FUN_080cb3b8
_080CB712:
	movs r0, #4
	ands r0, r4
	cmp r0, #0
	beq _080CB728
	movs r2, #0x80
	lsls r2, r2, #5
	add r2, sb
	adds r0, r5, #0
	mov r1, r8
	bl FUN_080cb3b8
_080CB728:
	movs r0, #8
	ands r4, r0
	cmp r4, #0
	beq _080CB73C
	ldr r1, _080CB754 @ =0xFFFFF000
	add r1, r8
	adds r0, r5, #0
	mov r2, sb
	bl FUN_080cb3b8
_080CB73C:
	adds r0, r5, #0
	bl FUN_080cb4c0
_080CB742:
	movs r0, #1
_080CB744:
	pop {r3, r4}
	mov r8, r3
	mov sb, r4
	pop {r4, r5, r6, r7}
	pop {r1}
	bx r1
	.align 2, 0
_080CB750: .4byte 0xFFFFF800
_080CB754: .4byte 0xFFFFF000
