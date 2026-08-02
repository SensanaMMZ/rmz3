	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_080bd48c
FUN_080bd48c: @ 0x080BD48C
	push {lr}
	mov ip, r0
	ldrb r0, [r0, #0xe]
	cmp r0, #0
	bne _080BD4CE
	ldr r1, _080BD4E4 @ =gWindowRegBuffer
	ldrh r2, [r1]
	movs r3, #0x80
	lsls r3, r3, #7
	adds r0, r3, #0
	movs r3, #0
	orrs r0, r2
	strh r0, [r1]
	movs r0, #0x31
	strb r0, [r1, #0xd]
	ldrb r2, [r1, #0xe]
	movs r0, #0xe
	orrs r0, r2
	strb r0, [r1, #0xe]
	movs r0, #0x80
	lsls r0, r0, #6
	mov r1, ip
	str r0, [r1, #0x78]
	mov r0, ip
	adds r0, #0x74
	strb r3, [r0]
	adds r0, #1
	strb r3, [r0]
	adds r0, #1
	strb r3, [r0]
	ldrb r0, [r1, #0xe]
	adds r0, #1
	strb r0, [r1, #0xe]
_080BD4CE:
	ldr r1, _080BD4E8 @ =gJoypad
	ldrh r2, [r1]
	movs r0, #1
	ands r0, r2
	cmp r0, #0
	beq _080BD4EC
	mov r2, ip
	ldr r0, [r2, #0x78]
	movs r3, #0x80
	lsls r3, r3, #1
	b _080BD4FA
	.align 2, 0
_080BD4E4: .4byte gWindowRegBuffer
_080BD4E8: .4byte gJoypad
_080BD4EC:
	movs r0, #2
	ands r0, r2
	cmp r0, #0
	beq _080BD4FE
	mov r2, ip
	ldr r0, [r2, #0x78]
	ldr r3, _080BD514 @ =0xFFFFFF00
_080BD4FA:
	adds r0, r0, r3
	str r0, [r2, #0x78]
_080BD4FE:
	ldrh r2, [r1]
	movs r1, #0xc0
	lsls r1, r1, #2
	adds r0, r1, #0
	ands r0, r2
	cmp r0, r1
	bne _080BD518
	movs r0, #0
	mov r1, ip
	str r0, [r1, #0x60]
	b _080BD53E
	.align 2, 0
_080BD514: .4byte 0xFFFFFF00
_080BD518:
	movs r0, #0x80
	lsls r0, r0, #1
	ands r0, r2
	cmp r0, #0
	beq _080BD52C
	mov r2, ip
	ldr r0, [r2, #0x60]
	adds r0, #0x10
	str r0, [r2, #0x60]
	b _080BD53E
_080BD52C:
	movs r0, #0x80
	lsls r0, r0, #2
	ands r0, r2
	cmp r0, #0
	beq _080BD53E
	mov r3, ip
	ldr r0, [r3, #0x60]
	subs r0, #0x10
	str r0, [r3, #0x60]
_080BD53E:
	mov r1, ip
	ldrb r0, [r1, #0x13]
	adds r0, #1
	strb r0, [r1, #0x13]
	movs r1, #1
	ands r0, r1
	cmp r0, #0
	beq _080BD55E
	mov r0, ip
	adds r0, #0x74
	movs r1, #0x1f
	strb r1, [r0]
	adds r0, #1
	strb r1, [r0]
	adds r0, #1
	b _080BD572
_080BD55E:
	mov r0, ip
	adds r0, #0x74
	movs r1, #0x18
	strb r1, [r0]
	mov r2, ip
	adds r2, #0x75
	movs r0, #0x1f
	strb r0, [r2]
	mov r0, ip
	adds r0, #0x76
_080BD572:
	strb r1, [r0]
	pop {r0}
	bx r0
