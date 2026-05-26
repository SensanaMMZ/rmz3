	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start FUN_080711d8
FUN_080711d8: @ 0x080711D8
	push {lr}
	adds r2, r0, #0
	adds r3, r1, #0
	ldr r0, [r2, #0xc]
	ldr r0, [r0, #4]
	ldrb r0, [r0, #4]
	cmp r0, #3
	beq _080711F0
	cmp r0, #0xe
	beq _080711F0
	cmp r0, #0xf
	bne _0807121A
_080711F0:
	ldr r2, [r2, #0x2c]
	adds r0, r2, #0
	adds r0, #0x8c
	ldr r0, [r0]
	movs r1, #0x80
	lsls r1, r1, #2
	ands r0, r1
	cmp r0, #0
	beq _0807121A
	ldr r1, [r2, #0x54]
	ldr r0, [r3]
	cmp r1, r0
	bge _08071212
	adds r1, r2, #0
	adds r1, #0xbf
	movs r0, #0xff
	b _08071218
_08071212:
	adds r1, r2, #0
	adds r1, #0xbf
	movs r0, #0xfe
_08071218:
	strb r0, [r1]
_0807121A:
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start forceWaterLanding
forceWaterLanding: @ 0x08071220
	push {lr}
	adds r3, r0, #0
	ldr r1, _08071238 @ =gOverworld
	ldr r2, _0807123C @ =0x0002C00C
	adds r1, r1, r2
	ldr r2, [r1]
	ldr r1, [r3, #0x58]
	cmp r2, r1
	ble _08071234
	str r2, [r3, #0x58]
_08071234:
	pop {r1}
	bx r1
	.align 2, 0
_08071238: .4byte gOverworld
_0807123C: .4byte 0x0002C00C
