	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start copyx_08056908
copyx_08056908: @ 0x08056908
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	beq _08056920
	ldr r1, _08056940 @ =0x0000B30B
	adds r0, r4, #0
	bl SetMotion
	movs r0, #0
	strb r0, [r4, #0xe]
	strb r0, [r4, #0x12]
_08056920:
	adds r0, r4, #0
	bl UpdateMotionGraphic
	ldrb r0, [r4, #0x12]
	cmp r0, #0x79
	beq _0805696C
	cmp r0, #0x79
	bgt _0805694E
	cmp r0, #0x35
	beq _0805696C
	cmp r0, #0x35
	bgt _08056944
	cmp r0, #0x2c
	beq _08056966
	b _08056980
	.align 2, 0
_08056940: .4byte 0x0000B30B
_08056944:
	cmp r0, #0x3e
	beq _0805696C
	cmp r0, #0x70
	beq _08056966
	b _08056980
_0805694E:
	cmp r0, #0xb4
	beq _08056966
	cmp r0, #0xb4
	bgt _0805695C
	cmp r0, #0x82
	beq _0805696C
	b _08056980
_0805695C:
	cmp r0, #0xbd
	beq _0805696C
	cmp r0, #0xc6
	beq _0805696C
	b _08056980
_08056966:
	movs r0, #0x3c
	bl PlaySound
_0805696C:
	adds r0, r4, #0
	movs r1, #2
	movs r2, #0
	bl FUN_080a9048
	adds r0, r4, #0
	movs r1, #2
	movs r2, #1
	bl FUN_080a9048
_08056980:
	ldrb r0, [r4, #0x12]
	adds r0, #1
	strb r0, [r4, #0x12]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0xd9
	bne _0805699E
	movs r0, #0x1b
	strb r0, [r4, #0xd]
	movs r0, #1
	strb r0, [r4, #0xe]
	adds r1, r4, #0
	adds r1, #0xc6
	movs r0, #0
	strb r0, [r1]
_0805699E:
	pop {r4}
	pop {r0}
	bx r0
