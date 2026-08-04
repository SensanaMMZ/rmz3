	push {r4, r5, r6, r7, lr}
	mov r7, r8
	push {r7}
	sub sp, #4
	adds r6, r0, #0
	ldr r0, [r6, #0x5c]
	lsls r0, r0, #0x10
	lsrs r1, r0, #0x10
	mov r8, r1
	ldrb r7, [r6, #0xe]
	cmp r7, #0
	bne _08014946
	lsrs r2, r0, #0x14
	lsls r4, r2, #1
	ldr r3, _0801498C @ =gVideoRegBuffer+4
	adds r4, r4, r3
	ldr r0, [r6, #0x60]
	ldr r1, [r6, #0x64]
	orrs r0, r1
	ldr r5, _08014990 @ =0x00008044
	adds r1, r5, #0
	orrs r0, r1
	strh r0, [r4]
	lsls r2, r2, #2
	adds r3, #8
	adds r2, r2, r3
	str r7, [r2]
	mov r1, r8
	lsls r0, r1, #0x18
	lsrs r0, r0, #0x18
	ldr r5, _08014994 @ =gBgMapOffsets
	str r7, [sp]
	adds r1, r5, #0
	movs r2, #0x5a
	movs r3, #0
	bl LoadBgMap
	ldrh r1, [r4]
	movs r0, #0xf8
	lsls r0, r0, #5
	ands r0, r1
	lsls r0, r0, #3
	ldr r2, _08014998 @ =0x06000800
	adds r0, r0, r2
	str r7, [sp]
	adds r1, r5, #0
	movs r2, #0x5a
	movs r3, #0
	bl loadBgMap_08004248
	strh r7, [r6, #0x10]
	strh r7, [r6, #0x12]
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_08014946:
	ldr r0, _0801499C @ =gOverworld
	ldr r5, _080149A0 @ =0x0002D025
	adds r0, r0, r5
	ldrb r0, [r0]
	cmp r0, #0
	beq _08014960
	ldrh r1, [r6, #0x12]
	ldr r0, _080149A4 @ =0x000007FF
	cmp r1, r0
	bhi _08014960
	adds r0, r1, #0
	adds r0, #8
	strh r0, [r6, #0x12]
_08014960:
	ldrh r0, [r6, #0x12]
	lsrs r0, r0, #8
	ldrh r2, [r6, #0x10]
	adds r1, r0, r2
	strh r1, [r6, #0x10]
	ldrb r0, [r6, #0xe]
	adds r2, r0, #0
	cmp r2, #1
	bne _080149AC
	lsls r1, r1, #0x10
	ldr r0, _080149A8 @ =0x14FF0000
	cmp r1, r0
	bls _080149AC
	mov r5, r8
	lsls r0, r5, #0x18
	lsrs r0, r0, #0x18
	ldr r1, _08014994 @ =gBgMapOffsets
	movs r2, #0
	str r2, [sp]
	movs r2, #0x5b
	b _08014A12
	.align 2, 0
_0801498C: .4byte gVideoRegBuffer+4
_08014990: .4byte 0x00008044
_08014994: .4byte gBgMapOffsets
_08014998: .4byte 0x06000800
_0801499C: .4byte gOverworld
_080149A0: .4byte 0x0002D025
_080149A4: .4byte 0x000007FF
_080149A8: .4byte 0x14FF0000
_080149AC:
	lsls r0, r2, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #2
	bne _080149F4
	ldrh r1, [r6, #0x10]
	ldr r0, _080149E4 @ =0x000015FF
	cmp r1, r0
	bls _080149F4
	mov r1, r8
	lsrs r0, r1, #4
	lsls r0, r0, #1
	ldr r1, _080149E8 @ =gVideoRegBuffer+4
	adds r0, r0, r1
	ldrh r1, [r0]
	movs r0, #0xf8
	lsls r0, r0, #5
	ands r0, r1
	lsls r0, r0, #3
	ldr r2, _080149EC @ =0x06000800
	adds r0, r0, r2
	ldr r1, _080149F0 @ =gBgMapOffsets
	movs r2, #0
	str r2, [sp]
	movs r2, #0x5d
	movs r3, #0
	bl loadBgMap_08004248
	b _08014A18
	.align 2, 0
_080149E4: .4byte 0x000015FF
_080149E8: .4byte gVideoRegBuffer+4
_080149EC: .4byte 0x06000800
_080149F0: .4byte gBgMapOffsets
_080149F4:
	lsls r0, r2, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #3
	bne _08014A1E
	ldrh r1, [r6, #0x10]
	ldr r0, _08014A2C @ =0x000016FF
	cmp r1, r0
	bls _08014A1E
	mov r5, r8
	lsls r0, r5, #0x18
	lsrs r0, r0, #0x18
	ldr r1, _08014A30 @ =gBgMapOffsets
	movs r2, #0
	str r2, [sp]
	movs r2, #0x5d
_08014A12:
	movs r3, #0
	bl LoadBgMap
_08014A18:
	ldrb r0, [r6, #0xe]
	adds r0, #1
	strb r0, [r6, #0xe]
_08014A1E:
	add sp, #4
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_08014A2C: .4byte 0x000016FF
_08014A30: .4byte gBgMapOffsets
