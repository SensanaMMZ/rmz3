	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080947c4
FUN_080947c4: @ 0x080947C4
	push {r4, r5, lr}
	sub sp, #8
	adds r4, r0, #0
	adds r0, #0x8c
	movs r1, #0
	str r1, [r0]
	adds r0, #4
	str r1, [r0]
	adds r0, #4
	strb r1, [r0]
	ldrb r1, [r4, #0xa]
	movs r0, #0xfb
	ands r0, r1
	movs r1, #0xfe
	ands r0, r1
	strb r0, [r4, #0xa]
	ldr r0, [r4, #0x54]
	str r0, [sp]
	ldr r0, [r4, #0x58]
	ldr r1, _08094814 @ =0xFFFFF000
	adds r0, r0, r1
	str r0, [sp, #4]
	movs r0, #1
	mov r1, sp
	bl CreateSmoke
	movs r0, #0x2a
	bl PlaySound
	ldrb r0, [r4, #0x11]
	cmp r0, #0
	bne _0809481C
	ldr r2, _08094818 @ =0x08369EBE
	adds r0, r4, #0
	mov r1, sp
	movs r3, #4
	bl FUN_080b7f70
	b _08094828
	.align 2, 0
_08094814: .4byte 0xFFFFF000
_08094818: .4byte 0x08369EBE
_0809481C:
	ldr r2, _08094864 @ =0x08369EBE
	adds r0, r4, #0
	mov r1, sp
	movs r3, #4
	bl FUN_080b7ffc
_08094828:
	adds r5, r4, #0
	adds r5, #0x54
	movs r0, #4
	adds r1, r5, #0
	bl TryDropItem
	ldr r2, _08094868 @ =gMission
	ldrh r1, [r2, #0xc]
	ldr r0, _0809486C @ =0x0000270E
	cmp r1, r0
	bhi _08094842
	adds r0, r1, #1
	strh r0, [r2, #0xc]
_08094842:
	adds r0, r4, #0
	adds r1, r5, #0
	bl TryDropZakoDisk
	ldr r1, _08094870 @ =gEnemyFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #4
	str r1, [r4, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0x10]
	str r0, [r4, #0x14]
	add sp, #8
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_08094864: .4byte 0x08369EBE
_08094868: .4byte gMission
_0809486C: .4byte 0x0000270E
_08094870: .4byte gEnemyFnTable

	thumb_func_start FUN_08094874
FUN_08094874: @ 0x08094874
	push {r4, r5, r6, lr}
	sub sp, #0x10
	adds r4, r0, #0
	ldrb r5, [r4, #0xe]
	cmp r5, #0
	beq _08094888
	cmp r5, #1
	bne _08094886
	b _08094988
_08094886:
	b _080949C6
_08094888:
	movs r6, #0
	ldr r0, _0809490C @ =pZero2
	ldr r0, [r0]
	ldr r0, [r0, #0x54]
	ldr r1, [r4, #0x54]
	subs r0, r0, r1
	cmp r0, #0
	ble _0809489A
	movs r6, #1
_0809489A:
	ldr r1, _08094910 @ =0x00008E0A
	adds r0, r4, #0
	bl SetMotion
	adds r0, r4, #0
	adds r0, #0x8c
	str r5, [r0]
	adds r0, #4
	str r5, [r0]
	adds r0, #4
	strb r5, [r0]
	ldrb r1, [r4, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r4, #0xa]
	ldr r0, [r4, #0x54]
	str r0, [sp, #8]
	ldr r0, [r4, #0x58]
	str r0, [sp, #0xc]
	movs r2, #0x80
	lsls r2, r2, #2
	movs r0, #0
	add r1, sp, #8
	adds r3, r6, #0
	bl FUN_080b2b40
	movs r1, #0x60
	lsls r0, r6, #1
	adds r0, r0, r6
	lsls r0, r0, #6
	subs r1, r1, r0
	str r1, [sp, #8]
	str r5, [sp, #0xc]
	adds r0, r4, #0
	movs r1, #1
	bl FUN_08093a64
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _08094934
	movs r0, #0x20
	str r0, [r4, #0x68]
	ldrb r0, [r4, #0x11]
	cmp r0, #0
	bne _08094918
	adds r1, r4, #0
	adds r1, #0x54
	ldr r0, _08094914 @ =0x08369EC6
	str r0, [sp]
	movs r0, #0x18
	str r0, [sp, #4]
	adds r0, r4, #0
	add r2, sp, #8
	movs r3, #0x15
	bl FUN_080b84f4
	b _0809496E
	.align 2, 0
_0809490C: .4byte pZero2
_08094910: .4byte 0x00008E0A
_08094914: .4byte 0x08369EC6
_08094918:
	adds r1, r4, #0
	adds r1, #0x54
	ldr r0, _08094930 @ =0x08369EC6
	str r0, [sp]
	movs r0, #0x18
	str r0, [sp, #4]
	adds r0, r4, #0
	add r2, sp, #8
	movs r3, #0x15
	bl FUN_080b857c
	b _0809496E
	.align 2, 0
_08094930: .4byte 0x08369EC6
_08094934:
	str r5, [r4, #0x68]
	ldrb r0, [r4, #0x11]
	cmp r0, #0
	bne _08094958
	adds r1, r4, #0
	adds r1, #0x54
	ldr r0, _08094954 @ =0x08369EC6
	str r0, [sp]
	movs r0, #0x18
	str r0, [sp, #4]
	adds r0, r4, #0
	add r2, sp, #8
	movs r3, #0
	bl FUN_080b834c
	b _0809496E
	.align 2, 0
_08094954: .4byte 0x08369EC6
_08094958:
	adds r1, r4, #0
	adds r1, #0x54
	ldr r0, _080949D0 @ =0x08369EC6
	str r0, [sp]
	movs r0, #0x18
	str r0, [sp, #4]
	adds r0, r4, #0
	add r2, sp, #8
	movs r3, #0
	bl FUN_080b83d4
_0809496E:
	ldr r0, [sp, #8]
	cmp r0, #0
	bge _08094976
	adds r0, #3
_08094976:
	asrs r0, r0, #2
	str r0, [r4, #0x5c]
	movs r0, #0
	str r0, [r4, #0x60]
	movs r0, #0x18
	strb r0, [r4, #0x12]
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08094988:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldr r1, [r4, #0x68]
	cmp r1, #0
	beq _080949AC
	ldr r0, [r4, #0x60]
	adds r0, r0, r1
	str r0, [r4, #0x60]
	movs r1, #0xe0
	lsls r1, r1, #3
	cmp r0, r1
	ble _080949A4
	str r1, [r4, #0x60]
_080949A4:
	ldr r1, [r4, #0x60]
	adds r0, r4, #0
	bl FUN_08093a64
_080949AC:
	ldr r0, [r4, #0x54]
	ldr r1, [r4, #0x5c]
	adds r0, r0, r1
	str r0, [r4, #0x54]
	ldrb r0, [r4, #0x12]
	subs r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080949C6
	adds r0, r4, #0
	bl FUN_080947c4
_080949C6:
	add sp, #0x10
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_080949D0: .4byte 0x08369EC6
