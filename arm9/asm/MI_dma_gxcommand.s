    .include "asm/macros.inc"
    .include "global.inc"

	.extern UNK_021D37FC

    .text

	arm_func_start MIi_DMAFastCallback
MIi_DMAFastCallback: ; 0x020CDE78
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, _020CDEB4 ; =UNK_021D37FC
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
_020CDEB4: .word UNK_021D37FC

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
	ldr r2, _020CDF6C ; =UNK_021D37FC
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
_020CDF6C: .word UNK_021D37FC
_020CDF70: .word MIi_DMAFastCallback
_020CDF74: .word 0x04000400

	arm_func_start MIi_DMACallback
MIi_DMACallback: ; 0x020CDF78
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r0, #0x200000
	bl OS_DisableIrqMask
	ldr r2, _020CDFE4 ; =0x04000600
	ldr r0, _020CDFE8 ; =UNK_021D37FC
	ldr r1, [r2, #0x0]
	ldr r3, [r0, #0x18]
	bic r1, r1, #0xc0000000
	orr r1, r1, r3, lsl #0x1e
	str r1, [r2, #0x0]
	ldr r1, [r0, #0x1c]
	mov r0, #0x200000
	bl OS_SetIrqFunction
	ldr r0, _020CDFE8 ; =UNK_021D37FC
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
_020CDFE8: .word UNK_021D37FC

	arm_func_start MIi_FIFOCallback
MIi_FIFOCallback: ; 0x020CDFEC
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r0, _020CE0A4 ; =UNK_021D37FC
	ldr r4, [r0, #0xc]
	cmp r4, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	ldr r0, _020CE0A4 ; =UNK_021D37FC
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
	ldr r1, _020CE0A4 ; =UNK_021D37FC
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
_020CE0A4: .word UNK_021D37FC
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
	ldr r0, _020CE1BC ; =UNK_021D37FC
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
	ldr ip, _020CE1BC ; =UNK_021D37FC
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
	ldr r1, _020CE1BC ; =UNK_021D37FC
	and r0, r0, #0xc0000000
	mov r2, r0, lsr #0x1e
	mov r0, #0x200000
	str r2, [r1, #0x18]
	bl OS_GetIrqFunction
	ldr r1, _020CE1BC ; =UNK_021D37FC
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
_020CE1BC: .word UNK_021D37FC
_020CE1C0: .word 0x04000600
_020CE1C4: .word MIi_FIFOCallback
