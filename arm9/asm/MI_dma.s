	.include "asm/macros.inc"
	.include "global.inc"

    .text

	arm_func_start MIi_CheckDma0SourceAddress
MIi_CheckDma0SourceAddress:
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {lr}
	bxne lr
	cmp r3, #0x0
	and r0, r1, #0xff000000
	beq _020CD8A4
	cmp r3, #0x800000
	subeq r1, r1, r2
	b _020CD8A8
_020CD8A4:
	add r1, r1, r2
_020CD8A8:
	cmp r0, #0x4000000
	beq _020CD8D4
	cmp r0, #0x8000000
	bhs _020CD8D4
	and r0, r1, #0xff000000
	cmp r0, #0x4000000
	beq _020CD8D4
	cmp r0, #0x8000000
	addcc sp, sp, #0x4
	ldmccia sp!, {lr}
	bxcc lr
_020CD8D4:
	bl OS_Terminate
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start MIi_CheckAnotherAutoDMA
MIi_CheckAnotherAutoDMA: ; 0x020CD8E4
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	ldr r4, _020CD994 ; =0x040000B8
	mov r7, r0
	mov r6, r1
	mov r5, #0x0
_020CD8FC:
	cmp r5, r7
	beq _020CD978
	ldr r1, [r4, #0x0]
	ands r0, r1, #0x80000000
	beq _020CD978
	and r0, r1, #0x38000000
	cmp r0, r6
	beq _020CD978
	cmp r0, #0x8000000
	bne _020CD92C
	cmp r6, #0x10000000
	beq _020CD978
_020CD92C:
	cmp r0, #0x10000000
	bne _020CD93C
	cmp r6, #0x8000000
	beq _020CD978
_020CD93C:
	cmp r0, #0x18000000
	beq _020CD974
	cmp r0, #0x20000000
	beq _020CD974
	cmp r0, #0x28000000
	beq _020CD974
	cmp r0, #0x30000000
	beq _020CD974
	cmp r0, #0x38000000
	beq _020CD974
	cmp r0, #0x8000000
	beq _020CD974
	cmp r0, #0x10000000
	bne _020CD978
_020CD974:
	bl OS_Terminate
_020CD978:
	add r5, r5, #0x1
	cmp r5, #0x3
	add r4, r4, #0xc
	blt _020CD8FC
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_020CD994: .word 0x040000B8

	arm_func_start MI_StopDma
MI_StopDma: ; 0x020CD998
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl OS_DisableInterrupts
	mov r1, #0x6
	mul r1, r4, r1
	add r1, r1, #0x5
	mov r1, r1, lsl #0x1
	add r1, r1, #0x4000000
	ldrh r2, [r1, #0xb0]
	cmp r4, #0x0
	bic r2, r2, #0x3a00
	strh r2, [r1, #0xb0]
	ldrh r2, [r1, #0xb0]
	bic r2, r2, #0x8000
	strh r2, [r1, #0xb0]
	ldrh r2, [r1, #0xb0]
	ldrh r1, [r1, #0xb0]
	bne _020CDA08
	mov r1, #0xc
	mul r12, r4, r1
	ldr r1, _020CDA14 ; =0x040000B0
	add r2, r12, #0x4000000
	mov r3, #0x0
	str r3, [r2, #0xb0]
	add r2, r12, r1
	ldr r1, _020CDA18 ; =0x81400001
	str r3, [r2, #0x4]
	str r1, [r2, #0x8]
_020CDA08:
	bl OS_RestoreInterrupts
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020CDA14: .word 0x040000B0
_020CDA18: .word 0x81400001

	arm_func_start MI_WaitDma
MI_WaitDma:
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl OS_DisableInterrupts
	mov r1, #0x3
	mul r2, r4, r1
	ldr r1, _020CDA84 ; =0x040000B0
	add r2, r2, #0x2
	add r2, r1, r2, lsl #0x2
_020CDA3C:
	ldr r1, [r2, #0x0]
	ands r1, r1, #0x80000000
	bne _020CDA3C
	cmp r4, #0x0
	bne _020CDA78
	mov r1, #0xc
	mul r12, r4, r1
	ldr r1, _020CDA84 ; =0x040000B0
	add r2, r12, #0x4000000
	mov r3, #0x0
	str r3, [r2, #0xb0]
	add r2, r12, r1
	ldr r1, _020CDA88 ; =0x81400001
	str r3, [r2, #0x4]
	str r1, [r2, #0x8]
_020CDA78:
	bl OS_RestoreInterrupts
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020CDA84: .word 0x040000B0
_020CDA88: .word 0x81400001

	arm_func_start MI_DmaCopy32Async
MI_DmaCopy32Async: ; 0x020CDA8C
	stmdb sp!, {r4-r8,lr}
	mov r5, r3
	mov r6, r2
	mov r2, r5
	mov r3, #0x0
	mov r8, r0
	mov r7, r1
	ldr r4, [sp, #0x18]
	bl MIi_CheckDma0SourceAddress
_020CDAB0:
	cmp r5, #0x0
	bne _020CDAD4
	cmp r4, #0x0
	ldmeqia sp!, {r4-r8, lr}
	bxeq lr
	ldr r0, [sp, #0x1C]
	blx r4
	ldmia sp!, {r4-r8, lr}
	bx lr
_020CDAD4:
	mov r0, r8
	bl MI_WaitDma
	cmp r4, #0x0
	beq _020CDB14
	ldr r2, [sp, #0x1C]
	mov r0, r8
	mov r1, r4
	bl OSi_EnterDmaCallback
	mov r3, r5, lsr #0x2
	mov r0, r8
	mov r1, r7
	mov r2, r6
	orr r3, r3, #0xc4000000
	bl MIi_DmaSetParams
	ldmia sp!, {r4-r8, lr}
	bx lr
_020CDB14:
	mov r3, r5, lsr #0x2
	mov r0, r8
	mov r1, r7
	mov r2, r6
	orr r3, r3, #0x84000000
	bl MIi_DmaSetParams
	ldmia sp!, {r4-r8, lr}
	bx lr

	arm_func_start MI_DmaFill32Async
MI_DmaFill32Async: ; 0x020CDB34
	stmdb sp!, {r4-r8,lr}
	movs r4, r3
	mov r7, r0
	mov r6, r1
	mov r5, r2
	ldr r8, [sp, #0x18]
	bne _020CDB6C
	cmp r8, #0x0
	ldmeqia sp!, {r4-r8,lr}
	bxeq lr
	ldr r0, [sp, #0x1c]
	blx r8
	ldmia sp!, {r4-r8,lr}
	bx lr
_020CDB6C:
	bl MI_WaitDma
_020CDB70:
	cmp r8, #0x0
	beq _020CDBC8
	ldr r2, [sp, #0x1C]
	mov r0, r7
	mov r1, r8
	bl OSi_EnterDmaCallback
	bl OS_DisableInterrupts
	mov r3, r4, lsr #2
	ldr r1, _20CDC08
	mov r2, r7, lsl #2
	add r2, r2, #0x4000000
	str r5, [r2, #0xE0]
	mov r4, r0
	add r1, r1, r7, lsl #0x2
	mov r0, r7
	mov r2, r6
	orr r3, r3, #0xc5000000
	bl MIi_DmaSetParams_noInt
	mov r0, r4
	bl OS_RestoreInterrupts
	ldmia sp!, {r4-r8,lr}
	bx lr
_020CDBC8:
	bl OS_DisableInterrupts
	ldr r1, _20CDC08
	mov r2, r7, lsl #0x2
	mov r3, r4, lsr #0x2
	mov r4, r0
	add ip, r2, #0x4000000
	mov r0, r7
	mov r2, r6
	add r1, r1, r7, lsl #0x2
	orr r3, r3, #0x85000000
	str r5, [ip, #0xE0]
	bl MIi_DmaSetParams_noInt
	mov r0, r4
	bl OS_RestoreInterrupts
	ldmia sp!, {r4-r8,lr}
	bx lr
_20CDC08: .word 0x040000E0

	arm_func_start MI_DmaCopy16
MI_DmaCopy16: ; 0x020CDC0C
	stmdb sp!, {r4-r8,lr}
	movs r5, r3
	mov r8, r0
	mov r7, r1
	mov r6, r2
	ldmeqia sp!, {r4-r8,lr}
	bxeq lr
	mov r2, r5
	mov r3, #0x0
	bl MIi_CheckDma0SourceAddress
	mov r0, #0x3
	mul r1, r8, r0
	ldr r0, _020CDC80 ; =0x040000B0
	add r1, r1, #0x2
	add r4, r0, r1, lsl #0x2
_020CDC48:
	ldr r0, [r4, #0x0]
	ands r0, r0, #0x80000000
	bne _020CDC48
	mov r3, r5, lsr #0x1
	mov r0, r8
	mov r1, r7
	mov r2, r6
	orr r3, r3, #0x80000000
	bl MIi_DmaSetParams_wait
_020CDC6C:
	ldr r0, [r4]
	ands r0, r0, #0x80000000
	bne _020CDC6C
	ldmia sp!, {r4-r8,lr}
	bx lr
_020CDC80: .word 0x040000B0

	arm_func_start MI_DmaCopy32
MI_DmaCopy32: ; 0x020CDC84
	stmdb sp!, {r4-r8,lr}
	mov r5, r3
	mov r6, r2
	mov r2, r5
	mov r3, #0x0
	mov r8, r0
	mov r7, r1
	bl MIi_CheckDma0SourceAddress
_020CDCA4:
	cmp r5, #0x0
	ldmeqia sp!, {r4-r8,lr}
	bxeq lr
	mov r0, #0x3
	mul r1, r8, r0
	ldr r0, _020CDCFC
	add r1, r1, #0x2
	add r4, r0, r1, lsl #0x2
_020CDCC4:
	ldr r0, [r4]
	ands r0, r0, #0x80000000
	bne _020CDCC4
	mov r3, r5, lsr #0x2
	mov r0, r8
	mov r1, r7
	mov r2, r6
	orr r3, r3, #0x84000000
	bl MIi_DmaSetParams_wait
_020CDCE8:
	ldr r0, [r4]
	ands r0, r0, #0x80000000
	bne _020CDCE8
	ldmia sp!, {r4-r8,lr}
	bx lr
_020CDCFC: .word 0x040000B0

	arm_func_start MI_DmaFill32
MI_DmaFill32: ; 0x020CDD00
	stmdb sp!, {r4-r8,lr}
	movs r4, r3
	mov r8, r0
	mov r7, r1
	mov r6, r2
	ldmeqia sp!, {r4-r8,lr}
	bxeq lr
	mov r0, #0x3
	mul r1, r8, r0
	ldr r0, _020CDD88 ; =0x040000B0
	add r1, r1, #0x2
	add r5, r0, r1, lsl #0x2
_020CDD30:
	ldr r0, [r5, #0x0]
	ands r0, r0, #0x80000000
	bne _020CDD30
	bl OS_DisableInterrupts
	ldr r1, _020CDD8C ; =0x040000E0
	mov r2, r8, lsl #0x2
	mov r3, r4, lsr #0x2
	mov r4, r0
	add r12, r2, #0x4000000
	mov r0, r8
	mov r2, r7
	add r1, r1, r8, lsl #0x2
	orr r3, r3, #0x85000000
	str r6, [r12, #0xe0]
	bl MIi_DmaSetParams_wait_noInt
	mov r0, r4
	bl OS_RestoreInterrupts
_020CDD74:
	ldr r0, [r5]
	ands r0, r0, #0x80000000
	bne _020CDD74
	ldmia sp!, {r4-r8,lr}
	bx lr
_020CDD88: .word 0x040000B0
_020CDD8C: .word 0x040000E0
