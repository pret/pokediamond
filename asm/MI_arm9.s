	.include "asm/macros.inc"
	.include "global.inc"
	.section .text


	arm_func_start MI_SetWramBank
MI_SetWramBank:
	ldr r1, _020CD870 ; =0x04000247
	strb r0, [r1, #0x0]
	bx lr
	.balign 4
_020CD870: .word 0x04000247

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

	arm_func_start MI_HBlankDmaCopy16
MI_HBlankDmaCopy16: ; 0x020CDD90
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r6, r1
	mov r7, r0
	mov r4, r3
	mov r1, #0x10000000
	mov r5, r2
	bl MIi_CheckAnotherAutoDMA
	mov r0, r7
	mov r1, r6
	mov r2, r4
	mov r3, #0x0
	bl MIi_CheckDma0SourceAddress
_020CDDC4:
	cmp r4, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7, lr}
	bxeq lr
	mov r0, r7
	bl MI_WaitDma
	ldr r3, _020CDE00
	mov r0, r7
	mov r1, r6
	mov r2, r5
	orr r3, r3, r4, lsr #0x1
	bl MIi_DmaSetParams
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
_020CDE00: .word 0x92600000

	arm_func_start MI_HBlankDmaCopy32
MI_HBlankDmaCopy32: ; 0x020CDE04
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r6, r1
	mov r7, r0
	mov r4, r3
	mov r1, #0x10000000
	mov r5, r2
	bl MIi_CheckAnotherAutoDMA
	mov r0, r7
	mov r1, r6
	mov r2, r4
	mov r3, #0x0
	bl MIi_CheckDma0SourceAddress
_020CDE38:
	cmp r4, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	mov r0, r7
	bl MI_WaitDma
	ldr r3, _020CDE74
	mov r0, r7
	mov r1, r6
	mov r2, r5
	orr r3, r3, r4, lsr #0x2
	bl MIi_DmaSetParams
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
_020CDE74: .word 0x96600000

	arm_func_start MIi_DMAFastCallback
MIi_DMAFastCallback: ; 0x020CDE78
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, _020CDEB4 ; =0x021D37FC
	mov r2, #0x0
	ldr r1, [r0, #0x10]
	str r2, [r0, #0x0]
	cmp r1, #0x0
	addeq sp, sp, #0x4
	ldr r0, [r0, #0x14]
	ldmeqia sp!, {lr}
	bxeq lr
	blx r1
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020CDEB4: .word 0x021D37FC

	arm_func_start MI_SendGXCommandAsyncFast
MI_SendGXCommandAsyncFast: ; 0x020CDEB8
	stmdb sp!, {r4-r6,lr}
	movs r4, r2
	mov r6, r0
	mov r5, r1
	bne _020CDEE8
	cmp r3, #0x0
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	ldr r0, [sp, #0x10]
	blx r3
	ldmia sp!, {r4-r6,lr}
	bx lr
_020CDEE8:
	ldr r2, _020CDF6C ; =0x021D37FC
	ldr r0, [r2, #0x0]
	cmp r0, #0x0
	bne _020CDEE8
	ldr r12, [sp, #0x10]
	mov lr, #0x1
	mov r0, r6
	mov r1, #0x38000000
	str lr, [r2, #0x0]
	str r6, [r2, #0x4]
	str r3, [r2, #0x10]
	str r12, [r2, #0x14]
	bl MIi_CheckAnotherAutoDMA
	mov r0, r6
	mov r1, r5
	mov r2, r4
	mov r3, #0x0
	bl MIi_CheckDma0SourceAddress
	mov r0, r6
	bl MI_WaitDma
	mov r0, r6
	ldr r1, _020CDF70 ; =MIi_DMAFastCallback
	mov r2, #0x0
	bl OSi_EnterDmaCallback
	mov r0, r6
	mov r1, r5
	ldr r2, _020CDF74 ; =0x04000400
	mov r3, #0x3c00000
	rsb r3, r3, #0x0
	orr r3, r3, r4, lsr #0x2
	bl MIi_DmaSetParams
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020CDF6C: .word 0x021D37FC
_020CDF70: .word MIi_DMAFastCallback
_020CDF74: .word 0x04000400

	arm_func_start MIi_DMACallback
MIi_DMACallback: ; 0x020CDF78
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r0, #0x200000
	bl OS_DisableIrqMask
	ldr r2, _020CDFE4 ; =0x04000600
	ldr r0, _020CDFE8 ; =0x021D37FC
	ldr r1, [r2, #0x0]
	ldr r3, [r0, #0x18]
	bic r1, r1, #0xc0000000
	orr r1, r1, r3, lsl #0x1e
	str r1, [r2, #0x0]
	ldr r1, [r0, #0x1c]
	mov r0, #0x200000
	bl OS_SetIrqFunction
	ldr r0, _020CDFE8 ; =0x021D37FC
	mov r2, #0x0
	ldr r1, [r0, #0x10]
	str r2, [r0, #0x0]
	cmp r1, #0x0
	addeq sp, sp, #0x4
	ldr r0, [r0, #0x14]
	ldmeqia sp!, {lr}
	bxeq lr
	blx r1
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020CDFE4: .word 0x04000600
_020CDFE8: .word 0x021D37FC

	arm_func_start MIi_FIFOCallback
MIi_FIFOCallback: ; 0x020CDFEC
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r0, _020CE0A4 ; =0x021D37FC
	ldr r4, [r0, #0xc]
	cmp r4, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	ldr r0, _020CE0A4 ; =0x021D37FC
	cmp r4, #0x1d8
	ldr r5, [r0, #0x8]
	movcs r4, #0x1d8
	ldr r2, [r0, #0xc]
	add r1, r5, r4
	subs r2, r2, r4
	str r2, [r0, #0xc]
	str r1, [r0, #0x8]
	bne _020CE078
	ldr r0, [r0, #0x4]
	ldr r1, _020CE0A8 ; =MIi_DMACallback
	mov r2, #0x0
	bl OSi_EnterDmaCallback
	mov r0, #0x3bc00000
	rsb r3, r0, #0x0
	ldr r1, _020CE0A4 ; =0x021D37FC
	ldr r2, _020CE0AC ; =0x04000400
	ldr r0, [r1, #0x4]
	mov r1, r5
	orr r3, r3, r4, lsr #0x2
	bl MIi_DmaSetParams
	mov r0, #0x200000
	bl OS_ResetRequestIrqMask
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
_020CE078:
	ldr r3, _020CE0B0 ; =0x84400000
	ldr r0, [r0, #0x4]
	ldr r2, _020CE0AC ; =0x04000400
	mov r1, r5
	orr r3, r3, r4, lsr #0x2
	bl MIi_DmaSetParams
	mov r0, #0x200000
	bl OS_ResetRequestIrqMask
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020CE0A4: .word 0x021D37FC
_020CE0A8: .word MIi_DMACallback
_020CE0AC: .word 0x04000400
_020CE0B0: .word 0x84400000

	arm_func_start MI_SendGXCommandAsync
MI_SendGXCommandAsync: ; 0x020CE0B4
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r4, r0
	cmp r2, #0x0
	bne _020CE0EC
	cmp r3, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	ldr r0, [sp, #0x10]
	blx r3
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
_020CE0EC:
	ldr r0, _020CE1BC ; =0x021D37FC
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _020CE0EC
	ldr r5, _020CE1C0 ; =0x04000600
_020CE100:
	ldr r0, [r5, #0x0]
	and r0, r0, #0x7000000
	mov r0, r0, lsr #0x18
	ands r0, r0, #0x2
	beq _020CE100
	ldr ip, _020CE1BC ; =0x021D37FC
	ldr lr, [sp, #0x10]
	str r3, [r12, #0x10]
	mov r5, #0x1
	mov r0, r4
	mov r3, #0x0
	str r5, [r12, #0x0]
	str r4, [r12, #0x4]
	str r1, [r12, #0x8]
	str r2, [r12, #0xc]
	str lr, [r12, #0x14]
	bl MIi_CheckDma0SourceAddress
	mov r0, r4
	bl MI_WaitDma
	bl OS_DisableInterrupts
	ldr r1, _020CE1C0 ; =0x04000600
	mov r4, r0
	ldr r0, [r1, #0x0]
	ldr r1, _020CE1BC ; =0x021D37FC
	and r0, r0, #0xc0000000
	mov r2, r0, lsr #0x1e
	mov r0, #0x200000
	str r2, [r1, #0x18]
	bl OS_GetIrqFunction
	ldr r1, _020CE1BC ; =0x021D37FC
	ldr r2, _020CE1C0 ; =0x04000600
	str r0, [r1, #0x1c]
	ldr r0, [r2, #0x0]
	ldr r1, _020CE1C4 ; =MIi_FIFOCallback
	bic r0, r0, #0xc0000000
	orr r3, r0, #0x40000000
	mov r0, #0x200000
	str r3, [r2, #0x0]
	bl OS_SetIrqFunction
	mov r0, #0x200000
	bl OS_EnableIrqMask
	bl MIi_FIFOCallback
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020CE1BC: .word 0x021D37FC
_020CE1C0: .word 0x04000600
_020CE1C4: .word MIi_FIFOCallback

	arm_func_start MIi_CpuClear16
MIi_CpuClear16: ; 0x020CE1C8
	mov r3, #0x0
_020CE1CC:
	cmp r3, r2
	strlth r0, [r1, r3]
	addlt r3, r3, #0x2
	blt _020CE1CC
	bx lr

	arm_func_start MIi_CpuCopy16
MIi_CpuCopy16: ; 0x020CE1E0
	mov r12, #0x0
_020CE1E4:
	cmp r12, r2
	ldrlth r3, [r0, r12]
	strlth r3, [r1, r12]
	addlt r12, r12, #0x2
	blt _020CE1E4
	bx lr

	arm_func_start MIi_CpuClear32
MIi_CpuClear32: ; 0x020CE1FC
	add r12, r1, r2
_020CE200:
	cmp r1, r12
	stmltia r1!, {r0}
	blt _020CE200
	bx lr

	arm_func_start MIi_CpuCopy32
MIi_CpuCopy32: ; 0x020CE210
	add r12, r1, r2
_020CE214:
	cmp r1, r12
	ldmltia r0!, {r2}
	stmltia r1!, {r2}
	blt _020CE214
	bx lr

	arm_func_start MIi_CpuSend32
MIi_CpuSend32: ; 0x020CE228
	add r12, r0, r2
_020CE22C:
	cmp r0, r12
	ldmltia r0!, {r2}
	strlt r2, [r1, #0x0]
	blt _020CE22C
	bx lr

	arm_func_start MIi_CpuClearFast
MIi_CpuClearFast: ; 0x020CE240
	stmdb sp!, {r4-r9}
	add r9, r1, r2
	mov r12, r2, lsr #0x5
	add r12, r1, r12, lsl #0x5
	mov r2, r0
	mov r3, r2
	mov r4, r2
	mov r5, r2
	mov r6, r2
	mov r7, r2
	mov r8, r2
_020CE26C:
	cmp r1, r12
	stmltia r1!, {r0,r2-r8}
	blt _020CE26C
_020CE278:
	cmp r1, r9
	stmltia r1!, {r0}
	blt _020CE278
	ldmia sp!, {r4-r9}
	bx lr

	arm_func_start MIi_CpuCopyFast
MIi_CpuCopyFast: ; 0x020CE28C
	stmdb sp!, {r4-r10}
	add r10, r1, r2
	mov r12, r2, lsr #0x5
	add r12, r1, r12, lsl #0x5
_020CE29C:
	cmp r1, r12
	ldmltia r0!, {r2-r9}
	stmltia r1!, {r2-r9}
	blt _020CE29C
_020CE2AC:
	cmp r1, r10
	ldmltia r0!, {r2}
	stmltia r1!, {r2}
	blt _020CE2AC
	ldmia sp!, {r4-r10}
	bx lr

	arm_func_start FUN_020CE2C4
FUN_020CE2C4:
	ldmia r0!, {r2, r3, ip}
	stmia r1!, {r2, r3, ip}
	ldmia r0!, {r2, r3, ip}
	stmia r1!, {r2, r3, ip}
	ldmia r0!, {r2, r3}
	stmia r1!, {r2, r3}
	bx lr

	arm_func_start MI_Copy36B
MI_Copy36B: ; 0x020CE2E0
	ldmia r0!, {r2-r3,r12}
	stmia r1!, {r2-r3,r12}
	ldmia r0!, {r2-r3,r12}
	stmia r1!, {r2-r3,r12}
	ldmia r0!, {r2-r3,r12}
	stmia r1!, {r2-r3,r12}
	bx lr

	arm_func_start MI_Copy48B
MI_Copy48B: ; 0x020CE2FC
	ldmia r0!, {r2-r3,r12}
	stmia r1!, {r2-r3,r12}
	ldmia r0!, {r2-r3,r12}
	stmia r1!, {r2-r3,r12}
	ldmia r0!, {r2-r3,r12}
	stmia r1!, {r2-r3,r12}
	ldmia r0!, {r2-r3,r12}
	stmia r1!, {r2-r3,r12}
	bx lr

	arm_func_start MI_Copy64B
MI_Copy64B: ; 0x020CE320
	ldmia r0!, {r2-r3,r12}
	stmia r1!, {r2-r3,r12}
	ldmia r0!, {r2-r3,r12}
	stmia r1!, {r2-r3,r12}
	ldmia r0!, {r2-r3,r12}
	stmia r1!, {r2-r3,r12}
	ldmia r0!, {r2-r3,r12}
	stmia r1!, {r2-r3,r12}
	ldmia r0, {r0,r2-r3,r12}
	stmia r1!, {r0,r2-r3,r12}
	bx lr

	arm_func_start MI_CpuFill8
MI_CpuFill8: ; 0x020CE34C
	cmp r2, #0x0
	bxeq lr
	tst r0, #0x1
	beq _020CE378
	ldrh r12, [r0, #-0x1]
	and r12, r12, #0xff
	orr r3, r12, r1, lsl #0x8
	strh r3, [r0, #-0x1]
	add r0, r0, #0x1
	subs r2, r2, #0x1
	bxeq lr
_020CE378:
	cmp r2, #0x2
	blo _020CE3C0
	orr r1, r1, r1, lsl #0x8
	tst r0, #0x2
	beq _020CE398
	strh r1, [r0], #0x2
	subs r2, r2, #0x2
	bxeq lr
_020CE398:
	orr r1, r1, r1, lsl #0x10
	bics r3, r2, #0x3
	beq _020CE3B8
	sub r2, r2, r3
	add r12, r3, r0
_020CE3AC:
	str r1, [r0], #0x4
	cmp r0, r12
	blo _020CE3AC
_020CE3B8:
	tst r2, #0x2
	strneh r1, [r0], #0x2
_020CE3C0:
	tst r2, #0x1
	bxeq lr
	ldrh r3, [r0, #0x0]
	and r3, r3, #0xff00
	and r1, r1, #0xff
	orr r1, r1, r3
	strh r1, [r0, #0x0]
	bx lr

	arm_func_start MI_CpuCopy8
MI_CpuCopy8:
	cmp r2, #0x0
	bxeq lr
	tst r1, #0x1
	beq _020CE420
	ldrh r12, [r1, #-0x1]
	and r12, r12, #0xff
	tst r0, #0x1
	ldrneh r3, [r0, #-0x1]
	movne r3, r3, lsr #0x8
	ldreqh r3, [r0, #0x0]
	orr r3, r12, r3, lsl #0x8
	strh r3, [r1, #-0x1]
	add r0, r0, #0x1
	add r1, r1, #0x1
	subs r2, r2, #0x1
	bxeq lr
_020CE420:
	eor r12, r1, r0
	tst r12, #0x1
	beq _020CE474
	bic r0, r0, #0x1
	ldrh r12, [r0], #0x2
	mov r3, r12, lsr #0x8
	subs r2, r2, #0x2
	blo _020CE458
_020CE440:
	ldrh r12, [r0], #0x2
	orr r12, r3, r12, lsl #0x8
	strh r12, [r1], #0x2
	mov r3, r12, lsr #0x10
	subs r2, r2, #0x2
	bhs _020CE440
_020CE458:
	tst r2, #0x1
	bxeq lr
	ldrh r12, [r1, #0x0]
	and r12, r12, #0xff00
	orr r12, r12, r3
	strh r12, [r1, #0x0]
	bx lr
_020CE474:
	tst r12, #0x2
	beq _020CE4A0
	bics r3, r2, #0x1
	beq _020CE4EC
	sub r2, r2, r3
	add r12, r3, r1
_020CE48C:
	ldrh r3, [r0], #0x2
	strh r3, [r1], #0x2
	cmp r1, r12
	blo _020CE48C
	b _020CE4EC
_020CE4A0:
	cmp r2, #0x2
	blo _020CE4EC
	tst r1, #0x2
	beq _020CE4C0
	ldrh r3, [r0], #0x2
	strh r3, [r1], #0x2
	subs r2, r2, #0x2
	bxeq lr
_020CE4C0:
	bics r3, r2, #0x3
	beq _020CE4E0
	sub r2, r2, r3
	add r12, r3, r1
_020CE4D0:
	ldr r3, [r0], #0x4
	str r3, [r1], #0x4
	cmp r1, r12
	blo _020CE4D0
_020CE4E0:
	tst r2, #0x2
	ldrneh r3, [r0], #0x2
	strneh r3, [r1], #0x2
_020CE4EC:
	tst r2, #0x1
	bxeq lr
	ldrh r2, [r1, #0x0]
	ldrh r0, [r0, #0x0]
	and r2, r2, #0xff00
	and r0, r0, #0xff
	orr r0, r2, r0
	strh r0, [r1, #0x0]
	bx lr

	thumb_func_start MI_Zero36B
MI_Zero36B: ; 0x020CE510
	mov r1, #0x0
	mov r2, #0x0
	mov r3, #0x0
	stmia r0!, {r1-r3}
	stmia r0!, {r1-r3}
	stmia r0!, {r1-r3}
	bx lr

	arm_func_start MI_SwapWord
MI_SwapWord: ; 0x020CE520
	swp r0, r0, [r1]
	bx lr

	arm_func_start MI_UncompressLZ8
MI_UncompressLZ8: ; 0x020CE528
	stmdb sp!, {r4-r6,lr}
	ldr r5, [r0], #0x4
	mov r2, r5, lsr #0x8
_020CE534:
	cmp r2, #0x0
	ble _020CE5B4
	ldrb lr, [r0], #0x1
	mov r4, #0x8
_020CE544:
	subs r4, r4, #0x1
	blt _020CE534
	tst lr, #0x80
	bne _020CE568
	ldrb r6, [r0], #0x1
	.word 0xE1416096
	add r1, r1, #0x1
	sub r2, r2, #0x1
	b _020CE5A4
_020CE568:
	ldrb r5, [r0, #0x0]
	mov r6, #0x3
	add r3, r6, r5, asr #0x4
	ldrb r6, [r0], #0x1
	and r5, r6, #0xf
	mov r12, r5, lsl #0x8
	ldrb r6, [r0], #0x1
	orr r5, r6, r12
	add r12, r5, #0x1
	sub r2, r2, r3
_020CE590:
	ldrb r5, [r1, -r12]
	.word 0xE1415095
	add r1, r1, #0x1
	subs r3, r3, #0x1
	bgt _020CE590
_020CE5A4:
	cmp r2, #0x0
	movgt lr, lr, lsl #0x1
	bgt _020CE544
	b _020CE534
_020CE5B4:
	ldmia sp!, {r4-r6,lr}
	bx lr

	arm_func_start MIi_CardDmaCopy32
MIi_CardDmaCopy32: ; 0x020CE5BC
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r5, r1
	mov r6, r0
	mov r7, r3
	mvn r1, #0x0
	mov r4, r2
	bl MIi_CheckAnotherAutoDMA
	mov r0, r6
	mov r1, r5
	mov r2, r7
	mov r3, #0x1000000
	bl MIi_CheckDma0SourceAddress
_020CE5F0:
	cmp r7, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7, lr}
	bxeq lr
	mov r0, #0x3
	mul r1, r6, r0
	ldr r0, _020CE640
	add r1, r1, #0x2
	add r1, r0, r1, lsl #0x2
_020CE614:
	ldr r0, [r1]
	ands r0, r0, #0x80000000
	bne _020CE614
	ldr r3, _020CE644
	mov r0, r6
	mov r1, r5
	mov r2, r4
	bl MIi_DmaSetParams
	add sp, sp, #0x4
	ldmia sp!, {r4-r7, lr}
	bx lr
_020CE640: .word 0x040000B0
_020CE644: .word 0xAf000001

	arm_func_start MI_Init
MI_Init: ; 0x020CE648
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r0, #0x3
	bl MI_SetWramBank
	mov r0, #0x0
	bl MI_StopDma
	add sp, sp, #0x4
	ldmfd sp!, {lr}
	bx lr

