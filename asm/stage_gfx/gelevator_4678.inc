	.include "asm/macros.inc"

	.syntax unified
	
	.text

	push {r4, r5, r6, r7, lr}
	mov r7, sl
	mov r6, sb
	mov r5, r8
	push {r5, r6, r7}
	sub sp, #4
	mov sb, r0
	ldr r1, _08014708 @ =gOverworld
	ldr r2, _0801470C @ =0x0002D034
	adds r0, r1, r2
	ldr r0, [r0]
	lsls r0, r0, #8
	lsrs r0, r0, #0x10
	mov sl, r0
	ldr r6, _08014710 @ =0x0002D038
	adds r0, r1, r6
	ldr r0, [r0]
	lsls r0, r0, #8
	lsrs r4, r0, #0x10
	ldr r7, _08014714 @ =0x0002D044
	adds r0, r1, r7
	ldr r0, [r0]
	lsls r0, r0, #8
	lsrs r0, r0, #0x10
	mov r8, r0
	ldr r0, _08014718 @ =0x0002D048
	adds r1, r1, r0
	ldr r0, [r1]
	lsls r0, r0, #0xf
	lsrs r5, r0, #0x17
	movs r0, #0xa0
	lsls r0, r0, #2
	bl Malloc
	adds r6, r0, #0
	cmp r6, #0
	beq _0801477C
	ldr r2, _0801471C @ =gIntrManager
	movs r1, #0xba
	lsls r1, r1, #1
	adds r0, r2, r1
	str r6, [r0]
	movs r7, #0xbc
	lsls r7, r7, #1
	adds r1, r2, r7
	ldr r0, _08014720 @ =0x04000018
	str r0, [r1]
	movs r0, #0xbe
	lsls r0, r0, #1
	adds r1, r2, r0
	ldr r0, _08014724 @ =0xA6600001
	str r0, [r1]
	movs r2, #0
	lsls r4, r4, #0x10
	str r4, [sp]
	movs r1, #0x80
	lsls r1, r1, #1
	mov ip, r1
	lsls r4, r5, #0x10
	mov r7, r8
	orrs r4, r7
	adds r0, r5, r1
	lsls r3, r0, #0x10
	orrs r3, r7
	adds r1, r6, #0
_080146FA:
	adds r0, r2, r5
	mov r7, ip
	ands r0, r7
	cmp r0, #0
	beq _08014728
	str r4, [r1]
	b _0801472A
	.align 2, 0
_08014708: .4byte gOverworld
_0801470C: .4byte 0x0002D034
_08014710: .4byte 0x0002D038
_08014714: .4byte 0x0002D044
_08014718: .4byte 0x0002D048
_0801471C: .4byte gIntrManager
_08014720: .4byte 0x04000018
_08014724: .4byte 0xA6600001
_08014728:
	str r3, [r1]
_0801472A:
	adds r1, #4
	adds r2, #1
	cmp r2, #0x9f
	ble _080146FA
	ldr r0, [sp]
	asrs r1, r0, #0x10
	cmp r1, #0xff
	ble _08014742
	mov r2, sb
	ldrb r0, [r2, #0xe]
	cmp r0, #7
	bls _0801477C
_08014742:
	movs r2, #0
	adds r3, r1, #0
	movs r7, #0x80
	lsls r7, r7, #1
	lsls r5, r3, #0x10
	mov r0, sl
	orrs r5, r0
	adds r0, r3, r7
	lsls r4, r0, #0x10
	mov r1, sl
	orrs r4, r1
	adds r1, r6, #0
_0801475A:
	adds r0, r2, r3
	ands r0, r7
	cmp r0, #0
	bne _08014766
	str r5, [r1]
	b _08014774
_08014766:
	mov r6, sb
	ldrb r0, [r6, #0xe]
	cmp r0, #7
	bls _08014774
	cmp r3, #0
	ble _08014774
	str r4, [r1]
_08014774:
	adds r1, #4
	adds r2, #1
	cmp r2, #0x9f
	ble _0801475A
_0801477C:
	add sp, #4
	pop {r3, r4, r5}
	mov r8, r3
	mov sb, r4
	mov sl, r5
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
