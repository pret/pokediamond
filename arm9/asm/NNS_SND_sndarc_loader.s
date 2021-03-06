	.include "asm/macros.inc"
	.include "global.inc"

	.section .bss

	.global waveArcHeader$8213
waveArcHeader$8213: ; 0x021D28C4
	.space 0x3c

	.section .text

	arm_func_start LoadSingleWaves
LoadSingleWaves: ; 0x020C2B1C
	stmdb sp!, {r4-r10,lr}
	sub sp, sp, #0x20
	mov r8, r0
	add r0, sp, #0x8
	mov r7, r1
	mov r6, r2
	mov r5, r3
	ldr r4, [sp, #0x40]
	bl SND_GetFirstInstDataPos
	ldr r1, [sp, #0x8]
	ldr r0, [sp, #0xc]
	str r1, [sp, #0x0]
	str r0, [sp, #0x4]
	cmp r7, #0x0
	add r2, sp, #0x0
	addeq sp, sp, #0x20
	moveq r0, #0x0
	ldmeqia sp!, {r4-r10,pc}
	add r1, sp, #0x10
	mov r0, r7
	bl SND_GetNextInstData
	cmp r0, #0x0
	beq _020C2BD4
	add r10, sp, #0x10
	add r9, sp, #0x0
_020C2B80:
	ldrb r0, [sp, #0x10]
	cmp r0, #0x1
	bne _020C2BBC
	ldrh r0, [sp, #0x14]
	cmp r6, r0
	bne _020C2BBC
	ldrh r1, [sp, #0x12]
	mov r0, r8
	mov r2, r5
	mov r3, r4
	bl LoadSingleWave
	cmp r0, #0x0
	addeq sp, sp, #0x20
	moveq r0, #0x0
	ldmeqia sp!, {r4-r10,pc}
_020C2BBC:
	mov r0, r7
	mov r1, r10
	mov r2, r9
	bl SND_GetNextInstData
	cmp r0, #0x0
	bne _020C2B80
_020C2BD4:
	mov r0, #0x1
	add sp, sp, #0x20
	ldmia sp!, {r4-r10,pc}

	arm_func_start LoadSingleWave
LoadSingleWave: ; 0x020C2BE0
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	mov r7, r0
	mov r6, r1
	mov r5, r2
	mov r4, r3
	bl SND_GetWaveDataAddress
	cmp r0, #0x0
	addne sp, sp, #0x4
	movne r0, #0x1
	ldmneia sp!, {r4-r9,pc}
	mov r0, r7
	bl SND_GetWaveDataCount
	ldr r1, [r7, #0x38]
	sub r0, r0, #0x1
	add r1, r1, r6
	add r1, r7, r1, lsl #0x2
	cmp r6, r0
	ldrcc r0, [r1, #0x40]
	ldr r8, [r1, #0x3c]
	ldrcs r0, [r7, #0x8]
	cmp r4, #0x0
	sub r9, r0, r8
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r9,pc}
	ldr r2, _020C2CBC ; =SingleWaveDisposeCallback
	mov r0, r4
	mov r3, r7
	add r1, r9, #0x20
	str r6, [sp, #0x0]
	bl NNS_SndHeapAlloc
	movs r4, r0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r9,pc}
	mov r0, r5
	mov r1, r4
	mov r2, r9
	mov r3, r8
	bl NNS_SndArcReadFile
	cmp r9, r0
	addne sp, sp, #0x4
	movne r0, #0x0
	ldmneia sp!, {r4-r9,pc}
	mov r0, r4
	mov r1, r9
	bl DC_StoreRange
	mov r0, r7
	mov r1, r6
	mov r2, r4
	bl SND_SetWaveDataAddress
	mov r0, #0x1
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,pc}
	.balign 4
_020C2CBC: .word SingleWaveDisposeCallback

	arm_func_start SingleWaveDisposeCallback
SingleWaveDisposeCallback: ; 0x020C2CC0
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r5, r2
	mov r7, r0
	mov r4, r3
	mov r6, r1
	mov r0, r5
	mov r1, r4
	bl SND_GetWaveDataAddress
	cmp r7, r0
	bne _020C2CFC
	mov r0, r5
	mov r1, r4
	mov r2, #0x0
	bl SND_SetWaveDataAddress
_020C2CFC:
	mov r0, r7
	add r1, r7, r6
	bl SND_InvalidateWaveData
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}

	arm_func_start WaveArcTableDisposeCallback
WaveArcTableDisposeCallback: ; 0x020C2D10
	stmdb sp!, {r4,lr}
	mov r1, r2
	mov r4, r0
	mov r2, r3
	bl DisposeCallback
	mov r0, r4
	bl SND_DestroyWaveArc
	ldmia sp!, {r4,pc}

	arm_func_start WaveArcDisposeCallback
WaveArcDisposeCallback: ; 0x020C2D30
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r4, r1
	mov r1, r2
	mov r5, r0
	mov r2, r3
	bl DisposeCallback
	mov r0, r5
	add r1, r5, r4
	bl SND_InvalidateWaveData
	mov r0, r5
	bl SND_DestroyWaveArc
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}

	arm_func_start BankDisposeCallback
BankDisposeCallback: ; 0x020C2D68
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r4, r1
	mov r1, r2
	mov r5, r0
	mov r2, r3
	bl DisposeCallback
	mov r0, r5
	add r1, r5, r4
	bl SND_InvalidateBankData
	mov r0, r5
	bl SND_DestroyBank
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}

	arm_func_start SeqDisposeCallback
SeqDisposeCallback: ; 0x020C2DA0
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r4, r1
	mov r1, r2
	mov r5, r0
	mov r2, r3
	bl DisposeCallback
	mov r0, r5
	add r1, r5, r4
	bl SND_InvalidateSeqData
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}

	arm_func_start DisposeCallback
DisposeCallback: ; 0x020C2DD0
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	movs r5, r1
	mov r7, r0
	mov r6, r2
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,pc}
	bl OS_DisableInterrupts
	mov r4, r0
	mov r0, r5
	bl NNS_SndArcSetCurrent
	mov r5, r0
	mov r0, r6
	bl NNS_SndArcGetFileAddress
	cmp r7, r0
	bne _020C2E1C
	mov r0, r6
	mov r1, #0x0
	bl NNS_SndArcSetFileAddress
_020C2E1C:
	mov r0, r5
	bl NNS_SndArcSetCurrent
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}

	arm_func_start LoadWaveArcTable
LoadWaveArcTable: ; 0x020C2E34
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	mov r9, r0
	mov r8, r1
	mov r7, r2
	bl NNS_SndArcGetFileAddress
	movs r6, r0
	bne _020C2F40
	ldr r1, _020C2F4C ; =waveArcHeader$8213
	mov r0, r9
	mov r2, #0x3c
	mov r3, #0x0
	bl NNS_SndArcReadFile
	cmp r0, #0x3c
	addne sp, sp, #0x4
	movne r0, #0x0
	ldmneia sp!, {r4-r9,pc}
	ldr r0, _020C2F4C ; =waveArcHeader$8213
	cmp r8, #0x0
	ldr r0, [r0, #0x38]
	addeq sp, sp, #0x4
	mov r4, r0, lsl #0x2
	mov r0, r4, lsl #0x1
	add r5, r0, #0x3c
	moveq r0, #0x0
	ldmeqia sp!, {r4-r9,pc}
	cmp r7, #0x0
	moveq r3, #0x0
	beq _020C2EB0
	bl NNS_SndArcGetCurrent
	mov r3, r0
_020C2EB0:
	ldr r2, _020C2F50 ; =WaveArcTableDisposeCallback
	mov r0, r8
	add r1, r5, #0x20
	str r9, [sp, #0x0]
	bl NNS_SndHeapAlloc
	movs r6, r0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r9,pc}
	mov r0, r9
	mov r1, r6
	add r2, r4, #0x3c
	mov r3, #0x0
	bl NNS_SndArcReadFile
	add r1, r4, #0x3c
	cmp r0, r1
	addne sp, sp, #0x4
	movne r0, #0x0
	ldmneia sp!, {r4-r9,pc}
	ldr r1, [r6, #0x38]
	add r0, r6, #0x3c
	mov r2, r4
	add r1, r0, r1, lsl #0x2
	bl MI_CpuCopy8
	mov r2, r4
	add r0, r6, #0x3c
	mov r1, #0x0
	bl MI_CpuFill8
	mov r0, r6
	mov r1, r5
	bl DC_StoreRange
	cmp r7, #0x0
	beq _020C2F40
	mov r0, r9
	mov r1, r6
	bl NNS_SndArcSetFileAddress
_020C2F40:
	mov r0, r6
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,pc}
	.balign 4
_020C2F4C: .word waveArcHeader$8213
_020C2F50: .word WaveArcTableDisposeCallback

	arm_func_start LoadWaveArc
LoadWaveArc: ; 0x020C2F54
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, r0
	mov r6, r1
	mov r5, r2
	bl NNS_SndArcGetFileAddress
	movs r4, r0
	bne _020C2FBC
	cmp r5, #0x0
	moveq r2, #0x0
	beq _020C2F88
	bl NNS_SndArcGetCurrent
	mov r2, r0
_020C2F88:
	ldr r1, _020C2FC8 ; =WaveArcDisposeCallback
	mov r0, r7
	mov r3, r7
	str r6, [sp, #0x0]
	bl NNSi_SndArcLoadFile
	mov r4, r0
	cmp r5, #0x0
	beq _020C2FBC
	cmp r4, #0x0
	beq _020C2FBC
	mov r0, r7
	mov r1, r4
	bl NNS_SndArcSetFileAddress
_020C2FBC:
	mov r0, r4
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
	.balign 4
_020C2FC8: .word WaveArcDisposeCallback

	arm_func_start LoadBank
LoadBank: ; 0x020C2FCC
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, r0
	mov r6, r1
	mov r5, r2
	bl NNS_SndArcGetFileAddress
	movs r4, r0
	bne _020C3034
	cmp r5, #0x0
	moveq r2, #0x0
	beq _020C3000
	bl NNS_SndArcGetCurrent
	mov r2, r0
_020C3000:
	ldr r1, _020C3040 ; =BankDisposeCallback
	mov r0, r7
	mov r3, r7
	str r6, [sp, #0x0]
	bl NNSi_SndArcLoadFile
	mov r4, r0
	cmp r5, #0x0
	beq _020C3034
	cmp r4, #0x0
	beq _020C3034
	mov r0, r7
	mov r1, r4
	bl NNS_SndArcSetFileAddress
_020C3034:
	mov r0, r4
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
	.balign 4
_020C3040: .word BankDisposeCallback

	arm_func_start LoadSeqArc
LoadSeqArc: ; 0x020C3044
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, r0
	mov r6, r1
	mov r5, r2
	bl NNS_SndArcGetFileAddress
	movs r4, r0
	bne _020C30AC
	cmp r5, #0x0
	moveq r2, #0x0
	beq _020C3078
	bl NNS_SndArcGetCurrent
	mov r2, r0
_020C3078:
	ldr r1, _020C30B8 ; =SeqDisposeCallback
	mov r0, r7
	mov r3, r7
	str r6, [sp, #0x0]
	bl NNSi_SndArcLoadFile
	mov r4, r0
	cmp r5, #0x0
	beq _020C30AC
	cmp r4, #0x0
	beq _020C30AC
	mov r0, r7
	mov r1, r4
	bl NNS_SndArcSetFileAddress
_020C30AC:
	mov r0, r4
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
	.balign 4
_020C30B8: .word SeqDisposeCallback

	arm_func_start LoadSeq
LoadSeq: ; 0x020C30BC
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, r0
	mov r6, r1
	mov r5, r2
	bl NNS_SndArcGetFileAddress
	movs r4, r0
	bne _020C3124
	cmp r5, #0x0
	moveq r2, #0x0
	beq _020C30F0
	bl NNS_SndArcGetCurrent
	mov r2, r0
_020C30F0:
	ldr r1, _020C3130 ; =SeqDisposeCallback
	mov r0, r7
	mov r3, r7
	str r6, [sp, #0x0]
	bl NNSi_SndArcLoadFile
	mov r4, r0
	cmp r5, #0x0
	beq _020C3124
	cmp r4, #0x0
	beq _020C3124
	mov r0, r7
	mov r1, r4
	bl NNS_SndArcSetFileAddress
_020C3124:
	mov r0, r4
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
	.balign 4
_020C3130: .word SeqDisposeCallback

	arm_func_start NNSi_SndArcLoadFile
NNSi_SndArcLoadFile: ; 0x020C3134
	stmdb sp!, {r4-r8,lr}
	sub sp, sp, #0x8
	mov r8, r0
	mov r7, r1
	mov r6, r2
	mov r4, r3
	bl NNS_SndArcGetFileSize
	movs r5, r0
	addeq sp, sp, #0x8
	moveq r0, #0x0
	ldmeqia sp!, {r4-r8,pc}
	ldr r0, [sp, #0x20]
	cmp r0, #0x0
	addeq sp, sp, #0x8
	moveq r0, #0x0
	ldmeqia sp!, {r4-r8,pc}
	mov r2, r7
	mov r3, r6
	add r1, r5, #0x20
	str r4, [sp, #0x0]
	bl NNS_SndHeapAlloc
	movs r4, r0
	addeq sp, sp, #0x8
	moveq r0, #0x0
	ldmeqia sp!, {r4-r8,pc}
	mov r0, r8
	mov r1, r4
	mov r2, r5
	mov r3, #0x0
	bl NNS_SndArcReadFile
	cmp r5, r0
	addne sp, sp, #0x8
	movne r0, #0x0
	ldmneia sp!, {r4-r8,pc}
	mov r0, r4
	mov r1, r5
	bl DC_StoreRange
	mov r0, r4
	add sp, sp, #0x8
	ldmia sp!, {r4-r8,pc}

	arm_func_start NNSi_SndArcLoadWaveArc
NNSi_SndArcLoadWaveArc: ; 0x020C31D4
	stmdb sp!, {r4-r6,lr}
	mov r6, r1
	mov r5, r2
	mov r4, r3
	bl NNS_SndArcGetWaveArcInfo
	cmp r0, #0x0
	moveq r0, #0x5
	ldmeqia sp!, {r4-r6,pc}
	ands r1, r6, #0x4
	beq _020C324C
	ldrb r1, [r0, #0x3]
	ands r1, r1, #0x1
	beq _020C3224
	ldr r0, [r0, #0x0]
	mov r1, r5
	mov r0, r0, lsl #0x8
	mov r2, r4
	mov r0, r0, lsr #0x8
	bl LoadWaveArcTable
	b _020C323C
_020C3224:
	ldr r0, [r0, #0x0]
	mov r1, r5
	mov r0, r0, lsl #0x8
	mov r2, r4
	mov r0, r0, lsr #0x8
	bl LoadWaveArc
_020C323C:
	cmp r0, #0x0
	bne _020C325C
	mov r0, #0x9
	ldmia sp!, {r4-r6,pc}
_020C324C:
	ldr r0, [r0, #0x0]
	mov r0, r0, lsl #0x8
	mov r0, r0, lsr #0x8
	bl NNS_SndArcGetFileAddress
_020C325C:
	ldr r1, [sp, #0x10]
	cmp r1, #0x0
	strne r0, [r1, #0x0]
	mov r0, #0x0
	ldmia sp!, {r4-r6,pc}

	arm_func_start NNSi_SndArcLoadBank
NNSi_SndArcLoadBank: ; 0x020C3270
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0xc
	mov r10, r1
	mov r9, r2
	mov r11, r3
	bl NNS_SndArcGetBankInfo
	movs r8, r0
	addeq sp, sp, #0xc
	moveq r0, #0x4
	ldmeqia sp!, {r4-r11,pc}
	ands r0, r10, #0x2
	beq _020C32C4
	ldr r0, [r8, #0x0]
	mov r1, r9
	mov r2, r11
	bl LoadBank
	movs r7, r0
	bne _020C32D0
	add sp, sp, #0xc
	mov r0, #0x8
	ldmia sp!, {r4-r11,pc}
_020C32C4:
	ldr r0, [r8, #0x0]
	bl NNS_SndArcGetFileAddress
	mov r7, r0
_020C32D0:
	and r5, r10, #0x4
	mov r6, #0x0
_020C32D8:
	add r0, r8, r6, lsl #0x1
	ldrh r0, [r0, #0x4]
	ldr r1, _020C33B4 ; =0x0000FFFF
	cmp r0, r1
	beq _020C3390
	bl NNS_SndArcGetWaveArcInfo
	movs r4, r0
	addeq sp, sp, #0xc
	moveq r0, #0x5
	ldmeqia sp!, {r4-r11,pc}
	add r0, sp, #0x4
	str r0, [sp, #0x0]
	add r0, r8, r6, lsl #0x1
	ldrh r0, [r0, #0x4]
	mov r1, r10
	mov r2, r9
	mov r3, r11
	bl NNSi_SndArcLoadWaveArc
	cmp r0, #0x0
	addne sp, sp, #0xc
	ldmneia sp!, {r4-r11,pc}
	ldrb r0, [r4, #0x3]
	ands r0, r0, #0x1
	beq _020C3370
	cmp r5, #0x0
	beq _020C3370
	str r9, [sp, #0x0]
	ldr r1, [r4, #0x0]
	ldr r0, [sp, #0x4]
	mov r3, r1, lsl #0x8
	mov r1, r7
	mov r2, r6
	mov r3, r3, lsr #0x8
	bl LoadSingleWaves
	cmp r0, #0x0
	addeq sp, sp, #0xc
	moveq r0, #0x9
	ldmeqia sp!, {r4-r11,pc}
_020C3370:
	cmp r7, #0x0
	beq _020C3390
	ldr r2, [sp, #0x4]
	cmp r2, #0x0
	beq _020C3390
	mov r0, r7
	mov r1, r6
	bl SND_AssignWaveArc
_020C3390:
	add r6, r6, #0x1
	cmp r6, #0x4
	blt _020C32D8
	ldr r0, [sp, #0x30]
	cmp r0, #0x0
	strne r7, [r0, #0x0]
	mov r0, #0x0
	add sp, sp, #0xc
	ldmia sp!, {r4-r11,pc}
	.balign 4
_020C33B4: .word 0x0000FFFF

	arm_func_start NNSi_SndArcLoadSeqArc
NNSi_SndArcLoadSeqArc: ; 0x020C33B8
	stmdb sp!, {r4-r6,lr}
	mov r6, r1
	mov r5, r2
	mov r4, r3
	bl NNS_SndArcGetSeqArcInfo
	cmp r0, #0x0
	moveq r0, #0x3
	ldmeqia sp!, {r4-r6,pc}
	ands r1, r6, #0x8
	beq _020C3400
	ldr r0, [r0, #0x0]
	mov r1, r5
	mov r2, r4
	bl LoadSeqArc
	cmp r0, #0x0
	bne _020C3408
	mov r0, #0x7
	ldmia sp!, {r4-r6,pc}
_020C3400:
	ldr r0, [r0, #0x0]
	bl NNS_SndArcGetFileAddress
_020C3408:
	ldr r1, [sp, #0x10]
	cmp r1, #0x0
	strne r0, [r1, #0x0]
	mov r0, #0x0
	ldmia sp!, {r4-r6,pc}

	arm_func_start NNSi_SndArcLoadSeq
NNSi_SndArcLoadSeq: ; 0x020C341C
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, r1
	mov r6, r2
	mov r5, r3
	bl NNS_SndArcGetSeqInfo
	movs r4, r0
	addeq sp, sp, #0x4
	moveq r0, #0x2
	ldmeqia sp!, {r4-r7,pc}
	mov r0, #0x0
	str r0, [sp, #0x0]
	ldrh r0, [r4, #0x4]
	mov r1, r7
	mov r2, r6
	mov r3, r5
	bl NNSi_SndArcLoadBank
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r7,pc}
	ands r0, r7, #0x1
	beq _020C3498
	ldr r0, [r4, #0x0]
	mov r1, r6
	mov r2, r5
	bl LoadSeq
	cmp r0, #0x0
	bne _020C34A0
	add sp, sp, #0x4
	mov r0, #0x6
	ldmia sp!, {r4-r7,pc}
_020C3498:
	ldr r0, [r4, #0x0]
	bl NNS_SndArcGetFileAddress
_020C34A0:
	ldr r1, [sp, #0x18]
	cmp r1, #0x0
	strne r0, [r1, #0x0]
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}

	arm_func_start NNSi_SndArcLoadGroup
NNSi_SndArcLoadGroup: ; 0x020C34B8
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0xc
	mov r9, r1
	bl NNS_SndArcGetGroupInfo
	movs r8, r0
	addeq sp, sp, #0xc
	moveq r0, #0x1
	ldmeqia sp!, {r4-r11,pc}
	ldr r0, [r8, #0x0]
	mov r7, #0x0
	cmp r0, #0x0
	bls _020C35D4
	add r6, r8, #0x4
	str r7, [sp, #0x4]
	mov r11, r7
	mov r10, r7
	mov r5, r7
	mov r4, #0x1
_020C3500:
	ldrb r0, [r6, #0x0]
	cmp r0, #0x3
	addls pc, pc, r0, lsl #0x2
	b _020C35C0
	; Jump table
	b _020C3520 ; case 0
	b _020C3570 ; case 1
	b _020C3598 ; case 2
	b _020C3548 ; case 3
_020C3520:
	str r5, [sp, #0x0]
	ldrb r1, [r6, #0x1]
	ldr r0, [r6, #0x4]
	mov r2, r9
	mov r3, r4
	bl NNSi_SndArcLoadSeq
	cmp r0, #0x0
	beq _020C35C0
	add sp, sp, #0xc
	ldmia sp!, {r4-r11,pc}
_020C3548:
	str r10, [sp, #0x0]
	ldrb r1, [r6, #0x1]
	ldr r0, [r6, #0x4]
	mov r2, r9
	mov r3, r4
	bl NNSi_SndArcLoadSeqArc
	cmp r0, #0x0
	beq _020C35C0
	add sp, sp, #0xc
	ldmia sp!, {r4-r11,pc}
_020C3570:
	str r11, [sp, #0x0]
	ldrb r1, [r6, #0x1]
	ldr r0, [r6, #0x4]
	mov r2, r9
	mov r3, r4
	bl NNSi_SndArcLoadBank
	cmp r0, #0x0
	beq _020C35C0
	add sp, sp, #0xc
	ldmia sp!, {r4-r11,pc}
_020C3598:
	ldr r0, [sp, #0x4]
	mov r2, r9
	str r0, [sp, #0x0]
	ldrb r1, [r6, #0x1]
	ldr r0, [r6, #0x4]
	mov r3, r4
	bl NNSi_SndArcLoadWaveArc
	cmp r0, #0x0
	addne sp, sp, #0xc
	ldmneia sp!, {r4-r11,pc}
_020C35C0:
	ldr r0, [r8, #0x0]
	add r7, r7, #0x1
	cmp r7, r0
	add r6, r6, #0x8
	blo _020C3500
_020C35D4:
	mov r0, #0x0
	add sp, sp, #0xc
	ldmia sp!, {r4-r11,pc}

	arm_func_start NNS_SndArcLoadSeqEx
NNS_SndArcLoadSeqEx: ; 0x020C35E0
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r12, #0x0
	mov r3, #0x1
	str r12, [sp, #0x0]
	bl NNSi_SndArcLoadSeq
	cmp r0, #0x0
	moveq r0, #0x1
	movne r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {pc}

	arm_func_start NNS_SndArcLoadWaveArc
NNS_SndArcLoadWaveArc: ; 0x020C360C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r2, r1
	mov r12, #0x0
	mov r1, #0xff
	mov r3, #0x1
	str r12, [sp, #0x0]
	bl NNSi_SndArcLoadWaveArc
	cmp r0, #0x0
	moveq r0, #0x1
	movne r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {pc}

	arm_func_start NNS_SndArcLoadBank
NNS_SndArcLoadBank: ; 0x020C3640
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r2, r1
	mov r12, #0x0
	mov r1, #0xff
	mov r3, #0x1
	str r12, [sp, #0x0]
	bl NNSi_SndArcLoadBank
	cmp r0, #0x0
	moveq r0, #0x1
	movne r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {pc}

	arm_func_start NNS_SndArcLoadSeq
NNS_SndArcLoadSeq: ; 0x020C3674
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r2, r1
	mov r12, #0x0
	mov r1, #0xff
	mov r3, #0x1
	str r12, [sp, #0x0]
	bl NNSi_SndArcLoadSeq
	cmp r0, #0x0
	moveq r0, #0x1
	movne r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {pc}

	arm_func_start NNS_SndArcLoadGroup
NNS_SndArcLoadGroup: ; 0x020C36A8
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	bl NNSi_SndArcLoadGroup
	cmp r0, #0x0
	moveq r0, #0x1
	movne r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {pc}
