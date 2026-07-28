	.include "asm/macros.inc"

	.syntax unified
	
	.text

	thumb_func_start FUN_08010dd8
FUN_08010dd8: @ 0x08010DD8
	push {r4, r5, lr}
	adds r4, r0, #0
	adds r5, r1, #0
	bl FUN_08010d70
	lsls r0, r0, #0x10
	cmp r0, #0
	beq _08010E96
	ldr r0, _08010E18 @ =0x001D0FFF
	cmp r4, r0
	ble _08010E4C
	movs r0, #0x80
	lsls r0, r0, #9
	cmp r5, r0
	ble _08010E1C
	asrs r0, r4, #0xc
	subs r0, #1
	movs r1, #3
	bl __divsi3
	lsls r1, r0, #1
	adds r1, r1, r0
	adds r4, r1, #1
	asrs r0, r5, #0xc
	adds r0, #2
	movs r1, #3
	bl __divsi3
	lsls r1, r0, #1
	adds r1, r1, r0
	subs r5, r1, #2
	b _08010E3C
	.align 2, 0
_08010E18: .4byte 0x001D0FFF
_08010E1C:
	asrs r0, r4, #0xc
	subs r0, #1
	movs r1, #3
	bl __divsi3
	lsls r1, r0, #1
	adds r1, r1, r0
	adds r4, r1, #1
	asrs r0, r5, #0xc
	adds r0, #1
	movs r1, #3
	bl __divsi3
	lsls r1, r0, #1
	adds r1, r1, r0
	subs r5, r1, #1
_08010E3C:
	ldr r2, _08010E48 @ =0x08340278
	adds r0, r4, #0
	adds r1, r5, #0
	bl PatchMetatileMap
	b _08010E7C
	.align 2, 0
_08010E48: .4byte 0x08340278
_08010E4C:
	ldr r0, _08010E9C @ =0x001B2FFF
	cmp r4, r0
	ble _08010E7C
	asrs r0, r4, #0xc
	subs r0, #2
	movs r1, #3
	bl __divsi3
	lsls r1, r0, #1
	adds r1, r1, r0
	adds r4, r1, #2
	asrs r0, r5, #0xc
	subs r0, #1
	movs r1, #3
	bl __divsi3
	lsls r1, r0, #1
	adds r1, r1, r0
	adds r5, r1, #1
	ldr r2, _08010EA0 @ =0x08340278
	adds r0, r4, #0
	adds r1, r5, #0
	bl PatchMetatileMap
_08010E7C:
	movs r0, #0x41
	bl isSoundPlaying
	cmp r0, #0
	bne _08010E8C
	movs r0, #0x41
	bl PlaySound
_08010E8C:
	lsls r1, r4, #0xc
	lsls r2, r5, #0xc
	movs r0, #0
	bl FUN_080cee14
_08010E96:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_08010E9C: .4byte 0x001B2FFF
_08010EA0: .4byte 0x08340278
