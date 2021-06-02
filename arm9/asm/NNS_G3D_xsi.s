	.include "asm/macros.inc"
	.include "global.inc"

	.section .data

	.global calcTexMtx_
calcTexMtx_: ; 0x021067F0
	.word texmtxCalc_flag_
	.word texmtxCalc_flagS_
	.word texmtxCalc_flagR_
	.word texmtxCalc_flagRS_
	.word texmtxCalc_flagT_
	.word texmtxCalc_flagTS_
	.word texmtxCalc_flagTR_
	.word texmtxCalc_flagTRS_

	.section .text

	arm_func_start NNSi_G3dSendTexSRTXsi
NNSi_G3dSendTexSRTXsi: ; 0x020BFA9C
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x50
	mov r4, r0
	ldr r0, [r4, #0x0]
	mov r3, #0x3
	ands r0, r0, #0x8
	ldrne r0, _020BFC1C ; =0x00101610
	mov r2, #0x2
	strne r0, [sp, #0x0]
	ldreq r0, _020BFC20 ; =0x00101810
	mov r1, #0x1000
	streq r0, [sp, #0x0]
	mov r0, #0x0
	str r3, [sp, #0x4]
	str r2, [sp, #0x48]
	str r1, [sp, #0x44]
	str r0, [sp, #0x40]
	str r0, [sp, #0x34]
	str r0, [sp, #0x30]
	str r0, [sp, #0x2c]
	str r0, [sp, #0x28]
	str r0, [sp, #0x24]
	str r0, [sp, #0x20]
	str r0, [sp, #0x14]
	str r0, [sp, #0x10]
	ldr r0, [r4, #0x0]
	ands r0, r0, #0x1
	strne r1, [r4, #0x1c]
	ldrne r0, [r4, #0x1c]
	strne r0, [r4, #0x18]
	ldr r0, [r4, #0x0]
	ands r0, r0, #0x2
	movne r0, #0x1000
	strneh r0, [r4, #0x22]
	movne r0, #0x0
	strneh r0, [r4, #0x20]
	ldr r0, [r4, #0x0]
	ands r0, r0, #0x4
	movne r0, #0x0
	strne r0, [r4, #0x28]
	ldrne r0, [r4, #0x28]
	strne r0, [r4, #0x24]
	ldr r1, [r4, #0x0]
	ldr r0, _020BFC24 ; =calcTexMtx_
	and r1, r1, #0x7
	ldr r2, [r0, r1, lsl #0x2]
	add r0, sp, #0x8
	mov r1, r4
	blx r2
	ldr r3, [r4, #0x30]
	cmp r3, #0x1000
	beq _020BFBB0
	ldr r0, [sp, #0x8]
	ldr r1, [sp, #0xc]
	smull r2, r0, r3, r0
	mov r2, r2, lsr #0xc
	orr r2, r2, r0, lsl #0x14
	str r2, [sp, #0x8]
	ldr r2, [r4, #0x30]
	ldr r0, [sp, #0x38]
	smull r3, r1, r2, r1
	mov r2, r3, lsr #0xc
	orr r2, r2, r1, lsl #0x14
	str r2, [sp, #0xc]
	ldr r1, [r4, #0x30]
	smull r2, r0, r1, r0
	mov r1, r2, lsr #0xc
	orr r1, r1, r0, lsl #0x14
	str r1, [sp, #0x38]
_020BFBB0:
	ldr r3, [r4, #0x34]
	cmp r3, #0x1000
	beq _020BFC00
	ldr r0, [sp, #0x18]
	ldr r1, [sp, #0x1c]
	smull r2, r0, r3, r0
	mov r2, r2, lsr #0xc
	orr r2, r2, r0, lsl #0x14
	str r2, [sp, #0x18]
	ldr r2, [r4, #0x34]
	ldr r0, [sp, #0x3c]
	smull r3, r1, r2, r1
	mov r2, r3, lsr #0xc
	orr r2, r2, r1, lsl #0x14
	str r2, [sp, #0x1c]
	ldr r1, [r4, #0x34]
	smull r2, r0, r1, r0
	mov r1, r2, lsr #0xc
	orr r1, r1, r0, lsl #0x14
	str r1, [sp, #0x3c]
_020BFC00:
	add r1, sp, #0x0
	ldr r0, [sp, #0x0]
	add r1, r1, #0x4
	mov r2, #0x12
	bl NNS_G3dGeBufferOP_N
	add sp, sp, #0x50
	ldmia sp!, {r4,pc}
	.balign 4
_020BFC1C: .word 0x00101610
_020BFC20: .word 0x00101810
_020BFC24: .word calcTexMtx_
	arm_func_end NNSi_G3dSendTexSRTXsi

	arm_func_start texmtxCalc_flagTRS_
texmtxCalc_flagTRS_: ; 0x020BFC28
	mov r2, #0x1000
	str r2, [r0, #0x0]
	mov r1, #0x0
	str r1, [r0, #0x4]
	str r1, [r0, #0x10]
	str r2, [r0, #0x14]
	str r1, [r0, #0x30]
	str r1, [r0, #0x34]
	bx lr
	arm_func_end texmtxCalc_flagTRS_

	arm_func_start texmtxCalc_flagTR_
texmtxCalc_flagTR_: ; 0x020BFC4C
	ldr r2, [r1, #0x18]
	mov r3, #0x0
	str r2, [r0, #0x0]
	ldr r2, [r1, #0x1c]
	str r2, [r0, #0x14]
	str r3, [r0, #0x4]
	str r3, [r0, #0x30]
	ldrh r2, [r1, #0x2e]
	ldr r1, [r1, #0x1c]
	rsb r2, r2, #0x0
	sub r1, r1, #0x1000
	mul r1, r2, r1
	mov r1, r1, lsl #0x4
	str r1, [r0, #0x34]
	str r3, [r0, #0x10]
	bx lr
	arm_func_end texmtxCalc_flagTR_

	arm_func_start texmtxCalc_flagTS_
texmtxCalc_flagTS_: ; 0x020BFC8C
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r5, r1
	ldrh r2, [r5, #0x2c]
	ldrh r1, [r5, #0x2e]
	mov r6, r0
	mov r4, r2, lsl #0xc
	mov r7, r1, lsl #0xc
	mov r0, r7
	mov r1, r4
	bl FX_DivAsync
	ldrsh r0, [r5, #0x22]
	str r0, [r6, #0x0]
	ldrsh r0, [r5, #0x22]
	str r0, [r6, #0x14]
	bl FX_GetDivResult
	ldrsh r2, [r5, #0x20]
	mov r1, r7
	mul r0, r2, r0
	mov r2, r0, asr #0xc
	mov r0, r4
	str r2, [r6, #0x4]
	bl FX_DivAsync
	ldrh r1, [r5, #0x2c]
	ldrsh r0, [r5, #0x20]
	mul r0, r1, r0
	mov r0, r0, lsl #0x4
	str r0, [r6, #0x30]
	ldrh r1, [r5, #0x2e]
	ldrsh r0, [r5, #0x22]
	rsb r1, r1, #0x0
	sub r0, r0, #0x1000
	mul r0, r1, r0
	mov r0, r0, lsl #0x4
	str r0, [r6, #0x34]
	bl FX_GetDivResult
	ldrsh r1, [r5, #0x20]
	rsb r1, r1, #0x0
	mul r0, r1, r0
	mov r0, r0, asr #0xc
	str r0, [r6, #0x10]
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
	arm_func_end texmtxCalc_flagTS_

	arm_func_start texmtxCalc_flagT_
texmtxCalc_flagT_: ; 0x020BFD38
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x4
	mov r9, r1
	ldrh r2, [r9, #0x2c]
	ldrh r1, [r9, #0x2e]
	mov r10, r0
	mov r8, r2, lsl #0xc
	mov r11, r1, lsl #0xc
	mov r0, r11
	mov r1, r8
	bl FX_DivAsync
	ldrsh r3, [r9, #0x22]
	ldr r0, [r9, #0x18]
	ldrsh r7, [r9, #0x20]
	ldr r5, [r9, #0x1c]
	smull r2, r1, r0, r3
	mov r2, r2, lsr #0xc
	orr r2, r2, r1, lsl #0x14
	str r2, [r10, #0x0]
	smull r2, r1, r5, r3
	mov r4, r2, lsr #0xc
	orr r4, r4, r1, lsl #0x14
	smull r2, r1, r0, r7
	mov r6, r2, lsr #0xc
	orr r6, r6, r1, lsl #0x14
	str r4, [r10, #0x14]
	bl FX_GetDivResult
	smull r2, r1, r5, r7
	mov r2, r2, lsr #0xc
	orr r2, r2, r1, lsl #0x14
	mul r0, r2, r0
	mov r0, r0, asr #0xc
	str r0, [r10, #0x4]
	mov r0, r8
	mov r1, r11
	bl FX_DivAsync
	sub r0, r4, #0x1000
	ldrh r1, [r9, #0x2c]
	mul r2, r1, r6
	mov r1, r2, lsl #0x4
	str r1, [r10, #0x30]
	ldrh r1, [r9, #0x2e]
	rsb r1, r1, #0x0
	mul r0, r1, r0
	mov r0, r0, lsl #0x4
	str r0, [r10, #0x34]
	bl FX_GetDivResult
	rsb r1, r6, #0x0
	mul r0, r1, r0
	mov r0, r0, asr #0xc
	str r0, [r10, #0x10]
	add sp, sp, #0x4
	ldmia sp!, {r4-r11,pc}
	arm_func_end texmtxCalc_flagT_

	arm_func_start texmtxCalc_flagRS_
texmtxCalc_flagRS_: ; 0x020BFE0C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r2, #0x1000
	str r2, [r0, #0x0]
	str r2, [r0, #0x14]
	mov lr, #0x0
	str lr, [r0, #0x4]
	ldr r2, [r1, #0x24]
	ldrh r3, [r1, #0x2c]
	rsb r2, r2, #0x0
	ldr r12, [r1, #0x28]
	mul r2, r3, r2
	mov r2, r2, lsl #0x4
	str r2, [r0, #0x30]
	ldrh r1, [r1, #0x2e]
	rsb r2, r12, #0x0
	rsb r1, r1, #0x0
	mul r2, r1, r2
	mov r1, r2, lsl #0x4
	str r1, [r0, #0x34]
	str lr, [r0, #0x10]
	add sp, sp, #0x4
	ldmia sp!, {pc}
	arm_func_end texmtxCalc_flagRS_

	arm_func_start texmtxCalc_flagR_
texmtxCalc_flagR_: ; 0x020BFE68
	stmdb sp!, {r4,lr}
	ldr r3, [r1, #0x18]
	mov r2, #0x0
	str r3, [r0, #0x0]
	ldr r3, [r1, #0x1c]
	str r3, [r0, #0x14]
	str r2, [r0, #0x4]
	ldr r12, [r1, #0x24]
	ldr r3, [r1, #0x18]
	ldr r4, [r1, #0x28]
	smull lr, r3, r12, r3
	mov r12, lr, lsr #0xc
	orr r12, r12, r3, lsl #0x14
	ldrh lr, [r1, #0x2c]
	rsb r3, r12, #0x0
	ldr r12, [r1, #0x1c]
	rsb r4, r4, #0x0
	mul r3, lr, r3
	smull lr, r12, r4, r12
	mov r3, r3, lsl #0x4
	str r3, [r0, #0x30]
	mov r4, lr, lsr #0xc
	ldrh r3, [r1, #0x2e]
	ldr r1, [r1, #0x1c]
	orr r4, r4, r12, lsl #0x14
	add r1, r1, r4
	rsb r3, r3, #0x0
	sub r1, r1, #0x1000
	mul r1, r3, r1
	mov r1, r1, lsl #0x4
	str r1, [r0, #0x34]
	str r2, [r0, #0x10]
	ldmia sp!, {r4,pc}
	arm_func_end texmtxCalc_flagR_

	arm_func_start texmtxCalc_flagS_
texmtxCalc_flagS_: ; 0x020BFEEC
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r5, r1
	ldrh r2, [r5, #0x2c]
	ldrh r1, [r5, #0x2e]
	mov r6, r0
	mov r4, r2, lsl #0xc
	mov r7, r1, lsl #0xc
	mov r0, r7
	mov r1, r4
	bl FX_DivAsync
	ldrsh r0, [r5, #0x22]
	str r0, [r6, #0x0]
	ldrsh r0, [r5, #0x22]
	str r0, [r6, #0x14]
	bl FX_GetDivResult
	ldrsh r2, [r5, #0x20]
	mov r1, r7
	mul r0, r2, r0
	mov r2, r0, asr #0xc
	mov r0, r4
	str r2, [r6, #0x4]
	bl FX_DivAsync
	ldrsh lr, [r5, #0x20]
	ldr r4, [r5, #0x28]
	ldrsh r0, [r5, #0x22]
	ldr r12, [r5, #0x24]
	smull r3, r2, r4, lr
	smlal r3, r2, r12, r0
	smull r1, r0, r4, r0
	mov r3, r3, lsr #0xc
	orr r3, r3, r2, lsl #0x14
	sub r4, lr, r3
	smull r3, r2, r12, lr
	subs r1, r3, r1
	sbc r0, r2, r0
	ldrh r2, [r5, #0x2c]
	mov r1, r1, lsr #0xc
	orr r1, r1, r0, lsl #0x14
	mul r0, r2, r4
	mov r0, r0, lsl #0x4
	str r0, [r6, #0x30]
	ldrsh r0, [r5, #0x22]
	ldrh r2, [r5, #0x2e]
	add r0, r0, r1
	rsb r1, r2, #0x0
	sub r0, r0, #0x1000
	mul r0, r1, r0
	mov r0, r0, lsl #0x4
	str r0, [r6, #0x34]
	bl FX_GetDivResult
	ldrsh r1, [r5, #0x20]
	rsb r1, r1, #0x0
	mul r0, r1, r0
	mov r0, r0, asr #0xc
	str r0, [r6, #0x10]
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
	arm_func_end texmtxCalc_flagS_

	arm_func_start texmtxCalc_flag_
texmtxCalc_flag_: ; 0x020BFFD4
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x4
	mov r6, r1
	ldrh r2, [r6, #0x2c]
	ldrh r1, [r6, #0x2e]
	mov r7, r0
	mov r10, r2, lsl #0xc
	mov r11, r1, lsl #0xc
	mov r0, r11
	mov r1, r10
	bl FX_DivAsync
	ldrsh r3, [r6, #0x22]
	ldr r0, [r6, #0x18]
	ldrsh r9, [r6, #0x20]
	smull r2, r1, r0, r3
	mov r2, r2, lsr #0xc
	ldr r8, [r6, #0x1c]
	orr r2, r2, r1, lsl #0x14
	str r2, [r7, #0x0]
	smull r2, r1, r8, r3
	mov r4, r2, lsr #0xc
	orr r4, r4, r1, lsl #0x14
	smull r2, r1, r0, r9
	mov r5, r2, lsr #0xc
	orr r5, r5, r1, lsl #0x14
	str r4, [r7, #0x14]
	bl FX_GetDivResult
	smull r2, r1, r8, r9
	mov r2, r2, lsr #0xc
	orr r2, r2, r1, lsl #0x14
	mul r0, r2, r0
	mov r0, r0, asr #0xc
	str r0, [r7, #0x4]
	mov r0, r10
	mov r1, r11
	bl FX_DivAsync
	ldr lr, [r6, #0x1c]
	ldrsh r2, [r6, #0x20]
	ldr r8, [r6, #0x24]
	ldr r0, [r6, #0x28]
	smull r10, r9, r8, r2
	ldrh r1, [r6, #0x2c]
	smull r3, r2, r0, r2
	ldrsh r12, [r6, #0x22]
	str r1, [sp, #0x0]
	mov r11, lr, asr #0x1f
	smlal r3, r2, r8, r12
	smull r8, r12, r0, r12
	subs r8, r10, r8
	sbc r0, r9, r12
	mov r9, r8, lsr #0xc
	mov r12, r3, lsr #0xc
	orr r9, r9, r0, lsl #0x14
	mov r3, r2, asr #0xc
	orr r12, r12, r2, lsl #0x14
	umull r10, r2, r9, lr
	mla r2, r9, r11, r2
	mov r8, r0, asr #0xc
	mla r2, r8, lr, r2
	ldr r1, [r6, #0x18]
	mov r8, r10, lsr #0xc
	orr r8, r8, r2, lsl #0x14
	add r2, r4, r8
	mov r0, r1, asr #0x1f
	umull r8, r4, r12, r1
	mla r4, r12, r0, r4
	mla r4, r3, r1, r4
	mov r0, r8, lsr #0xc
	orr r0, r0, r4, lsl #0x14
	sub r1, r5, r0
	ldr r0, [sp, #0x0]
	sub r2, r2, #0x1000
	mul r1, r0, r1
	mov r0, r1, lsl #0x4
	str r0, [r7, #0x30]
	ldrh r0, [r6, #0x2e]
	rsb r0, r0, #0x0
	mul r1, r0, r2
	mov r0, r1, lsl #0x4
	str r0, [r7, #0x34]
	bl FX_GetDivResult
	rsb r1, r5, #0x0
	mul r0, r1, r0
	mov r0, r0, asr #0xc
	str r0, [r7, #0x10]
	add sp, sp, #0x4
	ldmia sp!, {r4-r11,pc}
	arm_func_end texmtxCalc_flag_
