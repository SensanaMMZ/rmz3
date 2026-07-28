	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_08013b10
FUN_08013b10: @ 0x08013B10
	push {r4, lr}
	ldr r3, [r0, #0x68]
	cmp r3, #0
	beq _08013B4E
	ldrb r1, [r3, #0xa]
	movs r0, #0xfe
	ands r0, r1
	movs r2, #0
	movs r1, #0xfd
	ands r0, r1
	strb r0, [r3, #0xa]
	adds r0, r3, #0
	adds r0, #0x8c
	str r2, [r0]
	adds r0, #4
	str r2, [r0]
	adds r0, #4
	strb r2, [r0]
	ldrb r1, [r3, #0xa]
	movs r0, #0xfb
	ands r0, r1
	strb r0, [r3, #0xa]
	ldr r1, _08013B68 @ =gSolidFnTable
	ldrb r0, [r3, #9]
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r1, #3
	str r1, [r3, #0xc]
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	str r0, [r3, #0x14]
_08013B4E:
	movs r4, #0x92
	lsls r4, r4, #1
	adds r0, r4, #0
	bl isSoundPlaying
	cmp r0, #0
	beq _08013B62
	adds r0, r4, #0
	bl StopSound
_08013B62:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_08013B68: .4byte gSolidFnTable

	thumb_func_start sunkenlib_08013b6c
sunkenlib_08013b6c: @ 0x08013B6C
	push {r4, r5, r6, lr}
	adds r5, r0, #0
	ldrb r6, [r5, #0xe]
	cmp r6, #0
	bne _08013BBA
	ldr r0, [r5, #0x5c]
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x14
	lsls r3, r0, #1
	ldr r4, _08013BCC @ =gVideoRegBuffer+4
	adds r3, r3, r4
	ldr r1, [r5, #0x60]
	ldr r2, [r5, #0x64]
	orrs r1, r2
	movs r2, #0x44
	orrs r1, r2
	strh r1, [r3]
	lsls r0, r0, #2
	adds r4, #8
	adds r0, r0, r4
	str r6, [r0]
	ldr r0, _08013BD0 @ =0x085223BC
	ldr r0, [r0]
	ldr r2, _08013BD4 @ =0x085223C4
	adds r0, r0, r2
	movs r2, #0xf8
	lsls r2, r2, #5
	ands r1, r2
	lsls r1, r1, #3
	movs r2, #0xc0
	lsls r2, r2, #0x13
	adds r1, r1, r2
	movs r2, #0x80
	lsls r2, r2, #2
	bl CpuFastSet
	ldrb r0, [r5, #0xe]
	adds r0, #1
	strb r0, [r5, #0xe]
_08013BBA:
	ldr r2, _08013BD8 @ =gWindowRegBuffer
	ldrb r1, [r2, #0xd]
	movs r0, #8
	orrs r0, r1
	strb r0, [r2, #0xd]
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_08013BCC: .4byte gVideoRegBuffer+4
_08013BD0: .4byte 0x085223BC
_08013BD4: .4byte 0x085223C4
_08013BD8: .4byte gWindowRegBuffer

