	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start CreateCopyXIcon
CreateCopyXIcon: @ 0x080C81AC
	push {r4, r5, r6, r7, lr}
	adds r7, r0, #0
	adds r5, r1, #0
	lsls r2, r2, #0x18
	lsrs r6, r2, #0x18
	ldr r0, _080C81FC @ =gVFXHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	adds r4, r0, #0
	cmp r4, #0
	beq _080C81F4
	adds r0, #0x25
	movs r3, #0
	movs r2, #1
	strb r2, [r0]
	ldr r0, _080C8200 @ =gVFXFnTable
	movs r1, #0x4d
	strb r1, [r4, #9]
	adds r1, #0xe7
	adds r0, r0, r1
	ldr r0, [r0]
	ldr r0, [r0]
	str r0, [r4, #0x14]
	movs r0, #0
	strh r3, [r4, #0x20]
	adds r1, r4, #0
	adds r1, #0x22
	strb r0, [r1]
	strb r2, [r4, #0x10]
	strb r6, [r4, #0x11]
	ldr r0, [r5]
	str r0, [r4, #0x54]
	ldr r0, [r5, #4]
	str r0, [r4, #0x58]
	str r7, [r4, #0x28]
_080C81F4:
	adds r0, r4, #0
	pop {r4, r5, r6, r7}
	pop {r1}
	bx r1
	.align 2, 0
_080C81FC: .4byte gVFXHeaderPtr
_080C8200: .4byte gVFXFnTable

	thumb_func_start FUN_080c8204
FUN_080c8204: @ 0x080C8204
	push {r4, r5, lr}
	adds r4, r0, #0
	lsls r1, r1, #0x18
	lsrs r5, r1, #0x18
	ldr r0, _080C8254 @ =gVFXHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	adds r3, r0, #0
	cmp r3, #0
	beq _080C824C
	adds r1, r3, #0
	adds r1, #0x25
	movs r2, #0
	movs r0, #1
	strb r0, [r1]
	ldr r0, _080C8258 @ =gVFXFnTable
	movs r1, #0x4d
	strb r1, [r3, #9]
	adds r1, #0xe7
	adds r0, r0, r1
	ldr r0, [r0]
	ldr r0, [r0]
	str r0, [r3, #0x14]
	movs r0, #0
	strh r2, [r3, #0x20]
	adds r1, r3, #0
	adds r1, #0x22
	strb r0, [r1]
	movs r0, #2
	strb r0, [r3, #0x10]
	strb r5, [r3, #0x11]
	ldr r0, [r4]
	str r0, [r3, #0x54]
	ldr r0, [r4, #4]
	str r0, [r3, #0x58]
_080C824C:
	adds r0, r3, #0
	pop {r4, r5}
	pop {r1}
	bx r1
	.align 2, 0
_080C8254: .4byte gVFXHeaderPtr
_080C8258: .4byte gVFXFnTable

	thumb_func_start FUN_080c825c
FUN_080c825c: @ 0x080C825C
	push {r4, r5, r6, lr}
	adds r6, r0, #0
	adds r4, r1, #0
	lsls r2, r2, #0x18
	lsrs r5, r2, #0x18
	ldr r0, _080C82B0 @ =gVFXHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	adds r3, r0, #0
	cmp r3, #0
	beq _080C82A8
	adds r1, r3, #0
	adds r1, #0x25
	movs r2, #0
	movs r0, #1
	strb r0, [r1]
	ldr r0, _080C82B4 @ =gVFXFnTable
	movs r1, #0x4d
	strb r1, [r3, #9]
	adds r1, #0xe7
	adds r0, r0, r1
	ldr r0, [r0]
	ldr r0, [r0]
	str r0, [r3, #0x14]
	movs r0, #0
	strh r2, [r3, #0x20]
	adds r1, r3, #0
	adds r1, #0x22
	strb r0, [r1]
	movs r0, #3
	strb r0, [r3, #0x10]
	strb r5, [r3, #0x11]
	ldr r0, [r4]
	str r0, [r3, #0x54]
	ldr r0, [r4, #4]
	str r0, [r3, #0x58]
	str r6, [r3, #0x28]
_080C82A8:
	adds r0, r3, #0
	pop {r4, r5, r6}
	pop {r1}
	bx r1
	.align 2, 0
_080C82B0: .4byte gVFXHeaderPtr
_080C82B4: .4byte gVFXFnTable

	thumb_func_start FUN_080c82b8
FUN_080c82b8: @ 0x080C82B8
	push {r4, r5, r6, r7, lr}
	mov r7, r8
	push {r7}
	mov r8, r0
	adds r4, r1, #0
	adds r7, r3, #0
	ldr r0, [sp, #0x18]
	lsls r2, r2, #0x18
	lsrs r5, r2, #0x18
	lsls r0, r0, #0x18
	lsrs r6, r0, #0x18
	ldr r0, _080C8328 @ =gVFXHeaderPtr
	ldr r0, [r0]
	bl AllocEntityFirst
	adds r3, r0, #0
	cmp r3, #0
	beq _080C831A
	adds r1, r3, #0
	adds r1, #0x25
	movs r2, #0
	movs r0, #1
	strb r0, [r1]
	ldr r0, _080C832C @ =gVFXFnTable
	movs r1, #0x4d
	strb r1, [r3, #9]
	adds r1, #0xe7
	adds r0, r0, r1
	ldr r0, [r0]
	ldr r0, [r0]
	str r0, [r3, #0x14]
	movs r0, #0
	strh r2, [r3, #0x20]
	adds r1, r3, #0
	adds r1, #0x22
	strb r0, [r1]
	movs r0, #4
	strb r0, [r3, #0x10]
	strb r5, [r3, #0x11]
	ldr r0, [r4]
	str r0, [r3, #0x54]
	ldr r0, [r4, #4]
	str r0, [r3, #0x58]
	mov r0, r8
	str r0, [r3, #0x28]
	str r7, [r3, #0x74]
	adds r0, r3, #0
	adds r0, #0x7c
	strb r6, [r0]
_080C831A:
	adds r0, r3, #0
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6, r7}
	pop {r1}
	bx r1
	.align 2, 0
_080C8328: .4byte gVFXHeaderPtr
_080C832C: .4byte gVFXFnTable

	thumb_func_start Ghost77_Init
Ghost77_Init: @ 0x080C8330
	push {r4, r5, lr}
	mov ip, r0
	ldrb r5, [r0, #0x10]
	cmp r5, #0
	bne _080C8378
	ldrb r1, [r0, #0xa]
	movs r0, #0xef
	ands r0, r1
	mov r1, ip
	strb r0, [r1, #0xa]
	movs r2, #1
	mov r0, ip
	adds r0, #0x4c
	strb r5, [r0]
	mov r3, ip
	adds r3, #0x4a
	ldrb r1, [r3]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r3]
	ldr r1, _080C8374 @ =gVFXFnTable
	mov r3, ip
	ldrb r0, [r3, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	str r2, [r3, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r3, #0x14]
	strb r5, [r3, #0xd]
	strb r5, [r3, #0xe]
	strb r5, [r3, #0xf]
	b _080C83F4
	.align 2, 0
_080C8374: .4byte gVFXFnTable
_080C8378:
	cmp r5, #1
	bne _080C83AC
	movs r2, #0
	mov r4, ip
	ldrb r1, [r4, #0xa]
	movs r0, #0xef
	ands r0, r1
	strb r0, [r4, #0xa]
	mov r0, ip
	adds r0, #0x4c
	strb r2, [r0]
	mov r3, ip
	adds r3, #0x4a
	ldrb r1, [r3]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r3]
	ldr r1, _080C83A8 @ =gVFXFnTable
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	str r5, [r4, #0xc]
	b _080C83E8
	.align 2, 0
_080C83A8: .4byte gVFXFnTable
_080C83AC:
	cmp r5, #2
	beq _080C83B8
	cmp r5, #3
	beq _080C83B8
	cmp r5, #4
	bne _080C83F4
_080C83B8:
	movs r2, #0
	mov r0, ip
	ldrb r1, [r0, #0xa]
	movs r0, #0xef
	ands r0, r1
	mov r1, ip
	strb r0, [r1, #0xa]
	movs r3, #1
	mov r0, ip
	adds r0, #0x4c
	strb r2, [r0]
	mov r4, ip
	adds r4, #0x4a
	ldrb r1, [r4]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r4]
	ldr r1, _080C8400 @ =gVFXFnTable
	mov r4, ip
	ldrb r0, [r4, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	str r3, [r4, #0xc]
_080C83E8:
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r4, #0x14]
	strb r5, [r4, #0xd]
	strb r2, [r4, #0xe]
	strb r2, [r4, #0xf]
_080C83F4:
	mov r0, ip
	bl Ghost77_Update
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080C8400: .4byte gVFXFnTable
