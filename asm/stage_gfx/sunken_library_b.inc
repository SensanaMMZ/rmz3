	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start sunkenLib_08013c0c
sunkenLib_08013c0c: @ 0x08013C0C
	push {r4, r5, r6, r7, lr}
	adds r5, r0, #0
	ldrb r0, [r5, #0xe]
	ldr r2, _08013CA4 @ =gOverworld
	cmp r0, #0
	bne _08013C30
	movs r1, #0
	adds r0, r5, #0
	adds r0, #0xc
_08013C1E:
	str r1, [r0, #0x68]
	subs r0, #4
	cmp r0, r5
	bge _08013C1E
	movs r0, #0
	strh r0, [r5, #0x10]
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_08013C30:
	ldr r1, _08013CA8 @ =0x0002D024
	adds r0, r2, r1
	ldrb r0, [r0]
	cmp r0, #0
	beq _08013CC0
	ldrh r0, [r5, #0x10]
	adds r0, #1
	strh r0, [r5, #0x10]
	movs r6, #0
	adds r4, r5, #0
	adds r4, #0x68
_08013C46:
	ldr r0, [r4]
	cmp r0, #0
	bne _08013C56
	lsls r0, r6, #0x18
	lsrs r0, r0, #0x18
	bl FUN_080d8f7c
	str r0, [r4]
_08013C56:
	adds r4, #4
	adds r6, #1
	cmp r6, #3
	ble _08013C46
	movs r4, #0x92
	lsls r4, r4, #1
	adds r0, r4, #0
	bl isSoundPlaying
	cmp r0, #0
	bne _08013C72
	adds r0, r4, #0
	bl PlaySound
_08013C72:
	ldrh r1, [r5, #0x10]
	movs r3, #1
	adds r0, r3, #0
	ands r0, r1
	cmp r0, #0
	beq _08013D20
	ldr r2, _08013CA4 @ =gOverworld
	ldr r0, _08013CAC @ =0x0002D02C
	adds r2, r2, r0
	ldr r1, [r2]
	ldr r0, _08013CB0 @ =0x000343FD
	muls r0, r1, r0
	ldr r1, _08013CB4 @ =0x00269EC3
	adds r0, r0, r1
	lsls r0, r0, #1
	lsrs r1, r0, #1
	str r1, [r2]
	lsrs r0, r0, #0x11
	ands r0, r3
	cmp r0, #0
	beq _08013D20
	ldr r1, _08013CB8 @ =gBlendRegBuffer
	ldr r0, _08013CBC @ =0x00000C0A
	b _08013D24
	.align 2, 0
_08013CA4: .4byte gOverworld
_08013CA8: .4byte 0x0002D024
_08013CAC: .4byte 0x0002D02C
_08013CB0: .4byte 0x000343FD
_08013CB4: .4byte 0x00269EC3
_08013CB8: .4byte gBlendRegBuffer
_08013CBC: .4byte 0x00000C0A
_08013CC0:
	movs r4, #0
	ldr r7, _08013D2C @ =gSolidFnTable
	adds r3, r5, #0
	adds r3, #0x68
	movs r6, #3
_08013CCA:
	ldr r2, [r3]
	cmp r2, #0
	beq _08013D04
	ldrb r1, [r2, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r2, #0xa]
	adds r0, r2, #0
	adds r0, #0x8c
	str r4, [r0]
	adds r0, #4
	str r4, [r0]
	adds r0, #4
	strb r4, [r0]
	ldrb r1, [r2, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r2, #0xa]
	ldrb r1, [r2, #9]
	lsls r1, r1, #2
	adds r1, r1, r7
	movs r0, #3
	str r0, [r2, #0xc]
	ldr r0, [r1]
	ldr r0, [r0, #0xc]
	str r0, [r2, #0x14]
	str r4, [r3]
_08013D04:
	adds r3, #4
	subs r6, #1
	cmp r6, #0
	bge _08013CCA
	movs r4, #0x92
	lsls r4, r4, #1
	adds r0, r4, #0
	bl isSoundPlaying
	cmp r0, #0
	beq _08013D20
	adds r0, r4, #0
	bl StopSound
_08013D20:
	ldr r1, _08013D30 @ =gBlendRegBuffer
	ldr r0, _08013D34 @ =0x00000C04
_08013D24:
	strh r0, [r1, #2]
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_08013D2C: .4byte gSolidFnTable
_08013D30: .4byte gBlendRegBuffer
_08013D34: .4byte 0x00000C04
