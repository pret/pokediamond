	.include "asm/macros.inc"
	.include "global.inc"

	.extern UNK_020ECD4C
	.extern FX_SinCosTable_

	.section .rodata

	.global UNK_020ECBD0
UNK_020ECBD0: ; 0x020ECBD0
	.byte 0xA0, 0x00, 0x00, 0x00, 0xA0, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00, 0xB0, 0x00, 0x00, 0x00
	.byte 0xA0, 0x00, 0x00, 0x00, 0xA0, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00, 0xB0, 0x00, 0x00, 0x00
	.byte 0xA0, 0x00, 0x00, 0x00, 0xB0, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00
	.byte 0xA0, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00, 0xD0, 0x00, 0x00, 0x00

	.global UNK_020ECC10
UNK_020ECC10: ; 0x020ECC10
	.byte 0x1E, 0x21, 0x1F, 0x21, 0x20, 0x21, 0x1D, 0x22, 0x1E, 0x22, 0x1F, 0x22, 0x20, 0x22, 0x21, 0x22
	.byte 0x1C, 0x23, 0x1D, 0x23, 0x1E, 0x23, 0x1F, 0x23, 0x20, 0x23, 0x21, 0x23, 0x22, 0x23, 0x1C, 0x24
	.byte 0x1D, 0x24, 0x1E, 0x24, 0x1F, 0x24, 0x20, 0x24, 0x21, 0x24, 0x22, 0x24, 0x1C, 0x25, 0x1D, 0x25
	.byte 0x1E, 0x25, 0x1F, 0x25, 0x20, 0x25, 0x21, 0x25, 0x22, 0x25, 0x1C, 0x26, 0x1D, 0x26, 0x1E, 0x26
	.byte 0x1F, 0x26, 0x20, 0x26, 0x21, 0x26, 0x22, 0x26, 0x1C, 0x27, 0x1D, 0x27, 0x1E, 0x27, 0x1F, 0x27
	.byte 0x20, 0x27, 0x21, 0x27, 0x22, 0x27, 0x1D, 0x28, 0x1E, 0x28, 0x1F, 0x28, 0x20, 0x28, 0x21, 0x28
	.byte 0x1E, 0x29, 0x1F, 0x29, 0x20, 0x29, 0xFF, 0xFF

	.global UNK_020ECC78
UNK_020ECC78: ; 0x020ECC78
	.byte 0x33, 0x11, 0x34, 0x11, 0x35, 0x11, 0x36, 0x11, 0x32, 0x12, 0x33, 0x12, 0x34, 0x12, 0x35, 0x12
	.byte 0x36, 0x12, 0x37, 0x12, 0x31, 0x13, 0x32, 0x13, 0x33, 0x13, 0x34, 0x13, 0x35, 0x13, 0x36, 0x13
	.byte 0x37, 0x13, 0x38, 0x13, 0x31, 0x14, 0x32, 0x14, 0x33, 0x14, 0x34, 0x14, 0x35, 0x14, 0x36, 0x14
	.byte 0x37, 0x14, 0x38, 0x14, 0x31, 0x15, 0x32, 0x15, 0x33, 0x15, 0x34, 0x15, 0x35, 0x15, 0x36, 0x15
	.byte 0x37, 0x15, 0x38, 0x15, 0x31, 0x16, 0x32, 0x16, 0x33, 0x16, 0x34, 0x16, 0x35, 0x16, 0x36, 0x16
	.byte 0x37, 0x16, 0x38, 0x16, 0x32, 0x17, 0x33, 0x17, 0x34, 0x17, 0x35, 0x17, 0x36, 0x17, 0x37, 0x17
	.byte 0x33, 0x18, 0x34, 0x18, 0x35, 0x18, 0x36, 0x18, 0xFF, 0xFF

	.global UNK_020ECCE2
UNK_020ECCE2: ; 0x020ECCE2
	.byte 0x1B, 0x0F, 0x1C, 0x0F, 0x1D, 0x0F, 0x1E, 0x0F, 0x1A, 0x10, 0x1B, 0x10, 0x1C, 0x10, 0x1D, 0x10
	.byte 0x1E, 0x10, 0x1F, 0x10, 0x19, 0x11, 0x1A, 0x11, 0x1B, 0x11, 0x1C, 0x11, 0x1D, 0x11, 0x1E, 0x11
	.byte 0x1F, 0x11, 0x20, 0x11, 0x19, 0x12, 0x1A, 0x12, 0x1B, 0x12, 0x1C, 0x12, 0x1D, 0x12, 0x1E, 0x12
	.byte 0x1F, 0x12, 0x20, 0x12, 0x19, 0x13, 0x1A, 0x13, 0x1B, 0x13, 0x1C, 0x13, 0x1D, 0x13, 0x1E, 0x13
	.byte 0x1F, 0x13, 0x20, 0x13, 0x19, 0x14, 0x1A, 0x14, 0x1B, 0x14, 0x1C, 0x14, 0x1D, 0x14, 0x1E, 0x14
	.byte 0x1F, 0x14, 0x20, 0x14, 0x1A, 0x15, 0x1B, 0x15, 0x1C, 0x15, 0x1D, 0x15, 0x1E, 0x15, 0x1F, 0x15
	.byte 0x1B, 0x16, 0x1C, 0x16, 0x1D, 0x16, 0x1E, 0x16, 0xFF, 0xFF

	.global UNK_020ECD4C
UNK_020ECD4C: ; 0x020ECD4C
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00
	.byte 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xA0, 0x00, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0xA0, 0x00, 0x00, 0x00
	.byte 0x50, 0x00, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0xA0, 0x00, 0x00, 0x00, 0xA0, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0xA0, 0x00, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00
	.byte 0x50, 0x00, 0x00, 0x00, 0xA0, 0x00, 0x00, 0x00, 0xA0, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00
	.byte 0xA0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00
	.byte 0xA0, 0x00, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0xA0, 0x00, 0x00, 0x00

	.global UNK_020ECDCC
UNK_020ECDCC: ; 0x020ECDCC
	.byte 0x2B, 0x21, 0x2C, 0x21, 0x2D, 0x21, 0x29, 0x22, 0x2A, 0x22, 0x2B, 0x22, 0x2C, 0x22, 0x2D, 0x22
	.byte 0x2E, 0x22, 0x2F, 0x22, 0x28, 0x23, 0x29, 0x23, 0x2A, 0x23, 0x2B, 0x23, 0x2C, 0x23, 0x2D, 0x23
	.byte 0x2E, 0x23, 0x2F, 0x23, 0x30, 0x23, 0x28, 0x24, 0x29, 0x24, 0x2A, 0x24, 0x2B, 0x24, 0x2C, 0x24
	.byte 0x2D, 0x24, 0x2E, 0x24, 0x2F, 0x24, 0x30, 0x24, 0x28, 0x25, 0x29, 0x25, 0x2A, 0x25, 0x2B, 0x25
	.byte 0x2C, 0x25, 0x2D, 0x25, 0x2E, 0x25, 0x2F, 0x25, 0x30, 0x25, 0x28, 0x26, 0x29, 0x26, 0x2A, 0x26
	.byte 0x2B, 0x26, 0x2C, 0x26, 0x2D, 0x26, 0x2E, 0x26, 0x2F, 0x26, 0x30, 0x26, 0x28, 0x27, 0x29, 0x27
	.byte 0x2A, 0x27, 0x2B, 0x27, 0x2C, 0x27, 0x2D, 0x27, 0x2E, 0x27, 0x2F, 0x27, 0x30, 0x27, 0x28, 0x28
	.byte 0x29, 0x28, 0x2A, 0x28, 0x2B, 0x28, 0x2C, 0x28, 0x2D, 0x28, 0x2E, 0x28, 0x2F, 0x28, 0x30, 0x28
	.byte 0x29, 0x29, 0x2A, 0x29, 0x2B, 0x29, 0x2C, 0x29, 0x2D, 0x29, 0x2E, 0x29, 0x2F, 0x29, 0x2B, 0x2A
	.byte 0x2C, 0x2A, 0x2D, 0x2A, 0xFF, 0xFF, 0x00, 0x00

	.section .data

	.global UNK_02105AE8
UNK_02105AE8: ; 0x02105AE8
	.word UNK_020ECCE2
	.word UNK_020ECC78
	.word UNK_020ECC10
	.word UNK_020ECDCC

	.text

	thumb_func_start FUN_02006D98
FUN_02006D98: ; 0x02006D98
	push {r3-r7, lr}
	sub sp, #0x10
	mov r1, #0xba
	lsl r1, r1, #0x2
	add r5, r0, #0x0
	bl AllocFromHeap
	add r4, r0, #0x0
	mov r0, #0xa6
	lsl r0, r0, #0x2
	add r1, r0, #0x0
	add r3, r0, #0x0
	str r5, [r4, r0]
	mov r2, #0x0
	add r1, #0x48
	strb r2, [r4, r1]
	add r1, r0, #0x4
	str r2, [r4, r1]
	mov r1, #0x2
	lsl r1, r1, #0xe
	add r3, #0x8
	str r1, [r4, r3]
	add r3, r0, #0x0
	add r3, #0xc
	str r2, [r4, r3]
	mov r2, #0x80
	add r0, #0x10
	str r2, [r4, r0]
	add r0, r5, #0x0
	bl AllocFromHeap
	mov r1, #0xab
	lsl r1, r1, #0x2
	str r0, [r4, r1]
	add r0, r5, #0x0
	mov r1, #0xc0
	bl AllocFromHeap
	mov r1, #0x2b
	lsl r1, r1, #0x4
	str r0, [r4, r1]
	ldr r1, [r4, r1]
	mov r0, #0x0
	mov r2, #0x4
	bl MIi_CpuClearFast
	add r0, r5, #0x0
	mov r1, #0xc0
	bl AllocFromHeap
	mov r1, #0xad
	lsl r1, r1, #0x2
	str r0, [r4, r1]
	ldr r1, [r4, r1]
	mov r0, #0x0
	mov r2, #0x4
	bl MIi_CpuClearFast
	mov r6, #0x0
	add r5, r4, #0x0
	add r7, r6, #0x0
_02006E12:
	add r0, r7, #0x0
	add r1, r5, #0x0
	mov r2, #0x98
	bl MIi_CpuClearFast
	add r6, r6, #0x1
	add r5, #0x98
	cmp r6, #0x4
	blt _02006E12
	bl NNS_G2dSetupSoftwareSpriteCamera
	ldr r2, _02006EC8 ; =0x000002E3
	mov r0, #0x0
	strb r0, [r4, r2]
	sub r2, #0x4b
	ldr r2, [r4, r2]
	mov r0, #0x75 ; NARC_POKETOOL_POKEGRA_OTHERPOKE
	mov r1, #0xd3
	bl AllocAndReadWholeNarcMemberByIdPair
	add r1, sp, #0xc
	str r0, [sp, #0x4]
	bl NNS_G2dGetUnpackedCharacterData
	ldr r0, [sp, #0xc]
	mov r1, #0xaf
	ldr r0, [r0, #0x4]
	lsl r1, r1, #0x2
	str r0, [r4, r1]
	ldr r0, [sp, #0xc]
	ldr r2, [r0, #0x8]
	add r0, r1, #0x4
	str r2, [r4, r0]
	ldr r0, [sp, #0xc]
	add r1, #0x8
	ldr r0, [r0, #0xc]
	str r0, [r4, r1]
	ldr r0, [sp, #0xc]
	ldr r0, [r0, #0x14]
	str r0, [sp, #0x8]
	bl FUN_02008A74
	ldr r1, [sp, #0x8]
	mov r0, #0xab
	lsl r0, r0, #0x2
	mov r2, #0x2
	ldrb r1, [r1, #0x0]
	ldr r0, [r4, r0]
	lsl r2, r2, #0xe
	bl MI_CpuFill8
	mov r0, #0x0
	mov r7, #0xab
	ldr r6, _02006ECC ; =0x00005050
	mov r12, r0
	str r0, [sp, #0x0]
	add r3, r0, #0x0
	lsl r7, r7, #0x2
_02006E86:
	ldr r2, [sp, #0x8]
	ldr r0, [sp, #0x0]
	mov r1, #0x0
	add r2, r2, r0
_02006E8E:
	ldr r5, [r4, r7]
	ldrb r0, [r2, #0x0]
	add r5, r3, r5
	add r5, r1, r5
	add r1, r1, #0x1
	add r2, r2, #0x1
	strb r0, [r5, r6]
	cmp r1, #0x28
	blt _02006E8E
	ldr r0, [sp, #0x0]
	add r3, #0x80
	add r0, #0x50
	str r0, [sp, #0x0]
	mov r0, r12
	add r0, r0, #0x1
	mov r12, r0
	cmp r0, #0x50
	blt _02006E86
	ldr r0, [sp, #0x4]
	bl FreeToHeap
	ldr r0, _02006ED0 ; =0x000002E1
	mov r1, #0x1
	strb r1, [r4, r0]
	add r0, r0, #0x1
	strb r1, [r4, r0]
	add r0, r4, #0x0
	add sp, #0x10
	pop {r3-r7, pc}
	.balign 4
_02006EC8: .word 0x000002E3
_02006ECC: .word 0x00005050
_02006ED0: .word 0x000002E1

	thumb_func_start FUN_02006ED4
FUN_02006ED4: ; 0x02006ED4
	push {r3-r7, lr}
	sub sp, #0x20
	add r5, r0, #0x0
	bl FUN_020082A8
	add r0, r5, #0x0
	bl FUN_020086F4
	bl NNS_G3dGeFlushBuffer
	mov r6, #0x9f
	mov r0, #0x0
	ldr r4, _02007250 ; =0x04000444
	lsl r6, r6, #0x2
	str r0, [r4, #0x0]
	str r0, [sp, #0x18]
	add r0, r6, #0x0
	sub r0, #0xc
	ldr r1, [r5, r0]
	add r3, r6, #0x0
	ldr r2, [r5, r6]
	add r0, r6, #0x0
	sub r3, #0x8
	add r6, #0x20
	ldr r3, [r5, r3]
	ldr r6, [r5, r6]
	sub r0, #0x10
	ldr r0, [r5, r0]
	lsr r6, r6, #0x3
	lsl r3, r3, #0x1a
	orr r6, r3
	mov r3, #0x1
	lsl r3, r3, #0x1e
	lsl r0, r0, #0x14
	orr r3, r6
	lsl r1, r1, #0x17
	orr r0, r3
	lsl r2, r2, #0x1d
	orr r0, r1
	orr r0, r2
	str r0, [r4, #0x64]
	ldr r0, [sp, #0x18]
	add r4, r5, #0x0
	str r0, [sp, #0x14]
	ldr r0, _02007254 ; =UNK_020ECD4C
	str r0, [sp, #0x1c]
_02006F30:
	ldr r0, [r4, #0x0]
	lsl r0, r0, #0x1f
	lsr r0, r0, #0x1f
	beq _02006F46
	ldr r0, [r4, #0x54]
	lsl r1, r0, #0x1f
	lsr r1, r1, #0x1f
	bne _02006F46
	lsl r0, r0, #0x14
	lsr r0, r0, #0x1f
	beq _02006F48
_02006F46:
	b _020072BC
_02006F48:
	ldr r2, [r4, #0x68]
	cmp r2, #0x0
	beq _02006F56
	add r1, r4, #0x0
	add r0, r4, #0x0
	add r1, #0x24
	blx r2
_02006F56:
	bl NNS_G3dGeFlushBuffer
	ldr r0, _02007258 ; =0x000002E3
	ldrb r0, [r5, r0]
	cmp r0, #0x1
	beq _02006F68
	ldr r0, _0200725C ; =0x04000454
	mov r1, #0x0
	str r1, [r0, #0x0]
_02006F68:
	add r0, r4, #0x0
	bl FUN_02007F48
	mov r0, #0x9d
	lsl r0, r0, #0x2
	ldr r0, [r5, r0]
	cmp r0, #0x2
	bne _02006F7C
	mov r0, #0x1
	b _02006F7E
_02006F7C:
	mov r0, #0x0
_02006F7E:
	mov r1, #0xa9
	lsl r1, r1, #0x2
	ldr r2, [r5, r1]
	ldr r1, [sp, #0x14]
	add r2, r2, r1
	mov r1, #0x4
	sub r0, r1, r0
	add r1, r2, #0x0
	lsr r1, r0
	ldr r0, _02007260 ; =0x040004AC
	str r1, [r0, #0x0]
	ldr r0, [r4, #0x28]
	lsl r1, r0, #0xc
	mov r0, #0x26
	ldrsh r2, [r4, r0]
	mov r0, #0x42
	ldrsh r0, [r4, r0]
	add r0, r2, r0
	mov r2, #0x24
	ldrsh r3, [r4, r2]
	mov r2, #0x40
	ldrsh r2, [r4, r2]
	lsl r0, r0, #0xc
	add r2, r3, r2
	lsl r3, r2, #0xc
	ldr r2, _02007264 ; =0x04000470
	str r3, [r2, #0x0]
	str r0, [r2, #0x0]
	add r0, r2, #0x0
	str r1, [r0, #0x0]
	ldrh r0, [r4, #0x38]
	asr r0, r0, #0x4
	lsl r1, r0, #0x2
	ldr r0, _02007268 ; =FX_SinCosTable_
	add r2, r0, r1
	ldrsh r0, [r0, r1]
	mov r1, #0x2
	ldrsh r1, [r2, r1]
	bl G3_RotX
	ldrh r0, [r4, #0x3a]
	asr r0, r0, #0x4
	lsl r1, r0, #0x2
	ldr r0, _02007268 ; =FX_SinCosTable_
	add r2, r0, r1
	ldrsh r0, [r0, r1]
	mov r1, #0x2
	ldrsh r1, [r2, r1]
	bl G3_RotY
	ldrh r0, [r4, #0x3c]
	asr r0, r0, #0x4
	lsl r1, r0, #0x2
	ldr r0, _02007268 ; =FX_SinCosTable_
	add r2, r0, r1
	ldrsh r0, [r0, r1]
	mov r1, #0x2
	ldrsh r1, [r2, r1]
	bl G3_RotZ
	ldr r0, [r4, #0x28]
	lsl r0, r0, #0xc
	neg r1, r0
	mov r0, #0x26
	ldrsh r2, [r4, r0]
	mov r0, #0x42
	ldrsh r0, [r4, r0]
	add r0, r2, r0
	mov r2, #0x24
	ldrsh r3, [r4, r2]
	mov r2, #0x40
	ldrsh r2, [r4, r2]
	lsl r0, r0, #0xc
	neg r0, r0
	add r2, r3, r2
	lsl r2, r2, #0xc
	neg r3, r2
	ldr r2, _02007264 ; =0x04000470
	str r3, [r2, #0x0]
	str r0, [r2, #0x0]
	add r0, r2, #0x0
	str r1, [r0, #0x0]
	ldr r3, [r4, #0x50]
	lsl r0, r3, #0x11
	lsr r0, r0, #0x1b
	lsl r2, r3, #0x16
	lsl r1, r0, #0xa
	lsl r0, r3, #0x1b
	lsr r2, r2, #0x1b
	lsr r0, r0, #0x1b
	lsl r2, r2, #0x5
	orr r0, r2
	orr r0, r1
	lsl r0, r0, #0x10
	lsr r2, r0, #0x10
	lsl r0, r3, #0x2
	lsr r0, r0, #0x1b
	lsl r1, r0, #0xa
	lsl r0, r3, #0xc
	lsl r3, r3, #0x7
	lsr r3, r3, #0x1b
	lsr r0, r0, #0x1b
	lsl r3, r3, #0x5
	orr r0, r3
	orr r0, r1
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	lsl r0, r0, #0x10
	add r1, r2, #0x0
	orr r1, r0
	mov r0, #0x2
	lsl r0, r0, #0xe
	orr r1, r0
	ldr r0, _0200726C ; =0x040004C0
	str r1, [r0, #0x0]
	ldr r1, _02007270 ; =0x00004210
	add r0, r0, #0x4
	str r1, [r0, #0x0]
	ldr r1, [r4, #0x0]
	ldr r0, [r4, #0x54]
	lsl r1, r1, #0x19
	lsl r0, r0, #0x19
	lsr r1, r1, #0x1a
	lsr r0, r0, #0x1b
	lsl r2, r1, #0x18
	mov r1, #0xc0
	lsl r0, r0, #0x10
	orr r1, r2
	orr r1, r0
	ldr r0, _02007274 ; =0x040004A4
	str r1, [r0, #0x0]
	ldr r0, [r4, #0x54]
	lsl r0, r0, #0x1e
	lsr r0, r0, #0x1f
	beq _02007104
	add r0, r4, #0x0
	add r0, #0x5b
	ldrb r0, [r0, #0x0]
	add r2, r4, #0x0
	add r2, #0x44
	lsl r1, r0, #0x4
	ldr r0, [sp, #0x1c]
	ldrb r3, [r2, #0x0]
	add r0, r0, r1
	ldr r2, [sp, #0x1c]
	ldr r0, [r0, #0x4]
	ldr r1, [r2, r1]
	add r6, r3, r1
	add r1, r4, #0x0
	add r1, #0x46
	ldrb r1, [r1, #0x0]
	mov r12, r1
	add r1, r4, #0x0
	add r1, #0x45
	ldrb r2, [r1, #0x0]
	add r1, r2, r0
	add r0, r4, #0x0
	add r0, #0x47
	ldrb r7, [r0, #0x0]
	mov r0, r12
	add r0, r0, r6
	str r7, [sp, #0x0]
	str r6, [sp, #0x4]
	str r1, [sp, #0x8]
	str r0, [sp, #0xc]
	add r0, r7, r1
	str r0, [sp, #0x10]
	mov r1, #0x24
	ldrsh r1, [r4, r1]
	mov r0, #0x2c
	ldrsh r0, [r4, r0]
	sub r1, #0x28
	add r1, r1, r3
	add r0, r0, r1
	mov r3, #0x26
	ldrsh r3, [r4, r3]
	mov r1, #0x2e
	lsl r0, r0, #0x10
	sub r3, #0x28
	add r2, r3, r2
	ldrsh r1, [r4, r1]
	ldr r3, [r4, #0x28]
	asr r0, r0, #0x10
	add r2, r1, r2
	mov r1, #0x6e
	ldrsb r1, [r4, r1]
	sub r1, r2, r1
	ldr r2, [r4, #0x30]
	lsl r1, r1, #0x10
	add r2, r3, r2
	asr r1, r1, #0x10
	mov r3, r12
	bl NNS_G2dDrawSpriteFast
	b _02007174
_02007104:
	mov r0, #0x34
	ldrsh r1, [r4, r0]
	mov r0, #0x50
	ldr r2, [sp, #0x1c]
	mul r0, r1
	asr r3, r0, #0x8
	mov r0, #0x36
	ldrsh r1, [r4, r0]
	mov r0, #0x50
	ldr r6, [sp, #0x1c]
	mul r0, r1
	asr r1, r0, #0x8
	add r0, r4, #0x0
	add r0, #0x5b
	ldrb r0, [r0, #0x0]
	lsl r0, r0, #0x4
	str r1, [sp, #0x0]
	add r2, r2, r0
	ldr r0, [r6, r0]
	lsr r6, r1, #0x1f
	str r0, [sp, #0x4]
	ldr r0, [r2, #0x4]
	add r6, r1, r6
	str r0, [sp, #0x8]
	ldr r0, [r2, #0x8]
	asr r1, r6, #0x1
	str r0, [sp, #0xc]
	ldr r0, [r2, #0xc]
	str r0, [sp, #0x10]
	mov r0, #0x24
	ldrsh r2, [r4, r0]
	lsr r0, r3, #0x1f
	add r0, r3, r0
	asr r0, r0, #0x1
	sub r2, r2, r0
	mov r0, #0x2c
	ldrsh r0, [r4, r0]
	ldr r6, [r4, #0x28]
	add r0, r2, r0
	mov r2, #0x26
	ldrsh r2, [r4, r2]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	sub r2, r2, r1
	mov r1, #0x2e
	ldrsh r1, [r4, r1]
	add r2, r2, r1
	mov r1, #0x6e
	ldrsb r1, [r4, r1]
	sub r1, r2, r1
	ldr r2, [r4, #0x30]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add r2, r6, r2
	bl NNS_G2dDrawSpriteFast
_02007174:
	add r0, r4, #0x0
	add r0, #0x6c
	ldrh r0, [r0, #0x0]
	lsl r1, r0, #0x1e
	lsr r1, r1, #0x1e
	beq _0200719A
	lsl r0, r0, #0x19
	lsr r0, r0, #0x1e
	beq _0200719A
	ldr r0, [r4, #0x54]
	lsl r0, r0, #0x1e
	lsr r0, r0, #0x1f
	bne _0200719A
	mov r0, #0xb9
	lsl r0, r0, #0x2
	ldr r1, [r5, r0]
	mov r0, #0x1
	tst r0, r1
	beq _0200719C
_0200719A:
	b _020072BC
_0200719C:
	ldr r0, _02007258 ; =0x000002E3
	ldrb r0, [r5, r0]
	cmp r0, #0x1
	beq _020071AA
	ldr r0, _0200725C ; =0x04000454
	mov r1, #0x0
	str r1, [r0, #0x0]
_020071AA:
	mov r0, #0x9d
	lsl r0, r0, #0x2
	ldr r0, [r5, r0]
	cmp r0, #0x2
	bne _020071B8
	mov r1, #0x1
	b _020071BA
_020071B8:
	mov r1, #0x0
_020071BA:
	add r2, r4, #0x0
	add r2, #0x6c
	ldrh r2, [r2, #0x0]
	mov r0, #0xa9
	lsl r0, r0, #0x2
	lsl r2, r2, #0x1e
	lsr r2, r2, #0x1e
	add r2, r2, #0x3
	ldr r0, [r5, r0]
	lsl r2, r2, #0x5
	add r2, r0, r2
	mov r0, #0x4
	sub r0, r0, r1
	add r1, r2, #0x0
	lsr r1, r0
	ldr r0, _02007260 ; =0x040004AC
	str r1, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x6c
	ldrh r0, [r0, #0x0]
	lsl r0, r0, #0x1b
	lsr r0, r0, #0x1f
	beq _020071FA
	mov r0, #0x34
	ldrsh r0, [r4, r0]
	lsl r0, r0, #0x6
	asr r3, r0, #0x8
	mov r0, #0x36
	ldrsh r0, [r4, r0]
	lsl r0, r0, #0x4
	asr r1, r0, #0x8
	b _020071FE
_020071FA:
	mov r3, #0x40
	mov r1, #0x10
_020071FE:
	add r0, r4, #0x0
	add r0, #0x6c
	ldrh r0, [r0, #0x0]
	lsl r0, r0, #0x1d
	lsr r0, r0, #0x1f
	beq _02007220
	mov r0, #0x74
	ldrsh r2, [r4, r0]
	mov r0, #0x24
	mov r6, #0x2c
	ldrsh r0, [r4, r0]
	ldrsh r6, [r4, r6]
	add r0, r0, r6
	add r2, r2, r0
	add r0, r4, #0x0
	add r0, #0x70
	strh r2, [r0, #0x0]
_02007220:
	add r0, r4, #0x0
	add r0, #0x6c
	ldrh r0, [r0, #0x0]
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1f
	beq _02007242
	mov r0, #0x76
	ldrsh r2, [r4, r0]
	mov r0, #0x26
	mov r6, #0x2e
	ldrsh r0, [r4, r0]
	ldrsh r6, [r4, r6]
	add r0, r0, r6
	add r2, r2, r0
	add r0, r4, #0x0
	add r0, #0x72
	strh r2, [r0, #0x0]
_02007242:
	add r0, r4, #0x0
	add r0, #0x6c
	ldrh r0, [r0, #0x0]
	ldr r2, _02007278 ; =UNK_020ECBD0
	ldr r6, _02007278 ; =UNK_020ECBD0
	b _0200727C
	nop
_02007250: .word 0x04000444
_02007254: .word UNK_020ECD4C
_02007258: .word 0x000002E3
_0200725C: .word 0x04000454
_02007260: .word 0x040004AC
_02007264: .word 0x04000470
_02007268: .word FX_SinCosTable_
_0200726C: .word 0x040004C0
_02007270: .word 0x00004210
_02007274: .word 0x040004A4
_02007278: .word UNK_020ECBD0
_0200727C:
	lsl r0, r0, #0x19
	lsr r0, r0, #0x1e
	lsl r0, r0, #0x4
	str r1, [sp, #0x0]
	add r2, r2, r0
	ldr r0, [r6, r0]
	lsr r6, r1, #0x1f
	str r0, [sp, #0x4]
	ldr r0, [r2, #0x4]
	add r6, r1, r6
	str r0, [sp, #0x8]
	ldr r0, [r2, #0x8]
	asr r1, r6, #0x1
	str r0, [sp, #0xc]
	ldr r0, [r2, #0xc]
	str r0, [sp, #0x10]
	mov r0, #0x70
	ldrsh r2, [r4, r0]
	lsr r0, r3, #0x1f
	add r0, r3, r0
	asr r0, r0, #0x1
	sub r0, r2, r0
	mov r2, #0x72
	ldrsh r2, [r4, r2]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	sub r1, r2, r1
	lsl r1, r1, #0x10
	ldr r2, _020072E0 ; =0xFFFFFC18
	asr r1, r1, #0x10
	bl NNS_G2dDrawSpriteFast
_020072BC:
	ldr r0, [sp, #0x14]
	add r4, #0x98
	add r0, #0x20
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x1c]
	add r0, #0x20
	str r0, [sp, #0x1c]
	ldr r0, [sp, #0x18]
	add r0, r0, #0x1
	str r0, [sp, #0x18]
	cmp r0, #0x4
	bge _020072D6
	b _02006F30
_020072D6:
	ldr r0, _020072E4 ; =0x04000448
	mov r1, #0x1
	str r1, [r0, #0x0]
	add sp, #0x20
	pop {r3-r7, pc}
	.balign 4
_020072E0: .word 0xFFFFFC18
_020072E4: .word 0x04000448

	thumb_func_start FUN_020072E8
FUN_020072E8: ; 0x020072E8
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0xab
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	bl FreeToHeap
	mov r0, #0x2b
	lsl r0, r0, #0x4
	ldr r0, [r4, r0]
	bl FreeToHeap
	mov r0, #0xad
	lsl r0, r0, #0x2
	ldr r0, [r4, r0]
	bl FreeToHeap
	add r0, r4, #0x0
	bl FreeToHeap
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02007314
FUN_02007314: ; 0x02007314
	push {r3-r4}
	add r1, r0, #0x0
	mov r3, #0x0
	add r1, #0x59
	strb r3, [r1, #0x0]
	add r1, r3, #0x0
_02007320:
	add r2, r0, r3
	add r2, #0x5c
	add r3, r3, #0x1
	strb r1, [r2, #0x0]
	cmp r3, #0xa
	blt _02007320
	add r2, r0, #0x0
	add r2, #0x59
	ldrb r2, [r2, #0x0]
	lsl r2, r2, #0x1
	add r3, r0, r2
	mov r2, #0x84
	ldrsb r4, [r3, r2]
	add r3, r2, #0x0
	sub r3, #0x85
	cmp r4, r3
	bne _0200734A
	add r0, #0x5b
	strb r1, [r0, #0x0]
	pop {r3-r4}
	bx lr
_0200734A:
	add r1, r0, #0x0
	mov r3, #0x1
	add r1, #0x58
	strb r3, [r1, #0x0]
	add r1, r0, #0x0
	add r1, #0x59
	ldrb r1, [r1, #0x0]
	lsl r1, r1, #0x1
	add r1, r0, r1
	ldrsb r2, [r1, r2]
	add r1, r0, #0x0
	add r1, #0x5b
	strb r2, [r1, #0x0]
	add r1, r0, #0x0
	add r1, #0x59
	ldrb r1, [r1, #0x0]
	lsl r1, r1, #0x1
	add r1, r0, r1
	add r1, #0x85
	ldrb r1, [r1, #0x0]
	add r0, #0x5a
	strb r1, [r0, #0x0]
	pop {r3-r4}
	bx lr
	.balign 4

	thumb_func_start FUN_0200737C
FUN_0200737C: ; 0x0200737C
	add r2, r0, #0x0
	ldr r3, _0200738C ; =MI_CpuCopy8
	add r2, #0x84
	add r0, r1, #0x0
	add r1, r2, #0x0
	mov r2, #0x14
	bx r3
	nop
_0200738C: .word MI_CpuCopy8

	thumb_func_start FUN_02007390
FUN_02007390: ; 0x02007390
	add r0, #0x58
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	beq _0200739C
	mov r0, #0x1
	bx lr
_0200739C:
	mov r0, #0x0
	bx lr

	thumb_func_start FUN_020073A0
FUN_020073A0: ; 0x020073A0
	push {r3-r7, lr}
	sub sp, #0x18
	add r5, r0, #0x0
	add r6, r1, #0x0
	add r7, r2, #0x0
	str r3, [sp, #0x14]
	mov r4, #0x0
_020073AE:
	ldr r1, [r0, #0x0]
	lsl r1, r1, #0x1f
	lsr r1, r1, #0x1f
	beq _020073BE
	add r4, r4, #0x1
	add r0, #0x98
	cmp r4, #0x4
	blt _020073AE
_020073BE:
	cmp r4, #0x4
	bne _020073C6
	bl GF_AssertFail
_020073C6:
	ldr r0, [sp, #0x30]
	ldr r3, [sp, #0x14]
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x34]
	add r1, r6, #0x0
	str r0, [sp, #0x4]
	ldr r0, [sp, #0x38]
	str r4, [sp, #0x8]
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x3c]
	add r2, r7, #0x0
	str r0, [sp, #0x10]
	add r0, r5, #0x0
	bl FUN_020073E8
	add sp, #0x18
	pop {r3-r7, pc}

	thumb_func_start FUN_020073E8
FUN_020073E8: ; 0x020073E8
	push {r4-r7, lr}
	sub sp, #0xc
	str r1, [sp, #0x8]
	ldr r1, [sp, #0x28]
	add r4, r0, #0x0
	mov r0, #0x98
	add r6, r1, #0x0
	mul r6, r0
	ldr r0, [r4, r6]
	str r2, [sp, #0x0]
	lsl r0, r0, #0x1f
	str r3, [sp, #0x4]
	lsr r0, r0, #0x1f
	beq _02007408
	bl GF_AssertFail
_02007408:
	add r5, r4, r6
	mov r0, #0x0
	add r1, r5, #0x0
	mov r2, #0x98
	bl MIi_CpuClearFast
	ldr r1, [r4, r6]
	mov r0, #0x1
	bic r1, r0
	mov r0, #0x1
	orr r0, r1
	str r0, [r4, r6]
	ldr r1, [r4, r6]
	mov r0, #0x80
	orr r0, r1
	str r0, [r4, r6]
	mov r0, #0x80
	ldr r1, [r4, r6]
	add r0, #0x80
	orr r0, r1
	str r0, [r4, r6]
	add r2, r5, #0x0
	ldr r0, [r4, r6]
	mov r1, #0x7e
	bic r0, r1
	ldr r1, [sp, #0x24]
	add r7, r2, #0x4
	lsl r1, r1, #0x1a
	lsr r1, r1, #0x19
	orr r0, r1
	str r0, [r4, r6]
	ldr r0, [sp, #0x8]
	mov r12, r0
	mov r3, r12
	ldmia r3!, {r0-r1}
	stmia r7!, {r0-r1}
	ldmia r3!, {r0-r1}
	stmia r7!, {r0-r1}
	add r7, r2, #0x0
	ldr r3, [sp, #0x8]
	add r7, #0x14
	ldmia r3!, {r0-r1}
	stmia r7!, {r0-r1}
	str r3, [sp, #0x8]
	ldmia r3!, {r0-r1}
	stmia r7!, {r0-r1}
	ldr r0, [sp, #0x0]
	ldr r1, [sp, #0x4]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	lsl r1, r1, #0x10
	asr r7, r1, #0x10
	strh r0, [r2, #0x24]
	str r3, [sp, #0x8]
	ldr r1, [sp, #0x20]
	strh r7, [r2, #0x26]
	str r1, [r2, #0x28]
	mov r1, #0x80
	add r1, #0x80
	strh r1, [r2, #0x34]
	strh r1, [r2, #0x36]
	ldr r1, [r5, #0x54]
	mov r3, #0x7c
	bic r1, r3
	mov r3, #0x7c
	orr r1, r3
	str r1, [r5, #0x54]
	ldr r1, [r5, #0x50]
	mov r3, #0x1f
	bic r1, r3
	mov r3, #0x1f
	orr r3, r1
	ldr r1, _02007520 ; =0xFFFFFC1F
	and r1, r3
	mov r3, #0x1f
	lsl r3, r3, #0x5
	orr r3, r1
	ldr r1, _02007524 ; =0xFFFF83FF
	and r1, r3
	mov r3, #0x1f
	lsl r3, r3, #0xa
	orr r3, r1
	ldr r1, _02007528 ; =0xFFF07FFF
	and r1, r3
	mov r3, #0x80
	lsl r3, r3, #0xc
	orr r3, r1
	ldr r1, _0200752C ; =0xFE0FFFFF
	and r1, r3
	mov r3, #0x80
	lsl r3, r3, #0x11
	orr r3, r1
	ldr r1, _02007530 ; =0xC1FFFFFF
	and r1, r3
	mov r3, #0x80
	lsl r3, r3, #0x16
	orr r1, r3
	str r1, [r5, #0x50]
	ldr r1, [sp, #0x30]
	str r1, [r2, #0x68]
	add r1, r2, #0x0
	add r1, #0x70
	strh r0, [r1, #0x0]
	add r2, #0x72
	add r0, r5, #0x0
	strh r7, [r2, #0x0]
	add r0, #0x6c
	ldrh r1, [r0, #0x0]
	mov r0, #0x4
	orr r1, r0
	add r0, r5, #0x0
	add r0, #0x6c
	strh r1, [r0, #0x0]
	add r0, r5, #0x0
	add r0, #0x6c
	ldrh r1, [r0, #0x0]
	mov r0, #0x8
	orr r1, r0
	add r0, r5, #0x0
	add r0, #0x6c
	strh r1, [r0, #0x0]
	add r0, r5, #0x0
	add r0, #0x6c
	ldrh r1, [r0, #0x0]
	mov r0, #0x10
	add r5, #0x6c
	orr r0, r1
	strh r0, [r5, #0x0]
	ldr r0, [sp, #0x2c]
	cmp r0, #0x0
	beq _02007518
	add r1, r4, r6
	add r1, #0x84
	mov r2, #0x14
	bl MI_CpuCopy8
_02007518:
	add r0, r4, r6
	add sp, #0xc
	pop {r4-r7, pc}
	nop
_02007520: .word 0xFFFFFC1F
_02007524: .word 0xFFFF83FF
_02007528: .word 0xFFF07FFF
_0200752C: .word 0xFE0FFFFF
_02007530: .word 0xC1FFFFFF

	thumb_func_start FUN_02007534
FUN_02007534: ; 0x02007534
	ldr r2, [r0, #0x0]
	mov r1, #0x1
	bic r2, r1
	str r2, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02007540
FUN_02007540: ; 0x02007540
	push {r3-r5, lr}
	add r5, r0, #0x0
	mov r4, #0x0
_02007546:
	add r0, r5, #0x0
	bl FUN_02007534
	add r4, r4, #0x1
	add r5, #0x98
	cmp r4, #0x4
	blt _02007546
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02007558
FUN_02007558: ; 0x02007558
	cmp r1, #0x2e
	bls _0200755E
	b _02007800
_0200755E:
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0200756A: ; jump table (using 16-bit offset)
	.short _020075C8 - _0200756A - 2; case 0
	.short _020075CC - _0200756A - 2; case 1
	.short _020075D0 - _0200756A - 2; case 2
	.short _020075D4 - _0200756A - 2; case 3
	.short _020075D8 - _0200756A - 2; case 4
	.short _020075DC - _0200756A - 2; case 5
	.short _020075E0 - _0200756A - 2; case 6
	.short _020075F0 - _0200756A - 2; case 7
	.short _020075F4 - _0200756A - 2; case 8
	.short _020075F8 - _0200756A - 2; case 9
	.short _020075FC - _0200756A - 2; case 10
	.short _02007602 - _0200756A - 2; case 11
	.short _02007608 - _0200756A - 2; case 12
	.short _0200760C - _0200756A - 2; case 13
	.short _02007610 - _0200756A - 2; case 14
	.short _02007620 - _0200756A - 2; case 15
	.short _02007626 - _0200756A - 2; case 16
	.short _0200762C - _0200756A - 2; case 17
	.short _02007632 - _0200756A - 2; case 18
	.short _02007638 - _0200756A - 2; case 19
	.short _0200763E - _0200756A - 2; case 20
	.short _02007644 - _0200756A - 2; case 21
	.short _0200764A - _0200756A - 2; case 22
	.short _02007650 - _0200756A - 2; case 23
	.short _02007660 - _0200756A - 2; case 24
	.short _02007670 - _0200756A - 2; case 25
	.short _02007680 - _0200756A - 2; case 26
	.short _02007690 - _0200756A - 2; case 27
	.short _020076A0 - _0200756A - 2; case 28
	.short _020076B0 - _0200756A - 2; case 29
	.short _020076C0 - _0200756A - 2; case 30
	.short _020076DA - _0200756A - 2; case 31
	.short _020076E8 - _0200756A - 2; case 32
	.short _020076FA - _0200756A - 2; case 33
	.short _0200770C - _0200756A - 2; case 34
	.short _02007712 - _0200756A - 2; case 35
	.short _0200772A - _0200756A - 2; case 36
	.short _02007742 - _0200756A - 2; case 37
	.short _02007752 - _0200756A - 2; case 38
	.short _02007800 - _0200756A - 2; case 39
	.short _02007758 - _0200756A - 2; case 40
	.short _02007770 - _0200756A - 2; case 41
	.short _02007776 - _0200756A - 2; case 42
	.short _0200779A - _0200756A - 2; case 43
	.short _020077B4 - _0200756A - 2; case 44
	.short _020077CE - _0200756A - 2; case 45
	.short _020077E8 - _0200756A - 2; case 46
_020075C8:
	strh r2, [r0, #0x24]
	bx lr
_020075CC:
	strh r2, [r0, #0x26]
	bx lr
_020075D0:
	str r2, [r0, #0x28]
	bx lr
_020075D4:
	strh r2, [r0, #0x2c]
	bx lr
_020075D8:
	strh r2, [r0, #0x2e]
	bx lr
_020075DC:
	str r2, [r0, #0x30]
	bx lr
_020075E0:
	ldr r3, [r0, #0x54]
	mov r1, #0x1
	bic r3, r1
	mov r1, #0x1
	and r1, r2
	orr r1, r3
	str r1, [r0, #0x54]
	bx lr
_020075F0:
	strh r2, [r0, #0x38]
	bx lr
_020075F4:
	strh r2, [r0, #0x3a]
	bx lr
_020075F8:
	strh r2, [r0, #0x3c]
	bx lr
_020075FC:
	add r0, #0x40
	strh r2, [r0, #0x0]
	bx lr
_02007602:
	add r0, #0x42
	strh r2, [r0, #0x0]
	bx lr
_02007608:
	strh r2, [r0, #0x34]
	bx lr
_0200760C:
	strh r2, [r0, #0x36]
	bx lr
_02007610:
	ldr r3, [r0, #0x54]
	mov r1, #0x2
	bic r3, r1
	lsl r1, r2, #0x1f
	lsr r1, r1, #0x1e
	orr r1, r3
	str r1, [r0, #0x54]
	bx lr
_02007620:
	add r0, #0x44
	strb r2, [r0, #0x0]
	bx lr
_02007626:
	add r0, #0x45
	strb r2, [r0, #0x0]
	bx lr
_0200762C:
	add r0, #0x46
	strb r2, [r0, #0x0]
	bx lr
_02007632:
	add r0, #0x47
	strb r2, [r0, #0x0]
	bx lr
_02007638:
	add r0, #0x70
	strh r2, [r0, #0x0]
	bx lr
_0200763E:
	add r0, #0x72
	strh r2, [r0, #0x0]
	bx lr
_02007644:
	add r0, #0x74
	strh r2, [r0, #0x0]
	bx lr
_0200764A:
	add r0, #0x76
	strh r2, [r0, #0x0]
	bx lr
_02007650:
	ldr r3, [r0, #0x54]
	mov r1, #0x7c
	bic r3, r1
	lsl r1, r2, #0x1b
	lsr r1, r1, #0x19
	orr r1, r3
	str r1, [r0, #0x54]
	bx lr
_02007660:
	ldr r3, [r0, #0x50]
	mov r1, #0x1f
	bic r3, r1
	mov r1, #0x1f
	and r1, r2
	orr r1, r3
	str r1, [r0, #0x50]
	bx lr
_02007670:
	ldr r3, [r0, #0x50]
	ldr r1, _02007804 ; =0xFFFFFC1F
	and r3, r1
	lsl r1, r2, #0x1b
	lsr r1, r1, #0x16
	orr r1, r3
	str r1, [r0, #0x50]
	bx lr
_02007680:
	ldr r3, [r0, #0x50]
	ldr r1, _02007808 ; =0xFFFF83FF
	and r3, r1
	lsl r1, r2, #0x1b
	lsr r1, r1, #0x11
	orr r1, r3
	str r1, [r0, #0x50]
	bx lr
_02007690:
	ldr r3, [r0, #0x50]
	ldr r1, _0200780C ; =0xFFF07FFF
	and r3, r1
	lsl r1, r2, #0x1b
	lsr r1, r1, #0xc
	orr r1, r3
	str r1, [r0, #0x50]
	bx lr
_020076A0:
	ldr r3, [r0, #0x50]
	ldr r1, _02007810 ; =0xFE0FFFFF
	and r3, r1
	lsl r1, r2, #0x1b
	lsr r1, r1, #0x7
	orr r1, r3
	str r1, [r0, #0x50]
	bx lr
_020076B0:
	ldr r3, [r0, #0x50]
	ldr r1, _02007814 ; =0xC1FFFFFF
	and r3, r1
	lsl r1, r2, #0x1b
	lsr r1, r1, #0x2
	orr r1, r3
	str r1, [r0, #0x50]
	bx lr
_020076C0:
	ldr r3, [r0, #0x54]
	ldr r1, _02007818 ; =0xFFFFEFFF
	and r3, r1
	lsl r1, r2, #0x1f
	lsr r1, r1, #0x13
	orr r1, r3
	str r1, [r0, #0x54]
	mov r1, #0x1
	ldr r2, [r0, #0x0]
	lsl r1, r1, #0x8
	orr r1, r2
	str r1, [r0, #0x0]
	bx lr
_020076DA:
	str r2, [r0, #0x4c]
	mov r1, #0x1
	ldr r2, [r0, #0x0]
	lsl r1, r1, #0x8
	orr r1, r2
	str r1, [r0, #0x0]
	bx lr
_020076E8:
	add r1, r0, #0x0
	add r1, #0x48
	strb r2, [r1, #0x0]
	mov r1, #0x1
	ldr r2, [r0, #0x0]
	lsl r1, r1, #0x8
	orr r1, r2
	str r1, [r0, #0x0]
	bx lr
_020076FA:
	add r1, r0, #0x0
	add r1, #0x49
	strb r2, [r1, #0x0]
	mov r1, #0x1
	ldr r2, [r0, #0x0]
	lsl r1, r1, #0x8
	orr r1, r2
	str r1, [r0, #0x0]
	bx lr
_0200770C:
	add r0, #0x4a
	strb r2, [r0, #0x0]
	bx lr
_02007712:
	ldr r3, [r0, #0x54]
	ldr r1, _0200781C ; =0xFFFFFDFF
	and r3, r1
	lsl r1, r2, #0x1f
	lsr r1, r1, #0x16
	orr r1, r3
	str r1, [r0, #0x54]
	ldr r2, [r0, #0x0]
	mov r1, #0x80
	orr r1, r2
	str r1, [r0, #0x0]
	bx lr
_0200772A:
	ldr r3, [r0, #0x54]
	ldr r1, _02007820 ; =0xFFFFFBFF
	and r3, r1
	lsl r1, r2, #0x1f
	lsr r1, r1, #0x15
	orr r1, r3
	str r1, [r0, #0x54]
	ldr r2, [r0, #0x0]
	mov r1, #0x80
	orr r1, r2
	str r1, [r0, #0x0]
	bx lr
_02007742:
	ldr r3, [r0, #0x54]
	ldr r1, _02007824 ; =0xFFFFF7FF
	and r3, r1
	lsl r1, r2, #0x1f
	lsr r1, r1, #0x14
	orr r1, r3
	str r1, [r0, #0x54]
	bx lr
_02007752:
	add r0, #0x5b
	strb r2, [r0, #0x0]
	bx lr
_02007758:
	ldr r3, [r0, #0x54]
	ldr r1, _02007828 ; =0xFFFE1FFF
	and r3, r1
	lsl r1, r2, #0x1c
	lsr r1, r1, #0xf
	orr r1, r3
	str r1, [r0, #0x54]
	ldr r2, [r0, #0x0]
	mov r1, #0x80
	orr r1, r2
	str r1, [r0, #0x0]
	bx lr
_02007770:
	add r0, #0x6e
	strb r2, [r0, #0x0]
	bx lr
_02007776:
	add r1, r0, #0x0
	add r1, #0x6c
	ldrh r3, [r1, #0x0]
	mov r1, #0x3
	bic r3, r1
	lsl r1, r2, #0x10
	lsr r1, r1, #0x10
	mov r2, #0x3
	and r1, r2
	orr r3, r1
	add r1, r0, #0x0
	add r1, #0x6c
	strh r3, [r1, #0x0]
	ldr r1, [r0, #0x0]
	add r2, #0xfd
	orr r1, r2
	str r1, [r0, #0x0]
	bx lr
_0200779A:
	add r1, r0, #0x0
	add r1, #0x6c
	ldrh r3, [r1, #0x0]
	mov r1, #0x4
	add r0, #0x6c
	bic r3, r1
	lsl r1, r2, #0x10
	lsr r1, r1, #0x10
	lsl r1, r1, #0x1f
	lsr r1, r1, #0x1d
	orr r1, r3
	strh r1, [r0, #0x0]
	bx lr
_020077B4:
	add r1, r0, #0x0
	add r1, #0x6c
	ldrh r3, [r1, #0x0]
	mov r1, #0x8
	add r0, #0x6c
	bic r3, r1
	lsl r1, r2, #0x10
	lsr r1, r1, #0x10
	lsl r1, r1, #0x1f
	lsr r1, r1, #0x1c
	orr r1, r3
	strh r1, [r0, #0x0]
	bx lr
_020077CE:
	add r1, r0, #0x0
	add r1, #0x6c
	ldrh r3, [r1, #0x0]
	mov r1, #0x10
	add r0, #0x6c
	bic r3, r1
	lsl r1, r2, #0x10
	lsr r1, r1, #0x10
	lsl r1, r1, #0x1f
	lsr r1, r1, #0x1b
	orr r1, r3
	strh r1, [r0, #0x0]
	bx lr
_020077E8:
	add r1, r0, #0x0
	add r1, #0x6c
	ldrh r3, [r1, #0x0]
	mov r1, #0x60
	add r0, #0x6c
	bic r3, r1
	lsl r1, r2, #0x10
	lsr r1, r1, #0x10
	lsl r1, r1, #0x1e
	lsr r1, r1, #0x19
	orr r1, r3
	strh r1, [r0, #0x0]
_02007800:
	bx lr
	nop
_02007804: .word 0xFFFFFC1F
_02007808: .word 0xFFFF83FF
_0200780C: .word 0xFFF07FFF
_02007810: .word 0xFE0FFFFF
_02007814: .word 0xC1FFFFFF
_02007818: .word 0xFFFFEFFF
_0200781C: .word 0xFFFFFDFF
_02007820: .word 0xFFFFFBFF
_02007824: .word 0xFFFFF7FF
_02007828: .word 0xFFFE1FFF

	thumb_func_start FUN_0200782C
FUN_0200782C: ; 0x0200782C
	push {r3, lr}
	cmp r1, #0x2e
	bls _02007834
	b _020079D6
_02007834:
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02007840: ; jump table (using 16-bit offset)
	.short _0200789E - _02007840 - 2; case 0
	.short _020078A4 - _02007840 - 2; case 1
	.short _020078AA - _02007840 - 2; case 2
	.short _020078AE - _02007840 - 2; case 3
	.short _020078B4 - _02007840 - 2; case 4
	.short _020078BA - _02007840 - 2; case 5
	.short _020078BE - _02007840 - 2; case 6
	.short _020078C6 - _02007840 - 2; case 7
	.short _020078CA - _02007840 - 2; case 8
	.short _020078CE - _02007840 - 2; case 9
	.short _020078D2 - _02007840 - 2; case 10
	.short _020078D8 - _02007840 - 2; case 11
	.short _020078DE - _02007840 - 2; case 12
	.short _020078E4 - _02007840 - 2; case 13
	.short _020078EA - _02007840 - 2; case 14
	.short _020078F2 - _02007840 - 2; case 15
	.short _020078F8 - _02007840 - 2; case 16
	.short _020078FE - _02007840 - 2; case 17
	.short _02007904 - _02007840 - 2; case 18
	.short _0200790A - _02007840 - 2; case 19
	.short _02007910 - _02007840 - 2; case 20
	.short _02007916 - _02007840 - 2; case 21
	.short _0200791C - _02007840 - 2; case 22
	.short _02007922 - _02007840 - 2; case 23
	.short _0200792A - _02007840 - 2; case 24
	.short _02007932 - _02007840 - 2; case 25
	.short _0200793A - _02007840 - 2; case 26
	.short _02007942 - _02007840 - 2; case 27
	.short _0200794A - _02007840 - 2; case 28
	.short _02007952 - _02007840 - 2; case 29
	.short _0200795A - _02007840 - 2; case 30
	.short _02007962 - _02007840 - 2; case 31
	.short _02007966 - _02007840 - 2; case 32
	.short _0200796C - _02007840 - 2; case 33
	.short _02007972 - _02007840 - 2; case 34
	.short _02007978 - _02007840 - 2; case 35
	.short _02007980 - _02007840 - 2; case 36
	.short _02007988 - _02007840 - 2; case 37
	.short _02007990 - _02007840 - 2; case 38
	.short _020079D6 - _02007840 - 2; case 39
	.short _02007996 - _02007840 - 2; case 40
	.short _0200799E - _02007840 - 2; case 41
	.short _020079A4 - _02007840 - 2; case 42
	.short _020079AE - _02007840 - 2; case 43
	.short _020079B8 - _02007840 - 2; case 44
	.short _020079C2 - _02007840 - 2; case 45
	.short _020079CC - _02007840 - 2; case 46
_0200789E:
	mov r1, #0x24
	ldrsh r0, [r0, r1]
	pop {r3, pc}
_020078A4:
	mov r1, #0x26
	ldrsh r0, [r0, r1]
	pop {r3, pc}
_020078AA:
	ldr r0, [r0, #0x28]
	pop {r3, pc}
_020078AE:
	mov r1, #0x2c
	ldrsh r0, [r0, r1]
	pop {r3, pc}
_020078B4:
	mov r1, #0x2e
	ldrsh r0, [r0, r1]
	pop {r3, pc}
_020078BA:
	ldr r0, [r0, #0x30]
	pop {r3, pc}
_020078BE:
	ldr r0, [r0, #0x54]
	lsl r0, r0, #0x1f
	lsr r0, r0, #0x1f
	pop {r3, pc}
_020078C6:
	ldrh r0, [r0, #0x38]
	pop {r3, pc}
_020078CA:
	ldrh r0, [r0, #0x3a]
	pop {r3, pc}
_020078CE:
	ldrh r0, [r0, #0x3c]
	pop {r3, pc}
_020078D2:
	mov r1, #0x40
	ldrsh r0, [r0, r1]
	pop {r3, pc}
_020078D8:
	mov r1, #0x42
	ldrsh r0, [r0, r1]
	pop {r3, pc}
_020078DE:
	mov r1, #0x34
	ldrsh r0, [r0, r1]
	pop {r3, pc}
_020078E4:
	mov r1, #0x36
	ldrsh r0, [r0, r1]
	pop {r3, pc}
_020078EA:
	ldr r0, [r0, #0x54]
	lsl r0, r0, #0x1e
	lsr r0, r0, #0x1f
	pop {r3, pc}
_020078F2:
	add r0, #0x44
	ldrb r0, [r0, #0x0]
	pop {r3, pc}
_020078F8:
	add r0, #0x45
	ldrb r0, [r0, #0x0]
	pop {r3, pc}
_020078FE:
	add r0, #0x46
	ldrb r0, [r0, #0x0]
	pop {r3, pc}
_02007904:
	add r0, #0x47
	ldrb r0, [r0, #0x0]
	pop {r3, pc}
_0200790A:
	mov r1, #0x70
	ldrsh r0, [r0, r1]
	pop {r3, pc}
_02007910:
	mov r1, #0x72
	ldrsh r0, [r0, r1]
	pop {r3, pc}
_02007916:
	mov r1, #0x74
	ldrsh r0, [r0, r1]
	pop {r3, pc}
_0200791C:
	mov r1, #0x76
	ldrsh r0, [r0, r1]
	pop {r3, pc}
_02007922:
	ldr r0, [r0, #0x54]
	lsl r0, r0, #0x19
	lsr r0, r0, #0x1b
	pop {r3, pc}
_0200792A:
	ldr r0, [r0, #0x50]
	lsl r0, r0, #0x1b
	lsr r0, r0, #0x1b
	pop {r3, pc}
_02007932:
	ldr r0, [r0, #0x50]
	lsl r0, r0, #0x16
	lsr r0, r0, #0x1b
	pop {r3, pc}
_0200793A:
	ldr r0, [r0, #0x50]
	lsl r0, r0, #0x11
	lsr r0, r0, #0x1b
	pop {r3, pc}
_02007942:
	ldr r0, [r0, #0x50]
	lsl r0, r0, #0xc
	lsr r0, r0, #0x1b
	pop {r3, pc}
_0200794A:
	ldr r0, [r0, #0x50]
	lsl r0, r0, #0x7
	lsr r0, r0, #0x1b
	pop {r3, pc}
_02007952:
	ldr r0, [r0, #0x50]
	lsl r0, r0, #0x2
	lsr r0, r0, #0x1b
	pop {r3, pc}
_0200795A:
	ldr r0, [r0, #0x54]
	lsl r0, r0, #0x13
	lsr r0, r0, #0x1f
	pop {r3, pc}
_02007962:
	ldr r0, [r0, #0x4c]
	pop {r3, pc}
_02007966:
	add r0, #0x48
	ldrb r0, [r0, #0x0]
	pop {r3, pc}
_0200796C:
	add r0, #0x49
	ldrb r0, [r0, #0x0]
	pop {r3, pc}
_02007972:
	add r0, #0x4a
	ldrb r0, [r0, #0x0]
	pop {r3, pc}
_02007978:
	ldr r0, [r0, #0x54]
	lsl r0, r0, #0x16
	lsr r0, r0, #0x1f
	pop {r3, pc}
_02007980:
	ldr r0, [r0, #0x54]
	lsl r0, r0, #0x15
	lsr r0, r0, #0x1f
	pop {r3, pc}
_02007988:
	ldr r0, [r0, #0x54]
	lsl r0, r0, #0x14
	lsr r0, r0, #0x1f
	pop {r3, pc}
_02007990:
	add r0, #0x5b
	ldrb r0, [r0, #0x0]
	pop {r3, pc}
_02007996:
	ldr r0, [r0, #0x54]
	lsl r0, r0, #0xf
	lsr r0, r0, #0x1c
	pop {r3, pc}
_0200799E:
	mov r1, #0x6e
	ldrsb r0, [r0, r1]
	pop {r3, pc}
_020079A4:
	add r0, #0x6c
	ldrh r0, [r0, #0x0]
	lsl r0, r0, #0x1e
	lsr r0, r0, #0x1e
	pop {r3, pc}
_020079AE:
	add r0, #0x6c
	ldrh r0, [r0, #0x0]
	lsl r0, r0, #0x1d
	lsr r0, r0, #0x1f
	pop {r3, pc}
_020079B8:
	add r0, #0x6c
	ldrh r0, [r0, #0x0]
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1f
	pop {r3, pc}
_020079C2:
	add r0, #0x6c
	ldrh r0, [r0, #0x0]
	lsl r0, r0, #0x1b
	lsr r0, r0, #0x1f
	pop {r3, pc}
_020079CC:
	add r0, #0x6c
	ldrh r0, [r0, #0x0]
	lsl r0, r0, #0x19
	lsr r0, r0, #0x1e
	pop {r3, pc}
_020079D6:
	bl GF_AssertFail
	mov r0, #0x0
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_020079E0
FUN_020079E0: ; 0x020079E0
	push {r3-r4}
	add r3, r0, #0x0
	add r0, r2, #0x0
	cmp r1, #0x2e
	bls _020079EC
	b _02007E12
_020079EC:
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_020079F8: ; jump table (using 16-bit offset)
	.short _02007A56 - _020079F8 - 2; case 0
	.short _02007A62 - _020079F8 - 2; case 1
	.short _02007A6E - _020079F8 - 2; case 2
	.short _02007A78 - _020079F8 - 2; case 3
	.short _02007A84 - _020079F8 - 2; case 4
	.short _02007A90 - _020079F8 - 2; case 5
	.short _02007A9A - _020079F8 - 2; case 6
	.short _02007AB4 - _020079F8 - 2; case 7
	.short _02007ABE - _020079F8 - 2; case 8
	.short _02007AC8 - _020079F8 - 2; case 9
	.short _02007AD2 - _020079F8 - 2; case 10
	.short _02007AE0 - _020079F8 - 2; case 11
	.short _02007AEE - _020079F8 - 2; case 12
	.short _02007AFA - _020079F8 - 2; case 13
	.short _02007B06 - _020079F8 - 2; case 14
	.short _02007B20 - _020079F8 - 2; case 15
	.short _02007B30 - _020079F8 - 2; case 16
	.short _02007B40 - _020079F8 - 2; case 17
	.short _02007B50 - _020079F8 - 2; case 18
	.short _02007B60 - _020079F8 - 2; case 19
	.short _02007B6E - _020079F8 - 2; case 20
	.short _02007B7C - _020079F8 - 2; case 21
	.short _02007B8A - _020079F8 - 2; case 22
	.short _02007B98 - _020079F8 - 2; case 23
	.short _02007BB2 - _020079F8 - 2; case 24
	.short _02007BCC - _020079F8 - 2; case 25
	.short _02007BE4 - _020079F8 - 2; case 26
	.short _02007BFC - _020079F8 - 2; case 27
	.short _02007C14 - _020079F8 - 2; case 28
	.short _02007C2C - _020079F8 - 2; case 29
	.short _02007C44 - _020079F8 - 2; case 30
	.short _02007C66 - _020079F8 - 2; case 31
	.short _02007C7A - _020079F8 - 2; case 32
	.short _02007C96 - _020079F8 - 2; case 33
	.short _02007CB2 - _020079F8 - 2; case 34
	.short _02007CC2 - _020079F8 - 2; case 35
	.short _02007CE2 - _020079F8 - 2; case 36
	.short _02007D02 - _020079F8 - 2; case 37
	.short _02007D1A - _020079F8 - 2; case 38
	.short _02007E12 - _020079F8 - 2; case 39
	.short _02007D2A - _020079F8 - 2; case 40
	.short _02007D4A - _020079F8 - 2; case 41
	.short _02007D58 - _020079F8 - 2; case 42
	.short _02007D86 - _020079F8 - 2; case 43
	.short _02007DAA - _020079F8 - 2; case 44
	.short _02007DCE - _020079F8 - 2; case 45
	.short _02007DF2 - _020079F8 - 2; case 46
_02007A56:
	mov r1, #0x24
	ldrsh r1, [r3, r1]
	add r0, r1, r0
	strh r0, [r3, #0x24]
	pop {r3-r4}
	bx lr
_02007A62:
	mov r1, #0x26
	ldrsh r1, [r3, r1]
	add r0, r1, r0
	strh r0, [r3, #0x26]
	pop {r3-r4}
	bx lr
_02007A6E:
	ldr r1, [r3, #0x28]
	add r0, r1, r0
	str r0, [r3, #0x28]
	pop {r3-r4}
	bx lr
_02007A78:
	mov r1, #0x2c
	ldrsh r1, [r3, r1]
	add r0, r1, r0
	strh r0, [r3, #0x2c]
	pop {r3-r4}
	bx lr
_02007A84:
	mov r1, #0x2e
	ldrsh r1, [r3, r1]
	add r0, r1, r0
	strh r0, [r3, #0x2e]
	pop {r3-r4}
	bx lr
_02007A90:
	ldr r1, [r3, #0x30]
	add r0, r1, r0
	str r0, [r3, #0x30]
	pop {r3-r4}
	bx lr
_02007A9A:
	ldr r4, [r3, #0x54]
	mov r2, #0x1
	add r1, r4, #0x0
	bic r1, r2
	lsl r2, r4, #0x1f
	lsr r2, r2, #0x1f
	add r2, r2, r0
	mov r0, #0x1
	and r0, r2
	orr r0, r1
	str r0, [r3, #0x54]
	pop {r3-r4}
	bx lr
_02007AB4:
	ldrh r1, [r3, #0x38]
	add r0, r1, r0
	strh r0, [r3, #0x38]
	pop {r3-r4}
	bx lr
_02007ABE:
	ldrh r1, [r3, #0x3a]
	add r0, r1, r0
	strh r0, [r3, #0x3a]
	pop {r3-r4}
	bx lr
_02007AC8:
	ldrh r1, [r3, #0x3c]
	add r0, r1, r0
	strh r0, [r3, #0x3c]
	pop {r3-r4}
	bx lr
_02007AD2:
	mov r1, #0x40
	ldrsh r1, [r3, r1]
	add r3, #0x40
	add r0, r1, r0
	strh r0, [r3, #0x0]
	pop {r3-r4}
	bx lr
_02007AE0:
	mov r1, #0x42
	ldrsh r1, [r3, r1]
	add r3, #0x42
	add r0, r1, r0
	strh r0, [r3, #0x0]
	pop {r3-r4}
	bx lr
_02007AEE:
	mov r1, #0x34
	ldrsh r1, [r3, r1]
	add r0, r1, r0
	strh r0, [r3, #0x34]
	pop {r3-r4}
	bx lr
_02007AFA:
	mov r1, #0x36
	ldrsh r1, [r3, r1]
	add r0, r1, r0
	strh r0, [r3, #0x36]
	pop {r3-r4}
	bx lr
_02007B06:
	ldr r4, [r3, #0x54]
	mov r2, #0x2
	add r1, r4, #0x0
	bic r1, r2
	lsl r2, r4, #0x1e
	lsr r2, r2, #0x1f
	add r0, r2, r0
	lsl r0, r0, #0x1f
	lsr r0, r0, #0x1e
	orr r0, r1
	str r0, [r3, #0x54]
	pop {r3-r4}
	bx lr
_02007B20:
	add r1, r3, #0x0
	add r1, #0x44
	ldrb r1, [r1, #0x0]
	add r3, #0x44
	add r0, r1, r0
	strb r0, [r3, #0x0]
	pop {r3-r4}
	bx lr
_02007B30:
	add r1, r3, #0x0
	add r1, #0x45
	ldrb r1, [r1, #0x0]
	add r3, #0x45
	add r0, r1, r0
	strb r0, [r3, #0x0]
	pop {r3-r4}
	bx lr
_02007B40:
	add r1, r3, #0x0
	add r1, #0x46
	ldrb r1, [r1, #0x0]
	add r3, #0x46
	add r0, r1, r0
	strb r0, [r3, #0x0]
	pop {r3-r4}
	bx lr
_02007B50:
	add r1, r3, #0x0
	add r1, #0x47
	ldrb r1, [r1, #0x0]
	add r3, #0x47
	add r0, r1, r0
	strb r0, [r3, #0x0]
	pop {r3-r4}
	bx lr
_02007B60:
	mov r1, #0x70
	ldrsh r1, [r3, r1]
	add r3, #0x70
	add r0, r1, r0
	strh r0, [r3, #0x0]
	pop {r3-r4}
	bx lr
_02007B6E:
	mov r1, #0x72
	ldrsh r1, [r3, r1]
	add r3, #0x72
	add r0, r1, r0
	strh r0, [r3, #0x0]
	pop {r3-r4}
	bx lr
_02007B7C:
	mov r1, #0x74
	ldrsh r1, [r3, r1]
	add r3, #0x74
	add r0, r1, r0
	strh r0, [r3, #0x0]
	pop {r3-r4}
	bx lr
_02007B8A:
	mov r1, #0x76
	ldrsh r1, [r3, r1]
	add r3, #0x76
	add r0, r1, r0
	strh r0, [r3, #0x0]
	pop {r3-r4}
	bx lr
_02007B98:
	ldr r4, [r3, #0x54]
	mov r2, #0x7c
	add r1, r4, #0x0
	bic r1, r2
	lsl r2, r4, #0x19
	lsr r2, r2, #0x1b
	add r0, r2, r0
	lsl r0, r0, #0x1b
	lsr r0, r0, #0x19
	orr r0, r1
	str r0, [r3, #0x54]
	pop {r3-r4}
	bx lr
_02007BB2:
	ldr r4, [r3, #0x50]
	mov r2, #0x1f
	add r1, r4, #0x0
	bic r1, r2
	lsl r2, r4, #0x1b
	lsr r2, r2, #0x1b
	add r2, r2, r0
	mov r0, #0x1f
	and r0, r2
	orr r0, r1
	str r0, [r3, #0x50]
	pop {r3-r4}
	bx lr
_02007BCC:
	ldr r2, [r3, #0x50]
	ldr r1, _02007E18 ; =0xFFFFFC1F
	and r1, r2
	lsl r2, r2, #0x16
	lsr r2, r2, #0x1b
	add r0, r2, r0
	lsl r0, r0, #0x1b
	lsr r0, r0, #0x16
	orr r0, r1
	str r0, [r3, #0x50]
	pop {r3-r4}
	bx lr
_02007BE4:
	ldr r2, [r3, #0x50]
	ldr r1, _02007E1C ; =0xFFFF83FF
	and r1, r2
	lsl r2, r2, #0x11
	lsr r2, r2, #0x1b
	add r0, r2, r0
	lsl r0, r0, #0x1b
	lsr r0, r0, #0x11
	orr r0, r1
	str r0, [r3, #0x50]
	pop {r3-r4}
	bx lr
_02007BFC:
	ldr r2, [r3, #0x50]
	ldr r1, _02007E20 ; =0xFFF07FFF
	and r1, r2
	lsl r2, r2, #0xc
	lsr r2, r2, #0x1b
	add r0, r2, r0
	lsl r0, r0, #0x1b
	lsr r0, r0, #0xc
	orr r0, r1
	str r0, [r3, #0x50]
	pop {r3-r4}
	bx lr
_02007C14:
	ldr r2, [r3, #0x50]
	ldr r1, _02007E24 ; =0xFE0FFFFF
	and r1, r2
	lsl r2, r2, #0x7
	lsr r2, r2, #0x1b
	add r0, r2, r0
	lsl r0, r0, #0x1b
	lsr r0, r0, #0x7
	orr r0, r1
	str r0, [r3, #0x50]
	pop {r3-r4}
	bx lr
_02007C2C:
	ldr r2, [r3, #0x50]
	ldr r1, _02007E28 ; =0xC1FFFFFF
	and r1, r2
	lsl r2, r2, #0x2
	lsr r2, r2, #0x1b
	add r0, r2, r0
	lsl r0, r0, #0x1b
	lsr r0, r0, #0x2
	orr r0, r1
	str r0, [r3, #0x50]
	pop {r3-r4}
	bx lr
_02007C44:
	ldr r2, [r3, #0x54]
	ldr r1, _02007E2C ; =0xFFFFEFFF
	and r1, r2
	lsl r2, r2, #0x13
	lsr r2, r2, #0x1f
	add r0, r2, r0
	lsl r0, r0, #0x1f
	lsr r0, r0, #0x13
	orr r0, r1
	str r0, [r3, #0x54]
	mov r0, #0x1
	ldr r1, [r3, #0x0]
	lsl r0, r0, #0x8
	orr r0, r1
	str r0, [r3, #0x0]
	pop {r3-r4}
	bx lr
_02007C66:
	ldr r1, [r3, #0x4c]
	add r0, r1, r0
	str r0, [r3, #0x4c]
	mov r0, #0x1
	ldr r1, [r3, #0x0]
	lsl r0, r0, #0x8
	orr r0, r1
	str r0, [r3, #0x0]
	pop {r3-r4}
	bx lr
_02007C7A:
	add r1, r3, #0x0
	add r1, #0x48
	ldrb r1, [r1, #0x0]
	add r1, r1, r0
	add r0, r3, #0x0
	add r0, #0x48
	strb r1, [r0, #0x0]
	mov r0, #0x1
	ldr r1, [r3, #0x0]
	lsl r0, r0, #0x8
	orr r0, r1
	str r0, [r3, #0x0]
	pop {r3-r4}
	bx lr
_02007C96:
	add r1, r3, #0x0
	add r1, #0x49
	ldrb r1, [r1, #0x0]
	add r1, r1, r0
	add r0, r3, #0x0
	add r0, #0x49
	strb r1, [r0, #0x0]
	mov r0, #0x1
	ldr r1, [r3, #0x0]
	lsl r0, r0, #0x8
	orr r0, r1
	str r0, [r3, #0x0]
	pop {r3-r4}
	bx lr
_02007CB2:
	add r1, r3, #0x0
	add r1, #0x4a
	ldrb r1, [r1, #0x0]
	add r3, #0x4a
	add r0, r1, r0
	strb r0, [r3, #0x0]
	pop {r3-r4}
	bx lr
_02007CC2:
	ldr r2, [r3, #0x54]
	ldr r1, _02007E30 ; =0xFFFFFDFF
	and r1, r2
	lsl r2, r2, #0x16
	lsr r2, r2, #0x1f
	add r0, r2, r0
	lsl r0, r0, #0x1f
	lsr r0, r0, #0x16
	orr r0, r1
	str r0, [r3, #0x54]
	ldr r1, [r3, #0x0]
	mov r0, #0x80
	orr r0, r1
	str r0, [r3, #0x0]
	pop {r3-r4}
	bx lr
_02007CE2:
	ldr r2, [r3, #0x54]
	ldr r1, _02007E34 ; =0xFFFFFBFF
	and r1, r2
	lsl r2, r2, #0x15
	lsr r2, r2, #0x1f
	add r0, r2, r0
	lsl r0, r0, #0x1f
	lsr r0, r0, #0x15
	orr r0, r1
	str r0, [r3, #0x54]
	ldr r1, [r3, #0x0]
	mov r0, #0x80
	orr r0, r1
	str r0, [r3, #0x0]
	pop {r3-r4}
	bx lr
_02007D02:
	ldr r2, [r3, #0x54]
	ldr r1, _02007E38 ; =0xFFFFF7FF
	and r1, r2
	lsl r2, r2, #0x14
	lsr r2, r2, #0x1f
	add r0, r2, r0
	lsl r0, r0, #0x1f
	lsr r0, r0, #0x14
	orr r0, r1
	str r0, [r3, #0x54]
	pop {r3-r4}
	bx lr
_02007D1A:
	add r1, r3, #0x0
	add r1, #0x5b
	ldrb r1, [r1, #0x0]
	add r3, #0x5b
	add r0, r1, r0
	strb r0, [r3, #0x0]
	pop {r3-r4}
	bx lr
_02007D2A:
	ldr r2, [r3, #0x54]
	ldr r1, _02007E3C ; =0xFFFE1FFF
	and r1, r2
	lsl r2, r2, #0xf
	lsr r2, r2, #0x1c
	add r0, r2, r0
	lsl r0, r0, #0x1c
	lsr r0, r0, #0xf
	orr r0, r1
	str r0, [r3, #0x54]
	ldr r1, [r3, #0x0]
	mov r0, #0x80
	orr r0, r1
	str r0, [r3, #0x0]
	pop {r3-r4}
	bx lr
_02007D4A:
	mov r1, #0x6e
	ldrsb r1, [r3, r1]
	add r3, #0x6e
	add r0, r1, r0
	strb r0, [r3, #0x0]
	pop {r3-r4}
	bx lr
_02007D58:
	add r1, r3, #0x0
	add r1, #0x6c
	ldrh r4, [r1, #0x0]
	mov r2, #0x3
	add r1, r4, #0x0
	bic r1, r2
	lsl r2, r4, #0x1e
	lsr r2, r2, #0x1e
	add r0, r2, r0
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	mov r2, #0x3
	and r0, r2
	orr r1, r0
	add r0, r3, #0x0
	add r0, #0x6c
	strh r1, [r0, #0x0]
	ldr r0, [r3, #0x0]
	add r2, #0xfd
	orr r0, r2
	str r0, [r3, #0x0]
	pop {r3-r4}
	bx lr
_02007D86:
	add r1, r3, #0x0
	add r1, #0x6c
	ldrh r4, [r1, #0x0]
	mov r2, #0x4
	add r3, #0x6c
	add r1, r4, #0x0
	bic r1, r2
	lsl r2, r4, #0x1d
	lsr r2, r2, #0x1f
	add r0, r2, r0
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	lsl r0, r0, #0x1f
	lsr r0, r0, #0x1d
	orr r0, r1
	strh r0, [r3, #0x0]
	pop {r3-r4}
	bx lr
_02007DAA:
	add r1, r3, #0x0
	add r1, #0x6c
	ldrh r4, [r1, #0x0]
	mov r2, #0x8
	add r3, #0x6c
	add r1, r4, #0x0
	bic r1, r2
	lsl r2, r4, #0x1c
	lsr r2, r2, #0x1f
	add r0, r2, r0
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	lsl r0, r0, #0x1f
	lsr r0, r0, #0x1c
	orr r0, r1
	strh r0, [r3, #0x0]
	pop {r3-r4}
	bx lr
_02007DCE:
	add r1, r3, #0x0
	add r1, #0x6c
	ldrh r4, [r1, #0x0]
	mov r2, #0x10
	add r3, #0x6c
	add r1, r4, #0x0
	bic r1, r2
	lsl r2, r4, #0x1b
	lsr r2, r2, #0x1f
	add r0, r2, r0
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	lsl r0, r0, #0x1f
	lsr r0, r0, #0x1b
	orr r0, r1
	strh r0, [r3, #0x0]
	pop {r3-r4}
	bx lr
_02007DF2:
	add r1, r3, #0x0
	add r1, #0x6c
	ldrh r4, [r1, #0x0]
	mov r2, #0x60
	add r3, #0x6c
	add r1, r4, #0x0
	bic r1, r2
	lsl r2, r4, #0x19
	lsr r2, r2, #0x1e
	add r0, r2, r0
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	lsl r0, r0, #0x1e
	lsr r0, r0, #0x19
	orr r0, r1
	strh r0, [r3, #0x0]
_02007E12:
	pop {r3-r4}
	bx lr
	nop
_02007E18: .word 0xFFFFFC1F
_02007E1C: .word 0xFFFF83FF
_02007E20: .word 0xFFF07FFF
_02007E24: .word 0xFE0FFFFF
_02007E28: .word 0xC1FFFFFF
_02007E2C: .word 0xFFFFEFFF
_02007E30: .word 0xFFFFFDFF
_02007E34: .word 0xFFFFFBFF
_02007E38: .word 0xFFFFF7FF
_02007E3C: .word 0xFFFE1FFF

	thumb_func_start FUN_02007E40
FUN_02007E40: ; 0x02007E40
	push {r4-r5}
	ldr r5, [r0, #0x54]
	mov r4, #0x2
	orr r4, r5
	str r4, [r0, #0x54]
	add r4, r0, #0x0
	add r4, #0x44
	strb r1, [r4, #0x0]
	add r1, r0, #0x0
	add r1, #0x45
	strb r2, [r1, #0x0]
	add r1, r0, #0x0
	add r1, #0x46
	strb r3, [r1, #0x0]
	ldr r1, [sp, #0x8]
	add r0, #0x47
	strb r1, [r0, #0x0]
	pop {r4-r5}
	bx lr
	.balign 4

	thumb_func_start FUN_02007E68
FUN_02007E68: ; 0x02007E68
	push {r4-r5}
	mov r4, #0x1
	ldr r5, [r0, #0x54]
	lsl r4, r4, #0xc
	orr r4, r5
	str r4, [r0, #0x54]
	add r4, r0, #0x0
	add r4, #0x48
	strb r1, [r4, #0x0]
	add r1, r0, #0x0
	add r1, #0x49
	strb r2, [r1, #0x0]
	add r1, r0, #0x0
	mov r2, #0x0
	add r1, #0x4a
	strb r2, [r1, #0x0]
	add r1, r0, #0x0
	add r1, #0x4b
	strb r3, [r1, #0x0]
	ldr r1, [sp, #0x8]
	str r1, [r0, #0x4c]
	pop {r4-r5}
	bx lr
	.balign 4

	thumb_func_start FUN_02007E98
FUN_02007E98: ; 0x02007E98
	push {r4-r7}
	add r4, r0, #0x0
	add r0, r1, #0x0
	add r5, r2, #0x0
	lsl r0, r0, #0x18
	lsr r6, r0, #0x18
	lsl r0, r5, #0x18
	lsr r5, r0, #0x18
	lsl r0, r3, #0x18
	ldr r2, [sp, #0x10]
	mov r1, #0x0
	lsr r0, r0, #0x18
_02007EB0:
	ldr r3, [r4, #0x0]
	lsl r3, r3, #0x1f
	lsr r3, r3, #0x1f
	beq _02007EDE
	mov r3, #0x1
	ldr r7, [r4, #0x54]
	lsl r3, r3, #0xc
	orr r3, r7
	str r3, [r4, #0x54]
	add r3, r4, #0x0
	add r3, #0x48
	strb r6, [r3, #0x0]
	add r3, r4, #0x0
	add r3, #0x49
	add r7, r4, #0x0
	strb r5, [r3, #0x0]
	add r7, #0x4a
	mov r3, #0x0
	strb r3, [r7, #0x0]
	add r3, r4, #0x0
	add r3, #0x4b
	strb r0, [r3, #0x0]
	str r2, [r4, #0x4c]
_02007EDE:
	add r1, r1, #0x1
	add r4, #0x98
	cmp r1, #0x4
	blt _02007EB0
	pop {r4-r7}
	bx lr
	.balign 4

	thumb_func_start FUN_02007EEC
FUN_02007EEC: ; 0x02007EEC
	ldr r2, [r0, #0x54]
	ldr r1, _02007F1C ; =0xFFFFEFFF
	and r1, r2
	str r1, [r0, #0x54]
	add r1, r0, #0x0
	mov r2, #0x0
	add r1, #0x48
	strb r2, [r1, #0x0]
	add r1, r0, #0x0
	add r1, #0x49
	strb r2, [r1, #0x0]
	add r1, r0, #0x0
	add r1, #0x4a
	strb r2, [r1, #0x0]
	add r1, r0, #0x0
	add r1, #0x4b
	strb r2, [r1, #0x0]
	str r2, [r0, #0x4c]
	mov r1, #0x1
	ldr r2, [r0, #0x0]
	lsl r1, r1, #0x8
	orr r1, r2
	str r1, [r0, #0x0]
	bx lr
	.balign 4
_02007F1C: .word 0xFFFFEFFF

	thumb_func_start FUN_02007F20
FUN_02007F20: ; 0x02007F20
	ldr r0, [r0, #0x54]
	lsl r0, r0, #0x13
	lsr r0, r0, #0x1f
	cmp r0, #0x1
	bne _02007F2E
	mov r0, #0x1
	bx lr
_02007F2E:
	mov r0, #0x0
	bx lr
	.balign 4

	thumb_func_start FUN_02007F34
FUN_02007F34: ; 0x02007F34
	mov r2, #0x28
	sub r2, r2, r1
	mov r1, #0x36
	ldrsh r1, [r0, r1]
	mul r1, r2
	asr r1, r1, #0x8
	sub r1, r2, r1
	strh r1, [r0, #0x2e]
	bx lr
	.balign 4

	thumb_func_start FUN_02007F48
FUN_02007F48: ; 0x02007F48
	push {r4-r7}
	add r1, r0, #0x0
	add r1, #0x58
	ldrb r1, [r1, #0x0]
	add r6, r0, #0x0
	add r6, #0x59
	cmp r1, #0x0
	beq _0200800A
	add r1, r0, #0x0
	add r1, #0x5a
	ldrb r1, [r1, #0x0]
	cmp r1, #0x0
	bne _02007FFE
	ldrb r1, [r6, #0x0]
	add r1, r1, #0x1
	strb r1, [r6, #0x0]
	ldrb r3, [r6, #0x0]
	mov r1, #0x84
	lsl r4, r3, #0x1
	add r2, r0, r4
	ldrsb r2, [r2, r1]
	sub r1, #0x85
	cmp r2, r1
	bge _02007FC6
	mov r2, #0x0
	sub r1, r2, #0x2
_02007F7C:
	add r4, r0, r3
	add r4, #0x5c
	ldrb r4, [r4, #0x0]
	add r3, r0, r3
	add r3, #0x5c
	add r4, r4, #0x1
	strb r4, [r3, #0x0]
	ldrb r5, [r6, #0x0]
	lsl r3, r5, #0x1
	add r4, r0, r3
	add r3, r4, #0x0
	add r7, r0, r5
	add r3, #0x85
	add r7, #0x5c
	ldrb r3, [r3, #0x0]
	ldrb r7, [r7, #0x0]
	cmp r3, r7
	beq _02007FA4
	cmp r3, #0x0
	bne _02007FAE
_02007FA4:
	add r3, r0, r5
	add r3, #0x5c
	strb r2, [r3, #0x0]
	add r6, r6, #0x1
	b _02007FB6
_02007FAE:
	mov r3, #0x84
	ldrsb r3, [r4, r3]
	sub r3, r1, r3
	strb r3, [r6, #0x0]
_02007FB6:
	ldrb r3, [r6, #0x0]
	mov r5, #0x84
	lsl r4, r3, #0x1
	add r7, r0, r4
	ldrsb r7, [r7, r5]
	sub r5, #0x85
	cmp r7, r5
	blt _02007F7C
_02007FC6:
	add r2, r0, r4
	mov r1, #0x84
	ldrsb r2, [r2, r1]
	sub r1, #0x85
	cmp r2, r1
	beq _02007FD6
	cmp r3, #0xa
	blo _02007FE6
_02007FD6:
	add r1, r0, #0x0
	mov r2, #0x0
	add r1, #0x5b
	strb r2, [r1, #0x0]
	add r0, #0x58
	strb r2, [r0, #0x0]
	pop {r4-r7}
	bx lr
_02007FE6:
	add r1, r0, #0x0
	add r1, #0x5b
	strb r2, [r1, #0x0]
	ldrb r1, [r6, #0x0]
	lsl r1, r1, #0x1
	add r1, r0, r1
	add r1, #0x85
	ldrb r1, [r1, #0x0]
	add r0, #0x5a
	strb r1, [r0, #0x0]
	pop {r4-r7}
	bx lr
_02007FFE:
	add r1, r0, #0x0
	add r1, #0x5a
	ldrb r1, [r1, #0x0]
	add r0, #0x5a
	sub r1, r1, #0x1
	strb r1, [r0, #0x0]
_0200800A:
	pop {r4-r7}
	bx lr
	.balign 4

	thumb_func_start FUN_02008010
FUN_02008010: ; 0x02008010
	mov r2, #0x1
	strb r2, [r0, #0x0]
	mov r3, #0x0
	strb r3, [r0, #0x2]
	ldrsb r2, [r1, r3]
	strb r2, [r0, #0x1]
	ldrb r2, [r1, #0x1]
	strb r2, [r0, #0x3]
	str r1, [r0, #0x10]
	add r2, r3, #0x0
_02008024:
	add r1, r0, r3
	add r3, r3, #0x1
	strb r2, [r1, #0x4]
	cmp r3, #0xa
	blt _02008024
	bx lr

	thumb_func_start FUN_02008030
FUN_02008030: ; 0x02008030
	push {r4-r7}
	ldrb r1, [r0, #0x0]
	cmp r1, #0x0
	beq _020080C6
	add r3, r0, #0x2
	ldr r4, [r0, #0x10]
	cmp r1, #0x0
	beq _020080C0
	ldrb r1, [r0, #0x3]
	cmp r1, #0x0
	bne _020080BC
	ldrb r1, [r3, #0x0]
	add r1, r1, #0x1
	strb r1, [r3, #0x0]
	ldrb r2, [r3, #0x0]
	mov r1, #0x0
	mvn r1, r1
	lsl r5, r2, #0x1
	ldrsb r6, [r4, r5]
	cmp r6, r1
	bge _02008098
	mov r1, #0x0
_0200805C:
	add r5, r0, r2
	ldrb r2, [r5, #0x4]
	add r2, r2, #0x1
	strb r2, [r5, #0x4]
	ldrb r2, [r3, #0x0]
	add r5, r0, r2
	lsl r2, r2, #0x1
	add r2, r4, r2
	ldrb r7, [r2, #0x1]
	ldrb r6, [r5, #0x4]
	cmp r7, r6
	beq _02008078
	cmp r7, #0x0
	bne _0200807E
_02008078:
	strb r1, [r5, #0x4]
	add r3, r3, #0x1
	b _0200808A
_0200807E:
	mov r5, #0x0
	ldrsb r5, [r2, r5]
	mov r2, #0x1
	mvn r2, r2
	sub r2, r2, r5
	strb r2, [r3, #0x0]
_0200808A:
	ldrb r2, [r3, #0x0]
	mov r6, #0x0
	mvn r6, r6
	lsl r5, r2, #0x1
	ldrsb r7, [r4, r5]
	cmp r7, r6
	blt _0200805C
_02008098:
	ldrsb r5, [r4, r5]
	mov r1, #0x0
	mvn r1, r1
	cmp r5, r1
	beq _020080A6
	cmp r2, #0xa
	blo _020080AE
_020080A6:
	mov r1, #0x0
	strb r1, [r0, #0x1]
	strb r1, [r0, #0x0]
	b _020080C0
_020080AE:
	strb r5, [r0, #0x1]
	ldrb r1, [r3, #0x0]
	lsl r1, r1, #0x1
	add r1, r4, r1
	ldrb r1, [r1, #0x1]
	strb r1, [r0, #0x3]
	b _020080C0
_020080BC:
	sub r1, r1, #0x1
	strb r1, [r0, #0x3]
_020080C0:
	ldrb r0, [r0, #0x1]
	pop {r4-r7}
	bx lr
_020080C6:
	mov r0, #0x0
	mvn r0, r0
	pop {r4-r7}
	bx lr
	.balign 4

	thumb_func_start FUN_020080D0
FUN_020080D0: ; 0x020080D0
	ldr r2, [r0, #0x0]
	mov r1, #0x80
	orr r2, r1
	add r1, #0x80
	orr r1, r2
	str r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_020080E0
FUN_020080E0: ; 0x020080E0
	push {r3-r4}
	add r2, r0, #0x0
	add r3, r2, #0x0
	add r4, r2, #0x4
	add r3, #0x14
	ldmia r4!, {r0-r1}
	stmia r3!, {r0-r1}
	ldmia r4!, {r0-r1}
	stmia r3!, {r0-r1}
	add r0, r2, #0x0
	add r0, #0x6c
	ldrh r1, [r0, #0x0]
	add r0, r2, #0x0
	add r0, #0x78
	strh r1, [r0, #0x0]
	add r0, r2, #0x0
	add r0, #0x6e
	ldrh r1, [r0, #0x0]
	add r0, r2, #0x0
	add r0, #0x7a
	strh r1, [r0, #0x0]
	add r0, r2, #0x0
	add r0, #0x70
	ldrh r1, [r0, #0x0]
	add r0, r2, #0x0
	add r0, #0x7c
	strh r1, [r0, #0x0]
	add r0, r2, #0x0
	add r0, #0x72
	ldrh r1, [r0, #0x0]
	add r0, r2, #0x0
	add r0, #0x7e
	strh r1, [r0, #0x0]
	add r0, r2, #0x0
	add r0, #0x74
	ldrh r1, [r0, #0x0]
	add r0, r2, #0x0
	add r0, #0x80
	strh r1, [r0, #0x0]
	add r0, r2, #0x0
	add r0, #0x76
	ldrh r0, [r0, #0x0]
	add r2, #0x82
	strh r0, [r2, #0x0]
	pop {r3-r4}
	bx lr

	thumb_func_start FUN_0200813C
FUN_0200813C: ; 0x0200813C
	push {r3-r4}
	add r2, r0, #0x0
	add r4, r2, #0x0
	add r4, #0x14
	add r3, r2, #0x4
	ldmia r4!, {r0-r1}
	stmia r3!, {r0-r1}
	ldmia r4!, {r0-r1}
	stmia r3!, {r0-r1}
	add r0, r2, #0x0
	add r0, #0x78
	ldrh r1, [r0, #0x0]
	add r0, r2, #0x0
	add r0, #0x6c
	strh r1, [r0, #0x0]
	add r0, r2, #0x0
	add r0, #0x7a
	ldrh r1, [r0, #0x0]
	add r0, r2, #0x0
	add r0, #0x6e
	strh r1, [r0, #0x0]
	add r0, r2, #0x0
	add r0, #0x7c
	ldrh r1, [r0, #0x0]
	add r0, r2, #0x0
	add r0, #0x70
	strh r1, [r0, #0x0]
	add r0, r2, #0x0
	add r0, #0x7e
	ldrh r1, [r0, #0x0]
	add r0, r2, #0x0
	add r0, #0x72
	strh r1, [r0, #0x0]
	add r0, r2, #0x0
	add r0, #0x80
	ldrh r1, [r0, #0x0]
	add r0, r2, #0x0
	add r0, #0x74
	strh r1, [r0, #0x0]
	add r0, r2, #0x0
	add r0, #0x82
	ldrh r1, [r0, #0x0]
	add r0, r2, #0x0
	add r0, #0x76
	strh r1, [r0, #0x0]
	ldr r1, [r2, #0x0]
	mov r0, #0x80
	orr r1, r0
	add r0, #0x80
	orr r0, r1
	str r0, [r2, #0x0]
	pop {r3-r4}
	bx lr
	.balign 4

	thumb_func_start FUN_020081A8
FUN_020081A8: ; 0x020081A8
	mov r3, #0xa7
	lsl r3, r3, #0x2
	str r1, [r0, r3]
	add r1, r3, #0x4
	str r2, [r0, r1]
	bx lr

	thumb_func_start FUN_020081B4
FUN_020081B4: ; 0x020081B4
	mov r3, #0xa9
	lsl r3, r3, #0x2
	str r1, [r0, r3]
	add r1, r3, #0x4
	str r2, [r0, r1]
	bx lr

	thumb_func_start FUN_020081C0
FUN_020081C0: ; 0x020081C0
	add r0, r0, #0x4
	bx lr

	thumb_func_start FUN_020081C4
FUN_020081C4: ; 0x020081C4
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, _02008254 ; =0x000002E1
	ldrb r1, [r4, r0]
	cmp r1, #0x0
	beq _02008212
	mov r1, #0x0
	strb r1, [r4, r0]
	sub r0, #0x81
	add r0, r4, r0
	bl NNS_G2dInitImageProxy
	mov r3, #0xae
	lsl r3, r3, #0x2
	mov r1, #0x20
	strh r1, [r4, r3]
	add r0, r3, #0x2
	strh r1, [r4, r0]
	add r0, r3, #0x0
	sub r0, #0x18
	ldr r1, [r4, r0]
	add r0, r3, #0x0
	add r0, #0x10
	str r1, [r4, r0]
	add r0, r3, #0x0
	sub r0, #0xc
	ldr r1, [r4, r0]
	add r0, r3, #0x0
	add r0, #0x14
	str r1, [r4, r0]
	add r1, r3, #0x0
	sub r1, #0x1c
	add r0, r4, r3
	sub r3, #0x58
	ldr r1, [r4, r1]
	mov r2, #0x0
	add r3, r4, r3
	bl NNS_G2dLoadImage2DMapping
_02008212:
	ldr r0, _02008258 ; =0x000002E2
	ldrb r1, [r4, r0]
	cmp r1, #0x0
	beq _02008252
	mov r1, #0x0
	strb r1, [r4, r0]
	sub r0, #0x5e
	add r0, r4, r0
	bl NNS_G2dInitImagePaletteProxy
	mov r3, #0xaa
	lsl r3, r3, #0x2
	add r0, r3, #0x0
	ldr r1, [r4, r3]
	add r0, #0x30
	str r1, [r4, r0]
	add r0, r3, #0x0
	add r0, #0x8
	ldr r1, [r4, r0]
	add r0, r3, #0x0
	add r0, #0x34
	str r1, [r4, r0]
	add r0, r3, #0x0
	sub r1, r3, #0x4
	add r0, #0x28
	sub r3, #0x24
	ldr r1, [r4, r1]
	add r0, r4, r0
	mov r2, #0x0
	add r3, r4, r3
	bl NNS_G2dLoadPalette
_02008252:
	pop {r4, pc}
	.balign 4
_02008254: .word 0x000002E1
_02008258: .word 0x000002E2

	thumb_func_start FUN_0200825C
FUN_0200825C: ; 0x0200825C
	ldr r2, _02008264 ; =0x000002E3
	strb r1, [r0, r2]
	bx lr
	nop
_02008264: .word 0x000002E3

	thumb_func_start FUN_02008268
FUN_02008268: ; 0x02008268
	push {r4, lr}
	add r4, r0, #0x0
	bne _02008272
	bl GF_AssertFail
_02008272:
	ldr r0, [r4, #0x0]
	lsl r0, r0, #0x1f
	lsr r0, r0, #0x1f
	beq _0200827E
	mov r0, #0x1
	pop {r4, pc}
_0200827E:
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02008284
FUN_02008284: ; 0x02008284
	mov r2, #0xb9
	lsl r2, r2, #0x2
	ldr r3, [r0, r2]
	orr r1, r3
	str r1, [r0, r2]
	bx lr

	thumb_func_start FUN_02008290
FUN_02008290: ; 0x02008290
	push {r3-r4}
	mov r3, #0xb9
	lsl r3, r3, #0x2
	mov r2, #0x0
	mvn r2, r2
	ldr r4, [r0, r3]
	eor r1, r2
	and r1, r4
	str r1, [r0, r3]
	pop {r3-r4}
	bx lr
	.balign 4

	thumb_func_start FUN_020082A8
FUN_020082A8: ; 0x020082A8
	push {r4-r7, lr}
	sub sp, #0x5c
	add r6, r0, #0x0
	mov r0, #0x0
	str r0, [sp, #0x48]
	str r0, [sp, #0x54]
	ldr r0, [sp, #0x48]
	str r6, [sp, #0x44]
	str r0, [sp, #0x38]
_020082BA:
	ldr r0, [sp, #0x44]
	ldr r1, [r0, #0x0]
	lsl r0, r1, #0x1f
	lsr r0, r0, #0x1f
	beq _020082CA
	lsl r0, r1, #0x18
	lsr r0, r0, #0x1f
	bne _020082CC
_020082CA:
	b _020086C2
_020082CC:
	mov r0, #0x80
	bic r1, r0
	ldr r0, [sp, #0x44]
	mov r2, #0xa6
	str r1, [r0, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x48]
	ldr r0, [sp, #0x44]
	ldr r1, [sp, #0x44]
	lsl r2, r2, #0x2
	ldrh r0, [r0, #0x4]
	ldrh r1, [r1, #0x6]
	ldr r2, [r6, r2]
	bl AllocAndReadWholeNarcMemberByIdPair
	add r1, sp, #0x58
	str r0, [sp, #0x4c]
	bl NNS_G2dGetUnpackedCharacterData
	ldr r0, [sp, #0x58]
	mov r1, #0xaf
	ldr r0, [r0, #0x4]
	lsl r1, r1, #0x2
	str r0, [r6, r1]
	ldr r0, [sp, #0x58]
	ldr r2, [r0, #0x8]
	add r0, r1, #0x4
	str r2, [r6, r0]
	ldr r0, [sp, #0x58]
	add r1, #0x8
	ldr r0, [r0, #0xc]
	str r0, [r6, r1]
	ldr r0, [sp, #0x58]
	ldr r0, [r0, #0x14]
	str r0, [sp, #0x50]
	bl FUN_02008A74
	ldr r0, [sp, #0x44]
	ldr r1, [sp, #0x50]
	bl FUN_020088EC
	ldr r0, [sp, #0x54]
	cmp r0, #0x3
	beq _02008326
	b _02008554
_02008326:
	mov r5, #0x0
	add r0, r5, #0x0
	str r5, [sp, #0x14]
	str r0, [sp, #0x24]
_0200832E:
	ldr r0, [sp, #0x14]
	mov r1, #0x4f
	sub r2, r1, r0
	mov r0, #0x50
	add r1, r2, #0x0
	mul r1, r0
	ldr r0, [sp, #0x50]
	mov r4, #0x0
	add r0, r0, r1
	str r0, [sp, #0x20]
	ldr r1, [sp, #0x50]
	ldr r0, [sp, #0x24]
	add r7, r1, r0
	ldr r0, [sp, #0x20]
	str r7, [sp, #0x18]
	str r0, [sp, #0x1c]
	ldr r0, [sp, #0x14]
	sub r0, r0, #0x1
	lsl r0, r0, #0x7
	str r0, [sp, #0x10]
_02008356:
	cmp r4, #0x28
	bge _02008442
	ldr r0, [sp, #0x44]
	ldr r1, [r0, #0x54]
	lsl r0, r1, #0x16
	lsr r0, r0, #0x1f
	beq _02008386
	lsl r1, r1, #0x15
	lsr r1, r1, #0x1f
	beq _02008386
	mov r0, #0x27
	sub r1, r0, r4
	ldr r0, [sp, #0x1c]
	ldrb r0, [r0, r1]
	bl FUN_020088D8
	mov r1, #0xab
	lsl r1, r1, #0x2
	ldr r1, [r6, r1]
	add r1, r5, r1
	add r1, r4, r1
	add r1, #0x50
	strb r0, [r1, #0x0]
	b _0200852E
_02008386:
	cmp r0, #0x0
	beq _020083A6
	mov r0, #0x27
	sub r1, r0, r4
	ldr r0, [sp, #0x18]
	ldrb r0, [r0, r1]
	bl FUN_020088D8
	mov r1, #0xab
	lsl r1, r1, #0x2
	ldr r1, [r6, r1]
	add r1, r5, r1
	add r1, r4, r1
	add r1, #0x50
	strb r0, [r1, #0x0]
	b _0200852E
_020083A6:
	ldr r0, [sp, #0x44]
	ldr r0, [r0, #0x54]
	lsl r1, r0, #0x15
	lsr r1, r1, #0x1f
	beq _020083C4
	mov r1, #0xab
	lsl r1, r1, #0x2
	ldr r0, [sp, #0x20]
	ldr r1, [r6, r1]
	ldrb r0, [r0, #0x0]
	add r1, r5, r1
	add r1, r4, r1
	add r1, #0x50
	strb r0, [r1, #0x0]
	b _0200852E
_020083C4:
	lsl r0, r0, #0xf
	lsr r0, r0, #0x1c
	str r0, [sp, #0xc]
	beq _02008430
	ldr r1, [sp, #0xc]
	ldr r0, [sp, #0x14]
	lsl r1, r1, #0x1
	bl _u32_div_f
	cmp r1, #0x0
	beq _020083F4
	mov r0, #0xab
	lsl r0, r0, #0x2
	ldr r1, [r6, r0]
	ldr r0, [sp, #0x10]
	add r0, r0, r1
	add r0, r4, r0
	add r0, #0x50
	add r1, r5, r1
	add r1, r4, r1
	ldrb r0, [r0, #0x0]
	add r1, #0x50
	strb r0, [r1, #0x0]
	b _0200852E
_020083F4:
	ldr r1, [sp, #0xc]
	add r0, r4, #0x0
	bl _u32_div_f
	cmp r1, #0x0
	beq _02008416
	mov r0, #0xab
	lsl r0, r0, #0x2
	ldr r0, [r6, r0]
	add r2, r5, r0
	add r0, r2, r4
	add r0, #0x4f
	ldrb r1, [r0, #0x0]
	add r0, r2, r4
	add r0, #0x50
	strb r1, [r0, #0x0]
	b _0200852E
_02008416:
	ldrb r1, [r7, #0x0]
	mov r0, #0xf
	and r1, r0
	lsl r0, r1, #0x4
	orr r0, r1
	mov r1, #0xab
	lsl r1, r1, #0x2
	ldr r1, [r6, r1]
	add r1, r5, r1
	add r1, r4, r1
	add r1, #0x50
	strb r0, [r1, #0x0]
	b _0200852E
_02008430:
	mov r1, #0xab
	lsl r1, r1, #0x2
	ldr r1, [r6, r1]
	ldrb r0, [r7, #0x0]
	add r1, r5, r1
	add r1, r4, r1
	add r1, #0x50
	strb r0, [r1, #0x0]
	b _0200852E
_02008442:
	ldr r0, [sp, #0x44]
	ldr r1, [r0, #0x54]
	lsl r0, r1, #0x16
	lsr r0, r0, #0x1f
	beq _02008472
	lsl r1, r1, #0x15
	lsr r1, r1, #0x1f
	beq _02008472
	add r1, r4, #0x0
	sub r1, #0x28
	mov r0, #0x4f
	sub r1, r0, r1
	ldr r0, [sp, #0x1c]
	ldrb r0, [r0, r1]
	bl FUN_020088D8
	mov r1, #0xab
	lsl r1, r1, #0x2
	ldr r1, [r6, r1]
	add r1, r5, r1
	add r2, r4, r1
	ldr r1, _020086E8 ; =0x00002828
	strb r0, [r2, r1]
	b _0200852E
_02008472:
	cmp r0, #0x0
	beq _02008496
	add r1, r4, #0x0
	sub r1, #0x28
	mov r0, #0x4f
	sub r1, r0, r1
	ldr r0, [sp, #0x18]
	ldrb r0, [r0, r1]
	bl FUN_020088D8
	mov r1, #0xab
	lsl r1, r1, #0x2
	ldr r1, [r6, r1]
	add r1, r5, r1
	add r2, r4, r1
	ldr r1, _020086E8 ; =0x00002828
	strb r0, [r2, r1]
	b _0200852E
_02008496:
	ldr r0, [sp, #0x44]
	ldr r0, [r0, #0x54]
	lsl r1, r0, #0x15
	lsr r1, r1, #0x1f
	beq _020084B4
	mov r1, #0xab
	lsl r1, r1, #0x2
	ldr r0, [sp, #0x20]
	ldr r1, [r6, r1]
	ldrb r0, [r0, #0x0]
	add r1, r5, r1
	add r2, r4, r1
	ldr r1, _020086E8 ; =0x00002828
	strb r0, [r2, r1]
	b _0200852E
_020084B4:
	lsl r0, r0, #0xf
	lsr r0, r0, #0x1c
	str r0, [sp, #0x8]
	beq _0200851E
	ldr r1, [sp, #0x8]
	ldr r0, [sp, #0x14]
	lsl r1, r1, #0x1
	bl _u32_div_f
	cmp r1, #0x0
	beq _020084E4
	mov r0, #0xab
	lsl r0, r0, #0x2
	ldr r1, [r6, r0]
	ldr r0, [sp, #0x10]
	add r0, r0, r1
	add r2, r4, r0
	ldr r0, _020086E8 ; =0x00002828
	add r1, r5, r1
	ldrb r0, [r2, r0]
	add r2, r4, r1
	ldr r1, _020086E8 ; =0x00002828
	strb r0, [r2, r1]
	b _0200852E
_020084E4:
	ldr r1, [sp, #0x8]
	add r0, r4, #0x0
	bl _u32_div_f
	cmp r1, #0x0
	beq _02008504
	mov r0, #0xab
	lsl r0, r0, #0x2
	ldr r0, [r6, r0]
	ldr r1, _020086EC ; =0x00002827
	add r0, r5, r0
	add r0, r0, r4
	ldrb r2, [r0, r1]
	add r1, r1, #0x1
	strb r2, [r0, r1]
	b _0200852E
_02008504:
	ldrb r1, [r7, #0x0]
	mov r0, #0xf
	and r1, r0
	lsl r0, r1, #0x4
	orr r0, r1
	mov r1, #0xab
	lsl r1, r1, #0x2
	ldr r1, [r6, r1]
	add r1, r5, r1
	add r2, r4, r1
	ldr r1, _020086E8 ; =0x00002828
	strb r0, [r2, r1]
	b _0200852E
_0200851E:
	mov r1, #0xab
	lsl r1, r1, #0x2
	ldr r1, [r6, r1]
	ldrb r0, [r7, #0x0]
	add r1, r5, r1
	add r2, r4, r1
	ldr r1, _020086E8 ; =0x00002828
	strb r0, [r2, r1]
_0200852E:
	ldr r0, [sp, #0x20]
	add r4, r4, #0x1
	add r0, r0, #0x1
	add r7, r7, #0x1
	str r0, [sp, #0x20]
	cmp r4, #0x50
	bge _0200853E
	b _02008356
_0200853E:
	ldr r0, [sp, #0x24]
	add r5, #0x80
	add r0, #0x50
	str r0, [sp, #0x24]
	ldr r0, [sp, #0x14]
	add r0, r0, #0x1
	str r0, [sp, #0x14]
	cmp r0, #0x50
	bge _02008552
	b _0200832E
_02008552:
	b _020086BC
_02008554:
	mov r0, #0x0
	str r0, [sp, #0x0]
	str r0, [sp, #0x40]
	str r0, [sp, #0x3c]
_0200855C:
	ldr r0, [sp, #0x0]
	mov r1, #0x4f
	sub r2, r1, r0
	mov r0, #0x50
	add r1, r2, #0x0
	mul r1, r0
	ldr r0, [sp, #0x50]
	mov r4, #0x0
	add r0, r0, r1
	str r0, [sp, #0x34]
	ldr r1, [sp, #0x50]
	ldr r0, [sp, #0x3c]
	add r7, r1, r0
	ldr r0, [sp, #0x34]
	ldr r1, [sp, #0x38]
	str r0, [sp, #0x30]
	ldr r0, [sp, #0x40]
	str r7, [sp, #0x2c]
	add r5, r1, r0
	ldr r0, [sp, #0x0]
	sub r0, r0, #0x1
	lsl r1, r0, #0x7
	ldr r0, [sp, #0x38]
	add r0, r0, r1
	str r0, [sp, #0x28]
_0200858E:
	ldr r0, [sp, #0x44]
	ldr r1, [r0, #0x54]
	lsl r0, r1, #0x16
	lsr r0, r0, #0x1f
	beq _020085D6
	lsl r1, r1, #0x15
	lsr r1, r1, #0x1f
	beq _020085D6
	cmp r4, #0x28
	bge _020085BA
	mov r0, #0x27
	sub r1, r0, r4
	ldr r0, [sp, #0x30]
	ldrb r0, [r0, r1]
	bl FUN_020088D8
	mov r1, #0xab
	lsl r1, r1, #0x2
	ldr r1, [r6, r1]
	add r1, r5, r1
	strb r0, [r4, r1]
	b _02008694
_020085BA:
	add r1, r4, #0x0
	sub r1, #0x28
	mov r0, #0x4f
	sub r1, r0, r1
	ldr r0, [sp, #0x30]
	ldrb r0, [r0, r1]
	bl FUN_020088D8
	mov r1, #0xab
	lsl r1, r1, #0x2
	ldr r1, [r6, r1]
	add r1, r5, r1
	strb r0, [r4, r1]
	b _02008694
_020085D6:
	cmp r0, #0x0
	beq _02008612
	cmp r4, #0x28
	bge _020085F6
	mov r0, #0x27
	sub r1, r0, r4
	ldr r0, [sp, #0x2c]
	ldrb r0, [r0, r1]
	bl FUN_020088D8
	mov r1, #0xab
	lsl r1, r1, #0x2
	ldr r1, [r6, r1]
	add r1, r5, r1
	strb r0, [r4, r1]
	b _02008694
_020085F6:
	add r1, r4, #0x0
	sub r1, #0x28
	mov r0, #0x4f
	sub r1, r0, r1
	ldr r0, [sp, #0x2c]
	ldrb r0, [r0, r1]
	bl FUN_020088D8
	mov r1, #0xab
	lsl r1, r1, #0x2
	ldr r1, [r6, r1]
	add r1, r5, r1
	strb r0, [r4, r1]
	b _02008694
_02008612:
	ldr r0, [sp, #0x44]
	ldr r0, [r0, #0x54]
	lsl r1, r0, #0x15
	lsr r1, r1, #0x1f
	beq _0200862C
	ldr r0, [sp, #0x34]
	mov r1, #0xab
	lsl r1, r1, #0x2
	ldr r1, [r6, r1]
	ldrb r0, [r0, #0x0]
	add r1, r5, r1
	strb r0, [r4, r1]
	b _02008694
_0200862C:
	lsl r0, r0, #0xf
	lsr r0, r0, #0x1c
	str r0, [sp, #0x4]
	beq _02008688
	ldr r1, [sp, #0x4]
	ldr r0, [sp, #0x0]
	lsl r1, r1, #0x1
	bl _u32_div_f
	cmp r1, #0x0
	beq _02008654
	mov r0, #0xab
	lsl r0, r0, #0x2
	ldr r0, [r6, r0]
	ldr r1, [sp, #0x28]
	add r1, r1, r0
	ldrb r1, [r4, r1]
	add r0, r5, r0
	strb r1, [r4, r0]
	b _02008694
_02008654:
	ldr r1, [sp, #0x4]
	add r0, r4, #0x0
	bl _u32_div_f
	cmp r1, #0x0
	beq _02008672
	mov r0, #0xab
	lsl r0, r0, #0x2
	ldr r0, [r6, r0]
	add r1, r5, r0
	add r0, r1, r4
	sub r0, r0, #0x1
	ldrb r0, [r0, #0x0]
	strb r0, [r1, r4]
	b _02008694
_02008672:
	ldrb r1, [r7, #0x0]
	mov r0, #0xf
	and r1, r0
	lsl r0, r1, #0x4
	orr r0, r1
	mov r1, #0xab
	lsl r1, r1, #0x2
	ldr r1, [r6, r1]
	add r1, r5, r1
	strb r0, [r4, r1]
	b _02008694
_02008688:
	mov r1, #0xab
	lsl r1, r1, #0x2
	ldr r1, [r6, r1]
	ldrb r0, [r7, #0x0]
	add r1, r5, r1
	strb r0, [r4, r1]
_02008694:
	ldr r0, [sp, #0x34]
	add r4, r4, #0x1
	add r0, r0, #0x1
	add r7, r7, #0x1
	str r0, [sp, #0x34]
	cmp r4, #0x50
	bge _020086A4
	b _0200858E
_020086A4:
	ldr r0, [sp, #0x40]
	add r0, #0x80
	str r0, [sp, #0x40]
	ldr r0, [sp, #0x3c]
	add r0, #0x50
	str r0, [sp, #0x3c]
	ldr r0, [sp, #0x0]
	add r0, r0, #0x1
	str r0, [sp, #0x0]
	cmp r0, #0x50
	bge _020086BC
	b _0200855C
_020086BC:
	ldr r0, [sp, #0x4c]
	bl FreeToHeap
_020086C2:
	ldr r0, [sp, #0x44]
	mov r1, #0xa
	add r0, #0x98
	str r0, [sp, #0x44]
	ldr r0, [sp, #0x38]
	lsl r1, r1, #0xa
	add r0, r0, r1
	str r0, [sp, #0x38]
	ldr r0, [sp, #0x54]
	add r0, r0, #0x1
	str r0, [sp, #0x54]
	cmp r0, #0x4
	bge _020086DE
	b _020082BA
_020086DE:
	ldr r1, _020086F0 ; =0x000002E1
	ldr r0, [sp, #0x48]
	strb r0, [r6, r1]
	add sp, #0x5c
	pop {r4-r7, pc}
	.balign 4
_020086E8: .word 0x00002828
_020086EC: .word 0x00002827
_020086F0: .word 0x000002E1

	thumb_func_start FUN_020086F4
FUN_020086F4: ; 0x020086F4
	push {r4-r7, lr}
	sub sp, #0x1c
	add r5, r0, #0x0
	mov r0, #0x0
	str r0, [sp, #0xc]
	str r0, [sp, #0x14]
	ldr r0, [sp, #0xc]
	add r4, r5, #0x0
	str r0, [sp, #0x8]
_02008706:
	ldr r1, [r4, #0x0]
	lsl r0, r1, #0x1f
	lsr r0, r0, #0x1f
	beq _020087E0
	lsl r0, r1, #0x17
	lsr r0, r0, #0x1f
	beq _020087E0
	ldr r0, _020088CC ; =0xFFFFFEFF
	mov r2, #0xa6
	and r0, r1
	str r0, [r4, #0x0]
	mov r0, #0x1
	str r0, [sp, #0xc]
	lsl r2, r2, #0x2
	ldrh r0, [r4, #0x4]
	ldrh r1, [r4, #0x8]
	ldr r2, [r5, r2]
	bl AllocAndReadWholeNarcMemberByIdPair
	add r1, sp, #0x18
	str r0, [sp, #0x10]
	bl NNS_G2dGetUnpackedPaletteData
	ldr r0, [sp, #0x18]
	mov r7, #0x0
	ldr r1, [r0, #0x0]
	mov r0, #0x2d
	lsl r0, r0, #0x4
	str r1, [r5, r0]
	ldr r0, [sp, #0x18]
	add r2, r7, #0x0
	ldr r1, [r0, #0xc]
	ldr r0, [sp, #0x8]
	lsl r3, r0, #0x1
_0200874A:
	mov r6, #0x2b
	lsl r6, r6, #0x4
	ldr r6, [r5, r6]
	ldrh r0, [r1, #0x0]
	add r6, r3, r6
	add r7, r7, #0x1
	strh r0, [r2, r6]
	mov r6, #0xad
	lsl r6, r6, #0x2
	ldrh r0, [r1, #0x0]
	ldr r6, [r5, r6]
	add r1, r1, #0x2
	add r6, r3, r6
	strh r0, [r2, r6]
	add r2, r2, #0x2
	cmp r7, #0x10
	blt _0200874A
	ldr r0, [sp, #0x10]
	bl FreeToHeap
	add r0, r4, #0x0
	add r0, #0x6c
	ldrh r0, [r0, #0x0]
	lsl r0, r0, #0x1e
	lsr r0, r0, #0x1e
	beq _020087E0
	mov r2, #0xa6
	lsl r2, r2, #0x2
	ldr r2, [r5, r2]
	mov r0, #0x75 ; NARC_POKETOOL_POKEGRA_OTHERPOKE
	mov r1, #0xd4
	bl AllocAndReadWholeNarcMemberByIdPair
	add r1, sp, #0x18
	str r0, [sp, #0x4]
	bl NNS_G2dGetUnpackedPaletteData
	ldr r0, [sp, #0x18]
	mov r7, #0xad
	ldr r0, [r0, #0xc]
	mov r1, #0x0
	lsl r7, r7, #0x2
_0200879E:
	add r6, r4, #0x0
	add r6, #0x6c
	ldrh r6, [r6, #0x0]
	mov r2, #0x2b
	lsl r2, r2, #0x4
	lsl r6, r6, #0x1e
	lsr r6, r6, #0x1e
	add r6, r6, #0x3
	lsl r6, r6, #0x4
	add r6, r1, r6
	ldrh r3, [r0, #0x0]
	ldr r2, [r5, r2]
	lsl r6, r6, #0x1
	strh r3, [r2, r6]
	add r6, r4, #0x0
	add r6, #0x6c
	ldrh r6, [r6, #0x0]
	ldrh r3, [r0, #0x0]
	ldr r2, [r5, r7]
	lsl r6, r6, #0x1e
	lsr r6, r6, #0x1e
	add r6, r6, #0x3
	lsl r6, r6, #0x4
	add r6, r1, r6
	lsl r6, r6, #0x1
	add r1, r1, #0x1
	add r0, r0, #0x2
	strh r3, [r2, r6]
	cmp r1, #0x10
	blt _0200879E
	ldr r0, [sp, #0x4]
	bl FreeToHeap
_020087E0:
	ldr r0, [r4, #0x0]
	lsl r0, r0, #0x1f
	lsr r0, r0, #0x1f
	beq _020088AE
	ldr r0, [r4, #0x54]
	lsl r0, r0, #0x13
	lsr r0, r0, #0x1f
	beq _020088AE
	add r0, r4, #0x0
	add r0, #0x4a
	ldrb r0, [r0, #0x0]
	cmp r0, #0x0
	bne _020088A0
	mov r0, #0x1
	str r0, [sp, #0xc]
	add r0, r4, #0x0
	add r0, #0x4b
	ldrb r1, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x4a
	strb r1, [r0, #0x0]
	ldr r0, [sp, #0x8]
	mov r2, #0xad
	lsl r1, r0, #0x1
	ldr r0, [r4, #0x4c]
	add r3, r4, #0x0
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	lsl r2, r2, #0x2
	str r0, [sp, #0x0]
	ldr r0, [r5, r2]
	sub r2, r2, #0x4
	add r3, #0x48
	ldr r2, [r5, r2]
	add r0, r0, r1
	add r1, r2, r1
	ldrb r3, [r3, #0x0]
	mov r2, #0x10
	bl BlendPalette
	add r0, r4, #0x0
	add r0, #0x6c
	ldrh r0, [r0, #0x0]
	lsl r0, r0, #0x1e
	lsr r0, r0, #0x1e
	beq _02008862
	add r0, r0, #0x3
	lsl r1, r0, #0x5
	ldr r0, [r4, #0x4c]
	mov r2, #0xad
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	add r3, r4, #0x0
	lsl r2, r2, #0x2
	str r0, [sp, #0x0]
	ldr r0, [r5, r2]
	sub r2, r2, #0x4
	add r3, #0x48
	ldr r2, [r5, r2]
	add r0, r0, r1
	add r1, r2, r1
	ldrb r3, [r3, #0x0]
	mov r2, #0x10
	bl BlendPalette
_02008862:
	add r0, r4, #0x0
	add r0, #0x49
	ldrb r1, [r0, #0x0]
	add r0, r4, #0x0
	add r0, #0x48
	ldrb r0, [r0, #0x0]
	cmp r0, r1
	bne _0200887C
	ldr r1, [r4, #0x54]
	ldr r0, _020088D0 ; =0xFFFFEFFF
	and r0, r1
	str r0, [r4, #0x54]
	b _020088AE
_0200887C:
	cmp r0, r1
	bls _02008890
	add r0, r4, #0x0
	add r0, #0x48
	ldrb r0, [r0, #0x0]
	sub r1, r0, #0x1
	add r0, r4, #0x0
	add r0, #0x48
	strb r1, [r0, #0x0]
	b _020088AE
_02008890:
	add r0, r4, #0x0
	add r0, #0x48
	ldrb r0, [r0, #0x0]
	add r1, r0, #0x1
	add r0, r4, #0x0
	add r0, #0x48
	strb r1, [r0, #0x0]
	b _020088AE
_020088A0:
	add r0, r4, #0x0
	add r0, #0x4a
	ldrb r0, [r0, #0x0]
	sub r1, r0, #0x1
	add r0, r4, #0x0
	add r0, #0x4a
	strb r1, [r0, #0x0]
_020088AE:
	ldr r0, [sp, #0x8]
	add r4, #0x98
	add r0, #0x10
	str r0, [sp, #0x8]
	ldr r0, [sp, #0x14]
	add r0, r0, #0x1
	str r0, [sp, #0x14]
	cmp r0, #0x4
	bge _020088C2
	b _02008706
_020088C2:
	ldr r1, _020088D4 ; =0x000002E2
	ldr r0, [sp, #0xc]
	strb r0, [r5, r1]
	add sp, #0x1c
	pop {r4-r7, pc}
	.balign 4
_020088CC: .word 0xFFFFFEFF
_020088D0: .word 0xFFFFEFFF
_020088D4: .word 0x000002E2

	thumb_func_start FUN_020088D8
FUN_020088D8: ; 0x020088D8
	mov r1, #0xf0
	and r1, r0
	lsl r1, r1, #0x14
	lsl r0, r0, #0x1c
	lsr r1, r1, #0x18
	lsr r0, r0, #0x18
	orr r0, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bx lr

	thumb_func_start FUN_020088EC
FUN_020088EC: ; 0x020088EC
	push {r3, lr}
	add r2, r0, #0x0
	ldrh r0, [r2, #0xa]
	cmp r0, #0x0
	beq _02008900
	add r0, r1, #0x0
	ldr r1, [r2, #0x10]
	mov r2, #0x1
	bl FUN_02008904
_02008900:
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02008904
FUN_02008904: ; 0x02008904
	push {r4-r7, lr}
	sub sp, #0x1c
	add r3, r0, #0x0
	add r0, r1, #0x0
	mov lr, r0
	mov r0, #0x0
	mov r12, r0
	ldr r0, _02008A50 ; =UNK_02105AE8
	str r1, [sp, #0x0]
	str r2, [sp, #0x4]
	str r0, [sp, #0x10]
_0200891A:
	ldr r0, [sp, #0x10]
	mov r1, #0x0
	ldr r6, [r0, #0x0]
	ldrb r0, [r6, #0x0]
	cmp r0, #0xff
	beq _02008992
	ldr r0, [sp, #0x0]
	mov r2, #0xf
	and r0, r2
	str r0, [sp, #0xc]
	sub r0, #0x8
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x0]
	mov r2, #0xf0
	and r0, r2
	lsr r7, r0, #0x4
	sub r7, #0x8
_0200893C:
	lsl r0, r1, #0x1
	add r2, r6, r0
	ldrb r4, [r6, r0]
	ldrb r2, [r2, #0x1]
	ldr r0, [sp, #0xc]
	add r0, r0, r4
	add r2, r7, r2
	lsl r0, r0, #0x18
	lsl r2, r2, #0x18
	lsr r0, r0, #0x18
	lsr r4, r2, #0x18
	mov r2, #0x50
	mul r2, r4
	lsr r5, r0, #0x1
	add r2, r5, r2
	mov r4, #0x1
	tst r0, r4
	ldrb r4, [r3, r2]
	beq _02008974
	mov r0, #0xf0
	and r0, r4
	cmp r0, #0x10
	blt _02008984
	cmp r0, #0x30
	bgt _02008984
	add r4, #0x50
	strb r4, [r3, r2]
	b _02008984
_02008974:
	mov r0, #0xf
	and r0, r4
	cmp r0, #0x1
	blt _02008984
	cmp r0, #0x3
	bgt _02008984
	add r0, r4, #0x5
	strb r0, [r3, r2]
_02008984:
	add r0, r1, #0x1
	lsl r0, r0, #0x18
	lsr r1, r0, #0x18
	lsl r0, r1, #0x1
	ldrb r0, [r6, r0]
	cmp r0, #0xff
	bne _0200893C
_02008992:
	ldr r0, [sp, #0x0]
	lsr r0, r0, #0x8
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x10]
	add r0, r0, #0x4
	str r0, [sp, #0x10]
	mov r0, r12
	add r0, r0, #0x1
	mov r12, r0
	cmp r0, #0x4
	blt _0200891A
	mov r0, lr
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	beq _02008A4A
	mov r0, #0x0
	str r0, [sp, #0x8]
	ldr r0, _02008A50 ; =UNK_02105AE8
	str r0, [sp, #0x18]
_020089BA:
	ldr r0, [sp, #0x18]
	mov r4, #0x0
	ldr r2, [r0, #0x0]
	ldrb r0, [r2, #0x0]
	cmp r0, #0xff
	beq _02008A34
	ldr r0, [sp, #0x0]
	mov r1, #0xf
	and r0, r1
	str r0, [sp, #0x14]
	add r0, #0x48
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x0]
	mov r1, #0xf0
	and r0, r1
	lsr r7, r0, #0x4
	sub r7, #0x8
_020089DC:
	lsl r0, r4, #0x1
	add r5, r2, r0
	ldrb r1, [r2, r0]
	ldrb r5, [r5, #0x1]
	ldr r0, [sp, #0x14]
	sub r1, #0xe
	add r0, r0, r1
	add r5, r7, r5
	lsl r0, r0, #0x18
	lsl r5, r5, #0x18
	lsr r1, r0, #0x18
	lsr r6, r5, #0x18
	mov r5, #0x50
	lsr r0, r1, #0x1
	mul r5, r6
	add r0, r0, r5
	mov r5, #0x1
	tst r1, r5
	ldrb r5, [r3, r0]
	beq _02008A16
	mov r1, #0xf0
	and r1, r5
	cmp r1, #0x10
	blt _02008A26
	cmp r1, #0x30
	bgt _02008A26
	add r5, #0x50
	strb r5, [r3, r0]
	b _02008A26
_02008A16:
	mov r1, #0xf
	and r1, r5
	cmp r1, #0x1
	blt _02008A26
	cmp r1, #0x3
	bgt _02008A26
	add r1, r5, #0x5
	strb r1, [r3, r0]
_02008A26:
	add r0, r4, #0x1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	lsl r0, r4, #0x1
	ldrb r0, [r2, r0]
	cmp r0, #0xff
	bne _020089DC
_02008A34:
	ldr r0, [sp, #0x0]
	lsr r0, r0, #0x8
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x18]
	add r0, r0, #0x4
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x8]
	add r0, r0, #0x1
	str r0, [sp, #0x8]
	cmp r0, #0x4
	blt _020089BA
_02008A4A:
	add sp, #0x1c
	pop {r4-r7, pc}
	nop
_02008A50: .word UNK_02105AE8

	thumb_func_start FUN_02008A54
FUN_02008A54: ; 0x02008A54
	ldr r2, [r0, #0x0]
	ldr r1, _02008A6C ; =0x41C64E6D
	add r3, r2, #0x0
	mul r3, r1
	ldr r1, _02008A70 ; =0x00006073
	add r1, r3, r1
	str r1, [r0, #0x0]
	lsr r0, r1, #0x10
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bx lr
	nop
_02008A6C: .word 0x41C64E6D
_02008A70: .word 0x00006073

	thumb_func_start FUN_02008A74
FUN_02008A74: ; 0x02008A74
	push {r3-r7, lr}
	ldr r1, _02008AA0 ; =0x000018FE
	mov r6, #0x0
	ldrh r2, [r0, r1]
	lsr r4, r1, #0x1
	add r5, r0, r1
	str r2, [sp, #0x0]
	add r7, sp, #0x0
	mvn r6, r6
_02008A86:
	ldrh r1, [r5, #0x0]
	ldr r0, [sp, #0x0]
	eor r0, r1
	strh r0, [r5, #0x0]
	add r0, r7, #0x0
	bl FUN_02008A54
	sub r4, r4, #0x1
	sub r5, r5, #0x2
	cmp r4, r6
	bgt _02008A86
	pop {r3-r7, pc}
	nop
_02008AA0: .word 0x000018FE
