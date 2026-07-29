	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start Projectile31_Init
Projectile31_Init: @ 0x080AA808
	push {r4, r5, r6, r7, lr}
	adds r6, r0, #0
	ldr r7, [r6, #0x28]
	bl InitRotatableMotion
	ldrb r1, [r6, #0xa]
	movs r0, #1
	movs r5, #0
	orrs r0, r1
	movs r1, #2
	orrs r0, r1
	strb r0, [r6, #0xa]
	ldr r1, _080AA894 @ =0x0000640F
	adds r0, r6, #0
	bl SetMotion
	ldrb r1, [r6, #0xa]
	movs r0, #4
	orrs r0, r1
	strb r0, [r6, #0xa]
	adds r4, r6, #0
	adds r4, #0x74
	ldr r1, _080AA898 @ =0x0836C32C
	adds r2, r6, #0
	adds r2, #0x54
	adds r0, r4, #0
	movs r3, #0x40
	bl InitBody
	str r6, [r4, #0x2c]
	str r5, [r4, #0x24]
	ldrb r1, [r6, #0xa]
	movs r0, #0xef
	ands r0, r1
	strb r0, [r6, #0xa]
	adds r0, r6, #0
	adds r0, #0x4c
	strb r5, [r0]
	adds r2, r6, #0
	adds r2, #0x4a
	ldrb r1, [r2]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r2]
	ldr r0, [r7, #0x54]
	ldr r1, [r7, #0x58]
	str r0, [r6, #0x54]
	str r1, [r6, #0x58]
	ldrb r1, [r7, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _080AA8A4
	ldr r2, _080AA89C @ =0x0836C35C
	ldrb r1, [r6, #0x11]
	movs r0, #3
	ands r0, r1
	lsls r0, r0, #2
	adds r0, r0, r2
	ldr r1, [r7, #0x54]
	ldr r0, [r0]
	adds r1, r1, r0
	str r1, [r6, #0x54]
	ldr r1, _080AA8A0 @ =0x0836C36C
	ldrb r0, [r6, #0x11]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r0, [r0]
	b _080AA8C4
	.align 2, 0
_080AA894: .4byte 0x0000640F
_080AA898: .4byte 0x0836C32C
_080AA89C: .4byte 0x0836C35C
_080AA8A0: .4byte 0x0836C36C
_080AA8A4:
	ldr r2, _080AA91C @ =0x0836C35C
	ldrb r1, [r6, #0x11]
	movs r0, #3
	ands r0, r1
	lsls r0, r0, #2
	adds r0, r0, r2
	ldr r1, [r7, #0x54]
	ldr r0, [r0]
	subs r1, r1, r0
	str r1, [r6, #0x54]
	ldr r1, _080AA920 @ =0x0836C36C
	ldrb r0, [r6, #0x11]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r0, [r0]
	rsbs r0, r0, #0
_080AA8C4:
	str r0, [r6, #0x5c]
	ldrb r2, [r6, #0x11]
	ldr r0, [r7, #0x58]
	ldr r1, _080AA924 @ =0xFFFFD000
	adds r0, r0, r1
	str r0, [r6, #0x58]
	ldr r1, _080AA928 @ =0x0836C38C
	lsls r0, r2, #2
	adds r0, r0, r1
	ldr r1, [r0]
	str r1, [r6, #0x60]
	ldr r0, [r6, #0x5c]
	lsls r0, r0, #0x10
	asrs r0, r0, #0x10
	lsls r1, r1, #0x10
	asrs r1, r1, #0x10
	bl ArcTan2
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	movs r1, #0x80
	lsls r1, r1, #7
	adds r0, r0, r1
	asrs r0, r0, #8
	strb r0, [r6, #0x13]
	adds r1, r6, #0
	adds r1, #0x24
	strb r0, [r1]
	ldr r1, _080AA92C @ =gProjectileFnTable
	ldrb r0, [r6, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #1
	str r1, [r6, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #4]
	str r0, [r6, #0x14]
	adds r0, r6, #0
	bl Projectile31_Update
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080AA91C: .4byte 0x0836C35C
_080AA920: .4byte 0x0836C36C
_080AA924: .4byte 0xFFFFD000
_080AA928: .4byte 0x0836C38C
_080AA92C: .4byte gProjectileFnTable
