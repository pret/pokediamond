	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD11_0225C91C
MOD11_0225C91C: ; 0x0225C91C
	push {r3, r4, r5, lr}
	sub sp, #0x18
	add r5, r0, #0
	mov r0, #0x1b
	str r0, [sp]
	mov r0, #0x4a
	str r0, [sp, #4]
	mov r0, #0
	add r4, r1, #0
	str r0, [sp, #8]
	mov r0, #1
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	ldr r0, _0225C990 ; =0x00004E41
	mov r1, #2
	str r0, [sp, #0x14]
	add r0, r2, #0
	add r2, r5, #0
	add r3, r4, #0
	bl FUN_0200C0DC
	mov r0, #1
	str r0, [sp]
	str r0, [sp, #4]
	ldr r0, _0225C994 ; =0x00004FB9
	mov r2, #0x1b
	add r3, r2, #0
	str r0, [sp, #8]
	add r0, r5, #0
	add r1, r4, #0
	add r3, #0xf9
	bl FUN_0200C00C
	mov r0, #1
	str r0, [sp]
	ldr r0, _0225C998 ; =0x00004FB3
	mov r2, #0x1b
	add r3, r2, #0
	str r0, [sp, #4]
	add r0, r5, #0
	add r1, r4, #0
	add r3, #0xfa
	bl FUN_0200C124
	mov r0, #1
	str r0, [sp]
	ldr r0, _0225C99C ; =0x00004FA8
	mov r2, #0x1b
	add r3, r2, #0
	str r0, [sp, #4]
	add r0, r5, #0
	add r1, r4, #0
	add r3, #0xfb
	bl FUN_0200C13C
	add sp, #0x18
	pop {r3, r4, r5, pc}
	nop
_0225C990: .word 0x00004E41
_0225C994: .word 0x00004FB9
_0225C998: .word 0x00004FB3
_0225C99C: .word 0x00004FA8

	thumb_func_start MOD11_0225C9A0
MOD11_0225C9A0: ; 0x0225C9A0
	push {r4, lr}
	ldr r1, _0225C9C4 ; =0x00004FB9
	add r4, r0, #0
	bl FUN_0200C358
	ldr r1, _0225C9C8 ; =0x00004E41
	add r0, r4, #0
	bl FUN_0200C368
	ldr r1, _0225C9CC ; =0x00004FB3
	add r0, r4, #0
	bl FUN_0200C378
	ldr r1, _0225C9D0 ; =0x00004FA8
	add r0, r4, #0
	bl FUN_0200C388
	pop {r4, pc}
	.align 2, 0
_0225C9C4: .word 0x00004FB9
_0225C9C8: .word 0x00004E41
_0225C9CC: .word 0x00004FB3
_0225C9D0: .word 0x00004FA8

	thumb_func_start MOD11_0225C9D4
MOD11_0225C9D4: ; 0x0225C9D4
	push {r4, lr}
	mov r0, #5
	lsl r1, r0, #6
	bl AllocFromHeap
	mov r2, #5
	mov r1, #0
	lsl r2, r2, #6
	add r4, r0, #0
	bl MI_CpuFill8
	add r0, r4, #0
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD11_0225C9F0
MOD11_0225C9F0: ; 0x0225C9F0
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #4]
	cmp r0, #0
	beq _0225C9FE
	bl GF_AssertFail
_0225C9FE:
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}
	.align 2, 0

	thumb_func_start MOD11_0225CA08
MOD11_0225CA08: ; 0x0225CA08
	push {r4, r5, r6, r7, lr}
	sub sp, #0x24
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x38]
	str r3, [sp, #0x1c]
	str r0, [sp, #0x38]
	add r6, r1, #0
	str r2, [sp, #0x18]
	ldr r7, [sp, #0x3c]
	bl MOD11_0225C9D4
	ldr r2, [sp, #0x1c]
	ldr r3, [sp, #0x38]
	add r1, r6, #0
	str r0, [sp, #0x20]
	str r7, [sp]
	bl MOD11_0225CB10
	ldr r5, [sp, #0x20]
	mov r4, #0
	add r5, #0x1c
_0225CA32:
	ldr r0, [sp, #0x14]
	add r1, r6, #0
	ldrb r0, [r0, r4]
	bl MOD11_0225D374
	ldr r1, [sp, #0x1c]
	ldr r2, [sp, #0x20]
	str r1, [sp]
	str r4, [sp, #4]
	str r0, [sp, #8]
	ldr r0, [sp, #0x38]
	mov r1, #0x4f
	str r0, [sp, #0xc]
	lsl r1, r1, #2
	add r1, r2, r1
	ldr r3, [sp, #0x18]
	add r0, r5, #0
	add r2, r6, #0
	str r7, [sp, #0x10]
	bl MOD11_0225CDB0
	add r4, r4, #1
	add r5, #0x30
	cmp r4, #6
	blt _0225CA32
	ldr r0, [sp, #0x20]
	add sp, #0x24
	pop {r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD11_0225CA6C
MOD11_0225CA6C: ; 0x0225CA6C
	ldr r1, [r0, #4]
	cmp r1, #0
	bne _0225CA8A
	mov r2, #0
_0225CA74:
	ldr r1, [r0, #0x20]
	cmp r1, #0
	bne _0225CA82
	add r2, r2, #1
	add r0, #0x30
	cmp r2, #6
	blt _0225CA74
_0225CA82:
	cmp r2, #6
	bne _0225CA8A
	mov r0, #1
	bx lr
_0225CA8A:
	mov r0, #0
	bx lr
	.align 2, 0

	thumb_func_start MOD11_0225CA90
MOD11_0225CA90: ; 0x0225CA90
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	add r4, r1, #0
	add r7, r2, #0
	cmp r6, #0
	bne _0225CAA0
	bl GF_AssertFail
_0225CAA0:
	add r0, r6, #0
	add r1, r4, #0
	bl MOD11_0225CC68
	add r5, r6, #0
	mov r4, #0
	add r5, #0x1c
	add r6, #0x18
_0225CAB0:
	add r0, r5, #0
	add r1, r4, #0
	add r2, r7, #0
	add r3, r6, #0
	bl MOD11_0225D1A8
	add r4, r4, #1
	add r5, #0x30
	cmp r4, #6
	blt _0225CAB0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start MOD11_0225CAC8
MOD11_0225CAC8: ; 0x0225CAC8
	ldr r1, [r0, #4]
	cmp r1, #0
	bne _0225CAE6
	mov r2, #0
_0225CAD0:
	ldr r1, [r0, #0x20]
	cmp r1, #0
	bne _0225CADE
	add r2, r2, #1
	add r0, #0x30
	cmp r2, #6
	blt _0225CAD0
_0225CADE:
	cmp r2, #6
	bne _0225CAE6
	mov r0, #1
	bx lr
_0225CAE6:
	mov r0, #0
	bx lr
	.align 2, 0

	thumb_func_start MOD11_0225CAEC
MOD11_0225CAEC: ; 0x0225CAEC
	push {r4, r5, r6, lr}
	add r6, r0, #0
	ldr r0, [r6]
	bl FUN_0200C3DC
	mov r4, #0
	add r5, r6, #0
_0225CAFA:
	ldr r0, [r5, #0x1c]
	bl FUN_0200C3DC
	add r4, r4, #1
	add r5, #0x30
	cmp r4, #6
	blt _0225CAFA
	add r0, r6, #0
	bl MOD11_0225C9F0
	pop {r4, r5, r6, pc}

	thumb_func_start MOD11_0225CB10
MOD11_0225CB10: ; 0x0225CB10
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	ldr r0, [r5]
	add r6, r1, #0
	add r4, r2, #0
	add r7, r3, #0
	mov r1, #0
	cmp r0, #0
	bne _0225CB2A
	ldr r0, [r5, #4]
	cmp r0, #0
	bne _0225CB2A
	mov r1, #1
_0225CB2A:
	cmp r1, #0
	bne _0225CB32
	bl GF_AssertFail
_0225CB32:
	add r0, r5, #0
	mov r1, #0
	mov r2, #0x1c
	bl MI_CpuFill8
	ldr r1, [sp, #0x18]
	ldr r2, _0225CBA8 ; =MOD11_0225FE48
	add r0, r7, #0
	bl FUN_0200C154
	str r0, [r5]
	cmp r6, #0
	ldr r0, [r5]
	bne _0225CB68
	ldr r2, _0225CBAC ; =MOD11_0225FE38
	lsl r3, r4, #1
	ldrsh r2, [r2, r3]
	mov r1, #0x16
	lsl r1, r1, #4
	bl FUN_0200C714
	ldr r0, [r5]
	mov r1, #8
	ldr r0, [r0]
	bl FUN_02020130
	b _0225CB80
_0225CB68:
	ldr r2, _0225CBB0 ; =MOD11_0225FE30
	lsl r3, r4, #1
	ldrsh r2, [r2, r3]
	mov r1, #0x5f
	mvn r1, r1
	bl FUN_0200C714
	ldr r0, [r5]
	mov r1, #7
	ldr r0, [r0]
	bl FUN_02020130
_0225CB80:
	ldr r0, [r5]
	ldr r0, [r0]
	bl FUN_0200C59C
	str r6, [r5, #0xc]
	mov r2, #0x7d
	str r4, [r5, #0x10]
	mov r0, #0
	strb r0, [r5, #0x1a]
	ldr r0, _0225CBB4 ; =MOD11_0225CBBC
	add r1, r5, #0
	lsl r2, r2, #2
	bl FUN_0200CA44
	str r0, [r5, #4]
	ldr r0, _0225CBB8 ; =0x00000711
	bl PlaySE
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0225CBA8: .word MOD11_0225FE48
_0225CBAC: .word MOD11_0225FE38
_0225CBB0: .word MOD11_0225FE30
_0225CBB4: .word MOD11_0225CBBC
_0225CBB8: .word 0x00000711

	thumb_func_start MOD11_0225CBBC
MOD11_0225CBBC: ; 0x0225CBBC
	push {r3, r4, lr}
	sub sp, #4
	add r4, r1, #0
	ldrb r1, [r4, #0x1a]
	cmp r1, #0
	beq _0225CBCE
	cmp r1, #1
	beq _0225CBEA
	b _0225CC52
_0225CBCE:
	add r1, sp, #0
	ldr r0, [r4]
	add r1, #2
	add r2, sp, #0
	bl FUN_0200C7A0
	add r1, sp, #0
	mov r0, #2
	ldrsh r0, [r1, r0]
	lsl r0, r0, #8
	str r0, [r4, #0x14]
	ldrb r0, [r4, #0x1a]
	add r0, r0, #1
	strb r0, [r4, #0x1a]
_0225CBEA:
	ldr r0, [r4, #0xc]
	ldr r1, [r4, #0x14]
	cmp r0, #0
	bne _0225CC22
	mov r0, #0xe
	lsl r0, r0, #8
	sub r2, r1, r0
	lsl r1, r0, #4
	str r2, [r4, #0x14]
	cmp r2, r1
	bgt _0225CC0A
	lsl r0, r0, #4
	str r0, [r4, #0x14]
	ldrb r0, [r4, #0x1a]
	add r0, r0, #1
	strb r0, [r4, #0x1a]
_0225CC0A:
	ldr r2, [r4, #0x10]
	ldr r1, [r4, #0x14]
	lsl r3, r2, #1
	ldr r2, _0225CC60 ; =MOD11_0225FE38
	lsl r1, r1, #8
	ldrsh r2, [r2, r3]
	ldr r0, [r4]
	asr r1, r1, #0x10
	bl FUN_0200C714
	add sp, #4
	pop {r3, r4, pc}
_0225CC22:
	mov r0, #0xe
	lsl r0, r0, #8
	add r1, r1, r0
	mov r0, #2
	lsl r0, r0, #0xc
	str r1, [r4, #0x14]
	cmp r1, r0
	blt _0225CC3A
	str r0, [r4, #0x14]
	ldrb r0, [r4, #0x1a]
	add r0, r0, #1
	strb r0, [r4, #0x1a]
_0225CC3A:
	ldr r2, [r4, #0x10]
	ldr r1, [r4, #0x14]
	lsl r3, r2, #1
	ldr r2, _0225CC64 ; =MOD11_0225FE30
	lsl r1, r1, #8
	ldrsh r2, [r2, r3]
	ldr r0, [r4]
	asr r1, r1, #0x10
	bl FUN_0200C714
	add sp, #4
	pop {r3, r4, pc}
_0225CC52:
	bl FUN_0200CAB4
	mov r0, #0
	str r0, [r4, #4]
	add sp, #4
	pop {r3, r4, pc}
	nop
_0225CC60: .word MOD11_0225FE38
_0225CC64: .word MOD11_0225FE30

	thumb_func_start MOD11_0225CC68
MOD11_0225CC68: ; 0x0225CC68
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5]
	add r4, r1, #0
	cmp r0, #0
	beq _0225CC7A
	ldr r0, [r5, #4]
	cmp r0, #0
	beq _0225CC7E
_0225CC7A:
	bl GF_AssertFail
_0225CC7E:
	mov r0, #0
	strb r0, [r5, #0x1a]
	str r4, [r5, #8]
	cmp r4, #0
	bne _0225CC8C
	mov r0, #4
	b _0225CC8C
_0225CC8C:
	strb r0, [r5, #0x1b]
	mov r2, #0x7d
	ldr r0, _0225CCA0 ; =MOD11_0225CCA4
	add r1, r5, #0
	lsl r2, r2, #2
	bl FUN_0200CA44
	str r0, [r5, #4]
	pop {r3, r4, r5, pc}
	nop
_0225CCA0: .word MOD11_0225CCA4

	thumb_func_start MOD11_0225CCA4
MOD11_0225CCA4: ; 0x0225CCA4
	push {r3, r4, r5, lr}
	sub sp, #8
	add r4, r1, #0
	add r5, r0, #0
	ldrb r0, [r4, #0x1a]
	cmp r0, #0
	beq _0225CCBC
	cmp r0, #1
	beq _0225CCFC
	cmp r0, #2
	beq _0225CD10
	b _0225CD8E
_0225CCBC:
	add r1, sp, #4
	ldr r0, [r4]
	add r1, #2
	add r2, sp, #4
	bl FUN_0200C7A0
	add r1, sp, #4
	mov r0, #2
	ldrsh r0, [r1, r0]
	mov r1, #1
	lsl r0, r0, #8
	str r0, [r4, #0x14]
	ldr r0, [r4]
	bl FUN_0200C90C
	mov r0, #1
	lsl r0, r0, #0xc
	strh r0, [r4, #0x18]
	mov r0, #0x18
	ldrsh r0, [r4, r0]
	mov r1, #0
	mov r2, #0x3f
	asr r3, r0, #8
	mov r0, #0x10
	sub r0, r0, r3
	str r0, [sp]
	ldr r0, _0225CDA0 ; =0x04000050
	bl G2x_SetBlendAlpha_
	ldrb r0, [r4, #0x1a]
	add r0, r0, #1
	strb r0, [r4, #0x1a]
_0225CCFC:
	ldrb r0, [r4, #0x1b]
	cmp r0, #0
	beq _0225CD0A
	sub r0, r0, #1
	add sp, #8
	strb r0, [r4, #0x1b]
	pop {r3, r4, r5, pc}
_0225CD0A:
	ldrb r0, [r4, #0x1a]
	add r0, r0, #1
	strb r0, [r4, #0x1a]
_0225CD10:
	ldr r0, [r4, #8]
	cmp r0, #0
	bne _0225CD54
	ldr r0, [r4, #0xc]
	ldr r1, [r4, #0x14]
	cmp r0, #0
	bne _0225CD3A
	mov r0, #1
	lsl r0, r0, #0xa
	sub r1, r1, r0
	str r1, [r4, #0x14]
	ldr r2, [r4, #0x10]
	lsl r1, r1, #8
	lsl r3, r2, #1
	ldr r2, _0225CDA4 ; =MOD11_0225FE38
	ldr r0, [r4]
	ldrsh r2, [r2, r3]
	asr r1, r1, #0x10
	bl FUN_0200C714
	b _0225CD54
_0225CD3A:
	mov r0, #1
	lsl r0, r0, #0xa
	add r1, r1, r0
	str r1, [r4, #0x14]
	ldr r2, [r4, #0x10]
	lsl r1, r1, #8
	lsl r3, r2, #1
	ldr r2, _0225CDA8 ; =MOD11_0225FE30
	ldr r0, [r4]
	ldrsh r2, [r2, r3]
	asr r1, r1, #0x10
	bl FUN_0200C714
_0225CD54:
	mov r1, #0x18
	ldrsh r2, [r4, r1]
	add r0, r1, #0
	add r0, #0xe8
	sub r0, r2, r0
	strh r0, [r4, #0x18]
	ldrsh r0, [r4, r1]
	cmp r0, #0
	bgt _0225CD78
	mov r1, #0
	strh r1, [r4, #0x18]
	ldr r0, [r4]
	ldr r0, [r0]
	bl FUN_0200C63C
	ldrb r0, [r4, #0x1a]
	add r0, r0, #1
	strb r0, [r4, #0x1a]
_0225CD78:
	mov r0, #0x18
	ldrsh r0, [r4, r0]
	add sp, #8
	asr r1, r0, #8
	mov r0, #0x10
	sub r0, r0, r1
	lsl r0, r0, #8
	orr r1, r0
	ldr r0, _0225CDAC ; =0x04000052
	strh r1, [r0]
	pop {r3, r4, r5, pc}
_0225CD8E:
	bl MOD11_02231678
	add r0, r5, #0
	bl FUN_0200CAB4
	mov r0, #0
	str r0, [r4, #4]
	add sp, #8
	pop {r3, r4, r5, pc}
	.align 2, 0
_0225CDA0: .word 0x04000050
_0225CDA4: .word MOD11_0225FE38
_0225CDA8: .word MOD11_0225FE30
_0225CDAC: .word 0x04000052

	thumb_func_start MOD11_0225CDB0
MOD11_0225CDB0: ; 0x0225CDB0
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	ldr r0, [r5]
	add r7, r1, #0
	add r6, r2, #0
	mov r1, #0
	str r3, [sp]
	ldr r4, [sp, #0x1c]
	cmp r0, #0
	bne _0225CDCC
	ldr r0, [r5, #4]
	cmp r0, #0
	bne _0225CDCC
	mov r1, #1
_0225CDCC:
	cmp r1, #0
	bne _0225CDD4
	bl GF_AssertFail
_0225CDD4:
	add r0, r5, #0
	mov r1, #0
	mov r2, #0x30
	bl MI_CpuFill8
	ldr r0, [sp, #0x24]
	ldr r1, [sp, #0x28]
	ldr r2, _0225CEA4 ; =MOD11_0225FE7C
	bl FUN_0200C154
	str r0, [r5]
	cmp r6, #0
	ldr r0, [r5]
	bne _0225CE02
	ldr r2, [sp, #0x18]
	mov r1, #0x45
	lsl r3, r2, #1
	ldr r2, _0225CEA8 ; =MOD11_0225FE40
	lsl r1, r1, #2
	ldrsh r2, [r2, r3]
	bl FUN_0200C714
	b _0225CE12
_0225CE02:
	ldr r2, [sp, #0x18]
	mov r1, #0x13
	lsl r3, r2, #1
	ldr r2, _0225CEAC ; =MOD11_0225FE28
	mvn r1, r1
	ldrsh r2, [r2, r3]
	bl FUN_0200C714
_0225CE12:
	ldr r0, [r5]
	ldr r1, [sp, #0x20]
	ldr r0, [r0]
	bl FUN_02020130
	ldr r0, [r5]
	ldr r0, [r0]
	bl FUN_0200C59C
	add r0, r5, #0
	str r6, [r5, #8]
	add r0, #0x2d
	strb r4, [r0]
	ldr r0, [sp, #0x18]
	str r0, [r5, #0xc]
	ldr r0, [sp, #0x20]
	bl MOD11_0225D3B4
	add r1, r5, #0
	add r1, #0x2e
	strb r0, [r1]
	ldr r0, [sp, #0x20]
	str r7, [r5, #0x14]
	cmp r0, #6
	bne _0225CE48
	ldr r0, _0225CEB0 ; =0x00000713
	b _0225CE4A
_0225CE48:
	ldr r0, _0225CEB4 ; =0x00000712
_0225CE4A:
	strh r0, [r5, #0x2a]
	cmp r6, #0
	bne _0225CE5E
	lsl r0, r4, #4
	add r0, #0xa2
	str r0, [r5, #0x20]
	mov r0, #0xf
	mul r0, r4
	add r0, #0x9c
	b _0225CE70
_0225CE5E:
	lsl r1, r4, #4
	mov r0, #0x5e
	sub r0, r0, r1
	str r0, [r5, #0x20]
	mov r0, #0xf
	add r1, r4, #0
	mul r1, r0
	mov r0, #0x64
	sub r0, r0, r1
_0225CE70:
	str r0, [r5, #0x24]
	add r0, r5, #0
	mov r1, #0
	add r0, #0x2c
	strb r1, [r0]
	ldr r0, [sp]
	ldr r2, _0225CEB8 ; =0x000001F5
	cmp r0, #0
	bne _0225CE96
	lsl r0, r4, #1
	add r0, r4, r0
	add r0, r0, #5
	strh r0, [r5, #0x28]
	ldr r0, _0225CEBC ; =MOD11_0225CEC4
	add r1, r5, #0
	bl FUN_0200CA44
	str r0, [r5, #4]
	pop {r3, r4, r5, r6, r7, pc}
_0225CE96:
	ldr r0, _0225CEC0 ; =MOD11_0225D0C4
	strh r1, [r5, #0x28]
	add r1, r5, #0
	bl FUN_0200CA44
	str r0, [r5, #4]
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0225CEA4: .word MOD11_0225FE7C
_0225CEA8: .word MOD11_0225FE40
_0225CEAC: .word MOD11_0225FE28
_0225CEB0: .word 0x00000713
_0225CEB4: .word 0x00000712
_0225CEB8: .word 0x000001F5
_0225CEBC: .word MOD11_0225CEC4
_0225CEC0: .word MOD11_0225D0C4

	thumb_func_start MOD11_0225CEC4
MOD11_0225CEC4: ; 0x0225CEC4
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	add r0, #0x2c
	ldrb r0, [r0]
	cmp r0, #6
	bls _0225CED6
	b _0225D0A6
_0225CED6:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0225CEE2: ; jump table
	.short _0225CEF0 - _0225CEE2 - 2 ; case 0
	.short _0225CF14 - _0225CEE2 - 2 ; case 1
	.short _0225CF22 - _0225CEE2 - 2 ; case 2
	.short _0225CFA4 - _0225CEE2 - 2 ; case 3
	.short _0225CFBC - _0225CEE2 - 2 ; case 4
	.short _0225CFFC - _0225CEE2 - 2 ; case 5
	.short _0225D02A - _0225CEE2 - 2 ; case 6
_0225CEF0:
	add r1, sp, #0
	ldr r0, [r4]
	add r1, #2
	add r2, sp, #0
	bl FUN_0200C7A0
	add r1, sp, #0
	mov r0, #2
	ldrsh r0, [r1, r0]
	lsl r0, r0, #8
	str r0, [r4, #0x1c]
	add r0, r4, #0
	add r0, #0x2c
	ldrb r0, [r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0x2c
	strb r1, [r0]
_0225CF14:
	mov r0, #0x28
	ldrsh r0, [r4, r0]
	cmp r0, #0
	ble _0225CF22
	sub r0, r0, #1
	strh r0, [r4, #0x28]
	pop {r3, r4, r5, pc}
_0225CF22:
	ldr r0, [r4, #8]
	ldr r1, [r4, #0x1c]
	cmp r0, #0
	bne _0225CF66
	mov r0, #0xe
	lsl r0, r0, #8
	sub r1, r1, r0
	str r1, [r4, #0x1c]
	ldr r0, [r4, #0x24]
	lsl r0, r0, #8
	cmp r1, r0
	bgt _0225CF50
	str r0, [r4, #0x1c]
	ldrh r0, [r4, #0x2a]
	bl PlaySE
	add r0, r4, #0
	add r0, #0x2c
	ldrb r0, [r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0x2c
	strb r1, [r0]
_0225CF50:
	ldr r2, [r4, #0xc]
	ldr r1, [r4, #0x1c]
	lsl r3, r2, #1
	ldr r2, _0225D0BC ; =MOD11_0225FE40
	lsl r1, r1, #8
	ldrsh r2, [r2, r3]
	ldr r0, [r4]
	asr r1, r1, #0x10
	bl FUN_0200C714
	b _0225CF9A
_0225CF66:
	mov r0, #0xe
	lsl r0, r0, #8
	add r1, r1, r0
	str r1, [r4, #0x1c]
	ldr r0, [r4, #0x24]
	lsl r0, r0, #8
	cmp r1, r0
	blt _0225CF86
	str r0, [r4, #0x1c]
	add r0, r4, #0
	add r0, #0x2c
	ldrb r0, [r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0x2c
	strb r1, [r0]
_0225CF86:
	ldr r2, [r4, #0xc]
	ldr r1, [r4, #0x1c]
	lsl r3, r2, #1
	ldr r2, _0225D0C0 ; =MOD11_0225FE28
	lsl r1, r1, #8
	ldrsh r2, [r2, r3]
	ldr r0, [r4]
	asr r1, r1, #0x10
	bl FUN_0200C714
_0225CF9A:
	ldr r0, [r4]
	ldr r0, [r0]
	bl FUN_0200C59C
	pop {r3, r4, r5, pc}
_0225CFA4:
	ldr r1, [r4, #0x14]
	mov r0, #0
	ldrsb r0, [r1, r0]
	add r0, r0, #1
	strb r0, [r1]
	add r0, r4, #0
	add r0, #0x2c
	ldrb r0, [r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0x2c
	strb r1, [r0]
_0225CFBC:
	ldr r1, [r4, #0x14]
	mov r0, #0
	ldrsb r0, [r1, r0]
	cmp r0, #6
	beq _0225CFD0
	ldr r0, [r4]
	ldr r0, [r0]
	bl FUN_0200C59C
	pop {r3, r4, r5, pc}
_0225CFD0:
	ldr r0, [r4, #8]
	cmp r0, #0
	ldr r0, [r4]
	bne _0225CFE2
	ldr r0, [r0]
	mov r1, #1
	bl FUN_02020208
	b _0225CFEA
_0225CFE2:
	ldr r0, [r0]
	mov r1, #1
	bl FUN_02020208
_0225CFEA:
	mov r0, #0
	strh r0, [r4, #0x28]
	add r0, r4, #0
	add r0, #0x2c
	ldrb r0, [r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0x2c
	strb r1, [r0]
_0225CFFC:
	mov r0, #0x28
	ldrsh r1, [r4, r0]
	add r1, r1, #1
	strh r1, [r4, #0x28]
	ldrsh r0, [r4, r0]
	cmp r0, #0
	blt _0225D0BA
	add r1, r4, #0
	ldr r0, [r4]
	add r1, #0x2e
	ldrb r1, [r1]
	ldr r0, [r0]
	bl FUN_02020130
	mov r0, #0
	strh r0, [r4, #0x28]
	add r0, r4, #0
	add r0, #0x2c
	ldrb r0, [r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0x2c
	strb r1, [r0]
_0225D02A:
	ldr r0, [r4, #8]
	ldr r1, [r4, #0x1c]
	cmp r0, #0
	bne _0225D068
	mov r0, #6
	lsl r0, r0, #8
	add r1, r1, r0
	str r1, [r4, #0x1c]
	ldr r0, [r4, #0x20]
	lsl r0, r0, #8
	cmp r1, r0
	blt _0225D052
	str r0, [r4, #0x1c]
	add r0, r4, #0
	add r0, #0x2c
	ldrb r0, [r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0x2c
	strb r1, [r0]
_0225D052:
	ldr r2, [r4, #0xc]
	ldr r1, [r4, #0x1c]
	lsl r3, r2, #1
	ldr r2, _0225D0BC ; =MOD11_0225FE40
	lsl r1, r1, #8
	ldrsh r2, [r2, r3]
	ldr r0, [r4]
	asr r1, r1, #0x10
	bl FUN_0200C714
	b _0225D09C
_0225D068:
	mov r0, #6
	lsl r0, r0, #8
	sub r1, r1, r0
	str r1, [r4, #0x1c]
	ldr r0, [r4, #0x20]
	lsl r0, r0, #8
	cmp r1, r0
	bgt _0225D088
	str r0, [r4, #0x1c]
	add r0, r4, #0
	add r0, #0x2c
	ldrb r0, [r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0x2c
	strb r1, [r0]
_0225D088:
	ldr r2, [r4, #0xc]
	ldr r1, [r4, #0x1c]
	lsl r3, r2, #1
	ldr r2, _0225D0C0 ; =MOD11_0225FE28
	lsl r1, r1, #8
	ldrsh r2, [r2, r3]
	ldr r0, [r4]
	asr r1, r1, #0x10
	bl FUN_0200C714
_0225D09C:
	ldr r0, [r4]
	ldr r0, [r0]
	bl FUN_0200C59C
	pop {r3, r4, r5, pc}
_0225D0A6:
	ldr r0, [r4]
	mov r1, #0
	ldr r0, [r0]
	bl FUN_02020208
	add r0, r5, #0
	bl FUN_0200CAB4
	mov r0, #0
	str r0, [r4, #4]
_0225D0BA:
	pop {r3, r4, r5, pc}
	.align 2, 0
_0225D0BC: .word MOD11_0225FE40
_0225D0C0: .word MOD11_0225FE28

	thumb_func_start MOD11_0225D0C4
MOD11_0225D0C4: ; 0x0225D0C4
	push {r3, r4, lr}
	sub sp, #4
	add r4, r1, #0
	add r1, #0x2c
	ldrb r1, [r1]
	cmp r1, #0
	beq _0225D0DC
	cmp r1, #1
	beq _0225D10A
	cmp r1, #2
	beq _0225D11A
	b _0225D192
_0225D0DC:
	add r1, sp, #0
	ldr r0, [r4]
	add r1, #2
	add r2, sp, #0
	bl FUN_0200C7A0
	add r1, sp, #0
	mov r0, #2
	ldrsh r0, [r1, r0]
	mov r1, #0
	lsl r0, r0, #8
	str r0, [r4, #0x1c]
	ldr r0, [r4]
	ldr r0, [r0]
	bl FUN_02020208
	add r0, r4, #0
	add r0, #0x2c
	ldrb r0, [r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0x2c
	strb r1, [r0]
_0225D10A:
	mov r0, #0x28
	ldrsh r0, [r4, r0]
	cmp r0, #0
	ble _0225D11A
	sub r0, r0, #1
	add sp, #4
	strh r0, [r4, #0x28]
	pop {r3, r4, pc}
_0225D11A:
	ldr r0, [r4, #8]
	ldr r1, [r4, #0x1c]
	cmp r0, #0
	bne _0225D15A
	mov r0, #0xe
	lsl r0, r0, #8
	sub r1, r1, r0
	str r1, [r4, #0x1c]
	ldr r0, [r4, #0x20]
	lsl r0, r0, #8
	cmp r1, r0
	bgt _0225D142
	str r0, [r4, #0x1c]
	add r0, r4, #0
	add r0, #0x2c
	ldrb r0, [r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0x2c
	strb r1, [r0]
_0225D142:
	ldr r2, [r4, #0xc]
	ldr r1, [r4, #0x1c]
	lsl r3, r2, #1
	ldr r2, _0225D1A0 ; =MOD11_0225FE40
	lsl r1, r1, #8
	ldrsh r2, [r2, r3]
	ldr r0, [r4]
	asr r1, r1, #0x10
	bl FUN_0200C714
	add sp, #4
	pop {r3, r4, pc}
_0225D15A:
	mov r0, #0xe
	lsl r0, r0, #8
	add r1, r1, r0
	str r1, [r4, #0x1c]
	ldr r0, [r4, #0x20]
	lsl r0, r0, #8
	cmp r1, r0
	blt _0225D17A
	str r0, [r4, #0x1c]
	add r0, r4, #0
	add r0, #0x2c
	ldrb r0, [r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0x2c
	strb r1, [r0]
_0225D17A:
	ldr r2, [r4, #0xc]
	ldr r1, [r4, #0x1c]
	lsl r3, r2, #1
	ldr r2, _0225D1A4 ; =MOD11_0225FE28
	lsl r1, r1, #8
	ldrsh r2, [r2, r3]
	ldr r0, [r4]
	asr r1, r1, #0x10
	bl FUN_0200C714
	add sp, #4
	pop {r3, r4, pc}
_0225D192:
	bl FUN_0200CAB4
	mov r0, #0
	str r0, [r4, #4]
	add sp, #4
	pop {r3, r4, pc}
	nop
_0225D1A0: .word MOD11_0225FE40
_0225D1A4: .word MOD11_0225FE28

	thumb_func_start MOD11_0225D1A8
MOD11_0225D1A8: ; 0x0225D1A8
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	ldr r0, [r5]
	add r6, r1, #0
	add r7, r2, #0
	add r4, r3, #0
	cmp r0, #0
	beq _0225D1BE
	ldr r0, [r5, #4]
	cmp r0, #0
	beq _0225D1C2
_0225D1BE:
	bl GF_AssertFail
_0225D1C2:
	add r0, r5, #0
	mov r1, #0
	add r0, #0x2c
	strb r1, [r0]
	cmp r7, #0
	str r4, [r5, #0x18]
	ldr r2, _0225D200 ; =0x000001F5
	bne _0225D1EC
	lsl r0, r6, #1
	add r0, r6, r0
	strh r0, [r5, #0x28]
	add r0, r5, #0
	mov r1, #4
	add r0, #0x2f
	strb r1, [r0]
	ldr r0, _0225D204 ; =MOD11_0225D20C
	add r1, r5, #0
	bl FUN_0200CA44
	str r0, [r5, #4]
	pop {r3, r4, r5, r6, r7, pc}
_0225D1EC:
	add r0, r5, #0
	strh r1, [r5, #0x28]
	add r0, #0x2f
	strb r1, [r0]
	ldr r0, _0225D208 ; =MOD11_0225D31C
	add r1, r5, #0
	bl FUN_0200CA44
	str r0, [r5, #4]
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_0225D200: .word 0x000001F5
_0225D204: .word MOD11_0225D20C
_0225D208: .word MOD11_0225D31C

	thumb_func_start MOD11_0225D20C
MOD11_0225D20C: ; 0x0225D20C
	push {r3, r4, r5, lr}
	add r4, r1, #0
	ldr r1, [r4, #0x18]
	add r5, r0, #0
	mov r0, #0
	ldrsh r0, [r1, r0]
	cmp r0, #0
	bne _0225D224
	add r0, r4, #0
	mov r1, #0x64
	add r0, #0x2c
	strb r1, [r0]
_0225D224:
	add r0, r4, #0
	add r0, #0x2c
	ldrb r0, [r0]
	cmp r0, #2
	bgt _0225D23E
	cmp r0, #0
	blt _0225D2FA
	beq _0225D242
	cmp r0, #1
	beq _0225D26E
	cmp r0, #2
	beq _0225D294
	b _0225D2FA
_0225D23E:
	cmp r0, #0x64
	b _0225D2FA
_0225D242:
	add r1, sp, #0
	ldr r0, [r4]
	add r1, #2
	add r2, sp, #0
	bl FUN_0200C7A0
	add r1, sp, #0
	mov r0, #2
	ldrsh r0, [r1, r0]
	mov r1, #1
	lsl r0, r0, #8
	str r0, [r4, #0x1c]
	ldr r0, [r4]
	bl FUN_0200C90C
	add r0, r4, #0
	add r0, #0x2c
	ldrb r0, [r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0x2c
	strb r1, [r0]
_0225D26E:
	add r0, r4, #0
	add r0, #0x2f
	ldrb r0, [r0]
	cmp r0, #0
	beq _0225D286
	add r0, r4, #0
	add r0, #0x2f
	ldrb r0, [r0]
	add r4, #0x2f
	sub r0, r0, #1
	strb r0, [r4]
	pop {r3, r4, r5, pc}
_0225D286:
	mov r0, #0x28
	ldrsh r0, [r4, r0]
	cmp r0, #0
	ble _0225D294
	sub r0, r0, #1
	strh r0, [r4, #0x28]
	pop {r3, r4, r5, pc}
_0225D294:
	ldr r0, [r4, #8]
	ldr r1, [r4, #0x1c]
	cmp r0, #0
	bne _0225D2B8
	mov r0, #3
	lsl r0, r0, #0xa
	sub r1, r1, r0
	str r1, [r4, #0x1c]
	ldr r2, [r4, #0xc]
	lsl r1, r1, #8
	lsl r3, r2, #1
	ldr r2, _0225D310 ; =MOD11_0225FE40
	ldr r0, [r4]
	ldrsh r2, [r2, r3]
	asr r1, r1, #0x10
	bl FUN_0200C714
	b _0225D2D2
_0225D2B8:
	mov r0, #3
	lsl r0, r0, #0xa
	add r1, r1, r0
	str r1, [r4, #0x1c]
	ldr r2, [r4, #0xc]
	lsl r1, r1, #8
	lsl r3, r2, #1
	ldr r2, _0225D314 ; =MOD11_0225FE28
	ldr r0, [r4]
	ldrsh r2, [r2, r3]
	asr r1, r1, #0x10
	bl FUN_0200C714
_0225D2D2:
	ldr r1, [r4, #0x1c]
	ldr r0, _0225D318 ; =0xFFFFF000
	cmp r1, r0
	blt _0225D2E2
	mov r0, #0x11
	lsl r0, r0, #0xc
	cmp r1, r0
	ble _0225D2F0
_0225D2E2:
	add r0, r4, #0
	add r0, #0x2c
	ldrb r0, [r0]
	add r1, r0, #1
	add r0, r4, #0
	add r0, #0x2c
	strb r1, [r0]
_0225D2F0:
	ldr r0, [r4]
	ldr r0, [r0]
	bl FUN_0200C59C
	pop {r3, r4, r5, pc}
_0225D2FA:
	ldr r0, [r4]
	mov r1, #0
	ldr r0, [r0]
	bl FUN_0200C63C
	add r0, r5, #0
	bl FUN_0200CAB4
	mov r0, #0
	str r0, [r4, #4]
	pop {r3, r4, r5, pc}
	.align 2, 0
_0225D310: .word MOD11_0225FE40
_0225D314: .word MOD11_0225FE28
_0225D318: .word 0xFFFFF000

	thumb_func_start MOD11_0225D31C
MOD11_0225D31C: ; 0x0225D31C
	push {r3, r4, r5, lr}
	add r4, r1, #0
	ldr r1, [r4, #0x18]
	add r5, r0, #0
	mov r0, #0
	ldrsh r0, [r1, r0]
	cmp r0, #0
	bne _0225D334
	add r0, r4, #0
	mov r1, #0x64
	add r0, #0x2c
	strb r1, [r0]
_0225D334:
	add r0, r4, #0
	add r0, #0x2c
	ldrb r0, [r0]
	cmp r0, #0
	beq _0225D346
	cmp r0, #1
	beq _0225D370
	cmp r0, #0x64
	b _0225D35C
_0225D346:
	ldr r0, [r4]
	mov r1, #1
	bl FUN_0200C90C
	add r0, r4, #0
	add r0, #0x2c
	ldrb r0, [r0]
	add r4, #0x2c
	add r0, r0, #1
	strb r0, [r4]
	pop {r3, r4, r5, pc}
_0225D35C:
	ldr r0, [r4]
	mov r1, #0
	ldr r0, [r0]
	bl FUN_0200C63C
	add r0, r5, #0
	bl FUN_0200CAB4
	mov r0, #0
	str r0, [r4, #4]
_0225D370:
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start MOD11_0225D374
MOD11_0225D374: ; 0x0225D374
	cmp r0, #3
	bhi _0225D38C
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0225D384: ; jump table
	.short _0225D38C - _0225D384 - 2 ; case 0
	.short _0225D390 - _0225D384 - 2 ; case 1
	.short _0225D39C - _0225D384 - 2 ; case 2
	.short _0225D3A8 - _0225D384 - 2 ; case 3
_0225D38C:
	mov r0, #6
	bx lr
_0225D390:
	cmp r1, #0
	bne _0225D398
	mov r0, #3
	bx lr
_0225D398:
	mov r0, #0
	bx lr
_0225D39C:
	cmp r1, #0
	bne _0225D3A4
	mov r0, #5
	bx lr
_0225D3A4:
	mov r0, #2
	bx lr
_0225D3A8:
	cmp r1, #0
	bne _0225D3B0
	mov r0, #4
	bx lr
_0225D3B0:
	mov r0, #1
	bx lr

	thumb_func_start MOD11_0225D3B4
MOD11_0225D3B4: ; 0x0225D3B4
	cmp r0, #6
	bhi _0225D3EA
	add r1, r0, r0
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_0225D3C4: ; jump table
	.short _0225D3D8 - _0225D3C4 - 2 ; case 0
	.short _0225D3E8 - _0225D3C4 - 2 ; case 1
	.short _0225D3E0 - _0225D3C4 - 2 ; case 2
	.short _0225D3D4 - _0225D3C4 - 2 ; case 3
	.short _0225D3E4 - _0225D3C4 - 2 ; case 4
	.short _0225D3DC - _0225D3C4 - 2 ; case 5
	.short _0225D3D2 - _0225D3C4 - 2 ; case 6
_0225D3D2:
	bx lr
_0225D3D4:
	mov r0, #0
	bx lr
_0225D3D8:
	mov r0, #3
	bx lr
_0225D3DC:
	mov r0, #2
	bx lr
_0225D3E0:
	mov r0, #5
	bx lr
_0225D3E4:
	mov r0, #1
	bx lr
_0225D3E8:
	mov r0, #4
_0225D3EA:
	bx lr

	.section .rodata

	.global MOD11_0225FE28
MOD11_0225FE28: ; 0x0225FE28
	.byte 0x0E, 0x00, 0x32, 0x00, 0x32, 0x00, 0x00, 0x00

	.global MOD11_0225FE30
MOD11_0225FE30: ; 0x0225FE30
	.byte 0x14, 0x00, 0x38, 0x00, 0x38, 0x00, 0x00, 0x00

	.global MOD11_0225FE38
MOD11_0225FE38: ; 0x0225FE38
	.byte 0x5C, 0x00, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00

	.global MOD11_0225FE40
MOD11_0225FE40: ; 0x0225FE40
	.byte 0x56, 0x00, 0x7A, 0x00, 0x7A, 0x00, 0x00, 0x00

	.global MOD11_0225FE48
MOD11_0225FE48: ; 0x0225FE48
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0xB9, 0x4F, 0x00, 0x00, 0x41, 0x4E, 0x00, 0x00, 0xB3, 0x4F, 0x00, 0x00
	.byte 0xA8, 0x4F, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00

	.global MOD11_0225FE7C
MOD11_0225FE7C: ; 0x0225FE7C
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0xB9, 0x4F, 0x00, 0x00, 0x41, 0x4E, 0x00, 0x00
	.byte 0xB3, 0x4F, 0x00, 0x00, 0xA8, 0x4F, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
