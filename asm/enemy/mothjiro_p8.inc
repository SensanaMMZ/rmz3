	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start mothjiro_08088a50
mothjiro_08088a50: @ 0x08088A50
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0xe]
	cmp r0, #0
	bne _08088A6A
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _08088A70 @ =0x083687E0
	bl SetDDP
	ldrb r0, [r4, #0xe]
	adds r0, #1
	strb r0, [r4, #0xe]
_08088A6A:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_08088A70: .4byte 0x083687E0

	thumb_func_start mothjiro_08088a74
mothjiro_08088a74: @ 0x08088A74
	push {r4, r5, lr}
	adds r4, r0, #0
	adds r5, r4, #0
	adds r5, #0xc0
	ldr r0, [r5]
	cmp r0, #0
	bne _08088AD2
	adds r0, r4, #0
	adds r0, #0x8c
	ldr r0, [r0]
	movs r1, #1
	ands r0, r1
	cmp r0, #0
	beq _08088AD2
	ldr r2, _08088ABC @ =0x083687F8
	movs r0, #0
	adds r1, r4, #0
	bl ApplyElementEffect
	str r0, [r5]
	cmp r0, #0
	beq _08088AD2
	adds r0, r4, #0
	adds r0, #0x97
	ldrb r0, [r0]
	movs r1, #0xf0
	ands r1, r0
	cmp r1, #0x10
	bne _08088AC4
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _08088AC0 @ =0x083687E0
	bl SetDDP
	b _08088AD2
	.align 2, 0
_08088ABC: .4byte 0x083687F8
_08088AC0: .4byte 0x083687E0
_08088AC4:
	cmp r1, #0x30
	bne _08088AD2
	adds r0, r4, #0
	adds r0, #0x74
	ldr r1, _08088ADC @ =0x083687E0
	bl SetDDP
_08088AD2:
	movs r0, #1
	pop {r4, r5}
	pop {r1}
	bx r1
	.align 2, 0
_08088ADC: .4byte 0x083687E0

	thumb_func_start FUN_08088ae0
FUN_08088ae0: @ 0x08088AE0
	push {r4, lr}
	adds r4, r0, #0
	adds r0, #0x54
	bl FUN_08012a64
	adds r2, r0, #0
	cmp r2, #0
	bne _08088AF4
	movs r0, #0
	b _08088B04
_08088AF4:
	adds r1, r4, #0
	adds r1, #0xb8
	ldr r0, [r2]
	str r0, [r1]
	adds r1, #4
	ldr r0, [r2, #4]
	str r0, [r1]
	movs r0, #1
_08088B04:
	pop {r4}
	pop {r1}
	bx r1
	.align 2, 0

	thumb_func_start FUN_08088b0c
FUN_08088b0c: @ 0x08088B0C
	push {lr}
	adds r2, r0, #0
	adds r3, r1, #0
	ldr r0, [r2, #0xc]
	ldr r0, [r0, #4]
	ldrb r0, [r0, #4]
	cmp r0, #3
	beq _08088B24
	cmp r0, #0xe
	beq _08088B24
	cmp r0, #0xf
	bne _08088B46
_08088B24:
	ldr r2, [r2, #0x2c]
	adds r0, r2, #0
	adds r0, #0x8c
	ldr r0, [r0]
	movs r1, #0x80
	lsls r1, r1, #2
	ands r0, r1
	cmp r0, #0
	beq _08088B46
	ldr r1, [r2, #0x54]
	ldr r0, [r3]
	cmp r1, r0
	bge _08088B42
	movs r0, #0xff
	b _08088B44
_08088B42:
	movs r0, #0xfe
_08088B44:
	strb r0, [r2, #0x11]
_08088B46:
	pop {r0}
	bx r0
	.align 2, 0
