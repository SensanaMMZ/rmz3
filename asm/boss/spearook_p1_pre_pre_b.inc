	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start Spearook_Update
Spearook_Update: @ 0x080620AC
	push {r4, r5, lr}
	adds r4, r0, #0
	bl FUN_08061e24
	lsls r0, r0, #0x18
	lsrs r5, r0, #0x18
	cmp r5, #0
	beq _080620BE
	b _08062246
_080620BE:
	adds r0, r4, #0
	bl FUN_08061ef0
	ldr r1, _08062158 @ =0x083656E8
	ldrb r0, [r4, #0xd]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r1, [r0]
	adds r0, r4, #0
	bl _call_via_r1
	ldr r1, _0806215C @ =0x0836572C
	ldrb r0, [r4, #0xd]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r1, [r0]
	adds r0, r4, #0
	bl _call_via_r1
	ldrb r0, [r4, #0x10]
	cmp r0, #1
	beq _080620EC
	b _08062246
_080620EC:
	ldr r3, [r4, #0x28]
	adds r2, r3, #0
	adds r2, #0xbc
	ldr r0, [r2]
	movs r1, #0x40
	ands r0, r1
	movs r1, #0xba
	adds r1, r1, r4
	mov ip, r1
	cmp r0, #0
	beq _08062170
	ldrb r0, [r4, #0xd]
	subs r0, #0xa
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #2
	bhi _0806211E
	movs r0, #2
	strb r0, [r4, #0xd]
	strb r5, [r4, #0xe]
	ldr r0, [r2]
	movs r1, #0x21
	rsbs r1, r1, #0
	ands r0, r1
	str r0, [r2]
_0806211E:
	ldr r0, [r2]
	movs r1, #0x41
	rsbs r1, r1, #0
	ands r0, r1
	str r0, [r2]
	movs r2, #0xc0
	lsls r2, r2, #6
	adds r1, r2, #0
	mov r5, ip
	ldrh r5, [r5]
	adds r1, r1, r5
	mov r0, ip
	strh r1, [r0]
	adds r0, r3, #0
	adds r0, #0xc0
	ldrb r2, [r0]
	lsls r0, r2, #1
	adds r0, r0, r2
	lsls r0, r0, #0xd
	subs r1, r1, r0
	mov r2, ip
	strh r1, [r2]
	lsls r1, r1, #0x10
	asrs r1, r1, #0x10
	ldr r0, _08062160 @ =0xFFFFC000
	cmp r1, r0
	bge _08062164
	strh r0, [r2]
	b _08062170
	.align 2, 0
_08062158: .4byte 0x083656E8
_0806215C: .4byte 0x0836572C
_08062160: .4byte 0xFFFFC000
_08062164:
	movs r0, #0x80
	lsls r0, r0, #7
	cmp r1, r0
	ble _08062170
	mov r5, ip
	strh r0, [r5]
_08062170:
	adds r2, r4, #0
	adds r2, #0xb8
	mov r0, ip
	movs r5, #0
	ldrsh r1, [r0, r5]
	movs r5, #0
	ldrsh r0, [r2, r5]
	subs r0, r1, r0
	cmp r0, #0
	bge _08062186
	adds r0, #0xf
_08062186:
	asrs r0, r0, #4
	ldrh r5, [r2]
	adds r1, r0, r5
	strh r1, [r2]
	adds r0, r3, #0
	adds r0, #0xb4
	ldr r5, [r0]
	cmp r5, #0
	bne _080621E2
	lsls r0, r1, #0x10
	cmp r0, #0
	ble _080621C0
	mov r1, ip
	ldrh r0, [r1]
	subs r0, #0x80
	strh r0, [r1]
	lsls r0, r0, #0x10
	cmp r0, #0
	bge _080621AE
	strh r5, [r1]
_080621AE:
	ldrh r0, [r2]
	subs r0, #0x80
	strh r0, [r2]
	lsls r0, r0, #0x10
	adds r3, #0xbc
	cmp r0, #0
	bge _08062202
	strh r5, [r2]
	b _08062202
_080621C0:
	mov r1, ip
	ldrh r0, [r1]
	adds r0, #0x80
	strh r0, [r1]
	lsls r0, r0, #0x10
	cmp r0, #0
	ble _080621D0
	strh r5, [r1]
_080621D0:
	ldrh r0, [r2]
	adds r0, #0x80
	strh r0, [r2]
	lsls r0, r0, #0x10
	adds r3, #0xbc
	cmp r0, #0
	ble _08062202
	strh r5, [r2]
	b _08062202
_080621E2:
	ldrb r0, [r4, #0xd]
	subs r0, #0xa
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	adds r3, #0xbc
	cmp r0, #2
	bhi _08062202
	movs r0, #2
	strb r0, [r4, #0xd]
	movs r0, #0
	strb r0, [r4, #0xe]
	ldr r0, [r3]
	movs r1, #0x21
	rsbs r1, r1, #0
	ands r0, r1
	str r0, [r3]
_08062202:
	mov r5, ip
	movs r1, #0
	ldrsh r0, [r5, r1]
	movs r5, #0x80
	lsls r5, r5, #5
	adds r0, r0, r5
	movs r1, #0x80
	lsls r1, r1, #6
	cmp r0, r1
	bls _0806221E
	ldr r0, [r3]
	movs r1, #2
	orrs r0, r1
	b _08062226
_0806221E:
	ldr r0, [r3]
	movs r1, #3
	rsbs r1, r1, #0
	ands r0, r1
_08062226:
	str r0, [r3]
	ldrb r1, [r4, #0xa]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _0806223C
	ldrh r0, [r2]
	lsls r0, r0, #0x10
	asrs r0, r0, #0x18
	rsbs r0, r0, #0
	b _08062240
_0806223C:
	ldrh r0, [r2]
	lsrs r0, r0, #8
_08062240:
	adds r1, r4, #0
	adds r1, #0x24
	strb r0, [r1]
_08062246:
	pop {r4, r5}
	pop {r0}
	bx r0
