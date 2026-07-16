push {r4, lr}
adds r4, r0, #0
bl InitScalerotMotion1
movs r1, #0x80
lsls r1, r1, #1
str r1, [r4, #0x7c]
adds r0, r4, #0
adds r0, #0x50
movs r2, #0
strh r1, [r0]
ldr r0, [r4, #0x7c]
adds r1, r4, #0
adds r1, #0x52
strh r0, [r1]
adds r0, r4, #0
adds r0, #0x24
strb r2, [r0]
ldr r1, _080BACA0 @ =gVFXFnTable
ldrb r0, [r4, #9]
lsls r0, r0, #2
adds r0, r0, r1
movs r1, #1
str r1, [r4, #0xc]
ldr r0, [r0]
movs r1, #4
ldr r0, [r0, #4]
str r0, [r4, #0x14]
strb r1, [r4, #0xd]
strb r2, [r4, #0xe]
strb r2, [r4, #0xf]
pop {r4}
pop {r0}
bx r0
.align 2, 0
_080BACA0: .4byte gVFXFnTable

