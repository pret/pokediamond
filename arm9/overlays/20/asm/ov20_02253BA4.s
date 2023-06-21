	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 2, 0

	thumb_func_start ov20_02253BA4
ov20_02253BA4: ; 0x02253BA4
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	add r7, r0, #0
	add r0, r5, #0
	mov r1, #0x1c
	mov r6, #0
	bl AllocFromHeap
	add r4, r0, #0
	beq _02253C0E
	add r0, r6, #0
	str r0, [r4, #0x14]
	str r0, [r4, #0xc]
	str r0, [r4, #4]
	str r7, [r4]
	str r5, [r4, #0x18]
	add r0, r7, #0
	bl NNS_G2dGetOamManagerOamCapacity
	strh r0, [r4, #0x10]
	ldrh r1, [r4, #0x10]
	add r0, r5, #0
	lsl r1, r1, #3
	bl AllocFromHeap
	str r0, [r4, #0x14]
	cmp r0, #0
	beq _02253C0E
	ldrh r2, [r4, #0x10]
	mov r1, #0x90
	add r0, r5, #0
	mul r1, r2
	bl AllocFromHeap
	str r0, [r4, #0xc]
	cmp r0, #0
	beq _02253C0E
	ldrh r1, [r4, #0x10]
	add r0, r5, #0
	lsl r1, r1, #2
	bl AllocFromHeap
	str r0, [r4, #4]
	cmp r0, #0
	beq _02253C0E
	ldrh r2, [r4, #0x10]
	ldr r1, [r4, #0xc]
	bl ov20_0225403C
	add r0, r6, #0
	strh r0, [r4, #0x12]
	str r0, [r4, #8]
	mov r6, #1
_02253C0E:
	cmp r6, #0
	bne _02253C46
	cmp r4, #0
	beq _02253C42
	ldr r1, [r4, #0x14]
	cmp r1, #0
	beq _02253C22
	add r0, r5, #0
	bl FreeToHeapExplicit
_02253C22:
	ldr r1, [r4, #0xc]
	cmp r1, #0
	beq _02253C2E
	add r0, r5, #0
	bl FreeToHeapExplicit
_02253C2E:
	ldr r1, [r4, #4]
	cmp r1, #0
	beq _02253C3A
	add r0, r5, #0
	bl FreeToHeapExplicit
_02253C3A:
	add r0, r5, #0
	add r1, r4, #0
	bl FreeToHeapExplicit
_02253C42:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_02253C46:
	add r0, r4, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end ov20_02253BA4

	thumb_func_start ov20_02253C4C
ov20_02253C4C: ; 0x02253C4C
	push {r4, lr}
	add r4, r0, #0
	beq _02253C76
	ldr r0, [r4, #0x14]
	cmp r0, #0
	beq _02253C5C
	bl FreeToHeap
_02253C5C:
	ldr r0, [r4, #0xc]
	cmp r0, #0
	beq _02253C66
	bl FreeToHeap
_02253C66:
	ldr r0, [r4, #4]
	cmp r0, #0
	beq _02253C70
	bl FreeToHeap
_02253C70:
	add r0, r4, #0
	bl FreeToHeap
_02253C76:
	pop {r4, pc}
	thumb_func_end ov20_02253C4C

	thumb_func_start ov20_02253C78
ov20_02253C78: ; 0x02253C78
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x20
	str r0, [sp, #0xc]
	ldrh r0, [r0, #0x12]
	cmp r0, #0
	bne _02253C86
	b _02253E52
_02253C86:
	ldr r0, [sp, #0xc]
	ldr r4, [r0, #8]
	ldr r5, [r0, #0x14]
	ldrh r0, [r0, #0x10]
	cmp r4, #0
	str r0, [sp, #0x10]
	bne _02253C96
	b _02253E38
_02253C96:
	add r0, r4, #0
	mov r1, #2
	add r0, #8
	lsl r1, r1, #0xc
	bl NNS_G2dTickCellAnimation
	add r0, r4, #0
	add r0, #0x86
	ldrb r0, [r0]
	cmp r0, #0
	beq _02253CAE
	b _02253E30
_02253CAE:
	add r6, r4, #0
	add r6, #0x40
	mov r0, #0xc
	ldrsh r0, [r6, r0]
	ldr r1, [r4, #0x64]
	lsl r0, r0, #0xc
	add r0, r1, r0
	str r0, [sp, #0x18]
	mov r0, #0xe
	ldrsh r0, [r6, r0]
	ldr r1, [r4, #0x68]
	lsl r0, r0, #0xc
	add r0, r1, r0
	str r0, [sp, #0x1c]
	add r0, r4, #0
	add r0, #0x87
	ldrb r0, [r0]
	cmp r0, #0
	bne _02253CEE
	add r0, sp, #0x18
	str r0, [sp]
	mov r3, #0
	str r3, [sp, #4]
	ldr r1, [sp, #0x10]
	str r3, [sp, #8]
	lsl r1, r1, #0x10
	ldr r2, [r4, #0x34]
	add r0, r5, #0
	lsr r1, r1, #0x10
	bl NNS_G2dMakeCellToOams
	b _02253D86
_02253CEE:
	ldr r0, [r4, #0x6c]
	bl MTX_Identity22_
	ldrh r1, [r6, #0x12]
	mov r0, #4
	tst r0, r1
	beq _02253D20
	add r0, r4, #0
	add r0, #0x8c
	ldrh r2, [r6, #0x10]
	ldrh r0, [r0]
	ldr r1, _02253E58 ; =FX_SinCosTable_
	add r0, r2, r0
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	asr r0, r0, #4
	lsl r3, r0, #2
	add r2, r1, r3
	ldrsh r1, [r1, r3]
	mov r3, #2
	ldrsh r2, [r2, r3]
	ldr r0, [r4, #0x6c]
	bl MTX_Rot22_
	b _02253D3E
_02253D20:
	add r0, r4, #0
	add r0, #0x8c
	ldrh r0, [r0]
	cmp r0, #0
	beq _02253D3E
	asr r0, r0, #4
	lsl r3, r0, #2
	ldr r1, _02253E58 ; =FX_SinCosTable_
	ldr r0, [r4, #0x6c]
	add r2, r1, r3
	ldrsh r1, [r1, r3]
	mov r3, #2
	ldrsh r2, [r2, r3]
	bl MTX_Rot22_
_02253D3E:
	ldrh r1, [r6, #0x12]
	mov r0, #2
	tst r0, r1
	beq _02253D62
	ldr r0, [r6, #4]
	ldr r7, [r4, #0x6c]
	bl FX_Inv
	str r0, [sp, #0x14]
	ldr r0, [r6, #8]
	bl FX_Inv
	add r3, r0, #0
	ldr r2, [sp, #0x14]
	add r0, r7, #0
	add r1, r7, #0
	bl MTX_ScaleApply22
_02253D62:
	ldr r0, [sp, #0xc]
	ldr r1, [r4, #0x6c]
	ldr r0, [r0]
	bl NNS_G2dEntryOamManagerAffine
	add r1, sp, #0x18
	str r1, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	ldr r1, [sp, #0x10]
	ldr r2, [r4, #0x34]
	lsl r1, r1, #0x10
	ldr r3, [r4, #0x6c]
	add r0, r5, #0
	lsr r1, r1, #0x10
	bl NNS_G2dMakeCellToOams
_02253D86:
	ldr r1, [sp, #0x10]
	sub r1, r1, r0
	str r1, [sp, #0x10]
	add r1, r0, #0
	sub r0, r0, #1
	cmp r1, #0
	beq _02253E30
	ldr r7, _02253E5C ; =0xDFFFFFFF
	asr r1, r7, #0x11
_02253D98:
	ldr r3, [r5, #4]
	ldr r2, _02253E60 ; =0xFFFFF3FF
	add r6, r4, #0
	and r2, r3
	add r3, r4, #0
	add r3, #0x82
	ldrh r3, [r3]
	add r6, #0x84
	lsl r3, r3, #0x1e
	lsr r3, r3, #0x14
	orr r2, r3
	str r2, [r5, #4]
	ldr r3, _02253E64 ; =0xFFFF0FFF
	ldrh r6, [r6]
	and r3, r2
	lsl r2, r2, #0x10
	lsr r2, r2, #0x1c
	add r2, r2, r6
	lsl r2, r2, #0x1c
	lsr r2, r2, #0x10
	orr r2, r3
	add r6, r4, #0
	ldr r3, _02253E68 ; =0xFFFFFC00
	str r2, [r5, #4]
	add r6, #0x88
	and r3, r2
	lsl r2, r2, #0x16
	ldrh r6, [r6]
	lsr r2, r2, #0x16
	add r6, r2, r6
	ldr r2, _02253E6C ; =0x000003FF
	and r2, r6
	orr r2, r3
	add r6, r4, #0
	str r2, [r5, #4]
	add r6, #0x8a
	ldr r2, [r5]
	ldr r3, _02253E70 ; =0xEFFFFFFF
	ldrb r6, [r6]
	and r3, r2
	lsl r2, r2, #3
	lsr r2, r2, #0x1f
	eor r2, r6
	lsl r2, r2, #0x1f
	lsr r2, r2, #3
	orr r2, r3
	add r6, r4, #0
	add r3, r2, #0
	str r2, [r5]
	add r6, #0x8b
	lsl r2, r2, #2
	ldrb r6, [r6]
	lsr r2, r2, #0x1f
	and r3, r7
	eor r2, r6
	lsl r2, r2, #0x1f
	lsr r2, r2, #2
	orr r2, r3
	add r6, r4, #0
	add r3, r2, #0
	str r2, [r5]
	add r6, #0x8e
	lsl r2, r2, #0x13
	ldrb r6, [r6]
	lsr r2, r2, #0x1f
	and r3, r1
	eor r2, r6
	lsl r2, r2, #0x1f
	lsr r2, r2, #0x13
	orr r2, r3
	str r2, [r5]
	add r2, r0, #0
	add r5, #8
	sub r0, r0, #1
	cmp r2, #0
	bne _02253D98
_02253E30:
	ldr r4, [r4, #0x5c]
	cmp r4, #0
	beq _02253E38
	b _02253C96
_02253E38:
	ldr r0, [sp, #0xc]
	ldr r1, [r0, #0x14]
	cmp r5, r1
	bls _02253E52
	sub r3, r5, r1
	asr r2, r3, #2
	lsr r2, r2, #0x1d
	add r2, r3, r2
	lsl r2, r2, #0xd
	ldr r0, [r0]
	lsr r2, r2, #0x10
	bl NNS_G2dEntryOamManagerOam
_02253E52:
	add sp, #0x20
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02253E58: .word FX_SinCosTable_
_02253E5C: .word 0xDFFFFFFF
_02253E60: .word 0xFFFFF3FF
_02253E64: .word 0xFFFF0FFF
_02253E68: .word 0xFFFFFC00
_02253E6C: .word 0x000003FF
_02253E70: .word 0xEFFFFFFF
	thumb_func_end ov20_02253C78

	thumb_func_start ov20_02253E74
ov20_02253E74: ; 0x02253E74
	push {r3, r4, r5, r6, r7, lr}
	add r7, r0, #0
	add r5, r1, #0
	add r6, r2, #0
	bl ov20_02254068
	add r4, r0, #0
	beq _02253F10
	ldrb r1, [r5, #0xb]
	add r0, #0x82
	strh r1, [r0]
	add r0, r4, #0
	ldrb r1, [r5, #0xc]
	add r0, #0x80
	strh r1, [r0]
	add r0, r7, #0
	add r1, r4, #0
	bl ov20_022540A4
	ldr r0, [r6, #8]
	str r0, [r4]
	ldr r0, [r6, #0xc]
	str r0, [r4, #4]
	ldrh r1, [r5, #8]
	bl NNS_G2dGetAnimSequenceByIdx
	add r1, r0, #0
	add r0, r4, #0
	ldr r2, [r4]
	add r0, #8
	bl NNS_G2dInitCellAnimation
	ldr r1, [r5]
	ldr r0, [r5, #4]
	str r1, [r4, #0x64]
	add r1, r4, #0
	str r0, [r4, #0x68]
	mov r0, #0
	add r1, #0x84
	strh r0, [r1]
	add r1, r4, #0
	add r1, #0x88
	strh r0, [r1]
	ldrb r2, [r5, #0xa]
	mov r1, #1
	tst r2, r1
	beq _02253ED4
	add r0, r1, #0
_02253ED4:
	add r1, r4, #0
	add r1, #0x8a
	strb r0, [r1]
	ldrb r1, [r5, #0xa]
	mov r0, #2
	tst r0, r1
	beq _02253EE6
	mov r1, #1
	b _02253EE8
_02253EE6:
	mov r1, #0
_02253EE8:
	add r0, r4, #0
	add r0, #0x8b
	strb r1, [r0]
	add r1, r4, #0
	mov r0, #0
	add r1, #0x8e
	strb r0, [r1]
	add r1, r4, #0
	add r1, #0x8c
	strh r0, [r1]
	add r1, r4, #0
	add r1, #0x70
	str r1, [r4, #0x6c]
	add r1, r4, #0
	ldrb r2, [r5, #0xd]
	add r1, #0x87
	strb r2, [r1]
	add r1, r4, #0
	add r1, #0x86
	strb r0, [r1]
_02253F10:
	add r0, r4, #0
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end ov20_02253E74

	thumb_func_start ov20_02253F14
ov20_02253F14: ; 0x02253F14
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	bl ov20_022540FC
	add r0, r5, #0
	add r1, r4, #0
	bl ov20_02254080
	pop {r3, r4, r5, pc}
	thumb_func_end ov20_02253F14

	thumb_func_start ov20_02253F28
ov20_02253F28: ; 0x02253F28
	push {r4, lr}
	add r4, r0, #0
	lsl r1, r1, #0x10
	ldr r0, [r4, #4]
	lsr r1, r1, #0x10
	bl NNS_G2dGetAnimSequenceByIdx
	add r1, r0, #0
	add r0, r4, #0
	ldr r2, [r4]
	add r0, #8
	bl NNS_G2dInitCellAnimation
	pop {r4, pc}
	thumb_func_end ov20_02253F28

	thumb_func_start ov20_02253F44
ov20_02253F44: ; 0x02253F44
	ldr r0, [r0, #0x10]
	cmp r0, #0
	bne _02253F4E
	mov r0, #1
	bx lr
_02253F4E:
	mov r0, #0
	bx lr
	.align 2, 0
	thumb_func_end ov20_02253F44

	thumb_func_start ov20_02253F54
ov20_02253F54: ; 0x02253F54
	ldr r3, [r0, #0x64]
	add r1, r3, r1
	str r1, [r0, #0x64]
	ldr r1, [r0, #0x68]
	add r1, r1, r2
	str r1, [r0, #0x68]
	bx lr
	.align 2, 0
	thumb_func_end ov20_02253F54

	thumb_func_start ov20_02253F64
ov20_02253F64: ; 0x02253F64
	str r1, [r0, #0x64]
	str r2, [r0, #0x68]
	bx lr
	.align 2, 0
	thumb_func_end ov20_02253F64

	thumb_func_start ov20_02253F6C
ov20_02253F6C: ; 0x02253F6C
	ldr r3, [r0, #0x64]
	str r3, [r1]
	ldr r0, [r0, #0x68]
	str r0, [r2]
	bx lr
	.align 2, 0
	thumb_func_end ov20_02253F6C

	thumb_func_start ov20_02253F78
ov20_02253F78: ; 0x02253F78
	add r0, #0x86
	strb r1, [r0]
	bx lr
	.align 2, 0
	thumb_func_end ov20_02253F78

	thumb_func_start ov20_02253F80
ov20_02253F80: ; 0x02253F80
	push {r4, r5, r6, lr}
	add r5, r1, #0
	add r6, r0, #0
	add r4, r2, #0
	bl ov20_022540FC
	add r0, r5, #0
	add r0, #0x80
	strh r4, [r0]
	add r0, r6, #0
	add r1, r5, #0
	bl ov20_022540A4
	pop {r4, r5, r6, pc}
	thumb_func_end ov20_02253F80

	thumb_func_start ov20_02253F9C
ov20_02253F9C: ; 0x02253F9C
	add r0, #0x84
	strh r1, [r0]
	bx lr
	.align 2, 0
	thumb_func_end ov20_02253F9C

	thumb_func_start ov20_02253FA4
ov20_02253FA4: ; 0x02253FA4
	add r0, #0x88
	strh r1, [r0]
	bx lr
	.align 2, 0
	thumb_func_end ov20_02253FA4

	thumb_func_start ov20_02253FAC
ov20_02253FAC: ; 0x02253FAC
	add r0, #0x8e
	strb r1, [r0]
	bx lr
	.align 2, 0
	thumb_func_end ov20_02253FAC

	thumb_func_start ov20_02253FB4
ov20_02253FB4: ; 0x02253FB4
	add r0, #0x8c
	strh r1, [r0]
	bx lr
	.align 2, 0
	thumb_func_end ov20_02253FB4

	thumb_func_start ov20_02253FBC
ov20_02253FBC: ; 0x02253FBC
	push {r3, r4, r5, r6, r7, lr}
	ldr r4, [sp, #0x18]
	add r5, r0, #0
	add r6, r1, #0
	add r1, r2, #0
	add r7, r3, #0
	str r4, [r5, #0x10]
	add r0, r6, #0
	add r2, r4, #0
	bl GfGfxLoader_UncompressFromNarc
	str r0, [r5]
	add r0, r6, #0
	add r1, r7, #0
	add r2, r4, #0
	bl GfGfxLoader_UncompressFromNarc
	str r0, [r5, #4]
	ldr r0, [r5]
	cmp r0, #0
	beq _0225400E
	ldr r1, [r5, #4]
	cmp r1, #0
	beq _0225400E
	add r1, r5, #0
	add r1, #8
	bl NNS_G2dGetUnpackedCellBank
	cmp r0, #0
	bne _02253FFC
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_02253FFC:
	ldr r0, [r5, #4]
	add r5, #0xc
	add r1, r5, #0
	bl NNS_G2dGetUnpackedMCAnimBank
	cmp r0, #0
	bne _0225400E
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
_0225400E:
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end ov20_02253FBC

	thumb_func_start ov20_02254014
ov20_02254014: ; 0x02254014
	push {r4, lr}
	add r4, r0, #0
	ldr r1, [r4]
	cmp r1, #0
	beq _02254028
	ldr r0, [r4, #0x10]
	bl FreeToHeapExplicit
	mov r0, #0
	str r0, [r4]
_02254028:
	ldr r1, [r4, #4]
	cmp r1, #0
	beq _02254038
	ldr r0, [r4, #0x10]
	bl FreeToHeapExplicit
	mov r0, #0
	str r0, [r4, #4]
_02254038:
	pop {r4, pc}
	.align 2, 0
	thumb_func_end ov20_02254014

	thumb_func_start ov20_0225403C
ov20_0225403C: ; 0x0225403C
	push {r4, r5, r6, lr}
	add r6, r2, #0
	add r5, r0, #0
	add r0, r6, #0
	add r4, r1, #0
	sub r6, r6, #1
	cmp r0, #0
	beq _0225405E
_0225404C:
	add r0, r4, #0
	stmia r5!, {r4}
	bl ov20_02254060
	add r0, r6, #0
	add r4, #0x90
	sub r6, r6, #1
	cmp r0, #0
	bne _0225404C
_0225405E:
	pop {r4, r5, r6, pc}
	thumb_func_end ov20_0225403C

	thumb_func_start ov20_02254060
ov20_02254060: ; 0x02254060
	mov r1, #0
	str r1, [r0, #0x5c]
	str r1, [r0, #0x60]
	bx lr
	thumb_func_end ov20_02254060

	thumb_func_start ov20_02254068
ov20_02254068: ; 0x02254068
	ldrh r2, [r0, #0x12]
	ldrh r1, [r0, #0x10]
	cmp r2, r1
	bhs _0225407C
	add r1, r2, #1
	strh r1, [r0, #0x12]
	ldr r1, [r0, #4]
	lsl r0, r2, #2
	ldr r0, [r1, r0]
	bx lr
_0225407C:
	mov r0, #0
	bx lr
	thumb_func_end ov20_02254068

	thumb_func_start ov20_02254080
ov20_02254080: ; 0x02254080
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldrh r0, [r5, #0x12]
	add r4, r1, #0
	cmp r0, #0
	beq _022540A0
	add r0, r4, #0
	bl ov20_02254060
	ldrh r0, [r5, #0x12]
	sub r0, r0, #1
	strh r0, [r5, #0x12]
	ldrh r0, [r5, #0x12]
	ldr r1, [r5, #4]
	lsl r0, r0, #2
	str r4, [r1, r0]
_022540A0:
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end ov20_02254080

	thumb_func_start ov20_022540A4
ov20_022540A4: ; 0x022540A4
	push {r4, r5}
	ldr r3, [r0, #8]
	cmp r3, #0
	bne _022540B8
	str r1, [r0, #8]
	mov r0, #0
	str r0, [r1, #0x5c]
	str r0, [r1, #0x60]
	pop {r4, r5}
	bx lr
_022540B8:
	add r4, r1, #0
	add r4, #0x80
	ldr r5, [r4]
	add r2, r3, #0
_022540C0:
	add r4, r2, #0
	add r4, #0x80
	ldr r4, [r4]
	cmp r5, r4
	bhs _022540E2
	cmp r2, r3
	bne _022540D0
	str r1, [r0, #8]
_022540D0:
	ldr r0, [r2, #0x60]
	str r0, [r1, #0x60]
	cmp r0, #0
	beq _022540DA
	str r1, [r0, #0x5c]
_022540DA:
	str r2, [r1, #0x5c]
	str r1, [r2, #0x60]
	pop {r4, r5}
	bx lr
_022540E2:
	ldr r4, [r2, #0x5c]
	cmp r4, #0
	bne _022540F4
	str r1, [r2, #0x5c]
	str r2, [r1, #0x60]
	mov r0, #0
	str r0, [r1, #0x5c]
	pop {r4, r5}
	bx lr
_022540F4:
	add r2, r4, #0
	b _022540C0
	thumb_func_end ov20_022540A4

	thumb_func_start ov20_022540F8
ov20_022540F8: ; 0x022540F8
	pop {r4, r5}
	bx lr
	thumb_func_end ov20_022540F8

	thumb_func_start ov20_022540FC
ov20_022540FC: ; 0x022540FC
	ldr r2, [r1, #0x60]
	cmp r2, #0
	beq _02254118
	ldr r0, [r1, #0x5c]
	cmp r0, #0
	beq _02254112
	str r0, [r2, #0x5c]
	ldr r2, [r1, #0x60]
	ldr r0, [r1, #0x5c]
	str r2, [r0, #0x60]
	bx lr
_02254112:
	mov r0, #0
	str r0, [r2, #0x5c]
	bx lr
_02254118:
	ldr r3, [r1, #0x5c]
	cmp r3, #0
	beq _02254128
	mov r2, #0
	str r2, [r3, #0x60]
	ldr r1, [r1, #0x5c]
	str r1, [r0, #8]
	bx lr
_02254128:
	mov r1, #0
	str r1, [r0, #8]
	bx lr
	.align 2, 0
	thumb_func_end ov20_022540FC
