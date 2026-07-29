	.include "asm/macros.inc"

	.syntax unified

	.text

	thumb_func_start missileFactory_0800f560
missileFactory_0800f560: @ 0x0800F560
	push {r4, r5, r6, r7, lr}
	mov r7, r8
	push {r7}
	adds r7, r0, #0
	ldrb r0, [r7, #0xe]
	mov r8, r0
	cmp r0, #0
	bne _0800F5D8
	ldr r0, [r7, #0x5c]
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x14
	lsls r5, r0, #1
	ldr r3, _0800F5E8 @ =gVideoRegBuffer+4
	adds r5, r5, r3
	ldr r1, [r7, #0x60]
	ldr r2, [r7, #0x64]
	orrs r1, r2
	ldr r4, _0800F5EC @ =0x00004044
	adds r2, r4, #0
	orrs r1, r2
	strh r1, [r5]
	lsls r0, r0, #2
	adds r3, #8
	adds r0, r0, r3
	mov r2, r8
	str r2, [r0]
	ldr r0, _0800F5F0 @ =0x085223E4
	ldr r0, [r0]
	ldr r4, _0800F5F4 @ =0x085223EC
	adds r0, r0, r4
	movs r4, #0xf8
	lsls r4, r4, #5
	ands r1, r4
	lsls r1, r1, #3
	movs r2, #0xc0
	lsls r2, r2, #0x13
	adds r1, r1, r2
	movs r6, #0x80
	lsls r6, r6, #2
	adds r2, r6, #0
	bl CpuFastSet
	ldr r0, _0800F5F8 @ =0x085223E8
	ldr r0, [r0]
	ldr r1, _0800F5FC @ =0x085223F0
	adds r0, r0, r1
	ldrh r1, [r5]
	ands r4, r1
	lsls r4, r4, #3
	ldr r2, _0800F600 @ =0x06000800
	adds r4, r4, r2
	adds r1, r4, #0
	adds r2, r6, #0
	bl CpuFastSet
	mov r4, r8
	strh r4, [r7, #0x10]
	ldrb r0, [r7, #0xe]
	adds r0, #1
	strb r0, [r7, #0xe]
_0800F5D8:
	ldrh r0, [r7, #0x10]
	adds r0, #4
	strh r0, [r7, #0x10]
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_0800F5E8: .4byte gVideoRegBuffer+4
_0800F5EC: .4byte 0x00004044
_0800F5F0: .4byte 0x085223E4
_0800F5F4: .4byte 0x085223EC
_0800F5F8: .4byte 0x085223E8
_0800F5FC: .4byte 0x085223F0
_0800F600: .4byte 0x06000800

