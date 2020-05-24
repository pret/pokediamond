    .include "asm/macros.inc"
    .include "global.inc"

	.extern UNK_020F96DC
	.extern UNK_020FA6E8

	.section .rodata

	.global UNK_020FD154
UNK_020FD154: ; 0x020FD154
	.byte 0x04, 0x08, 0x00, 0x00

	.global UNK_020FD158
UNK_020FD158: ; 0x020FD158
	.byte 0x04, 0x07, 0x08, 0x00

	.global UNK_020FD15C
UNK_020FD15C: ; 0x020FD15C
	.word MOD65_021D74E0, MOD65_021D7524, MOD65_021D753C, SDK_OVERLAY_MODULE_65_ID

	.global UNK_020FD16C
UNK_020FD16C: ; 0x020FD16C
	.word MOD65_021D8A08, MOD65_021D8A40, MOD65_021D8BBC, SDK_OVERLAY_MODULE_65_ID

	.global UNK_020FD17C
UNK_020FD17C: ; 0x020FD17C
	.byte 0x05

	.global UNK_020FD17D
UNK_020FD17D: ; 0x020FD17D
	.byte 0x05, 0x00, 0x04, 0x00, 0x02, 0x00, 0x01, 0x00, 0x03, 0x04, 0x00, 0x05, 0x05, 0x04, 0x02, 0x04
	.byte 0x01, 0x04, 0x03, 0x02, 0x00, 0x02, 0x04, 0x05, 0x05, 0x02, 0x01, 0x02, 0x03, 0x01, 0x00, 0x01
	.byte 0x04, 0x01, 0x02, 0x05, 0x05, 0x01, 0x03, 0x03, 0x00, 0x03, 0x04, 0x03, 0x02, 0x03, 0x01, 0x05
	.byte 0x05, 0x00, 0x00

	.global UNK_020FD1B0
UNK_020FD1B0: ; 0x020FD1B0
	.word FUN_02087E40, FUN_02087E74, FUN_02087EE8, 0xFFFFFFFF

	.text

	thumb_func_start FUN_02087D00
FUN_02087D00: ; 0x02087D00
	push {r3-r7, lr}
	sub sp, #0x10
	add r4, r0, #0x0
	add r5, r1, #0x0
	mov r0, #0x0
	mov r1, #0xcf
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	lsl r1, r1, #0x2
	bl FUN_02016998
	mov r2, #0xcf
	mov r1, #0x0
	lsl r2, r2, #0x2
	add r7, r0, #0x0
	bl MI_CpuFill8
	add r0, r4, #0x0
	bl FUN_02028048
	str r0, [r7, #0x8]
	add r0, r4, #0x0
	bl FUN_020238F4
	str r0, [r7, #0xc]
	add r0, r4, #0x0
	bl FUN_0206BB1C
	str r0, [r7, #0x10]
	add r0, r4, #0x0
	bl FUN_0206F158
	str r0, [r7, #0x14]
	add r0, r4, #0x0
	bl LoadPlayerDataAddress
	str r0, [r7, #0x18]
	add r0, r5, #0x0
	bl FUN_02027E5C
	add r4, r0, #0x0
	mov r0, #0x1
	mov r1, #0x20
	add r2, r5, #0x0
	bl FUN_0200AA90
	str r0, [sp, #0x4]
	mov r6, #0x0
_02087D60:
	ldr r0, [r7, #0x8]
	add r1, r6, #0x0
	add r2, r4, #0x0
	bl FUN_02028174
	add r0, r4, #0x0
	bl FUN_02027E34
	cmp r0, #0x0
	beq _02087DEE
	add r0, r4, #0x0
	add r1, sp, #0x8
	bl FUN_02027FBC
	ldr r0, [sp, #0x0]
	add r1, r7, #0x0
	add r1, #0x1c
	lsl r0, r0, #0x3
	add r5, r1, r0
	strb r6, [r1, r0]
	add r0, r4, #0x0
	bl FUN_02027FDC
	strb r0, [r5, #0x1]
	add r0, sp, #0x8
	ldrb r1, [r0, #0x0]
	mov r2, #0x1
	strb r1, [r5, #0x2]
	ldrb r0, [r0, #0x6]
	mov r1, #0x0
	strb r0, [r5, #0x3]
	add r0, sp, #0x8
_02087DA0:
	add r3, r0, r1
	ldrb r3, [r3, #0x1]
	cmp r3, #0x0
	beq _02087DAE
	ldrb r3, [r5, #0x4]
	orr r3, r2
	strb r3, [r5, #0x4]
_02087DAE:
	add r1, r1, #0x1
	lsl r1, r1, #0x18
	lsl r2, r2, #0x19
	lsr r1, r1, #0x18
	lsr r2, r2, #0x18
	cmp r1, #0x5
	blo _02087DA0
	ldrb r1, [r5, #0x4]
	mov r0, #0x20
	orr r0, r1
	strb r0, [r5, #0x4]
	ldrb r2, [r5, #0x4]
	mov r1, #0x80
	add r0, r2, #0x0
	bic r0, r1
	lsl r1, r2, #0x1a
	lsr r1, r1, #0x1f
	lsl r1, r1, #0x1f
	lsr r1, r1, #0x18
	orr r0, r1
	strb r0, [r5, #0x4]
	ldr r0, [sp, #0x0]
	add r1, r0, #0x0
	add r1, r1, #0x1
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	str r1, [sp, #0x0]
	strb r0, [r5, #0x5]
	mov r0, #0xff
	strb r0, [r5, #0x6]
	ldrb r0, [r5, #0x6]
	strb r0, [r5, #0x7]
_02087DEE:
	add r0, r6, #0x1
	lsl r0, r0, #0x18
	lsr r6, r0, #0x18
	cmp r6, #0x64
	blo _02087D60
	ldr r0, [sp, #0x4]
	bl FUN_0200AB18
	add r0, r4, #0x0
	bl FUN_02016A18
	ldr r0, [sp, #0x0]
	strb r0, [r7, #0x0]
	mov r0, #0x5
	strb r0, [r7, #0x3]
	add r0, r7, #0x0
	add sp, #0x10
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02087E14
FUN_02087E14: ; 0x02087E14
	ldr r3, _02087E18 ; =FUN_02016A18
	bx r3
	.balign 4
_02087E18: .word FUN_02016A18

	thumb_func_start FUN_02087E1C
FUN_02087E1C: ; 0x02087E1C
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	beq _02087E3C
	bl FUN_02006290
	cmp r0, #0x0
	beq _02087E3C
	ldr r0, [r4, #0x0]
	bl FUN_02006260
	mov r0, #0x0
	str r0, [r4, #0x0]
	mov r0, #0x1
	pop {r4, pc}
_02087E3C:
	mov r0, #0x0
	pop {r4, pc}

	thumb_func_start FUN_02087E40
FUN_02087E40: ; 0x02087E40
	push {r3-r5, lr}
	add r4, r0, #0x0
	bl FUN_0200628C
	mov r2, #0x1
	add r5, r0, #0x0
	mov r0, #0x3
	mov r1, #0x2c
	lsl r2, r2, #0xc
	bl FUN_0201681C
	add r0, r4, #0x0
	mov r1, #0x18
	mov r2, #0x2c
	bl FUN_02006268
	mov r1, #0x0
	mov r2, #0x18
	add r4, r0, #0x0
	bl MI_CpuFill8
	mov r0, #0x2c
	str r0, [r4, #0x0]
	str r5, [r4, #0xc]
	mov r0, #0x1
	pop {r3-r5, pc}

	thumb_func_start FUN_02087E74
FUN_02087E74: ; 0x02087E74
	push {r4, lr}
	add r4, r1, #0x0
	bl FUN_02006278
	ldr r1, [r4, #0x0]
	cmp r1, #0x8
	bhi _02087EE4
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02087E8E: ; jump table (using 16-bit offset)
	.short _02087EA0 - _02087E8E - 2; case 0
	.short _02087EA8 - _02087E8E - 2; case 1
	.short _02087EB0 - _02087E8E - 2; case 2
	.short _02087EB8 - _02087E8E - 2; case 3
	.short _02087EC0 - _02087E8E - 2; case 4
	.short _02087EC8 - _02087E8E - 2; case 5
	.short _02087ED0 - _02087E8E - 2; case 6
	.short _02087ED8 - _02087E8E - 2; case 7
	.short _02087EE0 - _02087E8E - 2; case 8
_02087EA0:
	bl FUN_02087F50
	str r0, [r4, #0x0]
	b _02087EE4
_02087EA8:
	bl FUN_02087F68
	str r0, [r4, #0x0]
	b _02087EE4
_02087EB0:
	bl FUN_02087FD4
	str r0, [r4, #0x0]
	b _02087EE4
_02087EB8:
	bl FUN_0208805C
	str r0, [r4, #0x0]
	b _02087EE4
_02087EC0:
	bl FUN_020880A0
	str r0, [r4, #0x0]
	b _02087EE4
_02087EC8:
	bl FUN_0208810C
	str r0, [r4, #0x0]
	b _02087EE4
_02087ED0:
	bl FUN_02088130
	str r0, [r4, #0x0]
	b _02087EE4
_02087ED8:
	bl FUN_020881AC
	str r0, [r4, #0x0]
	b _02087EE4
_02087EE0:
	mov r0, #0x1
	pop {r4, pc}
_02087EE4:
	mov r0, #0x0
	pop {r4, pc}

	thumb_func_start FUN_02087EE8
FUN_02087EE8: ; 0x02087EE8
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl FUN_02006278
	add r4, r0, #0x0
	bl FUN_02087F08
	add r0, r5, #0x0
	bl FUN_0200627C
	ldr r0, [r4, #0x0]
	bl FUN_020168D0
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02087F08
FUN_02087F08: ; 0x02087F08
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r2, [r5, #0xc]
	mov r0, #0x0
	ldrb r1, [r2, #0x0]
	add r4, r0, #0x0
	cmp r1, #0x0
	bls _02087F42
	mov r6, #0x1
_02087F1A:
	add r3, r2, #0x0
	add r3, #0x1c
	lsl r1, r4, #0x3
	add r1, r3, r1
	ldrb r3, [r1, #0x4]
	lsl r3, r3, #0x19
	lsr r3, r3, #0x1f
	beq _02087F34
	ldrb r1, [r1, #0x0]
	ldr r0, [r2, #0x8]
	bl FUN_020280B8
	add r0, r6, #0x0
_02087F34:
	add r1, r4, #0x1
	lsl r1, r1, #0x18
	ldr r2, [r5, #0xc]
	lsr r4, r1, #0x18
	ldrb r1, [r2, #0x0]
	cmp r4, r1
	blo _02087F1A
_02087F42:
	cmp r0, #0x0
	beq _02087F4C
	ldr r0, [r2, #0x8]
	bl FUN_020280F4
_02087F4C:
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_02087F50
FUN_02087F50: ; 0x02087F50
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, _02087F64 ; =UNK_020FD15C
	ldr r1, [r4, #0xc]
	ldr r2, [r4, #0x0]
	bl FUN_02006234
	str r0, [r4, #0x14]
	mov r0, #0x1
	pop {r4, pc}
	.balign 4
_02087F64: .word UNK_020FD15C

	thumb_func_start FUN_02087F68
FUN_02087F68: ; 0x02087F68
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x14
	bl FUN_02087E1C
	cmp r0, #0x0
	bne _02087F7A
	mov r0, #0x1
	pop {r3-r5, pc}
_02087F7A:
	ldr r1, [r5, #0xc]
	ldrb r0, [r1, #0x2]
	cmp r0, #0x0
	bne _02087F86
	mov r0, #0x8
	pop {r3-r5, pc}
_02087F86:
	mov r0, #0x0
	strb r0, [r1, #0x2]
	ldr r0, [r5, #0x0]
	mov r1, #0x40
	bl FUN_02016998
	mov r1, #0x0
	mov r2, #0x40
	add r4, r0, #0x0
	bl MI_CpuFill8
	ldr r0, [r5, #0xc]
	mov r1, #0x0
	ldr r0, [r0, #0x10]
	str r0, [r4, #0x0]
	ldr r0, [r5, #0xc]
	ldr r0, [r0, #0x14]
	str r0, [r4, #0x4]
	add r0, r4, #0x0
	add r0, #0x21
	strb r1, [r0, #0x0]
	add r0, r4, #0x0
	mov r1, #0x14
	add r0, #0x20
	strb r1, [r0, #0x0]
	ldr r0, [r5, #0xc]
	add r1, r4, #0x0
	ldr r0, [r0, #0x18]
	str r0, [r4, #0xc]
	ldr r0, _02087FD0 ; =UNK_020F96DC
	ldr r2, [r5, #0x0]
	bl FUN_02006234
	str r0, [r5, #0x14]
	str r4, [r5, #0x10]
	mov r0, #0x2
	pop {r3-r5, pc}
	.balign 4
_02087FD0: .word UNK_020F96DC

	thumb_func_start FUN_02087FD4
FUN_02087FD4: ; 0x02087FD4
	push {r3-r7, lr}
	add r5, r0, #0x0
	add r0, #0x14
	bl FUN_02087E1C
	cmp r0, #0x0
	bne _02087FE6
	mov r0, #0x2
	pop {r3-r7, pc}
_02087FE6:
	ldr r7, [r5, #0x10]
	add r0, r7, #0x0
	add r0, #0x22
	ldrb r6, [r0, #0x0]
	strb r6, [r5, #0x8]
	ldr r0, [r5, #0x10]
	bl FUN_02016A18
	cmp r6, #0x7
	bne _02087FFE
	mov r0, #0x0
	pop {r3-r7, pc}
_02087FFE:
	ldr r0, [r5, #0x0]
	mov r1, #0x30
	bl FUN_02016998
	add r4, r0, #0x0
	ldr r0, [r5, #0xc]
	ldr r0, [r0, #0x10]
	str r0, [r4, #0x0]
	ldr r0, [r5, #0xc]
	ldr r0, [r0, #0x18]
	str r0, [r4, #0x4]
	mov r0, #0x1
	strb r0, [r4, #0x11]
	strb r6, [r4, #0x14]
	ldr r0, [r4, #0x0]
	bl FUN_0206B9AC
	strb r0, [r4, #0x13]
	mov r1, #0x0
	strh r1, [r4, #0x18]
	mov r0, #0x3
	strb r0, [r4, #0x12]
	mov r0, #0x1
	str r0, [r4, #0x2c]
	str r1, [r4, #0x28]
	ldr r1, _02088054 ; =UNK_020FD158
	add r0, r4, #0x0
	bl FUN_0207B000
	ldr r1, [r5, #0xc]
	add r0, r4, #0x0
	ldr r1, [r1, #0xc]
	bl FUN_0207C2A4
	ldr r0, _02088058 ; =UNK_020FA6E8
	ldr r2, [r5, #0x0]
	add r1, r7, #0x0
	bl FUN_02006234
	str r0, [r5, #0x14]
	str r4, [r5, #0x10]
	mov r0, #0x3
	pop {r3-r7, pc}
	.balign 4
_02088054: .word UNK_020FD158
_02088058: .word UNK_020FA6E8

	thumb_func_start FUN_0208805C
FUN_0208805C: ; 0x0208805C
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x14
	bl FUN_02087E1C
	cmp r0, #0x0
	bne _0208806E
	mov r0, #0x3
	pop {r3-r5, pc}
_0208806E:
	ldr r0, [r5, #0x10]
	ldrb r4, [r0, #0x17]
	ldrb r0, [r0, #0x14]
	strb r0, [r5, #0x8]
	ldr r0, [r5, #0x10]
	bl FUN_02016A18
	cmp r4, #0x1
	bne _02088084
	mov r0, #0x0
	pop {r3-r5, pc}
_02088084:
	ldr r0, [r5, #0xc]
	add r3, r0, #0x0
	ldrb r0, [r0, #0x1]
	add r3, #0x20
	lsl r2, r0, #0x3
	ldrb r1, [r3, r2]
	mov r0, #0x40
	orr r0, r1
	strb r0, [r3, r2]
	ldr r0, [r5, #0xc]
	mov r1, #0x1
	strb r1, [r0, #0x2]
	mov r0, #0x4
	pop {r3-r5, pc}

	thumb_func_start FUN_020880A0
FUN_020880A0: ; 0x020880A0
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x0]
	mov r1, #0xc
	bl FUN_02016998
	mov r1, #0x0
	mov r2, #0xc
	add r4, r0, #0x0
	bl MI_CpuFill8
	ldr r1, [r5, #0xc]
	ldrb r0, [r1, #0x1]
	lsl r0, r0, #0x3
	add r0, r1, r0
	ldrb r0, [r0, #0x1e]
	strh r0, [r4, #0x8]
	ldr r2, [r5, #0xc]
	ldrb r1, [r2, #0x1]
	ldr r0, [r2, #0x8]
	lsl r1, r1, #0x3
	add r1, r2, r1
	ldrb r1, [r1, #0x1c]
	ldr r2, [r5, #0x0]
	bl FUN_02028190
	str r0, [r4, #0x4]
	ldr r0, [r5, #0xc]
	ldrb r1, [r5, #0x8]
	ldr r0, [r0, #0x10]
	bl FUN_0206B9B0
	str r0, [r4, #0x0]
	ldr r0, [r5, #0xc]
	ldr r0, [r0, #0x18]
	bl FUN_02024FF4
	strb r0, [r4, #0xa]
	ldr r0, [r5, #0xc]
	ldr r0, [r0, #0x18]
	bl FUN_02025084
	strb r0, [r4, #0xb]
	ldr r0, _02088108 ; =UNK_020FD16C
	ldr r2, [r5, #0x0]
	add r1, r4, #0x0
	bl FUN_02006234
	str r0, [r5, #0x14]
	str r4, [r5, #0x10]
	mov r0, #0x5
	pop {r3-r5, pc}
	.balign 4
_02088108: .word UNK_020FD16C

	thumb_func_start FUN_0208810C
FUN_0208810C: ; 0x0208810C
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x14
	bl FUN_02087E1C
	cmp r0, #0x0
	bne _0208811E
	mov r0, #0x5
	pop {r4, pc}
_0208811E:
	ldr r4, [r4, #0x10]
	ldr r0, [r4, #0x4]
	bl FUN_02016A18
	add r0, r4, #0x0
	bl FUN_02016A18
	mov r0, #0x6
	pop {r4, pc}

	thumb_func_start FUN_02088130
FUN_02088130: ; 0x02088130
	push {r4-r6, lr}
	add r5, r0, #0x0
	ldr r0, [r5, #0x0]
	mov r1, #0x30
	bl FUN_02016998
	ldr r2, [r5, #0xc]
	add r4, r0, #0x0
	ldrb r1, [r2, #0x1]
	ldr r0, [r2, #0x8]
	lsl r1, r1, #0x3
	add r1, r2, r1
	ldrb r1, [r1, #0x1c]
	ldr r2, [r5, #0x0]
	bl FUN_02028190
	add r6, r0, #0x0
	ldr r0, [r5, #0xc]
	ldr r0, [r0, #0x10]
	str r0, [r4, #0x0]
	ldr r0, [r5, #0xc]
	ldr r0, [r0, #0x18]
	str r0, [r4, #0x4]
	mov r0, #0x1
	strb r0, [r4, #0x11]
	ldrb r0, [r5, #0x8]
	strb r0, [r4, #0x14]
	ldr r0, [r4, #0x0]
	bl FUN_0206B9AC
	strb r0, [r4, #0x13]
	mov r1, #0x0
	strh r1, [r4, #0x18]
	mov r0, #0x4
	strb r0, [r4, #0x12]
	str r6, [r4, #0x24]
	mov r0, #0x1
	str r0, [r4, #0x2c]
	str r1, [r4, #0x28]
	ldr r1, _020881A4 ; =UNK_020FD154
	add r0, r4, #0x0
	bl FUN_0207B000
	ldr r1, [r5, #0xc]
	add r0, r4, #0x0
	ldr r1, [r1, #0xc]
	bl FUN_0207C2A4
	ldr r0, _020881A8 ; =UNK_020FA6E8
	ldr r2, [r5, #0x0]
	add r1, r4, #0x0
	bl FUN_02006234
	str r0, [r5, #0x14]
	str r4, [r5, #0x10]
	mov r0, #0x7
	pop {r4-r6, pc}
	nop
_020881A4: .word UNK_020FD154
_020881A8: .word UNK_020FA6E8

	thumb_func_start FUN_020881AC
FUN_020881AC: ; 0x020881AC
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x14
	bl FUN_02087E1C
	cmp r0, #0x0
	bne _020881BE
	mov r0, #0x7
	pop {r4, pc}
_020881BE:
	ldr r0, [r4, #0x10]
	ldr r0, [r0, #0x24]
	bl FUN_02016A18
	ldr r0, [r4, #0x10]
	bl FUN_02016A18
	mov r0, #0x0
	pop {r4, pc}

	thumb_func_start FUN_020881D0
FUN_020881D0: ; 0x020881D0
	push {r3-r5, lr}
	sub sp, #0x8
	lsl r2, r1, #0x1
	ldr r1, _02088214 ; =UNK_020FD17C
	ldrb r4, [r1, r2]
	ldr r1, _02088218 ; =UNK_020FD17D
	ldrb r5, [r1, r2]
	cmp r4, #0x5
	bne _020881E8
	add sp, #0x8
	mov r0, #0x2
	pop {r3-r5, pc}
_020881E8:
	add r1, sp, #0x0
	bl FUN_02027FBC
	add r0, r4, #0x1
	add r2, sp, #0x0
	ldrb r1, [r2, r0]
	add r0, r5, #0x1
	ldrb r0, [r2, r0]
	cmp r1, r0
	bne _02088202
	add sp, #0x8
	mov r0, #0x2
	pop {r3-r5, pc}
_02088202:
	cmp r1, r0
	bls _0208820C
	add sp, #0x8
	mov r0, #0x0
	pop {r3-r5, pc}
_0208820C:
	mov r0, #0x1
	add sp, #0x8
	pop {r3-r5, pc}
	nop
_02088214: .word UNK_020FD17C
_02088218: .word UNK_020FD17D

	thumb_func_start FUN_0208821C
FUN_0208821C: ; 0x0208821C
	push {r3-r7, lr}
	sub sp, #0x30
	add r6, r1, #0x0
	add r4, r0, #0x0
	add r0, r6, #0x0
	bl FUN_02068854
	lsl r1, r0, #0x1
	ldr r0, _02088310 ; =UNK_020FD17C
	ldrb r0, [r0, r1]
	str r0, [sp, #0x4]
	ldr r0, _02088314 ; =UNK_020FD17D
	ldrb r0, [r0, r1]
	add r1, sp, #0x10
	str r0, [sp, #0x0]
	add r0, r4, #0x0
	bl FUN_02027FBC
	mov r4, #0x0
	add r7, r4, #0x0
	add r5, sp, #0x18
_02088246:
	add r1, r4, #0x0
	add r0, r6, #0x0
	add r1, #0x13
	add r2, r7, #0x0
	bl FUN_020671BC
	lsl r1, r4, #0x2
	str r0, [r5, r1]
	add r0, r4, #0x1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #0x6
	blo _02088246
	add r4, sp, #0x8
	mov r1, #0x0
	mov r3, #0x1
	add r0, sp, #0x10
	add r4, #0x1
_0208826A:
	ldrb r5, [r0, r3]
	add r2, r1, #0x0
	add r1, r1, #0x1
	strb r5, [r4, r2]
	add r2, r3, #0x1
	lsl r2, r2, #0x18
	lsl r1, r1, #0x18
	lsr r3, r2, #0x18
	lsr r1, r1, #0x18
	cmp r3, #0x6
	bls _0208826A
	ldr r0, [sp, #0x4]
	cmp r0, #0x5
	beq _020882B8
	ldrb r0, [r4, r0]
	bl _ffltu
	add r1, r0, #0x0
	ldr r0, _02088318 ; =0x3F8CCCCD
	bl _fmul
	bl _ffixu
	ldr r1, [sp, #0x4]
	strb r0, [r4, r1]
	add r4, sp, #0x8
	ldr r0, [sp, #0x0]
	add r4, #0x1
	ldrb r0, [r4, r0]
	bl _ffltu
	add r1, r0, #0x0
	ldr r0, _0208831C ; =0x3F666666
	bl _fmul
	bl _ffixu
	ldr r1, [sp, #0x0]
	strb r0, [r4, r1]
_020882B8:
	add r7, sp, #0x8
	mov r5, #0x0
	add r4, sp, #0x18
	add r7, #0x1
_020882C0:
	lsl r2, r5, #0x2
	ldrb r0, [r7, r5]
	ldr r1, [r4, r2]
	add r0, r1, r0
	str r0, [r4, r2]
	ldr r0, [r4, r2]
	cmp r0, #0xff
	ble _020882D4
	mov r0, #0xff
	str r0, [r4, r2]
_020882D4:
	add r1, r5, #0x0
	add r0, r6, #0x0
	add r1, #0x13
	add r2, r4, r2
	bl FUN_02067830
	add r0, r5, #0x1
	lsl r0, r0, #0x18
	lsr r5, r0, #0x18
	cmp r5, #0x6
	blo _020882C0
	add r0, r6, #0x0
	mov r1, #0x9
	mov r2, #0x0
	bl FUN_020671BC
	add r1, sp, #0x8
	strb r0, [r1, #0x0]
	ldrb r0, [r1, #0x0]
	cmp r0, #0xff
	bhs _0208830C
	add r0, r0, #0x1
	strb r0, [r1, #0x0]
	add r0, r6, #0x0
	mov r1, #0x9
	add r2, sp, #0x8
	bl FUN_02067830
_0208830C:
	add sp, #0x30
	pop {r3-r7, pc}
	.balign 4
_02088310: .word UNK_020FD17C
_02088314: .word UNK_020FD17D
_02088318: .word 0x3F8CCCCD
_0208831C: .word 0x3F666666
